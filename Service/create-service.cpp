// https://s-kita.hatenablog.com/entry/20130502/1367458848

#include <windows.h>
#include <strsafe.h>


BOOL installservice() {
	SC_HANDLE hSCM = NULL;
	SC_HANDLE hService = NULL;
	TCHAR binarypath[MAX_PATH];
	SERVICE_DESCRIPTION sd;
	BOOL ret = FALSE;

	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if(hSCM==NULL)
		goto EXIT;

	GetModuleFileName(NULL, binarypath, sizeof(binarypath)/sizeof(binarypath[0]));

	hService = CreateService(hSCM,
			"ApiPracticeService",
			"PracServiceDisplayName",
			SERVICE_CHANGE_CONFIG,
			SERVICE_WIN32_OWN_PROCESS,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_IGNORE,
			binarypath,
			NULL,
			NULL,
			NULL,
			NULL,
			NULL
	);

	if(hService==NULL)
		goto EXIT;

	sd.lpDescription = "Sample service application for practice";
	ChangeServiceConfig2(hService, SERVICE_CONFIG_DESCRIPTION, &sd);

	ret = TRUE;

EXIT:
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);

	return ret;
}




int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	if(installservice())
		MessageBox(NULL, "service installation complete!", "success", MB_OK);
	else
		MessageBox(NULL, "service installation failed", "error", MB_OK); // ä«óùé“å†å¿Ç∂Ç·Ç»Ç¢Ç∆FailedÇ…Ç»ÇÈ

	return 0;
}
