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

    char buf[256];
    snprintf(buf, 256, "myfunc=%p", myfunc);
    OutputDebugString(buf);

    *(BYTE*)target = 0x48;
    *(BYTE*)((DWORD)target + 1) = 0xb8;
    *(QWORD*)((QWORD)target + 2) = (QWORD)myfunc; // mov rax, <myfuncAddr>
    *(BYTE*)((DWORD)target + 10) = 0xff;
    *(BYTE*)((DWORD)target + 11) = 0xd0;          // call rax


    DWORD temp;
    VirtualProtect(target, len, curProtection, &temp);

    return true;
}



DWORD WINAPI dothread(LPVOID param) {
    int hookLength = 19;
    DWORD hookAddr = 0x00401564;

    if (Hook((void*)hookAddr, myfunc, hookLength))
        MessageBox(NULL, TEXT("hooked"), TEXT("info"), MB_OK);

    while (1) {
        if (GetAsyncKeyState(VK_ESCAPE))
            break;
        Sleep(50);
    }

    FreeLibraryAndExitThread((HMODULE)param, 0);
    return 0;
}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, dothread, hModule, 0, 0);
    return TRUE;
}



