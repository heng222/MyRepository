/********************************************************
*                                                                                                            
* �� �� ���� CircQueueStruct.cpp
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� ������
* ���������� ���ζ��нṹ��  
* �޸ļ�¼��   
*
********************************************************/ 
#include "CircQueueStruct.h"







/*
* ���������� ��Ӷ�������
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��
*              CHAR_S* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���
* ����ֵ  �� 0: �ɹ�
*              -1: ʧ��
*/
INT8_S AddQueueData(CirQueueStruct* pCirQueueStru,const UINT8_S* pDataBuf,const UINT32_S dataLen)
{
    INT8_S retVal = 0;
    
    if ((pCirQueueStru != NULL) && (pDataBuf != NULL) && (dataLen > 0) && (dataLen <= DATA_LEN_MAX) && (pCirQueueStru->DataPkgCount != DATA_PACKAGE_MAX))
    {
        if (DATA_PACKAGE_MAX == pCirQueueStru->TailIndex)
        {
            pCirQueueStru->TailIndex = 0;
        }

        MemoryCpy(pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataBuf, DATA_LEN_MAX, pDataBuf, dataLen); /*���������*/

        pCirQueueStru->DataCellStru[pCirQueueStru->TailIndex].DataLen = dataLen; /*��¼��ӵ����ݳ���*/

        /*������ݺ���β����*/
        pCirQueueStru->TailIndex++; /*����β����*/
        pCirQueueStru->DataPkgCount++; /*�������ݰ�����*/

        retVal = 0;
    }
    else
    {
        retVal = 1;
    }

    return retVal;
}


/*
* ���������� ��ȡ�������ݰ�����
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��    
* ����ֵ  �� ���ݰ�����
*/
UINT32_S GetQueuePkgCount(const CirQueueStruct* pCirQueueStru)
{
    UINT32_S retVal = 0u;
    if (pCirQueueStru != NULL)
    {
        retVal = pCirQueueStru->DataPkgCount; /*���ݰ�����*/
    }
    
    return retVal;
}


/*
* ���������� ��ȡ�������ݰ�
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��
*              CHAR_S* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���    
* ����ֵ  �� -1: ʧ��
*              >=0: ���ݵ��ֽڳ���
*/
UINT32_S GetQueuePkgData(CirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen)
{
    UINT32_S realDataLen = 0u; /*��¼ʵ�����ݳ���*/
    UINT32_S retVal = 0u;

    
    if ((pCirQueueStru != NULL) && (pDataBuf != NULL) && (dataLen > 0))
    {
        if (pCirQueueStru->DataPkgCount > 0)
        { /*���ݰ���������0*/

            realDataLen = pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataLen; /*��¼ʵ�����ݳ���*/

            if ((realDataLen > 0) && (dataLen >= realDataLen))
            { /*ʵ�����ݳ�����Ч && ��ȡ���ݻ�����������Ч && ���ݰ���������0*/

                MemoryCpy(pDataBuf, dataLen, pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataBuf, realDataLen); /*COPY����*/

                pCirQueueStru->DataCellStru[pCirQueueStru->HeadIndex].DataLen = 0; /*���ݳ�����0*/

                /*��ȡ���ݺ���ͷ����*/
                pCirQueueStru->HeadIndex++;

                if (DATA_PACKAGE_MAX == pCirQueueStru->HeadIndex)
                {
                    pCirQueueStru->HeadIndex = 0;
                }

                pCirQueueStru->DataPkgCount--; /*�������ݰ�����*/

                retVal = realDataLen;
            }
            else
            {
                retVal = 0u;
            }
        }
        else
        {
            retVal = 0u;
        }
    }
    else
    {
        retVal = 0u;
    }
    return retVal;
}




