// testcu001.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include <iostream>
#include <Tlhelp32.h>
#include <shlwapi.h>

/* **********************************************************************
 * BOOL GetDiskSpaceInfo(LPCSTR pszDrive)
 * 功能：根据输入的驱动器，获取磁盘总容量、空闲空间、簇数量等磁盘信息
 * 参数：驱动器根路径，比如：“D:\”
 ***********************************************************************/
BOOL GetDiskSpaceInfo(LPCSTR pszDrive)
{
	DWORD64 qwFreeBytesToCaller, qwTotalBytes, qwFreeBytes;
	DWORD dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;
	BOOL bResult;

	printf("%s\n", pszDrive);

	//使用GetDiskFreeSpaceEx获取磁盘信息并打印结果
	bResult = GetDiskFreeSpaceExA(
		pszDrive,
		(PULARGE_INTEGER)& qwFreeBytesToCaller,
		(PULARGE_INTEGER)& qwTotalBytes,
		(PULARGE_INTEGER)& qwFreeBytes
	);
	if (bResult)
	{
		printf("使用GetDiskFreeSpaceEx获取磁盘空间信息\n");
		printf("可获得的空闲空间（字节）：\t%I64d\n", qwFreeBytesToCaller);
		printf("空闲空间（字节）：\t\t%I64d\n", qwFreeBytes);
		printf("磁盘总容量（字节）：\t\t%I64d\n", qwTotalBytes);
	}
	//使用GetDiskFreeSpace获取磁盘信息并打印结果
	bResult = GetDiskFreeSpaceA(
		pszDrive,
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters,
		&dwTotalClusters
	);
	if (bResult)
	{
		printf("\n使用GetDiskFreeSpace获取磁盘空间信息\n");
		printf("空闲的簇数量：\t\t%d\n", dwFreeClusters);
		printf("总簇数量：\t\t%d\n", dwTotalClusters);
		printf("每簇的扇区数量：\t%d\n", dwSectPerClust);
		printf("每扇区的容量（字节）：\t%d\n", dwBytesPerSect);
		printf("空闲空间（字节）：\t%I64d\n", (DWORD64)dwFreeClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);
		printf("磁盘总容量（字节）：\t%I64d\n", (DWORD64)dwTotalClusters * (DWORD64)dwSectPerClust * (DWORD64)dwBytesPerSect);
	}
	return bResult;
}

BOOL IsExistProcess(WCHAR* szProcessName)  //TCHAR 在使用多字节编码时被定义成char，在Unicode编码时定义成wchar_t
{
	printf("processname wcslen=%d\n", wcslen(szProcessName));
	printf("processname = %ls\n", szProcessName);
	printf("---------------\n");
	PROCESSENTRY32 processEntry32;
	HANDLE toolHelp32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (((int)toolHelp32Snapshot) != -1)
	{
		processEntry32.dwSize = sizeof(processEntry32);
		if (Process32First(toolHelp32Snapshot, &processEntry32))
		{
			do
			{	//int lstrcmpW( LPCWSTR lpString1, LPCWSTR lpString2 );    LPCWSTR===const wchar_t*
				if (lstrcmpW((szProcessName), processEntry32.szExeFile) == 0)
				{
					return TRUE;
				}
			} while (Process32Next(toolHelp32Snapshot, &processEntry32));
		}
		CloseHandle(toolHelp32Snapshot);
	}

	return FALSE;
}
int main()
{
	setlocale(LC_CTYPE, "chs");   // 添加了此行，printf("%ls") 能正常输出汉字了
	std::cout << "Hello World!\n";
	WCHAR w_str[128] = L"360主动防御.exe";
	printf("w_str = %ls\n", w_str);
	std::wcout.imbue(std::locale("chs"));
	std::wcout << "---" << w_str << std::endl;

	if (IsExistProcess(w_str))
		printf("存在\n");
	else
		printf("no\n");
	//GetDiskSpaceInfo("c:");
	return 0;


}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单



/*
#include <MsgBoxConstants.au3>

If ProcessExists("notepad.exe") Then; Check if the Notepad process is running.
MsgBox($MB_SYSTEMMODAL, "", "Notepad is running")
Else
MsgBox($MB_SYSTEMMODAL, "", "Notepad is not running")
EndIf
*/