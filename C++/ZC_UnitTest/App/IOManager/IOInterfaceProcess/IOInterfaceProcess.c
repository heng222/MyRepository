/************************************************************************
*
* 文件名   ：  IOInterfaceProcess.c
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  输入输出接口处理 
* 备  注   ：  无
*
************************************************************************/

#include "IOInterfaceProcess.h"
#include "../../../Common/CircQueueStruct.h"
#include "../../SysDataManager/SysDefine.h"
#include "../../../Common/MemSet.h"

#ifdef SYS_TYPE_VXWORKS
#include "../../../PlatformAdapter/AppItf/AdptAppExtDevDataInterface.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../PlatformAdapter/PlatformLog/AdapterLog.h"
#endif

/*与CI通信队列*/
CirQueueStruct gZcToCiDataQueueStru;             /*ZC到CI数据队列*/
CirQueueStruct gCiToZcDataQueueStru;             /*CI到ZC数据队列*/

/*与ATS通信队列*/
CirQueueStruct gZcToAtsDataQueueStru;            /*ZC到ATS数据缓冲区*/
CirQueueStruct gAtsToZcDataQueueStru;            /*ATS到ZC数据缓冲区*/ /*-bye-*/


/*与ZC通信队列*/
CirQueueStruct gZcToNZcDataQueueStru;            /*ZC到NZc数据队列*/
CirQueueStruct gNZcToZcDataQueueStru;            /*NZC到ZC数据队列*/

/*与车载ATP通信队列*/
CirQueueStruct gZcToTrainDataQueueStru;           /*ZC到车载ATP数据队列*/
CirQueueStruct gTrainToZcDataQueueStru;           /*车载ATP到ZC数据队列*/

/*与Ntp通信队列*/
CirQueueStruct gZcToNtpDataQueueStru;            /*ZC到Ntp数据队列*/
CirQueueStruct gNtpToZcDataQueueStru;            /*Ntp到ZC数据队列*/
 
/*
* 功能描述： 获取平台输入的数据解析到各个通信队列中
* 参数说明： void
* 返回值  ： 无
*/
void InterfaceInputProcessToLocalQueue(void)
{
    /*处理输入的数据填写到本地各个队列中*/
#ifdef SYS_TYPE_VXWORKS
	UINT8_S  dataBuff[UDP_OUT_FRAME_LEN] = {0U};        /* 数据数组 */
	UINT32_S dataLen = 0U;                              /* 数据长度 */
	UINT8_S devType = 0U;
    UINT8_S devId = 0U;
   
    /*初始化*/
    MemorySet(&dataBuff[0],((UINT32_S)(sizeof(UINT8_S) * UDP_OUT_FRAME_LEN)),0U,((UINT32_S)(sizeof(UINT8_S) * UDP_OUT_FRAME_LEN)));

    dataLen = AdptAppExtDevRcvData(dataBuff,UDP_OUT_FRAME_LEN,&devType,&devId);

	while(0U < dataLen)
	{
	    RecvQueueToLocalSingleQueue(devType,&dataBuff[0],dataLen);		
		
	    dataLen = AdptAppExtDevRcvData(dataBuff,UDP_OUT_FRAME_LEN,&devType,&devId);
	}
#endif
}

/*
* 功能描述： 组织本地管理的各个队列信息，发送至平台进行输出
* 参数说明： void
* 返回值  ： 无
*/
void InterfaceOutputProcessToPlatform(void)
{
	/*处理输出的数据填写到平台中*/
#ifdef SYS_TYPE_VXWORKS

    UINT8_S rtnValue = 0U;
	CirQueueStruct *pCirQueueStru = NULL;              /* 本地数据队列指针 */
	
	/* ZC To CI */
	pCirQueueStru = GetZcToCiDataQueueStru();
	rtnValue = LocalSingleQueueToSendQueue(pCirQueueStru);

	
	/* ZC To ATS */
	pCirQueueStru = GetZcToAtsDataQueueStru();
	rtnValue *= LocalSingleQueueToSendQueue(pCirQueueStru);

	
	/* ZC To NZC */
	pCirQueueStru = GetZcToNZcDataQueueStru();
	rtnValue *= LocalSingleQueueToSendQueue(pCirQueueStru);

	
	/* ZC To ATP */
	pCirQueueStru = GetZcToTrainDataQueueStru();
	rtnValue *= LocalSingleQueueToSendQueue(pCirQueueStru);


	/* ZC To NTP */
	pCirQueueStru = GetZcToNtpDataQueueStru();
	rtnValue *= LocalSingleQueueToSendQueue(pCirQueueStru);

	
	/* ZC To Log */
    /* PutLogToSendQueue(); */ 
	AdptAppLogDataPack(INNER_DEVTYPE_LOG,1u);
#endif	
}

/*
* 功能描述： 将接收队列当中数据放入单个数据队列
* 参数说明： UINT8_S devType,类型
*            const UIN8_S dataBuff[],数据数组
*            UINT32_S datalen,数据长度
* 返回值  ： void
*/

void RecvQueueToLocalSingleQueue(UINT8_S devType,const UINT8_S dataBuff[],UINT32_S datalen)
{
    /* 将接收队列当中数据放入单个数据队列 */
#ifdef SYS_TYPE_VXWORKS

    CirQueueStruct *pCirQueueStru = NULL;

	switch(devType)
    {
        case INNER_DEVTYPE_CI:
			{
			    pCirQueueStru = GetCiToZcDataQueueStru();
        	}
			break;
		case INNER_DEVTYPE_ZC:
			{
                pCirQueueStru = GetNZcToZcDataQueueStru();
		    }
			break;
		case INNER_DEVTYPE_TRAIN:
			{
		        pCirQueueStru = GetTrainToZcDataQueueStru();
		    }
			break;
		case INNER_DEVTYPE_NTP:
			{
                pCirQueueStru = GetNtpToZcDataQueueStru();				
			}
			break;
		case INNER_DEVTYPE_ATS:
			{
				/* 没有ATS数据 */
				pCirQueueStru = GetAtsToZcDataQueueStru();/*-bye-*/
			}
			break;
		default:
			break;
    }

    if((NULL != pCirQueueStru) && (NULL != dataBuff)
		&& (datalen > 0U))
    {
        /*将数据添加到队列中*/
		if (0 == AddQueueData(pCirQueueStru,dataBuff,datalen))
		{
            /* 不处理 */

		}
		
    }	
#endif

}

/*
* 功能描述： 将单个队列数据放入发送的队列当中
* 参数说明： CirQueueStruct *pCirQueueStru 队列指针
* 返回值  ： 0: 失败
*            1: 成功
*/

UINT8_S LocalSingleQueueToSendQueue(CirQueueStruct *pCirQueueStru)
{
    /* 将单个队列数据放入发送的队列当中 */
    UINT8_S rtnValue = RETURN_ERROR;
#ifdef SYS_TYPE_VXWORKS
    
    UINT32_S i = 0U;        /**/
	UINT32_S pkgCount = 0U;                             /* 数据总数 */
	UINT8_S  dataBuff[UDP_MAX_BUFF_SIZE] = {0U};        /* 数据数组 */
	UINT32_S dataLen = 0U;                              /* 数据长度 */
    UINT32_S startIndex = 0U;
	UINT8_S destDevType = 0U;
    UINT8_S destDevId = 0U;
    UINT8_S addFlag = 0U;       /* 放入发送队列的成功与否标志*/
	UINT8_S breakFlag = 0U;

    /*初始化*/
    MemorySet(&dataBuff[0],((UINT32_S)(sizeof(UINT8_S) * UDP_MAX_BUFF_SIZE)),0U,((UINT32_S)(sizeof(UINT8_S) * UDP_MAX_BUFF_SIZE)));
	
    if (NULL != pCirQueueStru)
    {
        /* 获取数据包的个数 */
        pkgCount = GetQueuePkgCount(pCirQueueStru);   
		
        for(i = 0U;i < pkgCount;i++)
        {
            MemorySet(&dataBuff[0],((UINT32_S)(sizeof(UINT8_S) * UDP_MAX_BUFF_SIZE)),0U,((UINT32_S)(sizeof(UINT8_S) * UDP_MAX_BUFF_SIZE)));

            dataLen = GetQueuePkgData(pCirQueueStru,&dataBuff[0],UDP_MAX_BUFF_SIZE);
		
			if(0U < dataLen)
			{
			    /* 获取目标类型和ID */
                destDevType = dataBuff[2];
                destDevId =dataBuff[3];

				/* ATS、NTP、日志去掉4个头 */
				if(((INNER_DEVTYPE_ATS == destDevType) || (INNER_DEVTYPE_NTP == destDevType))
					&& (dataLen >= 4U))
				{
				    startIndex = 4U;
					dataLen = dataLen - 4U;
				}

                /* 将数据写入发送队列当中 */
                addFlag = AdptAppExtDevSndData(&dataBuff[startIndex],dataLen,destDevType,destDevId);

                if(0U == addFlag)
                { 
                    breakFlag = FLAG_SET;
                    break;
                }  
			}           
        }

        if(FLAG_SET == breakFlag)
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
    	
#endif	

    return rtnValue;
}

/*
* 功能描述： 获取ZcToCi接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetZcToCiDataQueueStru(void)
{
	return &gZcToCiDataQueueStru;
}

/*
* 功能描述： 获取CiToZc接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetCiToZcDataQueueStru(void)
{
	return &gCiToZcDataQueueStru;
}

/*
* 功能描述： 获取ZcTo车载ATP接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetZcToTrainDataQueueStru(void)
{
	return &gZcToTrainDataQueueStru;
}

/*
* 功能描述： 获取车载ATPToZc接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetTrainToZcDataQueueStru(void)
{
	return &gTrainToZcDataQueueStru;
}

/*
* 功能描述： 获取ZcToAts接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetZcToAtsDataQueueStru(void)
{
	return &gZcToAtsDataQueueStru;
}

/*
* 功能描述： 获取AtsToZc接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetAtsToZcDataQueueStru(void)/*-bye-*/
{
    return &gAtsToZcDataQueueStru;
}


/*
* 功能描述： 获取ZcToNZc接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetZcToNZcDataQueueStru(void)
{
	return &gZcToNZcDataQueueStru;
}

/*
* 功能描述： 获取NZcToZc接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetNZcToZcDataQueueStru(void)
{
	return &gNZcToZcDataQueueStru;
}

/*
* 功能描述： 获取ZcToNtp接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetZcToNtpDataQueueStru(void)
{
	return &gZcToNtpDataQueueStru;
}

/*
* 功能描述： 获取NtpToZc接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetNtpToZcDataQueueStru(void)
{
	return &gNtpToZcDataQueueStru;
}


/*
* 功能描述： 获取ZC给日志的接口队列
* 参数说明： void
* 返回值  ： NULL: 获取数据失败
*           !NULL: 接口队列
*/
CirQueueStruct* GetZcToLogDataQueueStru(void)
{
	/*return &gZcToLogDataQueueStru;*/
    return NULL;
}
