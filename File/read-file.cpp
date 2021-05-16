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
	hFile = CreateFile(lpCmdLine, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE) {     // 失敗
		MessageBox(NULL, "ファイルが開けません", "error", MB_OK);
		return 1;
	}

	DWORD readsize;
	LPSTR msg = (LPSTR)malloc(GetFileSize(hFile, NULL));
	ReadFile(hFile, msg, GetFileSize(hFile, NULL), &readsize, NULL);

	MessageBox(NULL, msg, "file content", MB_OK);

	CloseHandle(hFile);
	return 0;
}


/*
 *BOOL ReadFile(
 *   HANDLE hFile ,
 *   LPVOID lpBuffer ,
 *   DWORD nNumberOfBytesToRead ,
 *   LPDWORD lpNumberOfBytesRead ,
 *   LPOVERLAPPED lpOverlapped
 *);
 */
