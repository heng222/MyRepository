/************************************************************************
*
* �ļ���   ��  RouteStatusData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·״̬����
* ��  ע   ��  ��
*
************************************************************************/
#include "RouteStatusData.h"
#include "RouteConfigData.h"

RouteDataStruct gRouteStatusDataStruBuff[ROUTE_LOCAL_SUM_MAX];          /*���ع���ı�������״̬��Ϣ*/

/*
* ���������� ��ȡ��·����
* ����˵���� void    
* ����ֵ  �� NULL: ��ȡ����ʧ��
*			 !NULL: ��·����
*/
RouteDataStruct* GetRouteStatusData(void)
{
	return gRouteStatusDataStruBuff;
}

/*
* ���������� ��ȡ��·��ǰ״̬
* ����˵���� const routeId ��·ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��·״̬
*/
UINT8_S GetRouteStatus(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteStatusDataStruBuff[bufIndex].RouteStatus;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ���ý�·��ǰ״̬
* ����˵���� const UINT16  routeId ��·ID; 
*	         UINT8_S routeStatus ��·״̬    
* ����ֵ  �� 0;ʧ��
*            1;�ɹ�
*/
UINT8_S SetRouteStatus(const UINT16_S routeId,UINT8_S routeStatus)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		if ((ROUTE_STATE_SET == routeStatus) || (ROUTE_STATE_UNSET == routeStatus))
		{
			gRouteStatusDataStruBuff[bufIndex].RouteStatus = routeStatus;
			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ��·ͣ����֤����
* ����˵���� const UINT16_S routeId ��·ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��·״̬
*/
UINT8_S GetRouteStopReq(const UINT16_S routeId)
{

    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

    if (bufIndex < GetRouteSum())
    {
        rtnValue = gRouteStatusDataStruBuff[bufIndex].RouteStopReq;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� ���ý�·ͣ����֤����
* ����˵���� const UINT16_S routeId ��·ID    
*          const UINT8_S routeStopReq,��·ͣ����֤����
* ����ֵ  �� 0: ʧ��
*			1: �ɹ�
*/
UINT8_S SetRouteStopReq(const UINT16_S routeId,const UINT8_S routeStopReq)	
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

    if (bufIndex < GetRouteSum())
    {
        if ((ROUTE_STOP_REQ_SET == routeStopReq) || (ROUTE_STOP_REQ_UNSET == routeStopReq))
        {
            gRouteStatusDataStruBuff[bufIndex].RouteStopReq = routeStopReq;
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;

}


/*
* ���������� ��ȡ��·ͣ����֤ȷ��
* ����˵���� const UINT16_S routeId ��·ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��·״̬
*/
UINT8_S GetRouteStopConfirm(const UINT16_S routeId)
{

    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

    if (bufIndex < GetRouteSum())
    {
        rtnValue = gRouteStatusDataStruBuff[bufIndex].RouteStopConfirm;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*
* ���������� ���ý�·ͣ����֤ȷ��
* ����˵���� const UINT16_S routeId ��·ID    
*          const UINT8_S routeStopConfirm,��·ͣ����֤ȷ��
* ����ֵ  �� 0: ʧ��
*			1: �ɹ�
*/
UINT8_S SetRouteStopConfirm(const UINT16_S routeId,const UINT8_S routeStopConfirm)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

    if (bufIndex < GetRouteSum())
    {
        if ((ROUTE_STOP_CONFIRM_SET == routeStopConfirm) || (ROUTE_STOP_CONFIRM_UNSET == routeStopConfirm))
        {
            gRouteStatusDataStruBuff[bufIndex].RouteStopConfirm = routeStopConfirm;
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;

}