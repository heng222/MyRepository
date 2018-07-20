/*************************************************
  文件名   ：CommFailTimeData.h
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
#ifndef COMMFAILTIME_DATA_H_
#define COMMFAILTIME_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  COMMFAILTIME_LINE_BYTE_NUM                    60                            /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*通信故障配置表数据结构体*/
typedef struct BnfCommFailTimeStruct
{
    UINT32_S  atpToZcCommFailTime;                       /*ATP至ZC通信故障时间(ms)*/
    UINT32_S  zcToAtpCommFailTime;                       /*ZC至ATP通信故障时间*/
    UINT32_S  atpToCiCommFailTime;                       /*ATP至CI通信故障时间(ms)*/
    UINT32_S  ciToAtpCommFailTime;                       /*CI至ATP通信故障时间(ms)*/
    UINT32_S  atpToAtsCommFailTime;                       /*ATP至ATS通信故障时间(ms)*/
    UINT32_S  atsToAtpCommFailTime;                       /*ATS至ATP通信故障时间(ms)*/
    UINT32_S  zcToDmsCommFailTime;                       /*ZC至DMS通信故障时间(ms)*/
    UINT32_S  dmsToZcCommFailTime;                       /*DMS至ZC通信故障时间(ms)*/
    UINT32_S  zcToCiCommFailTime;                           /*ZC至CI通信故障时间(ms)*/
    UINT32_S  ciToZcCommFailTime;                           /*CI至ZC通信故障时间(ms)*/
    UINT32_S  dmsToAtsCommFailTime;                       /*DMS至ATS通信故障时间(ms)*/
    UINT32_S  atsToDmsCommFailTime;                       /*ATS至DMS通信故障时间(ms)*/
    UINT32_S  zcToAtsCommFailTime;                       /*ZC至ATS通信故障时间(ms)*/
    UINT32_S  zcToZcCommFailTime;                           /*ZC至ZC通信故障时间(ms)*/
    UINT32_S  ciToCiCommFailTime;                           /*CI至CI通信故障时间(ms)*/
}BnfCommFailTimeStruct;

/*
* 功能描述： 给CommFailTimeDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocCommFailTimeDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取CommFailTimeData数据
* 参数说明：
* 返回值  ： 
            BnfCommFailTimeStruct*
*/
BnfCommFailTimeStruct *GetCommFailTimeData(void);

/*
* 功能描述： 获取CommFailTimeData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfCommFailTimeStruct*
*/
BnfCommFailTimeStruct *GetCommFailTimeDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATP至ZC通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATP至ZC通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToZcCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至ATP通信故障时间
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至ATP通信故障时间
*/ 
UINT32_S GetCommFailTimeDataStruZcToAtpCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATP至CI通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATP至CI通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToCiCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的CI至ATP通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: CI至ATP通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToAtpCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATP至ATS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATP至ATS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtpToAtsCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATS至ATP通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATS至ATP通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtsToAtpCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至DMS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至DMS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToDmsCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的DMS至ZC通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: DMS至ZC通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruDmsToZcCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至CI通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至CI通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToCiCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的CI至ZC通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: CI至ZC通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToZcCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的DMS至ATS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: DMS至ATS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruDmsToAtsCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ATS至DMS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ATS至DMS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruAtsToDmsCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至ATS通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至ATS通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToAtsCommFailTime(void);


/*
** 功能描述： 获取指定IDCommFailTimeDataStru的ZC至ZC通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: ZC至ZC通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruZcToZcCommFailTime(void);

/*
** 功能描述： 获取指定IDCommFailTimeDataStru的CI至CI通信故障时间(ms)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*            <UINT32_NULL: CI至CI通信故障时间(ms)
*/ 
UINT32_S GetCommFailTimeDataStruCiToCiCommFailTime(void);


#ifdef __cplusplus
}
#endif

#endif
