/******************************************************************************
 *File Name         :    Vcp_Track_Interface.h
 *Copyright         :    Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :    2015/08/04
 *Module Id      :  SD-SM_PAB-1015
 *Description    :  USR�û�ϵ�䵹�����ݴ���
 *
 *  +----------+---------------------------------------------------------------+
 *  | Design   |        USR�û�ϵ�䵹�����ݴ���                                |
 *  |  File    |                                                               |
 *  +----------+--------------+------------+-----------------------------------+
 *  | Version  |    Author    |    Date    |            Description            |
 *  +----------+--------------+------------+-----------------------------------+
 *  | C.A.0001 |    Pengfq    | 2015/08/04 |  File Create                      |
 *  +----------+--------------+------------+-----------------------------------+
 *
******************************************************************************/

#include "Vcp_Track_Interface.h"


/******************************************************************************
 *Name    : F_VCP_TrackRegister
 *Function: USRϵ�䵹������ע�����
 *
 *Para    : @inMaxLen  : ע����󵹻����ݳ���;
 *          @inInterval: ע��ǿ�Ƶ������ڼ��;
 *          @inDataGet : ע���ȡUSR�������ݺ���;
 *          @inDataSet : ע������USR�������ݺ���;
 *
 *Return  : ��ʼ���ɹ�=> e_TRUE, ����=>e_FALSE.
 *
 *Note    : inDataGet �� inDataSet ����ǿ�;
 * 
******************************************************************************/
E_SysBool  F_VCP_TrackRegister(const unsigned int inMaxLen,
                               const unsigned int inInterval,
                               F_TrackDataGet inDataGet,
                               F_TrackDataSet inDataSet)
{
	E_SysBool retVal = e_TRUE;
	return retVal;
}