#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "DS_timer.h"
#include "DS_definitions.h"

// Set the size of matrix and vector
// matrix A = m by n
// vector b = n by 1
// #define m (10000)
// #define n (10000)
int m;
int n;
int numThreads;

#define GenFloat (rand() % 100 + ((float)(rand() % 100) / 100.0f))

void init(int argc, char **argv);

void free(void);

void genRandomInput();

// float A[m][n];
// float X[n];
// float Y_serial[m];
// float Y_parallel[m];

float **A;
float *X;
float *Y_serial;
float *Y_parallel;

int main(int argc, char **argv) {
    DS_timer timer(2);
    timer.setTimerName(0, (char *) "Serial");
    timer.setTimerName(1, (char *) "Parallel");

    init(argc, argv);
    printf("m: %d, n: %d, numThreads: %d\n", m, n, numThreads);
    genRandomInput();


    //** 1. Serial code **//
    timer.onTimer(0);


    //** HERE
    //** Write your code implementing the serial algorithm here
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            Y_serial[r] += A[r][c] * X[c];
        }
    }

    timer.offTimer(0);



    //** 2. Parallel code **//
    timer.onTimer(1);


    //** HERE
    //** Write your code implementing the parallel algorithm here
    #pragma omp parallel for num_threads(numThreads)
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            Y_parallel[r] += A[r][c] * X[c];
        }
    }


    timer.offTimer(1);



    //** 3. Result checking code **//
    bool isCorrect = true;

    //** HERE
    //** Wriet your code that compares results of serial and parallel algorithm
    // Set the flag 'isCorrect' to true when they are matched
    for (int row = 0; row < m; row++) {
        if (Y_parallel[row] != Y_serial[row]) {
            isCorrect = false;
            break;
        }
    }


    if (!isCorrect)
        printf("Results are not matched :(\n");
    else
        printf("Results are matched! :)\n");

    timer.printTimer();
    free();
    if (argc == 1) {
        EXIT_WIHT_KEYPRESS;
    }
}

void init(int argc, char **argv) {
    m = argc > 1 ? atoi(argv[1]) : 10000;
    n = argc > 2 ? atoi(argv[2]) : 10000;
    numThreads = argc > 3 ? atoi(argv[3]) : omp_get_max_threads();

    A = new float *[m];
    for (int row = 0; row < m; row++) {
        A[row] = new float[n];
    }

    X = new float[n];
    Y_serial = new float[m];
    Y_parallel = new float[m];
}

void free(void) {
    for (int row = 0; row < m; row++) {
        delete[] A[row];
    }
    delete[] A;

    delete[] X;
    delete[] Y_serial;
    delete[] Y_parallel;
}

void genRandomInput(void) {
    // A matrix
    LOOP_INDEX(row, m) {
        LOOP_INDEX(col, n) {
            A[row][col] = GenFloat;
        }
    }
    LOOP_I(n) X[i] = GenFloat;

    memset(Y_serial, 0, sizeof(float) * m);
    memset(Y_parallel, 0, sizeof(float) * m);
}