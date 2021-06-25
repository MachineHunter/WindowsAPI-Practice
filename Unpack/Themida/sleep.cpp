#include <windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	for(int i=0; 1; i++) {
		if(i%5==0) printf("%d\n", i);
		Sleep(1000);
	}
	return TRUE;
}
