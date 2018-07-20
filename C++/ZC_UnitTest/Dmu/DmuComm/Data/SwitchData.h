/*************************************************
  文件名   ：SwitchData.h
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
#ifndef SWITCH_DATA_H_
#define SWITCH_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SWITCH_NAME_LEN                      16                                /*道岔名称字节数*/
#define SWITCH_LINE_BYTE_NUM                 30                                /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*道岔数据结构体*/
typedef struct BnfSwitchStruct
{
    UINT16_S switchId;                        /*道岔编号*/
    UINT8_S  switchName [SWITCH_NAME_LEN];    /*道岔名称*/
    UINT16_S switchOtherId;                   /*联动道岔编号*/
    UINT16_S dir;                                /*方向*/
    UINT16_S locSegId;                        /*定位SegID*/
    UINT16_S antiSegId;                        /*反位SegID*/
    UINT16_S joinSegId;                        /*汇合SegID*/
    UINT16_S switchSideResSpeed;                /*道岔反位静态限制速度(cm/s)*/

    /*动态计算字段*/
    UINT32_S    locSegOffset;                    /*定位道岔的偏移量*/
    UINT32_S    antiSegOffset;                    /*反位道岔的偏移量*/
    UINT32_S    joinSegOffset;                    /*汇合道岔的偏移量*/
    UINT16_S  manageZCId;                        /*所属ZC区域ID*/
    UINT16_S  manageCIId;                        /*所属CI区域ID*/ 
}BnfSwitchStruct;    

/*
* 功能描述： 给SwitchDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSwitchDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取SwitchData数据
* 参数说明：
* 返回值  ： 
            BnfSwitchStruct*
*/
BnfSwitchStruct *GetSwitchData(void);

/*
* 功能描述： 获取SwitchData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSwitchStruct*
*/
BnfSwitchStruct *GetSwitchDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDSwitchDataStru的结构体下标
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSwitchDataStruIndex(const UINT16_S switchId);

/*
** 功能描述： 获取指定IDSwitchDataStru的结构体指针
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSwitchStruct* GetIndexIdSwitchDataStru(const UINT16_S switchId);

/*
** 功能描述： 获取指定IDSwitchDataStru的道岔名称
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 道岔名称
*/ 
UINT8_S* GetSwitchDataStruswitchName(const UINT16_S switchId);

/*
** 功能描述： 获取指定IDSwitchDataStru的联动道岔编号
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 联动道岔编号
*/ 
UINT16_S GetSwitchDataStruswitchOtherId(const UINT16_S switchId);

/*
** 功能描述： 获取指定IDSwitchDataStru的方向
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 方向
*/ 
UINT16_S GetSwitchDataStrudir(const UINT16_S switchId);

/*
** 功能描述： 获取指定IDSwitchDataStru的定位SegID
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 定位SegID
*/ 
UINT16_S GetSwitchDataStrulocSegId(const UINT16_S switchId);

/*
** 功能描述： 获取指定IDSwitchDataStru的反位SegID
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 反位SegID
*/ 
UINT16_S GetSwitchDataStruantiSegId(const UINT16_S switchId);

/*
** 功能描述： 获取指定IDSwitchDataStru的所有SegID
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*             1: 获取数据成功
*/ 
UINT8_S GetSwitchDataStruSegIdInfo(const UINT16_S switchId,UINT16_S* locSegId,UINT16_S* antiSegId,UINT16_S* joinSegId);

/*
** 功能描述： 获取指定IDSwitchDataStru的道岔反位静态限制速度(cm/s)
* 参数说明： const UINT16_S switchId;道岔编号
* 返回值  :  0: 获取数据失败
*            >0: 道岔反位静态限制速度(cm/s)
*/ 
UINT16_S GetSwitchDataStruswitchSideResSpeed(const UINT16_S switchId);

/*
** 功能描述： 根据输入的SEGID获取道岔的数量
* 参数说明： const UINT16_S* pSegId;SEGID指针指针
             const UINT16_S segIdNum;SEGID个数
* 返回值  :  0: 获取数据失败
*            >0: 道岔个数
*/ 
UINT16_S GetSegIdOfSwitchIdNum(const UINT16_S* pSegId,const UINT16_S segIdNum);

/*
* 功能描述： 获取线路道岔最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:道岔最大ID
*/
UINT16_S GetLineSwitchMaxId(void);

/*
** 功能描述： 根据输入的SEGID获取道岔信息
* 参数说明： 输入:const UINT16_S segId,SEGID
*             const UINT8_S segIdNum    SEGID个数
*             UINT16_S index    数组偏移                  
*             输入输出:UINT16_S switchIdBuff[],道岔ID数组      
* 返回值  :  0: 获取数据失败
*            >0: 道岔个数
*/ 
UINT16_S GetSegIdBelongofSwitchInfo(const UINT16_S* segIdBuff,const UINT8_S segIdNum,UINT16_S index,UINT16_S switchIdBuff[]);

/*
** 功能描述： 根据输入的SEGID获取道岔的数量
* 参数说明： const UINT16_S* pSegId;SEGID指针指针
             const UINT16_S segIdNum;SEGID个数
* 返回值  :  0: 获取数据失败
*            >0: 道岔个数
*/ 
UINT8_S GetSegIdBuffOfSwitchInfo(const UINT16_S* pSegId,const UINT16_S segIdNum,UINT16_S switchIdBuff[]);

/*
* 功能描述： 获取线路道岔所属ZC
* 参数说明： const UINT16_S switchId,道岔ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLineSwitchBelongZcId(const UINT16_S switchId);

/*
* 功能描述： 获取线路道岔所属CI
* 参数说明： const UINT16_S switchId,道岔ID
* 返回值  ： 0: 获取数据失败
*            >0:所属CIId
*/
UINT16_S GetLineSwitchBelongCiId(const UINT16_S switchId);

#ifdef __cplusplus
}
#endif

#endif
