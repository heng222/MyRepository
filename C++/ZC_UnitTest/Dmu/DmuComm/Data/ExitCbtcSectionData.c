/*************************************************
  �ļ���   ��ExitCbtcSectionData.c
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� ExitCbtcSectionData���ݹ���
			DmuCommonData�����ExitCbtcSectionData���ܿɷֽ����£�
			1��	��ExitCbtcSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡExitCbtcSectionData����
			3��	��ȡExitCbtcSectionData��Ϣ
			4��	��ȡָ��IDExitCbtcSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDExitCbtcSectionDataStru�Ľṹ��ָ��
			6��	 ��ȡָ��IDExitCbtcSectionDataStru���˳�CBTC����ʱ�г����з���
			7��	��ȡָ��IDExitCbtcSectionDataStru���˳�CBTC��������
			8��	 ��ȡָ��IDExitCbtcSectionDataStru���������seg���
			9��	��ȡָ��IDExitCbtcSectionDataStru���������Segƫ����
			10��	��ȡָ��IDExitCbtcSectionDataStru���յ�����Segƫ����
			11��	��ȡָ��IDExitCbtcSectionDataStru�İ�����Seg��Ŀ
			12��	��ȡָ��IDExitCbtcSectionDataStru��SEG���
			13��	��ѯĳ�����Ƿ���˳�CBTC�����յ��غ�
			14��	��ѯĳ�����Ƿ�����CBTC����

  ��ע    ���ޡ�
 
*************************************************/

#include "ExitCbtcSectionData.h"
#include "../../../Common/Malloc.h"

static BnfExitCbtcSectionStruct* ExitCbtcSectionDataStru = NULL;   /*����ExitCbtcSectionData���ݽṹ��*/
static UINT16_S LineNumExitCbtcSection = 0u;/*������*/


/*
* ���������� ��ExitCbtcSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocExitCbtcSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ExitCbtcSectionDataStru))
    {
        ExitCbtcSectionDataStru = (BnfExitCbtcSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfExitCbtcSectionStruct) * lineNum);
        LineNumExitCbtcSection = lineNum;
    }
}

/*
* ���������� ��ȡExitCbtcSectionData����
* ����˵����
* ����ֵ  �� 
            BnfExitCbtcSectionStruct*
*/
BnfExitCbtcSectionStruct *GetExitCbtcSectionData(void)
{
    return ExitCbtcSectionDataStru;
}


/*
* ���������� ��ȡExitCbtcSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfExitCbtcSectionStruct*
*/
BnfExitCbtcSectionStruct *GetExitCbtcSectionDataInfo(UINT16_S* lineNum)
{
    BnfExitCbtcSectionStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumExitCbtcSection;
        retVal = ExitCbtcSectionDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetExitCbtcSectionDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumExitCbtcSection; i++)
    {
        if (indexId == ExitCbtcSectionDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfExitCbtcSectionStruct* GetIndexIdExitCbtcSectionDataStru(const UINT16_S indexId)
{
    BnfExitCbtcSectionStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = &ExitCbtcSectionDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���˳�CBTC����ʱ�г����з���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �˳�CBTC����ʱ�г����з���
*/ 
UINT16_S GetExitCbtcSectionDataStrudir(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].dir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���˳�CBTC��������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �˳�CBTC��������
*/ 
UINT16_S GetExitCbtcSectionDataStruattribute(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].attribute;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���������seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������seg���
*/ 
UINT16_S GetExitCbtcSectionDataStrustartSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].startSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���������Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Segƫ����
*/ 
UINT32_S GetExitCbtcSectDataStartOff(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].startOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru���յ�����Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Segƫ����
*/ 
UINT32_S GetExitCbtcSectionDataStruendOffSet(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].endOffSet;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru�İ�����Seg��Ŀ
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ������Seg��Ŀ
*/ 
UINT16_S GetExitCbtcSectionDataStrusegNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].segNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDExitCbtcSectionDataStru��SEG���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: SEG���
*/ 
UINT16_S* GetExitCbtcSectionDataStrusegInfoBuff(const UINT16_S indexId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetExitCbtcSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumExitCbtcSection)
    {
        retVal = ExitCbtcSectionDataStru[bufIndex].segInfoBuff;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/* ���������� ��ѯĳ�����Ƿ���˳�CBTC�����յ��غ�
* ����˵���� 
* ����ֵ  �� 
*    1,�غ�
*    2,���غ�
*/
UINT8_S CheckAtQuitCbtcIsFindPoint(const UINT16_S seg,const UINT32_S offset)
{
    UINT8_S retVal = 2u;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j =0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumExitCbtcSection; i++)
    {
        for (j = 0u; j < ExitCbtcSectionDataStru[i].segNum; j++)
        {
            if ((seg == ExitCbtcSectionDataStru[i].segInfoBuff[j])&&(offset == ExitCbtcSectionDataStru[i].endOffSet))
            {
                retVal = 1u;
                break;
            }
        }

    }
    return retVal;
}

/* ���������� ��ѯĳ�����Ƿ�����CBTC����
* ����˵���� 
* ����ֵ  �� 
*    0,������
*    1,����
*/
UINT8_S ExitCbtcSecIncludePoint(UINT16_S segId,UINT32_S offset)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S i = 0u;    /*ѭ��ʹ��*/
    UINT16_S j = 0u;    /*ѭ��ʹ��*/
    UINT8_S flag = 0u;  /* �ҵ���־ ,��ʼ��Ϊδ�ҵ�*/

    for ( i = 0u; i < LineNumExitCbtcSection; i++)
    {
        for (j = 0u; j < ExitCbtcSectionDataStru[i].segNum; j++)
        {
            if ((segId == ExitCbtcSectionDataStru[i].segInfoBuff[j]))
            {
                if (ExitCbtcSectionDataStru[i].startOffset < ExitCbtcSectionDataStru[i].endOffSet)
                {
                    /* �˳���������С���յ� */
                    if ((offset>= ExitCbtcSectionDataStru[i].startOffset)&&(offset <= ExitCbtcSectionDataStru[i].endOffSet))
                    {
                        flag = 1u;
                    }
                } 
                else
                {
                    /* �˳�������������յ� */
                    if ((offset <= ExitCbtcSectionDataStru[i].startOffset)&&(offset >= ExitCbtcSectionDataStru[i].endOffSet))
                    {
                        flag = 1u;
                    }
                }
                
                if (1u == flag)
                {
                    break;
                }
                
            }
        }
        if (1u == flag)
        {
            break;
        }

    }

    if(1u == flag)
    {
        retVal = 1u;
    }
    return retVal;
}
