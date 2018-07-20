/*******************************************
* 文件名	：  ZcCommConfigData.h
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	载入ZcCommConfigData数据管理
* 备  注	：  无
*******************************************/
#ifndef ZC_COMM_CONFIG_DATA_H_
#define ZC_COMM_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ZCCOMMCONFIG_LINE_BYTE_NUM                   4U                          /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*通信配置表数据结构体*/
typedef struct BnfZcCommConfigStruct
{
	UINT32_S  zcSendAtsDataCycle;						/*ZC向ATS发送数据周期时间(ms)*/
}BnfZcCommConfigStruct;

/*******************************************
* 函数名	：  MallocZcCommConfigDataStru
* 功能描述	：	给ZcCommConfigDataStru结构体指针分配空间
* 输入：  UINT16_S lineNum 表的数据行数
* 输出：  无
* 返回值：  无
*******************************************/
void MallocZcCommConfigDataStru(UINT16_S lineNum);


/*******************************************
* 函数名	：  GetZcCommConfigData
* 功能描述	：	获取ZcCommConfigData数据
* 输入：  无
* 输出：  无
* 返回值：  BnfZcCommConfigStruct* ZcCommConfigData数据指针
*******************************************/
BnfZcCommConfigStruct *GetZcCommConfigData(void);

/*******************************************
* 函数名	：  GetZcCommConfigDataInfo
* 功能描述	：	获取ZcCommConfigData信息
* 输入：  无
* 输出：  UINT16* lineNum  数据行数
* 返回值： BnfZcCommConfigStruct* ZcCommConfigData信息指针
*******************************************/
BnfZcCommConfigStruct *GetZcCommConfigDataInfo(UINT16_S* lineNum);

/*******************************************
* 函数名	：  GetZcCommConfigDataStruzcSendAtsDataCycle
* 功能描述	：	获取指定IDZcCommConfigDataStru的ZC向ATS发送数据周期时间(ms)
* 输入：  无
* 输出：  无
* 返回值：  UINT32_NULL: 获取数据失败
*			!=UINT32_NULL: ZC向ATS发送数据周期时间(ms)
*******************************************/
UINT32_S GetZcCommConfigDataStruzcSendAtsDataCycle(void);

#ifdef __cplusplus
}
#endif

#endif
