#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include "DS_timer.h"
#include "DS_definitions.h"

#define F_EXPRESSION "x * x"

inline double f(double x) {
    return x * x;
}

int main(int argc, char **argv) {
    DS_timer timer(2);
    timer.setTimerName(0, (char *) "Serial");
    timer.setTimerName(1, (char *) "Parallel");

    if (argc < 4) {
        printf("It requires three arguments\n");
        printf("Usage: Execution_file [a] [b] [n] [numThread (optional)]\n");
        return -1;
    }

    double a = atof(argv[1]);
    double b = atof(argv[2]);
    if(a > b){
        double c = a;
        a = b;
        b = c;
    }
    int n = atoi(argv[3]);
    double delta = (b - a) / n;
    const int numThreads = argc > 4 ? atoi(argv[4]) : omp_get_max_threads();

    printf("f(x) = %s\n", F_EXPRESSION);
    printf("range = (%f, %f), n = %d\n", a, b, n);
    printf("numThreads: %d\n", numThreads);

    //** 1. Serial code **//
    timer.onTimer(0);

    //** HERE
    //** Write your code implementing the serial algorithm here
    double serialSum = 0.0;
    for (int i = 1; i < n; i++) {
        double x = a + i * delta;
        serialSum += f(x);
    }
    serialSum = (serialSum + (f(a) + f(b)) / 2.0) * delta;
    printf("[Serial] area = %lf\n", serialSum);


    timer.offTimer(0);



    //** 2. Parallel code **//
    timer.onTimer(1);


    //** HERE
    //** Write your code implementing the parallel algorithm here
    double parallelSum = 0.0;
    double *sums = new double[numThreads];
    std::fill(sums, sums + numThreads, 0.0);

    #pragma omp parallel num_threads(numThreads)
    {
        int tid = omp_get_thread_num();
        #pragma omp for
        for (int i = 1; i < n; i++) {
            double x = a + i * delta;
            sums[tid] += f(x);
            // 스레드별 합 계산
        }
    }

    for (int i = 0; i < numThreads; i++) {
        parallelSum += sums[i];
    }
    // 스레드별 합을 더하여 최종 합 계산
    parallelSum = (parallelSum + (f(a) + f(b)) / 2.0) * delta;
    printf("[Parallel] area = %lf\n", parallelSum);
    free(sums);

    timer.offTimer(1);

    //** 3. Result checking code **//
    bool isCorrect = abs(serialSum - parallelSum) < 1e-9;

    //** HERE
    //** Wriet your code that compares results of serial and parallel algorithm
    // Set the flag 'isCorrect' to true when they are matched

    if (!isCorrect)
        printf("Results are not matched :(\n");
    else
        printf("Results are matched! :)\n");

    timer.printTimer();
}