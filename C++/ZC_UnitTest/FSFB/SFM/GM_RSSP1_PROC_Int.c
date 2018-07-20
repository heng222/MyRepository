#include "GM_RSSP1_PROC_Int.h"
#include "../GM_RSSP1_Msg_Define.h"
#include "../GM_RSSP1_Utils.h"

/********************GM_GM_UINT32M_CHN_CHECK_Int********************************************************
用途:对接收到的报文进行FSFB校验
参数:crcm(接收报文某一通道的crcm值)
  crc32(接收报文CRC校验值)
  syscheck(系统校核字)
  left_tab(查表法线形逻辑左移运算表)
  right_tab(查表法线形逻辑右移运算表)
  msgTC(报文中计数器数值)
  tc(本机某通道计数器数值)
  localTC(本机器最近一次接收到报文时本机该通道计数器数值)
  remoteTC(本机器最近一次接收到报文时报文中计数器数值)
  dynamickey(sint+(sid~t(n-1))
  prec_sint(用于计算从dynamickey计算出新的dynamickey)
  post_data(存放正确计算结果, 范围跟随deltaTime变化)
  cycle(存放计算用周期常数)
  p_peer_crc (接收到的数据中的CRC值)
返回值:正确(GM_RSSP1_OK)
    错误(GM_RSSP1_ERROR)
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
        return GM_RSSP1_RETURN_RESERVED;  /* jianghongjun mod 20101222。针对CR：LKD00000389  包西修改站间通信不稳定。UDP乱序时，收到旧数据包不认为校验失败，直接返回，丢弃数据 */
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
用途:生成SSE报文
参数:msg(SSE报文)
  sourAddr(FSFB SSE报文中 源地址)
  desAddr(FSFB SSE报文中 目标地址)
  tc(本机器的时间计数器)
  sid_1(通道1 sid)
  ts_1(通道1 时间戳)
  sid_2(通道2 sid)
  ts_2(通道2 时间戳)
  preSSETC1(上一次发送SSE 通道1 的时间计数器数值)
  preSSETC2(上一次发送SSE 通道2 的时间计数器数值)
  bSendSSE1(0xff(发送了SSE但还未收到SSR), 0x00(未发送SSE))
  bSendSSE2(0xff(发送了SSE但还未收到SSR), 0x00(未发送SSE))
返回值:生成SSE报文成功(GM_RSSP1_OK)
    生成SSE报文失败(GM_RSSP1_ERROR)
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
用途:生成SSR报文
参数:msg(生成报文)
  sourAddr(FSFB SSR报文中 源地址)
  desAddr(FSFB SSR报文中 目标地址)
  seqenq_1(对方发送SSE报文中通道1 seqenq数值)
  seqenq_2(对方发送SSE报文中通道2 seqenq数值)
  sid_r1(本机通道1 sid)
  sid_r2(本机通道2 sid)
  dataver_r1(对方设备通道1的dataver)
  dataver_r2(对方设备通道1的dataver)
  ts_r1(本机通道1 时间戳)
  ts_r2(本机通道2 时间戳)
  tc_e(对应sse报文中时间计数器数值)
  tc_r(本机时间计数器数值)
  num_dataver(版本数值,固定为1)
返回值:生成SSR报文成功(GM_RSSP1_OK)
    生成SSR报文失败(GM_RSSP1_ERROR)
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
用途:根据接收到SSR报文设置接收方的dynamic
参数:left_tab(查表法线形逻辑左移运算表)
  right_tab(查表法线形逻辑右移运算表)
  seqini(接收到SSR报文中的seqini数值)
  prec_fisrtsint(PREC_FISRTSINT数值)
  preSSEtc(本机发送SSE报文的时间计数器数值)
  preSSEts(本机发送SSE报文的时间计数器数值)
  dynamic
  tc(本机当前时间计数器数值)
  localTC(接收到报文时本机的时间计数器数值)
  remoteTC(接收到报文时对方的时间计数器数值)
  TC_E(SSR报文中对应的SSE报文中的计数器数值)
  TC_R(SSR报文中对方的时间计数器数值)
  bSendSSE(本机是否发送SSE, 0x00表示未发送 0xff表示发送后未收到SSR)
返回值:成功(GM_RSSP1_OK)
    失败(GM_RSSP1_ERROR)
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

    /* bgn 增加对SSR时效性判断,不考虑TC回卷，。 jianghongjun TSRS00000125 */
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
用途:生成RSD报文
参数:msg(报文)
     len(需要封装报文的长度)
  mstorslv(主备机标志,0x01:主机, 0x02备机)
  aorb(A\B系标志, 0x80:A机, 0x81:B机)
  sourAddr(FSFB RSD报文中 源地址)
  desAddr(FSFB RSD报文中 目标地址)
  tc(本机时间计数器数值)
  crcm1(通道1 crcm数值)
  crcm2(通道2 crcm数值)
返回值:成功(GM_RSSP1_OK)
    失败(GM_RSSP1_ERROR)
******************************************************************************************************************/
GM_INT32 GM_RSSP1_RSD_BUILD_Int(GM_UINT8 *pResult , GM_UINT16 *pResult_len , GM_UINT8 *app_data, GM_UINT16 app_data_len, GM_UINT8 mstorslv, GM_UINT8 aorb, GM_UINT16 sourAddr, GM_UINT16 desAddr,
                       GM_UINT32 tc, GM_UINT32 crcm1, GM_UINT32 crcm2 , GM_UINT32* pCRC16_table)
{
    GM_UINT16 crc16 = 0;

    if ((app_data_len % 2) != 0)
    {
        /* return GM_RSSP1_ERROR; 为了能使用fsfb模块传输rssp2同步消息而修改 2010-04-12 */  /* 要求必须为偶数字节长度 */
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

    /* 与CRCM异或 */
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
用途:初始化时计算prec_sinit
参数:sinit(sint参数)
     sid(sid参数)
  prec_sinit()
  left_tab(查表法线形逻辑左移运算表)
  right_tab(查表法线形逻辑右移运算表)
返回值:成功(GM_RSSP1_OK)
    失败(GM_RSSP1_ERROR)
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
用途:计算prec_firstinit
参数:sint_r(对方节点的sint数值)
  sid_e(本节点的sid数值)
  dataver_r(对方节点的dataver数值)
  prec_firstsinit(返回的针对对方节点的prec_firstsinit数值)
  left_tab(查表法线形逻辑左移运算表)
  right_tab(查表法线形逻辑右移运算表)
返回值:成功(GM_RSSP1_OK)
    失败(GM_RSSP1_ERROR)
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
用途:预计算校验结果post_rxdata
参数:sinit(对方节点sinit)
     sid(对方节点的sid)
  post_rxdata(post_rxdata计算结果)
  left_tab(查表法线形逻辑左移运算表)
  right_tab(查表法线形逻辑右移运算表)
返回值:成功(GM_RSSP1_OK)
    失败(GM_RSSP1_ERROR)
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
