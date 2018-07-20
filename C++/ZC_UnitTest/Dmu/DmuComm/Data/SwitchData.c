/*************************************************
  文件名   ：SwitchData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SwitchData数据管理
			DmuCommonData组件的SwitchData功能可分解如下：
			1）	给SwitchDataStru结构体指针分配空间
			2）	获取SwitchData数据
			3）	获取SwitchData信息
			4）	获取指定IDSwitchDataStru的结构体下标
			5）	获取指定IDSwitchDataStru的结构体指针
			6）	获取指定IDSwitchDataStru的道岔名称
			7）	获取指定IDSwitchDataStru的联动道岔编号
			8）	获取指定IDSwitchDataStru的方向
			9）	获取指定IDSwitchDataStru的定位SegID
			10）	获取指定IDSwitchDataStru的反位SegID
			11）	获取指定IDSwitchDataStru的所有SegID
			12）	获取指定IDSwitchDataStru的道岔反位静态限制速度(cm/s)
			13）	根据输入的SEGID获取道岔的数量
			14）	获取线路道岔最大ID
			15）	根据输入的SEGID获取道岔信息
			16）	根据输入的SEGID获取道岔的数量
			17）	获取线路道岔所属ZC
			18）	获取线路道岔所属CI
  备注    ：无。
 
*************************************************/

#include "SwitchData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfSwitchStruct* SwitchDataStru = NULL;   /*定义SwitchData数据结构体*/
static UINT16_S LineNumSwitch = 0u;/*表行数*/


/*
* 功能描述： 给SwitchDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSwitchDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SwitchDataStru))
    {
        SwitchDataStru = (BnfSwitchStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSwitchStruct) * lineNum);
        if (SwitchDataStru != NULL)
        {
            LineNumSwitch = lineNum;
            /*赋值为无效值*/
            MemorySet(SwitchDataStru,lineNum*sizeof(BnfSwitchStruct),UINT8_NULL,lineNum*sizeof(BnfSwitchStruct));
        }
    }
}

/*
* 功能描述： 获取SwitchData数据
* 参数说明：
* 返回值  ： 
BnfSwitchStruct*
*/
BnfSwitchStruct *GetSwitchData(void)
{
    return SwitchDataStru;
}


/*
* 功能描述： 获取SwitchData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfSwitchStruct*
*/
BnfSwitchStruct *GetSwitchDataInfo(UINT16_S* lineNum)
{

    BnfSwitchStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSwitch;
        retVal = SwitchDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDSwitchDataStru的结构体下标
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSwitchDataStruIndex(const UINT16_S switchId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumSwitch; i++)
    {
        if (switchId == SwitchDataStru[i].switchId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSwitchDataStru的结构体指针
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSwitchStruct* GetIndexIdSwitchDataStru(const UINT16_S switchId)
{
    BnfSwitchStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = &SwitchDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSwitchDataStru的道岔名称
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 道岔名称
*/ 
UINT8_S* GetSwitchDataStruswitchName(const UINT16_S switchId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].switchName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSwitchDataStru的联动道岔编号
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 联动道岔编号
*/ 
UINT16_S GetSwitchDataStruswitchOtherId(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].switchOtherId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSwitchDataStru的方向
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 方向
*/ 
UINT16_S GetSwitchDataStrudir(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].dir;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSwitchDataStru的定位SegID
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 定位SegID
*/ 
UINT16_S GetSwitchDataStrulocSegId(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].locSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSwitchDataStru的反位SegID
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 反位SegID
*/ 
UINT16_S GetSwitchDataStruantiSegId(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].antiSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSwitchDataStru的所有SegID
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*             1: 获取数据成功
*/ 
UINT8_S GetSwitchDataStruSegIdInfo(const UINT16_S switchId,UINT16_S* locSegId,UINT16_S* antiSegId,UINT16_S* joinSegId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        * joinSegId = SwitchDataStru[bufIndex].joinSegId;
        *locSegId = SwitchDataStru[bufIndex].locSegId;
        *antiSegId =SwitchDataStru[bufIndex].antiSegId;

        retVal = 1u;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSwitchDataStru的道岔反位静态限制速度(cm/s)
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 道岔反位静态限制速度(cm/s)
*/ 
UINT16_S GetSwitchDataStruswitchSideResSpeed(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].switchSideResSpeed;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 根据输入的SEGID获取道岔的数量
* 参数说明： const UINT16_S* pSegId;SEGID指针指针
const UINT16_S segIdNum;SEGID个数
* 返回值  :  0: 获取数据失败
*            >0: 道岔个数
*/ 
UINT16_S GetSegIdOfSwitchIdNum(const UINT16_S* pSegId,const UINT16_S segIdNum)
{
    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j = 0u;/*循环使用*/

    UINT16_S switchIdNum = 0u;/*道岔个数*/

    for ( i = 0u; i < LineNumSwitch; i++)
    {
        for (j = 0u;j < segIdNum; j++)
        {
            if ((SwitchDataStru[i].locSegId == pSegId[j])||(SwitchDataStru[i].joinSegId == pSegId[j])
                ||(SwitchDataStru[i].antiSegId == pSegId[j]))
            {
                switchIdNum++;
                break;
            }
        }

    }

    return switchIdNum;
}


/*
* 功能描述： 获取线路道岔最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:道岔最大ID
*/
UINT16_S GetLineSwitchMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S switchId = 0u;/*道岔ID*/
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumSwitch; i++)
    {
        if (switchId < SwitchDataStru[i].switchId)
        {
            switchId = SwitchDataStru[i].switchId;
        }
    }

    if(switchId != 0u)
    {
        retVal = switchId;
    }

    return retVal;
}

/*
** 功能描述： 根据输入的SEGID获取道岔信息
* 参数说明： 输入:const UINT16_S segId,SEGID
*             const UINT8_S segIdNum    SEGID个数
*             UINT16_S index    数组偏移                  
*             输入输出:UINT16_S switchIdBuff[],道岔ID数组      
* 返回值  :  >=0: 道岔个数
*/ 
UINT16_S GetSegIdBelongofSwitchInfo(const UINT16_S* segIdBuff,const UINT8_S segIdNum,UINT16_S index,UINT16_S switchIdBuff[])
{
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/
    UINT16_S switchIdNum = 0u;/*道岔个数*/

    if ((segIdBuff != NULL)&&(segIdNum >0u)&&(switchIdBuff != NULL))
    {
        for ( i = 0u; i < LineNumSwitch; i++)
        {
            for (j = 0u; j < segIdNum; j++)
            {
                if ((SwitchDataStru[i].locSegId == segIdBuff[j])||(SwitchDataStru[i].antiSegId == segIdBuff[j]))
                {
                    switchIdBuff[index] = SwitchDataStru[i].switchId;
                    index=index+1;
                    switchIdBuff[index] = LINEOBS_SWITCH;
                    index=index+1;
                    switchIdNum++;
                    break;
                }
            }
        }
    }

    return switchIdNum;
}


/*
** 功能描述： 根据输入的SEGID获取道岔的数量
* 参数说明： const UINT16_S* pSegId;SEGID指针指针
const UINT8_S segIdNum;SEGID个数
UINT16_S switchIdBuff[];道岔ID数组
* 返回值  :  0: 获取数据失败
*            >0: 道岔个数
*/ 
UINT8_S GetSegIdBuffOfSwitchInfo(const UINT16_S* pSegId,const UINT16_S segIdNum,UINT16_S switchIdBuff[])
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j = 0u;/*循环使用*/
    UINT8_S index = 0u;/*数组偏移*/

    UINT8_S switchIdNum = 0u;/*道岔个数*/

    if (((segIdNum <= BOTHSEG_INCLUDE_MAX_SEG)&&(segIdNum > 0u))
        &&(pSegId != NULL)&&(switchIdBuff != NULL))
    {
        for ( i = 0u;(i < LineNumSwitch)&&(switchIdNum < TWO_POINT_SWITCH_NUM_MAX); i++)
        {
            for (j = 0u;j < segIdNum; j++)
            {
                if (SwitchDataStru[i].locSegId == pSegId[j])
                {
                    switchIdBuff[index] = SwitchDataStru[i].switchId;
                    index=index+1;
                    switchIdBuff[index] = SWITCH_STATUS_SAME;
                    index=index+1;
                    switchIdNum++;
                    break;
                }
                else if (SwitchDataStru[i].antiSegId == pSegId[j])
                {
                    switchIdBuff[index] = SwitchDataStru[i].switchId;
                    index=index+1;
                    switchIdBuff[index] = SWITCH_STATUS_CONTRA;
                    index=index+1;
                    switchIdNum++;
                    break;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }

        }

        if (i == LineNumSwitch)
        {
            retVal = switchIdNum;
        }

    }

    return retVal;
}

/*
* 功能描述： 获取线路道岔所属ZC
* 参数说明： const UINT16_S switchId,道岔ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLineSwitchBelongZcId(const UINT16_S switchId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].manageZCId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路道岔所属CI
* 参数说明： const UINT16_S switchId,道岔ID
* 返回值  ： 0: 获取数据失败
*            >0:所属CIId
*/
UINT16_S GetLineSwitchBelongCiId(const UINT16_S switchId)
{    
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSwitchDataStruIndex(switchId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSwitch)
    {
        retVal = SwitchDataStru[bufIndex].manageCIId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
