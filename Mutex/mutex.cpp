// https://bituse.info/winapi/17

#include <windows.h>
#include <iostream>

DWORD WINAPI dothread(LPVOID pParam) {
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, FALSE, "name_of_mutex");
	WaitForSingleObject(hMutex, INFINITE);

	MessageBox(NULL, "inside thread", "info", MB_OK);

	ReleaseMutex(hMutex);
	return 0;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	HANDLE hMutex = CreateMutex(NULL, FALSE, "name_of_mutex");
	// 作成時に既に同じ名前で作成されていた場合は、
	// 新規に作成されず、既に作成済みのハンドルを返してくれます。

	HANDLE hThread = CreateThread(NULL, 0, dothread, NULL, 0, NULL);

	WaitForSingleObject(hThread, INFINITE);
	std::cout << "Thread done" << std::endl;
	CloseHandle(hThread);

	// hMutexはCloseしてないが、どうやらどこかのタイミングでちゃんとMutexは削除されてるっぽい
	return 0;
}
