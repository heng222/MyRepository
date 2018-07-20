
/********************************************************                                                                                                           
 文 件 名： ChangeConfigData.c   
 作    者： ZC组
 创建时间： 2015.04.18
 描述： 切换区域配置数据  
 备注： 无  
********************************************************/ 

#include "ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/SwitchData.h"
#include "../../../Dmu/DmuComm/Data/SignData.h"
#include "../../../Dmu/DmuComm/Data/ShieldDoorData.h"
#include "../../../Dmu/DmuComm/Data/EmergStopButtonData.h"
#include "../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "../../../Dmu/DmuComm/Data/RouteData.h"
#include "../../../Dmu/DmuComm/Data/ProtectZoneData.h"
#include "../../../Dmu/DmuComm/Data/ArData.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../IOManager/CommTarget/CommTargetConfigData.h"
#include "../../SysDataManager/SysConfigData.h"

ChangeLineConfigDataStruct gChangeLineConfigDataStruBuff[CHANGE_LINE_LOCAL_SUM_MAX];     /*本地管理的切换线路配置信息*/
UINT16_S  gChangeLineIdBuff[CHANGE_LINE_SUM_MAX] = {CHANGE_AREA_SUM_MAX};          /*定义切换线路映射数组*/
UINT16_S  gChangeLineCurSum = 0U;                                                                      /*切换线路当前总数*/

ChangeAreaConfigStruct* gpChangeAreaConfigStruBuff = NULL;             /*本地管理的切换区域配置信息*/
UINT16_S   gChangeAreaIdBuff[CHANGE_AREA_SUM_MAX] = {CHANGE_AREA_SUM_MAX};         /*定义切换区域映射数组*/
UINT16_S   gChangeAreaCurSum = 0U;                                                                     /*切换区域当前总数*/

/*************************************************
  函数名:  GetChangeLineSum    
  功能描述: 获取切换线路总数
  输入: void    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 切换线路当前总数
*************************************************/
UINT16_S GetChangeLineSum(void)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (gChangeLineCurSum >= CHANGE_LINE_LOCAL_SUM_MAX)
    {
        rtnValue = 0U;
    } 
    else
    {
        rtnValue = gChangeLineCurSum;
    }

    return rtnValue;
}

/*************************************************
  函数名:  GetChangeLineId    
  功能描述: 获取指定数组下标对应的切换线路ID
  输入: const UINT16 bufIndex, 数组下标    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 切换线路ID      
*************************************************/
UINT16_S GetChangeLineId(const UINT16_S bufIndex)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].ChangeLineId;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:  GetChangeLineConfigBufIndex    
  功能描述: 获取指定ID切换线路索引号
  输入: const UINT16 changeLineId,切换线路ID
  输出: 无
  返回值: CHANGE_LINE_SUM_MAX: 获取数据失败
			  >=0查找索引成功
*************************************************/
UINT16_S GetChangeLineConfigBufIndex(const UINT16_S changeLineId)
{
    UINT16_S rtnValue = CHANGE_LINE_SUM_MAX;

    if ((changeLineId >= 1U)&&(changeLineId < CHANGE_LINE_SUM_MAX))
    {
        rtnValue = gChangeLineIdBuff[changeLineId];
    }
    else
    {
        rtnValue = CHANGE_LINE_SUM_MAX;
    }

    return rtnValue;
}

/*************************************************
  函数名:   GetChangeLineDir   
  功能描述: 获取指定切换线路ID对应的切换方向
  输入: const UINT16 changeLineId, 切换线路ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 切换方向      
*************************************************/
UINT8_S GetChangeLineDir(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT8_S rtnValue = DEFAULT_ZERO;


    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].ChangeDir;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:    GetChangeLineHandOverZcId  
  功能描述: 获取指定切换线路ID对应的移交ZCid
  输入: const UINT16 changeLineId, 切换线路ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 移交ZCid      
*************************************************/
UINT16_S GetChangeLineHandOverZcId(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].HandOverZcId;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}



/*************************************************
  函数名:   GetChangeLineTakeOverZcId   
  功能描述: 获取指定切换线路ID对应的接管ZCid
  输入: const UINT16 changeLineId, 切换线路ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 接管ZCid      
*************************************************/
UINT16_S GetChangeLineTakeOverZcId(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].TakeOverZcId;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:   GetChangeLineStartLink   
  功能描述: 获取指定切换线路ID对应的起点link
  输入: const UINT16 changeLineId, 切换线路ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 起点link     
*************************************************/
UINT16_S GetChangeLineStartLink(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex]. ChangeLineStartLink;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:   GetChangeLineStartOffset   
  功能描述: 获取指定切换线路ID对应的起点offset
  输入: const UINT16 changeLineId, 切换线路ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: offset      
*************************************************/
UINT32_S GetChangeLineStartOffset(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT32_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex]. ChangeLineStartOffset;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:   GetChangeLineChangePointLink   
  功能描述: 获取指定切换线路ID对应的切换点link
  输入: const UINT16 changeLineId, 切换线路ID  
  输出: 无
  返回值: 0: 获取数据失败
			>0: 切换点link      
*************************************************/
UINT16_S GetChangeLineChangePointLink(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].ChangePointLink;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
    return rtnValue;
}

/*************************************************
  函数名:   GetChangeLineChangePointOffset   
  功能描述: 获取指定切换线路ID对应的切换点offset
  输入: const UINT16 changeLineId, 切换线路ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: offset      
*************************************************/
UINT32_S GetChangeLineChangePointOffset(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT32_S rtnValue= DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].ChangePointOffset;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:   GetChangeLineEndLink   
  功能描述: 获取指定切换线路ID对应的终点link
  输入: const UINT16 changeLineId, 切换线路ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 终点Link      
*************************************************/
UINT16_S GetChangeLineEndLink(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex]. ChangeLineEndLink;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:  GetChangeLineEndOffset    
  功能描述: 获取指定切换线路ID对应的终点offset
  输入: const UINT16 changeLineId, 切换线路ID   
  输出: 无
  返回值: 0: 获取数据失败
			>0: offset      
*************************************************/
UINT32_S GetChangeLineEndOffset(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT32_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex]. ChangeLineEndOffset;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:    GetChangeLineRelevanceRouteId  
  功能描述: 获取指定切换线路ID对应的进路ID
  输入: const UINT16 changeLineId, 切换线路ID 
  输出: 无
  返回值: 0: 获取数据失败
			>0: 进路ID      
*************************************************/
UINT16_S GetChangeLineRelevanceRouteId(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].RelevanceRouteId;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:  GetChangeLineSwitchNum    
  功能描述: 获取指定切换线路ID对应的道岔数量
  输入: const UINT16 changeLineId, 切换线路ID    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 道岔数量     
*************************************************/
UINT8_S GetChangeLineSwitchNum(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].SwitchNum;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}


/*************************************************
  函数名:   GetChangeLineSwitchStruct   
  功能描述: 获取指定切换线路ID对应的道岔信息
  输入: const UINT16 changeLineId, 切换线路ID    
            const UINT8_S switchStruBufSize, 数组大小
            ChangeLineSwitchStruct switchStruBuff[],输出数组
  输出: ChangeLineSwitchStruct switchStruBuff[] 道岔信息
  返回值: 0: 获取数据失败
			>0: 道岔信息      
*************************************************/
UINT8_S GetChangeLineSwitchStruct(const UINT16_S changeLineId,const UINT8_S switchStruBufSize, ChangeLineSwitchStruct switchStruBuff[])
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT8_S rtnValue = 0U;
    UINT8_S cycle = 0U;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*获取数组下标*/

    if ((bufIndex < GetChangeLineSum())
        && (switchStruBufSize >= CHANGE_LINE_SWITCH_MAX)
        && (switchStruBuff != NULL))
    {
        for (cycle = 0U;cycle < GetChangeLineSwitchNum(changeLineId);cycle++)
        {
            switchStruBuff[cycle].SwitchId = gChangeLineConfigDataStruBuff[bufIndex].SwitchStruBuff[cycle].SwitchId;
            switchStruBuff[cycle].SwitchNeedStatus = gChangeLineConfigDataStruBuff[bufIndex].SwitchStruBuff[cycle].SwitchNeedStatus;
        }
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:  GetChangeAreaConfigSum    
  功能描述: 获取切换区域总数
  输入: void    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 切换线路当前总数
*************************************************/
UINT16_S GetChangeAreaConfigSum(void)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (gChangeAreaCurSum >= CHANGE_AREA_LOCAL_SUM_MAX)
    {
        rtnValue = 0U;
    } 
    else
    {
        rtnValue = gChangeAreaCurSum;
    }

    return rtnValue;
}

/*************************************************
  函数名: GetChangeAreaOfNextZcId     
  功能描述: 获取指定数组下标对应的切换区域对应的ZCID
  输入: const UINT16 bufIndex, 数组下标    
  输出: 无
  返回值: 0: 获取数据失败
			>0: 切换线路ID      
*************************************************/
UINT16_S GetChangeAreaOfNextZcId(const UINT16_S bufIndex)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (bufIndex < GetChangeAreaConfigSum())
    {
        rtnValue = gpChangeAreaConfigStruBuff[bufIndex].NextZcId;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:   GetChangeAreaConfigBufIndex   
  功能描述: 获取指定ID切换区域索引号
  输入: const UINT16 nextZcId,相邻ZCid
            const UINT16_S outputZcId,输出方ZcId
  输出: 无
  返回值:CHANGE_AREA_SUM_MAX: 获取数据失败
		   >=0: 查找索引成功
*************************************************/
UINT16_S GetChangeAreaConfigBufIndex(const UINT16_S outputZcId ,const UINT16_S nextZcId)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S index = CHANGE_AREA_LOCAL_SUM_MAX;

    if ((nextZcId >= 1U)&&(nextZcId < LINE_ZC_SUM_MAX)
        && (outputZcId >= 1U)&&(outputZcId < LINE_ZC_SUM_MAX))
    {
        for (cycle = DEFAULT_ZERO;cycle < gChangeAreaCurSum;cycle++)
        {
            if ((gpChangeAreaConfigStruBuff[cycle].LocalZcId == outputZcId)
                && (gpChangeAreaConfigStruBuff[cycle].NextZcId == nextZcId))
            {
                index = cycle;
                break;
            } 
            else
            {
                /*Do nothing currently !*/
            }
        }
    }
    else
    {
        index = CHANGE_AREA_SUM_MAX;
    }

    return index;
}

/*************************************************
  函数名:    GetChangeAreaObsNum  
  功能描述: 获取指定ID切区域障碍物数量
  输入: const UINT16 nextZcId,相邻ZCid
            const UINT16_S outputZcId,输出方ZcId
  输出: 无
  返回值:0: 获取数据失败
		   >0: 查询成功
*************************************************/
UINT16_S GetChangeAreaObsNum(const UINT16_S outputZcId ,const UINT16_S nextZcId)
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeAreaConfigBufIndex(outputZcId,nextZcId);  /*获取数组下标*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gpChangeAreaConfigStruBuff[bufIndex].ObsNum;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:  GetChangeAreapObsStructBuff    
  功能描述: 获取指定ID切换区域对应障碍物信息
  输入: const UINT16 nextZcId,相邻ZCID
            const UINT16_S outputZcId,输出方ZcId
            const UINT16_S bufSize, 障碍物结构体数组大小
            ChangeAreapObsStruct obsStruBuff[], 输出的障碍物信息数组
  输出: 无
  返回值:0: 获取数据失败
		   >0: 查询成功
*************************************************/
UINT8_S GetChangeAreapObsStructBuff(const UINT16_S outputZcId ,const UINT16_S nextZcId,const UINT16_S bufSize,ChangeAreapObsStruct obsStruBuff[])
{
    UINT16_S bufIndex = 0U;     /*数组下标*/
    UINT8_S rtnValue = 0U;
    UINT16_S cycle = 0U;

    bufIndex = GetChangeAreaConfigBufIndex(outputZcId,nextZcId);  /*获取数组下标*/

    if ((bufIndex < GetChangeLineSum())
        && (bufSize >= CHANGE_AREA_OBS_MAX)
        && (obsStruBuff != NULL))
    {
        for (cycle = 0U;cycle < GetChangeAreaObsNum(outputZcId,nextZcId);cycle++)
        {
            obsStruBuff[cycle].ObsId = gpChangeAreaConfigStruBuff[bufIndex].ObsStruBuff[cycle].ObsId;
            obsStruBuff[cycle].ObsType = gpChangeAreaConfigStruBuff[bufIndex].ObsStruBuff[cycle].ObsType;
        }
        rtnValue = RETURN_SUCCESS ;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
    return rtnValue;
}

/*************************************************
  函数名:   GetLineDeviceBelongZcId    
  功能描述: 获取线路设备所属ZC信息
  输入: 无   
  输出: 无
  返回值: 0: 获取失败
			>0: 所属ZCID      
*************************************************/
UINT16_S GetLineDeviceBelongZcId(const UINT16_S devId,const UINT8_S devType)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    switch (devType)
    {
    case OBS_TYPE_POINT:
        rtnValue = GetLineSwitchBelongZcId(devId);
        break;

    case OBS_TYPE_SIGNAL:
        rtnValue = GetLineSignalBelongZcId(devId);
        break;

    case OBS_TYPE_PSD:
        rtnValue = GetLinePsdBelongZcId(devId);
        break;

    case OBS_TYPE_ESB:
        rtnValue = GetLineEsbBelongZcId(devId);
        break;

    case OBS_TYPE_AC:
        rtnValue = GetLineAcBelongZcId(devId);
        break;

    case OBS_TYPE_LS:
        rtnValue = GetLineAcBelongZcId(GetLineLogicSectionBelongAcId(devId));
        break;

    case OBS_TYPE_ROUTE:
        rtnValue = GetLineRouteBelongZcId(devId);
        break;

    case OBS_TYPE_OVERLAP:
        rtnValue = GetLineOverlapBelongZcId(devId);
        break;

    case OBS_TYPE_DRB:
        rtnValue = GetLineDrButtonBelongZcId(devId);
        break;

    case OBS_TYPE_DRL:
        rtnValue = GetLineDrLampBelongZcId(devId);
        break;

    default:
        rtnValue = DEFAULT_ZERO;
        break;
    }

    return rtnValue;
}

/*************************************************
  函数名:    GetAppointObsInChangeArea  
  功能描述: 获取指定ID和类型的障碍物是否属于切换区域
  输入: const UINT16 obsId 障碍物ID
       const UINT8_S obsType 障碍物类型
  输出: 无
  返回值:0: 获取数据失败（不属于切换区域的相邻ZC）
		    1: 查询成功（属于切换区域的相邻ZC）
*************************************************/
UINT8_S GetAppointObsInChangeArea(const UINT16_S obsId,const UINT8_S obsType)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT16_S cycleObs = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsInfoStru = NULL;
    UINT8_S commTargetNum = 0U;                                           
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};

    /*获取本ZC通信的相邻ZC信息*/
    commTargetNum = GetSingleCommTargetTypeSum(INNER_DEVTYPE_ZC);

    if (RETURN_SUCCESS == GetSingleCommTargetIdBuff(INNER_DEVTYPE_ZC,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff))
    {
        for (cycle = DEFAULT_ZERO;cycle < commTargetNum;cycle++)
        {
            /*初始化局部变量*/
            pObsInfoStru = NULL;
            obsNum = DEFAULT_ZERO;

            /*获取ZC对应的该类型的障碍物数量*/
            GetObsBitTableNum(commTargetIdBuff[cycle],GetLocalZcId(),obsType,&obsNum);

            /*获取ZC对应的该类型的障碍物Id数组*/
            pObsInfoStru = GetObsBitTableStrInfo(commTargetIdBuff[cycle],GetLocalZcId(),obsType);

            if (NULL != pObsInfoStru)
            {
                for (cycleObs = DEFAULT_ZERO;cycleObs < obsNum;cycleObs++)
                {
                    if (obsId == pObsInfoStru[cycleObs].ObsId)
                    {
                        rtnValue = RETURN_SUCCESS;
                        breakFlag = FLAG_SET;
                        break;
                    } 
                    else
                    {
                        /*不处理*/
                    }
                }
            } 
            else
            {
                rtnValue = RETURN_ERROR;
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
  函数名:  GetObsBitTableNum    
  功能描述: 获取指定类型的障碍物的码位数量
  输入: const UINT16 nZcId, 相邻ZCid
            const UINT16_S outputZcId,输出方ZcId
            const UINT8_S obsType 障碍物类型
            UINT16_S *pObsNum 障碍物数量
  输出: 无
  返回值:RETURN_ERROR: 获取数据失败
		    RETURN_SUCCESS: 查询成功
*************************************************/
UINT8_S GetObsBitTableNum(const UINT16_S outputZcId,const UINT16_S nZcId, const UINT8_S obsType, UINT16_S *pObsNum)
{
    UINT16_S index = DEFAULT_UINT16_VALUE;
    UINT8_S flag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (NULL != pObsNum)
    {
        /*初始化输出变量*/
        (*pObsNum) = DEFAULT_ZERO;

        /*计算ZcID对应的数组下标*/
        index = GetChangeAreaConfigBufIndex(outputZcId,nZcId);

        if (CHANGE_AREA_SUM_MAX != index)
        {
            switch (obsType)
            {
            case OBS_TYPE_AC:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].AcNum;
                break;

            case OBS_TYPE_DRB:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].DrButtonNum;
                break;

            case OBS_TYPE_DRL:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].DrLampNum;
                break;

            case OBS_TYPE_POINT:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].SwitchNum;
                break;

            case OBS_TYPE_OVERLAP:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].OverlapNum;
                break;

            case OBS_TYPE_SIGNAL:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].SignalNum;
                break;

            case OBS_TYPE_PSD:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].PsdNum;
                break;

            case OBS_TYPE_ESB:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].EsbNum;
                break;

            case OBS_TYPE_ROUTE:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].RouteNum;
                break;

            case OBS_TYPE_LS:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].LogicSectionNum;
                break;

            default:
                flag = FLAG_SET;
                (*pObsNum) = 0U;
                break;
            }
        } 
        else
        {
            flag = FLAG_SET;
            (*pObsNum) = 0U;		
        }

        if (FLAG_SET == flag)
        {
            rtnValue = RETURN_ERROR;	
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;	
    }
    
    return rtnValue;
}

/*************************************************
  函数名:   GetObsBitTableStrInfo  
  功能描述: 获取指定类型的障碍物是码位信息结构
  输入: const UINT16 nZcId, 相邻ZCid
            const UINT16_S outputZcId,输出方ZcId
            const UINT8_S obsType 障碍物类型
  输出: 无
  返回值:NULL: 获取数据失败
		   !NULL: 查询成功
*************************************************/
ChangeBitTableStruct* GetObsBitTableStrInfo(const UINT16_S outputZcId,const UINT16_S nZcId,const UINT8_S obsType)
{
    UINT16_S index = DEFAULT_UINT16_VALUE;
    ChangeBitTableStruct *pRtnValue = NULL;

    /*计算ZcID对应的数组下标*/
    index = GetChangeAreaConfigBufIndex(outputZcId,nZcId);

    if (CHANGE_AREA_SUM_MAX != index)
    {
        switch (obsType)
        {
        case OBS_TYPE_AC:
            /* return gpChangeAreaConfigStruBuff[index].AcBitStruBuff; */
            pRtnValue = gpChangeAreaConfigStruBuff[index].AcBitStruBuff;
            break;

        case OBS_TYPE_DRB:
            pRtnValue = gpChangeAreaConfigStruBuff[index].DrButtonBitStruBuff;
            break;

        case OBS_TYPE_DRL:
            pRtnValue = gpChangeAreaConfigStruBuff[index].DrLampBitStruBuff;
            break;

        case OBS_TYPE_POINT:
            pRtnValue = gpChangeAreaConfigStruBuff[index].SwitchBitStruBuff;
            break;

        case OBS_TYPE_OVERLAP:
            pRtnValue = gpChangeAreaConfigStruBuff[index].OverlapBitStruBuff;
            break;

        case OBS_TYPE_SIGNAL:
            pRtnValue = gpChangeAreaConfigStruBuff[index].SignalBitStruBuff;
            break;

        case OBS_TYPE_PSD:
            pRtnValue = gpChangeAreaConfigStruBuff[index].PsdBitStruBuff;
            break;

        case OBS_TYPE_ESB:
            pRtnValue = gpChangeAreaConfigStruBuff[index].EsbBitStruBuff;
            break;

        case OBS_TYPE_ROUTE:
            pRtnValue = gpChangeAreaConfigStruBuff[index].RouteBitStruBuff;
            break;

        case OBS_TYPE_LS:
            pRtnValue = gpChangeAreaConfigStruBuff[index].LogicSectionBitStruBuff;
            break;

        default:
            pRtnValue = NULL;
            break;
        }
    } 
    else
    {
        pRtnValue = NULL;
    }

    return pRtnValue;
}

/*************************************************
  函数名:  GetObsBitTableNumOfIndex    
  功能描述: 获取指定类型的障碍物的码位数量（下标索引）
  输入: const UINT8 changeAreaIndex 切换线路下标
            const UINT8_S obsType 障碍物类型
            UINT16_S *pObsNum 障碍物数量
  输出: 无
  返回值:RETURN_ERROR: 获取数据失败
		    RETURN_SUCCESS: 查询成功
*************************************************/
UINT8_S GetObsBitTableNumOfIndex(const UINT8_S changeAreaIndex, const UINT8_S obsType, UINT16_S *pObsNum)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S flag = DEFAULT_ZERO;

    if (NULL != pObsNum)
    {
        /*初始化输出变量*/
        (*pObsNum) = DEFAULT_ZERO;

        if (CHANGE_AREA_LOCAL_SUM_MAX <= changeAreaIndex)
        {
            flag = FLAG_SET;
            (*pObsNum) = 0U;
        } 
        else
        {          
            switch (obsType)
            {
            case OBS_TYPE_AC:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].AcNum;
                break;

            case OBS_TYPE_DRB:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].DrButtonNum;
                break;

            case OBS_TYPE_DRL:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].DrLampNum;
                break;

            case OBS_TYPE_POINT:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].SwitchNum;
                break;

            case OBS_TYPE_OVERLAP:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].OverlapNum;
                break;

            case OBS_TYPE_SIGNAL:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].SignalNum;
                break;

            case OBS_TYPE_PSD:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].PsdNum;
                break;

            case OBS_TYPE_ESB:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].EsbNum;
                break;

            case OBS_TYPE_ROUTE:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].RouteNum;
                break;

            case OBS_TYPE_LS:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].LogicSectionNum;
                break;

            default:
                flag = FLAG_SET;
                (*pObsNum) = 0U;
                break;
            }
        }
    } 
    else
    {
        flag = FLAG_SET;
    }
    
    if (FLAG_SET == flag)
    {
        rtnValue = RETURN_ERROR;	
    } 
    else
    {
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:  GetObsBitTableStrInfoOfIndex    
  功能描述: 获取指定类型的障碍物是码位信息结构（下标索引）
  输入: const UINT8 changeAreaIndex 切换区域下标
            const UINT8_S obsType 障碍物类型
  输出: 无
  返回值:NULL: 获取数据失败
		   !NULL: 查询成功
*************************************************/
ChangeBitTableStruct* GetObsBitTableStrInfoOfIndex(const UINT8_S changeAreaIndex,const UINT8_S obsType)
{
    ChangeBitTableStruct *pRtnValue = NULL;

    if (CHANGE_AREA_LOCAL_SUM_MAX <= changeAreaIndex)
    {
        pRtnValue = NULL;
    } 
    else
    {      
        switch (obsType)
        {
        case OBS_TYPE_AC:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].AcBitStruBuff;
            break;

        case OBS_TYPE_DRB:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].DrButtonBitStruBuff;
            break;

        case OBS_TYPE_DRL:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].DrLampBitStruBuff;
            break;

        case OBS_TYPE_POINT:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].SwitchBitStruBuff;
            break;

        case OBS_TYPE_OVERLAP:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].OverlapBitStruBuff;
            break;

        case OBS_TYPE_SIGNAL:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].SignalBitStruBuff;
            break;

        case OBS_TYPE_PSD:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].PsdBitStruBuff;
            break;

        case OBS_TYPE_ESB:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].EsbBitStruBuff;
            break;

        case OBS_TYPE_ROUTE:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].RouteBitStruBuff;
            break;

        case OBS_TYPE_LS:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].LogicSectionBitStruBuff;
            break;

        default:
            pRtnValue = NULL;
            break;
        }
    }

    return pRtnValue;
}
