#include <windows.h>
#include <iostream>

using namespace std;


int add(int x, int y) {
	int sum = x + y;
	return sum;
}

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {

	while(1) {
		if(GetAsyncKeyState(VK_ESCAPE))
			break;
		int a = 3;
		int b = 4;
		cout << add(a,b) << endl;
		Sleep(1000);
	}

	return 0;
}
