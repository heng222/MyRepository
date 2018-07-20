/*************************************************
  文件名   ：CommFailTimeData.C
  作者     ：董欣      
  创建时间 ：2016-8-11
  功能描述 ： CommFailTimeData数据管理
			DmuCommonData组件的CommFailTimeData功能可分解如下：
			1）	给CommFailTimeDataStru结构体指针分配空间
			2）	获取CommFailTimeData数据
			3）	获取CommFailTimeData信息
			4）	获取指定IDCommFailTimeDataStru的ATP至ZC通信故障时间(ms)
			5）	获取指定IDCommFailTimeDataStru的ZC至ATP通信故障时间
			6）	获取指定IDCommFailTimeDataStru的ATP至CI通信故障时间(ms)
			7）	获取指定IDCommFailTimeDataStru的CI至ATP通信故障时间(ms)
			8）	获取指定IDCommFailTimeDataStru的ATP至ATS通信故障时间(ms)
			9）	获取指定IDCommFailTimeDataStru的ATS至ATP通信故障时间(ms)
			10）	获取指定IDCommFailTimeDataStru的DMS至ZC通信故障时间(ms)
			11）	获取指定IDCommFailTimeDataStru的ZC至CI通信故障时间(ms)
			12）	获取指定IDCommFailTimeDataStru的CI至ZC通信故障时间(ms)
			13）	获取指定IDCommFailTimeDataStru的DMS至ATS通信故障时间(ms)
			14）	获取指定IDCommFailTimeDataStru的ATS至DMS通信故障时间(ms)
			15）	获取指定IDCommFailTimeDataStru的ZC至ATS通信故障时间(ms)
			16）	获取指定IDCommFailTimeDataStru的ZC至ZC通信故障时间(ms)
			17）	获取指定IDCommFailTimeDataStru的CI至CI通信故障时间(ms)

  备注    ：无。
 
*************************************************/

#include "CommFailTimeData.h"
#include "../../../Common/Malloc.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

static BnfCommFailTimeStruct* CommFailTimeDataStru = NULL;   /*定义CommFailTimeData数据结构体*/
static UINT16_S LineNumCommFailTime = 0u;/*表行数*/


/*
* 功能描述： 给CommFailTimeDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocCommFailTimeDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == CommFailTimeDataStru))
    {
        CommFailTimeDataStru = (BnfCommFailTimeStruct*)MemoryMalloc((UINT32_S)sizeof(BnfCommFailTimeStruct) * lineNum);
        LineNumCommFailTime = lineNum;
    }
}

/*
* 功能描述： 获取CommFailTimeData数据
* 参数说明：
* 返回值  ： 
            BnfCommFailTimeStruct*
*/
BnfCommFailTimeStruct *GetCommFailTimeData(void)
{
    return CommFailTimeDataStru;
}


/*
* 功能描述： 获取CommFailTimeData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfCommFailTimeStruct*
*/
BnfCommFailTimeStruct *GetCommFailTimeDataInfo(UINT16_S* lineNum)
{

    BnfCommFailTimeStruct * retVal = NULL;
    if(NULL == lineNum)
    {
        retVal = NULL;
    }
    else
    {
        *lineNum = LineNumCommFailTime;
        retVal =  CommFailTimeDataStru;

    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATP至ZC通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATP至ZC通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToZcCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atpToZcCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至ATP通信故障时间
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至ATP通信故障时间
*/ 
UINT32_S GetCommFailTimeDataStruZcToAtpCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToAtpCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATP至CI通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATP至CI通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToCiCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atpToCiCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的CI至ATP通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: CI至ATP通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToAtpCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].ciToAtpCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATP至ATS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATP至ATS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToAtsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atpToAtsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATS至ATP通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATS至ATP通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtsToAtpCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atsToAtpCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至DMS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至DMS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToDmsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToDmsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的DMS至ZC通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: DMS至ZC通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruDmsToZcCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].dmsToZcCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至CI通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至CI通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToCiCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToCiCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的CI至ZC通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: CI至ZC通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToZcCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].ciToZcCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的DMS至ATS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: DMS至ATS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruDmsToAtsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].dmsToAtsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATS至DMS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATS至DMS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtsToDmsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].atsToDmsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至ATS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至ATS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToAtsCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToAtsCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至ZC通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至ZC通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToZcCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].zcToZcCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的CI至CI通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: CI至CI通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToCiCommFailTime(void)
{
    UINT32_S retVal = UINT32_NULL;/*函数返回值*/
    if (NULL != CommFailTimeDataStru)
    {
        retVal = CommFailTimeDataStru[0].ciToCiCommFailTime;
    }
    else
    {
/*Do nothing currently !*/
    }
    return retVal;
}

