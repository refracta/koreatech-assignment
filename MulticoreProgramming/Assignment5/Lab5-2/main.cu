#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <random>
#include <sstream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "timer.h"
#include "DS_timer.h"

#define TO_INDEX(row, col, width) ((row) * (width) + (col))
#define GET(pointer, row, col, width) (pointer[TO_INDEX(row, col, width)])
#define GET_B(pointer, row, col) GET(pointer, row, col, blockSize)

__global__ void matrixMul(const float *a, const float *b, float *c, int row, int k, int col, int blockSize) {
    unsigned int rowIx = blockDim.x * blockIdx.x + threadIdx.x;
    unsigned int colIx = blockDim.y * blockIdx.y + threadIdx.y;

    extern __shared__ float sharedTotal[];
    float *sharedA = sharedTotal;
    float *sharedB = sharedA + blockSize * blockSize;

    unsigned int threadRow = threadIdx.x;
    unsigned int threadCol = threadIdx.y;

    unsigned int blockLimit = ceil(k / (float) blockSize);

    float result = 0;
    for (int block = 0; block < blockLimit; block++) {
        int offset = block * blockSize;

        GET_B(sharedA, threadCol, threadRow) = (rowIx < row && offset + threadCol < k) ? a[TO_INDEX(rowIx,
                                                                                                    offset + threadCol,
                                                                                                    k)] : 0;
        GET_B(sharedB, threadCol, threadRow) = (colIx < col && offset + threadRow < k) ? b[TO_INDEX(offset + threadRow,
                                                                                                    colIx, col)] : 0;
        __syncthreads();

        for (int i = 0; i < blockSize; i++) {
            result += __fmul_rn(GET_B(sharedA, i, threadRow), GET_B(sharedB, threadCol, i));
        }
        __syncthreads();
    }

    if (!(rowIx < row && colIx < col)) {
        return;
    }

    c[TO_INDEX(rowIx, colIx, col)] = result;
}

DS_timer timer(TIMER_LIST_SIZE);

inline void initTimer() {
    timer.setTimerName(TIMER_TOTAL, TIMER_TOTAL_NAME);
    timer.setTimerName(TIMER_KERNEL, TIMER_KERNEL_NAME);
    timer.setTimerName(TIMER_DATA_TRANSFER_H2D, TIMER_DATA_TRANSFER_H2D_NAME);
    timer.setTimerName(TIMER_DATA_TRANSFER_D2H, TIMER_DATA_TRANSFER_D2H_NAME);
    timer.setTimerName(TIMER_HOST, TIMER_HOST_NAME);
    timer.setTimerName(TIMER_OMP, TIMER_OMP_NAME);
    timer.initTimers();
}

int row;
int k;
int col;
int blockSize;
int sizeA;
int sizeB;
int sizeC;
float *a, *b, *c, *h_c, *o_c;
float *d_a, *d_b, *d_c;

inline void initData(int argc, char **argv) {
    if (argc < 1 + 4) {
        printf("Usage: Execution_file [row] [k] [col] [blockSize]\n");
        exit(1);
    }
    row = atoi(argv[1]);
    k = atoi(argv[2]);
    col = atoi(argv[3]);
    blockSize = atoi(argv[4]);

    printf("[row, k, col, blockSize] = [%d, %d, %d, %d]\n", row, k, col, blockSize);

    a = new float[sizeA = row * k];
    b = new float[sizeB = k * col];
    c = new float[sizeC = row * col];
    h_c = new float[sizeC];
    o_c = new float[sizeC];

    std::random_device rd;
    std::mt19937 engine(rd());
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    for (int i = 0; i < sizeA; i++) {
        a[i] = distribution(engine);
    }
    for (int i = 0; i < sizeB; i++) {
        b[i] = distribution(engine);
    }
    std::fill(c, c + sizeC, 0.0f);
}

inline void freeData() {
    delete[] a;
    delete[] b;
    delete[] c;
    delete[] h_c;
    delete[] o_c;
}

std::string toReportFileName(int row, int k, int col, int blockSize) {
    std::ostringstream stream;
    stream << "report_" << row << "_" << k << "_" << col << "_" << blockSize << ".txt";
    return stream.str();
}

int main(int argc, char **argv) {
    initData(argc, argv);
    initTimer();

    cudaMalloc(&d_a, sizeA * sizeof(float));
    cudaMalloc(&d_b, sizeB * sizeof(float));
    cudaMalloc(&d_c, sizeC * sizeof(float));

    timer.onTimer(TIMER_TOTAL);

    timer.onTimer(TIMER_DATA_TRANSFER_H2D);
    cudaMemcpy(d_a, a, sizeA * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeB * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, sizeC * sizeof(float), cudaMemcpyHostToDevice);
    timer.offTimer(TIMER_DATA_TRANSFER_H2D);

    dim3 dimGrid((unsigned int) ceil(row / blockSize), (unsigned int) ceil(col / blockSize));
    dim3 dimBlock(blockSize, blockSize);

    timer.onTimer(TIMER_KERNEL);
    matrixMul <<<dimGrid, dimBlock, 2 * blockSize * blockSize * sizeof(float)>>>(d_a, d_b, d_c, row, k, col, blockSize);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL);

    timer.onTimer(TIMER_DATA_TRANSFER_D2H);
    cudaMemcpy(c, d_c, sizeC * sizeof(float), cudaMemcpyDeviceToHost);
    timer.offTimer(TIMER_DATA_TRANSFER_D2H);

    timer.offTimer(TIMER_TOTAL);

    timer.onTimer(TIMER_HOST);
    for (int rowIx = 0; rowIx < row; rowIx++) {
        for (int colIx = 0; colIx < col; colIx++) {
            float sum = 0.0f;
            for (int kIx = 0; kIx < k; kIx++) {
                sum += a[rowIx * k + kIx] * b[kIx * col + colIx];
            }
            h_c[rowIx * col + colIx] = sum;
        }
    }
    timer.offTimer(TIMER_HOST);

    timer.onTimer(TIMER_OMP);
    #pragma omp parallel for
    for (int rowIx = 0; rowIx < row; rowIx++) {
        for (int colIx = 0; colIx < col; colIx++) {
            float sum = 0.0f;
            for (int kIx = 0; kIx < k; kIx++) {
                sum += a[rowIx * k + kIx] * b[kIx * col + colIx];
            }
            o_c[rowIx * col + colIx] = sum;
        }
    }
    timer.offTimer(TIMER_OMP);

    timer.printTimer();

    bool isValidData = true;
    for (int i = 0; i < sizeC; i++) {
        if (!(h_c[i] == c[i] && o_c[i] == c[i])) {
            printf("[%d] The result is not matched! (Host, OpenMP, CUDA)=(%f, %f, %f)\n", i, h_c[i], o_c[i], c[i]);
            isValidData = false;
        }
    }

    if (isValidData) {
        printf("CUDA & OpenMP works well!\n");
    }

    timer.printToFile((char *) toReportFileName(row, k, col, blockSize).c_str());

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    freeData();

    return 0;
}
