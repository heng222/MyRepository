/********************************************************
* 
* 文 件 名： AdptPlatBasicTypeDefinition.h
* 作    者： 董欣 
* 创建时间： 2016-09-01 
* 功能描述： 平台适配层对底层基本定义头文件  
* 备    注： 无 
* 
********************************************************/ 

#ifndef ADPT_PLAT_BASIC_TYPE_DEFINITION_H_
#define ADPT_PLAT_BASIC_TYPE_DEFINITION_H_

#include "../../Common/CommonTypes.h"

#include "../../cspadpt/Vcp_File_Interface.h"
#include "../../cspadpt/GL_Basic_Type_Definition.h"

#ifdef SYS_TYPE_WINDOWS
typedef FILE*               FILEType;        /*文件句柄类型*/
#else
typedef signed long int     FILEType;         /*文件句柄类型*/
#endif

/*定义实时时钟的格式*/
typedef struct AdptRealClk
{
  UINT16_S Year ; /*[2 Byte] 年份,取值[0~10000]   */
  UINT8_S  Month; /*[1 Byte] 月份,取值[1~12]      */
  UINT8_S  Day  ; /*[1 Byte] 天数,取值[1~31]      */
  UINT32_S MiSec; /*[4 Byte] 毫秒,取值[0~86399999]*/
}AdptRealClkStruct;     /*[8 Byte]*/

/*定义通用原子消息*/
typedef struct AdptCellMsg
{
  UINT8_S*  ptrMsg ; /* [4 Bytes] 取值[非零地址]     */
  UINT32_S  dataLen; /* [4 Bytes] 取值[0, 0xFFFFFFFF]*/
}AdptCellMsgStruct;        /* [8 Bytes] */


#endif



