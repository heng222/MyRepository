/******************************************************************************
 *File Name         :    Vcp_Track_Interface.h
 *Copyright         :    Zhuzhou CSR Times Electric Co.,Ltd. All Rights Reserved.
 *Create Date    :    2015/08/04
 *Module Id      :  SD-SM_PAB-1015
 *Description    :  USR用户系间倒机数据处理
 *
 *  +----------+---------------------------------------------------------------+
 *  | Design   |        USR用户系间倒机数据处理                                |
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
 *Function: USR系间倒机数据注册操作
 *
 *Para    : @inMaxLen  : 注册最大倒机数据长度;
 *          @inInterval: 注册强制倒机周期间隔;
 *          @inDataGet : 注册获取USR倒机数据函数;
 *          @inDataSet : 注册设置USR倒机数据函数;
 *
 *Return  : 初始化成功=> e_TRUE, 否则=>e_FALSE.
 *
 *Note    : inDataGet 及 inDataSet 必须非空;
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