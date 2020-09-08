프로그래밍 과제 2 (C 프로그래밍, 강승우 교수님)
=============
```
1. 중심각과 반지름을 입력받아 부채꼴의 넓이를 계산하고 출력하는 프로그램을 작성하여 보자. 
원주율은 3.14라고 가정한다. 모든 변수는 float형으로 입력한다.
2. 달러($)를 입력하면 원(\) 으로 얼마인지 알려주는 프로그램을 작성하라. 
환율은 1$ 당 1234.5\ 이라고 가정한다. 모든 변수는 float형으로 입력한다.
3. 사용자가 두 개의 알파벳 대문자를 입력하면, 두 문자의 아스키 코드값의 곱을 출력하는 프로그램을 작성하라.
4. 초만으로 표기된 시간을 입력받아 시, 분, 초로 계산하여 표기할 수 있도록 하는 프로그램을 작성하라. 
입력되는 초는 항상 1시간을 넘는다고 가정한다. 
5. ‘a’, ‘b’, ‘c’, ‘d’, 이 4개의 문자의 아스키 코드 값을 알아내고
이를 8진수, 10진수, 16진수로 출력하는 프로그램을 작성하라.

 * 개인적인 도전 과제:
 * 1. 주어진 것보다 Hardcore 하게
```

2번 문제 프로그램은 libcurl(https://curl.haxx.se/libcurl/) 외부 라이브러리를 사용하며 Debian Linux(Ubuntu 18.04 LTS)에서 테스트되었습니다.
```
apt-get install libcurl4-openssl-dev
gcc main.c -lcurl -o main
./main
```
Tested on CLion + WSL (GCC, C99)

Run Result: https://github.com/refracta/koreatech-assignment/blob/master/CPrograming1/Assignment2/RESULT.pdf
