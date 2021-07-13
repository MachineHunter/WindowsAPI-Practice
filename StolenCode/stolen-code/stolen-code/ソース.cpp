#include <windows.h>
#include <stdio.h>

typedef unsigned __int64 QWORD;
typedef BOOL(*BEEP)(DWORD dwFreq, DWORD dwDuration);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	// nop kernel32.dll Beep's first instructions
	HMODULE hkernel32 = GetModuleHandle("kernel32.dll");
	QWORD patch_addr = (QWORD)GetProcAddress(hkernel32, "Beep");

	DWORD curProtection, temp;
	int len = 13;

	VirtualProtect((void*)patch_addr, len, PAGE_EXECUTE_READWRITE, &curProtection);
	memset((void*)patch_addr, 0x90, len);
	VirtualProtect((void*)patch_addr, len, curProtection, &temp);


	// write stolen code to code cave
	TCHAR szMyPath[MAX_PATH];
	GetModuleFileName(NULL, szMyPath, _countof(szMyPath));
	QWORD base = (QWORD)GetModuleHandle((LPCSTR)szMyPath);
	QWORD stolen_addr = base + 0x7efd;
	int len2 = 25;

	char buf[256];
	snprintf(buf, 256, "code cave = %p", stolen_addr);
	OutputDebugString(buf);

	VirtualProtect((void*)stolen_addr, len2, PAGE_EXECUTE_READWRITE, &curProtection);
	memset((void*)stolen_addr, 0x90, len2);

	*(BYTE*)(stolen_addr + 0) = 0x48;
	*(BYTE*)(stolen_addr + 1) = 0x89;
	*(BYTE*)(stolen_addr + 2) = 0x5c;
	*(BYTE*)(stolen_addr + 3) = 0x24;
	*(BYTE*)(stolen_addr + 4) = 0x18;
	*(BYTE*)(stolen_addr + 5) = 0x57;
	*(BYTE*)(stolen_addr + 6) = 0x48;
	*(BYTE*)(stolen_addr + 7) = 0x81;
	*(BYTE*)(stolen_addr + 8) = 0xec;
	*(BYTE*)(stolen_addr + 9) = 0xf0;
	*(BYTE*)(stolen_addr + 10) = 0x03;
	*(BYTE*)(stolen_addr + 11) = 0x00;
	*(BYTE*)(stolen_addr + 12) = 0x00;

	*(BYTE*)(stolen_addr + 13) = 0x48;
	*(BYTE*)(stolen_addr + 14) = 0xb8;
	*(QWORD*)(stolen_addr + 15) = (QWORD)(patch_addr + len); // mov rax, <original addr of kernel32.dll beep>
	*(BYTE*)(stolen_addr + 23) = 0xff;
	*(BYTE*)(stolen_addr + 24) = 0xe0;                       // jmp rax

	VirtualProtect((void*)stolen_addr, len2, curProtection, &temp);


	// custom beep to first go to stolen code
	BEEP custom_beep = (BEEP)stolen_addr;

	// use beep
	while (1) {
		custom_beep(5000, 500);
		Sleep(3000);
	}
	return TRUE;
}