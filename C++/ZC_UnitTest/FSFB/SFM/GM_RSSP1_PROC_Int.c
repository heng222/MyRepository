#include "GM_RSSP1_PROC_Int.h"
#include "../GM_RSSP1_Msg_Define.h"
#include "../GM_RSSP1_Utils.h"

/********************GM_GM_UINT32M_CHN_CHECK_Int********************************************************
��;:�Խ��յ��ı��Ľ���FSFBУ��
����:crcm(���ձ���ĳһͨ����crcmֵ)
  crc32(���ձ���CRCУ��ֵ)
  syscheck(ϵͳУ����)
  left_tab(��������߼����������)
  right_tab(��������߼����������)
  msgTC(�����м�������ֵ)
  tc(����ĳͨ����������ֵ)
  localTC(���������һ�ν��յ�����ʱ������ͨ����������ֵ)
  remoteTC(���������һ�ν��յ�����ʱ�����м�������ֵ)
  dynamickey(sint+(sid~t(n-1))
  prec_sint(���ڼ����dynamickey������µ�dynamickey)
  post_data(�����ȷ������, ��Χ����deltaTime�仯)
  cycle(��ż��������ڳ���)
  p_peer_crc (���յ��������е�CRCֵ)
����ֵ:��ȷ(GM_RSSP1_OK)
    ����(GM_RSSP1_ERROR)
***********************************************************************************************/
GM_INT32 GM_GM_UINT32M_CHN_CHECK_Int(GM_UINT32 crcm, GM_UINT32 crc32, GM_UINT32 syscheck, GM_UINT32 *left_tab, GM_UINT32 *right_tab, GM_UINT32 msgTC, GM_UINT32 tc, GM_UINT32 *localTC,
                            GM_UINT32 *remoteTC, GM_UINT32 *dynamickey, GM_UINT32 *prec_sint, GM_UINT32 *post_data, GM_UINT16 delta_time , GM_UINT16 life_time)
{
    GM_UINT32 i = 0;
    GM_UINT32 x = 0;
	GM_UINT32 y = 0;
	GM_LFSR reg = {0};

    if (msgTC <= *remoteTC)
    {
        GM_Log_Msg(0,"rsd check:msgTC=%d, *remoteTC=%d\n", msgTC, *remoteTC, 0, 0, 0, 0);  
        return GM_RSSP1_RETURN_RESERVED;  /* jianghongjun mod 20101222�����CR��LKD00000389  �����޸�վ��ͨ�Ų��ȶ���UDP����ʱ���յ������ݰ�����ΪУ��ʧ�ܣ�ֱ�ӷ��أ��������� */
    }

    if ((msgTC - *remoteTC) >= delta_time)
    {
        GM_Log_Msg(0,"rsd check:msgTC=%d, *remoteTC=%d, cycle->deltaTime=%d\n", msgTC, *remoteTC, delta_time, 0, 0, 0);
        return GM_RSSP1_ERROR;
    }

    if ((tc - *localTC) >= delta_time)
    {
        GM_Log_Msg(0,"rsd check:tc=%d, *localTC=%d, cycle->deltaTime=%d\n", tc, *localTC, delta_time, 0, 0, 0);
        return GM_RSSP1_ERROR;
    }

    /* Start, LFSR to check CRCM.  */
	x = crcm ^ crc32 ^ syscheck;

    GM_memset(&reg, 0, sizeof(reg));
    GM_LFSR_Init(&reg, left_tab, right_tab);
    GM_LFSR_Load(&reg, *dynamickey);

    for (i = 0; i < msgTC - *remoteTC - 1; i++)
    {
        GM_LFSR_Add(&reg, 0);
    }

    GM_LFSR_Add(&reg, x);

    if(GM_FALSE == GM_LFSR_Read(&reg , &x))
    {
        return GM_RSSP1_ERROR;
    }
    GM_LFSR_Load(&reg, 0);
    GM_LFSR_Add(&reg, x);
    if(GM_FALSE == GM_LFSR_Read(&reg , &x))
    {
        return GM_RSSP1_ERROR;
    }

    if (x != *(post_data + (msgTC - *remoteTC - 1)))
    {
		GM_Log_Msg(0,"rsd check:x=0x%x, *(post_data+(msgTC - *remoteTC-1)):0x%x\n",  x, *(post_data+(msgTC - *remoteTC-1)), msgTC - *remoteTC-1, 0,0,0);
        return GM_RSSP1_ERROR;
    }
	/* End, LFSR to check CRCM.  */

    /* Start, to generate latest dynamic key.  */
    GM_LFSR_Load(&reg, *dynamickey);

    for (i = 0; i <= (msgTC - *remoteTC); i++)
    {
        GM_LFSR_Add(&reg, 0);
    }

    if(GM_FALSE == GM_LFSR_Read(&reg , &x))
    {
        return GM_RSSP1_ERROR;
    }

    GM_LFSR_Load(&reg, *(prec_sint + (msgTC - *remoteTC - 1)));
    GM_LFSR_Add(&reg, crcm ^ crc32 ^ syscheck);
    GM_LFSR_Add(&reg, crcm ^ crc32 ^ syscheck);
    if(GM_FALSE == GM_LFSR_Read(&reg , &y))
    {
        return GM_RSSP1_ERROR;
    }

    *dynamickey = x ^ y;
    *remoteTC = msgTC;
    *localTC = tc;
	/* End, to generate latest dynamic key.  */
    return GM_RSSP1_OK;
}

/**************************FSFB_SSE_BUILD*************************************************************************************
��;:����SSE����
����:msg(SSE����)
  sourAddr(FSFB SSE������ Դ��ַ)
  desAddr(FSFB SSE������ Ŀ���ַ)
  tc(��������ʱ�������)
  sid_1(ͨ��1 sid)
  ts_1(ͨ��1 ʱ���)
  sid_2(ͨ��2 sid)
  ts_2(ͨ��2 ʱ���)
  preSSETC1(��һ�η���SSE ͨ��1 ��ʱ���������ֵ)
  preSSETC2(��һ�η���SSE ͨ��2 ��ʱ���������ֵ)
  bSendSSE1(0xff(������SSE����δ�յ�SSR), 0x00(δ����SSE))
  bSendSSE2(0xff(������SSE����δ�յ�SSR), 0x00(δ����SSE))
����ֵ:����SSE���ĳɹ�(GM_RSSP1_OK)
    ����SSE����ʧ��(GM_RSSP1_ERROR)
*****************************************************************************************************************************/
GM_INT32 GM_RSSP1_SSE_BUILD_Int(GM_UINT8 *pResult , GM_UINT16 *pResult_len , GM_UINT16 sourAddr, GM_UINT16 desAddr, GM_UINT32 tc, GM_UINT32 sid_1, GM_UINT32 ts_1, GM_UINT32 sid_2, GM_UINT32 ts_2,
                       GM_UINT32 *preSSETC1, GM_UINT32 *preSSETC2, GM_UINT32 *preSSETS1, GM_UINT32 *preSSETS2, GM_UINT8 *bSendSSE1, GM_UINT8 *bSendSSE2, GM_UINT16 lifeTime , GM_UINT32 *pCRC16_table)
{
    GM_UINT32 SEQENQ_1  = 0;
    GM_UINT32 SEQENQ_2  = 0;
    GM_UINT16 crc16    = 0;

    if (*bSendSSE1 == 0xff)
    {
        if ((tc - *preSSETC1) <= lifeTime)
        {
            return GM_RSSP1_ERROR;
        }
    }

    if (*bSendSSE2 == 0xff)
    {
        if ((tc - *preSSETC2) <= lifeTime)
        {
            return GM_RSSP1_ERROR;
        }
    }

    SEQENQ_1    = sid_1 ^ ts_1;

    SEQENQ_2    = sid_2 ^ ts_2;

    *(pResult + 0)        = RSSP1_SSE_PROTOCOL_TYPE;
    *(pResult + 1)        = RSSP1_SSE_FRAME_TYPE;
    *(pResult + 2)        = (GM_UINT8)(sourAddr & 0xff);
    *(pResult + 3)        = (GM_UINT8)(sourAddr >> 8);
    *(pResult + 4)        = (GM_UINT8)(desAddr & 0xff);
    *(pResult + 5)        = (GM_UINT8)(desAddr >> 8);

    *(pResult + 6)        = (GM_UINT8)(tc & 0xff);
    *(pResult + 7)        = (GM_UINT8)((tc & 0xff00) >> 8);
    *(pResult + 8)        = (GM_UINT8)((tc & 0xff0000) >> 16);
    *(pResult + 9)        = (GM_UINT8)((tc & 0xff000000) >> 24);

    *(pResult + 10)        = (GM_UINT8)(SEQENQ_1 & 0xff);
    *(pResult + 11)        = (GM_UINT8)((SEQENQ_1 & 0xff00) >> 8);
    *(pResult + 12)        = (GM_UINT8)((SEQENQ_1 & 0xff0000) >> 16);
    *(pResult + 13)        = (GM_UINT8)((SEQENQ_1 & 0xff000000) >> 24);

    *(pResult + 14)        = (GM_UINT8)(SEQENQ_2 & 0xff);
    *(pResult + 15)        = (GM_UINT8)((SEQENQ_2 & 0xff00) >> 8);
    *(pResult + 16)        = (GM_UINT8)((SEQENQ_2 & 0xff0000) >> 16);
    *(pResult + 17)        = (GM_UINT8)((SEQENQ_2 & 0xff000000) >> 24);

    /*FSFB_CRC16_Calc(pCRC16_table, &crc16, (GM_INT8 *)(pResult) , 18);*/
	GM_CRC_Calculate_CRC16(pResult, 18, &crc16, (GM_UINT16*)pCRC16_table);
    *(pResult + 18)        = (GM_UINT8)(crc16 & 0xff);
    *(pResult + 19)        = (GM_UINT8)(crc16 >> 8);

    *pResult_len = 20;

    *preSSETC1 = tc;
    *preSSETC2 = tc;
    *preSSETS1 = ts_1;
    *preSSETS2 = ts_2;
    *bSendSSE1 = 0xff;
    *bSendSSE2 = 0xff;

	GM_Log_Msg(0,"Sending SSE: TC_1= %d, TS_1 = %x\n", tc, ts_1, 0, 0, 0, 0);
#ifdef WIN32
	printf(">>>>>>>>>>>>>>SSE: TC=%d, TS=%x, SEQENQ_1\n",tc, ts_1, SEQENQ_1);
#endif
    if (*pResult_len > GM_RSSP1_MAX_SAFETY_DAT_LEN)
    {
        return GM_RSSP1_ERROR;
    }
    else
    {
        return GM_RSSP1_OK;
    }
}

/*********************************FSFB_SSR_BUILD****************************************************************************
��;:����SSR����
����:msg(���ɱ���)
  sourAddr(FSFB SSR������ Դ��ַ)
  desAddr(FSFB SSR������ Ŀ���ַ)
  seqenq_1(�Է�����SSE������ͨ��1 seqenq��ֵ)
  seqenq_2(�Է�����SSE������ͨ��2 seqenq��ֵ)
  sid_r1(����ͨ��1 sid)
  sid_r2(����ͨ��2 sid)
  dataver_r1(�Է��豸ͨ��1��dataver)
  dataver_r2(�Է��豸ͨ��1��dataver)
  ts_r1(����ͨ��1 ʱ���)
  ts_r2(����ͨ��2 ʱ���)
  tc_e(��Ӧsse������ʱ���������ֵ)
  tc_r(����ʱ���������ֵ)
  num_dataver(�汾��ֵ,�̶�Ϊ1)
����ֵ:����SSR���ĳɹ�(GM_RSSP1_OK)
    ����SSR����ʧ��(GM_RSSP1_ERROR)
****************************************************************************************************************************/
GM_INT32 GM_RSSP1_SSR_BUILD_Int(GM_UINT8 *pResult , GM_UINT16 *pResult_len , GM_UINT16 sourAddr, GM_UINT16 desAddr, GM_UINT32 seqenq_1, GM_UINT32 seqenq_2, GM_UINT32 sid_r1, GM_UINT32 sid_r2,
                       GM_UINT32 dataver_r1, GM_UINT32 dataver_r2, GM_UINT32 ts_r1, GM_UINT32 ts_r2, GM_UINT32 tc_e, GM_UINT32 tc_r, GM_UINT8 num_dataver , GM_UINT32 *pCRC16_table)
{
    GM_UINT32 SEQINI_1  = 0;
    GM_UINT32 SEQINI_2  = 0;
    GM_UINT16 crc16    = 0;

    SEQINI_1 = seqenq_1 ^ sid_r1 ^ dataver_r1 ^ ts_r1;
    SEQINI_2 = seqenq_2 ^ sid_r2 ^ dataver_r2 ^ ts_r2;

    *(pResult + 0)        = RSSP1_SSR_PROTOCOL_TYPE;
    *(pResult + 1)        = RSSP1_SSR_FRAME_TYPE;
    *(pResult + 2)        = (GM_UINT8)(sourAddr & 0xff);
    *(pResult + 3)        = (GM_UINT8)(sourAddr >> 8);
    *(pResult + 4)        = (GM_UINT8)(desAddr & 0xff);
    *(pResult + 5)        = (GM_UINT8)(desAddr >> 8);

    *(pResult + 6)        = (GM_UINT8)(tc_r & 0xff);
    *(pResult + 7)        = (GM_UINT8)((tc_r & 0xff00) >> 8);
    *(pResult + 8)        = (GM_UINT8)((tc_r & 0xff0000) >> 16);
    *(pResult + 9)        = (GM_UINT8)((tc_r & 0xff000000) >> 24);

    *(pResult + 10)        = (GM_UINT8)(tc_e & 0xff);
    *(pResult + 11)        = (GM_UINT8)((tc_e & 0xff00) >> 8);
    *(pResult + 12)        = (GM_UINT8)((tc_e & 0xff0000) >> 16);
    *(pResult + 13)        = (GM_UINT8)((tc_e & 0xff000000) >> 24);

    *(pResult + 14)        = (GM_UINT8)(SEQINI_1 & 0xff);
    *(pResult + 15)        = (GM_UINT8)((SEQINI_1 & 0xff00) >> 8);
    *(pResult + 16)        = (GM_UINT8)((SEQINI_1 & 0xff0000) >> 16);
    *(pResult + 17)        = (GM_UINT8)((SEQINI_1 & 0xff000000) >> 24);

    *(pResult + 18)        = (GM_UINT8)(SEQINI_2 & 0xff);
    *(pResult + 19)        = (GM_UINT8)((SEQINI_2 & 0xff00) >> 8);
    *(pResult + 20)        = (GM_UINT8)((SEQINI_2 & 0xff0000) >> 16);
    *(pResult + 21)        = (GM_UINT8)((SEQINI_2 & 0xff000000) >> 24);

    *(pResult + 22)        = (GM_UINT8)(num_dataver);

	GM_CRC_Calculate_CRC16(pResult, 23, &crc16, (GM_UINT16*)pCRC16_table);

    *(pResult + 23)        = (GM_UINT8)(crc16 & 0xff);
    *(pResult + 24)        = (GM_UINT8)(crc16 >> 8);

    *pResult_len = 25;

	GM_Log_Msg(0,"Sending SSR: TC_R= %d, TC_E = %d, TS_R1 = %x\n", tc_r, tc_e, ts_r1, 0, 0, 0);
#ifdef WIN32
	printf(">>>>>>>>>>>>>>SSR:TC_R=%d, TC_E=%d, SEQINI_1=%x\n", tc_r, tc_e,SEQINI_1);
#endif
    if (*pResult_len > GM_RSSP1_MAX_SAFETY_DAT_LEN)
    {
        return GM_RSSP1_ERROR;
    }
    else
    {
        return GM_RSSP1_OK;
    }
}

/**********************************GM_RSSP1_SSR_CHN_SET***************************************************************************
��;:���ݽ��յ�SSR�������ý��շ���dynamic
����:left_tab(��������߼����������)
  right_tab(��������߼����������)
  seqini(���յ�SSR�����е�seqini��ֵ)
  prec_fisrtsint(PREC_FISRTSINT��ֵ)
  preSSEtc(��������SSE���ĵ�ʱ���������ֵ)
  preSSEts(��������SSE���ĵ�ʱ���������ֵ)
  dynamic
  tc(������ǰʱ���������ֵ)
  localTC(���յ�����ʱ������ʱ���������ֵ)
  remoteTC(���յ�����ʱ�Է���ʱ���������ֵ)
  TC_E(SSR�����ж�Ӧ��SSE�����еļ�������ֵ)
  TC_R(SSR�����жԷ���ʱ���������ֵ)
  bSendSSE(�����Ƿ���SSE, 0x00��ʾδ���� 0xff��ʾ���ͺ�δ�յ�SSR)
����ֵ:�ɹ�(GM_RSSP1_OK)
    ʧ��(GM_RSSP1_ERROR)
*****************************************************************************************************************************/
GM_INT32 GM_RSSP1_SSR_CHN_SET(GM_UINT32 *left_tab, GM_UINT32 *right_tab, GM_UINT32 seqini, GM_UINT32 prec_firstsint, GM_UINT32 preSSEtc, GM_UINT32 preSSEts, GM_UINT32 *dynamic,
                     GM_UINT32 tc, GM_UINT32 *localTC, GM_UINT32 *remoteTC, GM_UINT32 TC_E,  GM_UINT32 TC_R, GM_UINT8 *bSendSSE , GM_UINT32 ssr_valid_cycle)
{
	GM_LFSR reg = {0};

    if (TC_E != preSSEtc)
    {
        GM_Log_Msg(0,"FSFB ssr set: TC_E=%ld, preSSEtc=%ld\n", TC_E, preSSEtc, 0, 0, 0, 0);
        return GM_RSSP1_ERROR;
    }

    if (0x00 == *bSendSSE)
    {
        GM_Log_Msg(0,"FSFB ssr set err! local didn't send SSE!\n", TC_E, preSSEtc, 0, 0, 0, 0);
        return GM_RSSP1_ERROR;
    }

    /* bgn ���Ӷ�SSRʱЧ���ж�,������TC�ؾ��� jianghongjun TSRS00000125 */
    if (tc - TC_E > ssr_valid_cycle)
    {
        GM_Log_Msg(0,"@@@@FSFB ssr expire! Tsendsse:%d,now:%d.\n", TC_E, tc, 0, 0, 0, 0);
        return GM_RSSP1_ERROR;
    }
    /* end */

    GM_memset(&reg, 0, sizeof(reg));

    GM_LFSR_Init(&reg, left_tab, right_tab);
    GM_LFSR_Load(&reg, prec_firstsint);
    GM_LFSR_Add(&reg, seqini ^ preSSEts);

    if(GM_FALSE == GM_LFSR_Read(&reg , dynamic))
    {
        return GM_RSSP1_ERROR;
	}
	GM_Log_Msg(0,"Rcving SSR, TC =  %d , TC_R: = %d \n", tc, TC_R, 0, 0, 0, 0);

    *localTC = tc;
    *remoteTC = TC_R;

    *bSendSSE = 0x00;

    return GM_RSSP1_OK;
}

/*******************************FSFB_XSD_BUILD*********************************************************************
��;:����RSD����
����:msg(����)
     len(��Ҫ��װ���ĵĳ���)
  mstorslv(��������־,0x01:����, 0x02����)
  aorb(A\Bϵ��־, 0x80:A��, 0x81:B��)
  sourAddr(FSFB RSD������ Դ��ַ)
  desAddr(FSFB RSD������ Ŀ���ַ)
  tc(����ʱ���������ֵ)
  crcm1(ͨ��1 crcm��ֵ)
  crcm2(ͨ��2 crcm��ֵ)
����ֵ:�ɹ�(GM_RSSP1_OK)
    ʧ��(GM_RSSP1_ERROR)
******************************************************************************************************************/
GM_INT32 GM_RSSP1_RSD_BUILD_Int(GM_UINT8 *pResult , GM_UINT16 *pResult_len , GM_UINT8 *app_data, GM_UINT16 app_data_len, GM_UINT8 mstorslv, GM_UINT8 aorb, GM_UINT16 sourAddr, GM_UINT16 desAddr,
                       GM_UINT32 tc, GM_UINT32 crcm1, GM_UINT32 crcm2 , GM_UINT32* pCRC16_table)
{
    GM_UINT16 crc16 = 0;

    if ((app_data_len % 2) != 0)
    {
        /* return GM_RSSP1_ERROR; Ϊ����ʹ��fsfbģ�鴫��rssp2ͬ����Ϣ���޸� 2010-04-12 */  /* Ҫ�����Ϊż���ֽڳ��� */
    }

    *(pResult + 0) = mstorslv;

    *(pResult + 1) = aorb;
    *(pResult + 2) = (GM_UINT8)(sourAddr & 0xff);
    *(pResult + 3) = (GM_UINT8)(sourAddr >> 8);
    *(pResult + 4) = (GM_UINT8)(desAddr & 0xff);
    *(pResult + 5) = (GM_UINT8)(desAddr >> 8);

    *(pResult + 6) = (GM_UINT8)(tc & 0xff);
    *(pResult + 7) = (GM_UINT8)((tc & 0xff00) >> 8);
    *(pResult + 8) = (GM_UINT8)((tc & 0xff0000) >> 16);
    *(pResult + 9) = (GM_UINT8)((tc & 0xff000000) >> 24);

    *(pResult + 10) = (GM_UINT8)((app_data_len + 8) & 0xff);
    *(pResult + 11) = (GM_UINT8)((app_data_len + 8) >> 8);

    /* ��CRCM��� */
    *(pResult + 12) ^= (GM_UINT8)(crcm1 & 0xff);
    *(pResult + 13) ^= (GM_UINT8)((crcm1 & 0xff00) >> 8);
    *(pResult + 14) ^= (GM_UINT8)((crcm1 & 0xff0000) >> 16);
    *(pResult + 15) ^= (GM_UINT8)((crcm1 & 0xff000000) >> 24);

    *(pResult + 16) ^= (GM_UINT8)(crcm2 & 0xff);
    *(pResult + 17) ^= (GM_UINT8)((crcm2 & 0xff00) >> 8);
    *(pResult + 18) ^= (GM_UINT8)((crcm2 & 0xff0000) >> 16);
    *(pResult + 19) ^= (GM_UINT8)((crcm2 & 0xff000000) >> 24);

    GM_memcpy(pResult + 20 , app_data, app_data_len);

	GM_CRC_Calculate_CRC16(pResult, 20 + app_data_len, &crc16, (GM_UINT16*)pCRC16_table);

    *(pResult + 20 + app_data_len)        = (GM_UINT8)(crc16 & 0xff);
    *(pResult + 21 + app_data_len)        = (GM_UINT8)(crc16 >> 8);

    *pResult_len = 22 + app_data_len;

	GM_Log_Msg(0,"Sending RSD: TC = %d\n", tc, 0, 0, 0, 0, 0);
#ifdef WIN32
 	GM_Log_Msg(0,">>>>>>>>>>>>>RSD: TC=%d, CRCM_1=%x\n",tc, crcm1,0,0,0,0);
#endif
    if (*pResult_len > GM_RSSP1_MAX_SAFETY_DAT_LEN)
    {
        return GM_RSSP1_ERROR;
    }
    else
    {
        return GM_RSSP1_OK;
    }
}

/***************************************FSFB_PREC_SINT_CAL***********************************************************
��;:��ʼ��ʱ����prec_sinit
����:sinit(sint����)
     sid(sid����)
  prec_sinit()
  left_tab(��������߼����������)
  right_tab(��������߼����������)
����ֵ:�ɹ�(GM_RSSP1_OK)
    ʧ��(GM_RSSP1_ERROR)
*********************************************************************************************************************/
GM_INT32 GM_RSSP1_PREC_SINT_CAL_Int(GM_UINT32 sinit, GM_UINT32 sid, GM_UINT32 *prec_sinit, GM_UINT32 *left_tab, GM_UINT32 *right_tab , GM_INT32 max_delta_time)
{
    GM_INT32 i = 0;
	GM_INT32 j = 0;
    GM_UINT32 x = 0;
	GM_LFSR reg = {0};
    GM_memset(&reg, 0, sizeof(reg));
    GM_LFSR_Init(&reg, left_tab, right_tab);

    if ((max_delta_time < 0) || (max_delta_time > GM_RSSP1_MAX_DELTATIME_ARRAY_SIZE))
    {
        return GM_RSSP1_ERROR;
    }

    for (i = 0; i < max_delta_time; i++)
    {
        GM_LFSR_Load(&reg, sinit);
        GM_LFSR_Add(&reg, sid);

        for (j = 0; j < i; j++)
        {
            GM_LFSR_Add(&reg, 0);
        }

        GM_LFSR_Post(&reg, sinit);

        if(GM_FALSE == GM_LFSR_Read(&reg , &x))
        {
            return GM_RSSP1_ERROR;
        }
        *(prec_sinit + i) = x ^ sid;
    }

    return GM_RSSP1_OK;
}

/***************************GM_RSSP1_PREC_FIRSTSINIT_CAL**************************************************************************
��;:����prec_firstinit
����:sint_r(�Է��ڵ��sint��ֵ)
  sid_e(���ڵ��sid��ֵ)
  dataver_r(�Է��ڵ��dataver��ֵ)
  prec_firstsinit(���ص���ԶԷ��ڵ��prec_firstsinit��ֵ)
  left_tab(��������߼����������)
  right_tab(��������߼����������)
����ֵ:�ɹ�(GM_RSSP1_OK)
    ʧ��(GM_RSSP1_ERROR)
*****************************************************************************************************************************/
GM_INT32 GM_RSSP1_PREC_FIRSTSINIT_CAL(GM_UINT32 sint_r, GM_UINT32 sid_e, GM_UINT32 dataver_r, GM_UINT32 *prec_firstsinit, GM_UINT32 *left_tab, GM_UINT32 *right_tab)
{
    GM_UINT32   x;
    GM_LFSR reg;

    if((NULL == prec_firstsinit) || (NULL == left_tab) || (NULL == right_tab) )
    {
        return GM_RSSP1_ERROR;
    }
    GM_memset(&reg, 0, sizeof(reg));
    GM_LFSR_Init(&reg, left_tab, right_tab);
    GM_LFSR_Load(&reg, sint_r);
    GM_LFSR_Add(&reg, sid_e ^ dataver_r);
    if(GM_FALSE == GM_LFSR_Read(&reg , &x))
    {
        return GM_RSSP1_ERROR;
    }
    GM_LFSR_Load(&reg, 0);
    GM_LFSR_Post(&reg, x);
    if(GM_FALSE == GM_LFSR_Read(&reg , prec_firstsinit))
    {
        return GM_RSSP1_ERROR;
    }
    return GM_RSSP1_OK;
}

/*********************************GM_RSSP1_POST_RXDATA_Int***************************************************************************
��;:Ԥ����У����post_rxdata
����:sinit(�Է��ڵ�sinit)
     sid(�Է��ڵ��sid)
  post_rxdata(post_rxdata������)
  left_tab(��������߼����������)
  right_tab(��������߼����������)
����ֵ:�ɹ�(GM_RSSP1_OK)
    ʧ��(GM_RSSP1_ERROR)
****************************************************************************************************************************/
GM_INT32 GM_RSSP1_POST_RXDATA_Int(GM_UINT32 sinit, GM_UINT32 sid, GM_UINT32 *post_rxdata, GM_UINT32 *left_tab, GM_UINT32 *right_tab , GM_INT32 max_delta_time)
{
    GM_INT32 i, j;
    GM_UINT32 x;
    GM_LFSR reg;

    if ((max_delta_time < 0) || (max_delta_time > GM_RSSP1_MAX_DELTATIME_ARRAY_SIZE))
    {
        return GM_RSSP1_ERROR;
    }

    GM_memset(&reg, 0, sizeof(reg));

    GM_LFSR_Init(&reg, left_tab, right_tab);

    for (i = 0; i < max_delta_time; i++)
    {
        GM_LFSR_Load(&reg, sinit);
        GM_LFSR_Add(&reg, sid);

        for (j = 0; j < i; j++)
        {
            GM_LFSR_Add(&reg, 0);
        }

        GM_LFSR_Add(&reg, sid);

        if(GM_FALSE == GM_LFSR_Read(&reg , &x))
        {
            return GM_RSSP1_ERROR;
        }
        GM_LFSR_Load(&reg, 0);
        GM_LFSR_Add(&reg, x);
        if(GM_FALSE == GM_LFSR_Read(&reg , post_rxdata + i))
        {
            return GM_RSSP1_ERROR;
        }
    }

    return GM_RSSP1_OK;
}
