#ifndef _GM_RSSP1_SFM_INTERFACE_H
#define _GM_RSSP1_SFM_INTERFACE_H


#include "../GM_RSSP1_Utils.h"
#include "GM_RSSP1_SFM.h"

#ifdef __cplusplus
extern "C"
{
#endif

	void GM_RSSP1_SFM_Interface_Proc_Send(void);

	void GM_RSSP1_SFM_Interface_Proc_Recv(void);

#ifdef __cplusplus
}
#endif

#endif