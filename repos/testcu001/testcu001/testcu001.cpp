// testcu001.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <windows.h>
#include <iostream>
#include <Tlhelp32.h>
#include <shlwapi.h>

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
	std::cout << "Hello World!\n";
	WCHAR w_str[128] = L"360主动防御.exe";
	printf("w_str = %ls\n", w_str);
	std::wcout.imbue(std::locale("chs"));
	std::wcout << "---" << w_str << std::endl;

	if (IsExistProcess(w_str))
		printf("存在\n");
	else
		printf("no\n");
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