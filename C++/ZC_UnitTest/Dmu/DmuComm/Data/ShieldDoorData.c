/*************************************************
  文件名   ：ShieldDoorData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： ShieldDoorData数据管理
			DmuCommonData组件的ShieldDoorData功能可分解如下：
			1）	给ShieldDoorDataStru结构体指针分配空间
			2）	获取ShieldDoorData数据
			3）	获取ShieldDoorData信息
			4）	获取指定IDShieldDoorDataStru的结构体下标
			5）	获取指定IDShieldDoorDataStru的结构体指针
			6）	获取指定IDShieldDoorDataStru的名称
			7）	获取指定IDShieldDoorDataStru的所属站台编号
			8）	获取线路屏蔽门最大ID
			9）	查询站台表获取此站台对应的PSD信息
			10）	获取此SEG对应的屏蔽门ID
			11）	获取线路屏蔽门所属ZC
			12）	获取线路屏蔽门所属CI

  备注    ：无。
 
*************************************************/

#include "ShieldDoorData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Convert.h"

static BnfShieldDoorStruct* ShieldDoorDataStru = NULL;   /*定义ShieldDoorData数据结构体*/
static UINT16_S LineNumShieldDoor = 0u;/*表行数*/


/*
* 功能描述： 给ShieldDoorDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocShieldDoorDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == ShieldDoorDataStru))
    {
        ShieldDoorDataStru = (BnfShieldDoorStruct*)MemoryMalloc((UINT32_S)sizeof(BnfShieldDoorStruct) * lineNum);
        if (ShieldDoorDataStru != NULL)
        {
            LineNumShieldDoor = lineNum;
            /*赋值为无效值*/
            MemorySet(ShieldDoorDataStru,lineNum*sizeof(BnfShieldDoorStruct),UINT8_NULL,lineNum*sizeof(BnfShieldDoorStruct));
        }
    }
}

/*
* 功能描述： 获取ShieldDoorData数据
* 参数说明：
* 返回值  ： 
            BnfShieldDoorStruct*
*/
BnfShieldDoorStruct *GetShieldDoorData(void)
{
    return ShieldDoorDataStru;
}


/*
* 功能描述： 获取ShieldDoorData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfShieldDoorStruct*
*/
BnfShieldDoorStruct *GetShieldDoorDataInfo(UINT16_S* lineNum)
{

    BnfShieldDoorStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumShieldDoor;
        retVal = ShieldDoorDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDShieldDoorDataStru的结构体下标
* 参数说明： const UINT16_S shieldDoorId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetShieldDoorDataStruIndex(const UINT16_S shieldDoorId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumShieldDoor; i++)
    {
        if (shieldDoorId == ShieldDoorDataStru[i].shieldDoorId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDShieldDoorDataStru的结构体指针
* 参数说明： const UINT16_S shieldDoorId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfShieldDoorStruct* GetIndexIdShieldDoorDataStru(const UINT16_S shieldDoorId)
{
    BnfShieldDoorStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetShieldDoorDataStruIndex(shieldDoorId);/*获取结构体数组下标*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = &ShieldDoorDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDShieldDoorDataStru的名称
* 参数说明： const UINT16_S shieldDoorId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetShieldDoorDataStruname(const UINT16_S shieldDoorId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetShieldDoorDataStruIndex(shieldDoorId);/*获取结构体数组下标*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = ShieldDoorDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDShieldDoorDataStru的所属站台编号
* 参数说明： const UINT16_S shieldDoorId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属站台编号
*/ 
UINT16_S GetShieldDoorDataStrustationId(const UINT16_S shieldDoorId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetShieldDoorDataStruIndex(shieldDoorId);/*获取结构体数组下标*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = ShieldDoorDataStru[bufIndex].stationId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路屏蔽门最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:屏蔽门最大ID
*/
UINT16_S GetLinePsdMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S shieldDoorId = 0u;/*屏蔽门ID*/
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumShieldDoor; i++)
    {
        if (shieldDoorId < ShieldDoorDataStru[i].shieldDoorId)
        {
            shieldDoorId = ShieldDoorDataStru[i].shieldDoorId;
        }
    }

    if(shieldDoorId != 0u)
    {
        retVal = shieldDoorId;
    }

    return retVal;
}


/*
* 功能描述： 查询站台表获取此站台对应的PSD信息
* 参数说明： 输入:const UINT16_S stationId,站台ID
*             const UINT8_S stationIdNum   站台个数
*             UINT16_S index    数组偏移                  
*             输入输出:UINT16_S psdIdBuff[],屏蔽门ID数组          
* 返回值  ： >=0:屏蔽门个数
*/
UINT16_S GetStationIdBelongofPsdInfo(const UINT16_S* stationIdBuff,const UINT8_S stationIdNum,UINT16_S index,UINT16_S psdIdBuff[])
{
    UINT16_S psdIdNum = 0u;/*屏蔽门个数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/

    if ((stationIdBuff != NULL)&&(stationIdNum > 0u)&&(psdIdBuff != NULL))
    {
        for ( i = 0u; i < LineNumShieldDoor; i++)
        {
            for ( j = 0u; j < stationIdNum; j++)
            {
                if (stationIdBuff[j] == ShieldDoorDataStru[i].stationId)
                {
                    psdIdBuff[index] = ShieldDoorDataStru[i].shieldDoorId;
                    index=index+1;
                    psdIdBuff[index] = LINEOBS_PLATFORM;
                    index=index+1;
                    psdIdNum++;
                    break;
                }
            }
        }
    }
    return psdIdNum;
}

/*
** 功能描述： 获取此SEG对应的屏蔽门ID
* 参数说明： const UINT16_S pPlatformId;站台ID
*             const UINT8_S platformNum  站台ID个数
*             UINT16_S*  pPsdId          屏蔽门ID指针
* 返回值  :  0: 获取数据失败
*            >0: 屏蔽门个数
*/ 
UINT8_S GetPsdIdAccordPlatformIdBuff(const UINT16_S* pPlatformId,const UINT8_S platformNum,UINT16_S* pPsdId)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*循环使用*/
    UINT8_S  j = 0u;/*循环使用*/

    UINT8_S index = 0u;/*数组下标*/

    if (((platformNum <= TWO_POINT_STATION_NUM_MAX)&&(platformNum > 0u))
        &&(pPlatformId != NULL)&&(pPsdId != NULL))
    {
        for ( i = 0u;( i < LineNumShieldDoor)&&(index < TWO_POINT_STATION_NUM_MAX); i++)
        {
            for ( j = 0u; j < platformNum; j++)
            {
                if (pPlatformId[j] == ShieldDoorDataStru[i].stationId)
                {
                    pPsdId[index] = ShieldDoorDataStru[i].shieldDoorId;
                    index=index+1;
                    break;
                }
            }
        }

        if ((index <= TWO_POINT_PSD_NUM_MAX)&&(i == LineNumShieldDoor))
        {
            retVal = index;
        }
    }

    return retVal;
}

/*
* 功能描述： 获取线路屏蔽门所属ZC
* 参数说明： const UINT16_S psdId,屏蔽门ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLinePsdBelongZcId(const UINT16_S psdId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetShieldDoorDataStruIndex(psdId);/*获取结构体数组下标*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = ShieldDoorDataStru[bufIndex].manageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路屏蔽门所属CI
* 参数说明： const UINT16_S psdId,屏蔽门ID
* 返回值  ： 0: 获取数据失败
*            >0:所属CIId
*/
UINT16_S GetLinePsdBelongCiId(const UINT16_S psdId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetShieldDoorDataStruIndex(psdId);/*获取结构体数组下标*/
    if (bufIndex < LineNumShieldDoor)
    {
        retVal = ShieldDoorDataStru[bufIndex].manageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}
