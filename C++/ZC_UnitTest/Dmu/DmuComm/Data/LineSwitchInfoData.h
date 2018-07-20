/*************************************************
  文件名   ：LineSwitchInfoData.h
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： LineSwitchInfoData数据管理
			DmuCommonData组件的LineSwitchInfoData功能可分解如下：
			1）	给LineSwitchInfoDataStru结构体指针分配空间
			2）	获取LineSwitchInfoData数据
			3）	获取LineSwitchInfoData信息
			4）	获取指定IDLineSwitchInfoDataStru的结构体下标
			5）	获取指定IDLineSwitchInfoDataStru的结构体指针
			6）	获取指定IDLineSwitchInfoDataStru的切换线路移交ZCID
			7）	获取指定IDLineSwitchInfoDataStru的切换线路接管ZCID
			8）	获取指定IDLineSwitchInfoDataStru的切换线路方向
			9）	获取指定IDLineSwitchInfoDataStru的切换线路起点所处seg编号
			10）	获取指定IDLineSwitchInfoDataStru的切换线路起点所处seg偏移
			11）	获取指定IDLineSwitchInfoDataStru的切换点所处seg编号
			12）	获取指定IDLineSwitchInfoDataStru的切换点所处seg偏移
			13）	获取指定IDLineSwitchInfoDataStru的切换线路终点所处seg编号
			14）	获取指定IDLineSwitchInfoDataStru的切换线路终点所处seg偏移
			15）	获取指定IDLineSwitchInfoDataStru的切换点相关进路编号
			16）	获取指定IDLineSwitchInfoDataStru的切换线路内包含的道岔数目
			17）	获取指定IDLineSwitchInfoDataStru的道岔信息结构体
			18）	获取切换线路数量和ID信息

  备注    ：无。
 
*************************************************/
#ifndef LINESWITCHINFO_DATA_H_
#define LINESWITCHINFO_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "DataCommondefine.h"
#include "../DataHandle/DmuCommDataTypeDefine.h"

#define LINESWITCHINFO_SWITCH_NUM                         (6 + 4)                                         /*道岔个数*/
#define LINESWITCHINFO_LINE_BYTE_NUM                    (53  + 16)                                          /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*切换线路信息数据结构体*/
typedef struct BnfLineSwitchInfoStruct
{
    UINT16_S  indexId;                                                    /*索引编号*/
    UINT16_S  lineSwitchTraZcId;                                            /*切换线路移交ZCID*/
    UINT16_S  lineSwitchTakeOverZcId;                                        /*切换线路接管ZCID*/
    UINT8_S   lineSwitchDir;                                                /*切换线路方向*/
    UINT16_S  startLineSwitchInfoId;                                        /*切换线路起点所处seg编号*/
    UINT32_S  startSegOffset;                                                /*切换线路起点所处seg偏移*/
    UINT16_S  switchPointSegId;                                            /*切换点所处seg编号*/
    UINT32_S  switchPointOffset;                                            /*切换点所处seg偏移*/
    UINT16_S  endLineSwitchInfoId;                                          /*切换线路终点所处seg编号*/
    UINT32_S  segEndOffset;                                                  /*切换线路终点所处seg偏移*/
    UINT16_S  relationRouteNum;                                           /*切换点相关进路编号*/  
    UINT16_S  includeSwitchNum;                                            /*切换线路内包含的道岔数目*/ 
    BnfSngSwitchInfoStruct switchInfoStru[LINESWITCHINFO_SWITCH_NUM];   /*道岔信息结构体*/

    /*增加项*/
    UINT8_S segNum;                                                        /*SEGID个数*/
    UINT16_S segIdBuff[BOTHSEG_INCLUDE_MAX_SEG];                            /*包含的SEGID个数*/
    UINT8_S acNum;                                                        /*计轴区段个数*/
    UINT16_S acIdBuff[TWO_POINT_AC_NUM_MAX];                                /*包含的计轴区段ID*/
}BnfLineSwitchInfoStruct;

/*
* 功能描述： 给LineSwitchInfoDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocLineSwitchInfoDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取LineSwitchInfoData数据
* 参数说明：
* 返回值  ： 
            BnfLineSwitchInfoStruct*
*/
BnfLineSwitchInfoStruct *GetLineSwitchInfoData(void);

/*
* 功能描述： 获取LineSwitchInfoData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfLineSwitchInfoStruct*
*/
BnfLineSwitchInfoStruct *GetLineSwitchInfoDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetLineSwitchInfoDataStruIndex(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfLineSwitchInfoStruct* GetIndexIdLineSwitchInfoDataStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路移交ZCID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路移交ZCID
*/ 
UINT16_S GetLineSwitchInfoDataStrulineSwitchTraZcId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路接管ZCID
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路接管ZCID
*/ 
UINT16_S GetLinSwInfDatliSwTakeOvZcId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路方向
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路方向
*/ 
UINT8_S GetLineSwInfoDatalineSwDir(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路起点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路起点所处seg编号
*/ 
UINT16_S GetLineSwitchInfoDataStrustartLineSwitchInfoId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路起点所处seg偏移
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路起点所处seg偏移
*/ 
UINT32_S GetLineSwitchInfoDataStrustartSegOffset(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换点所处seg编号
*/ 
UINT16_S GetLineSwitchInfoDataStruswitchPointSegId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换点所处seg偏移
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换点所处seg偏移
*/ 
UINT32_S GetLineSwInfoDataSwPointOff(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路终点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路终点所处seg编号
*/ 
UINT16_S GetLineSwitchInfoDataStruendLineSwitchInfoId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路终点所处seg偏移
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路终点所处seg偏移
*/ 
UINT32_S GetLineSwitchInfoDataStrusegEndOffset(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换点相关进路编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换点相关进路编号
*/ 
UINT16_S GetLineSwitchInfoDataStrurelationRouteNum(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的切换线路内包含的道岔数目
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 切换线路内包含的道岔数目
*/ 
UINT16_S GetLineSwitchInfoDataStruincludeSwitchNum(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLineSwitchInfoDataStru的道岔信息结构体
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 道岔信息结构体
*/ 
BnfSngSwitchInfoStruct* GetLineSwInfDataSwInfStru(const UINT16_S indexId);

/*
* 功能描述： 获取切换线路数量和ID信息
* 输入参数： const UINT16_S localZcId, 本地ZCid
*            UINT16_S changeLineIdBuf[]，切换线路ID数组（最大30条）
* 返回值  ： 0xff: 获取数据失败
*            0>: 数量
*/
UINT8_S GetLocalZcChangeLineNum(const UINT16_S localZcId, UINT16_S changeLineIdBuf[]);

#ifdef __cplusplus
}
#endif

#endif
