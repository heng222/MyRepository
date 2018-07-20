/*************************************************
  文件名   ：SignData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SignData数据管理
			DmuCommonData组件的SignData功能可分解如下：
			1）	给SignDataStru结构体指针分配空间
			2）	获取SignData数据
			3）	获取SignData信息
			4）	获取指定IDSignDataStru的结构体下标
			5）	获取指定IDSignDataStru的结构体指针
			6）	 获取指定IDSignDataStru的信号机名称
			7）	获取指定IDSignDataStru的类型
			8）	 获取指定IDSignDataStru的属性
			9）	获取指定IDSignDataStru的所处seg编号
			10）	 获取指定IDSignDataStru的所处Seg偏移量（cm）
			11）	获取指定IDSignDataStru的防护方向
			12）	获取指定IDSignDataStru的灯列信息
			13）	获取线路信号机最大ID
			14）	本函数功能是查询当前SEG上指定防护方向的信号机信息
			15）	获取线路信号机所属ZC
			16）	获取线路信号机所属CI
  备注    ：无。
 
*************************************************/

#include "SignData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfSignStruct* SignDataStru = NULL;   /*定义SignData数据结构体*/
static UINT16_S LineNumSign = 0u;/*表行数*/


/*
* 功能描述： 给SignDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSignDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SignDataStru))
    {
        SignDataStru = (BnfSignStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSignStruct) * lineNum);
        if (SignDataStru != NULL)
        {
            LineNumSign = lineNum;
            /*赋值为无效值*/
            MemorySet(SignDataStru,lineNum*sizeof(BnfSignStruct),UINT8_NULL,lineNum*sizeof(BnfSignStruct));
        }
    }
}

/*
* 功能描述： 获取SignData数据
* 参数说明：
* 返回值  ： 
BnfSignStruct*
*/
BnfSignStruct *GetSignData(void)
{
    return SignDataStru;
}


/*
* 功能描述： 获取SignData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfSignStruct*
*/
BnfSignStruct *GetSignDataInfo(UINT16_S* lineNum)
{

    BnfSignStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSign;
        retVal = SignDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDSignDataStru的结构体下标
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSignDataStruIndex(const UINT16_S signId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumSign; i++)
    {
        if (signId == SignDataStru[i].signId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的结构体指针
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSignStruct* GetIndexIdSignDataStru(const UINT16_S signId)
{
    BnfSignStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = &SignDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的信号机名称
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 信号机名称
*/ 
UINT8_S* GetSignDataStrusignName(const UINT16_S signId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的类型
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 类型
*/ 
UINT16_S GetSignDataStrusignType(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signType;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的属性
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 属性
*/ 
UINT16_S GetSignDataStrusignProperty(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signProperty;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的所处seg编号
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT16_S GetSignDataStrusignSegId(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的防护seg编号
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT16_S GetSignDataStrusignProtectSegId(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signProtectSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的防护seg偏移量
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT32_S GetSignDataStrusignProtectSegOffset(const UINT16_S signId)
{
	UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
    	retVal = SignDataStru[bufIndex].signProtectSegOffset;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的所处Seg偏移量（cm）
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处Seg偏移量（cm）
*/ 
UINT32_S GetSignDataStrusignSegOffset(const UINT16_S signId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signSegOffset;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的所处防护方向seg编号
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT16_S GetSignDataStrusignProSegId(const UINT16_S signId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signProtectSegId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的所处防护方向Seg偏移量（cm）
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处Seg偏移量（cm）
*/ 
UINT32_S GetSignDataStrusignProSegOffset(const UINT16_S signId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].signProtectSegOffset;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的防护方向
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 防护方向
*/ 
UINT8_S GetSignDataStruprotectiveDir(const UINT16_S signId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].protectiveDir;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSignDataStru的灯列信息
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 灯列信息
*/ 
UINT32_S GetSignDataStrulightInfo(const UINT16_S signId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].lightInfo;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路信号机最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:信号机最大ID
*/
UINT16_S GetLineSignalMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S signId = 0u;/*信号ID*/
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumSign; i++)
    {
        if (signId < SignDataStru[i].signId)
        {
            signId = SignDataStru[i].signId;
        }
    }

    if(signId != 0u)
    {
        retVal = signId;
    }

    return retVal;
}

/*
* 函数功能：本函数功能是查询当前SEG上指定防护方向的信号机信息。
* 入口参数：UINT16 segId                seg编号
*            UINT8_S  dir                    运行方向
* 出口参数：UINT16 findSignalIDBuff[]        找到的信号机ID
*            UINT8_S* fingNum              查找到信号机的个数
* 返回值：  UINT8_S retVal 
*            查询成功:当前SEG上无信号机，返回0;
*            查询成功:当前SEG上存在信号机，返回1      
*******************************************************************************************/
UINT8_S FindCurrentSegSignal(UINT16_S segId, UINT8_S dir, UINT16_S findSignalIDBuff[],UINT8_S* fingNum)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S i = 0u;/*循环用变量*/

    if((NULL != findSignalIDBuff) && (NULL != fingNum))
    {
        /*初始化输入变量*/
        *fingNum = (UINT8_S)DEFAULT_ZERO;

        /*遍历信号机信息，找到在当前seg上的信号机*/
        for (i=0u; i<LineNumSign; i++)
        {
            /*2010.9.6: 信号机位置改用逻辑位置*/
            if (segId == SignDataStru[i].signProtectSegId) 
            {
                /*判断找到的信号机的方向是否与给定的方向相同*/
                /*说明，DMS描述中，0表示信号机的防护方向与所处seg的逻辑方向相同，
                1表示信号机的防护方向与所处seg的逻辑方向相反*/
                if (((LINESEG_SAME_DIR == SignDataStru[i].protectiveDir) && (LINESEG_SAME_DIR == dir))
                    || ((LINESEG_CONVER_DIR == SignDataStru[i].protectiveDir) && (LINESEG_CONVER_DIR == dir)))
                {
                    /*找到需求的信号机，输出查询结果，查询成功*/
                    findSignalIDBuff[*fingNum] = SignDataStru[i].signId;
                    *fingNum = *fingNum + 1u;
                }
            }
        }

        if ((*fingNum) > 0u)
        {
            retVal = 1u;
        } 

    }


    return retVal;
}

/*
* 功能描述： 获取线路信号机所属ZC
* 参数说明： const UINT16_S signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLineSignalBelongZcId(const UINT16_S signalId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signalId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].manageZCId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取线路信号机所属CI
* 参数说明： const UINT16_S signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*            >0:所属CIId
*/
UINT16_S GetLineSignalBelongCiId(const UINT16_S signalId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSignDataStruIndex(signalId);/*获取结构体数组下标*/
    if (bufIndex < LineNumSign)
    {
        retVal = SignDataStru[bufIndex].manageCIId;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
