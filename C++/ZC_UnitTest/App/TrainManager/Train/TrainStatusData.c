/********************************************************                                                                                                            
 文 件 名： TrainStatusData.c   
 作    者： ZC组
 创建时间： 2015-07-01
 描述： 列车状态数据管理  
 备注： 无  
********************************************************/
#include "TrainStatusData.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../../Common/Copy.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

TrainInfoStruct gTrainStatusDataStruBuff[SIZE_MAX_CONTROLE_TRAIN];   /*定义本ZC控制范围内最大列车数量*/
UINT8_S gLocalTrainIndexBuff[SIZE_MAX_LINE_TRAIN] = {0U};			 /*定义列车索引数组，数组长度为线路可能的最大列车ID*/
UINT8_S gTrainCurSum = 0U;									         /*本ZC当前列车数量*/


/*************************************************
  函数名:      GetTrainCurSum
  功能描述:    获取指定列车ID索引号
  输入:        无
  输出:        无
  返回值:      0U: 获取数据失败
               <SIZE_MAX_CONTROLE_TRAIN: 查找成功
*************************************************/
UINT8_S GetTrainCurSum(void)
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_CONTROLE_TRAIN < gTrainCurSum)
    {
        rtnValue = 0U;		
    }
    else
    {
        rtnValue = gTrainCurSum;
    }
    return rtnValue;
}

/*************************************************
  函数名:      GetSingalTrainInfoOfIndex
  功能描述:    获取指定列车列车信息首地址
  输入:        const UINT16_S index, 数组下标
  输出:        无
  返回值:      Null: 获取数据失败
               >0: 单个列车信息首地址
*************************************************/
TrainInfoStruct* GetSingalTrainInfoOfIndex(const UINT16_S index)
{
    TrainInfoStruct *pRtnValue = NULL;

    if (SIZE_MAX_CONTROLE_TRAIN <= index)
    {
        pRtnValue = NULL;		
    }
    else
    {
        pRtnValue = &gTrainStatusDataStruBuff[index];
    }

    return pRtnValue;
}

/*************************************************
  函数名:      GetTrainIdOfIndex
  功能描述:    获取指定索引号的列车ID
  输入:        const UINT8_S index, 列车ID的下标
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               <SIZE_MAX_CONTROLE_TRAIN: 查找成功
*************************************************/
UINT16_S GetTrainIdOfIndex(const UINT8_S index)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (SIZE_MAX_CONTROLE_TRAIN <= index)
    {
        rtnValue = RETURN_ERROR;		
    }
    else
    {
        rtnValue = gTrainStatusDataStruBuff[index].TrainID;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainStatusBufIndex
  功能描述:    获取指定列车ID索引号
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <SIZE_MAX_LINE_TRAIN: 查找成功
*************************************************/
UINT8_S GetTrainStatusBufIndex(const UINT16_S trainId)
{
    UINT8_S rtnIndex = RETURN_UINT8_MAX_VALUE;

    if ((1U <= trainId) && (trainId < SIZE_MAX_LINE_TRAIN))
    {
        rtnIndex = gLocalTrainIndexBuff[trainId];
    }

    return rtnIndex;
}

/*************************************************
  函数名:      GetSingleTrainInfo
  功能描述:    获取指定列车ID列车信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        TrainInfoStruct *pSingleTrainInfo, 列车信息结构体
  返回值:      RETURN_ERROR:   获取数据失败
               RETURN_SUCCESS: 获取数据成功
*************************************************/
UINT8_S GetSingleTrainInfo(const UINT16_S trainId,TrainInfoStruct *pSingleTrainInfo)
{
    UINT8_S rtnIndex = 0U;
    UINT8_S getBufIndex = 0U;

    getBufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != getBufIndex) && (NULL != pSingleTrainInfo))
    {
        MemoryCpy(pSingleTrainInfo,(UINT32_S)(sizeof(TrainInfoStruct)),&gTrainStatusDataStruBuff[getBufIndex],(UINT32_S)(sizeof(TrainInfoStruct)));
        rtnIndex = RETURN_SUCCESS;
    }
    else
    {
        rtnIndex = RETURN_ERROR;
    }

    return rtnIndex;
}

/*************************************************
  函数名:      SetSingleTrainNextZcInputDataInfo
  功能描述:    设置相邻ZC输入的指定列车ID列车信息
  输入:        const UINT16_S trainId, 列车ID
               const TrainInfoStruct *pSingleTrainInfo, 列车信息结构体
  输出:        无
  返回值:      RETURN_ERROR:   设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT8_S SetSingleTrainNextZcInputDataInfo(const UINT16_S trainId,const TrainInfoStruct *pSingleTrainInfo)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S getBufIndex = 0U;
    UINT8_S trainIndex = DEFAULT_ZERO;
    UINT8_S copyRtn = DEFAULT_ZERO;

    getBufIndex = AllotTrainIndex(trainId);

    if ((SIZE_MAX_CONTROLE_TRAIN != getBufIndex) && (NULL != pSingleTrainInfo))
    {
        trainIndex = GetTrainStatusBufIndex(trainId);

        if (RETURN_UINT8_MAX_VALUE == trainIndex)
        {
            /*列车数量增加*/
            gTrainCurSum++;
            gLocalTrainIndexBuff[trainId] = getBufIndex;
        } 
        else
        {
            /*不处理*/
        }

        /*拷贝数据*/
        gTrainStatusDataStruBuff[getBufIndex].TrainID = trainId;
        gTrainStatusDataStruBuff[getBufIndex].TrainType = pSingleTrainInfo->TrainType;
        gTrainStatusDataStruBuff[getBufIndex].TrainControlZC = pSingleTrainInfo->TrainControlZC;
        gTrainStatusDataStruBuff[getBufIndex].TrainCycle = pSingleTrainInfo->TrainCycle;
        gTrainStatusDataStruBuff[getBufIndex].SuspectHead = pSingleTrainInfo->SuspectHead;
        gTrainStatusDataStruBuff[getBufIndex].SuspectTail = pSingleTrainInfo->SuspectTail;
        gTrainStatusDataStruBuff[getBufIndex].TrainHeadAC = pSingleTrainInfo->TrainHeadAC;
        gTrainStatusDataStruBuff[getBufIndex].TrainTailAC = pSingleTrainInfo->TrainTailAC;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnsafeHeadAC = pSingleTrainInfo->TrainUnsafeHeadAC;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnsafeTailAC = pSingleTrainInfo->TrainUnsafeTailAC;
        gTrainStatusDataStruBuff[getBufIndex].TrainFrontSignal = pSingleTrainInfo->TrainFrontSignal;
        gTrainStatusDataStruBuff[getBufIndex].SignalProtection = pSingleTrainInfo->SignalProtection;

        gTrainStatusDataStruBuff[getBufIndex].TrainSafeLocStru.TrainHeadLink = pSingleTrainInfo->TrainSafeLocStru.TrainHeadLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainSafeLocStru.TrainHeadOffset = pSingleTrainInfo->TrainSafeLocStru.TrainHeadOffset;
        gTrainStatusDataStruBuff[getBufIndex].TrainSafeLocStru.TrainTailLink = pSingleTrainInfo->TrainSafeLocStru.TrainTailLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainSafeLocStru.TrainTailOffset = pSingleTrainInfo->TrainSafeLocStru.TrainTailOffset;

        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainHeadLink = pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainHeadOffset = pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadOffset;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainTailLink = pSingleTrainInfo->TrainUnSafeLocStru.TrainTailLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainTailOffset = pSingleTrainInfo->TrainUnSafeLocStru.TrainTailOffset;

        gTrainStatusDataStruBuff[getBufIndex].TrainError = pSingleTrainInfo->TrainError;
        gTrainStatusDataStruBuff[getBufIndex].TrainRealDirection = pSingleTrainInfo->TrainRealDirection;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnsafeDirection = pSingleTrainInfo->TrainUnsafeDirection;
        gTrainStatusDataStruBuff[getBufIndex].TrainMode = pSingleTrainInfo->TrainMode;
        gTrainStatusDataStruBuff[getBufIndex].TrainLevel = pSingleTrainInfo->TrainLevel;
        gTrainStatusDataStruBuff[getBufIndex].TrainSpeed = pSingleTrainInfo->TrainSpeed;
        gTrainStatusDataStruBuff[getBufIndex].TrainStopArea = pSingleTrainInfo->TrainStopArea;
        gTrainStatusDataStruBuff[getBufIndex].TrainEmergency = pSingleTrainInfo->TrainEmergency;
        gTrainStatusDataStruBuff[getBufIndex].TrainIntegrity = pSingleTrainInfo->TrainIntegrity;	

        /* LogPrintf(1U,"20.002 train=%d,U[%d,%d;%d,%d],S[%d,%d,%d,%d];getBufIndex=%d\n",trainId,
        pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadLink,pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadOffset,
        pSingleTrainInfo->TrainUnSafeLocStru.TrainTailLink,pSingleTrainInfo->TrainUnSafeLocStru.TrainTailOffset,
        pSingleTrainInfo->TrainSafeLocStru.TrainHeadLink,pSingleTrainInfo->TrainSafeLocStru.TrainHeadOffset,
        pSingleTrainInfo->TrainSafeLocStru.TrainTailLink,pSingleTrainInfo->TrainSafeLocStru.TrainTailOffset,
        getBufIndex); */


        rtnValue =  RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetSingleTrainInputDataInfo
  功能描述:    设置列车输入信息中指定列车ID列车信息
  输入:        const UINT16_S trainId, 列车ID
               const TrainInfoStruct *pSingleTrainInfo, 列车信息结构体
  输出:        无
  返回值:      RETURN_ERROR:   设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT8_S SetSingleTrainInputDataInfo(const UINT16_S trainId,const TrainInfoStruct *pSingleTrainInfo)
{
    UINT8_S rtnIndex = 0U;
    UINT8_S getBufIndex = 0U;
    UINT8_S trainIndex = DEFAULT_ZERO;

    /* 申请下标 */
    getBufIndex = AllotTrainIndex(trainId);

    if ((SIZE_MAX_CONTROLE_TRAIN != getBufIndex) && (NULL != pSingleTrainInfo))
    {
        trainIndex = GetTrainStatusBufIndex(trainId);

        if (RETURN_UINT8_MAX_VALUE == trainIndex)
        {
            /*列车数量增加*/
            gTrainCurSum++;
            gLocalTrainIndexBuff[trainId] = getBufIndex;
        } 
        else
        {
            /*不处理*/
        }

        /*拷贝数据*/
        gTrainStatusDataStruBuff[getBufIndex].TrainID = trainId;
        gTrainStatusDataStruBuff[getBufIndex].TrainInType = pSingleTrainInfo->TrainInType;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainHeadLink = pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainHeadOffset = pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadOffset;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainTailLink = pSingleTrainInfo->TrainUnSafeLocStru.TrainTailLink;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnSafeLocStru.TrainTailOffset = pSingleTrainInfo->TrainUnSafeLocStru.TrainTailOffset;
        gTrainStatusDataStruBuff[getBufIndex].TrainRealDirection = pSingleTrainInfo->TrainRealDirection;
        gTrainStatusDataStruBuff[getBufIndex].TrainUnsafeDirection = pSingleTrainInfo->TrainUnsafeDirection;
        gTrainStatusDataStruBuff[getBufIndex].TrainMode = pSingleTrainInfo->TrainMode;
        gTrainStatusDataStruBuff[getBufIndex].TrainLevel = pSingleTrainInfo->TrainLevel;
        gTrainStatusDataStruBuff[getBufIndex].TrainSpeed = pSingleTrainInfo->TrainSpeed;
        gTrainStatusDataStruBuff[getBufIndex].TrainStopArea = pSingleTrainInfo->TrainStopArea;
        gTrainStatusDataStruBuff[getBufIndex].TrainError = pSingleTrainInfo->TrainError;
        gTrainStatusDataStruBuff[getBufIndex].TrainEmergency = pSingleTrainInfo->TrainEmergency;
        gTrainStatusDataStruBuff[getBufIndex].TrainIntegrity = pSingleTrainInfo->TrainIntegrity;
        gTrainStatusDataStruBuff[getBufIndex].TrainControlZC = pSingleTrainInfo->TrainControlZC;
        gTrainStatusDataStruBuff[getBufIndex].TrainCycle = pSingleTrainInfo->TrainCycle;

        /*为了解决闯红灯现象,*/
        gTrainStatusDataStruBuff[getBufIndex].SignalProtection =FLAG_UNSET;

        /*LogPrintf(1U,"20.001 train=%d,%d,%d;%d,%d;getBufIndex=%d\n",trainId,pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadLink,
        pSingleTrainInfo->TrainUnSafeLocStru.TrainHeadOffset,pSingleTrainInfo->TrainUnSafeLocStru.TrainTailLink,
        pSingleTrainInfo->TrainUnSafeLocStru.TrainTailOffset,getBufIndex);*/

        rtnIndex = RETURN_SUCCESS;
    }
    else
    {
        rtnIndex = RETURN_ERROR;
    }

    return rtnIndex;
}

/*************************************************
  函数名:      GetTrainControlZc
  功能描述:    获取指定列车受控ZC
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               <RETURN_UINT8_MAX_VALUE: 获取数据成功
*************************************************/
UINT16_S GetTrainControlZc(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainControlZC;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainControlZc
  功能描述:    设置指定列车受控ZC
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S zcId, ZC的编号
  输出:        无
  返回值:      RETURN_ERROR:   设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT8_S SetTrainControlZc(const UINT16_S trainId,const UINT16_S zcId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainControlZC = zcId;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainCycle
  功能描述:    获取指定列车周期号
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取数据失败
               >0:             获取数据成功
*************************************************/
UINT32_S GetTrainCycle(const UINT16_S trainId)
{
    UINT32_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainCycle;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainCycle
  功能描述:    设置指定列车周期号
  输入:        const UINT16_S trainId, 列车ID
               const UINT32_S trainCycle， 列车周期号
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainCycle(const UINT16_S trainId,const UINT32_S trainCycle)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainCycle = trainCycle;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainType
  功能描述:    获取指定列车类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT8_S GetTrainType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainType;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainType
  功能描述:    设置指定列车类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainType, 列车类型
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainType(const UINT16_S trainId,const UINT8_S trainType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainType = trainType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainSuspectHead
  功能描述:    获取指定列车前端可疑标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT8_S GetTrainSuspectHead(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].SuspectHead;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainSuspectHead
  功能描述:    设置指定列车前端可疑标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S suspectHead, 列车前端可疑标志
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainSuspectHead(const UINT16_S trainId,const UINT8_S suspectHead)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].SuspectHead = suspectHead;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainSuspectTail
  功能描述:    获取指定列车后端可疑标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT8_S GetTrainSuspectTail(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].SuspectTail;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainSuspectTail
  功能描述:    设置指定列车后端可疑标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S suspectTail, 列车后端可疑标志
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainSuspectTail(const UINT16_S trainId,const UINT8_S suspectTail)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].SuspectTail = suspectTail;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainTrainHeadAC
  功能描述:    获取指定列车车头所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取数据失败
               >0:             设置成功
*************************************************/
UINT16_S GetTrainTrainHeadAC(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainHeadAC;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainTrainHeadAC
  功能描述:    设置指定列车车头所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainHeadAC, 车头所在的计轴区段
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainTrainHeadAC(const UINT16_S trainId,const UINT16_S trainHeadAC)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainHeadAC = trainHeadAC;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainTrainTailAC
  功能描述:    获取指定列车车尾所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT16_S GetTrainTrainTailAC(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainTailAC;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainTrainTailAC
  功能描述:    设置指定列车车尾所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainTailAC, 列车车尾所在计轴
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainTrainTailAC(const UINT16_S trainId,const UINT16_S trainTailAC)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainTailAC = trainTailAC;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainUnsafeTrainHeadAC
  功能描述:    获取指定列车非安全车头所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT16_S GetTrainUnsafeTrainHeadAC(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainUnsafeHeadAC;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainUnsafeTrainHeadAC
  功能描述:    设置指定列车非安全车头所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainUnsafeHeadAC, 列车非安全车头所在计轴区段
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainUnsafeTrainHeadAC(const UINT16_S trainId,const UINT16_S trainUnsafeHeadAC)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainUnsafeHeadAC = trainUnsafeHeadAC;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainUnsafeTrainTailAC
  功能描述:    获取指定列车非安全车尾所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               RETURN_SUCCESS: 获取成功
*************************************************/
UINT16_S GetTrainUnsafeTrainTailAC(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainUnsafeTailAC;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainUnsafeTrainTailAC
  功能描述:    获取指定列车非安全车尾所在计轴区段
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainUnsafeTailAC, 列车非安全车尾所在计轴区段
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainUnsafeTrainTailAC(const UINT16_S trainId,const UINT16_S trainUnsafeTailAC)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainUnsafeTailAC = trainUnsafeTailAC;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainFrontSignal
  功能描述:    获取指定列车前方需要防护信号机
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT16_S GetTrainFrontSignal(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainFrontSignal;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainFrontSignal
  功能描述:    设置指定列车前方需要防护信号机
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainFrontSignal, 列车前方信号机
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetTrainFrontSignal(const UINT16_S trainId,const UINT16_S trainFrontSignal)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainFrontSignal = trainFrontSignal;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainSignalProtection
  功能描述:    获取指定列车闯信号标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:   获取失败
               >0:             获取成功
*************************************************/
UINT8_S GetTrainSignalProtection(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].SignalProtection;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainSignalProtection
  功能描述:    设置指定列车闯信号标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S signalProtection, 列车闯信号机防护标志
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSignalProtection(const UINT16_S trainId,const UINT8_S signalProtection)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].SignalProtection = signalProtection;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainCommStatus
  功能描述:    获取指定列车通信链路状态
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:    获取失败
               >0:              获取成功
*************************************************/
UINT8_S GetTrainCommStatus(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].CommStatus;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainCommStatus
  功能描述:    设置指定列车通信链路状态
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S commStatus, 列车通信链路状态
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainCommStatus(const UINT16_S trainId,const UINT8_S commStatus)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].CommStatus = commStatus;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainCommRedundancy
  功能描述:    获取指定列车通信计时位
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:    获取失败
               >0:              获取成功
*************************************************/
UINT8_S GetTrainCommRedundancy(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].CommRedundancy;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainCommRedundancy
  功能描述:    设置指定列车通信计时位
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S commRedundancy, 列车通信计时位
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainCommRedundancy(const UINT16_S trainId,const UINT8_S commRedundancy)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].CommRedundancy = commRedundancy;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainPrtclDelay
  功能描述:    获取指定列车通信协议延迟时间
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:    获取失败
               >0:              获取成功
*************************************************/
UINT8_S GetTrainPrtclDelay(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].PrtclDelay;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainPrtclDelay
  功能描述:    设置指定列车通信协议延迟时间
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S prtclDelay, 列车通信协议延迟时间
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainPrtclDelay(const UINT16_S trainId,const UINT8_S prtclDelay)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].PrtclDelay = prtclDelay;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainStatus
  功能描述:    获取指定列车状态
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainStatus(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainStatus;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainPrtclDelay
  功能描述:    设置指定列车状态
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainStatus, 列车列车状态
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainStatus(const UINT16_S trainId,const UINT8_S trainStatus)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainStatus = trainStatus;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainInType
  功能描述:    获取指定列车输入类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainInType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainInType;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainInType
  功能描述:    设置指定列车输入类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainInType, 列车输入类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainInType(const UINT16_S trainId,const UINT8_S trainInType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainInType = trainInType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainOutType
  功能描述:    获取指定列车输出类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainOutType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainOutType;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainOutType
  功能描述:    设置指定列车输出类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainOutType, 列车输出类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainOutType(const UINT16_S trainId,const UINT8_S trainOutType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainOutType = trainOutType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainHandoverInType
  功能描述:    获取指定相邻ZC输入类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainHandoverInType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].HandoverInType;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainHandoverInType
  功能描述:    设置指定列车相邻ZC输入类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S handoverInType, 列车相邻ZC输入类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainHandoverInType(const UINT16_S trainId,const UINT8_S handoverInType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].HandoverInType = handoverInType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainHandoverOutType
  功能描述:    获取指定相邻ZC输出类型
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainHandoverOutType(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_UINT8_MAX_VALUE;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].HandoverOutType;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainHandoverOutType
  功能描述:    设置指定列车相邻ZC输出类型
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S handoverOutType, 列车相邻ZC输出类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainHandoverOutType(const UINT16_S trainId,const UINT8_S handoverOutType)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].HandoverOutType = handoverOutType;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainUnsafeDirection
  功能描述:    获取指定列车期望运行方向
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainUnsafeDirection(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainUnsafeDirection;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainUnsafeDirection
  功能描述:    设置指定列车期望运行方向
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainUnsafeDirection, 列车期望运行方向
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainUnsafeDirection(const UINT16_S trainId,const UINT8_S trainUnsafeDirection)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainUnsafeDirection = trainUnsafeDirection;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainRealDirection
  功能描述:    获取指定列车实际运行方向
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainRealDirection(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainRealDirection;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainRealDirection
  功能描述:    设置指定列车实际运行方向
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainRealDirection, 列车实际运行方向
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainRealDirection(const UINT16_S trainId,const UINT8_S trainRealDirection)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainRealDirection = trainRealDirection;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainMode
  功能描述:    获取指定列车模式
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainMode(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainMode;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainMode
  功能描述:    设置指定列车模式
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainMode, 列车列车模式
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainMode(const UINT16_S trainId,const UINT8_S trainMode)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainMode = trainMode;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainLevel
  功能描述:    获取指定列车级别
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainLevel(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainLevel;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainMode
  功能描述:    设置指定列车级别
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainLevel, 列车列车级别
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainLevel(const UINT16_S trainId,const UINT8_S trainLevel)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainLevel = trainLevel;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainSpeed
  功能描述:    获取指定列车速度
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT16_S GetTrainSpeed(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_UINT16_MAX_VALUE;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainSpeed;
    }

    return rtnValue;
}  

/*************************************************
  函数名:      SetTrainSpeed
  功能描述:    设置指定列车速度
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainSpeed, 列车速度
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSpeed(const UINT16_S trainId,const UINT16_S trainSpeed)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainSpeed = trainSpeed;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainStopArea
  功能描述:    获取指定列车停稳标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainStopArea(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainStopArea;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainStopArea
  功能描述:    设置指定列车停稳标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainStopArea, 列车停稳标志
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainStopArea(const UINT16_S trainId,const UINT8_S trainStopArea)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainStopArea = trainStopArea;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainEmergency
  功能描述:    获取指定列车完整性标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainIntegrity(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainIntegrity;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainIntegrity
  功能描述:    设置指定列车完整性标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainIntegrity, 列车完整性标志
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainIntegrity(const UINT16_S trainId,const UINT8_S trainIntegrity)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainIntegrity = trainIntegrity;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainEmergency
  功能描述:    获取指定列车紧急停车标志
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR: 获取数据失败
               >0:           获取数据成功
*************************************************/
UINT8_S GetTrainEmergency(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainEmergency;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainEmergency
  功能描述:    设置指定列车紧急停车标志
  输入:        const UINT16_S trainId, 列车ID
               const UINT8_S trainEmergency, 列车紧急停车标志
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainEmergency(const UINT16_S trainId,const UINT8_S trainEmergency)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].TrainEmergency = trainEmergency;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetMatchRouteNum
  功能描述:    获取指定列车已匹配进路数量
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      >=0,数量
*************************************************/
UINT8_S GetMatchRouteNum(const UINT16_S trainId)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].MatchRouteNum;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainMatchedRouteIdBuff
  功能描述:    获取指定列车已匹配进路信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        UINT16_S routeIdBuff[], 匹配的进路的编号
  返回值:      RETURN_ERROR:    获取数据失败
               RETURN_SUCCESS:  获取数据成功
*************************************************/
UINT8_S GetTrainMatchedRouteIdBuff(const UINT16_S trainId,UINT16_S routeIdBuff[])
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S k = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex) &&(NULL != routeIdBuff))
    {
        for(k=0U;k<SIZE_MAX_ROUTENUM;k++)
        {
            routeIdBuff[k] = gTrainStatusDataStruBuff[bufIndex].MatchedRouteIDBuff[k];
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
  函数名:      GetTrainMatchedLastRouteId
  功能描述:    获取指定列车已匹配的最后一条进路信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        UINT16_S *pLastRouteId, 最后一条进路Id
  返回值:      RETURN_ERROR:    获取数据失败
               RETURN_SUCCESS:  获取数据成功
*************************************************/
UINT8_S GetTrainMatchedLastRouteId(const UINT16_S trainId,UINT16_S *pLastRouteId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S routeNum = DEFAULT_ZERO;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (NULL != pLastRouteId)
    {
        if ((RETURN_UINT8_MAX_VALUE != bufIndex) )
        {
            routeNum = gTrainStatusDataStruBuff[bufIndex].MatchRouteNum;

            if ((SIZE_MAX_ROUTENUM >= routeNum) && (DEFAULT_ZERO < routeNum))
            {
                (*pLastRouteId) = gTrainStatusDataStruBuff[bufIndex].MatchedRouteIDBuff[routeNum - 1U];
                rtnValue = RETURN_SUCCESS;
            } 
            else
            {
                (*pLastRouteId) = 0U;
                rtnValue = RETURN_ERROR;
            }

        }
        else
        {
            (*pLastRouteId) = 0U;
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainMatchedRouteIdBuf
  功能描述:    设置指定列车已匹配进路信息
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S routeIdBuff[] 进路ID数组
               const UINT8_S routeNum 进路数量
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainMatchedRouteIdBuf(const UINT16_S trainId,const UINT16_S routeIdBuff[],const UINT8_S routeNum)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S k = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (routeNum <= SIZE_MAX_ROUTENUM) && (NULL != routeIdBuff))
    {
        gTrainStatusDataStruBuff[bufIndex].MatchRouteNum = 0U;

        if (DEFAULT_ZERO == routeNum)
        {
            for(k=0U;k<SIZE_MAX_ROUTENUM;k++)
            {
                gTrainStatusDataStruBuff[bufIndex].MatchedRouteIDBuff[k] = DEFAULT_ZERO;
            }
        } 
        else
        {
            for(k=0U;k<routeNum;k++)
            {
                gTrainStatusDataStruBuff[bufIndex].MatchedRouteIDBuff[k] = routeIdBuff[k];
                gTrainStatusDataStruBuff[bufIndex].MatchRouteNum++;
            }
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
  函数名:      GetTrainSafeLoc
  功能描述:    获取指定列车切换线路ID
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_ERROR:    获取数据失败
               >0:              获取数据成功
*************************************************/
UINT16_S GetTrainChangeLineId(const UINT16_S trainId)
{
    UINT16_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].ChangeLineId;
    }

    return rtnValue;
}  

/*************************************************
  函数名:      SetTrainChangeLineId
  功能描述:    设置指定列车切换线路ID
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S changeLineId, 列车切换线路ID
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainChangeLineId(const UINT16_S trainId,const UINT16_S changeLineId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {		
        gTrainStatusDataStruBuff[bufIndex].ChangeLineId = changeLineId;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainSafeLoc
  功能描述:    获取指定列车安全位置信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        TrainSafeLocStruct *pTrainSafeLocStru, 列车位置信息结构体
  返回值:      RETURN_ERROR:    获取数据失败
               RETURN_SUCCESS:  获取数据成功
*************************************************/
UINT8_S GetTrainSafeLoc(const UINT16_S trainId,TrainSafeLocStruct *pTrainSafeLocStru)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;


    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (NULL != pTrainSafeLocStru))
    {
        pTrainSafeLocStru->TrainHeadLink = gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadLink;
        pTrainSafeLocStru->TrainHeadOffset = gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadOffset;
        pTrainSafeLocStru->TrainTailLink = gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailLink;
        pTrainSafeLocStru->TrainTailOffset = gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailOffset;

        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainSafeLoc
  功能描述:    设置指定列车安全位置信息
  输入:        const UINT16_S trainId, 列车ID
               TrainSafeLocStruct *pTrainSafeLocStru, 列车位置结构体
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSafeLoc(const UINT16_S trainId,const TrainSafeLocStruct *pTrainSafeLocStru)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (NULL != pTrainSafeLocStru))
    {
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadLink = pTrainSafeLocStru->TrainHeadLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadOffset = pTrainSafeLocStru->TrainHeadOffset;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailLink = pTrainSafeLocStru->TrainTailLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailOffset = pTrainSafeLocStru->TrainTailOffset;
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainSafeHeadLoc
  功能描述:    设置指定列车安全车头位置信息
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainSafeHeadLink, 安全车头link
               const UINT32_S trainSafeHeadOffset, 安全车头offset
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSafeHeadLoc(const UINT16_S trainId,const UINT16_S trainSafeHeadLink,const UINT32_S trainSafeHeadOffset)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;


    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadLink = trainSafeHeadLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadOffset = trainSafeHeadOffset;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainSafeTailLoc
  功能描述:    设置指定列车安全车尾位置信息
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainSafeTailLink, 安全车尾link
               const UINT32_S trainSafeTailOffset, 安全车尾offset
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainSafeTailLoc(const UINT16_S trainId,const UINT16_S trainSafeTailLink,const UINT32_S trainSafeTailOffset)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;


    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailLink = trainSafeTailLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailOffset = trainSafeTailOffset;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainUnSafeLoc
  功能描述:    获取指定列车非安全位置信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        TrainSafeLocStruct *pTrainUnSafeLocStru, 列车位置信息结构体
  返回值:      RETURN_ERROR:    获取数据失败
               RETURN_SUCCESS:  获取数据成功
*************************************************/
UINT8_S GetTrainUnSafeLoc(const UINT16_S trainId,TrainSafeLocStruct *pTrainUnSafeLocStru)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (NULL != pTrainUnSafeLocStru))
    {
        pTrainUnSafeLocStru->TrainHeadLink = gTrainStatusDataStruBuff[bufIndex].TrainUnSafeLocStru.TrainHeadLink;
        pTrainUnSafeLocStru->TrainHeadOffset = gTrainStatusDataStruBuff[bufIndex].TrainUnSafeLocStru.TrainHeadOffset;
        pTrainUnSafeLocStru->TrainTailLink = gTrainStatusDataStruBuff[bufIndex].TrainUnSafeLocStru.TrainTailLink;
        pTrainUnSafeLocStru->TrainTailOffset = gTrainStatusDataStruBuff[bufIndex].TrainUnSafeLocStru.TrainTailOffset;
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainUnSafeLoc
  功能描述:    设置指定列车非安全位置信息
  输入:        const UINT16_S trainId, 列车ID
               const TrainSafeLocStruct trainUnSafeLocStru, 位置信息结构体
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainUnSafeLoc(const UINT16_S trainId,const TrainSafeLocStruct trainUnSafeLocStru)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadLink = trainUnSafeLocStru.TrainHeadLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainHeadOffset = trainUnSafeLocStru.TrainHeadOffset;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailLink = trainUnSafeLocStru.TrainTailLink;
        gTrainStatusDataStruBuff[bufIndex].TrainSafeLocStru.TrainTailOffset = trainUnSafeLocStru.TrainTailOffset;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainError
  功能描述:    获取指定列车ID不确定误差
  输入:        const UINT16_S trainId, 列车ID
  输出:        UINT16_S sectionIdBuff[], 逻辑区段ID数组
  返回值:      TRAIN_ERROR_MAX_NUM:      获取数据失败
               >0:    获取数据成功
*************************************************/
UINT16_S GetTrainError(const UINT16_S trainId)
{
    UINT16_S rtnValue = TRAIN_ERROR_MAX_NUM;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].TrainError;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainError
  功能描述:    设置指定列车ID不确定误差
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S trainError, 不确定误差
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainError(const UINT16_S trainId, const UINT16_S trainError)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        gTrainStatusDataStruBuff[bufIndex].TrainError = trainError;
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      AllotTrainIndex
  功能描述:    分配确定列车分配的缓存下标
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      SIZE_MAX_CONTROLE_TRAIN: 分配下标失败
               (0,SIZE_MAX_CONTROLE_TRAIN): 分配下标成功
*************************************************/
UINT8_S AllotTrainIndex(const UINT16_S trainId)
{
    UINT8_S rtnValue = SIZE_MAX_CONTROLE_TRAIN;
    UINT16_S trainIndex = DEFAULT_ZERO;

    trainIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != trainIndex)
    {
        /*已分配下标*/
        rtnValue = (UINT8_S)(trainIndex);
    } 
    else
    {
        /*未分配下标*/
        /*判断当前已管辖列车数量*/
        if (GetTrainCurSum() < SIZE_MAX_CONTROLE_TRAIN)
        {
            /*小于能管辖的列车数量,还可以分配下标存储列车数据*/
            rtnValue = GetTrainCurSum();
        } 
        else
        {
            rtnValue = SIZE_MAX_CONTROLE_TRAIN;
        }
    }

    return rtnValue;
}

/*************************************************
  函数名:      GetTrainPreSectionId
  功能描述:    获取指定列车上周期逻辑区段ID
  输入:        const UINT16_S trainId, 列车ID
  输出:        UINT16_S sectionIdBuff[], 逻辑区段ID数组
  返回值:      RETURN_ERROR:      获取数据失败
               RETURN_SUCCESS:    获取数据成功
*************************************************/
UINT8_S GetTrainPreSectionId(const UINT16_S trainId,UINT16_S sectionIdBuff[])
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S k = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex) && (NULL != sectionIdBuff))
    {
        for(k=0U;k<SIZE_MAX_SECTION_OF_TRAIN;k++)
        {
            sectionIdBuff[k] = gTrainStatusDataStruBuff[bufIndex].PreSectionIdBuff[k];
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
  函数名:      GetTrainPreSectionNum
  功能描述:    获取指定列车上周期逻辑区段数量
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE:      获取数据失败
               [0,RETURN_UINT8_MAX_VALUE):  获取数据成功
*************************************************/
UINT8_S GetTrainPreSectionNum(const UINT16_S trainId)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if (RETURN_UINT8_MAX_VALUE != bufIndex)
    {
        rtnValue = gTrainStatusDataStruBuff[bufIndex].PreSectionNum;
    }
    else
    {
        rtnValue = RETURN_UINT8_MAX_VALUE;
    }

    return rtnValue;
}

/*************************************************
  函数名:      SetTrainPreSectionId
  功能描述:    设置指定列车上周期逻辑区段信息
  输入:        const UINT16_S trainId, 列车ID
               const UINT16_S sectionIdBuff[], 逻辑区段ID数组
               const UINT8_S sectionNum, 逻辑区段的数量
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetTrainPreSectionId(const UINT16_S trainId,const UINT16_S sectionIdBuff[],const UINT8_S sectionNum)
{
    UINT8_S rtnValue = RETURN_ERROR;
    UINT8_S bufIndex = 0U;
    UINT8_S k = 0U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    if ((RETURN_UINT8_MAX_VALUE != bufIndex)
        && (sectionNum <= SIZE_MAX_SECTION_OF_TRAIN))
    {
        gTrainStatusDataStruBuff[bufIndex].PreSectionNum = DEFAULT_ZERO;

        for(k=0U;k < sectionNum;k++)
        {
            gTrainStatusDataStruBuff[bufIndex].PreSectionIdBuff[k] = sectionIdBuff[k];
        }

        gTrainStatusDataStruBuff[bufIndex].PreSectionNum = sectionNum;

        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  函数名:      DeleteSingleTrainInfo
  功能描述:    删除单个列车信息
  输入:        const UINT16_S trainId, 列车ID
  输出:        无
  返回值:      无
*************************************************/
void DeleteSingleTrainInfo(const UINT16_S trainId)
{
    UINT8_S bufIndex = 0U;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S rtnCpy = 1U;

    bufIndex = GetTrainStatusBufIndex(trainId);

    /* 判断下标值 */
    if (RETURN_UINT8_MAX_VALUE == bufIndex)
    {
        /*不处理*/
    } 
    else
    {
        /*清除信息*/
        if (bufIndex == (GetTrainCurSum() - 1U))
        {
            MemorySet(&gTrainStatusDataStruBuff[bufIndex],((UINT32_S)(sizeof(TrainInfoStruct))),
                0U,((UINT32_S)(sizeof(TrainInfoStruct))));
        } 
        else
        {
            for (cycle = bufIndex + 1U;cycle < GetTrainCurSum();cycle++)
            {
                rtnCpy = MemoryCpy(&gTrainStatusDataStruBuff[cycle - 1U],((UINT32_S)(sizeof(TrainInfoStruct))),
                    &gTrainStatusDataStruBuff[cycle],((UINT32_S)(sizeof(TrainInfoStruct))));

                if (0U == rtnCpy)
                {
                    /*更新索引数组*/
                    gLocalTrainIndexBuff[gTrainStatusDataStruBuff[cycle - 1U].TrainID] = cycle - 1U;
                }
                else
                {
                    /* 复制失败 */
                }
            }

            /*清除最后一个*/
            MemorySet(&gTrainStatusDataStruBuff[gTrainCurSum - 1U],((UINT32_S)(sizeof(TrainInfoStruct))),
                0U,((UINT32_S)(sizeof(TrainInfoStruct))));
        }

        if (gTrainCurSum > 0U)
        {
            gTrainCurSum--;
        } 
        else
        {
            gTrainCurSum = 0U;
        }

        gLocalTrainIndexBuff[trainId] = RETURN_UINT8_MAX_VALUE;
    }
}
