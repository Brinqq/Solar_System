SETLOCAL
set maketype="MinGW Makefiles"
set builddir= build\
set arg1=%1

GOTO :START

:fullcompile
cmake -G %maketype% src/ -B %builddir%
pushd build
mingw32-make
popd
call scripts\cc.bat
GOTO :END

:makecompile
pushd build
mingw32-make
popd
GOTO :END

:START

if "%arg1%" == "full" (GOTO :fullcompile)

call :makecompile

:END
ENDLOCAL
