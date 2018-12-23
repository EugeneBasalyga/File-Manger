#pragma once
#include <Windows.h>

void CreateNewFileOrFolder(TCHAR * tPath);

void getNameOfDir(TCHAR nameStr[MAX_PATH], TCHAR res[MAX_PATH]);

void reverseString(wchar_t str1[255], wchar_t str2[255]);

void getTypeOfFile(TCHAR nameStr[MAX_PATH], TCHAR res[MAX_PATH]);

void Copy_File(TCHAR from[MAX_PATH], TCHAR directory[MAX_PATH], TCHAR buf[MAX_PATH]);

void Delete_File(TCHAR from[MAX_PATH], TCHAR directory[MAX_PATH], TCHAR buf[MAX_PATH]);

void FileTimeToString(FILETIME ft, TCHAR str[255]);

void ShortSize(double size, wchar_t str[255]);

double GetDiskTotalNumberOfFreeBytes(TCHAR * tDisk);

double GetDiskTotalNumberOfBytes(TCHAR * tDisk);