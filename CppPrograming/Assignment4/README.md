프로그래밍 과제 4 (C++ 프로그래밍, 최영규 교수님)
=============
## 1. 게임으로 배우는 C++ 190~196쪽의 코드를 참고하여 퍼즐 게임을 구현하라.
```
(1) 게임은 교재와 같이 4x4로 구현해도 되고, 3x3이나 5x5등 다른 크기로 구현해도 됨
(2) 랭킹은 10위까지 관리되도록 구현하며, 랭킹 파일은 가급적 이진 파일로 저장할 것. (이진 파일이 어려운 경우 텍스트 파일로 저장해도 됨)
(3) 점수 계산은 이동 횟수가 아니라 시간을 기준으로 처리하도록 함. 즉, 조금이라도 빨리 해결한 사람이 더 높은 랭킹을 가짐
(보너스 최대 2점) 203쪽의 실습문제 4에서 게임 확장 기능 구현
--> (2) replay 기능
--> (3-4) 게임 저장/다시 시작 기능
--> (5) 아스키 아트를 이용한 그림 퍼즐 기능
```
Tested on VS2019 (C++14)


![](https://user-images.githubusercontent.com/58779799/112709105-c818c700-8ef9-11eb-8353-3517ef9fa39f.gif)
> 셔플 횟수가 1로 설정된 시연용 이미지입니다.
