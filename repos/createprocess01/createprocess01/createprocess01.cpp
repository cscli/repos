// createprocess01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

//#include <cstring>
#pragma warning(disable:4996)
void _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
/*
	if (argc != 2)
	{
		printf("Usage: %s [cmdline]\n", argv[0]);
		return;
	}
	
//	strncpy(argv[1], "dir", sizeof("dir"));
	printf("%s\n", argv[1]);
	*/
	char str[64] = {0};
	//LPTSTR  strcmd = ("c:\\windows\\system32\\cmd.exe");
	//strcpy(str, "c:\\windows\\system32\\cmd.exe");
	strcpy(str, "c:\\windows\\notepad.exe");
	//printf("ret = %d\n", ret);
	printf("str = %s\n", str);
	// Start the child process. 
	if (!CreateProcess(NULL,   // No module name (use command line)
		str,        // Command line
		NULL,           // Process handle not inheritable
		NULL,           // Thread handle not inheritable
		FALSE,          // Set handle inheritance to FALSE
		0,              // No creation flags
		NULL,           // Use parent's environment block
		NULL,           // Use parent's starting directory 
		&si,            // Pointer to STARTUPINFO structure
		&pi)           // Pointer to PROCESS_INFORMATION structure
		)
	{
		printf("CreateProcess failed (%d).\n", GetLastError());
		printf("error is %d", GetLastError());
		getchar();
		return;
	}
	printf("1error is %d\n", GetLastError());
	Sleep(10);
	// Wait until child process exits.
	WaitForSingleObject(pi.hProcess, INFINITE);
	printf("2error is %d\n", GetLastError());
	//getchar();
	// Close process and thread handles. 
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);
}

/*
BOOL CreateProcess(
　LPCTSTR lpApplicationName, // 应用程序名称
　LPTSTR lpCommandLine, // 命令行字符串
　LPSECURITY_ATTRIBUTES lpProcessAttributes, // 进程的安全属性
　LPSECURITY_ATTRIBUTES lpThreadAttributes, // 线程的安全属性
　BOOL bInheritHandles, // 是否继承父进程的属性
　DWORD dwCreationFlags, // 创建标志
　LPVOID lpEnvironment, // 指向新的环境块的指针
　LPCTSTR lpCurrentDirectory, // 指向当前目录名的指针
　LPSTARTUPINFO lpStartupInfo, // 传递给新进程的信息
　LPPROCESS_INFORMATION lpProcessInformation // 新进程返回的信息
);


char cWindowsDirectory[MAX_PATH];

	//LPTSTR 与 wchar_t* 等价(Unicode环境下)
	LPTSTR cWinDir = new TCHAR[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, cWinDir);

	LPTSTR sConLin = wcscat(cWinDir , L"\\..\\Debug\\another.exe a b c d");
*/
