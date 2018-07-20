/*************************************************
  文件名   ：SignData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： SignData数据管理
			DmuCommonData组件的SignData功能可分解如下：
			1）	给SignDataStru结构体指针分配空间
			2）	获取SignData数据
			3）	获取SignData信息
			4）	获取指定IDSignDataStru的结构体下标
			5）	获取指定IDSignDataStru的结构体指针
			6）	 获取指定IDSignDataStru的信号机名称
			7）	获取指定IDSignDataStru的类型
			8）	 获取指定IDSignDataStru的属性
			9）	获取指定IDSignDataStru的所处seg编号
			10）	 获取指定IDSignDataStru的所处Seg偏移量（cm）
			11）	获取指定IDSignDataStru的防护方向
			12）	获取指定IDSignDataStru的灯列信息
			13）	获取线路信号机最大ID
			14）	本函数功能是查询当前SEG上指定防护方向的信号机信息
			15）	获取线路信号机所属ZC
			16）	获取线路信号机所属CI
  备注    ：无。
 
*************************************************/
#ifndef SIGN_DATA_H_
#define SIGN_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SIGN_NAME_LEN                      12                           /*信号机名称字节数*/
#define SIGN_LINE_BYTE_NUM                 29                            /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*信号机表数据结构体*/
typedef struct BnfSignStruct
{ 
    UINT16_S signId;                                /*索引编号*/
    UINT8_S  signName [SIGN_NAME_LEN];            /*信号机名称*/
    UINT16_S signType;                            /*类型*/
    UINT16_S signProperty;                        /*属性*/
    UINT16_S signProtectSegId;                    /*所处防护方向seg编号*/
    UINT32_S signProtectSegOffset;                /*所处防护方向Seg偏移量（cm）*/
    UINT8_S protectiveDir;                        /*防护方向*/
    UINT32_S lightInfo;                            /*灯列信息*/

    /*动态计算字段*/
    UINT16_S signSegId;                            /*所处seg编号*/
    UINT32_S signSegOffset;                        /*所处Seg偏移量（cm）*/
    UINT16_S  manageZCId;                            /*所属ZC区域ID*/
    UINT16_S  manageCIId;                            /*所属CI区域ID*/ 
}BnfSignStruct;    

/*
* 功能描述： 给SignDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocSignDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取SignData数据
* 参数说明：
* 返回值  ： 
            BnfSignStruct*
*/
BnfSignStruct *GetSignData(void);

/*
* 功能描述： 获取SignData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfSignStruct*
*/
BnfSignStruct *GetSignDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDSignDataStru的结构体下标
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetSignDataStruIndex(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的结构体指针
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfSignStruct* GetIndexIdSignDataStru(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的信号机名称
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 信号机名称
*/ 
UINT8_S* GetSignDataStrusignName(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的类型
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 类型
*/ 
UINT16_S GetSignDataStrusignType(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的属性
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 属性
*/ 
UINT16_S GetSignDataStrusignProperty(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的所处seg编号
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT16_S GetSignDataStrusignSegId(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的所处Seg偏移量（cm）
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处Seg偏移量（cm）
*/ 
UINT32_S GetSignDataStrusignSegOffset(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的所处防护方向seg编号
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT16_S GetSignDataStrusignProSegId(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的所处防护方向Seg偏移量（cm）
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处Seg偏移量（cm）
*/ 
UINT32_S GetSignDataStrusignProSegOffset(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的防护方向
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 防护方向
*/ 
UINT8_S GetSignDataStruprotectiveDir(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的灯列信息
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 灯列信息
*/ 
UINT32_S GetSignDataStrulightInfo(const UINT16_S signId);

/*
* 功能描述： 获取线路信号机最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:信号机最大ID
*/
UINT16_S GetLineSignalMaxId(void);

/*
* 函数功能：本函数功能是查询当前SEG上指定防护方向的信号机信息。
* 入口参数：UINT16 segId                seg编号
*            UINT8_S  dir                    运行方向
* 出口参数：UINT16 findSignalIDBuff[]        找到的信号机ID
*            UINT8_S* fingNum              查找到信号机的个数
* 返回值：  UINT8_S retVal 
*            查询成功:当前SEG上无信号机，返回0;
*            查询成功:当前SEG上存在信号机，返回1      
*******************************************************************************************/
UINT8_S FindCurrentSegSignal(UINT16_S segId, UINT8_S dir, UINT16_S findSignalIDBuff[],UINT8_S* fingNum);

/*
* 功能描述： 获取线路信号机所属ZC
* 参数说明： const UINT16_S signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLineSignalBelongZcId(const UINT16_S signalId);

/*
* 功能描述： 获取线路信号机所属CI
* 参数说明： const UINT16_S signalId,信号机ID
* 返回值  ： 0: 获取数据失败
*            >0:所属CIId
*/
UINT16_S GetLineSignalBelongCiId(const UINT16_S signalId);

/*
** 功能描述： 获取指定IDSignDataStru的防护seg编号
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT16_S GetSignDataStrusignProtectSegId(const UINT16_S signId);

/*
** 功能描述： 获取指定IDSignDataStru的防护seg偏移量
* 参数说明： const UINT16_S signId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所处seg编号
*/ 
UINT32_S GetSignDataStrusignProtectSegOffset(const UINT16_S signId);

#ifdef __cplusplus
}
#endif

#endif
