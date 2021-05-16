// https://www.wabiapp.com/WabiSampleSource/windows/reg_query_value_ex.html

#include <windows.h>
#include <iostream>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpszCmdLine,
	int nCmdShow
) {
	HKEY hkey = NULL;
	DWORD result;
	result = RegOpenKeyEx(HKEY_LOCAL_MACHINE, (PCTSTR)"SOFTWARE\\Microsoft\\Internet Explorer", 0, KEY_QUERY_VALUE, &hkey);

	if(result != ERROR_SUCCESS) {
		MessageBox(NULL, "Failed to open registry", "error", MB_OK | MB_ICONHAND);
		return 1;
	}

	DWORD datatype = 0;
	TCHAR readbuf[MAX_PATH];
	DWORD readsize = sizeof(readbuf);
	result = RegQueryValueEx(hkey, (PCTSTR)"svcVersion", 0, &datatype, (LPBYTE)readbuf, &readsize);

	if(result != ERROR_SUCCESS) {
		MessageBox(NULL, "Failed to read registry", "error", MB_OK | MB_ICONHAND);
		return 1;
	}

	std::cout << readbuf << std::endl;
	switch(datatype) {
		case REG_SZ: std::cout << "REG_SZ" << std::endl; break;
	}

	RegCloseKey(hkey);

	return 0;
}

