/**
  @file Problem4.c
  @brief Lab2-4. 1차원 합성곱 (이재홍 조교)
  */
#include <stdio.h>
#include <stdlib.h>
#include "simpleConvolution.h"

int main()
{
	fftw_complex data[100] = {0, }; //입력 및 출력 f(x)
	fftw_complex filter[100]= { 0, }; //필터 h(x)
	fftw_complex val[100]; //검증 데이터
	const int size = 100; //데이터 갯수
	fileRead(val, size);

	/*!<---------------코딩 시작 */
	const int ARRAY_SIZE = sizeof(data) / sizeof(fftw_complex);
	//0. 배열 초기화
	for (int i = 0; i < ARRAY_SIZE; i++) {
		data[i][0] = i;
		data[i][1] = 2 * i;

		filter[i][0] = 100 - i;
		filter[i][1] = 2 * (100 - i);
	}
	
	//1. 합성곱 구현
	fft1d_forward(data, ARRAY_SIZE);
	fft1d_forward(filter, ARRAY_SIZE);
	elementWiseMultiplication(data, filter, ARRAY_SIZE);
	fft1d_backward(data, ARRAY_SIZE);
	/*!<---------------코딩 끝*/

	
	if (validation(data, val, size)) {
		printf("success\n");
	}
	else {
		printf("error\n");
	}
	printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
