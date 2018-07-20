/********************************************************
*                                                                                                            
* �� �� ���� Copy.c
* ��Ȩ˵����  
* ����ʱ�䣺 
* ��    �ߣ� ������
* ���������� ���ƺ��� 
* �޸ļ�¼��   
*
********************************************************/
#include "Copy.h"
#include "string.h"


/* �������� : �ڴ濽��������
*  ����˵�� : void *pDest, Ŀ�ĵ�ַ
*             UINT32_S destBuffSize, ���������ȣ������ÿ��������ݳ���
*             const void *pSrc, Դ��ַ
*             UINT32_S count, ��������
*  ����ֵ:    1, δ�������������ȴ��ڱ�������
*             0, �����ɹ�
*/
UINT8_S MemoryCpy(void *pDest, UINT32_S destBuffSize, const void *pSrc, UINT32_S count)
{
    UINT8_S Result = 0u; /* ���ؽ�� */

    if((count > destBuffSize) || (NULL == pDest) || (NULL == pSrc))
    { 
        /* ���������쳣��Ϊ��ָ�룬������*/
        Result = 1u;
    }
    else 
    {
        /*�ڴ渴��*/
        memcpy(pDest,pSrc,count);
        Result = 0u;

    }

    return Result;
}


