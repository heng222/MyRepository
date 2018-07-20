
/********************************************************                                                                                                           
 文 件 名： ChangeLogicManager.c   
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 切换区域逻辑处理管理  
 备注： 无  
********************************************************/ 

#include "ChangeConfigData.h"
#include "ChangeLogicManager.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../AC/ACConfigData.h"

/*************************************************
  函数名:  JudgeACIsChangeEnd    
  功能描述: 检查输入计轴ID是否属于切换区域终端计轴
  输入: const UINT16 acId 待判定计轴
            const UINT8_S dir 运行方向
  输出: 无
  返回值: RETURN_ERROR 失败
             FLAG_SET  属于
			 FLAG_UNSET 不属于
*************************************************/
UINT8_S JudgeACIsChangeEnd(const UINT16_S acId,const UINT8_S dir)
{
	UINT16_S cycle = 0U;
	UINT16_S endLink = 0U;
	UINT32_S endOffset = 0U;
	UINT16_S endAcId = 0U;
	UINT8_S rtnValue = FLAG_UNSET;
	UINT16_S changeLineId = DEFAULT_ZERO;

	for (cycle = 0U;cycle < GetChangeLineSum();cycle++)
	{
		/*获取切换线路ID*/
		changeLineId = GetChangeLineId(cycle);
		if (GetChangeLineDir(changeLineId) == dir)
		{
			endLink = GetChangeLineEndLink(changeLineId);
			endOffset = GetChangeLineEndOffset(changeLineId);

			endAcId = CheckPositionBelongAc(endLink);

			if (RETURN_ERROR != endAcId)
			{
				if (acId == endAcId)
				{
					rtnValue = FLAG_SET;
					break;
				}
				else
				{
					/*继续遍历*/
				}
			}
			else
			{
				rtnValue = RETURN_ERROR;
				break;
			}
		} 
		else
		{
            /*不处理*/
		}
	}

	return rtnValue;
}

/*************************************************
  函数名: JudgeAcIsInChangeLine     
  功能描述: 检查输入计轴ID是否属于沿指定方向切换区域
  输入: const UINT16 acId 待判定计轴   
       const UINT8_S trainDir 方向
  输出: 无
  返回值: RETURN_SUCESS  属于
			 RETURN_ERROR 不属于
*************************************************/
UINT8_S JudgeAcIsInChangeLine(const UINT16_S acId,const UINT8_S trainDir)
{
    UINT16_S changeCycle = 0U;
    UINT16_S acNum = 0U;
    UINT8_S acCycle = 0U;
    UINT8_S rtnValue = 0U;
    ChangeBitTableStruct* pObsOfAcStru = NULL;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S getAcRtn = DEFAULT_ZERO;
    UINT8_S acChangeDir = DEFAULT_ZERO; /* 区段支持的切换方向 */

    for (changeCycle = 0U;changeCycle < GetChangeAreaConfigSum();changeCycle++)
    {
        /*获取计轴区段数量*/
        getAcRtn = GetObsBitTableNumOfIndex((UINT8_S)changeCycle,OBS_TYPE_AC,&acNum);

        pObsOfAcStru = GetObsBitTableStrInfoOfIndex((UINT8_S)changeCycle,OBS_TYPE_AC);

        if ((NULL != pObsOfAcStru) &&(RETURN_SUCCESS == getAcRtn))
        {
            for (acCycle = 0U;acCycle < acNum;acCycle++)
            {
#if 0
                /*判断计轴是否位于切换区域范围内*/
                if (acId == pObsOfAcStru[acCycle].ObsId)
                {
                    rtnValue = RETURN_SUCCESS;
                    breakFlag = FLAG_SET;
                    break;
                }
                else
                {
                    /*继续遍历*/
                }
#else
                acChangeDir = pObsOfAcStru[acCycle].ChageDir;
                /* 判断计轴是否位于切换区域范围内和区段支持的切换方向 */
                if ((acId == pObsOfAcStru[acCycle].ObsId) 
                    && ((acChangeDir == trainDir) || (acChangeDir == AC_CHANGER_DIR_DOUBLE)))
                {
                    rtnValue = RETURN_SUCCESS;
                    breakFlag = FLAG_SET;
                    break;
                }
                else
                {
                    /*继续遍历*/
                }
#endif
            }
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }

        if (FLAG_SET == breakFlag)
        {
            break;
        } 
        else
        {
            /*不处理*/
        }	
    }

    return rtnValue;
}


/*
* 功能描述： 计算切换区域内本ZC管辖范围内的逻辑区段信息
* 参数说明： UINT16_S *logicNum，
*            UINT16_S logicIdBuff[CHANGE_AREA_LOGIC_MAX]
* 返回值  ： 1,计算成功
*            2,计算失败
*/
UINT8_S CalculatChangeAreaLogicInfoOfZc(UINT16_S zcId,UINT16_S *logicNum,UINT16_S logicIdBuff[])
{
	UINT8_S rtn = RETURN_ERROR;
	ChangeBitTableStruct *tempChangeBitTableStr = NULL;
	UINT16_S pObsNum = DEFAULT_ZERO;
	UINT8_S checkObsNum = DEFAULT_ZERO;
	UINT16_S cycleObs = DEFAULT_ZERO;
	UINT16_S logicOfAcNum = DEFAULT_ZERO;
	UINT16_S logicOfAcIdBuff[SIZE_MAX_SECTIONNUM] = {DEFAULT_ZERO};
	UINT8_S checkLogicOfAcRtn = DEFAULT_ZERO;
	UINT16_S cycleLogic = DEFAULT_ZERO;

	/*获取切换线路信息*/
	tempChangeBitTableStr = GetObsBitTableStrInfo(GetLocalZcId(), zcId, OBS_TYPE_AC);
	checkObsNum = GetObsBitTableNum(GetLocalZcId(), zcId, OBS_TYPE_AC, &pObsNum);

	(*logicNum) = DEFAULT_ZERO;

	if ((RETURN_ERROR != checkObsNum) && (NULL != tempChangeBitTableStr))
	{
		for (cycleObs = DEFAULT_ZERO; cycleObs < pObsNum;cycleObs++)
		{
			/*查询计轴区段对应的逻辑区段ID*/
			logicOfAcNum = GetAcLogicSectionNum(tempChangeBitTableStr[cycleObs].ObsId);
			checkLogicOfAcRtn = GetAcLogicSectionIdBuf(tempChangeBitTableStr[cycleObs].ObsId,SIZE_MAX_SECTIONNUM,logicOfAcIdBuff);
			
			if (RETURN_SUCCESS == checkLogicOfAcRtn)
			{
				for (cycleLogic = DEFAULT_ZERO;cycleLogic < logicOfAcNum;cycleLogic++)
				{
					logicIdBuff[(*logicNum)] = logicOfAcIdBuff[cycleLogic];
					(*logicNum)++;
				}

				rtn = RETURN_SUCCESS;
			} 
			else
			{
				rtn = RETURN_ERROR;
				break;
			}
		}
	} 
	else
	{
		rtn = RETURN_ERROR;
	}

	return rtn;
}


