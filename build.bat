@echo off

set opts=-FC -GR- -EHa- -nologo -Zi
set linker_opts=-L glfw3 opengl32.lib
set code=%cd%
pushd build
cl %opts% %code%\src\main.c %linker_opts% -FeDungeonMaster
popd
