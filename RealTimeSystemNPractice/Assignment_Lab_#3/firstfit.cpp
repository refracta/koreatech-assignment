#include <bits/stdc++.h>

using namespace std;

// First Fit 알고리즘을 이용하여 필요한 bin의 개수를 반환
int first_fit(const int weight[], int n, int c) {
    // bin 개수를 초기화
    int result = 0;
    // bin에서 남은 공간을 저장하기 위한 배열을 생성
    int *bin_remain = new int[n];
    // 항목을 하나씩 배치
    for (int i = 0; i < n; i++) {
        // weight[i]를 넣을 수 있는 첫 번째 bin를 찾기
        int j;
        for (j = 0; j < result; j++) {
            if (bin_remain[j] >= weight[i]) {
                bin_remain[j] = bin_remain[j] - weight[i];
                break;
            }
        }
        // weight[i]를 수용할 수 있는 bin이 없다면
        if (j == result) {
            bin_remain[result] = c - weight[i];
            result++;
        }
    }
    delete[] bin_remain;
    return result;
}

int main() {
    int weight[] = {2, 5, 4, 7, 1, 3, 8, 2, 5, 4, 7, 1, 3, 8};
    int c = 10;
    int n = sizeof(weight) / sizeof(weight[0]);
    cout << "Number of bins required (First Fit) : " << first_fit(weight, n, c);
    return 0;
}
