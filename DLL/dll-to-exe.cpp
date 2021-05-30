#include <windows.h>

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	MessageBox(NULL, "init", "info", MB_OK);
	return TRUE;
}
