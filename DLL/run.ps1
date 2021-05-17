g++ -c testdll.cpp
g++ testdll.o -o DLLTest.dll -shared
rundll32.exe DLLTest.dll,TestFunc
