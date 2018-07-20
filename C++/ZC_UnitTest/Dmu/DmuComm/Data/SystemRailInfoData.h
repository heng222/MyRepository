/*************************************************
  �ļ���   ��SystemRailInfoData.h
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
#ifndef SYSTEMRAILINFO_DATA_H_
#define SYSTEMRAILINFO_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SYSTEMRAILINFO_LINE_BYTE_NUM                      7                        /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*��·������ṹ�嶨��*/
typedef struct BnfSystemRailInfoStruct
{
    UINT32_S disFrontToGetGrade;          /*��ͷǰ������¶ȼ��㷶Χ�����㳵ͷǰ��EBi��Ӧ������¶�ʱ,�ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm*/
    UINT16_S disBetweenToGetGrade;        /*��������¶ȼ��㷶Χ�����㳵��EBi��Ӧ������¶�ʱ, �ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm*/
    UINT8_S  minMarginFromEBI;            /*�Ƽ��ٶ���EBI����С��ֵ(km/h)*/
}BnfSystemRailInfoStruct;

/*
* ���������� ��SystemRailInfoDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSystemRailInfoDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡSystemRailInfoData����
* ����˵����
* ����ֵ  �� 
            BnfSystemRailInfoStruct*
*/
BnfSystemRailInfoStruct *GetSystemRailInfoData(void);

/*
* ���������� ��ȡSystemRailInfoData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSystemRailInfoStruct*
*/
BnfSystemRailInfoStruct *GetSystemRailInfoDataInfo(UINT16_S* lineNum);

/*
** ���������� ��ȡ��ͷǰ������¶ȼ��㷶Χ�����㳵ͷǰ��EBi��Ӧ������¶�ʱ,�ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
* ����˵��:  ��
* ����ֵ  :  UINT32_NULL: ��ȡ����ʧ��
*            <UINT32_NULL: ��ͷǰ������¶ȼ��㷶Χ�����㳵ͷǰ��EBi��Ӧ������¶�ʱ,�ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
*/ 
UINT32_S GetSystemRailDisFrontToGetGrade(void);

/*
** ���������� ��ȡ��������¶ȼ��㷶Χ�����㳵��EBi��Ӧ������¶�ʱ, �ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
* ����˵��:  ��
* ����ֵ  :  UINT16_NULL: ��ȡ����ʧ��
*            <UINT16_NULL: ��������¶ȼ��㷶Χ�����㳵��EBi��Ӧ������¶�ʱ, �ڳ�ͷǰ����Ѱ�ĳ��ȷ�Χ,��λcm
*/ 
UINT16_S GetSystemRailDisBetweenToGetGrade(void);

/*
** ���������� ��ȡ�Ƽ��ٶ���EBI����С��ֵ(km/h)
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*            <UINT8_NULL: �Ƽ��ٶ���EBI����С��ֵ(km/h)
*/ 
UINT8_S GetSystemRailMinMarginFromEBI(void);
#ifdef __cplusplus
}
#endif

#endif
