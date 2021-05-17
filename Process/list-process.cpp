// https://www.keicode.com/windows/win07.php

#include <windows.h>
#include <iostream>
#include <tlhelp32.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	HANDLE procsnap;
	PROCESSENTRY32 pe32;

	procsnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(procsnap==INVALID_HANDLE_VALUE) {
		MessageBox(NULL, TEXT("Failed to get snapshot"), "error", MB_YESNO);
		return 1;
	}

	Process32First(procsnap, &pe32);

	std::cout << "PID  Name  NumberOfThreads" << std::endl;
	while(1) {
		std::cout << pe32.th32ProcessID <<" "<< pe32.szExeFile <<" "<< pe32.cntThreads << std::endl;
		if(!Process32Next(procsnap, &pe32)) break;
	}

	CloseHandle(procsnap);

	return 0;
}
