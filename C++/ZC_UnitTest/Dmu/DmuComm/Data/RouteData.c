/*************************************************
  文件名   ：RouteData.c
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

#include "RouteData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Copy.h"

static BnfRouteStruct* RouteDataStru = NULL;   /*定义RouteData数据结构体*/
static UINT16_S LineNumRoute = 0u;/*表行数*/


/*
* 功能描述： 给RouteDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocRouteDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == RouteDataStru))
    {
        RouteDataStru = (BnfRouteStruct*)MemoryMalloc((UINT32_S)sizeof(BnfRouteStruct) * lineNum);
        if (RouteDataStru != NULL)
        {
            LineNumRoute = lineNum;
            /*赋值为无效值*/
            MemorySet(RouteDataStru,lineNum*sizeof(BnfRouteStruct),UINT8_NULL,lineNum*sizeof(BnfRouteStruct));
        }
    }
}

/*
* 功能描述： 获取RouteData数据
* 参数说明：
* 返回值  ： 
BnfRouteStruct*
*/
BnfRouteStruct *GetRouteData(void)
{
    return RouteDataStru;
}


/*
* 功能描述： 获取RouteData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfRouteStruct*
*/
BnfRouteStruct *GetRouteDataInfo(UINT16_S* lineNum)
{

    BnfRouteStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumRoute;
        retVal = RouteDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDRouteDataStru的结构体下标
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetRouteDataStruIndex(const UINT16_S routeId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumRoute; i++)
    {
        if (routeId == RouteDataStru[i].routeId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的结构体指针
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfRouteStruct* GetIndexIdRouteDataStru(const UINT16_S routeId)
{
    BnfRouteStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = &RouteDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的进路名称
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 进路名称
*/ 
UINT8_S* GetRouteDataStrurouteName(const UINT16_S routeId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].routeName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的进路性质
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 进路性质
*/ 
UINT16_S GetRouteDataStrurouteType(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].routeType;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的起始信号机编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起始信号机编号
*/ 
UINT16_S GetRouteDataStrustartSignalId(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].startSignalId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的终止信号机编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终止信号机编号
*/ 
UINT16_S GetRouteDataStruendSignalId(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].endSignalId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的包含计轴区段数目
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含计轴区段数目
*/ 
UINT16_S GetRouteDataStruincludeAxleSecNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].includeAxleSecNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的计轴区段编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 计轴区段编号
*/ 
UINT16_S* GetRouteDataStruAxleSec(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].AxleSec;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的保护区段数目
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 保护区段数目
*/ 
UINT16_S GetRouteDataStruprotectSecNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].protectSecNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的保护区段编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 保护区段编号
*/ 
UINT16_S* GetRouteDataStruprotectSecId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].protectSecId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的点式接近区段数目
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 点式接近区段数目
*/ 
UINT16_S GetRouteDataStrublogAccessSegNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].blogAccessSegNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的点式接近区段编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 点式接近区段编号
*/ 
UINT16_S* GetRouteDataStrublogAccessSegId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].blogAccessSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的CBTC接近区段数目
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: CBTC接近区段数目
*/ 
UINT16_S GetRouteDataStrucbtcAccessSegNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].cbtcAccessSegNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的CBTC接近区段编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: CBTC接近区段编号
*/ 
UINT16_S* GetRouteDataStrucbtcAccessSegId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].cbtcAccessSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的点式触发区段数量
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 点式触发区段数量
*/ 
UINT16_S GetRouteDataStrublocTrgAreaNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].blocTrgAreaNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的点式触发区段ID
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 点式触发区段ID
*/ 
UINT16_S* GetRouteDataStrublocTrgAreaId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].blocTrgAreaId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的CBTC触发区段数量
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: CBTC触发区段数量
*/ 
UINT16_S GetRouteDataStrucbtcTrgAreaNum(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].cbtcTrgAreaNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的CBTC触发区段ID
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: CBTC触发区段ID
*/ 
UINT16_S* GetRouteDataStrucbtcTrgAreaId(const UINT16_S routeId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].cbtcTrgAreaId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDRouteDataStru的所属CI区域编号
* 参数说明： const UINT16_S routeId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属CI区域编号
*/ 
UINT16_S GetRouteDataStrumanageCI(const UINT16_S routeId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].manageCI;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路进路最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:进路最大ID
*/
UINT16_S GetLineRouteMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S routeId = 0u;/*进路ID*/
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumRoute; i++)
    {
        if (routeId < RouteDataStru[i].routeId)
        {
            routeId = RouteDataStru[i].routeId;
        }
    }

    if(routeId != 0u)
    {
        retVal = routeId;
    }

    return retVal;
}

/*
* 功能描述： 获取进路对应保护区段信息
* 参数说明： const UINT16_S routeId,进路ID
*            UINT16_S* pOverlapId，保护区段ID指针
* 返回值  ： 0xff: 获取数据失败
*            >=0:保护区段数量
*/
UINT16_S GetLineRouteOfOverlapInfo(const UINT16_S routeId,UINT16_S* pOverlapId)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/

    if (pOverlapId != NULL)
    {
        if (bufIndex < LineNumRoute)
        {
            MemoryCpy(pOverlapId,sizeof(UINT16_S)*ROUTE_PROTECT_SEC_MAX_NUM,RouteDataStru[bufIndex].protectSecId,sizeof(UINT16_S)*ROUTE_PROTECT_SEC_MAX_NUM);
            retVal = RouteDataStru[bufIndex].protectSecNum;
        }
        else
        {
            retVal = UINT16_NULL;
        }
    }
    else
    {
        retVal = UINT16_NULL;
    }

    return retVal;
}

/*
* 功能描述： 获取进路对应计轴区段信息
* 参数说明： const UINT16_S routeId,进路ID
*            UINT16_S* pAcId，计轴区段ID输出数组
* 返回值  ： 0xffFF: 获取数据失败
*            >=0:计轴区段数量
*/
UINT16_S GetLineRouteOfAcInfo(const UINT16_S routeId,UINT16_S* pAcId)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/

    if (pAcId != NULL)
    {
        bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
        if (bufIndex < LineNumRoute)
        {
            MemoryCpy(pAcId,sizeof(UINT16_S)*ROUTE_SEC_MAX_NUM,RouteDataStru[bufIndex].AxleSec,sizeof(UINT16_S)*ROUTE_SEC_MAX_NUM);
            retVal = RouteDataStru[bufIndex].includeAxleSecNum;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }
    else
    {
        retVal = UINT16_NULL;
    }

    return retVal;
}

/*
* 功能描述： 获取线路进路所属ZCID
* 参数说明： const UINT16_S routeId,进路ID
* 返回值  ： 0xffff: 获取数据失败
*            >0:所属ZCID
*/
UINT16_S GetLineRouteBelongZcId(const UINT16_S routeId)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetRouteDataStruIndex(routeId);/*获取结构体数组下标*/
    if (bufIndex < LineNumRoute)
    {
        retVal = RouteDataStru[bufIndex].manageZCId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
