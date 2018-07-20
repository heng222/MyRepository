#ifndef _GM_RSSP1_SYN_H
#define _GM_RSSP1_SYN_H

#include "GM_RSSP1_Utils.h"
#include "GM_RSSP1_Lib_Def.h"
#include "SFM/GM_RSSP1_SFM.h"
#include "CFM/GM_RSSP1_CFM.h"


#ifdef __cplusplus
extern "C"
{
#endif

		/** Լ������ͬ��ͨ����ID.��������fsfb���ӵ�sacepid��ϲ�������ظ�! */
	#define GM_RSSP1_SYN_DEST_ADDR   ((GM_UINT16)0xffff)

	typedef struct
	{
		GM_RSSP1_SACEPID_struct sacepid;
		/* FSFB ������TIME��Ϣ */
		GM_UINT32     time_TC;
		GM_UINT32  time_TS[GM_RSSP1_CHECK_CHN_NUM];
		GM_UINT32  time_oldTS[GM_RSSP1_CHECK_CHN_NUM];

		/* FSFB ������ENV��Ϣ */
		GM_RSSP1_CHN_ENV        env[GM_RSSP1_CHECK_CHN_NUM];

	} GM_PACKED GM_RSSP1_Syn_Info_struct;

    GM_BOOL GM_RSSP1_Syn_Send_Fsfb_State_To_Peer(GM_RSSP1_SFM_object_struct *pSFM , Local_Sys_AB_enum sys_a_b , GM_BOOL b_is_active);
    void GM_RSSP1_Syn_Proc_Rcvd_Syn_Dat(GM_UINT8 *pDat , GM_INT32 dat_len , GM_RSSP1_SFM_object_struct *pSFM);

#ifdef __cplusplus
}
#endif

#endif
