/******************************************************************************
 *File Name	        :	Vcp_Device_Definition_Inf.h
 *Copyright	        :	Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date       :	2018/02/28
 *
 *Description       :	PCA工具自动生成设备配置列表文件
 *
 *Protocol Version  : V.C.6
 *PCA Tool Version  : V.C.6.0001
 *PCA CFG  Version  : None
 *
******************************************************************************/

/******************************************************************************
*    Multi-Include-Prevent Start Section
******************************************************************************/
#ifndef _VCP_DEVICE_DEFINITION_INF_H_
#define _VCP_DEVICE_DEFINITION_INF_H_

/******************************************************************************
*    Debug switch Section
******************************************************************************/

/******************************************************************************
*    Include File Section
******************************************************************************/
#include "GL_Basic_Type_Definition.h"


/******************************************************************************
*    Global Struct    Define Section
******************************************************************************/
typedef struct TAG_DeviceInf
{
 UINT16 Type ; /**/
 UINT8  AppId; /**/
 UINT8  SysId; /**/
}T_DeviceInf;            

/******************************************************************************
*    Global Macro Define Section
******************************************************************************/
#define c_DeviceItemTotal (74UL)
#define      MIC_A1  (0UL)
#define      MIC_A2  (1UL)
#define      SME_A1  (2UL)
#define      MIC_B1  (3UL)
#define      MIC_B2  (4UL)
#define      SME_B1  (5UL)
#define      Log_B1  (6UL)
#define      DMS_B1  (7UL)
#define      Log_A1  (8UL)
#define      DMS_A1  (9UL)
#define      CI1_A1  (10UL)
#define      CI2_A2  (11UL)
#define      CI3_A3  (12UL)
#define      ZC2_A2  (13UL)
#define      ATS_A1  (14UL)
#define      NTP_A1  (15UL)
#define       T1_A1  (16UL)
#define       T2_A2  (17UL)
#define       T3_A3  (18UL)
#define       T4_A4  (19UL)
#define       T5_A5  (20UL)
#define       T6_A6  (21UL)
#define       T7_A7  (22UL)
#define       T8_A8  (23UL)
#define       T9_A9  (24UL)
#define     T10_A10  (25UL)
#define      TCP_A1  (26UL)
#define     T12_A12  (27UL)
#define     T13_A13  (28UL)
#define     T14_A14  (29UL)
#define     T15_A15  (30UL)
#define     T16_A16  (31UL)
#define     T17_A17  (32UL)
#define     T18_A18  (33UL)
#define     T19_A19  (34UL)
#define     T20_A20  (35UL)
#define     T21_A21  (36UL)
#define     T22_A22  (37UL)
#define     T23_A23  (38UL)
#define     T24_A24  (39UL)
#define     T25_A25  (40UL)
#define      CI1_B1  (41UL)
#define      CI2_B2  (42UL)
#define      CI3_B3  (43UL)
#define      ZC2_B2  (44UL)
#define      ATS_B1  (45UL)
#define      NTP_B1  (46UL)
#define       T1_B1  (47UL)
#define       T2_B2  (48UL)
#define       T3_B3  (49UL)
#define       T4_B4  (50UL)
#define       T5_B5  (51UL)
#define       T6_B6  (52UL)
#define       T7_B7  (53UL)
#define       T8_B8  (54UL)
#define       T9_B9  (55UL)
#define     T10_B10  (56UL)
#define      TCP_B1  (57UL)
#define     T12_B12  (58UL)
#define     T13_B13  (59UL)
#define     T14_B14  (60UL)
#define     T15_B15  (61UL)
#define     T16_B16  (62UL)
#define     T17_B17  (63UL)
#define     T18_B18  (64UL)
#define     T19_B19  (65UL)
#define     T20_B20  (66UL)
#define     T21_B21  (67UL)
#define     T22_B22  (68UL)
#define     T23_B23  (69UL)
#define     T24_B24  (70UL)
#define     T25_B25  (71UL)
#define     Log2_B2  (72UL)
#define     Log2_A2  (73UL)
 
/******************************************************************************
*    Global Variable Declare Section
******************************************************************************/
extern const T_DeviceInf c_DeviceInfTable[c_DeviceItemTotal];
 
#endif
