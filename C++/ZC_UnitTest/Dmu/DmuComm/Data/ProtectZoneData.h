/*************************************************
  �ļ���   ��ProtectZoneData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� ProtectZoneData���ݹ���
			DmuCommonData�����ProtectZoneData���ܿɷֽ����£�
			1��	��ProtectZoneDataStru�ṹ��ָ�����ռ�
			2��	��ȡProtectZoneData����
			3��	��ȡProtectZoneData��Ϣ
			4��	��ȡָ��IDProtectZoneDataStru�Ľṹ���±�
			5��	��ȡָ��IDProtectZoneDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDProtectZoneDataStru�İ����ļ���������Ŀ
			7��	��ȡָ��IDProtectZoneDataStru�İ����ļ������α��
			8��	��ȡ��·�����������ID
			9��	��ȡ�������ΰ����ļ���������Ϣ
			10��	��ȡ��·������������ZC
			11��	��ȡ��·�����������ID
  ��ע    ���ޡ�
 
*************************************************/
#ifndef PROTECTZONE_DATA_H_
#define PROTECTZONE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define PROTECTZONE_AXLESGM_MAX_NUM               4                                            /*�����������ε������Ŀ*/
#define PROTECTZONE_LINE_BYTE_NUM                 12                                        /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�������α����ݽṹ��*/
typedef struct BnfProtectZoneStruct
{
    UINT16_S  protectZoneId;                                                /*�������*/
    UINT16_S  includeAxleSgmtNum;                                            /*�����ļ���������Ŀ*/
    UINT16_S  includeAxleSgmtId[PROTECTZONE_AXLESGM_MAX_NUM];                /*�����ļ������α��*/

    /*��̬�����ֶ�*/
    UINT16_S  manageZCId;                                                    /*����ZC����ID*/
    UINT16_S  manageCIId;                                                    /*����CI����ID*/ 
}BnfProtectZoneStruct;

/*
* ���������� ��ProtectZoneDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocProtectZoneDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡProtectZoneData����
* ����˵����
* ����ֵ  �� 
            BnfProtectZoneStruct*
*/
BnfProtectZoneStruct *GetProtectZoneData(void);

/*
* ���������� ��ȡProtectZoneData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfProtectZoneStruct*
*/
BnfProtectZoneStruct *GetProtectZoneDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDProtectZoneDataStru�Ľṹ���±�
* ����˵���� const UINT16_S protectZoneId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetProtectZoneDataStruIndex(const UINT16_S protectZoneId);

/*
** ���������� ��ȡָ��IDProtectZoneDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S protectZoneId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfProtectZoneStruct* GetIndexIdProtectZoneDataStru(const UINT16_S protectZoneId);

/*
** ���������� ��ȡָ��IDProtectZoneDataStru�İ����ļ���������Ŀ
* ����˵���� const UINT16_S protectZoneId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����ļ���������Ŀ
*/ 
UINT16_S GetProtectZoneDataStruincludeAxleSgmtNum(const UINT16_S protectZoneId);

/*
** ���������� ��ȡָ��IDProtectZoneDataStru�İ����ļ������α��
* ����˵���� const UINT16_S protectZoneId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �����ļ������α��
*/ 
UINT16_S* GetProtZoDataInAxleSgmtId(const UINT16_S protectZoneId);

/*
* ���������� ��ȡ��·�����������ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0: ��·�����������ID
*/
UINT16_S GetLineOverlapMaxId(void);

/*
* ���������� ��ȡ�������ΰ����ļ���������Ϣ
* ����˵���� const UINT16_S protectZoneId,��������ID
*            UINT16_S* pAcIdBuf����������ID����
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:������������
*/
UINT16_S GetLineOverlapOfAcInfo(const UINT16_S protectZoneId,UINT16_S* pAcIdBuf);

/*
* ���������� ��ȡ��·������������ZC
* ����˵���� const UINT16_S overlapId,��������ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLineOverlapBelongZcId(const UINT16_S overlapId);

/*
* ���������� ��ȡ��·�����������ID
����CI
* ����˵���� const UINT16_S overlapId,��������ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ciId
*/
UINT16_S GetLineOverlapBelongCiId(const UINT16_S overlapId);

#ifdef __cplusplus
}
#endif

#endif
