// TargetDll.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "TargetDll.h"


//// �����ѵ�����Ĺ��캯����
//// �й��ඨ�����Ϣ������� TargetDll.h
//CTargetDll::CTargetDll()
//{
//	return;
//}

// ���ǵ���������һ��ʾ��
TARGETDLL_API int nTargetDll=0;

// ���ǵ���������һ��ʾ����
TARGETDLL_API int fnTargetDll(void)
{
	return 42;
}
