/*************************************************
  �ļ���   ��StopPointData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� StopPointData���ݹ���
			DmuCommonData�����StopPointData���ܿɷֽ����£�
			1��	��StopPointDataStru�ṹ��ָ�����ռ�
			2��	��ȡStopPointData����
			3��	��ȡStopPointData��Ϣ
			4��	��ȡָ��IDStopPointDataStru�Ľṹ���±�
			5��	��ȡָ��IDStopPointDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDStopPointDataStru��ͣ��������
			7��	��ȡָ��IDStopPointDataStru��ͣ�������÷���(16����)
			8��	��ȡָ��IDStopPointDataStru��ͣ��������seg���
			9��	��ȡָ��IDStopPointDataStru��ͣ����Segƫ����
			10��	��ȡָ��IDStopPointDataStru��ͣ�����ӦATO���ô���Χ
			11��	��ȡָ��IDStopPointDataStru��ͣ�����ӦATP���ô���Χ
			12��	��ȡָ��ƫ���Ƿ���ATP���ô���Χ
			13��	��ȡָ��ƫ���Ƿ���ATO���ô���Χ

  ��ע    ���ޡ�
 
*************************************************/
#ifndef STOPPOINT_DATA_H_
#define STOPPOINT_DATA_H_

#include "../../../Common/CommonTypes.h"

#define STOPPOINT_LINE_BYTE_NUM                 20                           /*һ�����ݵ��ֽ���*/


#ifdef __cplusplus
extern "C" {
#endif

/*ͣ�����*/
typedef struct BnfStopPointStruct
{
    UINT16_S  stopPointId;                    /*�������*/
    UINT16_S  attribute;                        /*ͣ��������*/
    UINT16_S  dir;                            /*ͣ�������÷���(16����)*/
    UINT16_S  segId;                            /*ͣ��������seg���*/
    UINT32_S  segOfst;                        /*ͣ����Segƫ����*/
    UINT32_S  aTOParkArea;                    /*ͣ�����ӦATO���ô���Χ*/
    UINT32_S  aTPParkArea;                    /*ͣ�����ӦATP���ô���Χ*/
}BnfStopPointStruct;

/*
* ���������� ��StopPointDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocStopPointDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡStopPointData����
* ����˵����
* ����ֵ  �� 
            BnfStopPointStruct*
*/
BnfStopPointStruct *GetStopPointData(void);

/*
* ���������� ��ȡStopPointData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfStopPointStruct*
*/
BnfStopPointStruct *GetStopPointDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDStopPointDataStru�Ľṹ���±�
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetStopPointDataStruIndex(const UINT16_S stopPointId);

/*
** ���������� ��ȡָ��IDStopPointDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStopPointStruct* GetIndexIdStopPointDataStru(const UINT16_S stopPointId);

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ��������
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ��������
*/ 
UINT16_S GetStopPointDataStruattribute(const UINT16_S stopPointId);

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ�������÷���(16����)
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ�������÷���(16����)
*/ 
UINT16_S GetStopPointDataStrudir(const UINT16_S stopPointId);

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ��������seg���
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ��������seg���
*/ 
UINT16_S GetStopPointDataStrusegId(const UINT16_S stopPointId);

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ����Segƫ����
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ����Segƫ����
*/ 
UINT32_S GetStopPointDataStrusegOfst(const UINT16_S stopPointId);

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ�����ӦATO���ô���Χ
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ�����ӦATO���ô���Χ
*/ 
UINT32_S GetStopPointDataStruaTOParkArea(const UINT16_S stopPointId);

/*
** ���������� ��ȡָ��IDStopPointDataStru��ͣ�����ӦATP���ô���Χ
* ����˵���� const UINT16_S stopPointId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ͣ�����ӦATP���ô���Χ
*/ 
UINT32_S GetStopPointDataStruaTPParkArea(const UINT16_S stopPointId);
/*
** ���������� ��ȡָ��ƫ���Ƿ���ATP���ô���Χ
* ����˵���� const UINT16_S stopPointId;�������
                         UINT32_S Off
* ����ֵ  :  0������ATPͣ������
*                    1����ATPͣ������
*/ 
UINT8_S GetThisInAtpStopPointWindow(const UINT16_S stopPointId,UINT32_S Off);
/*
** ���������� ��ȡָ��ƫ���Ƿ���ATO���ô���Χ
* ����˵���� const UINT16_S stopPointId;�������
                         UINT32_S Off
* ����ֵ  :  0������ATPͣ������
*                    1����ATPͣ������
*/ 
UINT8_S GetThisInAtoStopPointWindow(const UINT16_S stopPointId,UINT32_S Off);

#ifdef __cplusplus
}
#endif

#endif
