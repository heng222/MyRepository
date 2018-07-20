
#include "GM_RSSP1_TIME.h"
#include "../GM_RSSP1_Utils.h"

GM_INT32 GM_RSSP1_TIME_INIT_Int(GM_RSSP1_TIME *time, GM_UINT32 *left_tab1, GM_UINT32 *left_tab2, GM_UINT32 ts0_a, GM_UINT32 ts0_b);
GM_INT32 GM_RSSP1_TIME_STEP(GM_RSSP1_TIME *time);
GM_INT32 GM_RSSP1_TIME_GET(GM_RSSP1_TIME *time, GM_UINT32 *tc, GM_UINT32 *ts_a, GM_UINT32 *ts_b);
GM_INT32 GM_RSSP1_TIME_SET(GM_RSSP1_TIME *time, GM_UINT32 tc, GM_UINT32 ts_a, GM_UINT32 ts_b);

GM_INT32 GM_RSSP1_TIME_INIT_Int(GM_RSSP1_TIME *time, GM_UINT32 *left_tab1, GM_UINT32 *left_tab2, GM_UINT32 ts0_a, GM_UINT32 ts0_b)
{
    time->TC = 0;

    time->oldTS[0] = 0;
    time->oldTS[1] = 0;

    time->TS[0] = ts0_a;
    time->TS[1] = ts0_b;

    time->left_tab[0] = left_tab1;
    time->left_tab[1] = left_tab2;

    return GM_RSSP1_OK;
}

GM_INT32 GM_RSSP1_TIME_STEP(GM_RSSP1_TIME *time)
{
    GM_INT32 i;
    GM_LFSR reg;

    time->TC = time->TC + 1;

    for (i = 0; i < MAX_CHANNEL_NUM; i++)
    {
        GM_LFSR_Init(&reg, time->left_tab[i], (GM_UINT32*)&i);
        GM_LFSR_Load(&reg, time->TS[i]);
        GM_LFSR_Add(&reg, 0);
        time->oldTS[i] = time->TS[i];
        if(GM_RSSP1_ERROR == GM_LFSR_Read(&reg , &(time->TS[i])))
        {
            return GM_RSSP1_ERROR;
        }
    }

    return GM_RSSP1_OK;
}

GM_INT32 GM_RSSP1_TIME_GET(GM_RSSP1_TIME *time, GM_UINT32 *tc, GM_UINT32 *ts_a, GM_UINT32 *ts_b)
{
    *tc = time->TC;

    *ts_a = time->TS[0];
    *ts_b = time->TS[1];

    return GM_RSSP1_OK;
}

GM_INT32 GM_RSSP1_TIME_SET(GM_RSSP1_TIME *time, GM_UINT32 tc, GM_UINT32 ts_a, GM_UINT32 ts_b)
{

    time->TC = tc;

    time->TS[0] = ts_a;
    time->TS[1] = ts_b;

    return GM_RSSP1_OK;
}
