gcc -c testdll.cpp
gcc testdll.o -o DLLTest.dll -shared
rundll32.exe DLLTest.dll,TestFunc
