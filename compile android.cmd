@echo off
:start
ECHO [1] x86
ECHO [2] ARM
set /p appabi="Architecture: "

IF "%appabi%"=="1" (
start cocos compile -p android --app-abi x86 --android-studio	
)

IF "%appabi%"=="2" (
start cocos compile -p android --android-studio	
)

pause
goto start