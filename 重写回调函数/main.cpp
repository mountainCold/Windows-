#include<windows.h>
#include "resource.h"
WNDPROC OldButt = NULL;
LRESULT CALLBACK ButtProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_LBUTTONUP:
	{
		MessageBox(0, 0, 0, 0);
	}break;
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
		PostQuitMessage(NULL);
	}
	default:
		break;
	}
	return OldButt(hWnd, uMsg, wParam, lParam);
}
INT_PTR CALLBACK DIAProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hButton = GetDlgItem(hWnd, IDC_BUTTON1);
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		
		OldButt = (WNDPROC)SetWindowLong(hButton, GWL_WNDPROC, (LONG)ButtProc);
	}break;
	case WM_COMMAND:
	{
 		
	}break;
	case WM_CLOSE:
	{
		SendMessage(hButton, WM_CLOSE, 0, 0);
		EndDialog(hWnd, 0);

	}break;
	default:
	
		return false;
	}
	return true;
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DIAProc);
	return 0;
}