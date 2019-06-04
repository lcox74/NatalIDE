mingw32-make.exe
for /R Dependencies\SDL2\bin %%f in (*.dll) do copy %%f bin\
pause