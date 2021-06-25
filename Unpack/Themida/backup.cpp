#include <Windows.h>
#include <sstream>

typedef unsigned __int64 QWORD;

extern "C" __declspec(dllexport) void __cdecl ExportFunc() {
	MessageBox(NULL, TEXT("dummy export"), TEXT("info"), MB_OK);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        int patchlen     = 21;
        QWORD offset     = 0x9d130;
        DWORD curProtection;
        DWORD temp;

		  QWORD base = (QWORD)GetModuleHandle("ntdll.dll");
		  QWORD patchaddr = base + offset;
		  void *ppatchaddr = (void*)patchaddr;

		  /*
			*std::stringstream ss;
			*ss << "patch address : 0x" << std::hex << patchaddr;
         *MessageBox(NULL, ss.str().c_str(), TEXT("info"), MB_OK);
			*/

        if (VirtualProtect(ppatchaddr, patchlen, PAGE_EXECUTE_READWRITE, &curProtection) == 0)
            MessageBox(NULL, TEXT("virtualProtect failed!"), TEXT("fail"), MB_OK | MB_ICONERROR);

		  for(int i=0; i<16; i++)
			  *(BYTE*)(patchaddr+i) = 0x90;
        *(BYTE*)(patchaddr+16) = 0xb8;
		  for(int i=17; i<21; i++)
			  *(BYTE*)(patchaddr+i) = 0x00;

        VirtualProtect(ppatchaddr, patchlen, curProtection, &temp);
        //FreeLibraryAndExitThread(hModule, 0);
    }
    
    return TRUE;
}



