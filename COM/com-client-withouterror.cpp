#include <windows.h>
#include <stdio.h>
#include <dshow.h>
#include <iostream>
#pragma comment(lib, "strmiids.lib")

int main() {
	IMediaControl* pIFMediaControl = NULL;
	IMediaEvent* pIFMediaEvent     = NULL;
	BSTR bstr                      = NULL;
	long evCode                    = 0;

	CoInitialize(NULL);
	DWORD dwClsContent = CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER;
	CoCreateInstance(CLSID_FilterGraph, NULL, dwClsContent, IID_IMediaControl, (LPVOID*)&pIFMediaControl);
	pIFMediaControl->QueryInterface(IID_IMediaEvent, (LPVOID*)&pIFMediaEvent);
	bstr = SysAllocString(L"c:\\windows\\media\\Ring01.wav");
	pIFMediaControl->RenderFile(bstr);

	pIFMediaControl->Run();
	pIFMediaEvent->WaitForCompletion(INFINITE, &evCode);
	pIFMediaControl->Release();
	pIFMediaEvent->Release();
	SysFreeString(bstr);
	CoUninitialize();
	return 0;
}

