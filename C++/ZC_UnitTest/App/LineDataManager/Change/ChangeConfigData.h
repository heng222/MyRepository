
/********************************************************                                                                                                           
文 件 名： ChangeConfigData.h  
作    者： ZC组
创建时间： 2015.04.18
描述： 切换区域配置数据  
备注： 无  
********************************************************/ 

#ifndef CHANGE_CONFIG_DATA_H_
#define CHANGE_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ChangeDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*切换区域数据结构体*/
typedef struct ChangeLineSwitchStruct
{
	UINT16_S SwitchId;                             /*切换线路对应道岔ID*/
	UINT8_S SwitchNeedStatus;                      /*对应道岔需要的状态*/
}  ChangeLineSwitchStruct;

/*切换线路数据结构体*/
typedef struct ChangeLineConfigDataStruct
{
	UINT16_S ChangeLineId;                          /*切换线路ID*/
	UINT16_S HandOverZcId;                          /*本线路对应的移交ZCid*/
	UINT16_S TakeOverZcId;                          /*本线路对应的接管ZCid*/
	UINT8_S ChangeDir;                              /*切换方向*/
	UINT16_S  ChangeLineStartLink;                  /*本切换线路始端Link编号*/
	UINT32_S  ChangeLineStartOffset; 	            /*本切换线路始端Link对应偏移量*/
	UINT16_S  ChangePointLink;                      /*本线路对应的切换点所处link编号*/
	UINT32_S  ChangePointOffset;                    /*本线路对应的切换点所处link偏移量*/
	UINT16_S  ChangeLineEndLink;                    /*本切换线路终端Link编号*/
	UINT32_S  ChangeLineEndOffset;                  /*本切换线路终端Link对应偏移量*/
	UINT16_S  RelevanceRouteId;                     /*本线路对应的进路ID*/
	UINT8_S  SwitchNum;                             /*本切换线路对应的道岔数量*/
	ChangeLineSwitchStruct SwitchStruBuff[CHANGE_LINE_SWITCH_MAX];/*本切换线路对应的道岔数据*/
} ChangeLineConfigDataStruct;

typedef struct ChangeAreapObsStruct
{
	UINT16_S ObsId;                                /*切换区域对应障碍物Id*/
	UINT8_S ObsType;                               /*切换区域对应障碍物类型*/
} ChangeAreapObsStruct;

typedef struct ChangeAreaBitTableStruct
{
	UINT16_S ObsId;                                /*障碍物ID*/
	UINT16_S StateBitIndex;                        /*障碍物状态对应码位*/
	UINT16_S LockBitIndex;                         /*障碍物锁闭信息对应码位*/
    UINT8_S ChageDir;                              /* 切换方向(只计轴区段使用)*/
}ChangeBitTableStruct;

/*切换区域配置数据结构体*/  
typedef struct ChangeAreaConfigStruct
{
	UINT16_S LocalZcId;                                                               /*输出方ZcId*/
	UINT16_S NextZcId;                                                                /*切换区域对应的相邻ZcId*/
	UINT16_S ObsNum;                                                                  /*本区域对应的障碍物个数*/
	ChangeAreapObsStruct ObsStruBuff[CHANGE_AREA_OBS_MAX];                            /*本区域对应的障碍物信息*/
	UINT16_S RouteNum;                                                                /*进路码位数量*/
	ChangeBitTableStruct RouteBitStruBuff[CHANGE_AREA_ROUTE_MAX];                       /*进路码位*/
	UINT16_S OverlapNum;                                                              /*保护区段码位数量*/
	ChangeBitTableStruct OverlapBitStruBuff[CHANGE_AREA_OVERLAP_MAX];                   /*保护区段码位*/
	UINT16_S SignalNum;                                                               /*信号机码位数量*/
	ChangeBitTableStruct SignalBitStruBuff[CHANGE_AREA_SIGNAL_MAX];                     /*信号机码位*/
	UINT16_S SwitchNum;                                                               /*道岔码位数量*/
	ChangeBitTableStruct SwitchBitStruBuff[CHANGE_AREA_SWITCH_MAX];                     /*道岔码位*/
	UINT16_S PsdNum;                                                                  /*屏蔽门码位数量*/
	ChangeBitTableStruct PsdBitStruBuff[CHANGE_AREA_PSD_MAX];                           /*屏蔽门码位*/
	UINT16_S EsbNum;                                                                  /*紧急停车按钮码位数量*/
	ChangeBitTableStruct EsbBitStruBuff[CHANGE_AREA_ESB_MAX];                           /*紧急停车按钮码位*/
	UINT16_S DrButtonNum;                                                             /*无人折返按钮码位数量*/
	ChangeBitTableStruct DrButtonBitStruBuff[CHANGE_AREA_DRBUTTON_MAX];                 /*无人折返按钮码位*/
	UINT16_S DrLampNum;                                                               /*无人折返灯码位数量*/
	ChangeBitTableStruct DrLampBitStruBuff[CHANGE_AREA_DRLAMP_MAX];                     /*无人折返灯码位*/
	UINT16_S AcNum;                                                                   /*计轴区段码位数量*/
	ChangeBitTableStruct AcBitStruBuff[CHANGE_AREA_AC_MAX];                             /*计轴区段码位*/
	UINT16_S LogicSectionNum;                                                         /*逻辑区段码位数量*/
	ChangeBitTableStruct LogicSectionBitStruBuff[CHANGE_AREA_LOGIC_MAX];              /*逻辑区段码位*/	
} ChangeAreaConfigStruct;
	
/*************************************************
函数名:  GetChangeLineSum    
功能描述: 获取切换线路总数
输入: void    
输出: 无
返回值: 0: 获取数据失败
		>0: 切换线路当前总数
*************************************************/
UINT16_S GetChangeLineSum(void);

/*************************************************
函数名:  GetChangeLineId    
功能描述: 获取指定数组下标对应的切换线路ID
输入: const UINT16 bufIndex, 数组下标    
输出: 无
返回值: 0: 获取数据失败
		>0: 切换线路ID      
*************************************************/
UINT16_S GetChangeLineId(const UINT16_S bufIndex);

/*************************************************
函数名:  GetChangeLineConfigBufIndex    
功能描述: 获取指定ID切换线路索引号
输入: const UINT16 changeLineId,切换线路ID
输出: 无
返回值: CHANGE_LINE_SUM_MAX: 获取数据失败
			>=0查找索引成功
*************************************************/
UINT16_S GetChangeLineConfigBufIndex(const UINT16_S changeLineId);

/*************************************************
函数名:   GetChangeLineDir   
功能描述: 获取指定切换线路ID对应的切换方向
输入: const UINT16 changeLineId, 切换线路ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 切换方向      
*************************************************/
UINT8_S GetChangeLineDir(const UINT16_S changeLineId);

/*************************************************
函数名:    GetChangeLineHandOverZcId  
功能描述: 获取指定切换线路ID对应的移交ZCid
输入: const UINT16 changeLineId, 切换线路ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 移交ZCid      
*************************************************/
UINT16_S GetChangeLineHandOverZcId(const UINT16_S changeLineId);

/*************************************************
函数名:   GetChangeLineTakeOverZcId   
功能描述: 获取指定切换线路ID对应的接管ZCid
输入: const UINT16 changeLineId, 切换线路ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 接管ZCid      
*************************************************/
UINT16_S GetChangeLineTakeOverZcId(const UINT16_S changeLineId);

/*************************************************
函数名:   GetChangeLineStartLink   
功能描述: 获取指定切换线路ID对应的起点link
输入: const UINT16 changeLineId, 切换线路ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 起点link     
*************************************************/
UINT16_S GetChangeLineStartLink(const UINT16_S changeLineId);

/*************************************************
函数名:   GetChangeLineStartOffset   
功能描述: 获取指定切换线路ID对应的起点offset
输入: const UINT16 changeLineId, 切换线路ID    
输出: 无
返回值: 0: 获取数据失败
		>0: offset      
*************************************************/
UINT32_S GetChangeLineStartOffset(const UINT16_S changeLineId);

/*************************************************
函数名:   GetChangeLineChangePointLink   
功能描述: 获取指定切换线路ID对应的切换点link
输入: const UINT16 changeLineId, 切换线路ID  
输出: 无
返回值: 0: 获取数据失败
		>0: 切换点link      
*************************************************/
UINT16_S GetChangeLineChangePointLink(const UINT16_S changeLineId);

/*************************************************
函数名:   GetChangeLineChangePointOffset   
功能描述: 获取指定切换线路ID对应的切换点offset
输入: const UINT16 changeLineId, 切换线路ID    
输出: 无
返回值: 0: 获取数据失败
		>0: offset      
*************************************************/
UINT32_S GetChangeLineChangePointOffset(const UINT16_S changeLineId);

/*************************************************
函数名:   GetChangeLineEndLink   
功能描述: 获取指定切换线路ID对应的终点link
输入: const UINT16 changeLineId, 切换线路ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 终点Link      
*************************************************/
UINT16_S GetChangeLineEndLink(const UINT16_S changeLineId);

/*************************************************
函数名:  GetChangeLineEndOffset    
功能描述: 获取指定切换线路ID对应的终点offset
输入: const UINT16 changeLineId, 切换线路ID   
输出: 无
返回值: 0: 获取数据失败
		>0: offset      
*************************************************/
UINT32_S GetChangeLineEndOffset(const UINT16_S changeLineId);

/*************************************************
函数名:    GetChangeLineRelevanceRouteId  
功能描述: 获取指定切换线路ID对应的进路ID
输入: const UINT16 changeLineId, 切换线路ID 
输出: 无
返回值: 0: 获取数据失败
		>0: 进路ID      
*************************************************/
UINT16_S GetChangeLineRelevanceRouteId(const UINT16_S changeLineId);

/*************************************************
函数名:  GetChangeLineSwitchNum    
功能描述: 获取指定切换线路ID对应的道岔数量
输入: const UINT16 changeLineId, 切换线路ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 道岔数量     
*************************************************/
UINT8_S GetChangeLineSwitchNum(const UINT16_S changeLineId);

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
UINT8_S GetChangeLineSwitchStruct(const UINT16_S changeLineId,const UINT8_S switchStruBufSize, ChangeLineSwitchStruct switchStruBuff[]);

/*************************************************
函数名:  GetChangeAreaConfigSum    
功能描述: 获取切换区域总数
输入: void    
输出: 无
返回值: 0: 获取数据失败
		>0: 切换线路当前总数
*************************************************/
UINT16_S GetChangeAreaConfigSum(void);

/*************************************************
函数名: GetChangeAreaOfNextZcId     
功能描述: 获取指定数组下标对应的切换区域对应的ZCID
输入: const UINT16 bufIndex, 数组下标    
输出: 无
返回值: 0: 获取数据失败
		>0: 切换线路ID      
*************************************************/
UINT16_S GetChangeAreaOfNextZcId(const UINT16_S bufIndex);

/*************************************************
函数名:   GetChangeAreaConfigBufIndex   
功能描述: 获取指定ID切换区域索引号
输入: const UINT16 nextZcId,相邻ZCid
        const UINT16_S outputZcId,输出方ZcId
输出: 无
返回值:CHANGE_AREA_SUM_MAX: 获取数据失败
		>=0: 查找索引成功
*************************************************/
UINT16_S GetChangeAreaConfigBufIndex(const UINT16_S outputZcId ,const UINT16_S nextZcId);


/*************************************************
函数名:    GetChangeAreaObsNum  
功能描述: 获取指定ID切区域障碍物数量
输入: const UINT16 nextZcId,相邻ZCid
        const UINT16_S outputZcId,输出方ZcId
输出: 无
返回值:0: 获取数据失败
		>0: 查询成功
*************************************************/
UINT16_S GetChangeAreaObsNum(const UINT16_S outputZcId ,const UINT16_S nextZcId);

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
UINT8_S GetChangeAreapObsStructBuff(const UINT16_S outputZcId ,const UINT16_S nextZcId,const UINT16_S bufSize,ChangeAreapObsStruct obsStruBuff[]);


/*************************************************
函数名:    GetAppointObsInChangeArea  
功能描述: 获取指定ID和类型的障碍物是否属于切换区域
输入: const UINT16 obsId 障碍物ID
    const UINT8_S obsType 障碍物类型
输出: 无
返回值:0: 获取数据失败（不属于切换区域的相邻ZC）
		1: 查询成功（属于切换区域的相邻ZC）
*************************************************/
UINT8_S GetAppointObsInChangeArea(const UINT16_S obsId,const UINT8_S obsType);

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
UINT8_S GetObsBitTableNum(const UINT16_S outputZcId,const UINT16_S nZcId, const UINT8_S obsType, UINT16_S *pObsNum);

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
ChangeBitTableStruct* GetObsBitTableStrInfo(const UINT16_S outputZcId,const UINT16_S nZcId,const UINT8_S obsType);

/*************************************************
函数名:   GetLineDeviceBelongZcId    
功能描述: 获取线路设备所属ZC信息
输入: 无   
输出: 无
返回值: 0: 获取失败
		>0: 所属ZCID      
*************************************************/
UINT16_S GetLineDeviceBelongZcId(const UINT16_S devId,const UINT8_S devType);


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
UINT8_S GetObsBitTableNumOfIndex(const UINT8_S changeAreaIndex, const UINT8_S obsType, UINT16_S *pObsNum);

/*************************************************
函数名:  GetObsBitTableStrInfoOfIndex    
功能描述: 获取指定类型的障碍物是码位信息结构（下标索引）
输入: const UINT8 changeAreaIndex 切换区域下标
        const UINT8_S obsType 障碍物类型
输出: 无
返回值:NULL: 获取数据失败
		!NULL: 查询成功
*************************************************/
ChangeBitTableStruct* GetObsBitTableStrInfoOfIndex(const UINT8_S changeAreaIndex,const UINT8_S obsType);

#ifdef __cplusplus
}
#endif

#endif
