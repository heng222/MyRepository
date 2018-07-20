/*******************************************
* 文件名	：  LoadZcCommConfig.h
* 作  者	：  ZC组
* 创建时间	：  2015-5-25
* 功能描述	：	载入ZcCommConfig数据
* 备  注	：  无
*******************************************/
#ifndef LOAD_ZCCOMMCONFIG_H_
#define LOAD_ZCCOMMCONFIG_H_


#include "../../../Common/CommonTypes.h"
#include "../Data/ZcCommConfigData.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
* 函数名	：
* 功能描述： 载入ZcCommConfig数据
* 参数说明： void
* 返回值  ： 0:成功
*			-2 数据长度错误
*			-1 函数指针为空
*			1接口防护错误
*			2传入的数据类型和表单编号错误
*/
INT8_S LoadZcCommConfigData(void);

#ifdef __cplusplus
}
#endif
#endif
