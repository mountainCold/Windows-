#include <windows.h>
/*#include "../win32Dll/Dll.h"*/
/*#include "../win32Dll/Dll.cpp"*/
#include "header.h"
#pragma comment(lib,"../Debug/win32Dll.lib")
typedef void (*FUNC)();
int main()
{
	/*funTest1();*/
	funTest2();
// 	HMODULE hModule = LoadLibraryA("../Debug/win32Dll.dll");
// 	// 2. ��ȡ���������ã�ָ������һ��ģ���ȡ��һ������
// 	FUNC func = (FUNC)GetProcAddress(hModule, "funTest1");
// 	if (func != nullptr) func();
// 	// 3. ж��ģ��
// 	FreeLibrary(hModule);
}