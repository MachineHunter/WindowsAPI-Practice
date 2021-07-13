#include <Windows.h>
#include <stdio.h>

int main() {
	HANDLE rslt;
	LPCSTR fnameList[] = { "\\\\.\\Global\\ProcmonDebugLogger", }; // ProcmonŒŸ’m—p

	for (int cnt = 0; cnt < sizeof(fnameList) / sizeof(LPSTR); cnt++) {
		if (*(UCHAR*)CreateFileA == 0xcc) {
			MessageBox(NULL, TEXT("INT3 is found"), TEXT("info"), MB_OK);
			break;
		}

		rslt = CreateFileA(fnameList[cnt], 
			GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, 
			NULL, 
			OPEN_EXISTING, 
			FILE_ATTRIBUTE_NORMAL, 
			0);
		if (rslt == INVALID_HANDLE_VALUE)
			MessageBox(NULL, TEXT("not found"), TEXT("info"), MB_OK);
		else {
			MessageBox(NULL, TEXT("found"), TEXT("info"), MB_OK);
			CloseHandle(rslt);
		}
	}

	return 0;
}