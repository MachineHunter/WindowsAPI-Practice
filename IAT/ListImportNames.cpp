#include <windows.h>
#include <dbghelp.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#pragma comment(lib, "dbghelp.lib")

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	ULONG cbSize;
	TCHAR szMyPath[MAX_PATH];
	HMODULE hModule;
	PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor = NULL;

	GetModuleFileName(NULL, szMyPath, _countof(szMyPath));
	hModule = GetModuleHandle((LPCSTR)szMyPath);
	pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hModule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &cbSize);

	if (pImageImportDescriptor == NULL)
		MessageBox(NULL, TEXT("error"), TEXT("null"), MB_OK);
	else {
		while(pImageImportDescriptor->Name!=NULL) {
			LPCSTR pszDllName = (LPCSTR)((PBYTE)(hModule)+pImageImportDescriptor->Name);
			MessageBox(NULL, pszDllName, TEXT("DLL name"), MB_OK);
			pImageImportDescriptor++;
		}
	}
	
	CloseHandle(hModule);
	return 0;
}

