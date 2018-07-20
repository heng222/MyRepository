/********************************************************                                                                                                            
�� �� ���� ZcMaintainManager.c
��    �ߣ� ZC��
����ʱ�䣺 2015-04-18
������ ZCά����־����
��ע�� ��  
********************************************************/

#include "ZcMaintainManager.h"
#include "MaintainManager.h"
#include "../LineDataManager/PSD/PSDStatusData.h"
#include "../LineDataManager/PSD/PSDConfigData.h"
#include "../LineDataManager/AC/ACConfigData.h"
#include "../LineDataManager/AC/ACStatusData.h"
#include "../LineDataManager/DR/DRStatusData.h"
#include "../LineDataManager/DR/DRConfigData.h"
#include "../LineDataManager/DataVersion/DataVersionConfigData.h"
#include "../LineDataManager/ESB/ESBStatusData.h"
#include "../LineDataManager/ESB/ESBConfigData.h"
#include "../LineDataManager/LogicSection/LogicSectionConfigData.h"
#include "../LineDataManager/LogicSection/LogicSectionStatusData.h"
#include "../LineDataManager/Overlap/OverlapStatusData.h"
#include "../LineDataManager/Overlap/OverlapConfigData.h"
#include "../LineDataManager/Route/RouteStatusData.h"
#include "../LineDataManager/Route/RouteConfigData.h"
#include "../LineDataManager/Signal/SignalStatusData.h"
#include "../LineDataManager/Signal/SignalConfigData.h"
#include "../LineDataManager/Switch/SwitchStatusData.h"
#include "../LineDataManager/Switch/SwitchConfigData.h"
#include "../TrainManager/MA/MAStatusData.h"
#include "../TrainManager/Train/TrainStatusData.h"
#include "../../Common/Copy.h"
#include "../../Common/MemSet.h"
#include "../../Common/Convert.h"
#include "../SysDataManager/SysDefine.h"
#include "../SysDataManager/SysStatusData.h"
#include "../IOManager/CommTarget/CommTargetDefine.h"
#include "../IOManager/CommTarget/CommTargetStatusData.h"
#include "../IOManager/CommTarget/CommTargetConfigData.h"
#include "../LineDataManager/Tsr/TsrStatusData.h"

#ifdef SYS_TYPE_VXWORKS
#include "../../PlatformAdapter/AppItf/AdptAppServiceInterface.h"
#endif

extern NextZcMaDataStruct gNextZcDataStruBuff[COMM_TRAIN_SUM_MAX];                  /* ��������ZC���Ʒ�Χ������г��ƶ���Ȩ���� */                                       						      
extern TsrDataStruct gTsrDataStruBuff[TSR_BUFF_SUM_MAX];                            /* ���屾ZC���Ʒ�Χ�ڵ���ʱ������Ϣ */

/**********************************�ڲ�����START*********************************/  
static void LogPrintfVersion(void);
static void ShowVersion(UINT32_S version);
static void LogPrintfDataVer(void);
static void LogMaCalcBySelf(void);     /* ��ӡ��ZC�����MA��Ϣ */
static void LogMaCalcByNzc(void);      /* ��ӡ����ZC�����MA��Ϣ */
/**********************************�ڲ�����END***********************************/


/*************************************************
������:      PrintfZcMaintainInfo
��������:    ��ӡZCά����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void PrintfZcMaintainInfo(void)
{
    /*
    LogPrintf(1U,"\n");
    */
#ifdef LOG_ANOTHER_METHOND
    LogBufPeriodClear();
#endif	
    LogPrintfVersion();

    LogPrintfMicAndSme();

    LogPrintfAllCommTargetStatus();

    LogPrintfPsd();

    LogPrintfDR();

    LogPrintfESB();

    LogPrintfLogicSection();

    LogPrintfSignal();

    LogPrintfSwitch();

    LogPrintfOverlap();

    LogPrintfRoute();

    LogPrintfAc();

    LogPrintfTsr();

    LogPrintfMA();

    LogPrintfTrain();

}



/*************************************************
������:      LogPrintfPsd
��������:    ��ӡZCά����Ϣ��PSD����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfPsd(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S psdSum = DEFAULT_ZERO;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  status = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    LogPrintf(1U,"PSD\n");

    psdSum = GetPsdSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(psdSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < psdSum;cycle++)
    {
        id = GetPsdId(cycle);
        status = GetPsdStatus(id);

#ifdef SYS_TYPE_WINDOWS
        LogPrintf(1U,"PSD[%d],Status=%d;",id,status);

        if((cycle % 10U) == 9U)
        {
            LogPrintf(1U,"\n");
        }

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"%d,%d;",id,status);	

#else

#endif

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = status;
        tmpIndex = tmpIndex + 1u;

#endif 

    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 

}

/*************************************************
������:      LogPrintfAc
��������:    ��ӡZCά����Ϣ��AC����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfAc(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S cycleOther = DEFAULT_ZERO;
    UINT16_S acCurSum = DEFAULT_ZERO;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  acLockDir = DEFAULT_ZERO;      /* �����������շ��� */
    UINT8_S  acLockStatus = DEFAULT_ZERO;   /* ������������״̬ */
    UINT8_S  acStatus = DEFAULT_ZERO;       /* ��������״̬ */
    UINT8_S  acUtFlag = DEFAULT_ZERO;       /* ��������UT��ʶ */
    UINT8_S  acUtRedundance = DEFAULT_ZERO; /* ��������UT�����ʱ */
    UINT8_S  acArbFlag = DEFAULT_ZERO;      /* ��������ARB��ʶ */
    UINT8_S  trainCleanFlag = DEFAULT_ZERO; /* �г���ɨ���α�ʶ */
    UINT16_S cleanTrainId = DEFAULT_ZERO;   /* ��ɨ�г�ID */
    UINT8_S  acArbRedundance = DEFAULT_ZERO;      /* ��������ARB�����ʱ */
    UINT8_S  tmpRtn = RETURN_ERROR;         /* ��ȡ�������г�ID���鷵��ֵ */
    UINT8_S  trainOfAcNum = DEFAULT_ZERO;   /* �������г����� */
    UINT16_S trainIdSequBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};  /* �������г�ID���� */ 
    UINT8_S  tmpRtn1 = RETURN_ERROR;        /* ��ȡ������ǰһ�����г�ID���鷵��ֵ */
    UINT8_S  lastTrainOfAcNum = DEFAULT_ZERO;   /* ������ǰһ�����г����� */
    UINT16_S lastTrainSequenceBuff[SIZE_MAX_TRAINOFAC] = {DEFAULT_ZERO};  /* ������ǰһ�����г�ID���� */ 
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    MemorySet(trainIdSequBuff,(UINT32_S)(sizeof(trainIdSequBuff)),DEFAULT_ZERO,(UINT32_S)(sizeof(trainIdSequBuff)));
    MemorySet(lastTrainSequenceBuff,(UINT32_S)(sizeof(lastTrainSequenceBuff)),DEFAULT_ZERO,(UINT32_S)(sizeof(lastTrainSequenceBuff)));

    LogPrintf(1U,"AC\n");

    acCurSum = GetAcCurSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(acCurSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < acCurSum;cycle++)
    {
        id = GetAcId(cycle);

        acLockDir = GetAcDirection(id);

        acLockStatus = GetAcBelock(id);

        acStatus = GetAcStatusNow(id);

        acUtFlag = GetAcUtFlag(id);

        acUtRedundance = GetAcUtRedundance(id);

        acArbFlag = GetAcArbFlag(id);

        acArbRedundance = GetAcArbRedundance(id);

        trainCleanFlag = GetAcTrainCleanFlag(id);

        cleanTrainId= GetAcCleanTrainId(id);

        trainOfAcNum = GetAcTrainOfAcNum(id);
        tmpRtn = GetAcTrainSequenceBuff(id,SIZE_MAX_TRAINOFAC,trainIdSequBuff);

        lastTrainOfAcNum = GetLastTrainOfAcNum(id);
        tmpRtn1 = GetLastTrainSequenceBuf(id,SIZE_MAX_TRAINOFAC,lastTrainSequenceBuff);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"AC[%d],Dir=%d,Lock=%d,Status=%d,",id,acLockDir,acLockStatus,acStatus);

        LogPrintf(1U,"UtFlag=%d,UtRed=%d,ArbFlag=%d,ArbRed=%d,",acUtFlag,acUtRedundance,acArbFlag,acArbRedundance);

        LogPrintf(1U,"CleanFlag=%d,CleanTrainId=%d,TSum=%d,",trainCleanFlag,cleanTrainId,trainOfAcNum);

        LogPrintf(1U,"TrainId=[");
        for (cycleOther = 0U;cycleOther < trainOfAcNum;cycleOther++)
        {
            LogPrintf(1U,"%d,",trainIdSequBuff[cycleOther]);
        }
        LogPrintf(1U,"],");

        LogPrintf(1U,"LTrainNum=%d,LTrainId=[",lastTrainOfAcNum);

        for (cycleOther = 0U;cycleOther < lastTrainOfAcNum;cycleOther++)
        {
            LogPrintf(1U,"%d,",lastTrainSequenceBuff[cycleOther]);
        }

        LogPrintf(1U,"]\n");

#elif defined SYS_TYPE_VXWORKS	

        if(0u == (cycle % 3u))
        {
            LogPrintf(1U,"\n"); 
        }

        LogPrintf(1U,"[%d]:%d,%d,%d,%d-%d,",id,acLockDir,acLockStatus,acStatus,acUtFlag,acUtRedundance);

        LogPrintf(1U,"%d-%d,%d,%d,%d,",acArbFlag,acArbRedundance,trainCleanFlag,cleanTrainId,trainOfAcNum);

        LogPrintf(1U,"[");		
        for (cycleOther = 0U;cycleOther < trainOfAcNum;cycleOther++)
        {		    
            LogPrintf(1U,"%d,",trainIdSequBuff[cycleOther]);			
        }	
        LogPrintf(1U,"],");

        LogPrintf(1U,"%d,",lastTrainOfAcNum);
        LogPrintf(1U,"[");
        for (cycleOther = 0U;cycleOther < lastTrainOfAcNum;cycleOther++)
        {
            LogPrintf(1U,"%d,",lastTrainSequenceBuff[cycleOther]);
        }
        LogPrintf(1U,"];"); 
#else

#endif

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = acLockDir;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = acLockStatus;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = acStatus;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = acUtFlag;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = acUtRedundance;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = acArbFlag;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = acArbRedundance;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = trainCleanFlag;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(cleanTrainId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = trainOfAcNum;
        tmpIndex = tmpIndex + 1u;

        for (cycleOther = 0U;cycleOther < trainOfAcNum;cycleOther++)
        {
            ShortToChar(trainIdSequBuff[cycleOther],&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;;
        }

#endif 

    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND

    *(GetgMaintainLen()) = tmpIndex;

#endif 
}

/*************************************************
������:      LogPrintfDR
��������:    ��ӡZCά����Ϣ��DR����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfDR(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S dRBtnSum = DEFAULT_ZERO;
    UINT16_S dRLampSum = DEFAULT_ZERO;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  status = DEFAULT_ZERO;
    UINT16_S   trainId = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    LogPrintf(1U,"DrB\n");

    dRBtnSum = GetDRButtonSum();
    dRLampSum = GetDRLampSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(dRBtnSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < dRBtnSum;cycle++)
    {
        id = GetDRButtonId(cycle);
        status = GetDRButtonStatus(id);
        trainId = GetDRButtonOfTrainId(id);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"DR[%d],ButtonStatus=%d,TrainId=%d\n", trainId,status,trainId);

#elif defined SYS_TYPE_VXWORKS	

        LogPrintf(1U,"%d,%d,%d;", trainId,status,trainId);

#else

#endif

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = status;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(trainId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

#endif


    }

    LogPrintf(1U,"\nDrL\n");

#ifdef LOG_ANOTHER_METHOND

    ShortToChar(dRLampSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < dRLampSum;cycle++)
    {
        id = GetDRLampId(cycle);
        status = GetDRLampCommand(id);
        trainId = GetDRLampOfTrainId(id);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"DR[%d],LampCmd=%d,TrainId=%d;",id,status,trainId);

#elif defined SYS_TYPE_VXWORKS	

        LogPrintf(1U,"%d,%d,%d;",id,status,trainId);

#else

#endif

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = status;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(trainId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

#endif
    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 

}

/*************************************************
������:      LogPrintfESB
��������:    ��ӡZCά����Ϣ��ESB����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfESB(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S esbSum = DEFAULT_ZERO;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  status = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    LogPrintf(1U,"ESB\n");

    esbSum = GetEsbSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(esbSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 
    for (cycle = 0U;cycle < esbSum;cycle++)
    {
        id = GetEsbId(cycle);
        status = GetEsbStatus(id);

#ifdef SYS_TYPE_WINDOWS
        LogPrintf(1U,"ESB[%d],Status=%d;",id,status);

        if((cycle % 10U) == 9U)
        {
            LogPrintf(1U,"\n");
        }

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"%d,%d;",id,status);	

#else

#endif

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = status;
        tmpIndex = tmpIndex + 1u;

#endif 

    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 

}

/*************************************************
������:      LogPrintfLogicSection
��������:    ��ӡZCά����Ϣ��LOGICSECTION����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfLogicSection(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S logicSectionSum = DEFAULT_ZERO;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  status = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    LogPrintf(1U,"Ls\n");

    logicSectionSum = GetLogicSectionSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(logicSectionSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < logicSectionSum;cycle++)
    {
        id = GetLogicSectionId(cycle);
        status = GetLogicSectionOccStatus(id);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"Ls[%d,%d];",id,status);

        if((cycle % 20U) == 19U)
        {
            LogPrintf(1U,"\n");
        }

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"%d,%d;",id,status);

#else

#endif

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = status;
        tmpIndex = tmpIndex + 1u;

#endif 

    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 

}

/*************************************************
������:      LogPrintfOverlap
��������:    ��ӡZCά����Ϣ��OverLap����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfOverlap(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S overlapSum = DEFAULT_ZERO;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  status = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    LogPrintf(1U,"Overlap\n");

    overlapSum = GetOverlapSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(overlapSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 
    for (cycle = 0U;cycle < overlapSum;cycle++)
    {
        id = GetOverlapId(cycle);
        status = GetOverlapStatus(id);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"Overlap[%d,%d];",id,status);

        if((cycle % 10U) == 9U)
        {
            LogPrintf(1U,"\n");
        }

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"%d,%d;",id,status);	

#else

#endif

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = status;
        tmpIndex = tmpIndex + 1u;

#endif 

    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 
}

/*************************************************
������:      LogPrintfRoute
��������:    ��ӡZCά����Ϣ��Route����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfRoute(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S routeSum = DEFAULT_ZERO;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  status = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */


    LogPrintf(1U,"Route\n");

    routeSum = GetRouteSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(routeSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle <  routeSum;cycle++)
    {
        id = GetRouteId(cycle);
        status = GetRouteStatus(id);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"Route[%d,%d];",id,status);

        if((cycle % 12U) == 11U)
        {
            LogPrintf(1U,"\n");
        }

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"%d,%d;",id,status);

#else

#endif

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = status;
        tmpIndex = tmpIndex + 1u;

#endif 

    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 
}

/*************************************************
������:      LogPrintfSignal
��������:    ��ӡZCά����Ϣ��Signal����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfSignal(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S signalSum = 0U;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  status = DEFAULT_ZERO;         /* ����״̬ */
    UINT8_S crossStatus = DEFAULT_ZERO;     /* ��ѹ״̬ */
    UINT8_S lightOffStatus = DEFAULT_ZERO;  /* ����״̬ */
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    LogPrintf(1U,"Signal\n");

    signalSum = GetSignalSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(signalSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < signalSum;cycle++)
    { 
        id = GetSignalId(cycle);
        status = GetSignalStatus(id);
        crossStatus = GetSignalCrossStatus(id);
        lightOffStatus = GetSignalLightOffStatus(id);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"Signal[%d],KF=%d,CS=%d,LOS=%d;",id,status,crossStatus,lightOffStatus);

        if((cycle % 5U) == 4U)
        {
            LogPrintf(1U,"\n");
        }

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"%d,%d,%d,%d;",id,status,crossStatus,lightOffStatus);

#else

#endif	

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = status;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = crossStatus;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = lightOffStatus;
        tmpIndex = tmpIndex + 1u;

#endif 

    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 
}

/*************************************************
������:      LogPrintfSwitch
��������:    ��ӡZCά����Ϣ��SWITCH����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfSwitch(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT16_S switchSum = DEFAULT_ZERO;
    UINT16_S id = DEFAULT_ZERO;
    UINT8_S  lockStatus = DEFAULT_ZERO;     /* ����״̬ */
    UINT8_S  posStatus = DEFAULT_ZERO;      /* λ��״̬ */
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    LogPrintf(1U,"Switch\n");

    switchSum = GetSwitchSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(switchSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle <  switchSum;cycle++)
    {
        id = GetSwitchId(cycle);
        lockStatus = GetSwitchLock(id);
        posStatus = GetSwitchPosStatus(id);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"Switch[%d],Lock=%d,PosStatus=%d;", id,lockStatus,posStatus);

        if ((cycle % 24U) == 23U)
        {
            LogPrintf(1U,"\n");
        }

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"%d,%d,%d;",  id,lockStatus,posStatus);	

#else

#endif		

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(id,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = lockStatus;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = posStatus;
        tmpIndex = tmpIndex + 1u;

#endif 


    }

    LogPrintf(1U,"\n");

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 
}

/*************************************************
������:      LogPrintfMA
��������:    ��ӡZCά����Ϣ��MA����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfMA(void)
{ 
    LogMaCalcBySelf();
    LogMaCalcByNzc();
}

/*************************************************
������:      LogMaCalcBySelf
��������:    ��ӡ��ZC�����MA��Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
static void LogMaCalcBySelf(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S cycleObs = DEFAULT_ZERO;
    UINT8_S cycleTsr = DEFAULT_ZERO;
    UINT16_S maStatusSum = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */
    UINT16_S  trainId = DEFAULT_ZERO;       /* �г�ID */
    UINT8_S  maEndObsType = DEFAULT_ZERO;   /* MA�յ��ϰ������� */
    UINT8_S  maEndAttribute =DEFAULT_ZERO;  /* MA�յ����� */
    UINT8_S  maHeadDir = DEFAULT_UINT8_VALUE;      /* MA��㷽�� */
    UINT16_S maHeadLink = DEFAULT_UINT16_VALUE;     /* MA���Link */
    UINT32_S maHeadOffset = DEFAULT_UINT32_VALUE;   /* MA���Offset */ 
    UINT8_S  maTailDir = DEFAULT_UINT8_VALUE;       /* MA�յ㷽�� */
    UINT16_S maTailLink = DEFAULT_UINT16_VALUE;     /* MA�յ�Link */
    UINT32_S maTailOffset = DEFAULT_UINT32_VALUE;   /* MA�յ�Offset */ 
    UINT8_S  maType = DEFAULT_UINT8_VALUE;          /* MA���� */
    UINT8_S  maObsNum = DEFAULT_ZERO;               /* MA��Χ���ϰ������� */
    UINT8_S  tmp1 = RETURN_ERROR;                   /* ��ȡMA��Χ���ϰ���ṹ�����鷵��ֵ */
    ObsOfMAStruct obs1StruBuff[MA_AREA_OBS_SUM_MAX]={DEFAULT_ZERO};
    UINT8_S  maTsrNum = DEFAULT_ZERO;               /* MA��Χ����ʱ�������� */
    UINT8_S  tmp2 = RETURN_ERROR;                   /* ��ȡMA��Χ����ʱ���ٽṹ�����鷵��ֵ */
    TsrOfMAStruct tsrOfMAStruBuff[MA_AREA_TSR_SUM_MAX] = {DEFAULT_ZERO};


    /*��ʼ������ṹ������*/
    MemorySet(&obs1StruBuff[0],((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))));
    MemorySet(tsrOfMAStruBuff,((UINT32_S)(sizeof(TsrOfMAStruct)*MA_AREA_TSR_SUM_MAX)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(TsrOfMAStruct)*MA_AREA_TSR_SUM_MAX)));

    maStatusSum = GetMaStatusSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(maStatusSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < maStatusSum;cycle++)
    {
        trainId = GetMaStatusTrainId(cycle);
        maEndObsType = GetMaEndObsType(trainId);
        maEndAttribute = GetMaEndAttribute(trainId);
        maHeadDir = GetMaHeadDir(trainId);
        maHeadLink = GetMaHeadLink(trainId);
        maHeadOffset = GetMaHeadOffset(trainId);
        maTailDir = GetMaTailDir(trainId);
        maTailLink = GetMaTailLink(trainId);
        maTailOffset = GetMaTailOffset(trainId);
        maType = GetMaType(trainId);

        maObsNum = GetMaObsNum(trainId);
        tmp1 = GetObsOfMAStru(trainId,MA_AREA_OBS_SUM_MAX,obs1StruBuff);

        maTsrNum = GetMaTsrNum(trainId);
        tmp2 = GetTsrOfMAStru(trainId,MA_AREA_TSR_SUM_MAX,tsrOfMAStruBuff);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"MA[%d],EndObsType=%d,EndAtt=%d,",trainId,maEndObsType,maEndAttribute);

        LogPrintf(1U,"HDir=%d,HLink=%d,HOffset=%d,",maHeadDir,maHeadLink,maHeadOffset);

        LogPrintf(1U,"TDir=%d,TLink=%d,TOffset=%d,",maTailDir,maTailLink,maTailOffset);

        LogPrintf(1U,"Type=%d,ObsNum=%d,",maType,maObsNum);

        LogPrintf(1U,"ObsInfo=");
        for(cycleObs = 0U;cycleObs < maObsNum;cycleObs++)
        {
            LogPrintf(1U,"%d+%d+0x%x+0x%x,",obs1StruBuff[cycleObs].ObsId,obs1StruBuff[cycleObs].ObsType,
                obs1StruBuff[cycleObs].ObsStatus,obs1StruBuff[cycleObs].ObsLockStatus);
        }

        LogPrintf(1U,"TsrNum=%d,",maTsrNum);
        for (cycleTsr = 0U;cycleTsr < maTsrNum;cycleTsr++)
        {
            LogPrintf(1U,"ZcId=%d,speed=%d,HLink=%d,HOffset=%d,TLink=%d,TOffset=%d",
                tsrOfMAStruBuff[cycleTsr].BelongZcId,tsrOfMAStruBuff[cycleTsr].TsrSpeed,
                tsrOfMAStruBuff[cycleTsr].TsrHeadLink,tsrOfMAStruBuff[cycleTsr].TsrHeadOffset,
                tsrOfMAStruBuff[cycleTsr].TsrTailLink,tsrOfMAStruBuff[cycleTsr].TsrTailOffset);			
        }
        LogPrintf(1U,"\n");

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"Ma[%d]:%d,%d,",trainId,maEndObsType,maEndAttribute);
        LogPrintf(1U,"%d,%d,%d,",maHeadDir,maHeadLink,maHeadOffset);
        LogPrintf(1U,"%d,%d,%d,",maTailDir,maTailLink,maTailOffset);
        LogPrintf(1U,"%d,%d,",maType,maObsNum);

        for(cycleObs = 0U;cycleObs < maObsNum;cycleObs++)
        {	    
            LogPrintf(1U,"%d+%d+0x%x+0x%x,",obs1StruBuff[cycleObs].ObsId,obs1StruBuff[cycleObs].ObsType,
                obs1StruBuff[cycleObs].ObsStatus,obs1StruBuff[cycleObs].ObsLockStatus);
        }

        LogPrintf(1U,"%d,",maTsrNum);
        for (cycleTsr = 0U;cycleTsr < maTsrNum;cycleTsr++)
        {		    
            LogPrintf(1U,"%d,%d,%d,%d,%d,%d,",
                tsrOfMAStruBuff[cycleTsr].BelongZcId,tsrOfMAStruBuff[cycleTsr].TsrSpeed,
                tsrOfMAStruBuff[cycleTsr].TsrHeadLink,tsrOfMAStruBuff[cycleTsr].TsrHeadOffset,
                tsrOfMAStruBuff[cycleTsr].TsrTailLink,tsrOfMAStruBuff[cycleTsr].TsrTailOffset);				
        }

        LogPrintf(1U,"\n");				
#else

#endif  

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(trainId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = maEndObsType;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = maEndAttribute;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = maHeadDir;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(maHeadLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(maHeadOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        pTmp[tmpIndex] = maTailDir;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(maTailLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(maTailOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        pTmp[tmpIndex] = maType;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = maObsNum;
        tmpIndex = tmpIndex + 1u;

        for(cycleObs = 0U;cycleObs < maObsNum;cycleObs++)
        {	    
            ShortToChar(obs1StruBuff[cycleObs].ObsId,&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;

            pTmp[tmpIndex] = obs1StruBuff[cycleObs].ObsType;
            tmpIndex = tmpIndex + 1u;

            pTmp[tmpIndex] = obs1StruBuff[cycleObs].ObsStatus;
            tmpIndex = tmpIndex + 1u;

            pTmp[tmpIndex] = obs1StruBuff[cycleObs].ObsLockStatus;
            tmpIndex = tmpIndex + 1u;
        }

        pTmp[tmpIndex] = maTsrNum;
        tmpIndex = tmpIndex + 1u;

        for (cycleTsr = 0U;cycleTsr < maTsrNum;cycleTsr++)
        {		
            ShortToChar(tsrOfMAStruBuff[cycleTsr].BelongZcId,&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;

            ShortToChar(tsrOfMAStruBuff[cycleTsr].TsrSpeed,&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;

            ShortToChar(tsrOfMAStruBuff[cycleTsr].TsrHeadLink,&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;

            LongToChar(tsrOfMAStruBuff[cycleTsr].TsrHeadOffset,&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 4u;

            ShortToChar(tsrOfMAStruBuff[cycleTsr].TsrTailLink,&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;

            LongToChar(tsrOfMAStruBuff[cycleTsr].TsrTailOffset,&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 4u;		
        }      
#endif

    }

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 

}

/*************************************************
������:      LogMaCalcByNzc
��������:    ��ӡ����ZC�����MA��Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
static void LogMaCalcByNzc(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S cycleObs = DEFAULT_ZERO;
    UINT8_S cycleTsr = DEFAULT_ZERO;
    UINT16_S nextZcMaStatusSum = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */
    UINT16_S  trainId = DEFAULT_ZERO;       /* �г�ID */
    UINT16_S  nextId = DEFAULT_ZERO;        /* ����MA2��ZcId*/
    UINT8_S   handOutType = DEFAULT_ZERO;   /* ����ZC�����Ϣ */
    UINT8_S   maInfoFlag = DEFAULT_ZERO;    /* ����ZC�������Ϣ���Ƿ����MA��Ϣ */
    UINT8_S   maLen = DEFAULT_ZERO;         /* ����ZC�����MA�ĳ��� */
    UINT8_S   maHeadDir = DEFAULT_UINT8_VALUE;       /* ����ZC�����MA��㷽�� */
    UINT16_S  maHeadLink = DEFAULT_UINT16_VALUE;     /* ����ZC�����MA���Link */
    UINT32_S  maHeadOffset = DEFAULT_UINT32_VALUE;   /* ����ZC�����MA���Offset */ 
    UINT8_S   maTailDir = DEFAULT_UINT8_VALUE;       /* ����ZC�����MA�յ㷽�� */
    UINT16_S  maTailLink = DEFAULT_UINT16_VALUE;     /* ����ZC�����MA�յ�Link */
    UINT32_S  maTailOffset = DEFAULT_UINT32_VALUE;   /* ����ZC�����MA�յ�Offset */ 
    UINT8_S   maEndAttribute =DEFAULT_ZERO;            /* ����ZC�����MA�յ����� */
    UINT8_S   maObsNum = DEFAULT_ZERO;                /* ����ZC�����MA��Χ���ϰ������� */
    UINT8_S   tmp1 = RETURN_ERROR;                    /* ����ZC����Ļ�ȡMA��Χ���ϰ���ṹ�����鷵��ֵ */
    ObsOfMAStruct obs1StruBuff[MA_AREA_OBS_SUM_MAX]={DEFAULT_ZERO};
    UINT8_S  maTsrNum = DEFAULT_ZERO;               /* MA��Χ����ʱ�������� */
    UINT8_S  tmp2 = RETURN_ERROR;                   /* ��ȡMA��Χ����ʱ���ٽṹ�����鷵��ֵ */
    TsrOfMAStruct tsrOfMAStruBuff[MA_AREA_TSR_SUM_MAX] = {DEFAULT_ZERO};

    /*��ʼ������ṹ������*/
    MemorySet(&obs1StruBuff[0],((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))),
        0U,((UINT32_S)(MA_AREA_OBS_SUM_MAX*sizeof(ObsOfMAStruct))));
    MemorySet(tsrOfMAStruBuff,((UINT32_S)(sizeof(TsrOfMAStruct)*MA_AREA_TSR_SUM_MAX)),
        DEFAULT_ZERO,((UINT32_S)(sizeof(TsrOfMAStruct)*MA_AREA_TSR_SUM_MAX)));

    nextZcMaStatusSum = GetNextZcMaStatusSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(nextZcMaStatusSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < nextZcMaStatusSum;cycle++)
    {
        trainId = gNextZcDataStruBuff[cycle].TrainID;
        nextId = GetNextZcId(trainId);
        handOutType = GetNextZcHandOutType(trainId);
        maInfoFlag = GetNextZcMaInfoFlag(trainId);
        maLen = GetNextZcMaStatusMaLength(trainId);
        maHeadDir = GetNextZcMaHeadDir(trainId);
        maHeadLink = GetNextZcMaHeadLink(trainId);
        maHeadOffset = GetNextZcMaHeadOffset(trainId);
        maTailDir = GetNextZcMaTailDir(trainId);
        maTailLink = GetNextZcMaTailLink(trainId);
        maTailOffset = GetNextZcMaTailOffset(trainId);
        maEndAttribute = GetNextZcMaEndAttribute(trainId);

        maObsNum = GetNextZcMaTsrNum(trainId);
        tmp1 = GetNextZcObsOfMAStru(trainId,obs1StruBuff);

        maTsrNum = GetMaTsrNum(trainId);
        tmp2 = GetNextZcTsrOfMAStru(trainId,tsrOfMAStruBuff);

#ifdef SYS_TYPE_WINDOWS

        LogPrintf(1U,"NextID=%d,NextZcId=%d,HandOutType=%d,",trainId,nextId,handOutType);      
        LogPrintf(1U,"InfoFlag=%d,Length=%d,",maInfoFlag,maLen);
        LogPrintf(1U,"HeadDir=%d,HeadLink=%d,HeadOffset=%d,",maHeadDir,maHeadLink,maHeadOffset);
        LogPrintf(1U,"TailDir=%d,TailLink=%d,TailOffset=%d,",maTailDir,maTailLink,maTailOffset);
        LogPrintf(1U,"EndAttribute=%d,ObsNum=%d,",maEndAttribute,maObsNum);

        LogPrintf(1U,"ObsInfo=");
        for(cycleObs = 0U;cycleObs < maObsNum;cycleObs++)
        {
            LogPrintf(1U,"%d+%d+0x%x+0x%x,",obs1StruBuff[cycleObs].ObsId,obs1StruBuff[cycleObs].ObsType,
                obs1StruBuff[cycleObs].ObsStatus,obs1StruBuff[cycleObs].ObsLockStatus);
        }

        LogPrintf(1U,"TsrNum=%d,",maTsrNum);
        for (cycleTsr = 0U;cycleTsr < maTsrNum;cycleTsr++)
        {
            LogPrintf(1U,"ZcId=%d,speed=%d,HLink=%d,HOffset=%d,TLink=%d,TOffset=%d",
                tsrOfMAStruBuff[cycleTsr].BelongZcId,tsrOfMAStruBuff[cycleTsr].TsrSpeed,
                tsrOfMAStruBuff[cycleTsr].TsrHeadLink,tsrOfMAStruBuff[cycleTsr].TsrHeadOffset,
                tsrOfMAStruBuff[cycleTsr].TsrTailLink,tsrOfMAStruBuff[cycleTsr].TsrTailOffset);			
        }
        LogPrintf(1U,"\n");

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"NTId=%d,NZcId=%d,%d,",trainId,nextId,handOutType);
        LogPrintf(1U,"%d,Len=%d,",maInfoFlag,maLen);
        LogPrintf(1U,"%d,%d,%d,",maHeadDir,maHeadLink,maHeadOffset);
        LogPrintf(1U,"%d,%d,%d,",maTailDir,maTailLink,maTailOffset);
        LogPrintf(1U,"%d,%d,",maEndAttribute,maObsNum);

        for(cycleObs = 0U;cycleObs < maObsNum;cycleObs++)
        {
            LogPrintf(1U,"%d+%d+0x%x+0x%x,",obs1StruBuff[cycleObs].ObsId,obs1StruBuff[cycleObs].ObsType,
                obs1StruBuff[cycleObs].ObsStatus,obs1StruBuff[cycleObs].ObsLockStatus);
        }

        LogPrintf(1U,"TSrN=%d,",maTsrNum);
        for (cycleTsr = 0U;cycleTsr < maTsrNum;cycleTsr++)
        {		    
            LogPrintf(1U,"%d,%d,%d,%d,%d,%d,",
                tsrOfMAStruBuff[cycleTsr].BelongZcId,tsrOfMAStruBuff[cycleTsr].TsrSpeed,
                tsrOfMAStruBuff[cycleTsr].TsrHeadLink,tsrOfMAStruBuff[cycleTsr].TsrHeadOffset,
                tsrOfMAStruBuff[cycleTsr].TsrTailLink,tsrOfMAStruBuff[cycleTsr].TsrTailOffset);				
        }

        LogPrintf(1U,"\n");	

#else

#endif  

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(trainId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(nextId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = handOutType;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = maInfoFlag;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = maHeadDir;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(maHeadLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(maHeadOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        pTmp[tmpIndex] = maTailDir;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(maTailLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(maTailOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        pTmp[tmpIndex] = maObsNum;
        tmpIndex = tmpIndex + 1u;

        for(cycleObs = 0U;cycleObs < maObsNum;cycleObs++)
        {	    
            ShortToChar(obs1StruBuff[cycleObs].ObsId,&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;

            pTmp[tmpIndex] = obs1StruBuff[cycleObs].ObsType;
            tmpIndex = tmpIndex + 1u;

            pTmp[tmpIndex] = obs1StruBuff[cycleObs].ObsStatus;
            tmpIndex = tmpIndex + 1u;

            pTmp[tmpIndex] = obs1StruBuff[cycleObs].ObsLockStatus;
            tmpIndex = tmpIndex + 1u;
        }
        /*
        pTmp[tmpIndex] = maTsrNum;
        tmpIndex = tmpIndex + 1u;

        for (cycleTsr = 0U;cycleTsr < maTsrNum;cycleTsr++)
        {		
        ShortToChar(tsrOfMAStruBuff[cycleTsr].BelongZcId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(tsrOfMAStruBuff[cycleTsr].TsrSpeed,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(tsrOfMAStruBuff[cycleTsr].TsrHeadLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(tsrOfMAStruBuff[cycleTsr].TsrHeadOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        ShortToChar(tsrOfMAStruBuff[cycleTsr].TsrTailLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(tsrOfMAStruBuff[cycleTsr].TsrTailOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;		
        } 
        */
#endif 
    }


#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 

}

/*************************************************
������:      LogPrintfTrain
��������:    ��ӡZCά����Ϣ��TRAIN����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfTrain(void)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S cycleRoute = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */
    UINT8_S trainCurSum = DEFAULT_ZERO;
    UINT8_S tmpRtn = DEFAULT_ZERO;
    UINT8_S matchRouteNum = DEFAULT_ZERO;
    UINT16_S routeIdBuff[SIZE_MAX_ROUTENUM] = {DEFAULT_ZERO};
    UINT16_S trainId = DEFAULT_ZERO;       /* �г�ID    */
    UINT16_S changeLineId = DEFAULT_ZERO;  /* �л���·Id */
    UINT16_S commRed = DEFAULT_UINT16_VALUE; /* ��ʧͨ�������� */
    UINT8_S  commStatus = DEFAULT_ZERO;      /* ͨ��״̬ */
    UINT16_S trainControlZC = DEFAULT_ZERO;  /* �г��ܿ�ZC��ID*/ 
    UINT8_S  handoverInType = DEFAULT_UINT8_VALUE;
    UINT8_S  handoverOutType = DEFAULT_UINT8_VALUE;
    UINT8_S  trainInType = DEFAULT_UINT8_VALUE;   /* ATP�������� */
    UINT8_S  trainOutType = DEFAULT_UINT8_VALUE;  /* ��ATP������� */
    UINT8_S  trainStatus = DEFAULT_UINT8_VALUE;   /* �г�״̬ */
    UINT8_S  trainType = DEFAULT_UINT8_VALUE;     /* �г����� */ 
    UINT8_S  suspectHead = DEFAULT_UINT8_VALUE;   /* ǰ�˿��ɱ�ʶ */
    UINT8_S  suspectTail = DEFAULT_UINT8_VALUE;   /* ��˿��ɱ�ʶ */
    UINT8_S  trainLevel = DEFAULT_UINT8_VALUE;    /* �г����� */
    UINT8_S  trainMode = DEFAULT_UINT8_VALUE;     /* �г�ģʽ */
    UINT8_S  trainUnsafeDir = DEFAULT_UINT8_VALUE;   /* �������з��� */
    UINT8_S  trainRealDir = DEFAULT_UINT8_VALUE;   /* ʵ�����з��� */
    UINT16_S trainHeadAC = DEFAULT_UINT16_VALUE;   /* ��ȫ��ͷ������������ */
    UINT16_S trainTailAC = DEFAULT_UINT16_VALUE;   /* ��ȫ��β������������ */
    UINT16_S trainUnsafeHeadAC = DEFAULT_UINT16_VALUE;   /* �ǰ�ȫ��ͷ������������ */
    UINT16_S trainUnsafeTailAC = DEFAULT_UINT16_VALUE;   /* �ǰ�ȫ��β������������ */
    TrainSafeLocStruct trainSafeLocStru;
    TrainSafeLocStruct trainUnsafeLocStru;
    UINT8_S preSectionNum = DEFAULT_ZERO;  /* ������ռѹ�߼��������� */
    UINT16_S preSectionIdBuff[SIZE_MAX_SECTION_OF_TRAIN] = {0U};
    UINT16_S trainSpeed = DEFAULT_UINT16_VALUE;  /* �г��ٶ� */
    UINT8_S  signalProtection = DEFAULT_UINT8_VALUE; /* ���źű�ʶ */
    UINT32_S trainCycle = DEFAULT_ZERO;  /* �г����ں� */
    UINT8_S  trainEmergency = DEFAULT_ZERO; /* ������ʶ */
    UINT16_S trainError = DEFAULT_UINT16_VALUE;  /* ��ȷ����� */
    UINT16_S trainFrontSignal = DEFAULT_UINT16_VALUE; /* �г�ǰ����Ҫ�������ź�ID */
    UINT8_S  trainIntegrity = DEFAULT_UINT8_VALUE;    /* �г������Ա�ʶ */
    UINT8_S  trainStopArea = DEFAULT_UINT8_VALUE;     /* �г�ͣ�ȱ�ʶ */

    MemorySet(&trainSafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
    MemorySet(&trainUnsafeLocStru,((UINT32_S)(sizeof(TrainSafeLocStruct))),0U,((UINT32_S)(sizeof(TrainSafeLocStruct))));
    MemorySet(&preSectionIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)),
        0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_SECTION_OF_TRAIN)));
    MemorySet(&routeIdBuff[0],((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)),0U,((UINT32_S)(SIZE_UINT16 * SIZE_MAX_ROUTENUM)));

    trainCurSum = GetTrainCurSum();

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(trainCurSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

#endif 

    for (cycle = 0U;cycle < trainCurSum;cycle++)
    {
        trainId = GetTrainIdOfIndex(cycle);
        changeLineId = GetTrainChangeLineId(trainId);
        commRed = GetCommTargetCycle(INNER_DEVTYPE_TRAIN,trainId);
        commStatus = GetCommTargetStatus(INNER_DEVTYPE_TRAIN,trainId);
        trainControlZC = GetTrainControlZc(trainId);
        handoverInType= GetTrainHandoverInType(trainId);
        handoverOutType= GetTrainHandoverOutType(trainId);
        trainInType = GetTrainInType(trainId);
        trainOutType = GetTrainOutType(trainId);
        trainStatus = GetTrainStatus(trainId);
        trainType = GetTrainType(trainId);

        suspectHead = GetTrainSuspectHead(trainId);
        suspectTail = GetTrainSuspectTail(trainId);
        trainLevel = GetTrainLevel(trainId);    
        trainMode = GetTrainMode(trainId);    
        trainUnsafeDir = GetTrainUnsafeDirection(trainId);   
        trainRealDir = GetTrainRealDirection(trainId);
        matchRouteNum = GetMatchRouteNum(trainId);
        tmpRtn = GetTrainMatchedRouteIdBuff(trainId,routeIdBuff);

        trainHeadAC = GetTrainTrainHeadAC(trainId);   
        trainTailAC = GetTrainTrainTailAC(trainId);   
        trainUnsafeHeadAC = GetTrainUnsafeTrainHeadAC(trainId);   
        trainUnsafeTailAC = GetTrainUnsafeTrainTailAC(trainId);   
        tmpRtn = GetTrainSafeLoc(trainId,&trainSafeLocStru);
        tmpRtn = GetTrainUnSafeLoc(trainId,&trainUnsafeLocStru);
        preSectionNum = GetTrainPreSectionNum(trainId);

        tmpRtn = GetTrainPreSectionId(trainId,preSectionIdBuff);
        trainSpeed = GetTrainSpeed(trainId);
        signalProtection = GetTrainSignalProtection(trainId);
        trainCycle= GetTrainCycle(trainId);
        trainEmergency = GetTrainEmergency(trainId);
        trainError = GetTrainError(trainId);
        trainFrontSignal = GetTrainFrontSignal(trainId);
        trainIntegrity = GetTrainIntegrity(trainId);
        trainStopArea = GetTrainStopArea(trainId);

#ifdef SYS_TYPE_WINDOWS
        LogPrintf(1U,"Train[%d],ChangeLineId=%d,CommRed=%d,CommStatus=%d,",trainId,changeLineId,commRed,commStatus);
        LogPrintf(1U,"ControlZC=%d,HIT=%d,HOT=%d,",trainControlZC,handoverInType,handoverOutType);
        LogPrintf(1U,"InType=%d,OutType=%d,Status=%d,TrainType=%d,",trainInType,trainOutType,trainStatus,trainType);
        LogPrintf(1U,"HeadF=%d,TailF=%d,Level=%d,Mode=%d,",suspectHead,suspectTail,trainLevel,trainMode);
        LogPrintf(1U,"UDir=%d,RDir=%d,",trainUnsafeDir,trainRealDir);

        LogPrintf(1U,"RouteID=[");		
        for (cycleRoute = 0U;cycleRoute < matchRouteNum;cycleRoute++)
        {
            LogPrintf(1U,"%d,",routeIdBuff[cycleRoute]);
        }
        LogPrintf(1U,"]\n");

        LogPrintf(1U,"HeadAC=%d,TailAC=%d,UHeadAC=%d,UTailAC=%d,",trainHeadAC,trainTailAC,trainUnsafeHeadAC,trainUnsafeTailAC);

        LogPrintf(1U,"SafeLoc=[%d+%d,%d+%d],",trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,
            trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset);

        LogPrintf(1U,"UnSafeLoc=[%d+%d,%d+%d],",trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,
            trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

        LogPrintf(1U,"LSNum=%d,LSId=[",preSectionNum);

        for (cycleRoute = 0U;cycleRoute < preSectionNum;cycleRoute++)
        {
            LogPrintf(1U,"%d,",preSectionIdBuff[cycleRoute]);
        }

        LogPrintf(1U,"],Speed=%d,PSignalF=%d,Cycle=%d,Emergency=%d,",trainSpeed,signalProtection,trainCycle,trainEmergency);
        LogPrintf(1U,"Deviation=%d,FSignal=%d,Integrity=%d,StopArea=%d\n",trainError,trainFrontSignal,trainIntegrity,trainStopArea);

#elif defined SYS_TYPE_VXWORKS

        LogPrintf(1U,"\nTra[%d]:%d,%d,%d,%d,",trainId,changeLineId,commRed,commStatus,trainControlZC);    

        LogPrintf(1U,"%d,%d,%d,%d,",handoverInType,handoverOutType,trainInType,trainOutType);

        LogPrintf(1U,"S=%d,%d,%d,%d,",trainStatus,trainType,suspectHead,suspectTail);

        LogPrintf(1U,"%d,%d,%d,%d,[",trainLevel,trainMode,trainUnsafeDir,trainRealDir);

        for (cycleRoute = 0U;cycleRoute < matchRouteNum;cycleRoute++)
        {
            LogPrintf(1U,"%d,",routeIdBuff[cycleRoute]);
        }

        LogPrintf(1U,"],%d,%d,%d,%d,",trainHeadAC,trainTailAC,trainUnsafeHeadAC,trainUnsafeTailAC);

        LogPrintf(1U,"[%d+%d,%d+%d],",trainSafeLocStru.TrainHeadLink,trainSafeLocStru.TrainHeadOffset,
            trainSafeLocStru.TrainTailLink,trainSafeLocStru.TrainTailOffset);

        LogPrintf(1U,"[%d+%d,%d+%d],",trainUnsafeLocStru.TrainHeadLink,trainUnsafeLocStru.TrainHeadOffset,
            trainUnsafeLocStru.TrainTailLink,trainUnsafeLocStru.TrainTailOffset);

        LogPrintf(1U,"%d,[",preSectionNum);

        for (cycleRoute = 0U;cycleRoute < preSectionNum;cycleRoute++)
        {
            LogPrintf(1U,"%d,",preSectionIdBuff[cycleRoute]);
        }

        LogPrintf(1U,"],V=%d,%d,%d,%d,",trainSpeed,signalProtection,trainCycle,trainEmergency);

        LogPrintf(1U,"%d,%d,%d,%d\n",trainError,trainFrontSignal,trainIntegrity,trainStopArea);

#else

#endif		

#ifdef LOG_ANOTHER_METHOND

        ShortToChar(trainId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(changeLineId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = commRed;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = commStatus;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(trainControlZC,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = handoverInType;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = handoverOutType;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = trainStatus;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = trainType;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = suspectHead;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = suspectTail;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = trainLevel;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = trainMode;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = trainUnsafeDir;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = trainRealDir;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = matchRouteNum;
        tmpIndex = tmpIndex + 1u;

        for (cycleRoute = 0U;cycleRoute < matchRouteNum;cycleRoute++)
        {
            ShortToChar(routeIdBuff[cycleRoute],&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;
        }

        ShortToChar(trainHeadAC,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(trainTailAC,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(trainUnsafeHeadAC,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(trainUnsafeTailAC,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(trainSafeLocStru.TrainHeadLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(trainSafeLocStru.TrainHeadOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        ShortToChar(trainSafeLocStru.TrainTailLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(trainSafeLocStru.TrainTailOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        ShortToChar(trainUnsafeLocStru.TrainHeadLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(trainUnsafeLocStru.TrainHeadOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        ShortToChar(trainUnsafeLocStru.TrainTailLink,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        LongToChar(trainUnsafeLocStru.TrainTailOffset,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        /**/
        pTmp[tmpIndex] = preSectionNum;
        tmpIndex = tmpIndex + 1u;

        for (cycleRoute = 0U;cycleRoute < preSectionNum;cycleRoute++)
        {
            ShortToChar(preSectionIdBuff[cycleRoute],&pTmp[tmpIndex]);
            tmpIndex = tmpIndex + 2u;
        }

        ShortToChar(trainSpeed,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = signalProtection;
        tmpIndex = tmpIndex + 1u;

        LongToChar(trainCycle,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 4u;

        pTmp[tmpIndex] = trainEmergency;
        tmpIndex = tmpIndex + 1u;

        ShortToChar(trainError,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(trainFrontSignal,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        pTmp[tmpIndex] = trainIntegrity;
        tmpIndex = tmpIndex + 1u;

        pTmp[tmpIndex] = trainStopArea;
        tmpIndex = tmpIndex + 1u;

#endif 

    }

#ifdef LOG_ANOTHER_METHOND
    *(GetgMaintainLen()) = tmpIndex;
#endif 

}

/*************************************************
������:      LogPrintfTsr
��������:    ��ӡZCά����Ϣ��TSR����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfTsr(void)
{
    UINT16_S cycle = DEFAULT_ZERO;
    UINT8_S cycleTsr = DEFAULT_ZERO;
    UINT8_S cycleSec = DEFAULT_ZERO;
    UINT16_S tsrOfZcSum = DEFAULT_ZERO;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    tsrOfZcSum = GetTsrOfZcSum();

#ifdef SYS_TYPE_WINDOWS

    for(cycle = 0u;cycle < tsrOfZcSum;cycle++)
    {
        LogPrintf(1U,"TsrZcId=%d,TsrNum=%d,",gTsrDataStruBuff[cycle].BelongZcId,gTsrDataStruBuff[cycle].TsrNum);

        for(cycleTsr = 0u;cycleTsr < gTsrDataStruBuff[cycle].TsrNum;cycleTsr++)
        {
            LogPrintf(1U,"Speed=%d,SectionNum=%d,L[",gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].Speed,
                gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionNum);

            for(cycleSec = 0u;cycleSec < gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionNum;cycleSec++)
            {
                LogPrintf(1U,"%d,",gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionIdBuff[cycleSec]);
            }

            LogPrintf(1U,"]\n");
        }

        LogPrintf(1U,"\n");
    }

#elif defined SYS_TYPE_VXWORKS

    LogPrintf(1U,"tsrOfZc\n");

    /*
    LogPrintf(1U,"%02d",tsrOfZcSum);
    */

    for(cycle = 0u;cycle < tsrOfZcSum;cycle++)
    {
        LogPrintf(1U,"%d-%d\n",gTsrDataStruBuff[cycle].BelongZcId,gTsrDataStruBuff[cycle].TsrNum);

        for(cycleTsr = 0u;cycleTsr < gTsrDataStruBuff[cycle].TsrNum;cycleTsr++)
        {	    
            LogPrintf(1U,"%d,%d,[",gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].Speed,
                gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionNum);

            for(cycleSec = 0u;cycleSec < gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionNum;cycleSec++)
            {		    
                LogPrintf(1U,"%d,",gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionIdBuff[cycleSec]);		
            }		
            LogPrintf(1U,"]\n");		
        }
        LogPrintf(1U,"\n");
    }

#else

#endif

#ifdef LOG_ANOTHER_METHOND
    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    ShortToChar(tsrOfZcSum,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 2u;

    for(cycle = 0u;cycle < tsrOfZcSum;cycle++)
    {
        ShortToChar(gTsrDataStruBuff[cycle].BelongZcId,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        ShortToChar(gTsrDataStruBuff[cycle].TsrNum,&pTmp[tmpIndex]);
        tmpIndex = tmpIndex + 2u;

        for(cycleTsr = 0u;cycleTsr < gTsrDataStruBuff[cycle].TsrNum;cycleTsr++)
        {	    
            pTmp[tmpIndex] = gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].Speed;
            tmpIndex = tmpIndex + 1u;

            pTmp[tmpIndex] = gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionNum;
            tmpIndex = tmpIndex + 1u;

            for(cycleSec = 0u;cycleSec < gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionNum;cycleSec++)
            {		    
                ShortToChar(gTsrDataStruBuff[cycle].SingleTsrDataStru[cycleTsr].SectionIdBuff[cycleSec],&pTmp[tmpIndex]);
                tmpIndex = tmpIndex + 2u;	
            }			
        }
    }

    *(GetgMaintainLen()) = tmpIndex;

#endif 


}

/*************************************************
������:      LogPrintfMicAndSme
��������:    ��ӡͨ�Ű��������ά����Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfMicAndSme(void)
{
    UINT8_S mic1Status = DEFAULT_ZERO;  /* ͨ�Ű�1��״̬����ֵ */
    UINT8_S mic2Status = DEFAULT_ZERO;  /* ͨ�Ű�2��״̬����ֵ */
    UINT8_S sme1Status = DEFAULT_ZERO;  /* ������1��״̬����ֵ */
    UINT8_S mic3Status = DEFAULT_ZERO;  /* ͨ�Ű�3��״̬����ֵ */
    UINT8_S mic4Status = DEFAULT_ZERO;  /* ͨ�Ű�4��״̬����ֵ */
    UINT8_S sme2Status = DEFAULT_ZERO;  /* ������2��״̬����ֵ */
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

#ifdef SYS_TYPE_WINDOWS


#elif defined SYS_TYPE_VXWORKS

    /*LogPrintf(1U,"HardWare\n");*/

    mic1Status = AdptAppInquiryDevStatus(ZC_DEVTYPE_MIC,1u,1u);
    mic2Status = AdptAppInquiryDevStatus(ZC_DEVTYPE_MIC,2u,1u);
    sme1Status = AdptAppInquiryDevStatus(ZC_DEVTYPE_SME,1u,1u);
    mic3Status = AdptAppInquiryDevStatus(ZC_DEVTYPE_MIC,1u,2u);
    mic4Status = AdptAppInquiryDevStatus(ZC_DEVTYPE_MIC,2u,2u);
    sme2Status = AdptAppInquiryDevStatus(ZC_DEVTYPE_SME,1u,2u);


    LogPrintf(1U,"%d-%d-%d;%d-%d-%d\n",mic1Status,mic2Status,sme1Status,mic3Status,mic4Status,sme2Status);
#else

#endif

#ifdef LOG_ANOTHER_METHOND
    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    pTmp[tmpIndex] = mic1Status;
    tmpIndex = tmpIndex + 1u;

    pTmp[tmpIndex] = mic2Status;
    tmpIndex = tmpIndex + 1u;

    pTmp[tmpIndex] = sme1Status;
    tmpIndex = tmpIndex + 1u;

    pTmp[tmpIndex] = mic3Status;
    tmpIndex = tmpIndex + 1u;

    pTmp[tmpIndex] = mic4Status;
    tmpIndex = tmpIndex + 1u;

    pTmp[tmpIndex] = sme2Status;
    tmpIndex = tmpIndex + 1u;

    *(GetgMaintainLen()) = tmpIndex;

#endif 

}


/*************************************************
������:      LogPrintfPOneCommTargetStatus
��������:    ��ӡ����ͨ�Ŷ���ͨ��״̬��Ϣ
����:        const UINT8_S commTargetType ͨ�Ŷ�������ֵ
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfPOneCommTargetStatus(const UINT8_S commTargetType)
{
    UINT8_S cycle = DEFAULT_ZERO;
    UINT8_S commTargetBufIndex = DEFAULT_ZERO;
    UINT8_S singleCommTargetNum = DEFAULT_ZERO;
    UINT16_S commTargetIdBuff[SINGLE_TYPE_COMM_TARGET_SUM_MAX];
    UINT16_S commCycle = DEFAULT_ZERO;
    UINT8_S rtnGet = DEFAULT_ZERO;
    UINT8_S commStatus = DEFAULT_ZERO;  /* ͨ��״̬ */
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    /*��ʼ��*/
    MemorySet(&commTargetIdBuff[DEFAULT_ZERO],sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX,DEFAULT_ZERO,sizeof(UINT16_S)*SINGLE_TYPE_COMM_TARGET_SUM_MAX);

    /*��ȡͨ�Ŷ��������*/
    commTargetBufIndex = GetCommTargetTypeBuffIndex(commTargetType);
    singleCommTargetNum = GetSingleCommTargetTypeSum(commTargetType);
    rtnGet = GetSingleCommTargetIdBuff(commTargetType,SINGLE_TYPE_COMM_TARGET_SUM_MAX,commTargetIdBuff);

#ifdef LOG_ANOTHER_METHOND

    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    pTmp[tmpIndex] = singleCommTargetNum;
    tmpIndex = tmpIndex + 1u;

#endif

    if ((COMM_TYPE_SUM_MAX > commTargetBufIndex)
        && (RETURN_SUCCESS == rtnGet)
        && (SINGLE_TYPE_COMM_TARGET_SUM_MAX > singleCommTargetNum))
    {
        for (cycle = DEFAULT_ZERO;cycle < singleCommTargetNum;cycle++)
        {
            commStatus = GetCommTargetStatus(commTargetType,commTargetIdBuff[cycle]);
            commCycle = GetCommTargetCycle(commTargetType,commTargetIdBuff[cycle]);

#ifdef SYS_TYPE_WINDOWS

            LogPrintf(1U,"CommType=0x%x,id=%d,Status=%d,CommCycle=%d\n",commTargetType,commTargetIdBuff[cycle],commStatus,commCycle);

#elif defined SYS_TYPE_VXWORKS

            LogPrintf(1U,"0x%x,%d,%d,%d\n",commTargetType,commTargetIdBuff[cycle],commStatus,commCycle);

#else

#endif

#ifdef LOG_ANOTHER_METHOND

            ShortToChar(commTargetIdBuff[cycle],&pTmp[tmpIndex]); 
            tmpIndex = tmpIndex + 2u;

            pTmp[tmpIndex] = commStatus;
            tmpIndex = tmpIndex + 1u;

            ShortToChar(commCycle,&pTmp[tmpIndex]); 
            tmpIndex = tmpIndex + 2u;

#endif 

        }
    }  

#ifdef LOG_ANOTHER_METHOND

    *(GetgMaintainLen()) = tmpIndex;

#endif
}

/*************************************************
������:      LogPrintfAllCommTargetStatus
��������:    ��ӡ����ͨ�Ŷ���ͨ��״̬��Ϣ(���г�����)
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfAllCommTargetStatus(void)
{
    LogPrintf(1U,"CommStatus\n");

    /* ��ӡ����ͨ��״̬ */
    LogPrintfPOneCommTargetStatus(INNER_DEVTYPE_CI);

    /* ��ӡ����ZCͨ��״̬ */
    LogPrintfPOneCommTargetStatus(INNER_DEVTYPE_ZC);

    /* ��ӡNTPͨ��״̬ */
    LogPrintfPOneCommTargetStatus(INNER_DEVTYPE_NTP);
}

/*************************************************
������:      LogPrintfVersion
��������:    ��ӡ�汾(�����塢ͨ�Ű塢Ӧ��)��Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
void LogPrintfVersion(void)
{
    UINT8_S retValue = DEFAULT_ZERO;         /* ��������ֵ */
    UINT32_S  plugAppVer  = DEFAULT_ZERO;    /* �汾�� */
    UINT32_S  plugCommVer = DEFAULT_ZERO;    /* �汾�� */
    UINT8_S   *pTmp = NULL;
    UINT32_S  tmpIndex = DEFAULT_ZERO;

    LogPrintf(1U,"Version\n"); 

    LogPrintf(1U,"APP:V.0.0.7\n");

#ifdef SYS_TYPE_WINDOWS


#elif defined SYS_TYPE_VXWORKS

    LogPrintf(1U,"Platform:");
    /* 1ϵ��ȫ��ͨ�Ű� */
    retValue = AdptAppPlugSwVersionGet(ZC_DEVTYPE_MIC,1u,1u,&plugAppVer,&plugCommVer);

	LogPrintf(1U,"MIC:");
    ShowVersion(plugAppVer);

	LogPrintf(1U,"MIC:");
    ShowVersion(plugCommVer);

    /* 1ϵ�ǰ�ȫ��ͨ�Ű� */
    retValue = AdptAppPlugSwVersionGet(ZC_DEVTYPE_MIC,2u,1u,&plugAppVer,&plugCommVer);

	LogPrintf(1U,"MIC:");
    ShowVersion(plugAppVer);

	LogPrintf(1U,"MIC:");
    ShowVersion(plugCommVer);

    /* 1ϵ������ */
    retValue = AdptAppPlugSwVersionGet(ZC_DEVTYPE_SME,1u,1u,&plugAppVer,&plugCommVer);

	LogPrintf(1U,"SME_AB:");
    ShowVersion(plugAppVer);

	LogPrintf(1U,"SME_C:");
    ShowVersion(plugCommVer);

    /* 2ϵ��ȫ��ͨ�Ű� */
    retValue = AdptAppPlugSwVersionGet(ZC_DEVTYPE_MIC,1u,2u,&plugAppVer,&plugCommVer);

	LogPrintf(1U,"MIC:");
    ShowVersion(plugAppVer);

	LogPrintf(1U,"MIC:");
    ShowVersion(plugCommVer); 

    /* 2ϵ�ǰ�ȫ��ͨ�Ű� */
    retValue = AdptAppPlugSwVersionGet(ZC_DEVTYPE_MIC,2u,2u,&plugAppVer,&plugCommVer);

	LogPrintf(1U,"MIC:");
    ShowVersion(plugAppVer);

	LogPrintf(1U,"MIC:");
    ShowVersion(plugCommVer);

    /* 2ϵ������ */
    retValue = AdptAppPlugSwVersionGet(ZC_DEVTYPE_SME,1u,2u,&plugAppVer,&plugCommVer);

	LogPrintf(1U,"SME_AB:");
    ShowVersion(plugAppVer);

	LogPrintf(1U,"SME_C:");
    ShowVersion(plugCommVer);

    LogPrintf(1U,"\n");
#else

#endif

#ifdef LOG_ANOTHER_METHOND
    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    LogPrintf(1U,"V003");
    tmpIndex = tmpIndex + 4u;

    LongToChar(plugAppVer,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 4u;

    LongToChar(plugCommVer,&pTmp[tmpIndex]);
    tmpIndex = tmpIndex + 4u;

    *(GetgMaintainLen()) = tmpIndex;
#endif
    /* ���ݰ汾��*/
    LogPrintfDataVer();

}

/*************************************************
������:      ShowVersion
��������:    ת��4���İ汾��Ϣ
����:        const UINT32_S version���汾��
���:        ��
����ֵ:      ��
*************************************************/
static void ShowVersion(UINT32_S version)
{
    UINT8_S  verbuff[4] = {DEFAULT_ZERO};   /* �汾�� */

    MemorySet(verbuff,sizeof(verbuff),DEFAULT_ZERO,sizeof(verbuff));

    /* ������±����,����Ϊ�汾��ʶ���汾���͡������š��汾��� */
    LongToChar(version,verbuff);

    /* �жϲ���汾��� */
    if(0u != version)
    {
        if(0u != verbuff[2])
        {
            LogPrintf(1U,"%c.%c.%04d%c  ",verbuff[0],verbuff[1],verbuff[3],verbuff[2]);		
        }
        else
        {
            LogPrintf(1U,"%c.%c.%04d  ",verbuff[0],verbuff[1],verbuff[3]);
        }  
    }
    else
    {
        LogPrintf(1U,"%d.%d.%04d  ",0,0,0);
    }
}

/*************************************************
������:      LogPrintfDataVer
��������:    ���ݰ汾��Ϣ
����:        ��
���:        ��
����ֵ:      ��
*************************************************/
static void LogPrintfDataVer(void)
{
    UINT8_S  verbuff[SINGLE_VERSION_LEN_MAX] = {DEFAULT_ZERO};   /* �汾�� */
    UINT8_S  tmpRtn = RETURN_ERROR;
    UINT8_S  verbuff1[SINGLE_VERSION_LEN_MAX] = {DEFAULT_ZERO};   /* �汾�� */
    UINT8_S  tmpRtn1 = RETURN_ERROR;
    UINT8_S  verbuff2[SINGLE_VERSION_LEN_MAX] = {DEFAULT_ZERO};   /* �汾�� */
    UINT8_S  tmpRtn2 = RETURN_ERROR;
    UINT8_S   *pTmp = NULL;                 /* ��־������׵�ַ  */
    UINT32_S  tmpIndex = DEFAULT_ZERO;      /* ��־����Ŀǰ���±� */

    MemorySet(verbuff,(UINT32_S)(sizeof(verbuff)),DEFAULT_ZERO,(UINT32_S)(sizeof(verbuff)));
    MemorySet(verbuff1,(UINT32_S)(sizeof(verbuff1)),DEFAULT_ZERO,(UINT32_S)(sizeof(verbuff1)));
    MemorySet(verbuff2,(UINT32_S)(sizeof(verbuff2)),DEFAULT_ZERO,(UINT32_S)(sizeof(verbuff2)));
    /*
    GetSelfDataVersionData
    GetZcAtpDataVersionData 
    */
    tmpRtn = GetSelfDataVersionData(SINGLE_VERSION_LEN_MAX,verbuff);	
    tmpRtn1 = GetZcAtpDataVersionData(SINGLE_VERSION_LEN_MAX,verbuff1);

    LogPrintf(1U,"DataVer:%d.%d.%d.%d\n",verbuff[0],verbuff[1],verbuff[2],verbuff[3]);
    LogPrintf(1U,"%x.%x.%x.%x\n",verbuff1[0],verbuff1[1],verbuff1[2],verbuff1[3]);
    LogPrintf(1U,"%x.%x.%x.%x\n",verbuff2[0],verbuff2[1],verbuff2[2],verbuff2[3]);
#ifdef LOG_ANOTHER_METHOND
    pTmp = GetgMaintainDataArr();
    tmpIndex = *(GetgMaintainLen());

    MemoryCpy(&pTmp[tmpIndex],MAINTAIN_DATA_LEN_MAX,verbuff,(UINT32_S)(sizeof(verbuff)));
    tmpIndex = tmpIndex + (UINT32_S)(sizeof(verbuff));

    MemoryCpy(&pTmp[tmpIndex],MAINTAIN_DATA_LEN_MAX,verbuff1,(UINT32_S)(sizeof(verbuff1)));
    tmpIndex = tmpIndex + (UINT32_S)(sizeof(verbuff1));

    *(GetgMaintainLen()) = tmpIndex;

#endif 

}

