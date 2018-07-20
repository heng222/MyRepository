/*************************************************
  文件名   ：ExitCbtcSectionData.h
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： ExitCbtcSectionData数据管理
			DmuCommonData组件的ExitCbtcSectionData功能可分解如下：
			1）	给ExitCbtcSectionDataStru结构体指针分配空间
			2）	获取ExitCbtcSectionData数据
			3）	获取ExitCbtcSectionData信息
			4）	获取指定IDExitCbtcSectionDataStru的结构体下标
			5）	获取指定IDExitCbtcSectionDataStru的结构体指针
			6）	 获取指定IDExitCbtcSectionDataStru的退出CBTC区域时列车运行方向
			7）	获取指定IDExitCbtcSectionDataStru的退出CBTC区域属性
			8）	 获取指定IDExitCbtcSectionDataStru的起点所处seg编号
			9）	获取指定IDExitCbtcSectionDataStru的起点所处Seg偏移量
			10）	获取指定IDExitCbtcSectionDataStru的终点所处Seg偏移量
			11）	获取指定IDExitCbtcSectionDataStru的包含的Seg数目
			12）	获取指定IDExitCbtcSectionDataStru的SEG编号
			13）	查询某个点是否和退出CBTC区域终点重合
			14）	查询某个点是否属于CBTC区域

  备注    ：无。
 
*************************************************/
#ifndef EXITCBTCSECTION_DATA_H_
#define EXITCBTCSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define EXITCBTCSECTION_SEG_MAX_NUM                      16                                                           /*最大SEG个数*/
#define EXITCBTCSECTION_LINE_BYTE_NUM                 48                                                        /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif


/*退出CBTC区域表数据结构体*/
typedef struct BnfExitCbtcSectionStruct
{
    UINT16_S  indexId;                                        /*索引编号*/
    UINT16_S  dir;                                            /*退出CBTC区域时列车运行方向*/
    UINT16_S  attribute;                                        /*退出CBTC区域属性*/
    UINT32_S  startOffset;                                    /*起点所处Seg偏移量*/
    UINT32_S  endOffSet;                                        /*终点所处Seg偏移量*/
    UINT16_S  segNum;                                            /*包含的Seg数目*/
    UINT16_S  segInfoBuff[EXITCBTCSECTION_SEG_MAX_NUM];          /*SEG编号*/

    /*动态计算生成*/
    UINT16_S  startSegId;                                        /*起点所处seg编号*/
    UINT16_S  endSegId;                                        /*起点所处seg编号*/
}BnfExitCbtcSectionStruct;

/*
* 功能描述： 给ExitCbtcSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocExitCbtcSectionDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取ExitCbtcSectionData数据
* 参数说明：
* 返回值  ： 
            BnfExitCbtcSectionStruct*
*/
BnfExitCbtcSectionStruct *GetExitCbtcSectionData(void);

/*
* 功能描述： 获取ExitCbtcSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfExitCbtcSectionStruct*
*/
BnfExitCbtcSectionStruct *GetExitCbtcSectionDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetExitCbtcSectionDataStruIndex(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfExitCbtcSectionStruct* GetIndexIdExitCbtcSectionDataStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的退出CBTC区域时列车运行方向
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 退出CBTC区域时列车运行方向
*/ 
UINT16_S GetExitCbtcSectionDataStrudir(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的退出CBTC区域属性
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 退出CBTC区域属性
*/ 
UINT16_S GetExitCbtcSectionDataStruattribute(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的起点所处seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处seg编号
*/ 
UINT16_S GetExitCbtcSectionDataStrustartSegId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的起点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg偏移量
*/ 
UINT32_S GetExitCbtcSectDataStartOff(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的终点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg偏移量
*/ 
UINT32_S GetExitCbtcSectionDataStruendOffSet(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的包含的Seg数目
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 包含的Seg数目
*/ 
UINT16_S GetExitCbtcSectionDataStrusegNum(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDExitCbtcSectionDataStru的SEG编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: SEG编号
*/ 
UINT16_S* GetExitCbtcSectionDataStrusegInfoBuff(const UINT16_S indexId);

/* 功能描述： 查询某个点是否和退出CBTC区域终点重合
* 参数说明： 
* 返回值  ： 
*    1,重合
*    2,不重合
*/
UINT8_S CheckAtQuitCbtcIsFindPoint(const UINT16_S seg,const UINT32_S offset);


/* 功能描述： 查询某个点是否属于CBTC区域
* 参数说明： 
* 返回值  ： 
*    0,不属于
*    1,属于
*/
UINT8_S ExitCbtcSecIncludePoint(UINT16_S segId,UINT32_S offset);

#ifdef __cplusplus
}
#endif

#endif
