@echo off
setlocal

if "%~1"=="" (
  echo Usage: build-and-run.bat ^<source.c^> [args...]
  exit /b 1
)

set SRC=%~1
set OUT=%~n1.exe

set GCC=C:\msys64\mingw64\bin\gcc.exe

set CFLAGS=-std=c99 -I. -g -O0 ^
  -Wall -Wextra -Wshadow -Wcast-align -Wpointer-arith ^
  -Wno-unused-parameter -Wno-unused-function ^
  -fno-omit-frame-pointer -fstack-protector-strong

"%GCC%" %CFLAGS% "%SRC%" -o "%OUT%"
if errorlevel 1 exit /b %errorlevel%

".\%OUT%" %2 %3 %4 %5 %6 %7 %8 %9
exit /b %errorlevel%
