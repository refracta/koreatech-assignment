# 용산 전자상가 탈출하기
## 문제 [(PPT 바로가기)](https://docs.google.com/presentation/d/e/2PACX-1vSRqDTt6DdDhc0iCUxOtus4WyGY1W843peYzcvgTlROoQD41EhVIsYwpvlta5iP_tYLuMPc9wkACEAz/pub?start=false&loop=false&delayms=3000&slide=id.g9560dc4242_3_0) [(추가 PPT 자료)](http://private_raw.abstr.net/files/AddtionalPPT.pptx)
당신은 C프로그래밍II 과목 수강에 사용 할 컴퓨터를 구입하러 용산 지하상가에 들어왔습니다.
어찌저찌 컴퓨터는 구입하는데 성공했지만 지하상가가 너무 번잡한 나머지 자신의 위치와 출구가 어디인지 알 수 없게 되어버렸습니다.
당신은 구입한 컴퓨터를 켜고 프로그래밍을 통해 나갈 방법을 궁리하기 시작했습니다.

용산 지하상가는 10x10 격자로 표현됩니다.
당신과 용산 지하상가의 출구는 10x10 격자판의 내부의 어딘가에(무작위로) 존재합니다.

당신은 매 차례마다 8개의 동작을 취할 수 있습니다.

## SEEK_*
```
SEEK_UP
SEEK_DOWN
SEEK_LEFT
SEEK_RIGHT
```
위의 상태는 본인의 위치를 기준으로 상하좌우에 출구가 있는지 확인합니다. (있으면 SEEK_SUCCESS 변수를 1로 변경합니다)

## MOVE_* 
```
MOVE_UP
MOVE_DOWN
MOVE_LEFT
MOVE_RIGHT
```
위의 상태는 본인의 위치를 상하좌우로 움직입니다. (벽에 부딪힌 경우 움직이지 않으며, 움직이는데 성공했을 경우 MOVE_SUCCESS 변수를 1로 변경합니다)


## <용산 지하상가> 그리기 코드 조각

이 코드 조각에는 위의 함수는 2차원 배열로 이루어진 용산 지하상가의 모습을 출력하는 코드가 들어갑니다. 본인의 위치는 @로 출구는 <로 비어있는 공간은 .로 벽은 #로 표현합니다.
벽은 10x10 격자 외부에 1칸의 두께로 둘러져 있습니다.

## <움직임 전략> 코드 조각
이 코드 조각에는 자신이 매 차례 할 동작을 정의합니다. NEXT_FUNC를 위의 동작 상수로 초기화하여 다음 차례에 행할 동작을 지시할 수 있으며 이 함수 안에서는 좌표를 읽을 수 없습니다.

## 문제 (problem.c)
아래의 코드에서 프로그램이 끝날 수 있도록 위의 함수를 구현하세요.

```C
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int x;
int y;

int outX;
int outY;

int turn = 0;

int NEXT_FUNC = 0;
int SEEK_SUCCESS = 0;
int MOVE_SUCCESS = 0;

const int MOVE_UP = 1;
const int MOVE_DOWN = 2;
const int MOVE_LEFT = 3;
const int MOVE_RIGHT = 4;
const int SEEK_UP = 5;
const int SEEK_DOWN = 6;
const int SEEK_LEFT = 7;
const int SEEK_RIGHT = 8;

int main() {
	// srand 초기화
    srand(time(NULL));
	/*
		x = rand() % 10;
		y = rand() % 10;
		outX = rand() % 10;
		outY = rand() % 10;
		// 초기화 예시입니다.
	*/
    while (!(x == outX && y == outY)) {
        // <용산 지하상가 그리기>
		
        if (turn > 1000) {
            printf("당신은 용산 지하상가 안에서 굶어죽었습니다.");
            exit(0);
        }
		
        SEEK_SUCCESS = 0;
        MOVE_SUCCESS = 0;
        switch (NEXT_FUNC) {
            case 1:
                // MOVE_UP
                break;
            case 2:
                // MOVE_DOWN
                break;
            case 3:
                // MOVE_LEFT
                break;
            case 4:
                // MOVE_RIGHT
                break;
            case 5:
                // SEEK_UP
                break;
            case 6:
                // SEEK_DOWN
                break;
            case 7:
                // SEEK_LEFT
                break;
            case 8:
                // SEEK_RIGHT
                break;
        }
        
        // <움직임 전략>
        printf("Current Turn: %d\n", turn++);
    }
    
	// <용산 지하상가 그리기>
    printf("End Turn: %d\n", turn);
    printf("용산 지하상가에서 탈출했습니다.");
}
```

## 프로그램의 목적
배열을 통한 유사 로그라이크 게임 응용 프로그램 제작

## 프로그램의 기능
제약된 정보 상황에서의 필요한 위치까지 이동하기 위한 경로탐색 시뮬레이션

## 입력 양식
없음

## 출력 양식
output.pdf 참조

## 해설
[solve.c 참조](https://github.com/refracta/koreatech-assignment/blob/master/CPrograming2/MyProblem1/solve.c)
