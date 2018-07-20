/*******************************************
* �ļ���	��  ZcSystemConfigData.c
* ��  ��	��  ZC��
* ����ʱ��	��  2015-5-25
* ��������	��	����ZcSystemConfigData���ݹ���
* ��  ע	��  ��
*******************************************/

#include "ZcSystemConfigData.h"
#include "../../../Dmu/Read/ReadDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Dmu/DmuComm/DataHandle/DmuCommDataTypeDefine.h"

static BnfZcSystemConfigStruct* gZcSystemConfigDataStru = NULL;   /*����ZcSystemConfigData���ݽṹ��*/
static UINT16_S gLineNumZcSystemConfig = 0U;/*������*/


/*******************************************
* ������	��
* ���������� ��ZcSystemConfigDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16 lineNum �����������
* ����ֵ  �� void
*/
void MallocZcSystemConfigDataStru(UINT16_S lineNum)
{
	if ((lineNum > 0U)&&(NULL == gZcSystemConfigDataStru))
	{
		gZcSystemConfigDataStru = (BnfZcSystemConfigStruct*)MemoryMalloc(((UINT32_S)(lineNum*sizeof(BnfZcSystemConfigStruct))));
		gLineNumZcSystemConfig = lineNum;
	}
}

/*******************************************
* ������	��
* ���������� ��ȡZcSystemConfigData����
* ����˵����
* ����ֵ  �� 
			BnfZcSystemConfigStruct*
*/
BnfZcSystemConfigStruct *GetZcSystemConfigData(void)
{
	return gZcSystemConfigDataStru;
}


/*******************************************
* ������	��
* ���������� ��ȡZcSystemConfigData��Ϣ
* ����˵�����������:UINT16* lineNum  ��������
* ����ֵ  �� 
			BnfZcSystemConfigStruct*
*/
BnfZcSystemConfigStruct *GetZcSystemConfigDataInfo(UINT16_S* lineNum)
{
    if (NULL != lineNum)
    {
        (*lineNum) = gLineNumZcSystemConfig;
    }
	
	return gZcSystemConfigDataStru;
}
/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSystemConfigDataStru���г�������о��루ms��
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: �г�������о��루ms��
*/ 
UINT16_S GetZcSystemConfigDataStrutrainMaxRecedeDis(void)
{
	UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].trainMaxRecedeDis;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡָ��IDZcSystemConfigDataStru����·��С���ܳ���(cm)
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: ��·��С���ܳ���(cm)
*/ 
UINT16_S GetZcSystemConfigDataStrulineMinTrainLength(void)
{
	UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].lineMinTrainLength;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡ��ӪҪ��ĵ�����γ���(cm)
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: ��ӪҪ��ĵ�����γ���(cm)
*/ 
UINT32_S GetZcSystemSectionLength(void)
{
	UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].sectionLength;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡǰ��ɸѡ������������
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: ǰ��ɸѡ������������
*/ 
UINT16_S GetZcSystemAxleSectionNum(void)
{
	UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].axleSectionNum;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡ�������η�ͨ�ų�ռ�������ж�ʱ�䣨ms��
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: �������η�ͨ�ų�ռ�������ж�ʱ�䣨ms��
*/ 
UINT32_S GetZcSystemRedunJudgmentTime(void)
{
	UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].redunJudgmentTime;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡ�߼�����ռ�ÿ�����λ��������
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*			<UINT8_NULL: ZC-CI�߼�����ռ�ÿ�����λ��������
*/ 
UINT8_S GetZcSystemFreeCodeNumSwitch(void)
{
	UINT8_S retVal = UINT8_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].freeCodeNumSwitch;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ��ȡ�г�CBTC�۷�ʱ�䣨ms��
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*			<UINT32_NULL: �г�CBTC�۷�ʱ�䣨ms��
*/ 
UINT32_S GetZcSystemTrainCbtcBackTime(void)
{
	UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].trainCbtcBackTime;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� �ж��źŻ���ѹ����
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*			<UINT16_NULL: �ж��źŻ���ѹ����
*/ 
UINT16_S GetZcSystemSignPressureDis(void)
{
	UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].signPressureDis;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

/*******************************************
* ������	��
** ���������� ׷�ٲ����󷽼����RM�г���ʽ
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*			<UINT8_NULL: ׷�ٲ����󷽼����RM�г���ʽ
*/ 
UINT8_S GetZcTrackRmTrainType(void)
{
	UINT8_S retVal = UINT8_NULL;/*��������ֵ*/
	if (NULL != gZcSystemConfigDataStru)
	{
		retVal = gZcSystemConfigDataStru[0].zcTrackRmTrainType;
	}
	else
	{
        /*������*/
	}
	return retVal;
}

