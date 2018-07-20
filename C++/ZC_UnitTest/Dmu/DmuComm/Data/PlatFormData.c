/*************************************************
  文件名   ：PlatFormData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： PlatFormData数据管理
			DmuCommonData组件的PlatFormData功能可分解如下：
			1）	给PlatFormDataStru结构体指针分配空间
			2）	获取PlatFormData数据
			3）	获取PlatFormData信息
			4）	获取指定IDPlatFormDataStru的结构体下标
			5）	获取指定IDPlatFormDataStru的结构体指针
			6）	 获取指定IDPlatFormDataStru的站台中心公里标
			7）	获取指定IDPlatFormDataStru的站台关联seg编号
			8）	获取指定IDPlatFormDataStru的逻辑方向上站台相对于停车区域的方向
			9）	获取此SEG对应的站台ID
			10）	查找此计轴区段是否属于站台区域
			11）	获取此SEG对应的站台ID
			12）	获取此SEG对应的站台ID
  备注    ：无。 
*************************************************/

#include "PlatFormData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"

static BnfPlatFormStruct* PlatFormDataStru = NULL;   /*定义PlatFormData数据结构体*/
static UINT16_S LineNumPlatForm = 0u;/*表行数*/


/*
* 功能描述： 给PlatFormDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocPlatFormDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == PlatFormDataStru))
    {
        PlatFormDataStru = (BnfPlatFormStruct*)MemoryMalloc((UINT32_S)sizeof(BnfPlatFormStruct) * lineNum);
        LineNumPlatForm = lineNum;
    }
}

/*
* 功能描述： 获取PlatFormData数据
* 参数说明：
* 返回值  ： 
            BnfPlatFormStruct*
*/
BnfPlatFormStruct *GetPlatFormData(void)
{
    return PlatFormDataStru;
}


/*
* 功能描述： 获取PlatFormData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfPlatFormStruct*
*/
BnfPlatFormStruct *GetPlatFormDataInfo(UINT16_S* lineNum)
{

    BnfPlatFormStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumPlatForm;
        retVal = PlatFormDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDPlatFormDataStru的结构体下标
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetPlatFormDataStruIndex(const UINT16_S platFormId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumPlatForm; i++)
    {
        if (platFormId == PlatFormDataStru[i].platFormId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPlatFormDataStru的结构体指针
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfPlatFormStruct* GetIndexIdPlatFormDataStru(const UINT16_S platFormId)
{
    BnfPlatFormStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPlatFormDataStruIndex(platFormId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPlatForm)
    {
        retVal = &PlatFormDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPlatFormDataStru的站台中心公里标
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 站台中心公里标
*/ 
UINT8_S* GetPlatFormDataStruplatFormKillPost(const UINT16_S platFormId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPlatFormDataStruIndex(platFormId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPlatForm)
    {
        retVal = PlatFormDataStru[bufIndex].platFormKillPost;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPlatFormDataStru的站台关联seg编号
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  0: 获取数据失败
*            >0: 站台关联seg编号
*/ 
UINT16_S GetPlatFormDataStrusegId(const UINT16_S platFormId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPlatFormDataStruIndex(platFormId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPlatForm)
    {
        retVal = PlatFormDataStru[bufIndex].segId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDPlatFormDataStru的逻辑方向上站台相对于停车区域的方向
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  0: 获取数据失败
*            >0: 逻辑方向上站台相对于停车区域的方向
*/ 
UINT8_S GetPlatFormDataStrudir(const UINT16_S platFormId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetPlatFormDataStruIndex(platFormId);/*获取结构体数组下标*/
    if (bufIndex < LineNumPlatForm)
    {
        retVal = PlatFormDataStru[bufIndex].dir;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取此SEG对应的站台ID
* 参数说明： const UINT16_S segId;SEGID
*             UINT16_S* platFormIdBuff  站台ID
* 返回值  :  Oxff: 获取数据失败
*            >=0: 站台ID个数
*/ 
UINT8_S GetSegIdBelongOfStationId(const UINT16_S* segIdBuff,UINT8_S segIdNum,UINT16_S* platFormIdBuff)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/
    UINT8_S platFormIdNum = 0u;/*站台个数*/

    if ((NULL == segIdBuff) ||(NULL == platFormIdBuff))
    {
        retVal = UINT8_NULL;
    }
    else
    {
        for ( i = 0u;(i < LineNumPlatForm)&&(UINT8_NULL != retVal); i++)
        {
            for (j = 0u; j < segIdNum; j++)
            {
                if (segIdBuff[j] == PlatFormDataStru[i].segId)
                {
                    if (platFormIdNum == ROUTE_INCLUDE_PLATFORM_MAX_NUM)
                    {
                        retVal = UINT8_NULL;
                        break;
                    }
                    else
                    {
                        platFormIdBuff[platFormIdNum] = PlatFormDataStru[i].platFormId;
                        platFormIdNum=platFormIdNum+1;
                        break;
                    }

                }
            }

        }

        if (UINT8_NULL != retVal)
        {
            retVal = platFormIdNum;
        }

    }
    return retVal;
}

/*
* 功能描述： 查找此计轴区段是否属于站台区域
* 参数说明： const UINT16_S* pSegId;SEGID指针
* 返回值  :  1 属于
*             2 不属于
*/ 
UINT8_S SearchStationBelongAxleSec(const UINT16_S* pSegId,UINT16_S includeSegNum)
{
    UINT8_S retVal = 2u;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/
    UINT16_S  j = 0u;/*循环使用*/

    if(NULL != pSegId)
    {
        for ( i = 0u; i < LineNumPlatForm; i++)
        {
            for (j = 0u;j < includeSegNum; j++)
            {
                if (pSegId[j] == PlatFormDataStru[i].segId)
                {
                    retVal = 1u;
                    break;
                }
            }
        }
    }

    return retVal;
}

/*
** 功能描述： 获取此SEG对应的站台ID
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :  0: 获取数据失败
*            >0: 站台个数
*/ 
UINT8_S GetPlatformIdAccordSegBuff(const UINT16_S* pSegId,const UINT8_S segNum,UINT16_S* pPlatformId)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*循环使用*/
    UINT8_S  j = 0u;/*循环使用*/

    UINT8_S index = 0u;/*数组下标*/

    if (((segNum <= BOTHSEG_INCLUDE_MAX_SEG)&&(segNum > 0))
        &&(pSegId != NULL)&&(pPlatformId != NULL))
    {
        for ( i = 0u;( i < LineNumPlatForm)&&(index < TWO_POINT_STATION_NUM_MAX); i++)
        {
            for ( j = 0u; j < segNum; j++)
            {
                if (pSegId[j] == PlatFormDataStru[i].segId)
                {
                    pPlatformId[index] = PlatFormDataStru[i].platFormId;
                    index=index+1;
                    break;
                }
            }
        }

        if ((index <= TWO_POINT_STATION_NUM_MAX)&&(i == LineNumPlatForm))
        {
            retVal = index;
        }
    }

    return retVal;
}

/*
** 功能描述： 获取此SEG对应的站台ID
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :  0: 获取数据失败
*            >0: 站台ID
*/ 
UINT16_S GetPlatformIdAccordSegId(const UINT16_S segId)
{
    UINT16_S retVal = 0u;

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u;i < LineNumPlatForm; i++)
    {
        if (segId == PlatFormDataStru[i].segId)
        {
            retVal = PlatFormDataStru[i].platFormId;
            break;
        }
    }

    return retVal;
}
