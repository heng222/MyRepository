/********************************************************
* 
* 文 件 名： LoadManage.h 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 载入管理头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef LOAD_MANAGE_H_
#define LOAD_MANAGE_H_

#include "../../../Common/CommonTypes.h"

#define LOAD_OBJECT_MAX   50

/*载入数据结构体*/
typedef struct LoadObjectStruct
{
    INT8_S (*LoadData)(void); /*载入数据*/
} LoadObjectStruct;

#ifdef __cplusplus
extern "C" {
#endif

/*
* 功能描述： 载入线路数据管理
* 参数说明： void
* 返回值  ： void       
*/
void LoadLineDataManage(void);

/*
* 功能描述： 载入运营数据管理
* 参数说明： void
* 返回值  ： void       
*/
void LoadRunDataManage(void);

/*
* 功能描述： 载入系统配置数据管理
* 参数说明： void
* 返回值  ： void       
*/
void LoadSystemDataManage(void);

/*
* 功能描述： 载入分界点数据管理
* 参数说明： void
* 返回值  ： void       
*/
void LoadDividPointDataManage(void);

/*
* 功能描述： 载入数据
* 参数说明： void
* 返回值  ： 0:成功返回
*           -1:错误返回
*/
INT8_S LoadData(void);

#ifdef __cplusplus
}
#endif

#endif
