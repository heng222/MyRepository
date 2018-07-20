/*************************************************
  文件名   ：SegData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SegData数据管理
			DmuCommonData组件的SegData功能可分解如下：
			1）	给SegDataStru结构体指针分配空间
			2）	获取SEG表的行数
			3）	获取SegData数据
			4）	获取SegData信息
			5）	获取指定IDSegDataStru的结构体下标
			6）	获取指定IDSegDataStru的结构体指针
			7）	 获取指定IDSegDataStru的长度（cm)
			8）	获取指定IDSegDataStru的起点端点类型
			9）	获取指定IDSegDataStru的起点端点编号
			10）	获取指定IDSegDataStru的终点端点类型
			11）	获取指定IDSegDataStru的终点端点编号
			12）	获取指定IDSegDataStru的起点正向相邻SegID
			13）	获取指定IDSegDataStru的起点侧向相邻点SegID
			14）	获取指定IDSegDataStru的终点正向相邻点SegID
			15）	获取指定IDSegDataStru的终点侧向相邻点SegID
			16）	获取指定IDSegDataStru的所属ZC区域ID
			17）	获取指定IDSegDataStru的所属ATS区域ID
			18）	获取指定IDSegDataStru的所属CI区域ID
			19）	获取指定IDSegDataStru的终点端点编号和终点端点类型
			20）	获取指定IDSegDataStru的起点端点编号和起点端点类型
			21）	获取指定点指定位置的SEG信息
			22）	获取指定CIID获取ZCID
  备注    ：无。
 
*************************************************/
#ifndef SEG_DATA_H_
#define SEG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SEG_LINE_BYTE_NUM                 30                           /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*Seg表数据结构体*/
typedef struct BnfSegStruct
{
    UINT16_S  segId;                        /*索引编号*/
    UINT32_S     length;                        /*长度（cm)*/
    UINT16_S  startPointType;                /*起点端点类型*/
    UINT16_S  startPointId;                /*起点端点编号*/
    UINT16_S  endPointType;                /*终点端点类型*/
    UINT16_S  endPointId;                    /*终点端点编号*/
    UINT16_S  segStartJointMainSegId;        /*起点正向相邻SegID*/
    UINT16_S  segStartJointSideSegId;        /*起点侧向相邻点SegID*/
    UINT16_S  segTmnlJointMainSegId;        /*终点正向相邻点SegID*/
    UINT16_S  segTmnlJointSideSegId;        /*终点侧向相邻点SegID*/
    UINT16_S  segManageZCId;                /*所属ZC区域ID*/
    UINT16_S  segManageATSId;                /*所属ATS区域ID*/
    UINT16_S  segManageCIId;                /*所属CI区域ID*/ 
    UINT8_S    segResSpeed;                /*SEG限速信息属性*/
    UINT8_S    grade;                        /*SEG坡度信息属性*/
}BnfSegStruct;

/*
* 功能描述： 给SegDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSegDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取SegData数据
* 参数说明：
* 返回值  ： 
            BnfSegStruct*
*/
BnfSegStruct *GetSegData(void);

/*获取SEG表的行数*/
UINT16_S GetSegIdNum(void);
/*
* 功能描述： 获取SegData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSegStruct*
*/
BnfSegStruct *GetSegDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDSegDataStru的结构体下标
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSegDataStruIndex(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的结构体指针
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSegStruct* GetIndexIdSegDataStru(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的长度（cm)
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 长度（cm)
*/ 
UINT32_S GetSegDataStrulength(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的起点端点类型
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点端点类型
*/ 
UINT16_S GetSegDataStrustartPointType(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的起点端点编号
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点端点编号
*/ 
UINT16_S GetSegDataStrustartPointId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的终点端点类型
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点端点类型
*/ 
UINT16_S GetSegDataStruendPointType(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的终点端点编号
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点端点编号
*/ 
UINT16_S GetSegDataStruendPointId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的起点正向相邻SegID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点正向相邻SegID
*/ 
UINT16_S GetSegDataStrusegStartJointMainSegId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的起点侧向相邻点SegID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点侧向相邻点SegID
*/ 
UINT16_S GetSegDataStrusegStartJointSideSegId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的终点正向相邻点SegID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点正向相邻点SegID
*/ 
UINT16_S GetSegDataStrusegTmnlJointMainSegId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的终点侧向相邻点SegID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点侧向相邻点SegID
*/ 
UINT16_S GetSegDataStrusegTmnlJointSideSegId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的所属ZC区域ID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属ZC区域ID
*/ 
UINT16_S GetSegDataStrusegManageZCId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的所属ATS区域ID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属ATS区域ID
*/ 
UINT16_S GetSegDataStrusegManageATSId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的所属CI区域ID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属CI区域ID
*/ 
UINT16_S GetSegDataStrusegManageCIId(const UINT16_S segId);

/*
** 功能描述： 获取指定IDSegDataStru的终点端点编号和终点端点类型
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点端点编号
*/ 
UINT16_S GetSegDataStruendPointInfo(const UINT16_S segId,UINT16_S* pointType);

/*
** 功能描述： 获取指定IDSegDataStru的起点端点编号和起点端点类型
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点端点编号
*/ 
UINT16_S GetSegDataStrustartPointInfo(const UINT16_S segId,UINT16_S* pointType);

/*
** 功能描述： 获取指定点指定位置的SEG信息
* 参数说明： const UINT16_S pointId;点编号
*             const UINT8_S startOrEnd  此点为起点或终点  1 起点 2 终点
*             BnfSegStruct* pSegStru SEG结构体信息指针
* 返回值  :  0: 获取数据失败
*            >0: 终点端点编号
*/ 
UINT8_S GetSegInfoBuffAccordPointId(UINT16_S pointId,const UINT8_S startOrEnd,BnfSegStruct* pSegStru);

/*
** 功能描述： 获取指定CIID获取ZCID
* 参数说明： const UINT16_S segId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: ZCID
*/ 
UINT16_S ArrordCiIdGetZcId(const UINT16_S ciId);

#ifdef __cplusplus
}
#endif

#endif
