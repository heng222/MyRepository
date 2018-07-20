
/********************************************************                                                                                                           
 �� �� ���� ChangeInitManager.c   
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015.04.18
 ������ �л������ʼ������  
 ��ע�� ��  
********************************************************/ 

#include "ChangeConfigData.h"
#include "ChangeInitManager.h"
#include "../../SysDataManager/SysConfigData.h"
#include "../../DmuZc/DataHandle/DmuZcDataHandle.h"
#include "../../../Dmu/DmuComm/Data/LineSwitchInfoData.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../../Common/Convert.h"
#include "../../IOManager/CommTarget/CommTargetConfigData.h"
#include "../../../Common/Malloc.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern ChangeLineConfigDataStruct gChangeLineConfigDataStruBuff[CHANGE_LINE_LOCAL_SUM_MAX];     /*���ñ��ع�����л���·������Ϣ*/
extern UINT16_S  gChangeLineIdBuff[CHANGE_LINE_SUM_MAX];                                            /*���ö����л���·ӳ������*/
extern UINT16_S  gChangeLineCurSum;                                                                          /*�����л���·��ǰ����*/

extern ChangeAreaConfigStruct* gpChangeAreaConfigStruBuff;             /*���ñ��ع�����л�����������Ϣ*/
extern UINT16_S   gChangeAreaIdBuff[CHANGE_AREA_SUM_MAX];                                           /*���ö����л�����ӳ������*/
extern UINT16_S   gChangeAreaCurSum;                                                                         /*�����л�����ǰ����*/

/*************************************************
  ������:   InitChangeLineInitializationData   
  ��������: ��ʼ�����ع�����л���·��ʼ��Ϣ
  ����: ��   
  ���: ��
  ����ֵ: ��     
*************************************************/
void InitChangeLineInitializationData(void)
{
    UINT16_S cycle = DEFAULT_ZERO;

    for (cycle = DEFAULT_ZERO;cycle < CHANGE_LINE_SUM_MAX;cycle++)
    {
        gChangeLineIdBuff[cycle] = CHANGE_LINE_SUM_MAX;
    }
}

/*************************************************
  ������:  InitChangeInfo    
  ��������: ��ʼ���л���������
  ����: void 
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeInfo(void)
{
    UINT16_S initErrorFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*��ʼ���л���·����*/
    if (RETURN_SUCCESS == InitChangeLineInfo())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
    }

    /*��ʼ���л���������*/
    if (RETURN_SUCCESS == InitChangeAreaMaskInfo())
    {
        /*������*/
    }
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
    }

    if (DEFAULT_ZERO == initErrorFlag)
    {
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    LogPrintf(1U,"InitChangeInfo Error %d\n",initErrorFlag);
    return rtnValue;
}

/*************************************************
  ������:   InitChangeLineInfo   
  ��������: ��ʼ���л���·����
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeLineInfo(void)
{
    UINT16_S cLIdBuff[CHANGE_LINE_LOCAL_SUM_MAX] = {DEFAULT_ZERO};
    BnfSngSwitchInfoStruct *pSwitchInfoInChangeLineStru = NULL;
    UINT16_S switchNum = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S cycleSwitch = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;
	UINT16_S handOverZcId = DEFAULT_ZERO;
	UINT16_S takeOverZcId = DEFAULT_ZERO;
	UINT16_S localZcId = DEFAULT_ZERO;

    /*��ʼ��*/
    MemorySet(&cLIdBuff[0],((UINT32_S)(SIZE_UINT16 * CHANGE_LINE_LOCAL_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * CHANGE_LINE_LOCAL_SUM_MAX)));
    InitChangeLineInitializationData();

	localZcId = GetLocalZcId();

    /*��ȡ��ZC��Ӧ���л���·������*/
    gChangeLineCurSum = GetLocalZcChangeLineNum(GetLocalZcId(),cLIdBuff);

    if ((gChangeLineCurSum > DEFAULT_ZERO) && (gChangeLineCurSum <= CHANGE_LINE_LOCAL_SUM_MAX))
    {
        /*��ȡ���л���·����*/
        for (cycle = DEFAULT_ZERO;cycle < gChangeLineCurSum;cycle++)
        {
            if ((DEFAULT_ZERO < cLIdBuff[cycle]) && (CHANGE_LINE_SUM_MAX >= cLIdBuff[cycle]))
            {
				handOverZcId = GetLineSwitchInfoDataStrulineSwitchTraZcId(cLIdBuff[cycle]);
				takeOverZcId = GetLinSwInfDatliSwTakeOvZcId(cLIdBuff[cycle]);

                if ((handOverZcId == localZcId) || (takeOverZcId == localZcId))
                {
					/*��������*/
					gChangeLineIdBuff[cLIdBuff[cycle]] = cycle;

					/*���õ����ṹ��Ϣ*/
					gChangeLineConfigDataStruBuff[cycle].ChangeLineId = cLIdBuff[cycle];

					gChangeLineConfigDataStruBuff[cycle].HandOverZcId = handOverZcId;

					gChangeLineConfigDataStruBuff[cycle].TakeOverZcId = takeOverZcId;

					gChangeLineConfigDataStruBuff[cycle].ChangeDir = GetLineSwInfoDatalineSwDir(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangeLineStartLink = GetLineSwitchInfoDataStrustartLineSwitchInfoId(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangeLineStartOffset = GetLineSwitchInfoDataStrustartSegOffset(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangePointLink = GetLineSwitchInfoDataStruswitchPointSegId(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangePointOffset = GetLineSwInfoDataSwPointOff(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangeLineEndLink = GetLineSwitchInfoDataStruendLineSwitchInfoId(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].ChangeLineEndOffset = GetLineSwitchInfoDataStrusegEndOffset(cLIdBuff[cycle]);

					gChangeLineConfigDataStruBuff[cycle].RelevanceRouteId = GetLineSwitchInfoDataStrurelationRouteNum(cLIdBuff[cycle]);

					/*��ȡ�����л���·��Ӧ�ĵ���Ӧ��״̬*/
					switchNum = GetLineSwitchInfoDataStruincludeSwitchNum(cLIdBuff[cycle]);
					pSwitchInfoInChangeLineStru = GetLineSwInfDataSwInfStru(cLIdBuff[cycle]);

					if ((switchNum <= CHANGE_LINE_SWITCH_MAX)
						&& (NULL != pSwitchInfoInChangeLineStru))
					{
						gChangeLineConfigDataStruBuff[cycle].SwitchNum = (UINT8_S)switchNum;

						for(cycleSwitch = DEFAULT_ZERO;cycleSwitch < switchNum;cycleSwitch++)
						{
							gChangeLineConfigDataStruBuff[cycle].SwitchStruBuff[cycleSwitch].SwitchId = pSwitchInfoInChangeLineStru[cycleSwitch].switchId;
							gChangeLineConfigDataStruBuff[cycle].SwitchStruBuff[cycleSwitch].SwitchNeedStatus = (UINT8_S)pSwitchInfoInChangeLineStru[cycleSwitch].switchStatus;
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
					/* ������ */
                }
            } 
            else
            {
                rtnValue = RETURN_ERROR;
                break;
            }
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:   InitZcNZcMaskConfigCommTargetData   
  ��������: ��ʼ��ZC-NZC��λ������Ϣ����λ��Ϣ
  ����: ��   
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			>0: ��ʼ���ɹ�      
*************************************************/
UINT8_S InitZcNZcMaskConfigCommTargetData(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S commTargetId = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_SUCCESS;
    UINT8_S typeBuffIndex = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};

    MemorySet(&commTargetIdBuff[0],((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)),
        0U,((UINT32_S)(SIZE_UINT16 * SINGLE_TYPE_COMM_TARGET_SUM_MAX)));

    typeBuffIndex = GetCommTargetTypeBuffIndex(INNER_DEVTYPE_ZC);

    GetSingleCommTargetIdBuff(INNER_DEVTYPE_ZC,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

    for (cycle = DEFAULT_ZERO;cycle < GetSingleCommTargetTypeSum(INNER_DEVTYPE_ZC);cycle++)
    {
        commTargetId = commTargetIdBuff[cycle];

        if ((gChangeAreaCurSum <= COMM_ZC_SUM_MAX) 
            && (LINE_ZC_SUM_MAX > commTargetId))
        {
            /*��д��ZC�����Id��Ϣ*/
            gpChangeAreaConfigStruBuff[gChangeAreaCurSum].LocalZcId = GetLocalZcId();
            gpChangeAreaConfigStruBuff[gChangeAreaCurSum].NextZcId = commTargetId;
            gChangeAreaIdBuff[commTargetId] = gChangeAreaCurSum;

            gChangeAreaCurSum++;

            /*��д����ZC���뱾Zc��Id��Ϣ*/
            gpChangeAreaConfigStruBuff[gChangeAreaCurSum].LocalZcId = commTargetId;
            gpChangeAreaConfigStruBuff[gChangeAreaCurSum].NextZcId = GetLocalZcId();
            gChangeAreaIdBuff[commTargetId] = gChangeAreaCurSum;

            gChangeAreaCurSum++;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
            break;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:    InitChangeAreaMaskInfo  
  ��������: ��ʼ���л�������λ����
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
*			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaMaskInfo(void)
{
    UINT16_S initErrorFlag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    /*��ʼ��ͨ�Ź�ϵ*/
    if (RETURN_SUCCESS == InitZcNZcMaskConfigCommTargetData())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_1);
    }

    /*��ʼ��������Ϣ*/
    if (RETURN_SUCCESS == InitChangeAreaOfSwitchMask())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_2);
    }

    /*��ʼ�źŻ���Ϣ*/
    if (RETURN_SUCCESS == InitChangeAreaOfSignalMask())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_3);
    }

    /*��ʼ����������Ϣ*/
    if (RETURN_SUCCESS == InitChangeAreaOfPsdMask())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_4);
    }

    /*��ʼ������ͣ����ť��Ϣ*/
    if (RETURN_SUCCESS == InitChangeAreaOfEsbMask())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_5);
    }

    /*��ʼ������������Ϣ*/
    if (RETURN_SUCCESS == InitChangeAreaOfAcMask())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_6);
    }

    /*��ʼ����·��Ϣ*/
    if (RETURN_SUCCESS == InitChangeAreaOfRouteMask())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_7);
    }

    /*��ʼ������������Ϣ*/
    if (RETURN_SUCCESS == InitChangeAreaOfOverlapMask())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_8);
    }

    /*��ʼ�������۷���Ϣ*/
    if (RETURN_SUCCESS == InitChangeAreaOfDrMask())
    {
        /*������*/
    } 
    else
    {
        initErrorFlag = (UINT16_S)(initErrorFlag | ZC_ERROR_CODE_9);
    }

    if (DEFAULT_ZERO == initErrorFlag)
    {
        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue =  RETURN_ERROR;
    }

    LogPrintf(1U,"InitChangeAreaMaskInfo Error %d\n",initErrorFlag);
    return rtnValue;
}

/*************************************************
  ������:   InitChangeAreaOfSwitchMask   
  ��������: ��ʼ���л�������λ����(��������)
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfSwitchMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* �����ļ��е�ZC�ı�� */

    /*��ȡ�ļ��еĵ�����Ϣ�ܺ�*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_SWITCHCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*�����ڴ��С*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_SWITCH_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*��ѯ�ɹ�*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_SWITCH_MASK_SUM)
            {
                /*��������*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*���������ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*����ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���״̬��λ*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���������λ*/
                obsLockMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (obsLockMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchNum;

                        if (obsNum < CHANGE_AREA_SWITCH_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SwitchNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*�ñ�������*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:  InitChangeAreaOfSignalMask    
  ��������: ��ʼ���л�������λ����(�źŻ�����)
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
*			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfSignalMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* �����ļ��е�ZC�ı�� */

    /*��ȡ�ļ��е��źŻ���Ϣ�ܺ�*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_SIGNCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*����ռ�*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_SIGNAL_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*��ѯ�ɹ�*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_SIGNAL_MASK_SUM)
            {
                /*��������*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*���������ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*����ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���״̬��λ*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId(); 

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalNum;

                        if (obsNum < CHANGE_AREA_SIGNAL_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].SignalNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*�ñ�������*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:   InitChangeAreaOfPsdMask   
  ��������: ��ʼ���л�������λ����(����������)
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfPsdMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* �����ļ��е�ZC�ı�� */

    /*��ȡ�ļ��е���������Ϣ�ܺ�*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_PSDCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*����ռ�*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_PSD_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*��ѯ�ɹ�*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_PSD_MASK_SUM)
            {
                /*��������*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*���������ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*����ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���״̬��λ*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdNum;

                        if (obsNum < CHANGE_AREA_PSD_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].PsdNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*�ñ�������*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:    InitChangeAreaOfEsbMask  
  ��������: ��ʼ���л�������λ����(����ͣ����ť����)
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfEsbMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* �����ļ��е�ZC�ı�� */

    /*��ȡ�ļ��еĽ���ͣ����ť��Ϣ�ܺ�*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_ESBCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*����ռ�*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_ESB_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*��ѯ�ɹ�*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_ESB_MASK_SUM)
            {
                /*��������*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*���������ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*����ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���״̬��λ*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbNum;

                        if (obsNum < CHANGE_AREA_ESB_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].EsbNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*�ñ�������*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:   InitChangeAreaOfAcMask   
  ��������: ��ʼ���л�������λ����(������������)
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfAcMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* �����ļ��е�ZC�ı�� */
    UINT8_S chageDir = DEFAULT_ZERO;  /* �����ο����л��ķ��� */

    /*��ȡ�ļ��еļ���������Ϣ�ܺ�*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_AXLESECCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*����ռ�*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_AC_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*��ѯ�ɹ�*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_AC_MASK_SUM)
            {
                /*��������*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*���������ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*����ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���״̬��λ*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /* ���ο����л��ķ��� */
                chageDir= *pMaskData;
                pMaskData += 1U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcNum;

                        if (obsNum < CHANGE_AREA_AC_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            /* 2017.8.1 ������;0x55:����;0xaa:����;0xcc:������;0x00:������ */
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcBitStruBuff[obsNum].ChageDir = chageDir;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].AcNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*�ñ�������*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:   InitChangeAreaOfRouteMask   
  ��������: ��ʼ���л�������λ����(��·����)
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfRouteMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* �����ļ��е�ZC�ı�� */

    /*��ȡ�ļ��еĽ�·��Ϣ�ܺ�*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_ROUTECODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*����ռ�*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_ROUTE_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*��ѯ�ɹ�*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_ROUTE_MASK_SUM)
            {
                /*��������*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*���������ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*����ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���״̬��λ*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteNum;

                        if (obsNum < CHANGE_AREA_ROUTE_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].RouteNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*�ñ�������*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:   InitChangeAreaOfOverlapMask   
  ��������: ��ʼ���л�������λ����(������������)
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfOverlapMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* �����ļ��е�ZC�ı�� */

    /*��ȡ�ļ��еı���������Ϣ�ܺ�*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_PROSECCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*����ռ�*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_OVERLAP_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*��ѯ�ɹ�*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_OVERLAP_MASK_SUM)
            {
                /*��������*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*���������ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*����ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���״̬��λ*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapNum;

                        if (obsNum < CHANGE_AREA_OVERLAP_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapBitStruBuff[obsNum].LockBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].OverlapNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
        } 
        else
        {
            /*�ñ�������*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}

/*************************************************
  ������:  InitChangeAreaOfDrMask    
  ��������: ��ʼ���л�������λ����(�����۷�����)
  ����: void  
  ���: ��
  ����ֵ: 0: ��ʼ��ʧ��
			 1; ��ʼ���ɹ�
*************************************************/
UINT8_S InitChangeAreaOfDrMask(void)
{
    UINT32_S maskDataLen = DEFAULT_ZERO;
    UINT8_S indexId = DEFAULT_ZERO;
    UINT8_S *pMaskData = NULL;
    INT8_S tempRtnLen = 0;
    INT8_S tempRtnData = 0;
    UINT16_S obsId = DEFAULT_ZERO;
    UINT16_S nextZcId = DEFAULT_ZERO;
    UINT16_S obsStateMaskId = DEFAULT_ZERO;
    UINT16_S obsLockMaskId = DEFAULT_ZERO;
    UINT16_S changeAreaIndexOfZc = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    UINT8_S rtnValue = RETURN_ERROR;
    UINT16_S cycleMaskData = DEFAULT_ZERO;
    UINT16_S localZcId = DEFAULT_ZERO;
    UINT8_S configFlag = RETURN_ERROR;
    UINT16_S configedZcId = DEFAULT_ZERO;  /* �����ļ��е�ZC�ı�� */

    /*��ȡ�ļ��е������۷���Ϣ�ܺ�*/
    tempRtnLen = GetConfigDataLen(((UINT8_S)(ZC_NZC_INTERCODE_TYPE)),((UINT8_S)(ZC_NZC_ARCODE_TYPE)),&maskDataLen,&indexId);

    if ((0 == tempRtnLen)
        && (0U < maskDataLen))
    {
        /*����ռ�*/
        pMaskData = (UINT8_S*)MemoryMalloc(sizeof(UINT8_S)*(maskDataLen+50U));
        tempRtnData = GetConfigData(((UINT16_S)(ZC_NZC_DR_MASK_SUM)),maskDataLen,indexId,pMaskData);

        /*��ѯ�ɹ�*/
        if (0 == tempRtnData)
        {
            for (cycleMaskData = DEFAULT_ZERO;cycleMaskData < maskDataLen;cycleMaskData += ZC_NZC_DR_MASK_SUM)
            {
                /*��������*/
                obsId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*���������ZCID*/
                localZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*����ZCId*/
                nextZcId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ���״̬��λ*/
                obsStateMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                /*�ϰ�������״̬��λ*/
                obsLockMaskId = ShortFromChar(pMaskData);
                pMaskData += 2U;

                configFlag = GetCommTargetIdInConfigData(INNER_DEVTYPE_ZC,nextZcId);
                configedZcId = GetLocalZcId();

                if ((RETURN_SUCCESS == configFlag)
                    || (nextZcId == configedZcId))
                {
                    changeAreaIndexOfZc = GetChangeAreaConfigBufIndex(localZcId,nextZcId);

                    if ((obsStateMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (obsLockMaskId < ZC_NZC_MASK_NUM_MAX)
                        && (changeAreaIndexOfZc < CHANGE_AREA_SUM_MAX))
                    {
                        /*���������۷���վ̨*/
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrLampNum;

                        if (obsNum < CHANGE_AREA_DRLAMP_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrLampBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrLampBitStruBuff[obsNum].StateBitIndex = obsStateMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrLampNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
                        }

                        /*���������۷���ťվ̨*/
                        obsNum = gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrButtonNum;

                        if (obsNum < CHANGE_AREA_DRBUTTON_MAX)
                        {
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrButtonBitStruBuff[obsNum].ObsId = obsId;
                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrButtonBitStruBuff[obsNum].StateBitIndex = obsLockMaskId;

                            gpChangeAreaConfigStruBuff[changeAreaIndexOfZc].DrButtonNum++;
                        } 
                        else
                        {
                            rtnValue = RETURN_ERROR;
                            break;
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
                    /*Do nothing currently !*/
                }
            }
        } 
        else
        {
            /*�ñ�������*/
        }

        if (cycleMaskData == maskDataLen)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            /*������*/
        }
    } 
    else
    {
        if (0 != tempRtnLen)
        {
            rtnValue = RETURN_ERROR;
        } 
        else
        {
            rtnValue = RETURN_SUCCESS;
        }
    }

    return rtnValue;
}
