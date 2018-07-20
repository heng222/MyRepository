/*************************************************
  �ļ���   ��SignData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SignData���ݹ���
			DmuCommonData�����SignData���ܿɷֽ����£�
			1��	��SignDataStru�ṹ��ָ�����ռ�
			2��	��ȡSignData����
			3��	��ȡSignData��Ϣ
			4��	��ȡָ��IDSignDataStru�Ľṹ���±�
			5��	��ȡָ��IDSignDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDSignDataStru���źŻ�����
			7��	��ȡָ��IDSignDataStru������
			8��	 ��ȡָ��IDSignDataStru������
			9��	��ȡָ��IDSignDataStru������seg���
			10��	 ��ȡָ��IDSignDataStru������Segƫ������cm��
			11��	��ȡָ��IDSignDataStru�ķ�������
			12��	��ȡָ��IDSignDataStru�ĵ�����Ϣ
			13��	��ȡ��·�źŻ����ID
			14��	�����������ǲ�ѯ��ǰSEG��ָ������������źŻ���Ϣ
			15��	��ȡ��·�źŻ�����ZC
			16��	��ȡ��·�źŻ�����CI
  ��ע    ���ޡ�
 
*************************************************/
#ifndef SIGN_DATA_H_
#define SIGN_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SIGN_NAME_LEN                      12                           /*�źŻ������ֽ���*/
#define SIGN_LINE_BYTE_NUM                 29                            /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�źŻ������ݽṹ��*/
typedef struct BnfSignStruct
{ 
    UINT16_S signId;                                /*�������*/
    UINT8_S  signName [SIGN_NAME_LEN];            /*�źŻ�����*/
    UINT16_S signType;                            /*����*/
    UINT16_S signProperty;                        /*����*/
    UINT16_S signProtectSegId;                    /*������������seg���*/
    UINT32_S signProtectSegOffset;                /*������������Segƫ������cm��*/
    UINT8_S protectiveDir;                        /*��������*/
    UINT32_S lightInfo;                            /*������Ϣ*/

    /*��̬�����ֶ�*/
    UINT16_S signSegId;                            /*����seg���*/
    UINT32_S signSegOffset;                        /*����Segƫ������cm��*/
    UINT16_S  manageZCId;                            /*����ZC����ID*/
    UINT16_S  manageCIId;                            /*����CI����ID*/ 
}BnfSignStruct;    

/*
* ���������� ��SignDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSignDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡSignData����
* ����˵����
* ����ֵ  �� 
            BnfSignStruct*
*/
BnfSignStruct *GetSignData(void);

/*
* ���������� ��ȡSignData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSignStruct*
*/
BnfSignStruct *GetSignDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDSignDataStru�Ľṹ���±�
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSignDataStruIndex(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSignStruct* GetIndexIdSignDataStru(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru���źŻ�����
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: �źŻ�����
*/ 
UINT8_S* GetSignDataStrusignName(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru������
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����
*/ 
UINT16_S GetSignDataStrusignType(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru������
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����
*/ 
UINT16_S GetSignDataStrusignProperty(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru������seg���
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT16_S GetSignDataStrusignSegId(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru������Segƫ������cm��
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����Segƫ������cm��
*/ 
UINT32_S GetSignDataStrusignSegOffset(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru��������������seg���
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT16_S GetSignDataStrusignProSegId(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru��������������Segƫ������cm��
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����Segƫ������cm��
*/ 
UINT32_S GetSignDataStrusignProSegOffset(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru�ķ�������
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������
*/ 
UINT8_S GetSignDataStruprotectiveDir(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru�ĵ�����Ϣ
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ������Ϣ
*/ 
UINT32_S GetSignDataStrulightInfo(const UINT16_S signId);

/*
* ���������� ��ȡ��·�źŻ����ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�źŻ����ID
*/
UINT16_S GetLineSignalMaxId(void);

/*
* �������ܣ������������ǲ�ѯ��ǰSEG��ָ������������źŻ���Ϣ��
* ��ڲ�����UINT16 segId                seg���
*            UINT8_S  dir                    ���з���
* ���ڲ�����UINT16 findSignalIDBuff[]        �ҵ����źŻ�ID
*            UINT8_S* fingNum              ���ҵ��źŻ��ĸ���
* ����ֵ��  UINT8_S retVal 
*            ��ѯ�ɹ�:��ǰSEG�����źŻ�������0;
*            ��ѯ�ɹ�:��ǰSEG�ϴ����źŻ�������1      
*******************************************************************************************/
UINT8_S FindCurrentSegSignal(UINT16_S segId, UINT8_S dir, UINT16_S findSignalIDBuff[],UINT8_S* fingNum);

/*
* ���������� ��ȡ��·�źŻ�����ZC
* ����˵���� const UINT16_S signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLineSignalBelongZcId(const UINT16_S signalId);

/*
* ���������� ��ȡ��·�źŻ�����CI
* ����˵���� const UINT16_S signalId,�źŻ�ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIId
*/
UINT16_S GetLineSignalBelongCiId(const UINT16_S signalId);

/*
** ���������� ��ȡָ��IDSignDataStru�ķ���seg���
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT16_S GetSignDataStrusignProtectSegId(const UINT16_S signId);

/*
** ���������� ��ȡָ��IDSignDataStru�ķ���segƫ����
* ����˵���� const UINT16_S signId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT32_S GetSignDataStrusignProtectSegOffset(const UINT16_S signId);

#ifdef __cplusplus
}
#endif

#endif
