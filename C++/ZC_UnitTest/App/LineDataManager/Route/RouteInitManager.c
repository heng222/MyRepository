/************************************************************************
*
* �ļ���   ��  RouteInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��·��ʼ������
* ��  ע   ��  ��
*
************************************************************************/

#include "RouteConfigData.h"
#include "RouteInitManager.h"
#include "RouteStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/RouteData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern RouteConfigDataStruct gRouteConfigDataStruBuff[ROUTE_LOCAL_SUM_MAX];          /*���ñ��ع���Ľ�·������Ϣ*/
extern UINT16_S gRouteIdBuff[ROUTE_SUM_MAX];                                        /*���ý�·ӳ������*/
extern UINT16_S gRouteCurSum;                                                      /*���ý�·��ǰ����*/
extern RouteDataStruct gRouteStatusDataStruBuff[ROUTE_LOCAL_SUM_MAX];                /*���ñ��ع���Ľ�·״̬��Ϣ*/

/*
* ���������� ��ʼ�����ع���Ľ�·��ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitRouteInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gRouteCurSum = DEFAULT_ZERO;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < ROUTE_SUM_MAX;cycle++)
	{
		gRouteIdBuff[cycle] = ROUTE_SUM_MAX;
	}

	/*״̬��ȫ�ദ��*/
	for (cycle = DEFAULT_ZERO;cycle < ROUTE_LOCAL_SUM_MAX;cycle++)
	{
		gRouteStatusDataStruBuff[cycle].RouteStatus = ROUTE_STATE_UNSET;
	}
}

/*
* ���������� ��ʼ�����ع���Ľ�·��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitRouteLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineRouteMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S acNumOfRoute = DEFAULT_ZERO;
	UINT8_S obsNumOfRoute = DEFAULT_ZERO;
	UINT16_S acIdBuff[ROUTE_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
	UINT16_S obsIdBuff[ROUTE_OF_OBS_SUM_MAX * 2U] = {DEFAULT_ZERO};
	UINT8_S cycleOfAc = DEFAULT_ZERO;
	UINT8_S cycleOfObs = DEFAULT_ZERO;
	UINT8_S index = DEFAULT_ZERO;
	UINT8_S overlapNum = DEFAULT_ZERO;
	UINT8_S cycleOfOverlap = DEFAULT_ZERO;
	UINT16_S overlapIdBuff[ROUTE_OF_OVERLAP_SUM_MAX] = {DEFAULT_ZERO};
    UINT16_S localZcId = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;

	/*��ʼ������*/
	MemorySet(&acIdBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_AC_SUM_MAX)));
	MemorySet(&obsIdBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OBS_SUM_MAX*2U)),
                 0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OBS_SUM_MAX*2U)));
	MemorySet(&overlapIdBuff[0],((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OVERLAP_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * ROUTE_OF_OVERLAP_SUM_MAX)));

	InitRouteInitializationData();

	lineRouteMaxId = GetLineRouteMaxId();

	if (ROUTE_SUM_MAX >= lineRouteMaxId)
	{
		for (cycle = 1U; cycle <= lineRouteMaxId;cycle++)
		{
			/*�жϸ�Id�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_ROUTE);

			/*�жϸ�Id�Ƿ����ڱ�ZC*/
			belongZcId = GetLineRouteBelongZcId(cycle);
            localZcId = GetLocalZcId();
                 
			if ((belongZcId == localZcId) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				if (addIndex < ROUTE_LOCAL_SUM_MAX)
				{
					gRouteConfigDataStruBuff[addIndex].RouteId = cycle;
					gRouteConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)belongZcId;
					gRouteConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)GetRouteDataStrumanageCI(cycle);
					gRouteConfigDataStruBuff[addIndex].RouteSingalId = (UINT8_S)(GetRouteDataStrustartSignalId(cycle));

					if (belongZcId == GetLocalZcId())
					{
						gRouteConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
					}
					else
					{
						gRouteConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
					}

					gRouteConfigDataStruBuff[addIndex].RouteType = (UINT8_S)GetRouteDataStrurouteType(cycle);
					gRouteConfigDataStruBuff[addIndex].RouteAreaType = GetLineRouteAreaType(cycle);

					/*��ȡ��·�����ı���������Ϣ*/
					overlapNum = (UINT8_S)(GetLineRouteOfOverlapInfo(cycle, overlapIdBuff));

					if ((overlapNum > 0U) && (overlapNum <= ROUTE_OF_OVERLAP_SUM_MAX))
					{
						gRouteConfigDataStruBuff[addIndex].OverlapNum = overlapNum;

						for (cycleOfOverlap = DEFAULT_ZERO; cycleOfOverlap < overlapNum; cycleOfOverlap++)
						{
							gRouteConfigDataStruBuff[addIndex].OverlapIdBuff[cycleOfOverlap] = overlapIdBuff[cycleOfOverlap];
						}
					}
					else
					{
						/*������*/
					}

					/*��ȡ��·�����ļ���������Ϣ*/
					acNumOfRoute = (UINT8_S)(GetLineRouteOfAcInfo(cycle, acIdBuff));

					if ((acNumOfRoute > 0U) && (acNumOfRoute <= ROUTE_OF_AC_SUM_MAX))
					{
						gRouteConfigDataStruBuff[addIndex].AcNum = acNumOfRoute;

						for (cycleOfAc = DEFAULT_ZERO; cycleOfAc < acNumOfRoute; cycleOfAc++)
						{
							gRouteConfigDataStruBuff[addIndex].AcIdBuff[cycleOfAc] = acIdBuff[cycleOfAc];
						}
					}
					else
					{
						/*������*/
					}

					/*��ȡ��·�������ϰ�����Ϣ*/
					obsNumOfRoute = (UINT8_S)(GetLineRouteOfObsInfo(cycle, obsIdBuff));

					/*��ʼ��*/
					index = DEFAULT_ZERO;

					if ((obsNumOfRoute > 0U) && (obsNumOfRoute <= ROUTE_OF_OBS_SUM_MAX))
					{
						gRouteConfigDataStruBuff[addIndex].ObsNum = obsNumOfRoute;

						for (cycleOfObs = DEFAULT_ZERO; cycleOfObs < obsNumOfRoute; cycleOfObs++)
						{
							gRouteConfigDataStruBuff[addIndex].RouteObsStruBuff[cycleOfObs].ObsId = obsIdBuff[index];
							index = index + 1U;

							gRouteConfigDataStruBuff[addIndex].RouteObsStruBuff[cycleOfObs].ObsType = (UINT8_S)obsIdBuff[index];
							index = index + 1U;
						}
					}
					else
					{
						/*������*/
					}

					/*����IDӳ������*/
					gRouteIdBuff[cycle] = addIndex;

					/*��д״̬��Ӧ��ID��Ϣ*/
					gRouteStatusDataStruBuff[addIndex].RouteId = cycle;

					gRouteCurSum++;
					addIndex++;
				}
				else
				{
					breakFlag = FLAG_SET;
					break;
				}
			} 
			else
			{
				/*�����ڱ�ZC��Ͻ��Χ�����л������ڵ��ϰ���*/
			}
		}

		rtnValue = RETURN_SUCCESS;
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}
	
	if (FLAG_SET == breakFlag)
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
