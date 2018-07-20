/************************************************************************
*
* �ļ���   ��  SynDataPackAndParse.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  2ϵͬ�����ݵĴ���ͽ���
* ��  ע   ��  ��
*
************************************************************************/
#include "SynDataPackAndParse.h"
#include "SynDataDefine.h"
#include "../SysDataManager/SysDefine.h"
#include "../LineDataManager/AC/ACDefine.h"
#include "../LineDataManager/AC/ACConfigData.h"
#include "../LineDataManager/DR/DRDefine.h"
#include "../LineDataManager/DR/DRConfigData.h"
#include "../LineDataManager/ESB/ESBDefine.h"
#include "../LineDataManager/ESB/ESBConfigData.h"
#include "../LineDataManager/PSD/PSDDefine.h"
#include "../LineDataManager/PSD/PSDConfigData.h"
#include "../LineDataManager/LogicSection/LogicSectionDefine.h"
#include "../LineDataManager/LogicSection/LogicSectionConfigData.h"
#include "../LineDataManager/Overlap/OverlapDefine.h"
#include "../LineDataManager/Overlap/OverlapConfigData.h"
#include "../LineDataManager/Route/RouteDefine.h"
#include "../LineDataManager/Route/RouteConfigData.h"
#include "../LineDataManager/Signal/SignalDefine.h"
#include "../LineDataManager/Signal/SignalConfigData.h"
#include "../LineDataManager/Switch/SwitchDefine.h"
#include "../LineDataManager/Switch/SwitchConfigData.h"
#include "../LineDataManager/Tsr/TsrDefine.h"
#include "../LineDataManager/Tsr/TsrConfigData.h"
#include "../TrainManager/Train/TrainDefine.h"
#include "../LineDataManager/DataVersion/DataVersionConfigData.h"
#include "../LineDataManager/DataVersion/DataVersionDefine.h"
#include "../IOManager/CommTarget/CommTargetConfigData.h"
#include "../IOManager/CommTarget/CommTargetDefine.h"
#include "../IOManager/CommTarget/CommTargetStatusData.h"
#include "../LineDataManager/AC/ACStatusData.h"
#include "../LineDataManager/Change/ChangeStatusData.h"
#include "../LineDataManager/DR/DRStatusData.h"
#include "../LineDataManager/ESB/ESBStatusData.h"
#include "../LineDataManager/LogicSection/LogicSectionStatusData.h"
#include "../LineDataManager/Overlap/OverlapStatusData.h"
#include "../LineDataManager/PSD/PSDStatusData.h"
#include "../LineDataManager/Route/RouteStatusData.h"
#include "../LineDataManager/Signal/SignalStatusData.h"
#include "../LineDataManager/Switch/SwitchStatusData.h"
#include "../LineDataManager/Tsr/TsrStatusData.h"
#include "../TrainManager/Train/TrainStatusData.h"
#include "../SysDataManager/SysStatusData.h"
#include "../SysDataManager/SysTimeData.h"
#include "../../Common/MemSet.h"
#include "../../Common/Copy.h"
#include "../../Common/Convert.h"
#include "../MaintainManager/MaintainManager.h"
#include "../TsrManager/TsrInterface.h"/*-bye-*/

#ifdef SYS_TYPE_VXWORKS
#include "../../cspadpt/Vcp_Service_Interface.h"
#endif

/*AC*/
extern AcStatusDataStruct gAcStatusDataStruBuff[LOCAL_AC_SUM_MAX];          /*���屾ZC��������״̬�ṹ��*/
extern UINT16_S gAcCurSum;	   /*ZC��������״̬�ṹ������*/
/*DR*/
extern DRButtonDataStruct  gDRButtonDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];  /*���������۷���ť״̬���ݽṹ��*/
extern UINT16_S gDRButtonCurSum ;                                                    /*�����۷���ť��ǰ����*/
extern DRLampDataStruct gDRLampDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];         /*���������۷���״̬���ݽṹ��*/
extern UINT16_S gDRLampCurSum ;                                                      /*�����۷���ť��ǰ����*/
/*ESB*/
extern EsbDataStruct gEsbDataStruBuff[ESB_LOCAL_SUM_MAX];             /*���ع���Ľ���ͣ����ť״̬��Ϣ*/
extern UINT16_S gEsbCurSum ;                                              /*����ͣ����ť��ǰ����*/
/*PSD*/
extern PsdDataStruct gPsdDataStruBuff[PSD_LOCAL_SUM_MAX];                 /*���屾�ع����������״̬��������*/
extern UINT16_S gPsdCurSum ;                                    /*�����ŵ�ǰ����*/
/*LogicSection*/
extern LogicSectionStruct gLogicSectionDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];     /*���屾�ع�����߼�����״̬��������*/
extern UINT16_S gLogicSectionCurSum ;     /*�߼����ε�ǰ����*/
/*Overlap*/
extern OverlapDataStruct gOverlapDataStruBuff[OVERLAP_LOCAL_SUM_MAX];          /*���ع���ı�������״̬��Ϣ*/
extern UINT16_S gOverlapCurSum ;                                                        /*�������ε�ǰ����*/
/*Route*/
extern RouteDataStruct gRouteStatusDataStruBuff[ROUTE_LOCAL_SUM_MAX];          /*���ع���ı�������״̬��Ϣ*/
extern UINT16_S gRouteCurSum ;                                                          /*��·��ǰ����*/
/*Signal*/
extern SignalDataStruct gSignalDataStruBuff[SIGNAL_LOCAL_SUM_MAX];          /*���ع���ı�������״̬��Ϣ*/
extern UINT16_S gSignalCurSum ;                                                      /*�źŻ���ǰ����*/
/*Switch*/
extern SwitchDataStruct gSwitchStatusDataStruBuff[SWITCH_LOCAL_SUM_MAX];          /*���ع���ĵ���״̬��Ϣ*/
extern UINT16_S gSwitchCurSum ;                                                      /*����ǰ����*/
/*Tsr*/
extern TsrDataStruct gTsrDataStruBuff[TSR_BUFF_SUM_MAX];                  /*���ع������ʱ����������Ϣ*/
extern UINT16_S gTsrOfZcIdBuff[LINE_ZC_SUM_MAX] ;    /*������ʱ���٣�ZC��ӳ������*/
extern UINT16_S gTsrOfZcCurSum ;                                     /*��ʱ���٣�ZC����ǰ����*/
/*Train*/
extern TrainInfoStruct gTrainStatusDataStruBuff[SIZE_MAX_CONTROLE_TRAIN];   /*���屾ZC���Ʒ�Χ������г�����*/
extern UINT8_S gLocalTrainIndexBuff[SIZE_MAX_LINE_TRAIN] ;			/*�����г��������飬���鳤��Ϊ��·���ܵ�����г�ID*/
extern UINT8_S gTrainCurSum ;									        /*��ZC��ǰ�г�����*/
/*DataVersion*/
extern DataVersionStruct gInputDataVersionStru;                 /*�������ݰ汾����Ϣ*/
/*CommTarget*/
extern CommTargetDataStruct gCommTargetDataStruBuff[COMM_TYPE_SUM_MAX];      /*����ͨ�Ŷ���״̬��Ϣ�����г��������ϵͳ��*/
extern SingleCommTargeStruct gCommTrainDataStruBuff[COMM_TRAIN_ID_MAX];      /*ͨ���г�״̬��Ϣ*/
extern UINT8_S gCommTargetTypeCurSum ;                                                       /*����ͨ�Ŷ�������*/

/*
* ���������� ����֡���е�ȫ����Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S ParseAllInfoFromFrame(const UINT8_S inFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT32_S buffIndex=DEFAULT_ZERO;           /*������±�*/
	UINT32_S dataLength=DEFAULT_ZERO;          /*���������ܳ���*/
	UINT32_S totalLength=DEFAULT_ZERO;         /*�����ܳ���*/
	
    if (NULL != inFrameContent)
    {
        /*�ܳ���*/
        totalLength=LongFromChar(&inFrameContent[DEFAULT_ZERO]);

        /*2����ͷ*/
        if ((SYN_DATA_CONTENT_HEAD1==inFrameContent[4])&&(SYN_DATA_CONTENT_HEAD2==inFrameContent[5]))
        {
            /*���������ܳ���*/
            dataLength=LongFromChar(&inFrameContent[6]);

            /*��Ϊ�����ܳ���δ֪,����4���ֽ�*/
            buffIndex=SYN_DATA_START_INDEX;

            /*AC*/
            rtnValue = GetACInfoFromFrame(inFrameContent,&buffIndex);

            /*DR*/
            rtnValue *= GetDRButtonInfoFromFrame(inFrameContent,&buffIndex);
            rtnValue *=GetDRLampInfoFromFrame(inFrameContent,&buffIndex);

            /*ESB*/
            rtnValue *= GetESBInfoFromFrame(inFrameContent,&buffIndex);

            /*PSD*/
            rtnValue *= GetPSDInfoFromFrame(inFrameContent,&buffIndex);

            /*LogicSection*/
            rtnValue *= GetLogicSectionInfoFromFrame(inFrameContent,&buffIndex);

            /*Overlap*/
            rtnValue *= GetOverlapInfoFromFrame(inFrameContent,&buffIndex);

            /*Route*/
            rtnValue *= GetRouteInfoFromFrame(inFrameContent,&buffIndex);

            /*Signal*/
            rtnValue *= GetSignalInfoFromFrame(inFrameContent,&buffIndex);

            /*Switch*/
            rtnValue *= GetSwitchInfoFromFrame(inFrameContent,&buffIndex);

            /*Tsr*/
            rtnValue *= GetTsrInfoFromFrame(inFrameContent,&buffIndex);

            /*Train*/
            rtnValue *= GetTrainInfoFromFrame(inFrameContent,&buffIndex);

            /*CommTarget*/
            rtnValue *= GetCommTargetInfoFromFrame(inFrameContent,&buffIndex);

            /*NTPУʱ�ɹ���־*/
            rtnValue *= GetNTPTimeFlagInfoFromFrame(inFrameContent,&buffIndex);

            /*NTPУʱ����ʱ��*/
            rtnValue *= GetNTPLocalTimeInfoFromFrame(inFrameContent,&buffIndex);

            /*NTPУʱ4���ṹ��ʱ��*/
            rtnValue *= GetNTPStructTimeInfoFromFrame(inFrameContent,&buffIndex);

            /*ZC�ϵ��ǳɹ���־*/
            rtnValue *= GetZCPowerUpFlagInfoFromFrame(inFrameContent,&buffIndex);

            /*CRC32*/


            if ((dataLength == ((buffIndex-SYN_DATA_START_INDEX) + 1U)) 
                && (RETURN_SUCCESS == rtnValue))
            {
                rtnValue=RETURN_SUCCESS; 
            } 
            else
            {
                rtnValue=RETURN_ERROR;
            }
        } 
        else
        {
            rtnValue=RETURN_ERROR;
        }
    } 
    else
    {
        rtnValue=RETURN_ERROR;
    }
	
	if(RETURN_SUCCESS == rtnValue)
	{
        LogPrintf(1u,"Switchover Success!\n");

#ifdef SYS_TYPE_VXWORKS
	    printf("Switchover Success!\n");
#endif
        
	}
	else
	{		
        LogPrintf(1u,"Switchover Error!\n");

		/*F_VCP_UsrHaltSystem*/
#ifdef SYS_TYPE_VXWORKS
        printf("Switchover Error!\n");
		F_VCP_UsrHaltSystem(1U);
#endif
        
	}
	
	return rtnValue;
}

/*
* ���������� ����֡���е�ȫ����Ϣ
* ����˵���� UINT8 outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S PackAllInfoToFrame(UINT8_S outFrameContent[])
{
	UINT32_S buffIndex=DEFAULT_ZERO;           /*������±�*/
	UINT32_S dataLength=DEFAULT_ZERO;          /*�����ܳ���*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	/*��ʼ��*/
	MemorySet(&outFrameContent[DEFAULT_ZERO],SYN_DATA_MAX_NUM,DEFAULT_ZERO,SYN_DATA_MAX_NUM);	
	
    if (NULL != outFrameContent)
    {
        /*2����ͷ*/
        outFrameContent[4]=SYN_DATA_CONTENT_HEAD1;
        outFrameContent[5]=SYN_DATA_CONTENT_HEAD2;

        /*��Ϊ�����ܳ���δ֪,����4���ֽ�*/
        buffIndex=SYN_DATA_START_INDEX;

        /*AC*/
        rtnValue = SetACInfoToFrame(&buffIndex,outFrameContent);

        /*DR*/
        rtnValue *= SetDRButtonInfoToFrame(&buffIndex,outFrameContent);
        rtnValue *= SetDRLampInfoToFrame(&buffIndex,outFrameContent);

        /*ESB*/
        rtnValue *= SetESBInfoToFrame(&buffIndex, outFrameContent);

        /*PSD*/
        rtnValue *= SetPSDInfoToFrame(&buffIndex, outFrameContent);

        /*LogicSection*/
        rtnValue *= SetLogicSectionInfoToFrame(&buffIndex, outFrameContent);

        /*Overlap*/
        rtnValue *= SetOverlapInfoToFrame(&buffIndex, outFrameContent);

        /*Route*/
        rtnValue *= SetRouteInfoToFrame(&buffIndex, outFrameContent);

        /*Signal*/
        rtnValue *= SetSignalInfoToFrame(&buffIndex, outFrameContent);

        /*Switch*/
        rtnValue *= SetSwitchInfoToFrame(&buffIndex, outFrameContent);

        /*Tsr*/
        rtnValue *= SetTsrInfoToFrame(&buffIndex, outFrameContent);

        /*Train*/
        rtnValue *= SetTrainInfoToFrame(&buffIndex, outFrameContent);

        /*CommTarget*/
        rtnValue *= SetCommTargetInfoToFrame(&buffIndex, outFrameContent);

        /*NTPУʱ�ɹ���־*/
        rtnValue *= SetNTPTimeFlagInfoToFrame(&buffIndex,outFrameContent);

        /*NTPУʱʱ��*/
        rtnValue *= SetNTPLocalTimeInfoToFrame(&buffIndex,outFrameContent);

        /*NTPУʱ4���ṹ��ʱ��*/
        rtnValue *= SetNTPStructTimeInfoToFrame(&buffIndex,outFrameContent);

        /*ZC�ϵ��ǳɹ���־*/
        rtnValue *= SetZCPowerUpFlagInfoToFrame(&buffIndex, outFrameContent);
        /*CRC32*/

        /*���������ܳ���,5����֡ͷ*/
        dataLength=(buffIndex-SYN_DATA_START_INDEX)+1U;
        LongToChar(dataLength,&outFrameContent[6]);

        /*����ܳ���*/
        LongToChar(dataLength+6U,&outFrameContent[DEFAULT_ZERO]);

        if(RETURN_SUCCESS == rtnValue)
        {
            LogPrintf(1u,"Switch Pack Success!\n");

#ifdef SYS_TYPE_VXWORKS
            printf("Switch Pack Success!\n");
#endif
        }
        else
        {
            LogPrintf(1u,"Switch Pack Error!\n");

#ifdef SYS_TYPE_VXWORKS
            printf("Switch Pack Error!\n");
#endif
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }
	
	return rtnValue;
}

/*
* ���������� ����֡���е�AC��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetACInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S acCycle=DEFAULT_ZERO;
	UINT8_S  trainIdCycle=DEFAULT_ZERO;
	UINT16_S acId=DEFAULT_ZERO;   /*��������ID*/
	UINT8_S  acTrainOfAcNum=DEFAULT_ZERO;  /*�����������г�������*/
	UINT16_S trainIdSequenceBuff[SIZE_MAX_TRAINOFAC]={DEFAULT_ZERO};  /*�г�ID����*/

	if ((NULL!=buffIndex)&&(NULL!=inFrameContent))
	{	
        /*������������*/
        gAcCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (acCycle=DEFAULT_ZERO;acCycle<gAcCurSum;acCycle++)
		{
			/*��������ID*/
			acId=ShortFromChar(&inFrameContent[*buffIndex]);
			gAcStatusDataStruBuff[acCycle].AcId=acId;
			*buffIndex=*buffIndex+2U;

			/*����*/
			SetAcDirection(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*����״̬*/
			SetAcBelock(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*ռ��״̬*/
			SetAcStatusNow(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*UT��־*/
			SetAcUtFlag(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*UT������Ϣ*/
			SetAcUtRedundance(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
			
			/*ARB��־*/
			SetAcArbFlag(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*ARB������Ϣ*/
			SetAcArbRedundance(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*��ɨ�г�ID*/
			SetAcCleanTrainId(acId,ShortFromChar(&inFrameContent[*buffIndex]));			
			*buffIndex=*buffIndex+2U;

			/*�г���ɨ��־*/
			SetAcTrainCleanFlag(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*�����������г�����*/
			acTrainOfAcNum=inFrameContent[*buffIndex];
			SetAcTrainOfAcNum(acId,acTrainOfAcNum);
			*buffIndex=*buffIndex+1U;

			/*�г���Ϣ*/
			for (trainIdCycle=DEFAULT_ZERO;trainIdCycle<acTrainOfAcNum;trainIdCycle++)
			{				
				trainIdSequenceBuff[trainIdCycle]=ShortFromChar(&inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;
			}

			SetAcTrainSequenceBuff(acId,trainIdSequenceBuff,acTrainOfAcNum);
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�AC��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetACInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;  /*����ֵ*/
	UINT16_S acCycle=DEFAULT_ZERO;
	UINT8_S  trainIdCycle=DEFAULT_ZERO; 
	UINT16_S acId=DEFAULT_ZERO;         /*����ID*/
	UINT16_S acTotalNum=DEFAULT_ZERO;     /*�г�״̬����*/ 
	UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC]={DEFAULT_ZERO};  /*�г�ID����*/
	UINT8_S  acTrainOfAcNum=DEFAULT_ZERO;  /*�����������г�������*/

	/*��ʼ���г���������*/
	MemorySet(&trainSequenceBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC);

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*��ȡ����״̬������*/
        acTotalNum = GetAcCurSum(); 

        /*������������*/
        ShortToChar(acTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (acCycle=DEFAULT_ZERO;acCycle<acTotalNum;acCycle++)
		{			
			/*��������ID*/
			acId=gAcStatusDataStruBuff[acCycle].AcId;  /*��ȡ�����ID*/
			ShortToChar(acId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;
			
			/*����*/
			outFrameContent[*buffIndex]=GetAcDirection(acId);
			*buffIndex=*buffIndex+1U;

			/*����״̬*/
			outFrameContent[*buffIndex]=GetAcBelock(acId);
			*buffIndex=*buffIndex+1U;

			/*ռ��״̬*/
			outFrameContent[*buffIndex]=GetAcStatusNow(acId);
			*buffIndex=*buffIndex+1U;

			/*UT��־*/
			outFrameContent[*buffIndex]=GetAcUtFlag(acId);
			*buffIndex=*buffIndex+1U;

			/*UT������Ϣ*/
			outFrameContent[*buffIndex]=GetAcUtRedundance(acId);
			*buffIndex=*buffIndex+1U;

			/*ARB��־*/
			outFrameContent[*buffIndex]=GetAcArbFlag(acId);
			*buffIndex=*buffIndex+1U;

			/*ARB������Ϣ*/
			outFrameContent[*buffIndex]=GetAcArbRedundance(acId);
			*buffIndex=*buffIndex+1U;

			/*��ɨ�г�ID*/
			ShortToChar(GetAcCleanTrainId(acId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�г���ɨ��־*/
			outFrameContent[*buffIndex]=GetAcTrainCleanFlag(acId);
			*buffIndex=*buffIndex+1U;

			/*�����������г�����*/
			acTrainOfAcNum=GetAcTrainOfAcNum(acId);
			outFrameContent[*buffIndex]=acTrainOfAcNum;
			*buffIndex=*buffIndex+1U;

			/*�г���Ϣ���г�ID*/
			if (RETURN_SUCCESS==GetAcTrainSequenceBuff(acId,SIZE_MAX_TRAINOFAC,trainSequenceBuff))
			{
				for (trainIdCycle=DEFAULT_ZERO;trainIdCycle<acTrainOfAcNum;trainIdCycle++)
				{
					ShortToChar(trainSequenceBuff[trainIdCycle],&outFrameContent[*buffIndex]);
					*buffIndex=*buffIndex+2U;
				}
			}
			else
			{
                /*������*/
			}			
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}
	
	return rtnValue;
}

/*
* ���������� ����֡����DR�������۷���ť��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetDRButtonInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S drBtnCycle=DEFAULT_ZERO;
    UINT16_S drButtonId=DEFAULT_ZERO;   /*�����۷���ťID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*�����۷���ť����*/
        gDRButtonCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (drBtnCycle=DEFAULT_ZERO;drBtnCycle<gDRButtonCurSum;drBtnCycle++)
		{
			/*�����۷���ťID*/
			drButtonId=ShortFromChar(&inFrameContent[*buffIndex]);
			gDRButtonDataStruBuff[drBtnCycle].DRButtonId=drButtonId;
			*buffIndex=*buffIndex+2U;

			/*�����۷���ť��Ӧ�г�ID*/
			SetDRButtonOfTrainId(drButtonId,ShortFromChar(&inFrameContent[*buffIndex]));
			*buffIndex=*buffIndex+2U;

			/*�����۷���ť��ǰ״̬*/
			SetDRButtonStatus(drButtonId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡����DR�������۷���ť��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetDRButtonInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S drBtnCycle=DEFAULT_ZERO;
	UINT16_S drBtnId=DEFAULT_ZERO;         /*�����۷���ťID*/
	UINT16_S drBtnTrainId=DEFAULT_ZERO;    /*�����۷���ť���г�ID*/
	UINT16_S drBtnTotalNum=DEFAULT_ZERO;   /*�����۷���ť����*/
	
	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*��ȡ�����۷���ť����*/
        drBtnTotalNum=GetDRButtonSum();

        /*�����۷���ť����*/
        ShortToChar(drBtnTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (drBtnCycle=DEFAULT_ZERO;drBtnCycle<drBtnTotalNum;drBtnCycle++)
		{			
			/*�����۷���ťID*/	
			drBtnId=gDRButtonDataStruBuff[drBtnCycle].DRButtonId;  /*��ȡ�����۷���ťID*/
			ShortToChar(drBtnId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�����۷���ť��Ӧ�г�ID*/
			drBtnTrainId=GetDRButtonOfTrainId(drBtnId);
			ShortToChar(drBtnTrainId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�����۷���ť��ǰ״̬*/
			outFrameContent[*buffIndex]=GetDRButtonStatus(drBtnId);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡����DR�������۷�����Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetDRLampInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S drLampCycle=DEFAULT_ZERO;
	UINT16_S drLampId=DEFAULT_ZERO;   /*�����۷���ID*/

	if ((NULL != inFrameContent)&&(NULL != buffIndex))
	{
        /*�����۷���ť����*/
        gDRLampCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (drLampCycle=DEFAULT_ZERO;drLampCycle<gDRLampCurSum;drLampCycle++)
		{
			/*�����۷���ID*/
			drLampId=ShortFromChar(&inFrameContent[*buffIndex]);
			gDRLampDataStruBuff[drLampCycle].DRLampId=drLampId;
			*buffIndex=*buffIndex+2U;

			/*�����۷��ƶ�Ӧ�г�ID*/
			SetDRLampOfTrainId(drLampId,ShortFromChar(&inFrameContent[*buffIndex]));
			*buffIndex=*buffIndex+2U;

			/*�����۷��ƿ�������*/
			SetDRLampCommand(drLampId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡����DR�������۷�����Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetDRLampInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S drLampCycle=DEFAULT_ZERO;
	UINT16_S drLampId=DEFAULT_ZERO;        /*�����۷���ID*/
	UINT16_S drLampTrainId=DEFAULT_ZERO;   /*�����۷������г�ID*/
	UINT16_S drLampTotalNum=DEFAULT_ZERO;  /*�����۷�������*/

	if ((NULL != outFrameContent)&&(NULL != buffIndex))
	{	
        /*��ȡ�����۷�������*/
        drLampTotalNum=GetDRButtonSum();

        /*�����۷�������*/
        ShortToChar(drLampTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex + 2U;

		for (drLampCycle=DEFAULT_ZERO;drLampCycle<drLampTotalNum;drLampCycle++)
		{
			/*�����۷���ID*/
			drLampId=gDRLampDataStruBuff[drLampCycle].DRLampId;  /*��ȡ�����۷���ťID*/
			ShortToChar(drLampId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�����۷��ƶ�Ӧ�г�ID*/
			drLampTrainId=GetDRLampOfTrainId(drLampId);
			ShortToChar(drLampTrainId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�����۷��ƿ�������*/
			outFrameContent[*buffIndex]=GetDRLampCommand(drLampId);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���еĽ���ͣ����ťESB��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetESBInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S esbCycle=DEFAULT_ZERO;
	UINT16_S esbId=DEFAULT_ZERO;   /*����ͣ����ťID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*����ͣ����ť����*/
        gEsbCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (esbCycle=DEFAULT_ZERO;esbCycle<gEsbCurSum;esbCycle++)
		{
			/*����ͣ����ťID*/
			esbId=ShortFromChar(&inFrameContent[*buffIndex]);
			gEsbDataStruBuff[esbCycle].EsbId=esbId;
			*buffIndex=*buffIndex+2U;

			/*����ͣ����ť״̬*/
			SetEsbStatus(esbId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�ESB��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetESBInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S esbCycle=DEFAULT_ZERO;
	UINT16_S esbId=DEFAULT_ZERO;   /*����ͣ����ťID*/
	UINT16_S esbTotalNum=DEFAULT_ZERO;  /*����ͣ����ť����*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*��ȡ����ͣ������*/
        esbTotalNum=GetEsbSum();

        /*����ͣ����ť������*/
        ShortToChar(esbTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (esbCycle=DEFAULT_ZERO;esbCycle<esbTotalNum;esbCycle++)
		{
			/*����ͣ����ťID*/
			esbId=gEsbDataStruBuff[esbCycle].EsbId;   /*��ȡ����ͣ����ťID*/
			ShortToChar(esbId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*����ͣ����ť��ǰ״̬*/
			outFrameContent[*buffIndex]=GetEsbStatus(esbId);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�������PSD��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetPSDInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S psdCycle=DEFAULT_ZERO;
	UINT16_S psdId=DEFAULT_ZERO;   /*������ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*����������*/
        gPsdCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (psdCycle=DEFAULT_ZERO;psdCycle<gPsdCurSum;psdCycle++)
		{
			/*������ID*/
			psdId=ShortFromChar(&inFrameContent[*buffIndex]);
			gPsdDataStruBuff[psdCycle].PsdId=psdId;
			*buffIndex=*buffIndex+2U;

			/*������״̬*/
			SetPsdStatus(psdId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�PSD��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetPSDInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S psdCycle=DEFAULT_ZERO;
	UINT16_S psdId=DEFAULT_ZERO;         /*������ID*/
	UINT16_S psdTotalNum=DEFAULT_ZERO;   /*�����ŵ�����*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*��ȡ����������*/
        psdTotalNum=GetPsdSum();

        /*����������*/
        ShortToChar(psdTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (psdCycle=DEFAULT_ZERO;psdCycle<psdTotalNum;psdCycle++)
		{
			/*������ID*/
			psdId=gPsdDataStruBuff[psdCycle].PsdId;/*��ȡ������ID*/
			ShortToChar(psdId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�����ŵ�ǰ״̬*/
			outFrameContent[*buffIndex]=GetPsdStatus(psdId);
			*buffIndex=*buffIndex+1U;

		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�LogicSection��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetLogicSectionInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S logicSectionCycle=DEFAULT_ZERO;
	UINT16_S logicSectionId=DEFAULT_ZERO;   /*�߼�����ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*�߼���������*/
        gLogicSectionCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (logicSectionCycle=DEFAULT_ZERO;logicSectionCycle<gLogicSectionCurSum;logicSectionCycle++)
		{
			/*�߼�����ID*/
			logicSectionId=ShortFromChar(&inFrameContent[*buffIndex]);
			gLogicSectionDataStruBuff[logicSectionCycle].LogicSectionId=logicSectionId;
			*buffIndex=*buffIndex+2U;

			/*�߼�����״̬*/
			SetLogicSectionOccStatus(logicSectionId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�LogicSection��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetLogicSectionInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S logicSectionCycle=DEFAULT_ZERO;
	UINT16_S logicSectionId=DEFAULT_ZERO;         /*�߼�����ID*/
	UINT16_S logicSectionTotalNum=DEFAULT_ZERO;   /*�߼����ε�����*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*��ȡ�߼���������*/
        logicSectionTotalNum=GetLogicSectionSum();

        /*�߼���������*/
        ShortToChar(logicSectionTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (logicSectionCycle=DEFAULT_ZERO;logicSectionCycle<logicSectionTotalNum;logicSectionCycle++)
		{
			/*�߼�����ID*/
			logicSectionId=gLogicSectionDataStruBuff[logicSectionCycle].LogicSectionId;   /*��ȡ�߼�����ID*/
			ShortToChar(logicSectionId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�߼����ε�ǰ״̬*/
			outFrameContent[*buffIndex]=GetLogicSectionOccStatus(logicSectionId);
			*buffIndex=*buffIndex+1U;

		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Overlap��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetOverlapInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S overlapCycle=DEFAULT_ZERO;
	UINT16_S overlapId=DEFAULT_ZERO;   /*��������ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*������������*/
        gOverlapCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (overlapCycle=DEFAULT_ZERO;overlapCycle<gOverlapCurSum;overlapCycle++)
		{
			/*��������ID*/
			overlapId=ShortFromChar(&inFrameContent[*buffIndex]);
			gOverlapDataStruBuff[overlapCycle].OverlapId=overlapId;
			*buffIndex=*buffIndex+2U;

			/*��������״̬*/
			SetOverlapStatus(overlapId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Overlap��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetOverlapInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S overlapCycle=DEFAULT_ZERO;
	UINT16_S overlapId=DEFAULT_ZERO;         /*��������ID*/
	UINT16_S overlapTotalNum=DEFAULT_ZERO;   /*�������ε�����*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{
        /*��ȡ������������*/
        overlapTotalNum=GetOverlapSum();

        /*������������*/
        ShortToChar(overlapTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (overlapCycle=DEFAULT_ZERO;overlapCycle<overlapTotalNum;overlapCycle++)
		{			
			/*��������ID*/
			overlapId=gOverlapDataStruBuff[overlapCycle].OverlapId;/*��ȡ��������ID*/
			ShortToChar(overlapId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�������ε�ǰ״̬*/
			outFrameContent[*buffIndex]=GetOverlapStatus(overlapId);
			*buffIndex=*buffIndex+1U;

		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Route��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetRouteInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S routeCycle=DEFAULT_ZERO;
	UINT16_S routeId=DEFAULT_ZERO;   /*��·ID*/

	if ((NULL != inFrameContent)&&(NULL != buffIndex))
	{
        /*��·����*/
        gRouteCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (routeCycle=DEFAULT_ZERO;routeCycle<gRouteCurSum;routeCycle++)
		{
			/*��·ID*/
			routeId=ShortFromChar(&inFrameContent[*buffIndex]);
			gRouteStatusDataStruBuff[routeCycle].RouteId=routeId;
			*buffIndex=*buffIndex+2U;

			/*��·״̬*/
			SetRouteStatus(routeId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Route��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetRouteInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S routeCycle=DEFAULT_ZERO;
	UINT16_S routeId=DEFAULT_ZERO;         /*��·ID*/
	UINT16_S routeTotalNum=DEFAULT_ZERO;   /*��·������*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*��ȡ��·����*/
        routeTotalNum=GetRouteSum();

        /*��·����*/
        ShortToChar(routeTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (routeCycle=DEFAULT_ZERO;routeCycle<routeTotalNum;routeCycle++)
		{
			/*��·ID*/
			routeId=gRouteStatusDataStruBuff[routeCycle].RouteId;     /*��ȡ��·ID*/
			ShortToChar(routeId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*��·��ǰ״̬*/
			outFrameContent[*buffIndex]=GetRouteStatus(routeId);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Signal��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetSignalInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S signalCycle=DEFAULT_ZERO;
	UINT16_S signalId=DEFAULT_ZERO;   /*�źŻ�ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*�źŻ�����*/
        gSignalCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (signalCycle=DEFAULT_ZERO;signalCycle<gSignalCurSum;signalCycle++)
		{
			/*�źŻ�ID*/
			signalId=ShortFromChar(&inFrameContent[*buffIndex]);
			gSignalDataStruBuff[signalCycle].SignalId=signalId;
			*buffIndex=*buffIndex+2U;

			/*�źŻ���ǰ״̬*/
			SetSignalStatus(signalId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*�źŻ�����״̬*/
			SetSignalLightOffStatus(signalId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*�źŻ���ѹ״̬*/
			SetSignalCrossStatus(signalId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Signal��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetSignalInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S signalCycle=DEFAULT_ZERO;
	UINT16_S signalId=DEFAULT_ZERO;         /*�źŻ�ID*/
	UINT16_S signalTotalNum=DEFAULT_ZERO;   /*�źŻ�������*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*��ȡ�źŻ�����*/
        signalTotalNum=GetSignalSum();

        /*�źŻ�����*/
        ShortToChar(signalTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (signalCycle=DEFAULT_ZERO;signalCycle<signalTotalNum;signalCycle++)
		{
			/*�źŻ�ID*/
			signalId=gSignalDataStruBuff[signalCycle].SignalId;   /*��ȡ�źŻ�ID*/
			ShortToChar(signalId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�źŻ���ǰ״̬*/
			outFrameContent[*buffIndex]=GetSignalStatus(signalId);
			*buffIndex=*buffIndex+1U;

			/*�źŻ�����״̬*/
			outFrameContent[*buffIndex]=GetSignalLightOffStatus(signalId);
			*buffIndex=*buffIndex+1U;

			/*�źŻ���ѹ״̬*/
			outFrameContent[*buffIndex]=GetSignalCrossStatus(signalId);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Switch��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetSwitchInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S switchCycle=DEFAULT_ZERO;
	UINT16_S switchId=DEFAULT_ZERO;   /*����ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*��������*/
        gSwitchCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (switchCycle=DEFAULT_ZERO;switchCycle<gSwitchCurSum;switchCycle++)
		{
			/*����ID*/
			switchId=ShortFromChar(&inFrameContent[*buffIndex]);
			gSwitchStatusDataStruBuff[switchCycle].SwitchId=switchId;
			*buffIndex=*buffIndex+2U;

			/*����ǰ״̬*/
			SetSwitchPosStatus(switchId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*��������״̬*/
			SetSwitchLock(switchId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Switch��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetSwitchInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S switchCycle=DEFAULT_ZERO;
	UINT16_S switchId=DEFAULT_ZERO;         /*����ID*/
	UINT16_S switchTotalNum=DEFAULT_ZERO;   /*���������*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*��ȡ��������*/
        switchTotalNum=GetSwitchSum();

        /*��������*/
        ShortToChar(switchTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (switchCycle=DEFAULT_ZERO;switchCycle<switchTotalNum;switchCycle++)
		{
			/*����ID*/
			switchId=gSwitchStatusDataStruBuff[switchCycle].SwitchId;/*��ȡ����ID*/
			ShortToChar(switchId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*����ǰ״̬*/
			outFrameContent[*buffIndex]=GetSwitchPosStatus(switchId);
			*buffIndex=*buffIndex+1U;

			/*��������״̬*/
			outFrameContent[*buffIndex]=GetSwitchLock(switchId);
			*buffIndex=*buffIndex+1U;			
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Tsr��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetTsrInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S tsrCycle=DEFAULT_ZERO;
	UINT8_S singleCycle=DEFAULT_ZERO;
	UINT8_S singleTsrLogicSecCycle=DEFAULT_ZERO;
	UINT8_S tsrNum=DEFAULT_ZERO;    /*��ʱ��������*/	
	UINT16_S belongZcId=DEFAULT_ZERO;         /*����ZCID*/
    UINT8_S sectionNum=DEFAULT_ZERO;    /*�����߼���������*/
	UINT16_S sectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX]={DEFAULT_ZERO}; /*�����߼�����ID����*/
	UINT8_S zcIndexInTsr = DEFAULT_ZERO;
	UINT8_S getOfFlag = DEFAULT_ZERO;
    UINT16_S innerTsrOfZcCurSum=DEFAULT_ZERO;
	
	/*��ʼ���߼�����ID����*/
	MemorySet(sectionIdBuff,SINGLE_TSR_SECTION_SUM_MAX,DEFAULT_ZERO,SINGLE_TSR_SECTION_SUM_MAX);

	if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
	{
        innerTsrOfZcCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (tsrCycle=DEFAULT_ZERO;tsrCycle<innerTsrOfZcCurSum;tsrCycle++)
		{
			/*��ʱ��������ZCID*/
			belongZcId=ShortFromChar(&inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�����±�*/
			AplyTsrIndexOfZcId(belongZcId);

			/*��ȡ�洢��Tsr�ṹ�и�ZCid��Ӧ�±�*/
			zcIndexInTsr = GeZcIdOfTsrBufIndex(belongZcId);

			if (zcIndexInTsr < TSR_BUFF_SUM_MAX)
			{
				gTsrDataStruBuff[zcIndexInTsr].BelongZcId=belongZcId;
			
				/*��ʱ��������*/
				tsrNum=inFrameContent[*buffIndex];
				SetZcIdOfTsrNum(zcIndexInTsr,tsrNum);
				*buffIndex=*buffIndex+1U;

				/*��ʱ����*/
				for (singleCycle=DEFAULT_ZERO;singleCycle<tsrNum;singleCycle++)
				{
					/*�ٶ�*/
					SetSingleTsrDataOfSpeed(zcIndexInTsr,((UINT16_S)singleCycle),((UINT16_S)inFrameContent[*buffIndex]));
					*buffIndex=*buffIndex+1U;

					/*�����߼���������*/
					sectionNum=inFrameContent[*buffIndex];
					*buffIndex=*buffIndex+1U;

					/*�����߼�����ID*/
					for(singleTsrLogicSecCycle=DEFAULT_ZERO;singleTsrLogicSecCycle<sectionNum;singleTsrLogicSecCycle++)
					{
						sectionIdBuff[singleTsrLogicSecCycle]=ShortFromChar(&inFrameContent[*buffIndex]);
						*buffIndex=*buffIndex+2U;
					}

					SetSingleTsrDataOfSectionInfo(zcIndexInTsr,singleCycle,sectionNum,sectionIdBuff);
				}
			}
			else
			{
				rtnValue = RETURN_ERROR;
				getOfFlag = FLAG_SET;
				break;
			}
		}

		if ((DEFAULT_ZERO == getOfFlag))
		{
			rtnValue = RETURN_SUCCESS;
		} 
		else
		{
           rtnValue = RETURN_ERROR;
		}
	} 
	else
	{
		rtnValue = RETURN_ERROR;
	}

	return rtnValue;
}
/*
* ���������� ����֡���е�Tsr��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetTsrInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;  /*����ֵ*/
	UINT8_S tsrCyle=DEFAULT_ZERO;
	UINT8_S singleTsrCycle=DEFAULT_ZERO; 
	UINT8_S singleTsrLogicSecCycle=DEFAULT_ZERO;
	UINT8_S  singleTsrDataOfSectionNum=DEFAULT_ZERO;/*����Tsr���߼����θ���*/
	UINT16_S belongZcId=DEFAULT_ZERO;         /*����ZCID*/
	UINT16_S tsrTotalNum=DEFAULT_ZERO;        /*��ʱ��������*/ 
	UINT16_S sectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX]={DEFAULT_ZERO}; /*�߼�����ID����*/
	UINT8_S zcIdOfTsrNum=DEFAULT_ZERO;  /*��ʱ���ٵ�����*/

	/*��ʼ���߼�����ID����*/
	MemorySet(sectionIdBuff,SINGLE_TSR_SECTION_SUM_MAX,DEFAULT_ZERO,SINGLE_TSR_SECTION_SUM_MAX);

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*��ȡ��ʱ���ٵ�����*/
        tsrTotalNum=GetTsrOfZcSum();  

        /*��ʱ���ٵ�����*/
        ShortToChar(tsrTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (tsrCyle=DEFAULT_ZERO;tsrCyle<tsrTotalNum;tsrCyle++)
		{
			/*����ZCID*/
			belongZcId=GeTsrOfBelongZcId((UINT16_S)tsrCyle);   /*��ȡ������ZCID*/			
			ShortToChar(belongZcId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*��ʱ��������*/
			zcIdOfTsrNum=GetZcIdOfTsrNum(belongZcId);
			outFrameContent[*buffIndex]=zcIdOfTsrNum;
			*buffIndex=*buffIndex+1U;

			for(singleTsrCycle=DEFAULT_ZERO;singleTsrCycle<zcIdOfTsrNum;singleTsrCycle++)
			{
				/*������ʱ���ٵ��ٶ�*/
				outFrameContent[*buffIndex]=GetSingleTsrDataOfSpeed(belongZcId,((UINT16_S)singleTsrCycle));
				*buffIndex=*buffIndex+1U;

				/*������ʱ���ٵİ����߼���������*/
				singleTsrDataOfSectionNum=GetSingleTsrDataOfSectionNum(belongZcId,((UINT16_S)singleTsrCycle));
				outFrameContent[*buffIndex]=singleTsrDataOfSectionNum;
				*buffIndex=*buffIndex+1U;

				/*������ʱ���ٵ��߼�����ID*/
				if (RETURN_SUCCESS == GetSingleTsrDataOfSectionBuff(belongZcId,((UINT16_S)singleTsrCycle),((UINT8_S)(SINGLE_TSR_SECTION_SUM_MAX)),sectionIdBuff))
				{
					for(singleTsrLogicSecCycle=DEFAULT_ZERO;singleTsrLogicSecCycle<singleTsrDataOfSectionNum;singleTsrLogicSecCycle++)
					{
						ShortToChar(sectionIdBuff[singleTsrLogicSecCycle],&outFrameContent[*buffIndex]);
						*buffIndex=*buffIndex+2U;
					}
				} 
				else
				{
                    /*������*/
				}
				
			}
						
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Train��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetTrainInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR; 	
	UINT8_S trainCycle=DEFAULT_ZERO;
	UINT8_S trainSectionCycle=DEFAULT_ZERO;
	UINT16_S trainId=DEFAULT_ZERO;    /*�г�ID*/
    UINT8_S sectionNum=DEFAULT_ZERO;  /*������ռѹ�߼���������*/
	UINT16_S sectionId[SIZE_MAX_SECTION_OF_TRAIN]={DEFAULT_ZERO};  /*�߼�����ID*/
	TrainSafeLocStruct trainSafeLoc;    /*��ȫλ��*/
	TrainSafeLocStruct trainUnSafeLoc;  /*�ǰ�ȫλ��*/
	UINT16_S trainIndex = DEFAULT_ZERO;
	UINT8_S getFlag = DEFAULT_ZERO;
    UINT16_S innerTrainCurSum=DEFAULT_ZERO;   /*����ֲ��г�����*/

	/*��ʼ��*/
	MemorySet(sectionId,SIZE_MAX_SECTION_OF_TRAIN,DEFAULT_ZERO,SIZE_MAX_SECTION_OF_TRAIN);
	gTrainCurSum = 0U;
	
	/*printf("get��buffIndex=%d,TrainCurSum=%d\n",*buffIndex,innerTrainCurSum);*/	
	if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
	{
        /*�г�����*/
        innerTrainCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (trainCycle=DEFAULT_ZERO;trainCycle<innerTrainCurSum;trainCycle++)
		{
			/*�г�ID*/
			trainId=ShortFromChar(&inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;
			/* printf("get��buffIndex=%d,trainId=%d\n",*buffIndex,trainId); */
			
			/*�����±�*/
			trainIndex = AllotTrainIndex(trainId);
            /* printf("APPLY: trainIndex=%d\n",trainIndex); */
			if (SIZE_MAX_CONTROLE_TRAIN != trainIndex)
			{
				/*����г�������������Ϣ*/
				gLocalTrainIndexBuff[trainId] = (UINT8_S)(trainIndex);
				gTrainCurSum++;
				
				/*��дTrainId*/
			    gTrainStatusDataStruBuff[trainIndex].TrainID=trainId;
			
				/*�ܿ�ZCID*/
				SetTrainControlZc(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*�г�����*/
				SetTrainCycle(trainId,LongFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+4U;

				/*�г�����*/
				SetTrainType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*ǰ�˱��*/
				SetTrainSuspectHead(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*��˱��*/
				SetTrainSuspectTail(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*��ȫ��ͷռѹ��������ID*/
				SetTrainTrainHeadAC(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*��ȫ��βռѹ��������ID*/
				SetTrainTrainTailAC(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*�ǰ�ȫ��ͷռѹ��������ID*/
				SetTrainUnsafeTrainHeadAC(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*�ǰ�ȫ��βռѹ��������ID*/
				SetTrainUnsafeTrainTailAC(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*ǰ�������źŻ�ID*/
				SetTrainFrontSignal(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*�źŻ��������*/
				SetTrainSignalProtection(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*�г�ͨ����ʱʱ��*/
				SetTrainPrtclDelay(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*�г�״̬��Ϣ*/
				SetTrainStatus(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*�г���������*/
				SetTrainInType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*����г�����*/
				SetTrainOutType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*����ZC������Ϣ*/
				SetTrainHandoverInType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*����ZC�����Ϣ*/
				SetTrainHandoverOutType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*��ȫλ��*/
				trainSafeLoc.TrainHeadLink=ShortFromChar(&inFrameContent[*buffIndex]);  /*��ͷlink*/
				*buffIndex=*buffIndex+2U;
				trainSafeLoc.TrainHeadOffset=LongFromChar(&inFrameContent[*buffIndex]);  /*��ͷoffset*/
				*buffIndex=*buffIndex+4U;
				trainSafeLoc.TrainTailLink=ShortFromChar(&inFrameContent[*buffIndex]);  /*��βlink*/
				*buffIndex=*buffIndex+2U;
				trainSafeLoc.TrainTailOffset=LongFromChar(&inFrameContent[*buffIndex]);  /*��βoffset*/
				*buffIndex=*buffIndex+4U;
				SetTrainSafeLoc(trainId,&trainSafeLoc);

				/*�ǰ�ȫλ��*/
				trainUnSafeLoc.TrainHeadLink=ShortFromChar(&inFrameContent[*buffIndex]);  /*��ͷlink*/
				*buffIndex=*buffIndex+2U;
				trainUnSafeLoc.TrainHeadOffset=LongFromChar(&inFrameContent[*buffIndex]);  /*��ͷoffset*/
				*buffIndex=*buffIndex+4U;
				trainUnSafeLoc.TrainTailLink=ShortFromChar(&inFrameContent[*buffIndex]);  /*��βlink*/
				*buffIndex=*buffIndex+2U;
				trainUnSafeLoc.TrainTailOffset=LongFromChar(&inFrameContent[*buffIndex]);  /*��βoffset*/
				*buffIndex=*buffIndex+4U;
				SetTrainUnSafeLoc(trainId,trainUnSafeLoc);

				/*�������з���*/
				SetTrainUnsafeDirection(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*ʵ�����з���*/
				SetTrainRealDirection(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*��ʻģʽ*/
				SetTrainMode(trainId,inFrameContent[*buffIndex]);
				
				/*printf("get:TrainMode=%d\n",inFrameContent[*buffIndex]);*/
				
				*buffIndex=*buffIndex+1U;

				/*���м���*/
				SetTrainLevel(trainId,inFrameContent[*buffIndex]);
				
				/*printf("get:TrainLevel=%d\n",inFrameContent[*buffIndex]);*/
				
				
				*buffIndex=*buffIndex+1U;

				/*ʵ���ٶ�*/
				SetTrainSpeed(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*ͣ����Ϣ*/
				SetTrainStopArea(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*�����Ա��*/
				SetTrainIntegrity(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*����ͣ�����*/
				SetTrainEmergency(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*��ȷ�����*/
				SetTrainError(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*�л���·ID*/
				SetTrainChangeLineId(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*������ռѹ�߼���������*/
				sectionNum=inFrameContent[*buffIndex];
				*buffIndex=*buffIndex+1U;

				/*������ռѹ�߼�����ID*/
				for (trainSectionCycle=DEFAULT_ZERO;trainSectionCycle<sectionNum;trainSectionCycle++)
				{
					sectionId[trainSectionCycle]=ShortFromChar(&inFrameContent[*buffIndex]);
					*buffIndex=*buffIndex+2U;
				}

				SetTrainPreSectionId(trainId,sectionId,sectionNum);
			} 
			else
			{
				rtnValue = RETURN_ERROR;
				getFlag = FLAG_SET;
				break;
			}
		}
		
		if(innerTrainCurSum==GetTrainCurSum())
		{
			if (DEFAULT_ZERO == getFlag)
			{
				rtnValue = RETURN_SUCCESS;
			} 
			else
			{
				rtnValue=RETURN_ERROR;
			}
		}
		else
		{
			rtnValue=RETURN_ERROR;
		}
		
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�Train��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetTrainInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S trainCycle=DEFAULT_ZERO;
	UINT8_S trainPreSecCycle=DEFAULT_ZERO;
	UINT8_S trainTotalNum=DEFAULT_ZERO;        /*�г�������*/
	UINT16_S trainId=DEFAULT_ZERO;             /*�г�ID*/
	UINT8_S trainPreSectionNum=DEFAULT_ZERO;   /*������ռѹ�߼���������*/
	UINT16_S trainSectionId[SIZE_MAX_SECTION_OF_TRAIN]={DEFAULT_ZERO}; /*������ռѹ�߼�����ID*/
	TrainSafeLocStruct trainSafeLoc;         /*�г���ȫλ�ýṹ��*/
	TrainSafeLocStruct trainUnSafeLoc;       /*�г��ǰ�ȫλ�ýṹ��*/
	
	/*��ʼ���г�ռѹ�߼��������顢�г���ȫλ�á��г��ǰ�ȫλ��*/
	MemorySet(trainSectionId,SIZE_MAX_SECTION_OF_TRAIN,DEFAULT_ZERO,SIZE_MAX_SECTION_OF_TRAIN);
	MemorySet(&trainSafeLoc,sizeof(TrainSafeLocStruct),DEFAULT_ZERO,sizeof(TrainSafeLocStruct));
	MemorySet(&trainUnSafeLoc,sizeof(TrainSafeLocStruct),DEFAULT_ZERO,sizeof(TrainSafeLocStruct));

	/*printf("set��buffIndex=%d,TrainCurSum=%d\n",*buffIndex,trainTotalNum);*/
	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*��ȡ�г�����*/
        trainTotalNum=GetTrainCurSum();  

        /*printf("set��TrainCurSum=%d\n",trainTotalNum);*/

        /*�г�����*/
        ShortToChar(((UINT16_S)trainTotalNum),&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (trainCycle=DEFAULT_ZERO;trainCycle<trainTotalNum;trainCycle++)
		{
			/*�г�ID*/
			trainId=GetTrainIdOfIndex(trainCycle);
			ShortToChar(trainId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*printf("set��buffIndex=%d,TrainID=%d\n",*buffIndex,trainId);*/

			/*�ܿ�ZCID*/
			ShortToChar( GetTrainControlZc(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�г�����*/
			LongToChar(GetTrainCycle(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+4U;

			/*�г�����*/
			outFrameContent[*buffIndex]=GetTrainType(trainId);
			*buffIndex=*buffIndex+1U;

			/*ǰ�˱��*/
			outFrameContent[*buffIndex]=GetTrainSuspectHead(trainId);
			*buffIndex=*buffIndex+1U;

			/*��˱��*/
			outFrameContent[*buffIndex]=GetTrainSuspectTail(trainId);
			*buffIndex=*buffIndex+1U;

			/*��ȫ��ͷռѹ��������ID*/
			ShortToChar(GetTrainTrainHeadAC(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*��ȫ��βռѹ��������ID*/
			ShortToChar(GetTrainTrainTailAC(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�ǰ�ȫ��ͷռѹ��������ID*/
			ShortToChar(GetTrainUnsafeTrainHeadAC(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�ǰ�ȫ��βռѹ��������ID*/
			ShortToChar(GetTrainUnsafeTrainTailAC(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*ǰ�������źŻ�ID*/
			ShortToChar(GetTrainFrontSignal(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�źŻ��������*/
			outFrameContent[*buffIndex]=GetTrainSignalProtection(trainId);
			*buffIndex=*buffIndex+1U;

			/*�г�ͨ����ʱʱ��*/
			outFrameContent[*buffIndex]=GetTrainPrtclDelay(trainId);
			*buffIndex=*buffIndex+1U;

			/*�г�״̬��Ϣ*/
			outFrameContent[*buffIndex]=GetTrainStatus(trainId);
			*buffIndex=*buffIndex+1U;

			/*�г���������*/
			outFrameContent[*buffIndex]=GetTrainInType(trainId);
			*buffIndex=*buffIndex+1U;

			/*����г�����*/
			outFrameContent[*buffIndex]=GetTrainOutType(trainId);
			*buffIndex=*buffIndex+1U;

			/*����ZC������Ϣ*/
			outFrameContent[*buffIndex]=GetTrainHandoverInType(trainId);
			*buffIndex=*buffIndex+1U;

			/*����ZC�����Ϣ*/
			outFrameContent[*buffIndex]=GetTrainHandoverOutType(trainId);
			*buffIndex=*buffIndex+1U;

			/*��ȫλ��*/
			if (RETURN_SUCCESS==GetTrainSafeLoc(trainId,&trainSafeLoc))
			{
				/*�г���ȫλ�ó�ͷ����Link*/
				ShortToChar(trainSafeLoc.TrainHeadLink,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*�г���ȫλ�ó�ͷ����offset */
				LongToChar(trainSafeLoc.TrainHeadOffset,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;

				/*�г���ȫλ�ó�β����Link*/
				ShortToChar(trainSafeLoc.TrainTailLink,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*�г���ȫλ�ó�β����offset*/
				LongToChar(trainSafeLoc.TrainTailOffset,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;
			} 
			else
			{
                /*������*/
			}
			
			/*�ǰ�ȫλ��*/
			if (RETURN_SUCCESS==GetTrainUnSafeLoc(trainId,&trainUnSafeLoc))
			{
				/*�г��ǰ�ȫλ�ó�ͷ����Link*/
				ShortToChar(trainUnSafeLoc.TrainHeadLink,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*�г��ǰ�ȫλ�ó�ͷ����offset*/
				LongToChar(trainUnSafeLoc.TrainHeadOffset,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;

				/*�г��ǰ�ȫλ�ó�β����Link*/
				ShortToChar(trainUnSafeLoc.TrainTailLink,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*�г��ǰ�ȫλ�ó�β����offset*/
				LongToChar(trainUnSafeLoc.TrainTailOffset,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;
			}
			else
			{
                /*������*/
			}
			
			/*�������з���*/
			outFrameContent[*buffIndex]=GetTrainUnsafeDirection(trainId);
			*buffIndex=*buffIndex+1U;

			/*ʵ�����з���*/
			outFrameContent[*buffIndex]=GetTrainRealDirection(trainId);
			*buffIndex=*buffIndex+1U;

			/*��ʻģʽ*/
			outFrameContent[*buffIndex]=GetTrainMode(trainId);
			*buffIndex=*buffIndex+1U;

			/*printf("set��TrainMode=%d\n",GetTrainMode(trainId));*/

			/*���м���*/
			outFrameContent[*buffIndex]=GetTrainLevel(trainId);
			*buffIndex=*buffIndex+1U;

			/*printf("set��TrainLevel=%d\n",GetTrainLevel(trainId));*/

			/*ʵ���ٶ�*/
			ShortToChar(GetTrainSpeed(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*ͣ����Ϣ*/
			outFrameContent[*buffIndex]=GetTrainStopArea(trainId);
			*buffIndex=*buffIndex+1U;

			/*�����Ա��*/
			outFrameContent[*buffIndex]=GetTrainIntegrity(trainId);
			*buffIndex=*buffIndex+1U;

			/*����ͣ�����*/
			outFrameContent[*buffIndex]=GetTrainEmergency(trainId);
			*buffIndex=*buffIndex+1U;

			/*��ȷ�����*/
			ShortToChar(GetTrainError(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*�л���·ID*/
			ShortToChar(GetTrainChangeLineId(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*������ռѹ�߼���������*/
			trainPreSectionNum=GetTrainPreSectionNum(trainId);
			outFrameContent[*buffIndex]=trainPreSectionNum;			
			*buffIndex=*buffIndex+1U;

			/*������ռѹ�߼�����ID*/
			if (RETURN_SUCCESS==GetTrainPreSectionId(trainId,&trainSectionId[DEFAULT_ZERO]))
			{
				for (trainPreSecCycle=DEFAULT_ZERO;trainPreSecCycle<trainPreSectionNum;trainPreSecCycle++)
				{
					ShortToChar(trainSectionId[trainPreSecCycle],&outFrameContent[*buffIndex]);		
					*buffIndex=*buffIndex+2U;
				}
			} 
			else
			{
                /*������*/
			}
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}
	
	return rtnValue;
}

/*
* ���������� ����֡���е�CommTarget��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetCommTargetInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S commTargetCycle=DEFAULT_ZERO;
	UINT8_S commTargetType=DEFAULT_ZERO;  /*ͨѶĿ������*/
	UINT8_S singleCommTargetCycle=DEFAULT_ZERO; 
	UINT8_S singleCommTargetTypeSum=DEFAULT_ZERO;  /*�豸ͨ������*/
	UINT16_S commTargetId=DEFAULT_ZERO;  /*ͨ��ID*/

	if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
	{
        /*�����豸��������*/
        gCommTargetTypeCurSum=inFrameContent[*buffIndex];
        *buffIndex=*buffIndex+1U;

		for (commTargetCycle=DEFAULT_ZERO;commTargetCycle<gCommTargetTypeCurSum;commTargetCycle++)  
		{
			/*�豸����*/
			commTargetType=inFrameContent[*buffIndex];
			gCommTargetDataStruBuff[commTargetCycle].CommTargetType=commTargetType;
			*buffIndex=*buffIndex+1U;
					
			/*�豸ͨ������*/
			singleCommTargetTypeSum=inFrameContent[*buffIndex];
			gCommTargetDataStruBuff[commTargetType].CommTargetNum=singleCommTargetTypeSum;
			*buffIndex=*buffIndex+1U;

			/*�豸ͨ��������*/
			MemoryCpy(&gCommTargetDataStruBuff[commTargetCycle].CommTargetIdBuff[DEFAULT_ZERO],COMM_TARGET_ID_MAX,&inFrameContent[*buffIndex],COMM_TARGET_ID_MAX);
			*buffIndex=*buffIndex+COMM_TARGET_ID_MAX;
			
			/*ͨ�Ŷ���*/
			for (singleCommTargetCycle=DEFAULT_ZERO;singleCommTargetCycle<singleCommTargetTypeSum;singleCommTargetCycle++)
			{
				/*ͨ��ID*/
			    commTargetId=ShortFromChar(&inFrameContent[*buffIndex]);  
				gCommTargetDataStruBuff[commTargetCycle].SingleCommTargeStru[singleCommTargetCycle].CommTargetId=commTargetId;
				*buffIndex=*buffIndex+2U;

				/*ͨ��״̬*/
				SetCommTargetStatus(commTargetType,commTargetId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*ͨ���ۼ�λ*/
				SetCommTargetCycle(commTargetType,commTargetId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*ͨ�Ŷ����������ں�*/
				SetCommTargetCycleNum(commTargetType,commTargetId,LongFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+4U;
			}
		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}
/*
* ���������� ����֡���е�ͨѶ�豸��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetCommTargetInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S commTargetTotalNum=DEFAULT_ZERO; /*ͨѶĿ������*/
	UINT8_S commTargetCycle=DEFAULT_ZERO;
	UINT8_S commTargetType=DEFAULT_ZERO;  /*ͨѶĿ������*/
	UINT8_S singleCommTargetCycle=DEFAULT_ZERO;  
	UINT8_S singleCommTargetTypeSum=DEFAULT_ZERO;  /*�豸ͨ������*/
	UINT16_S commTargetId=DEFAULT_ZERO;  /*ͨ��ID*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{
        /*��ȡͨ��Ŀ����������*/
        commTargetTotalNum=GetCommTargetTypeSum();

        outFrameContent[*buffIndex]=commTargetTotalNum;
        *buffIndex=*buffIndex+1U;

		for (commTargetCycle=DEFAULT_ZERO;commTargetCycle<commTargetTotalNum;commTargetCycle++)
		{
			/*�豸����*/
			commTargetType=gCommTargetDataStruBuff[commTargetCycle].CommTargetType;
			outFrameContent[*buffIndex]=commTargetType;
			*buffIndex=*buffIndex+1U;

			/*�豸ͨ������*/
			singleCommTargetTypeSum=GetSingleCommTargetTypeSum(commTargetType);
			outFrameContent[*buffIndex]=singleCommTargetTypeSum;
			*buffIndex=*buffIndex+1U;

			/*����Ĵ�С*/
			MemoryCpy(&outFrameContent[*buffIndex],COMM_TARGET_ID_MAX,&gCommTargetDataStruBuff[commTargetCycle].CommTargetIdBuff[DEFAULT_ZERO],COMM_TARGET_ID_MAX);
			*buffIndex=*buffIndex+COMM_TARGET_ID_MAX;

			for (singleCommTargetCycle=DEFAULT_ZERO;singleCommTargetCycle<singleCommTargetTypeSum;singleCommTargetCycle++)
			{
				/*ͨ��ID*/
				commTargetId=gCommTargetDataStruBuff[commTargetCycle].SingleCommTargeStru[singleCommTargetCycle].CommTargetId;
				ShortToChar(commTargetId,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;
			
				/*ͨ��״̬*/
				outFrameContent[*buffIndex]=GetCommTargetStatus(commTargetType,commTargetId);
				*buffIndex=*buffIndex+1U;

				/*ͨ���ۼ�λ*/
				ShortToChar(GetCommTargetCycle(commTargetType,commTargetId),&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*ͨ�Ŷ����������ں�*/
				LongToChar(GetCommTargetCycleNum(commTargetType, commTargetId),&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;
			}

		}

		rtnValue=RETURN_SUCCESS;
	} 
	else
	{
		rtnValue=RETURN_ERROR;
	}

	return rtnValue;
}

/*
* ���������� ����֡���е�NTPУʱ�ɹ���־��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetNTPTimeFlagInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S ntpTimeFlag = DEFAULT_ZERO;

    if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
    {
        /*����NTPУʱ�ɹ���־��Ϣ*/
        ntpTimeFlag = inFrameContent[*buffIndex];
        *buffIndex = *buffIndex+1U;

        if (DEFAULT_ZERO < ntpTimeFlag)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue=RETURN_ERROR;
    }

	return rtnValue;
}

/*
* ���������� ����֡���е�NTPУʱ�ɹ���־��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetNTPTimeFlagInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S ntpTimeFlag = DEFAULT_ZERO;

    if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
    {
        /*��ȡNTPУʱ�ɹ���־��Ϣ*/
        ntpTimeFlag = GetNtpTimeSuccFlag();

        outFrameContent[*buffIndex] = ntpTimeFlag;
        *buffIndex = *buffIndex + 1U;

        if (DEFAULT_ZERO < ntpTimeFlag)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue=RETURN_ERROR;
    }
	
	
	return rtnValue;
}

/*
* ���������� ����֡���е�NTPУʱ����ʱ����Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetNTPLocalTimeInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue = RETURN_ERROR;
	UINT32_S localNtpTime = DEFAULT_ZERO;

    if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
    {
        /*����NTPУʱ�ɹ���־��Ϣ*/
        localNtpTime = LongFromChar(&inFrameContent[*buffIndex]);

        SetLocalNtpTime(localNtpTime);
        *buffIndex = *buffIndex + 4U;

        if (DEFAULT_ZERO < localNtpTime)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
	
	return rtnValue;
}

/*
* ���������� ����֡���е�NTPУʱ����ʱ����Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetNTPLocalTimeInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT32_S localNtpTime = DEFAULT_ZERO;

    if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
    {
        /*��ȡNTPУʱ�ɹ���־��Ϣ*/
        localNtpTime = GetLocalNtpTime();

        LongToChar(localNtpTime,&outFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        if (DEFAULT_ZERO < localNtpTime)
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue = RETURN_ERROR;
        }
    }
    else
    {
        rtnValue=RETURN_ERROR;
    }
	
	return rtnValue;
}

/*
* ���������� ����֡���е�NTPУʱ�ṹ��ʱ����Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetNTPStructTimeInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue = RETURN_ERROR;
	NTPTimeStruct ntpTimeStu;
	UINT32_S integer = DEFAULT_ZERO;                                    /*��������������*/
	UINT32_S fractional = DEFAULT_ZERO;                                 /*������С������*/

    if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
    {
        /*����ϵͳʱ�����һ�α��趨����µ�ʱ��*/
        integer = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        fractional = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        ntpTimeStu.Integer = integer;
        ntpTimeStu.Fractional = fractional;

        SetReferenceTimestamp(ntpTimeStu);

        /*���÷������յ����������뿪���صı���ʱ��*/
        integer = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        fractional = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        ntpTimeStu.Integer = integer;
        ntpTimeStu.Fractional = fractional;

        SetOriginateTimestamp(ntpTimeStu);

        /*����Ӧ�����뿪�������ķ�����ʱ��*/
        integer = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        fractional = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        ntpTimeStu.Integer = integer;
        ntpTimeStu.Fractional = fractional;

        SetReceiveTimestamp(ntpTimeStu);

        /*���������ĵ���������ķ�����ʱ��*/
        integer = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        fractional = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        ntpTimeStu.Integer = integer;
        ntpTimeStu.Fractional = fractional;

        SetTransmitTimestamp(ntpTimeStu);

        /*����ֵ*/
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
	
	return rtnValue;
	
}

/*
* ���������� ����֡���е�NTPУʱ�ṹ��ʱ����Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetNTPStructTimeInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue = RETURN_ERROR;
	UINT8_S rtnValue1 = RETURN_ERROR;
	UINT8_S rtnValue2 = RETURN_ERROR;
	UINT8_S rtnValue3 = RETURN_ERROR;
	UINT8_S rtnValue4 = RETURN_ERROR;
	NTPTimeStruct *ntpTimeStu = NULL;
	UINT32_S integer = DEFAULT_ZERO;                                    /*��������������*/
	UINT32_S fractional = DEFAULT_ZERO;                                 /*������С������*/

    if ((NULL != buffIndex) && (NULL != outFrameContent))
    {
        /*��ȡϵͳʱ�����һ�α��趨����µ�ʱ��*/
        ntpTimeStu = GetReferenceTimestamp();

        if ((NULL != ntpTimeStu))
        {
            /*��ȡ��������������*/
            integer = ntpTimeStu->Integer;
            LongToChar(integer,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            /*��ȡ������С������*/
            fractional = ntpTimeStu->Fractional;
            LongToChar(fractional,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            rtnValue1 = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue1 = RETURN_ERROR;
        }

        /*��ȡ�������յ����������뿪���صı���ʱ��*/
        ntpTimeStu = GetOriginateTimestamp();

        if (NULL != ntpTimeStu)
        {
            /*��ȡ��������������*/
            integer = ntpTimeStu->Integer;
            LongToChar(integer,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            /*��ȡ������С������*/
            fractional = ntpTimeStu->Fractional;
            LongToChar(fractional,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            rtnValue2 = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue2 = RETURN_ERROR;
        }

        /*��ȡӦ�����뿪�������ķ�����ʱ��*/
        ntpTimeStu = GetReceiveTimestamp();

        if (NULL != ntpTimeStu)
        {
            /*��ȡ��������������*/
            integer = ntpTimeStu->Integer;
            LongToChar(integer,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            /*��ȡ������С������*/
            fractional = ntpTimeStu->Fractional;
            LongToChar(fractional,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            rtnValue3 = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue3 = RETURN_ERROR;
        }

        /*��ȡ�����ĵ���������ķ�����ʱ��*/
        ntpTimeStu = GetTransmitTimestamp();

        if (NULL != ntpTimeStu)
        {
            /*��ȡ��������������*/
            integer = ntpTimeStu->Integer;
            LongToChar(integer,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            /*��ȡ������С������*/
            fractional = ntpTimeStu->Fractional;
            LongToChar(fractional,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            rtnValue4 = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue4 = RETURN_ERROR;
        }

        if ((RETURN_SUCCESS == rtnValue1) && (RETURN_SUCCESS == rtnValue2)
            && (RETURN_SUCCESS == rtnValue3) && (RETURN_SUCCESS == rtnValue4))
        {
            rtnValue = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue =RETURN_ERROR;
        }
    } 
    else
    {
        rtnValue = RETURN_ERROR;
    }	

	return rtnValue;
}
/*
* ���������� ����֡���е�ZC�ϵ��ǳɹ���־��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetZCPowerUpFlagInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S resetStatus = DEFAULT_ZERO;
	
    if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
    {
        resetStatus = inFrameContent[*buffIndex];
        *buffIndex=*buffIndex+1U;

        TsrIFSetZcWorkState(resetStatus);

        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue=RETURN_ERROR;
    }

	return rtnValue;
}

/*
* ���������� ����֡���е�ZC�ϵ��ǳɹ���־��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetZCPowerUpFlagInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue = RETURN_ERROR;
	UINT8_S resetStatus = DEFAULT_ZERO;
	
    if ((NULL != buffIndex) && (NULL != outFrameContent))
    {
        resetStatus = TsrIFGetZcWorkState();

        outFrameContent[*buffIndex] = resetStatus;
        *buffIndex=*buffIndex+1U;

        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }

	return rtnValue;
}

/*
* ���������� ����֡���е�CRC32��Ϣ
* ����˵���� const UINT8 inFrameContent[],����֡
*            UINT32_S *buffIndex,֡������±�
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S GetCRC32InfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
    UINT32_S index = DEFAULT_ZERO;

    if ((NULL != inFrameContent) && (NULL != buffIndex))
    {
        /* �ݴ濪ʼ�±� */
        index = *buffIndex;


        /* �����������±� */
        *buffIndex = index;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue=RETURN_ERROR;
    }
    
	return rtnValue;
}

/*
* ���������� ����֡���е�CRC32��Ϣ
* ����˵���� UINT32 *buffIndex,֡������±�
*            UINT8_S outFrameContent[],���֡
* ����ֵ  �� RETURN_ERROR������ʧ��
*			 RETURN_SUCCESS�����óɹ�
*/
UINT8_S SetCRC32InfoToFrame(UINT32_S *buffIndex,const UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
    UINT32_S index = DEFAULT_ZERO;

    if ((NULL != buffIndex) && (NULL != outFrameContent))
    {
        /* ���ÿ�ʼ�±� */
        index = *buffIndex;


        /* ���ò�����������±� */
        *buffIndex = index;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue=RETURN_ERROR;
    }
    
	return rtnValue;
}

