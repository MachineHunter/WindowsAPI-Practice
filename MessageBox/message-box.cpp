// http://kaitei.net/winapi/getting-started/
// https://docs.microsoft.com/ja-jp/cpp/windows/walkthrough-creating-windows-desktop-applications-cpp?view=msvc-160

#include <windows.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	MessageBox(NULL, "thisismessage", TEXT("Test"), MB_YESNO | MB_ICONEXCLAMATION);
	return 0;
}

// ボタンの種類
// #define MB_OK                       0x00000000L  // OK
// #define MB_OKCANCEL                 0x00000001L  // OK, キャンセル
// #define MB_ABORTRETRYIGNORE         0x00000002L  // 中止，再試行，無視
// #define MB_YESNOCANCEL              0x00000003L  // はい，いいえ，キャンセル
// #define MB_YESNO                    0x00000004L  // はい，いいえ
// #define MB_RETRYCANCEL              0x00000005L  // 再試行，キャンセル
// #define MB_CANCELTRYCONTINUE        0x00000006L  // キャンセル，再実行，継続
//
// // アイコンの種類
// #define MB_ICONHAND                 0x00000010L  // エラー
// #define MB_ICONQUESTION             0x00000020L  // 問合せ
// #define MB_ICONEXCLAMATION          0x00000030L  // 警告
// #define MB_ICONASTERISK             0x00000040L  // 情報
