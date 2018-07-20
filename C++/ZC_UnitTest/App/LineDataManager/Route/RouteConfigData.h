/************************************************************************
*
* 文件名   ：  RouteConfigData.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  进路配置数据管理
* 备  注   ：  无
*
************************************************************************/
#ifndef ROUTE_CONFIG_DATA_H_
#define ROUTE_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "RouteDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	typedef struct RouteObsStruct
	{
		UINT16_S ObsId;                                /*进路内障碍物Id*/
		UINT8_S ObsType;                               /*进路内障碍物类型*/
	} RouteObsStruct;

	/*进路数据结构体*/
	typedef struct RouteConfigDataStruct
	{
		UINT16_S RouteId;                                      /*进路ID*/
		UINT8_S BelongCiId;                                    /*所属联锁ID*/
		UINT8_S BelongZcId;                                    /*所属ZCID*/
		UINT8_S ChangeAttribute;                               /*共管区域属性(标志是否属于某个共管区域)*/
		UINT8_S RouteType;                                     /*进路类型*/
		UINT8_S RouteAreaType;                                 /*进路区域类型*/
		UINT8_S RouteSingalId;                                 /*进路对应的信号机Id*/  
		UINT8_S OverlapNum;                                    /*进路包含的保护区段数量*/
		UINT16_S OverlapIdBuff[ROUTE_OF_OVERLAP_SUM_MAX];      /*进路包含的保护区段数组*/
		UINT8_S  AcNum;                                        /*进路范围内计轴区段数量*/
		UINT16_S AcIdBuff[ROUTE_OF_AC_SUM_MAX];                /*进路范围内计轴区段Id数组*/
		UINT8_S  ObsNum;                                       /*进路范围内障碍物数量*/
		RouteObsStruct RouteObsStruBuff[ROUTE_OF_OBS_SUM_MAX];      /*进路范围的障碍物结构体*/
	} RouteConfigDataStruct;

	/*
	* 功能描述： 获取进路管理总数
	* 参数说明： void    
	* 返回值  ： 0: 获取数据失败
	*			>0: 进路当前总数
	*/
	UINT16_S GetRouteSum(void);

	/*
	* 功能描述： 获取指定数组下标对应的进路ID
	* 参数说明： const UINT16 bufIndex, 数组下标    
	* 返回值  ： 0: 获取数据失败
	*			>0: 进路ID      
	*/
	UINT16_S GetRouteId(const UINT16_S bufIndex);

	/*
	* 功能描述： 获取指定ID进路索引号
	* 参数说明： const UINT16 routeId,进路ID
	* 返回值  ：  ROUTE_SUM_MAX;获取数据失败
	*			  >=0;查找索引成功
	*/
	UINT16_S GetRouteConfigBufIndex(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定ID站台进路所属联锁ID
	* 参数说明： const UINT16 routeId,进路ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属联锁ID      
	*/
	UINT8_S GetRouteBelongCiId(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定ID进路所属ZC的ID
	* 参数说明： const UINT16 routeId, 进路ID    
	* 返回值  ： 0: 获取数据失败
	*			>0: 所属ZcID      
	*/
	UINT8_S GetRouteBelongZcId(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定ID进路共管区域属性
	* 参数说明： const UINT16 routeId, 进路ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT16_S GetRouteChangeAttribute(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定ID进路类型
	* 参数说明： const UINT16 routeId, 进路ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetRouteType(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定ID进路区域类型
	* 参数说明： const UINT16 routeId, 进路ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetRouteAreaType(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定进路Id的防护信号机Id
	* 参数说明： const UINT16 routeId, 进路ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT16_S GetRouteOfSingalId(const UINT16_S routeId);
	
	/*
	* 功能描述： 获取指定ID进路内保护区段数量
	* 参数说明： const UINT16 routeId, 进路ID     
	* 返回值  ： DEFAULT_UINT8_VALUE: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetRouteOfOverlapNum(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定ID进路内保护区段Idbuff
	* 参数说明： const UINT16 routeId, 进路ID   
	*			 UINT8_S bufSize,输出数组大小，
	*            UINT16_S overlapIdBuff[],输出数组
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetRoutOfOverlapIdBuff(const UINT16_S routeId,UINT8_S bufSize,UINT16_S overlapIdBuff[]);

	/*
	* 功能描述： 获取指定ID进路内计轴区段数量
	* 参数说明： const UINT16 routeId, 进路ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetRouteOfAcNum(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定id进路内指定下标的计轴区段Id
	* 参数说明： const UINT16 routeId, 进路ID   
	*			 UINT8_S index,查询下标
	*            UINT16_S *outAcId,输出计轴区段ID
    * 返回值  ： RETURN_ERROR: 获取数据失败
    *			 RETURN_SUCCESS: 获取成功      
	*/
	UINT8_S GetRoutOfAcIdFromIndex(const UINT16_S routeId,UINT8_S index,UINT16_S *outAcId);

	/*
	* 功能描述： 获取指定ID进路内计轴区段buff
	* 参数说明： const UINT16 routeId, 进路ID   
	*			 UINT8_S bufSize,输出数组大小，
	*            UINT16_S acIdBuff[],输出数组
    * 返回值  ： RETURN_ERROR: 获取数据失败
    *			 RETURN_SUCCESS: 获取成功        
	*/
	UINT8_S GetRoutOfAcIdBuff(const UINT16_S routeId,UINT8_S bufSize,UINT16_S acIdBuff[]);

	/*
	* 功能描述： 获取指定ID进路内障碍物数量
	* 参数说明： const UINT16 routeId, 进路ID     
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT16_S GetRouteOfObsNum(const UINT16_S routeId);

	/*
	* 功能描述： 获取指定ID进路内障碍物信息
	* 参数说明： const UINT16 routeId, 进路ID   
	*            const UINT8_S bufSize,数组大小
	*            RoutepObsStru uct routepObsStru uBuff[],输出数组
	* 返回值  ： 0: 获取数据失败
	*			>0: 获取成功      
	*/
	UINT8_S GetRoutepObsStruBuff(const UINT16_S routeId,const UINT8_S bufSize,RouteObsStruct routeObsStruBuff[]);

	/*
	* 功能描述： 获取指定进路最后一个计轴区段
	* 参数说明： const UINT16 routeId, 进路ID   
	*            UINT16_S *acId, 计轴区段ID（输出）
	* 返回值  ： 0: 获取失败
	*			 1: 获取成功
	*/
	UINT8_S GetRouteLastAcId(const UINT16_S routeId,UINT16_S *acId);

#ifdef __cplusplus
}
#endif

#endif
