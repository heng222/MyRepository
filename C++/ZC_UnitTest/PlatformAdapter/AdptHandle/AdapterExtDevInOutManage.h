/********************************************************
*                                                                                                            
* �� �� ���� AdapterExtDevInOutManage.h   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-01
* ���������� ����㴦��ͷ�ļ� 
* ��    ע�� �� 
*
********************************************************/ 

#ifndef ADAPTER_EXTDEV_INOUT_MANAGE_H_
#define ADAPTER_EXTDEV_INOUT_MANAGE_H_


#include "../../Common/CommonTypes.h"


#define DEV_TOTAL_FRAME_NUM          100u    /* ���ݰ������� */
#define DEV_TOTAL_FRAME_LEN          1300u   /*�������ݵ��ܳ���*/

/* �������ݵ��ܳ��ȣ����ڽ��������ж�����һ���������������ռ� */
#define DEV_TOTAL_RCV_FRAME_LEN          (DEV_TOTAL_FRAME_LEN*15u*2u)


/*���ݴ洢�ṹ��*/
typedef struct
{
    UINT8_S DataBuf[DEV_TOTAL_FRAME_LEN];  /*���ݻ�����*/
    UINT32_S DataLen;                     /*���ݳ���*/
    UINT8_S  DestDevType;                 /*Ŀ���豸����*/
    UINT8_S  DestDevId;                   /*Ŀ���豸ID*/
    UINT8_S  scanFlag;                   /* �Ѿ���ɨ����ı�־ */
} DevComDataCellStruct;



/*���ݻ��ζ��нṹ��*/
typedef struct
{
    DevComDataCellStruct DataCellStru[DEV_TOTAL_FRAME_NUM]; /*���νṹ�нڵ�����*/
    UINT32_S HeadIndex;                                          /*���νṹͷָ��*/
    UINT32_S TailIndex;                                          /*���νṹβָ��*/
    UINT32_S DataPkgCount;                                       /*���νṹ����������*/
} DevComCirQueueStruct;



#ifdef __cplusplus
extern "C" {
#endif
/*
* ������������ʼ���豸������Ϣ�ṹ
* ����˵���� ��
* ����ֵ  ��    1,�ɹ���0��ʧ��
*/
UINT8_S AdapterExtDevCfgInfoInit(void);


/*
* ������������ȡ�豸������Ϣ
* ����˵���� 
* ����ֵ  �� 1:�ɹ�  0,ʧ��
*/
UINT8_S AdapterGetDevCfgDetail(void);

/*
*��������: ƽ̨�ⲿ�������ݹ���
*������
*����ֵ: ��
*/
void  AdapterExtDevInDataManage(void);

/*
*��������: ƽ̨�ⲿ������ݹ���
*������
*����ֵ: 
*/
void AdapterExtDevOutDataManage(void);

/*
* ���������� ��ӷ��Ͷ�������
* ����˵���� 
*            pDataBuf, ���ݻ�����
*            dataLen, ���ݳ���
*            destDevType,�豸����
*            destDevId,�豸ID
* ����ֵ  �� 1: �ɹ�
*            0: ʧ��
*/
UINT8_S AdapterAddDevSndQueData(const UINT8_S* pDataBuf, const UINT32_S dataLen,const UINT8_S destDevType,const UINT8_S destDevId);

/*
* ���������� �����豸���ͺ��豸���ɨ����ն����е�һ������
* ����˵���� pDataBuf, ���ݻ�����
*            dataLen, ���ݳ���
*            destDevType,�豸����
*            destDevId,�豸ID
* ����ֵ  �� 0: ʧ��
*            >0: ���ݵ��ֽڳ���
*/
UINT32_S AdapterScanDevRcvQueData(UINT8_S* pDataBuf, UINT32_S dataLen, const UINT8_S destDevType, const UINT8_S destDevId);

/*
* ���������� ˳���ȡ���ն��е�һ�����ݰ�
* ����˵���� 
*              char* pDataBuf, ���ݻ�����
*              int dataLen, ���ݳ���    
*            pDevType,�豸����
*            pDevId,�豸ID
* ����ֵ  �� 0: ʧ��
*              >0: ���ݵ��ֽڳ���
*/
UINT32_S AdapterGetDevRcvQuePkgData(UINT8_S* pDataBuf, UINT32_S dataLen,UINT8_S* pDevType,UINT8_S* pDevId);


/* 
* ������������ȡ�豸��ͨ��״̬��¼��־
* ����˵����devIndex �豸������
* ����ֵ  ��    1 ������ 0 ������
*/
UINT8_S AdapterGetDevComStatus(const UINT8_S devType, const UINT8_S devId, const UINT8_S sysId);

/* 
* �����������������ص�����
* ����˵����micrNum �����豸������
* ����ֵ  ��    ��
*/
void AdapterSetMicrNum(const UINT8_S micrNum);

#ifdef __cplusplus
}
#endif
#endif

