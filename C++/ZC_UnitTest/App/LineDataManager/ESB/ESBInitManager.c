/************************************************************************
*
* �ļ���   ��  ESBInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ����ͣ����ť��ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#include "ESBConfigData.h"
#include "ESBInitManager.h"
#include "ESBStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/EmergStopButtonData.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern EsbConfigDataStruct gEsbConfigDataStruBuff[ESB_LOCAL_SUM_MAX];          /*���ñ��ع���Ľ���ͣ����ť������Ϣ*/
extern UINT16_S gEsbIdBuff[ESB_SUM_MAX];                                      /*���ý���ͣ����ťӳ������*/
extern UINT16_S gEsbCurSum;                                                  /*���ý���ͣ����ť��ǰ����*/
extern EsbDataStruct gEsbDataStruBuff[ESB_LOCAL_SUM_MAX];                      /*���ñ��ع���Ľ���ͣ����ť״̬��Ϣ*/

/*
* ���������� ��ʼ�����ع���Ľ���ͣ����ť��ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitEsbInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gEsbCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < ESB_SUM_MAX;cycle++)
	{
		gEsbIdBuff[cycle] = ESB_SUM_MAX;
	}

	/*״̬��ȫ�ദ��*/
	for (cycle = DEFAULT_ZERO;cycle < ESB_LOCAL_SUM_MAX;cycle++)
	{
		gEsbDataStruBuff[cycle].EsbStatus = ESB_STATE_DOWN;
	}
}

/*
* ���������� ��ʼ�����ع���Ľ���ͣ����ť��Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			 1: ��ʼ���ɹ�      
*/
UINT8_S InitESBLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineEsbMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;

	/*��ʼ������*/
	InitEsbInitializationData();

	lineEsbMaxId = GetLineEsbMaxId();

	if (ESB_SUM_MAX >= lineEsbMaxId)
	{
		for (cycle = 1U; cycle <= lineEsbMaxId;cycle++)
		{
			/*�жϸ�Id�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_ESB);

			/*�жϸ�Id�Ƿ����ڱ�ZC*/
			belongZcId = GetLineEsbBelongZcId(cycle);

			if ((belongZcId == GetLocalZcId()) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gEsbConfigDataStruBuff[addIndex].EsbId = cycle;
				gEsbConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gEsbConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineEsbBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gEsbConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gEsbConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*����IDӳ������*/
				gEsbIdBuff[cycle] = addIndex;

				/*��д״̬��Ӧ��ID��Ϣ*/
				gEsbDataStruBuff[addIndex].EsbId = cycle;

				gEsbCurSum++;
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
