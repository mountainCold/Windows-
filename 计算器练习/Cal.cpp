#include<windows.h>
HWND hCalcText = 0;
BOOL CALLBACK EnumProc(HWND hWnd, LPARAM lParam)
{
	static int count = 0;
	if (++count == 6) {
		HWND* p = (HWND*)lParam;
		*p = hWnd;
		return FALSE;
	}
	return TRUE;
}

LRESULT CALLBACK WinPro(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//获取当前的实例句柄
	static HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
	HWND hCalWnd = FindWindowA(NULL, "计算器");

	switch (uMsg)
	{
	case WM_CREATE:
	{		

		EnumChildWindows(hCalWnd, EnumProc, (LPARAM)& hCalcText);
		// 添加一个编辑框控件，用于输入数据
		CreateWindow(L"edit", L"", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_MULTILINE | ES_READONLY,
			10, 10, 130, 30, hWnd, (HMENU)0x1010, hInstance, NULL);
		CreateWindow(L"Button", L"1", WS_CHILD | WS_VISIBLE, 10, 40, 30, 20,
			hWnd, (HMENU)0x1001, hInstance, NULL);
		CreateWindow(L"Button", L"4", WS_CHILD | WS_VISIBLE, 10, 60, 30, 20,
			hWnd, (HMENU)0x1004, hInstance, NULL);
		CreateWindow(L"Button", L"7", WS_CHILD | WS_VISIBLE, 10, 80, 30, 20,
			hWnd, (HMENU)0x1007, hInstance, NULL);
		CreateWindow(L"Button", L"2", WS_CHILD | WS_VISIBLE, 40, 40, 30, 20,
			hWnd, (HMENU)0x1002, hInstance, NULL);
		CreateWindow(L"Button", L"5", WS_CHILD | WS_VISIBLE, 40, 60, 30, 20,
			hWnd, (HMENU)0x1005, hInstance, NULL);
		CreateWindow(L"Button", L"8", WS_CHILD | WS_VISIBLE, 40, 80, 30, 20,
			hWnd, (HMENU)0x1008, hInstance, NULL);
		CreateWindow(L"Button", L"0", WS_CHILD | WS_VISIBLE, 10, 100, 60, 20,
			hWnd, (HMENU)0x1000, hInstance, NULL);
		CreateWindow(L"Button", L"3", WS_CHILD | WS_VISIBLE, 70, 40, 30, 20,
			hWnd, (HMENU)0x1003, hInstance, NULL);
		CreateWindow(L"Button", L"6", WS_CHILD | WS_VISIBLE, 70, 60, 30, 20,
			hWnd, (HMENU)0x1006, hInstance, NULL);
		CreateWindow(L"Button", L"9", WS_CHILD | WS_VISIBLE, 70, 80, 30, 20,
			hWnd, (HMENU)0x1009, hInstance, NULL);
		CreateWindow(L"Button", L"=", WS_CHILD | WS_VISIBLE, 70, 100, 30, 20,
			hWnd, (HMENU)0x100E, hInstance, NULL);
		CreateWindow(L"Button", L"+", WS_CHILD | WS_VISIBLE, 100, 40, 30, 20,
			hWnd, (HMENU)0x100A, hInstance, NULL);
		CreateWindow(L"Button", L"-", WS_CHILD | WS_VISIBLE, 100, 60, 30, 20,
			hWnd, (HMENU)0x100B, hInstance, NULL);
		CreateWindow(L"Button", L"*", WS_CHILD | WS_VISIBLE, 100, 80, 30, 20,
			hWnd, (HMENU)0x100C, hInstance, NULL);
		CreateWindow(L"Button", L"/", WS_CHILD | WS_VISIBLE, 100, 100, 30, 20,
			hWnd, (HMENU)0x100D, hInstance, NULL);
	}break;
	case WM_CLOSE:
	{
		//销毁窗口
		DestroyWindow(hWnd);
		//结束消息循环
		PostQuitMessage(0);
	}
	case WM_COMMAND:
	{
		//方法一找到按钮的句柄然后在发送控件通知消息
		HWND h2 = GetDlgItem(hCalWnd, 0x00000000);
		HWND h3 = GetDlgItem(h2, 0x00000000);
		HWND h4 = GetWindow(h3, GW_HWNDNEXT);
		
		switch (LOWORD(wParam))
		{
		case 0x1000:
		{			
			HWND h1 = GetDlgItem(h4 ,0x00000082); 
			SendMessage(h1, BM_CLICK, 0, 0);
			//直接向窗口发送消息
			//SendMessage(hCalWnd,WM_COMMAND,MAKEWPARAM(0x82, BN_CLICKED), 0)
		}break; 
		case 0x1001:
		{
			HWND h1 = GetDlgItem(h4, 0x00000083);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break;
		case 0x1002:
		{
			HWND h1 = GetDlgItem(h4, 0x00000084);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break;
		case 0x1003:
		{
			HWND h1 = GetDlgItem(h4, 0x00000085);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break; 
		case 0x1004:
		{
			HWND h1 = GetDlgItem(h4, 0x00000086);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break;
		case 0x1005:
		{
			HWND h1 = GetDlgItem(h4, 0x00000087);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break; 
		case 0x1006:
		{
			HWND h1 = GetDlgItem(h4, 0x00000088);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break;
		case 0x1007:
		{
			HWND h1 = GetDlgItem(h4, 0x00000089);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break;
		case 0x1008:
		{
			HWND h1 = GetDlgItem(h4, 0x0000008A);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break;
		case 0x1009:
		{
			HWND h1 = GetDlgItem(h4, 0x0000008B);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break; 
		case 0x100A:
		{
			HWND h1 = GetDlgItem(h4, 0x0000005D);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break; 
		case 0x100B:
		{
			HWND h1 = GetDlgItem(h4, 0x0000005E);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break; 
		case 0x100C:
		{
			HWND h1 = GetDlgItem(h4, 0x0000005C);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break;
		case 0x100D:
		{
			HWND h1 = GetDlgItem(h4, 0x0000005B);
			SendMessage(h1, BM_CLICK, 0, 0);
		}break;
		case 0x100E:
		{
			HWND h1 = GetDlgItem(h4, 0x00000079);
			SendMessage(h1, BM_CLICK, 0, 0);
			
		}break;		
		default:
			break;
		}
		HWND hEditWnd = GetDlgItem(hWnd, 0x1010);
		TCHAR buff[100];
		GetWindowText(hCalcText, buff, 100);
		SetWindowText(hEditWnd, buff);
		
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