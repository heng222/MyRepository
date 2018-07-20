/************************************************************************
*
* 文件名   ：  DataVersionInitManage.h
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  数据版本初始化管理
* 备  注   ：  无
*
************************************************************************/
#ifndef DATA_VERSION_INIT_MANAGE_H_
#define DATA_VERSION_INIT_MANAGE_H_

#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif
	
	/*
	* 功能描述： 初始化本地数据版本信息
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			 1: 初始化成功
	*/
	UINT8_S InitLocalDataVersion(void);

	/*
	* 功能描述： 初始化本地数据版本信息(ZC字节数据版本)
	* 参数说明： 无   
	* 返回值  ： 0: 初始化失败
	*			 1: 初始化成功
	*/
	UINT8_S InitLocalZcSelfDataVersion(void);

    /*
    * 功能描述： 初始化本地数据版本信息(ZC和ATP数据版本)
    * 参数说明： 无   
    * 返回值  ： 0: 初始化失败
    *			 1: 初始化成功
    */
    UINT8_S InitZcAtpDataVersion(void);

#ifdef __cplusplus
}
#endif

#endif
