@echo off
pushd %~dp0\..\
call premake\windows_premake5.exe vs2019
popd
IF %ERRORLEVEL% NEQ 0 (
	PAUSE
)
