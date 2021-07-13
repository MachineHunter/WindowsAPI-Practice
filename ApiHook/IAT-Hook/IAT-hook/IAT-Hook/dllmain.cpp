#include "pch.h"
#include <windows.h>
#include <Dbghelp.h>
#include <sstream>
#pragma comment(lib, "Dbghelp")


typedef BOOL* (WINAPI* OriginalBeep)(DWORD dwFreq, DWORD dwDuration);
OriginalBeep originalBeep;


void WINAPI MyBeep(DWORD dwFreq, DWORD dwDuration) {
    MessageBox(NULL, TEXT("Hooked Beep!!!"), TEXT("success"), MB_OK | MB_ICONEXCLAMATION);
    originalBeep(dwFreq, dwDuration);
    return;
}


BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        TCHAR szMyPath[MAX_PATH];
        ULONG cbSize = 0;

        GetModuleFileName(NULL, szMyPath, _countof(szMyPath));
        HANDLE hModule = GetModuleHandle((LPCSTR)szMyPath);
        std::stringstream s;
        s << szMyPath << std::endl;
        MessageBox(NULL, s.str().c_str(), TEXT("target"), MB_OK);

        originalBeep = (OriginalBeep)GetProcAddress(GetModuleHandle("kernel32.dll"), "Beep");
        PIMAGE_IMPORT_DESCRIPTOR pImageImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hModule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &cbSize);

        for (; pImageImportDescriptor->Name; pImageImportDescriptor++) {
            LPCSTR pModuleName = (LPCSTR)((PBYTE)hModule + pImageImportDescriptor->Name);
            DWORD ModuleBase = (DWORD)GetModuleHandle(pModuleName);

            PIMAGE_THUNK_DATA pFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImageImportDescriptor->FirstThunk);
            PIMAGE_THUNK_DATA pOriginalFirstThunk = (PIMAGE_THUNK_DATA)((PBYTE)hModule + pImageImportDescriptor->OriginalFirstThunk);

            for (; pFirstThunk->u1.Function; pFirstThunk++, pOriginalFirstThunk++) {
                FARPROC pfnImportedFunc = (FARPROC)(pFirstThunk->u1.Function);
                PIMAGE_IMPORT_BY_NAME pImageImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hModule + pOriginalFirstThunk->u1.AddressOfData);

                if (pfnImportedFunc == (FARPROC)originalBeep) {
                    MEMORY_BASIC_INFORMATION mbi;
                    DWORD dwJunk = 0;

                    VirtualQuery(pFirstThunk, &mbi, sizeof(MEMORY_BASIC_INFORMATION));
                    if (!VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect)) {
                        MessageBox(NULL, TEXT("VirtualProtect Failed!"), TEXT("error"), MB_OK | MB_ICONERROR);
                        return FALSE;
                    }

                    pFirstThunk->u1.Function = (ULONGLONG)(DWORD_PTR)MyBeep;
                    if (VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &dwJunk))
                        break;
                }
            }
        }
    }

    return TRUE;
}
