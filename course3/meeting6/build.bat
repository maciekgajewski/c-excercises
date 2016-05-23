@echo off

IF "%1"=="clean" goto clean

goto build

:clean
	IF EXIST "build\" rm -rf build
	IF EXIST "main.exe" rm main.exe
	goto end

:build
	IF NOT EXIST "build\" mkdir build

	cd build
	rem cmake ../ -G "MSYS Makefiles"
	rem make
	c:\MinGW\bin\g++ -Wall -std=c++14 -pedantic -Werror ../main.cc -o../main
	cd ..
	goto end

:end