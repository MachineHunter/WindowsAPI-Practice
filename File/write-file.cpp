// http://wisdom.sakura.ne.jp/system/winapi/win32/win111.html
// http://wisdom.sakura.ne.jp/system/winapi/win32/win113.html

#include <windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	HANDLE hFile;
	hFile = CreateFile(__argv[1], GENERIC_WRITE, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE) {
		MessageBox(NULL, "ファイルが開けません", "error", MB_OK);
		return 1;
	}

	DWORD writesize;
	WriteFile(hFile, __argv[2], lstrlen(__argv[2]), &writesize, NULL);

	MessageBox(NULL, "file write successful", "info", MB_OK);

	CloseHandle(hFile);
	return 0;
}
