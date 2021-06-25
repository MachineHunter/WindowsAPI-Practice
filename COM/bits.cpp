#include <windows.h>
#include <stdio.h>
#include <Bits.h>
#pragma comment(lib, "bits")

int Error(HRESULT hr) {
	printf("COM error (hr=%08x)\n", hr);
	return 1;
}

int main() {
	::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);

	IBackgroundCopyManager* mgr;
	HRESULT hr = ::CoCreateInstance(CLSID_BackgroundCopyManager, nullptr, CLSCTX_ALL, IID_IBackgroundCopyManager, reinterpret_cast<void**>(&mgr));

	if (FAILED(hr))
		return Error(hr);

	hr = ::CoCreateInstance(__uuidof(BackgroundCopyManager), nullptr, CLSCTX_ALL, __uuidof(IBackgroundCopyManager), reinterpret_cast<void**>(&mgr));

	GUID jobId;
	IBackgroundCopyJob* pJob;
	hr = mgr->CreateJob(L"My job", BG_JOB_TYPE_DOWNLOAD, &jobId, &pJob);

	if (FAILED(hr))
		return Error(hr);

	mgr->Release();

	hr = pJob->AddFile(L"http://www.indetail.co.jp/wp-content/uploads/2017/01/1.png", L"c:\\Users\\kazu3\\Desktop\\parrot.png");

	if (FAILED(hr))
		return Error(hr);

	hr = pJob->Resume();

	if (SUCCEEDED(hr)) {
		printf("Downloading ...");
		BG_JOB_STATE state;
		for (;;) {
			pJob->GetState(&state);
			if (state == BG_JOB_STATE_ERROR || state == BG_JOB_STATE_TRANSFERRED)
				break;
			printf(".");
			Sleep(300);
		}

		if (state == BG_JOB_STATE_ERROR)
			printf("\nError in transfer!\n");
		else {
			pJob->Complete();
			printf("\nTransfer successfull!\n");
		}
	}


	pJob->Release();

	::CoUninitialize();

	return 0;
}
