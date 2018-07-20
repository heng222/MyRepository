/*************************************************
  �ļ���   ��LineSwitchInfoData.c
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� LineSwitchInfoData���ݹ���
			DmuCommonData�����LineSwitchInfoData���ܿɷֽ����£�
			1��	��LineSwitchInfoDataStru�ṹ��ָ�����ռ�
			2��	��ȡLineSwitchInfoData����
			3��	��ȡLineSwitchInfoData��Ϣ
			4��	��ȡָ��IDLineSwitchInfoDataStru�Ľṹ���±�
			5��	��ȡָ��IDLineSwitchInfoDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDLineSwitchInfoDataStru���л���·�ƽ�ZCID
			7��	��ȡָ��IDLineSwitchInfoDataStru���л���·�ӹ�ZCID
			8��	��ȡָ��IDLineSwitchInfoDataStru���л���·����
			9��	��ȡָ��IDLineSwitchInfoDataStru���л���·�������seg���
			10��	��ȡָ��IDLineSwitchInfoDataStru���л���·�������segƫ��
			11��	��ȡָ��IDLineSwitchInfoDataStru���л�������seg���
			12��	��ȡָ��IDLineSwitchInfoDataStru���л�������segƫ��
			13��	��ȡָ��IDLineSwitchInfoDataStru���л���·�յ�����seg���
			14��	��ȡָ��IDLineSwitchInfoDataStru���л���·�յ�����segƫ��
			15��	��ȡָ��IDLineSwitchInfoDataStru���л�����ؽ�·���
			16��	��ȡָ��IDLineSwitchInfoDataStru���л���·�ڰ����ĵ�����Ŀ
			17��	��ȡָ��IDLineSwitchInfoDataStru�ĵ�����Ϣ�ṹ��
			18��	��ȡ�л���·������ID��Ϣ

  ��ע    ���ޡ�
 
*************************************************/

#include "LineSwitchInfoData.h"
#include "../../../Common/Malloc.h"

static BnfLineSwitchInfoStruct* LineSwitchInfoDataStru = NULL;   /*����LineSwitchInfoData���ݽṹ��*/
static UINT16_S LineNumLineSwitchInfo = 0u;/*������*/


/*
* ���������� ��LineSwitchInfoDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocLineSwitchInfoDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == LineSwitchInfoDataStru))
    {
        LineSwitchInfoDataStru = (BnfLineSwitchInfoStruct*)MemoryMalloc((UINT32_S)sizeof(BnfLineSwitchInfoStruct) * lineNum);
        LineNumLineSwitchInfo = lineNum;
    }
}

/*
* ���������� ��ȡLineSwitchInfoData����
* ����˵����
* ����ֵ  �� 
            BnfLineSwitchInfoStruct*
*/
BnfLineSwitchInfoStruct *GetLineSwitchInfoData(void)
{
    return LineSwitchInfoDataStru;
}


/*
* ���������� ��ȡLineSwitchInfoData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfLineSwitchInfoStruct*
*/
BnfLineSwitchInfoStruct *GetLineSwitchInfoDataInfo(UINT16_S* lineNum)
{

    BnfLineSwitchInfoStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumLineSwitchInfo;
        retVal = LineSwitchInfoDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetLineSwitchInfoDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumLineSwitchInfo; i++)
    {
        if (indexId == LineSwitchInfoDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfLineSwitchInfoStruct* GetIndexIdLineSwitchInfoDataStru(const UINT16_S indexId)
{
    BnfLineSwitchInfoStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = &LineSwitchInfoDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�ƽ�ZCID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�ƽ�ZCID
*/ 
UINT16_S GetLineSwitchInfoDataStrulineSwitchTraZcId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].lineSwitchTraZcId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�ӹ�ZCID
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�ӹ�ZCID
*/ 
UINT16_S GetLinSwInfDatliSwTakeOvZcId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].lineSwitchTakeOverZcId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·����
*/ 
UINT8_S GetLineSwInfoDatalineSwDir(const UINT16_S indexId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].lineSwitchDir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�������seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�������seg���
*/ 
UINT16_S GetLineSwitchInfoDataStrustartLineSwitchInfoId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].startLineSwitchInfoId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�������segƫ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�������segƫ��
*/ 
UINT32_S GetLineSwitchInfoDataStrustartSegOffset(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].startSegOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л�������seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л�������seg���
*/ 
UINT16_S GetLineSwitchInfoDataStruswitchPointSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].switchPointSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л�������segƫ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л�������segƫ��
*/ 
UINT32_S GetLineSwInfoDataSwPointOff(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].switchPointOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�յ�����seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�յ�����seg���
*/ 
UINT16_S GetLineSwitchInfoDataStruendLineSwitchInfoId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].endLineSwitchInfoId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�յ�����segƫ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�յ�����segƫ��
*/ 
UINT32_S GetLineSwitchInfoDataStrusegEndOffset(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].segEndOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л�����ؽ�·���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л�����ؽ�·���
*/ 
UINT16_S GetLineSwitchInfoDataStrurelationRouteNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].relationRouteNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru���л���·�ڰ����ĵ�����Ŀ
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �л���·�ڰ����ĵ�����Ŀ
*/ 
UINT16_S GetLineSwitchInfoDataStruincludeSwitchNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].includeSwitchNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLineSwitchInfoDataStru�ĵ�����Ϣ�ṹ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ������Ϣ�ṹ��
*/ 
BnfSngSwitchInfoStruct* GetLineSwInfDataSwInfStru(const UINT16_S indexId)
{
    BnfSngSwitchInfoStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLineSwitchInfoDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLineSwitchInfo)
    {
        retVal = LineSwitchInfoDataStru[bufIndex].switchInfoStru;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ�л���·������ID��Ϣ
* ��������� const UINT16_S localZcId, ����ZCid
*            UINT16_S changeLineIdBuf[]���л���·ID���飨���30����
* ����ֵ  �� 0xff: ��ȡ����ʧ��
*            0>: ����
*/
UINT8_S GetLocalZcChangeLineNum(const UINT16_S localZcId, UINT16_S changeLineIdBuf[])
{
    UINT8_S retVal = 0xffu;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S index = 0u;/*����ƫ��*/

    if(NULL != changeLineIdBuf)
    {
        for ( i = 0u; i < LineNumLineSwitchInfo; i++)
        {
            if ((localZcId == LineSwitchInfoDataStru[i].lineSwitchTraZcId)
                || (localZcId == LineSwitchInfoDataStru[i].lineSwitchTakeOverZcId))
            {
                changeLineIdBuf[index] = LineSwitchInfoDataStru[i].indexId;
                index=index+1;
            }
        }

        if(index != 0u)
        {
            retVal = index;
        }

    }

    return retVal;
}
