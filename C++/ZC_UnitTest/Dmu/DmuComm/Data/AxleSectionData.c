
/*************************************************
  文件名   ：AxleSectionData.c
  作者     ：董欣      
  创建时间 ：2016-8-10
  功能描述 ： AxleSectionData数据管理
			DmuCommonData组件的AxleSectionData功能可分解如下：
			1）	给AxleSectionDataStru结构体指针分配空间
			2）	获取AxleSectionData数据
			3）	获取AxleSectionData信息
			4）	获取指定IDAxleSectionDataStru的结构体下标
			5）	获取指定IDAxleSectionDataStru的结构体指针
			6）	获取指定IDAxleSectionDataStru的名称
			7）	获取指定IDAxleSectionDataStru的包含Seg数目
			8）	获取指定IDAxleSectionDataStru的Seg编号
			9）	获取计轴区段包含的SegId的信息
			10）	获取SEGID包含的计轴区段ID
			11）	获取SEGID包含的计轴区段结构体指针
			12）	获取线路计轴区段最大ID
			13）	获取指定IDAxleSectionDataStru的Seg信息
			14）	获取计轴区段所属CIID
			15）	获取计轴区段所属ZC
			16）	获取计轴区段包含逻辑区段信息

  备注    ：无。
 
*************************************************/

#include "AxleSectionData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"
#include "../../../Common/Copy.h"

static BnfAxleSectionStruct* AxleSectionDataStru = NULL;   /*定义AxleSectionData数据结构体*/
static UINT16_S LineNumAxleSection = 0u;/*表行数*/


/*
* 函数名称：MallocAxleSectionDataStru
* 功能描述： 给AxleSectionDataStru结构体指针分配空间
* 输入参数： UINT16_S lineNum 表的数据行数
* 输出参数： 无
* 返回值  ： void
*/
void MallocAxleSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == AxleSectionDataStru))
    {
        AxleSectionDataStru = (BnfAxleSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfAxleSectionStruct) * lineNum);
        if (AxleSectionDataStru != NULL)
        {
            LineNumAxleSection = lineNum;
            /*赋值为无效值*/
            MemorySet(AxleSectionDataStru,lineNum*sizeof(BnfAxleSectionStruct),UINT8_NULL,lineNum*sizeof(BnfAxleSectionStruct));
        }
    }
}

/*
* 函数名称： GetAxleSectionData
* 功能描述： 获取AxleSectionData数据
* 输入参数： 无
* 输出参数： 无
* 返回值  ：
*           BnfAxleSectionStruct*
*/
BnfAxleSectionStruct *GetAxleSectionData(void)
{
    return AxleSectionDataStru;
}


/*
* 函数名称： GetAxleSectionData
* 功能描述： 获取AxleSectionData数据
* 输入参数： 无
* 输出参数： 无
* 返回值  ：
*           BnfAxleSectionStruct*
*/
BnfAxleSectionStruct *GetAxleSectionDataInfo(UINT16_S* lineNum)
{
    BnfAxleSectionStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumAxleSection;
        retVal =  AxleSectionDataStru;

    }
    return retVal;
}
/*
* 函数名称： GetAxleSectionDataStruIndex
* 功能描述： 获取指定IDAxleSectionDataStru的结构体下标
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetAxleSectionDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumAxleSection; i++)
    {
        if (indexId == AxleSectionDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
* 函数名称： GetIndexIdAxleSectionDataStru
* 功能描述： 获取指定IDAxleSectionDataStru的结构体指针
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfAxleSectionStruct* GetIndexIdAxleSectionDataStru(const UINT16_S indexId)
{
    BnfAxleSectionStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetAxleSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumAxleSection)
    {
        retVal = &AxleSectionDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 函数名称： GetAxleSectionDataStruaxleStcName
* 功能描述： 获取指定IDAxleSectionDataStru的名称
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetAxleSectionDataStruaxleStcName(const UINT16_S indexId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetAxleSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumAxleSection)
    {
        retVal = AxleSectionDataStru[bufIndex].axleStcName;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 函数名称： GetAxleSectionDataStruincludeSegNum
* 功能描述： 获取指定IDAxleSectionDataStru的包含Seg数目
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 包含Seg数目
*/ 
UINT16_S GetAxleSectionDataStruincludeSegNum(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetAxleSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumAxleSection)
    {
        retVal = AxleSectionDataStru[bufIndex].includeSegNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 函数名称： GetAxleSectionDataStrusegIdBuff
* 功能描述： 获取指定IDAxleSectionDataStru的Seg编号
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: Seg编号
*/ 
UINT16_S* GetAxleSectionDataStrusegIdBuff(const UINT16_S indexId)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetAxleSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumAxleSection)
    {
        retVal = AxleSectionDataStru[bufIndex].segIdBuff;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* 函数名称： GetAxleSectionOfSegInfo
* 功能描述： 获取计轴区段包含的SegId的信息
* 输入参数： const UINT16_S AxleSecId,计轴区段ID
* 输出参数： UINT16_S* pSegId，SegID数组
* 返回值  ： 0xffff: 获取数据失败
*            >0:SegId数量
*/
UINT16_S GetAxleSectionOfSegInfo(const UINT16_S AxleSecId,UINT16_S* pSegId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/

    if(NULL != pSegId)
    {
        bufIndex = GetAxleSectionDataStruIndex(AxleSecId);/*获取结构体数组下标*/
        if (bufIndex < LineNumAxleSection)
        {
            MemoryCpy(pSegId,sizeof(UINT16_S)*AXLESECTION_SEG_MAX_NUM,AxleSectionDataStru[bufIndex].segIdBuff,sizeof(UINT16_S)*AXLESECTION_SEG_MAX_NUM);
            retVal =  AxleSectionDataStru[bufIndex].includeSegNum;
        }
        else
        {
            /*Do nothing currently !*/
        }


    }
    return retVal;
}


/*
* 函数名称： GetSegIdBelongofAxleSecId
* 功能描述： 获取SEGID包含的计轴区段ID
* 输入参数： const UINT16_S  segId，SegID
*             const UINT8_S segNum      SEG个数
*             const UINT8_S findNum  需要查找几个
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*            >0:计轴区段ID
*/
UINT16_S GetSegIdBelongofAxleSecId(const UINT16_S* segIdbuff,const UINT8_S segNum,const UINT8_S findNum)
{
    UINT16_S retVal = 0u;

    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j = 0u;/*循环使用*/
    UINT8_S  k = 0u;/*循环使用*/
    UINT8_S tmpFindNum = 0u;/*查找到的个数*/

    if(NULL != segIdbuff)
    {
        for ( i = 0u; i < LineNumAxleSection; i++)
        {
            tmpFindNum = 0u;
            for(j = 0u;j < AxleSectionDataStru[i].includeSegNum;j++)
            {
                if (AxleSectionDataStru[i].includeSegNum == 1u)
                {
                    if ((segIdbuff[0] == AxleSectionDataStru[i].segIdBuff[j]))
                    {
                        tmpFindNum++;
                    }
                }
                else
                {
                    for (k = 0u;k < segNum;k++)
                    {
                        if ((segIdbuff[k] == AxleSectionDataStru[i].segIdBuff[j]))
                        {
                            tmpFindNum++;
                            break;
                        }

                    }
                }
                if (tmpFindNum >= findNum)
                {
                    retVal = AxleSectionDataStru[i].indexId;
                    break;
                }

            }
            if (retVal != 0u)
            {
                break;
            }
        }


    }



    return retVal;
}

/*
* 函数名称： GetSegIdBelongofAxleSecInfo
* 功能描述： 获取SEGID包含的计轴区段结构体指针
* 输入参数： const UINT16_S  segId，SegID
*             const UINT8_S segNum      SEG个数
* 输出参数： 无
* 返回值  ： NULL: 获取数据失败
*             !NULL:计轴区段结构体指针
*/
BnfAxleSectionStruct* GetSegIdBelongofAxleSecInfo(const UINT16_S* segIdbuff,const UINT8_S segNum)
{
    BnfAxleSectionStruct* retVal = NULL;

    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j = 0u;/*循环使用*/
    UINT8_S  k = 0u;/*循环使用*/
    UINT8_S findNum = 0u;/*查找到的个数*/

    if(NULL != segIdbuff)
    {
        for ( i = 0u; i < LineNumAxleSection; i++)
        {
            findNum = 0u;
            for(j = 0u;j < AxleSectionDataStru[i].includeSegNum;j++)
            {
                if (AxleSectionDataStru[i].includeSegNum == 1u)
                {
                    if ((segIdbuff[0] == AxleSectionDataStru[i].segIdBuff[j]))
                    {
                        retVal = &AxleSectionDataStru[i];
                        break;
                    }
                }
                else
                {
                    for (k = 0u;k < segNum;k++)
                    {
                        if ((segIdbuff[k] == AxleSectionDataStru[i].segIdBuff[j]))
                        {
                            findNum++;
                            break;
                        }

                    }
                    if (findNum >= 2u)
                    {
                        retVal = &AxleSectionDataStru[i];
                        break;
                    }
                }

            }
            if (retVal != NULL)
            {
                break;
            }
        }


    }

    return retVal;
}


/*
* 函数名称： GetLineAcMaxId
* 功能描述： 获取线路计轴区段最大ID
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:计轴区段最大ID
*/
UINT16_S GetLineAcMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S axleSecId = 0u;/*计轴区段ID*/
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumAxleSection; i++)
    {
        if (axleSecId < AxleSectionDataStru[i].indexId)
        {
            axleSecId = AxleSectionDataStru[i].indexId;
        }
    }

    if(axleSecId != 0u)
    {
        retVal = axleSecId;
    }

    return retVal;
}

/*
* 函数名称： GetAxleSectionDataStruSegInfo
* 功能描述： 获取指定IDAxleSectionDataStru的Seg信息
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 包含SEG的个数
*/ 
UINT16_S GetAxleSectionDataStruSegInfo(const UINT16_S indexId,UINT16_S* pSegId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;/*数组下标*/

    if(NULL != pSegId)
    {
        bufIndex = GetAxleSectionDataStruIndex(indexId);/*获取结构体数组下标*/
        if (bufIndex < LineNumAxleSection)
        {
            MemoryCpy(pSegId,sizeof(UINT16_S)*AXLESECTION_SEG_MAX_NUM,AxleSectionDataStru[bufIndex].segIdBuff,sizeof(UINT16_S)*AXLESECTION_SEG_MAX_NUM);
            retVal = AxleSectionDataStru[bufIndex].includeSegNum;
        }
        else
        {
            /*Do nothing currently !*/
        }

    }
    return retVal;
}

/*
* 函数名称： GetLineAcBelongCiId
* 功能描述： 获取计轴区段所属CIID
* 输入参数： const UINT16_S acId，计轴区段ID
* 输出参数： 无
* 返回值  ： 0: 获取失败
*             联锁ID
*/
UINT16_S GetLineAcBelongCiId(const UINT16_S acId)
{
    UINT16_S buffIndex = 0u;/*数组下标*/
    UINT16_S ciId = 0u; /*联锁ID*/

    /*获取计轴区段对应的数组下标*/
    buffIndex = GetAxleSectionDataStruIndex(acId);

    /*货物所属CI的ID*/
    if (buffIndex < UINT16_NULL)
    {
        ciId = AxleSectionDataStru[buffIndex].manageCIId;
    }

    return ciId;
}


/*
* 函数名称： GetLineAcBelongZcId
* 功能描述： 获取计轴区段所属ZC
* 输入参数： const UINT16_S acId，计轴区段ID
* 输出参数： 无
* 返回值  ： 0: 获取失败
*            >0:所属ZCID
*/
UINT16_S GetLineAcBelongZcId(const UINT16_S acId)
{
    UINT16_S buffIndex = 0u;/*数组下标*/
    UINT16_S zcId = 0u; /*ZCID*/

    /*获取计轴区段对应的数组下标*/
    buffIndex = GetAxleSectionDataStruIndex(acId);

    /*货物所属CI的ID*/
    if (buffIndex < UINT16_NULL)
    {
        zcId = AxleSectionDataStru[buffIndex].manageZCId;
    }

    return zcId;
}

/*
* 函数名称： GetLineAcIncludeLogicSectionInfo
* 功能描述： 获取计轴区段包含逻辑区段信息
* 输入参数： const UINT16_S acId，计轴区段ID
* 输出参数： UINT8_S *logicSectionNum,逻辑区段数量
*            UINT16_S logicSectionIdBuf[]，逻辑区段ID数组
* 返回值  ： 0: 获取失败
*            1: 获取成功
*/
UINT8_S GetLineAcIncludeLogicSectionInfo(const UINT16_S acId,UINT8_S *logicSectionNum,UINT16_S logicSectionIdBuf[])
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;/*数组下标*/
    bufIndex = GetAxleSectionDataStruIndex(acId);/*获取结构体数组下标*/
    if ((logicSectionIdBuf != NULL)&&(bufIndex < LineNumAxleSection))
    {
        MemoryCpy(logicSectionIdBuf,sizeof(UINT16_S)*AxleSectionDataStru[bufIndex].includeLogicAxleSecNum,AxleSectionDataStru[bufIndex].logicSecId,sizeof(UINT16_S)*AxleSectionDataStru[bufIndex].includeLogicAxleSecNum);
        *logicSectionNum = AxleSectionDataStru[bufIndex].includeLogicAxleSecNum;
        retVal = 1u;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
