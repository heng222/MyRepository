/*************************************************
  �ļ���   ��DefaultRouteData.h
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� DefaultRouteData���ݹ���
			DmuCommonData�����DefaultRouteData���ܿɷֽ����£�
			1��	��DefaultRouteDataStru�ṹ��ָ�����ռ�
			2��	��ȡDefaultRouteData����
			3��	 ��ȡDefaultRouteData��Ϣ
			4��	��ȡָ��IDDefaultRouteDataStru�Ľṹ���±�
			5��	��ȡָ��IDDefaultRouteDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDDefaultRouteDataStru��seg���
			7��	��ȡָ��IDDefaultRouteDataStru�����з���
			8��	��ȡָ��IDDefaultRouteDataStru��ǰ��վ̨ID
			9��	��ȡָ��IDDefaultRouteDataStru��Ŀ��վ̨ID
			10��	��ȡ���з������һ����Ȼվ̨ID��ѯ��һ����Ȼվ̨ID


  ��ע    ���ޡ�
 
*************************************************/
#ifndef DEFAULTROUTE_DATA_H_
#define DEFAULTROUTE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define DEFAULTROUTE_LINE_BYTE_NUM                 10                           /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*Ĭ���������б����ݽṹ��*/
typedef struct BnfDefaultRouteStruct
{
    UINT16_S  indexId;                        /*�������*/
    UINT16_S  segId;                            /*seg���*/
    UINT16_S  dir;                            /*���з���*/
    UINT16_S  arriveStaId;                    /*ǰ��վ̨ID*/
    UINT16_S  aimStaId;                        /*Ŀ��վ̨ID*/
}BnfDefaultRouteStruct;

/*
* ���������� ��DefaultRouteDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocDefaultRouteDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡDefaultRouteData����
* ����˵����
* ����ֵ  �� 
            BnfDefaultRouteStruct*
*/
BnfDefaultRouteStruct *GetDefaultRouteData(void);

/*
* ���������� ��ȡDefaultRouteData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfDefaultRouteStruct*
*/
BnfDefaultRouteStruct *GetDefaultRouteDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDDefaultRouteDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetDefaultRouteDataStruIndex(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfDefaultRouteStruct* GetIndexIdDefaultRouteDataStru(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru��seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: seg���
*/ 
UINT16_S GetDefaultRouteDataStrusegId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru�����з���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���з���
*/ 
UINT16_S GetDefaultRouteDataStrudir(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru��ǰ��վ̨ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ǰ��վ̨ID
*/ 
UINT16_S GetDefaultRouteDataStruarriveStaId(const UINT16_S indexId);

/*
** ���������� ��ȡָ��IDDefaultRouteDataStru��Ŀ��վ̨ID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: Ŀ��վ̨ID
*/ 
UINT16_S GetDefaultRouteDataStruaimStaId(const UINT16_S indexId);

/*
* ��������:��ȡ���з������һ����Ȼվ̨ID��ѯ��һ����Ȼվ̨ID
* ����˵��:����:UINT16_S     segId          SEGID 
*                UINT16_S      dir             ���з���
*                UINT16_S*   nextStationId  >0 ��һ����Ȼվ̨ID
* ����ֵ   UINT8_S  1 �ɹ�  0ʧ��
*/
UINT8_S GetNextAccordCurStationId(const UINT16_S segId,const UINT16_S dir,UINT16_S* nextStationId);

#ifdef __cplusplus
}
#endif

#endif
