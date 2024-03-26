#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;

// 프로세스 정보를 담는 구조체
struct process {
    int pid; // 프로세스 ID
    int arrival_time; // 도착 시간
    int burst_time; // 실행 시간
    int start_time; // 시작 시간
    int completion_time; // 완료 시간
    int turnaround_time; // 반환 시간
    int waiting_time; // 대기 시간
    int response_time; // 응답 시간
};

// 도착 시간에 따라 프로세스를 정렬하는 함수
bool compareArrival(process p1, process p2) {
    return p1.arrival_time < p2.arrival_time;
}

// 프로세스 ID에 따라 프로세스를 정렬하는 함수
bool compareID(process p1, process p2) {
    return p1.pid < p2.pid;
}

int main() {
    int n; // 프로세스의 수
    struct process p[100]; // 프로세스를 저장할 배열
    float avg_turnaround_time; // 평균 반환 시간
    float avg_waiting_time; // 평균 대기 시간
    float avg_response_time; // 평균 응답 시간
    float cpu_utilisation; // CPU 사용률
    int total_turnaround_time = 0; // 총 반환 시간
    int total_waiting_time = 0; // 총 대기 시간
    int total_response_time = 0; // 총 응답 시간
    int total_idle_time = 0; // 총 유휴 시간
    float throughput; // 처리량

    cout << setprecision(2) << fixed;

    // 프로세스 정보 입력 처리
    cout << "Enter the number of processes: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }

    sort(p, p + n, compareArrival);

    for (int i = 0; i < n; i++) {
        // 프로세스 시작 시간, 완료 시간, 반환 시간, 대기 시간, 응답 시간을 계산
        p[i].start_time = (i == 0) ? p[i].arrival_time : max(p[i - 1].completion_time, p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        // 총 시간들을 계산
        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
        total_idle_time += (i == 0) ? (p[i].arrival_time) : (p[i].start_time - p[i - 1].completion_time);
    }

    // 평균 시간과 CPU 사용률, 처리량을 계산
    avg_turnaround_time = (float) total_turnaround_time / n;
    avg_waiting_time = (float) total_waiting_time / n;
    avg_response_time = (float) total_response_time / n;
    cpu_utilisation = ((p[n - 1].completion_time - total_idle_time) / (float) p[n - 1].completion_time) * 100;
    throughput = float(n) / (p[n - 1].completion_time - p[0].arrival_time);

    sort(p, p + n, compareID);

    cout << endl;
    cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;

    for (int i = 0; i < n; i++) {
        // 각 프로세스의 상세 정보를 출력
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t"
             << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t"
             << p[i].response_time << "\t" << "\n" << endl;
    }
    // 평균 시간, CPU 사용률, 처리량을 출력
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