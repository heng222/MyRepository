#ifndef _GM_RSSP1_MQ_INTERFACE_H
#define _GM_RSSP1_MQ_INTERFACE_H

#include "GM_RSSP1_Msg_Queue.h"
#include "GM_RSSP1_Utils.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	GM_RSSP1_Msg_Queue_struct RCV_MQ;
	GM_RSSP1_Msg_Queue_struct SND_MQ;
}GM_RSSP1_RCV_SND_MQ_struct;

typedef struct
{
	GM_RSSP1_RCV_SND_MQ_struct     RCV_SND_MQ[GM_RSSP1_MAX_LINK_CHANNEL];
}RSSP1_MQ_LINK_struct;

typedef enum
{
	RSSP1_S2C_SND = 0x01,
	RSSP1_C2S_RCV = 0x02
}GM_RSSP1_MQ_Type_Enum;


typedef GM_RSSP1_RCV_SND_MQ_struct RSSP1_MQ_Inter_struct;

GM_BOOL GM_RSSP1_SND_com_Interface(GM_UINT8* p_dat, GM_UINT16* len, GM_UINT8 index, GM_UINT8 chn_index);

GM_BOOL GM_RSSP1_RCV_com_Interface(GM_UINT8* p_dat, GM_INT16 recv_len, GM_UINT8 index, GM_UINT8 chn_index);

GM_BOOL GM_RSSP1_MessageQueue_Inter_Set(GM_RSSP1_MQ_Type_Enum type, GM_UINT8* pMsg);

GM_BOOL GM_RSSP1_MessageQueue_Inter_Get(GM_RSSP1_MQ_Type_Enum type, GM_UINT8* pMsg, GM_UINT32* len);


#ifdef __cplusplus
}
#endif /* extern "C" */

#endif