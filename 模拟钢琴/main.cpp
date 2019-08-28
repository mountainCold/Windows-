#include<windows.h>
#include<Mmsystem.h>
#include <tchar.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")
using namespace std; //PlaySound(L"F:\\c.wav", NULL, SND_FILENAME | SND_ASYNC);

LRESULT CALLBACK WinPro(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//获取当前的实例句柄
	static HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
	switch (uMsg)
	{
	case WM_CREATE:
	{
		CreateWindow(L"Button", L"点击播放音乐", WS_CHILD | WS_VISIBLE, 10, 40, 200, 20,
			hWnd, (HMENU)0x1001, hInstance, NULL);
		
	}break;
	case WM_CLOSE:
	{
		//销毁窗口
		DestroyWindow(hWnd);
		//结束消息循环
		PostQuitMessage(0);
	}
	case WM_CHAR:
	{
		TCHAR path[255] = { 0 };
		_stprintf_s(path, L"sound\\sound_%c.wav", wParam);
		PlaySound(path, NULL, SND_FILENAME | SND_ASYNC);
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam)==0x1001)
		{
			FILE* f = NULL;
			fopen_s(&f, "Sound\\Sound.txt", "r");
			if (f == NULL) {
				break;
			}

			char ch = 0;
			while (feof(f) == 0)
			{
				ch = fgetc(f);
				if (ch >= 'A' && ch <= 'Z') {
					SendMessage(hWnd, WM_CHAR, ch, 0);
					Sleep(800);
				}
				else {
					Sleep(500);
				}
			}

			fclose(f);
		}
	}
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR IpCmdLine,
	_In_ int nShowCmd)
{
	//创建并注册窗口类
	WNDCLASS WndClass = { 0 };
	WndClass.lpfnWndProc = WinPro;
	WndClass.lpszClassName = L"MYClass";
	WndClass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	RegisterClass(&WndClass);
	//创建窗口并显示更新
	HWND hWnd = CreateWindow(L"MYClass", L"主窗口", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	//建立消息循环
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// 转换函数: 将一组 WM_KEYDOWN 和 WM_KEYUP 组合成一个 WM_CHAR
		// 保留原有的两个消息，将新生成的消息放置到消息队列中
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}