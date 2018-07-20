/************************************************************************
*
* �ļ���   ��  SysConfigData.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��ȡZCϵͳ�������ݹ���
* ��  ע   ��  ��
*
************************************************************************/
#include "SysConfigData.h"

ZcSubsystemConfigDataStruct gZcSubsystemConfigDataStru;     /*����ZC��ϵͳ������������Ϣ�ṹ*/
SystemConfigDataStruct gSystemConfigDataStru;               /*����CBTCϵͳ������������Ϣ�ṹ*/
LocalZcConfigDataStruct gLocalZcConfigDataStru;             /*���屾��ZC�������ݽṹ��Ϣ*/

/*
* ���������� ��ȡ����ZC��id
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ����ZCid      
*/
UINT16_S GetLocalZcId(void)
{
	UINT16_S rtnValue = DEFAULT_ZERO;

	if (gLocalZcConfigDataStru.wZCID >= LINE_ZC_SUM_MAX)
	{
		rtnValue = 0U;
	} 
	else
	{
		rtnValue = gLocalZcConfigDataStru.wZCID;
	}

	return rtnValue;
}

/*
* ���������� ��ȡ��Ӫ���źŻ��������Ҫ�ĳ���
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��Ӫ���źŻ��������Ҫ�ĳ���      
*/
UINT32_S GetSignalLightLength(void)
{
	return gZcSubsystemConfigDataStru.SignalLightLength;
}

/*
* ���������� ��ȡ��·��С���ܳ���
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��·��С���ܳ���      
*/
UINT16_S GetLineMinTrainLength(void)
{
	return gZcSubsystemConfigDataStru.LineMinTrainLength;
}

/*
* ���������� ��ȡ�г�������з�������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г�������з�������      
*/
UINT16_S GetRetreatProtectDistance(void)
{
	return gZcSubsystemConfigDataStru.RetreatProtectDistance;
}

/*
* ���������� ��ȡ���������ж�������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ���������ж�������     
*/
UINT16_S GetSectionRedundantCycle(void)
{
    UINT16_S rtnValue = 0U;

    rtnValue = (UINT16_S)gZcSubsystemConfigDataStru.SectionRedundantCycle;

	return rtnValue;
}

/*
* ���������� ��ȡNTPУʱʱ����
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: NTPУʱʱ����     
*/
UINT8_S GetNtpTimeZoneDiff(void)
{
	return gSystemConfigDataStru.NtpTimeZoneDiff;
}

/*
* ���������� ��ȡZC��ATS�㱨�г�ռ��������Ϣ��������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ZC��ATS�㱨�г�ռ��������Ϣ��������     
*/
UINT8_S GetZCToATSCycleCycle(void)
{
	return gZcSubsystemConfigDataStru.ZCToATSCycleCycle;
}

/*
* ���������� ��ȡ�г�CBTC�۷�������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г�CBTC�۷�������    
*/
UINT8_S GetReverseCycle(void)
{
	return gZcSubsystemConfigDataStru.ReverseCycle;
}

/*
* ���������� ��ȡZC�Ƿ���Ҫ崻���־
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ZC�Ƿ���Ҫ崻���־    
*/
UINT8_S GetZCDowntimeFlag(void)
{
	return gZcSubsystemConfigDataStru.ZCDowntimeFlag;
}

/*
* ���������� ��ȡ���͸�CI���߼�����ռ����λ����
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ���͸�CI���߼�����ռ����λ����    
*/
UINT8_S GetToCiSectionType(void)
{
	return gZcSubsystemConfigDataStru.ToCiSectionType;
}
/*
* ���������� ��ȡ�г���ѹ�źŻ��жϾ���
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г���ѹ�źŻ��жϾ���   
*/
UINT16_S GetTrainAcrossSignalDis(void)
{
	return gZcSubsystemConfigDataStru.TrainAcrossSignalDis;
}

/*
* ���������� ��ȡNTPУʱ���ʱ��
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: NTPУʱ���ʱ��   
*/
UINT32_S GetNtpCheckDiffTime(void)
{
	return gZcSubsystemConfigDataStru.NtpCheckDiffTime;
}

/*
* ���������� ��ȡУʱ����
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: Уʱ����   
*/
UINT16_S GetSendNtpApplyCycle(void)
{
	return gZcSubsystemConfigDataStru.SendNtpApplyCycle;
}

/*
* ���������� ��ȡϵͳ��С�������γ���
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ϵͳ��С�������γ���   
*/
UINT16_S GetLineMinOverlapLength(void)
{
	return gSystemConfigDataStru.LineMinOverlapLength;
}

/*
* ���������� ��ȡϵ��·�������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��·�������   
*/
UINT16_S GetLineMaxSpeed(void)
{
	return gSystemConfigDataStru.LineMaxSpeed;
}

/*
* ���������� ��ȡ��ʱ�����������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ʱ�����������   
*/
UINT16_S GetLineMaxTSRSpeed(void)
{
	return gSystemConfigDataStru.LineMaxTSRSpeed;
}

/*
* ���������� ��ȡ��ȫ��������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ȫ��������   
*/
UINT16_S GetLineMaBackDistance(void)
{
	return gSystemConfigDataStru.LineMaBackDistance;
}

/*
* ���������� ��ȡ�복��ATPͨ�Ź���������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �복��ATPͨ�Ź���������   
*/
UINT8_S GetTrainAtpCommCycle(void)
{
	return gSystemConfigDataStru.TrainAtpCommCycle;
}

/*
* ���������� ��ȡ������ZCͨ�Ź���������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ������ZCͨ�Ź���������  
*/
UINT8_S GetNZcCommCycle(void)
{
	return gSystemConfigDataStru.NZcCommCycle;
}

/*
* ���������� ��ȡ��CIͨ�Ź���������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��CIͨ�Ź���������   
*/
UINT8_S GetCICommCycle(void)
{
	return gSystemConfigDataStru.CICommCycle;
}

/*
* ���������� ��ȡ��ATSͨ�Ź���������
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ��ATSͨ�Ź���������   
*/
UINT8_S GetATSCommCycle(void)
{
	return gSystemConfigDataStru.ATSCommCycle;
}

/*
* ���������� ��ȡZC�ڲ��߼�������CI�����з���֮��Ĺ�ϵ
* ����˵���� void    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: ZC�ڲ��߼�������CI�����з���֮��Ĺ�ϵ   
*/
UINT8_S GetLinkLogicDirUpAndDown(void)
{
	return gSystemConfigDataStru.LinkLogicDirUpAndDown;
}

/*
* ���������� ��ȡָ��ZcId��Ӧ���г�����
* ����˵���� const UINT16 trainId �г�Id    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г�����   
*/
UINT16_S GetLineTrainType(const UINT16_S trainId)
{
	UINT16_S rtnvalue = DEFAULT_ZERO;

	if ((trainId >= 1U)&&(trainId < LINE_MAX_TRAIN_ID))
	{
		rtnvalue = gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainType;
	}
	else
	{
		rtnvalue = RETURN_ERROR;
	}

	return rtnvalue;
}

/*
* ���������� ��ȡָ��ZcId��Ӧ���г�����
* ����˵���� const UINT16 trainId �г�Id    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г�����   
*/
UINT16_S GetTrainLength(const UINT16_S trainId)
{
	UINT16_S rtnvalue = DEFAULT_ZERO;

	if ((trainId >= 1U)&&(trainId < LINE_MAX_TRAIN_ID))
	{
		rtnvalue = gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].TrainLength;
	}
	else
	{
		rtnvalue = RETURN_ERROR;
	}

	return rtnvalue;
}

/*
* ���������� ��ȡָ��ZcId��Ӧ���г���·��������¶�
* ����˵���� const UINT16 trainId �г�Id    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г���·��������¶�   
*/
UINT16_S GetMaxLineDeclGradient(const UINT16_S trainId)
{
	UINT16_S rtnvalue = DEFAULT_ZERO;

	if ((trainId >= 1U)&&(trainId < LINE_MAX_TRAIN_ID))
	{
		rtnvalue = gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].MaxLineDeclGradient;
	}
	else
	{
		rtnvalue = RETURN_ERROR;
	}

	return rtnvalue;
}

/*
* ���������� ��ȡָ��ZcId��Ӧ���г����ǣ�����ٶ�
* ����˵���� const UINT16 trainId �г�Id    
* ����ֵ  �� 0: ��ȡ����ʧ��
*			>0: �г����ǣ�����ٶ�  
*/
UINT16_S GetMaxTrainTractionAcc(const UINT16_S trainId)
{
	UINT16_S rtnvalue = DEFAULT_ZERO;

	if ((trainId >= 1U)&&(trainId < LINE_MAX_TRAIN_ID))
	{
		rtnvalue = gSystemConfigDataStru.TrainPerParameterStruBuff[trainId].MaxTrainTractionAcc;
	}
	else
	{
		rtnvalue = RETURN_ERROR;
	}

	return rtnvalue;
}

/*
* ���������� ׷�ٲ����󷽼����RM�г���ʽ
* ����˵��:  ��
* ����ֵ  :  UINT8_NULL: ��ȡ����ʧ��
*			<UINT8_NULL: ׷�ٲ����󷽼����RM�г���ʽ
*/ 
UINT8_S GetZcTraceRmTrainType(void)
{
	return gZcSubsystemConfigDataStru.ZcTraceRmTrainType;
}

/*
* ���������� ��ȡ��·����󳵳�
* ����˵��:  ��
* ����ֵ  :  >0 ��·�г���󳤶�
*/ 
UINT16_S GetLineMaxTrainLength(void)
{
    return gZcSubsystemConfigDataStru.LineMaxTrainLength;
}

/*
* ���������� ������·����󳵳�
* ����˵��:  const UINT16_S trainMaxLen  ��·�г���󳤶�
* ����ֵ  :  ��
*/ 
void SetLineMaxTrainLength(const UINT16_S trainMaxLen)
{
    if ((DEFAULT_ZERO != trainMaxLen)
        && (UINT16_MAX != trainMaxLen))
    {
        gZcSubsystemConfigDataStru.LineMaxTrainLength = trainMaxLen;
    }  
}
