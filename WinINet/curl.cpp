// http://nienie.com/~masapico/api_InternetOpen.html
// http://nienie.com/~masapico/api_InternetOpenUrl.html

// �R���p�C�����ӁFg++ <source.c> -lwininet

#include <windows.h>
#include <wininet.h>
#include <iostream>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	HINTERNET hInternet;
	HINTERNET hFile;

	hInternet = InternetOpen("Agent", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
	if(hInternet==NULL) {
		MessageBox(NULL, "InternetOpen Failed", "error", MB_OK);
		return 1;
	}

	hFile = InternetOpenUrl(hInternet, lpCmdLine, NULL, 0, INTERNET_FLAG_RELOAD, 0);
	if(hFile==NULL) {
		MessageBox(NULL, "InternetOpenUrl Failed", "error", MB_OK);
		return 1;
	}

	while(1) {
		DWORD readsize = 1000;
		BOOL result;
		char buf[1000];

		result = InternetReadFile(hFile, buf, 1000, &readsize);

		if(result && (readsize==0)) break;

		buf[readsize] = '\0';
		std::cout << buf;
	}

	InternetCloseHandle(hFile);
	InternetCloseHandle(hInternet);

	return 0;
}

//INTERNET_FLAG_RELOAD	���[�J���̃L���b�V���𖳎����A��ɃT�[�o����f�[�^���擾����B
//INTERNET_FLAG_DONT_CACHE	���[�J���y�уQ�[�g�E�F�C�Ƀf�[�^���L���b�V�����Ȃ��B
//INTERNET_FLAG_RAW_DATA	���̃f�[�^��Ԃ�(FTP�̏ꍇWIN32_FIND_DATA�AGopher�̏ꍇGOPHER_FIND_DATA)�B���̃t���O���w�肳��Ă��Ȃ��ꍇ�A�f�B���N�g���̈ꗗ��HTML�t�H�[�}�b�g�ŕԋp����B(->)
//INTERNET_FLAG_SECURE	SSL��PCT���g�p����B(HTTP�̂�)
//INTERNET_FLAG_EXISTING_CONNECT	�\�Ȍ�������̃T�[�o�Ƃ̐ڑ����ė��p����B
