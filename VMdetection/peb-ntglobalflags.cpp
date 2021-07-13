#include <windows.h>
#include <stdio.h>

__declspec(naked) DWORD getNtGlobalFlag() {
	__asm {
		mov eax, fs:[0x18]
		mov eax, [eax + 0x30]
		mov eax, [eax + 0x68]
		ret
	}
}

int main() {
	char buf[100];
	snprintf(buf, 100, "0x%08x", getNtGlobalFlag());
	OutputDebugStringA((LPCSTR)buf);
	return 0;
}
