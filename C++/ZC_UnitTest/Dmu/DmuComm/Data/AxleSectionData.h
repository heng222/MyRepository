
/*************************************************
  文件名   ：AxleSectionData.c
  作者     ：董欣      
  创建时间 ：2016-8-10
  功能描述 ： AxleSectionData数据管理
			DmuCommonData组件的AxleSectionData功能可分解如下：
			1）	给AxleSectionDataStru结构体指针分配空间
			2）	获取AxleSectionData数据
			3）	获取AxleSectionData信息
			4）	获取指定IDAxleSectionDataStru的结构体下标
			5）	获取指定IDAxleSectionDataStru的结构体指针
			6）	获取指定IDAxleSectionDataStru的名称
			7）	获取指定IDAxleSectionDataStru的包含Seg数目
			8）	获取指定IDAxleSectionDataStru的Seg编号
			9）	获取计轴区段包含的SegId的信息
			10）	获取SEGID包含的计轴区段ID
			11）	获取SEGID包含的计轴区段结构体指针
			12）	获取线路计轴区段最大ID
			13）	获取指定IDAxleSectionDataStru的Seg信息
			14）	获取计轴区段所属CIID
			15）	获取计轴区段所属ZC
			16）	获取计轴区段包含逻辑区段信息

  备注    ：无。
 
*************************************************/
#ifndef AXLESECTION_DATA_H_
#define AXLESECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  AXLESECTION_NAME_BYTE_NUM       16                                                                  /*名称的字节数*/
#define  AXLESECTION_SEG_MAX_NUM          5                                                                /*SEG最大数目*/    
#define  AXLESECTION_LINE_BYTE_NUM       30                                                             /*一行数据的字节数*/
#define  AXLESECTION_BELONG_LOGICSEC_MAX_NUM      20                                                    /*计轴区段包含逻辑区段最大个数*/        

#ifdef __cplusplus
extern "C" {
#endif

/*计轴区段表*/
typedef struct BnfAxleSectionStruct
{ 
    UINT16_S  indexId;                                                    /*索引编号*/
    UINT8_S      axleStcName[AXLESECTION_NAME_BYTE_NUM];                        /*名称*/        
    UINT16_S  includeSegNum;                                                /*包含Seg数目*/    
    UINT16_S     segIdBuff[AXLESECTION_SEG_MAX_NUM];                            /*Seg编号*/

    /*计算获取逻辑区段所属的包含的逻辑区段个数以及逻辑区段ID*/
    UINT8_S includeLogicAxleSecNum;                                        /*包含的逻辑区段个数*/
    UINT16_S logicSecId[AXLESECTION_BELONG_LOGICSEC_MAX_NUM];                /*包含的逻辑区段ID*/
    UINT16_S orgnSegId;                                                    /*起点所处seg编号*/
    UINT16_S tmnlSegId;                                                    /*终点所处seg编号*/
    UINT32_S orgnSegOfst;                                                    /*起点所处seg偏移量*/
    UINT32_S tmnlSegOfst;                                                    /*终点所处seg偏移量*/
    UINT16_S  orgnAxleId;                                                    /*起点计轴器编号*/
    UINT16_S  tmnlAxleId;                                                    /*终点计轴器编号*/
    UINT8_S  orgnAxleSecNum;                                                /*计轴区段起点链接计轴区段个数*/
    UINT16_S  orgnAxleSgmtId[3];                                            /*计轴区段起点连接计轴区段编号*/
    UINT8_S  tmnlAxleSecNum;                                                /*计轴区段终点点链接计轴区段个数*/
    UINT16_S  tmnlAxleSgmtId[3];                                            /*计轴区段终点连接计轴区段编号*/
    UINT16_S  relatPointNum;                                                /*关联道岔数目*/    
    UINT16_S  relatPointId[4];                                            /*关联道岔编号*/
    UINT16_S  relatPointStatus[4];                                         /*关联道岔状态*/
    UINT16_S  manageZCId;                                                    /*所属ZC区域ID*/
    UINT16_S  manageCIId;                                                    /*所属CI区域ID*/ 
}BnfAxleSectionStruct;

/*
* 函数名称：MallocAxleSectionDataStru
* 功能描述： 给AxleSectionDataStru结构体指针分配空间
* 输入参数： UINT16_S lineNum 表的数据行数
* 输出参数： 无
* 返回值  ： void
*/
void MallocAxleSectionDataStru(UINT16_S lineNum);

/*
* 函数名称： GetAxleSectionData
* 功能描述： 获取AxleSectionData数据
* 输入参数： 无
* 输出参数： 无
* 返回值  ：
*           BnfAxleSectionStruct*
*/
BnfAxleSectionStruct *GetAxleSectionData(void);

/*
* 函数名称： GetAxleSectionData
* 功能描述： 获取AxleSectionData数据
* 输入参数： 无
* 输出参数： 无
* 返回值  ：
*           BnfAxleSectionStruct*
*/
BnfAxleSectionStruct *GetAxleSectionDataInfo(UINT16_S* lineNum);

/*
* 函数名称： GetAxleSectionDataStruIndex
* 功能描述： 获取指定IDAxleSectionDataStru的结构体下标
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetAxleSectionDataStruIndex(const UINT16_S indexId);

/*
* 函数名称： GetIndexIdAxleSectionDataStru
* 功能描述： 获取指定IDAxleSectionDataStru的结构体指针
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/
BnfAxleSectionStruct* GetIndexIdAxleSectionDataStru(const UINT16_S indexId);

/*
* 函数名称： GetAxleSectionDataStruaxleStcName
* 功能描述： 获取指定IDAxleSectionDataStru的名称
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetAxleSectionDataStruaxleStcName(const UINT16_S indexId);

/*
* 函数名称： GetAxleSectionDataStruincludeSegNum
* 功能描述： 获取指定IDAxleSectionDataStru的包含Seg数目
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 包含Seg数目
*/ 
UINT16_S GetAxleSectionDataStruincludeSegNum(const UINT16_S indexId);

/*
* 函数名称： GetAxleSectionDataStrusegIdBuff
* 功能描述： 获取指定IDAxleSectionDataStru的Seg编号
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: Seg编号
*/ 
UINT16_S* GetAxleSectionDataStrusegIdBuff(const UINT16_S indexId);

/*
* 函数名称： GetAxleSectionOfSegInfo
* 功能描述： 获取计轴区段包含的SegId的信息
* 输入参数： const UINT16_S AxleSecId,计轴区段ID
* 输出参数： UINT16_S* pSegId，SegID数组
* 返回值  ： 0xffff: 获取数据失败
*            >0:SegId数量
*/
UINT16_S GetAxleSectionOfSegInfo(const UINT16_S AxleSecId,UINT16_S* pSegId);

/*
* 函数名称： GetSegIdBelongofAxleSecId
* 功能描述： 获取SEGID包含的计轴区段ID
* 输入参数： const UINT16_S  segId，SegID
*             const UINT8_S segNum      SEG个数
*             const UINT8_S findNum  需要查找几个
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*            >0:计轴区段ID
*/
UINT16_S GetSegIdBelongofAxleSecId(const UINT16_S* segIdbuff,const UINT8_S segNum,const UINT8_S findNum);

/*
* 函数名称： GetSegIdBelongofAxleSecInfo
* 功能描述： 获取SEGID包含的计轴区段结构体指针
* 输入参数： const UINT16_S  segId，SegID
*             const UINT8_S segNum      SEG个数
* 输出参数： 无
* 返回值  ： NULL: 获取数据失败
*             !NULL:计轴区段结构体指针
*/
BnfAxleSectionStruct* GetSegIdBelongofAxleSecInfo(const UINT16_S* segIdbuff,const UINT8_S segNum);

/*
* 函数名称： GetLineAcMaxId
* 功能描述： 获取线路计轴区段最大ID
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:计轴区段最大ID
*/
UINT16_S GetLineAcMaxId(void);

/*
* 函数名称： GetAxleSectionDataStruSegInfo
* 功能描述： 获取指定IDAxleSectionDataStru的Seg信息
* 输入参数： const UINT16_S indexId;索引编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 包含SEG的个数
*/ 
UINT16_S GetAxleSectionDataStruSegInfo(const UINT16_S indexId,UINT16_S* pSegId);

/*
* 函数名称： GetLineAcBelongCiId
* 功能描述： 获取计轴区段所属CIID
* 输入参数： const UINT16_S acId，计轴区段ID
* 输出参数： 无
* 返回值  ： 0: 获取失败
*             联锁ID
*/
UINT16_S GetLineAcBelongCiId(const UINT16_S acId);

/*
* 函数名称： GetLineAcBelongZcId
* 功能描述： 获取计轴区段所属ZC
* 输入参数： const UINT16_S acId，计轴区段ID
* 输出参数： 无
* 返回值  ： 0: 获取失败
*            >0:所属ZCID
*/
UINT16_S GetLineAcBelongZcId(const UINT16_S acId);

/*
* 函数名称： GetLineAcIncludeLogicSectionInfo
* 功能描述： 获取计轴区段包含逻辑区段信息
* 输入参数： const UINT16_S acId，计轴区段ID
* 输出参数： UINT8_S *logicSectionNum,逻辑区段数量
*            UINT16_S logicSectionIdBuf[]，逻辑区段ID数组
* 返回值  ： 0: 获取失败
*            1: 获取成功
*/
UINT8_S GetLineAcIncludeLogicSectionInfo(const UINT16_S acId,UINT8_S *logicSectionNum,UINT16_S logicSectionIdBuf[]);

#ifdef __cplusplus
}
#endif

#endif
