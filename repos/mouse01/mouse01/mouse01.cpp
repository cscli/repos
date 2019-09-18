// mouse01.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <windows.h>
#include <stdio.h>
#pragma comment(lib, "user32.lib")

void main()
{
	BOOL fResult;
	int aMouseInfo[3];

	fResult = GetSystemMetrics(SM_MOUSEPRESENT);

	if (fResult == 0)
		printf("No mouse installed.\n");
	else
	{
		printf("Mouse installed.\n");

		// Determine whether the buttons are swapped. 

		fResult = GetSystemMetrics(SM_SWAPBUTTON);

		if (fResult == 0)
			printf("Buttons not swapped.\n");
		else printf("Buttons swapped.\n");

		// Get the mouse speed and the threshold values. 

		fResult = SystemParametersInfo(
			SPI_GETMOUSE,  // get mouse information 
			0,             // not used 
			&aMouseInfo,   // holds mouse information 
			0);            // not used 

		if (fResult)
		{
			printf("Speed: %d\n", aMouseInfo[2]);
			printf("Threshold (x,y): %d,%d\n",
				aMouseInfo[0], aMouseInfo[1]);
		}
		system("pause");
	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
