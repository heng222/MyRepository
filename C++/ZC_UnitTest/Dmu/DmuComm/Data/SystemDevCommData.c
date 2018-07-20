/*************************************************
  文件名   ：SystemDevCommData.c
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SystemDevCommData数据管理
			DmuCommonData组件的SystemDevCommData功能可分解如下：
			1）	给SystemDevCommDataStru结构体指针分配空间
			2）	获取SystemDevCommData数据
			3）	获取SystemDevCommData信息
			4）	获取指定IDSystemDevCommDataStru的结构体下标
			5）	获取指定IDSystemDevCommDataStru的结构体指针
			6）	获取指定IDSystemDevCommDataStru的通信对象数量
			7）	获取指定IDSystemDevCommDataStru的通信对象编号(Device_Type+Device_ID)
			8）	获取指定IDSystemDevCommDataStru的通信对象信息

  备注    ：无。 
*************************************************/

#include "SystemDevCommData.h"
#include "../../../Common/Malloc.h"
#include "../../../Common/Copy.h"

static BnfSystemDevCommStruct* SystemDevCommDataStru = NULL;   /*定义SystemDevCommData数据结构体*/
static UINT16_S LineNumSystemDevComm = 0u;/*表行数*/


/*
* 功能描述： 给SystemDevCommDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSystemDevCommDataStru(UINT16_S lineNum)
{
    if ((lineNum > 0u)&&(NULL == SystemDevCommDataStru))
    {
        SystemDevCommDataStru = (BnfSystemDevCommStruct*)MemoryMalloc((UINT32_S)sizeof(BnfSystemDevCommStruct) * lineNum);
        LineNumSystemDevComm = lineNum;
    }
}

/*
* 功能描述： 获取SystemDevCommData数据
* 参数说明：
* 返回值  ： 
BnfSystemDevCommStruct*
*/
BnfSystemDevCommStruct *GetSystemDevCommData(void)
{
    return SystemDevCommDataStru;
}


/*
* 功能描述： 获取SystemDevCommData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfSystemDevCommStruct*
*/
BnfSystemDevCommStruct *GetSystemDevCommDataInfo(UINT16_S* lineNum)
{

    BnfSystemDevCommStruct * retVal = NULL;

    if(NULL != lineNum)
    {
        *lineNum = LineNumSystemDevComm;
        retVal = SystemDevCommDataStru;
    }
    else
    {
        retVal = NULL;
    }
    return retVal;
}
/*
** 功能描述： 获取指定IDSystemDevCommDataStru的结构体下标
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSystemDevCommDataStruIndex(const UINT16_S devName)
{
    UINT16_S retVal = 0xFFFFu;/*函数返回值*/

    UINT16_S i = 0u;/*循环使用*/

    for ( i = 0u; i < LineNumSystemDevComm; i++)
    {
        if (devName == SystemDevCommDataStru[i].devName)
        {
            retVal = i;
            break;
        }
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSystemDevCommDataStru的结构体指针
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSystemDevCommStruct* GetIndexIdSystemDevCommDataStru(const UINT16_S devName)
{
    BnfSystemDevCommStruct* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSystemDevCommDataStruIndex(devName);/*获取结构体数组下标*/
    if (bufIndex < LineNumSystemDevComm)
    {
        retVal = &SystemDevCommDataStru[bufIndex];
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSystemDevCommDataStru的通信对象数量
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 返回值  :  0: 获取数据失败
*            >0: 通信对象数量
*/ 
UINT16_S GetSystemDevCommDataStrucommObjectNum(const UINT16_S devName)
{
    UINT16_S retVal = 0u;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSystemDevCommDataStruIndex(devName);/*获取结构体数组下标*/
    if (bufIndex < LineNumSystemDevComm)
    {
        retVal = SystemDevCommDataStru[bufIndex].commObjectNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSystemDevCommDataStru的通信对象编号(Device_Type+Device_ID)
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 返回值  :  NULL: 获取数据失败
*            !NULL: 通信对象编号(Device_Type+Device_ID)
*/ 
UINT16_S* GetSysDevComDataComObjIdBuf(const UINT16_S devName)
{
    UINT16_S* retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSystemDevCommDataStruIndex(devName);/*获取结构体数组下标*/
    if (bufIndex < LineNumSystemDevComm)
    {
        retVal = SystemDevCommDataStru[bufIndex].commObjectIdBuff;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
** 功能描述： 获取指定IDSystemDevCommDataStru的通信对象信息
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 输出参数:     UINT16_S* pCommObjectId   通信对象编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 通信对象编号(Device_Type+Device_ID)
*/ 
UINT16_S GetSysDevComDataComObjInfo(const UINT16_S devName,UINT16_S* pCommObjectId)
{
    UINT16_S retVal = NULL;/*函数返回值*/
    UINT16_S bufIndex = 0u;  /*数组下标*/
    bufIndex = GetSystemDevCommDataStruIndex(devName);/*获取结构体数组下标*/

    if ((pCommObjectId != NULL)&&(bufIndex < LineNumSystemDevComm))
    {
        MemoryCpy(pCommObjectId,sizeof(UINT16_S)*SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM,SystemDevCommDataStru[bufIndex].commObjectIdBuff,sizeof(UINT16_S)*SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM);
        retVal = SystemDevCommDataStru[bufIndex].commObjectNum;
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}
