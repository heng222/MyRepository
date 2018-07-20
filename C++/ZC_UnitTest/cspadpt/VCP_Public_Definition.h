/******************************************************************************
 *File Name         :  Vcp_Public_Definition.h
 *Copyright         :  Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :  2016/06/22
 *Module Id      :  SD-SM_PAB-1020
 *Description    :  平台提供的通用数据及类型定义
 *
 * +----------+---------------------------------------------------------------+
 * | Design   |    轨道交通信号系统通用安全计算机平台主机插件SM_PAB           |
 * |  File    |    软件结构设计说明书                                         |
 * +----------+--------------+------------+-----------------------------------+
 * | Version  |    Author    |    Date    |            Description            |
 * +----------+--------------+------------+-----------------------------------+
 * | C.A.0001 | ZhuHui       | 2016/06/22 |  File Create                      |
 * +----------+--------------+------------+-----------------------------------+
 *
 ******************************************************************************/

/******************************************************************************
 *    Multi-Include-Prevent Start Section
 ******************************************************************************/
#ifndef VCP_PUBLIC_DEFINITION_H_
#define VCP_PUBLIC_DEFINITION_H_

/******************************************************************************
 *    Debug switch Section
 ******************************************************************************/

/******************************************************************************
 *    Include File Section
 ******************************************************************************/
#include "GL_Basic_Type_Definition.h"



/******************************************************************************
 *    Global Macro Define Section
 ******************************************************************************/
/* 平台Cpu定义 */
/* CpuA, 单Cpu插件 */
#define c_VCP_CpuA (0xAAAAAAAAUL)
/* CpuB */
#define c_VCP_CpuB (0xBBBBBBBBUL)
/* CpuC */
#define c_VCP_CpuC (0xCCCCCCCCUL)
/* 错误的Cpu */
#define c_VCP_CpuX (0x00000000UL)



/******************************************************************************
 *    Global Struct    Define Section
 ******************************************************************************/
/* 用户设备 */
typedef struct TAG_UsrDevInf
{
  UINT16 DevType;
  UINT8  AppId  ;
  UINT8  AccSys ;
}T_UsrDevInf;

/* 用户管道设备 */
typedef struct TAG_UsrPipeInf
{
  T_UsrDevInf DevInf;
  UINT32      PipeId;
}T_UsrPipeInf;

/* 用户缓冲 */
typedef struct TAG_UsrBuff
{
  UINT8* ptrMsg  ;  /* 缓冲地址     */
  UINT32 dataLen ;  /* 缓冲内容长度 */
  UINT32 allocLen;  /* 缓冲分配长度 */
}T_UsrBuff;

/*定义日历时钟*/
typedef  struct TAG_CalendarClk
{
  UINT32 Year    ; /* 年份 */
  UINT32 Mon     ; /* 月份 */
  UINT32 Day     ; /* 日期 */
  UINT32 Hour    ; /* 小时 */
  UINT32 Min     ; /* 分钟 */
  UINT32 Sec     ; /* 秒   */
  UINT32 MiSec   ; /* 毫秒 */
  UINT32 WeekDay ; /* 星期 */
}T_CalendarClk;



/******************************************************************************
 *    Global Variable Declare Section
 ******************************************************************************/



/******************************************************************************
 *    Global Prototype Declare Section
 ******************************************************************************/

#endif



