/*************************************************
  文件名   ：StopSectionData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： StopSectionData数据管理
			DmuCommonData组件的StopSectionData功能可分解如下：
			1）	给StopSectionDataStru结构体指针分配空间
			2）	获取StopSectionData数据
			3）	获取StopSectionData信息
			4）	获取指定IDStopSectionDataStru的结构体下标
			5）	获取指定IDStopSectionDataStru的结构体指针
			6）	获取指定IDStopSectionDataStru的所属车站名称
			7）	获取指定dstCode的所属车站名称
			8）	获取指定IDStopSectionDataStru的目的地编号
			9）	获取指定IDStopSectionDataStru的停车区域seg编号
			10）	获取指定IDStopSectionDataStru的停车区域属性
			11）	获取指定IDStopSectionDataStru的站台最小停站时间
			12）	获取指定IDStopSectionDataStru的站台最大停站时间
			13）	获取指定IDStopSectionDataStru的站台默认停站时间
			14）	获取指定IDStopSectionDataStru的站台开门方式
			15）	获取指定IDStopSectionDataStru的站台开门时间间隔
			16）	获取指定IDStopSectionDataStru的站台关门方式
			17）	获取指定IDStopSectionDataStru的站台关门时间间隔
			18）	获取指定IDStopSectionDataStru的站台默认停稳时间
			19）	查询某个点是否属于转换轨
			20）	获取指定位置的停车区域属性
			21）	获取指定位置的停车区域ID
			22）	获取指定位置的停车区域信息
  备注    ：无。
 
*************************************************/
#ifndef STOPSECTION_DATA_H_
#define STOPSECTION_DATA_H_

#include "../../../Common/CommonTypes.h"

#define STOPSECTION_STATION_NAME_LEN                  20                                                       /*名称字节数*/
#define STOPSECTION_DEST_CODE_LEN                         4                                                       /*目的地编号长度*/
#define STOPSECTION_LINE_BYTE_NUM                      46                                                    /*一行数据字节数*/
#define STOPSECTION_MAX_PSD_NUM                        0x02                                                    /*同时需要控制的PSD最大数量,考虑一个站台有两侧PSD,所以定义为2*/



#ifdef __cplusplus
extern "C" {
#endif

/*停车区域表*/
typedef struct BnfStopSectionStruct
{
    UINT16_S  stopSectionId;                                                /*索引编号*/                    
    UINT8_S   stationName[STOPSECTION_STATION_NAME_LEN];                    /*所属车站名称*/
    UINT8_S   bDesId[STOPSECTION_DEST_CODE_LEN];                            /*目的地编号*/
    UINT16_S  segId;                                                        /*停车区域seg编号*/
    UINT16_S  sttribute;                                                    /*停车区域属性*/
    UINT16_S  minParkTime;                                                   /*站台最小停站时间*/
    UINT16_S  maxParkTime;                                                   /*站台最大停站时间*/
    UINT16_S  parkTime;                                                    /*站台默认停站时间*/
    UINT16_S  doorOpenMode;                                                /*站台开门方式*/
    UINT16_S  doorOpenTime;                                                /*站台开门时间间隔*/
    UINT16_S  doorCloseMode;                                                /*站台关门方式*/
    UINT16_S  doorCloseTime;                                                /*站台关门时间间隔*/
    UINT16_S  parkSteadyTime;                                                /*站台默认停稳时间*/

    
    /*动态计算字段*/
    UINT8_S  psdNum;                                                        /*站台中屏蔽门数量*/
    UINT16_S  psdId[STOPSECTION_MAX_PSD_NUM];                                /*安全屏蔽门编号*/
    UINT16_S  manageZCId;                                                    /*所属ZC区域ID*/
    UINT16_S  manageCIId;                                                    /*所属CI区域ID*/ 
}BnfStopSectionStruct;

/*
* 功能描述： 给StopSectionDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocStopSectionDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取StopSectionData数据
* 参数说明：
* 返回值  ： 
            BnfStopSectionStruct*
*/
BnfStopSectionStruct *GetStopSectionData(void);

/*
* 功能描述： 获取StopSectionData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfStopSectionStruct*
*/
BnfStopSectionStruct *GetStopSectionDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDStopSectionDataStru的结构体下标
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetStopSectionDataStruIndex(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的结构体指针
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStopSectionStruct* GetIndexIdStopSectionDataStru(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的所属车站名称
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 所属车站名称
*/ 
UINT8_S* GetStopSectionDataStrustationName(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定dstCode的所属车站名称
* 参数说明： const UINT16_S dstCode;
* 返回值  :  NULL: 获取数据失败
*            !NULL: 所属车站名称
*/ 
UINT8_S* GetStopSecNameByDstCode(const UINT16_S dstCode);


/*
** 功能描述： 获取指定IDStopSectionDataStru的目的地编号
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 目的地编号
*/ 
UINT8_S* GetStopSectionDataStrubDesId(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的停车区域seg编号
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车区域seg编号
*/ 
UINT16_S GetStopSectionDataStrusegId(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的停车区域属性
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 停车区域属性
*/ 
UINT16_S GetStopSectionDataStrusttribute(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台最小停站时间
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台最小停站时间
*/ 
UINT16_S GetStopSectionDataStruminParkTime(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台最大停站时间
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台最大停站时间
*/ 
UINT16_S GetStopSectionDataStrumaxParkTime(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台默认停站时间
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台默认停站时间
*/ 
UINT16_S GetStopSectionDataStruparkTime(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台开门方式
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台开门方式
*/ 
UINT16_S GetStopSectionDataStrudoorOpenMode(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台开门时间间隔
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台开门时间间隔
*/ 
UINT16_S GetStopSectionDataStrudoorOpenTime(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台关门方式
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台关门方式
*/ 
UINT16_S GetStopSectionDataStrudoorCloseMode(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台关门时间间隔
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台关门时间间隔
*/ 
UINT16_S GetStopSectDataDoorCTim(const UINT16_S stopSectionId);

/*
** 功能描述： 获取指定IDStopSectionDataStru的站台默认停稳时间
* 参数说明： const UINT16_S stopSectionId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 站台默认停稳时间
*/ 
UINT16_S GetStopSectionDataStruparkSteadyTime(const UINT16_S stopSectionId);

/*
* 功能描述： 查询某个点是否属于转换轨
* 参数说明： 
* 返回值  ： 0: 不属于
*             1: 属于
*/
UINT8_S CheckPointBelongToZHG(UINT16_S wTrainHeadSeg);

/*
** 功能描述： 获取指定位置的停车区域属性
* 参数说明： const UINT16_S segId;SEGID
*             const UINT32_S offset;偏移量
*             const UINT8_S dir;运行方向
* 返回值  :   0: 此SEGID没有停车区域
*             >0: 停车区域属性
*/ 
UINT16_S GetCurSegOfStopSecType(const UINT16_S segId);

/*
** 功能描述： 获取指定位置的停车区域ID
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :   0: 此SEGID没有停车区域
*             >0: 停车区域ID
*/ 
UINT16_S GetCurSegOfStopSecId(const UINT16_S segId);

/*
** 功能描述： 获取指定位置的停车区域信息
* 参数说明： const UINT16_S segId;SEGID
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfStopSectionStruct* GetCurSegOfStopSecInfo(const UINT16_S segId);

#ifdef __cplusplus
}
#endif

#endif
