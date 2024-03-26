#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <string>
#include <format>
#include <sstream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "timer.h"
#include "DS_timer.h"

#define LIMIT (13 * 2)
#define FLATTEN_MATRIX_SIZE (1 << LIMIT)
// FLATTEN_MATRIX_SIZE = 8192 * 8192
#define MEMORY_SIZE (FLATTEN_MATRIX_SIZE * sizeof(int))
#define TO_INDEX(x, y, z, w, dimX, dimY, dimZ) (x + dimX * (y + dimY * (z + dimZ * w)))

__global__ void vectorAdd(const int *a, const int *b, int *c, int size) {
    unsigned int tID = TO_INDEX(threadIdx.x, threadIdx.y, blockIdx.x, blockIdx.y, blockDim.x, blockDim.y, gridDim.x);
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

int *a, *b, *c, *h_c;
int *d_a, *d_b, *d_c;

inline void initData() {
    printf("%d elements, memorySize = %lld bytes\n", FLATTEN_MATRIX_SIZE, MEMORY_SIZE);

    a = new int[FLATTEN_MATRIX_SIZE];
    b = new int[FLATTEN_MATRIX_SIZE];
    c = new int[FLATTEN_MATRIX_SIZE];
    h_c = new int[FLATTEN_MATRIX_SIZE];

    for (int i = 0; i < FLATTEN_MATRIX_SIZE; i++) {
        a[i] = rand() % 10;
        b[i] = rand() % 10;
    }
}

inline void freeData() {
    delete[] a;
    delete[] b;
    delete[] c;
}

std::string toReportFileName(int gridX, int gridY, int blockX, int blockY) {
    std::ostringstream stream;
    stream << "report_" << gridX << "_" << gridY << "_" << blockX << "_" << blockY << ".txt";
    return stream.str();
}

bool runVectorAdd(dim3 dimGrid, dim3 dimBlock) {
    printf("runVectorAdd(dimGrid={%d, %d, %d}, dimBlock={%d, %d, %d})\n", dimGrid.x, dimGrid.y, dimGrid.z, dimBlock.x,
           dimBlock.y, dimBlock.z);

    timer.initTimers();
    cudaMalloc(&d_a, MEMORY_SIZE);
    cudaMalloc(&d_b, MEMORY_SIZE);
    cudaMalloc(&d_c, MEMORY_SIZE);

    timer.onTimer(TIMER_TOTAL);

    timer.onTimer(TIMER_DATA_TRANSFER_H2D);
    cudaMemcpy(d_a, a, MEMORY_SIZE, cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, MEMORY_SIZE, cudaMemcpyHostToDevice);
    timer.offTimer(TIMER_DATA_TRANSFER_H2D);

    timer.onTimer(TIMER_KERNEL);
    vectorAdd <<<dimGrid, dimBlock>>>(d_a, d_b, d_c, FLATTEN_MATRIX_SIZE);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL);

    timer.onTimer(TIMER_DATA_TRANSFER_D2H);
    cudaMemcpy(c, d_c, MEMORY_SIZE, cudaMemcpyDeviceToHost);
    timer.offTimer(TIMER_DATA_TRANSFER_D2H);

    timer.offTimer(TIMER_TOTAL);

    timer.onTimer(TIMER_HOST);
    for (int i = 0; i < FLATTEN_MATRIX_SIZE; i++) {
        h_c[i] = a[i] + b[i];
    }
    timer.offTimer(TIMER_HOST);

    bool isValidData = true;
    for (int i = 0; i < FLATTEN_MATRIX_SIZE; i++) {
        if (h_c[i] != c[i]) {
            printf("\t[%d] The result is not matched! (%d, %d)\n", i, h_c[i], c[i]);
            isValidData = false;
        }
    }

    if (isValidData) {
        printf("\tGPU works well!\n");
    }
    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    return isValidData;
}

int main(int argc, char **argv) {
    initData();
    initTimer();

    int count = 0;
    for (int gridX = 0; gridX <= LIMIT - 2; gridX++) {
        for (int gridY = 0; gridY <= LIMIT - gridX - 1; gridY++) {
            for (int blockX = 0; blockX <= LIMIT - gridX - gridY; blockX++) {
                int blockY = LIMIT - gridX - gridY - blockX;
                if (blockX + blockY <= 10 && gridY < 16) {
                    // blockX + blockY <= 1024 && gridY < 65536
                    dim3 dimBlock(1 << blockX, 1 << blockY, 1);
                    dim3 dimGrid(1 << gridX, 1 << gridY, 1);
                    printf("[#%d] ", ++count);
                    runVectorAdd(dimGrid, dimBlock);
                    // 가능한 모든 경우의 수에 대해서 테스트
                    timer.printToFile((char *) toReportFileName(gridX, gridY, blockX, blockY).c_str());
                }
            }
        }
    }

    freeData();
    return 0;
}
