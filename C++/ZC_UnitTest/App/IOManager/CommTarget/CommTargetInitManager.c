/************************************************************************
*
* 文件名   ：  CommTargetInitManager.c
* 作者     ：  ZC组
* 创建时间 ：  2015.07.14
* 功能描述 ：  通讯目标初始化
* 备  注   ：  无 
*
************************************************************************/

#include "CommTargetInitManager.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../../Dmu/DmuComm/Data/SystemDevCommData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "CommTargetConfigData.h"
#include "CommTargetStatusData.h"

extern CommTargetConfigDataStruct gCommTargetConfigDataStru[COMM_TYPE_SUM_MAX];           /*引用通信对象配置信息*/
extern UINT8_S gCommTargetTypeCurSum;                                                       /*引用通信对象总数*/

extern CommTargetDataStruct gCommTargetDataStruBuff[COMM_TYPE_SUM_MAX];                       /*引用通信对象状态信息（除列车外的其他系统）*/
extern SingleCommTargeStruct gCommTrainDataStruBuff[COMM_TRAIN_ID_MAX];                       /*引用通信列车状态信息*/

/*
* 函数名称： InitCommTargetInfo
* 功能描述： 初始化通信对象关系
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 0u: 初始化失败
*			 1u: 初始化成功
*/
UINT8_S InitCommTargetInfo(void)
{
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (RETURN_SUCCESS == InitOtherCommTargetInfo())
    {
        InitTrainCommTargetInfo();

        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* 函数名称： InitOtherCommTargetInfo
* 功能描述： 初始化其他通信对象（非列车）的通信关系
* 输入参数： void   
* 输出参数： 无
* 返回值  ： 0u: 初始化失败
*			 1u: 初始化成功
*/
UINT8_S InitOtherCommTargetInfo(void)
{
    UINT16_S tempZcId = DEFAULT_ZERO;
    BnfSystemDevCommStruct *pBnfSystemDevCommStru = NULL;
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTragetId = DEFAULT_ZERO;
    UINT8_S commTragetType = DEFAULT_ZERO;
    UINT8_S commTragetIndex = DEFAULT_ZERO;
    UINT8_S singleCommNum = DEFAULT_ZERO;
    UINT8_S breakFalg = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;

    /*获取本ZC的Id*/
    tempZcId = (UINT16_S)INNER_DEVTYPE_ZC;
    localZcId = GetLocalZcId();
    localZcId = (UINT16_S)((UINT16_S)(tempZcId << 8) | localZcId);

    /*获取本ZC通信的设备关系*/
    pBnfSystemDevCommStru = GetIndexIdSystemDevCommDataStru(localZcId);

    /*设置最大的通信对象数量*/
    gCommTargetTypeCurSum = (UINT8_S)DEFAULT_ZERO;

    if (NULL != pBnfSystemDevCommStru)
    {
        for (cycle = DEFAULT_ZERO;cycle < pBnfSystemDevCommStru->commObjectNum;cycle++)
        {
            /*获取通信设备类型*/
            commTragetType = (UINT8_S)((pBnfSystemDevCommStru->commObjectIdBuff[cycle] & ((UINT16_S)0xff00U)) >> 8);

            /*通信对象ID*/
            commTragetId = (UINT16_S)(pBnfSystemDevCommStru->commObjectIdBuff[cycle] & ((UINT16_S)0x00ffU));

            /*获取通信对象下标*/
            commTragetIndex = GetCommTargetTypeBuffIndex(commTragetType);

            if (COMM_TYPE_SUM_MAX != commTragetIndex)
            {
                /*类型已包括，增加该类型通信信息*/
                singleCommNum = gCommTargetConfigDataStru[commTragetIndex].CommTargetNum;

                if (singleCommNum < SINGLE_TYPE_COMM_TARGET_SUM_MAX)
                {
                    /*添加配置端*/
                    gCommTargetConfigDataStru[commTragetIndex].CommTargetIdBuff[singleCommNum] = commTragetId;
                    gCommTargetConfigDataStru[commTragetIndex].CommTargetNum++;

                    /*添加状态端*/
                    gCommTargetDataStruBuff[commTragetIndex].SingleCommTargeStru[singleCommNum].CommTargetId = commTragetId;
                    gCommTargetDataStruBuff[commTragetIndex].SingleCommTargeStru[singleCommNum].CommTargetStatus = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[commTragetIndex].SingleCommTargeStru[singleCommNum].CommTargetCycle = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[commTragetIndex].CommTargetIdBuff[commTragetId] = singleCommNum;
                    gCommTargetDataStruBuff[commTragetIndex].CommTargetNum++;
                } 
                else
                {
                    /*无法再填入,返回失败*/
                    rtnValue = RETURN_ERROR;
                    breakFalg = FLAG_SET;
                    break;
                }

            } 
            else
            {
                /*类型未包括，增加该类型通信信息*/
                if (((UINT8_S)(COMM_TYPE_SUM_MAX-1U)) > gCommTargetTypeCurSum)
                {
                    /*类型未包括，增加该类型通信信息*/
                    /*添加配置端*/
                    gCommTargetConfigDataStru[gCommTargetTypeCurSum].CommTargetType = commTragetType;
                    gCommTargetConfigDataStru[gCommTargetTypeCurSum].CommTargetNum = DEFAULT_ZERO;
                    gCommTargetConfigDataStru[gCommTargetTypeCurSum].CommTargetIdBuff[DEFAULT_ZERO] = (UINT16_S)(pBnfSystemDevCommStru->commObjectIdBuff[cycle] & ((UINT16_S)0x00ffU));
                    gCommTargetConfigDataStru[gCommTargetTypeCurSum].CommTargetNum++;


                    /*添加状态端*/
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].CommTargetType = commTragetType;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].CommTargetNum = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].SingleCommTargeStru[DEFAULT_ZERO].CommTargetId = commTragetId;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].SingleCommTargeStru[DEFAULT_ZERO].CommTargetStatus = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].SingleCommTargeStru[DEFAULT_ZERO].CommTargetCycle = DEFAULT_ZERO;
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].CommTargetIdBuff[commTragetId] = DEFAULT_ZERO;				
                    gCommTargetDataStruBuff[gCommTargetTypeCurSum].CommTargetNum++;

                    gCommTargetTypeCurSum++;
                } 
                else
                {
                    /*无法再填入,返回失败*/
                    rtnValue = RETURN_ERROR;
                    breakFalg = FLAG_SET;
                    break;
                }
            }
        }

        if (FLAG_SET != breakFalg)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*Do nothing currently !*/
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
    return rtnValue;
}

/*
* 函数名称： InitTrainCommTargetInfo
* 功能描述： 初始化列车通信对象的通信关系
* 输入参数： void    
* 输出参数： 无
* 返回值  ： 无
*/
void InitTrainCommTargetInfo(void)
{
    UINT8_S cycle = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < COMM_TRAIN_ID_MAX;cycle++)
    {
        gCommTrainDataStruBuff[cycle].CommTargetId = cycle;
        gCommTrainDataStruBuff[cycle].CommTargetStatus = DEFAULT_ZERO;
        gCommTrainDataStruBuff[cycle].CommTargetCycle = DEFAULT_ZERO;
        gCommTrainDataStruBuff[cycle].CommTargetCycleNum = DEFAULT_ZERO;
    }
}

