#include <iostream>
#include <algorithm>
#include <iomanip>
#include <queue>
#include <cstring>

using namespace std;

// 프로세스 정보를 담는 구조체
struct process {
    int pid; // 프로세스 ID
    int arrival_time; // 도착 시간
    int burst_time; // 실행 시간(버스트 시간)
    int start_time; // 시작 시간
    int completion_time; // 완료 시간
    int turnaround_time; // 반환 시간
    int waiting_time; // 대기 시간
    int response_time; // 응답 시간
};

// 도착 시간에 따라 프로세스를 정렬하는 함수
bool compare1(process p1, process p2) {
    return p1.arrival_time < p2.arrival_time;
}

// 프로세스 ID에 따라 프로세스를 정렬하는 함수
bool compare2(process p1, process p2) {
    return p1.pid < p2.pid;
}

int main() {
    int n; // 프로세스의 수
    int tq; // 타임 퀀텀
    struct process p[100]; // 프로세스 배열
    float avg_turnaround_time; // 평균 반환 시간
    float avg_waiting_time; // 평균 대기 시간
    float avg_response_time; // 평균 응답 시간
    float cpu_utilisation; // CPU 사용률
    int total_turnaround_time = 0; // 총 반환 시간
    int total_waiting_time = 0; // 총 대기 시간
    int total_response_time = 0; // 총 응답 시간
    int total_idle_time = 0; // 총 유휴 시간
    float throughput; // 처리량
    int burst_remaining[100]; // 남은 실행 시간
    int idx; // 큐 순회용 색인

    // 프로세스 정보 입력 처리
    cout << setprecision(2) << fixed;

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter time quantum: ";
    cin >> tq;

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        burst_remaining[i] = p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }

    // 도착 시간에 따라 프로세스를 정렬
    sort(p, p + n, compare1);

    // 실행 시간 초기화
    for (int i = 0; i < n; i++) {
        burst_remaining[i] = p[i].burst_time;
    }

    // 프로세스 큐
    queue<int> q;
    // 현재 시간
    int current_time = 0;
    // 첫 번째 프로세스를 큐에 추가
    q.push(0);
    // 완료된 프로세스 수
    int completed = 0;
    // 프로세스의 상태 표시 배열
    int mark[100];
    memset(mark, 0, sizeof(mark));
    mark[0] = 1; // 첫 번째 프로세스 표시 초기화

    // 모든 프로세스가 완료될 때 까지
    while (completed != n) {
        // 큐의 첫번째 프로세스를 인출
        idx = q.front();
        q.pop();

        // 프로세스가 처음 실행되는 경우 초기화
        if (burst_remaining[idx] == p[idx].burst_time) {
            p[idx].start_time = max(current_time, p[idx].arrival_time);
            total_idle_time += p[idx].start_time - current_time;
            current_time = p[idx].start_time;
        }

        // 타임 퀀텀보다 남은 시간이 많으면
        if (burst_remaining[idx] - tq > 0) {
            // 타임 퀀텀만큼 남은 시간 감소 후 현재 시간 갱신
            burst_remaining[idx] -= tq;
            current_time += tq;
        } else {
            // 타임 퀀텀보다 남은 시간이 적으면
            // 남은 시간만큼 현재 시간 증가
            current_time += burst_remaining[idx];
            // 남은 시간을 0으로 설정
            burst_remaining[idx] = 0;
            // 완료된 프로세스 수 증가
            completed++;

            // 프로세스 완료 시간, 반환 시간, 대기 시간, 응답 시간을 계산
            p[idx].completion_time = current_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;

            // 총 시간들을 계산
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
        }

        // 다음에 실행할 프로세스를 큐에 추가
        for (int i = 1; i < n; i++) {
            if (burst_remaining[i] > 0 && p[i].arrival_time <= current_time && mark[i] == 0) {
                q.push(i);
                mark[i] = 1;
            }
        }

        // 남은 시간이 있는 경우, 큐에 프로세스를 다시 추가
        if (burst_remaining[idx] > 0) {
            q.push(idx);
        }

        // 큐가 빈 경우, 다음 프로세스를 찾아 추가
        if (q.empty()) {
            for (int i = 1; i < n; i++) {
                if (burst_remaining[i] > 0) {
                    q.push(i);
                    mark[i] = 1;
                    break;
                }
            }
        }
    }

    // 평균 시간과 CPU 사용률, 처리량을 계산
    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((p[n - 1].completion_time - total_idle_time) / (float) p[n - 1].completion_time) * 100;
    throughput = float(n) / (p[n - 1].completion_time - p[0].arrival_time);

    sort(p, p + n, compare2);

    cout << endl;
    cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;

    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t"
             << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t"
             << p[i].response_time << "\t" << "\n" << endl;
    }
    cout << "Average Turnaround Time = " << avg_turnaround_time << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << endl;
    cout << "Average Response Time = " << avg_response_time << endl;
    cout << "CPU Utilization = " << cpu_utilisation << "%" << endl;
    cout << "Throughput = " << throughput << " process/unit time" << endl;
}

/*

AT - 프로세스의 도착 시간
BT - 프로세스의 실행 시간
ST - 프로세스의 시작 시간
CT - 프로세스의 완료 시간
TAT - 프로세스의 반환 시간
WT - 프로세스의 대기 시간
RT - 프로세스의 응답 시간

사용된 공식들:

TAT = CT - AT
WT = TAT - BT
RT = ST - AT

*/