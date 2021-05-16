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

// �{�^���̎��
// #define MB_OK                       0x00000000L  // OK
// #define MB_OKCANCEL                 0x00000001L  // OK, �L�����Z��
// #define MB_ABORTRETRYIGNORE         0x00000002L  // ���~�C�Ď��s�C����
// #define MB_YESNOCANCEL              0x00000003L  // �͂��C�������C�L�����Z��
// #define MB_YESNO                    0x00000004L  // �͂��C������
// #define MB_RETRYCANCEL              0x00000005L  // �Ď��s�C�L�����Z��
// #define MB_CANCELTRYCONTINUE        0x00000006L  // �L�����Z���C�Ď��s�C�p��
//
// // �A�C�R���̎��
// #define MB_ICONHAND                 0x00000010L  // �G���[
// #define MB_ICONQUESTION             0x00000020L  // �⍇��
// #define MB_ICONEXCLAMATION          0x00000030L  // �x��
// #define MB_ICONASTERISK             0x00000040L  // ���
