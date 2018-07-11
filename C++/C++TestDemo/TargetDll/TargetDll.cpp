// TargetDll.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "TargetDll.h"


//// 这是已导出类的构造函数。
//// 有关类定义的信息，请参阅 TargetDll.h
//CTargetDll::CTargetDll()
//{
//	return;
//}

// 这是导出变量的一个示例
TARGETDLL_API int nTargetDll=0;

// 这是导出函数的一个示例。
TARGETDLL_API int fnTargetDll(void)
{
	return 42;
}
