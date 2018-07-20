/*************************************************
  �ļ���   ��ArData.h
  ����     ������      
  ����ʱ�� ��2016-8-10
  �������� �� ����ArData���ݹ���
				 DmuCommonData���ArData.c ���ܿɷֽ����£�
				1��	��ArDataStru�ṹ��ָ�����ռ�
				2��	 ��ȡArData����
				3��	��ȡArData��Ϣ
				4��	��ȡָ��IDArDataStru�Ľṹ���±�
				5��	��ȡָ��IDArDataStru�Ľṹ��ָ��
				6��	��ȡָ��IDArDataStru�������۷�����վ̨���
				7��	��ȡָ��IDArDataStru�Ľ�����Ӧͣ������
				8��	��ȡָ��IDArDataStru�Ļ��˵��Ӧͣ������
				9��	��ȡָ��IDArDataStru���˳�վ̨���
				10��	��ȡָ��IDArDataStru���˳����Ӧͣ������
				11��	��ȡָ��IDArDataStru�������۷���ID
				12��	��ȡָ��IDArDataStru�������۷���ťID
				13��	��ȡ��·�����۷���ť���ID
				14��	��ȡ��·�����۷���ťID��Ӧ�Ľ�����Ӧͣ������
				15��	 ��ȡ��·�����۷������ID
				16��	��ȡ��·�����۷���ID��Ӧ�Ľ�����Ӧͣ������
				17��	��ȡ��·�����۷���ť����ZCid
				18��	��ȡ��·�����۷���ť����CIid
				19��	��ȡ��·�����۷�������ZCID
				20��	��ȡ��·�����۷�������CIid
				21��	�жϴ�ͣ�����Ƿ��������۷����д���
				22��	�жϴ�ͣ�����Ƿ��������۷����е��˳�����

  ��ע    ���ޡ�
 
*************************************************/

#ifndef AR_DATA_H_
#define AR_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  AR_LINE_BYTE_NUM                   16                           /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*�����۷�������ݽṹ��*/
typedef struct BnfArStruct
{ 
    UINT16_S  arId;                            /*���*/
    UINT16_S  startPlartformId;                /*�����۷�����վ̨���*/
    UINT16_S  arInStopPointId;                /*������Ӧͣ������*/
    UINT16_S  revertPointId;                    /*���˵��Ӧͣ������*/
    UINT16_S  endPlartformId;                    /*�˳�վ̨���*/
    UINT16_S  aROutStopPointId;                /*�˳����Ӧͣ������*/
    UINT16_S  aRLampID;                        /*�����۷���ID*/
    UINT16_S  aRButtonId;                        /*�����۷���ťID*/

    /*��̬�����ֶ�*/
    UINT16_S  manageZCId;                        /*����ZC����ID*/
    UINT16_S  manageCIId;                        /*����CI����ID*/ 
}BnfArStruct;

/*
* �������ƣ�MallocArDataStru
* ���������� ��ArDataStru�ṹ��ָ�����ռ�
* ��������� UINT16_S lineNum �����������
* ��������� ��
* ����ֵ  �� void
*/
void MallocArDataStru(UINT16_S lineNum);


/*
* �������ƣ�GetArData
* ���������� ��ȡArData����
* ��������� ��
* ��������� ��
* ����ֵ  �� 
BnfArStruct*
*/
BnfArStruct *GetArData(void);

/*
* �������ƣ�GetArDataInfo
* ���������� ��ȡArData��Ϣ
* �����������
* �������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfArStruct* 
*/
BnfArStruct *GetArDataInfo(UINT16_S* lineNum);
/*
* �������ƣ�GetArDataStruIndex
* ���������� ��ȡָ��IDArDataStru�Ľṹ���±�
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/  
UINT16_S GetArDataStruIndex(const UINT16_S arId);

/*
* �������ƣ�GetIndexIdArDataStru
* ���������� ��ȡָ��IDArDataStru�Ľṹ��ָ��
* ���˲����� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfArStruct* GetIndexIdArDataStru(const UINT16_S arId);

/*
* �������ƣ�GetArDataStrustartPlartformId
* ���������� ��ȡָ��IDArDataStru�������۷�����վ̨���
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����۷�����վ̨���
*/ 
UINT16_S GetArDataStrustartPlartformId(const UINT16_S arId);

/*
* �������ƣ�GetArDataStruarInStopPointId
* ���������� ��ȡָ��IDArDataStru�Ľ�����Ӧͣ������
* ��������� const UINT16_S arId;���
* �����������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ������Ӧͣ������
*/ 
UINT16_S GetArDataStruarInStopPointId(const UINT16_S arId);

/*
* �������ƣ�GetArDataStrurevertPointId
* ���������� ��ȡָ��IDArDataStru�Ļ��˵��Ӧͣ������
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���˵��Ӧͣ������
*/ 
UINT16_S GetArDataStrurevertPointId(const UINT16_S arId);

/*
* �������ƣ�GetArDataStruendPlartformId
* ���������� ��ȡָ��IDArDataStru���˳�վ̨���
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �˳�վ̨���
*/ 
UINT16_S GetArDataStruendPlartformId(const UINT16_S arId);

/*
* �������ƣ�GetArDataStruaROutStopPointId
* ���������� ��ȡָ��IDArDataStru���˳����Ӧͣ������
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �˳����Ӧͣ������
*/ 
UINT16_S GetArDataStruaROutStopPointId(const UINT16_S arId);

/*
* �������ƣ�GetArDataStruaRLampID
* ���������� ��ȡָ��IDArDataStru�������۷���ID
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����۷���ID
*/ 
UINT16_S GetArDataStruaRLampID(const UINT16_S arId);

/*
* �������ƣ�GetArDataStruaRButtonId
* ���������� ��ȡָ��IDArDataStru�������۷���ťID
* ��������� const UINT16_S arId;���
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����۷���ťID
*/ 
UINT16_S GetArDataStruaRButtonId(const UINT16_S arId);

/*
* �������ƣ�GetLineDrButtonMaxId
* ���������� ��ȡ��·�����۷���ť���ID
* ��������� ��
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�����۷���ť���ID
*/
UINT16_S GetLineDrButtonMaxId(void);

/*
* �������ƣ�GetLineDrButtonBelongPointId
* ���������� ��ȡ��·�����۷���ťID��Ӧ�Ľ�����Ӧͣ������
* ��������� const UINT16_S arButtonId   �����۷���ťID
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:������Ӧͣ������
*/
UINT16_S GetLineDrButtonBelongPointId(const UINT16_S arButtonId);

/*
* �������ƣ�GetLineDrLampMaxId
* ���������� ��ȡ��·�����۷������ID
* ��������� ��
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�����۷������ID
*/
UINT16_S GetLineDrLampMaxId(void);

/*
* �������ƣ�GetLineDrLampBelongPointId
* ���������� ��ȡ��·�����۷���ID��Ӧ�Ľ�����Ӧͣ������
* ��������� const UINT16_S arLampID   �����۷���ID
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:������Ӧͣ������
*/
UINT16_S GetLineDrLampBelongPointId(const UINT16_S arLampID);

/*
* �������ƣ�GetLineDrButtonBelongZcId
* ���������� ��ȡ��·�����۷���ť����ZCid
* ��������� const UINT16_S drButtonId,�����۷���ť
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCid
*/
UINT16_S GetLineDrButtonBelongZcId(const UINT16_S drButtonId);

/*
* �������ƣ�GetLineDrButtonBelongCiId
* ���������� ��ȡ��·�����۷���ť����CIid
* ��������� const UINT16_S drButtonId,�����۷���ť
* �����������
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIid
*/
UINT16_S GetLineDrButtonBelongCiId(const UINT16_S drButtonId);

/*
* �������ƣ�GetLineDrLampBelongZcId
* ���������� ��ȡ��·�����۷�������ZCID
* ��������� const UINT16_S drLampId,�����۷���ID
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCID
*/
UINT16_S GetLineDrLampBelongZcId(const UINT16_S drLampId);

/*
* �������ƣ�GetLineDrLampBelongCiId
* ���������� ��ȡ��·�����۷�������CIid
* ��������� const UINT16_S drLampId,�����۷���ID
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIid
*/
UINT16_S GetLineDrLampBelongCiId(const UINT16_S drLampId);

/*
** ���������� �жϴ�ͣ�����Ƿ��������۷����д���
* ����˵���� const UINT16_S arId;���
* ����ֵ  :  0:������
*             1:����
*/ 
UINT8_S CheckSopPointIsAr(const UINT16_S stopPointId);

/*
* �������ƣ�CheckSopPointIsAr
* ���������� �жϴ�ͣ�����Ƿ��������۷����д���
* ��������� const UINT16_S arId;���
* �����������
* ����ֵ  :  0:������
*             1:����
*/ 
UINT8_S CheckSopPointIsExitAr(const UINT16_S stopPointId);

#ifdef __cplusplus
}
#endif

#endif
