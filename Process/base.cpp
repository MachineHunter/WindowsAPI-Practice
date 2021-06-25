#include <windows.h>
#include <dbghelp.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#pragma comment(lib, "dbghelp.lib")

DWORD WINAPI dothread(LPVOID param) {
	ULONG cbSize;
	TCHAR szMyPath[MAX_PATH];
	HMODULE hModule;

	GetModuleFileName(NULL, szMyPath, _countof(szMyPath));

	std::stringstream s;
	s << szMyPath << std::endl;
	MessageBox(NULL, s.str().c_str(), "info", MB_OK);

	hModule = GetModuleHandle((LPCSTR)szMyPath);

	std::stringstream ss;
	ss << std::hex << hModule << std::endl;
	MessageBox(NULL, ss.str().c_str(), "info", MB_OK);

	CloseHandle(hModule);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, dothread, hModule, 0, 0);
    return TRUE;
}
