@echo off
pushd %~dp0\..\
call thirdparty\premake\bin\premake5.exe clean
popd
PAUSE
