/*************************************************
  文件名   ：StaticResSpeedData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： StaticResSpeedData数据管理
			DmuCommonData组件的StaticResSpeedData功能可分解如下：
			1）	给StaticResSpeedDataStru结构体指针分配空间
			2）	获取StaticResSpeedData数据
			3）	获取StaticResSpeedData信息
			4）	获取指定IDStaticResSpeedDataStru的结构体下标
			5）	 获取指定IDStaticResSpeedDataStru的结构体指针
			6）	获取指定IDStaticResSpeedDataStru的该限速区域所处Seg编号
			7）	获取指定IDStaticResSpeedDataStru的起点所处Seg偏移量(cm)
			8）	 获取指定IDStaticResSpeedDataStru的终点所处Seg偏移量(cm)
			9）	获取指定IDStaticResSpeedDataStru的静态限速值
			10）	获取指定的SEGID获取相关信息
  备注    ：无。
 
*************************************************/
#ifndef STATICRESSPEED_DATA_H_
#define STATICRESSPEED_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  STATICRESSPEED_LINE_BYTE_NUM        16                   /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*静态限速表*/
typedef struct BnfStaticResSpeedStruct
{ 
    UINT16_S  staticResSpeedId;                /*编号*/
    UINT16_S  segId;                            /*该限速区域所处Seg编号*/
    UINT32_S  orgnSegOfst;                    /*起点所处Seg偏移量(cm)*/
    UINT32_S  tmnlSegOfst;                    /*终点所处Seg偏移量(cm)*/
    UINT16_S  relateSwitchId;                    /*关联道岔ID*/
    UINT16_S  staticSpeed;                    /*静态限速值*/
}BnfStaticResSpeedStruct;

/*
* 功能描述： 给StaticResSpeedDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocStaticResSpeedDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取StaticResSpeedData数据
* 参数说明：
* 返回值  ： 
            BnfStaticResSpeedStruct*
*/
BnfStaticResSpeedStruct *GetStaticResSpeedData(void);

/*
* 功能描述： 获取StaticResSpeedData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfStaticResSpeedStruct*
*/
BnfStaticResSpeedStruct *GetStaticResSpeedDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的结构体下标
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetStaticResSpeedDataStruIndex(const UINT16_S staticResSpeedId);

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的结构体指针
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStaticResSpeedStruct* GetIndexIdStaticResSpeedDataStru(const UINT16_S staticResSpeedId);

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的该限速区域所处Seg编号
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0: 获取数据失败
*            >0: 该限速区域所处Seg编号
*/ 
UINT16_S GetStaticResSpeedDataStrusegId(const UINT16_S staticResSpeedId);

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的起点所处Seg偏移量(cm)
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0: 获取数据失败
*            >0: 起点所处Seg偏移量(cm)
*/ 
UINT32_S GetStaticResSpeedDataStruorgnSegOfst(const UINT16_S staticResSpeedId);

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的终点所处Seg偏移量(cm)
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0: 获取数据失败
*            >0: 终点所处Seg偏移量(cm)
*/ 
UINT32_S GetStaticResSpeedDataStrutmnlSegOfst(const UINT16_S staticResSpeedId);

/*
** 功能描述： 获取指定IDStaticResSpeedDataStru的静态限速值
* 参数说明： const UINT16_S staticResSpeedId;编号
* 返回值  :  0: 获取数据失败
*            >0: 静态限速值
*/ 
UINT16_S GetStaticResSpeedDataStrustaticSpeed(const UINT16_S staticResSpeedId);

/*
* 功能描述： 获取指定的SEGID获取相关信息
* 参数说明： 输入参数:const UINT16_S segId;编号
*                      const UINT32_S startOffset  起点偏移量
*                      const UINT32_S endOffset    终点偏移量
*             输出参数:UINT16_S* limitSpeed  限速值
* 返回值  :  0: 获取数据失败
*             1: 查找成功
*/ 
UINT8_S GetSegIdOfLimitSpeed(const UINT16_S segId,const UINT32_S startOffset,const UINT32_S endOffset,UINT16_S* limitSpeed);

#ifdef __cplusplus
}
#endif

#endif
