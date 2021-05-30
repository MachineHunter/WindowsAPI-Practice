// https://s-kita.hatenablog.com/entry/20120727/1343397362

#include <windows.h>
#include <dbghelp.h>
#include <stdlib.h>
#include <string>
#include <iostream>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
) {
	// �C���|�[�g�Z�N�V������winnt.h��IMAGE_IMPORT_DESCRIPTOR�\���̂ŕ\������Ă�
	// IMAGE_IMPORT_DESCRIPTOR�̂R�̃����o��
	// 	- OriginalFirstThunk�F�C���|�[�g���b�N�A�b�v�e�[�u��(ILT)��RVA�ŁAwinnt.h�ł�IMAGE_THUNK_DATA�\����
	//  	- Name�F�C���|�[�g���Ă���DLL��RVA
	// 	- FirstThunk�FIAT��RVA

	PIMAGE_IMPORT_DESCRIPTOR pImportDesc;
	HMODULE hmymodule;
	TCHAR szMyPath[MAX_PATH];
	std::string s;
	ULONG ulSize;

	GetModuleFileName(NULL, szMyPath, _countof(szMyPath));
	hmymodule   = GetModuleHandleW((LPCWSTR)szMyPath);
	pImportDesc = (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToData(hmymodule, TRUE, IMAGE_DIRECTORY_ENTRY_IMPORT, &ulSize);

	while(pImportDesc->OriginalFirstThunk) {
		PSTR pszDllName = (PSTR)((PBYTE)hmymodule + pImportDesc->Name);
		s += pszDllName;
		s += '\n';

		PIMAGE_THUNK_DATA pThunkData = (PIMAGE_THUNK_DATA)((PBYTE)hmymodule + pImportDesc->OriginalFirstThunk);

		while(pThunkData->u1.AddressOfData) {
			if(IMAGE_SNAP_BY_ORDINAL(pThunkData->u1.Ordinal)) continue;
			PIMAGE_IMPORT_BY_NAME pImageImportByName = (PIMAGE_IMPORT_BY_NAME)((PBYTE)hmymodule + pThunkData->u1.AddressOfData);

			PSTR pszFuncName = (PSTR)&pImageImportByName->Name[0];
			s += pszFuncName;
			s += ",";
			pThunkData++;
		}

		s += "\n\n\n";
		pImportDesc++;
	}

	std::cout << s << std::endl;
	return 0;
}
