#include<stdio.h>
#include "Dll.h"
BOOL APIENTRY DllMain(HMODULE hModule,			// 模块的句柄
	DWORD  ul_reason_for_call,	// 程序开始和关闭，线程开始和结束
	LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH: // 进行附加 只调用一次
	case DLL_THREAD_ATTACH: //线程附加
	case DLL_THREAD_DETACH: // 线程分离
	case DLL_PROCESS_DETACH: //进程分离 只调用一次
		break;
	}
	return true;
}
//函数导出方式 声明导出/模块定义文件导出
//声明导出
extern "C" _declspec(dllexport) void funTest1()
{
	printf("声明导出函数：funTest1（）\n");
}
//模块定义导出
void funTest2()
{
	printf("模块定义导出函数");
}