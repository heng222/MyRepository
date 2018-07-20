/********************************************************
*                                                                                                            
* �� �� ���� Malloc.c
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� ������
* ���������� �ڴ���亯�� 
* �޸ļ�¼��   
*
********************************************************/
#include "Malloc.h"
#include "stdlib.h"

/*
*  ����������  �ڴ����
*  ����˵����  
*  ����ֵ��    
*/
void* MemoryMalloc(UINT32_S size)
{
    void* retFun = NULL;
    if (size > 0)
    {
        retFun = malloc(size);
    }
    else
    {
        retFun = NULL;
    }

    return retFun;
}

