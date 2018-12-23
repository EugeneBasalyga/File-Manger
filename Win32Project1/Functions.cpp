#include "stdafx.h"
#include "Win32Project1.h"
#include "Functions.h"
#include <shlwapi.h>
#include <math.h>
#include <cmath>

void CreateNewFileOrFolder(TCHAR * tPath)
{
	TCHAR *tBuffer0 = new TCHAR[256];
	memset(tBuffer0, '\0', 256);
	tBuffer0 = PathFindExtension(tPath);

	if (!_tcscmp(tBuffer0, TEXT("")))
	{
		CreateDirectory(tPath, NULL);
	}
	else
	{
		HANDLE filehandle = CreateFile(tPath,
			GENERIC_READ | GENERIC_WRITE,
			FILE_SHARE_READ | FILE_SHARE_WRITE,
			NULL,
			CREATE_NEW,
			FILE_ATTRIBUTE_NORMAL,
			NULL);
		CloseHandle(filehandle);
	}
	//delete(tBuffer0);
}


void getNameOfDir(TCHAR nameStr[MAX_PATH], TCHAR res[MAX_PATH])
{
	TCHAR typestr[255], temp[255];
	int ending = 0;
	BOOL flag = false;
	wcscpy(typestr, nameStr);
	reverseString(typestr, temp);
	while ((ending < wcslen(temp)))
	{
		if (!flag)
		{
			if (temp[ending] == '\\')
			{
				temp[ending] = NULL;
				flag = true;
			}
		}
		else
			temp[ending] = NULL;
		ending++;
	}
	wcscpy(typestr, temp);
	reverseString(typestr, temp);
	wcscpy(res, temp);
}

void reverseString(wchar_t str1[255], wchar_t str2[255])
{
	int a1, a2, a3;
	a1 = wcslen(str1);
	a3 = a1;
	for (a2 = 0;a2 < a1;a2++, a3--)
		str2[a2] = str1[a3 - 1];
}

void getTypeOfFile(TCHAR nameStr[MAX_PATH], TCHAR res[MAX_PATH])
{
	//try
	//{
	TCHAR typestr[255], temp[255];
	int ending = 0;
	BOOL flag = false;
	wcscpy(typestr, nameStr);
	reverseString(typestr, temp);
	while ((ending < wcslen(temp)))
	{
		if (!flag)
		{
			if (temp[ending] == '.')
			{
				temp[ending] = NULL;
				flag = true;
			}
		}
		else
			temp[ending] = NULL;
		ending++;
	}
	if (temp[ending] != '\0')
	{
		wcscpy(typestr, temp);
		reverseString(typestr, temp);
		wcscpy(res, temp);
	}
	//throw;
//
//catch(exception &e)
//{
//	MessageBox(0, _T("Not found"), _T("Error"), MB_OK | MB_ICONERROR);
//}
}

void Copy_File(TCHAR from[MAX_PATH], TCHAR directory[MAX_PATH], TCHAR buf[MAX_PATH])
{
	wcscpy(from, directory);
	from[wcslen(from) - 1] = 0;
	wcscat(from, buf);
}

void Delete_File(TCHAR from[MAX_PATH], TCHAR directory[MAX_PATH], TCHAR buf[MAX_PATH])
{
	int res;
	wcscpy(from, directory);
	from[wcslen(from) - 1] = 0;
	wcscat(from, buf);
	if (PathIsDirectory(from))
	{
		RemoveDirectory(from);
	}
	else
	{
		res = DeleteFile(from);
		if (res == 0)
		{
			MessageBox(NULL, TEXT("Cannot delete file!"), TEXT("Error"), MB_OK | MB_ICONERROR);
		}
	}
}

void FileTimeToString(FILETIME ft, TCHAR str[255])
{
	SYSTEMTIME st;
	TCHAR szLocalDate[255], szLocalTime[255];

	FileTimeToLocalFileTime(&ft, &ft);
	FileTimeToSystemTime(&ft, &st);
	GetDateFormat(LOCALE_USER_DEFAULT, DATE_LONGDATE, &st, NULL, szLocalDate, 255);
	GetTimeFormat(LOCALE_USER_DEFAULT, 0, &st, NULL, szLocalTime, 255);
	wcscpy(str, szLocalDate);
	wcscat(str, _T(" "));
	wcscat(str, szLocalTime);
}

void ShortSize(double size, wchar_t str[255])
{
	int power = 0;
	double shortsize = size;

	while (floor(shortsize / 1024) != 0)
	{
		shortsize /= 1024;
		power++;
	}

	wchar_t buffer[MAX_PATH];
	swprintf(buffer, L"%f", shortsize);
	buffer[wcslen(buffer) - 5] = 0;
	switch (power)
	{
	case 0:
		break;
	case 1:
		wcscat(str, _T(" ("));
		wcscat(str, buffer);
		wcscat(str, _T(" Kb)"));
		break;
	case 2:
		wcscat(str, _T(" ("));
		wcscat(str, buffer);
		wcscat(str, _T(" Mb)"));
		break;
	case 3:
		wcscat(str, _T(" ("));
		wcscat(str, buffer);
		wcscat(str, _T(" Gb)"));
		break;
	case 4:
		wcscat(str, _T(" ("));
		wcscat(str, buffer);
		wcscat(str, _T(" Tb)"));
		break;
	}
}


double GetDiskTotalNumberOfFreeBytes(TCHAR * tDisk)
{

	ULARGE_INTEGER FreeBytesAvailable;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;

	BOOL GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx(
		tDisk,					  // directory name
		&FreeBytesAvailable,     // bytes available to caller
		&TotalNumberOfBytes,     // bytes on disk
		&TotalNumberOfFreeBytes  // free bytes on disk
	);

	double dGBFreSpace;
	if (GetDiskFreeSpaceFlag != 0)
	{
		const LONGLONG nGBFactor = 1024 * 1024 * 1024;
		dGBFreSpace = (double)(LONGLONG)TotalNumberOfFreeBytes.QuadPart / nGBFactor;
	}
	dGBFreSpace = round(dGBFreSpace * 100) / 100;
	return dGBFreSpace;
}

double GetDiskTotalNumberOfBytes(TCHAR * tDisk)
{

	ULARGE_INTEGER FreeBytesAvailable;
	ULARGE_INTEGER TotalNumberOfBytes;
	ULARGE_INTEGER TotalNumberOfFreeBytes;

	BOOL GetDiskFreeSpaceFlag = GetDiskFreeSpaceEx(
		tDisk,					  // directory name
		&FreeBytesAvailable,     // bytes available to caller
		&TotalNumberOfBytes,     // bytes on disk
		&TotalNumberOfFreeBytes  // free bytes on disk
	);

	double dGBFreSpace;
	if (GetDiskFreeSpaceFlag != 0)
	{
		const LONGLONG nGBFactor = 1024 * 1024 * 1024;
		dGBFreSpace = (double)(LONGLONG)TotalNumberOfBytes.QuadPart / nGBFactor;
	}
	dGBFreSpace = round(dGBFreSpace * 100) / 100;

	return dGBFreSpace;
}

