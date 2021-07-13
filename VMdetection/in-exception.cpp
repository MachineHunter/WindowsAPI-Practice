#include <windows.h>
#include <stdio.h>

int checkVMware() {
	__try {
		__asm {
			push edx
			push ecx
			push ebx
			mov eax, 'VMXh'
			mov ebx, 0
			mov ecx, 10
			mov edx, 'VX'
			in eax, dx
			pop ebx
			pop ecx
			pop edx
		}
	}
	__except (EXCEPTION_EXECUTE_HANDLER) {
		return 0;
	}
	return 1;
}

int main() {
	if (checkVMware()) printf("On VMware\n");
	else printf("On Real Machine\n");
	return 0;
}
