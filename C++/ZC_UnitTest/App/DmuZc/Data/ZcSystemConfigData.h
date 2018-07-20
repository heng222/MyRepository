/*******************************************
* �ļ���	��  ZcSystemConfigData.h
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	����ZcSystemConfigData���ݹ���
* ��  ע	��  ��
*******************************************/
#ifndef ZCSYSTEMCONFIG_DATA_H_
#define ZCSYSTEMCONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ZCSYSTEMCONFIG_LINE_BYTE_NUM                   22U                         /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*ZCϵͳ���ñ����ݽṹ��*/
typedef struct BnfZcSystemConfigStruct
{
	UINT16_S  trainMaxRecedeDis;						/*�г�������о��루ms��*/
	UINT16_S  lineMinTrainLength;						/*��·��С���ܳ���(cm)*/
	UINT32_S  sectionLength;							/*��ӪҪ��ĵ�����γ���(cm)*/
	UINT16_S  axleSectionNum;							/*ǰ��ɸѡ������������*/
	UINT32_S  redunJudgmentTime;						/*�������η�ͨ�ų�ռ�������ж�ʱ�䣨ms��*/
	UINT8_S  freeCodeNumSwitch;						/*ZC-CI�߼�����ռ�ÿ�����λ��������*/
	UINT32_S  trainCbtcBackTime;						/*�г�CBTC�۷�ʱ�䣨ms��*/
	UINT16_S  signPressureDis;						/*�ж��źŻ���ѹ����(cm)*/
	UINT8_S  zcTrackRmTrainType;                      /*׷�ٲ����󷽼����RM�г���ʽ*/
}BnfZcSystemConfigStruct;

/*******************************************
* ������	��
* ���������� ��ZcSystemConfigDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16 lineNum �����������
* ����ֵ  �� void
*/
void MallocZcSystemConfigDataStru(UINT16_S lineNum);

/*******************************************
* ������	��
* ���������� ��ȡZcSystemConfigData����
* ����˵����
* ����ֵ  �� 
			BnfZcSystemConfigStruct*
*/
BnfZcSystemConfigStruct *GetZcSystemConfigData(void);

/*******************************************
* ������	��
* ���������� ��ȡZcSystemConfigData��Ϣ
* ����˵�����������:UINT16* lineNum  ��������
* ����ֵ  �� 
			BnfZcSystemConfigStruct*
*/
BnfZcSystemConfigStruct *GetZcSystemConfigDataInfo(UINT16_S* lineNum);

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSystemConfigDataStru���г�������о��루ms��
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: �г�������о��루ms��
*/ 
UINT16_S GetZcSystemConfigDataStrutrainMaxRecedeDis(void);

/*******************************************
* ������	��
** ���������� ��ȡ��·��С���ܳ���(cm)
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: ��·��С���ܳ���(cm)
*/ 
UINT16_S GetZcSystemLineMinTrainLength(void);

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSystemConfigDataStru����·��С���ܳ���(cm)
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: ��·��С���ܳ���(cm)
*/ 
UINT16_S GetZcSystemConfigDataStrulineMinTrainLength(void);

/*******************************************
* ������	��
** ���������� ��ȡ��ӪҪ��ĵ�����γ���(cm)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: ��ӪҪ��ĵ�����γ���(cm)
*/ 
UINT32_S GetZcSystemSectionLength(void);

/*******************************************
* ������	��
** ���������� ��ȡǰ��ɸѡ������������
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: ǰ��ɸѡ������������
*/ 
UINT16_S GetZcSystemAxleSectionNum(void);
/*******************************************
* ������	��
** ���������� ��ȡ�������η�ͨ�ų�ռ�������ж�ʱ�䣨ms��
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: �������η�ͨ�ų�ռ�������ж�ʱ�䣨ms��
*/ 
UINT32_S GetZcSystemRedunJudgmentTime(void);

/*******************************************
* ������	��
** ���������� ��ȡ�߼�����ռ�ÿ�����λ��������
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*			<UINT8_NULL: ZC-CI�߼�����ռ�ÿ�����λ��������
*/ 
UINT8_S GetZcSystemFreeCodeNumSwitch(void);

/*******************************************
* ������	��
** ���������� ��ȡ�г�CBTC�۷�ʱ�䣨ms��
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: �г�CBTC�۷�ʱ�䣨ms��
*/ 
UINT32_S GetZcSystemTrainCbtcBackTime(void);

/*******************************************
* ������	��
** ���������� �ж��źŻ���ѹ����
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: �ж��źŻ���ѹ����
*/ 
UINT16_S GetZcSystemSignPressureDis(void);

/*******************************************
* ������	��
** ���������� ׷�ٲ����󷽼����RM�г���ʽ
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*			<UINT8_NULL: ׷�ٲ����󷽼����RM�г���ʽ
*/ 
UINT8_S GetZcTrackRmTrainType(void);

#ifdef __cplusplus
}
#endif

#endif
