/************************************************************************
*
* �ļ���   ��  RouteConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·�������ݹ���
* ��  ע   ��  ��
*
************************************************************************/
#include "RouteConfigData.h"

RouteConfigDataStruct gRouteConfigDataStruBuff[ROUTE_LOCAL_SUM_MAX];                  /*���ع���Ľ�·������Ϣ*/
UINT16_S gRouteIdBuff[ROUTE_SUM_MAX] = {0U};                                          /*�����·ӳ������*/
UINT16_S gRouteCurSum = 0U;                                                          /*��·��ǰ����*/

/*
* ���������� ��ȡ��·��������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��·��ǰ����
*/
UINT16_S GetRouteSum(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gRouteCurSum >= ROUTE_LOCAL_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gRouteCurSum;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ�������±��Ӧ�Ľ�·ID
* ����˵���� const UINT16 bufIndex, �����±�    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��·ID      
*/
UINT16_S GetRouteId(const UINT16_S bufIndex)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].RouteId;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·������
* ����˵���� const UINT16 routeId,��·ID
* ����ֵ  ��  ROUTE_SUM_MAX;��ȡ����ʧ��
*			  >=0U;���������ɹ�
*/
UINT16_S GetRouteConfigBufIndex(const UINT16_S routeId)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if ((routeId >= 1U)&&(routeId < ROUTE_SUM_MAX))
	{
		rtnValue = gRouteIdBuff[routeId];
	}
	else
	{
		rtnValue = ROUTE_SUM_MAX;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��IDվ̨��·��������ID
* ����˵���� const UINT16 routeId,��·ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��������ID      
*/
UINT8_S GetRouteBelongCiId(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].BelongCiId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·����ZC��ID
* ����˵���� const UINT16 psbId, ��·ID    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZcID      
*/
UINT8_S GetRouteBelongZcId(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].BelongZcId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·������������
* ����˵���� const UINT16 routeId, ��·ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT16_S GetRouteChangeAttribute(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].ChangeAttribute;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·����
* ����˵���� const UINT16 routeId, ��·ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetRouteType(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].RouteType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·��������
* ����˵���� const UINT16 routeId, ��·ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetRouteAreaType(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].RouteAreaType;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ����·Id�ķ����źŻ�Id
* ����˵���� const UINT16 routeId, ��·ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT16_S GetRouteOfSingalId(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].RouteSingalId;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·�ڱ�����������
* ����˵���� const UINT16 routeId, ��·ID     
* ����ֵ  �� DEFAULT_UINT8_VALUE: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetRouteOfOverlapNum(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].OverlapNum;
	}
	else
	{
		rtnValue = DEFAULT_UINT8_VALUE;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·�ڱ�������Idbuff
* ����˵���� const UINT16 routeId, ��·ID   
*			 UINT8_S bufSize,��������С��
*            UINT16_S overlapIdBuff[],�������
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			RETURN_SUCCESS: ��ȡ�ɹ�      
*/
UINT8_S GetRoutOfOverlapIdBuff(const UINT16_S routeId,UINT8_S bufSize,UINT16_S overlapIdBuff[])
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;   
    UINT8_S routeOfOverlapNum = DEFAULT_UINT8_VALUE;  /* ��·���������������� */

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if ((bufIndex < GetRouteSum())
		&& (bufSize >= ROUTE_OF_OVERLAP_SUM_MAX)
		&& (overlapIdBuff != NULL))
	{
        routeOfOverlapNum = GetRouteOfOverlapNum(routeId);

        if(DEFAULT_UINT8_VALUE == routeOfOverlapNum)
        {
            rtnValue = RETURN_ERROR;
        }
        else
        {
            for (cycle = 0U; cycle < routeOfOverlapNum; cycle++)
            {
                overlapIdBuff[cycle] = gRouteConfigDataStruBuff[bufIndex].OverlapIdBuff[cycle];
            }
            rtnValue = RETURN_SUCCESS;
        } 		
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
	
/*
* ���������� ��ȡָ��ID��·�ڼ�����������
* ����˵���� const UINT16 routeId, ��·ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetRouteOfAcNum(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].AcNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��id��·��ָ���±�ļ�������Id
* ����˵���� const UINT16 routeId, ��·ID   
*			 UINT8_S index,��ѯ�±�
*            UINT16_S *outAcId,�����������ID
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: ��ȡ�ɹ�      
*/
UINT8_S GetRoutOfAcIdFromIndex(const UINT16_S routeId,UINT8_S index,UINT16_S *outAcId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S rtnValue = DEFAULT_ZERO;

	if (NULL != outAcId)
	{
		bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/
		*outAcId = DEFAULT_ZERO;

		if ((bufIndex < GetRouteSum())
			&& (index < GetRouteOfAcNum(routeId)))
		{
			*outAcId = gRouteConfigDataStruBuff[bufIndex].AcIdBuff[index];
			rtnValue = RETURN_SUCCESS;
		}
		else
		{
			rtnValue = RETURN_ERROR;
		}
	}
	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·�ڼ�������buff
* ����˵���� const UINT16 routeId, ��·ID   
*			 UINT8_S bufSize,��������С��
*            UINT16_S acIdBuff[],�������
* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
*			 RETURN_SUCCESS: ��ȡ�ɹ�      
*/
UINT8_S GetRoutOfAcIdBuff(const UINT16_S routeId,UINT8_S bufSize,UINT16_S acIdBuff[])
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if ((bufIndex < GetRouteSum())
		&& (bufSize >= ROUTE_OF_AC_SUM_MAX)
		&& (acIdBuff != NULL))
	{
		for (cycle = 0U; cycle < GetRouteOfAcNum(routeId); cycle++)
		{
			acIdBuff[cycle] = gRouteConfigDataStruBuff[bufIndex].AcIdBuff[cycle];
		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·���ϰ�������
* ����˵���� const UINT16 routeId, ��·ID     
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT16_S GetRouteOfObsNum(const UINT16_S routeId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT16_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if (bufIndex < GetRouteSum())
	{
		rtnValue = gRouteConfigDataStruBuff[bufIndex].ObsNum;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ��ID��·���ϰ�����Ϣ
* ����˵���� const UINT16 routeId, ��·ID   
*            const UINT8_S bufSize,�����С
*            RouteObsStruct routeObsStruBuff[],�������
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȡ�ɹ�      
*/
UINT8_S GetRoutepObsStruBuff(const UINT16_S routeId,const UINT8_S bufSize,RouteObsStruct routeObsStruBuff[])
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S cycle = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

	if ((bufIndex < GetRouteSum())
		&& (bufSize >= ROUTE_OF_OBS_SUM_MAX)
		&& (routeObsStruBuff != NULL))
	{
		for (cycle = 0U; cycle < GetRouteOfObsNum(routeId); cycle++)
		{
			routeObsStruBuff[cycle].ObsId = gRouteConfigDataStruBuff[bufIndex].RouteObsStruBuff[cycle].ObsId;
			routeObsStruBuff[cycle].ObsType = gRouteConfigDataStruBuff[bufIndex].RouteObsStruBuff[cycle].ObsType;
		}
		rtnValue = RETURN_SUCCESS;
	}
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ��ȡָ����·���һ����������
* ����˵���� const UINT16 routeId, ��·ID   
*            UINT16_S *acId, ��������ID�������
* ����ֵ  �� 0: ��ȡʧ��
*			 1: ��ȡ�ɹ�
*/
UINT8_S GetRouteLastAcId(const UINT16_S routeId,UINT16_S *acId)
{
	UINT16_S bufIndex = 0U;     /*�����±�*/
	UINT8_S acNumOfRoute = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	bufIndex = GetRouteConfigBufIndex(routeId);  /*��ȡ�����±�*/

    if (NULL != acId)
    {
        if (bufIndex < GetRouteSum())
        {
            acNumOfRoute = gRouteConfigDataStruBuff[bufIndex].AcNum;

            if (ROUTE_OF_AC_SUM_MAX >= acNumOfRoute)
            {
                (*acId) = gRouteConfigDataStruBuff[bufIndex].AcIdBuff[acNumOfRoute - 1U];
                rtnValue = RETURN_SUCCESS;
            } 
            else
            {
                (*acId) = 0U;
                rtnValue = RETURN_ERROR;
            }
        }
        else
        {
            (*acId) = 0U;
            rtnValue = RETURN_ERROR;
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
	
	return rtnValue;
}
