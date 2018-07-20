/********************************************************
*                                                                                                            
* �� �� ���� MemSet.c
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� ������
* ���������� ���г�ʼ����ֵ���� 
* �޸ļ�¼��   
*
********************************************************/
#include "MemSet.h"
#include "string.h"

/*
*  ����������  �ڴ����ݳ�ʼ��
*  ����˵����  
*  ����ֵ��    
*/
UINT8_S MemorySet(void* pDest, UINT32_S destBuffSize, UINT8_S c, UINT32_S count)
{
    UINT8_S Result = 0; /* ���ؽ�� */

    if((count > destBuffSize) || (NULL == pDest))
    { 
        /* ��ֵ�����쳣��Ϊ��ָ�룬����ֵ*/
        Result = 0;
    }
    else 
    {
        /*�ڴ渳ֵ*/
        memset(pDest,c,count);
        Result = 1;
    }

    return Result;
}

