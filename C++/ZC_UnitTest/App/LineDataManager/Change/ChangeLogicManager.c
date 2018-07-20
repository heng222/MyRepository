
/********************************************************                                                                                                           
 �� �� ���� ChangeLogicManager.c   
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015.04.18
 ������ �л������߼��������  
 ��ע�� ��  
********************************************************/ 

#include "ChangeConfigData.h"
#include "ChangeLogicManager.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../AC/ACConfigData.h"

/*************************************************
  ������:  JudgeACIsChangeEnd    
  ��������: ����������ID�Ƿ������л������ն˼���
  ����: const UINT16 acId ���ж�����
            const UINT8_S dir ���з���
  ���: ��
  ����ֵ: RETURN_ERROR ʧ��
             FLAG_SET  ����
			 FLAG_UNSET ������
*************************************************/
UINT8_S JudgeACIsChangeEnd(const UINT16_S acId,const UINT8_S dir)
{
	UINT16_S cycle = 0U;
	UINT16_S endLink = 0U;
	UINT32_S endOffset = 0U;
	UINT16_S endAcId = 0U;
	UINT8_S rtnValue = FLAG_UNSET;
	UINT16_S changeLineId = DEFAULT_ZERO;

	for (cycle = 0U;cycle < GetChangeLineSum();cycle++)
	{
		/*��ȡ�л���·ID*/
		changeLineId = GetChangeLineId(cycle);
		if (GetChangeLineDir(changeLineId) == dir)
		{
			endLink = GetChangeLineEndLink(changeLineId);
			endOffset = GetChangeLineEndOffset(changeLineId);

			endAcId = CheckPositionBelongAc(endLink);

			if (RETURN_ERROR != endAcId)
			{
				if (acId == endAcId)
				{
					rtnValue = FLAG_SET;
					break;
				}
				else
				{
					/*��������*/
				}
			}
			else
			{
				rtnValue = RETURN_ERROR;
				break;
			}
		} 
		else
		{
            /*������*/
		}
	}

	return rtnValue;
}

/*************************************************
  ������: JudgeAcIsInChangeLine     
  ��������: ����������ID�Ƿ�������ָ�������л�����
  ����: const UINT16 acId ���ж�����   
       const UINT8_S trainDir ����
  ���: ��
  ����ֵ: RETURN_SUCESS  ����
			 RETURN_ERROR ������
*************************************************/
UINT8_S JudgeAcIsInChangeLine(const UINT16_S acId,const UINT8_S trainDir)
{
    UINT16_S changeCycle = 0U;
    UINT16_S acNum = 0U;
    UINT8_S acCycle = 0U;
    UINT8_S rtnValue = 0U;
    ChangeBitTableStruct* pObsOfAcStru = NULL;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT8_S getAcRtn = DEFAULT_ZERO;
    UINT8_S acChangeDir = DEFAULT_ZERO; /* ����֧�ֵ��л����� */

    for (changeCycle = 0U;changeCycle < GetChangeAreaConfigSum();changeCycle++)
    {
        /*��ȡ������������*/
        getAcRtn = GetObsBitTableNumOfIndex((UINT8_S)changeCycle,OBS_TYPE_AC,&acNum);

        pObsOfAcStru = GetObsBitTableStrInfoOfIndex((UINT8_S)changeCycle,OBS_TYPE_AC);

        if ((NULL != pObsOfAcStru) &&(RETURN_SUCCESS == getAcRtn))
        {
            for (acCycle = 0U;acCycle < acNum;acCycle++)
            {
#if 0
                /*�жϼ����Ƿ�λ���л�����Χ��*/
                if (acId == pObsOfAcStru[acCycle].ObsId)
                {
                    rtnValue = RETURN_SUCCESS;
                    breakFlag = FLAG_SET;
                    break;
                }
                else
                {
                    /*��������*/
                }
#else
                acChangeDir = pObsOfAcStru[acCycle].ChageDir;
                /* �жϼ����Ƿ�λ���л�����Χ�ں�����֧�ֵ��л����� */
                if ((acId == pObsOfAcStru[acCycle].ObsId) 
                    && ((acChangeDir == trainDir) || (acChangeDir == AC_CHANGER_DIR_DOUBLE)))
                {
                    rtnValue = RETURN_SUCCESS;
                    breakFlag = FLAG_SET;
                    break;
                }
                else
                {
                    /*��������*/
                }
#endif
            }
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }

        if (FLAG_SET == breakFlag)
        {
            break;
        } 
        else
        {
            /*������*/
        }	
    }

    return rtnValue;
}


/*
* ���������� �����л������ڱ�ZC��Ͻ��Χ�ڵ��߼�������Ϣ
* ����˵���� UINT16_S *logicNum��
*            UINT16_S logicIdBuff[CHANGE_AREA_LOGIC_MAX]
* ����ֵ  �� 1,����ɹ�
*            2,����ʧ��
*/
UINT8_S CalculatChangeAreaLogicInfoOfZc(UINT16_S zcId,UINT16_S *logicNum,UINT16_S logicIdBuff[])
{
	UINT8_S rtn = RETURN_ERROR;
	ChangeBitTableStruct *tempChangeBitTableStr = NULL;
	UINT16_S pObsNum = DEFAULT_ZERO;
	UINT8_S checkObsNum = DEFAULT_ZERO;
	UINT16_S cycleObs = DEFAULT_ZERO;
	UINT16_S logicOfAcNum = DEFAULT_ZERO;
	UINT16_S logicOfAcIdBuff[SIZE_MAX_SECTIONNUM] = {DEFAULT_ZERO};
	UINT8_S checkLogicOfAcRtn = DEFAULT_ZERO;
	UINT16_S cycleLogic = DEFAULT_ZERO;

	/*��ȡ�л���·��Ϣ*/
	tempChangeBitTableStr = GetObsBitTableStrInfo(GetLocalZcId(), zcId, OBS_TYPE_AC);
	checkObsNum = GetObsBitTableNum(GetLocalZcId(), zcId, OBS_TYPE_AC, &pObsNum);

	(*logicNum) = DEFAULT_ZERO;

	if ((RETURN_ERROR != checkObsNum) && (NULL != tempChangeBitTableStr))
	{
		for (cycleObs = DEFAULT_ZERO; cycleObs < pObsNum;cycleObs++)
		{
			/*��ѯ�������ζ�Ӧ���߼�����ID*/
			logicOfAcNum = GetAcLogicSectionNum(tempChangeBitTableStr[cycleObs].ObsId);
			checkLogicOfAcRtn = GetAcLogicSectionIdBuf(tempChangeBitTableStr[cycleObs].ObsId,SIZE_MAX_SECTIONNUM,logicOfAcIdBuff);
			
			if (RETURN_SUCCESS == checkLogicOfAcRtn)
			{
				for (cycleLogic = DEFAULT_ZERO;cycleLogic < logicOfAcNum;cycleLogic++)
				{
					logicIdBuff[(*logicNum)] = logicOfAcIdBuff[cycleLogic];
					(*logicNum)++;
				}

				rtn = RETURN_SUCCESS;
			} 
			else
			{
				rtn = RETURN_ERROR;
				break;
			}
		}
	} 
	else
	{
		rtn = RETURN_ERROR;
	}

	return rtn;
}


