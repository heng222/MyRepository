/************************************************************************
*
* 文件名   ：  SynDataPackAndParse.c
* 创建时间 ：  2015.04.18
* 作者     ：  ZC组
* 功能描述 ：  2系同步数据的打包和解析
* 备  注   ：  无
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
extern AcStatusDataStruct gAcStatusDataStruBuff[LOCAL_AC_SUM_MAX];          /*定义本ZC计轴数据状态结构体*/
extern UINT16_S gAcCurSum;	   /*ZC计轴数据状态结构体数量*/
/*DR*/
extern DRButtonDataStruct  gDRButtonDataStruBuff[DR_BUTTON_LOCAL_SUM_MAX];  /*定义无人折返按钮状态数据结构体*/
extern UINT16_S gDRButtonCurSum ;                                                    /*无人折返按钮当前总数*/
extern DRLampDataStruct gDRLampDataStruBuff[DR_LAMP_LOCAL_SUM_MAX];         /*定义无人折返灯状态数据结构体*/
extern UINT16_S gDRLampCurSum ;                                                      /*无人折返按钮当前总数*/
/*ESB*/
extern EsbDataStruct gEsbDataStruBuff[ESB_LOCAL_SUM_MAX];             /*本地管理的紧急停车按钮状态信息*/
extern UINT16_S gEsbCurSum ;                                              /*紧急停车按钮当前总数*/
/*PSD*/
extern PsdDataStruct gPsdDataStruBuff[PSD_LOCAL_SUM_MAX];                 /*定义本地管理的屏蔽门状态数据数组*/
extern UINT16_S gPsdCurSum ;                                    /*屏蔽门当前总数*/
/*LogicSection*/
extern LogicSectionStruct gLogicSectionDataStruBuff[LOGIC_SECTION_LOCAL_SUM_MAX];     /*定义本地管理的逻辑区段状态数据数组*/
extern UINT16_S gLogicSectionCurSum ;     /*逻辑区段当前总数*/
/*Overlap*/
extern OverlapDataStruct gOverlapDataStruBuff[OVERLAP_LOCAL_SUM_MAX];          /*本地管理的保护区段状态信息*/
extern UINT16_S gOverlapCurSum ;                                                        /*保护区段当前总数*/
/*Route*/
extern RouteDataStruct gRouteStatusDataStruBuff[ROUTE_LOCAL_SUM_MAX];          /*本地管理的保护区段状态信息*/
extern UINT16_S gRouteCurSum ;                                                          /*进路当前总数*/
/*Signal*/
extern SignalDataStruct gSignalDataStruBuff[SIGNAL_LOCAL_SUM_MAX];          /*本地管理的保护区段状态信息*/
extern UINT16_S gSignalCurSum ;                                                      /*信号机当前总数*/
/*Switch*/
extern SwitchDataStruct gSwitchStatusDataStruBuff[SWITCH_LOCAL_SUM_MAX];          /*本地管理的道岔状态信息*/
extern UINT16_S gSwitchCurSum ;                                                      /*道岔当前总数*/
/*Tsr*/
extern TsrDataStruct gTsrDataStruBuff[TSR_BUFF_SUM_MAX];                  /*本地管理的临时限速配置信息*/
extern UINT16_S gTsrOfZcIdBuff[LINE_ZC_SUM_MAX] ;    /*定义临时限速（ZC）映射数组*/
extern UINT16_S gTsrOfZcCurSum ;                                     /*临时限速（ZC）当前总数*/
/*Train*/
extern TrainInfoStruct gTrainStatusDataStruBuff[SIZE_MAX_CONTROLE_TRAIN];   /*定义本ZC控制范围内最大列车数量*/
extern UINT8_S gLocalTrainIndexBuff[SIZE_MAX_LINE_TRAIN] ;			/*定义列车索引数组，数组长度为线路可能的最大列车ID*/
extern UINT8_S gTrainCurSum ;									        /*本ZC当前列车数量*/
/*DataVersion*/
extern DataVersionStruct gInputDataVersionStru;                 /*定义数据版本号信息*/
/*CommTarget*/
extern CommTargetDataStruct gCommTargetDataStruBuff[COMM_TYPE_SUM_MAX];      /*定义通信对象状态信息（除列车外的其他系统）*/
extern SingleCommTargeStruct gCommTrainDataStruBuff[COMM_TRAIN_ID_MAX];      /*通信列车状态信息*/
extern UINT8_S gCommTargetTypeCurSum ;                                                       /*定义通信对象总数*/

/*
* 功能描述： 解析帧当中的全部信息
* 参数说明： const UINT8 inFrameContent[],输入帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S ParseAllInfoFromFrame(const UINT8_S inFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT32_S buffIndex=DEFAULT_ZERO;           /*数组的下标*/
	UINT32_S dataLength=DEFAULT_ZERO;          /*数据内容总长度*/
	UINT32_S totalLength=DEFAULT_ZERO;         /*数据总长度*/
	
    if (NULL != inFrameContent)
    {
        /*总长度*/
        totalLength=LongFromChar(&inFrameContent[DEFAULT_ZERO]);

        /*2个报头*/
        if ((SYN_DATA_CONTENT_HEAD1==inFrameContent[4])&&(SYN_DATA_CONTENT_HEAD2==inFrameContent[5]))
        {
            /*数据内容总长度*/
            dataLength=LongFromChar(&inFrameContent[6]);

            /*因为数据总长度未知,余下4个字节*/
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

            /*NTP校时成功标志*/
            rtnValue *= GetNTPTimeFlagInfoFromFrame(inFrameContent,&buffIndex);

            /*NTP校时本地时间*/
            rtnValue *= GetNTPLocalTimeInfoFromFrame(inFrameContent,&buffIndex);

            /*NTP校时4个结构体时间*/
            rtnValue *= GetNTPStructTimeInfoFromFrame(inFrameContent,&buffIndex);

            /*ZC上电标记成功标志*/
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
* 功能描述： 设置帧当中的全部信息
* 参数说明： UINT8 outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S PackAllInfoToFrame(UINT8_S outFrameContent[])
{
	UINT32_S buffIndex=DEFAULT_ZERO;           /*数组的下标*/
	UINT32_S dataLength=DEFAULT_ZERO;          /*数据总长度*/
	UINT8_S rtnValue = RETURN_ERROR;
	
	/*初始化*/
	MemorySet(&outFrameContent[DEFAULT_ZERO],SYN_DATA_MAX_NUM,DEFAULT_ZERO,SYN_DATA_MAX_NUM);	
	
    if (NULL != outFrameContent)
    {
        /*2个报头*/
        outFrameContent[4]=SYN_DATA_CONTENT_HEAD1;
        outFrameContent[5]=SYN_DATA_CONTENT_HEAD2;

        /*因为数据总长度未知,余下4个字节*/
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

        /*NTP校时成功标志*/
        rtnValue *= SetNTPTimeFlagInfoToFrame(&buffIndex,outFrameContent);

        /*NTP校时时间*/
        rtnValue *= SetNTPLocalTimeInfoToFrame(&buffIndex,outFrameContent);

        /*NTP校时4个结构体时间*/
        rtnValue *= SetNTPStructTimeInfoToFrame(&buffIndex,outFrameContent);

        /*ZC上电标记成功标志*/
        rtnValue *= SetZCPowerUpFlagInfoToFrame(&buffIndex, outFrameContent);
        /*CRC32*/

        /*数据内容总长度,5代表帧头*/
        dataLength=(buffIndex-SYN_DATA_START_INDEX)+1U;
        LongToChar(dataLength,&outFrameContent[6]);

        /*填充总长度*/
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
* 功能描述： 解析帧当中的AC信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetACInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S acCycle=DEFAULT_ZERO;
	UINT8_S  trainIdCycle=DEFAULT_ZERO;
	UINT16_S acId=DEFAULT_ZERO;   /*计轴区段ID*/
	UINT8_S  acTrainOfAcNum=DEFAULT_ZERO;  /*计轴区段内列车的数量*/
	UINT16_S trainIdSequenceBuff[SIZE_MAX_TRAINOFAC]={DEFAULT_ZERO};  /*列车ID数组*/

	if ((NULL!=buffIndex)&&(NULL!=inFrameContent))
	{	
        /*计轴区段数量*/
        gAcCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (acCycle=DEFAULT_ZERO;acCycle<gAcCurSum;acCycle++)
		{
			/*计轴区段ID*/
			acId=ShortFromChar(&inFrameContent[*buffIndex]);
			gAcStatusDataStruBuff[acCycle].AcId=acId;
			*buffIndex=*buffIndex+2U;

			/*方向*/
			SetAcDirection(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*锁闭状态*/
			SetAcBelock(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*占用状态*/
			SetAcStatusNow(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*UT标志*/
			SetAcUtFlag(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*UT冗余信息*/
			SetAcUtRedundance(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;
			
			/*ARB标志*/
			SetAcArbFlag(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*ARB冗余信息*/
			SetAcArbRedundance(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*清扫列车ID*/
			SetAcCleanTrainId(acId,ShortFromChar(&inFrameContent[*buffIndex]));			
			*buffIndex=*buffIndex+2U;

			/*列车清扫标志*/
			SetAcTrainCleanFlag(acId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*计轴区段内列车数量*/
			acTrainOfAcNum=inFrameContent[*buffIndex];
			SetAcTrainOfAcNum(acId,acTrainOfAcNum);
			*buffIndex=*buffIndex+1U;

			/*列车信息*/
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
* 功能描述： 设置帧当中的AC信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetACInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;  /*返回值*/
	UINT16_S acCycle=DEFAULT_ZERO;
	UINT8_S  trainIdCycle=DEFAULT_ZERO; 
	UINT16_S acId=DEFAULT_ZERO;         /*计轴ID*/
	UINT16_S acTotalNum=DEFAULT_ZERO;     /*列车状态总数*/ 
	UINT16_S trainSequenceBuff[SIZE_MAX_TRAINOFAC]={DEFAULT_ZERO};  /*列车ID数组*/
	UINT8_S  acTrainOfAcNum=DEFAULT_ZERO;  /*计轴区段内列车的数量*/

	/*初始化列车序列数组*/
	MemorySet(&trainSequenceBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC,DEFAULT_ZERO,sizeof(UINT16_S)*SIZE_MAX_TRAINOFAC);

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*获取计轴状态的总数*/
        acTotalNum = GetAcCurSum(); 

        /*计轴区段数量*/
        ShortToChar(acTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (acCycle=DEFAULT_ZERO;acCycle<acTotalNum;acCycle++)
		{			
			/*计轴区段ID*/
			acId=gAcStatusDataStruBuff[acCycle].AcId;  /*获取计轴的ID*/
			ShortToChar(acId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;
			
			/*方向*/
			outFrameContent[*buffIndex]=GetAcDirection(acId);
			*buffIndex=*buffIndex+1U;

			/*锁闭状态*/
			outFrameContent[*buffIndex]=GetAcBelock(acId);
			*buffIndex=*buffIndex+1U;

			/*占用状态*/
			outFrameContent[*buffIndex]=GetAcStatusNow(acId);
			*buffIndex=*buffIndex+1U;

			/*UT标志*/
			outFrameContent[*buffIndex]=GetAcUtFlag(acId);
			*buffIndex=*buffIndex+1U;

			/*UT冗余信息*/
			outFrameContent[*buffIndex]=GetAcUtRedundance(acId);
			*buffIndex=*buffIndex+1U;

			/*ARB标志*/
			outFrameContent[*buffIndex]=GetAcArbFlag(acId);
			*buffIndex=*buffIndex+1U;

			/*ARB冗余信息*/
			outFrameContent[*buffIndex]=GetAcArbRedundance(acId);
			*buffIndex=*buffIndex+1U;

			/*清扫列车ID*/
			ShortToChar(GetAcCleanTrainId(acId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*列车清扫标志*/
			outFrameContent[*buffIndex]=GetAcTrainCleanFlag(acId);
			*buffIndex=*buffIndex+1U;

			/*计轴区段内列车数量*/
			acTrainOfAcNum=GetAcTrainOfAcNum(acId);
			outFrameContent[*buffIndex]=acTrainOfAcNum;
			*buffIndex=*buffIndex+1U;

			/*列车信息的列车ID*/
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
                /*不处理*/
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
* 功能描述： 解析帧当中DR的无人折返按钮信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetDRButtonInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S drBtnCycle=DEFAULT_ZERO;
    UINT16_S drButtonId=DEFAULT_ZERO;   /*无人折返按钮ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*无人折返按钮数量*/
        gDRButtonCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (drBtnCycle=DEFAULT_ZERO;drBtnCycle<gDRButtonCurSum;drBtnCycle++)
		{
			/*无人折返按钮ID*/
			drButtonId=ShortFromChar(&inFrameContent[*buffIndex]);
			gDRButtonDataStruBuff[drBtnCycle].DRButtonId=drButtonId;
			*buffIndex=*buffIndex+2U;

			/*无人折返按钮对应列车ID*/
			SetDRButtonOfTrainId(drButtonId,ShortFromChar(&inFrameContent[*buffIndex]));
			*buffIndex=*buffIndex+2U;

			/*无人折返按钮当前状态*/
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
* 功能描述： 设置帧当中DR的无人折返按钮信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetDRButtonInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S drBtnCycle=DEFAULT_ZERO;
	UINT16_S drBtnId=DEFAULT_ZERO;         /*无人折返按钮ID*/
	UINT16_S drBtnTrainId=DEFAULT_ZERO;    /*无人折返按钮中列车ID*/
	UINT16_S drBtnTotalNum=DEFAULT_ZERO;   /*无人折返按钮总数*/
	
	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*获取无人折返按钮总数*/
        drBtnTotalNum=GetDRButtonSum();

        /*无人折返按钮数量*/
        ShortToChar(drBtnTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (drBtnCycle=DEFAULT_ZERO;drBtnCycle<drBtnTotalNum;drBtnCycle++)
		{			
			/*无人折返按钮ID*/	
			drBtnId=gDRButtonDataStruBuff[drBtnCycle].DRButtonId;  /*获取无人折返按钮ID*/
			ShortToChar(drBtnId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*无人折返按钮对应列车ID*/
			drBtnTrainId=GetDRButtonOfTrainId(drBtnId);
			ShortToChar(drBtnTrainId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*无人折返按钮当前状态*/
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
* 功能描述： 解析帧当中DR的无人折返灯信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetDRLampInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S drLampCycle=DEFAULT_ZERO;
	UINT16_S drLampId=DEFAULT_ZERO;   /*无人折返灯ID*/

	if ((NULL != inFrameContent)&&(NULL != buffIndex))
	{
        /*无人折返按钮数量*/
        gDRLampCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (drLampCycle=DEFAULT_ZERO;drLampCycle<gDRLampCurSum;drLampCycle++)
		{
			/*无人折返灯ID*/
			drLampId=ShortFromChar(&inFrameContent[*buffIndex]);
			gDRLampDataStruBuff[drLampCycle].DRLampId=drLampId;
			*buffIndex=*buffIndex+2U;

			/*无人折返灯对应列车ID*/
			SetDRLampOfTrainId(drLampId,ShortFromChar(&inFrameContent[*buffIndex]));
			*buffIndex=*buffIndex+2U;

			/*无人折返灯控制命令*/
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
* 功能描述： 设置帧当中DR的无人折返灯信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetDRLampInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S drLampCycle=DEFAULT_ZERO;
	UINT16_S drLampId=DEFAULT_ZERO;        /*无人折返灯ID*/
	UINT16_S drLampTrainId=DEFAULT_ZERO;   /*无人折返灯中列车ID*/
	UINT16_S drLampTotalNum=DEFAULT_ZERO;  /*无人折返灯总数*/

	if ((NULL != outFrameContent)&&(NULL != buffIndex))
	{	
        /*获取无人折返灯总数*/
        drLampTotalNum=GetDRButtonSum();

        /*无人折返灯数量*/
        ShortToChar(drLampTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex + 2U;

		for (drLampCycle=DEFAULT_ZERO;drLampCycle<drLampTotalNum;drLampCycle++)
		{
			/*无人折返灯ID*/
			drLampId=gDRLampDataStruBuff[drLampCycle].DRLampId;  /*获取无人折返按钮ID*/
			ShortToChar(drLampId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*无人折返灯对应列车ID*/
			drLampTrainId=GetDRLampOfTrainId(drLampId);
			ShortToChar(drLampTrainId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*无人折返灯控制命令*/
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
* 功能描述： 解析帧当中的紧急停车按钮ESB信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetESBInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S esbCycle=DEFAULT_ZERO;
	UINT16_S esbId=DEFAULT_ZERO;   /*紧急停车按钮ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*紧急停车按钮数量*/
        gEsbCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (esbCycle=DEFAULT_ZERO;esbCycle<gEsbCurSum;esbCycle++)
		{
			/*紧急停车按钮ID*/
			esbId=ShortFromChar(&inFrameContent[*buffIndex]);
			gEsbDataStruBuff[esbCycle].EsbId=esbId;
			*buffIndex=*buffIndex+2U;

			/*紧急停车按钮状态*/
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
* 功能描述： 设置帧当中的ESB信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetESBInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S esbCycle=DEFAULT_ZERO;
	UINT16_S esbId=DEFAULT_ZERO;   /*紧急停车按钮ID*/
	UINT16_S esbTotalNum=DEFAULT_ZERO;  /*紧急停车按钮总数*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*获取紧急停车总数*/
        esbTotalNum=GetEsbSum();

        /*紧急停车按钮的数量*/
        ShortToChar(esbTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (esbCycle=DEFAULT_ZERO;esbCycle<esbTotalNum;esbCycle++)
		{
			/*紧急停车按钮ID*/
			esbId=gEsbDataStruBuff[esbCycle].EsbId;   /*获取紧急停车按钮ID*/
			ShortToChar(esbId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*紧急停车按钮当前状态*/
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
* 功能描述： 解析帧当中的屏蔽门PSD信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetPSDInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S psdCycle=DEFAULT_ZERO;
	UINT16_S psdId=DEFAULT_ZERO;   /*屏蔽门ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*屏蔽门数量*/
        gPsdCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (psdCycle=DEFAULT_ZERO;psdCycle<gPsdCurSum;psdCycle++)
		{
			/*屏蔽门ID*/
			psdId=ShortFromChar(&inFrameContent[*buffIndex]);
			gPsdDataStruBuff[psdCycle].PsdId=psdId;
			*buffIndex=*buffIndex+2U;

			/*屏蔽门状态*/
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
* 功能描述： 设置帧当中的PSD信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetPSDInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S psdCycle=DEFAULT_ZERO;
	UINT16_S psdId=DEFAULT_ZERO;         /*屏蔽门ID*/
	UINT16_S psdTotalNum=DEFAULT_ZERO;   /*屏蔽门的总数*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*获取屏蔽门总数*/
        psdTotalNum=GetPsdSum();

        /*屏蔽门总数*/
        ShortToChar(psdTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (psdCycle=DEFAULT_ZERO;psdCycle<psdTotalNum;psdCycle++)
		{
			/*屏蔽门ID*/
			psdId=gPsdDataStruBuff[psdCycle].PsdId;/*获取屏蔽门ID*/
			ShortToChar(psdId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*屏蔽门当前状态*/
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
* 功能描述： 解析帧当中的LogicSection信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetLogicSectionInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S logicSectionCycle=DEFAULT_ZERO;
	UINT16_S logicSectionId=DEFAULT_ZERO;   /*逻辑区段ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*逻辑区段数量*/
        gLogicSectionCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (logicSectionCycle=DEFAULT_ZERO;logicSectionCycle<gLogicSectionCurSum;logicSectionCycle++)
		{
			/*逻辑区段ID*/
			logicSectionId=ShortFromChar(&inFrameContent[*buffIndex]);
			gLogicSectionDataStruBuff[logicSectionCycle].LogicSectionId=logicSectionId;
			*buffIndex=*buffIndex+2U;

			/*逻辑区段状态*/
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
* 功能描述： 设置帧当中的LogicSection信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetLogicSectionInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S logicSectionCycle=DEFAULT_ZERO;
	UINT16_S logicSectionId=DEFAULT_ZERO;         /*逻辑区段ID*/
	UINT16_S logicSectionTotalNum=DEFAULT_ZERO;   /*逻辑区段的总数*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*获取逻辑区段总数*/
        logicSectionTotalNum=GetLogicSectionSum();

        /*逻辑区段总数*/
        ShortToChar(logicSectionTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (logicSectionCycle=DEFAULT_ZERO;logicSectionCycle<logicSectionTotalNum;logicSectionCycle++)
		{
			/*逻辑区段ID*/
			logicSectionId=gLogicSectionDataStruBuff[logicSectionCycle].LogicSectionId;   /*获取逻辑区段ID*/
			ShortToChar(logicSectionId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*逻辑区段当前状态*/
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
* 功能描述： 解析帧当中的Overlap信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetOverlapInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S overlapCycle=DEFAULT_ZERO;
	UINT16_S overlapId=DEFAULT_ZERO;   /*保护区段ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*保护区段数量*/
        gOverlapCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (overlapCycle=DEFAULT_ZERO;overlapCycle<gOverlapCurSum;overlapCycle++)
		{
			/*保护区段ID*/
			overlapId=ShortFromChar(&inFrameContent[*buffIndex]);
			gOverlapDataStruBuff[overlapCycle].OverlapId=overlapId;
			*buffIndex=*buffIndex+2U;

			/*保护区段状态*/
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
* 功能描述： 设置帧当中的Overlap信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetOverlapInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S overlapCycle=DEFAULT_ZERO;
	UINT16_S overlapId=DEFAULT_ZERO;         /*保护区段ID*/
	UINT16_S overlapTotalNum=DEFAULT_ZERO;   /*保护区段的总数*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{
        /*获取保护区段总数*/
        overlapTotalNum=GetOverlapSum();

        /*保护区段总数*/
        ShortToChar(overlapTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (overlapCycle=DEFAULT_ZERO;overlapCycle<overlapTotalNum;overlapCycle++)
		{			
			/*保护区段ID*/
			overlapId=gOverlapDataStruBuff[overlapCycle].OverlapId;/*获取保护区段ID*/
			ShortToChar(overlapId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*保护区段当前状态*/
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
* 功能描述： 解析帧当中的Route信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetRouteInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S routeCycle=DEFAULT_ZERO;
	UINT16_S routeId=DEFAULT_ZERO;   /*进路ID*/

	if ((NULL != inFrameContent)&&(NULL != buffIndex))
	{
        /*进路数量*/
        gRouteCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (routeCycle=DEFAULT_ZERO;routeCycle<gRouteCurSum;routeCycle++)
		{
			/*进路ID*/
			routeId=ShortFromChar(&inFrameContent[*buffIndex]);
			gRouteStatusDataStruBuff[routeCycle].RouteId=routeId;
			*buffIndex=*buffIndex+2U;

			/*进路状态*/
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
* 功能描述： 设置帧当中的Route信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetRouteInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S routeCycle=DEFAULT_ZERO;
	UINT16_S routeId=DEFAULT_ZERO;         /*进路ID*/
	UINT16_S routeTotalNum=DEFAULT_ZERO;   /*进路的总数*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*获取进路总数*/
        routeTotalNum=GetRouteSum();

        /*进路总数*/
        ShortToChar(routeTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (routeCycle=DEFAULT_ZERO;routeCycle<routeTotalNum;routeCycle++)
		{
			/*进路ID*/
			routeId=gRouteStatusDataStruBuff[routeCycle].RouteId;     /*获取进路ID*/
			ShortToChar(routeId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*进路当前状态*/
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
* 功能描述： 解析帧当中的Signal信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetSignalInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S signalCycle=DEFAULT_ZERO;
	UINT16_S signalId=DEFAULT_ZERO;   /*信号机ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*信号机数量*/
        gSignalCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (signalCycle=DEFAULT_ZERO;signalCycle<gSignalCurSum;signalCycle++)
		{
			/*信号机ID*/
			signalId=ShortFromChar(&inFrameContent[*buffIndex]);
			gSignalDataStruBuff[signalCycle].SignalId=signalId;
			*buffIndex=*buffIndex+2U;

			/*信号机当前状态*/
			SetSignalStatus(signalId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*信号机亮灭状态*/
			SetSignalLightOffStatus(signalId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*信号机跨压状态*/
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
* 功能描述： 设置帧当中的Signal信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetSignalInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S signalCycle=DEFAULT_ZERO;
	UINT16_S signalId=DEFAULT_ZERO;         /*信号机ID*/
	UINT16_S signalTotalNum=DEFAULT_ZERO;   /*信号机的总数*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*获取信号机总数*/
        signalTotalNum=GetSignalSum();

        /*信号机总数*/
        ShortToChar(signalTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (signalCycle=DEFAULT_ZERO;signalCycle<signalTotalNum;signalCycle++)
		{
			/*信号机ID*/
			signalId=gSignalDataStruBuff[signalCycle].SignalId;   /*获取信号机ID*/
			ShortToChar(signalId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*信号机当前状态*/
			outFrameContent[*buffIndex]=GetSignalStatus(signalId);
			*buffIndex=*buffIndex+1U;

			/*信号机亮灭状态*/
			outFrameContent[*buffIndex]=GetSignalLightOffStatus(signalId);
			*buffIndex=*buffIndex+1U;

			/*信号机跨压状态*/
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
* 功能描述： 解析帧当中的Switch信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetSwitchInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S switchCycle=DEFAULT_ZERO;
	UINT16_S switchId=DEFAULT_ZERO;   /*道岔ID*/

	if ((NULL!=inFrameContent)&&(NULL!= buffIndex))
	{
        /*道岔数量*/
        gSwitchCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (switchCycle=DEFAULT_ZERO;switchCycle<gSwitchCurSum;switchCycle++)
		{
			/*道岔ID*/
			switchId=ShortFromChar(&inFrameContent[*buffIndex]);
			gSwitchStatusDataStruBuff[switchCycle].SwitchId=switchId;
			*buffIndex=*buffIndex+2U;

			/*道岔当前状态*/
			SetSwitchPosStatus(switchId,inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+1U;

			/*道岔锁闭状态*/
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
* 功能描述： 设置帧当中的Switch信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetSwitchInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT16_S switchCycle=DEFAULT_ZERO;
	UINT16_S switchId=DEFAULT_ZERO;         /*道岔ID*/
	UINT16_S switchTotalNum=DEFAULT_ZERO;   /*道岔的总数*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{	
        /*获取道岔总数*/
        switchTotalNum=GetSwitchSum();

        /*道岔总数*/
        ShortToChar(switchTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (switchCycle=DEFAULT_ZERO;switchCycle<switchTotalNum;switchCycle++)
		{
			/*道岔ID*/
			switchId=gSwitchStatusDataStruBuff[switchCycle].SwitchId;/*获取道岔ID*/
			ShortToChar(switchId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*道岔当前状态*/
			outFrameContent[*buffIndex]=GetSwitchPosStatus(switchId);
			*buffIndex=*buffIndex+1U;

			/*道岔锁闭状态*/
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
* 功能描述： 解析帧当中的Tsr信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetTsrInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S tsrCycle=DEFAULT_ZERO;
	UINT8_S singleCycle=DEFAULT_ZERO;
	UINT8_S singleTsrLogicSecCycle=DEFAULT_ZERO;
	UINT8_S tsrNum=DEFAULT_ZERO;    /*临时限速数量*/	
	UINT16_S belongZcId=DEFAULT_ZERO;         /*所属ZCID*/
    UINT8_S sectionNum=DEFAULT_ZERO;    /*包含逻辑区段数量*/
	UINT16_S sectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX]={DEFAULT_ZERO}; /*包含逻辑区段ID数组*/
	UINT8_S zcIndexInTsr = DEFAULT_ZERO;
	UINT8_S getOfFlag = DEFAULT_ZERO;
    UINT16_S innerTsrOfZcCurSum=DEFAULT_ZERO;
	
	/*初始化逻辑区段ID数组*/
	MemorySet(sectionIdBuff,SINGLE_TSR_SECTION_SUM_MAX,DEFAULT_ZERO,SINGLE_TSR_SECTION_SUM_MAX);

	if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
	{
        innerTsrOfZcCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (tsrCycle=DEFAULT_ZERO;tsrCycle<innerTsrOfZcCurSum;tsrCycle++)
		{
			/*临时限速所属ZCID*/
			belongZcId=ShortFromChar(&inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*申请下标*/
			AplyTsrIndexOfZcId(belongZcId);

			/*获取存储的Tsr结构中该ZCid对应下标*/
			zcIndexInTsr = GeZcIdOfTsrBufIndex(belongZcId);

			if (zcIndexInTsr < TSR_BUFF_SUM_MAX)
			{
				gTsrDataStruBuff[zcIndexInTsr].BelongZcId=belongZcId;
			
				/*临时限速数量*/
				tsrNum=inFrameContent[*buffIndex];
				SetZcIdOfTsrNum(zcIndexInTsr,tsrNum);
				*buffIndex=*buffIndex+1U;

				/*临时限速*/
				for (singleCycle=DEFAULT_ZERO;singleCycle<tsrNum;singleCycle++)
				{
					/*速度*/
					SetSingleTsrDataOfSpeed(zcIndexInTsr,((UINT16_S)singleCycle),((UINT16_S)inFrameContent[*buffIndex]));
					*buffIndex=*buffIndex+1U;

					/*包含逻辑区段数量*/
					sectionNum=inFrameContent[*buffIndex];
					*buffIndex=*buffIndex+1U;

					/*包含逻辑区段ID*/
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
* 功能描述： 设置帧当中的Tsr信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetTsrInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;  /*返回值*/
	UINT8_S tsrCyle=DEFAULT_ZERO;
	UINT8_S singleTsrCycle=DEFAULT_ZERO; 
	UINT8_S singleTsrLogicSecCycle=DEFAULT_ZERO;
	UINT8_S  singleTsrDataOfSectionNum=DEFAULT_ZERO;/*单个Tsr中逻辑区段个数*/
	UINT16_S belongZcId=DEFAULT_ZERO;         /*所属ZCID*/
	UINT16_S tsrTotalNum=DEFAULT_ZERO;        /*临时限速总数*/ 
	UINT16_S sectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX]={DEFAULT_ZERO}; /*逻辑区段ID数组*/
	UINT8_S zcIdOfTsrNum=DEFAULT_ZERO;  /*临时限速的数量*/

	/*初始化逻辑区段ID数组*/
	MemorySet(sectionIdBuff,SINGLE_TSR_SECTION_SUM_MAX,DEFAULT_ZERO,SINGLE_TSR_SECTION_SUM_MAX);

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*获取临时限速的总数*/
        tsrTotalNum=GetTsrOfZcSum();  

        /*临时限速的数量*/
        ShortToChar(tsrTotalNum,&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (tsrCyle=DEFAULT_ZERO;tsrCyle<tsrTotalNum;tsrCyle++)
		{
			/*所属ZCID*/
			belongZcId=GeTsrOfBelongZcId((UINT16_S)tsrCyle);   /*获取所属的ZCID*/			
			ShortToChar(belongZcId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*临时限速数量*/
			zcIdOfTsrNum=GetZcIdOfTsrNum(belongZcId);
			outFrameContent[*buffIndex]=zcIdOfTsrNum;
			*buffIndex=*buffIndex+1U;

			for(singleTsrCycle=DEFAULT_ZERO;singleTsrCycle<zcIdOfTsrNum;singleTsrCycle++)
			{
				/*单个临时限速的速度*/
				outFrameContent[*buffIndex]=GetSingleTsrDataOfSpeed(belongZcId,((UINT16_S)singleTsrCycle));
				*buffIndex=*buffIndex+1U;

				/*单个临时限速的包含逻辑区段数量*/
				singleTsrDataOfSectionNum=GetSingleTsrDataOfSectionNum(belongZcId,((UINT16_S)singleTsrCycle));
				outFrameContent[*buffIndex]=singleTsrDataOfSectionNum;
				*buffIndex=*buffIndex+1U;

				/*单个临时限速的逻辑区段ID*/
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
                    /*不处理*/
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
* 功能描述： 解析帧当中的Train信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetTrainInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR; 	
	UINT8_S trainCycle=DEFAULT_ZERO;
	UINT8_S trainSectionCycle=DEFAULT_ZERO;
	UINT16_S trainId=DEFAULT_ZERO;    /*列车ID*/
    UINT8_S sectionNum=DEFAULT_ZERO;  /*上周期占压逻辑区段数量*/
	UINT16_S sectionId[SIZE_MAX_SECTION_OF_TRAIN]={DEFAULT_ZERO};  /*逻辑区段ID*/
	TrainSafeLocStruct trainSafeLoc;    /*安全位置*/
	TrainSafeLocStruct trainUnSafeLoc;  /*非安全位置*/
	UINT16_S trainIndex = DEFAULT_ZERO;
	UINT8_S getFlag = DEFAULT_ZERO;
    UINT16_S innerTrainCurSum=DEFAULT_ZERO;   /*定义局部列车变量*/

	/*初始化*/
	MemorySet(sectionId,SIZE_MAX_SECTION_OF_TRAIN,DEFAULT_ZERO,SIZE_MAX_SECTION_OF_TRAIN);
	gTrainCurSum = 0U;
	
	/*printf("get：buffIndex=%d,TrainCurSum=%d\n",*buffIndex,innerTrainCurSum);*/	
	if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
	{
        /*列车数量*/
        innerTrainCurSum=ShortFromChar(&inFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (trainCycle=DEFAULT_ZERO;trainCycle<innerTrainCurSum;trainCycle++)
		{
			/*列车ID*/
			trainId=ShortFromChar(&inFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;
			/* printf("get：buffIndex=%d,trainId=%d\n",*buffIndex,trainId); */
			
			/*申请下标*/
			trainIndex = AllotTrainIndex(trainId);
            /* printf("APPLY: trainIndex=%d\n",trainIndex); */
			if (SIZE_MAX_CONTROLE_TRAIN != trainIndex)
			{
				/*添加列车数量和索引信息*/
				gLocalTrainIndexBuff[trainId] = (UINT8_S)(trainIndex);
				gTrainCurSum++;
				
				/*填写TrainId*/
			    gTrainStatusDataStruBuff[trainIndex].TrainID=trainId;
			
				/*受控ZCID*/
				SetTrainControlZc(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*列车周期*/
				SetTrainCycle(trainId,LongFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+4U;

				/*列车类型*/
				SetTrainType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*前端标记*/
				SetTrainSuspectHead(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*后端标记*/
				SetTrainSuspectTail(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*安全车头占压计轴区段ID*/
				SetTrainTrainHeadAC(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*安全车尾占压计轴区段ID*/
				SetTrainTrainTailAC(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*非安全车头占压计轴区段ID*/
				SetTrainUnsafeTrainHeadAC(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*非安全车尾占压计轴区段ID*/
				SetTrainUnsafeTrainTailAC(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*前方防护信号机ID*/
				SetTrainFrontSignal(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*信号机防护标记*/
				SetTrainSignalProtection(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*列车通信延时时间*/
				SetTrainPrtclDelay(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*列车状态信息*/
				SetTrainStatus(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*列车输入类型*/
				SetTrainInType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*输出列车类型*/
				SetTrainOutType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*相邻ZC输入信息*/
				SetTrainHandoverInType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*相邻ZC输出信息*/
				SetTrainHandoverOutType(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*安全位置*/
				trainSafeLoc.TrainHeadLink=ShortFromChar(&inFrameContent[*buffIndex]);  /*车头link*/
				*buffIndex=*buffIndex+2U;
				trainSafeLoc.TrainHeadOffset=LongFromChar(&inFrameContent[*buffIndex]);  /*车头offset*/
				*buffIndex=*buffIndex+4U;
				trainSafeLoc.TrainTailLink=ShortFromChar(&inFrameContent[*buffIndex]);  /*车尾link*/
				*buffIndex=*buffIndex+2U;
				trainSafeLoc.TrainTailOffset=LongFromChar(&inFrameContent[*buffIndex]);  /*车尾offset*/
				*buffIndex=*buffIndex+4U;
				SetTrainSafeLoc(trainId,&trainSafeLoc);

				/*非安全位置*/
				trainUnSafeLoc.TrainHeadLink=ShortFromChar(&inFrameContent[*buffIndex]);  /*车头link*/
				*buffIndex=*buffIndex+2U;
				trainUnSafeLoc.TrainHeadOffset=LongFromChar(&inFrameContent[*buffIndex]);  /*车头offset*/
				*buffIndex=*buffIndex+4U;
				trainUnSafeLoc.TrainTailLink=ShortFromChar(&inFrameContent[*buffIndex]);  /*车尾link*/
				*buffIndex=*buffIndex+2U;
				trainUnSafeLoc.TrainTailOffset=LongFromChar(&inFrameContent[*buffIndex]);  /*车尾offset*/
				*buffIndex=*buffIndex+4U;
				SetTrainUnSafeLoc(trainId,trainUnSafeLoc);

				/*期望运行方向*/
				SetTrainUnsafeDirection(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*实际运行方向*/
				SetTrainRealDirection(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*驾驶模式*/
				SetTrainMode(trainId,inFrameContent[*buffIndex]);
				
				/*printf("get:TrainMode=%d\n",inFrameContent[*buffIndex]);*/
				
				*buffIndex=*buffIndex+1U;

				/*运行级别*/
				SetTrainLevel(trainId,inFrameContent[*buffIndex]);
				
				/*printf("get:TrainLevel=%d\n",inFrameContent[*buffIndex]);*/
				
				
				*buffIndex=*buffIndex+1U;

				/*实际速度*/
				SetTrainSpeed(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*停稳信息*/
				SetTrainStopArea(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*完整性标记*/
				SetTrainIntegrity(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*紧急停车标记*/
				SetTrainEmergency(trainId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*不确定误差*/
				SetTrainError(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*切换线路ID*/
				SetTrainChangeLineId(trainId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*上周期占压逻辑区段数量*/
				sectionNum=inFrameContent[*buffIndex];
				*buffIndex=*buffIndex+1U;

				/*上周期占压逻辑区段ID*/
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
* 功能描述： 设置帧当中的Train信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetTrainInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S trainCycle=DEFAULT_ZERO;
	UINT8_S trainPreSecCycle=DEFAULT_ZERO;
	UINT8_S trainTotalNum=DEFAULT_ZERO;        /*列车的总数*/
	UINT16_S trainId=DEFAULT_ZERO;             /*列车ID*/
	UINT8_S trainPreSectionNum=DEFAULT_ZERO;   /*上周期占压逻辑区段数量*/
	UINT16_S trainSectionId[SIZE_MAX_SECTION_OF_TRAIN]={DEFAULT_ZERO}; /*上周期占压逻辑区段ID*/
	TrainSafeLocStruct trainSafeLoc;         /*列车安全位置结构体*/
	TrainSafeLocStruct trainUnSafeLoc;       /*列车非安全位置结构体*/
	
	/*初始化列车占压逻辑区段数组、列车安全位置、列车非安全位置*/
	MemorySet(trainSectionId,SIZE_MAX_SECTION_OF_TRAIN,DEFAULT_ZERO,SIZE_MAX_SECTION_OF_TRAIN);
	MemorySet(&trainSafeLoc,sizeof(TrainSafeLocStruct),DEFAULT_ZERO,sizeof(TrainSafeLocStruct));
	MemorySet(&trainUnSafeLoc,sizeof(TrainSafeLocStruct),DEFAULT_ZERO,sizeof(TrainSafeLocStruct));

	/*printf("set：buffIndex=%d,TrainCurSum=%d\n",*buffIndex,trainTotalNum);*/
	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{		
        /*获取列车总数*/
        trainTotalNum=GetTrainCurSum();  

        /*printf("set：TrainCurSum=%d\n",trainTotalNum);*/

        /*列车总数*/
        ShortToChar(((UINT16_S)trainTotalNum),&outFrameContent[*buffIndex]);
        *buffIndex=*buffIndex+2U;

		for (trainCycle=DEFAULT_ZERO;trainCycle<trainTotalNum;trainCycle++)
		{
			/*列车ID*/
			trainId=GetTrainIdOfIndex(trainCycle);
			ShortToChar(trainId,&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*printf("set：buffIndex=%d,TrainID=%d\n",*buffIndex,trainId);*/

			/*受控ZCID*/
			ShortToChar( GetTrainControlZc(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*列车周期*/
			LongToChar(GetTrainCycle(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+4U;

			/*列车类型*/
			outFrameContent[*buffIndex]=GetTrainType(trainId);
			*buffIndex=*buffIndex+1U;

			/*前端标记*/
			outFrameContent[*buffIndex]=GetTrainSuspectHead(trainId);
			*buffIndex=*buffIndex+1U;

			/*后端标记*/
			outFrameContent[*buffIndex]=GetTrainSuspectTail(trainId);
			*buffIndex=*buffIndex+1U;

			/*安全车头占压计轴区段ID*/
			ShortToChar(GetTrainTrainHeadAC(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*安全车尾占压计轴区段ID*/
			ShortToChar(GetTrainTrainTailAC(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*非安全车头占压计轴区段ID*/
			ShortToChar(GetTrainUnsafeTrainHeadAC(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*非安全车尾占压计轴区段ID*/
			ShortToChar(GetTrainUnsafeTrainTailAC(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*前方防护信号机ID*/
			ShortToChar(GetTrainFrontSignal(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*信号机防护标记*/
			outFrameContent[*buffIndex]=GetTrainSignalProtection(trainId);
			*buffIndex=*buffIndex+1U;

			/*列车通信延时时间*/
			outFrameContent[*buffIndex]=GetTrainPrtclDelay(trainId);
			*buffIndex=*buffIndex+1U;

			/*列车状态信息*/
			outFrameContent[*buffIndex]=GetTrainStatus(trainId);
			*buffIndex=*buffIndex+1U;

			/*列车输入类型*/
			outFrameContent[*buffIndex]=GetTrainInType(trainId);
			*buffIndex=*buffIndex+1U;

			/*输出列车类型*/
			outFrameContent[*buffIndex]=GetTrainOutType(trainId);
			*buffIndex=*buffIndex+1U;

			/*相邻ZC输入信息*/
			outFrameContent[*buffIndex]=GetTrainHandoverInType(trainId);
			*buffIndex=*buffIndex+1U;

			/*相邻ZC输出信息*/
			outFrameContent[*buffIndex]=GetTrainHandoverOutType(trainId);
			*buffIndex=*buffIndex+1U;

			/*安全位置*/
			if (RETURN_SUCCESS==GetTrainSafeLoc(trainId,&trainSafeLoc))
			{
				/*列车安全位置车头所在Link*/
				ShortToChar(trainSafeLoc.TrainHeadLink,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*列车安全位置车头所处offset */
				LongToChar(trainSafeLoc.TrainHeadOffset,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;

				/*列车安全位置车尾所在Link*/
				ShortToChar(trainSafeLoc.TrainTailLink,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*列车安全位置车尾所在offset*/
				LongToChar(trainSafeLoc.TrainTailOffset,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;
			} 
			else
			{
                /*不处理*/
			}
			
			/*非安全位置*/
			if (RETURN_SUCCESS==GetTrainUnSafeLoc(trainId,&trainUnSafeLoc))
			{
				/*列车非安全位置车头所在Link*/
				ShortToChar(trainUnSafeLoc.TrainHeadLink,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*列车非安全位置车头所处offset*/
				LongToChar(trainUnSafeLoc.TrainHeadOffset,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;

				/*列车非安全位置车尾所在Link*/
				ShortToChar(trainUnSafeLoc.TrainTailLink,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*列车非安全位置车尾所在offset*/
				LongToChar(trainUnSafeLoc.TrainTailOffset,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+4U;
			}
			else
			{
                /*不处理*/
			}
			
			/*期望运行方向*/
			outFrameContent[*buffIndex]=GetTrainUnsafeDirection(trainId);
			*buffIndex=*buffIndex+1U;

			/*实际运行方向*/
			outFrameContent[*buffIndex]=GetTrainRealDirection(trainId);
			*buffIndex=*buffIndex+1U;

			/*驾驶模式*/
			outFrameContent[*buffIndex]=GetTrainMode(trainId);
			*buffIndex=*buffIndex+1U;

			/*printf("set：TrainMode=%d\n",GetTrainMode(trainId));*/

			/*运行级别*/
			outFrameContent[*buffIndex]=GetTrainLevel(trainId);
			*buffIndex=*buffIndex+1U;

			/*printf("set：TrainLevel=%d\n",GetTrainLevel(trainId));*/

			/*实际速度*/
			ShortToChar(GetTrainSpeed(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*停稳信息*/
			outFrameContent[*buffIndex]=GetTrainStopArea(trainId);
			*buffIndex=*buffIndex+1U;

			/*完整性标记*/
			outFrameContent[*buffIndex]=GetTrainIntegrity(trainId);
			*buffIndex=*buffIndex+1U;

			/*紧急停车标记*/
			outFrameContent[*buffIndex]=GetTrainEmergency(trainId);
			*buffIndex=*buffIndex+1U;

			/*不确定误差*/
			ShortToChar(GetTrainError(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*切换线路ID*/
			ShortToChar(GetTrainChangeLineId(trainId),&outFrameContent[*buffIndex]);
			*buffIndex=*buffIndex+2U;

			/*上周期占压逻辑区段数量*/
			trainPreSectionNum=GetTrainPreSectionNum(trainId);
			outFrameContent[*buffIndex]=trainPreSectionNum;			
			*buffIndex=*buffIndex+1U;

			/*上周期占压逻辑区段ID*/
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
                /*不处理*/
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
* 功能描述： 解析帧当中的CommTarget信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetCommTargetInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S commTargetCycle=DEFAULT_ZERO;
	UINT8_S commTargetType=DEFAULT_ZERO;  /*通讯目标类型*/
	UINT8_S singleCommTargetCycle=DEFAULT_ZERO; 
	UINT8_S singleCommTargetTypeSum=DEFAULT_ZERO;  /*设备通信数量*/
	UINT16_S commTargetId=DEFAULT_ZERO;  /*通信ID*/

	if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
	{
        /*其他设备类型数量*/
        gCommTargetTypeCurSum=inFrameContent[*buffIndex];
        *buffIndex=*buffIndex+1U;

		for (commTargetCycle=DEFAULT_ZERO;commTargetCycle<gCommTargetTypeCurSum;commTargetCycle++)  
		{
			/*设备类型*/
			commTargetType=inFrameContent[*buffIndex];
			gCommTargetDataStruBuff[commTargetCycle].CommTargetType=commTargetType;
			*buffIndex=*buffIndex+1U;
					
			/*设备通信数量*/
			singleCommTargetTypeSum=inFrameContent[*buffIndex];
			gCommTargetDataStruBuff[commTargetType].CommTargetNum=singleCommTargetTypeSum;
			*buffIndex=*buffIndex+1U;

			/*设备通信索引表*/
			MemoryCpy(&gCommTargetDataStruBuff[commTargetCycle].CommTargetIdBuff[DEFAULT_ZERO],COMM_TARGET_ID_MAX,&inFrameContent[*buffIndex],COMM_TARGET_ID_MAX);
			*buffIndex=*buffIndex+COMM_TARGET_ID_MAX;
			
			/*通信对象*/
			for (singleCommTargetCycle=DEFAULT_ZERO;singleCommTargetCycle<singleCommTargetTypeSum;singleCommTargetCycle++)
			{
				/*通信ID*/
			    commTargetId=ShortFromChar(&inFrameContent[*buffIndex]);  
				gCommTargetDataStruBuff[commTargetCycle].SingleCommTargeStru[singleCommTargetCycle].CommTargetId=commTargetId;
				*buffIndex=*buffIndex+2U;

				/*通信状态*/
				SetCommTargetStatus(commTargetType,commTargetId,inFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+1U;

				/*通信累加位*/
				SetCommTargetCycle(commTargetType,commTargetId,ShortFromChar(&inFrameContent[*buffIndex]));
				*buffIndex=*buffIndex+2U;

				/*通信对象输入周期号*/
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
* 功能描述： 设置帧当中的通讯设备信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetCommTargetInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S commTargetTotalNum=DEFAULT_ZERO; /*通讯目标总数*/
	UINT8_S commTargetCycle=DEFAULT_ZERO;
	UINT8_S commTargetType=DEFAULT_ZERO;  /*通讯目标类型*/
	UINT8_S singleCommTargetCycle=DEFAULT_ZERO;  
	UINT8_S singleCommTargetTypeSum=DEFAULT_ZERO;  /*设备通信数量*/
	UINT16_S commTargetId=DEFAULT_ZERO;  /*通信ID*/

	if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
	{
        /*获取通信目标类型总数*/
        commTargetTotalNum=GetCommTargetTypeSum();

        outFrameContent[*buffIndex]=commTargetTotalNum;
        *buffIndex=*buffIndex+1U;

		for (commTargetCycle=DEFAULT_ZERO;commTargetCycle<commTargetTotalNum;commTargetCycle++)
		{
			/*设备类型*/
			commTargetType=gCommTargetDataStruBuff[commTargetCycle].CommTargetType;
			outFrameContent[*buffIndex]=commTargetType;
			*buffIndex=*buffIndex+1U;

			/*设备通信数量*/
			singleCommTargetTypeSum=GetSingleCommTargetTypeSum(commTargetType);
			outFrameContent[*buffIndex]=singleCommTargetTypeSum;
			*buffIndex=*buffIndex+1U;

			/*数组的大小*/
			MemoryCpy(&outFrameContent[*buffIndex],COMM_TARGET_ID_MAX,&gCommTargetDataStruBuff[commTargetCycle].CommTargetIdBuff[DEFAULT_ZERO],COMM_TARGET_ID_MAX);
			*buffIndex=*buffIndex+COMM_TARGET_ID_MAX;

			for (singleCommTargetCycle=DEFAULT_ZERO;singleCommTargetCycle<singleCommTargetTypeSum;singleCommTargetCycle++)
			{
				/*通信ID*/
				commTargetId=gCommTargetDataStruBuff[commTargetCycle].SingleCommTargeStru[singleCommTargetCycle].CommTargetId;
				ShortToChar(commTargetId,&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;
			
				/*通信状态*/
				outFrameContent[*buffIndex]=GetCommTargetStatus(commTargetType,commTargetId);
				*buffIndex=*buffIndex+1U;

				/*通信累加位*/
				ShortToChar(GetCommTargetCycle(commTargetType,commTargetId),&outFrameContent[*buffIndex]);
				*buffIndex=*buffIndex+2U;

				/*通信对象输入周期号*/
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
* 功能描述： 解析帧当中的NTP校时成功标志信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetNTPTimeFlagInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S ntpTimeFlag = DEFAULT_ZERO;

    if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
    {
        /*设置NTP校时成功标志信息*/
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
* 功能描述： 设置帧当中的NTP校时成功标志信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetNTPTimeFlagInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT8_S ntpTimeFlag = DEFAULT_ZERO;

    if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
    {
        /*获取NTP校时成功标志信息*/
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
* 功能描述： 解析帧当中的NTP校时本地时间信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetNTPLocalTimeInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue = RETURN_ERROR;
	UINT32_S localNtpTime = DEFAULT_ZERO;

    if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
    {
        /*设置NTP校时成功标志信息*/
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
* 功能描述： 设置帧当中的NTP校时本地时间信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetNTPLocalTimeInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
	UINT32_S localNtpTime = DEFAULT_ZERO;

    if ((NULL!=buffIndex)&&(NULL!=outFrameContent))
    {
        /*获取NTP校时成功标志信息*/
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
* 功能描述： 解析帧当中的NTP校时结构体时间信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetNTPStructTimeInfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue = RETURN_ERROR;
	NTPTimeStruct ntpTimeStu;
	UINT32_S integer = DEFAULT_ZERO;                                    /*秒数的整数部分*/
	UINT32_S fractional = DEFAULT_ZERO;                                 /*秒数的小数部分*/

    if ((NULL!=inFrameContent)&&(NULL!=buffIndex))
    {
        /*设置系统时钟最后一次被设定或更新的时间*/
        integer = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        fractional = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        ntpTimeStu.Integer = integer;
        ntpTimeStu.Fractional = fractional;

        SetReferenceTimestamp(ntpTimeStu);

        /*设置服务器收到的请求报文离开本地的本地时间*/
        integer = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        fractional = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        ntpTimeStu.Integer = integer;
        ntpTimeStu.Fractional = fractional;

        SetOriginateTimestamp(ntpTimeStu);

        /*设置应答报文离开服务器的服务器时间*/
        integer = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        fractional = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        ntpTimeStu.Integer = integer;
        ntpTimeStu.Fractional = fractional;

        SetReceiveTimestamp(ntpTimeStu);

        /*设置请求报文到达服务器的服务器时间*/
        integer = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        fractional = LongFromChar(&inFrameContent[*buffIndex]);
        *buffIndex = *buffIndex + 4U;

        ntpTimeStu.Integer = integer;
        ntpTimeStu.Fractional = fractional;

        SetTransmitTimestamp(ntpTimeStu);

        /*返回值*/
        rtnValue = RETURN_SUCCESS;
    }
    else
    {
        rtnValue = RETURN_ERROR;
    }
	
	return rtnValue;
	
}

/*
* 功能描述： 设置帧当中的NTP校时结构体时间信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetNTPStructTimeInfoToFrame(UINT32_S *buffIndex,UINT8_S outFrameContent[])
{
	UINT8_S rtnValue = RETURN_ERROR;
	UINT8_S rtnValue1 = RETURN_ERROR;
	UINT8_S rtnValue2 = RETURN_ERROR;
	UINT8_S rtnValue3 = RETURN_ERROR;
	UINT8_S rtnValue4 = RETURN_ERROR;
	NTPTimeStruct *ntpTimeStu = NULL;
	UINT32_S integer = DEFAULT_ZERO;                                    /*秒数的整数部分*/
	UINT32_S fractional = DEFAULT_ZERO;                                 /*秒数的小数部分*/

    if ((NULL != buffIndex) && (NULL != outFrameContent))
    {
        /*获取系统时钟最后一次被设定或更新的时间*/
        ntpTimeStu = GetReferenceTimestamp();

        if ((NULL != ntpTimeStu))
        {
            /*获取秒数的整数部分*/
            integer = ntpTimeStu->Integer;
            LongToChar(integer,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            /*获取秒数的小数部分*/
            fractional = ntpTimeStu->Fractional;
            LongToChar(fractional,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            rtnValue1 = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue1 = RETURN_ERROR;
        }

        /*获取服务器收到的请求报文离开本地的本地时间*/
        ntpTimeStu = GetOriginateTimestamp();

        if (NULL != ntpTimeStu)
        {
            /*获取秒数的整数部分*/
            integer = ntpTimeStu->Integer;
            LongToChar(integer,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            /*获取秒数的小数部分*/
            fractional = ntpTimeStu->Fractional;
            LongToChar(fractional,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            rtnValue2 = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue2 = RETURN_ERROR;
        }

        /*获取应答报文离开服务器的服务器时间*/
        ntpTimeStu = GetReceiveTimestamp();

        if (NULL != ntpTimeStu)
        {
            /*获取秒数的整数部分*/
            integer = ntpTimeStu->Integer;
            LongToChar(integer,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            /*获取秒数的小数部分*/
            fractional = ntpTimeStu->Fractional;
            LongToChar(fractional,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            rtnValue3 = RETURN_SUCCESS;
        } 
        else
        {
            rtnValue3 = RETURN_ERROR;
        }

        /*获取请求报文到达服务器的服务器时间*/
        ntpTimeStu = GetTransmitTimestamp();

        if (NULL != ntpTimeStu)
        {
            /*获取秒数的整数部分*/
            integer = ntpTimeStu->Integer;
            LongToChar(integer,&outFrameContent[*buffIndex]);
            *buffIndex = *buffIndex + 4U;

            /*获取秒数的小数部分*/
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
* 功能描述： 解析帧当中的ZC上电标记成功标志信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
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
* 功能描述： 设置帧当中的ZC上电标记成功标志信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
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
* 功能描述： 解析帧当中的CRC32信息
* 参数说明： const UINT8 inFrameContent[],输入帧
*            UINT32_S *buffIndex,帧的起点下标
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S GetCRC32InfoFromFrame(const UINT8_S inFrameContent[],UINT32_S *buffIndex)
{
	UINT8_S rtnValue=RETURN_ERROR;
    UINT32_S index = DEFAULT_ZERO;

    if ((NULL != inFrameContent) && (NULL != buffIndex))
    {
        /* 暂存开始下标 */
        index = *buffIndex;


        /* 回设操作后的下标 */
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
* 功能描述： 设置帧当中的CRC32信息
* 参数说明： UINT32 *buffIndex,帧的起点下标
*            UINT8_S outFrameContent[],输出帧
* 返回值  ： RETURN_ERROR：设置失败
*			 RETURN_SUCCESS：设置成功
*/
UINT8_S SetCRC32InfoToFrame(UINT32_S *buffIndex,const UINT8_S outFrameContent[])
{
	UINT8_S rtnValue=RETURN_ERROR;
    UINT32_S index = DEFAULT_ZERO;

    if ((NULL != buffIndex) && (NULL != outFrameContent))
    {
        /* 设置开始下标 */
        index = *buffIndex;


        /* 设置操作结束后的下标 */
        *buffIndex = index;

        rtnValue = RETURN_SUCCESS;
    } 
    else
    {
        rtnValue=RETURN_ERROR;
    }
    
	return rtnValue;
}

