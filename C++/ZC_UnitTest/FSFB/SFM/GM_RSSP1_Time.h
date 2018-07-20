#ifndef _GM_RSSP1_TIME_H_
#define _GM_RSSP1_TIME_H_

#include "../GM_RSSP1_Utils.h"

#ifdef __cplusplus
extern "C"
{
#endif

	#define MAX_CHANNEL_NUM  GM_RSSP1_CHECK_CHN_NUM

    struct _GM_RSSP1_TIME_CYCLE_
    {
        GM_UINT8 lifeTime;
        GM_UINT8 deltaTime;
    };

    typedef struct _GM_RSSP1_TIME_CYCLE_ GM_RSSP1_TIME_CYCLE_;

    struct _GM_RSSP1_TIME_
    {
        /*
         SEM_ID  semMTime;     / *ª•≥‚–≈∫≈¡ø* /
        */
        GM_UINT32 *left_tab[MAX_CHANNEL_NUM];
        GM_UINT32  TC;
        GM_UINT32  TS[MAX_CHANNEL_NUM];
        GM_UINT32  oldTS[MAX_CHANNEL_NUM];
    };

    typedef struct _GM_RSSP1_TIME_ GM_RSSP1_TIME;

	extern GM_INT32 GM_RSSP1_TIME_INIT_Int(GM_RSSP1_TIME *time, GM_UINT32 *left_tab1, GM_UINT32 *left_tab2, GM_UINT32 ts0_a, GM_UINT32 ts0_b);
    extern GM_INT32 GM_RSSP1_TIME_STEP(GM_RSSP1_TIME *time);
    extern GM_INT32 GM_RSSP1_TIME_GET(GM_RSSP1_TIME *time, GM_UINT32 *tc, GM_UINT32 *ts_a, GM_UINT32 *ts_b);
    extern GM_INT32 GM_RSSP1_TIME_SET(GM_RSSP1_TIME *time, GM_UINT32 tc, GM_UINT32 ts_a, GM_UINT32 ts_b);

#ifdef __cplusplus
}
#endif


#endif
