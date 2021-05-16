// http://nienie.com/~masapico/api_InternetOpen.html
// http://nienie.com/~masapico/api_InternetOpenUrl.html

// コンパイル注意：g++ <source.c> -lwininet

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

//INTERNET_FLAG_RELOAD	ローカルのキャッシュを無視し、常にサーバからデータを取得する。
//INTERNET_FLAG_DONT_CACHE	ローカル及びゲートウェイにデータをキャッシュしない。
//INTERNET_FLAG_RAW_DATA	生のデータを返す(FTPの場合WIN32_FIND_DATA、Gopherの場合GOPHER_FIND_DATA)。このフラグが指定されていない場合、ディレクトリの一覧をHTMLフォーマットで返却する。(->)
//INTERNET_FLAG_SECURE	SSLやPCTを使用する。(HTTPのみ)
//INTERNET_FLAG_EXISTING_CONNECT	可能な限り既存のサーバとの接続を再利用する。
