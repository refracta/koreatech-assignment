# Assignment5

## 문제
```
Lab5-1. 아스키코드를 통한 암호 해독（팀1)
<팀 출제 문제로 풀지 않음> Lab5-2. 4x4 행렬 뒤집기（팀5)
Lab5-3. 일차원 배열로 이차원 배열 표현하기 (김영우 조교)
<선물 수령함> Lab5-4. 시험기간 선물 - 이중 포인터 (김덕수 교수)
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
report: CodeCollection, Report, Capture 수록
doxygen: 문제에 대한 Doxygen HTML Document 수록
```

## 실행 결과 캡쳐
### Problem1	Lab5-1. 아스키코드를 통한 암호 해독（팀1)
![Problem1](./report/capture/Problem1.png)
### Problem2	Lab5-3. 일차원 배열로 이차원 배열 표현하기 (김영우 조교)
![Problem3](./report/capture/Problem3.png)

## 소감
```C
*((message*) 소감?! )
```
선물 수령했습니다! 감사합니다!

```C
cudaMemcpy(gMemory, present, presentSize, CudaMemcpyCProgramming2ToMulticoreProgramming);
```
나중에 멀티코어 프로그래밍 수강하면 cudaError_t 'cudaSuccess' 로 나오나요? :D?

## 기타
[GitHub](https://github.com/refracta/koreatech-assignment/tree/master/CPrograming2)
