/*************************************************
  文件名   ：SystemDevCommData.h
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
#ifndef SYSTEMDEVCOMM_DATA_H_
#define SYSTEMDEVCOMM_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM          15                                            /*通信对象最大个数*/
#define  SYSTEMDEVCOMM_LINE_BYTE_NUM              34                                            /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*设备通信关系表数据结构体*/
typedef struct BnfSystemDevCommStruct
{
    UINT16_S  devName;                                                    /*本设备编号(Device_Type+Device_ID)*/    
    UINT16_S  commObjectNum;                                                /*通信对象数量*/
    UINT16_S  commObjectIdBuff[SYSTEMDEVCOMM_COMMOBJECT_MAX_NUM];            /*通信对象编号(Device_Type+Device_ID)*/
}BnfSystemDevCommStruct;

/*
* 功能描述： 给SystemDevCommDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSystemDevCommDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取SystemDevCommData数据
* 参数说明：
* 返回值  ： 
            BnfSystemDevCommStruct*
*/
BnfSystemDevCommStruct *GetSystemDevCommData(void);

/*
* 功能描述： 获取SystemDevCommData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSystemDevCommStruct*
*/
BnfSystemDevCommStruct *GetSystemDevCommDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDSystemDevCommDataStru的结构体下标
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSystemDevCommDataStruIndex(const UINT16_S devName);

/*
** 功能描述： 获取指定IDSystemDevCommDataStru的结构体指针
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSystemDevCommStruct* GetIndexIdSystemDevCommDataStru(const UINT16_S devName);

/*
** 功能描述： 获取指定IDSystemDevCommDataStru的通信对象数量
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 返回值  :  0: 获取数据失败
*            >0: 通信对象数量
*/ 
UINT16_S GetSystemDevCommDataStrucommObjectNum(const UINT16_S devName);

/*
** 功能描述： 获取指定IDSystemDevCommDataStru的通信对象编号(Device_Type+Device_ID)
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 返回值  :  NULL: 获取数据失败
*            !NULL: 通信对象编号(Device_Type+Device_ID)
*/ 
UINT16_S* GetSysDevComDataComObjIdBuf(const UINT16_S devName);

/*
** 功能描述： 获取指定IDSystemDevCommDataStru的通信对象信息
* 参数说明： const UINT16_S devName;本设备编号(Device_Type+Device_ID)
* 输出参数:     UINT16_S* pCommObjectId   通信对象编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 通信对象编号(Device_Type+Device_ID)
*/ 
UINT16_S GetSysDevComDataComObjInfo(const UINT16_S devName,UINT16_S* pCommObjectId);

#ifdef __cplusplus
}
#endif

#endif
