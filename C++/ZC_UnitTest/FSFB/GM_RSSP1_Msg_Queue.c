
#include "GM_RSSP1_Msg_Queue.h"


GM_BOOL FSFB_Msg_Queue_Init(GM_RSSP1_Msg_Queue_struct *pQueuestruct , GM_UINT32 Q_size , GM_UINT32 Q_offset , GM_RSSP1_Msg_Queue_TYPE_Enum type)
{
    if (NULL == pQueuestruct || (NULL == Q_offset))

    {
        return GM_FALSE;
    }

    pQueuestruct->type          = type;

    pQueuestruct->head_Position = 0;
    pQueuestruct->tail_Position = 0;
    pQueuestruct->count         = 0;
    pQueuestruct->Q_size        = Q_size;
    pQueuestruct->Q_offset      = Q_offset;

    return GM_TRUE;
}

GM_BOOL FSFB_Msg_Queue_Clear(GM_RSSP1_Msg_Queue_struct *pQueuestruct)
{
    if (NULL == pQueuestruct)
    {
        return GM_FALSE;
    }

    pQueuestruct->head_Position = 0;

    pQueuestruct->tail_Position = 0;
    pQueuestruct->count         = 0;

    return GM_TRUE;
}

GM_BOOL FSFB_Is_Msg_Queue_Empty(GM_RSSP1_Msg_Queue_struct *pQueuestruct)
{
    if (NULL == pQueuestruct)
    {
        return GM_TRUE;
    }

    if (pQueuestruct->count > 0)
    {
        return GM_FALSE;
    }
    else
    {
        return GM_TRUE;
    }
}

GM_BOOL FSFB_Is_Msg_Queue_Full(GM_RSSP1_Msg_Queue_struct *pQueuestruct)
{
    if (NULL == pQueuestruct)
    {
        return GM_FALSE;
    }

    if (pQueuestruct->count == pQueuestruct->Q_size)
    {
        return GM_TRUE;
    }
    else
    {
        return GM_FALSE;
    }
}

GM_INT32 FSFB_Get_Queue_Count(GM_RSSP1_Msg_Queue_struct *pQueuestruct)
{
    if (NULL == pQueuestruct)
    {
        return -1;
    }

    if (pQueuestruct->count > pQueuestruct->Q_size)
    {
        return -1;
    }

    return pQueuestruct->count;
}

GM_BOOL FSFB_Msg_Queue_Get(GM_RSSP1_Msg_Queue_struct *pQueuestruct, void *pQElement)
{
    GM_RSSP1_SFM_U2L_pri_struct *pSFM_U2L_pri   = NULL;
    GM_RSSP1_SFM_L2U_pri_struct *pSFM_L2U_pri   = NULL;
    GM_RSSP1_CFM_U2L_pri_struct *pCFM_U2L_pri   = NULL;
    GM_RSSP1_CFM_L2U_pri_struct *pCFM_L2U_pri   = NULL;
    GM_RSSP1_com_pri_struct *precv_pri     = NULL;
    GM_RSSP1_com_pri_struct *psend_pri     = NULL;

    if ((NULL == pQueuestruct) || (NULL == pQElement))
    {
        return GM_FALSE;
    }

    if (NULL == pQueuestruct->Q_offset)
    {
        return GM_FALSE;
    }

    if (GM_TRUE == FSFB_Is_Msg_Queue_Empty(pQueuestruct))
    {
        return GM_FALSE;
    }

    switch (pQueuestruct->type)
    {

		case FSFB_Q_TYPE_SFM_U2L_PRI:
			pSFM_U2L_pri = (GM_RSSP1_SFM_U2L_pri_struct *)((GM_RSSP1_SFM_U2L_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->head_Position);
			*((GM_RSSP1_SFM_U2L_pri_struct *)pQElement) = *pSFM_U2L_pri;
			break;

		case FSFB_Q_TYPE_SFM_L2U_PRI:
			pSFM_L2U_pri = (GM_RSSP1_SFM_L2U_pri_struct *)((GM_RSSP1_SFM_L2U_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->head_Position);
			*((GM_RSSP1_SFM_L2U_pri_struct *)pQElement) = *pSFM_L2U_pri;
			break;

		case FSFB_Q_TYPE_CFM_U2L_PRI:
			pCFM_U2L_pri = (GM_RSSP1_CFM_U2L_pri_struct *)((GM_RSSP1_CFM_U2L_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->head_Position);
			*((GM_RSSP1_CFM_U2L_pri_struct *)pQElement) = *pCFM_U2L_pri;
			break;

        case FSFB_Q_TYPE_CFM_L2U_PRI:
            pCFM_L2U_pri = (GM_RSSP1_CFM_L2U_pri_struct *)((GM_RSSP1_CFM_L2U_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->head_Position);
            *((GM_RSSP1_CFM_L2U_pri_struct *)pQElement) = *pCFM_L2U_pri;
            break;

        case FSFB_Q_TYPE_SENT_PKT:
            psend_pri = (GM_RSSP1_com_pri_struct *)((GM_RSSP1_com_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->head_Position);
            *((GM_RSSP1_com_pri_struct *)pQElement) = *psend_pri;
            break;

        case FSFB_Q_TYPE_RCVD_PKT:
            precv_pri = (GM_RSSP1_com_pri_struct *)((GM_RSSP1_com_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->head_Position);
            *((GM_RSSP1_com_pri_struct *)pQElement) = *precv_pri;
            break;
        default:
            return GM_FALSE;
    }

    --(pQueuestruct->count);

    pQueuestruct->head_Position = (pQueuestruct->head_Position + 1) % (pQueuestruct->Q_size);


    return GM_TRUE;
}

GM_RSSP1_Write_Q_Return_Enum FSFB_Msg_Queue_Write(GM_RSSP1_Msg_Queue_struct *pQueuestruct, void *pQElement)
{
    GM_RSSP1_SFM_U2L_pri_struct *pSFM_U2L_pri   = NULL;
    GM_RSSP1_SFM_L2U_pri_struct *pSFM_L2U_pri   = NULL;
    GM_RSSP1_CFM_U2L_pri_struct *pCFM_U2L_pri   = NULL;
    GM_RSSP1_CFM_L2U_pri_struct *pCFM_L2U_pri   = NULL;
    GM_RSSP1_com_pri_struct *precv_pri     = NULL;
    GM_RSSP1_com_pri_struct *psend_pri     = NULL;

    GM_BOOL bQ_full    = GM_FALSE;
    if ((NULL == pQueuestruct) || (NULL == pQElement))
    {
		printf("Queue_Write111\n");
        return Q_WRITE_FAIL;
    }

    if (0 >= pQueuestruct->Q_size)
    {
		printf("Queue_Write222\n");		
        return Q_WRITE_FAIL;
    }

    if (GM_TRUE == FSFB_Is_Msg_Queue_Full(pQueuestruct))
    {
        bQ_full     = GM_TRUE;

        if (GM_FALSE == FSFB_Msg_Queue_Pop(pQueuestruct))
        {
		printf("Queue_Write333\n");			
            return Q_WRITE_FAIL;
        }
    }


    ++(pQueuestruct->count);

    switch (pQueuestruct->type)
    {

		case FSFB_Q_TYPE_SFM_U2L_PRI:
			pSFM_U2L_pri = (GM_RSSP1_SFM_U2L_pri_struct *)((GM_RSSP1_SFM_U2L_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->tail_Position);
			*pSFM_U2L_pri = *((GM_RSSP1_SFM_U2L_pri_struct *)pQElement);
			break;

		case FSFB_Q_TYPE_SFM_L2U_PRI:
			pSFM_L2U_pri = (GM_RSSP1_SFM_L2U_pri_struct *)((GM_RSSP1_SFM_L2U_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->tail_Position);
			*pSFM_L2U_pri = *((GM_RSSP1_SFM_L2U_pri_struct *)pQElement);
			break;

		case FSFB_Q_TYPE_CFM_U2L_PRI:
			pCFM_U2L_pri = (GM_RSSP1_CFM_U2L_pri_struct *)((GM_RSSP1_CFM_U2L_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->tail_Position);
			*pCFM_U2L_pri = *((GM_RSSP1_CFM_U2L_pri_struct *)pQElement);
			break;

        case FSFB_Q_TYPE_CFM_L2U_PRI:
            pCFM_L2U_pri = (GM_RSSP1_CFM_L2U_pri_struct *)((GM_RSSP1_CFM_L2U_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->tail_Position);
            *pCFM_L2U_pri = *((GM_RSSP1_CFM_L2U_pri_struct *)pQElement);
            break;

        case FSFB_Q_TYPE_SENT_PKT:
            psend_pri = (GM_RSSP1_com_pri_struct *)((GM_RSSP1_com_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->tail_Position);
            *psend_pri = *((GM_RSSP1_com_pri_struct *)pQElement);
            break;

        case FSFB_Q_TYPE_RCVD_PKT:
            precv_pri = (GM_RSSP1_com_pri_struct *)((GM_RSSP1_com_pri_struct *)(pQueuestruct->Q_offset) + pQueuestruct->tail_Position);
            *precv_pri = *((GM_RSSP1_com_pri_struct *)pQElement);
            break;

        default:
        --(pQueuestruct->count);
		printf("Invalid msg type=%d\n",pQueuestruct->type);
        return Q_WRITE_FAIL;
    }

    pQueuestruct->tail_Position = (pQueuestruct->tail_Position + 1) % (pQueuestruct->Q_size);

    if (GM_TRUE == bQ_full)
    {
		
        return Q_WRITE_OK_FULL;
    }
    else
    {
		

        return Q_WRITE_OK_NOT_FULL;
    }
}

GM_BOOL FSFB_Msg_Queue_Pop(GM_RSSP1_Msg_Queue_struct  *pQueuestruct)
{
    if (NULL == pQueuestruct)
    {
        return GM_FALSE;
    }

    if (GM_TRUE == FSFB_Is_Msg_Queue_Empty(pQueuestruct))
    {
        return GM_TRUE;
    }



    --(pQueuestruct->count);

    pQueuestruct->head_Position = (pQueuestruct->head_Position + 1) % (pQueuestruct->Q_size);

    return GM_TRUE;
}

