/************************************************************************
*
* 文件名   ：  ParsePackIODefine.h
* 创建时间 ：  2014.04.14
* 作者     ：  ZC组
* 功能描述 ：  输入输出解析相关定义  
* 备  注	：  无
*
************************************************************************/

#ifndef PARSE_PACK_IO_DEFINE_H_
#define PARSE_PACK_IO_DEFINE_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif
	
/*ZC与CI通信的最大字节数量*/
#define ZC_CI_COM_BYTE_SUM_MAX       1000U

/*ZC与车载ATP通信的最大字节数量*/
#define ZC_TRAIN_COM_BYTE_SUM_MAX    500U

/*ZC与相邻ZC通信的最大字节数量*/
#define ZC_NZC_COM_BYTE_SUM_MAX      1300U

/*ZC与ATS通信的最大字节数量*/
#define ZC_ATS_COM_BYTE_SUM_MAX      1300U
#define	DEV_TOTAL_FRAME_LEN          1300U/*-bye-*/


/*ZC与NTP的最大字节数量*/
#define ZC_NTP_COM_BYTE_SUM_MAX      1000U

#ifdef __cplusplus
}
#endif
#endif
