/************************************************************************
*
* 文件名   ：  InputDataProcess.h
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  解析组ZC收到的数据管理
* 备  注	：  无
*
************************************************************************/

#ifndef INPUT_DATA_PROCESS_H_
#define INPUT_DATA_PROCESS_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* 功能描述： 输入数据处理
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void InputDataProcess(void);

	/*
	* 功能描述： 解析CI输入数据
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void CiToZcInputDataProcess(void);

	/*
	* 功能描述： 解析CI输入的单帧数据
	* 参数说明： const UINT8 ciInValueBuff[],输入数据
	*            const UINT16_S dataLength,输入长度
	*            const UINT16_S maskSum,码位总数
	*            UINT8_S maskValueBuff[],输出码位
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseCiInMaskDataToMaskBuf(const UINT8_S ciInValueBuff[],const UINT16_S dataLength,const UINT16_S maskSum,UINT8_S maskValueBuff[]);

	/*
	* 功能描述： 解析CI输入的码位数据到各设备数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT8_S maskValueBuff[],输入码位
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToDeviceData(const UINT16_S commTargetId,const UINT8_S maskValueBuff[]);

	/*
	* 功能描述： 解析CI输入的码位数据到道岔设备位置数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskMainValue,道岔定位码位值
	*            const UINT8_S maskSideValue,道岔反位码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToSwitchPostData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskMainValue,const UINT8_S maskSideValue);

	/*
	* 功能描述： 解析CI输入的码位数据到道岔设备锁闭数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskValue,道岔锁闭码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToSwitchLockData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析CI输入的码位数据到信号机设备状态数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*             const UINT8_S maskValue,信号机状态码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToSignalStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析CI输入的码位数据到Psd设备状态数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskValue,屏蔽门状态码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToPsdStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析CI输入的码位数据到Esb设备状态数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskValue,紧急停车按钮状态码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToEsbStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析CI输入的码位数据到计轴区段设备方向数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskUpDirValue,计轴区段上行码位值
	*            const UINT8_S maskDownDirValue,计轴区段下行码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToACDirData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskUpDirValue,const UINT8_S maskDownDirValue);

	/*
	* 功能描述： 解析CI输入的码位数据到计轴区段占用数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskValue,计轴区段占用码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToAcOccStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析CI输入的码位数据到计轴区段锁闭数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskValue,计轴区段锁闭状态码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToAcLockStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析CI输入的码位数据到进路状态数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskValue,进路状态码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToRouteStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析CI输入的码位数据到保护区段状态数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskValue,保护区段状态码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToOverlapStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析CI输入的码位数据到无人折返按钮状态数据中
	* 参数说明： const UINT16 commTargetId,通信CIid
	*            const UINT16_S maskId,码位ID
	*            const UINT8_S maskValue,无人折返按钮状态码位值
	* 返回值  ： 0: 数据解析失败
	*			 1: 数据解析成功      
	*/
	UINT8_S ParseMaskValueToDRButtonStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* 功能描述： 解析相邻ZC输入数据
	* 参数说明： 无
	* 返回值  ： 无      
	*/
	void NextZcInputDataProcess(void);

	/*
	* 功能描述： 解析相邻ZC输入单帧数据
	* 参数说明： const UINT16 zcId,ZC的编号
	*            const UINT8_S pBuff[],指向数据缓冲区的指针
	* 返回值  ： 0: 失败
	*            1: 成功
	*/
	UINT8_S ParseNextZcInput(const UINT16_S zcId,const UINT8_S pBuff[]);

	/*
	* 功能描述： 解析相邻ZC输入障碍物数据
	* 参数说明： const UINT16_S zcId,ZC的编号
	*            const UINT8_S *pBuff,指向数据缓冲区的指针
	*            UINT16_S *dataIndex,
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcObsMsgParse(const UINT16_S zcId,const UINT8_S *pBuff,UINT16_S *dataIndex);

	/*
	* 功能描述： 读取相邻ZC输入障碍物码位数据
	* 参数说明： const UINT16_S bitIndex, 码位值
	*            const UINT16_S baseBufIndex,缓存基础下标
	*            const UINT8_S baseAddr[]，缓存数组
	* 返回值  ： 码位值
	*/
	UINT8_S GetZcBitValue(const UINT16_S bitIndex, const UINT16_S baseBufIndex,const UINT8_S baseAddr[]);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（进路）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcRouteMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（保护区段）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcOverLapMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（信号机）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcSignalMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（道岔）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcSwitchMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（屏蔽门）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcPsdMsgParse(const UINT16_S zcId,const UINT8_S pBuff[], UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（紧急停车按钮）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcEsbMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（无人折返按钮）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcDrButtonMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（无人折返灯）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcDrLampMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入障碍物（计轴区段）数据
	* 参数说明： const UINT16 zcId,zcId
	*            UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcAcMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入临时限速数据
	* 参数说明： const UINT16_S zcId,zcId
	*            const UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcTsrMsgParse(const UINT16_S zcId,const UINT8_S pBuff[], UINT16_S *dataIndex);


	/*
	* 功能描述： 解析相邻ZC输入单帧数据中列车信息
	* 参数说明： const UINT16_S trainId,列车的ID
	*            const UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcTrainMsgParse(const UINT16_S trainId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入单帧数据中列车移动授权信息
	* 参数说明： const UINT16_S zcId,相邻ZC的编号
    *            const UINT16_S trainId,列车的ID
	*            const UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcMaMsgParse(const UINT16_S zcId,const UINT16_S trainId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 解析相邻ZC输入单帧数据中列车和移动授权信息
	* 参数说明： const UINT16_S zcId,ZC编号
	*            const UINT8_S pBuff[],输入数组
	*            UINT16_S *dataIndex,输入输出数组下标
	* 返回值  ： 0,处理失败
	*            1,处理成功
	*/
	UINT8_S NextZcTrainAndMaMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* 功能描述： 处理Ntp输入ZC的数据
	* 参数说明： 无
	* 返回值  ： 无    
	*/
	void NtpToZcInputDataProcess(void);

	/*
	* 功能描述： 解析车载ATP输入的单帧数据
	* 参数说明： 无
	* 返回值  ： 无     
	*/
	void TrainToZcInputDataProcess(void);

    /*
    * 功能描述： 更新列车输入数据
    * 参数说明： const UINT16_S trainId,列车ID            
    *            const UINT16_S dataLen,数据长度(预留)
    *            const UINT8_S *pDataBuff,数据缓存
    * 返回值  ： 0: 失败
    *　　　　　　1; 成功
    */
	UINT8_S UpdateTrainInputData(const UINT16_S trainId,const UINT16_S dataLen,const UINT8_S pDataBuff[]);

#ifdef __cplusplus
}
#endif

#endif
