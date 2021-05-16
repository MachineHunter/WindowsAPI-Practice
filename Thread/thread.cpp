// https://www.paveway.info/entry/2020/04/19/win32api_thread

#include <windows.h>
#include <iostream>

DWORD WINAPI dothread(LPVOID pParam) {  // à¯êîÇÃLPVOIDñ≥Ç¢Ç∆ÉGÉâÅ[Ç…Ç»ÇÈÇÃÇ≈íçà”
	MessageBox(NULL, "inside thread", "info", MB_OK);
	return 0;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	HANDLE hThread = CreateThread(NULL, 0, dothread, NULL, 0, NULL);
	HANDLE hThread2 = CreateThread(NULL, 0, dothread, NULL, 0, NULL);

	WaitForSingleObject(hThread, INFINITE);
	std::cout << "Thread1 done" << std::endl;
	CloseHandle(hThread);

	WaitForSingleObject(hThread2, INFINITE);
	std::cout << "Thread2 done" << std::endl;
	CloseHandle(hThread2);

	return 0;
}
