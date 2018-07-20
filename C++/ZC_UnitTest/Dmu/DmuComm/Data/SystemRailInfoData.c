/*************************************************
  �ļ���   ��SystemRailInfoData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SystemRailInfoData���ݹ���
			DmuCommonData�����SystemRailInfoData���ܿɷֽ����£�
			1��	��SystemRailInfoDataStru�ṹ��ָ�����ռ�
			2��	��ȡSystemRailInfoData����
			3��	��ȡSystemRailInfoData��Ϣ
			4��	��ȡ��ͷǰ������¶ȼ��㷶Χ�����㳵ͷǰ��EBi��Ӧ������¶�ʱ,�ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
			5��	��ȡ��������¶ȼ��㷶Χ�����㳵��EBi��Ӧ������¶�ʱ,
			6��	��ȡ�Ƽ��ٶ���EBI����С��ֵ(km/h)

  ��ע    ���ޡ� 
*************************************************/

#include "SystemRailInfoData.h"
#include "../../../Common/Malloc.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfSystemRailInfoStruct* SystemRailInfoDataStru = NULL;   /*����SystemRailInfoData���ݽṹ��*/
static UINT16_S LineNumSystemRailInfo = 0u;/*������*/


/*
* ���������� ��SystemRailInfoDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSystemRailInfoDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SystemRailInfoDataStru))
    {
        SystemRailInfoDataStru = (BnfSystemRailInfoStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSystemRailInfoStruct) * lineNum);
        LineNumSystemRailInfo = lineNum;
    }
}

/*
* ���������� ��ȡSystemRailInfoData����
* ����˵����
* ����ֵ  �� 
            BnfSystemRailInfoStruct*
*/
BnfSystemRailInfoStruct *GetSystemRailInfoData(void)
{
    return SystemRailInfoDataStru;
}


/*
* ���������� ��ȡSystemRailInfoData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSystemRailInfoStruct*
*/
BnfSystemRailInfoStruct *GetSystemRailInfoDataInfo(UINT16_S* lineNum)
{

    BnfSystemRailInfoStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSystemRailInfo;
        retVal = SystemRailInfoDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡ��ͷǰ������¶ȼ��㷶Χ�����㳵ͷǰ��EBi��Ӧ������¶�ʱ,�ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ��ͷǰ������¶ȼ��㷶Χ�����㳵ͷǰ��EBi��Ӧ������¶�ʱ,�ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
*/ 
UINT32_S GetSystemRailDisFrontToGetGrade(void)
{
    UINT32_S retVal = UINT32_NULL;/*��������ֵ*/
    if (NULL != SystemRailInfoDataStru)
    {
        retVal = SystemRailInfoDataStru[0].disFrontToGetGrade;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡ��������¶ȼ��㷶Χ�����㳵��EBi��Ӧ������¶�ʱ, �ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: ��������¶ȼ��㷶Χ�����㳵��EBi��Ӧ������¶�ʱ, �ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
*/ 
UINT16_S GetSystemRailDisBetweenToGetGrade(void)
{
    UINT16_S retVal = UINT16_NULL;/*��������ֵ*/
    if (NULL != SystemRailInfoDataStru)
    {
        retVal = SystemRailInfoDataStru[0].disBetweenToGetGrade;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡ�Ƽ��ٶ���EBI����С��ֵ(km/h)
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: �Ƽ��ٶ���EBI����С��ֵ(km/h)
*/ 
UINT8_S GetSystemRailMinMarginFromEBI(void)
{
    UINT8_S retVal = UINT8_NULL;/*��������ֵ*/
    if (NULL != SystemRailInfoDataStru)
    {
        retVal = SystemRailInfoDataStru[0].minMarginFromEBI;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

