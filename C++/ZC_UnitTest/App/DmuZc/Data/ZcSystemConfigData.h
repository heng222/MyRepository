/*******************************************
* 文件名	：  ZcSystemConfigData.h
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	载入ZcSystemConfigData数据管理
* 备  注	：  无
*******************************************/
#ifndef ZCSYSTEMCONFIG_DATA_H_
#define ZCSYSTEMCONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ZCSYSTEMCONFIG_LINE_BYTE_NUM                   22U                         /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*ZC系统配置表数据结构体*/
typedef struct BnfZcSystemConfigStruct
{
	UINT16_S  trainMaxRecedeDis;						/*列车最大退行距离（ms）*/
	UINT16_S  lineMinTrainLength;						/*线路最小可能车长(cm)*/
	UINT32_S  sectionLength;							/*运营要求的点灯区段长度(cm)*/
	UINT16_S  axleSectionNum;							/*前端筛选计轴区段数量*/
	UINT32_S  redunJudgmentTime;						/*计轴区段非通信车占用冗余判断时间（ms）*/
	UINT8_S  freeCodeNumSwitch;						/*ZC-CI逻辑区段占用空闲码位个数开关*/
	UINT32_S  trainCbtcBackTime;						/*列车CBTC折返时间（ms）*/
	UINT16_S  signPressureDis;						/*判断信号机跨压距离(cm)*/
	UINT8_S  zcTrackRmTrainType;                      /*追踪不带后方检查标记RM列车方式*/
}BnfZcSystemConfigStruct;

/*******************************************
* 函数名	：
* 功能描述： 给ZcSystemConfigDataStru结构体指针分配空间
* 参数说明： UINT16 lineNum 表的数据行数
* 返回值  ： void
*/
void MallocZcSystemConfigDataStru(UINT16_S lineNum);

/*******************************************
* 函数名	：
* 功能描述： 获取ZcSystemConfigData数据
* 参数说明：
* 返回值  ： 
			BnfZcSystemConfigStruct*
*/
BnfZcSystemConfigStruct *GetZcSystemConfigData(void);

/*******************************************
* 函数名	：
* 功能描述： 获取ZcSystemConfigData信息
* 参数说明：输出参数:UINT16* lineNum  数据行数
* 返回值  ： 
			BnfZcSystemConfigStruct*
*/
BnfZcSystemConfigStruct *GetZcSystemConfigDataInfo(UINT16_S* lineNum);

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSystemConfigDataStru的列车最大退行距离（ms）
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 列车最大退行距离（ms）
*/ 
UINT16_S GetZcSystemConfigDataStrutrainMaxRecedeDis(void);

/*******************************************
* 函数名	：
** 功能描述： 获取线路最小可能车长(cm)
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 线路最小可能车长(cm)
*/ 
UINT16_S GetZcSystemLineMinTrainLength(void);

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSystemConfigDataStru的线路最小可能车长(cm)
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 线路最小可能车长(cm)
*/ 
UINT16_S GetZcSystemConfigDataStrulineMinTrainLength(void);

/*******************************************
* 函数名	：
** 功能描述： 获取运营要求的点灯区段长度(cm)
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: 运营要求的点灯区段长度(cm)
*/ 
UINT32_S GetZcSystemSectionLength(void);

/*******************************************
* 函数名	：
** 功能描述： 获取前端筛选计轴区段数量
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 前端筛选计轴区段数量
*/ 
UINT16_S GetZcSystemAxleSectionNum(void);
/*******************************************
* 函数名	：
** 功能描述： 获取计轴区段非通信车占用冗余判断时间（ms）
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: 计轴区段非通信车占用冗余判断时间（ms）
*/ 
UINT32_S GetZcSystemRedunJudgmentTime(void);

/*******************************************
* 函数名	：
** 功能描述： 获取逻辑区段占用空闲码位个数开关
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*			<UINT8_NULL: ZC-CI逻辑区段占用空闲码位个数开关
*/ 
UINT8_S GetZcSystemFreeCodeNumSwitch(void);

/*******************************************
* 函数名	：
** 功能描述： 获取列车CBTC折返时间（ms）
* 参数说明:  无
* 返回值  :  UINT32_NULL: 获取数据失败
*			<UINT32_NULL: 列车CBTC折返时间（ms）
*/ 
UINT32_S GetZcSystemTrainCbtcBackTime(void);

/*******************************************
* 函数名	：
** 功能描述： 判断信号机跨压距离
* 参数说明:  无
* 返回值  :  UINT16_NULL: 获取数据失败
*			<UINT16_NULL: 判断信号机跨压距离
*/ 
UINT16_S GetZcSystemSignPressureDis(void);

/*******************************************
* 函数名	：
** 功能描述： 追踪不带后方检查标记RM列车方式
* 参数说明:  无
* 返回值  :  UINT8_NULL: 获取数据失败
*			<UINT8_NULL: 追踪不带后方检查标记RM列车方式
*/ 
UINT8_S GetZcTrackRmTrainType(void);

#ifdef __cplusplus
}
#endif

#endif
