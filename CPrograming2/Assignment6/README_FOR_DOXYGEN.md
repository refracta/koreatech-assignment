# Assignment6 # {#mainpage}

## 문제
```
<팀 출제 문제로 풀지 않음> Lab6-1. 카드 나눠주기 (팀4)
Lab6-2. 베팅판 게임 (팀1)
Lab6-3. 워드 테이블 (김영우 조교)
```

## 개발 및 컴파일 환경
Windows Server 2019 + CLion + WSL(Ubuntu 18.04) + C99에서 작업되었고 GCC를 통해 i686-w64-mingw32로 윈도우용 바이너리를 크로스 컴파일하였습니다.

프로젝트 파일은 한글 출력 호환을 위해 CP949로 인코딩되었습니다.

## 빌드 방법 (Ubuntu 18.04)
```
apt-get install mingw-w64
cmake CMakeLists.txt
make
```

## 구조
```
src: 문제 소스 코드 수록
bin: 크로스 컴파일된 윈도우용 바이너리 수록
```

## 실행 결과 캡쳐
### Problem2	Lab6-2. 베팅판 게임 (팀1)
![Problem2](../report/capture/Problem2.png)
### Problem3	Lab6-3. 워드 테이블 (김영우 조교)
![Problem3](../report/capture/Problem3.png)

## 소감
마지막으로 수행하는 팀 프로젝트에서 만든 문제 과제라고 생각하니 조금 아쉽기도 했지만 재미있었습니다!

## 기타
[GitHub](https://github.com/refracta/koreatech-assignment/tree/master/CPrograming2)