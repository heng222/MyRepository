/*************************************************
  文件名   ：TrainInfoData.h
  作者     ：董欣      
  创建时间 ：2016-8-13
  功能描述 ： TrainInfoData数据管理
			DmuCommonData组件的TrainInfoData功能可分解如下：
			1）	给TrainInfoDataStru结构体指针分配空间
			2）	获取TrainInfoData数据
			3）	获取TrainInfoData信息
			4）	获取指定IDTrainInfoDataStru的结构体下标
			5）	获取指定IDTrainInfoDataStru的结构体指针
			6）	获取指定IDTrainInfoDataStru的列车长度(cm)
			7）	获取指定IDTrainInfoDataStru的列车最大牵引加速度（cm/s/s）
			8）	获取指定IDTrainInfoDataStru的线路最大下坡坡度（线路夹角的正切值*10000）
			9）	获取指定IDTrainInfoDataStru的列车旋转质量系数。由车辆提供，用于速度曲线计算，单位0.01
			10）	获取指定IDTrainInfoDataStru的最不利情况下紧急制动减速度。系统保证在最坏情况下
			实施最小减速度的紧急制动，由紧急制动最小加速度值乘以紧急制动有效率获得,单位cm/s2
			11）	获取指定IDTrainInfoDataStru的紧急制动建立等效时间。即滑行时间,单位:ms
			12）	获取指定IDTrainInfoDataStru的牵引切除延时。施加紧急制动时考虑的牵引切除延时,单位:ms
			13）	获取指定IDTrainInfoDataStru的线路速度上限。线路规定的，列车在任何位置和任何时刻都
			不允许达到的速度值上限，单位km/h
  备注    ：无。 
*************************************************/
#ifndef TRAININFO_DATA_H_
#define TRAININFO_DATA_H_

#include "../../../Common/CommonTypes.h"

#define  TRAININFO_LINE_BYTE_NUM                 13                            /*一行数据字节数*/

#ifdef __cplusplus
extern "C" {
#endif

/*列车性能参数配置表数据结构体*/
typedef struct BnfTrainInfoStruct
{
    UINT8_S  trainType;                /*列车车型*/        
    UINT16_S trainLength;                /*列车长度(cm)*/
    UINT8_S  trainMaxTracAcc;            /*列车最大牵引加速度（cm/s/s）*/    
    UINT16_S lineMaxGrade;            /*线路最大下坡坡度（线路夹角的正切值*10000）*/        
    UINT8_S  trainRotateRate;          /*列车旋转质量系数。由车辆提供，用于速度曲线计算，单位0.01*/
    UINT8_S  trainWorstEbAcc;          /*最不利情况下紧急制动减速度。系统保证在最坏情况下实施最小减速度的紧急制动，由紧急制动最小加速度值乘以紧急制动有效率获得,单位cm/s2*/
    UINT16_S timeEbBrakeBuild;        /*紧急制动建立等效时间。即滑行时间,单位:ms*/
    UINT16_S timeTracCut;                /*牵引切除延时。施加紧急制动时考虑的牵引切除延时,单位:ms*/
    UINT8_S maxLineLimitSpeed;        /*线路速度上限。线路规定的，列车在任何位置和任何时刻都不允许达到的速度值上限，单位km/h*/    
}BnfTrainInfoStruct;

/*
* 功能描述： 给TrainInfoDataStru结构体指针分配空间
* 参数说明： UINT16_S lineNum 表的数据行数
* 返回值  ： void
*/
void MallocTrainInfoDataStru(UINT16_S lineNum);

/*
* 功能描述： 获取TrainInfoData数据
* 参数说明：
* 返回值  ： 
            BnfTrainInfoStruct*
*/
BnfTrainInfoStruct *GetTrainInfoData(void);

/*
* 功能描述： 获取TrainInfoData信息
* 参数说明：输出参数:UINT16_S* lineNum  数据行数
* 返回值  ： 
            BnfTrainInfoStruct*
*/
BnfTrainInfoStruct *GetTrainInfoDataInfo(UINT16_S* lineNum);
/*
** 功能描述： 获取指定IDTrainInfoDataStru的结构体下标
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0xFFFF: 获取数据失败
*            <0xFFFF: 查找成功
*/ 
UINT16_S GetTrainInfoDataStruIndex(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的结构体指针
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  NULL: 获取数据失败
*            !NULL: 查找成功,并且返回值为结构体指针
*/ 
BnfTrainInfoStruct* GetIndexIdTrainInfoDataStru(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的列车长度(cm)
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 列车长度(cm)
*/ 
UINT16_S GetTrainInfoDataStrutrainLength(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的列车最大牵引加速度（cm/s/s）
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 列车最大牵引加速度（cm/s/s）
*/ 
UINT8_S GetTrainInfoDataStrutrainMaxTracAcc(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的线路最大下坡坡度（线路夹角的正切值*10000）
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 线路最大下坡坡度（线路夹角的正切值*10000）
*/ 
UINT16_S GetTrainInfoDataStrulineMaxGrade(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的列车旋转质量系数。由车辆提供，用于速度曲线计算，单位0.01
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 列车旋转质量系数。由车辆提供，用于速度曲线计算，单位0.01
*/ 
UINT8_S GetTrainInfoDataStrutrainRotateRate(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的最不利情况下紧急制动减速度。系统保证在最坏情况下实施最小减速度的紧急制动，由紧急制动最小加速度值乘以紧急制动有效率获得,单位cm/s2
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 最不利情况下紧急制动减速度。系统保证在最坏情况下实施最小减速度的紧急制动，由紧急制动最小加速度值乘以紧急制动有效率获得,单位cm/s2
*/ 
UINT8_S GetTrainInfoDataStrutrainWorstEbAcc(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的紧急制动建立等效时间。即滑行时间,单位:ms
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 紧急制动建立等效时间。即滑行时间,单位:ms
*/ 
UINT16_S GetTrainInfoDataStrutimeEbBrakeBuild(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的牵引切除延时。施加紧急制动时考虑的牵引切除延时,单位:ms
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 牵引切除延时。施加紧急制动时考虑的牵引切除延时,单位:ms
*/ 
UINT16_S GetTrainInfoDataStrutimeTracCut(const UINT8_S trainType);

/*
** 功能描述： 获取指定IDTrainInfoDataStru的线路速度上限。线路规定的，列车在任何位置和任何时刻都不允许达到的速度值上限，单位km/h
* 参数说明： const UINT8_S trainType;列车车型
* 返回值  :  0: 获取数据失败
*            >0: 线路速度上限。线路规定的，列车在任何位置和任何时刻都不允许达到的速度值上限，单位km/h
*/ 
UINT8_S GetTrainInfoDataStrumaxLineLimitSpeed(const UINT8_S trainType);


#ifdef __cplusplus
}
#endif

#endif
