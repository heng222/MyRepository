/************************************************************************
*
* 文件名   ：  IOInterfaceProcess.h
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  输入输出接口处理
* 备  注   ：  无
*
************************************************************************/
#ifndef IO_INTERFACE_PROCESS_H_
#define IO_INTERFACE_PROCESS_H_

#include "../../../Common/CommonTypes.h"
#include "../../../Common/CircQueueStruct.h"


#define UDP_MAX_BUFF_SIZE 5000U

#ifdef __cplusplus
extern "C" {
#endif


	/*
	* 功能描述： 获取平台输入的数据解析到各个通信队列中
	* 参数说明： void
	* 返回值  ： 无
	*/
	void InterfaceInputProcessToLocalQueue(void);

	/*
	* 功能描述： 组织本地管理的各个队列信息，发送至平台进行输出
	* 参数说明： void
	* 返回值  ： 无
	*/
	void InterfaceOutputProcessToPlatform(void);

	/*
    * 功能描述： 将接收队列当中数据放入单个数据队列
    * 参数说明： UINT8_S devType,类型
    *            const UIN8_S dataBuff[],数据数组
    *            UINT32_S datalen,数据长度
    * 返回值  ： void
    */

    void RecvQueueToLocalSingleQueue(UINT8_S devType,const UINT8_S dataBuff[],UINT32_S datalen);

    /*
    * 功能描述： 将单个队列数据放入发送的队列当中
    * 参数说明： CirQueueStruct *pCirQueueStru 队列指针
    * 返回值  ： 0: 失败
    *            1: 成功
    */

    UINT8_S LocalSingleQueueToSendQueue(CirQueueStruct *pCirQueueStru);
	 

	/*
	* 功能描述： 获取ZcToCi接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetZcToCiDataQueueStru(void);

	/*
	* 功能描述： 获取CiToZc接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetCiToZcDataQueueStru(void);

	/*
	* 功能描述： 获取ZcTo车载ATP接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetZcToTrainDataQueueStru(void);

	/*
	* 功能描述： 获取车载ATPToZc接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetTrainToZcDataQueueStru(void);

	/*
	* 功能描述： 获取ZcToAts接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetZcToAtsDataQueueStru(void);

	/*
	* 功能描述： 获取AtsToZc接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	extern CirQueueStruct* GetAtsToZcDataQueueStru(void);/*-bye-*/

	/*
	* 功能描述： 获取ZcToNZc接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetZcToNZcDataQueueStru(void);

	/*
	* 功能描述： 获取NZcToZc接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetNZcToZcDataQueueStru(void);

	/*
	* 功能描述： 获取ZcToNtp接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetZcToNtpDataQueueStru(void);

	/*
	* 功能描述： 获取NtpToZc接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetNtpToZcDataQueueStru(void);
	
	/*
	* 功能描述： 获取ZC给日志的接口队列
	* 参数说明： void
	* 返回值  ： NULL: 获取数据失败
	*           !NULL: 接口队列
	*/
	CirQueueStruct* GetZcToLogDataQueueStru(void);

#ifdef __cplusplus
}
#endif

#endif
