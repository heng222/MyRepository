/******************************************************************************
 *File Name         :    Vcp_Service_TestInterface.h
 *Copyright         :    Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :  2013/04/19
 *
 *Description    :  测试用的接口
 *
 *+----------+---------------------------------------------------------------+
 *| Design   |    轨道交通信号系统通用安全计算机平台主机插件SM_PAB           |
 *|  File    |    软件详细设计说明书_SM_PAB_XXXX组件_A.3                     |
 *+----------+--------------+------------+-----------------------------------+
 *| Version  |    Author    |    Date    |            Description            |
 *+----------+--------------+------------+-----------------------------------+
 *| C.A.0001 |    SUo   | 2018/05/19 |  File Create                      |
 *+----------+--------------+------------+-----------------------------------+
 *
 ******************************************************************************/

/******************************************************************************
*    Include File Section
******************************************************************************/
#include "Vcp_Service_TestInterface.h"

static unsigned int gCycNum = 0u;

/******************************************************************************
 *Name    : F_VCP_Test_GetCycleNum
 *Function: 获取当前周期数
 *Para    : void
 *Return  : 当前周期数
 ******************************************************************************/
unsigned int F_VCP_Test_GetCycleNum(void)
{
	unsigned int retVal = gCycNum;
	return retVal;
}


/******************************************************************************
 *Name    : F_VCP_Test_GetSysClk
 *Function: 获取当前系统时间
 *Para    : void
 *Return  : 当前系统时间
 ******************************************************************************/
T_SysClk F_VCP_Test_GetSysClk(void)
{
	T_SysClk retVal;
	retVal.Sec = 0;
	retVal.uSec = 0;
	return retVal;
}


/*
* 功能描述：通过适配层获取CSP平台的周期号                           
* 参数说明：无
* 返回值      :    周期号
*/
void UpdataRunCycNum(unsigned int cycNum)
{
	UINT32* mCycNum = CSPADPT_Get_Main_Cycle_Ptr();
	 cycNum = *mCycNum; 

}

