#include<windows.h>
#define UM_MYMSG WM_USER+1 //自定义消息 必须在WM_USER之后
bool print(CONST TCHAR* format, ...) //变参函数
{
	TCHAR buffer[1000];
	va_list argptr;
	va_start(argptr, format);
	// 将格式化信息写入指定的缓冲区
	wvsprintf(buffer, format, argptr);
	va_end(argptr);
	// 将缓冲区信息输出，在调试窗口输出信息
	OutputDebugString(buffer);
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lPram)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		// 通过 msdn 可以知道当产生的消息是 WM_MOVE 时， wParam 没有被使用， lParam 表示左上角的坐标
		WORD x = LOWORD(lPram);
		WORD y = HIWORD(lPram);
		print(L"WM_MOVE: (%d, %d)\n", x, y);
		
	}break;
	case WM_LBUTTONDOWN:
	{
		// wParam 表示是什么按键产生的消息，lParam是一个相对于屏幕左上角的坐标
		WORD x = LOWORD(lPram);
		WORD y = HIWORD(lPram);
		print(L"WM_LBUTTONDOWN: (%d, %d)\n", x, y);
		//PostMessage 发送队列消息到窗口 非阻塞函数不会立即执行
		//PostMessage(hWnd, UM_MYMSG, 0, 0);
		//SendMessage 发送非队列消息到窗口 阻塞函数会立即执行回调函数
		SendMessage(hWnd, UM_MYMSG, 0, 0);
		print(L"111111\n");
	}break;
	case WM_CREATE:
	{
		print(L"窗口被创建\n");
	}
	case WM_CLOSE:
	{
		//销毁窗口
		DestroyWindow(hWnd);
		//结束消息循环
		PostQuitMessage(0);
	}
	case UM_MYMSG:
	{
		print(L"123123\n");
	}
		break;
	default:
		break;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lPram);
}
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR IpCmdLine,
	_In_ int nShowCmd)
{
	//1 创建窗口类并注册
	WNDCLASS wndClass = { 0 };
	wndClass.lpfnWndProc=WndProc; //回调函数
	wndClass.lpszClassName = L"MyClass"; //窗口类名不能重复

	RegisterClass(&wndClass); //使用前必须先注册 一个窗口类只能被注册一次
	//2 创建具体的窗口
	HWND hWnd = CreateWindow(
		L"MyClass", //窗口类名
		L"窗口标题",//窗口标题
		WS_OVERLAPPEDWINDOW, //窗口类型 重叠窗口 三大类型之一
		CW_USEDEFAULT, 0,//窗口的x，y的坐标  窗口为左上角的默认位置并忽略y的参数
		CW_USEDEFAULT, 0,//窗口的宽度和高度 ，默认宽度忽略高度
		NULL,			//父窗口 ，不写就默认为桌面的子窗口
		NULL,			//菜单的句柄
		hInstance, //实例句柄 标识当前窗口属于哪个程序
		0 //附加信息
	);
	//3 显示并更新创建的窗口
	ShowWindow(hWnd, SW_SHOW);//参数窗口 及显示的方式
	UpdateWindow(hWnd);
	//4建立消息泵
	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		DispatchMessage(&msg);
	}
	return 0;

}

