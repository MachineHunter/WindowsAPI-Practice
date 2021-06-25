// https://www.youtube.com/watch?v=e4HZgx3A-wk

#include "pch.h"
#include <Windows.h>
#include <sstream>

typedef unsigned __int64 QWORD;


void __stdcall myfunc() {
    MessageBox(NULL, TEXT("detoured!!"), TEXT("success"), MB_OK | MB_ICONEXCLAMATION);
    return;
}



bool Hook(void* target, void* myfunc, int len) {
    if (len < 12)
        return false;

    DWORD curProtection;
    VirtualProtect(target, len, PAGE_EXECUTE_READWRITE, &curProtection);
    memset(target, 0x90, len);

    //char buf[256];
    //snprintf(buf, 256, "myfunc=%p", myfunc);
    //OutputDebugString(buf);

    *(BYTE*)target = 0x48;
    *(BYTE*)((QWORD)target + 1) = 0xb8;
    *(QWORD*)((QWORD)target + 2) = (QWORD)myfunc; // mov rax, <myfuncAddr>
    *(BYTE*)((QWORD)target + 10) = 0xff;
    *(BYTE*)((QWORD)target + 11) = 0xd0;          // call rax


    DWORD temp;
    VirtualProtect(target, len, curProtection, &temp);

    return true;
}



BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        int hookLength = 14;
        QWORD hookAddr = 0x00007FFF548F1150;

        MessageBox(NULL, TEXT("dll attached"), TEXT("info"), MB_OK);

        if (Hook((void*)hookAddr, myfunc, hookLength))
            MessageBox(NULL, TEXT("hooked"), TEXT("info"), MB_OK);

        MessageBox(NULL, TEXT("dll attachssssssed"), TEXT("info"), MB_OK);

        // エントリーポイント復元 -------------------------------
        QWORD entryaddr = 0x7ff6b4fc1262;
        void* pentry = (void*)entryaddr;
        DWORD curProtection;
        DWORD temp;

        MessageBox(NULL, TEXT("start restoring entrypoint 2byte"), TEXT("info"), MB_OK);
        if (VirtualProtect(pentry, 2, PAGE_EXECUTE_READWRITE, &curProtection) == 0)
            MessageBox(NULL, TEXT("virtualProtect failed!"), TEXT("fail"), MB_OK | MB_ICONERROR);
        *(BYTE*)((QWORD)pentry) = 0xe9;        // eb => e9
        *(BYTE*)((QWORD)pentry + 1) = 0xc9;    // fe => c9
        VirtualProtect(pentry, 2, curProtection, &temp);
        // -------------------------------------------------------

        FreeLibraryAndExitThread(hModule, 0);
    }
    
    return TRUE;
}


