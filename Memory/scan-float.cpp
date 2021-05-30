// https://stackoverflow.com/questions/2330906/c-readprocessmemory-how-to-examine-the-memory-area-associated-with-a-process
// https://riosu.hateblo.jp/entry/2013/09/06/001208

#include <windows.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <iostream>


HANDLE get_process_hundle(TCHAR* target_exe_file) {
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if(hSnapshot == INVALID_HANDLE_VALUE) {
		printf("Error: hSnapshot is INVALID_HANDLE_VALUE\n");
		return INVALID_HANDLE_VALUE;
	}
	
	PROCESSENTRY32 pe;
	pe.dwSize = sizeof(PROCESSENTRY32);
	
	if(!Process32First(hSnapshot, &pe)) {
		CloseHandle(hSnapshot);
		printf("Error: couldn't get entry by Process32First\n");
		return INVALID_HANDLE_VALUE;
	}
	do {
		if(_tcscmp(pe.szExeFile, target_exe_file) == 0) {
			CloseHandle(hSnapshot);
			HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, pe.th32ProcessID);
			if(hProcess) {
				return hProcess;
			} else {
				return INVALID_HANDLE_VALUE;
			}
		}

	} while(Process32Next(hSnapshot, &pe));
	
	CloseHandle(hSnapshot);

	return INVALID_HANDLE_VALUE;
}



int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	HANDLE hProcess = get_process_hundle("test.exe");
	char *base = (char *)0;

	do {
		byte memory[4];
		
		if(ReadProcessMemory(hProcess, base, memory, 4, NULL) != 0) {
			//float value = BitConverter.ToSingle(memory, 0);
			float value = *reinterpret_cast<float*>(memory);
			std::cout << value << std::endl;
		}

		base += 4;
	} while(base!=0);

	return 0;
}
