/************************************************************************
*
* �ļ���   ��  SwitchInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#include "SwitchConfigData.h"
#include "SwitchInitManager.h"
#include "SwitchStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/SwitchData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern SwitchConfigDataStruct gSwitchConfigDataStruBuff[SWITCH_LOCAL_SUM_MAX];             /*���ñ��ع���ĵ�����Ϣ*/
extern UINT16_S gSwitchIdBuff[SWITCH_SUM_MAX];                                      /*���õ���ӳ������*/
extern UINT16_S gSwitchCurSum;                                                       /*���õ���ǰ����*/
extern SwitchDataStruct gSwitchStatusDataStruBuff[SWITCH_LOCAL_SUM_MAX];                         /*���ñ��ع���ĵ���״̬��Ϣ*/

/*
* ���������� ��ʼ�����ع���ĵ����ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitSwitchInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gSwitchCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < SWITCH_SUM_MAX;cycle++)
	{
		gSwitchIdBuff[cycle] = SWITCH_SUM_MAX;
	}

	/*״̬��ȫ�ദ��*/
	for (cycle = DEFAULT_ZERO;cycle < SWITCH_LOCAL_SUM_MAX;cycle++)
	{
		gSwitchStatusDataStruBuff[cycle].SwitchLock = SWITCH_STATE_UNLOCK;

		gSwitchStatusDataStruBuff[cycle].SwitchPosStatus = SWITCH_STATE_LOSE;
	}
}

/*
* ���������� ��ʼ�����ع���ĵ�����Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitSwitchLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineSwitchMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ʼ������*/
	InitSwitchInitializationData();

	lineSwitchMaxId = GetLineSwitchMaxId();

	if (SWITCH_SUM_MAX >= lineSwitchMaxId)
	{
		for (cycle = 1U; cycle <= lineSwitchMaxId;cycle++)
		{
			/*�жϸ�Id�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_POINT);

			/*�жϸ�Id�Ƿ����ڱ�ZC*/
			belongZcId = GetLineSwitchBelongZcId(cycle);

			if ((belongZcId == GetLocalZcId()) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gSwitchConfigDataStruBuff[addIndex].SwitchId = cycle;
				gSwitchConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gSwitchConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineSwitchBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gSwitchConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gSwitchConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}
				gSwitchConfigDataStruBuff[addIndex].SwitchPosition = GetLineSwitchPosition(cycle);


				/*����IDӳ������*/
				gSwitchIdBuff[cycle] = addIndex;

				/*��д״̬��Ӧ��ID��Ϣ*/
				gSwitchStatusDataStruBuff[addIndex].SwitchId = cycle;

				gSwitchCurSum++;
				addIndex++;
				
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
	
	return rtnValue;
}
