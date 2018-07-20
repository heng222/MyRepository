/*************************************************
  �ļ���   ��SegData.h
  ����     ������      
  ����ʱ�� ��2016-8-13
  �������� �� SegData���ݹ���
			DmuCommonData�����SegData���ܿɷֽ����£�
			1��	��SegDataStru�ṹ��ָ�����ռ�
			2��	��ȡSEG�������
			3��	��ȡSegData����
			4��	��ȡSegData��Ϣ
			5��	��ȡָ��IDSegDataStru�Ľṹ���±�
			6��	��ȡָ��IDSegDataStru�Ľṹ��ָ��
			7��	 ��ȡָ��IDSegDataStru�ĳ��ȣ�cm)
			8��	��ȡָ��IDSegDataStru�����˵�����
			9��	��ȡָ��IDSegDataStru�����˵���
			10��	��ȡָ��IDSegDataStru���յ�˵�����
			11��	��ȡָ��IDSegDataStru���յ�˵���
			12��	��ȡָ��IDSegDataStru�������������SegID
			13��	��ȡָ��IDSegDataStru�����������ڵ�SegID
			14��	��ȡָ��IDSegDataStru���յ��������ڵ�SegID
			15��	��ȡָ��IDSegDataStru���յ�������ڵ�SegID
			16��	��ȡָ��IDSegDataStru������ZC����ID
			17��	��ȡָ��IDSegDataStru������ATS����ID
			18��	��ȡָ��IDSegDataStru������CI����ID
			19��	��ȡָ��IDSegDataStru���յ�˵��ź��յ�˵�����
			20��	��ȡָ��IDSegDataStru�����˵��ź����˵�����
			21��	��ȡָ����ָ��λ�õ�SEG��Ϣ
			22��	��ȡָ��CIID��ȡZCID
  ��ע    ���ޡ�
 
*************************************************/


#include "SegData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfSegStruct* SegDataStru = NULL;   /*����SegData���ݽṹ��*/
static UINT16_S LineNumSeg = 0u;/*������*/


/*
* ���������� ��SegDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocSegDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SegDataStru))
    {
        SegDataStru = (BnfSegStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSegStruct) * lineNum);
        LineNumSeg = lineNum;
    }
    

}

/*��ȡSEG�������*/
UINT16_S GetSegIdNum(void)
{
    return LineNumSeg;
}

/*
* ���������� ��ȡSegData����
* ����˵����
* ����ֵ  �� 
            BnfSegStruct*
*/
BnfSegStruct *GetSegData(void)
{
    return SegDataStru;
}


/*
* ���������� ��ȡSegData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfSegStruct*
*/
BnfSegStruct *GetSegDataInfo(UINT16_S* lineNum)
{
    BnfSegStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSeg;
        retVal = SegDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDSegDataStru�Ľṹ���±�
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetSegDataStruIndex(const UINT16_S segId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSeg; i++)
    {
        if (segId == SegDataStru[i].segId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfSegStruct* GetIndexIdSegDataStru(const UINT16_S segId)
{
    BnfSegStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = &SegDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru�ĳ��ȣ�cm)
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���ȣ�cm)
*/ 
UINT32_S GetSegDataStrulength(const UINT16_S segId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].length;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru�����˵�����
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���˵�����
*/ 
UINT16_S GetSegDataStrustartPointType(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].startPointType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru�����˵���
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���˵���
*/ 
UINT16_S GetSegDataStrustartPointId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].startPointId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru���յ�˵�����
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵�����
*/ 
UINT16_S GetSegDataStruendPointType(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].endPointType;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru���յ�˵���
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵���
*/ 
UINT16_S GetSegDataStruendPointId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].endPointId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru�������������SegID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �����������SegID
*/ 
UINT16_S GetSegDataStrusegStartJointMainSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segStartJointMainSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru�����������ڵ�SegID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ���������ڵ�SegID
*/ 
UINT16_S GetSegDataStrusegStartJointSideSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segStartJointSideSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru���յ��������ڵ�SegID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ��������ڵ�SegID
*/ 
UINT16_S GetSegDataStrusegTmnlJointMainSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segTmnlJointMainSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru���յ�������ڵ�SegID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�������ڵ�SegID
*/ 
UINT16_S GetSegDataStrusegTmnlJointSideSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segTmnlJointSideSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru������ZC����ID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ZC����ID
*/ 
UINT16_S GetSegDataStrusegManageZCId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segManageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru������ATS����ID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����ATS����ID
*/ 
UINT16_S GetSegDataStrusegManageATSId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segManageATSId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru������CI����ID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����CI����ID
*/ 
UINT16_S GetSegDataStrusegManageCIId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumSeg)
    {
        retVal = SegDataStru[bufIndex].segManageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru���յ�˵��ź��յ�˵�����
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵���
*/ 
UINT16_S GetSegDataStruendPointInfo(const UINT16_S segId,UINT16_S* pointType)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/

    if(NULL != pointType)
    {
        bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
        if (bufIndex < LineNumSeg)
        {
            retVal = SegDataStru[bufIndex].endPointId;
            *pointType = SegDataStru[bufIndex].endPointType;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }

    return retVal;
}

/*
** ���������� ��ȡָ��IDSegDataStru�����˵��ź����˵�����
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵���
*/ 
UINT16_S GetSegDataStrustartPointInfo(const UINT16_S segId,UINT16_S* pointType)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/

    if(NULL != pointType)
    {
        bufIndex = GetSegDataStruIndex(segId);/*��ȡ�ṹ�������±�*/
        if (bufIndex < LineNumSeg)
        {
            retVal = SegDataStru[bufIndex].startPointId;
            *pointType = SegDataStru[bufIndex].startPointType;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }

    return retVal;
}

/*
** ���������� ��ȡָ����ָ��λ�õ�SEG��Ϣ
* ����˵���� const UINT16_S pointId;����
*             const UINT8_S startOrEnd  �˵�Ϊ�����յ�  1 ��� 2 �յ�
*             BnfSegStruct* pSegStru SEG�ṹ����Ϣָ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�˵���
*/ 
UINT8_S GetSegInfoBuffAccordPointId(UINT16_S pointId,const UINT8_S startOrEnd,BnfSegStruct* pSegStru)
{
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S index = 0u;/*�ṹ�������±�*/

    if ((startOrEnd != START_POINT)&&(startOrEnd != END_POINT)&&(pSegStru == NULL))
    {
/*Do nothing currently !*/
    }
    else
    {
        for (i = 0u;(i < LineNumSeg)&&(index < ONEPOINT_SAMEDIR_INCLUDE_SEG); i++)
        {
            if (START_POINT == startOrEnd)
            {
                if (pointId == SegDataStru[i].startPointId)
                {
                    pSegStru[index] = SegDataStru[i];
                    index=index+1;
                }
            }
            else
            {
                if (pointId == SegDataStru[i].endPointId)
                {
                    pSegStru[index] = SegDataStru[i];
                    index=index+1;
                }
            }
        }
    }
    
    return index;
}

/*
** ���������� ��ȡָ��CIID��ȡZCID
* ����˵���� const UINT16_S segId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ZCID
*/ 
UINT16_S ArrordCiIdGetZcId(const UINT16_S ciId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumSeg; i++)
    {
        if (ciId == SegDataStru[i].segManageCIId)
        {
            retVal = SegDataStru[i].segManageZCId;
            break;
        }
    }
    return retVal;
}
