@echo off

 ::::::::::::::::
 :: BUILD TOOL ::
 ::::::::::::::::
 : �� ������ Command-Line ���� ����� �ȳ��Ӱ� ���ÿ� �������Դϴ�.
 : IDE�� �̿��� ���� ��� �ȳ��� �Ʒ� �ּҿ��� Ȯ�� �����մϴ�.
 : https://github.com/refracta/koreatech-assignment/wiki/CMake-Build-Guide
 : CMake�� VS 2019�� ��ġ�� ȯ�濡�� README.txt�� build.bat���� �̸� ���� �� �����ϸ� �������� �۵��մϴ�. 
 : (CMake�� ����Ͽ� �ַ�� ���ϵ�(sln, vcxproj)�� �ڵ����� �����ϰ� ���带 �����մϴ�)
 : CMake: https://cmake.org/download/
 : ����� ���� �۾��� �̷������ ���� ������Ʈ ������ bin/Win32, bin/x64 ������ �����ǰ� �̰��� ���� ����� ����˴ϴ�.
 : by refracta

 :::::::::::::::::::::::::::
 :: MSBUILD.EXE ��ġ ���� ::
 :::::::::::::::::::::::::::
 : �� ������Ʈ�� ���带 ���� msbuild.exe�� ����մϴ�.
 set MSBUILD_DEFAULT="msbuild.exe"
 : Visual Studio Community 2019�� ��ġ�Ǿ� �ִ� ���
 set MSBUILD_COMMUNITY="%programfiles(x86)%\Microsoft Visual Studio\2019\Community\MSBuild\Current\Bin\msbuild.exe"
 : Visual Studio Professional 2019�� ��ġ�Ǿ� �ִ� ���
 set MSBUILD_PROFESSIONAL="%programfiles(x86)%\Microsoft Visual Studio\2019\Professional\MSBuild\Current\Bin\msbuild.exe"
 : Visual Studio Enterprise 2019�� ��ġ�Ǿ� �ִ� ���
 set MSBUILD_ENTERPRISE="%programfiles(x86)%\Microsoft Visual Studio\2019\Enterprise\MSBuild\Current\Bin\msbuild.exe"

 ::::::::::::::::::::::::::::
 :: MSBUILD_PATH �ڵ� ���� ::
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
   set /p MSBUILD_PATH=msbuild.exe ��θ� �Է����ּ���: 
 )

 :::::::::::::::::::::::::::::::::::::::::::
 :: Clean CMakeFiles & CMakeCache.txt <1> ::
 :::::::::::::::::::::::::::::::::::::::::::
 rmdir /s /q CMakeFiles 2>NUL && del CMakeCache.txt 2>NUL

 ::::::::::::::::::::::
 :: 32��Ʈ ���� ��� ::
 ::::::::::::::::::::::
 cmake -G "Visual Studio 16 2019" -A Win32 CMakeLists.txt
 %MSBUILD_PATH% /p:Configuration=Release /p:Platform=Win32 /p:OutDir=.\bin\Win32\ .\ALL_BUILD.vcxproj

 :::::::::::::::::::::::::::::::::::::::::::
 :: Clean CMakeFiles & CMakeCache.txt <2> ::
 :::::::::::::::::::::::::::::::::::::::::::
 rmdir /s /q CMakeFiles 2>NUL && del CMakeCache.txt 2>NUL

 ::::::::::::::::::::::
 :: 64��Ʈ ���� ��� ::
 ::::::::::::::::::::::
 cmake -G "Visual Studio 16 2019" -A x64 CMakeLists.txt
 %MSBUILD_PATH% /p:Configuration=Release /p:Platform=x64 /p:OutDir=.\bin\x64\ .\ALL_BUILD.vcxproj