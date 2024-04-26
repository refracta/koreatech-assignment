#include <bits/stdc++.h>
using namespace std;

// Next Fit 알고리즘을 이용하여 필요한 bin의 개수를 반환
int next_fit(int weight[], int n, int c) {
    // 결과 (bin 수)와 현재 bin의 남은 용량을 초기화
    int result = 0;
    int bin_remain = c;
    // 항목을 하나씩 배치
    for (int i = 0; i < n; i++) {
        // 이 항목이 현재 bin에 들어갈 수 없다면
        if (weight[i] > bin_remain) {
            result++;
            // 새로운 bin을 사용
            bin_remain = c - weight[i];
        } else
            bin_remain -= weight[i];
    }
    return result;
}

int main() {
    int weight[] = {2, 5, 4, 7, 1, 3, 8, 2, 5, 4, 7, 1, 3, 8};
    int c = 10;
    int n = sizeof(weight) / sizeof(weight[0]);
    cout << "Number of bins required (Next Fit) : "
         << next_fit(weight, n, c);
    return 0;
}