#include <windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	int i=0;
	while(1) {
		if(i%5==0) printf("%d\n", i);
		Sleep(1000);
		i++;
	}

	return TRUE;
}
