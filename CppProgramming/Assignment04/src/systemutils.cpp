/**
  @file systemutils.c
  @brief 시스템 유틸 함수들이 구현된 소스 파일
*/
#include "systemutils.h"

/**
 * @brief 주어진 timespec 매개변수에 시간을 계산하여 저장한다.
 * @param spec timespec
 * @description Source from https://stackoverflow.com/questions/5404277/porting-clock-gettime-to-windows
*/
void SystemUtils::unix_time(struct timespec *spec)
{
    __int64 wintime;
    GetSystemTimeAsFileTime((FILETIME *) &wintime);
    wintime -= w2ux;
    spec->tv_sec = wintime / exp7;
    spec->tv_nsec = wintime % exp7 * 100;
}

/**
 * @brief unix 계열에서 사용하는 clock_gettime의 윈도우 구현체
 * @param id clk_id
 * @param spec tp
 * @return errno
 */
int SystemUtils::clock_gettime(int id, struct timespec *spec)
{
    static struct timespec startspec;
    static double ticks2nano;
    static __int64 startticks, tps = 0;
    __int64 tmp, curticks;
    QueryPerformanceFrequency((LARGE_INTEGER *) &tmp);
    if (tps != tmp)
    {
        tps = tmp;
        QueryPerformanceCounter((LARGE_INTEGER *) &startticks);
        unix_time(&startspec);
        ticks2nano = (double) exp9 / tps;
    }
    QueryPerformanceCounter((LARGE_INTEGER *) &curticks);
    curticks -= startticks;
    spec->tv_sec = startspec.tv_sec + (curticks / tps);
    spec->tv_nsec = startspec.tv_nsec + (double) (curticks % tps) * ticks2nano;
    if (!(spec->tv_nsec < exp9))
    {
        spec->tv_sec++;
        spec->tv_nsec -= exp9;
    }
    return 0;
}

/**
 * @brief 지정한 시간동안 대기한다.
 * @param ms 대기할 시간 (밀리초)
 */
void SystemUtils::wait(unsigned long ms)
{
    Sleep(ms);
}