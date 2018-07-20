/*************************************************
  文件名   ：EmergStopButtonData.h
  作者     ：董欣      
  创建时间 ：2016-8-12
  功能描述 ： EmergStopButtonData数据管理
			DmuCommonData组件的EmergStopButtonData功能可分解如下：
			1）	给EmergStopButtonDataStru结构体指针分配空间
			2）	获取EmergStopButtonData数据
			3）	获取EmergStopButtonData信息
			4）	获取指定IDEmergStopButtonDataStru的结构体下标
			5）	获取指定IDEmergStopButtonDataStru的结构体指针
			6）	 获取指定IDEmergStopButtonDataStru的名称
			7）	获取指定IDEmergStopButtonDataStru的所属站台编号
			8）	获取线路紧急停车按钮最大ID
			9）	获取线路紧急停车按钮所属站台ID
			10）	根据输入的SEGID获取ESB信息
			11）	根据站台ID获取对应的紧急停车按钮ID
			12）	获取线路紧急停车按钮所属ZC
			13）	获取线路紧急停车按钮所属ci
  备注    ：无。
 
*************************************************/
#ifndef EMERGSTOPBUTTON_DATA_H_
#define EMERGSTOPBUTTON_DATA_H_

#include "../../../Common/CommonTypes.h"

#define EMERGSTOPBUTTON_NAME_BYTE_LEN                 12                                /*名称长度*/
#define EMERGSTOPBUTTON_LINE_BYTE_NUM                 16                                /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*EmergStopButton表数据结构体*/
typedef struct BnfEmergStopButtonStruct
{
    UINT16_S  emergStopButtonId;                                    /*索引编号*/
    UINT8_S   name[EMERGSTOPBUTTON_NAME_BYTE_LEN];                /*名称*/
    UINT16_S  stationId;                                            /*所属站台编号*/

    /*动态计算字段*/
    UINT16_S  manageZCId;                                            /*所属ZC区域ID*/
    UINT16_S  manageCIId;                                            /*所属CI区域ID*/ 
    UINT16_S  segId;                                                /*获取SEG所属的SEGID*/
}BnfEmergStopButtonStruct;

/*
* 功能描述： 给EmergStopButtonDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocEmergStopButtonDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取EmergStopButtonData数据
* 参数说明：
* 返回值  ： 
            BnfEmergStopButtonStruct*
*/
BnfEmergStopButtonStruct *GetEmergStopButtonData(void);

/*
* 功能描述： 获取EmergStopButtonData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfEmergStopButtonStruct*
*/
BnfEmergStopButtonStruct *GetEmergStopButtonDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDEmergStopButtonDataStru的结构体下标
* 参数说明： const UINT16_S emergStopButtonId;索引编号
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetEmergStopButtonDataStruIndex(const UINT16_S emergStopButtonId);

/*
** 功能描述： 获取指定IDEmergStopButtonDataStru的结构体指针
* 参数说明： const UINT16_S emergStopButtonId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfEmergStopButtonStruct* GetIndexIdEmergStopButtonDataStru(const UINT16_S emergStopButtonId);

/*
** 功能描述： 获取指定IDEmergStopButtonDataStru的名称
* 参数说明： const UINT16_S emergStopButtonId;索引编号
* 返回值  :  NULL: 获取数据失败
*            !NULL: 名称
*/ 
UINT8_S* GetEmergStopButtonDataStruname(const UINT16_S emergStopButtonId);

/*
** 功能描述： 获取指定IDEmergStopButtonDataStru的所属站台编号
* 参数说明： const UINT16_S emergStopButtonId;索引编号
* 返回值  :  0: 获取数据失败
*            >0: 所属站台编号
*/ 
UINT16_S GetEmergStopButtonDataStrustationId(const UINT16_S emergStopButtonId);
/*
* 功能描述： 获取线路紧急停车按钮最大ID
* 参数说明： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:紧急停车按钮最大ID
*/
UINT16_S GetLineEsbMaxId(void);

/*
* 功能描述： 获取线路紧急停车按钮所属站台ID
* 参数说明： const UINT16_S esbId,紧急停车按钮ID
* 返回值  ： 0xffff: 获取数据失败
*            >0:所属站台ID
*/
UINT16_S GetLineEsbBelongStationId(const UINT16_S esbId);

/*
** 功能描述： 根据输入的SEGID获取ESB信息
* 参数说明： 输入:const UINT16_S stationIdBuff,站台ID
*             const UINT8_S stationIdNum    站台ID个数
*             UINT16_S index*    数组偏移                  
*             输入输出:UINT16_S esbIdBuff[],ESBID数组      
* 返回值  :  0: 获取数据失败
*            >0: ESB信息
*/ 
UINT16_S GetStationIdBelongofEsbInfo(const UINT16_S* stationIdBuff,const UINT8_S stationIdNum,UINT16_S index,UINT16_S esbIdBuff[]);

/*
** 功能描述： 根据站台ID获取对应的紧急停车按钮ID
* 参数说明： const UINT16_S pPlatformId;站台ID
*             const UINT8_S platformNum  站台ID个数
*             UINT16_S*  pPsdId          屏蔽门ID指针
* 返回值  :  0: 获取数据失败
*            >0: 紧急停车按钮个数
*/ 
UINT8_S GetEsbIdAccordPlatformIdBuff(const UINT16_S* pPlatformId,const UINT8_S platformNum,UINT16_S* pEsbId);

/*
* 功能描述： 获取线路紧急停车按钮所属ZC
* 参数说明： const UINT16_S esbId,紧急停车按钮ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCId
*/
UINT16_S GetLineEsbBelongZcId(const UINT16_S esbId);

/*
* 功能描述： 获取线路紧急停车按钮所属ci
* 参数说明： const UINT16_S esbId,紧急停车按钮ID
* 返回值  ： 0: 获取数据失败
*            >0:所属ciId
*/
UINT16_S GetLineEsbBelongCiId(const UINT16_S esbId);

#ifdef __cplusplus
}
#endif

#endif
