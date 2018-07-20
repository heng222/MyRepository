#ifndef GM_LOG_INTERCOMM_H

#define GM_LOG_INTERCOMM_H

#include "GM_RSSP1_INTERCOMM_Socket.h"
#include "GM_RSSP1_INTERCOMM_Def.h"
#include "..\Common\CommonQueue.h"
#include "..\FSFB\GM_RSSP1_Utils.h"
#include "..\cspadpt\Vcp_Service_Interface.h"

GM_BOOL GM_LOG_INTERCOMM_SEND(UINT8*  m_Msg_Ptr, UINT32 m_Msg_Length);
#endif

