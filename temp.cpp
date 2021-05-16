// 

#include <windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	MessageBox(NULL, TEXT("Hello World!"), TEXT("Test"), MB_YESNO | MB_ICONEXCLAMATION);
	return 0;
}
