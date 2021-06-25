#include <windows.h>
#include <stdio.h>
#include <dshow.h>
#include <iostream>
#pragma comment(lib, "strmiids.lib")

int Error(HRESULT hr) {
	printf("COM error (hr=%08x)\n", hr);
	return 1;
}

int main() {
	HRESULT hr;
	IMediaControl* pIFMediaControl = NULL;
	IMediaEvent* pIFMediaEvent     = NULL;
	BSTR bstr                      = NULL;
	long evCode                    = 0;

	hr = CoInitialize(NULL);
	if (FAILED(hr))
		Error(hr);

	DWORD dwClsContent = CLSCTX_INPROC_SERVER | CLSCTX_INPROC_HANDLER | CLSCTX_LOCAL_SERVER;
	hr = CoCreateInstance(CLSID_FilterGraph, NULL, dwClsContent, IID_IMediaControl, (LPVOID*)&pIFMediaControl);

	if (SUCCEEDED(hr))
		hr = pIFMediaControl->QueryInterface(IID_IMediaEvent, (LPVOID*)&pIFMediaEvent);

	if (SUCCEEDED(hr)) {
		bstr = SysAllocString(L"c:\\windows\\media\\Ring01.wav");
		if (bstr == NULL)
			hr = E_OUTOFMEMORY;
	}

	if (SUCCEEDED(hr)) {
		hr = pIFMediaControl->RenderFile(bstr);
		if (FAILED(hr))
			Error(hr);
	}

	if (SUCCEEDED(hr))
		hr = pIFMediaControl->Run();

	if (SUCCEEDED(hr))
		hr = pIFMediaEvent->WaitForCompletion(INFINITE, &evCode);

	if (SUCCEEDED(hr))
		pIFMediaControl->Release();

	if (SUCCEEDED(hr))
		pIFMediaEvent->Release();

	if (bstr != NULL)
		SysFreeString(bstr);

	if (FAILED(hr))
		Error(hr);

	CoUninitialize();
	return 0;
}
