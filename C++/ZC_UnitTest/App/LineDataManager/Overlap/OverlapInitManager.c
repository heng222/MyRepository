
/********************************************************                                                                                                           
 �� �� ���� OverlapInitManager.c 
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015.04.18
 ������ �������γ�ʼ��  
 ��ע�� ��  
********************************************************/ 

#include "OverlapConfigData.h"
#include "OverlapInitManager.h"
#include "OverlapStatusData.h"
#include "../Change/ChangeConfigData.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../../Dmu/DmuComm/Data/ProtectZoneData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern OverlapConfigDataStruct gOverlapConfigDataStruBuff[OVERLAP_LOCAL_SUM_MAX];            /*���ñ��ع���ı�������������Ϣ*/
extern UINT16_S gOverlapIdBuff[OVERLAP_SUM_MAX];                                            /*���ñ�������ӳ������*/
extern UINT16_S gOverlapCurSum;                                                            /*���ñ������ε�ǰ����*/

extern OverlapDataStruct gOverlapDataStruBuff[OVERLAP_LOCAL_SUM_MAX];                        /*���ñ��ع���ı�������״̬��Ϣ*/

/*************************************************
  ������:    InitOverlapInitializationData  
  ��������: ��ʼ�����ع���ı������γ�ʼ��Ϣ
  ����: ��   
  ���: ��
  ����ֵ: ��      
*************************************************/
void InitOverlapInitializationData(void)
{
	UINT16_S cycle = DEFAULT_ZERO;

	gOverlapCurSum = 0U;

	/*��ʼ��ȫ�ֱ���*/
	for (cycle = DEFAULT_ZERO;cycle < OVERLAP_SUM_MAX;cycle++)
	{
		gOverlapIdBuff[cycle] = OVERLAP_SUM_MAX;
	}

	/*״̬��ȫ�ദ��*/
	for (cycle = DEFAULT_ZERO;cycle < OVERLAP_LOCAL_SUM_MAX;cycle++)
	{
		gOverlapDataStruBuff[cycle].OverlapStatus = OVERLAP_STATE_UNSET;
	}
}

/*************************************************
  ������:   InitOverlapLocalInfo   
  ��������: ��ʼ�����ع���ı���������Ϣ
  ����: ��   
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			>0: ��ʼ���ɹ�      
*************************************************/
UINT8_S InitOverlapLocalInfo(void)
{
	UINT16_S cycle = DEFAULT_ZERO;
	UINT16_S addIndex = DEFAULT_ZERO;
	UINT16_S lineOverlapMaxId = DEFAULT_ZERO;
	UINT16_S belongZcId = DEFAULT_ZERO;
	UINT8_S  rtnOfChangeArea = DEFAULT_ZERO;
	UINT8_S rtnValue = DEFAULT_ZERO;
	UINT16_S  acNumOfOverlap = DEFAULT_ZERO;
	UINT16_S acInfoOfOvaerlapBuff[OVERLAP_OF_AC_SUM_MAX] = {DEFAULT_ZERO};
	UINT16_S cycleOfAc = DEFAULT_ZERO;
	UINT16_S  overlapOfSwitchNum = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;

	MemorySet(&acInfoOfOvaerlapBuff[0],((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)),
                 0U,((UINT32_S)(SIZE_UINT16 * OVERLAP_OF_AC_SUM_MAX)));

	/*��ʼ������*/
	InitOverlapInitializationData();

	lineOverlapMaxId = GetLineOverlapMaxId();

	if (OVERLAP_SUM_MAX >= lineOverlapMaxId)
	{
		for (cycle = 1U; cycle <= lineOverlapMaxId;cycle++)
		{
			/*�жϸ�Id�Ƿ������л�����*/
			rtnOfChangeArea = GetAppointObsInChangeArea(cycle,OBS_TYPE_OVERLAP);

			/*�жϸ�Id�Ƿ����ڱ�ZC*/
			belongZcId = GetLineOverlapBelongZcId(cycle);
            localZcId = GetLocalZcId();

			if ((belongZcId == localZcId) || (RETURN_SUCCESS == rtnOfChangeArea))
			{
				gOverlapConfigDataStruBuff[addIndex].OverlapId = cycle;
				gOverlapConfigDataStruBuff[addIndex].BelongZcId = (UINT8_S)(belongZcId);
				gOverlapConfigDataStruBuff[addIndex].BelongCiId = (UINT8_S)(GetLineOverlapBelongCiId(cycle));

				if (belongZcId == GetLocalZcId())
				{
					gOverlapConfigDataStruBuff[addIndex].ChangeAttribute = DEFAULT_ZERO;
				} 
				else
				{
					gOverlapConfigDataStruBuff[addIndex].ChangeAttribute = FLAG_SET;
				}

				/*��ȡ�������ι����ļ���������Ϣ*/
				acNumOfOverlap = GetLineOverlapOfAcInfo(cycle,acInfoOfOvaerlapBuff);

				if ((acNumOfOverlap > 0U) && (acNumOfOverlap <= OVERLAP_OF_AC_SUM_MAX))
				{
					gOverlapConfigDataStruBuff[addIndex].ContainAcNum = (UINT8_S)(acNumOfOverlap);

					for (cycleOfAc = DEFAULT_ZERO;cycleOfAc < acNumOfOverlap;cycleOfAc++)
					{
						gOverlapConfigDataStruBuff[addIndex].ContainAcBuff[cycleOfAc] = acInfoOfOvaerlapBuff[cycleOfAc];
					}
				} 
				else
				{
                    /*������*/
				}

				/*�жϱ��������Ƿ��е���*/
				overlapOfSwitchNum = GetLineOverlapOfSwitchNum(cycle);

				if ((DEFAULT_ZERO < overlapOfSwitchNum)
					&& (DEFAULT_0XFF > overlapOfSwitchNum))
				{
					gOverlapConfigDataStruBuff[addIndex].SwitchAttribute = FLAG_SET;
				} 
				else
				{
                    /*������*/
				}

				/*����IDӳ������*/
				gOverlapIdBuff[cycle] = addIndex;

				/*��д״̬��Ӧ��ID��Ϣ*/
				gOverlapDataStruBuff[addIndex].OverlapId = cycle;

				gOverlapCurSum++;
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
