/********************************************************
*                                                                                                            
* �� �� ���� CircQueueStruct.h
* ��Ȩ˵����  
* ����ʱ�䣺 2013-10-25
* ��    �ߣ� ������
* ���������� ���ζ��нṹ�� 
* �޸ļ�¼��   
*
********************************************************/
#ifndef CIRC_QUEUE_STRUCT_H_
#define CIRC_QUEUE_STRUCT_H_


#include "Copy.h"


#define DATA_PACKAGE_MAX              100u    /*���ݰ�������*/
#define DATA_LEN_MAX                  1400u   /*���ݳ������ֵ*/



/*���ݴ洢�ṹ��*/
typedef struct
{
    UINT8_S DataBuf[DATA_LEN_MAX]; /*���ݻ�����*/
    UINT32_S DataLen; /*���ݳ���*/
} DataCellStruct;



/*���ݻ��ζ��нṹ��*/
typedef struct
{
    DataCellStruct DataCellStru[DATA_PACKAGE_MAX]; /*���νṹ�нڵ�����*/
    UINT32_S HeadIndex; /*���νṹͷָ��*/
    UINT32_S TailIndex; /*���νṹβָ��*/
    UINT32_S DataPkgCount; /*���νṹ����������*/
} CirQueueStruct;



typedef CirQueueStruct QUEUESTRUCT;



#ifdef __cplusplus
extern "C" {
#endif

/*
* ���������� ��Ӷ�������
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��
*              CHAR_S* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���
* ����ֵ  �� 0: �ɹ�
*              -1: ʧ��
*/
INT8_S AddQueueData(CirQueueStruct* pCirQueueStru, const UINT8_S* pDataBuf,const UINT32_S dataLen);

/*
* ���������� ��ȡ�������ݰ�����
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��   
* ����ֵ  �� -1: ʧ��
*              >=0: ���ݰ����� 
*/
UINT32_S GetQueuePkgCount(const CirQueueStruct* pCirQueueStru);

/*
* ���������� ��ȡ�������ݰ�
* ����˵���� CirQueueStruct* pCirQueueStru, ���ζ���ָ��
*              CHAR_S* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���    
* ����ֵ  �� -1: ʧ��
*              >=0: ���ݵ��ֽڳ���
*/
UINT32_S GetQueuePkgData(CirQueueStruct* pCirQueueStru, UINT8_S* pDataBuf, UINT32_S dataLen);




#ifdef __cplusplus
}
#endif


#endif
