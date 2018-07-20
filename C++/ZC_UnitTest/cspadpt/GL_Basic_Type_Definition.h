/******************************************************************************
 *File Name	     :	GL_Basic_Type_Definition.h
 *Copyright	     :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :	2011/03/06
 *Description    :	General Library's basic type definition
 *
 *+----------+---------------------------------------------------------------+
 *| Design   |    轨道交通信号系统通用安全计算机平台软件GL通用库             |
 *|  File    |    详细设计说明书-GL_Basic_Type_Definition组件A.4             |
 *+----------+--------------+------------+-----------------------------------+
 *| Version  |    Author    |    Date    |            Description            |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0001 | YanGuang     | 2011/03/06 |  File Create                      |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0002 | YanGuang     | 2013/03/19 |(1)新增F_GL_ReverseByte()          |
 *|          |              |            |(2)将INTEGER改为INTEGER32          |
 *|          |              |            |                                   |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0003 | YanGuang     | 2013/10/16 |(1)增加引用编译开关的文件          |
 *|          |              |            |(2)将编译开关删除                  |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0004 | YanGuang     | 2014/03/10 |(1)删除 T_Cell 结构定义            |
 *|          |              |            |(2)添加UINTEGER32 数据类型         |
 *+----------+--------------+------------+-----------------------------------+
 *
 ******************************************************************************/

/******************************************************************************
*    Multi-Include-Prevent Start Section
******************************************************************************/
#ifndef GL_BASIC_TYPE_DEFINITION_H_
#define GL_BASIC_TYPE_DEFINITION_H_
#include "..\GM_Utils\GM_Utils_Base.h"
/******************************************************************************
*    Debug switch Section
******************************************************************************/



/******************************************************************************
*    Include File Section
******************************************************************************/
#include "GL_Compile_Switch_Definition.h"


/******************************************************************************
*    Global Macro Define Section
******************************************************************************/
/*自定义基础数据类型*/
/*typedef unsigned char  UINT8     ;
typedef signed   char  INT8      ;*/
typedef char           CHARACTER ;
typedef int            INTEGER32 ;
typedef unsigned int   UINTEGER32;
typedef float          REAL32    ;
typedef double         REAL64    ;

/*typedef unsigned short int UINT16;
typedef signed   short int INT16 ;
typedef unsigned long  int UINT32;
typedef signed   long  int INT32 ;
*/

/*定义空指针*/
#define ptrNULL          ((void*)0)

/*定义1天对应的小时*/
#define c_DayToHour      (24UL)

/*定义1小时对应的分钟*/
#define c_HourToMinute   (60UL)

/*定义1分钟对应的秒数*/
#define c_MinuteToSecond (60UL)

/*定义1秒钟对应的毫秒数*/
#define c_SecondToMilSec (1000UL)

/*定义1毫秒对应的微秒数*/
#define c_MilSecToMicSec (1000UL)

/*定义1秒钟对应的微秒数[1,000,000]*/
#define c_SecondToMicSec (c_SecondToMilSec*c_MilSecToMicSec)

/*定义1分钟对应的毫秒数[60,000]*/
#define c_MinuteToMilSec (c_MinuteToSecond*c_SecondToMilSec)

/*定义1小时对应的秒数[3,600]*/
#define c_HourToSecond   (c_HourToMinute*c_MinuteToSecond)

/*定义1小时对应的毫秒[3,600,000]*/
#define c_HourToMilSec   (c_HourToSecond*c_SecondToMilSec)

/*定义1天对应的秒数[86,400]*/
#define c_DayToSecond    (c_DayToHour*c_HourToSecond)

/*定义1天对应的毫秒数[86,400,000]*/
#define c_DayToMilSec    (c_DayToSecond*c_SecondToMilSec)



/******************************************************************************
*    Global Struct    Define Section
******************************************************************************/

/*自定义布尔值*/
typedef enum TAG_SysBool
{
  e_TRUE  = 0x05555555, /*表示逻辑"真" */
  e_FALSE = 0x0AAAAAAA  /*表示逻辑"假" */
}E_SysBool;

/*定义通用校验和*/
typedef struct TAG_Checksum
{
  GM_INT32  C1; /* [4 Bytes] 取值[-0x80000000, 0x7FFFFFFF]*/
  GM_INT32  C2; /* [4 Bytes] 取值[-0x80000000, 0x7FFFFFFF]*/
}T_Checksum; /* [8 Bytes] */

/*定义系统时钟的格式*/
typedef struct TAG_SysClk


{
  GM_UINT32 Sec ; /*[4 Byte] 秒数,取值[0, 0xFFFFFFFF]*/
  GM_UINT32 uSec; /*[4 Byte] 微秒,取值[0, 999999]    */
}T_SysClk;

/*定义实时时钟的格式*/
typedef struct TAG_RealClk
{
  GM_UINT16 Year ; /*[2 Byte] 年份,取值[0~10000]   */
  GM_UINT8  Month; /*[1 Byte] 月份,取值[1~12]      */
  GM_UINT8  Day  ; /*[1 Byte] 天数,取值[1~31]      */
  GM_UINT32 MiSec; /*[4 Byte] 毫秒,取值[0~86399999]*/
}T_RealClk;     /*[8 Byte]*/

/*定义通用原子消息*/
typedef struct TAG_CellMsg
{
  GM_UINT8*  ptrMsg ; /* [4 Bytes] 取值[非零地址]     */
  GM_UINT32  dataLen; /* [4 Bytes] 取值[0, 0xFFFFFFFF]*/
}T_CellMsg;        /* [8 Bytes] */



/******************************************************************************
*    Global Variable Declare Section
******************************************************************************/
extern const T_RealClk c_DefaultRealClkF;
extern const T_RealClk c_DefaultRealClkM;
extern const T_SysClk  c_DefaultSysClk  ;
/******************************************************************************
*    Global Prototype Declare Section
******************************************************************************/
void F_reverseByte(void* const ioData, const UINT32 inDataLen);
void F_GL_ReverseByte(void* const ioData, const UINT32 inDataLen);
E_SysBool F_GL_IsDefaultRealClk(const T_RealClk inRealClk);

/******************************************************************************
*    Multi-Include-Prevent End Section
******************************************************************************/

#endif



