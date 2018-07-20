/********************************************************                                                                                                            
 文 件 名： MAStatusData.h  
 作    者： ZC组
 创建时间： 2015-04-18
 描述： 列车状态数据管理  
 备注： 无  
********************************************************/
#ifndef MA_STATUS_DATA_H_
#define MA_STATUS_DATA_H_


#include "MADefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

/*MA中使用到的障碍物信息数据结构*/
typedef struct ObsOfMAStruct
{
	UINT16_S  ObsId;                                      /*障碍物ID*/
	UINT8_S  ObsType;                                     /*障碍物类型*/
	UINT8_S ObsStatus;                                    /*障碍物状态*/
	UINT8_S ObsLockStatus;                                /*障碍物锁闭状态*/
}ObsOfMAStruct;

/*MA中使用到的临时限速信息数据结构*/
typedef struct TsrOfMAStruct
{
	UINT16_S TsrSpeed;                                   /*临时限速值（cm/s）*/
	UINT16_S TsrHeadLink;                                /*临时限速始端Link*/
	UINT32_S TsrHeadOffset;                              /*临时限速始端Offset*/
	UINT16_S TsrTailLink;                                /*临时限速终端Link*/
	UINT32_S TsrTailOffset;                              /*临时限速终点Offset*/
	UINT16_S BelongZcId;                                 /*临时限速所属ZCID*/
}TsrOfMAStruct;


/*列车移动授权信息(MA)状态数据结构体*/
typedef struct MaDataStruct
{
	UINT16_S TrainID;                                    /*列车ID号*/
	UINT8_S MaType;                                      /*MA类型：0x55-紧急制动MA;0xaa-非紧急制动MA;0-无MA信息*/
	UINT16_S MaHeadLink;                                 /*MA起点区段号*/
	UINT32_S MaHeadOffset;                               /*MA起点偏移位置*/
	UINT8_S MaHeadDir;                                   /*MA起点方向*/
	UINT16_S MaTailLink;                                 /*MA终点区段号*/
	UINT32_S MaTailOffset;                               /*MA终点偏移位置*/
	UINT8_S MaTailDir;                                   /*MA终点方向*/
	UINT16_S MaEndObsId;                                 /*MA终点障碍物ID*/
	UINT8_S  MaEndObsType;                               /*MA终点障碍物的类型*/
	UINT8_S  MaEndAttribute;                             /*MA终点属性*/
	UINT8_S ObsNum;                                      /*MA范围内的障碍物数量*/
	ObsOfMAStruct ObsOfMAStru[MA_AREA_OBS_SUM_MAX];      /*障碍物结构体*/
	UINT8_S TsrNum;                                      /*临时限速数量*/
	TsrOfMAStruct TsrOfMAStru[MA_AREA_TSR_SUM_MAX];      /*临时限速结构体*/
}MaDataStruct;

/*相邻ZC列车移动授权信息(MA2)状态数据结构体*/
typedef struct NextZcMaDataStruct
{
	UINT16_S TrainID;                                    /*列车ID号*/
	UINT16_S NextId;                                     /*计算MA2的相邻ZCID*/
	UINT8_S HandOutType;                                 /*相邻ZC输入信息帧类型*/
	UINT8_S MaInfoFlag;                                  /*MA2存在标志：0x55-有MA存在；0xaa-无MA存在*/
	UINT8_S ExceedBoundaryFlag;                          /*MA2是否已越过分界点*/
	UINT8_S MaLength;                                    /*MA2长度*/
	UINT16_S MaHeadLink;                                 /*MA起点区段号*/
	UINT32_S MaHeadOffset;                               /*MA起点偏移位置*/
	UINT8_S MaHeadDir;                                   /*MA起点方向*/
	UINT16_S MaTailLink;                                 /*MA终点区段号*/
	UINT32_S MaTailOffset;                               /*MA终点偏移位置*/
	UINT8_S MaTailDir;                                   /*MA终点方向*/
	UINT8_S  MaEndAttribute;                             /*MA终点属性*/
	UINT16_S OverlapId;                                  /*MA包含的overlapID*/
	UINT8_S ObsNum;                                      /*MA范围内的障碍物数量*/
	ObsOfMAStruct ObsOfMAStru[MA_AREA_OBS_SUM_MAX];      /*障碍物结构体*/
	UINT8_S TsrNum;                                      /*临时限速数量*/
	TsrOfMAStruct TsrOfMAStru[MA_AREA_TSR_SUM_MAX];      /*临时限速结构体*/
}NextZcMaDataStruct;

/*************************************************
  函数名:      GetNextZcMaStatusSum
  功能描述:    获取相邻ZC列车移动授权管理总数
  输入:        无
  输出:        无
  返回值:      0u: 获取数据失败
               >0u: 列车移动授权管理总数
*************************************************/
UINT16_S GetNextZcMaStatusSum(void);

/*************************************************
  函数名:      SetNextZcMaStatusSum
  功能描述:    设置相邻ZC列车移动授权管理总数
  输入:        const UINT8 maCurSum  移动授权目前总数 
  输出:        无
  返回值:      RETURN_ERROR:    设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT16_S SetNextZcMaStatusSum(const UINT8_S maCurSum);

/*************************************************
  函数名:      GetNextZcMaStatusBufIndex
  功能描述:    根据列车ID，获取相邻ZC列车移动授权管理数组下标
  输入:        const UINT16_S trainId  列车ID
  输出:        无
  返回值:      LINE_MAX_TRAIN_ID:      获取数据失败
               (0u,LINE_MAX_TRAIN_ID): 获取数据成功
*************************************************/
UINT8_S GetNextZcMaStatusBufIndex(const UINT16_S trainId);

/*************************************************
  函数名:      GetNextZcHandOutType
  功能描述:    根据列车ID，获取计算该移动授权的相邻ZC输入类型
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE:    获取数据失败
               <RETURN_UINT8_MAX_VALUE:   相邻ZC输入类型
*************************************************/
UINT8_S GetNextZcHandOutType(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcHandOutType
  功能描述:    根据列车ID，设置计算该移动授权的相邻ZC输入类型
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_ERROR: 设置数据失败
               RETURN_SUCCESS: 成功设置相邻ZC输入类型
*************************************************/
UINT8_S SetNextZcHandOutType(const UINT16_S trainId,const UINT8_S handOutType);

/*************************************************
  函数名:      GetNextZcId
  功能描述:    根据列车ID，获取计算该移动授权的相邻ZCID
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT16_MAX_VALUE: 获取数据失败
               <RETURN_UINT16_MAX_VALUE: 相邻ZCID
*************************************************/
UINT16_S GetNextZcId(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcId
  功能描述:    根据列车ID，设置计算该移动授权的相邻ZCID
  输入:        const UINT16_S trainId  列车ID 
               const UINT16_S zcId  相邻ZC的编号
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT16_S SetNextZcId(const UINT16_S trainId,const UINT16_S zcId);

/*************************************************
  函数名:      GetNextZcMaInfoFlag
  功能描述:    根据列车ID，获取相邻ZC列车移动授权存在标志
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               FLAG_SET: 存在MA
               FLAG_UNSET:不存在MA
*************************************************/
UINT8_S GetNextZcMaInfoFlag(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcMaInfoFlag
  功能描述:    根据列车ID，设置相邻ZC列车移动授权存在标志
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S maInfoFlag  标识
  输出:        无
  返回值:      RETURN_ERROR: 设置数据失败
               RETURN_SUCCESS: 设置数据成功
*************************************************/
UINT8_S SetNextZcMaInfoFlag(const UINT16_S trainId,const UINT8_S maInfoFlag);

/*************************************************
  函数名:      GetNextZcMaStatusMaLength
  功能描述:    根据列车ID，获取相邻ZC列车移动授权长度
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <RETURN_UINT8_MAX_VALUE:MA2长度
*************************************************/
UINT8_S GetNextZcMaStatusMaLength(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcMaStatusMaLength
  功能描述:    根据列车ID，获取相邻ZC列车移动授权长度
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S maLength  MA长度
  输出:        无
  返回值:      RETURN_ERROR:  设置数据失败
               RETURN_SUCCESS:设置数据成功
*************************************************/
UINT8_S SetNextZcMaStatusMaLength(const UINT16_S trainId,const UINT8_S maLength);

/*************************************************
  函数名:      GetNextZcMaHeadLink
  功能描述:    获取移动授权起点LINK
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_ERROR:  获取数据失败
               >0u: 起点LINK
*************************************************/
UINT16_S GetNextZcMaHeadLink(const UINT16_S trianId);

/*************************************************
  函数名:      SetNextZcMaHeadLink
  功能描述:    设置移动授权起点LINK
  输入:        const UINT16_S trainId  列车ID 
               const UINT16_S link MA起点link
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetNextZcMaHeadLink(const UINT16_S trianId, const UINT16_S link);

/*************************************************
  函数名:      GetNextZcMaHeadOffset
  功能描述:    获取MA2移动授权起点offset
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT32_MAX_VALUE: 获取数据失败
               <RETURN_UINT32_MAX_VALUE: 起点offset
*************************************************/
UINT32_S GetNextZcMaHeadOffset(const UINT16_S trianId);

/*************************************************
  函数名:      SetNextZcMaHeadOffset
  功能描述:    设置MA2移动授权起点offset
  输入:        const UINT16_S trainId  列车ID 
               const UINT32_S offset  起点偏移量
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaHeadOffset(const UINT16_S trianId, const UINT32_S offset);

/*************************************************
  函数名:      GetNextZcMaHeadDir
  功能描述:    获取相邻ZC移动授权起点方向
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 设置成功
               <RETURN_UINT8_MAX_VALUE: 起点LINK方向
*************************************************/
UINT8_S GetNextZcMaHeadDir(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcMaHeadDir
  功能描述:    设置相邻ZC移动授权起点方向
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S maHeadDir 起点MA方向
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaHeadDir(const UINT16_S trainId,const UINT8_S maHeadDir);

/*************************************************
  函数名:      GetNextZcMaTailLink
  功能描述:    获取MA2移动授权终点LINK
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      DEFAULT_UINT16_VALUE: 获取数据失败
               >0u: 起点LINK
*************************************************/
UINT16_S GetNextZcMaTailLink(const UINT16_S trianId);

/*************************************************
  函数名:      SetNextZcMaTailLink
  功能描述:    设置移动授权终点LINK
  输入:        const UINT16_S trainId  列车ID 
               const UINT16_S link MA终点link
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaTailLink(const UINT16_S trianId, const UINT16_S link);

/*************************************************
  函数名:      GetNextZcMaTailOffset
  功能描述:    获取MA2移动授权终点offset
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT32_MAX_VALUE: 获取数据失败
               <RETURN_UINT32_MAX_VALUE: 起点offset
*************************************************/
UINT32_S GetNextZcMaTailOffset(const UINT16_S trianId);

/*************************************************
  函数名:      SetNextZcMaTailOffset
  功能描述:    设置MA2移动授权终点offset
  输入:        const UINT16_S trainId  列车ID 
               const UINT32_S offset MA终点offset
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaTailOffset(const UINT16_S trianId, const UINT32_S offset);

/*************************************************
  函数名:      GetNextZcMaTailDir
  功能描述:    获取相邻ZC移动授权终点方向
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <RETURN_UINT8_MAX_VALUE: 终点LINK方向
*************************************************/
UINT8_S GetNextZcMaTailDir(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcMaTailDir
  功能描述:    获取相邻ZC移动授权终点方向
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S maTailDir 终点MA方向
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaTailDir(const UINT16_S trainId,const UINT8_S maTailDir);

/*************************************************
  函数名:      GetNextZcMaEndAttribute
  功能描述:    获取相邻ZC移动授权终点属性
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               >0u:                    终点属性
*************************************************/
UINT8_S GetNextZcMaEndAttribute(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcMaEndAttribute
  功能描述:    设置相邻ZC移动授权终点属性
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S endAttribute 终点属性
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaEndAttribute(const UINT16_S trainId, const UINT8_S endAttribute);

/*************************************************
  函数名:      GetNextZcMaObsNum
  功能描述:    获取相邻ZC移动授权对应障碍物数量
  输入:        const UINT16_S trainId  列车ID 
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <RETURN_UINT8_MAX_VALUE: 障碍物数量
*************************************************/
UINT8_S GetNextZcMaObsNum(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcMaObsNum
  功能描述:    设置相邻ZC移动授权对应障碍物数量
  输入:        const UINT16_S trainId  列车ID 
               const UINT8_S obsNum 障碍物数量
  输出:        无
  返回值:      RETURN_SUCCESS: 设置成功
               RETURN_ERROR:   设置失败
*************************************************/
UINT8_S SetNextZcMaObsNum(const UINT16_S trainId, const UINT8_S obsNum);

/*************************************************
  函数名:      GetNextZcObsOfMAStru
  功能描述:    获取相邻ZC移动授权障碍物信息
  输入:        const UINT16_S trainId  列车ID                
  输出:        ObsOfMAStruct obsStru[] 障碍物信息数组 
  返回值:      RETURN_SUCCESS: 获取成功
               RETURN_ERROR:   获取失败
*************************************************/
UINT8_S GetNextZcObsOfMAStru(const UINT16_S trainId, ObsOfMAStruct obsStru[]);

/*************************************************
  函数名:      SetNextZcObsOfMAStru
  功能描述:    设置相邻ZC移动授权障碍物信息
  输入:        const UINT16_S trainId  列车ID                
               const ObsOfMAStruct obsStru[] 障碍物信息数组
               const UINT8_S obsNum 障碍物数量
  输出:        无
  返回值:      RETURN_SUCCESS: 获取成功
               RETURN_ERROR:   获取失败
*************************************************/
UINT8_S SetNextZcObsOfMAStru(const UINT16_S trainId,const ObsOfMAStruct obsStru[],const UINT8_S obsNum);

/*************************************************
  函数名:      GetNextZcMaTsrNum
  功能描述:    获取相邻ZC移动授权对应Trs数量
  输入:        const UINT16_S trainId  列车ID                
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE: 获取数据失败
               <RETURN_UINT8_MAX_VALUE: 临时限速数量
*************************************************/
UINT8_S GetNextZcMaTsrNum(const UINT16_S trainId);

/*************************************************
  函数名:      SetNextZcMaTsrNum
  功能描述:    设置移动授权对应临时限速数量
  输入:        const UINT16_S trainId  列车ID
               const UINT8_S tsrNum    临时限速数量
  输出:        无
  返回值:      RETURN_SUCCESS:  设置成功
               RETURN_ERROR:    设置失败
*************************************************/
UINT8_S SetNextZcMaTsrNum(const UINT16_S trainId, const UINT8_S tsrNum);

/*************************************************
  函数名:      GetNextZcTsrOfMAStru
  功能描述:    获取相邻ZC移动授权Tsr信息
  输入:        const UINT16_S trainId    列车ID
  输出:        TsrOfMAStruct ObsOfMAStru Tsr信息
  返回值:      RETURN_SUCCESS:  获取成功
               RETURN_ERROR:    获取失败
*************************************************/
UINT8_S GetNextZcTsrOfMAStru(const UINT16_S trainId, TsrOfMAStruct tsrOfMAStru[]);

/*************************************************
  函数名:      SetNextZcTsrOfMAStru
  功能描述:    设置相邻ZC移动授权Tsr信息
  输入:        const UINT16_S trainId    列车ID
               const TsrOfMAStruct* tsrOfMAStru Tsr信息
               const UINT8_S tsrNum  TSR数量
  输出:        无
  返回值:      RETURN_SUCCESS:  设置成功
               RETURN_ERROR:    设置失败
*************************************************/
UINT8_S SetNextZcTsrOfMAStru(const UINT16_S trainId, const TsrOfMAStruct* tsrOfMAStru,const UINT8_S tsrNum);

/*************************************************
  函数名:      SetNextZcMaStatusTrainId
  功能描述:    设置相邻ZC输入某下标对应的列车ID
  输入:        const UINT16_S trainId    列车ID
  输出:        无
  返回值:      RETURN_SUCCESS:  设置成功
               RETURN_ERROR:    设置失败
*************************************************/
UINT8_S SetNextZcMaStatusTrainId(const UINT16_S trainId);

/*************************************************
  函数名:      DeleteNextZcSingleTrainMaInfo
  功能描述:    删除相邻ZC输入单个列车移动授权信息
  输入:        const UINT16_S trainId    列车ID
  输出:        无
  返回值:      无
*************************************************/
void DeleteNextZcSingleTrainMaInfo(const UINT16_S trainId);

/*************************************************
  函数名:      ClearNextZcSingleTrainMaInfo
  功能描述:    清除相邻ZC输入单个列车移动授权信息
  输入:        const UINT16_S trainId    列车ID
  输出:        无
  返回值:      无
*************************************************/
void ClearNextZcSingleTrainMaInfo(const UINT16_S trainId);

/*************************************************
  函数名:      GetMaStatusData
  功能描述:    获取移动授权数据
  输入:        无
  输出:        无
  返回值:      移动授权结构体数组的首地址
*************************************************/
MaDataStruct* GetMaStatusData(void);

/*************************************************
  函数名:      GetMaStatusSum
  功能描述:    获取列车移动授权管理总数
  输入:        无
  输出:        无
  返回值:      列车移动授权管理总数
*************************************************/
UINT16_S GetMaStatusSum(void);

/*************************************************
  函数名:      GetMaStatusTrainId
  功能描述:    获取某下标对应的列车ID
  输入:        const UINT16_S bufIndex, 数组下标 
  输出:        无
  返回值:      0u:  获取数据失败
               >0u: 列车ID 
*************************************************/
UINT16_S GetMaStatusTrainId(const UINT16_S bufIndex);

/*************************************************
  函数名:      SetMaStatusTrainId
  功能描述:    设置某下标对应的列车ID
  输入:        const UINT16_S trainId, 列车Id  
  输出:        无
  返回值:      RETURN_ERROR:   设置失败
               RETURN_SUCCESS: 设置成功
*************************************************/
UINT8_S SetMaStatusTrainId(const UINT16_S trainId);

/*************************************************
  函数名:      GetMaStatusBufIndex
  功能描述:    获取指定列车ID索引号
  输入:        const UINT16_S trainId, 列车Id  
  输出:        无
  返回值:      LINE_MAX_TRAIN_ID:      获取失败
               [1u,LINE_MAX_TRAIN_ID): 获取成功
*************************************************/
UINT8_S GetMaStatusBufIndex(const UINT16_S trainId);

/*************************************************
  函数名:      GeSingleMaInfo
  功能描述:    获取指定列车ID的MA信息
  输入:        const UINT16_S trainId, 列车Id  
  输出:        MaDataStruct *singleMaInfo ,MA结构体指针
  返回值:      RETURN_ERROR:  获取失败
               RETURN_SUCESS: 获取成功
*************************************************/
UINT8_S GeSingleMaInfo(const UINT16_S trainId,MaDataStruct *singleMaInfo);

/*************************************************
  函数名:      GetMaType
  功能描述:    获取移动授权类型
  输入:        const UINT16_S trainId, 列车Id  
  输出:        无
  返回值:      RETURN_UINT8_MAX_VALUE:  获取失败
               >0u:                     获取成功
*************************************************/
UINT8_S GetMaType(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaType
  功能描述:    设置移动授权类型
  输入:        const UINT16_S trainId, 列车Id  
               const UINT8_S maType, MA类型
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaType(const UINT16_S trianId,const UINT8_S maType);

/*************************************************
  函数名:      GetMaHeadLink
  功能描述:    获取移动授权起点LINK
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_UINT16_MAX_VALUE:    获取失败
               >0u:  获取成功
*************************************************/
UINT16_S GetMaHeadLink(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaHeadLink
  功能描述:    设置移动授权起点LINK
  输入:        const UINT16_S trainId, 列车Id
               const UINT16_S link, MA起点link
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaHeadLink(const UINT16_S trianId, const UINT16_S link);

/*************************************************
  函数名:      GetMaHeadOffset
  功能描述:    获取移动授权起点offset
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_UINT32_MAX_VALUE:  获取失败
               >0u:                      获取成功
*************************************************/
UINT32_S GetMaHeadOffset(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaHeadOffset
  功能描述:    设置移动授权起点offset
  输入:        const UINT16_S trainId, 列车Id
               const UINT32_S offset,  MA起点offset
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaHeadOffset(const UINT16_S trianId, const UINT32_S offset);

/*************************************************
  函数名:      GetMaHeadDir
  功能描述:    获取移动授权起点方向
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      DEFAULT_UINT8_VALUE:  获取失败
               >0u:                  获取成功
*************************************************/
UINT8_S GetMaHeadDir(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaHeadDir
  功能描述:    设置移动授权起点方向
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S dir,      MA起点方向
  输出:        无
  返回值:      RETURN_ERROR:       设置失败
               RETURN_SUCCESS:     设置成功
*************************************************/
UINT8_S SetMaHeadDir(const UINT16_S trianId, const UINT8_S dir);

/*************************************************
  函数名:      GetMaTailLink
  功能描述:    获取移动授权终点LINK
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      0:    获取失败
               >0u:  获取成功
*************************************************/
UINT16_S GetMaTailLink(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaTailLink
  功能描述:    设置移动授权终点LINK
  输入:        const UINT16_S trainId, 列车Id
               const UINT16_S link, MA终点link
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaTailLink(const UINT16_S trianId, const UINT16_S link);

/*************************************************
  函数名:      GetMaTailOffset
  功能描述:    获取移动授权终点offset
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_UINT32_MAX_VALUE:  获取失败
               [0u,RETURN_UINT32_MAX_VALUE): 获取成功
*************************************************/
UINT32_S GetMaTailOffset(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaTailOffset
  功能描述:    设置移动授权终点offset
  输入:        const UINT16_S trainId, 列车Id
               const UINT32_S offset,  MA终点offset
  输出:        无
  返回值:      RETURN_ERROR:    设置失败
               RETURN_SUCCESS:  设置成功
*************************************************/
UINT8_S SetMaTailOffset(const UINT16_S trianId, const UINT32_S offset);

/*************************************************
  函数名:      GetMaTailDir
  功能描述:    获取移动授权终点方向
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:                  获取成功
*************************************************/
UINT8_S GetMaTailDir(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaTailDir
  功能描述:    设置移动授权终点方向
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S dir,      MA终点方向
  输出:        无
  返回值:      RETURN_ERROR:       设置失败
               RETURN_SUCCESS:     设置成功
*************************************************/
UINT8_S SetMaTailDir(const UINT16_S trianId, const UINT8_S dir);

/*************************************************
  函数名:      GetMaEndObsId
  功能描述:    获取移动授权终点障碍物Id
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:                  获取成功
*************************************************/
UINT16_S GetMaEndObsId(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaEndObsId
  功能描述:    设置移动授权终点障碍物Id
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S endObstacleId, 终点障碍物Id
  输出:        无
  返回值:      RETURN_ERROR:         设置失败
               RETURN_SUCCESS:       获取成功
*************************************************/
UINT8_S SetMaEndObsId(const UINT16_S trianId, const UINT8_S endObstacleId);

/*************************************************
  函数名:      GetMaEndObsType
  功能描述:    获取移动授权终点障碍物类型
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:           获取成功
*************************************************/
UINT8_S GetMaEndObsType(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaEndObsType
  功能描述:    设置移动授权终点障碍物类型
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S endObstacleType, 终点障碍物类型
  输出:        无
  返回值:      RETURN_ERROR:         设置失败
               RETURN_SUCCESS:       获取成功
*************************************************/
UINT8_S SetMaEndObsType(const UINT16_S trianId, const UINT8_S endObstacleType);

/*************************************************
  函数名:      GetMaEndAttribute
  功能描述:    获取移动授权终点属性
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:           获取成功
*************************************************/
UINT8_S GetMaEndAttribute(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaEndAttribute
  功能描述:    设置移动授权终点属性
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S endAttribute, 终点属性
  输出:        无
  返回值:      RETURN_ERROR:         设置失败
               RETURN_SUCCESS:       获取成功
*************************************************/
UINT8_S SetMaEndAttribute(const UINT16_S trianId, const UINT8_S endAttribute);

/*************************************************
  函数名:      GetMaObsNum
  功能描述:    获取移动授权对应障碍物数量
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:  获取失败
               >0u:           获取成功
*************************************************/
UINT8_S GetMaObsNum(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaObsNum
  功能描述:    设置移动授权对应障碍物数量
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S obsNum, 障碍物数量
  输出:        无
  返回值:      RETURN_ERROR:         设置失败
               RETURN_SUCCESS:       获取成功
*************************************************/
UINT8_S SetMaObsNum(const UINT16_S trianId, const UINT8_S obsNum);

/*************************************************
  函数名:      GetObsOfMAStru
  功能描述:    获取移动授权障碍物信息
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S bufSize,输出障碍物结构数组大小(预留)
  输出:        ObsOfMAStruct obsOfMaStrBuff[],输出障碍物结构数组
  返回值:      RETURN_ERROR:     获取失败
               RETURN_SUCCESS:   获取成功
*************************************************/
UINT8_S GetObsOfMAStru(const UINT16_S trianId,const UINT8_S bufSize,ObsOfMAStruct obsOfMaStrBuff[]);

/*************************************************
  函数名:      SetObsOfMAStru
  功能描述:    设置移动授权障碍物信息
  输入:        const UINT16_S trainId, 列车Id
               const ObsOfMAStruct obsOfMABuff[],障碍物信息数组
               const UINT8_S obsNum,障碍物数量
  输出:        无
  返回值:      RETURN_ERROR:     设置失败
               RETURN_SUCCESS:   设置成功
*************************************************/
UINT8_S SetObsOfMAStru(const UINT16_S trianId, const ObsOfMAStruct obsOfMABuff[],const UINT8_S obsNum);

/*************************************************
  函数名:      GetMaTsrNum
  功能描述:    获取移动授权对应Tsr数量
  输入:        const UINT16_S trainId, 列车Id
  输出:        无
  返回值:      RETURN_ERROR:     获取失败
               >0u:   Tsr数量
*************************************************/
UINT8_S GetMaTsrNum(const UINT16_S trianId);

/*************************************************
  函数名:      SetMaTsrNum
  功能描述:    设置移动授权对应临时限速数量
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S tsrNum, 临时限速数量
  输出:        无
  返回值:      RETURN_ERROR:     设置失败
               RETURN_SUCCESS:   设置成功
*************************************************/
UINT8_S SetMaTsrNum(const UINT16_S trianId, const UINT8_S tsrNum);

/*************************************************
  函数名:      GetTsrOfMAStru
  功能描述:    获取移动授权Tsr信息
  输入:        const UINT16_S trainId, 列车Id
               const UINT8_S bufSize,输出障碍物结构数组大小(预留)
  输出:        TsrOfMAStruct tsrOfMaStrBuff[],输出临时限速结构数组
  返回值:      RETURN_ERROR:     获取失败
               RETURN_SUCCESS:   获取成功
*************************************************/
UINT8_S GetTsrOfMAStru(const UINT16_S trianId,const UINT8_S bufSize,TsrOfMAStruct tsrOfMaStrBuff[]);

/*************************************************
  函数名:      SetTsrOfMAStru
  功能描述:    设置移动授权Tsr信息
  输入:        const UINT16_S trainId, 列车Id
               const TsrOfMAStruct tsrOfMAStru[],Tsr信息
               const UINT8_S tsrNum,Tsr数量
  输出:        无
  返回值:      RETURN_ERROR:     设置失败
               RETURN_SUCCESS:   设置成功
*************************************************/
UINT8_S SetTsrOfMAStru(const UINT16_S trianId, const TsrOfMAStruct tsrOfMAStru[],const UINT8_S tsrNum);

/*
* 功能描述： 根据列车ID，获取相邻ZC列车移动授权越过分界点标志
* 参数说明： const UINT16 trainId    
* 返回值  ： RETURN_ERROR: 获取数据失败
*			 FLAG_SET: 越过分界点
*	         FLAG_UNSET:未越过分界点
*/
UINT8_S GetNextZcMaExceedBoundaryFlag(const UINT16_S trainId);

/*************************************************
  函数名:      DeleteSingleTrainMaInfo
  功能描述:    删除单个列车移动授权信息
  输入:        const UINT16_S trainId, 列车Id             
  输出:        无
  返回值:      无
*************************************************/
void DeleteSingleTrainMaInfo(const UINT16_S trainId);

/*************************************************
  函数名:      ClearSingleTrainMaInfo
  功能描述:    清除单个列车移动授权信息
  输入:        const UINT16_S trainId, 列车Id             
  输出:        无
  返回值:      无
*************************************************/
void ClearSingleTrainMaInfo(const UINT16_S trainId);

#ifdef __cplusplus
}
#endif

#endif
