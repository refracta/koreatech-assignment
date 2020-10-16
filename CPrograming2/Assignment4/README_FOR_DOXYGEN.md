# Assignment4 # {#mainpage}

## 문제
```
Lab4-1. 탱크 포탄（팀2)
Lab4-2. 달력 만들기（팀5)
Lab4-3. 반복문없이 구구단 출력하기（이재홍 조교)
Lab4-4. 메모리 세상에서 보물 찾기 (김덕수 교수)
```

## 개발 및 컴파일 환경
Problem1~3: Windows Server 2019 + CLion + WSL(Ubuntu 18.04) + C99에서 작업되었고 GCC를 통해 i686-w64-mingw32로 윈도우용 바이너리를 크로스 컴파일하였습니다.

Problem4: Windows Server 2019 + Visual Studio 2019에서 x64로 컴파일되었습니다.

프로젝트 파일은 한글 출력 호환을 위해 CP949로 인코딩되었습니다.

## 빌드 방법
### Problem1~3 (Ubuntu 18.04)
```
apt-get install mingw-w64
cmake CMakeLists.txt
make
```

### Problem4 (Windows)
```
inc - 라이브러리 헤더 파일 수록
lib - 라이브러리 파일 수록
```

Visual Studio x64 환경으로 컴파일합니다.

## 구조
```
src: 문제 소스 코드 수록
bin: 크로스 컴파일된 윈도우용 바이너리 수록
inc - 라이브러리 헤더 파일 수록
lib - 라이브러리 파일 수록
report: CodeCollection, Report, Capture 수록
doxygen: 문제에 대한 Doxygen HTML Document 수록
```

## 실행 결과 캡쳐
### Problem1	Lab4-1. 탱크 포탄（팀2)
![Problem1](../report/capture/Problem1.png)
### Problem2	Lab4-2. 달력 만들기（팀5)
![Problem2](../report/capture/Problem2.png)
### Problem3	Lab4-3. 반복문없이 구구단 출력하기（이재홍 조교)
![Problem3](../report/capture/Problem3.png)
### Problem4	Lab4-4. 메모리 세상에서 보물 찾기 (김덕수 교수)
![Problem4](../report/capture/Problem4.png)

## 소감
메모리 세상에서 보물 찾기 문제가 가장 재미있었습니다.

## 기타
[GitHub](https://github.com/refracta/koreatech-assignment/tree/master/CPrograming2)