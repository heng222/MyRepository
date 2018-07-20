/*************************************************
  �ļ���   ��SwitchData.c
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SwitchData���ݹ���
			DmuCommonData�����SwitchData���ܿɷֽ����£�
			1��	��SwitchDataStru�ṹ��ָ�����ռ�
			2��	��ȡSwitchData����
			3��	��ȡSwitchData��Ϣ
			4��	��ȡָ��IDSwitchDataStru�Ľṹ���±�
			5��	��ȡָ��IDSwitchDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDSwitchDataStru�ĵ�������
			7��	��ȡָ��IDSwitchDataStru������������
			8��	��ȡָ��IDSwitchDataStru�ķ���
			9��	��ȡָ��IDSwitchDataStru�Ķ�λSegID
			10��	��ȡָ��IDSwitchDataStru�ķ�λSegID
			11��	��ȡָ��IDSwitchDataStru������SegID
			12��	��ȡָ��IDSwitchDataStru�ĵ���λ��̬�����ٶ�(cm/s)
			13��	���������SEGID��ȡ���������
			14��	��ȡ��·�������ID
			15��	���������SEGID��ȡ������Ϣ
			16��	���������SEGID��ȡ���������
			17��	��ȡ��·��������ZC
			18��	��ȡ��·��������CI
  ��ע    ���ޡ�
 
*************************************************/

#include "SwitchData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfSwitchStruct* SwitchDataStru = NULL;   /*����SwitchData���ݽṹ��*/
static UINT16_S LineNumSwitch = 0u;/*������*/


/*
* ���������� ��SwitchDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSwitchDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SwitchDataStru))
    {
        SwitchDataStru = (BnfSwitchStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSwitchStruct) * lineNum);
        if (SwitchDataStru != NULL)
        {
            LineNumSwitch = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(SwitchDataStru,lineNum*sizeof(BnfSwitchStruct),UINT8_NULL,lineNum*sizeof(BnfSwitchStruct));
        }
    }
}

/*
* ���������� ��ȡSwitchData����
* ����˵����
* ����ֵ  �� 
BnfSwitchStruct*
*/
BnfSwitchStruct *GetSwitchData(void)
{
    return SwitchDataStru;
}


/*
* ���������� ��ȡSwitchData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
BnfSwitchStruct*
*/
BnfSwitchStruct *GetSwitchDataInfo(UINT16_S* lineNum)
{

    BnfSwitchStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSwitch;
        retVal = SwitchDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDSwitchDataStru�Ľṹ���±�
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSwitchDataStruIndex(const UINT16_S switchId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSwitch; i++)
    {
        if (switchId == SwitchDataStru[i].switchId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSwitchDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSwitchStruct* GetIndexIdSwitchDataStru(const UINT16_S switchId)
{
    BnfSwitchStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = &SwitchDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSwitchDataStru�ĵ�������
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ��������
*/ 
UINT8_S* GetSwitchDataStruswitchName(const UINT16_S switchId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].switchName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSwitchDataStru������������
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����������
*/ 
UINT16_S GetSwitchDataStruswitchOtherId(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].switchOtherId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSwitchDataStru�ķ���
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����
*/ 
UINT16_S GetSwitchDataStrudir(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].dir;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSwitchDataStru�Ķ�λSegID
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��λSegID
*/ 
UINT16_S GetSwitchDataStrulocSegId(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].locSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSwitchDataStru�ķ�λSegID
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ��λSegID
*/ 
UINT16_S GetSwitchDataStruantiSegId(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].antiSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSwitchDataStru������SegID
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*             1: ��ȡ���ݳɹ�
*/ 
UINT8_S GetSwitchDataStruSegIdInfo(const UINT16_S switchId,UINT16_S* locSegId,UINT16_S* antiSegId,UINT16_S* joinSegId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        * joinSegId = SwitchDataStru[bufIndex].joinSegId;
        *locSegId = SwitchDataStru[bufIndex].locSegId;
        *antiSegId =SwitchDataStru[bufIndex].antiSegId;

        retVal = 1u;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSwitchDataStru�ĵ���λ��̬�����ٶ�(cm/s)
* ����˵���� const UINT16_S switchId;������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����λ��̬�����ٶ�(cm/s)
*/ 
UINT16_S GetSwitchDataStruswitchSideResSpeed(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].switchSideResSpeed;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ���������SEGID��ȡ���������
* ����˵���� const UINT16_S* pSegId;SEGIDָ��ָ��
const UINT16_S segIdNum;SEGID����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������
*/ 
UINT16_S GetSegIdOfSwitchIdNum(const UINT16_S* pSegId,const UINT16_S segIdNum)
{
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/

    UINT16_S switchIdNum = 0u;/*�������*/

    for ( i = 0u; i < LineNumSwitch; i++)
    {
        for (j = 0u;j < segIdNum; j++)
        {
            if ((SwitchDataStru[i].locSegId == pSegId[j])||(SwitchDataStru[i].joinSegId == pSegId[j])
                ||(SwitchDataStru[i].antiSegId == pSegId[j]))
            {
                switchIdNum++;
                break;
            }
        }

    }

    return switchIdNum;
}


/*
* ���������� ��ȡ��·�������ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�������ID
*/
UINT16_S GetLineSwitchMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S switchId = 0u;/*����ID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSwitch; i++)
    {
        if (switchId < SwitchDataStru[i].switchId)
        {
            switchId = SwitchDataStru[i].switchId;
        }
    }

    if(switchId != 0u)
    {
        retVal = switchId;
    }

    return retVal;
}

/*
** ���������� ���������SEGID��ȡ������Ϣ
* ����˵���� ����:const UINT16_S segId,SEGID
*             const UINT8_S segIdNum    SEGID����
*             UINT16_S index    ����ƫ��                  
*             �������:UINT16_S switchIdBuff[],����ID����      
* ����ֵ  :  >=0: �������
*/ 
UINT16_S GetSegIdBelongofSwitchInfo(const UINT16_S* segIdBuff,const UINT8_S segIdNum,UINT16_S index,UINT16_S switchIdBuff[])
{
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/
    UINT16_S switchIdNum = 0u;/*�������*/

    if ((segIdBuff != NULL)&&(segIdNum >0u)&&(switchIdBuff != NULL))
    {
        for ( i = 0u; i < LineNumSwitch; i++)
        {
            for (j = 0u; j < segIdNum; j++)
            {
                if ((SwitchDataStru[i].locSegId == segIdBuff[j])||(SwitchDataStru[i].antiSegId == segIdBuff[j]))
                {
                    switchIdBuff[index] = SwitchDataStru[i].switchId;
                    index=index+1;
                    switchIdBuff[index] = LINEOBS_SWITCH;
                    index=index+1;
                    switchIdNum++;
                    break;
                }
            }
        }
    }

    return switchIdNum;
}


/*
** ���������� ���������SEGID��ȡ���������
* ����˵���� const UINT16_S* pSegId;SEGIDָ��ָ��
const UINT8_S segIdNum;SEGID����
UINT16_S switchIdBuff[];����ID����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������
*/ 
UINT8_S GetSegIdBuffOfSwitchInfo(const UINT16_S* pSegId,const UINT16_S segIdNum,UINT16_S switchIdBuff[])
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S index = 0u;/*����ƫ��*/

    UINT8_S switchIdNum = 0u;/*�������*/

    if (((segIdNum <= BOTHSEG_INCLUDE_MAX_SEG)&&(segIdNum > 0u))
        &&(pSegId != NULL)&&(switchIdBuff != NULL))
    {
        for ( i = 0u;(i < LineNumSwitch)&&(switchIdNum < TWO_POINT_SWITCH_NUM_MAX); i++)
        {
            for (j = 0u;j < segIdNum; j++)
            {
                if (SwitchDataStru[i].locSegId == pSegId[j])
                {
                    switchIdBuff[index] = SwitchDataStru[i].switchId;
                    index=index+1;
                    switchIdBuff[index] = SWITCH_STATUS_SAME;
                    index=index+1;
                    switchIdNum++;
                    break;
                }
                else if (SwitchDataStru[i].antiSegId == pSegId[j])
                {
                    switchIdBuff[index] = SwitchDataStru[i].switchId;
                    index=index+1;
                    switchIdBuff[index] = SWITCH_STATUS_CONTRA;
                    index=index+1;
                    switchIdNum++;
                    break;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }

        }

        if (i == LineNumSwitch)
        {
            retVal = switchIdNum;
        }

    }

    return retVal;
}

/*
* ���������� ��ȡ��·��������ZC
* ����˵���� const UINT16_S switchId,����ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����ZCId
*/
UINT16_S GetLineSwitchBelongZcId(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].manageZCId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ��·��������CI
* ����˵���� const UINT16_S switchId,����ID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:����CIId
*/
UINT16_S GetLineSwitchBelongCiId(const UINT16_S switchId)
{    
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].manageCIId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
