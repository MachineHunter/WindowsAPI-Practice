// https://www.youtube.com/watch?v=e4HZgx3A-wk

#include "pch.h"
#include <Windows.h>
#include <sstream>

typedef unsigned __int64 QWORD;


DWORD jmpBackAddy;
void __stdcall myfunc() {
    MessageBox(NULL, TEXT("detoured!!"), TEXT("success"), MB_OK | MB_ICONEXCLAMATION);
    void (*retAddr)(void) = (void (*)())jmpBackAddy;
    retAddr();
}



bool Hook(void* target, void* myfunc, int len) {
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

    // スタック整頓などの復旧作業 サイズ=13
    *(BYTE*)((DWORD)target + 12)  = 0x48;
    *(BYTE*)((DWORD)target + 13)  = 0x8d;
    *(BYTE*)((DWORD)target + 14)  = 0xa5;
    *(DWORD*)((DWORD)target + 15) = (DWORD)0xe8;  // lea rsp,qword ptr ss:[rbp+8]
    *(BYTE*)((DWORD)target + 19) = 0x5f;          // pop rdi (myfunc呼び出す時に格納したリターンアドレスを消去)
    *(BYTE*)((DWORD)target + 20) = 0x5f;          // pop rdi (myfuncで最後retAddr()呼び出す時のリターンアドレス消去)
    *(BYTE*)((DWORD)target + 21) = 0x5f;          // pop rdi
    *(BYTE*)((DWORD)target + 22) = 0x5d;          // pop rdp
    *(BYTE*)((DWORD)target + 23) = 0xeb;          
    *(BYTE*)((DWORD)target + 24) = 0xe4;          // jmp sample.40155d




    DWORD temp;
    VirtualProtect(target, len, curProtection, &temp);

    return true;
}



DWORD WINAPI dothread(LPVOID param) {
    int hookLength = 24;
    DWORD hookAddr = 0x00401564;
    jmpBackAddy = hookAddr + hookLength - 13;

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



