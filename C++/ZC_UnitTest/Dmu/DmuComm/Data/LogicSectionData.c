/*************************************************
  文件名   ：LogicSectionData.c
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： LogicSectionData数据管理
			DmuCommonData组件的LogicSectionData功能可分解如下：
			1）	给LogicSectionDataStru结构体指针分配空间
			2）	获取LogicSectionData数据
			3）	获取LogicSectionData信息
			4）	获取指定IDLogicSectionDataStru的结构体下标
			5）	获取指定IDLogicSectionDataStru的结构体指针
			6）	获取指定IDLogicSectionDataStru的名称
			7）	获取指定IDLogicSectionDataStru的起点所处Seg编号
			8）	获取指定IDLogicSectionDataStru的起点所处Seg偏移量
			9）	获取指定IDLogicSectionDataStru的终点所处Seg编号
			10）	获取指定IDLogicSectionDataStru的终点所处Seg偏移量
			11）	获取线路逻辑区段最大ID
			12）	根据输入的SEGID获取逻辑区段的信息
			13）	获取逻辑区段所属ZC
			14）	获取逻辑区段所属CI
			15）	获取逻辑区段所属AC
			16）	查询此SEG前方的逻辑区段
			17）	查询此SEG后方的逻辑区段
			18）	获取逻辑区段ID相关联的逻辑区段ID
  备注    ：无。
 
*************************************************/

#include "LogicSectionData.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/MemSet.h"

static BnfLogicSectionStruct* BnfLogicSectionDataStru = NULL;   /*定义LogicSectionData数据结构体*/
static UINT16_S LineNumLogicSection = 0u;/*表行数*/


/*
* 功能描述： 给LogicSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocLogicSectionDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == BnfLogicSectionDataStru))
    {
        BnfLogicSectionDataStru = (BnfLogicSectionStruct*)MemoryMalloc((UINT32_S)sizeof(BnfLogicSectionStruct) * lineNum);
        if (BnfLogicSectionDataStru != NULL)
        {
            LineNumLogicSection = lineNum;
            /*赋值为无效值*/
            MemorySet(BnfLogicSectionDataStru,lineNum*sizeof(BnfLogicSectionStruct),UINT8_NULL,lineNum*sizeof(BnfLogicSectionStruct));
        }
    }
}

/*
* 功能描述： 获取LogicSectionData数据
* 参数说明：
* 返回值  ： 
            BnfLogicSectionStruct*
*/
BnfLogicSectionStruct *GetLogicSectionData(void)
{
    return BnfLogicSectionDataStru;
}


/*
* 功能描述： 获取LogicSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfLogicSectionStruct*
*/
BnfLogicSectionStruct *GetLogicSectionDataInfo(UINT16_S* lineNum)
{

    BnfLogicSectionStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumLogicSection;
        retVal = BnfLogicSectionDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDLogicSectionDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetLogicSectionDataStruIndex(const UINT16_S indexId)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumLogicSection; i++)
    {
        if (indexId == BnfLogicSectionDataStru[i].indexId)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLogicSectionDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfLogicSectionStruct* GetIndexIdLogicSectionDataStru(const UINT16_S indexId)
{
    BnfLogicSectionStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = &BnfLogicSectionDataStru[bufIndex];
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLogicSectionDataStru的名称
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetLogicSectionDataStruname(const UINT16_S indexId)
{
    UINT8_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].name;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLogicSectionDataStru的起点所处Seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg编号
*/ 
UINT16_S GetLogicSectionDataStrustartSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].startSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLogicSectionDataStru的起点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg偏移量
*/ 
UINT32_S GetLogSecDataStartSegOff(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].startSegOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLogicSectionDataStru的终点所处Seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg编号
*/ 
UINT16_S GetLogicSectionDataStruendSegId(const UINT16_S indexId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].endSegId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDLogicSectionDataStru的终点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg偏移量
*/ 
UINT32_S GetLogicSectionDataStruendSegOffset(const UINT16_S indexId)
{
    UINT32_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(indexId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].endSegOffset;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}


/*
* 功能描述： 获取线路逻辑区段最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:逻辑区段最大ID
*/
UINT16_S GetLineLogicSectionMaxId(void)
{
    UINT16_S retVal = UINT16_NULL;
    UINT16_S logicSecId = 0u;/*逻辑区段ID*/
    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumLogicSection; i++)
    {
        if (logicSecId < BnfLogicSectionDataStru[i].indexId)
        {
            logicSecId = BnfLogicSectionDataStru[i].indexId;
        }
    }

    if(logicSecId != 0u)
    {
        retVal = logicSecId;
    }

    return retVal;
}


/*
* 功能描述： 根据输入的SEGID获取逻辑区段的信息
* 参数说明： const UINT16_S* pSegId;SEGID指针指针
             const UINT16_S segIdNum;SEGID个数
             UINT16_S logicSectionIdBuf[];逻辑区段ID数组
* 返回值  :  0: 获取数据失败
*            >0: 逻辑区段个数
*/ 
UINT8_S GetSegIdBuffOfLogSecInfo(const UINT16_S* pSegId,const UINT16_S segIdNum,UINT16_S logicSectionIdBuf[])
{
    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j = 0u;/*循环使用*/
    
    UINT8_S logicSecIdNum = 0u;/*逻辑区段个数*/
        
    if((NULL != pSegId) && (NULL != logicSectionIdBuf))
    {
        for ( i = 0u; i < LineNumLogicSection; i++)
        {
            for (j = 0u;j < segIdNum; j++)
            {
                if (BnfLogicSectionDataStru[i].startSegId == pSegId[j])
                {
                    logicSectionIdBuf[logicSecIdNum] = BnfLogicSectionDataStru[i].indexId;
                    logicSecIdNum=logicSecIdNum+1;
                    break;
                }
            }

        }
    }
    return logicSecIdNum;
}

/*
* 功能描述： 获取逻辑区段所属ZC
* 参数说明： const UINT16_S logicSectionId，逻辑区段ID
* 返回值  ： 0: 获取失败
*            >0:所属ZCID
*/
UINT16_S GetLineLogicSectionBelongZcId(const UINT16_S logicSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(logicSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].manageZCId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取逻辑区段所属CI
* 参数说明： const UINT16_S logicSectionId，逻辑区段ID
* 返回值  ： 0: 获取失败
*            >0:所属CIID
*/
UINT16_S GetLineLogicSectionBelongCiId(const UINT16_S logicSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(logicSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].manageCIId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 获取逻辑区段所属AC
* 参数说明： const UINT16_S logicSectionId，逻辑区段ID
* 返回值  ： 0: 获取失败
*            >0:所属ACID
*/
UINT16_S GetLineLogicSectionBelongAcId(const UINT16_S logicSectionId)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetLogicSectionDataStruIndex(logicSectionId);/*获取结构体数组下标*/
    if (bufIndex < LineNumLogicSection)
    {
        retVal = BnfLogicSectionDataStru[bufIndex].belongAxleSecId;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
* 功能描述： 查询此SEG前方的逻辑区段
*            (1)若有一个逻辑区段直接返回
*            (2)若有多个，返回逻辑区段偏移量最大的
*            (3)若此SEG包含在两个逻辑区段中，则根据输出两个逻辑区段ID
* 参数说明： const UINT16_S startSegId,const UINT32_S startOffset,const UINT32_S endOffset
             UINT16_S logicSectionIdBuf[];逻辑区段ID数组
* 返回值  :  0: 失败
*             1: 成功
*/ 
UINT8_S GetSegFontSecOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startSegLen,UINT16_S* mainLogicId,UINT16_S* sideLogicId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/
    UINT32_S endSegOffSet = 0u;/*查询到的SEG偏移量*/
    UINT8_S findNum = 0u;/*查询到的次数*/

    if((NULL != mainLogicId) && (NULL != sideLogicId))
    {
        *mainLogicId = UINT16_NULL;
        *sideLogicId = UINT16_NULL;
        for ( i = 0u; i < LineNumLogicSection; i++)
        {
            if (BnfLogicSectionDataStru[i].includeSegIdNum == 1u)
            {
                if (BnfLogicSectionDataStru[i].startSegId == startSegId)
                {
                    if ((BnfLogicSectionDataStru[i].startSegOffset == 0u)&&(BnfLogicSectionDataStru[i].endSegOffset == startSegLen))
                    {
                        findNum = 1u;
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                        break;
                    }
                    else
                    {
                        if (BnfLogicSectionDataStru[i].endSegOffset > endSegOffSet)
                        {
                            endSegOffSet = BnfLogicSectionDataStru[i].endSegOffset;
                            findNum = 1u;
                            *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                        }
                    }
                }
            }
            else
            {
                if (BnfLogicSectionDataStru[i].startSegId == startSegId)
                {
                    findNum += 1u;
                    if (BnfLogicSectionDataStru[i].switchIdStru[0].switchStatus == SWITCH_STATUS_SAME)
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else if (BnfLogicSectionDataStru[i].switchIdStru[0].switchStatus == SWITCH_STATUS_CONTRA)
                    {
                        *sideLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }

                    if (2u == findNum)
                    {
                        if ((*mainLogicId != UINT16_NULL)&&(*sideLogicId != UINT16_NULL))
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            findNum = 0u;
                        }
                        break;
                    }
                }
                else if(BnfLogicSectionDataStru[i].endSegId == startSegId)
                {
                    findNum += 1u;
                    if (BnfLogicSectionDataStru[i].switchIdStru[BnfLogicSectionDataStru[i].switchIdNum -1].switchStatus == SWITCH_STATUS_SAME)
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else if (BnfLogicSectionDataStru[i].switchIdStru[BnfLogicSectionDataStru[i].switchIdNum -1].switchStatus == SWITCH_STATUS_CONTRA)
                    {
                        *sideLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }

                    if (2u == findNum)
                    {
                        if ((*mainLogicId != UINT16_NULL)&&(*sideLogicId != UINT16_NULL))
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            findNum = 0u;
                        }
                        break;
                    }
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
        }

        if (findNum > 0u)
        {
            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }



    }

    return retVal;
}

/*
* 功能描述： 查询此SEG后方的逻辑区段
*            (1)若有一个逻辑区段直接返回
*            (2)若有多个，返回逻辑区段偏移量最大的
*            (3)若此SEG包含在两个逻辑区段中，则根据输出两个逻辑区段ID
* 参数说明： const UINT16_S startSegId,const UINT32_S startOffset,const UINT32_S endOffset
             UINT16_S logicSectionIdBuf[];逻辑区段ID数组
* 返回值  :  0: 失败
*             1: 成功
*/ 
UINT8_S GetSegRearSecOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startSegLen,UINT16_S* mainLogicId,UINT16_S* sideLogicId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/
    UINT32_S startSegOffSet = 0u;/*查询到的SEG偏移量*/
    UINT8_S findNum = 0u;/*查询到的次数*/

    if((NULL != mainLogicId) && (NULL != sideLogicId))
    {
        *mainLogicId = UINT16_NULL;
        *sideLogicId = UINT16_NULL;

        for ( i = 0u; i < LineNumLogicSection; i++)
        {
            if (BnfLogicSectionDataStru[i].includeSegIdNum == 1u)
            {
                if (BnfLogicSectionDataStru[i].startSegId == startSegId)
                {
                    if ((BnfLogicSectionDataStru[i].startSegOffset == 0u)&&(BnfLogicSectionDataStru[i].endSegOffset == startSegLen))
                    {
                        findNum = 1u;
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                        break;
                    }
                    else
                    {
                        findNum += 1u;
                        if (findNum == 1u)
                        {
                            startSegOffSet = BnfLogicSectionDataStru[i].startSegOffset;
                            *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                        }
                        else
                        {
                            if (BnfLogicSectionDataStru[i].startSegOffset < startSegOffSet)
                            {
                                startSegOffSet = BnfLogicSectionDataStru[i].startSegOffset;
                                *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                            }
                        }
                    }
                }
            }
            else
            {
                if (BnfLogicSectionDataStru[i].startSegId == startSegId)
                {
                    findNum += 1u;
                    if (BnfLogicSectionDataStru[i].switchIdStru[0].switchStatus == SWITCH_STATUS_SAME)
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else if (BnfLogicSectionDataStru[i].switchIdStru[0].switchStatus == SWITCH_STATUS_CONTRA)
                    {
                        *sideLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }

                    if (2u == findNum)
                    {
                        if ((*mainLogicId != UINT16_NULL)&&(*sideLogicId != UINT16_NULL))
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            findNum = 0u;
                        }
                        break;
                    }
                }
                else if(BnfLogicSectionDataStru[i].endSegId == startSegId)
                {
                    findNum += 1u;
                    if (BnfLogicSectionDataStru[i].switchIdStru[BnfLogicSectionDataStru[i].switchIdNum -1].switchStatus == SWITCH_STATUS_SAME)
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else if (BnfLogicSectionDataStru[i].switchIdStru[BnfLogicSectionDataStru[i].switchIdNum -1].switchStatus == SWITCH_STATUS_CONTRA)
                    {
                        *sideLogicId = BnfLogicSectionDataStru[i].indexId;
                    }
                    else
                    {
                        *mainLogicId = BnfLogicSectionDataStru[i].indexId;
                    }

                    if (2u == findNum)
                    {
                        if ((*mainLogicId != UINT16_NULL)&&(*sideLogicId != UINT16_NULL))
                        {
                            /*Do nothing currently !*/
                        }
                        else
                        {
                            findNum = 0u;
                        }
                        break;
                    }
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
        }

        if (findNum > 0u)
        {
            retVal = 1u;
        }
        else
        {
            retVal = 0u;
        }

    }

    return retVal;
}

/*
* 功能描述： 获取逻辑区段ID相关联的逻辑区段ID
* 参数说明： const UINT16_S logicSectionId，逻辑区段ID
* 返回值  ： UINT16_NULL: 查询失败
*            >0: 关联的逻辑区段ID
*/
UINT8_S GetLineLogicSectionBelongRelareLc(const UINT16_S logicSectionId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct* relateLogicInfo)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    UINT16_S j = 0u;/*循环使用*/
    UINT8_S i = 0u;/*循环使用*/
    UINT8_S k = 0u;/*循环使用*/
    UINT8_S findFlag = 0u;/*是否查找到*/
    UINT8_S findNum = 0u;/*需要查找到的个数*/

    if((NULL != relateLogicNum) && (NULL != relateLogicInfo))
    {
        *relateLogicNum = 0u;
        bufIndex = GetLogicSectionDataStruIndex(logicSectionId);/*获取结构体数组下标*/
        if ((bufIndex < LineNumLogicSection)&&(NULL != relateLogicInfo))
        {
            for (j = 0u;j < LineNumLogicSection;j++)
            {
                if(BnfLogicSectionDataStru[j].indexId != logicSectionId)
                {
                    findFlag = 0u;
                    if (BnfLogicSectionDataStru[j].includeSegIdNum > 1u)
                    {
                        for(i = 0u;i < BnfLogicSectionDataStru[j].includeSegIdNum;i++)
                        {
                            for (k = 0u;k < BnfLogicSectionDataStru[bufIndex].includeSegIdNum;k++)
                            {
                                if (BnfLogicSectionDataStru[j].segIdBuff[i] == BnfLogicSectionDataStru[bufIndex].segIdBuff[k])
                                {
                                    if (BnfLogicSectionDataStru[j].segIdBuff[i] == BnfLogicSectionDataStru[j].startSegId)
                                    {
                                        relateLogicInfo[*relateLogicNum].pointFalg = START_POINT;
                                    }
                                    else if (BnfLogicSectionDataStru[j].segIdBuff[i] == BnfLogicSectionDataStru[j].endSegId)
                                    {
                                        relateLogicInfo[*relateLogicNum].pointFalg = END_POINT;
                                    }
                                    else
                                    {
                                        /*Do nothing currently !*/
                                    }
                                    relateLogicInfo[*relateLogicNum].relateLogicId = BnfLogicSectionDataStru[j].indexId;
                                    relateLogicInfo[*relateLogicNum].relateSegId = BnfLogicSectionDataStru[j].segIdBuff[i];
                                    (*relateLogicNum)++;
                                    findFlag = 1u;
                                    findNum += 1u;
                                    break;
                                }
                            }

                            if (1u == findFlag)
                            {
                                break;
                            }
                        }

                        if (findNum == (BnfLogicSectionDataStru[j].includeSegIdNum -1u))
                        {
                            break;
                        }
                    }
                }
            }

            retVal = 1u;
        }
        else
        {
            /*Do nothing currently !*/
        }

    }

    return retVal;
}
