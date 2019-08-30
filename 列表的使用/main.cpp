#include<windows.h>
#include <commctrl.h>
#include "resource.h"
//初始化列表列信息
void InitListViewColumns(HWND hListView)
{
	LVCOLUMN lvc = { 0 };
	//有效字段 有 列名      宽         对齐方式
	lvc.mask = LVCF_TEXT | LVCF_WIDTH|LVCF_FMT;
	//居中对齐 第一列永远左对齐
	lvc.fmt = LVCFMT_CENTER;
	lvc.cx = 80;
	lvc.pszText = (LPWSTR)L"姓名";
	ListView_InsertColumn(hListView,0, &lvc);
	lvc.cx = 80;
	lvc.pszText = (LPWSTR)L"年龄";
	ListView_InsertColumn(hListView,1, &lvc);
	lvc.cx = 80;
	lvc.pszText = (LPWSTR)L"学号";
	ListView_InsertColumn(hListView, 2, &lvc);
}
//初始化行信息
void InItListViewItems(HWND hList, int i, LPWSTR x, LPWSTR n, LPWSTR h)
{
// 	LVITEM lvi = { 0 };
// 	lvi.mask = LVCF_TEXT;
// 	lvi.iItem = i;
// 	lvi.pszText = (LPWSTR)L"";
// 	ListView_InsertItem(hList, &lvi);
// 	ListView_SetItemText(hList, i, 1, x);
// 	ListView_SetItemText(hList, i, 2, n);
// 	ListView_SetItemText(hList, i, 3, h);
	// 需要设置文字的信息，第二个是行
	LVITEM lvItem = { LVIF_TEXT, i };

	// 向列表的指定位置添加一行信息，并且可以设置第一列的值
	lvItem.pszText = (LPWSTR)L"";
	ListView_InsertItem(hList, &lvItem);

	// 在调用 SetItemText 必须保证指定的行被 InsertItem 添加了
	ListView_SetItemText(hList, i, 0, x);
	ListView_SetItemText(hList, i, 1, n);
	ListView_SetItemText(hList, i, 2, h);
}
INT_PTR CALLBACK DIAProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
	{
		HWND hList = GetDlgItem(hWnd, IDC_LIST1);
		ListView_SetExtendedListViewStyle(hList, LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
		InitListViewColumns(hList);
		InItListViewItems(hList, 0,(LPWSTR)L"李白", (LPWSTR)L"24", (LPWSTR)L"长安学院");
		InItListViewItems(hList, 1,(LPWSTR)L"纪宁", (LPWSTR)L"14", (LPWSTR)L"黑白学院");
	}break;
	case WM_NOTIFY:
	{
		NMHDR* pNmHdr = (NMHDR*)lParam;
		if (pNmHdr->idFrom==IDC_LIST1)
		{
			NMLISTVIEW* pNML = (NMLISTVIEW*)lParam;
			if (pNmHdr->code ==NM_RCLICK && pNML->iItem !=-1)
			{
				POINT Point = { 0 };
				GetCursorPos(&Point);
				
				HMENU hMenu = LoadMenu(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_MENU1));
				HMENU hSubMenu = GetSubMenu(hMenu,0);
				TrackPopupMenu(hSubMenu, TPM_LEFTALIGN, Point.x, Point.y,0, hWnd, nullptr);
			}
			else if (pNmHdr->code == NM_CLICK && pNML->iItem != -1)
			{
				// 通过结构体中保存的行和列获取到点击的内容
				WCHAR Buffer[100] = { 0 };

				// pNmHdr->hwndFrom 和 pNmListView->hdr.hwndFrom 是一样的
				ListView_GetItemText(pNmHdr->hwndFrom, pNML->iItem,
					pNML ->iSubItem, Buffer, 100);

				MessageBox(hWnd, Buffer, L"列表控件", MB_OK);
			}
		}
	}break;
	case WM_CLOSE:
	{
		EndDialog(hWnd,0);
	}break;
	default:
		return false;
	}
	return true;
}
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DIAProc);
	return 0;
}