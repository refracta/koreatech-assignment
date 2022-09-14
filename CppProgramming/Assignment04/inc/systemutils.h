/**
 @file systemutils.h
 @brief systemutils의 헤더 파일
*/
#ifndef SYSTEMUTILS_H
#define SYSTEMUTILS_H

#include <Windows.h>
#include <time.h>

#define CLOCK_MONOTONIC 1
#define exp7           10000000i64     //1E+7     //C-file part
#define exp9         1000000000i64     //1E+9
#define w2ux 116444736000000000i64     //1.jan1601 to 1.jan1970

#define UNIT_WAIT 10
#define MILLISECOND_DIFF(begin, end) (((double) (end.tv_sec - begin.tv_sec) + (end.tv_nsec - begin.tv_nsec) * 1.0e-9) * 1000)

namespace SystemUtils {
    void unix_time(struct timespec *);
    int clock_gettime(int, struct timespec *);
    void wait(unsigned long);
}

#endif