#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <random>
#include <sstream>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include "timer.h"
#include "DS_timer.h"

#define USE_HOST
#define USE_OMP
#define TO_INDEX(row, col, width) ((row) * (width) + (col))
#define GET(pointer, row, col, width) (pointer[TO_INDEX(row, col, width)])
#define GET_B(pointer, row, col) GET(pointer, row, col, blockSize)

int row;
int k;
int col;
int blockSize;
int sizeA;
int sizeB;
int sizeC;
float *a, *b, *c, *h_c, *o_c;
float *d_a, *d_b;
float *d_c;
// __constant__ float d_a[32 * 32], d_b[32 * 32];

__global__ void matrixMul(const float *a, const float *b, float *c, int row, int k, int col) {
    unsigned int rowIx = blockDim.x * blockIdx.x + threadIdx.x;
    unsigned int colIx = blockDim.y * blockIdx.y + threadIdx.y;
    if (!(rowIx < row && colIx < col)) {
        return;
    }

    float sum = 0.0f;
    for (int kIx = 0; kIx < k; kIx++) {
        sum += __fmul_rn(a[rowIx * k + kIx], b[kIx * col + colIx]);
    }
    c[rowIx * col + colIx] = sum;
}

__global__ void matrixMulRR(const float *a, const float *b, float *c, int row, int k, int col, int blockSize) {
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

        GET_B(sharedA, threadRow, threadCol) = (rowIx < row && offset + threadCol < k) ?
                                               a[TO_INDEX(rowIx, offset + threadCol, k)] : 0;
        GET_B(sharedB, threadRow, threadCol) = (colIx < col && offset + threadRow < k) ?
                                               b[TO_INDEX(offset + threadRow, colIx, col)] : 0;
        __syncthreads();

        for (int i = 0; i < blockSize; i++) {
            result += __fmul_rn(GET_B(sharedA, threadRow, i), GET_B(sharedB, i, threadCol));
        }
        __syncthreads();
    }

    if (!(rowIx < row && colIx < col)) {
        return;
    }

    c[TO_INDEX(rowIx, colIx, col)] = result;
}

__global__ void matrixMulCC(const float *a, const float *b, float *c, int row, int k, int col, int blockSize) {
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

        GET_B(sharedA, threadCol, threadRow) = (rowIx < row && offset + threadCol < k) ?
                                               a[TO_INDEX(rowIx, offset + threadCol, k)] : 0;
        GET_B(sharedB, threadCol, threadRow) = (colIx < col && offset + threadRow < k) ?
                                               b[TO_INDEX(offset + threadRow, colIx, col)] : 0;
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

#define BLOCK_SIZE 16

__global__ void
matrixMulCC_V_STATIC_BLOCK(const float *a, const float *b, float *c, int row, int k, int col, int blockSize) {
    unsigned int rowIx = blockDim.x * blockIdx.x + threadIdx.x;
    unsigned int colIx = blockDim.y * blockIdx.y + threadIdx.y;

    __shared__ float sharedA[BLOCK_SIZE][BLOCK_SIZE];
    __shared__ float sharedB[BLOCK_SIZE][BLOCK_SIZE];

    unsigned int threadRow = threadIdx.x;
    unsigned int threadCol = threadIdx.y;

    unsigned int blockLimit = ceil(k / (float) blockSize);

    float result = 0;
    for (int block = 0; block < blockLimit; block++) {
        int offset = block * blockSize;

        sharedA[threadCol][threadRow] = (rowIx < row && offset + threadCol < k) ?
                                        a[TO_INDEX(rowIx, offset + threadCol, k)] : 0;
        sharedB[threadCol][threadRow] = (colIx < col && offset + threadRow < k) ?
                                        b[TO_INDEX(offset + threadRow, colIx, col)] : 0;
        __syncthreads();

        for (int i = 0; i < blockSize; i++) {
            result += __fmul_rn(sharedA[i][threadRow], sharedB[threadCol][i]);
        }
        __syncthreads();
    }

    if (!(rowIx < row && colIx < col)) {
        return;
    }

    c[TO_INDEX(rowIx, colIx, col)] = result;
}

__global__ void
matrixMulCC_V_IDX_CHACHING(const float *a, const float *b, float *c, int row, int k, int col, int blockSize) {
    unsigned int rowIx = blockDim.x * blockIdx.x + threadIdx.x;
    unsigned int colIx = blockDim.y * blockIdx.y + threadIdx.y;

    extern __shared__ float sharedTotal[];
    float *sharedA = sharedTotal;
    float *sharedB = sharedA + blockSize * blockSize;

    unsigned int threadRow = threadIdx.x;
    unsigned int threadCol = threadIdx.y;
    const unsigned int targetIdx = TO_INDEX(threadRow, threadCol, blockSize);
    const unsigned int limit = ceil(k / (float) blockSize) * blockSize;

    float result = 0;
    for (int offset = 0; offset < limit; offset += blockSize) {
        sharedA[targetIdx] = (rowIx < row && offset + threadCol < k) ?
                             a[TO_INDEX(rowIx, offset + threadCol, k)] : 0;
        sharedB[targetIdx] = (colIx < col && offset + threadRow < k) ?
                             b[TO_INDEX(offset + threadRow, colIx, col)] : 0;
        __syncthreads();

        for (int i = 0; i < blockSize; i++) {
            result += __fmul_rn(GET_B(sharedA, i, threadRow), GET_B(sharedB, threadCol, i));
        }
        __syncthreads();
    }

    if (rowIx >= row || colIx >= col) {
        return;
    }

    c[TO_INDEX(rowIx, colIx, col)] = result;
}


__global__ void matrixMulCC_V_FINAL(const float *a, const float *b, float *c, int row, int k, int col, int blockSize) {
    unsigned int rowIx = blockDim.x * blockIdx.x + threadIdx.x;
    unsigned int colIx = blockDim.y * blockIdx.y + threadIdx.y;

    extern __shared__ float sharedTotal[];
    float *sharedA = sharedTotal;
    float *sharedB = sharedA + blockSize * blockSize;

    unsigned int threadRow = threadIdx.x;
    unsigned int threadCol = threadIdx.y;

    const unsigned int limit = ceil(k / (float) blockSize) * blockSize;

    float result = 0;
    for (int offset = 0; offset < limit; offset += blockSize) {
        GET_B(sharedA, threadCol, threadRow) = (rowIx < row && offset + threadCol < k) ?
                                               a[TO_INDEX(rowIx, offset + threadCol, k)] : 0;
        GET_B(sharedB, threadCol, threadRow) = (colIx < col && offset + threadRow < k) ?
                                               b[TO_INDEX(offset + threadRow, colIx, col)] : 0;
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


__global__ void matrixMulRC(const float *a, const float *b, float *c, int row, int k, int col, int blockSize) {
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

        GET_B(sharedA, threadRow, threadCol) = (rowIx < row && offset + threadCol < k) ?
                                               a[TO_INDEX(rowIx, offset + threadCol, k)] : 0;
        GET_B(sharedB, threadCol, threadRow) = (colIx < col && offset + threadRow < k) ?
                                               b[TO_INDEX(offset + threadRow, colIx, col)] : 0;
        __syncthreads();

        for (int i = 0; i < blockSize; i++) {
            result += __fmul_rn(GET_B(sharedA, threadRow, i), GET_B(sharedB, threadCol, i));
        }
        __syncthreads();
    }

    if (!(rowIx < row && colIx < col)) {
        return;
    }

    c[TO_INDEX(rowIx, colIx, col)] = result;
}

__global__ void matrixMulCR(const float *a, const float *b, float *c, int row, int k, int col, int blockSize) {
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

        GET_B(sharedA, threadCol, threadRow) = (rowIx < row && offset + threadCol < k) ?
                                               a[TO_INDEX(rowIx, offset + threadCol, k)] : 0;
        GET_B(sharedB, threadRow, threadCol) = (colIx < col && offset + threadRow < k) ?
                                               b[TO_INDEX(offset + threadRow, colIx, col)] : 0;
        __syncthreads();

        for (int i = 0; i < blockSize; i++) {
            result += __fmul_rn(GET_B(sharedA, i, threadRow), GET_B(sharedB, i, threadCol));
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
    for (int i = 0; i < TIMER_LIST_SIZE; i++) {
        timer.setTimerName(i, TIMER_NAME_LIST[i]);
    }
    timer.initTimers();
}


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

bool checkResult(const float *base, const float *target) {
    bool isValidData = true;
    for (int i = 0; i < sizeC; i++) {
        if (base[i] != target[i]) {
            printf("\t[%d] The result is not matched! (base, target)=(%f, %f)\n", i, base[i], target[i]);
            isValidData = false;
        }
    }

    if (isValidData) {
        printf("\tTarget data valid!\n");
    }

    return isValidData;
}

void checkGPUResult(const char *name, bool clearDeviceMemory = true) {
#ifdef USE_OMP
    printf("checkGPUResult(%s)\n", name);
    cudaMemcpy(c, d_c, sizeC * sizeof(float), cudaMemcpyDeviceToHost);
    checkResult(o_c, c);
    if (clearDeviceMemory) {
        cudaMemcpy(d_c, c, sizeC * sizeof(float), cudaMemcpyHostToDevice);
    }
#else
    printf("checkGPUResult(%s): Passed\n", name);
#endif
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

#ifdef USE_HOST
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
#endif

#ifdef USE_OMP
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
#endif

#ifdef USE_HOST
    printf("checkResult(%s)\n", TIMER_OMP_NAME);
    checkResult(h_c, o_c);
#endif

    cudaMalloc(&d_a, sizeA * sizeof(float));
    cudaMalloc(&d_b, sizeB * sizeof(float));
    cudaMalloc(&d_c, sizeC * sizeof(float));

    timer.onTimer(TIMER_DATA_TRANSFER_H2D);
    /* cudaMemcpyToSymbol(d_a, a, sizeA * sizeof(float));
    cudaMemcpyToSymbol(d_b, b, sizeB * sizeof(float)); */
    cudaMemcpy(d_a, a, sizeA * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_b, b, sizeB * sizeof(float), cudaMemcpyHostToDevice);
    cudaMemcpy(d_c, c, sizeC * sizeof(float), cudaMemcpyHostToDevice);
    timer.offTimer(TIMER_DATA_TRANSFER_H2D);

    dim3 dimGrid((unsigned int) ceil(row / blockSize), (unsigned int) ceil(col / blockSize));
    dim3 dimBlock(blockSize, blockSize);

    timer.onTimer(TIMER_KERNEL_BASIC);
    matrixMul <<<dimGrid, dimBlock,
    2 * blockSize * blockSize * sizeof(float)>>>(d_a, d_b, d_c, row, k, col);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL_BASIC);
    checkGPUResult(TIMER_KERNEL_BASIC_NAME);

    timer.onTimer(TIMER_KERNEL_RR);
    matrixMulRR <<<dimGrid, dimBlock,
    2 * blockSize * blockSize * sizeof(float)>>>(d_a, d_b, d_c, row, k, col, blockSize);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL_RR);
    checkGPUResult(TIMER_KERNEL_RR_NAME);

    timer.onTimer(TIMER_KERNEL_RC);
    matrixMulRC <<<dimGrid, dimBlock,
    2 * blockSize * blockSize * sizeof(float)>>>(d_a, d_b, d_c, row, k, col, blockSize);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL_RC);
    checkGPUResult(TIMER_KERNEL_RC_NAME);

    timer.onTimer(TIMER_KERNEL_CR);
    matrixMulCR <<<dimGrid, dimBlock,
    2 * blockSize * blockSize * sizeof(float)>>>(d_a, d_b, d_c, row, k, col, blockSize);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL_CR);
    checkGPUResult(TIMER_KERNEL_CR_NAME);

    timer.onTimer(TIMER_KERNEL_CC);
    matrixMulCC <<<dimGrid, dimBlock,
    2 * blockSize * blockSize * sizeof(float)>>>(d_a, d_b, d_c, row, k, col, blockSize);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL_CC);
    checkGPUResult(TIMER_KERNEL_CC_NAME);

    timer.onTimer(TIMER_KERNEL_CC_V_FINAL);
    matrixMulCC_V_FINAL<<<dimGrid, dimBlock,
    2 * blockSize * blockSize * sizeof(float)>>>(d_a, d_b, d_c, row, k, col, blockSize);
    cudaDeviceSynchronize();
    timer.offTimer(TIMER_KERNEL_CC_V_FINAL);
    checkGPUResult(TIMER_KERNEL_CC_V_FINAL_NAME);

    timer.onTimer(TIMER_DATA_TRANSFER_D2H);
    cudaMemcpy(c, d_c, sizeC * sizeof(float), cudaMemcpyDeviceToHost);
    timer.offTimer(TIMER_DATA_TRANSFER_D2H);

    timer.printTimer();

    timer.printToFile((char *) toReportFileName(row, k, col, blockSize).c_str());

    cudaFree(d_a);
    cudaFree(d_b);
    cudaFree(d_c);

    freeData();

    return 0;
}
