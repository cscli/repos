#include<Windows.h>
#include<stdio.h>

int main()
{
  DWORD dwCode;
  //开始没有设置任何值，所以返回值为0
  dwCode = SetErrorMode(SEM_FAILCRITICALERRORS);
  printf("the first dwCode:0x%x\n", dwCode);

  //这里设置值SEM_NOGPFAULTERRORBOX是2，返回值为前面设置的值所以为1
  dwCode = SetErrorMode(SEM_NOGPFAULTERRORBOX);
  printf("the second dwCode:0x%x\n", dwCode);

  return 0;
}