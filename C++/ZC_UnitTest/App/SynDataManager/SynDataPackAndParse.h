/************************************************************************
*
* 文件名   ：  SynDataPackAndParse.h
* 创建时间 ：  2016.1.18
* 作者     ：  ZC组
* 功能描述 ：  2系同步数据的打包和解析
* 备  注   ：  无
*
************************************************************************/
#ifndef SYN_DATA_PACK_AND_PARSE_H_
#define SYN_DATA_PACK_AND_PARSE_H_

#include "../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

/*
* 功能描述： 解析帧当中的全部信息
* 参数说明： const UINT8 inFrameContent[],输入帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S ParseAllInfoFromFrame(const UINT8_S inFrameContent[]);

/*
* 功能描述： 设置帧当中的全部信息
* 参数说明： UINT8 outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S PackAllInfoToFrame(UINT8_S outFrameContent[]);

/*
* 功能描述： 设置帧当中的AC信息
* 参数说明： UINT32 *buffIndex,帧的终点下标
*            UINT8_S FrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetACInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的AC全部信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetACInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中DR的无人折返按钮信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的终点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetDRButtonInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的DR全部信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetDRButtonInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中DR的无人折返灯信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的终点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetDRLampInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中DR的无人折返灯信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetDRLampInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的紧急停车按钮ESB信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetESBInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的ESB信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetESBInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的屏蔽门PSD信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetPSDInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的PSD信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetPSDInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的LogicSection信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetLogicSectionInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的LogicSection信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetLogicSectionInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的Overlap信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetOverlapInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的Overlap信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetOverlapInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的Route信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetRouteInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的Route信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetRouteInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的Signal信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetSignalInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的Signal信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetSignalInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的Switch信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetSwitchInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的Switch信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetSwitchInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的Tsr信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetTsrInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的Tsr信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetTsrInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的Train信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetTrainInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的Train信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetTrainInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的CommTarget信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetCommTargetInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的通讯设备信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetCommTargetInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的NTP校时成功标志信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetNTPTimeFlagInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的NTP校时成功标志信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetNTPTimeFlagInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的NTP校时本地时间信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetNTPLocalTimeInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的NTP校时本地时间信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetNTPLocalTimeInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的NTP校时结构体时间信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetNTPStructTimeInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的NTP校时结构体时间信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetNTPStructTimeInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的ZC上电标记成功标志信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetZCPowerUpFlagInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的ZC上电标记成功标志信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetZCPowerUpFlagInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[]);

/*
* 功能描述： 解析帧当中的CRC32信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetCRC32InfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex);

/*
* 功能描述： 设置帧当中的CRC32信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetCRC32InfoToFrame(UINT32_S *buffIndex,const UINT8_S outFrameContent[]);

#ifdef __cplusplus
}
#endif

#endif 
