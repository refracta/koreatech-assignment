@echo off

 ::::::::::::::::
 :: BUILD TOOL ::
 ::::::::::::::::
 : 본 파일은 Command-Line 빌드 방법의 안내임과 동시에 빌드툴입니다.
 : IDE를 이용한 빌드 방법 안내는 아래 주소에서 확인 가능합니다.
 : https://github.com/refracta/koreatech-assignment/wiki/CMake-Build-Guide
 : CMake와 VS 2019가 설치된 환경에서 README.txt를 build.bat으로 이름 변경 후 실행하면 빌드툴로 작동합니다. 
 : (CMake를 사용하여 솔루션 파일등(sln, vcxproj)을 자동으로 생성하고 빌드를 생성합니다)
 : CMake: https://cmake.org/download/
 : 실행시 빌드 작업이 이루어지며 현재 프로젝트 폴더에 bin/Win32, bin/x64 폴더가 생성되고 이곳에 빌드 결과가 저장됩니다.
 : by refracta

 :::::::::::::::::::::::::::
 :: MSBUILD.EXE 위치 설정 ::
 :::::::::::::::::::::::::::
 : 본 프로젝트는 빌드를 위해 msbuild.exe를 사용합니다.
 set MSBUILD_DEFAULT="msbuild.exe"
 : Visual Studio Community 2019가 설치되어 있는 경우
 set MSBUILD_COMMUNITY="%programfiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\msbuild.exe"
 : Visual Studio Professional 2019가 설치되어 있는 경우
 set MSBUILD_PROFESSIONAL="%programfiles(x86)%\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\msbuild.exe"
 : Visual Studio Enterprise 2019가 설치되어 있는 경우
 set MSBUILD_ENTERPRISE="%programfiles(x86)%\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\msbuild.exe"

 ::::::::::::::::::::::::::::
 :: MSBUILD_PATH 자동 설정 ::
 ::::::::::::::::::::::::::::
 if exist %MSBUILD_DEFAULT% (
   set MSBUILD_PATH=%MSBUILD_DEFAULT%
 ) else if exist %MSBUILD_COMMUNITY% (
   set MSBUILD_PATH=%MSBUILD_COMMUNITY%
 ) else if exist %MSBUILD_PROFESSIONAL% (
   set MSBUILD_PATH=%MSBUILD_PROFESSIONAL%
 ) else if exist %MSBUILD_ENTERPRISE% (
   set MSBUILD_PATH=%MSBUILD_ENTERPRISE%
 ) else (
   set /p MSBUILD_PATH=msbuild.exe 경로를 입력해주세요: 
 )

 :::::::::::::::::::::::::::::::::::::::::::
 :: Clean CMakeFiles & CMakeCache.txt <1> ::
 :::::::::::::::::::::::::::::::::::::::::::
 rmdir /s /q CMakeFiles 2>NUL && del CMakeCache.txt 2>NUL

 ::::::::::::::::::::::
 :: 32비트 빌드 방법 ::
 ::::::::::::::::::::::
 cmake -G "Visual Studio 16 2019" -A Win32 CMakeLists.txt
 %MSBUILD_PATH% /p:Configuration=Release /p:Platform=Win32 /p:OutDir=.\bin\Win32\ .\ALL_BUILD.vcxproj

 :::::::::::::::::::::::::::::::::::::::::::
 :: Clean CMakeFiles & CMakeCache.txt <2> ::
 :::::::::::::::::::::::::::::::::::::::::::
 rmdir /s /q CMakeFiles 2>NUL && del CMakeCache.txt 2>NUL

 ::::::::::::::::::::::
 :: 64비트 빌드 방법 ::
 ::::::::::::::::::::::
 cmake -G "Visual Studio 16 2019" -A x64 CMakeLists.txt
 %MSBUILD_PATH% /p:Configuration=Release /p:Platform=x64 /p:OutDir=.\bin\x64\ .\ALL_BUILD.vcxproj