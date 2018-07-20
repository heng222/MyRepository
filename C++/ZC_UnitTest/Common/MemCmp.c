/********************************************************
*                                                                                                            
* �� �� ���� MemCmp.c
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� ������
* ���������� ���г�ʼ����ֵ���� 
* �޸ļ�¼��   
*
********************************************************/
#include "MemCmp.h"
#include "string.h"

/*
*  ����������  �Ƚ��ڴ�����
*  ����˵����  
*  ����ֵ      ��    1,�Ƚ���ͬ��0,�Ƚϲ���ͬ
*/
UINT8_S MemoryCmp(const void* pBuf1, UINT32_S buf1Len, const void* pBuf2,UINT32_S buf2Len)
{
    UINT8_S retVal = 0u; /* ���ؽ�� */
    INT32_S funcVal = 0;

    if((NULL != pBuf1) && (NULL != pBuf2))
    {
        if(buf1Len != buf2Len)
        {
            retVal = 0u;
        }
        else
        {
            funcVal = memcmp(pBuf1,pBuf2,buf1Len);
            if( 0 == funcVal)
            {
                retVal = 1u;
            }
            else
            {
                retVal = 0u;
            }
        }
    }

    return retVal;
}
