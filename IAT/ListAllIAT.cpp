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
	PIMAGE_THUNK_DATA pFirstThunk = NULL;
	PIMAGE_THUNK_DATA pOriginalFirstThunk = NULL;

	GetModuleFileName(NULL, szMyPath, _countof(szMyPath));
	hModule = GetModuleHandle((LPCSTR)szMyPath);
	pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hModule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &cbSize);
	
	while (pImageImportDescriptor->Name != NULL) {
		pFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImageImportDescriptor->FirstThunk);
		pOriginalFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImageImportDescriptor->OriginalFirstThunk);
		LPCSTR pszDllName = (LPCSTR)((PBYTE)hModule + pImageImportDescriptor->Name);
		MessageBox(NULL, pszDllName, "will show imports func addr from this dll", MB_OK | MB_ICONINFORMATION);

		while (pFirstThunk->u1.Function != NULL) {
			std::stringstream ss;
			ss << "0x" << std::hex << pFirstThunk->u1.Function << std::endl;

			PIMAGE_IMPORT_BY_NAME pImageImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hModule + pOriginalFirstThunk->u1.AddressOfData);
			LPCSTR pszFuncName = (LPCSTR)&pImageImportByName->Name[0];

			MessageBox(NULL, ss.str().c_str(), pszFuncName, MB_OK);
			pFirstThunk++;
			pOriginalFirstThunk++;
		}
		pImageImportDescriptor++;
	}

	CloseHandle(hModule);
	return 0;
}
