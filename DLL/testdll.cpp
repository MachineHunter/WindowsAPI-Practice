// https://digirakuda.org/blog/2018/06/15/post-273/
// https://qiita.com/tera1707/items/81042abaa62dc97e26ae

#include <windows.h>
#include "testdll.h"

void __cdecl TestFunc() {
	MessageBox(NULL, "TestFunc called", "info", MB_OK);
}
