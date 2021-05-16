// https://s-kita.hatenablog.com/entry/20130502/1367458848

#include <windows.h>
#include <strsafe.h>
#include <process.h>
#include <stdio.h>
#include <errhandlingapi.h>
#include <iostream>

SERVICE_STATUS ss;
SERVICE_STATUS_HANDLE hss;


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



DWORD WINAPI HandlerEx(DWORD dwControl, DWORD dwEventType, PVOID pvEventData, PVOID pvContext) {
	switch(dwControl) {
		case SERVICE_CONTROL_STOP:
			ss.dwCurrentState = SERVICE_STOPPED;
			break;
		case SERVICE_CONTROL_SHUTDOWN:
			ss.dwCurrentState = SERVICE_STOPPED;
			break;
		case SERVICE_CONTROL_PAUSE:
			ss.dwCurrentState = SERVICE_PAUSED;
			break;
		case SERVICE_CONTROL_CONTINUE:
			ss.dwCurrentState = SERVICE_RUNNING;
			break;
		default:
			break;
	}

	MessageBox(NULL, "inside HandlerEx", "info", MB_OK);
	SetServiceStatus(hss, &ss);
	return ERROR_CALL_NOT_IMPLEMENTED;
}




unsigned int WINAPI ServiceThread(LPVOID arg) {
	char filename[MAX_PATH];
	SYSTEMTIME localtime;

	MessageBox(NULL, "inside ServiceThread", "info", MB_OK);
	while(1) {
		FILE *f = fopen("aabbcc.txt", "a");
		if(f!=NULL) {
			GetLocalTime(&localtime);
			fprintf(f, "%02d:%02d:%02d\n", localtime.wHour, localtime.wMinute, localtime.wSecond);
			fclose(f);
		}
		Sleep(1000);
	}

	return 0;
}




void WINAPI ServiceEntry(DWORD dwArgs, LPTSTR *pszArgv) {
	unsigned int threadid;
	HANDLE hThread;

	hThread = (HANDLE)_beginthreadex(NULL, 0, ServiceThread, NULL, 0, &threadid);

	hss = RegisterServiceCtrlHandlerEx("ApiPracticeService", HandlerEx, NULL);

	memset(&ss, 0, sizeof(ss));
	ss.dwServiceType             = SERVICE_WIN32_OWN_PROCESS;
	ss.dwCurrentState            = SERVICE_RUNNING;
	ss.dwControlsAccepted        = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_PAUSE_CONTINUE;
	ss.dwWin32ExitCode           = NO_ERROR;
	ss.dwServiceSpecificExitCode = 0;
	ss.dwCheckPoint              = 0;
	ss.dwWaitHint                = 2000;
	SetServiceStatus(hss, &ss);

	MessageBox(NULL, "Service Entry done", "info", MB_OK);
}




int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	/*
	 *if(installservice())
	 *   MessageBox(NULL, "service installation complete!", "success", MB_OK);
	 *else
	 *   MessageBox(NULL, "service installation failed", "error", MB_OK); // ä«óùé“å†å¿Ç∂Ç·Ç»Ç¢Ç∆FailedÇ…Ç»ÇÈ
	 */

	SERVICE_TABLE_ENTRY ServiceTableEntry[] = { {"ApiPracticeService",ServiceEntry}, {NULL,NULL} };

	if(StartServiceCtrlDispatcher(ServiceTableEntry)==0)
		std::cout << "error code: " << GetLastError() << std::endl;

	return 0;
}

