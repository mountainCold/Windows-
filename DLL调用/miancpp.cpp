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
// 	// 2. 获取函数并调用，指定从哪一个模块获取哪一个函数
// 	FUNC func = (FUNC)GetProcAddress(hModule, "funTest1");
// 	if (func != nullptr) func();
// 	// 3. 卸载模块
// 	FreeLibrary(hModule);
}