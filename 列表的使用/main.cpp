#include<windows.h>
#include <commctrl.h>
#include "resource.h"
//��ʼ���б�����Ϣ
void InitListViewColumns(HWND hListView)
{
	LVCOLUMN lvc = { 0 };
	//��Ч�ֶ� �� ����      ��         ���뷽ʽ
	lvc.mask = LVCF_TEXT | LVCF_WIDTH|LVCF_FMT;
	//���ж��� ��һ����Զ�����
	lvc.fmt = LVCFMT_CENTER;
	lvc.cx = 80;
	lvc.pszText = (LPWSTR)L"����";
	ListView_InsertColumn(hListView,0, &lvc);
	lvc.cx = 80;
	lvc.pszText = (LPWSTR)L"����";
	ListView_InsertColumn(hListView,1, &lvc);
	lvc.cx = 80;
	lvc.pszText = (LPWSTR)L"ѧ��";
	ListView_InsertColumn(hListView, 2, &lvc);
}
//��ʼ������Ϣ
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
	// ��Ҫ�������ֵ���Ϣ���ڶ�������
	LVITEM lvItem = { LVIF_TEXT, i };

	// ���б��ָ��λ�����һ����Ϣ�����ҿ������õ�һ�е�ֵ
	lvItem.pszText = (LPWSTR)L"";
	ListView_InsertItem(hList, &lvItem);

	// �ڵ��� SetItemText ���뱣ָ֤�����б� InsertItem �����
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
		InItListViewItems(hList, 0,(LPWSTR)L"���", (LPWSTR)L"24", (LPWSTR)L"����ѧԺ");
		InItListViewItems(hList, 1,(LPWSTR)L"����", (LPWSTR)L"14", (LPWSTR)L"�ڰ�ѧԺ");
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
				// ͨ���ṹ���б�����к��л�ȡ�����������
				WCHAR Buffer[100] = { 0 };

				// pNmHdr->hwndFrom �� pNmListView->hdr.hwndFrom ��һ����
				ListView_GetItemText(pNmHdr->hwndFrom, pNML->iItem,
					pNML ->iSubItem, Buffer, 100);

				MessageBox(hWnd, Buffer, L"�б�ؼ�", MB_OK);
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