/*************************************************
  文件名   ：ArData.h
  作者     ：董欣      
  创建时间 ：2016-8-10
  功能描述 ： 载入ArData数据管理
				 DmuCommonData组件ArData.c 功能可分解如下：
				1）	给ArDataStru结构体指针分配空间
				2）	 获取ArData数据
				3）	获取ArData信息
				4）	获取指定IDArDataStru的结构体下标
				5）	获取指定IDArDataStru的结构体指针
				6）	获取指定IDArDataStru的无人折返出发站台编号
				7）	获取指定IDArDataStru的进入点对应停车点编号
				8）	获取指定IDArDataStru的换端点对应停车点编号
				9）	获取指定IDArDataStru的退出站台编号
				10）	获取指定IDArDataStru的退出点对应停车点编号
				11）	获取指定IDArDataStru的无人折返灯ID
				12）	获取指定IDArDataStru的无人折返按钮ID
				13）	获取线路无人折返按钮最大ID
				14）	获取线路无人折返按钮ID对应的进入点对应停车点编号
				15）	 获取线路无人折返灯最大ID
				16）	获取线路无人折返灯ID对应的进入点对应停车点编号
				17）	获取线路无人折返按钮所属ZCid
				18）	获取线路无人折返按钮所属CIid
				19）	获取线路无人折返灯所属ZCID
				20）	获取线路无人折返灯所属CIid
				21）	判断此停车点是否在无人折返表中存在
				22）	判断此停车点是否在无人折返表中的退出区域

  备注    ：无。
 
*************************************************/

#ifndef AR_DATA_H_
#define AR_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  AR_LINE_BYTE_NUM                   16                           /*一行数据的字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*无人折返表表数据结构体*/
typedef struct BnfArStruct
{ 
    UINT16_S  arId;                            /*编号*/
    UINT16_S  startPlartformId;                /*无人折返出发站台编号*/
    UINT16_S  arInStopPointId;                /*进入点对应停车点编号*/
    UINT16_S  revertPointId;                    /*换端点对应停车点编号*/
    UINT16_S  endPlartformId;                    /*退出站台编号*/
    UINT16_S  aROutStopPointId;                /*退出点对应停车点编号*/
    UINT16_S  aRLampID;                        /*无人折返灯ID*/
    UINT16_S  aRButtonId;                        /*无人折返按钮ID*/

    /*动态计算字段*/
    UINT16_S  manageZCId;                        /*所属ZC区域ID*/
    UINT16_S  manageCIId;                        /*所属CI区域ID*/ 
}BnfArStruct;

/*
* 函数名称：MallocArDataStru
* 功能描述： 给ArDataStru结构体指针分配空间
* 输入参数： UINT16_S lineNum 表的数据行数
* 输出参数： 无
* 返回值  ： void
*/
void MallocArDataStru(UINT16_S lineNum);


/*
* 函数名称：GetArData
* 功能描述： 获取ArData数据
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 
BnfArStruct*
*/
BnfArStruct *GetArData(void);

/*
* 函数名称：GetArDataInfo
* 功能描述： 获取ArData信息
* 输入参数：无
* 输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
BnfArStruct* 
*/
BnfArStruct *GetArDataInfo(UINT16_S* lineNum);
/*
* 函数名称：GetArDataStruIndex
* 功能描述： 获取指定IDArDataStru的结构体下标
* 输入参数： const UINT16_S arId;编号
* 输出参数： 无
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/  
UINT16_S GetArDataStruIndex(const UINT16_S arId);

/*
* 函数名称：GetIndexIdArDataStru
* 功能描述： 获取指定IDArDataStru的结构体指针
* 输人参数： const UINT16_S arId;编号
* 输出参数： 无
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfArStruct* GetIndexIdArDataStru(const UINT16_S arId);

/*
* 函数名称：GetArDataStrustartPlartformId
* 功能描述： 获取指定IDArDataStru的无人折返出发站台编号
* 输入参数： const UINT16_S arId;编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 无人折返出发站台编号
*/ 
UINT16_S GetArDataStrustartPlartformId(const UINT16_S arId);

/*
* 函数名称：GetArDataStruarInStopPointId
* 功能描述： 获取指定IDArDataStru的进入点对应停车点编号
* 输入参数： const UINT16_S arId;编号
* 输出参数：无
* 返回值  :  0: 获取数据失败
*            >0: 进入点对应停车点编号
*/ 
UINT16_S GetArDataStruarInStopPointId(const UINT16_S arId);

/*
* 函数名称：GetArDataStrurevertPointId
* 功能描述： 获取指定IDArDataStru的换端点对应停车点编号
* 输入参数： const UINT16_S arId;编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 换端点对应停车点编号
*/ 
UINT16_S GetArDataStrurevertPointId(const UINT16_S arId);

/*
* 函数名称：GetArDataStruendPlartformId
* 功能描述： 获取指定IDArDataStru的退出站台编号
* 输入参数： const UINT16_S arId;编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 退出站台编号
*/ 
UINT16_S GetArDataStruendPlartformId(const UINT16_S arId);

/*
* 函数名称：GetArDataStruaROutStopPointId
* 功能描述： 获取指定IDArDataStru的退出点对应停车点编号
* 输入参数： const UINT16_S arId;编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 退出点对应停车点编号
*/ 
UINT16_S GetArDataStruaROutStopPointId(const UINT16_S arId);

/*
* 函数名称：GetArDataStruaRLampID
* 功能描述： 获取指定IDArDataStru的无人折返灯ID
* 输入参数： const UINT16_S arId;编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 无人折返灯ID
*/ 
UINT16_S GetArDataStruaRLampID(const UINT16_S arId);

/*
* 函数名称：GetArDataStruaRButtonId
* 功能描述： 获取指定IDArDataStru的无人折返按钮ID
* 输入参数： const UINT16_S arId;编号
* 输出参数： 无
* 返回值  :  0: 获取数据失败
*            >0: 无人折返按钮ID
*/ 
UINT16_S GetArDataStruaRButtonId(const UINT16_S arId);

/*
* 函数名称：GetLineDrButtonMaxId
* 功能描述： 获取线路无人折返按钮最大ID
* 输入参数： 无
* 输出参数： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:无人折返按钮最大ID
*/
UINT16_S GetLineDrButtonMaxId(void);

/*
* 函数名称：GetLineDrButtonBelongPointId
* 功能描述： 获取线路无人折返按钮ID对应的进入点对应停车点编号
* 输出参数： const UINT16_S arButtonId   无人折返按钮ID
* 输入参数： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:进入点对应停车点编号
*/
UINT16_S GetLineDrButtonBelongPointId(const UINT16_S arButtonId);

/*
* 函数名称：GetLineDrLampMaxId
* 功能描述： 获取线路无人折返灯最大ID
* 输入参数： 无
* 输入参数： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:无人折返灯最大ID
*/
UINT16_S GetLineDrLampMaxId(void);

/*
* 函数名称：GetLineDrLampBelongPointId
* 功能描述： 获取线路无人折返灯ID对应的进入点对应停车点编号
* 输入参数： const UINT16_S arLampID   无人折返灯ID
* 输出参数： 无
* 返回值  ： 0xffff: 获取数据失败
*            >0:进入点对应停车点编号
*/
UINT16_S GetLineDrLampBelongPointId(const UINT16_S arLampID);

/*
* 函数名称：GetLineDrButtonBelongZcId
* 功能描述： 获取线路无人折返按钮所属ZCid
* 输入参数： const UINT16_S drButtonId,无人折返按钮
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCid
*/
UINT16_S GetLineDrButtonBelongZcId(const UINT16_S drButtonId);

/*
* 函数名称：GetLineDrButtonBelongCiId
* 功能描述： 获取线路无人折返按钮所属CIid
* 输入参数： const UINT16_S drButtonId,无人折返按钮
* 输出参数：无
* 返回值  ： 0: 获取数据失败
*            >0:所属CIid
*/
UINT16_S GetLineDrButtonBelongCiId(const UINT16_S drButtonId);

/*
* 函数名称：GetLineDrLampBelongZcId
* 功能描述： 获取线路无人折返灯所属ZCID
* 输入参数： const UINT16_S drLampId,无人折返灯ID
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*            >0:所属ZCID
*/
UINT16_S GetLineDrLampBelongZcId(const UINT16_S drLampId);

/*
* 函数名称：GetLineDrLampBelongCiId
* 功能描述： 获取线路无人折返灯所属CIid
* 输入参数： const UINT16_S drLampId,无人折返灯ID
* 输出参数： 无
* 返回值  ： 0: 获取数据失败
*            >0:所属CIid
*/
UINT16_S GetLineDrLampBelongCiId(const UINT16_S drLampId);

/*
** 功能描述： 判断此停车点是否在无人折返表中存在
* 参数说明： const UINT16_S arId;编号
* 返回值  :  0:不存在
*             1:存在
*/ 
UINT8_S CheckSopPointIsAr(const UINT16_S stopPointId);

/*
* 函数名称：CheckSopPointIsAr
* 功能描述： 判断此停车点是否在无人折返表中存在
* 输入参数： const UINT16_S arId;编号
* 输出参数：无
* 返回值  :  0:不存在
*             1:存在
*/ 
UINT8_S CheckSopPointIsExitAr(const UINT16_S stopPointId);

#ifdef __cplusplus
}
#endif

#endif
