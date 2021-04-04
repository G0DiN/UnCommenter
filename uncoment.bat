@echo off
set /p pathToFile="Write path to directory:"
set batFilePath=%~dp0
set appPath=%batFilePath%obj\Debug\UnComment.exe

echo "Please wait"
start /WAIT /B %appPath% %pathToFile%
pause