/********************************************************
* 
* 文 件 名： AdptPlatServiceInterface.c
* 作    者： 董欣 
* 创建时间： 2016-09-01 
* 功能描述： 适配层提供给平台层的底层适配库函数的接口文件  
* 备    注： 无 
* 
********************************************************/ 

#include "AdptPlatServiceInterface.h"
#include "../../cspadpt/Vcp_Service_Interface.h"
#include "../../cspadpt/Vcp_Service_TestInterface.h"
#include "../../cspadpt/Vcp_Track_Interface.h"
#include "../AdptHandle/AdapterCommonDef.h"
#include "../../Common/MemSet.h"
#include "../../Common/Copy.h"
#include "../../Common/Convert.h"
#include "../../Common/Crc32.h"
#include "../PlatItf/AdptPlatServiceInterface.h"
#include "../AppItf/AdptAppServiceInterface.h"
#include "../AdptHandle/AdapterExtDevInOutManage.h"
#include "../AppItf/AdptAppCommonDef.h"
/*#include "../../cspadpt/Rsp1.h"*/

/*
* 功能描述：根据不同设备的要求对数据进行特殊处理，
*           如对于ATP某些通信对象要求增加特殊头
* 参数说明： 无
* 全局变量： 
* 返回值  ： 1 过网关非NTP数据，经过处理
*           2 过网关NTP数据，经过处理
*           0 不过网关数据，不需处理
*/
UINT8_S AdptPlatOutDataHandle(UINT32_S inDevType, UINT32_S inAppId, const UINT8_S* inData, UINT32_S inLen, UINT8_S outData[], UINT32_S *pOutLen)
{
    UINT32_S index = 0u;
    UINT16_S localName = 0u;
    UINT8_S localType = 0u;
    UINT32_S crcValue = 0u;
    UINT8_S retVal = HANDLE_OUT_NOT_MICR;

    if (( NULL != inData ) && (NULL != outData) && (NULL != pOutLen))
    {

        localName = AdptAppGetLocalName();
        localType = (UINT8_S)((localName>>8u) & 0x00FFu);

        if ((localType == DEVTYPE_VOBC) && ((DEVTYPE_CI == inDevType) || 
            (DEVTYPE_ZC == inDevType) || (DEVTYPE_ATS == inDevType)|| 
            (DEVTYPE_NTP == inDevType) || (DEVTYPE_NMS == inDevType)))
        {

            /* 根据网关的需求ATP对外的某些设备需要增加四个字节头和四个字节尾 */

            outData[index++] = (UINT8_S)inDevType;
            outData[index++] = (UINT8_S)inAppId;

            ShortToChar(inLen, &outData[index]);
            index += 2u;

            MemoryCpy(&outData[index], DEV_TOTAL_FRAME_LEN, inData, inLen); /*将需要打包数据拷贝到临时缓冲区*/

            index = inLen + index;

            crcValue = Crc32(outData, index);

            LongToChar(crcValue, &outData[index]);

            *pOutLen = index + 4u;

            if(DEVTYPE_NTP == inDevType)
            {
                retVal = HANDLE_OUT_MICR_NTP;
               }
            else
            {
                retVal = HANDLE_OUT_MICR_DEV;
               }

        }
        else
        {
            MemoryCpy(outData, DEV_TOTAL_FRAME_LEN, inData, inLen); /*将需要打包数据拷贝到临时缓冲区*/
            *pOutLen = inLen;
            retVal = HANDLE_OUT_NOT_MICR;
        }

    }

    return retVal;

}

/*
* 功能描述：读取设备配置信息
* 参数说明： 
* 返回值  ： 1:成功  0,失败
*/
UINT8_S AdptPlatGetDevCfgDetail(const UINT32_S inListLen, AdptDevCfgDetailStruct outDevCfgDetailList[], UINT32_S* outDevNum)
{
    UINT8_S retVal = 1u;
    UINT32_S funcVal = 0u;
    UINT32_S devCfgNum = 0u;
    UINT32_S ii = 0u;
    UINT8_S micrNum = 0u;

    T_DevCfgDetail devCfgList[PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM];

    MemorySet(devCfgList, PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM * sizeof(T_DevCfgDetail),
        0u,PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM * sizeof(T_DevCfgDetail));
    devCfgNum = 0u;
    
    if((NULL == outDevCfgDetailList) || (NULL  == outDevNum))
    {
        retVal = 0u;
        
    }

    if(1u == retVal)
    {
        funcVal = F_VCP_GetDevCfgDetail(PLATFORM_COMM_DEV_MAXSUM * PLATFORM_DEV_SYS_NUM, devCfgList, &devCfgNum);
        if(funcVal > devCfgNum)
        {
            /*配置文件中的设备个数多余要读取的设备个数(空间不足)*/
            retVal = 0u;
        }
    }

    if(1u == retVal)
    {
        if(inListLen < devCfgNum )
        {
            /*outDevCfgDetailList的空间不足*/
            retVal = 0u;
        }
    }

    
    if(1u == retVal)
    {
        for(ii = 0u; ii < devCfgNum;ii++)
        {
            outDevCfgDetailList[ii].devType = devCfgList[ii].BasicInfo.DevType;
            outDevCfgDetailList[ii].devId = devCfgList[ii].BasicInfo.AppId;
            outDevCfgDetailList[ii].devSysId = devCfgList[ii].BasicInfo.AccSys;

            outDevCfgDetailList[ii].rcvPipeNum = devCfgList[ii].ExInfo.RecvNum;
            outDevCfgDetailList[ii].sndPipeNum = devCfgList[ii].ExInfo.SendNum;
            outDevCfgDetailList[ii].sndPipeIndex = 0u;

            if (DEVTYPE_MIC_R == devCfgList[ii].BasicInfo.DevType)
            {
                micrNum++;
            }

        }
        *outDevNum = devCfgNum;

        AdapterSetMicrNum(micrNum);

    }

    return retVal;
}



/*
* 功能描述: 获得指定设备的数据 使用平台提供的增强型接口 
* 参数：
*            输入:
*            inDevType : 输入设备的逻辑类型
*            inAppId   : 输入设备的应用ID
*            inDevSys  : 输入设备的所在系别
*            inPipeId: 输入所用通道号
*            ioUsrBuff: ioUsrBuff ->ptrMsg,接收缓冲区地址
*                           ioUsrBuff ->allocLen,接收缓冲可用空间
*            输出:
*            ioUsrBuff: ioUsrBuff ->ptrMsg,接收缓冲区地址
*                         ioUsrBuff ->dataLen,接收到的数据长度
*返回值: 1，成功；0，失败
*/

UINT8_S AdptPlatUsrDataRecv(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT32_S inPipeId,
                                  AdptUsrBuffStruct* ioUsrBuff)
{
    UINT8_S retVal = 0u;
    UINT8_S rcvDataBuff[DEV_TOTAL_FRAME_LEN] = {0u};

    T_UsrBuff  vcpBuff;
    E_UsrRxStatus rtnValue;

    vcpBuff.ptrMsg = rcvDataBuff;
    vcpBuff.dataLen = 0u;
    vcpBuff.allocLen = DEV_TOTAL_FRAME_LEN;

    if(NULL == ioUsrBuff)
    {
        retVal = 0u;
    }
    else
    {
        rtnValue = F_VCP_UsrDataRecvEx(inDevType, inAppId, inDevSys, inPipeId, &vcpBuff);
		
        if(e_UsrRxLcAppNew == rtnValue)
        {
            if(ioUsrBuff->allocLen > vcpBuff.dataLen)
            {
                MemoryCpy(ioUsrBuff->ptrMsg,ioUsrBuff->allocLen,vcpBuff.ptrMsg,vcpBuff.dataLen);
                ioUsrBuff->dataLen = vcpBuff.dataLen;
                retVal = 1u;
            }
            else
            {
                /*空间不足*/
                retVal = 0u;
            }

        }
        else
        {
            /*未接收到数据*/
            retVal = 0u;
        }

    }

    return retVal;
}


/*
* 功能描述: 向指定设备发送数据 使用平台提供的增强型接口
* 参数：
*            输入:
*            inDevType : 输入设备的逻辑类型
*            inAppId   : 输入设备的应用ID
*            inDevSys  : 输入设备的所在系别
*            inPipeId: 输入所用通道号
*            inData:输入发送缓冲区地址
*            dataLen:输入发送数据长度
*            输出:
*            无
*返回值: 1，成功；0，失败
*/

UINT8_S AdptPlatUsrDataSend(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT32_S inPipeId,
                                  const UINT8_S*  inData,
                                  const UINT32_S dataLen)
{

    UINT8_S retVal = 1u;/*函数返回值*/
    E_UsrTxStatus sndResult = e_UsrTxErrData;

    if ( (NULL == inData) || (0u == dataLen) )
    {
        retVal = 0u;
    }
    else
    {

        sndResult = F_VCP_UsrDataSendEx(inDevType, inAppId, inDevSys, inPipeId, inData, dataLen);

        if (e_UsrTxSuccess == sndResult)
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
* 功能描述：通过平台前面板发送调试数据(通过网口)
* 参数说明： 
*                           输入，const UINT8_S* const inData，发送缓冲区 const UINT32 inDataLen，发送数据长度
*                           输出，无
* 返回值  ： 1:有数据且发送成功  0,(发送失败 || 发送缓冲区地址为NULL || 发送长度为0)
*/

UINT8_S AdptPlatUsrDataWatch(const UINT8_S* const inData,
                                    const UINT32_S inDataLen)
{
    UINT8_S retVal = 1u;
    E_SysBool valFVcp = e_TRUE;

    if((NULL != inData) && (0u != inDataLen))
    {
         valFVcp = F_VCP_UsrDataWatch(inData,inDataLen);
         if(e_TRUE == valFVcp)
         {
            retVal = 1u;
         }
         else
         {
            retVal = 0u;
         }
    }
    else
    {
        retVal = 0u;
    }

    return retVal;
}


/*
* 功能描述：两系同步时两系间数据接收接口函数
* 参数说明：输入:
*                            AdptCellMsgStruct* const ioMsg
*                            ioMsg.ptrMsg,接收数据缓冲器
*                            ioMsg.dataLen ,接收缓冲区可用空间
*                            输出 :
*                            AdptCellMsgStruct* const ioMsg
*                            ioMsg.ptrMsg,接收数据存放缓冲器
*                            ioMsg.dataLen ,接收数据长度
*
* 返回值      :  1,成功 ，0，失败
*/
UINT8_S AdptPlatUsrDataRecvMutual(AdptCellMsgStruct* const ioMsg)
{
    UINT8_S retVal = 1u;
    E_UsrRxStatus result = e_UsrRxLcEmpty;
    T_CellMsg rcvMsg;
    UINT8_S buff[DEV_TOTAL_FRAME_LEN] = {0u};

    rcvMsg.ptrMsg = buff;
    rcvMsg.dataLen = 0u;

    if(NULL == ioMsg)
    {
        retVal = 0u;
    }

    if(1u == retVal)
    {
        result = F_VCP_UsrDataRecvMutual(&rcvMsg);

        if(e_UsrRxLcAppNew != result)
        {
            /*未接收到数据*/
            retVal = 0u;
        }
    }

    if(1u == retVal)
    {
        if(ioMsg->dataLen < rcvMsg.dataLen)
        {
            /*空间不足*/
            retVal = 0u;
        }
    }

    if(1u == retVal)
    {
        MemoryCpy(ioMsg->ptrMsg,DEV_TOTAL_FRAME_LEN,rcvMsg.ptrMsg,rcvMsg.dataLen);
        ioMsg->dataLen = rcvMsg.dataLen;
    }

    return retVal;
}


/*
* 功能描述：两系同步时两系间数据发送接口函数
* 参数说明：输入,
*                            const void* const inData，发送数据缓冲区
*                            const UINT32 inDataLen,发送数据长度
* 返回值      :  1,成功 ，0，失败
*/

UINT8_S AdptPlatUsrDataSendMutual(const void* const inData, const UINT32_S inDataLen)
{
    UINT8_S retVal = 1u;
    E_SysBool sndResult;

    if(NULL == inData )
    {
        retVal = 0u;
    }

    if(1u == retVal)
    {
        sndResult = F_VCP_UsrDataSendMutual(inData, inDataLen);

        if (e_TRUE == sndResult)
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
* 功能描述：驱使平台宕机的接口函数
* 参数说明：const UINT32 errNo ，需要记录的错误码
* 返回值      :  无
*/
void AdptPlatUsrHaltSystem(const UINT32_S inErrCode)
{
    F_VCP_UsrHaltSystem(inErrCode);
}



/*
* 功能描述：获取设备状态
* 参数说明： 
*                           输入，const UINT8_S devType，设备类型; const UINT8_S devId，设备ID;const UINT8_S sysId,设备ID
*                           输出，无
* 返回值  ： 设备状态

*/

UINT8_S AdptPlatInquiryDevStatus(const UINT32_S devType,const UINT32_S devId,const UINT32_S sysId)
{
    UINT8_S retVal = DEV_STATE_NORMAL;

    T_SysDevInf devStaStr;

    devStaStr = F_VCP_InquiryDevStatus(devType,devId,sysId);

    if(e_SysDevNotExist == devStaStr.Status)
    {
        retVal = DEV_STATE_EXIST_NO;
    }
    else if(e_SysDevInit == devStaStr.Status)
    {
        retVal = DEV_STATE_INIT;
    }
    else if(e_SysDevNormal == devStaStr.Status)
    {
        retVal = DEV_STATE_NORMAL;
    }
    else if(e_SysDevTesting == devStaStr.Status)
    {
        retVal = DEV_STATE_SELFCHECK;
    }
    else if(e_SysDevFault == devStaStr.Status)
    {
        retVal = DEV_STATE_FAULT;
    }
    else
    {
        retVal = DEV_STATE_FAULT;
    }

    return retVal;
}


/*
* 功能描述：获取平台周期开始系统时钟的接口函数
* 参数说明： 
*                         输入，无
*                         输出，
*                         UINT32 *sec，秒
*                         UINT32 * msec, 毫秒
* 返回值  ： 无
*/
void AdptPlatSystemClkGet(UINT32_S *sec, UINT32_S *msec)
{
    T_SysClk outSysClk;

    if((NULL != sec ) && (NULL != msec))
    {
        F_VCP_SystemClkGet(&outSysClk);
        *sec = outSysClk.Sec;
        *msec = (UINT32_S)((FLOAT32_S)outSysClk.uSec * 0.001);
    }

}


/*
* 功能描述：获取系统日历时间的接口函数
* 参数说明： 
*                           输入，无
*                           输出，
*                                UINT32 *year，年
*                                UINT32 * month, 月
*                                UINT32 * day,     日
*                                UINT32 *hour,     时
*                                UINT32 *min,      分
*                                UINT32 *sec,      秒
*                                (无效值:0xFFFF)
* 返回值  ： 无
*/
void  AdptPlatCalendarClkGet(UINT32_S *year, UINT32_S * month, UINT32_S * day, UINT32_S *hour, UINT32_S *min, UINT32_S *sec)
{

    T_CalendarClk outClk;
    if((NULL != year ) && (NULL != month )&& (NULL != day )&& (NULL != hour )&& (NULL != min )&& (NULL != sec ))
    {
        if(e_TRUE == F_VCP_CalendarClkGet(&outClk))
        {
            *year = outClk.Year;
            *month = outClk.Mon;
            *day = outClk.Day;
            *hour = outClk.Hour;
            *min = outClk.Min;
            *sec = outClk.Sec;
        }
        else
        {
            *year = 0xFFFFu;
            *month = 0xFFFFu;
            *day = 0xFFFFu;
            *hour = 0xFFFFu;
            *min = 0xFFFFu;
            *sec = 0xFFFFu;
        }

    }

}

/*
* 功能描述： 设置系统日历时间接口函数
* 参数说明： 
*                           输入，
*                                UINT32 year，年
*                                UINT32 month, 月
*                                UINT32 day,     日
*                                UINT32 hour,     时
*                                UINT32 min,      分
*                                UINT32 sec,      秒
*                           输出，无
* 返回值  ： 1，成功  0，失败
*/

UINT8_S AdptPlatCalendarClkSet(UINT32_S year, UINT32_S month, UINT32_S day, UINT32_S hour, UINT32_S min, UINT32_S sec)
{
    UINT8_S retVal = 0;

    T_CalendarClk inClk;

    inClk.Year = year;
    inClk.Mon = month;
    inClk.Day= day;
    inClk.Hour= hour;
    inClk.Min= min;
    inClk.Sec = sec;

    if(e_TRUE == F_VCP_CalendarClkSet(&inClk))
    {
        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }

    return retVal;

}


/*
* 功能描述：获取当前所处系别信息(0x01 ,I系;0x02,II系)接口函数
* 参数说明： 无
* 全局变量： 
* 返回值  ： 当前所处系别信息(0x01 ,I系;0x02,II系)
*/

UINT32_S AdptPlatGetSystemId(void)
{
    UINT32_S sysId = 0u;

    F_VCP_GetSystemId(&sysId);           /*获取本系系别:0x01 ,I系;0x02,II系*/

    return sysId;
}

/*
* 功能描述：获取主系系别信息(0x01 ,I系;0x02,II系)接口函数
* 参数说明： 无
* 全局变量： 
* 返回值  ：  主系系别信息(0x01 ,I系;0x02,II系)
*/
UINT32_S AdptPlatGetMasterId(void)
{
    UINT32_S masterId = 0u;

    F_VCP_GetMasterId(&masterId);           /*获取本系系别:0x01 ,I系;0x02,II系*/

    return masterId;
}

/*
* 功能描述：提供给应用导机注册接口函数
* 参数说明：const UINT32 inMaxLen, 注册最大倒机数据长度;
*                            const UINT32 inInterval,注册强制倒机周期间隔;
*                            AdptTrackDataGet inDataGet, 注册获取USR倒机数据函数
*                            AdptTrackDataSet inDataSe,t注册设置USR倒机数据函数
* 返回值      :    1,成功 0,失败
*/
UINT8_S AdptPlatTrackRegister(const UINT32_S inMaxLen, const UINT32_S inInterval,
                   AdptTrackDataGet inDataGet, AdptTrackDataSet inDataSet)
{
    UINT8_S retVal = 0u;
    E_SysBool FuncVal = e_FALSE;

    if((NULL != inDataGet) && (NULL != inDataSet))
    {
        FuncVal =  F_VCP_TrackRegister(inMaxLen,inInterval,(F_TrackDataGet)inDataGet,(F_TrackDataSet)inDataSet);
        if(e_TRUE == FuncVal)
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
* 功能描述：获取平台周期号的接口函数
* 参数说明：无
* 返回值      :    平台周期号
*/
UINT32_S AdptPlatCycNum(void)
{
    UINT32_S cycleNum = 0u;

    cycleNum = F_VCP_Test_GetCycleNum();

    return cycleNum;
}


/*
* 功能描述：Rssp协议进行初始化 
* 参数说明：selfDevId本机设备名，inCfgLen配置数据长度，inCfgBuf配置数据缓冲区 
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptPlatRsspInit(const UINT16_S selfDevId, const UINT16_S inCfgLen, UINT8_S *inCfgBuf)
{
    UINT8_S retVal = 1u;
#if 0 /* TODO INIT RSSP */
    E_Bool temp = r_FALSE;

    UINT16_S i = 0;

    if (inCfgBuf != NULL)
    {

        temp = Rsp1_Init((const UShort)selfDevId, (const UShort)inCfgLen, (UTiny *)inCfgBuf);

        if (r_TRUE == temp)
        {
            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }
    }
#endif
    return retVal;
}


/*
* 功能描述：Rssp协议更新周期时钟 
* 参数说明：无
* 返回值      :    无
*/
void AdptPlatRsspUpdateClock(void)
{
#if 0
    Rsp1_UpdateClock();
#endif
    return;
}

/*
* 功能描述：Rssp协议获取同步数据
* 参数说明：buf同步数据缓冲区 
* 返回值      :    同步数据长度 
*/
UINT16_S AdptPlatRsspGetSynData(UINT8_S *buf)
{
    UINT16_S retVal = 0u;
#if 0	/* TODO: Get status data of rssp */
    if (buf != NULL)
    {
        retVal = (UINT16_S)Rsp1_GetSynData((UTiny *)buf);
    }
#endif
    return retVal;
}

/*
* 功能描述：Rssp协议传输同步数据
* 参数说明：buf同步数据缓冲区 ,数据长度 
* 返回值      :    同步数据长度 
*/
void AdptPlatRsspSetSynData(UINT8_S *buf, UINT16_S len)
{
#if 0	/* TODO:sys rssp data */
    if (buf != NULL)
    {
        Rsp1_SetSynData((UTiny *)buf, (const UShort)len);
    }
#endif
    return;
}

/*
* 功能描述：Rssp协议打包函数 
* 参数说明：inDstDevId设备名，inLen输入长度，inBuf输入数据，
*                     outTsdLen应用数据长度，outTsdBuf应用数据，outSsLen对时帧长度，outSsBuf对时帧数据
* 返回值      :    0类型错误，1 长度错误，2未打包TSD，3已打包TSD 
*/
UINT8_S AdptPlatRsspPackData(const UINT16_S inDstDevId, const UINT16_S inLen, UINT8_S *inBuf,
        UINT16_S *outTsdLen, UINT8_S *outTsdBuf,UINT16_S *outSseLen, UINT8_S *outSseBuf,UINT16_S *outSsrLen, UINT8_S *outSsrBuf)
{
    UINT8_S proResult = 1u;
#if 0 /* TODO: Snd data by rssp */
    S_Msg inMsg;
    S_Msg outMsg;
    S_SsMsg outSseMsg;
    S_SsMsg outSsrMsg;

    if ((inBuf != NULL)&&(outTsdLen != NULL)&&(outTsdBuf != NULL)&&(outSseLen != NULL)&&(outSseBuf != NULL)&&(outSsrLen != NULL)&&(outSsrBuf != NULL))
    {
        MemorySet(&inMsg, sizeof(S_Msg), 0u, sizeof(S_Msg));
        MemorySet(&outMsg, sizeof(S_Msg), 0u, sizeof(S_Msg));
        MemorySet(&outSseMsg, sizeof(S_SsMsg), 0u, sizeof(S_SsMsg));
        MemorySet(&outSsrMsg, sizeof(S_SsMsg), 0u, sizeof(S_SsMsg));

        if (0u == MemoryCpy(&inMsg.buff, c_BUFF_SIZE, inBuf, inLen))
        {
            inMsg.length = inLen;

            proResult = (UINT8_S)Rsp1_PackageData(inDstDevId, &inMsg, &outMsg, &outSseMsg, &outSsrMsg);

            MemoryCpy(outTsdBuf, DEV_TOTAL_FRAME_LEN, &outMsg.buff[0u], outMsg.length);
            *outTsdLen = outMsg.length;

            MemoryCpy(outSseBuf, DEV_TOTAL_FRAME_LEN, &outSseMsg.buff[0u], outSseMsg.length);
            *outSseLen = outSseMsg.length;

            MemoryCpy(outSsrBuf, DEV_TOTAL_FRAME_LEN, &outSsrMsg.buff[0u], outSsrMsg.length);
            *outSsrLen = outSsrMsg.length;
        }
        else
        {
            /* 内存不足，暂不处理 */
        }

    }
#endif
    return proResult;
}

/*
* 功能描述：Rssp协议解包函数  
* 参数说明：inDstDevId设备名，inLen输入长度，inBuf输入数据，
*                     outLen应用数据长度，outBuf应用数据 
* 返回值      :    0类型错误，1 长度错误，2 SSE or SSR，3 RSD 
*/
UINT8_S AdptPlatRsspParseData(const UINT16_S inDstDevId, const UINT16_S inLen, UINT8_S *inBuf,
        UINT16_S *outLen, UINT8_S *outBuf)
{
    UINT8_S proRet = 0u;
#if 0 /* TODO: rcv data */
    if ((inBuf != NULL)&&(outLen != NULL)&&(outBuf != NULL))
    {
        proRet = (UINT8_S)Rsp1_CheckPackage((const UShort)inDstDevId, (const UShort)inLen, (UTiny *)inBuf, 
            (UShort*)outLen, (UTiny *)outBuf);
    }
#endif
    return proRet;
}

/*
* 功能描述：Rssp协议获取链路信息 
* 参数说明：inDstDevId设备名，timeDiff 时间差 
* 返回值      :    0关闭，1正常 
*/
UINT8_S AdptPlatRsspGetChaStat(const UINT16_S inDstDevId, UINT16_S *timeDiff)
{
    UINT8_S status = 1u;
/* todo get Rssp Link Status */
#if 0
    E_Bool temp = r_FALSE;

    if (timeDiff != NULL)
    {
        temp = Rsp1_GetChanelStatus((const UShort)inDstDevId, (UShort *)timeDiff);

        if (r_TRUE == temp)
        {
            status = 1u;
        }
        else
        {
            status = 0u;
        }
    }
#endif
    return status;
}

/*
* 功能描述：将输入设备类型、设备识别号对应的链路置为关闭状态， 
*                            协议栈将拒绝对应设备传入数据。 
* 参数说明：dstDevId设备名
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptPlatRsspClose(const UINT16_S dstDevId)
{
    UINT8_S retVal = 1u;
#if 0    /* todo Rssp close */	
    E_Bool temp = r_FALSE;
 
    temp = Rsp1_Close((const UShort)dstDevId);

    if (r_TRUE == temp)
    {
        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }
#endif
    return retVal;
}

/*
* 功能描述：将输入设备类型、设备识别号对应的链路置为打开状态， 
*                            协议栈将允许对应设备传入数据。 
* 参数说明：dstDevId设备名
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptPlatRsspOpen(const UINT16_S dstDevId)
{
    UINT8_S retVal = 1u;
#if 0    /* todo Rssp close */
    E_Bool temp = r_FALSE;
    
    temp = Rsp1_Open((const UShort)dstDevId);

    if (r_TRUE == temp)
    {
        retVal = 1u;
    }
    else
    {
        retVal = 0u;
    }
#endif
    return retVal;
}

/*
* 功能描述：查询各插件处理软件版本及通信软件版本
* 参数说明：
*Para    : inDevType      : 输入设备的逻辑类型
*            inAppId        : 输入设备的应用编号
*            inAccSys       : 输入设备所在系别标识
*            plugAppVer : 输出处理软件版本
*            plugCommVer : 输出通讯软件版本

*          |  版本标识  |  版本类型  |  补充编号  |  版本编号  |
*          |-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|-- 1 Byte --|
*          版本标识：'V'
*          版本类型：'A' - 'Z'
*          版本编号：1 - 15
*          补充编号：正式版本：0
*                    测试版本：'a' - 'z'
*
*          显示示例：
*          0x56 -> 'V'
*          0x43 -> 'C'
*          0x61 -> 'a'
*          0x56430001UL -> V.C.0001   正式版
*          0x56436101UL -> V.C.0001a  测试版


* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptPlatPlugSwVersionGet(const UINT32_S  inDevType,
                                  const UINT32_S  inAppId,
                                  const UINT32_S  inAccSys,
                                  UINT32_S* const plugAppVer,
                                  UINT32_S* const plugCommVer)
{
    UINT8_S retVal = 0u;
 #if 0 /* TODO：获取板卡状态 */   
    E_SysBool funVal = e_TRUE;

    if((NULL != plugAppVer) && (NULL != plugCommVer))
    {
            *plugAppVer = 0u;
            *plugCommVer = 0u;
            funVal  = F_VCP_InquirySwVersion(inDevType,inAppId,inAccSys,plugAppVer,plugCommVer);
            if(e_TRUE == funVal)
            {
                retVal = 1u;
            }
    }
#endif	
    return retVal;

}

/*
* 功能描述：获取平台系统时钟的接口函数 
*         注意此数据获取为系统当前时间，仅供串口打印日志使用 
* 参数说明： 
*                         输入，无
*                         输出，
*                         UINT32 *sec，秒
*                         UINT32 * msec, 毫秒
* 返回值  ： 无 
*/
void AdptPlatTestSystemClkGet(UINT32_S *sec, UINT32_S *msec)
{
#if 0	/* TODO: Get time */
    T_SysClk outSysClk;

    if((NULL != sec ) && (NULL != msec))
    {
        outSysClk = F_VCP_Test_GetSysClk();

        *sec = outSysClk.Sec;
        *msec = (UINT32_S)((FLOAT32_S)outSysClk.uSec * 0.001);
    }
#endif	
}
