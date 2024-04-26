#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include <omp.h>
#include "DS_timer.h"
#include "DS_definitions.h"

#define RAND() (rand()/(RAND_MAX + 1.0))

int dataSize = 1024 * 1024 * 1024;
double dataMin = 0.0;
double dataMax = 10.0;

int numBins;
int numThreads;
double *data;
int *serialBins;
int *version1Bins;
int *version2Bins;
int **version2LocalBins;
int **version3LocalBins;
double rangeSize;
bool skipVersion1 = false;

void init(int argc, char **argv) {
    srand((unsigned) time(NULL));

    numBins = atoi(argv[1]);
    rangeSize = (dataMax - dataMin) / (double) numBins;
    dataMin = argc <= 2 ? dataMin : atof(argv[2]);
    dataMax = argc <= 3 ? dataMax : atof(argv[3]);
    dataSize = argc <= 4 ? dataSize : atoi(argv[4]);
    int numThreadLimit = argc <= 5 ? omp_get_max_threads() : atoi(argv[5]);
    for (numThreads = 1; numThreads << 1 <= numThreadLimit; numThreads <<= 1);
    skipVersion1 = argc <= 6 ? skipVersion1 : atoi(argv[6]);

    data = new double[dataSize];
    for (int i = 0; i < dataSize; i++) {
        data[i] = dataMin + (dataMax - dataMin) * RAND();
    }

    serialBins = new int[numBins];
    std::fill(serialBins, serialBins + numBins, 0);

    version1Bins = new int[numBins];
    std::fill(version1Bins, version1Bins + numBins, 0);

    version2Bins = new int[numBins];
    std::fill(version2Bins, version2Bins + numBins, 0);

    version2LocalBins = new int *[numThreads];
    for (int i = 0; i < numThreads; i++) {
        version2LocalBins[i] = new int[numBins];
        std::fill(version2LocalBins[i], version2LocalBins[i] + numBins, 0);
    }

    version3LocalBins = new int *[numThreads];
    for (int i = 0; i < numThreads; i++) {
        version3LocalBins[i] = new int[numBins];
        std::fill(version3LocalBins[i], version3LocalBins[i] + numBins, 0);
    }
}

void free(void) {
    delete[] data;
    delete[] serialBins;
    delete[] version1Bins;

    delete[] version2Bins;
    for (int i = 0; i < numThreads; i++) {
        delete[] version2LocalBins[i];
    }
    delete[] version2LocalBins;

    for (int i = 0; i < numThreads; i++) {
        delete[] version3LocalBins[i];
    }
    delete[] version3LocalBins;
}

/**
 * 주어진 빈 배열 출력 및 검증
 */
void printBins(char *name, int *bins) {
    printf("[%s bins]\n", name);
    int sum = 0;
    for (int i = 0; i < numBins; i++) {
        printf("[%2d] %5.2lf ~ %5.2lf: %d %s\n", i, rangeSize * i, rangeSize * (i + 1), bins[i],
               serialBins[i] == bins[i] ? "(valid)" : "(invalid)");
        sum += bins[i];
    }
    printf("[%2c] %d %s\n", 'S', sum, sum == dataSize ? "(valid)" : "(invalid)");
}

/**
 * 루프 카운트 수 계산
 */
inline int getLoopCount(int threads, int tid) {
    int loopCount = 0;
    for (int gap = 1; gap <= threads; gap *= 2) {
        loopCount += tid % gap == 0;
    }
    return loopCount - (tid == 0);
}

/**
 * bins의 baseTID에 targetTID를 병합
 */
inline void mergeBins(int **bins, int baseTID, int targetTID, bool even = true) {
    for (int i = even ? 0 : 1; i < numBins; i += 2) {
        bins[baseTID][i] += bins[targetTID][i];
    }
}

int main(int argc, char **argv) {
    DS_timer timer(4);
    timer.setTimerName(0, (char *) "Serial");
    timer.setTimerName(1, (char *) "Version1");
    timer.setTimerName(2, (char *) "Version2");
    timer.setTimerName(3, (char *) "Version3");

    if (argc < 2) {
        printf("Usage: Execution_file [numBins] [dataMin (optional)] [dataMax (optional)] [dataSize (optional)] [numThread (optional)] [skipVersion1 (optional)]\n");
        return -1;
    }

    init(argc, argv);

    printf("numBins = %d, numThreads: %d\n", numBins, numThreads);
    printf("range: %.2lf ~ %.2lf (rangeSize: %.2lf) x%d\n", dataMin, dataMax, rangeSize, dataSize);
    printf("skipVersion1: %s\n", skipVersion1 ? "true" : "false");

    //** 1. Serial code **//
    timer.onTimer(0);
    for (int i = 0; i < dataSize; i++) {
        int index = (int) ((data[i] - dataMin) / rangeSize);
        serialBins[index]++;
    }
    timer.offTimer(0);
    printBins((char *) "Serial", serialBins);

    //** 2. Version 1 **//
    timer.onTimer(1);
        if(!skipVersion1) {
            omp_lock_t v1BinLock;
            omp_init_lock(&v1BinLock);
            #pragma omp parallel for num_threads(numThreads)
            for (int i = 0; i < dataSize; i++) {
                int index = (int) ((data[i] - dataMin) / rangeSize);
                omp_set_lock(&v1BinLock);
                version1Bins[index]++;
                omp_unset_lock(&v1BinLock);
            }
            omp_destroy_lock(&v1BinLock);
        }
    timer.offTimer(1);
    printBins((char *) "Version1", version1Bins);

    //** 3. Version 2 **//
    timer.onTimer(2);
    #pragma omp parallel num_threads(numThreads)
    {
        int tid = omp_get_thread_num();
        #pragma omp for nowait
        for (int i = 0; i < dataSize; i++) {
            int index = (int) ((data[i] - dataMin) / rangeSize);
            version2LocalBins[tid][index]++;
        }

        for (int i = 0; i < numBins; i++) {
            #pragma omp atomic
            version2Bins[i] += version2LocalBins[tid][i];
            // 원자적 연산을 통한 빈 합치기
        }
    }

    timer.offTimer(2);
    printBins((char *) "Version2", version2Bins);


    //** 4. Version 3 **//
    timer.onTimer(3);
    #pragma omp parallel num_threads(numThreads)
    {
        int tid = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < dataSize; i++) {
            int index = (int) ((data[i] - dataMin) / rangeSize);
            version3LocalBins[tid][index]++;
        }

        int loopCount = getLoopCount(numThreads, tid);
        int maxLoopCount = getLoopCount(numThreads, 0);
        for (int i = 0; i < maxLoopCount; i++) {
            if (i < loopCount) {
                int gap = 1 << i;
                int nth = tid / gap;
                // 현재 loop에서 tid가 몇번 째인지 계산
                bool even = nth % 2 == 0;
                mergeBins(version3LocalBins, tid - (!even) * gap, tid + even * gap, even);
                // 빈 합치기
            }
            #pragma omp barrier
        }
    }
    timer.offTimer(3);
    printBins((char *) "Version3", version3LocalBins[0]);

    timer.printTimer();

    free();
}