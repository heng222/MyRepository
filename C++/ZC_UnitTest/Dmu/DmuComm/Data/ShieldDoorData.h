/*************************************************
  文件名   ：ShieldDoorData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： ShieldDoorData数据管理
			DmuCommonData组件的ShieldDoorData功能可分解如下：
			1）	给ShieldDoorDataStru结构体指针分配空间
			2）	获取ShieldDoorData数据
			3）	获取ShieldDoorData信息
			4）	获取指定IDShieldDoorDataStru的结构体下标
			5）	获取指定IDShieldDoorDataStru的结构体指针
			6）	获取指定IDShieldDoorDataStru的名称
			7）	获取指定IDShieldDoorDataStru的所属站台编号
			8）	获取线路屏蔽门最大ID
			9）	查询站台表获取此站台对应的PSD信息
			10）	获取此SEG对应的屏蔽门ID
			11）	获取线路屏蔽门所属ZC
			12）	获取线路屏蔽门所属CI

  备注    ：无。
 
*************************************************/
#ifndef SHIELDDOOR_DATA_H_
#define SHIELDDOOR_DATA_H_

#include "../../../Common/CommonTypes.h"

#define SHIELDDOOR_NAME_BYTE_LEN                  12                            /*名称长度*/
#define SHIELDDOOR_LINE_BYTE_NUM                  16                            /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*屏蔽门表数据结构体*/
typedef struct BnfShieldDoorStruct
{
    UINT16_S  shieldDoorId;                        /*索引编号*/
    UINT8_S   name[SHIELDDOOR_NAME_BYTE_LEN];        /*名称*/
    UINT16_S  stationId;                            /*所属站台编号*/

    /*动态计算字段*/
    UINT16_S  manageZCId;                            /*所属ZC区域ID*/
    UINT16_S  manageCIId;                            /*所属CI区域ID*/ 
    UINT16_S  segId;                                /*所在的位置ID*/
    UINT8_S   dir;                                /*逻辑方向上站台相对于停车区域的方向*/
}BnfShieldDoorStruct;

/*
* 功能描述： 给ShieldDoorDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocShieldDoorDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取ShieldDoorData数据
* 参数说明：
* 返回值  ： 
            BnfShieldDoorStruct*
*/
BnfShieldDoorStruct *GetShieldDoorData(void);

/*
* 功能描述： 获取ShieldDoorData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfShieldDoorStruct*
*/
BnfShieldDoorStruct *GetShieldDoorDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDShieldDoorDataStru的结构体下标
* 参数说明： const UINT16_S shieldDoorId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetShieldDoorDataStruIndex(const UINT16_S shieldDoorId);

/*
** 功能描述： 获取指定IDShieldDoorDataStru的结构体指针
* 参数说明： const UINT16_S shieldDoorId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfShieldDoorStruct* GetIndexIdShieldDoorDataStru(const UINT16_S shieldDoorId);

/*
** 功能描述： 获取指定IDShieldDoorDataStru的名称
* 参数说明： const UINT16_S shieldDoorId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetShieldDoorDataStruname(const UINT16_S shieldDoorId);

/*
** 功能描述： 获取指定IDShieldDoorDataStru的所属站台编号
* 参数说明： const UINT16_S shieldDoorId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属站台编号
*/ 
UINT16_S GetShieldDoorDataStrustationId(const UINT16_S shieldDoorId);

/*
* 功能描述： 获取线路屏蔽门最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:屏蔽门最大ID
*/
UINT16_S GetLinePsdMaxId(void);

/*
* 功能描述： 查询站台表获取此站台对应的PSD信息
* 参数说明： 输入:const UINT16_S stationId,站台ID
*             const UINT8_S stationIdNum   站台个数
*             UINT16_S index    数组偏移                  
*             输入输出:UINT16_S psdIdBuff[],屏蔽门ID数组          
* 返回值  ： >=0:屏蔽门个数
*/
UINT16_S GetStationIdBelongofPsdInfo(const UINT16_S* stationIdBuff,const UINT8_S stationIdNum,UINT16_S index,UINT16_S psdIdBuff[]);

/*
** 功能描述： 获取此SEG对应的屏蔽门ID
* 参数说明： const UINT16_S pPlatformId;站台ID
*             const UINT8_S platformNum  站台ID个数
*             UINT16_S*  pPsdId          屏蔽门ID指针
* 返回值  :  0: 获取数据失败
*            >0: 屏蔽门个数
*/ 
UINT8_S GetPsdIdAccordPlatformIdBuff(const UINT16_S* pPlatformId,const UINT8_S platformNum,UINT16_S* pPsdId);

/*
* 功能描述： 获取线路屏蔽门所属ZC
* 参数说明： const UINT16_S psdId,屏蔽门ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLinePsdBelongZcId(const UINT16_S psdId);

/*
* 功能描述： 获取线路屏蔽门所属CI
* 参数说明： const UINT16_S psdId,屏蔽门ID
* 返回值  ： 0: 获取数据失败
*            >0:所属CIId
*/
UINT16_S GetLinePsdBelongCiId(const UINT16_S psdId);

#ifdef __cplusplus
}
#endif

#endif
