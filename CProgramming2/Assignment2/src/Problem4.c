/**
  @file Problem4.c
  @brief Lab2-4. 1���� �ռ��� (����ȫ ����)
  */
#include <stdio.h>
#include <stdlib.h>
#include "simpleConvolution.h"

int main()
{
	fftw_complex data[100] = {0, }; //�Է� �� ��� f(x)
	fftw_complex filter[100]= { 0, }; //���� h(x)
	fftw_complex val[100]; //���� ������
	const int size = 100; //������ ����
	fileRead(val, size);

	/*!<---------------�ڵ� ���� */
	const int ARRAY_SIZE = sizeof(data) / sizeof(fftw_complex);
	//0. �迭 �ʱ�ȭ
	for (int i = 0; i < ARRAY_SIZE; i++) {
		data[i][0] = i;
		data[i][1] = 2 * i;

		filter[i][0] = 100 - i;
		filter[i][1] = 2 * (100 - i);
	}
	
	//1. �ռ��� ����
	fft1d_forward(data, ARRAY_SIZE);
	fft1d_forward(filter, ARRAY_SIZE);
	elementWiseMultiplication(data, filter, ARRAY_SIZE);
	fft1d_backward(data, ARRAY_SIZE);
	/*!<---------------�ڵ� ��*/

	
	if (validation(data, val, size)) {
		printf("success\n");
	}
	else {
		printf("error\n");
	}
	printf("\nPress ENTER to exit..."); fflush(stdin); getchar();
}
