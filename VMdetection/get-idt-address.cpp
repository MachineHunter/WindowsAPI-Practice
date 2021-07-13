#include <windows.h>
#include <stdio.h>

DWORD getIdtAddr() {
	UCHAR idtr[6];
	__asm sidt idtr;
	return *(DWORD*)&idtr[2];
}

int main() {
	printf("0x%08X\n", getIdtAddr());
	return 0;
}
