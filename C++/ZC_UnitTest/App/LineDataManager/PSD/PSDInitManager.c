/************************************************************************
*
* �ļ���   ��  PSDInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����ų�ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#include "PSDConfigData.h"
#include "PSDInitManager.h"
#include "PSDStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/ShieldDoorData.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern PsdConfigDataStruct gPsdConfigDataStruBuff[PSD_LOCAL_SUM_MAX];          /*���ñ��ع����������������Ϣ*/
extern UINT16_S gPsdIdBuff[PSD_SUM_MAX];                                      /*����������ӳ������*/
extern UINT16_S gPsdCurSum;                                                  /*���������ŵ�ǰ����*/
extern PsdDataStruct gPsdDataStruBuff[PSD_LOCAL_SUM_MAX];                      /*���ñ��ع����������״̬��Ϣ*/

/*
* ���������� ��ʼ�����ع���������ų�ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitPsdInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gPsdCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < PSD_SUM_MAX;cycle++)
	{
		gPsdIdBuff[cycle] = PSD_SUM_MAX;
	}

	/*״̬��ȫ�ദ��*/
	for (cycle = DEFAULT_ZERO;cycle < PSD_LOCAL_SUM_MAX;cycle++)
	{
		gPsdDataStruBuff[cycle].PsdStatus = PSD_STATE_OPEN;
	}
}

/*
* ���������� ��ʼ�����ع������������Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitPSDLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S linePsdMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;

	/*��ʼ������*/
	InitPsdInitializationData();

	linePsdMaxId = GetLinePsdMaxId();

	if (PSD_SUM_MAX >= linePsdMaxId)
	{
		for (cycle = 1U; cycle <= linePsdMaxId;cycle++)
		{
			/*�жϸ�Id�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_PSD);

			/*�жϸ�Id�Ƿ����ڱ�ZC*/
			belongZcId = GetLinePsdBelongZcId(cycle);
            localZcId = GetLocalZcId();

			if ((belongZcId == localZcId ) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gPsdConfigDataStruBuff[addIndex].PsdId = cycle;
				gPsdConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gPsdConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLinePsdBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gPsdConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gPsdConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*����IDӳ������*/
				gPsdIdBuff[cycle] = addIndex;

				/*��д״̬��Ӧ��ID��Ϣ*/
				gPsdDataStruBuff[addIndex].PsdId = cycle;

				gPsdCurSum++;
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
