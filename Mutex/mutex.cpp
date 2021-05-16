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
	// �쐬���Ɋ��ɓ������O�ō쐬����Ă����ꍇ�́A
	// �V�K�ɍ쐬���ꂸ�A���ɍ쐬�ς݂̃n���h����Ԃ��Ă���܂��B

	HANDLE hThread = CreateThread(NULL, 0, dothread, NULL, 0, NULL);

	WaitForSingleObject(hThread, INFINITE);
	std::cout << "Thread done" << std::endl;
	CloseHandle(hThread);

	// hMutex��Close���ĂȂ����A�ǂ����ǂ����̃^�C�~���O�ł�����Mutex�͍폜����Ă���ۂ�
	return 0;
}
