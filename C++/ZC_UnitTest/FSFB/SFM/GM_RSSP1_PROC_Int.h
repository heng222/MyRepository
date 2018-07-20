#ifndef _GM_RSSP1_PROC_H_
#define _GM_RSSP1_PROC_H_
#include "GM_RSSP1_TIME.h"

#ifdef __cplusplus
extern "C"
{
#endif


	GM_INT32 GM_GM_UINT32M_CHN_CHECK_Int(GM_UINT32 crcm, GM_UINT32 crc32, GM_UINT32 syscheck, GM_UINT32 *left_tab, GM_UINT32 *right_tab, GM_UINT32 msgTC, GM_UINT32 tc, GM_UINT32 *localTC,
									   GM_UINT32 *remoteTC, GM_UINT32 *dynamickey, GM_UINT32 *prec_sint, GM_UINT32 *post_data, GM_UINT16 delta_time , GM_UINT16 life_time);

	GM_INT32 GM_RSSP1_SSE_BUILD_Int(GM_UINT8 *pResult , GM_UINT16 *pResult_len , GM_UINT16 sourAddr, GM_UINT16 desAddr, GM_UINT32 tc, GM_UINT32 sid_1, GM_UINT32 ts_1, GM_UINT32 sid_2, GM_UINT32 ts_2,
									  GM_UINT32 *preSSETC1, GM_UINT32 *preSSETC2, GM_UINT32 *preSSETS1, GM_UINT32 *preSSETS2, GM_UINT8 *bSendSSE1, GM_UINT8 *bSendSSE2, GM_UINT16 lifeTime , GM_UINT32* pCRC16_table);

	GM_INT32 GM_RSSP1_SSR_BUILD_Int(GM_UINT8 *pResult , GM_UINT16 *pResult_len , GM_UINT16 sourAddr, GM_UINT16 desAddr, GM_UINT32 seqenq_1, GM_UINT32 seqenq_2, GM_UINT32 sid_r1, GM_UINT32 sid_r2,
									  GM_UINT32 dataver_r1, GM_UINT32 dataver_r2, GM_UINT32 ts_r1, GM_UINT32 ts_r2, GM_UINT32 tc_e, GM_UINT32 tc_r, GM_UINT8 num_dataver , GM_UINT32* pCRC16_table);

	GM_INT32 GM_RSSP1_SSR_CHN_SET(GM_UINT32 *left_tab, GM_UINT32 *right_tab, GM_UINT32 seqini, GM_UINT32 prec_firstsint, GM_UINT32 preSSEtc, GM_UINT32 preSSEts, GM_UINT32 *dynamic,
									GM_UINT32 tc, GM_UINT32 *localTC, GM_UINT32 *remoteTC, GM_UINT32 TC_E,  GM_UINT32 TC_R, GM_UINT8 *bSendSSE , GM_UINT32 ssr_valid_cycle);

	GM_INT32 GM_RSSP1_RSD_BUILD_Int(GM_UINT8 *pResult , GM_UINT16 *pResult_len , GM_UINT8 *app_data, GM_UINT16 app_data_len, GM_UINT8 mstorslv, GM_UINT8 aorb, GM_UINT16 sourAddr, GM_UINT16 desAddr,
									  GM_UINT32 tc, GM_UINT32 crcm1, GM_UINT32 crcm2 , GM_UINT32* pCRC16_table);

	GM_INT32 GM_RSSP1_PREC_SINT_CAL_Int(GM_UINT32 sinit, GM_UINT32 sid, GM_UINT32 *prec_sinit, GM_UINT32 *left_tab, GM_UINT32 *right_tab , GM_INT32 max_delta_time);
	GM_INT32 GM_RSSP1_PREC_FIRSTSINIT_CAL(GM_UINT32 sint_r, GM_UINT32 sid_e, GM_UINT32 dataver_r, GM_UINT32 *prec_firstsinit, GM_UINT32 *left_tab, GM_UINT32 *right_tab);
	GM_INT32 GM_RSSP1_POST_RXDATA_Int(GM_UINT32 sinit, GM_UINT32 sid, GM_UINT32 *post_rxdata, GM_UINT32 *left_tab, GM_UINT32 *right_tab , GM_INT32 max_delta_time);
#ifdef __cplusplus
}
#endif

#endif
