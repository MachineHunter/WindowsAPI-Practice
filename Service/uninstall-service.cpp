// https://s-kita.hatenablog.com/entry/20130502/1367458848

#include <windows.h>
#include <strsafe.h>


BOOL UninstallService(LPTSTR lpszServiceName) {
	SC_HANDLE hSCM = NULL;
	SC_HANDLE hService = NULL;

	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	if(hSCM==NULL) {
		MessageBox(NULL, TEXT("SCM�f�[�^�x�[�X�̃I�[�v���Ɏ��s���܂����B"), NULL, MB_ICONWARNING);
		return FALSE;
	}

	hService = OpenService(hSCM, lpszServiceName, DELETE);

	if(hService==NULL) {
		MessageBox(NULL, TEXT("�T�[�r�X�̃I�[�v���Ɏ��s���܂����B"), NULL, MB_ICONWARNING);
		CloseServiceHandle(hSCM);
		return FALSE;
	}

	DeleteService(hService);

	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);

	return TRUE;
}



int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	int id = MessageBox(NULL, "uninstall ApiPracticeService?", "confirmation", MB_YESNOCANCEL);
	if(id==IDYES) {
		if(UninstallService("ApiPracticeService"))
			MessageBox(NULL, TEXT("�A���C���X�g�[�����I�����܂����B"), TEXT("OK"), MB_OK);
		else
			MessageBox(NULL, "service uninstallation failed", "error", MB_OK); // �Ǘ��Ҍ�������Ȃ���Failed�ɂȂ�
	}

	return 0;
}
