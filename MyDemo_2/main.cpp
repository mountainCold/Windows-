#include<windows.h>
#define UM_MYMSG WM_USER+1 //�Զ�����Ϣ ������WM_USER֮��
bool print(CONST TCHAR* format, ...) //��κ���
{
	TCHAR buffer[1000];
	va_list argptr;
	va_start(argptr, format);
	// ����ʽ����Ϣд��ָ���Ļ�����
	wvsprintf(buffer, format, argptr);
	va_end(argptr);
	// ����������Ϣ������ڵ��Դ��������Ϣ
	OutputDebugString(buffer);
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lPram)
{
	switch (uMsg)
	{
	case WM_PAINT:
	{
		// ͨ�� msdn ����֪������������Ϣ�� WM_MOVE ʱ�� wParam û�б�ʹ�ã� lParam ��ʾ���Ͻǵ�����
		WORD x = LOWORD(lPram);
		WORD y = HIWORD(lPram);
		print(L"WM_MOVE: (%d, %d)\n", x, y);
		
	}break;
	case WM_LBUTTONDOWN:
	{
		// wParam ��ʾ��ʲô������������Ϣ��lParam��һ���������Ļ���Ͻǵ�����
		WORD x = LOWORD(lPram);
		WORD y = HIWORD(lPram);
		print(L"WM_LBUTTONDOWN: (%d, %d)\n", x, y);
		//PostMessage ���Ͷ�����Ϣ������ ������������������ִ��
		//PostMessage(hWnd, UM_MYMSG, 0, 0);
		//SendMessage ���ͷǶ�����Ϣ������ ��������������ִ�лص�����
		SendMessage(hWnd, UM_MYMSG, 0, 0);
		print(L"111111\n");
	}break;
	case WM_CREATE:
	{
		print(L"���ڱ�����\n");
	}
	case WM_CLOSE:
	{
		//���ٴ���
		DestroyWindow(hWnd);
		//������Ϣѭ��
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
	//1 ���������ಢע��
	WNDCLASS wndClass = { 0 };
	wndClass.lpfnWndProc=WndProc; //�ص�����
	wndClass.lpszClassName = L"MyClass"; //�������������ظ�

	RegisterClass(&wndClass); //ʹ��ǰ������ע�� һ��������ֻ�ܱ�ע��һ��
	//2 ��������Ĵ���
	HWND hWnd = CreateWindow(
		L"MyClass", //��������
		L"���ڱ���",//���ڱ���
		WS_OVERLAPPEDWINDOW, //�������� �ص����� ��������֮һ
		CW_USEDEFAULT, 0,//���ڵ�x��y������  ����Ϊ���Ͻǵ�Ĭ��λ�ò�����y�Ĳ���
		CW_USEDEFAULT, 0,//���ڵĿ�Ⱥ͸߶� ��Ĭ�Ͽ�Ⱥ��Ը߶�
		NULL,			//������ ����д��Ĭ��Ϊ������Ӵ���
		NULL,			//�˵��ľ��
		hInstance, //ʵ����� ��ʶ��ǰ���������ĸ�����
		0 //������Ϣ
	);
	//3 ��ʾ�����´����Ĵ���
	ShowWindow(hWnd, SW_SHOW);//�������� ����ʾ�ķ�ʽ
	UpdateWindow(hWnd);
	//4������Ϣ��
	MSG msg = {};
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		DispatchMessage(&msg);
	}
	return 0;

}

