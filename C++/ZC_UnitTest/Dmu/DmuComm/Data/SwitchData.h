/*************************************************
  �ļ���   ��SwitchData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SwitchData���ݹ���
			DmuCommonData�����SwitchData���ܿɷֽ����£�
			1��	��SwitchDataStru�ṹ��ָ�����ռ�
			2��	��ȡSwitchData����
			3��	��ȡSwitchData��Ϣ
			4��	��ȡָ��IDSwitchDataStru�Ľṹ���±�
			5��	��ȡָ��IDSwitchDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDSwitchDataStru�ĵ�������
			7��	��ȡָ��IDSwitchDataStru������������
			8��	��ȡָ��IDSwitchDataStru�ķ���
			9��	��ȡָ��IDSwitchDataStru�Ķ�λSegID
			10��	��ȡָ��IDSwitchDataStru�ķ�λSegID
			11��	��ȡָ��IDSwitchDataStru������SegID
			12��	��ȡָ��IDSwitchDataStru�ĵ���λ��̬�����ٶ�(cm/s)
			13��	���������SEGID��ȡ���������
			14��	��ȡ��·�������ID
			15��	���������SEGID��ȡ������Ϣ
			16��	���������SEGID��ȡ���������
			17��	��ȡ��·��������ZC
			18��	��ȡ��·��������CI
  ��ע    ���ޡ�
 
*************************************************/
#ifndef SWITCH_DATA_H_
#define SWITCH_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SWITCH_NAME_LEN                      16                                /*���������ֽ���*/
#define SWITCH_LINE_BYTE_NUM                 30                                /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�������ݽṹ��*/
typedef struct BnfSwitchStruct
{
    UINT16_S switchId;                        /*������*/
    UINT8_S  switchName [SWITCH_NAME_LEN];    /*��������*/
    UINT16_S switchOtherId;                   /*����������*/
    UINT16_S dir;                                /*����*/
    UINT16_S locSegId;                        /*��λSegID*/
    UINT16_S antiSegId;                        /*��λSegID*/
    UINT16_S joinSegId;                        /*���SegID*/
    UINT16_S switchSideResSpeed;                /*����λ��̬�����ٶ�(cm/s)*/

    /*��̬�����ֶ�*/
    UINT32_S    locSegOffset;                    /*��λ�����ƫ����*/
    UINT32_S    antiSegOffset;                    /*��λ�����ƫ����*/
    UINT32_S    joinSegOffset;                    /*��ϵ����ƫ����*/
    UINT16_S  manageZCId;                        /*����ZC����ID*/
    UINT16_S  manageCIId;                        /*����CI����ID*/ 
}BnfSwitchStruct;    

/*
* ���������� ��SwitchDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSwitchDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡSwitchData����
* ����˵����
* ����ֵ  �� 
            BnfSwitchStruct*
*/
BnfSwitchStruct *GetSwitchData(void);

/*
* ���������� ��ȡSwitchData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSwitchStruct*
*/
BnfSwitchStruct *GetSwitchDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDSwitchDataStru�Ľṹ���±�
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSwitchDataStruIndex(const UINT16_S switchId);

/*
** ���������� ��ȡָ��IDSwitchDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSwitchStruct* GetIndexIdSwitchDataStru(const UINT16_S switchId);

/*
** ���������� ��ȡָ��IDSwitchDataStru�ĵ�������
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��������
*/ 
UINT8_S* GetSwitchDataStruswitchName(const UINT16_S switchId);

/*
** ���������� ��ȡָ��IDSwitchDataStru������������
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����������
*/ 
UINT16_S GetSwitchDataStruswitchOtherId(const UINT16_S switchId);

/*
** ���������� ��ȡָ��IDSwitchDataStru�ķ���
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����
*/ 
UINT16_S GetSwitchDataStrudir(const UINT16_S switchId);

/*
** ���������� ��ȡָ��IDSwitchDataStru�Ķ�λSegID
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��λSegID
*/ 
UINT16_S GetSwitchDataStrulocSegId(const UINT16_S switchId);

/*
** ���������� ��ȡָ��IDSwitchDataStru�ķ�λSegID
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��λSegID
*/ 
UINT16_S GetSwitchDataStruantiSegId(const UINT16_S switchId);

/*
** ���������� ��ȡָ��IDSwitchDataStru������SegID
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*             1: ��ȡ���ݳɹ�
*/ 
UINT8_S GetSwitchDataStruSegIdInfo(const UINT16_S switchId,UINT16_S* locSegId,UINT16_S* antiSegId,UINT16_S* joinSegId);

/*
** ���������� ��ȡָ��IDSwitchDataStru�ĵ���λ��̬�����ٶ�(cm/s)
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����λ��̬�����ٶ�(cm/s)
*/ 
UINT16_S GetSwitchDataStruswitchSideResSpeed(const UINT16_S switchId);

/*
** ���������� ���������SEGID��ȡ���������
* ����˵���� const UINT16_S* pSegId;SEGIDָ��ָ��
             const UINT16_S segIdNum;SEGID����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������
*/ 
UINT16_S GetSegIdOfSwitchIdNum(const UINT16_S* pSegId,const UINT16_S segIdNum);

/*
* ���������� ��ȡ��·�������ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�������ID
*/
UINT16_S GetLineSwitchMaxId(void);

/*
** ���������� ���������SEGID��ȡ������Ϣ
* ����˵���� ����:const UINT16_S segId,SEGID
*             const UINT8_S segIdNum    SEGID����
*             UINT16_S index    ����ƫ��                  
*             �������:UINT16_S switchIdBuff[],����ID����      
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������
*/ 
UINT16_S GetSegIdBelongofSwitchInfo(const UINT16_S* segIdBuff,const UINT8_S segIdNum,UINT16_S index,UINT16_S switchIdBuff[]);

/*
** ���������� ���������SEGID��ȡ���������
* ����˵���� const UINT16_S* pSegId;SEGIDָ��ָ��
             const UINT16_S segIdNum;SEGID����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������
*/ 
UINT8_S GetSegIdBuffOfSwitchInfo(const UINT16_S* pSegId,const UINT16_S segIdNum,UINT16_S switchIdBuff[]);

/*
* ���������� ��ȡ��·��������ZC
* ����˵���� const UINT16_S switchId,����ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLineSwitchBelongZcId(const UINT16_S switchId);

/*
* ���������� ��ȡ��·��������CI
* ����˵���� const UINT16_S switchId,����ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIId
*/
UINT16_S GetLineSwitchBelongCiId(const UINT16_S switchId);

#ifdef __cplusplus
}
#endif

#endif
