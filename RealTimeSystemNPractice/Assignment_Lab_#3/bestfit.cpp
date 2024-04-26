#include <bits/stdc++.h>

using namespace std;

// Best Fit 알고리즘을 이용하여 필요한 bin의 개수를 반환
int best_fit(int weight[], int n, int c) {
    // bin 개수를 초기화
    int result = 0;
    // bin에서 남은 공간을 저장하기 위한 배열을 생성
    int *bin_remain = new int[n];
    // 항목을 하나씩 배치
    for (int i = 0; i < n; i++) {
        // weight[i]를 넣을 수 있는 최적 bin을 찾기
        int j;
        // 남은 최소 공간과 최적 bin의 색인을 초기화
        int min = c + 1, bin_index = 0;
        for (j = 0; j < result; j++) {
            if (bin_remain[j] >= weight[i] && bin_remain[j] - weight[i] < min) {
                bin_index = j;
                min = bin_remain[j] - weight[i];
            }
        }
        // weight[i]를 넣을 수 있는 bin이 없다면 새로운 bin을 생성
        if (min == c + 1) {
            bin_remain[result] = c - weight[i];
            result++;
        } else {
            // 항목을 최적의 bin에 배정
            bin_remain[bin_index] -= weight[i];
        }
    }
    delete[] bin_remain;
    return result;
}

int main() {
    int weight[] = {2, 5, 4, 7, 1, 3, 8, 2, 5, 4, 7, 1, 3, 8};
    int c = 10;
    int n = sizeof(weight) / sizeof(weight[0]);
    cout << "Number of bins required (Best Fit) : "
         << best_fit(weight, n, c);
    return 0;
}