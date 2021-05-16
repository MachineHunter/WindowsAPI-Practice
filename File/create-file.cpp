// http://wisdom.sakura.ne.jp/system/winapi/win32/win111.html

#include <windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	HANDLE hFile;
	hFile = CreateFile(lpCmdLine, GENERIC_READ, 0, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);

	if(hFile == INVALID_HANDLE_VALUE) {     // Ž¸”s
		MessageBox(NULL, "File Creation Failed!", "error", MB_OK);
		return 1;
	}

	MessageBox(NULL, "File Created Successfully", "success", MB_OK);
	CloseHandle(hFile);
	return 0;
}


// HANDLE CreateFile(
// 	LPCTSTR lpFileName, 
//    DWORD dwDesiredAccess,
//    DWORD dwShareMode,
//    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
//    DWORD dwCreationDisposition,
//    DWORD dwFlagsAndAttributes,
//    HANDLE hTemplateFile
// );

// BOOL CloseHandle(HANDLE hObject);
