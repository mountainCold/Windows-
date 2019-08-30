#pragma once
#define WIN32_LEAN_AND_MEAN //从windows 头文件排除极少用的内容
#include <windows.h>
//函数导出方式 声明导出/模块定义文件导出
//声明导出
extern "C" _declspec(dllexport) void funTest1();
void funTest2();