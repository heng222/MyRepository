/************************************************************************
*
* �ļ���   ��  TsrLogicManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��ʱ�����߼��������
* ��  ע   ��  ��
*
************************************************************************/
#include "TsrLogicManager.h"
#include "TsrStatusData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"

/*
* ���������� ɾ��ĳ��ZCID����ʱ������Ϣ
* ����˵���� const UINT16 zcId, Id��Ϣ    
* ����ֵ  �� ��     
*/
void DeleteSingleZcTsrInfo(const UINT16_S zcId)
{
	UINT8_S bufIndex = DEFAULT_ZERO;
	TsrDataStruct *tsrDataStru = NULL;

	/*��ȡzcId��Ӧ���±�*/
	bufIndex = GeZcIdOfTsrBufIndex(zcId);

	if (TSR_BUFF_SUM_MAX > bufIndex)
	{
		tsrDataStru = GeTsrDataStructOfIndex((UINT16_S)bufIndex);
		
		/*�������*/
		if (NULL != tsrDataStru)
		{
			tsrDataStru->TsrNum = DEFAULT_ZERO;
			MemorySet(tsrDataStru->SingleTsrDataStru,((UINT32_S)(sizeof(SingleTsrDataStruct)*SINGLE_ZC_TSR_SUM_MAX)),
                DEFAULT_ZERO,((UINT32_S)(sizeof(SingleTsrDataStruct)*SINGLE_ZC_TSR_SUM_MAX)));
		} 
		else
		{
            /*������*/
		}
	} 
	else
	{
        /*������*/
	}
}

/*
* ���������� ��ѯ����ZC��������ʱ������Ϣ�Ƿ��ڱ�ZC��
* ����˵���� const UINT16_S startLink, ���Link 
*            const UINT32_S startOffset, ���Offset
*            const UINT16_S endLink,  �յ�Link
*            const UINT32_S endOffset �յ�Offset
* ����ֵ  �� ��    
*/
UINT8_S CheckMaTsrInLocalZc(const UINT16_S startLink,const UINT32_S startOffset,const UINT16_S endLink,const UINT32_S endOffset)
{
    UINT8_S cycleTsr = DEFAULT_ZERO;
    UINT8_S cycleLogic = DEFAULT_ZERO;
    UINT8_S cycleSec = DEFAULT_ZERO;
    UINT16_S zcId = DEFAULT_ZERO;       /* ��ZC�ı�� */
    UINT8_S tsrSum = DEFAULT_ZERO;     /* ��ZC��ʱ�������� */
    UINT8_S checkDir = DEFAULT_ZERO;    /* ��ѯ���� */
    UINT8_S rtnLocation = DEFAULT_ZERO; /* �߼���ϵԶ������ֵ */
    UINT16_S logicSectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX] = {0U};
    UINT16_S  sectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX] = {0U};
    UINT8_S logicSectionSum = DEFAULT_ZERO;
    UINT8_S tsrLogicSectionSum = DEFAULT_ZERO;
    UINT8_S retVal = RETURN_ERROR;
    UINT8_S breakFlag1 = FLAG_UNSET;
    UINT8_S breakFlag2= FLAG_UNSET;

    MemorySet(&logicSectionIdBuff[DEFAULT_ZERO],((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)));
    MemorySet(&sectionIdBuff[DEFAULT_ZERO],((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TSR_SECTION_SUM_MAX)));

    zcId = GetLocalZcId();
    tsrSum = GetZcIdOfTsrNum(zcId);

    rtnLocation = CheckLocRelationBetweenTwoPoints(startLink,startOffset,endLink,endOffset,LINESEG_SAME_DIR);

    if ((2u == rtnLocation) || (3u == rtnLocation))
    {
        checkDir = LINESEG_SAME_DIR;
    } 
    else if(1u == rtnLocation)
    {
        checkDir = LINESEG_CONVER_DIR;
    }
    else
    {
        /* ������ */
    }

    /* ��ѯ2��֮�����е��߼����� */
    logicSectionSum = CheckLogicIdBetweenPoints(3u,startLink,startOffset,endLink,endOffset,checkDir,logicSectionIdBuff);

    if (UINT8_MAX != logicSectionSum)
    {
        for (cycleLogic = DEFAULT_ZERO;cycleLogic < logicSectionSum;cycleLogic++)
        {
            /*������ZC���е���ʱ����*/
            for (cycleTsr = DEFAULT_ZERO;cycleTsr < tsrSum;cycleTsr++)
            {
                tsrLogicSectionSum = GetSingleTsrDataOfSectionNum(zcId,((UINT16_S)cycleTsr));

                if (RETURN_SUCCESS == GetSingleTsrDataOfSectionBuff(zcId,((UINT16_S)cycleTsr),((UINT8_S)(SINGLE_TSR_SECTION_SUM_MAX)),sectionIdBuff))
                {
                    for(cycleSec = DEFAULT_ZERO;cycleSec < tsrLogicSectionSum;cycleSec++)
                    {
                        if (logicSectionIdBuff[cycleLogic] == sectionIdBuff[cycleSec])
                        {
                            /* ���غϵ��߼�����,����cycleSecѭ�� */
                            retVal = RETURN_SUCCESS;
                            breakFlag1 = FLAG_SET;
                            break;
                        }
                    }
                }
                
                if (FLAG_SET == breakFlag1)
                {
                    /* �Ѿ��ҵ��غϵ��߼�����,����cycleTsrѭ�� */
                    breakFlag2 = FLAG_SET;
                    break;
                }
            }

            if (FLAG_SET == breakFlag2)
            {
                /* �Ѿ��ҵ��غϵ��߼�����,����cycleLogicѭ�� */
                break;
            }
        }
    }

    return retVal;
}