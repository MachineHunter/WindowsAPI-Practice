#include <Windows.h>
#include <sstream>

typedef unsigned __int64 QWORD;

extern "C" __declspec(dllexport) void __cdecl ExportFunc() {
	MessageBox(NULL, TEXT("dummy export"), TEXT("info"), MB_OK);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        int patchlen      = 21;
		  int hwbplen       = 33;
        QWORD offset      = 0x9d130;
		  QWORD hwbp_offset = 0x7DED0;
        DWORD curProtection;
        DWORD hwbp_curProtection;
        DWORD temp;

		  QWORD ntdll      = (QWORD)GetModuleHandle("ntdll.dll");
		  QWORD kernelbase = (QWORD)GetModuleHandle("kernelbase.dll");
		  QWORD patchaddr  = ntdll + offset;
		  void *ppatchaddr = (void*)patchaddr;
		  QWORD hwbpaddr   = kernelbase + hwbp_offset;
		  void *phwbpaddr = (void*)hwbpaddr;

        if (VirtualProtect(ppatchaddr, patchlen, PAGE_EXECUTE_READWRITE, &curProtection) == 0)
            MessageBox(NULL, TEXT("virtualProtect failed!"), TEXT("fail"), MB_OK | MB_ICONERROR);
        if (VirtualProtect(phwbpaddr, hwbplen, PAGE_EXECUTE_READWRITE, &hwbp_curProtection) == 0)
            MessageBox(NULL, TEXT("virtualProtect failed!"), TEXT("fail"), MB_OK | MB_ICONERROR);

		  // patch ntqueryinformationprocess
		  for(int i=0; i<16; i++)
			  *(BYTE*)(patchaddr+i) = 0x90;
        *(BYTE*)(patchaddr+16) = 0xb8;
		  for(int i=17; i<21; i++)
			  *(BYTE*)(patchaddr+i) = 0x00;

		  // enable hwbp
		  for(int i=0; i<28; i++)
			  *(BYTE*)(hwbpaddr+i) = 0x90;
        *(BYTE*)(hwbpaddr+28) = 0xb8;
		  for(int i=29; i<33; i++)
			  *(BYTE*)(hwbpaddr+i) = 0x00;

        VirtualProtect(ppatchaddr, patchlen, curProtection, &temp);
        VirtualProtect(phwbpaddr, hwbplen, hwbp_curProtection, &temp);
    }
    
    return TRUE;
}



