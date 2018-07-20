/*******************************************
* �ļ���	��  ZcCommConfigData.h
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	����ZcCommConfigData���ݹ���
* ��  ע	��  ��
*******************************************/
#ifndef ZC_COMM_CONFIG_DATA_H_
#define ZC_COMM_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ZCCOMMCONFIG_LINE_BYTE_NUM                   4U                          /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*ͨ�����ñ����ݽṹ��*/
typedef struct BnfZcCommConfigStruct
{
	UINT32_S  zcSendAtsDataCycle;						/*ZC��ATS������������ʱ��(ms)*/
}BnfZcCommConfigStruct;

/*******************************************
* ������	��  MallocZcCommConfigDataStru
* ��������	��	��ZcCommConfigDataStru�ṹ��ָ�����ռ�
* ���룺  UINT16_S lineNum �����������
* �����  ��
* ����ֵ��  ��
*******************************************/
void MallocZcCommConfigDataStru(UINT16_S lineNum);


/*******************************************
* ������	��  GetZcCommConfigData
* ��������	��	��ȡZcCommConfigData����
* ���룺  ��
* �����  ��
* ����ֵ��  BnfZcCommConfigStruct* ZcCommConfigData����ָ��
*******************************************/
BnfZcCommConfigStruct *GetZcCommConfigData(void);

/*******************************************
* ������	��  GetZcCommConfigDataInfo
* ��������	��	��ȡZcCommConfigData��Ϣ
* ���룺  ��
* �����  UINT16* lineNum  ��������
* ����ֵ�� BnfZcCommConfigStruct* ZcCommConfigData��Ϣָ��
*******************************************/
BnfZcCommConfigStruct *GetZcCommConfigDataInfo(UINT16_S* lineNum);

/*******************************************
* ������	��  GetZcCommConfigDataStruzcSendAtsDataCycle
* ��������	��	��ȡָ��IDZcCommConfigDataStru��ZC��ATS������������ʱ��(ms)
* ���룺  ��
* �����  ��
* ����ֵ��  UINT32_NULL: ��ȡ����ʧ��
*			!=UINT32_NULL: ZC��ATS������������ʱ��(ms)
*******************************************/
UINT32_S GetZcCommConfigDataStruzcSendAtsDataCycle(void);

#ifdef __cplusplus
}
#endif

#endif
