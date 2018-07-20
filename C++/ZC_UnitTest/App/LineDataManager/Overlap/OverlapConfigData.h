/********************************************************                                                                                                           
文 件 名： OverlapConfigData.h  
作    者： ZC组
创建时间： 2015.04.18
描述： 保护区段配置数据  
备注： 无  
********************************************************/ 

#ifndef OVERLAP_CONFIG_DATA_H_
#define OVERLAP_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "OverlapDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


/*保护区段数据结构体*/
typedef struct OverlapConfigDataStruct
{
	UINT16_S OverlapId;                     /*保护区段ID*/
	UINT8_S BelongCiId;                     /*所属联锁ID*/
	UINT8_S BelongZcId;                     /*所属ZCID*/
	UINT8_S ChangeAttribute;                /*共管区域属性(标志是否属于某个共管区域)*/
	UINT8_S SwitchAttribute;                /*保护区段道岔属性(标志是否具有道岔)*/
	UINT8_S ContainAcNum;                   /*保护区段包括的计轴区段数量*/
	UINT16_S ContainAcBuff[OVERLAP_OF_AC_SUM_MAX];  /*保护区段包括的计轴区段数组*/
} OverlapConfigDataStruct;

/*************************************************
函数名:   GetOverlapSum   
功能描述: 获取保护区段管理总数
输入: void    
输出: 无
返回值: 0: 获取数据失败
		>0: 保护区段当前总数
*************************************************/
UINT16_S GetOverlapSum(void);

/*************************************************
函数名:   GetOverlapId   
功能描述: 获取指定数组下标对应的保护区段ID
输入: const UINT16 bufIndex, 数组下标  
输出: 无
返回值: 0: 获取数据失败
		>0: 保护区段ID      
*************************************************/
UINT16_S GetOverlapId(const UINT16_S bufIndex);

/*************************************************
函数名:   GetOverlapConfigBufIndex   
功能描述: 获取指定ID保护区段索引号
输入: const UINT16 overlapId,保护区段ID
输出: 无
返回值:  OVERLAP_SUM_MAX;获取数据失败
			>0;查找索引成功
*************************************************/
UINT16_S GetOverlapConfigBufIndex(const UINT16_S overlapId);

/*************************************************
函数名:   GetOverlapBelongCiId   
功能描述: 获取指定ID站台保护区段所属联锁ID
输入: const UINT16 overlapId,保护区段ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 所属联锁ID      
*************************************************/
UINT8_S GetOverlapBelongCiId(const UINT16_S overlapId);

/*************************************************
函数名:   GetOverlapBelongZcId   
功能描述: 获取指定ID保护区段所属ZC的ID
输入: const UINT16 overlapId, 保护区段ID    
输出: 无
返回值: 0: 获取数据失败
		>0: 所属ZcID      
*************************************************/
UINT8_S GetOverlapBelongZcId(const UINT16_S overlapId);

/*************************************************
函数名:   GetOverlapChangeAttribute   
功能描述: 获取指定ID保护区段共管区域属性
输入: const UINT16 overlapId, 保护区段ID   
输出: 无
返回值: 0: 获取数据失败
		>0: 获取成功      
*************************************************/
UINT16_S GetOverlapChangeAttribute(const UINT16_S overlapId);

/*************************************************
函数名:    GetOverlapSwitchAttribute  
功能描述: 获取指定ID保护区段道岔属性
输入: const UINT16 overlapId, 保护区段ID   
输出: 无
返回值: 0: 获取数据失败
		>0: 获取成功      
*************************************************/
UINT16_S GetOverlapSwitchAttribute(const UINT16_S overlapId);

/*************************************************
函数名:  GetOverlapContainAcNum    
功能描述: 获取指定ID保护区段包含计轴区段数量
输入: const UINT16 overlapId, 保护区段ID     
输出: 无
返回值: 0: 获取数据失败
		>0: 获取数量      
*************************************************/
UINT8_S GetOverlapContainAcNum(const UINT16_S overlapId);

/*************************************************
函数名:   GetOverlapContainAcBuff   
功能描述: 获取指定ID保护区段包含计轴区段数组
输入: const UINT16 overlapId, 保护区段ID    
        const UINT8_S bufSzie, 输出数组大小
        UINT16_S containAcIdBuff[]，输出数组
输出: UINT16_S containAcIdBuff[] 包含的计轴区段数量
返回值: 0: 获取数据失败
		>0: 获取计轴区段数组      
*************************************************/
UINT8_S GetOverlapContainAcBuff(const UINT16_S overlapId,const UINT8_S bufSzie,UINT16_S containAcIdBuff[]);

#ifdef __cplusplus
}
#endif

#endif
