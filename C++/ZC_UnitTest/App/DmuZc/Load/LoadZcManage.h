/*******************************************
* 文件名	：  LoadZcManage.h
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	载入ZC管理
* 备  注	：  无
*******************************************/
#ifndef LOADZC_MANAGE_H_
#define LOADZC_MANAGE_H_

#include "../../../Common/CommonTypes.h"

#define LOADZC_OBJECT_MAX   50U

/*载入数据结构体*/
typedef struct LoadZCObjectStruct
{
	INT8_S (*LoadData)(void); /*载入数据*/
} LoadZCObjectStruct;

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
* 功能描述： 载入ZC相关数据管理
* 参数说明： void
* 返回值  ： void       
*/
void LoadZcManage(void);

/*******************************************
* 功能描述： 载入ZC数据
* 参数说明： void
* 返回值  ： 0:成功返回
*           -1:错误返回
*/
INT8_S LoadZcData(void);

#ifdef __cplusplus
}
#endif

#endif
