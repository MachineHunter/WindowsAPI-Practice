// https://digirakuda.org/blog/2018/06/15/post-273/
// https://qiita.com/tera1707/items/81042abaa62dc97e26ae

#include <windows.h>
#include "testdll.h"


void __cdecl TestFunc() {
	MessageBox(NULL, "TestFunc called", "info", MB_OK);
}


BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {

	MessageBox(NULL, "init", "info", MB_OK);

	/*
	 *switch(fdwReason) {
	 *   case DLL_PROCESS_ATTACH:
	 *      MessageBox(NULL, "DllMain called", "info", MB_OK);
	 *      break;
	 *   case DLL_THREAD_ATTACH:
	 *   case DLL_THREAD_DETACH:
	 *   case DLL_PROCESS_DETACH:
	 *      break;
	 *}
	 */

	return TRUE;
}
