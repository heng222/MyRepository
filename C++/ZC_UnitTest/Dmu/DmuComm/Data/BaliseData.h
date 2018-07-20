/*************************************************
  �ļ���   ��BaliseData.h
  ����     ������      
  ����ʱ�� ��2016-8-11
  �������� �� BaliseData���ݹ���
			DmuCommonData�����BaliseData���ܿɷֽ����£�
			1��	��BaliseDataStru�ṹ��ָ�����ռ�
			2��	��ȡBaliseData����
			3��	��ȡBaliseData��Ϣ
			4��	��ȡָ��IDBaliseDataStru�Ľṹ���±�
			5��	��ȡָ��IDBaliseDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDBaliseDataStru������
			7��	��ȡָ��IDBaliseDataStru������seg���
			8��	��ȡָ��IDBaliseDataStru������Segƫ������cm��


  ��ע    ���ޡ�
 
*************************************************/
#ifndef BALISE_DATA_H_
#define BALISE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define BALISE_NAME_BYTE_LEN                 8                                /*���Ƴ���*/
#define BALISE_RELATE_MAX_NUM                10                                /*Ӧ��������Ӧ�����������*/
#define BALISE_LINE_BYTE_NUM                20                               /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*Ӧ���������ݽṹ��*/
typedef struct BnfBaliseStruct
{
    UINT16_S  indexId;                                            /*�������*/
    UINT32_S  baliseId;                                            /*Ӧ����ID*/
    UINT8_S   name[BALISE_NAME_BYTE_LEN];                            /*����*/
    UINT16_S  segId;                                               /*����seg���*/  
    UINT32_S  segOffset;                                            /*����Segƫ������cm��*/  
}BnfBaliseStruct;

/*
* ���������� ��BaliseDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocBaliseDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡBaliseData����
* ����˵����
* ����ֵ  �� 
            BnfBaliseStruct*
*/
BnfBaliseStruct *GetBaliseData(void);

/*
* ���������� ��ȡBaliseData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfBaliseStruct*
*/
BnfBaliseStruct *GetBaliseDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDBaliseDataStru�Ľṹ���±�
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetBaliseDataStruIndex(const UINT32_S baliseId);

/*
** ���������� ��ȡָ��IDBaliseDataStru�Ľṹ��ָ��
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfBaliseStruct* GetIndexIdBaliseDataStru(const UINT32_S baliseId);

/*
** ���������� ��ȡָ��IDBaliseDataStru������
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetBaliseDataStruname(const UINT32_S baliseId);

/*
** ���������� ��ȡָ��IDBaliseDataStru������seg���
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����seg���
*/ 
UINT16_S GetBaliseDataStrusegId(const UINT32_S baliseId);

/*
** ���������� ��ȡָ��IDBaliseDataStru������Segƫ������cm��
* ����˵���� const UINT32_S baliseId;Ӧ����ID
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����Segƫ������cm��
*/ 
UINT32_S GetBaliseDataStrusegOffset(const UINT32_S baliseId);




#ifdef __cplusplus
}
#endif

#endif
