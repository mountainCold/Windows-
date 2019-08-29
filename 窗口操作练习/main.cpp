#include<windows.h>
#include "resource.h"
INT_PTR CALLBACK DiaLProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hWnd, IDC_RADIO3, BM_SETCHECK, BST_CHECKED, 0);
		SendDlgItemMessage(hWnd, IDC_CHECK1, BM_SETCHECK, BST_CHECKED, 0);
		return true;
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{
			for (int i=0;i<3;++i)
			{
				HWND hRad = GetDlgItem(hWnd, IDC_RADIO1 + i);
				BOOL Check = SendMessage(hRad, BM_GETCHECK, 0, 0);
				if (Check)
				{
					CHAR buff[100] = { 0 };
					GetDlgItemTextA(hWnd, IDC_RADIO1 + i, buff, 100);
					MessageBoxA(hWnd, buff, buff, MB_OK);
					break;
				}
			}
			return true;
		}
		case IDC_BUTTON2:
		{
			for (int i = 0; i < 3; ++i)
			{
				HWND hCHE = GetDlgItem(hWnd, IDC_CHECK1 + i);
				BOOL Checked = SendMessage(hCHE, BM_GETCHECK, 0, 0);
				// �����ѡ�о����
				if (Checked)
				{
					// ��ȡ�ؼ��������������
					CHAR Buffer[100] = { 0 };
					GetDlgItemTextA(hWnd, IDC_CHECK1 + i, Buffer, 100);

					// ��ʾ
					MessageBoxA(hWnd, Buffer, Buffer, MB_OK);
				}
			}
			return true;
		}
		default:
			break;;
		}
	}break;
	case WM_CLOSE:
	{
		EndDialog(hWnd, 0);
	}break;
	default:
		break;
		//return false;
	}
	return false;
}
LRESULT CALLBACK WinProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}
LRESULT CALLBACK WinPro(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;		//�������
	PAINTSTRUCT ps; //���ƽṹ
	RECT rect;		//���νṹ
	//��ȡ��ǰ��ʵ�����
	static HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
	switch (uMsg)
	{
	case WM_CREATE:
	{
		CreateWindow(L"Button", L"�����Ի���", WS_CHILD | WS_VISIBLE, 40, 40, 120, 40, hWnd, 
			(HMENU)0x1000, hInstance, NULL);
		CreateWindow(L"Button", L"���ò˵�", WS_CHILD | WS_VISIBLE, 40, 100, 120, 40, hWnd, 
			(HMENU)0x1001, hInstance, NULL); 
		CreateWindow(L"Button", L"����ͼ��", WS_CHILD | WS_VISIBLE, 40, 160, 120, 40, hWnd,
			(HMENU)0x1002, hInstance, NULL);
		return 0;
	}break;
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case 0x1000:
		{
			//ģ̬�Ի���
			DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, DiaLProc);
			return 0;
		}break;
		case 0x1001:
		{
			HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
			SetMenu(hWnd, hMenu);
			return 0;
		}
		case 0x1002:
		{
			//�����Զ���ͼ�� ���޸�
			HICON hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
			SetClassLong(hWnd, GCL_HICON, (LONG)hIcon);
			return 0;
		}
		default:
			break;
		}
		
	}break;
	case WM_RBUTTONDOWN:
	{
		POINT point = { LOWORD(lParam), HIWORD(lParam) };		ClientToScreen(hWnd, &point);
		HMENU hMenu = LoadMenu(hInstance, MAKEINTRESOURCE(IDR_MENU1));
		HMENU hSubMenu = GetSubMenu(hMenu,0);
		//�����˵�
		TrackPopupMenu(hSubMenu,TPM_LEFTALIGN,point.x,point.y,NULL,hWnd,NULL);
		return 0;
	}  break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		GetClientRect(hWnd, &rect);
		DrawText(hdc, L"��ŷ���ǣ����ﲻ��", -1, &rect, DT_SINGLELINE |
			DT_CENTER | DT_VCENTER);
		EndPaint(hWnd, &ps);
		return 0;
	}break;
	case WM_CLOSE:
	{
		PostQuitMessage(0);
		return 0;
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
	//������ע�ᴰ����
	WNDCLASS WndClass = { 0 };
	WndClass.lpfnWndProc = WinPro;
	//�����Զ����� NULL ��ʾʹ��ϵͳ��
	WndClass.hCursor = LoadCursor(hInstance,MAKEINTRESOURCE(IDC_CURSOR1));
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