#include<windows.h>
LRESULT CALLBACK WinPro(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//��ȡ��ǰ��ʵ�����
	static HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
	switch (uMsg)
	{
	case WM_CREATE:
	{
		CreateWindow(L"Button", L"�����ť", WS_CHILD | WS_VISIBLE, 10, 10, 150, 50, 
			hWnd, (HMENU)0x1000, hInstance, NULL);
	}break;
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
	//������ע�ᴰ����
	WNDCLASS WndClass = { 0 };
	WndClass.lpfnWndProc = WinPro;
	WndClass.lpszClassName = L"MYClass";
	WndClass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	RegisterClass(&WndClass);
	//�������ڲ���ʾ����
	HWND hWnd = CreateWindow(L"MYClass", L"������", WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
	ShowWindow(hWnd, SW_SHOWNORMAL);
	UpdateWindow(hWnd);
	//������Ϣѭ��
	MSG msg = { 0 };
	while (GetMessage(&msg, NULL, 0, 0))
	{
		// ת������: ��һ�� WM_KEYDOWN �� WM_KEYUP ��ϳ�һ�� WM_CHAR
		// ����ԭ�е�������Ϣ���������ɵ���Ϣ���õ���Ϣ������
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}