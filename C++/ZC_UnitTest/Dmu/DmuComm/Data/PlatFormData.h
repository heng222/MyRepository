/*************************************************
  �ļ���   ��PlatFormData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� PlatFormData���ݹ���
			DmuCommonData�����PlatFormData���ܿɷֽ����£�
			1��	��PlatFormDataStru�ṹ��ָ�����ռ�
			2��	��ȡPlatFormData����
			3��	��ȡPlatFormData��Ϣ
			4��	��ȡָ��IDPlatFormDataStru�Ľṹ���±�
			5��	��ȡָ��IDPlatFormDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDPlatFormDataStru��վ̨���Ĺ����
			7��	��ȡָ��IDPlatFormDataStru��վ̨����seg���
			8��	��ȡָ��IDPlatFormDataStru���߼�������վ̨�����ͣ������ķ���
			9��	��ȡ��SEG��Ӧ��վ̨ID
			10��	���Ҵ˼��������Ƿ�����վ̨����
			11��	��ȡ��SEG��Ӧ��վ̨ID(֧�ֶ��Seg)
			12��	��ȡ��SEG��Ӧ��վ̨ID
  ��ע    ���ޡ�
 
*************************************************/
#ifndef PLATFORM_DATA_H_
#define PLATFORM_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  PLATFORM_NAME_BYTE_LEN      16                            /*���Ƴ���*/
#define  PLATFORM_LINE_BYTE_NUM         21                            /*һ�������ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*վ̨��*/
typedef struct BnfPlatFormStruct
{
    UINT16_S  platFormId;                                    /*վ̨ID*/
    UINT8_S   platFormKillPost[PLATFORM_NAME_BYTE_LEN];    /*վ̨���Ĺ����*/
    UINT16_S  segId;                                        /*վ̨����seg���*/
    UINT8_S   dir;                                        /*�߼�������վ̨�����ͣ������ķ���*/
}BnfPlatFormStruct;

/*
* ���������� ��PlatFormDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocPlatFormDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡPlatFormData����
* ����˵����
* ����ֵ  �� 
            BnfPlatFormStruct*
*/
BnfPlatFormStruct *GetPlatFormData(void);

/*
* ���������� ��ȡPlatFormData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfPlatFormStruct*
*/
BnfPlatFormStruct *GetPlatFormDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDPlatFormDataStru�Ľṹ���±�
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetPlatFormDataStruIndex(const UINT16_S platFormId);

/*
** ���������� ��ȡָ��IDPlatFormDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfPlatFormStruct* GetIndexIdPlatFormDataStru(const UINT16_S platFormId);

/*
** ���������� ��ȡָ��IDPlatFormDataStru��վ̨���Ĺ����
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: վ̨���Ĺ����
*/ 
UINT8_S* GetPlatFormDataStruplatFormKillPost(const UINT16_S platFormId);

/*
** ���������� ��ȡָ��IDPlatFormDataStru��վ̨����seg���
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨����seg���
*/ 
UINT16_S GetPlatFormDataStrusegId(const UINT16_S platFormId);

/*
** ���������� ��ȡָ��IDPlatFormDataStru���߼�������վ̨�����ͣ������ķ���
* ����˵���� const UINT16_S platFormId;վ̨ID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �߼�������վ̨�����ͣ������ķ���
*/ 
UINT8_S GetPlatFormDataStrudir(const UINT16_S platFormId);

/*
** ���������� ��ȡ��SEG��Ӧ��վ̨ID
* ����˵���� const UINT16_S segId;SEGID
*             UINT16_S* platFormIdBuff  վ̨ID
* ����ֵ  :  Oxff: ��ȡ����ʧ��
*            >=0: վ̨ID����
*/ 
UINT8_S GetSegIdBelongOfStationId(const UINT16_S* segIdBuff,UINT8_S segIdNum,UINT16_S* platFormIdBuff);

/*
* ���������� ���Ҵ˼��������Ƿ�����վ̨����
* ����˵���� const UINT16_S* pSegId;SEGIDָ��
* ����ֵ  :  1 ����
*             2 ������
*/ 
UINT8_S SearchStationBelongAxleSec(const UINT16_S* pSegId,UINT16_S includeSegNum);

/*
** ���������� ��ȡ��SEG��Ӧ��վ̨ID
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨����
*/ 
UINT8_S GetPlatformIdAccordSegBuff(const UINT16_S* pSegId,const UINT8_S segNum,UINT16_S* pPlatformId);

/*
** ���������� ��ȡ��SEG��Ӧ��վ̨ID
* ����˵���� const UINT16_S segId;SEGID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: վ̨ID
*/ 
UINT16_S GetPlatformIdAccordSegId(const UINT16_S segId);

#ifdef __cplusplus
}
#endif

#endif
