/*************************************************
  �ļ���   ��ShieldDoorData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� ShieldDoorData���ݹ���
			DmuCommonData�����ShieldDoorData���ܿɷֽ����£�
			1��	��ShieldDoorDataStru�ṹ��ָ�����ռ�
			2��	��ȡShieldDoorData����
			3��	��ȡShieldDoorData��Ϣ
			4��	��ȡָ��IDShieldDoorDataStru�Ľṹ���±�
			5��	��ȡָ��IDShieldDoorDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDShieldDoorDataStru������
			7��	��ȡָ��IDShieldDoorDataStru������վ̨���
			8��	��ȡ��·���������ID
			9��	��ѯվ̨���ȡ��վ̨��Ӧ��PSD��Ϣ
			10��	��ȡ��SEG��Ӧ��������ID
			11��	��ȡ��·����������ZC
			12��	��ȡ��·����������CI

  ��ע    ���ޡ�
 
*************************************************/
#ifndef SHIELDDOOR_DATA_H_
#define SHIELDDOOR_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SHIELDDOOR_NAME_BYTE_LEN                  12                            /*���Ƴ���*/
#define SHIELDDOOR_LINE_BYTE_NUM                  16                            /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�����ű����ݽṹ��*/
typedef struct BnfShieldDoorStruct
{
    UINT16_S  shieldDoorId;                        /*�������*/
    UINT8_S   name[SHIELDDOOR_NAME_BYTE_LEN];        /*����*/
    UINT16_S  stationId;                            /*����վ̨���*/

    /*��̬�����ֶ�*/
    UINT16_S  manageZCId;                            /*����ZC����ID*/
    UINT16_S  manageCIId;                            /*����CI����ID*/ 
    UINT16_S  segId;                                /*���ڵ�λ��ID*/
    UINT8_S   dir;                                /*�߼�������վ̨�����ͣ������ķ���*/
}BnfShieldDoorStruct;

/*
* ���������� ��ShieldDoorDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocShieldDoorDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡShieldDoorData����
* ����˵����
* ����ֵ  �� 
            BnfShieldDoorStruct*
*/
BnfShieldDoorStruct *GetShieldDoorData(void);

/*
* ���������� ��ȡShieldDoorData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfShieldDoorStruct*
*/
BnfShieldDoorStruct *GetShieldDoorDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDShieldDoorDataStru�Ľṹ���±�
* ����˵���� const UINT16_S shieldDoorId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetShieldDoorDataStruIndex(const UINT16_S shieldDoorId);

/*
** ���������� ��ȡָ��IDShieldDoorDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S shieldDoorId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfShieldDoorStruct* GetIndexIdShieldDoorDataStru(const UINT16_S shieldDoorId);

/*
** ���������� ��ȡָ��IDShieldDoorDataStru������
* ����˵���� const UINT16_S shieldDoorId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetShieldDoorDataStruname(const UINT16_S shieldDoorId);

/*
** ���������� ��ȡָ��IDShieldDoorDataStru������վ̨���
* ����˵���� const UINT16_S shieldDoorId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����վ̨���
*/ 
UINT16_S GetShieldDoorDataStrustationId(const UINT16_S shieldDoorId);

/*
* ���������� ��ȡ��·���������ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:���������ID
*/
UINT16_S GetLinePsdMaxId(void);

/*
* ���������� ��ѯվ̨���ȡ��վ̨��Ӧ��PSD��Ϣ
* ����˵���� ����:const UINT16_S stationId,վ̨ID
*             const UINT8_S stationIdNum   վ̨����
*             UINT16_S index    ����ƫ��                  
*             �������:UINT16_S psdIdBuff[],������ID����          
* ����ֵ  �� >=0:�����Ÿ���
*/
UINT16_S GetStationIdBelongofPsdInfo(const UINT16_S* stationIdBuff,const UINT8_S stationIdNum,UINT16_S index,UINT16_S psdIdBuff[]);

/*
** ���������� ��ȡ��SEG��Ӧ��������ID
* ����˵���� const UINT16_S pPlatformId;վ̨ID
*             const UINT8_S platformNum  վ̨ID����
*             UINT16_S*  pPsdId          ������IDָ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����Ÿ���
*/ 
UINT8_S GetPsdIdAccordPlatformIdBuff(const UINT16_S* pPlatformId,const UINT8_S platformNum,UINT16_S* pPsdId);

/*
* ���������� ��ȡ��·����������ZC
* ����˵���� const UINT16_S psdId,������ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLinePsdBelongZcId(const UINT16_S psdId);

/*
* ���������� ��ȡ��·����������CI
* ����˵���� const UINT16_S psdId,������ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIId
*/
UINT16_S GetLinePsdBelongCiId(const UINT16_S psdId);

#ifdef __cplusplus
}
#endif

#endif
