/************************************************************************
*
* �ļ���   ��  LogicSectionInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �߼����γ�ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#include "LogicSectionConfigData.h"
#include "LogicSectionStatusData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../Change/ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "LogicSectionInitManager.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern LogicSectionConfigDataStruct gLogicSectionConfigDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];          /*���ñ��ع�����߼�����������Ϣ*/
extern UINT16_S gLogicSectionIdBuff[LOGIC_SECTION_SUM_MAX];                                         /*���ö����߼�����ӳ������*/
extern UINT16_S gLogicSectionCurSum;   
extern LogicSectionStruct gLogicSectionDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];                   /*���ö��屾�ع�����߼�����״̬��������*/

/*
* ���������� ��ʼ�����ع�����߼����γ�ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitLogicSectionInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gLogicSectionCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < LOGIC_SECTION_SUM_MAX;cycle++)
	{
		gLogicSectionIdBuff[cycle] = LOGIC_SECTION_SUM_MAX;
	}

	/*״̬��ȫ�ദ��*/
	for (cycle = DEFAULT_ZERO;cycle < LOGIC_SECTION_LOCAL_SUM_MAX;cycle++)
	{
		gLogicSectionDataStruBuff[cycle].LogicSectionOccStatus = LOGIC_SECTION_STATE_UT;
	}
}

/*
* ���������� ��ʼ�����ع�����߼�������Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitLogicSectionLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineLogicSectionMaxId = DEFAULT_ZERO;
	UINT16_S belongAcId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S breakFlag = DEFAULT_ZERO;
    UINT16_S localZcId =DEFAULT_ZERO;

	/*��ʼ������*/
	InitLogicSectionInitializationData();

	lineLogicSectionMaxId = GetLineLogicSectionMaxId();

	if (LOGIC_SECTION_SUM_MAX >= lineLogicSectionMaxId)
	{
		for (cycle = 1U; cycle <= lineLogicSectionMaxId;cycle++)
		{
			/*�жϸ�Id�Ƿ����ڱ�ZC*/
			belongAcId = GetLineLogicSectionBelongAcId(cycle);
			belongZcId = GetLineLogicSectionBelongZcId(cycle);

			if ((DEFAULT_ZERO != belongAcId) || (DEFAULT_ZERO != belongZcId))
			{
				/*�жϸ�acId�Ƿ������л�����*/
				rtnOfChangeArea = GetAppointObsInChangeArea(belongAcId,OBS_TYPE_AC);
                localZcId = GetLocalZcId();

				if ((belongZcId == localZcId) || (RETURN_SUCCESS == rtnOfChangeArea))
				{
					if (addIndex < LOGIC_SECTION_LOCAL_SUM_MAX)
					{
						gLogicSectionConfigDataStruBuff[addIndex].LogicSectionId = cycle;
						gLogicSectionConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
						gLogicSectionConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineLogicSectionBelongCiId(cycle));
						gLogicSectionConfigDataStruBuff[addIndex].BelongAcId = belongAcId;

						/*����IDӳ������*/
						gLogicSectionIdBuff[cycle] = addIndex;

						/*��д״̬��Ӧ��ID��Ϣ*/
						gLogicSectionDataStruBuff[addIndex].LogicSectionId = cycle;

						gLogicSectionCurSum++;
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
			else
			{			
				breakFlag = FLAG_SET;
				break;
			}
			
		}

		if (FLAG_SET == breakFlag)
		{           
            rtnValue = RETURN_ERROR;
		} 
		else
		{
			rtnValue = RETURN_SUCCESS;
    	}		
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}
	
	return rtnValue;
}
