/************************************************************************
*
* 文件名   ：  TsrLogicManager.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  临时限速逻辑处理管理
* 备  注   ：  无
*
************************************************************************/
#include "TsrLogicManager.h"
#include "TsrStatusData.h"
#include "../../../Common/Copy.h"
#include "../../../Common/MemSet.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"

/*
* 功能描述： 删除某个ZCID的临时限速信息
* 参数说明： const UINT16 zcId, Id信息    
* 返回值  ： 无     
*/
void DeleteSingleZcTsrInfo(const UINT16_S zcId)
{
	UINT8_S bufIndex = DEFAULT_ZERO;
	TsrDataStruct *tsrDataStru = NULL;

	/*获取zcId对应的下标*/
	bufIndex = GeZcIdOfTsrBufIndex(zcId);

	if (TSR_BUFF_SUM_MAX > bufIndex)
	{
		tsrDataStru = GeTsrDataStructOfIndex((UINT16_S)bufIndex);
		
		/*清除数据*/
		if (NULL != tsrDataStru)
		{
			tsrDataStru->TsrNum = DEFAULT_ZERO;
			MemorySet(tsrDataStru->SingleTsrDataStru,((UINT32_S)(sizeof(SingleTsrDataStruct)*SINGLE_ZC_TSR_SUM_MAX)),
                DEFAULT_ZERO,((UINT32_S)(sizeof(SingleTsrDataStruct)*SINGLE_ZC_TSR_SUM_MAX)));
		} 
		else
		{
            /*不处理*/
		}
	} 
	else
	{
        /*不处理*/
	}
}

/*
* 功能描述： 查询相邻ZC传来的临时限速信息是否在本ZC中
* 参数说明： const UINT16_S startLink, 起点Link 
*            const UINT32_S startOffset, 起点Offset
*            const UINT16_S endLink,  终点Link
*            const UINT32_S endOffset 终点Offset
* 返回值  ： 无    
*/
UINT8_S CheckMaTsrInLocalZc(const UINT16_S startLink,const UINT32_S startOffset,const UINT16_S endLink,const UINT32_S endOffset)
{
    UINT8_S cycleTsr = DEFAULT_ZERO;
    UINT8_S cycleLogic = DEFAULT_ZERO;
    UINT8_S cycleSec = DEFAULT_ZERO;
    UINT16_S zcId = DEFAULT_ZERO;       /* 本ZC的编号 */
    UINT8_S tsrSum = DEFAULT_ZERO;     /* 本ZC临时限速总数 */
    UINT8_S checkDir = DEFAULT_ZERO;    /* 查询方向 */
    UINT8_S rtnLocation = DEFAULT_ZERO; /* 逻辑关系远近返回值 */
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
        /* 不处理 */
    }

    /* 查询2点之间所有的逻辑区段 */
    logicSectionSum = CheckLogicIdBetweenPoints(3u,startLink,startOffset,endLink,endOffset,checkDir,logicSectionIdBuff);

    if (UINT8_MAX != logicSectionSum)
    {
        for (cycleLogic = DEFAULT_ZERO;cycleLogic < logicSectionSum;cycleLogic++)
        {
            /*遍历本ZC所有的临时限速*/
            for (cycleTsr = DEFAULT_ZERO;cycleTsr < tsrSum;cycleTsr++)
            {
                tsrLogicSectionSum = GetSingleTsrDataOfSectionNum(zcId,((UINT16_S)cycleTsr));

                if (RETURN_SUCCESS == GetSingleTsrDataOfSectionBuff(zcId,((UINT16_S)cycleTsr),((UINT8_S)(SINGLE_TSR_SECTION_SUM_MAX)),sectionIdBuff))
                {
                    for(cycleSec = DEFAULT_ZERO;cycleSec < tsrLogicSectionSum;cycleSec++)
                    {
                        if (logicSectionIdBuff[cycleLogic] == sectionIdBuff[cycleSec])
                        {
                            /* 有重合的逻辑区段,跳出cycleSec循环 */
                            retVal = RETURN_SUCCESS;
                            breakFlag1 = FLAG_SET;
                            break;
                        }
                    }
                }
                
                if (FLAG_SET == breakFlag1)
                {
                    /* 已经找到重合的逻辑区段,跳出cycleTsr循环 */
                    breakFlag2 = FLAG_SET;
                    break;
                }
            }

            if (FLAG_SET == breakFlag2)
            {
                /* 已经找到重合的逻辑区段,跳出cycleLogic循环 */
                break;
            }
        }
    }

    return retVal;
}