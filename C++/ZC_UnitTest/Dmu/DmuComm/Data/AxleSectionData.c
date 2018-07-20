
/*************************************************
  �ļ���   ��AxleSectionData.c
  ����     ������      
  ����ʱ�� ��2016-8-10
  �������� �� AxleSectionData���ݹ���
			DmuCommonData�����AxleSectionData���ܿɷֽ����£�
			1��	��AxleSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡAxleSectionData����
			3��	��ȡAxleSectionData��Ϣ
			4��	��ȡָ��IDAxleSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDAxleSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDAxleSectionDataStru������
			7��	��ȡָ��IDAxleSectionDataStru�İ���Seg��Ŀ
			8��	��ȡָ��IDAxleSectionDataStru��Seg���
			9��	��ȡ�������ΰ�����SegId����Ϣ
			10��	��ȡSEGID�����ļ�������ID
			11��	��ȡSEGID�����ļ������νṹ��ָ��
			12��	��ȡ��·�����������ID
			13��	��ȡָ��IDAxleSectionDataStru��Seg��Ϣ
			14��	��ȡ������������CIID
			15��	��ȡ������������ZC
			16��	��ȡ�������ΰ����߼�������Ϣ

  ��ע    ���ޡ�
 
*************************************************/

#include "AxleSectionData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Copy.h"

static BnfAxleSectionStruct* AxleSectionDataStru = NULL;   /*����AxleSectionData���ݽṹ��*/
static UINT16_S LineNumAxleSection = 0u;/*������*/


/*
* �������ƣ�MallocAxleSectionDataStru
* ���������� ��AxleSectionDataStru�ṹ��ָ�����ռ�
* ��������� UINT16_S lineNum �����������
* ��������� ��
* ����ֵ  �� void
*/
void MallocAxleSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == AxleSectionDataStru))
    {
        AxleSectionDataStru = (BnfAxleSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfAxleSectionStruct) * lineNum);
        if (AxleSectionDataStru != NULL)
        {
            LineNumAxleSection = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(AxleSectionDataStru,lineNum*sizeof(BnfAxleSectionStruct),UINT8_NULL,lineNum*sizeof(BnfAxleSectionStruct));
        }
    }
}

/*
* �������ƣ� GetAxleSectionData
* ���������� ��ȡAxleSectionData����
* ��������� ��
* ��������� ��
* ����ֵ  ��
*           BnfAxleSectionStruct*
*/
BnfAxleSectionStruct *GetAxleSectionData(void)
{
    return AxleSectionDataStru;
}


/*
* �������ƣ� GetAxleSectionData
* ���������� ��ȡAxleSectionData����
* ��������� ��
* ��������� ��
* ����ֵ  ��
*           BnfAxleSectionStruct*
*/
BnfAxleSectionStruct *GetAxleSectionDataInfo(UINT16_S* lineNum)
{
    BnfAxleSectionStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumAxleSection;
        retVal =  AxleSectionDataStru;

    }
    return retVal;
}
/*
* �������ƣ� GetAxleSectionDataStruIndex
* ���������� ��ȡָ��IDAxleSectionDataStru�Ľṹ���±�
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetAxleSectionDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAxleSection; i++)
    {
        if (indexId == AxleSectionDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
* �������ƣ� GetIndexIdAxleSectionDataStru
* ���������� ��ȡָ��IDAxleSectionDataStru�Ľṹ��ָ��
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfAxleSectionStruct* GetIndexIdAxleSectionDataStru(const UINT16_S indexId)
{
    BnfAxleSectionStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetAxleSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAxleSection)
    {
        retVal = &AxleSectionDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ� GetAxleSectionDataStruaxleStcName
* ���������� ��ȡָ��IDAxleSectionDataStru������
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetAxleSectionDataStruaxleStcName(const UINT16_S indexId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetAxleSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAxleSection)
    {
        retVal = AxleSectionDataStru[bufIndex].axleStcName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ� GetAxleSectionDataStruincludeSegNum
* ���������� ��ȡָ��IDAxleSectionDataStru�İ���Seg��Ŀ
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����Seg��Ŀ
*/ 
UINT16_S GetAxleSectionDataStruincludeSegNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetAxleSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAxleSection)
    {
        retVal = AxleSectionDataStru[bufIndex].includeSegNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ� GetAxleSectionDataStrusegIdBuff
* ���������� ��ȡָ��IDAxleSectionDataStru��Seg���
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: Seg���
*/ 
UINT16_S* GetAxleSectionDataStrusegIdBuff(const UINT16_S indexId)
{
    UINT16_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetAxleSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumAxleSection)
    {
        retVal = AxleSectionDataStru[bufIndex].segIdBuff;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* �������ƣ� GetAxleSectionOfSegInfo
* ���������� ��ȡ�������ΰ�����SegId����Ϣ
* ��������� const UINT16_S AxleSecId,��������ID
* ��������� UINT16_S* pSegId��SegID����
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:SegId����
*/
UINT16_S GetAxleSectionOfSegInfo(const UINT16_S AxleSecId,UINT16_S* pSegId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/

    if(NULL != pSegId)
    {
        bufIndex = GetAxleSectionDataStruIndex(AxleSecId);/*��ȡ�ṹ�������±�*/
        if (bufIndex < LineNumAxleSection)
        {
            MemoryCpy(pSegId,sizeof(UINT16_S)*AXLESECTION_SEG_MAX_NUM,AxleSectionDataStru[bufIndex].segIdBuff,sizeof(UINT16_S)*AXLESECTION_SEG_MAX_NUM);
            retVal =  AxleSectionDataStru[bufIndex].includeSegNum;
        }
        else
        {
            /*Do nothing currently !*/
        }


    }
    return retVal;
}


/*
* �������ƣ� GetSegIdBelongofAxleSecId
* ���������� ��ȡSEGID�����ļ�������ID
* ��������� const UINT16_S  segId��SegID
*             const UINT8_S segNum      SEG����
*             const UINT8_S findNum  ��Ҫ���Ҽ���
* ��������� ��
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:��������ID
*/
UINT16_S GetSegIdBelongofAxleSecId(const UINT16_S* segIdbuff,const UINT8_S segNum,const UINT8_S findNum)
{
    UINT16_S retVal = 0u;

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S  k = 0u;/*ѭ��ʹ��*/
    UINT8_S tmpFindNum = 0u;/*���ҵ��ĸ���*/

    if(NULL != segIdbuff)
    {
        for ( i = 0u; i < LineNumAxleSection; i++)
        {
            tmpFindNum = 0u;
            for(j = 0u;j < AxleSectionDataStru[i].includeSegNum;j++)
            {
                if (AxleSectionDataStru[i].includeSegNum == 1u)
                {
                    if ((segIdbuff[0] == AxleSectionDataStru[i].segIdBuff[j]))
                    {
                        tmpFindNum++;
                    }
                }
                else
                {
                    for (k = 0u;k < segNum;k++)
                    {
                        if ((segIdbuff[k] == AxleSectionDataStru[i].segIdBuff[j]))
                        {
                            tmpFindNum++;
                            break;
                        }

                    }
                }
                if (tmpFindNum >= findNum)
                {
                    retVal = AxleSectionDataStru[i].indexId;
                    break;
                }

            }
            if (retVal != 0u)
            {
                break;
            }
        }


    }



    return retVal;
}

/*
* �������ƣ� GetSegIdBelongofAxleSecInfo
* ���������� ��ȡSEGID�����ļ������νṹ��ָ��
* ��������� const UINT16_S  segId��SegID
*             const UINT8_S segNum      SEG����
* ��������� ��
* ����ֵ  �� NULL: ��ȡ����ʧ��
*             !NULL:�������νṹ��ָ��
*/
BnfAxleSectionStruct* GetSegIdBelongofAxleSecInfo(const UINT16_S* segIdbuff,const UINT8_S segNum)
{
    BnfAxleSectionStruct* retVal = NULL;

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S  k = 0u;/*ѭ��ʹ��*/
    UINT8_S findNum = 0u;/*���ҵ��ĸ���*/

    if(NULL != segIdbuff)
    {
        for ( i = 0u; i < LineNumAxleSection; i++)
        {
            findNum = 0u;
            for(j = 0u;j < AxleSectionDataStru[i].includeSegNum;j++)
            {
                if (AxleSectionDataStru[i].includeSegNum == 1u)
                {
                    if ((segIdbuff[0] == AxleSectionDataStru[i].segIdBuff[j]))
                    {
                        retVal = &AxleSectionDataStru[i];
                        break;
                    }
                }
                else
                {
                    for (k = 0u;k < segNum;k++)
                    {
                        if ((segIdbuff[k] == AxleSectionDataStru[i].segIdBuff[j]))
                        {
                            findNum++;
                            break;
                        }

                    }
                    if (findNum >= 2u)
                    {
                        retVal = &AxleSectionDataStru[i];
                        break;
                    }
                }

            }
            if (retVal != NULL)
            {
                break;
            }
        }


    }

    return retVal;
}


/*
* �������ƣ� GetLineAcMaxId
* ���������� ��ȡ��·�����������ID
* ��������� ��
* ��������� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�����������ID
*/
UINT16_S GetLineAcMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S axleSecId = 0u;/*��������ID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumAxleSection; i++)
    {
        if (axleSecId < AxleSectionDataStru[i].indexId)
        {
            axleSecId = AxleSectionDataStru[i].indexId;
        }
    }

    if(axleSecId != 0u)
    {
        retVal = axleSecId;
    }

    return retVal;
}

/*
* �������ƣ� GetAxleSectionDataStruSegInfo
* ���������� ��ȡָ��IDAxleSectionDataStru��Seg��Ϣ
* ��������� const UINT16_S indexId;�������
* ��������� ��
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: ����SEG�ĸ���
*/ 
UINT16_S GetAxleSectionDataStruSegInfo(const UINT16_S indexId,UINT16_S* pSegId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;/*�����±�*/

    if(NULL != pSegId)
    {
        bufIndex = GetAxleSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
        if (bufIndex < LineNumAxleSection)
        {
            MemoryCpy(pSegId,sizeof(UINT16_S)*AXLESECTION_SEG_MAX_NUM,AxleSectionDataStru[bufIndex].segIdBuff,sizeof(UINT16_S)*AXLESECTION_SEG_MAX_NUM);
            retVal = AxleSectionDataStru[bufIndex].includeSegNum;
        }
        else
        {
            /*Do nothing currently !*/
        }

    }
    return retVal;
}

/*
* �������ƣ� GetLineAcBelongCiId
* ���������� ��ȡ������������CIID
* ��������� const UINT16_S acId����������ID
* ��������� ��
* ����ֵ  �� 0: ��ȡʧ��
*             ����ID
*/
UINT16_S GetLineAcBelongCiId(const UINT16_S acId)
{
    UINT16_S buffIndex = 0u;/*�����±�*/
    UINT16_S ciId = 0u; /*����ID*/

    /*��ȡ�������ζ�Ӧ�������±�*/
    buffIndex = GetAxleSectionDataStruIndex(acId);

    /*��������CI��ID*/
    if (buffIndex < UINT16_NULL)
    {
        ciId = AxleSectionDataStru[buffIndex].manageCIId;
    }

    return ciId;
}


/*
* �������ƣ� GetLineAcBelongZcId
* ���������� ��ȡ������������ZC
* ��������� const UINT16_S acId����������ID
* ��������� ��
* ����ֵ  �� 0: ��ȡʧ��
*            >0:����ZCID
*/
UINT16_S GetLineAcBelongZcId(const UINT16_S acId)
{
    UINT16_S buffIndex = 0u;/*�����±�*/
    UINT16_S zcId = 0u; /*ZCID*/

    /*��ȡ�������ζ�Ӧ�������±�*/
    buffIndex = GetAxleSectionDataStruIndex(acId);

    /*��������CI��ID*/
    if (buffIndex < UINT16_NULL)
    {
        zcId = AxleSectionDataStru[buffIndex].manageZCId;
    }

    return zcId;
}

/*
* �������ƣ� GetLineAcIncludeLogicSectionInfo
* ���������� ��ȡ�������ΰ����߼�������Ϣ
* ��������� const UINT16_S acId����������ID
* ��������� UINT8_S *logicSectionNum,�߼���������
*            UINT16_S logicSectionIdBuf[]���߼�����ID����
* ����ֵ  �� 0: ��ȡʧ��
*            1: ��ȡ�ɹ�
*/
UINT8_S GetLineAcIncludeLogicSectionInfo(const UINT16_S acId,UINT8_S *logicSectionNum,UINT16_S logicSectionIdBuf[])
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;/*�����±�*/
    bufIndex = GetAxleSectionDataStruIndex(acId);/*��ȡ�ṹ�������±�*/
    if ((logicSectionIdBuf != NULL)&&(bufIndex < LineNumAxleSection))
    {
        MemoryCpy(logicSectionIdBuf,sizeof(UINT16_S)*AxleSectionDataStru[bufIndex].includeLogicAxleSecNum,AxleSectionDataStru[bufIndex].logicSecId,sizeof(UINT16_S)*AxleSectionDataStru[bufIndex].includeLogicAxleSecNum);
        *logicSectionNum = AxleSectionDataStru[bufIndex].includeLogicAxleSecNum;
        retVal = 1u;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
