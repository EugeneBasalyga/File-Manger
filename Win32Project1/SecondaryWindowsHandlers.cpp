#include "stdafx.h"
#include "Win32Project1.h"
#include "SecondaryWindowsHandlers.h"


extern struct Information
{
	TCHAR name[MAX_PATH];
	TCHAR type[MAX_PATH];
	double size;
	FILETIME crtd; //created
	FILETIME last; //last access
};

extern Information info;

extern TCHAR szWindowClass[MAX_LOADSTRING], szTitle[MAX_LOADSTRING], dir[MAX_PATH], dir1[MAX_PATH], copy_buf1[MAX_PATH];
extern HINSTANCE hInst;

extern TCHAR buf1[MAX_PATH], cm_dir_from[MAX_PATH], cm_dir_to[MAX_PATH], cm_dir_to_[MAX_PATH], cm_dir_from_[MAX_PATH],
path[MAX_PATH], _dir[MAX_PATH], _dir1[MAX_PATH], buff[MAX_PATH], tempdir[MAX_PATH], copyBuffer[MAX_PATH];


INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


INT_PTR CALLBACK InfoWindow(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		static HWND LabelName, LabelSize, LabelType, LabelState, LabelCrtd, LabelLast, LabelAtr;
		TCHAR stringCrtd[255], stringLast[255];
		wchar_t istr[255];
		if (wcscmp(_dir, _T("")) == 0)
			info = GetFileInform(dir);
		else
			info = GetFileInform(_dir);
		LabelName = CreateWindow(_T("static"), info.name, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			55, 15, 215, 16, hDlg, (HMENU)ID_LABELNAME, hInst, NULL);
		swprintf(istr, L"%f", info.size);
		istr[wcslen(istr) - 7] = 0;
		wcscat(istr, _T(" bytes"));
		ShortSize(info.size, istr);
		LabelType = CreateWindow(_T("static"), (LPCWSTR)info.type, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			55, 35, 215, 16, hDlg, (HMENU)ID_LABELTYPE, hInst, NULL);
		LabelSize = CreateWindow(_T("static"), istr, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			55, 60, 500, 16, hDlg, (HMENU)ID_LABELSIZE, hInst, NULL);
		FileTimeToString(info.crtd, stringCrtd);
		LabelCrtd = CreateWindow(_T("static"), stringCrtd, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			85, 80, 215, 16, hDlg, (HMENU)ID_LABELCRTD, hInst, NULL);
		FileTimeToString(info.last, stringLast);
		LabelLast = CreateWindow(_T("static"), stringLast, WS_CHILD | WS_VISIBLE | WS_TABSTOP,
			85, 110, 215, 16, hDlg, (HMENU)ID_LABELLAST, hInst, NULL);
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


BOOL CALLBACK NewFileDialogProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hTextField = GetDlgItem(hWnd, IDC_EDIT1);
	size_t len;
	TCHAR *tBuffer0 = new TCHAR[256], *tBuffer1 = new TCHAR[256], *tBuffer2 = new TCHAR[256];

	switch (uMsg)
	{
	case WM_INITDIALOG:
		SetWindowText(hWnd, dir);
		break;
	case WM_COMMAND:

		switch (LOWORD(wParam))
		{
		case IDOK:

			memset(tBuffer0, '\0', 256);
			memset(tBuffer1, '\0', 256);
			memset(tBuffer2, '\0', 256);

			GetWindowText(hTextField, tBuffer0, 256);
			wcscpy(tBuffer2, dir);
			len = wcslen(tBuffer2);
			tBuffer2[len - 1] = '\0';
			wcscpy(tBuffer1, tBuffer2);
			wcscat(tBuffer1, tBuffer0);

			if (wcscmp(tBuffer0, TEXT("")))
			{
				CreateNewFileOrFolder(tBuffer1);
			}

		case IDCANCEL:
			EndDialog(hWnd, NULL);
			break;
		default:
			break;
		}
		break;
	default:
		return FALSE;
	}
	delete(tBuffer0);
	delete(tBuffer1);
	delete(tBuffer2);
	return TRUE;
}