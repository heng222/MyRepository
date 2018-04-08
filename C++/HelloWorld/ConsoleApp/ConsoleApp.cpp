// ConsoleApp.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "iostream"
#include <conio.h>
#include "ConsoleApp.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;


void Test()
{
	int i,j;

	for(i=0;i<8;i++)
	{
		for(j=0; j<8; j++)
			if((i+j)%2==0)
				printf("%c%c", 219,219);
			else
				printf("  ");
		printf("\n");
	}
}



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
    //////////////////////////////////////////////////////////////////////////

	Test();

    //////////////////////////////////////////////////////////////////////////
    _tprintf_s(_T("Press any key to continue..."));
    _getch();
	return nRetCode;
}
