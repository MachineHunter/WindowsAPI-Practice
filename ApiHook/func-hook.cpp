#include <windows.h>


bool Hook(void *target, void *myfunc, int len) {
	if(len<5)
		return false;

	DWORD curProtection;
	VirtualProtect(target, len, PAGE_EXECUTE_READWRITE, &curProtection);

	memset(target, 0x90, len);

	DWORD relativeAddress = ((DWORD)myfunc - (DWORD)target) - len;

	*(byte*)target = 0xe8;     // jmp = E9
	*(DWORD*)((DWORD)target+1) = relativeAddress;

	DWORD temp;
	VirtualProtect(target, len, curProtection, &temp);
	
	return true;
}


DWORD jmpBackAddy;
void __declspec(naked) myfunc() {
	__asm {
		jmp [jmpBackAddy]
	}
}


DWORD WINAPI dothread(LPVOID param) {
	int hookLength = 5;
	DWORD hookAddress = 0x004015b8;
	jmpBackAddy = hookAddress + hookLength;

	Hook((void*)hookAddress, myfunc, hookLength);

	FreeLibraryAndExitThread((HMODULE)param, 0);

	return 0;
}


BOOL WINAPI DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserved) {
	switch(dwReason) {
		case DLL_PROCESS_ATTACH:
			CreateThread(0, 0, dothread, hModule, 0, 0);
			break;
	}

	return TRUE;
}
