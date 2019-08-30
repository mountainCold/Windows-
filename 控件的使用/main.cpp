#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h >
#include <stdio.h>
#include "resource.h"
INT_PTR CALLBACK DiaFunc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int static num = 0;
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hCOMbo = GetDlgItem(hWnd, IDC_COMBO1);
		ComboBox_AddString(hCOMbo, L"文本2");
		WCHAR buff[100] = { 0 };
		for (int i=0;i<20;++i)
		{
			swprintf_s(buff, L"1文本%d", i);
			ComboBox_AddString(hCOMbo,buff);
		}
		//添加下拉列表文本
		ComboBox_AddString(hCOMbo, L"1文本!");
		//设置默认选项
		//ComboBox_SetCurSel(hCOMbo, 0);
		ComboBox_SelectString(hCOMbo, 2, L"1文本0");
		HWND hPosCon = GetDlgItem(hWnd, IDC_PROGRESS1);
		SendMessage(hPosCon, PBM_SETRANGE, 0, MAKELPARAM(0,100));
		SendMessage(hPosCon, PBM_SETPOS, 50, 0);
		//SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETPOS, 50, 0);
		SendDlgItemMessage(hWnd, IDC_SLIDER1, TBM_SETRANGE, 0, MAKELPARAM(0, 100));
		SendDlgItemMessage(hWnd, IDC_SLIDER1, TBM_SETPOS, true,50);
		SendDlgItemMessage(hWnd, IDC_SLIDER2, TBM_SETRANGE, 0, MAKELPARAM(0, 2));
		SendDlgItemMessage(hWnd, IDC_SLIDER2, TBM_SETPOS, true, 1);
		
	}break;
	case WM_CLOSE:
	{
		EndDialog(hWnd, 0);
	}break;
	case WM_HSCROLL:
	{
		if (IDC_SLIDER1 == GetDlgCtrlID((HWND)lParam))
		{
			int pos = SendDlgItemMessage(hWnd, IDC_SLIDER1, TBM_GETPOS, 0, 0);
			SendDlgItemMessage(hWnd, IDC_PROGRESS1, PBM_SETPOS, pos, 0);
		}if (IDC_SLIDER2 == GetDlgCtrlID((HWND)lParam))
		{
			int pos = SendDlgItemMessage(hWnd, IDC_SLIDER2, TBM_GETPOS, 0, 0);
			pos %= 2;
			HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1 + pos));
			SendDlgItemMessage(hWnd, IDC_STATIC1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		}
		
	}
	case WM_COMMAND:
	{
		switch (LOWORD(wParam))
		{
		case IDC_BUTTON1:
		{
			num = ++num % 2;
			HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1 + num));
			SendDlgItemMessage(hWnd, IDC_STATIC1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
		}break;
		case IDC_COMBO1:
		{
			if (CBN_SELCHANGE==HIWORD(wParam))
			{
				int index = ComboBox_GetCurSel(HWND(lParam));
				index = index % 2;
				HBITMAP hBitmap = LoadBitmap(GetModuleHandle(NULL), MAKEINTRESOURCE(IDB_BITMAP1 +index));
				SendDlgItemMessage(hWnd, IDC_STATIC1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)hBitmap);
			}
		}
		default:
			break;
		}
	}
	default:
		return false;
	}
	return true;
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DiaFunc);
}