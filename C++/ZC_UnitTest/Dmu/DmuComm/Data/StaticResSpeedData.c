/*************************************************
  �ļ���   ��StaticResSpeedData.c
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

#include "StaticResSpeedData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfStaticResSpeedStruct* StaticResSpeedDataStru = NULL;   /*����StaticResSpeedData���ݽṹ��*/
static UINT16_S LineNumStaticResSpeed = 0u;/*������*/


/*
* ���������� ��StaticResSpeedDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocStaticResSpeedDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == StaticResSpeedDataStru))
    {
        StaticResSpeedDataStru = (BnfStaticResSpeedStruct*)MemoryMalloc((UINT32_S)sizeof(BnfStaticResSpeedStruct) * lineNum);
        LineNumStaticResSpeed = lineNum;
    }
}

/*
* ���������� ��ȡStaticResSpeedData����
* ����˵����
* ����ֵ  �� 
            BnfStaticResSpeedStruct*
*/
BnfStaticResSpeedStruct *GetStaticResSpeedData(void)
{
    return StaticResSpeedDataStru;
}


/*
* ���������� ��ȡStaticResSpeedData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfStaticResSpeedStruct*
*/
BnfStaticResSpeedStruct *GetStaticResSpeedDataInfo(UINT16_S* lineNum)
{

    BnfStaticResSpeedStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumStaticResSpeed;
        retVal = StaticResSpeedDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru�Ľṹ���±�
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetStaticResSpeedDataStruIndex(const UINT16_S staticResSpeedId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumStaticResSpeed; i++)
    {
        if (staticResSpeedId == StaticResSpeedDataStru[i].staticResSpeedId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfStaticResSpeedStruct* GetIndexIdStaticResSpeedDataStru(const UINT16_S staticResSpeedId)
{
    BnfStaticResSpeedStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = &StaticResSpeedDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru�ĸ�������������Seg���
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��������������Seg���
*/ 
UINT16_S GetStaticResSpeedDataStrusegId(const UINT16_S staticResSpeedId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = StaticResSpeedDataStru[bufIndex].segId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru���������Segƫ����(cm)
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Segƫ����(cm)
*/ 
UINT32_S GetStaticResSpeedDataStruorgnSegOfst(const UINT16_S staticResSpeedId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = StaticResSpeedDataStru[bufIndex].orgnSegOfst;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru���յ�����Segƫ����(cm)
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Segƫ����(cm)
*/ 
UINT32_S GetStaticResSpeedDataStrutmnlSegOfst(const UINT16_S staticResSpeedId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = StaticResSpeedDataStru[bufIndex].tmnlSegOfst;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDStaticResSpeedDataStru�ľ�̬����ֵ
* ����˵���� const UINT16_S staticResSpeedId;���
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��̬����ֵ
*/ 
UINT16_S GetStaticResSpeedDataStrustaticSpeed(const UINT16_S staticResSpeedId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetStaticResSpeedDataStruIndex(staticResSpeedId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumStaticResSpeed)
    {
        retVal = StaticResSpeedDataStru[bufIndex].staticSpeed;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡָ����SEGID��ȡ�����Ϣ
* ����˵���� �������:const UINT16_S segId;���
*                      const UINT32_S startOffset  ���ƫ����
*                      const UINT32_S endOffset    �յ�ƫ����
*             �������:UINT16_S* limitSpeed  ����ֵ
* ����ֵ  :  0: ��ȡ����ʧ��
*             1: ���ҳɹ�
*/ 
UINT8_S GetSegIdOfLimitSpeed(const UINT16_S segId,const UINT32_S startOffset,const UINT32_S endOffset,UINT16_S* limitSpeed)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    UINT16_S tempLimitSpeedBuff[SEG_INCLUDE_LIMITSPEED_MAX_NUM] = {0};
    UINT8_S limitSpeedNum = 0u;/*ͬһSEG���ٸ���*/

    if(NULL != limitSpeed)
    {
        for ( i = 0u; i < LineNumStaticResSpeed; i++)
        {
            if (segId == StaticResSpeedDataStru[i].segId)
            {
                if (((startOffset>= StaticResSpeedDataStru[i].orgnSegOfst)&&(endOffset <= StaticResSpeedDataStru[i].tmnlSegOfst))
                    ||((startOffset < StaticResSpeedDataStru[i].orgnSegOfst)&&(endOffset>StaticResSpeedDataStru[i].tmnlSegOfst)))
                {
                    tempLimitSpeedBuff[limitSpeedNum] = StaticResSpeedDataStru[i].staticSpeed;
                    limitSpeedNum=limitSpeedNum+1;
                }
            }
        }

        if (limitSpeedNum > 0u)
        {
            *limitSpeed = tempLimitSpeedBuff[0];
            for (i = 1u; i < limitSpeedNum; i++)
            {
                if (tempLimitSpeedBuff[i] < *limitSpeed)
                {
                    *limitSpeed = tempLimitSpeedBuff[i];
                }
            }
            retVal = 1u;
        }

    }

    return retVal;
}

