
/********************************************************                                                                                                           
文 件 名： ChangeInitManager.h
作    者： ZC组
创建时间： 2015.04.18
描述： 切换区域初始化管理  
备注： 无  
********************************************************/ 

#ifndef CHANGE_INIT_MANAGER_H_
#define CHANGE_INIT_MANAGER_H_

#include "../../../Common/CommonTypes.h"
#include "ChangeConfigData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
函数名:   InitChangeLineInitializationData   
功能描述: 初始化本地管理的切换线路初始信息
输入: 无   
输出: 无
返回值: 无     
*************************************************/
void InitChangeLineInitializationData(void);


/*************************************************
函数名:  InitChangeInfo    
功能描述: 初始化切换区域数据
输入: void 
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeInfo(void);

/*************************************************
函数名:   InitChangeLineInfo   
功能描述: 初始化切换线路数据
输入: void  
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeLineInfo(void);

/*************************************************
函数名:   InitZcNZcMaskConfigCommTargetData   
功能描述: 初始化ZC-NZC码位配置信息中码位信息
输入: 无   
输出: 无
返回值: 0: 初始化失败
		>0: 初始化成功      
*************************************************/
UINT8_S InitZcNZcMaskConfigCommTargetData(void);

/*************************************************
函数名:    InitChangeAreaMaskInfo  
功能描述: 初始化切换区域码位数据
输入: void  
输出: 无
返回值: 0: 初始化失败
*			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaMaskInfo(void);

/*************************************************
函数名:   InitChangeAreaOfSwitchMask   
功能描述: 初始化切换区域码位数据(道岔数据)
输入: void  
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfSwitchMask(void);

/*************************************************
函数名:  InitChangeAreaOfSignalMask    
功能描述: 初始化切换区域码位数据(信号机数据)
输入: void  
输出: 无
返回值: 0: 初始化失败
*			 1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfSignalMask(void);

/*************************************************
函数名:   InitChangeAreaOfPsdMask   
功能描述: 初始化切换区域码位数据(屏蔽门数据)
输入: void  
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfPsdMask(void);

/*************************************************
函数名:    InitChangeAreaOfEsbMask  
功能描述: 初始化切换区域码位数据(紧急停车按钮数据)
输入: void  
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfEsbMask(void);

/*************************************************
函数名:   InitChangeAreaOfAcMask   
功能描述: 初始化切换区域码位数据(计轴区段数据)
输入: void  
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfAcMask(void);

/*************************************************
函数名:   InitChangeAreaOfRouteMask   
功能描述: 初始化切换区域码位数据(进路数据)
输入: void  
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfRouteMask(void);

/*************************************************
函数名:   InitChangeAreaOfOverlapMask   
功能描述: 初始化切换区域码位数据(保护区段数据)
输入: void  
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfOverlapMask(void);

/*************************************************
函数名:  InitChangeAreaOfDrMask    
功能描述: 初始化切换区域码位数据(无人折返数据)
输入: void  
输出: 无
返回值: 0: 初始化失败
			1; 初始化成功
*************************************************/
UINT8_S InitChangeAreaOfDrMask(void);

#ifdef __cplusplus
}
#endif

#endif
