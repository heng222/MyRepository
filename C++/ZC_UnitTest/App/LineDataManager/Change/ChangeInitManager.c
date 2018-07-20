
/********************************************************                                                                                                           
 文 件 名： ChangeInitManager.c   
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 切换区域初始化管理  
 备注： 无  
********************************************************/ 

#include "ChangeConfigData.h"
#include "ChangeInitManager.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Dmu/DmuComm/Data/LineSwitchInfoData.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../IOManager/CommTarget/CommTargetConfigData.h"
#include "../../../Common/Malloc.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern ChangeLineConfigDataStruct gChangeLineConfigDataStruBuff[CHANGE_LINE_LOCAL_SUM_MAX];     /*引用本地管理的切换线路配置信息*/
extern UINT16_S  gChangeLineIdBuff[CHANGE_LINE_SUM_MAX];                                            /*引用定义切换线路映射数组*/
extern UINT16_S  gChangeLineCurSum;                                                                          /*引用切换线路当前总数*/

extern ChangeAreaConfigStruct* gpChangeAreaConfigStruBuff;             /*引用本地管理的切换区域配置信息*/
extern UINT16_S   gChangeAreaIdBuff[CHANGE_AREA_SUM_MAX];                                           /*引用定义切换区域映射数组*/
extern UINT16_S   gChangeAreaCurSum;                                                                         /*引用切换区域当前总数*/

/*************************************************
  函数名:   InitChangeLineInitializationData   
  功能描述: 初始化本地管理的切换线路初始信息
  输入: 无   
  输出: 无
  返回值: 无     
*************************************************/
void InitChangeLineInitializationData(void)
{
    UINT16_S cycle = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < CHANGE_LINE_SUM_MAX;cycle++)
    {
        gChangeLineIdBuff[cycle] = CHANGE_LINE_SUM_MAX;
    }
}

/*************************************************
  函数名:  InitChangeInfo    
  功能描述: 初始化切换区域数据
  输入: void 
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeInfo(void)
{
    UINT16_S initErrorFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*初始化切换线路数据*/
    if (RETURN_SUCCESS == InitChangeLineInfo())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
    }

    /*初始化切换区域数据*/
    if (RETURN_SUCCESS == InitChangeAreaMaskInfo())
    {
        /*不处理*/
    }
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
    }

    if (DEFAULT_ZERO == initErrorFlag)
    {
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    LogPrintf(1U,"InitChangeInfo Error %d\n",initErrorFlag);
    return rtnValue;
}

/*************************************************
  函数名:   InitChangeLineInfo   
  功能描述: 初始化切换线路数据
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeLineInfo(void)
{
    UINT16_S cLIdBuff[CHANGE_LINE_LOCAL_SUM_MAX] = {DEFAULT_ZERO};
    BnfSngSwitchInfoStruct *pSwitchInfoInChangeLineStru = NULL;
    UINT16_S switchNum = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S cycleSwitch = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;
	UINT16_S handOverZcId = DEFAULT_ZERO;
	UINT16_S takeOverZcId = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;

    /*初始化*/
    MemorySet(&cLIdBuff[0],((UINT32_S)(SIZE_UINT16 * CHANGE_LINE_LOCAL_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * CHANGE_LINE_LOCAL_SUM_MAX)));
    InitChangeLineInitializationData();

	localZcId = GetLocalZcId();

    /*获取本ZC对应的切换线路的数量*/
    gChangeLineCurSum = GetLocalZcChangeLineNum(GetLocalZcId(),cLIdBuff);

    if ((gChangeLineCurSum > DEFAULT_ZERO) && (gChangeLineCurSum <= CHANGE_LINE_LOCAL_SUM_MAX))
    {
        /*获取各切换线路数据*/
        for (cycle = DEFAULT_ZERO;cycle < gChangeLineCurSum;cycle++)
        {
            if ((DEFAULT_ZERO < cLIdBuff[cycle]) && (CHANGE_LINE_SUM_MAX >= cLIdBuff[cycle]))
            {
				handOverZcId = GetLineSwitchInfoDataStrulineSwitchTraZcId(cLIdBuff[cycle]);
				takeOverZcId = GetLinSwInfDatliSwTakeOvZcId(cLIdBuff[cycle]);

                if ((handOverZcId == localZcId) || (takeOverZcId == localZcId))
                {
					/*设置索引*/
					gChangeLineIdBuff[cLIdBuff[cycle]] = cycle;

					/*设置单个结构信息*/
					gChangeLineConfigDataStruBuff[cycle].ChangeLineId = cLIdBuff[cycle];

					gChangeLineConfigDataStruBuff[cycle].HandOverZcId = handOverZcId;

					gChangeLineConfigDataStruBuff[cycle].TakeOverZcId = takeOverZcId;

					gChangeLineConfigDataStruBuff[cycle].ChangeDir = GetLineSwInfoDatalineSwDir(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangeLineStartLink = GetLineSwitchInfoDataStrustartLineSwitchInfoId(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangeLineStartOffset = GetLineSwitchInfoDataStrustartSegOffset(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangePointLink = GetLineSwitchInfoDataStruswitchPointSegId(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangePointOffset = GetLineSwInfoDataSwPointOff(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangeLineEndLink = GetLineSwitchInfoDataStruendLineSwitchInfoId(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangeLineEndOffset = GetLineSwitchInfoDataStrusegEndOffset(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].RelevanceRouteId = GetLineSwitchInfoDataStrurelationRouteNum(cLIdBuff[cycle]);

					/*获取本条切换线路对应的道岔及应有状态*/
					switchNum = GetLineSwitchInfoDataStruincludeSwitchNum(cLIdBuff[cycle]);
					pSwitchInfoInChangeLineStru = GetLineSwInfDataSwInfStru(cLIdBuff[cycle]);

					if ((switchNum <= CHANGE_LINE_SWITCH_MAX)
						&& (NULL != pSwitchInfoInChangeLineStru))
					{
						gChangeLineConfigDataStruBuff[cycle].SwitchNum = (UINT8_S)switchNum;

						for(cycleSwitch = DEFAULT_ZERO;cycleSwitch < switchNum;cycleSwitch++)
						{
							gChangeLineConfigDataStruBuff[cycle].SwitchStruBuff[cycleSwitch].SwitchId = pSwitchInfoInChangeLineStru[cycleSwitch].switchId;
							gChangeLineConfigDataStruBuff[cycle].SwitchStruBuff[cycleSwitch].SwitchNeedStatus = (UINT8_S)pSwitchInfoInChangeLineStru[cycleSwitch].switchStatus;
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
					/* 不处理 */
                }
            } 
            else
            {
                rtnValue = RETURN_ERROR;
                break;
            }
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:   InitZcNZcMaskConfigCommTargetData   
  功能描述: 初始化ZC-NZC码位配置信息中码位信息
  输入: 无   
  输出: 无
  返回值: 0: 初始化失败
			>0: 初始化成功      
*************************************************/
UINT8_S InitZcNZcMaskConfigCommTargetData(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetId = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};

    MemorySet(&commTargetIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    typeBuffIndex = GetCommTargetTypeBuffIndex(INNER_DEVTYPE_ZC);

    GetSingleCommTargetIdBuff(INNER_DEVTYPE_ZC,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

    for (cycle = DEFAULT_ZERO;cycle < GetSingleCommTargetTypeSum(INNER_DEVTYPE_ZC);cycle++)
    {
        commTargetId = commTargetIdBuff[cycle];

        if ((gChangeAreaCurSum <= COMM_ZC_SUM_MAX) 
            && (LINE_ZC_SUM_MAX > commTargetId))
        {
            /*填写本ZC输出的Id信息*/
            gpChangeAreaConfigStruBuff[gChangeAreaCurSum].LocalZcId = GetLocalZcId();
            gpChangeAreaConfigStruBuff[gChangeAreaCurSum].NextZcId = commTargetId;
            gChangeAreaIdBuff[commTargetId] = gChangeAreaCurSum;

            gChangeAreaCurSum++;

            /*填写相邻ZC输入本Zc的Id信息*/
            gpChangeAreaConfigStruBuff[gChangeAreaCurSum].LocalZcId = commTargetId;
            gpChangeAreaConfigStruBuff[gChangeAreaCurSum].NextZcId = GetLocalZcId();
            gChangeAreaIdBuff[commTargetId] = gChangeAreaCurSum;

            gChangeAreaCurSum++;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
            break;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:    InitChangeAreaMaskInfo  
  功能描述: 初始化切换区域码位数据
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
*			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaMaskInfo(void)
{
    UINT16_S initErrorFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*初始化通信关系*/
    if (RETURN_SUCCESS == InitZcNZcMaskConfigCommTargetData())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
    }

    /*初始化道岔信息*/
    if (RETURN_SUCCESS == InitChangeAreaOfSwitchMask())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
    }

    /*初始信号机信息*/
    if (RETURN_SUCCESS == InitChangeAreaOfSignalMask())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
    }

    /*初始化屏蔽门信息*/
    if (RETURN_SUCCESS == InitChangeAreaOfPsdMask())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_4);
    }

    /*初始化紧急停车按钮信息*/
    if (RETURN_SUCCESS == InitChangeAreaOfEsbMask())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_5);
    }

    /*初始化计轴区段信息*/
    if (RETURN_SUCCESS == InitChangeAreaOfAcMask())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_6);
    }

    /*初始化进路信息*/
    if (RETURN_SUCCESS == InitChangeAreaOfRouteMask())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_7);
    }

    /*初始化保护区段信息*/
    if (RETURN_SUCCESS == InitChangeAreaOfOverlapMask())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_8);
    }

    /*初始化无人折返信息*/
    if (RETURN_SUCCESS == InitChangeAreaOfDrMask())
    {
        /*不处理*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_9);
    }

    if (DEFAULT_ZERO == initErrorFlag)
    {
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue =  RETURN_ERROR;
    }

    LogPrintf(1U,"InitChangeAreaMaskInfo Error %d\n",initErrorFlag);
    return rtnValue;
}

/*************************************************
  函数名:   InitChangeAreaOfSwitchMask   
  功能描述: 初始化切换区域码位数据(道岔数据)
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfSwitchMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* 配置文件中的ZC的编号 */

    /*读取文件中的道岔信息总和*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_SWITCHCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*分配内存大小*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_SWITCH_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*查询成功*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_SWITCH_MASK_SUM)
            {
                /*解析数据*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*解析输出方ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*相邻ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物状态码位*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物锁闭码位*/
                obsLockMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (obsLockMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchNum;

                        if (obsNum < CHANGE_AREA_SWITCH_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*该表无数据*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:  InitChangeAreaOfSignalMask    
  功能描述: 初始化切换区域码位数据(信号机数据)
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
*			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfSignalMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* 配置文件中的ZC的编号 */

    /*读取文件中的信号机信息总和*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_SIGNCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*分配空间*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_SIGNAL_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*查询成功*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_SIGNAL_MASK_SUM)
            {
                /*解析数据*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*解析输出方ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*相邻ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物状态码位*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId(); 

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalNum;

                        if (obsNum < CHANGE_AREA_SIGNAL_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*该表无数据*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:   InitChangeAreaOfPsdMask   
  功能描述: 初始化切换区域码位数据(屏蔽门数据)
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfPsdMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* 配置文件中的ZC的编号 */

    /*读取文件中的屏蔽门信息总和*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_PSDCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*分配空间*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_PSD_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*查询成功*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_PSD_MASK_SUM)
            {
                /*解析数据*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*解析输出方ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*相邻ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物状态码位*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdNum;

                        if (obsNum < CHANGE_AREA_PSD_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*该表无数据*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:    InitChangeAreaOfEsbMask  
  功能描述: 初始化切换区域码位数据(紧急停车按钮数据)
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfEsbMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* 配置文件中的ZC的编号 */

    /*读取文件中的紧急停车按钮信息总和*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_ESBCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*分配空间*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_ESB_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*查询成功*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_ESB_MASK_SUM)
            {
                /*解析数据*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*解析输出方ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*相邻ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物状态码位*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbNum;

                        if (obsNum < CHANGE_AREA_ESB_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*该表无数据*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:   InitChangeAreaOfAcMask   
  功能描述: 初始化切换区域码位数据(计轴区段数据)
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfAcMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* 配置文件中的ZC的编号 */
    UINT8_S chageDir = DEFAULT_ZERO;  /* 此区段可以切换的方向 */

    /*读取文件中的计轴区段信息总和*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_AXLESECCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*分配空间*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_AC_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*查询成功*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_AC_MASK_SUM)
            {
                /*解析数据*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*解析输出方ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*相邻ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物状态码位*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /* 区段可做切换的方向 */
                chageDir= *pMaskData;
                pMaskData += 1U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcNum;

                        if (obsNum < CHANGE_AREA_AC_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            /* 2017.8.1 赋方向;0x55:正切;0xaa:反切;0xcc:正反切;0x00:不能切 */
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcBitStruBuff[obsNum].ChageDir = chageDir;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*该表无数据*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:   InitChangeAreaOfRouteMask   
  功能描述: 初始化切换区域码位数据(进路数据)
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfRouteMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* 配置文件中的ZC的编号 */

    /*读取文件中的进路信息总和*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_ROUTECODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*分配空间*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_ROUTE_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*查询成功*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_ROUTE_MASK_SUM)
            {
                /*解析数据*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*解析输出方ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*相邻ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物状态码位*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteNum;

                        if (obsNum < CHANGE_AREA_ROUTE_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*该表无数据*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:   InitChangeAreaOfOverlapMask   
  功能描述: 初始化切换区域码位数据(保护区段数据)
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfOverlapMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* 配置文件中的ZC的编号 */

    /*读取文件中的保护区段信息总和*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_PROSECCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*分配空间*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_OVERLAP_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*查询成功*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_OVERLAP_MASK_SUM)
            {
                /*解析数据*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*解析输出方ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*相邻ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物状态码位*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapNum;

                        if (obsNum < CHANGE_AREA_OVERLAP_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*该表无数据*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:  InitChangeAreaOfDrMask    
  功能描述: 初始化切换区域码位数据(无人折返数据)
  输入: void  
  输出: 无
  返回值: 0: 初始化失败
			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfDrMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* 配置文件中的ZC的编号 */

    /*读取文件中的无人折返信息总和*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_ARCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*分配空间*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_DR_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*查询成功*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_DR_MASK_SUM)
            {
                /*解析数据*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*解析输出方ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*相邻ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物状态码位*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*障碍物锁闭状态码位*/
                obsLockMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (obsLockMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        /*更新无人折返灯站台*/
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrLampNum;

                        if (obsNum < CHANGE_AREA_DRLAMP_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrLampBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrLampBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrLampNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
                        }

                        /*更新无人折返按钮站台*/
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrButtonNum;

                        if (obsNum < CHANGE_AREA_DRBUTTON_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrButtonBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrButtonBitStruBuff[obsNum].StateBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrButtonNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
                    /*Do nothing currently !*/
                }
            }
        } 
        else
        {
            /*该表无数据*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*不处理*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}
