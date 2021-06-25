#include <windows.h>
#include <stdio.h>
#include <Dbghelp.h>
#include <sstream>
#pragma comment(lib, "Dbghelp")



typedef void* (WINAPI* OriginalSleep)(DWORD);
OriginalSleep originalSleep;


void WINAPI MySleepFunc(DWORD dwMilliseconds) {
    MessageBox(NULL, TEXT("Hooked Sleep!!!"), TEXT("success"), MB_OK | MB_ICONEXCLAMATION);
    originalSleep(dwMilliseconds);
    return;
}



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

    HMODULE hModule;
    TCHAR szMyPath[MAX_PATH];
    ULONG cbSize = 0;
    PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor = NULL;
    PIMAGE_THUNK_DATA pFirstThunk = NULL;
    PIMAGE_THUNK_DATA pOriginalFirstThunk = NULL;

    GetModuleFileName(NULL, szMyPath, _countof(szMyPath));
    std::stringstream s;
    s << szMyPath << std::endl;
    MessageBox(NULL, s.str().c_str(), TEXT("hooking target"), MB_OK);

    hModule = GetModuleHandle((LPCSTR)szMyPath);
    pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hModule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &cbSize);

    originalSleep = (OriginalSleep)GetProcAddress(GetModuleHandle("kernel32.dll"), "Sleep");
    std::stringstream ss;
    ss << "Sleep : 0x" << std::hex << (FARPROC)originalSleep << std::endl;
    MessageBox(NULL, ss.str().c_str(), TEXT("IAT info"), MB_OK);

    for (; pImageImportDescriptor->Name; pImageImportDescriptor++) {

        LPCSTR pModuleName = (LPCSTR)((PBYTE)hModule + pImageImportDescriptor->Name);
        DWORD ModuleBase = (DWORD)GetModuleHandle(pModuleName);

        pFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImageImportDescriptor->FirstThunk);
        pOriginalFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImageImportDescriptor->OriginalFirstThunk);

        for (; pFirstThunk->u1.Function; pFirstThunk++, pOriginalFirstThunk++) {

            FARPROC pfnImportedFunc = (FARPROC)(pFirstThunk->u1.Function);
            PIMAGE_IMPORT_BY_NAME pImageImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hModule + pOriginalFirstThunk->u1.AddressOfData);

            if (pfnImportedFunc == (FARPROC)originalSleep) {

                MEMORY_BASIC_INFORMATION mbi;
                DWORD dwJunk = 0;

                VirtualQuery(pFirstThunk, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
                if (!VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect)) {
                    MessageBox(NULL, TEXT("VirtualProtect Failed!"), TEXT("error"), MB_OK | MB_ICONERROR);
                    return FALSE;
                }

                pFirstThunk->u1.Function = (ULONGLONG)(DWORD_PTR)MySleepFunc;
                if (VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &dwJunk))
                    break;
            }

        }
    }

    MessageBox(NULL, TEXT("start sleep"), TEXT("info"), MB_OK);
    Sleep(3000);
    MessageBox(NULL, TEXT("end sleep"), TEXT("info"), MB_OK);

    return TRUE;
}

// https://guidedhacking.com/threads/how-to-hook-import-address-table-iat-hooking.13555/
// 注意として、originalSleep = MySleepFuncにすればいいのではと思うが、GetProcAddressはDLLのエクスポート関数のアドレスを
// 調べる感じなので、これを書き換えてもIATを書き換えてることにはならないので、意味がない
