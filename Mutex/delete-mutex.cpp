// 

#include <windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "name_of_mutex");
	if(hMutex==NULL) {
		MessageBox(NULL, "name_of_mutex already deleted", "info", MB_OK);
		return 1;
	}
	CloseHandle(hMutex);
	return 0;
}
