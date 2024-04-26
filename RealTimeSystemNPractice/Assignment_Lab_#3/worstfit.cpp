#include <bits/stdc++.h>

using namespace std;

// Worst Fit 알고리즘을 이용하여 필요한 bin의 개수를 반환
int worst_fit(int weight[], int n, int c) {
    // bin 개수를 초기화
    int result = 0;
    // bin에서 남은 공간을 저장하기 위한 배열을 생성
    int *bin_remain = new int[n];
    // 항목들을 하나씩 배치
    for (int i = 0; i < n; i++) {
        // weight[i]를 넣을 수 있는 최적의 bin를 찾기
        int j;
        // 남은 최대 공간과 가장 적합하지 않은 bin의 인덱스를 초기화
        int max = -1, worst_index = 0;
        for (j = 0; j < result; j++) {
            if (bin_remain[j] >= weight[i] && bin_remain[j] - weight[i] > max) {
                worst_index = j;
                max = bin_remain[j] - weight[i];
            }
        }
        // weight[i]를 넣을 수 있는 bin이 없다면 새로운 bin을 생성
        if (max == -1) {
            bin_remain[result] = c - weight[i];
            result++;
        } else {
            // 항목을 가장 적합한 bin에 배정
            bin_remain[worst_index] -= weight[i];
        }
    }
    delete[] bin_remain;
    return result;
}

int main() {
    int weight[] = {2, 5, 4, 7, 1, 3, 8, 2, 5, 4, 7, 1, 3, 8};
    int c = 10;
    int n = sizeof(weight) / sizeof(weight[0]);
    cout << "Number of bins required (Worst Fit) : "
         << worst_fit(weight, n, c);
    return 0;
}