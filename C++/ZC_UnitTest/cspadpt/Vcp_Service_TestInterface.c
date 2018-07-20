/******************************************************************************
 *File Name         :    Vcp_Service_TestInterface.h
 *Copyright         :    Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :  2013/04/19
 *
 *Description    :  �����õĽӿ�
 *
 *+----------+---------------------------------------------------------------+
 *| Design   |    �����ͨ�ź�ϵͳͨ�ð�ȫ�����ƽ̨�������SM_PAB           |
 *|  File    |    �����ϸ���˵����_SM_PAB_XXXX���_A.3                     |
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
 *Function: ��ȡ��ǰ������
 *Para    : void
 *Return  : ��ǰ������
 ******************************************************************************/
unsigned int F_VCP_Test_GetCycleNum(void)
{
	unsigned int retVal = gCycNum;
	return retVal;
}


/******************************************************************************
 *Name    : F_VCP_Test_GetSysClk
 *Function: ��ȡ��ǰϵͳʱ��
 *Para    : void
 *Return  : ��ǰϵͳʱ��
 ******************************************************************************/
T_SysClk F_VCP_Test_GetSysClk(void)
{
	T_SysClk retVal;
	retVal.Sec = 0;
	retVal.uSec = 0;
	return retVal;
}


/*
* ����������ͨ��������ȡCSPƽ̨�����ں�                           
* ����˵������
* ����ֵ      :    ���ں�
*/
void UpdataRunCycNum(unsigned int cycNum)
{
	UINT32* mCycNum = CSPADPT_Get_Main_Cycle_Ptr();
	 cycNum = *mCycNum; 

}

