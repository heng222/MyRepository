/*************************************************
  文件名   ：PlatFormData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： PlatFormData数据管理
			DmuCommonData组件的PlatFormData功能可分解如下：
			1）	给PlatFormDataStru结构体指针分配空间
			2）	获取PlatFormData数据
			3）	获取PlatFormData信息
			4）	获取指定IDPlatFormDataStru的结构体下标
			5）	获取指定IDPlatFormDataStru的结构体指针
			6）	 获取指定IDPlatFormDataStru的站台中心公里标
			7）	获取指定IDPlatFormDataStru的站台关联seg编号
			8）	获取指定IDPlatFormDataStru的逻辑方向上站台相对于停车区域的方向
			9）	获取此SEG对应的站台ID
			10）	查找此计轴区段是否属于站台区域
			11）	获取此SEG对应的站台ID(支持多个Seg)
			12）	获取此SEG对应的站台ID
  备注    ：无。
 
*************************************************/
#ifndef PLATFORM_DATA_H_
#define PLATFORM_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  PLATFORM_NAME_BYTE_LEN      16                            /*名称长度*/
#define  PLATFORM_LINE_BYTE_NUM         21                            /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*站台表*/
typedef struct BnfPlatFormStruct
{
    UINT16_S  platFormId;                                    /*站台ID*/
    UINT8_S   platFormKillPost[PLATFORM_NAME_BYTE_LEN];    /*站台中心公里标*/
    UINT16_S  segId;                                        /*站台关联seg编号*/
    UINT8_S   dir;                                        /*逻辑方向上站台相对于停车区域的方向*/
}BnfPlatFormStruct;

/*
* 功能描述： 给PlatFormDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocPlatFormDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取PlatFormData数据
* 参数说明：
* 返回值  ： 
            BnfPlatFormStruct*
*/
BnfPlatFormStruct *GetPlatFormData(void);

/*
* 功能描述： 获取PlatFormData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfPlatFormStruct*
*/
BnfPlatFormStruct *GetPlatFormDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDPlatFormDataStru的结构体下标
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetPlatFormDataStruIndex(const UINT16_S platFormId);

/*
** 功能描述： 获取指定IDPlatFormDataStru的结构体指针
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfPlatFormStruct* GetIndexIdPlatFormDataStru(const UINT16_S platFormId);

/*
** 功能描述： 获取指定IDPlatFormDataStru的站台中心公里标
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 站台中心公里标
*/ 
UINT8_S* GetPlatFormDataStruplatFormKillPost(const UINT16_S platFormId);

/*
** 功能描述： 获取指定IDPlatFormDataStru的站台关联seg编号
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  0: 获取数据失败
*            >0: 站台关联seg编号
*/ 
UINT16_S GetPlatFormDataStrusegId(const UINT16_S platFormId);

/*
** 功能描述： 获取指定IDPlatFormDataStru的逻辑方向上站台相对于停车区域的方向
* 参数说明： const UINT16_S platFormId;站台ID
* 返回值  :  0: 获取数据失败
*            >0: 逻辑方向上站台相对于停车区域的方向
*/ 
UINT8_S GetPlatFormDataStrudir(const UINT16_S platFormId);

/*
** 功能描述： 获取此SEG对应的站台ID
* 参数说明： const UINT16_S segId;SEGID
*             UINT16_S* platFormIdBuff  站台ID
* 返回值  :  Oxff: 获取数据失败
*            >=0: 站台ID个数
*/ 
UINT8_S GetSegIdBelongOfStationId(const UINT16_S* segIdBuff,UINT8_S segIdNum,UINT16_S* platFormIdBuff);

/*
* 功能描述： 查找此计轴区段是否属于站台区域
* 参数说明： const UINT16_S* pSegId;SEGID指针
* 返回值  :  1 属于
*             2 不属于
*/ 
UINT8_S SearchStationBelongAxleSec(const UINT16_S* pSegId,UINT16_S includeSegNum);

/*
** 功能描述： 获取此SEG对应的站台ID
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :  0: 获取数据失败
*            >0: 站台个数
*/ 
UINT8_S GetPlatformIdAccordSegBuff(const UINT16_S* pSegId,const UINT8_S segNum,UINT16_S* pPlatformId);

/*
** 功能描述： 获取此SEG对应的站台ID
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :  0: 获取数据失败
*            >0: 站台ID
*/ 
UINT16_S GetPlatformIdAccordSegId(const UINT16_S segId);

#ifdef __cplusplus
}
#endif

#endif
