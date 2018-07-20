/*************************************************
  文件名   ：ProtectZoneData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： ProtectZoneData数据管理
			DmuCommonData组件的ProtectZoneData功能可分解如下：
			1）	给ProtectZoneDataStru结构体指针分配空间
			2）	获取ProtectZoneData数据
			3）	获取ProtectZoneData信息
			4）	获取指定IDProtectZoneDataStru的结构体下标
			5）	获取指定IDProtectZoneDataStru的结构体指针
			6）	获取指定IDProtectZoneDataStru的包含的计轴区段数目
			7）	获取指定IDProtectZoneDataStru的包含的计轴区段编号
			8）	获取线路保护区段最大ID
			9）	获取保护区段包含的计轴区段信息
			10）	获取线路保护区段所属ZC
			11）	获取线路保护区段最大ID
  备注    ：无。
 
*************************************************/

#include "ProtectZoneData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Copy.h"

static BnfProtectZoneStruct* ProtectZoneDataStru = NULL;   /*定义ProtectZoneData数据结构体*/
static UINT16_S LineNumProtectZone = 0u;/*表行数*/


/*
* 功能描述： 给ProtectZoneDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocProtectZoneDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ProtectZoneDataStru))
    {
        ProtectZoneDataStru = (BnfProtectZoneStruct*)MemoryMalloc((UINT32_S)sizeof(BnfProtectZoneStruct) * lineNum);
        if (ProtectZoneDataStru != NULL)
        {
            LineNumProtectZone = lineNum;
            /*赋值为无效值*/
            MemorySet(ProtectZoneDataStru,lineNum*sizeof(BnfProtectZoneStruct),UINT8_NULL,lineNum*sizeof(BnfProtectZoneStruct));
        }
    }
}

/*
* 功能描述： 获取ProtectZoneData数据
* 参数说明：
* 返回值  ： 
            BnfProtectZoneStruct*
*/
BnfProtectZoneStruct *GetProtectZoneData(void)
{
    return ProtectZoneDataStru;
}


/*
* 功能描述： 获取ProtectZoneData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfProtectZoneStruct*
*/
BnfProtectZoneStruct *GetProtectZoneDataInfo(UINT16_S* lineNum)
{

    BnfProtectZoneStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumProtectZone;
        retVal = ProtectZoneDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDProtectZoneDataStru的结构体下标
* 参数说明： const UINT16_S protectZoneId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetProtectZoneDataStruIndex(const UINT16_S protectZoneId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumProtectZone; i++)
    {
        if (protectZoneId == ProtectZoneDataStru[i].protectZoneId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDProtectZoneDataStru的结构体指针
* 参数说明： const UINT16_S protectZoneId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfProtectZoneStruct* GetIndexIdProtectZoneDataStru(const UINT16_S protectZoneId)
{
    BnfProtectZoneStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetProtectZoneDataStruIndex(protectZoneId);/*获取结构体数组下标*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = &ProtectZoneDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDProtectZoneDataStru的包含的计轴区段数目
* 参数说明： const UINT16_S protectZoneId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的计轴区段数目
*/ 
UINT16_S GetProtectZoneDataStruincludeAxleSgmtNum(const UINT16_S protectZoneId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetProtectZoneDataStruIndex(protectZoneId);/*获取结构体数组下标*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = ProtectZoneDataStru[bufIndex].includeAxleSgmtNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDProtectZoneDataStru的包含的计轴区段编号
* 参数说明： const UINT16_S protectZoneId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 包含的计轴区段编号
*/ 
UINT16_S* GetProtZoDataInAxleSgmtId(const UINT16_S protectZoneId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetProtectZoneDataStruIndex(protectZoneId);/*获取结构体数组下标*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = ProtectZoneDataStru[bufIndex].includeAxleSgmtId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路保护区段最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0: 线路保护区段最大ID
*/
UINT16_S GetLineOverlapMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S protectZoneId = 0u;/*线路保护区段ID*/
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumProtectZone; i++)
    {
        if (protectZoneId < ProtectZoneDataStru[i].protectZoneId)
        {
            protectZoneId = ProtectZoneDataStru[i].protectZoneId;
        }
    }

    if(protectZoneId != 0u)
    {
        retVal = protectZoneId;
    }

    return retVal;
}


/*
* 功能描述： 获取保护区段包含的计轴区段信息
* 参数说明： const UINT16_S protectZoneId,保护区段ID
*            UINT16_S* pAcIdBuf，计轴区段ID数组
* 返回值  ： 0xffff: 获取数据失败
*            >0:计轴区段数量
*/
UINT16_S GetLineOverlapOfAcInfo(const UINT16_S protectZoneId,UINT16_S* pAcIdBuf)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetProtectZoneDataStruIndex(protectZoneId);/*获取结构体数组下标*/
    if (bufIndex < LineNumProtectZone)
    {
        MemoryCpy(pAcIdBuf,sizeof(UINT16_S)*PROTECTZONE_AXLESGM_MAX_NUM,ProtectZoneDataStru[bufIndex].includeAxleSgmtId,sizeof(UINT16_S)*PROTECTZONE_AXLESGM_MAX_NUM);
        retVal = ProtectZoneDataStru[bufIndex].includeAxleSgmtNum;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路保护区段所属ZC
* 参数说明： const UINT16_S overlapId,保护区段ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLineOverlapBelongZcId(const UINT16_S overlapId)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetProtectZoneDataStruIndex(overlapId);/*获取结构体数组下标*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = ProtectZoneDataStru[bufIndex].manageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路保护区段最大ID
所属CI
* 参数说明： const UINT16_S overlapId,保护区段ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ciId
*/
UINT16_S GetLineOverlapBelongCiId(const UINT16_S overlapId)
{
    UINT16_S retVal = UINT16_NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetProtectZoneDataStruIndex(overlapId);/*获取结构体数组下标*/
    if (bufIndex < LineNumProtectZone)
    {
        retVal = ProtectZoneDataStru[bufIndex].manageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

