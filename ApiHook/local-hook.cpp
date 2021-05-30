// http://bcb.client.jp/tips/005_setwindowshookex.html
// http://spacetimebubble.net/blog/2012/11/13/ローカルフック/

#include <windows.h>
#include <stdio.h>
#include <winuser.h>


HHOOK hmyhook;



LRESULT CALLBACK dohook(int nCode, WPARAM wParam, LPARAM lParam) {
	if(nCode<0)
		return CallNextHookEx(hmyhook, nCode, wParam, lParam);

	if(wParam==0x30)
		MessageBox(NULL, "0 key is pressed!", "success", MB_OK);

	MessageBox(NULL, "inside dohook", "log", MB_OK);

	return CallNextHookEx(hmyhook, nCode, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	hmyhook = SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)dohook, NULL, GetCurrentThreadId());

	if(hmyhook==NULL)
		return 1;

	getchar();

	if(UnhookWindowsHookEx(hmyhook)==0)
		MessageBox(NULL, "Failed to delete hook", "error", MB_OK);
	else
		MessageBox(NULL, "hook deleted", "success", MB_OK);
	
	return 0;
}
