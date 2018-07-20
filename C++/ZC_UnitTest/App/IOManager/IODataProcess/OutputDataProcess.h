/************************************************************************
*
* 文件名   ：  OutputDataProcess.c
* 创建时间 ：  2015.08.14
* 作者     ：  ZC组
* 功能描述 ：  打包ZC发送的数据管理
* 备  注	：  无
*
************************************************************************/

#ifndef OUTPUT_DATA_PROCESS_H_
#define OUTPUT_DATA_PROCESS_H_


#ifdef __cplusplus
extern "C" {
#endif
/*
* 功能描述： 输出数据处理
* 参数说明： 无
* 返回值  ： 无      
*/
void OutputDataProcess(void);

/*
* 功能描述： 组输出给CI的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S CiOutputDataProcess(void);

/*
* 功能描述： 组输出给CI的数据
* 参数说明： const UINT16 ciId,联锁的编号
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S SingleCiOutput(const UINT16_S ciId);

/*
* 功能描述： 填写码位值
* 参数说明： const UINT16 maskId,码位ID
*            const UINT16_S buffSize,数组大小
*            UINT8_S dataBuff[],输出数组
* 返回值  ： 0: 填写失败
*			 1: 填写成功      
*/
UINT8_S SetMaskValue(const UINT16_S maskId,const UINT16_S buffSize,UINT8_S dataBuff[]);

/*
* 功能描述： 处理输入给CI的逻辑区段CT列车占用码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessSectionCtMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 处理输入给CI的逻辑区段UT列车占用码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessSectionUtMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 处理输入给CI的计轴区段ARB码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessAcArbMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 处理输入给CI的计轴区段停稳码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessAcStopMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 处理输入给CI的无人折返灯闪灯码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessDrLampTwinkleMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 处理输入给CI的无人折返灯稳灯码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessDrLampSteadyMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 处理输入给CI的信号机跨压信息码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessSignalCrossMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 处理输入给CI的信号机亮灭信息码位信息
* 参数说明： const UINT8 deviceSum,设备数量
*            const UINT16_S deviceIdBuff[],设备ID数组
* 返回值  ： 0: 码位值为0
*			 1: 码位值为1      
*/
UINT8_S ProcessSignalLightOffMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* 功能描述： 组输出给NZC的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
void NZcOutputDataProcess(void);

/*
* 功能描述： 组输出给单个NZC的数据
* 参数说明： const UINT16 nZcId,ZCID
* 返回值  ： 无     
*/
void NextZcOutput(const UINT16_S nZcId);

/*
* 功能描述： 写输出给单个NZC的码位数据
* 参数说明： UINT8 bitValue,码位值
*            UINT16_S  bitIndex,码位下标
*            UINT8_S baseAddr[],输出数据基地址
* 返回值  ： 无     
*/
void  WriteZcBitValue(UINT8_S bitValue,UINT16_S  bitIndex,UINT8_S baseAddr[]);

/*
* 功能描述： 组输出给单个NZC的数据
* 参数说明： const UINT16 nZcId,ZCID
*			 UINT8_S *pBuff,输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功    
*/
UINT8_S NextZcObsMsgPack(const UINT16_S zcId,UINT8_S *pBuff, UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（进路）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcRouteMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（保护区段）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcOverlapMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（信号机）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcSignalMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（道岔）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcSwitchMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（屏蔽门）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcPsdMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（紧急停车按钮）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcEsbMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（无人折返按钮）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcDrButtonMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（无人折返灯）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcDrLampMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入障碍物（计轴区段）数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输出数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcAcMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组包相邻ZC输入临时限速数据
* 参数说明： const UINT16 zcId,zcId
*            UINT8_S pBuff[],输入数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： 0,处理失败
*            1,处理成功
*/
UINT8_S NextZcTsrMsgPack(const UINT16_S zcId,UINT8_S pBuff[], UINT16_S *dataIndex);

/*
* 功能描述： 组输出给单个NZC的列车数据
* 参数说明： const UINT16 trainId,列车ID
*            UINT8_S pBuff[],缓存数组
* 返回值  ： 数组下标     
*/
UINT8_S NextZcTrainMsgPack(const UINT16_S trainId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组输出给单个NZC的列车移动授权数据
* 参数说明： const UINT16 trainId,列车ID
*            UINT8_S pBuff[],缓存数组
* 返回值  ： 数组下标     
*/
UINT8_S NextZcMaMsgPack(const UINT16_S trainId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* 功能描述： 组输出给单个NZC的列车和移动授权数据
* 参数说明： const UINT16 zcId,ZC的ID(预留)
*            UINT8_S pBuff[],缓存数组
*            UINT16_S *dataIndex,输入输出数组下标
* 返回值  ： RETURN_ERROR,处理失败
*            RETURN_SUCCESS,处理成功       
*/
UINT8_S NextZcTrainAndMaMsgPack(const UINT16_S zcId,UINT8_S pBuff[], UINT16_S *dataIndex);

/*
* 功能描述： 组输出给Ntp的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S NtpOutputDataProcess(void);

/*
* 功能描述： 组帧给Ntp的数据
* 参数说明： const UINT16 commId，ID信息
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S NtpOutputDataPack(const UINT16_S commId);

/*
* 功能描述： 组输出给车载ATP的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S TrainOutputDataProcess(void);

/*
* 功能描述： 正常移动授权输出组织
* 参数说明： const UINT16 trainId,列车的ID
*            const UINT8_S trainOutType,列车输出类型
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S NormalMaOutputProcess(const UINT16_S trainId,const UINT8_S trainOutType);

/*
* 功能描述：紧急制动移动授权输出组织
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S AbnormalMaOutputProcess(const UINT16_S trainId);

/*
* 功能描述：统一的移动授权输出信息组织
* 参数说明： const UINT16 trainId,列车ID
*            const UINT8_S trainOutType,列车输出类型
*            UINT16_S * addIndex,缓存下标
*            UINT8_S dataBuff[],缓存数组
* 返回值  ： 无      
*/
void UnifiedMaOutputInfoProcess(const UINT16_S trainId,const UINT8_S trainOutType,UINT16_S *addIndex,UINT8_S dataBuff[]);

/*
* 功能描述： 组输出给Ats的数据
* 参数说明： 无
* 返回值  ： 0:组数据失败
*			 1:组数据成功      
*/
UINT8_S AtsOutputDataProcess(void);

/*
* 功能描述： CBTC列车占用逻辑区段组帧
* 参数说明： UINT16 *addIndex,数组大小;
*            UINT8_S dataBuff[],输出数组;
* 返回值  ： 0>=:列车数量     
*/
UINT8_S SectionOccFromCbtcTrain(UINT16_S *addIndex,UINT8_S dataBuff[]);

/*
* 功能描述： 非CBTC列车占用逻辑区段组帧
* 参数说明： UINT16 *addIndex,数组大小;
*            UINT8_S dataBuff[],输出数组;
* 返回值  ： 0>=:列车数量     
*/
UINT8_S SectionOccFromUnCbtcTrain(UINT16_S *addIndex,UINT8_S dataBuff[]);

#ifdef __cplusplus
}
#endif

#endif
