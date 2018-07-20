/*************************************************
  �ļ���   ��StaticResSpeedData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� StaticResSpeedData���ݹ���
			DmuCommonData�����StaticResSpeedData���ܿɷֽ����£�
			1��	��StaticResSpeedDataStru�ṹ��ָ�����ռ�
			2��	��ȡStaticResSpeedData����
			3��	��ȡStaticResSpeedData��Ϣ
			4��	��ȡָ��IDStaticResSpeedDataStru�Ľṹ���±�
			5��	 ��ȡָ��IDStaticResSpeedDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDStaticResSpeedDataStru�ĸ�������������Seg���
			7��	��ȡָ��IDStaticResSpeedDataStru���������Segƫ����(cm)
			8��	 ��ȡָ��IDStaticResSpeedDataStru���յ�����Segƫ����(cm)
			9��	��ȡָ��IDStaticResSpeedDataStru�ľ�̬����ֵ
			10��	��ȡָ����SEGID��ȡ�����Ϣ
  ��ע    ���ޡ�
 
*************************************************/
#ifndef STATICRESSPEED_DATA_H_
#define STATICRESSPEED_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  STATICRESSPEED_LINE_BYTE_NUM        16                   /*һ�����ݵ��ֽ���*/

#ifdef __cplusplus
extern "C" {
#endif

/*��̬���ٱ�*/
typedef struct BnfStaticResSpeedStruct
{ 
    UINT16_S  staticResSpeedId;                /*���*/
    UINT16_S  segId;                            /*��������������Seg���*/
    UINT32_S  orgnSegOfst;                    /*�������Segƫ����(cm)*/
    UINT32_S  tmnlSegOfst;                    /*�յ�����Segƫ����(cm)*/
    UINT16_S  relateSwitchId;                    /*��������ID*/
    UINT16_S  staticSpeed;                    /*��̬����ֵ*/
}BnfStaticResSpeedStruct;

/*
* ���������� ��StaticResSpeedDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocStaticResSpeedDataStru(UINT16_S lineNum);

/*
* ���������� ��ȡStaticResSpeedData����
* ����˵����
* ����ֵ  �� 
            BnfStaticResSpeedStruct*
*/
BnfStaticResSpeedStruct *GetStaticResSpeedData(void);

/*
* ���������� ��ȡStaticResSpeedData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfStaticResSpeedStruct*
*/
BnfStaticResSpeedStruct *GetStaticResSpeedDataInfo(UINT16_S* lineNum);
/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru�Ľṹ���±�
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetStaticResSpeedDataStruIndex(const UINT16_S staticResSpeedId);

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStaticResSpeedStruct* GetIndexIdStaticResSpeedDataStru(const UINT16_S staticResSpeedId);

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru�ĸ�������������Seg���
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������������Seg���
*/ 
UINT16_S GetStaticResSpeedDataStrusegId(const UINT16_S staticResSpeedId);

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru���������Segƫ����(cm)
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Segƫ����(cm)
*/ 
UINT32_S GetStaticResSpeedDataStruorgnSegOfst(const UINT16_S staticResSpeedId);

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru���յ�����Segƫ����(cm)
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Segƫ����(cm)
*/ 
UINT32_S GetStaticResSpeedDataStrutmnlSegOfst(const UINT16_S staticResSpeedId);

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru�ľ�̬����ֵ
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��̬����ֵ
*/ 
UINT16_S GetStaticResSpeedDataStrustaticSpeed(const UINT16_S staticResSpeedId);

/*
* ���������� ��ȡָ����SEGID��ȡ�����Ϣ
* ����˵���� �������:const UINT16_S segId;���
*                      const UINT32_S startOffset  ���ƫ����
*                      const UINT32_S endOffset    �յ�ƫ����
*             �������:UINT16_S* limitSpeed  ����ֵ
* ����ֵ  :  0: ��ȡ����ʧ��
*             1: ���ҳɹ�
*/ 
UINT8_S GetSegIdOfLimitSpeed(const UINT16_S segId,const UINT32_S startOffset,const UINT32_S endOffset,UINT16_S* limitSpeed);

#ifdef __cplusplus
}
#endif

#endif
