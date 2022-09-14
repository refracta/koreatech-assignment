프로그래밍 과제 8 (C++ 프로그래밍, 최영규 교수님)
=============
```
3.8.8절의 Monster World 프로그램을 다음과 같이 확장하라.
 (0) 먼저 8.8절의 Monster World 프로그램을 구현하고 동작을 확인하라.
 (1) 이 프로그램의 Monster클래스에 실습문제 7.3과 같이 “에너지”를 나타내는 속성을 추가하고, 관련 함수들을 수정하라. Monster의 생성자와 eat(), print()함수를 수정하면 된다.
 (2) Monster클래스에 “에너지” 값을 반환하는 getEnergy()함수를 추가하라. 이 함수는 private 멤버인 nEnergy를 반환한다.
 (3) 이제 에너지가 0이 되면 몬스터가 사라지도록 프로그램을 수정하라. 이를 위해 MonsterWorld클래스에 checkStarvation()함수를 추가한라. 이 함수에서는 모든 몬스터의 에너지 레벨을 검사하여 0인 몬스터들을 모두 동적으로 해제한다. 특히 pMon 배열에서 삭제할 항목의 처리에 유의해야 한다. 힌트: k번째 항목을 삭제하는 경우 맨 마지막 항목을 k번째 항목에 복사하고 몬스터의 수를 1 감소하면 된다.
 (4) Monster클래스에 몬스터의 수를 나타내는 정적 멤버 변수를 추가하라. 또한 생성자와 소멸자에서 이 멤버 변수의 값을 적절히 갱신하고, 현재 몬스터의 수를 출력하는 정적 멤버 함수 printCount()를 구현하라. 화면을 갱신할 때 마다 이 함수를 호출하여 전체 몬스터의 수를 출력한다. (이 정적 변수의 값은 MonsterWorld의 nMon과 동일하도록 유지되어야 한다.)
 (5) 화면 출력은 다음의 예를 참고하여 구성하라.
```
![](https://user-images.githubusercontent.com/58779799/115997600-9ab95900-a61e-11eb-8c53-f50c086cbf42.png)
![](https://user-images.githubusercontent.com/58779799/115997601-9b51ef80-a61e-11eb-94bd-01d4ea9526f6.png)
![](https://user-images.githubusercontent.com/58779799/115997602-9bea8600-a61e-11eb-92d4-2077f1b0b8cf.png)
Tested on VS2019 (C++14)