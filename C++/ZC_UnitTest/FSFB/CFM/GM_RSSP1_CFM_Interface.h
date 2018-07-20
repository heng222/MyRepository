#ifndef _GM_RSSP1_CFM_INTERFACE_H
#define _GM_RSSP1_CFM_INTERFACE_H

#include "../GM_RSSP1_Utils.h"
#include "GM_RSSP1_CFM.h"

#ifdef __cplusplus
extern "C"
{
#endif

	void GM_RSSP1_CFM_Interface_Proc_Send(void);

	void GM_RSSP1_CFM_Interface_Proc_Recv(void);
	
	void GM_RSSP1_CFM_Interface_Proc_Recv_For_Raw(void);
	
	void GM_RSSP1_CFM_Interface_Proc_Send_For_Raw(void);

	GM_BOOL GM_RSSP1_Get_Address(GM_UINT32* r_port, GM_UINT32* r_ip, GM_UINT8 con_index, GM_UINT8 red_index);
	GM_BOOL GM_RSSP1_Get_ConIndex(GM_UINT32 l_port, GM_UINT32 l_ip, GM_UINT8* con_index, GM_UINT8* red_index);
	GM_BOOL GM_RSSP1_Write_SFM_Interface_ergodic(GM_UINT8* p_dat, GM_UINT16* len, GM_UINT32* r_port, GM_UINT32* r_ip, GM_UINT8* index);
#ifdef __cplusplus
}
#endif

#endif