#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if defined(_WIN32) || defined(_WIN64)
# define strtok_r strtok_s
#endif

typedef enum Boolean {
    false, true
};


/**
 * 배타적 논리합 연산으로 배열의 두 색인에 존재하는 값을 교환한다.
 * https://en.wikipedia.org/wiki/XOR_swap_algorithm
 * @param array 대상 배열
 * @param x 교환할 배열의 한 색인
 * @param y 교환할 배열의 한 색인
 */
void swap(int array[], int x, int y) {
    if (x != y) {
        array[x] ^= array[y];
        array[y] ^= array[x];
        array[x] ^= array[y];
    }
}

/**
 * 배열의 세 색인의 값을 정렬한다. 중간 값 빠른 정렬에서 중간 값을 피벗으로 사용하기 위해 필요한 함수이다.
 * @param array 대상 배열
 * @param start 시작 색인
 * @param middle 중간 색인
 * @param end 마지막 색인
 */
void sort3Elements(int array[], int start, int middle, int end) {
    array[start] > array[middle] ? swap(array, start, middle) : false;
    array[middle] > array[end] ? swap(array, middle, end) : false;
    array[start] > array[middle] ? swap(array, start, middle) : false;
}

/**
 * 배열과 두 색인을 받아 그 사이의 값을 중간 값 빠른 정렬 알고리즘을 통해 정렬한다.
 * @param array 대상 배열
 * @param start 배열의 정렬할 시작 색인
 * @param end 배열의 정렬할 마지막 색인
 */
void motQuickSort(int array[], int start, int end) {
    int left, right, pivot;
    int middle = start + (end - start) / 2; // 중간 색인 산출, (start + end)/2의 오버플로우 방지형
    sort3Elements(array, start, middle, end); // 시작, 중앙, 끝의 3값 정렬
    // 3값 정렬 이상의 정렬이 필요한 경우 빠른 정렬 시도
    if (end - start >= 3) {
        pivot = array[middle];
        swap(array, middle, end - 1);
        // start, end 색인의 값들은 이미 피벗 기준으로 정렬된 상태이므로 각각 start - 1 + 1, end - 1로 시작
        left = start;
        right = end - 1;

        while (true) {
            while (array[++left] < pivot && left < end);
            while (array[--right] > pivot && start < right);
            if (left >= right) {
                break;
            }
            swap(array, left, right);
        }

        swap(array, left, end - 1);
        motQuickSort(array, start, left - 1);
        motQuickSort(array, left + 1, end);
    }
}


/**
 * Dynamically prompt for string without knowing string size
 * https://stackoverflow.com/a/25233929
 */
void *safeRealloc(void *ptr, size_t size) {
    void *newPtr = realloc(ptr, size);
    if (newPtr == NULL) { // 메모리 부족일 때
        free(ptr);
    }
    return newPtr;
}

char *allocFromStdin(void) {
    int size = 32; // 기본 문자열 크기
    char *str = malloc(size * sizeof(char));
    if (str == NULL) {
        return NULL; // 메모리 부족
    }
    char c = '\0';
    int i = 0;
    do {
        c = getchar();
        if (c == '\r' || c == '\n') {
            c = '\0'; // 사용자가 <Enter>를 누르면 문자열을 끝냄
        }
        if (i == size) {
            size *= 2; // 문자열 크기 증설
            str = safeRealloc(str, size * sizeof(char)); // 재할당
            if (str == NULL) {
                return NULL; // 메모리 부족
            }
        }
        str[i++] = c;
    } while (c != '\0');
    str = safeRealloc(str, i); // 문자열 크기로 메모리 정리
    return str;
}

/**
 * 2. 3개의 서로 다른 정수를 입력받고 가장 작은 수를 출력하는 프로그램을 작성하라.
 */
void runAssignment2() {
    printf("정수 n개를 입력하시오: ");
    char *arrayStr = allocFromStdin();
    int len = strlen(arrayStr);
    int inputLength = 1;
    for (int i = 0; i < len; i++) {
        if (arrayStr[i] == ' ' || arrayStr[i] == ',') {
            arrayStr[i] = ',';
            inputLength++;
        }
    }

    int *inputArray = malloc(sizeof(int) * (inputLength));
    char *splitArrayStrContext = NULL;
    char *splitArrayStr = strtok_r(arrayStr, ",", &splitArrayStrContext);
    int arrayIndex = 0;
    while (splitArrayStr != NULL) {
        inputArray[arrayIndex++] = atoi(splitArrayStr);
        splitArrayStr = strtok_r(splitArrayStrContext, ",", &splitArrayStrContext);
    }
    motQuickSort(inputArray, 0, inputLength - 1);

    printf("가장 작은 수는 %d입니다.\n", inputArray[0]);
    printf("입력된 정수의 개수: %d\n", inputLength);
    printf("중간 값 빠른 정렬(Median of three QuickSort) 결과: \n[");
    for (int i = 0; i < inputLength - 1; i++) {
        printf("%d", inputArray[i]);
        printf(", ");
    }

    printf("%d", inputArray[inputLength - 1]);
    printf("]\n");

    free(inputArray);
    free(arrayStr);
}

int main() {
    runAssignment2();
}
