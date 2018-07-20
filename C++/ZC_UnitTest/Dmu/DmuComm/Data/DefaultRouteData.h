/*************************************************
  文件名   ：DefaultRouteData.h
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： DefaultRouteData数据管理
			DmuCommonData组件的DefaultRouteData功能可分解如下：
			1）	给DefaultRouteDataStru结构体指针分配空间
			2）	获取DefaultRouteData数据
			3）	 获取DefaultRouteData信息
			4）	获取指定IDDefaultRouteDataStru的结构体下标
			5）	获取指定IDDefaultRouteDataStru的结构体指针
			6）	 获取指定IDDefaultRouteDataStru的seg编号
			7）	获取指定IDDefaultRouteDataStru的运行方向
			8）	获取指定IDDefaultRouteDataStru的前方站台ID
			9）	获取指定IDDefaultRouteDataStru的目标站台ID
			10）	获取运行方向的下一个自然站台ID查询下一个自然站台ID


  备注    ：无。
 
*************************************************/
#ifndef DEFAULTROUTE_DATA_H_
#define DEFAULTROUTE_DATA_H_

#include "../../../Common/CommonTypes.h"

#define DEFAULTROUTE_LINE_BYTE_NUM                 10                           /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*默认运行序列表数据结构体*/
typedef struct BnfDefaultRouteStruct
{
    UINT16_S  indexId;                        /*索引编号*/
    UINT16_S  segId;                            /*seg编号*/
    UINT16_S  dir;                            /*运行方向*/
    UINT16_S  arriveStaId;                    /*前方站台ID*/
    UINT16_S  aimStaId;                        /*目标站台ID*/
}BnfDefaultRouteStruct;

/*
* 功能描述： 给DefaultRouteDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocDefaultRouteDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取DefaultRouteData数据
* 参数说明：
* 返回值  ： 
            BnfDefaultRouteStruct*
*/
BnfDefaultRouteStruct *GetDefaultRouteData(void);

/*
* 功能描述： 获取DefaultRouteData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfDefaultRouteStruct*
*/
BnfDefaultRouteStruct *GetDefaultRouteDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDDefaultRouteDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetDefaultRouteDataStruIndex(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDDefaultRouteDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfDefaultRouteStruct* GetIndexIdDefaultRouteDataStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDDefaultRouteDataStru的seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: seg编号
*/ 
UINT16_S GetDefaultRouteDataStrusegId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDDefaultRouteDataStru的运行方向
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 运行方向
*/ 
UINT16_S GetDefaultRouteDataStrudir(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDDefaultRouteDataStru的前方站台ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 前方站台ID
*/ 
UINT16_S GetDefaultRouteDataStruarriveStaId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDDefaultRouteDataStru的目标站台ID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 目标站台ID
*/ 
UINT16_S GetDefaultRouteDataStruaimStaId(const UINT16_S indexId);

/*
* 功能描述:获取运行方向的下一个自然站台ID查询下一个自然站台ID
* 参数说明:输入:UINT16_S     segId          SEGID 
*                UINT16_S      dir             运行方向
*                UINT16_S*   nextStationId  >0 下一个自然站台ID
* 返回值   UINT8_S  1 成功  0失败
*/
UINT8_S GetNextAccordCurStationId(const UINT16_S segId,const UINT16_S dir,UINT16_S* nextStationId);

#ifdef __cplusplus
}
#endif

#endif
