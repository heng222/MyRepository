/*************************************************
  �ļ���   ��LogicSectionData.c
  ����     ������      
  ����ʱ�� ��2016-8-12
  �������� �� LogicSectionData���ݹ���
			DmuCommonData�����LogicSectionData���ܿɷֽ����£�
			1��	��LogicSectionDataStru�ṹ��ָ�����ռ�
			2��	��ȡLogicSectionData����
			3��	��ȡLogicSectionData��Ϣ
			4��	��ȡָ��IDLogicSectionDataStru�Ľṹ���±�
			5��	��ȡָ��IDLogicSectionDataStru�Ľṹ��ָ��
			6��	��ȡָ��IDLogicSectionDataStru������
			7��	��ȡָ��IDLogicSectionDataStru���������Seg���
			8��	��ȡָ��IDLogicSectionDataStru���������Segƫ����
			9��	��ȡָ��IDLogicSectionDataStru���յ�����Seg���
			10��	��ȡָ��IDLogicSectionDataStru���յ�����Segƫ����
			11��	��ȡ��·�߼��������ID
			12��	���������SEGID��ȡ�߼����ε���Ϣ
			13��	��ȡ�߼���������ZC
			14��	��ȡ�߼���������CI
			15��	��ȡ�߼���������AC
			16��	��ѯ��SEGǰ�����߼�����
			17��	��ѯ��SEG�󷽵��߼�����
			18��	��ȡ�߼�����ID��������߼�����ID
  ��ע    ���ޡ�
 
*************************************************/

#include "LogicSectionData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfLogicSectionStruct* BnfLogicSectionDataStru = NULL;   /*����LogicSectionData���ݽṹ��*/
static UINT16_S LineNumLogicSection = 0u;/*������*/


/*
* ���������� ��LogicSectionDataStru�ṹ��ָ�����ռ�
* ����˵���� UINT16_S lineNum �����������
* ����ֵ  �� void
*/
void MallocLogicSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BnfLogicSectionDataStru))
    {
        BnfLogicSectionDataStru = (BnfLogicSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfLogicSectionStruct) * lineNum);
        if (BnfLogicSectionDataStru != NULL)
        {
            LineNumLogicSection = lineNum;
            /*��ֵΪ��Чֵ*/
            MemorySet(BnfLogicSectionDataStru,lineNum*sizeof(BnfLogicSectionStruct),UINT8_NULL,lineNum*sizeof(BnfLogicSectionStruct));
        }
    }
}

/*
* ���������� ��ȡLogicSectionData����
* ����˵����
* ����ֵ  �� 
            BnfLogicSectionStruct*
*/
BnfLogicSectionStruct *GetLogicSectionData(void)
{
    return BnfLogicSectionDataStru;
}


/*
* ���������� ��ȡLogicSectionData��Ϣ
* ����˵�����������:UINT16_S* lineNum  ��������
* ����ֵ  �� 
            BnfLogicSectionStruct*
*/
BnfLogicSectionStruct *GetLogicSectionDataInfo(UINT16_S* lineNum)
{

    BnfLogicSectionStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumLogicSection;
        retVal = BnfLogicSectionDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** ���������� ��ȡָ��IDLogicSectionDataStru�Ľṹ���±�
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0xFFFF: ��ȡ����ʧ��
*            <0xFFFF: ���ҳɹ�
*/ 
UINT16_S GetLogicSectionDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*��������ֵ*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumLogicSection; i++)
    {
        if (indexId == BnfLogicSectionDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLogicSectionDataStru�Ľṹ��ָ��
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ���ҳɹ�,���ҷ���ֵΪ�ṹ��ָ��
*/ 
BnfLogicSectionStruct* GetIndexIdLogicSectionDataStru(const UINT16_S indexId)
{
    BnfLogicSectionStruct* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = &BnfLogicSectionDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLogicSectionDataStru������
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  NULL: ��ȡ����ʧ��
*            !NULL: ����
*/ 
UINT8_S* GetLogicSectionDataStruname(const UINT16_S indexId)
{
    UINT8_S* retVal = NULL;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLogicSectionDataStru���������Seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Seg���
*/ 
UINT16_S GetLogicSectionDataStrustartSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].startSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLogicSectionDataStru���������Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �������Segƫ����
*/ 
UINT32_S GetLogSecDataStartSegOff(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].startSegOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLogicSectionDataStru���յ�����Seg���
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Seg���
*/ 
UINT16_S GetLogicSectionDataStruendSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].endSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** ���������� ��ȡָ��IDLogicSectionDataStru���յ�����Segƫ����
* ����˵���� const UINT16_S indexId;�������
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �յ�����Segƫ����
*/ 
UINT32_S GetLogicSectionDataStruendSegOffset(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].endSegOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}


/*
* ���������� ��ȡ��·�߼��������ID
* ����˵���� ��
* ����ֵ  �� 0xffff: ��ȡ����ʧ��
*            >0:�߼��������ID
*/
UINT16_S GetLineLogicSectionMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S logicSecId = 0u;/*�߼�����ID*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for ( i = 0u; i < LineNumLogicSection; i++)
    {
        if (logicSecId < BnfLogicSectionDataStru[i].indexId)
        {
            logicSecId = BnfLogicSectionDataStru[i].indexId;
        }
    }

    if(logicSecId != 0u)
    {
        retVal = logicSecId;
    }

    return retVal;
}


/*
* ���������� ���������SEGID��ȡ�߼����ε���Ϣ
* ����˵���� const UINT16_S* pSegId;SEGIDָ��ָ��
             const UINT16_S segIdNum;SEGID����
             UINT16_S logicSectionIdBuf[];�߼�����ID����
* ����ֵ  :  0: ��ȡ����ʧ��
*            >0: �߼����θ���
*/ 
UINT8_S GetSegIdBuffOfLogSecInfo(const UINT16_S* pSegId,const UINT16_S segIdNum,UINT16_S logicSectionIdBuf[])
{
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/
    
    UINT8_S logicSecIdNum = 0u;/*�߼����θ���*/
        
    if((NULL != pSegId) && (NULL != logicSectionIdBuf))
    {
        for ( i = 0u; i < LineNumLogicSection; i++)
        {
            for (j = 0u;j < segIdNum; j++)
            {
                if (BnfLogicSectionDataStru[i].startSegId == pSegId[j])
                {
                    logicSectionIdBuf[logicSecIdNum] = BnfLogicSectionDataStru[i].indexId;
                    logicSecIdNum=logicSecIdNum+1;
                    break;
                }
            }

        }
    }
    return logicSecIdNum;
}

/*
* ���������� ��ȡ�߼���������ZC
* ����˵���� const UINT16_S logicSectionId���߼�����ID
* ����ֵ  �� 0: ��ȡʧ��
*            >0:����ZCID
*/
UINT16_S GetLineLogicSectionBelongZcId(const UINT16_S logicSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(logicSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].manageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ�߼���������CI
* ����˵���� const UINT16_S logicSectionId���߼�����ID
* ����ֵ  �� 0: ��ȡʧ��
*            >0:����CIID
*/
UINT16_S GetLineLogicSectionBelongCiId(const UINT16_S logicSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(logicSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].manageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ȡ�߼���������AC
* ����˵���� const UINT16_S logicSectionId���߼�����ID
* ����ֵ  �� 0: ��ȡʧ��
*            >0:����ACID
*/
UINT16_S GetLineLogicSectionBelongAcId(const UINT16_S logicSectionId)
{
    UINT16_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    bufIndex = GetLogicSectionDataStruIndex(logicSectionId);/*��ȡ�ṹ�������±�*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].belongAxleSecId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ѯ��SEGǰ�����߼�����
*            (1)����һ���߼�����ֱ�ӷ���
*            (2)���ж���������߼�����ƫ��������
*            (3)����SEG�����������߼������У��������������߼�����ID
* ����˵���� const UINT16_S startSegId,const UINT32_S startOffset,const UINT32_S endOffset
             UINT16_S logicSectionIdBuf[];�߼�����ID����
* ����ֵ  :  0: ʧ��
*             1: �ɹ�
*/ 
UINT8_S GetSegFontSecOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startSegLen,UINT16_S* mainLogicId,UINT16_S* sideLogicId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT32_S endSegOffSet = 0u;/*��ѯ����SEGƫ����*/
    UINT8_S findNum = 0u;/*��ѯ���Ĵ���*/

    if((NULL != mainLogicId) && (NULL != sideLogicId))
    {
        *mainLogicId = UINT16_NULL;
        *sideLogicId = UINT16_NULL;
        for ( i = 0u; i < LineNumLogicSection; i++)
        {
            if (BnfLogicSectionDataStru[i].includeSegIdNum == 1u)
            {
                if (BnfLogicSectionDataStru[i].startSegId == startSegId)
                {
                    if ((BnfLogicSectionDataStru[i].startSegOffset == 0u)&&(BnfLogicSectionDataStru[i].endSegOffset == startSegLen))
                    {
                        findNum = 1u;
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                        break;
                    }
                    else
                    {
                        if (BnfLogicSectionDataStru[i].endSegOffset > endSegOffSet)
                        {
                            endSegOffSet = BnfLogicSectionDataStru[i].endSegOffset;
                            findNum = 1u;
                            *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                        }
                    }
                }
            }
            else
            {
                if (BnfLogicSectionDataStru[i].startSegId == startSegId)
                {
                    findNum += 1u;
                    if (BnfLogicSectionDataStru[i].switchIdStru[0].switchStatus == SWITCH_STATUS_SAME)
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else if (BnfLogicSectionDataStru[i].switchIdStru[0].switchStatus == SWITCH_STATUS_CONTRA)
                    {
                        *sideLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }

                    if (2u == findNum)
                    {
                        if ((*mainLogicId != UINT16_NULL)&&(*sideLogicId != UINT16_NULL))
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            findNum = 0u;
                        }
                        break;
                    }
                }
                else if(BnfLogicSectionDataStru[i].endSegId == startSegId)
                {
                    findNum += 1u;
                    if (BnfLogicSectionDataStru[i].switchIdStru[BnfLogicSectionDataStru[i].switchIdNum -1].switchStatus == SWITCH_STATUS_SAME)
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else if (BnfLogicSectionDataStru[i].switchIdStru[BnfLogicSectionDataStru[i].switchIdNum -1].switchStatus == SWITCH_STATUS_CONTRA)
                    {
                        *sideLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }

                    if (2u == findNum)
                    {
                        if ((*mainLogicId != UINT16_NULL)&&(*sideLogicId != UINT16_NULL))
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            findNum = 0u;
                        }
                        break;
                    }
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
        }

        if (findNum > 0u)
        {
            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }



    }

    return retVal;
}

/*
* ���������� ��ѯ��SEG�󷽵��߼�����
*            (1)����һ���߼�����ֱ�ӷ���
*            (2)���ж���������߼�����ƫ��������
*            (3)����SEG�����������߼������У��������������߼�����ID
* ����˵���� const UINT16_S startSegId,const UINT32_S startOffset,const UINT32_S endOffset
             UINT16_S logicSectionIdBuf[];�߼�����ID����
* ����ֵ  :  0: ʧ��
*             1: �ɹ�
*/ 
UINT8_S GetSegRearSecOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startSegLen,UINT16_S* mainLogicId,UINT16_S* sideLogicId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT32_S startSegOffSet = 0u;/*��ѯ����SEGƫ����*/
    UINT8_S findNum = 0u;/*��ѯ���Ĵ���*/

    if((NULL != mainLogicId) && (NULL != sideLogicId))
    {
        *mainLogicId = UINT16_NULL;
        *sideLogicId = UINT16_NULL;

        for ( i = 0u; i < LineNumLogicSection; i++)
        {
            if (BnfLogicSectionDataStru[i].includeSegIdNum == 1u)
            {
                if (BnfLogicSectionDataStru[i].startSegId == startSegId)
                {
                    if ((BnfLogicSectionDataStru[i].startSegOffset == 0u)&&(BnfLogicSectionDataStru[i].endSegOffset == startSegLen))
                    {
                        findNum = 1u;
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                        break;
                    }
                    else
                    {
                        findNum += 1u;
                        if (findNum == 1u)
                        {
                            startSegOffSet = BnfLogicSectionDataStru[i].startSegOffset;
                            *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                        }
                        else
                        {
                            if (BnfLogicSectionDataStru[i].startSegOffset < startSegOffSet)
                            {
                                startSegOffSet = BnfLogicSectionDataStru[i].startSegOffset;
                                *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                            }
                        }
                    }
                }
            }
            else
            {
                if (BnfLogicSectionDataStru[i].startSegId == startSegId)
                {
                    findNum += 1u;
                    if (BnfLogicSectionDataStru[i].switchIdStru[0].switchStatus == SWITCH_STATUS_SAME)
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else if (BnfLogicSectionDataStru[i].switchIdStru[0].switchStatus == SWITCH_STATUS_CONTRA)
                    {
                        *sideLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }

                    if (2u == findNum)
                    {
                        if ((*mainLogicId != UINT16_NULL)&&(*sideLogicId != UINT16_NULL))
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            findNum = 0u;
                        }
                        break;
                    }
                }
                else if(BnfLogicSectionDataStru[i].endSegId == startSegId)
                {
                    findNum += 1u;
                    if (BnfLogicSectionDataStru[i].switchIdStru[BnfLogicSectionDataStru[i].switchIdNum -1].switchStatus == SWITCH_STATUS_SAME)
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else if (BnfLogicSectionDataStru[i].switchIdStru[BnfLogicSectionDataStru[i].switchIdNum -1].switchStatus == SWITCH_STATUS_CONTRA)
                    {
                        *sideLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }

                    if (2u == findNum)
                    {
                        if ((*mainLogicId != UINT16_NULL)&&(*sideLogicId != UINT16_NULL))
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            findNum = 0u;
                        }
                        break;
                    }
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
        }

        if (findNum > 0u)
        {
            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }

    }

    return retVal;
}

/*
* ���������� ��ȡ�߼�����ID��������߼�����ID
* ����˵���� const UINT16_S logicSectionId���߼�����ID
* ����ֵ  �� UINT16_NULL: ��ѯʧ��
*            >0: �������߼�����ID
*/
UINT8_S GetLineLogicSectionBelongRelareLc(const UINT16_S logicSectionId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct* relateLogicInfo)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S bufIndex = 0u;  /*�����±�*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S k = 0u;/*ѭ��ʹ��*/
    UINT8_S findFlag = 0u;/*�Ƿ���ҵ�*/
    UINT8_S findNum = 0u;/*��Ҫ���ҵ��ĸ���*/

    if((NULL != relateLogicNum) && (NULL != relateLogicInfo))
    {
        *relateLogicNum = 0u;
        bufIndex = GetLogicSectionDataStruIndex(logicSectionId);/*��ȡ�ṹ�������±�*/
        if ((bufIndex < LineNumLogicSection)&&(NULL != relateLogicInfo))
        {
            for (j = 0u;j < LineNumLogicSection;j++)
            {
                if(BnfLogicSectionDataStru[j].indexId != logicSectionId)
                {
                    findFlag = 0u;
                    if (BnfLogicSectionDataStru[j].includeSegIdNum > 1u)
                    {
                        for(i = 0u;i < BnfLogicSectionDataStru[j].includeSegIdNum;i++)
                        {
                            for (k = 0u;k < BnfLogicSectionDataStru[bufIndex].includeSegIdNum;k++)
                            {
                                if (BnfLogicSectionDataStru[j].segIdBuff[i] == BnfLogicSectionDataStru[bufIndex].segIdBuff[k])
                                {
                                    if (BnfLogicSectionDataStru[j].segIdBuff[i] == BnfLogicSectionDataStru[j].startSegId)
                                    {
                                        relateLogicInfo[*relateLogicNum].pointFalg = START_POINT;
                                    }
                                    else if (BnfLogicSectionDataStru[j].segIdBuff[i] == BnfLogicSectionDataStru[j].endSegId)
                                    {
                                        relateLogicInfo[*relateLogicNum].pointFalg = END_POINT;
                                    }
                                    else
                                    {
                                        /*Do nothing currently !*/
                                    }
                                    relateLogicInfo[*relateLogicNum].relateLogicId = BnfLogicSectionDataStru[j].indexId;
                                    relateLogicInfo[*relateLogicNum].relateSegId = BnfLogicSectionDataStru[j].segIdBuff[i];
                                    (*relateLogicNum)++;
                                    findFlag = 1u;
                                    findNum += 1u;
                                    break;
                                }
                            }

                            if (1u == findFlag)
                            {
                                break;
                            }
                        }

                        if (findNum == (BnfLogicSectionDataStru[j].includeSegIdNum -1u))
                        {
                            break;
                        }
                    }
                }
            }

            retVal = 1u;
        }
        else
        {
            /*Do nothing currently !*/
        }

    }

    return retVal;
}
