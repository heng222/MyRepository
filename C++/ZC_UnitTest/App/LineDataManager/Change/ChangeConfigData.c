
/********************************************************                                                                                                           
 �� �� ���� ChangeConfigData.c   
 ��    �ߣ� ZC��
 ����ʱ�䣺 2015.04.18
 ������ �л�������������  
 ��ע�� ��  
********************************************************/ 

#include "ChangeConfigData.h"
#include "../../../Dmu/DmuComm/Data/SwitchData.h"
#include "../../../Dmu/DmuComm/Data/SignData.h"
#include "../../../Dmu/DmuComm/Data/ShieldDoorData.h"
#include "../../../Dmu/DmuComm/Data/EmergStopButtonData.h"
#include "../../../Dmu/DmuComm/Data/AxleSectionData.h"
#include "../../../Dmu/DmuComm/Data/LogicSectionData.h"
#include "../../../Dmu/DmuComm/Data/RouteData.h"
#include "../../../Dmu/DmuComm/Data/ProtectZoneData.h"
#include "../../../Dmu/DmuComm/Data/ArData.h"
#include "../../../Dmu/Read/ReadManage.h"
#include "../../IOManager/CommTarget/CommTargetConfigData.h"
#include "../../SysDataManager/SysConfigData.h"

ChangeLineConfigDataStruct gChangeLineConfigDataStruBuff[CHANGE_LINE_LOCAL_SUM_MAX];     /*���ع�����л���·������Ϣ*/
UINT16_S  gChangeLineIdBuff[CHANGE_LINE_SUM_MAX] = {CHANGE_AREA_SUM_MAX};          /*�����л���·ӳ������*/
UINT16_S  gChangeLineCurSum = 0U;                                                                      /*�л���·��ǰ����*/

ChangeAreaConfigStruct* gpChangeAreaConfigStruBuff = NULL;             /*���ع�����л�����������Ϣ*/
UINT16_S   gChangeAreaIdBuff[CHANGE_AREA_SUM_MAX] = {CHANGE_AREA_SUM_MAX};         /*�����л�����ӳ������*/
UINT16_S   gChangeAreaCurSum = 0U;                                                                     /*�л�����ǰ����*/

/*************************************************
  ������:  GetChangeLineSum    
  ��������: ��ȡ�л���·����
  ����: void    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �л���·��ǰ����
*************************************************/
UINT16_S GetChangeLineSum(void)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (gChangeLineCurSum >= CHANGE_LINE_LOCAL_SUM_MAX)
    {
        rtnValue = 0U;
    } 
    else
    {
        rtnValue = gChangeLineCurSum;
    }

    return rtnValue;
}

/*************************************************
  ������:  GetChangeLineId    
  ��������: ��ȡָ�������±��Ӧ���л���·ID
  ����: const UINT16 bufIndex, �����±�    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �л���·ID      
*************************************************/
UINT16_S GetChangeLineId(const UINT16_S bufIndex)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].ChangeLineId;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:  GetChangeLineConfigBufIndex    
  ��������: ��ȡָ��ID�л���·������
  ����: const UINT16 changeLineId,�л���·ID
  ���: ��
  ����ֵ: CHANGE_LINE_SUM_MAX: ��ȡ����ʧ��
			  >=0���������ɹ�
*************************************************/
UINT16_S GetChangeLineConfigBufIndex(const UINT16_S changeLineId)
{
    UINT16_S rtnValue = CHANGE_LINE_SUM_MAX;

    if ((changeLineId >= 1U)&&(changeLineId < CHANGE_LINE_SUM_MAX))
    {
        rtnValue = gChangeLineIdBuff[changeLineId];
    }
    else
    {
        rtnValue = CHANGE_LINE_SUM_MAX;
    }

    return rtnValue;
}

/*************************************************
  ������:   GetChangeLineDir   
  ��������: ��ȡָ���л���·ID��Ӧ���л�����
  ����: const UINT16 changeLineId, �л���·ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �л�����      
*************************************************/
UINT8_S GetChangeLineDir(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT8_S rtnValue = DEFAULT_ZERO;


    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].ChangeDir;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:    GetChangeLineHandOverZcId  
  ��������: ��ȡָ���л���·ID��Ӧ���ƽ�ZCid
  ����: const UINT16 changeLineId, �л���·ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �ƽ�ZCid      
*************************************************/
UINT16_S GetChangeLineHandOverZcId(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].HandOverZcId;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}



/*************************************************
  ������:   GetChangeLineTakeOverZcId   
  ��������: ��ȡָ���л���·ID��Ӧ�Ľӹ�ZCid
  ����: const UINT16 changeLineId, �л���·ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �ӹ�ZCid      
*************************************************/
UINT16_S GetChangeLineTakeOverZcId(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].TakeOverZcId;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:   GetChangeLineStartLink   
  ��������: ��ȡָ���л���·ID��Ӧ�����link
  ����: const UINT16 changeLineId, �л���·ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ���link     
*************************************************/
UINT16_S GetChangeLineStartLink(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex]. ChangeLineStartLink;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:   GetChangeLineStartOffset   
  ��������: ��ȡָ���л���·ID��Ӧ�����offset
  ����: const UINT16 changeLineId, �л���·ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: offset      
*************************************************/
UINT32_S GetChangeLineStartOffset(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT32_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex]. ChangeLineStartOffset;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:   GetChangeLineChangePointLink   
  ��������: ��ȡָ���л���·ID��Ӧ���л���link
  ����: const UINT16 changeLineId, �л���·ID  
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �л���link      
*************************************************/
UINT16_S GetChangeLineChangePointLink(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].ChangePointLink;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
    return rtnValue;
}

/*************************************************
  ������:   GetChangeLineChangePointOffset   
  ��������: ��ȡָ���л���·ID��Ӧ���л���offset
  ����: const UINT16 changeLineId, �л���·ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: offset      
*************************************************/
UINT32_S GetChangeLineChangePointOffset(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT32_S rtnValue= DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].ChangePointOffset;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:   GetChangeLineEndLink   
  ��������: ��ȡָ���л���·ID��Ӧ���յ�link
  ����: const UINT16 changeLineId, �л���·ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �յ�Link      
*************************************************/
UINT16_S GetChangeLineEndLink(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex]. ChangeLineEndLink;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:  GetChangeLineEndOffset    
  ��������: ��ȡָ���л���·ID��Ӧ���յ�offset
  ����: const UINT16 changeLineId, �л���·ID   
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: offset      
*************************************************/
UINT32_S GetChangeLineEndOffset(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT32_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex]. ChangeLineEndOffset;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:    GetChangeLineRelevanceRouteId  
  ��������: ��ȡָ���л���·ID��Ӧ�Ľ�·ID
  ����: const UINT16 changeLineId, �л���·ID 
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��·ID      
*************************************************/
UINT16_S GetChangeLineRelevanceRouteId(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].RelevanceRouteId;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:  GetChangeLineSwitchNum    
  ��������: ��ȡָ���л���·ID��Ӧ�ĵ�������
  ����: const UINT16 changeLineId, �л���·ID    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ��������     
*************************************************/
UINT8_S GetChangeLineSwitchNum(const UINT16_S changeLineId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT8_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gChangeLineConfigDataStruBuff[bufIndex].SwitchNum;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}


/*************************************************
  ������:   GetChangeLineSwitchStruct   
  ��������: ��ȡָ���л���·ID��Ӧ�ĵ�����Ϣ
  ����: const UINT16 changeLineId, �л���·ID    
            const UINT8_S switchStruBufSize, �����С
            ChangeLineSwitchStruct switchStruBuff[],�������
  ���: ChangeLineSwitchStruct switchStruBuff[] ������Ϣ
  ����ֵ: 0: ��ȡ����ʧ��
			>0: ������Ϣ      
*************************************************/
UINT8_S GetChangeLineSwitchStruct(const UINT16_S changeLineId,const UINT8_S switchStruBufSize, ChangeLineSwitchStruct switchStruBuff[])
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT8_S rtnValue = 0U;
    UINT8_S cycle = 0U;

    bufIndex = GetChangeLineConfigBufIndex(changeLineId);  /*��ȡ�����±�*/

    if ((bufIndex < GetChangeLineSum())
        && (switchStruBufSize >= CHANGE_LINE_SWITCH_MAX)
        && (switchStruBuff != NULL))
    {
        for (cycle = 0U;cycle < GetChangeLineSwitchNum(changeLineId);cycle++)
        {
            switchStruBuff[cycle].SwitchId = gChangeLineConfigDataStruBuff[bufIndex].SwitchStruBuff[cycle].SwitchId;
            switchStruBuff[cycle].SwitchNeedStatus = gChangeLineConfigDataStruBuff[bufIndex].SwitchStruBuff[cycle].SwitchNeedStatus;
        }
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:  GetChangeAreaConfigSum    
  ��������: ��ȡ�л���������
  ����: void    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �л���·��ǰ����
*************************************************/
UINT16_S GetChangeAreaConfigSum(void)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (gChangeAreaCurSum >= CHANGE_AREA_LOCAL_SUM_MAX)
    {
        rtnValue = 0U;
    } 
    else
    {
        rtnValue = gChangeAreaCurSum;
    }

    return rtnValue;
}

/*************************************************
  ������: GetChangeAreaOfNextZcId     
  ��������: ��ȡָ�������±��Ӧ���л������Ӧ��ZCID
  ����: const UINT16 bufIndex, �����±�    
  ���: ��
  ����ֵ: 0: ��ȡ����ʧ��
			>0: �л���·ID      
*************************************************/
UINT16_S GetChangeAreaOfNextZcId(const UINT16_S bufIndex)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    if (bufIndex < GetChangeAreaConfigSum())
    {
        rtnValue = gpChangeAreaConfigStruBuff[bufIndex].NextZcId;
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:   GetChangeAreaConfigBufIndex   
  ��������: ��ȡָ��ID�л�����������
  ����: const UINT16 nextZcId,����ZCid
            const UINT16_S outputZcId,�����ZcId
  ���: ��
  ����ֵ:CHANGE_AREA_SUM_MAX: ��ȡ����ʧ��
		   >=0: ���������ɹ�
*************************************************/
UINT16_S GetChangeAreaConfigBufIndex(const UINT16_S outputZcId ,const UINT16_S nextZcId)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT16_S index = CHANGE_AREA_LOCAL_SUM_MAX;

    if ((nextZcId >= 1U)&&(nextZcId < LINE_ZC_SUM_MAX)
        && (outputZcId >= 1U)&&(outputZcId < LINE_ZC_SUM_MAX))
    {
        for (cycle = DEFAULT_ZERO;cycle < gChangeAreaCurSum;cycle++)
        {
            if ((gpChangeAreaConfigStruBuff[cycle].LocalZcId == outputZcId)
                && (gpChangeAreaConfigStruBuff[cycle].NextZcId == nextZcId))
            {
                index = cycle;
                break;
            } 
            else
            {
                /*Do nothing currently !*/
            }
        }
    }
    else
    {
        index = CHANGE_AREA_SUM_MAX;
    }

    return index;
}

/*************************************************
  ������:    GetChangeAreaObsNum  
  ��������: ��ȡָ��ID�������ϰ�������
  ����: const UINT16 nextZcId,����ZCid
            const UINT16_S outputZcId,�����ZcId
  ���: ��
  ����ֵ:0: ��ȡ����ʧ��
		   >0: ��ѯ�ɹ�
*************************************************/
UINT16_S GetChangeAreaObsNum(const UINT16_S outputZcId ,const UINT16_S nextZcId)
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT16_S rtnValue = DEFAULT_ZERO;

    bufIndex = GetChangeAreaConfigBufIndex(outputZcId,nextZcId);  /*��ȡ�����±�*/

    if (bufIndex < GetChangeLineSum())
    {
        rtnValue = gpChangeAreaConfigStruBuff[bufIndex].ObsNum;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

    return rtnValue;
}

/*************************************************
  ������:  GetChangeAreapObsStructBuff    
  ��������: ��ȡָ��ID�л������Ӧ�ϰ�����Ϣ
  ����: const UINT16 nextZcId,����ZCID
            const UINT16_S outputZcId,�����ZcId
            const UINT16_S bufSize, �ϰ���ṹ�������С
            ChangeAreapObsStruct obsStruBuff[], ������ϰ�����Ϣ����
  ���: ��
  ����ֵ:0: ��ȡ����ʧ��
		   >0: ��ѯ�ɹ�
*************************************************/
UINT8_S GetChangeAreapObsStructBuff(const UINT16_S outputZcId ,const UINT16_S nextZcId,const UINT16_S bufSize,ChangeAreapObsStruct obsStruBuff[])
{
    UINT16_S bufIndex = 0U;     /*�����±�*/
    UINT8_S rtnValue = 0U;
    UINT16_S cycle = 0U;

    bufIndex = GetChangeAreaConfigBufIndex(outputZcId,nextZcId);  /*��ȡ�����±�*/

    if ((bufIndex < GetChangeLineSum())
        && (bufSize >= CHANGE_AREA_OBS_MAX)
        && (obsStruBuff != NULL))
    {
        for (cycle = 0U;cycle < GetChangeAreaObsNum(outputZcId,nextZcId);cycle++)
        {
            obsStruBuff[cycle].ObsId = gpChangeAreaConfigStruBuff[bufIndex].ObsStruBuff[cycle].ObsId;
            obsStruBuff[cycle].ObsType = gpChangeAreaConfigStruBuff[bufIndex].ObsStruBuff[cycle].ObsType;
        }
        rtnValue = RETURN_SUCCESS ;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
    return rtnValue;
}

/*************************************************
  ������:   GetLineDeviceBelongZcId    
  ��������: ��ȡ��·�豸����ZC��Ϣ
  ����: ��   
  ���: ��
  ����ֵ: 0: ��ȡʧ��
			>0: ����ZCID      
*************************************************/
UINT16_S GetLineDeviceBelongZcId(const UINT16_S devId,const UINT8_S devType)
{
    UINT16_S rtnValue = DEFAULT_ZERO;

    switch (devType)
    {
    case OBS_TYPE_POINT:
        rtnValue = GetLineSwitchBelongZcId(devId);
        break;

    case OBS_TYPE_SIGNAL:
        rtnValue = GetLineSignalBelongZcId(devId);
        break;

    case OBS_TYPE_PSD:
        rtnValue = GetLinePsdBelongZcId(devId);
        break;

    case OBS_TYPE_ESB:
        rtnValue = GetLineEsbBelongZcId(devId);
        break;

    case OBS_TYPE_AC:
        rtnValue = GetLineAcBelongZcId(devId);
        break;

    case OBS_TYPE_LS:
        rtnValue = GetLineAcBelongZcId(GetLineLogicSectionBelongAcId(devId));
        break;

    case OBS_TYPE_ROUTE:
        rtnValue = GetLineRouteBelongZcId(devId);
        break;

    case OBS_TYPE_OVERLAP:
        rtnValue = GetLineOverlapBelongZcId(devId);
        break;

    case OBS_TYPE_DRB:
        rtnValue = GetLineDrButtonBelongZcId(devId);
        break;

    case OBS_TYPE_DRL:
        rtnValue = GetLineDrLampBelongZcId(devId);
        break;

    default:
        rtnValue = DEFAULT_ZERO;
        break;
    }

    return rtnValue;
}

/*************************************************
  ������:    GetAppointObsInChangeArea  
  ��������: ��ȡָ��ID�����͵��ϰ����Ƿ������л�����
  ����: const UINT16 obsId �ϰ���ID
       const UINT8_S obsType �ϰ�������
  ���: ��
  ����ֵ:0: ��ȡ����ʧ�ܣ��������л����������ZC��
		    1: ��ѯ�ɹ��������л����������ZC��
*************************************************/
UINT8_S GetAppointObsInChangeArea(const UINT16_S obsId,const UINT8_S obsType)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S breakFlag = DEFAULT_ZERO;
    UINT16_S cycleObs = DEFAULT_ZERO;
    UINT16_S obsNum = DEFAULT_ZERO;
    ChangeBitTableStruct *pObsInfoStru = NULL;
    UINT8_S commTargetNum = 0U;                                           
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX] = {DEFAULT_ZERO};

    /*��ȡ��ZCͨ�ŵ�����ZC��Ϣ*/
    commTargetNum = GetSingleCommTargetTypeSum(INNER_DEVTYPE_ZC);

    if (RETURN_SUCCESS == GetSingleCommTargetIdBuff(INNER_DEVTYPE_ZC,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff))
    {
        for (cycle = DEFAULT_ZERO;cycle < commTargetNum;cycle++)
        {
            /*��ʼ���ֲ�����*/
            pObsInfoStru = NULL;
            obsNum = DEFAULT_ZERO;

            /*��ȡZC��Ӧ�ĸ����͵��ϰ�������*/
            GetObsBitTableNum(commTargetIdBuff[cycle],GetLocalZcId(),obsType,&obsNum);

            /*��ȡZC��Ӧ�ĸ����͵��ϰ���Id����*/
            pObsInfoStru = GetObsBitTableStrInfo(commTargetIdBuff[cycle],GetLocalZcId(),obsType);

            if (NULL != pObsInfoStru)
            {
                for (cycleObs = DEFAULT_ZERO;cycleObs < obsNum;cycleObs++)
                {
                    if (obsId == pObsInfoStru[cycleObs].ObsId)
                    {
                        rtnValue = RETURN_SUCCESS;
                        breakFlag = FLAG_SET;
                        break;
                    } 
                    else
                    {
                        /*������*/
                    }
                }
            } 
            else
            {
                rtnValue = RETURN_ERROR;
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
  ������:  GetObsBitTableNum    
  ��������: ��ȡָ�����͵��ϰ������λ����
  ����: const UINT16 nZcId, ����ZCid
            const UINT16_S outputZcId,�����ZcId
            const UINT8_S obsType �ϰ�������
            UINT16_S *pObsNum �ϰ�������
  ���: ��
  ����ֵ:RETURN_ERROR: ��ȡ����ʧ��
		    RETURN_SUCCESS: ��ѯ�ɹ�
*************************************************/
UINT8_S GetObsBitTableNum(const UINT16_S outputZcId,const UINT16_S nZcId, const UINT8_S obsType, UINT16_S *pObsNum)
{
    UINT16_S index = DEFAULT_UINT16_VALUE;
    UINT8_S flag = DEFAULT_ZERO;
    UINT8_S rtnValue = DEFAULT_ZERO;

    if (NULL != pObsNum)
    {
        /*��ʼ���������*/
        (*pObsNum) = DEFAULT_ZERO;

        /*����ZcID��Ӧ�������±�*/
        index = GetChangeAreaConfigBufIndex(outputZcId,nZcId);

        if (CHANGE_AREA_SUM_MAX != index)
        {
            switch (obsType)
            {
            case OBS_TYPE_AC:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].AcNum;
                break;

            case OBS_TYPE_DRB:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].DrButtonNum;
                break;

            case OBS_TYPE_DRL:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].DrLampNum;
                break;

            case OBS_TYPE_POINT:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].SwitchNum;
                break;

            case OBS_TYPE_OVERLAP:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].OverlapNum;
                break;

            case OBS_TYPE_SIGNAL:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].SignalNum;
                break;

            case OBS_TYPE_PSD:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].PsdNum;
                break;

            case OBS_TYPE_ESB:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].EsbNum;
                break;

            case OBS_TYPE_ROUTE:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].RouteNum;
                break;

            case OBS_TYPE_LS:
                (*pObsNum) = gpChangeAreaConfigStruBuff[index].LogicSectionNum;
                break;

            default:
                flag = FLAG_SET;
                (*pObsNum) = 0U;
                break;
            }
        } 
        else
        {
            flag = FLAG_SET;
            (*pObsNum) = 0U;		
        }

        if (FLAG_SET == flag)
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

/*************************************************
  ������:   GetObsBitTableStrInfo  
  ��������: ��ȡָ�����͵��ϰ�������λ��Ϣ�ṹ
  ����: const UINT16 nZcId, ����ZCid
            const UINT16_S outputZcId,�����ZcId
            const UINT8_S obsType �ϰ�������
  ���: ��
  ����ֵ:NULL: ��ȡ����ʧ��
		   !NULL: ��ѯ�ɹ�
*************************************************/
ChangeBitTableStruct* GetObsBitTableStrInfo(const UINT16_S outputZcId,const UINT16_S nZcId,const UINT8_S obsType)
{
    UINT16_S index = DEFAULT_UINT16_VALUE;
    ChangeBitTableStruct *pRtnValue = NULL;

    /*����ZcID��Ӧ�������±�*/
    index = GetChangeAreaConfigBufIndex(outputZcId,nZcId);

    if (CHANGE_AREA_SUM_MAX != index)
    {
        switch (obsType)
        {
        case OBS_TYPE_AC:
            /* return gpChangeAreaConfigStruBuff[index].AcBitStruBuff; */
            pRtnValue = gpChangeAreaConfigStruBuff[index].AcBitStruBuff;
            break;

        case OBS_TYPE_DRB:
            pRtnValue = gpChangeAreaConfigStruBuff[index].DrButtonBitStruBuff;
            break;

        case OBS_TYPE_DRL:
            pRtnValue = gpChangeAreaConfigStruBuff[index].DrLampBitStruBuff;
            break;

        case OBS_TYPE_POINT:
            pRtnValue = gpChangeAreaConfigStruBuff[index].SwitchBitStruBuff;
            break;

        case OBS_TYPE_OVERLAP:
            pRtnValue = gpChangeAreaConfigStruBuff[index].OverlapBitStruBuff;
            break;

        case OBS_TYPE_SIGNAL:
            pRtnValue = gpChangeAreaConfigStruBuff[index].SignalBitStruBuff;
            break;

        case OBS_TYPE_PSD:
            pRtnValue = gpChangeAreaConfigStruBuff[index].PsdBitStruBuff;
            break;

        case OBS_TYPE_ESB:
            pRtnValue = gpChangeAreaConfigStruBuff[index].EsbBitStruBuff;
            break;

        case OBS_TYPE_ROUTE:
            pRtnValue = gpChangeAreaConfigStruBuff[index].RouteBitStruBuff;
            break;

        case OBS_TYPE_LS:
            pRtnValue = gpChangeAreaConfigStruBuff[index].LogicSectionBitStruBuff;
            break;

        default:
            pRtnValue = NULL;
            break;
        }
    } 
    else
    {
        pRtnValue = NULL;
    }

    return pRtnValue;
}

/*************************************************
  ������:  GetObsBitTableNumOfIndex    
  ��������: ��ȡָ�����͵��ϰ������λ�������±�������
  ����: const UINT8 changeAreaIndex �л���·�±�
            const UINT8_S obsType �ϰ�������
            UINT16_S *pObsNum �ϰ�������
  ���: ��
  ����ֵ:RETURN_ERROR: ��ȡ����ʧ��
		    RETURN_SUCCESS: ��ѯ�ɹ�
*************************************************/
UINT8_S GetObsBitTableNumOfIndex(const UINT8_S changeAreaIndex, const UINT8_S obsType, UINT16_S *pObsNum)
{
    UINT8_S rtnValue = DEFAULT_ZERO;
    UINT8_S flag = DEFAULT_ZERO;

    if (NULL != pObsNum)
    {
        /*��ʼ���������*/
        (*pObsNum) = DEFAULT_ZERO;

        if (CHANGE_AREA_LOCAL_SUM_MAX <= changeAreaIndex)
        {
            flag = FLAG_SET;
            (*pObsNum) = 0U;
        } 
        else
        {          
            switch (obsType)
            {
            case OBS_TYPE_AC:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].AcNum;
                break;

            case OBS_TYPE_DRB:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].DrButtonNum;
                break;

            case OBS_TYPE_DRL:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].DrLampNum;
                break;

            case OBS_TYPE_POINT:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].SwitchNum;
                break;

            case OBS_TYPE_OVERLAP:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].OverlapNum;
                break;

            case OBS_TYPE_SIGNAL:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].SignalNum;
                break;

            case OBS_TYPE_PSD:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].PsdNum;
                break;

            case OBS_TYPE_ESB:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].EsbNum;
                break;

            case OBS_TYPE_ROUTE:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].RouteNum;
                break;

            case OBS_TYPE_LS:
                (*pObsNum) = gpChangeAreaConfigStruBuff[changeAreaIndex].LogicSectionNum;
                break;

            default:
                flag = FLAG_SET;
                (*pObsNum) = 0U;
                break;
            }
        }
    } 
    else
    {
        flag = FLAG_SET;
    }
    
    if (FLAG_SET == flag)
    {
        rtnValue = RETURN_ERROR;	
    } 
    else
    {
        rtnValue = RETURN_SUCCESS;
    }

    return rtnValue;
}

/*************************************************
  ������:  GetObsBitTableStrInfoOfIndex    
  ��������: ��ȡָ�����͵��ϰ�������λ��Ϣ�ṹ���±�������
  ����: const UINT8 changeAreaIndex �л������±�
            const UINT8_S obsType �ϰ�������
  ���: ��
  ����ֵ:NULL: ��ȡ����ʧ��
		   !NULL: ��ѯ�ɹ�
*************************************************/
ChangeBitTableStruct* GetObsBitTableStrInfoOfIndex(const UINT8_S changeAreaIndex,const UINT8_S obsType)
{
    ChangeBitTableStruct *pRtnValue = NULL;

    if (CHANGE_AREA_LOCAL_SUM_MAX <= changeAreaIndex)
    {
        pRtnValue = NULL;
    } 
    else
    {      
        switch (obsType)
        {
        case OBS_TYPE_AC:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].AcBitStruBuff;
            break;

        case OBS_TYPE_DRB:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].DrButtonBitStruBuff;
            break;

        case OBS_TYPE_DRL:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].DrLampBitStruBuff;
            break;

        case OBS_TYPE_POINT:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].SwitchBitStruBuff;
            break;

        case OBS_TYPE_OVERLAP:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].OverlapBitStruBuff;
            break;

        case OBS_TYPE_SIGNAL:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].SignalBitStruBuff;
            break;

        case OBS_TYPE_PSD:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].PsdBitStruBuff;
            break;

        case OBS_TYPE_ESB:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].EsbBitStruBuff;
            break;

        case OBS_TYPE_ROUTE:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].RouteBitStruBuff;
            break;

        case OBS_TYPE_LS:
            pRtnValue = gpChangeAreaConfigStruBuff[changeAreaIndex].LogicSectionBitStruBuff;
            break;

        default:
            pRtnValue = NULL;
            break;
        }
    }

    return pRtnValue;
}
