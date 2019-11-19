#include<Windows.h>
#include<stdio.h>

int main()
{
  //模拟沙箱环境设置
  SetErrorMode(SEM_FAILCRITICALERRORS | SEM_NOALIGNMENTFAULTEXCEPT | SEM_NOGPFAULTERRORBOX | SEM_NOOPENFILEERRORBOX);

  DWORD dwCode ;
  dwCode = SetErrorMode(0x400);    //虽然没有参数的值为0x400，但是这里设置也可以正常运行
  //这里返回前面设置的值，0x1+0x2+0x4+0x8000=0x8007
  printf("the first dwCode:0x%x\n", dwCode);
  dwCode = SetErrorMode(0x0);
  //由于之前设置了SEM_NOALIGNMENTFAULTEXCEPT，所以这里返回值为是0x400+0x4=0x404
  printf("the second dwCode:0x%x\n", dwCode);
  //在沙箱下返回0x404与0x400不相等，所以可以判断是在沙箱下。如果在正常情况下返回0x400
  if (dwCode != 0x400)
  {
    printf("In Sandbox\n");
  }
  else
  {
    printf("In normal machine\n");
  }

  return 0;
}