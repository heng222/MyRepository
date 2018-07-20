/*************************************************
  文件名   ：EmergStopButtonData.c
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： EmergStopButtonData数据管理
			DmuCommonData组件的EmergStopButtonData功能可分解如下：
			1）	给EmergStopButtonDataStru结构体指针分配空间
			2）	获取EmergStopButtonData数据
			3）	获取EmergStopButtonData信息
			4）	获取指定IDEmergStopButtonDataStru的结构体下标
			5）	获取指定IDEmergStopButtonDataStru的结构体指针
			6）	 获取指定IDEmergStopButtonDataStru的名称
			7）	获取指定IDEmergStopButtonDataStru的所属站台编号
			8）	获取线路紧急停车按钮最大ID
			9）	获取线路紧急停车按钮所属站台ID
			10）	根据输入的SEGID获取ESB信息
			11）	根据站台ID获取对应的紧急停车按钮ID
			12）	获取线路紧急停车按钮所属ZC
			13）	获取线路紧急停车按钮所属ci
  备注    ：无。
 
*************************************************/

#include "EmergStopButtonData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfEmergStopButtonStruct* EmergStopButtonDataStru = NULL;   /*定义EmergStopButtonData数据结构体*/
static UINT16_S LineNumEmergStopButton = 0u;/*表行数*/


/*
* 功能描述： 给EmergStopButtonDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocEmergStopButtonDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == EmergStopButtonDataStru))
    {
        EmergStopButtonDataStru = (BnfEmergStopButtonStruct*)MemoryMalloc((UINT32_S)sizeof(BnfEmergStopButtonStruct) * lineNum);
        if (EmergStopButtonDataStru != NULL)
        {
            LineNumEmergStopButton = lineNum;
            /*赋值为无效值*/
            MemorySet(EmergStopButtonDataStru,lineNum*sizeof(BnfEmergStopButtonStruct),UINT8_NULL,lineNum*sizeof(BnfEmergStopButtonStruct));
        }
    }
}

/*
* 功能描述： 获取EmergStopButtonData数据
* 参数说明：
* 返回值  ： 
            BnfEmergStopButtonStruct*
*/
BnfEmergStopButtonStruct *GetEmergStopButtonData(void)
{
    return EmergStopButtonDataStru;
}


/*
* 功能描述： 获取EmergStopButtonData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfEmergStopButtonStruct*
*/
BnfEmergStopButtonStruct *GetEmergStopButtonDataInfo(UINT16_S* lineNum)
{
    BnfEmergStopButtonStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumEmergStopButton;
        retVal =  EmergStopButtonDataStru;

    }
    return retVal;
}
/*
** 功能描述： 获取指定IDEmergStopButtonDataStru的结构体下标
* 参数说明： const UINT16_S emergStopButtonId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetEmergStopButtonDataStruIndex(const UINT16_S emergStopButtonId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (emergStopButtonId == EmergStopButtonDataStru[i].emergStopButtonId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDEmergStopButtonDataStru的结构体指针
* 参数说明： const UINT16_S emergStopButtonId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfEmergStopButtonStruct* GetIndexIdEmergStopButtonDataStru(const UINT16_S emergStopButtonId)
{
    BnfEmergStopButtonStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetEmergStopButtonDataStruIndex(emergStopButtonId);/*获取结构体数组下标*/
    if (bufIndex < LineNumEmergStopButton)
    {
        retVal = &EmergStopButtonDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDEmergStopButtonDataStru的名称
* 参数说明： const UINT16_S emergStopButtonId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetEmergStopButtonDataStruname(const UINT16_S emergStopButtonId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetEmergStopButtonDataStruIndex(emergStopButtonId);/*获取结构体数组下标*/
    if (bufIndex < LineNumEmergStopButton)
    {
        retVal = EmergStopButtonDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDEmergStopButtonDataStru的所属站台编号
* 参数说明： const UINT16_S emergStopButtonId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属站台编号
*/ 
UINT16_S GetEmergStopButtonDataStrustationId(const UINT16_S emergStopButtonId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetEmergStopButtonDataStruIndex(emergStopButtonId);/*获取结构体数组下标*/
    if (bufIndex < LineNumEmergStopButton)
    {
        retVal = EmergStopButtonDataStru[bufIndex].stationId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路紧急停车按钮最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:紧急停车按钮最大ID
*/
UINT16_S GetLineEsbMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S emergStopButtonId = 0u;/*紧急停车按钮ID*/
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (emergStopButtonId < EmergStopButtonDataStru[i].emergStopButtonId)
        {
            emergStopButtonId = EmergStopButtonDataStru[i].emergStopButtonId;
        }
    }

    if(emergStopButtonId != 0u)
    {
        retVal = emergStopButtonId;
    }

    return retVal;
}

/*
* 功能描述： 获取线路紧急停车按钮所属站台ID
* 参数说明： const UINT16_S esbId,紧急停车按钮ID
* 返回值  ： 0xffff: 获取数据失败
*            >0:所属站台ID
*/
UINT16_S GetLineEsbBelongStationId(const UINT16_S esbId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (esbId == EmergStopButtonDataStru[i].emergStopButtonId)
        {
            retVal = EmergStopButtonDataStru[i].stationId;
            break;
        }
    }

    return retVal;
}

/*
** 功能描述： 根据输入的SEGID获取ESB信息
* 参数说明： 输入:const UINT16_S stationIdBuff,站台ID
*             const UINT8_S stationIdNum    站台ID个数
*             UINT16_S* index    数组偏移                  
*             输入输出:UINT16_S esbIdBuff[],ESBID数组      
* 返回值  :  >=0: ESB信息
*/ 
UINT16_S GetStationIdBelongofEsbInfo(const UINT16_S* stationIdBuff,const UINT8_S stationIdNum,UINT16_S index,UINT16_S esbIdBuff[])
{
    UINT16_S retVal = 0u;
    UINT16_S esbIdNum = 0u;/*紧急停车按钮个数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/
    
    if ((stationIdBuff != NULL)&&(stationIdNum > 0u)&&(esbIdBuff != NULL))
    {
        for ( i = 0u; i < LineNumEmergStopButton; i++)
        {
            for (j = 0u; j < stationIdNum; j++)
            {
                if (stationIdBuff[j] == EmergStopButtonDataStru[i].stationId)
                {
                    esbIdBuff[index] = EmergStopButtonDataStru[i].emergStopButtonId;
                    index=index+1;

                    esbIdBuff[index] = LINEOBS_ESB;
                    index=index+1;
                    esbIdNum++;
                    break;
                }
            }

        }
    }

    retVal = esbIdNum;
    return retVal;
}

/*
** 功能描述： 根据站台ID获取对应的紧急停车按钮ID
* 参数说明： const UINT16_S pPlatformId;站台ID
*             const UINT8_S platformNum  站台ID个数
*             UINT16_S*  pPsdId          屏蔽门ID指针
* 返回值  :  0: 获取数据失败
*            >0: 紧急停车按钮个数
*/ 
UINT8_S GetEsbIdAccordPlatformIdBuff(const UINT16_S* pPlatformId,const UINT8_S platformNum,UINT16_S* pEsbId)
{
    UINT8_S retVal = 0u;

    UINT16_S i = 0u;/*循环使用*/
    UINT8_S  j = 0u;/*循环使用*/

    UINT8_S index = 0u;/*数组下标*/

    if (((platformNum <= TWO_POINT_STATION_NUM_MAX)&&(platformNum > 0u))
        &&(pPlatformId != NULL)&&(pEsbId != NULL))
    {
        for ( i = 0u;( i < LineNumEmergStopButton)&&(index < TWO_POINT_ESB_NUM_MAX); i++)
        {
            for ( j = 0u; j < platformNum; j++)
            {
                if (pPlatformId[j] == EmergStopButtonDataStru[i].stationId)
                {
                    pEsbId[index] = EmergStopButtonDataStru[i].emergStopButtonId;
                    index=index+1;
                    break;
                }
            }
        }

        if (i == LineNumEmergStopButton)
        {
            retVal = index;
        }
    }

    return retVal;
}

/*
* 功能描述： 获取线路紧急停车按钮所属ZC
* 参数说明： const UINT16_S esbId,紧急停车按钮ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLineEsbBelongZcId(const UINT16_S esbId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (esbId == EmergStopButtonDataStru[i].emergStopButtonId)
        {
            retVal = EmergStopButtonDataStru[i].manageZCId;
            break;
        }
    }

    return retVal;
}

/*
* 功能描述： 获取线路紧急停车按钮所属ci
* 参数说明： const UINT16_S esbId,紧急停车按钮ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ciId
*/
UINT16_S GetLineEsbBelongCiId(const UINT16_S esbId)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumEmergStopButton; i++)
    {
        if (esbId == EmergStopButtonDataStru[i].emergStopButtonId)
        {
            retVal = EmergStopButtonDataStru[i].manageCIId;
            break;
        }
    }

    return retVal;
}
