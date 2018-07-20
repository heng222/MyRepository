/************************************************************************
*
* �ļ���   ��  ACInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �������εĳ�ʼ��
* ��  ע   ��  ��
*
************************************************************************/

#include "ACInitManager.h"
#include "ACConfigData.h"
#include "ACStatusData.h"
#include "../Change/ChangeConfigData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Common/MemSet.h"

extern AcConfigDataStruct gAcConfigDataStruBuff[LOCAL_AC_SUM_MAX];    /*���ñ�ZC�����������ýṹ��*/
extern UINT16_S gLocalAcIndexBuff[AC_SUM_MAX];		                 /*���ñ�ZC�����±�����*/
extern UINT16_S gAcCurSum;								     	     /*���ñ�ZC���ᵱǰ����*/
extern AcStatusDataStruct gAcStatusDataStruBuff[LOCAL_AC_SUM_MAX];    /*���ñ�ZC��������״̬�ṹ��*/

/*
* ���������� ��ʼ�����ع���ļ������γ�ʼ��Ϣ
* ����˵���� ��   
* ����ֵ  �� ��      
*/
void InitAcInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gAcCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < AC_SUM_MAX;cycle++)
	{
		gLocalAcIndexBuff[cycle] = AC_SUM_MAX;
	}

	/*״̬��ȫ̬����*/
	for (cycle = DEFAULT_ZERO;cycle < LOCAL_AC_SUM_MAX;cycle++)
	{
		gAcStatusDataStruBuff[cycle].AcUtFlag = AC_UT_OCC_STATUS;

		gAcStatusDataStruBuff[cycle].AcBelock = AC_UNLOCK_STATUS;

		gAcStatusDataStruBuff[cycle].AcStatusNow = AC_OCC_STATUS;
	}
}

/*
* ���������� ��ʼ�����ع���ļ���������Ϣ
* ����˵���� ��   
* ����ֵ  �� 0: ��ʼ��ʧ��
*			>0: ��ʼ���ɹ�      
*/
UINT8_S InitACLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineAcMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT8_S  switchNum = DEFAULT_ZERO;      
	UINT16_S switchInfoBuff[AC_SWITCH_SUM_MAX * 2U] = {0U};
	UINT8_S  logicSectionNum = DEFAULT_ZERO;                            
	UINT16_S logicSectionIdBuff[SIZE_MAX_SECTIONNUM] = {0U};
	UINT8_S cycleSwitch = DEFAULT_ZERO;
	UINT8_S cycleLogicSection = DEFAULT_ZERO;
	UINT8_S indexOfSwtich = DEFAULT_ZERO;
	UINT8_S errorFlag = DEFAULT_ZERO;

	/*��ʼ��*/
	InitAcInitializationData();
	MemorySet(&switchInfoBuff[0],((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)),
              0U,((UINT32_S)(SIZE_UINT16 * AC_SWITCH_SUM_MAX)));
	MemorySet(&logicSectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTIONNUM)),
              0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTIONNUM)));

	lineAcMaxId = GetLineAcMaxId();

	if (AC_SUM_MAX >= lineAcMaxId)
	{
		for (cycle = 1U; cycle <= lineAcMaxId;cycle++)
		{
			/*�жϸ�Id�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_AC);

			/*�жϸ�Id�Ƿ����ڱ�ZC*/
			belongZcId = GetLineAcBelongZcId(cycle);

			if ((belongZcId == GetLocalZcId()) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gAcConfigDataStruBuff[addIndex].AcId = cycle;
				gAcConfigDataStruBuff[addIndex].BelongZcId = belongZcId;
				gAcConfigDataStruBuff[addIndex].BelongCiId = GetLineAcBelongCiId(cycle);

				if (belongZcId == GetLocalZcId())
				{
					gAcConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gAcConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*��ȡ������������*/
				gAcConfigDataStruBuff[addIndex].AcType = GetLineAcType(cycle);

				/*��ʼ����ѯ��Ϣ*/
				MemorySet(switchInfoBuff,((UINT32_S)(sizeof(UINT16_S)*AC_SWITCH_SUM_MAX*2U)),
                          0U,((UINT32_S)(sizeof(UINT16_S)*AC_SWITCH_SUM_MAX*2U)));
				indexOfSwtich = DEFAULT_ZERO;

				if (RETURN_SUCCESS == GetLineAcIncludeSwitchInfo(cycle,&switchNum,switchInfoBuff))
				{
					gAcConfigDataStruBuff[addIndex].SwitchNum = switchNum;			

					for (cycleSwitch = DEFAULT_ZERO;cycleSwitch < switchNum;cycleSwitch++)
					{
						gAcConfigDataStruBuff[addIndex].SwitchInAcStru[cycleSwitch].SwitchId = switchInfoBuff[indexOfSwtich];
                        indexOfSwtich = indexOfSwtich + 1U;

						gAcConfigDataStruBuff[addIndex].SwitchInAcStru[cycleSwitch].SwitchPostion = (UINT8_S)switchInfoBuff[indexOfSwtich];
                        indexOfSwtich = indexOfSwtich + 1U;
					}
				} 
				else
				{
					errorFlag = FLAG_SET;
					break;
				}

				/*��ʼ����ѯ��Ϣ*/
				MemorySet(logicSectionIdBuff,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_SECTIONNUM)),
                          0U,((UINT32_S)(sizeof(UINT16_S)*SIZE_MAX_SECTIONNUM)));
				logicSectionNum = DEFAULT_ZERO;

				if (RETURN_SUCCESS == GetLineAcIncludeLogicSectionInfo(cycle,&logicSectionNum,logicSectionIdBuff))
				{
					gAcConfigDataStruBuff[addIndex].LogicSectionNum = logicSectionNum;

					for (cycleLogicSection = DEFAULT_ZERO;cycleLogicSection < logicSectionNum;cycleLogicSection++)
					{
						gAcConfigDataStruBuff[addIndex].LogicSectionIdBuff[cycleLogicSection] = logicSectionIdBuff[cycleLogicSection];
					}
				} 
				else
				{
					errorFlag = FLAG_SET;
					break;
				}

				/*����IDӳ������*/
				gLocalAcIndexBuff[cycle] = addIndex;

				/*��д״̬��Ӧ��ID��Ϣ*/
				gAcStatusDataStruBuff[addIndex].AcId = cycle;

				gAcCurSum++;
				addIndex++;
			} 
			else
			{
				/*�����ڱ�ZC��Ͻ��Χ�����л������ڵ��ϰ���*/
			}
		}

		if (FLAG_SET == errorFlag)
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
