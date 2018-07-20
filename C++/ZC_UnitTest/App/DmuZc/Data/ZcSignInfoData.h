/*******************************************
* 文件名	：  ZcSignInfoData.h
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	载入ZcSignInfoData数据管理
* 备  注	：  无
*******************************************/
#ifndef ZCSIGNINFO_DATA_H_
#define ZCSIGNINFO_DATA_H_

#include "../../../Common/CommonTypes.h"

#define ZCSIGNINFO_LINE_BYTE_NUM                 6U                           	/*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*ZC信号机表数据结构体*/
typedef struct BnfZcSignInfoStruct
{
	UINT16_S  signId;						/*信号机ID*/
	UINT16_S  throughSignFlag;            /*闯信号标志*/
	UINT16_S  lightFlag;                  /*亮灭标志*/
}BnfZcSignInfoStruct;

/*******************************************
* 函数名	：  MallocZcSignInfoDataStru
* 功能描述	：	分配 ZcSignInfoDataStru
* 输入：  无
* 输出：  无
* 返回值  :  NULL: 获取数据失败
*			!NULL: 成功
*******************************************/
void MallocZcSignInfoDataStru(UINT16_S lineNum);


/*******************************************
* 函数名	：  GetZcSignInfoData
* 功能描述	：	获取ZcSignInfoData数据
* 输入：  无
* 输出：  无
* 返回值  :  NULL: 获取数据失败
*			!NULL: 成功
*******************************************/
BnfZcSignInfoStruct *GetZcSignInfoData(void);

/*******************************************
* 函数名	：
* 功能描述： 获取ZcSignInfoData信息
* 参数说明：输出参数:UINT16* lineNum  数据行数
* 返回值  ： 
			BnfZcSignInfoStruct*
*/
BnfZcSignInfoStruct *GetZcSignInfoDataInfo(UINT16_S* lineNum);
/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSignInfoDataStru的结构体下标
* 参数说明： const UINT16 signId;信号机ID
* 返回值  :  0xFFFF: 获取数据失败
*			<0xFFFF: 查找成功
*/ 
UINT16_S GetZcSignInfoDataStruIndex(const UINT16_S signId);

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSignInfoDataStru的结构体指针
* 参数说明： const UINT16 signId;信号机ID
* 返回值  :  NULL: 获取数据失败
*			!NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfZcSignInfoStruct* GetIndexIdZcSignInfoDataStru(const UINT16_S signId);

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSignInfoDataStru的闯信号标志
* 参数说明： const UINT16 signId;信号机ID
* 返回值  :  0: 获取数据失败
*			>0: 闯信号标志
*/ 
UINT16_S GetZcSignInfoDataStruthroughSignFlag(const UINT16_S signId);

/*******************************************
* 函数名	：
** 功能描述： 获取指定IDZcSignInfoDataStru的亮灭标志
* 参数说明： const UINT16 signId;信号机ID
* 返回值  :  0: 获取数据失败
*			>0: 亮灭标志
*/ 
UINT16_S GetZcSignInfoDataStrulightFlag(const UINT16_S signId);


#ifdef __cplusplus
}
#endif

#endif
