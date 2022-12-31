@ECHO OFF

if exist dist rd /S /Q dist

mingw32-make PLATFORM=PLATFORM_ANDROID
