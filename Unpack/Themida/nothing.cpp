#include <Windows.h>
#include <sstream>

typedef unsigned __int64 QWORD;

extern "C" __declspec(dllexport) void __cdecl ExportFunc() {
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
		 return TRUE;
    }
    
    return TRUE;
}



