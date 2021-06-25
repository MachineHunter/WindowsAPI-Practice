// https://www.youtube.com/watch?v=e4HZgx3A-wk

#include "pch.h"
#include <Windows.h>
#include <sstream>


bool Hook(void* target, void* myfunc, int len) {
    if (len < 5)
        return false;
    
    DWORD curProtection;
    VirtualProtect(target, len, PAGE_EXECUTE_READWRITE, &curProtection);
    memset(target, 0x90, len);

    DWORD relativeAddr = ((DWORD)myfunc - (DWORD)target) - 5;
    // std::stringstream ss;
    // ss << "relativeAddr:" << std::hex << relativeAddr << std::endl;
    // MessageBox(NULL, (LPCSTR)ss.str().c_str(), TEXT("info"), MB_OK);
    *(BYTE*)target = 0xe8;
    *(DWORD*)((DWORD)target + 1) = relativeAddr;

    DWORD temp;
    VirtualProtect(target, len, curProtection, &temp);

    return true;
}




DWORD jmpBackAddy;
extern "C" __declspec(dllexport) void __cdecl myfunc() {
    MessageBox(NULL, TEXT("detoured!!"), TEXT("success"), MB_OK | MB_ICONEXCLAMATION);
    void (*retAddr)(void) = (void (*)())jmpBackAddy;
    retAddr();
}




DWORD WINAPI dothread(LPVOID param) {
    int hookLength = 5;
    DWORD hookAddr = 0x00401564;
    jmpBackAddy = hookAddr + hookLength;

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




BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
        CreateThread(0, 0, dothread, hModule, 0, 0);
    return TRUE;
}


