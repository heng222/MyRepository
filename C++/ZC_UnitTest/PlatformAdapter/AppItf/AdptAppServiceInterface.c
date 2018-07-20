/********************************************************
*                                                                                                            
* 文 件 名： AdptAppServiceInterface.c   
* 作    者： 董欣 
* 创建时间： 2016-09-01
* 功能描述： 适配层对应用层的接口文件 
* 备    注： 无 
*
********************************************************/ 

#include "AdptAppServiceInterface.h"
#include "../PlatItf/AdptPlatServiceInterface.h"
#include "../AdptHandle/AdapterExtDevInOutManage.h"
#include "../PlatformLog/AdapterLog.h"
#include "../../Common/MemSet.h"
#include "../PlatItf/AdptPlatFileInterface.h"
#include "../PlatItf/AdptPlatServiceInterface.h "
#include "../../cspadpt/Vcp_Service_TestInterface.h"



UINT16_S gLocalName = 0u;
UINT16_S gTrainName = 0u;

/*
* 功能描述：提供给应用设备通信初始化接口函数
* 参数说明： 
*                           输入，
*                           无
*                           输出，
*                           无
* 返回值  ：  1 成功 
*           0 失败 
*/
UINT8_S  AdptAppExtDevInit(void)
{
    UINT8_S retVal = 0u;

    retVal = AdapterExtDevCfgInfoInit();          /*初始化设备配置信息结构*/

    if(1 == retVal)
    {
        retVal = AdapterGetDevCfgDetail(); /*读取设备配置信息*/
    }

    return retVal;
}



/*
* 功能描述：外部设备接收处理 
* 参数说明： 
*                           输入，
*                           无
*                           输出，
*                           无
* 返回值  ：  无
*/
void  AdptAppExtDevInDataManage(void)
{
    AdapterExtDevInDataManage();

}


/*
* 功能描述：外部设备数据接收处理 
* 参数说明： 
*                           输入，
*                           无
*                           输出，
*                           无
* 返回值  ：  无
*/
void AdptAppExtDevOutDataManage(void)
{
    AdapterExtDevOutDataManage();
}



/*
*功能描述: 数据输入接口
* 参数：
*            输入:
*            inDevType : 输入设备的逻辑类型
*            inAppId   : 输入设备的应用ID
*            inDevSys  : 输入设备的所在系别
*            ioUsrBuff: ioUsrBuff ->ptrMsg,接收缓冲区地址
*                           ioUsrBuff ->allocLen,接收缓冲可用空间
*            输出:
*            ioUsrBuff: ioUsrBuff ->ptrMsg,接收缓冲区地址
*                         ioUsrBuff ->dataLen,接收到的数据长度
*返回值: 1，成功；0，失败
*/

UINT8_S AdptAppUsrDataRecv(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  AdptUsrBuffStruct* ioUsrBuff)
{
    UINT8_S retVal = 0u;

    if ( ioUsrBuff != NULL )
    {
        retVal = AdptPlatUsrDataRecv(inDevType, inAppId, inDevSys, 0u, ioUsrBuff);
    }

    return retVal;
}


/*
*功能描述: 数据输出接口
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

UINT8_S AdptAppUsrDataSend(const UINT32_S inDevType,
                                  const UINT32_S inAppId,
                                  const UINT32_S inDevSys,
                                  const UINT8_S*  inData,
                                  const UINT32_S dataLen)
{
    UINT8_S retVal = 0u;

    if ( inData != NULL )
    {
        retVal = AdptPlatUsrDataSend(inDevType, inAppId, inDevSys, 0u, inData, dataLen);
    }

    return retVal;
}




/*
* 功能描述：提供给应用通过平台前面板发送调试数据(通过网口)的接口
* 参数说明： 
*                           输入，
*                           const UINT8* const inData，发送缓冲区 
*                           const UINT32 inDataLen，发送数据长度
*                           输出，
*                           无
* 返回值  ： 1:有数据且发送成功 
*                          0:(发送失败 || 发送缓冲区地址为NULL || 发送长度为0)
*/


UINT8_S AdptAppUsrDataWatch(const UINT8_S* const inData,
                                    const UINT32_S inDataLen)
{
    UINT8_S retVal = 0u;

    if ( inData != NULL )
    {
        retVal = AdptPlatUsrDataWatch(inData,inDataLen);
    }

    return retVal;
}


/*
* 功能描述：提供给应用两系同步时两系间数据接收接口函数
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
UINT8_S AdptAppUsrDataRecvMutual(AdptCellMsgStruct* const ioMsg)
{
    UINT8_S result = 0u;

    if ( ioMsg != NULL )
    {
        result = AdptPlatUsrDataRecvMutual(ioMsg);
    }

    return result;

}


/*
* 功能描述：提供给应用两系同步时两系间数据发送接口函数
* 参数说明：输入,
*                            const void* const inData，发送数据缓冲区
*                            const UINT32 inDataLen,发送数据长度
* 返回值      :  1,成功 ，0，失败
*/
UINT8_S AdptAppUsrDataSendMutual(const void* const inData, const UINT32_S inDataLen)
{
    UINT8_S result = 0u;

    if ( inData != NULL )
    {
        result = AdptPlatUsrDataSendMutual(inData, inDataLen);
    }

    return result;
}



/*
* 功能描述：提供给应用驱使平台宕机的接口函数
* 参数说明：const UINT32 errNo ，需要记录的错误码
* 返回值      :  无
*/
void  AdptAppUsrHaltSystem(const UINT32_S errNo)
{
    printf("Halt! %x\n",errNo);
    AdptAppLogPrintf(1u, "Halt! %x\n",errNo);
    AdptPlatUsrHaltSystem(errNo);
}



/*
* 功能描述：提供给应用获取平台相关设备状态的接口函数
* 参数说明： 
*                           输入，
*                           const UINT8 devType，设备类型; 
*                           const UINT8 devId，设备ID;
*                           const UINT8 sysId,设备ID
*                           输出，无
* 返回值  ： 设备状态
                            1,设备不存在
                   2,设备初始化
                   4,设备正常状态
                   5,设备故障状态 
                   6,设备自检
*/
UINT8_S AdptAppInquiryDevStatus(const UINT32_S devType,const UINT32_S devId,const UINT32_S sysId)
{
    UINT8_S retVal = 0u;

    retVal = AdptPlatInquiryDevStatus(devType,devId,sysId);

    return retVal;
}



/*
* 功能描述：提供给 应用获取平台周期开始系统时钟的接口函数
* 参数说明： 
*                         输入，无
*                         输出，
*                                    UINT32 *sec，秒
*                                    UINT32 * msec, 毫秒
* 返回值  ： 无
*/

void AdptAppSystemClkGet(UINT32_S *sec, UINT32_S *msec)
{
    if (( sec != NULL ) && ( msec != NULL ))
    {
        AdptPlatSystemClkGet(sec, msec);
    }
}

/*
* 功能描述：提供给应用获取系统日历时间的接口函数
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
void  AdptAppCalendarClkGet(UINT32_S *year,UINT32_S * month,UINT32_S * day,UINT32_S *hour,UINT32_S *min,UINT32_S *sec)
{
    if (( year != NULL ) && ( month != NULL ) && ( day != NULL ) && ( hour != NULL ) && ( min != NULL ) && ( sec != NULL ))
    {
        AdptPlatCalendarClkGet(year,month,day,hour,min,sec);
    }
}

/*
* 功能描述： 提供给应用设置系统日历时间接口函数
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
UINT8_S  AdptAppCalendarClkSet(UINT32_S year,UINT32_S month,UINT32_S day,UINT32_S hour,UINT32_S min,UINT32_S sec)
{
    UINT8_S retVal = 0u;

    retVal = AdptPlatCalendarClkSet(year, month, day, hour, min, sec);

    return retVal;

}

/*
* 功能描述：提供给 应用获取当前所处系别信息(0x01 ,I系;0x02,II系)接口函数
* 参数说明： 无
* 全局变量： 
* 返回值  ： 当前所处系别信息(0x01 ,I系;0x02,II系)
*/
UINT32_S AdptAppGetSystemId(void)
{
    UINT32_S sysId = 0u;

    sysId = AdptPlatGetSystemId();         /*获取本系系别:0x01 ,I系;0x02,II系*/

    return sysId;
}

/*
* 功能描述：提供给 应用获取主系系别信息(0x01 ,I系;0x02,II系)接口函数
* 参数说明： 无
* 全局变量： 
* 返回值  ：  主系系别信息(0x01 ,I系;0x02,II系)
*/
UINT32_S AdptAppGetMasterId(void)
{
    UINT32_S masterId = 0u;

    masterId = AdptPlatGetMasterId();         /*获取本系系别:0x01 ,I系;0x02,II系*/

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
UINT8_S AdptAppTrackRegister(const UINT32_S inMaxLen,
                               const UINT32_S inInterval,
                               AdptTrackDataGet inDataGet,
                               AdptTrackDataSet inDataSet)
{
    UINT8_S result = 0u;

    result = AdptPlatTrackRegister(inMaxLen, inInterval, inDataGet, inDataSet);

    return result;
}


/*
* 功能描述：提供给应用获取平台周期号的接口函数
* 参数说明：无
* 返回值      :    平台周期号
*/
UINT32_S AdptAppCycNum(void)
{
    UINT32_S cycleNum = 0u;
    UpdataRunCycNum(cycleNum);
    return cycleNum;
}


/*
* 功能描述：提供给应用设置系统名称的接口函数
* 参数说明：localName 系统名称  
* 返回值      :    
*/
void AdptAppSetLocalName(UINT16_S localName)
{

    gLocalName = localName;

}

/*
* 功能描述：提供给应用获取系统名称的接口函数
* 参数说明：无
* 返回值      :    系统名称 
*/
UINT16_S AdptAppGetLocalName(void)
{

    return gLocalName;

}


/*
* 功能描述：Rssp协议进行初始化 
* 参数说明：selfDevId本机设备名 
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptAppRsspInit(const UINT16_S selfDevId)
{
    UINT8_S retVal = 0u;
    UINT8_S fileBuff[RSSP_CFG_MAX_LEN] = {0u};
    UINT8_S fileStatus = 0u;
    UINT32_S fileLen = 0u;
    FILEType fileHandle;

    MemorySet(fileBuff,RSSP_CFG_MAX_LEN,0u,RSSP_CFG_MAX_LEN);

    fileStatus = AdptPlatFileOpen(RSSP_CFG_NAME, 0u, &fileHandle);

    if ( 1u == fileStatus )
    {
        fileLen = AdptPlatFileRead(fileHandle, RSSP_CFG_NAME, &fileBuff[0u], RSSP_CFG_MAX_LEN);

        if ( fileLen > 0u )
        {
            retVal = AdptPlatRsspInit(selfDevId, fileLen,&fileBuff[0u]);
        }
    }

    return retVal;
}

/*
* 功能描述：Rssp协议更新周期时钟 
* 参数说明：无
* 返回值      :    无
*/
void AdptAppRsspUpdateClock(void)
{

    AdptPlatRsspUpdateClock();

    return;
}

/*
* 功能描述：Rssp协议获取同步数据
* 参数说明：buf同步数据缓冲区 
* 返回值      :    同步数据长度 
*/
UINT16_S AdptAppRsspGetSynData(UINT8_S *buf)
{
    UINT16_S retVal = 0u;

    if (buf != NULL)
    {
        retVal = AdptPlatRsspGetSynData(buf);
    }

    return retVal;
}

/*
* 功能描述：Rssp协议传输同步数据
* 参数说明：buf同步数据缓冲区 ,数据长度 
* 返回值      :    同步数据长度 
*/
void AdptAppRsspSetSynData(UINT8_S *buf, UINT16_S len)
{

    if (buf != NULL)
    {
        AdptPlatRsspSetSynData(buf, len);
    }

    return;
}

/*
* 功能描述：将输入设备类型、设备识别号对应的链路置为关闭状态， 
*                            协议栈将拒绝对应设备传入数据。 
* 参数说明：dstDevId设备名
* 返回值      :    1 成功， 0失败 
*/
UINT8_S AdptAppRsspClose(const UINT16_S dstDevId)
{
    UINT8_S retVal = 0u;

    retVal = AdptPlatRsspClose(dstDevId);

    return retVal;
}

/*
* 功能描述：提供给应用查询各插件处理软件版本及通信软件版本
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
UINT8_S AdptAppPlugSwVersionGet(const UINT32_S  inDevType,
                                  const UINT32_S  inAppId,
                                  const UINT32_S  inAccSys,
                                  UINT32_S* const plugAppVer,
                                  UINT32_S* const plugCommVer)
{

    UINT8_S retVal = 0u;
    
    UINT8_S funVal = 0u;

    if((NULL != plugAppVer) && (NULL != plugCommVer))
    {
        *plugAppVer = 0u;
        *plugCommVer = 0u;
        funVal  = AdptPlatPlugSwVersionGet(inDevType,inAppId,inAccSys,plugAppVer,plugCommVer);
        if(1u == funVal)
        {
            retVal = 1u;
        }
    }
    return retVal;

}

/*
* 功能描述：提供给应用设置系统一端二端名的接口函数
* 用于区分车载ATP ATO设备一端二端，如果为地面设备不需要调用此函数
* 参数说明：TrainName 系统名称  
* 返回值      :    
*/
void AdptAppSetTrainName(UINT16_S TrainName)
{
    gTrainName = TrainName;
}

/*
* 功能描述：提供给应用获取系统一端二端名的接口函数
* 参数说明：无
* 返回值      :    系统名称 
*/
UINT16_S AdptAppGetTrainName(void)
{
    return gTrainName;
}

/*
* 功能描述：获取平台系统时钟的接口函数
*                 注意此数据获取为系统当前时间，仅供串口打印日志使用 
* 参数说明： 
*                         输入，无
*                         输出，
*                                    UINT32 *sec，秒
*                                    UINT32 * msec, 毫秒
* 返回值  ： 无
*/
void AdptAppTestSystemClkGet(UINT32_S *sec, UINT32_S *msec)
{
    if (( sec != NULL ) && ( msec != NULL ))
    {
        AdptPlatTestSystemClkGet(sec, msec);
    }
}

/*******************************************************************************
* 功能秒数：将秒数转换为日历时间    
* 输入参数：const UINT32_S Seconds(自1970年1月1日0时开始的秒数,已经默认转为本地时间)
* 输出参数：UINT8 *pCalenderBuff   时间数组:年月日时分秒
* 返回值：  1-成功;0-失败;
********************************************************************************/
UINT8_S Seconds2Calendar(UINT32_S seconds, UINT32_S *pCalenderBuff)
{
    UINT8_S   retVal = 1u;                /*本函数的返回值*/
    const UINT8_S days[12u] = {31u,28u,31u,30u,31u,30u,31u,31u,30u,31u,30u,31u};    

    UINT32_S     fourYearsCal = 0u;            /*计算闰年时用到的时间中四年的数目*/
    UINT32_S     yearsCal = 0u;                /*计算秒数代表的年数*/
    UINT32_S     hourPerYear = 0u;            /*每年的小时数*/
    UINT32_S     month = 0u;                /*月份*/
    UINT32_S     day = 0u;                /*日期*/
    UINT32_S     hour = 0u;                /*时*/
    UINT32_S     min = 0u;                /*分*/
    UINT32_S     sec = 0u;                /*秒*/
    UINT32_S    secondsTemp = 0u;

    if (NULL != pCalenderBuff)
    {

        /*得到秒信息*/
        sec = seconds%60u;

        /*得到分信息*/
        seconds /= 60u;
        min = seconds%60u;

        /*得到小时数*/
        seconds /= 60u;

        /*取过去多少个四年,每四年有 1461*24 小时 = 35064 小时*/
        fourYearsCal = (seconds / 35064u);
        yearsCal = (fourYearsCal << 2u) + 70u;

        /*四年中剩下的小时数*/
        seconds %= 35064u;

        hourPerYear = 8760u; /*一年的小时数 365 * 24 = 8760 */ 
        /*校正闰年影响的年份,计算一年中剩下的小时数*/
        while(seconds > hourPerYear)
        {    
            /*判断闰年*/
            if ((yearsCal & 3u) == 0u)        
            {            
                /*是闰年,一年则多24小时,即一天 */           
                hourPerYear += 24u;        
            } 

            if (seconds < hourPerYear)        
            {            
                break;        
            } 

            yearsCal += 1u;        
            seconds -= hourPerYear;    

            hourPerYear = 8760u; /*一年的小时数 365 * 24 = 8760 */ 
        }

        /*得到当前时刻的小时*/
        hour = seconds%24u;
        seconds /= 24u;

        /*假定为闰年,+1变为从1开始计数*/
        seconds++; 

        /*校正润年的误差,计算月份,日期*/
        if ((yearsCal & 3u) == 0u)
        {        
            if (seconds > 60u)        
            {
                seconds--;    
            }
            else if (seconds == 60u)            
            {                
                month = 1u;
                day = 29u;

                /*用[0,99]表示年份20XX年*/
                yearsCal = yearsCal + 1900u;
                if(yearsCal < 2000u)
                {
                    retVal = 0u;
                }

                pCalenderBuff[0u] = yearsCal;
                pCalenderBuff[1u] = month + 1u;
                pCalenderBuff[2u] = day;
                pCalenderBuff[3u] = hour;
                pCalenderBuff[4u] = min;
                pCalenderBuff[5u] = sec;
            }    
            else
            {
                /*Seconds小于60时,无操作*/
            }
        }


        /*计算月日,月份从0到11 */
        #if 0
        for (month = 0; days[month] < seconds; month+=1)    
        {          
            seconds -= days[month];    
        }
        day = seconds;  

        #else
        secondsTemp = seconds;
        for(month = 0u;month < 12u; month++)
        {
            if(secondsTemp <= days[month])
            {
                break;
            }

            secondsTemp = secondsTemp - days[month];
        }
        day = secondsTemp;  
        #endif

    
        /*用[0,99]表示年份20XX年*/
        yearsCal = yearsCal + 1900u;
        if(yearsCal < 2000u)
        {
            retVal = 0u;
        }

        /*用BCD码表示年月日时分秒*/
        pCalenderBuff[0u] = yearsCal;
        pCalenderBuff[1u] = month + 1u;
        pCalenderBuff[2u] = day;
        pCalenderBuff[3u] = hour;
        pCalenderBuff[4u] = min;
        pCalenderBuff[5u] = sec;
    }

    return retVal;
}

/*******************************************************************************
* 功能秒数：将日历时间转换为秒数 
* 输入参数：UINT8 *pCalenderBuff   时间数组:年月日时分秒 
* 输出参数：无 
* 返回值：  UINT32_S Seconds(自1970年1月1日0时开始的秒数) 
*           >0 成功;0失败; 
********************************************************************************/
UINT32_S CalendarToSeconds(UINT32_S * pCalenderBuff)
{
    UINT32_S i = 0u;
    UINT32_S years = 0u;                /* 年数 */
    UINT32_S month = 0u;                /* 月份 */
    UINT32_S day = 0u;                  /* 日期 */
    UINT32_S hour = 0u;                 /* 时 */
    UINT32_S min = 0u;                  /* 分 */
    UINT32_S sec = 0u;                  /* 秒 */
    UINT32_S allHours = 0u;             /* 全部的小时数 */
    UINT32_S allSeconds = 0u;           /* 全部的秒数 */
    UINT8_S days[12u] = {31u, 28u, 31u, 30u, 31u, 30u, 31u, 31u, 30u, 31u, 30u, 31u};  /* 十二个月份对应的天数 */

    if (pCalenderBuff != NULL)
    {
        /* 取出年月日时分秒 */
        years = pCalenderBuff[0u];
        month = pCalenderBuff[1u] - 1u;
        day = pCalenderBuff[2u] - 1u;
        hour = pCalenderBuff[3u];
        min = pCalenderBuff[4u];
        sec = pCalenderBuff[5u];

        if(years < 1970u)
        {
            allSeconds = 0u;
        }
        else
        {
            /* 计时从1970年开始运算 */
            for (i = 1970u; i < years; i++)
            {
                /*判断闰年*/
                if ((i & 3u) == 0u)
                {
                    /* 是闰年,一年则多24小时 */
                    allHours += 24u;
                }
            }

            /* 计算本年，将2月份的天数按照是否为闰年更新一下 */
            if ((years & 3u) == 0u)
            {
                days[1u] = 29u;
            }

            years = years - 1970u;
            allHours = allHours + years * 365u * 24u;

            for (i = 0u; i < month; i++)
            {
                /* 不同月份天数 */
                allHours = allHours + days[i] * 24u;
            }

            allHours = allHours + day * 24u + hour;

            allSeconds = allHours * 60u * 60u + min * 60u + sec;

        }
    }

    return allSeconds;
}

