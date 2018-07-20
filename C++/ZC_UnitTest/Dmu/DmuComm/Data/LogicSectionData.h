/*************************************************
  文件名   ：LogicSectionData.h
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
#ifndef LOGICSECTION_DATA_H_
#define LOGICSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "DataCommondefine.h"

#define LOGICSECTION_NAME_BYTE_LEN                 16                               /*名称长度*/
#define LOGICSECTION_SEGID_MAX_NUM                    5                                /*逻辑区段包含的最大SEGID*/
#define LOGICSECTION_OF_SWITCH_MAX_NUM                2                                /*一个逻辑区段包含的道岔个数*/
#define LOGICSECTION_LINE_BYTE_NUM                 30                                /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

typedef struct BnfRelateLogicSecInfoStruct
{
    UINT16_S relateLogicId;                            /*相关联逻辑区段的ID*/
    UINT16_S relateSegId;                                /*相关联SEG的ID*/
    UINT8_S  pointFalg;                                /*起点 或是终点*/
}BnfRelateLogicSecInfoStruct;


/*逻辑区段表数据结构体*/
typedef struct BnfLogicSectionStruct
{
    UINT16_S  indexId;                                /*索引编号*/
    UINT8_S     name[LOGICSECTION_NAME_BYTE_LEN];        /*名称*/
    UINT16_S  startSegId;                                /*起点所处Seg编号*/
    UINT32_S  startSegOffset;                            /*起点所处Seg偏移量*/
    UINT16_S  endSegId;                                /*终点所处Seg编号*/
    UINT32_S  endSegOffset;                            /*终点所处Seg偏移量*/

    /*计算获取逻辑区段所属的计轴区段ID*/
    UINT16_S  belongAxleSecId;                        /*所属计轴区段ID*/
    UINT16_S  mainOrgnLogicSgmtId;                    /*所属计轴区段内前向逻辑区段的编号*/
    UINT16_S  mainTmnlLogicSgmtId;                    /*所属计轴区段内后向逻辑区段的编号*/    
    UINT16_S  startJointMainLogicId;                    /*起点正向相邻逻辑区段ID*/
    UINT16_S  startJointSideLogicId;                    /*起点侧向相邻逻辑区段ID*/
    UINT16_S  tmnlJointMainLogicId;                    /*终点正向相邻逻辑区段ID*/
    UINT16_S  tmnlJointSideLogicId;                    /*终点侧向相邻逻辑区段ID*/ 
    UINT8_S   relateLogicNum;                            /*相关联逻辑区段个数*/
    BnfRelateLogicSecInfoStruct  relateLogicInfo[LOGICSECTION_OF_SWITCH_MAX_NUM];        /*相关联逻辑区段信息*/
    UINT16_S  manageZCId;                                /*所属ZC区域ID*/
    UINT16_S  manageCIId;                                /*所属CI区域ID*/
    UINT16_S includeSegIdNum;                            /*包含的segId个数*/
    UINT16_S segIdBuff[LOGICSECTION_SEGID_MAX_NUM];    /*包含的SEGID*/
    UINT8_S switchIdNum;                                                                /*此逻辑区段包含道岔的个数*/
    BnfSngSwitchInfoStruct switchIdStru[LOGICSECTION_OF_SWITCH_MAX_NUM];            /*此逻辑区段包含的道岔信息*/
}BnfLogicSectionStruct;

/*
* 功能描述： 给LogicSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocLogicSectionDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取LogicSectionData数据
* 参数说明：
* 返回值  ： 
            BnfLogicSectionStruct*
*/
BnfLogicSectionStruct *GetLogicSectionData(void);

/*
* 功能描述： 获取LogicSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfLogicSectionStruct*
*/
BnfLogicSectionStruct *GetLogicSectionDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDLogicSectionDataStru的结构体下标
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetLogicSectionDataStruIndex(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLogicSectionDataStru的结构体指针
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfLogicSectionStruct* GetIndexIdLogicSectionDataStru(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLogicSectionDataStru的名称
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetLogicSectionDataStruname(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLogicSectionDataStru的起点所处Seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg编号
*/ 
UINT16_S GetLogicSectionDataStrustartSegId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLogicSectionDataStru的起点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg偏移量
*/ 
UINT32_S GetLogSecDataStartSegOff(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLogicSectionDataStru的终点所处Seg编号
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg编号
*/ 
UINT16_S GetLogicSectionDataStruendSegId(const UINT16_S indexId);

/*
** 功能描述： 获取指定IDLogicSectionDataStru的终点所处Seg偏移量
* 参数说明： const UINT16_S indexId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg偏移量
*/ 
UINT32_S GetLogicSectionDataStruendSegOffset(const UINT16_S indexId);

/*
* 功能描述： 获取线路逻辑区段最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:逻辑区段最大ID
*/
UINT16_S GetLineLogicSectionMaxId(void);

/*
* 功能描述： 根据输入的SEGID获取逻辑区段的信息
* 参数说明： const UINT16_S* pSegId;SEGID指针指针
             const UINT16_S segIdNum;SEGID个数
             UINT16_S logicSectionIdBuf[];逻辑区段ID数组
* 返回值  :  0: 获取数据失败
*            >0: 逻辑区段个数
*/ 
UINT8_S GetSegIdBuffOfLogSecInfo(const UINT16_S* pSegId,const UINT16_S segIdNum,UINT16_S logicSectionIdBuf[]);

/*
* 功能描述： 获取逻辑区段所属ZC
* 参数说明： const UINT16_S logicSectionId，逻辑区段ID
* 返回值  ： 0: 获取失败
*            >0:所属ZCID
*/
UINT16_S GetLineLogicSectionBelongZcId(const UINT16_S logicSectionId);

/*
* 功能描述： 获取逻辑区段所属CI
* 参数说明： const UINT16_S logicSectionId，逻辑区段ID
* 返回值  ： 0: 获取失败
*            >0:所属CIID
*/
UINT16_S GetLineLogicSectionBelongCiId(const UINT16_S logicSectionId);

/*
* 功能描述： 获取逻辑区段所属AC
* 参数说明： const UINT16_S logicSectionId，逻辑区段ID
* 返回值  ： 0: 获取失败
*            >0:所属ACID
*/
UINT16_S GetLineLogicSectionBelongAcId(const UINT16_S logicSectionId);

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
UINT8_S GetSegFontSecOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startSegLen,UINT16_S* mainLogicId,UINT16_S* sideLogicId);

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
UINT8_S GetSegRearSecOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startSegLen,UINT16_S* mainLogicId,UINT16_S* sideLogicId);

/*
* 功能描述： 获取逻辑区段ID相关联的逻辑区段ID
* 参数说明： const UINT16_S logicSectionId，逻辑区段ID
* 返回值  ： UINT16_NULL: 查询失败
*            >0: 关联的逻辑区段ID
*/
UINT8_S GetLineLogicSectionBelongRelareLc(const UINT16_S logicSectionId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct* relateLogicInfo);

#ifdef __cplusplus
}
#endif

#endif
