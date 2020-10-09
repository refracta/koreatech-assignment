/**
  @file FilterFunction.c
  @brief Lab3-5. 데이터 필터 만들기（김덕수 교수) - Baseline Code
*/

#include "FilterFunction.h"
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define PI (3.14)
#define LOOP_I(len) for(int i = 0 ; i < len ; i++)
#define MAX(a, b) (a > b ? a : b)
#define MIN(a, b) (a > b ? a : a)

/**
 * @brief Baseline Code에 정의된 함수의 동일 명세 구현체입니다.
 */
int smoothingFilter(int _data[], int _dataLen, int _index, int _filterSize) {
    // write your code here!
    int sum = 0;
    int count = 1;
    _filterSize /= 2;
    for (int i = _index - _filterSize; i < _index + _filterSize + 1; i++) {
        if(0 <= i && i < _dataLen){
            sum += _data[i];
            count++;
        }
    }
    return sum / count;
}

/**
 * @brief Baseline Code에 정의된 함수의 동일 명세 구현체입니다.
 */
int inversionFilter(int _input) {
    // write your code here!
    return -_input;
}

void genSineData(int *_data, int _len, int _max) {
    LOOP_I(_len)_data[i] = sin((i * PI * 10) / 180.0) * _max;
}

void genData(int *_data, int _len, int _max) {
    genSineData(_data, _len, _max);
    // add noise
    srand(time(NULL));
    LOOP_I(_len) {
        int noise = rand() % _max;
        noise = (rand() % 2 == 0 ? noise : -noise);
        if (noise > 0) _data[i] += noise;
        _data[i] = MAX(_data[i], -(_max));
        _data[i] = MIN(_data[i], _max);
    }
}

void printData(int *_data, int _len, int _max) {
    for (int height = 0; height < (_max + 1) * 2; height++) {
        for (int i = 0; i < _len; i++) {
            _data[i] == (height - _max) ? printf("*") : printf(" ");
        }
        printf("\n");
    }
}
