#include <cstdio>
#include <cstdlib>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "timer.h"
#include "DS_timer.h"

#define DEFAULT_DATA_SIZE (1024 * 1024)

__global__ void vectorAdd(const int *a, const int *b, int *c, int size) {
    unsigned int tID = blockIdx.x * blockDim.x + threadIdx.x;
    if (tID < size) {
        c[tID] = a[tID] + b[tID];
    }
}

DS_timer timer(TIMER_LIST_SIZE);

inline void initTimer() {
    timer.setTimerName(TIMER_TOTAL, TIMER_TOTAL_NAME);
    timer.setTimerName(TIMER_KERNEL, TIMER_KERNEL_NAME);
    timer.setTimerName(TIMER_DATA_TRANSFER_H2D, TIMER_DATA_TRANSFER_H2D_NAME);
    timer.setTimerName(TIMER_DATA_TRANSFER_D2H, TIMER_DATA_TRANSFER_D2H_NAME);
    timer.setTimerName(TIMER_HOST, TIMER_HOST_NAME);
    timer.initTimers();
}

int dataSize;
int *a, *b, *c, *h_c;
int *d_a, *d_b, *d_c;
long long memorySize;

inline void initData(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: Execution_file [dataSize]\n");
        exit(1);
    }
    dataSize = atoi(argv[1]) * DEFAULT_DATA_SIZE;
    memorySize = sizeof(int) * dataSize;

    printf("%d elements, memorySize = %lld bytes\n", dataSize, memorySize);

    a = new int[dataSize];
    b = new int[dataSize];
    c = new int[dataSize];
    h_c = new int[dataSize];

    for (int i = 0; i < dataSize; i++) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }
}
inline void freeData() {
    delete[] a;
    delete[] b;
    delete[] c;
}

int main(int argc, char **argv) {
    initData(argc, argv);
    initTimer();

    cudaMalloc(&d_a, memorySize);
    cudaMalloc(&d_b, memorySize);
    cudaMalloc(&d_c, memorySize);

    timer.onTimer(TIMER_TOTAL);

    timer.onTimer(TIMER_DATA_TRANSFER_H2D);
    cudaMemcpy(d_a, a, memorySize, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, memorySize, cudaMemcpyHostToDevice);
    timer.offTimer(TIMER_DATA_TRANSFER_H2D);

    dim3 dimGrid(ceil(dataSize / 1024.0), 1, 1);
    dim3 dimBlock(1024, 1, 1);

    timer.onTimer(TIMER_KERNEL);
    vectorAdd <<<dimGrid, dimBlock>>>(d_a, d_b, d_c, dataSize);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL);

    timer.onTimer(TIMER_DATA_TRANSFER_D2H);
    cudaMemcpy(c, d_c, memorySize, cudaMemcpyDeviceToHost);
    timer.offTimer(TIMER_DATA_TRANSFER_D2H);

    timer.offTimer(TIMER_TOTAL);

    timer.onTimer(TIMER_HOST);
    for (int i = 0; i < dataSize; i++) {
        h_c[i] = a[i] + b[i];
    }
    timer.offTimer(TIMER_HOST);

    timer.printTimer();

    bool isValidData = true;
    for (int i = 0; i < dataSize; i++) {
        if (h_c[i] != c[i]) {
            printf("[%d] The result is not matched! (%d, %d)\n", i, h_c[i], c[i]);
            isValidData = false;
        }
    }

    if (isValidData) {
        printf("GPU works well!\n");
    }
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    freeData();

    return 0;
}
