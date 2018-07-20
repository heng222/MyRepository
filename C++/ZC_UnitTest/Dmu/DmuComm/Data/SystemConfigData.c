/*************************************************
  �ļ���   ��SystemConfigData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SystemConfigData���ݹ���
			DmuCommonData�����SystemConfigData���ܿɷֽ����£�
			1��	��SystemConfigDataStru�ṹ��ָ�����ռ�
			2��	��ȡSystemConfigData����
			3��	��ȡSystemConfigData��Ϣ
			4��	��ȡָ��IDSystemConfigDataStru��ϵͳ��������ٶ�(km/h)
			5��	��ȡ��ʱ�����������(km/h)
			6��	��ȡNTPУʱʱ����.��������ʱ���뱾��ʱ���ʱ�����λ
			7��	��ȡ��ȫ��������.���ǵ�����������£����Ǳ�����о������·����¶ȵȣ��ƶ���Ȩ���ǵİ�ȫ��������
			8��	��ȡϵͳ������󱣻����γ��ȣ�cm��
			9��	��ȡseg�߼�����������
			10��	��ȡRM����ֵ
  ��ע    ���ޡ� 
*************************************************/

#include "SystemConfigData.h"
#include "../../../Common/Malloc.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfSystemConfigStruct* BnfSystemConfigDataStru = NULL;   /*����SystemConfigData���ݽṹ��*/
static UINT16_S LineNumSystemConfig = 0u;/*������*/


/*
* ���������� ��SystemConfigDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSystemConfigDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BnfSystemConfigDataStru))
    {
        BnfSystemConfigDataStru = (BnfSystemConfigStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSystemConfigStruct) * lineNum);
        LineNumSystemConfig = lineNum;
    }
}

/*
* ���������� ��ȡSystemConfigData����
* ����˵����
* ����ֵ  �� 
            BnfSystemConfigStruct*
*/
BnfSystemConfigStruct *GetSystemConfigData(void)
{
    return BnfSystemConfigDataStru;
}


/*
* ���������� ��ȡSystemConfigData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSystemConfigStruct*
*/
BnfSystemConfigStruct *GetSystemConfigDataInfo(UINT16_S* lineNum)
{

    BnfSystemConfigStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSystemConfig;
        retVal = BnfSystemConfigDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDSystemConfigDataStru��ϵͳ��������ٶ�(km/h)
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: ϵͳ��������ٶ�(km/h)
*/ 
UINT8_S GetSystemConfigDataStrumaxLineLimitSpeed(void)
{
    UINT8_S retVal = UINT8_NULL;/*��������ֵ*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].maxLineLimitSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}


/*
** ���������� ��ȡ��ʱ�����������(km/h)
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: ��ʱ�����������(km/h)
*/ 
UINT8_S GetSystemMaxTsrSpeed(void)
{
    UINT8_S retVal = UINT8_NULL;/*��������ֵ*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].maxTsrSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡNTPУʱʱ����.��������ʱ���뱾��ʱ���ʱ�����λ��ʱ����Ӧ��ʹ��ʱӦ����3600ת��Ϊ�롣
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: NTPУʱʱ����.��������ʱ���뱾��ʱ���ʱ�����λ��ʱ����Ӧ��ʹ��ʱӦ����3600ת��Ϊ�롣
*/ 
UINT8_S GetSystemNtpMimeZoneDifference(void)
{
    UINT8_S retVal = UINT8_NULL;/*��������ֵ*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].mimeZoneDifference;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡ��ȫ��������.���ǵ�����������£����Ǳ�����о������·����¶ȵȣ��ƶ���Ȩ���ǵİ�ȫ��������
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: ��ȫ��������.���ǵ�����������£����Ǳ�����о������·����¶ȵȣ��ƶ���Ȩ���ǵİ�ȫ��������
*/ 
UINT16_S GetSystemSafeBackDistance(void)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].safeBackDistance;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡϵͳ������󱣻����γ��ȣ�cm��
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: ϵͳ������󱣻����γ��ȣ�cm��
*/ 
UINT16_S GetSystemMaxOverlapLength(void)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].maxOverlapLength;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡseg�߼�����������
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: seg�߼�����������
*/ 
UINT8_S GetSystemSegLogicDirUpAndDown(void)
{
    UINT8_S retVal = UINT8_NULL;/*��������ֵ*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].segLogicDirUpAndDown;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡRM����ֵ
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: RM����ֵ
*/ 
UINT16_S GetSystemRmLimitSpeed(void)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    if (NULL != BnfSystemConfigDataStru)
    {
        retVal = BnfSystemConfigDataStru[0].rmLimitSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

