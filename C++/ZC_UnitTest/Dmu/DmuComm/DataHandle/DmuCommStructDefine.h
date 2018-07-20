/********************************************************
* 
* 文 件 名： DmuCommStructDefine.h 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 公共查询函数结构体定义头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef DMU_COMM_STRUCTDEFINE_H_
#define DMU_COMM_STRUCTDEFINE_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif
/*道岔状态信息*/
typedef struct _SwitchStatusInfoStruct
{
    UINT16_S  switchId;                        /*道岔ID*/
    UINT8_S   switchStatus;                    /*道岔状态*/    
}SwitchStatusInfoStruct;

/*临时限速结构体*/
typedef struct TmpLimitSpeedInfoStruct
{
    UINT16_S limitSpeed;                        /*限速值*/
    UINT16_S startSegId;                        /*起点SEGID*/
    UINT32_S startOffSet;                        /*起点Offset*/
    UINT16_S endSegID;                        /*终点SEGiD*/
    UINT32_S endSegOffset;                    /*终点Offset*/
}TmpLimitSpeedInfoStruct;

/*MA中的障碍物信息结构体*/
typedef struct obstInfoStruct
{
    UINT8_S  type;                /*障碍物类型*/
    UINT16_S obstId;                /*障碍物ID*/
    UINT16_S segId;                /*障碍物所在SEGID*/
    UINT32_S    offSet;                /*障碍物所在SEG的偏移量*/
    UINT8_S    status;                /*障碍物当前状态*/
    UINT8_S    realStatus;            /*障碍物实际状态*/
}ObstInfoStruct;

#ifdef __cplusplus
}
#endif

#endif
