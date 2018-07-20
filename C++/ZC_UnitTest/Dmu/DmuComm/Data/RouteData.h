/*************************************************
  文件名   ：RouteData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： RouteData数据管理
			DmuCommonData组件的RouteData功能可分解如下：
			1）	给RouteDataStru结构体指针分配空间
			2）	获取RouteData数据
			3）	获取RouteData信息
			4）	获取指定IDRouteDataStru的结构体下标
			5）	获取指定IDRouteDataStru的结构体指针
			6）	获取指定IDRouteDataStru的进路名称
			7）	获取指定IDRouteDataStru的进路性质
			8）	获取指定IDRouteDataStru的起始信号机编号
			9）	获取指定IDRouteDataStru的终止信号机编号
			10）	获取指定IDRouteDataStru的包含计轴区段数目
			11）	获取指定IDRouteDataStru的计轴区段编号
			12）	获取指定IDRouteDataStru的保护区段数目
			13）	获取指定IDRouteDataStru的保护区段编号
			14）	获取指定IDRouteDataStru的点式接近区段数目
			15）	获取指定IDRouteDataStru的点式接近区段编号
			16）	 获取指定IDRouteDataStru的CBTC接近区段数目
			17）	获取指定IDRouteDataStru的CBTC接近区段编号
			18）	获取指定IDRouteDataStru的点式触发区段数量
			19）	获取指定IDRouteDataStru的点式触发区段ID
			20）	获取指定IDRouteDataStru的CBTC触发区段数量
			21）	获取指定IDRouteDataStru的CBTC触发区段ID
			22）	获取指定IDRouteDataStru的所属CI区域编号
			23）	获取线路进路最大ID
			24）	获取进路对应保护区段信息
			25）	获取进路对应计轴区段信息
			26）	获取线路进路所属ZCID

  备注    ：无。
 
*************************************************/
#ifndef ROUTE_DATA_H_
#define ROUTE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ROUTE_NAME_BYTE_LEN                  24                          /*进路名称字节长度*/
#define ROUTE_SEC_MAX_NUM                      ( 9 + 11)                              /*计轴区段数目*/
#define ROUTE_PROTECT_SEC_MAX_NUM             5                             /*保护区段数目*/
#define ROTRE_ACCESS_SEC_MAX_NUM              (4  + 1)                           /*接近区段最大数目*/
#define ROUTE_TRG_SEC_MAX_NUM                  (4 +1 )                        /*触发区段最大数目*/
#define ROUTE_LINE_BYTE_NUM                  (106+30)                         /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*Route表数据结构体*/
typedef struct BnfRouteStruct
{
    UINT16_S  routeId;                                                    /*索引编号*/
    UINT8_S  routeName[ROUTE_NAME_BYTE_LEN];                                /*进路名称*/
    UINT16_S  routeType;                                                    /*进路性质*/
    UINT16_S  startSignalId;                                                /*起始信号机编号*/
    UINT16_S  endSignalId;                                                /*终止信号机编号*/
    UINT16_S  includeAxleSecNum;                                            /*包含计轴区段数目*/
    UINT16_S  AxleSec[ROUTE_SEC_MAX_NUM];                                    /*计轴区段编号*/
    UINT16_S  protectSecNum;                                                /*保护区段数目*/
    UINT16_S  protectSecId[ROUTE_PROTECT_SEC_MAX_NUM];                    /*保护区段编号*/
    UINT16_S  blogAccessSegNum;                                            /*点式接近区段数目*/    
    UINT16_S  blogAccessSegId[ROTRE_ACCESS_SEC_MAX_NUM];                    /*点式接近区段编号*/
    UINT16_S  cbtcAccessSegNum;                                            /*CBTC接近区段数目*/    
    UINT16_S  cbtcAccessSegId[ROTRE_ACCESS_SEC_MAX_NUM];                    /*CBTC接近区段编号*/
    UINT16_S  blocTrgAreaNum;                                                /*点式触发区段数量*/
    UINT16_S  blocTrgAreaId[ROUTE_TRG_SEC_MAX_NUM];                        /*点式触发区段ID*/
    UINT16_S  cbtcTrgAreaNum;                                                /*CBTC触发区段数量*/
    UINT16_S  cbtcTrgAreaId[ROUTE_TRG_SEC_MAX_NUM];                        /*CBTC触发区段ID*/    
    UINT16_S  manageCI;                                                    /*所属CI区域编号*/

    /*动态计算字段*/
    UINT16_S  manageZCId;                                                    /*所属ZC区域ID*/
}BnfRouteStruct;

/*
* 功能描述： 给RouteDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocRouteDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取RouteData数据
* 参数说明：
* 返回值  ： 
            BnfRouteStruct*
*/
BnfRouteStruct *GetRouteData(void);

/*
* 功能描述： 获取RouteData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfRouteStruct*
*/
BnfRouteStruct *GetRouteDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDRouteDataStru的结构体下标
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetRouteDataStruIndex(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的结构体指针
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfRouteStruct* GetIndexIdRouteDataStru(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的进路名称
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 进路名称
*/ 
UINT8_S* GetRouteDataStrurouteName(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的进路性质
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 进路性质
*/ 
UINT16_S GetRouteDataStrurouteType(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的起始信号机编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起始信号机编号
*/ 
UINT16_S GetRouteDataStrustartSignalId(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的终止信号机编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终止信号机编号
*/ 
UINT16_S GetRouteDataStruendSignalId(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的包含计轴区段数目
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含计轴区段数目
*/ 
UINT16_S GetRouteDataStruincludeAxleSecNum(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的计轴区段编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 计轴区段编号
*/ 
UINT16_S* GetRouteDataStruAxleSec(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的保护区段数目
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 保护区段数目
*/ 
UINT16_S GetRouteDataStruprotectSecNum(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的保护区段编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 保护区段编号
*/ 
UINT16_S* GetRouteDataStruprotectSecId(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的点式接近区段数目
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 点式接近区段数目
*/ 
UINT16_S GetRouteDataStrublogAccessSegNum(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的点式接近区段编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 点式接近区段编号
*/ 
UINT16_S* GetRouteDataStrublogAccessSegId(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的CBTC接近区段数目
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: CBTC接近区段数目
*/ 
UINT16_S GetRouteDataStrucbtcAccessSegNum(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的CBTC接近区段编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: CBTC接近区段编号
*/ 
UINT16_S* GetRouteDataStrucbtcAccessSegId(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的点式触发区段数量
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 点式触发区段数量
*/ 
UINT16_S GetRouteDataStrublocTrgAreaNum(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的点式触发区段ID
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 点式触发区段ID
*/ 
UINT16_S* GetRouteDataStrublocTrgAreaId(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的CBTC触发区段数量
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: CBTC触发区段数量
*/ 
UINT16_S GetRouteDataStrucbtcTrgAreaNum(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的CBTC触发区段ID
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: CBTC触发区段ID
*/ 
UINT16_S* GetRouteDataStrucbtcTrgAreaId(const UINT16_S routeId);

/*
** 功能描述： 获取指定IDRouteDataStru的所属CI区域编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属CI区域编号
*/ 
UINT16_S GetRouteDataStrumanageCI(const UINT16_S routeId);

/*
* 功能描述： 获取线路进路最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:进路最大ID
*/
UINT16_S GetLineRouteMaxId(void);

/*
* 功能描述： 获取进路对应保护区段信息
* 参数说明： const UINT16_S routeId,进路ID
*            UINT16_S* pOverlapId，保护区段ID指针
* 返回值  ： 0xff: 获取数据失败
*            >=0:保护区段数量
*/
UINT16_S GetLineRouteOfOverlapInfo(const UINT16_S routeId,UINT16_S* pOverlapId);

/*
* 功能描述： 获取进路对应计轴区段信息
* 参数说明： const UINT16_S routeId,进路ID
*            UINT16_S* pAcId，计轴区段ID输出数组
* 返回值  ： 0xff: 获取数据失败
*            >=0:计轴区段数量
*/
UINT16_S GetLineRouteOfAcInfo(const UINT16_S routeId,UINT16_S* pAcId);

/*
* 功能描述： 获取线路进路所属ZCID
* 参数说明： const UINT16_S routeId,进路ID
* 返回值  ： 0xffff: 获取数据失败
*            >0:所属ZCID
*/
UINT16_S GetLineRouteBelongZcId(const UINT16_S routeId);

#ifdef __cplusplus
}
#endif

#endif
