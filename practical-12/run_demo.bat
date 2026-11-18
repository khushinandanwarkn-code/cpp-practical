@echo off
title Student Portal - Khushboo Nandanwar (49, AIDS-C)
cd /d "%~dp0"

echo ==============================================
echo   Student Portal - C++ Mini Project
echo   Khushboo Nandanwar ^| Roll No 49 ^| AIDS-C
echo ==============================================
echo.

where g++ >nul 2>nul
if errorlevel 1 (
    echo g++ was not found. Please install MinGW / g++ first.
    pause
    exit /b
)

echo Compiling student_portal.cpp ...
g++ student_portal.cpp -o portal.exe
if errorlevel 1 (
    echo Compile failed. Check the error above.
    pause
    exit /b
)
echo Compiled successfully!
echo.

"%~dp0portal.exe"

echo.
pause
