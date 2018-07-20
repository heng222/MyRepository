/********************************************************
* 
* �� �� ���� DmuCommDataHandle.c   
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03
* ���������� ������ѯ���� 
* ���ܿɷֽ����£� 
*          1����ѯָ�����з������һ��Seg��Ϣ�� 
*          2����ѯָ�����з������һ��SegID(����״̬��֪)�� 
*          3����ѯ����Seg�������(����״̬δ֪)�� 
*          4����ȡSEGID�����ļ�������ID	�� 
*          5����ѯ����Seg�������(����״̬��֪)�� 
*          6����ѯ����Seg�������(����״̬��֪)�� 
*          7����ѯ����Seg�������(����״̬δ֪)�� 
*          8����ѯ����Seg��ľ���(����Ϊ��ֵ�� 
*          9����ѯ����Seg��ľ��룻 
*          10������ͬһSEG���Ӧ����ĳ��ȣ� 
*          11�����µ����ʵʱ״̬�� 
*          12����ȡ����״̬�� 
*          13����ѯָ�����з������һ����(���ӵ���Ժ�ſ���ʹ��)�� 
*          14������������������ 
*          15�������߼���������� 
*          16�������������� 
*          17�������źŻ������ 
*          18�������·����� 
*          19�����������۷������ 
*          20����������������� 
*          21�����㱣����������� 
*          22�������¶ȱ������ 
*          23������ͣ����������� 
*          24���������ͣ����ť����� 
*          25�������˳�CBTC��������� 
*          26�������л���·�е������ 
*          27������ͨ����Ϣ����� 
*          28����ȡCOM��ѯ������ʼ��ʧ��ԭ�� 
*          29���������������жϵ�ǰ�ĵ���״̬�Ƿ�����������ι����ĵ���״̬�� 
*          30�������������ǲ�ѯ��ǰ�������ε����ڼ������Ρ����ڼ������η�Ϊ������ڼ������κ��յ����ڼ������Σ� 
*          31����ѯ��ǰ����ǰ����һ�����������һ�����λ�ã� 
*          32����ȡSEGID�����ļ�������ID�� 
*          33�����ݵ�ǰλ�ú�λ��,�õ���λ��.(��֪�����״̬)�� 
*          34����ȡ����ľ�������,����㵽�յ㷽�� 
*          35������SEG�Լ�SEG��ǰ���ͺ��Ƿ��е���,���е������ӵ���ǰ����󷽵�SEGID������,֮�䷵�ش�SEGID 
*          36����ѯ������֮����߼�����ID�Ͷ�Ӧ��SEG��Ϣ����(����״̬��֪)�� 
*          37����ѯ��SEG�󷽵��߼����Σ� 
*          38����ѯָ�����з������һ��SegID(����״̬��֪)�� 
*          39���˺����Ĺ����ǲ�ѯ��ǰGarde������Grade�� 
*          40������SEG��IDͬʱ�Դ�SEGΪ�������յ�,���Կ��ǵ���״̬,�ҵ����ڵ�Seg��ID�� 
* ��    ע�� �� 
*
********************************************************/ 

#include "DmuCommDataHandle.h"
#include "../../../Common/Convert.h"
#include "../../../Common/Copy.h"
#include "DmuCommDataTypeDefine.h"
#include "../Data/PointData.h"
#include "../Data/AxleSectionData.h"
#include "../Data/SwitchData.h"
#include "../Data/SignData.h"
#include "../Data/RouteData.h"
#include "../Data/ArData.h"
#include "../Data/StopPointData.h"
#include "../Data/ShieldDoorData.h"
#include "../Data/PlatFormData.h"
#include "../Data/ProtectZoneData.h"
#include "../Data/EmergStopButtonData.h"
#include "../../../Common/MemSet.h"
#include "DmuCommStructDefine.h"
#include "../Data/ExitCbtcSectionData.h"
#include "../Data/StopSectionData.h"
#include "../Data/LineSwitchInfoData.h"
#include "../Data/GradeData.h"


/**********************************ȫ�ֱ���START**********************************************/
static SwitchStatusInfoStruct SwitchStatusInfoStru[SNGZC_INCLUDE_SWITCH_NUM] = {{0u}};/*ʵ�ʵ���״̬*/
static UINT16_S SwitchNum = 0u;/*�������*/
static UINT32_S ComBnfInitErrReason = 0u;
/**********************************ȫ�ֱ���END************************************************/

/**********************************�ڲ�����START************************************************/    
static UINT8_S SearchPointTypeStatus(const UINT16_S tmnlJointMainSegId,const UINT16_S tmnlJointSideSegId,UINT16_S pointId,UINT16_S pointType);
static UINT8_S CheckPointFitAxleSgmt(UINT16_S axleSgmtID);
static UINT8_S CalcAxleSectionInfo(void);
static UINT8_S CalcLogicSgmtStru(void);
static void CalcSwitchAddStru(void);
static UINT8_S CalcSignInfoAddStru(void);
static void CalcRouteInfoAddStru(void);
static void CalcArInfoAddStru(void);
static void CalcPsdInfoAddStru(void);
static void CalcProtectSecInfoAddStru(void);
static void CalcEsbButtonInfoAddStru(void);
static void CalcExitCbtcInfoAddStru(void);
static void CalcStopSecInfoAddStru(void);
static UINT8_S CalcGradeInfoAddStru(void);
static UINT8_S CalcLineSwitchInfoAddStru(void);
static void GetPointOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startOffSet,UINT16_S* logicId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct relateLogicInfo[][2]);
static UINT8_S GetNextLogicId(UINT16_S logicId,UINT8_S dir,UINT16_S* nextLogicId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct relateLogicInfo[][2]);
static BnfSegStruct* GetNextSegInfo(UINT16_S segId,UINT8_S dir);
static UINT8_S GetNoDirSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId);
static UINT8_S GetSameSegBothDis(UINT32_S startLoc,UINT32_S endLoc,UINT8_S dir,UINT32_S* dis);
static UINT8_S GetNextPointId(UINT16_S curPointId,UINT8_S dir,UINT16_S* curpointType,UINT16_S* nextPointId);
static UINT16_S AccordSwitchAndPointTypeGetSegId(UINT16_S segId,UINT8_S pointType);
/**********************************�ڲ�����END************************************************/


/*
* ���������� ��ѯָ�����з������һ��Seg��Ϣ
* ����˵���� �������:Seg_ID  UINT16_S    ��ǰ��SegID
*                         Dir  UINT8_S     ���з���
* ����ֵ  �� NULL :ʧ�� !NULL���ɹ�
*/
static BnfSegStruct* GetNextSegInfo(UINT16_S segId,UINT8_S dir)
{
    BnfSegStruct* retVal = NULL;/*��������*/
    UINT8_S tmpRetVal = 0u;/*�ֲ���������ֵ*/
    UINT16_S nextSegId = 0u;/*��һ��SegID*/

    tmpRetVal = GetNextSegId(segId,dir,&nextSegId);
    
    if (1u == tmpRetVal)
    {
        retVal = GetIndexIdSegDataStru(nextSegId);
    }

    return retVal;
}

/*
* ���������� ��ѯָ�����з������һ��SegID(����״̬��֪)
* ����˵���� �������:Seg_ID  UINT16_S    ��ǰ��SegID
*                         Dir  UINT8_S     ���з���
*             �������:nextSegId  UINT16_S*   ��һ��SEGID
* ����ֵ  �� 0:ʧ��1���ɹ�
*/
UINT8_S GetNextSegId(UINT16_S segId,UINT8_S dir,UINT16_S* nextSegId)
{
    UINT8_S retVal = 0u;/*��������*/
    BnfSegStruct* segInfoStru = NULL;
    UINT8_S switchStatus = 0u;/*����״̬*/

    if(NULL != nextSegId)
    {
        *nextSegId = 0u;

        /*��ȡ��SEG��Ӧ��SEG��Ϣ*/
        segInfoStru = GetIndexIdSegDataStru(segId);
        /*��ȡ��ǰSEG��Ӧ�ĵ�ID*/
        
        if((segInfoStru != NULL)&&(dir == LINESEG_SAME_DIR))
        {
            switchStatus = SearchPointTypeStatus(segInfoStru->segTmnlJointMainSegId,segInfoStru->segTmnlJointSideSegId,segInfoStru->endPointId,segInfoStru->endPointType);

            if(SWITCH_STATUS_SAME == switchStatus)
            {
                *nextSegId = GetSegDataStrusegTmnlJointMainSegId(segId);
            }
            else if (SWITCH_STATUS_CONTRA == switchStatus)
            {
                *nextSegId = GetSegDataStrusegTmnlJointSideSegId(segId);
            }
            else
            {
                /*Do nothing currently !*/            
            }
        }
        else if((segInfoStru != NULL)&&(dir == LINESEG_CONVER_DIR))
        {
            switchStatus = SearchPointTypeStatus(segInfoStru->segStartJointMainSegId,segInfoStru->segStartJointSideSegId,segInfoStru->startPointId,segInfoStru->startPointType);

            if(SWITCH_STATUS_SAME == switchStatus)
            {
                *nextSegId = GetSegDataStrusegStartJointMainSegId(segId);
            }
            else if (SWITCH_STATUS_CONTRA == switchStatus)
            {
                *nextSegId = GetSegDataStrusegStartJointSideSegId(segId);
            }
            else
            {
                /*Do nothing currently !*/            
            }
        }
        else
        {
            /*Do nothing currently !*/
        }

        if(*nextSegId > 0u)
        {
            retVal = 1u;
        }

    
    }

    return retVal;
}

/*
* ���������� ��ѯ����Seg�������(����״̬δ֪)
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      segEndID        UINT16_S    �յ�SegID
*                      dir            UINT8_S     ���з���
*             �������:pSegId        UINT16_S*    SEGID����
*                      segIdNum        UINT8_S*      SEGID����    
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    

UINT8_S GetDirNoSwitchStutasSegArray(UINT16_S startSegId,UINT16_S endSegId,UINT8_S dir,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S segIdBuff[])
{
    UINT8_S chReturnValue = 0u;/*��������ֵ*/
    UINT16_S stackSegId[STACK_PUSH_SEG_MAX_NUM] = {0u};    /*����ջ�����ڼ�¼����������δ֪��������SegID*/
    StackPushSegInfoStruct tmpSegInfoStru[STACK_PUSH_SEG_MAX_NUM] ={{{NULL}}};/*��Ų��ҵ���SEGID*/
    UINT16_S stackSegIdTop = 0u;          /*����ջ��ջ��ָ��*/
    UINT16_S k = 0u;                        /*ѭ���ñ���*/
    BnfSegStruct* pCursegStru = NULL;
    BnfSegStruct* tempSegStru = NULL;
    UINT16_S lineSegNum = 0u;
    UINT8_S includeSegIdNum = 0u;
    UINT8_S isErrorFlag = 1u;

    if (((dir != LINESEG_SAME_DIR)&&(dir != LINESEG_CONVER_DIR)) || (segIdBuff == NULL) || (NULL == segIdNum))
    {
        isErrorFlag = 0u;
    }
    else
    {
        /*��ѯ�õ���ǰSEG�Ķ�Ӧ�����Ϣ*/
        pCursegStru = GetIndexIdSegDataStru(startSegId);
        tempSegStru = GetSegDataInfo(&lineSegNum);
        if ((NULL == pCursegStru)||(NULL == tempSegStru))
        {
            isErrorFlag = 0u;
        }
        /*���ջ*/
        stackSegIdTop = 0u;

    }
    
    if (0u == isErrorFlag)
    {
        lineSegNum = 0u;
    }
    else
    {
        if(1u == includePoint)
        {
            /*��ӵ�ǰ��ʼseg*/
            segIdBuff[includeSegIdNum] = startSegId;
            includeSegIdNum=includeSegIdNum+1;
        }

        if (startSegId == endSegId)
        {
            chReturnValue = 1u; 
        }
    }
    
    if ((1u == isErrorFlag)&&(dir == LINESEG_SAME_DIR)&&(0u == chReturnValue))
    {
        /*�������*/
        for (k=0u;(k<lineSegNum)&&(NULL != pCursegStru);k++)
        {
            /*�˴�ѭ������Ϊ�˱���Seg������Ϊ��ѭ����������ѭ���������ܳ���lineSegNum*/
            if ((pCursegStru->segTmnlJointMainSegId == UINT16_NULL)||(BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG == includeSegIdNum))
            {
                /*Seg�յ�����·�յ�,�����Ѿ���ѯ����վID,����ջ��������Ϊ��һ��Seg*/
                if (stackSegIdTop == 0u)
                {
                    /*���ջ�ѿգ�˵���Ѿ�ȫ��������ϣ����ز���ǰ��*/
                    chReturnValue = 0u;
                    break;
                }
                else
                {
                    /*ջ�ǿգ���ջ*/
                    stackSegIdTop--;
                    MemorySet(segIdBuff,sizeof(UINT16_S)*BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG,0u,sizeof(UINT16_S)*BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG);
                    includeSegIdNum = tmpSegInfoStru[stackSegIdTop].includeSegIdNum;

                    MemoryCpy(segIdBuff,sizeof(UINT16_S)*includeSegIdNum,tmpSegInfoStru[stackSegIdTop].SegIdBuff,sizeof(UINT16_S)*includeSegIdNum);
                    pCursegStru = GetIndexIdSegDataStru(stackSegId[stackSegIdTop]);
                }

            }
            else if(pCursegStru->endPointType == POINTTYPE_AXLE)
            {
                /*Seg�յ��Ǽ���㣬����������Seg��Ϊ��һ��Seg*/
                pCursegStru = GetIndexIdSegDataStru(pCursegStru->segTmnlJointMainSegId);
            }
            else if (pCursegStru->endPointType == POINTTYPE_SWITCH)
            {
                /*�жϵ�ǰseg�Ƿ�Ϊ����Ļ��Seg*/
                if(pCursegStru->segTmnlJointSideSegId == UINT16_NULL)
                {
                    /*��ǰSeg�ǻ��Seg����������SegΪ��һ��Seg*/
                    pCursegStru = GetIndexIdSegDataStru(pCursegStru->segTmnlJointMainSegId);
                }
                else
                {
                    if (stackSegIdTop == STACK_PUSH_SEG_MAX_NUM)
                    {
                        /*���ջ��������Ӧ������*/
                        chReturnValue = 0u;
                        break;
                    }
                    else
                    {
                        /*����ID��ջ*/
                        stackSegId[stackSegIdTop] = pCursegStru->segTmnlJointSideSegId;
                        MemoryCpy(tmpSegInfoStru[stackSegIdTop].SegIdBuff,sizeof(UINT16_S)*includeSegIdNum,segIdBuff,sizeof(UINT16_S)*includeSegIdNum);
                        tmpSegInfoStru[stackSegIdTop].includeSegIdNum = includeSegIdNum;
                        stackSegIdTop++;
                        /*���Ѿ����ҵ���SEGIDд���SEGID*/
                    }

                    /*����Ϊ��һSeg*/
                    pCursegStru = GetIndexIdSegDataStru(pCursegStru->segTmnlJointMainSegId);
                }
            }
            else
            {
                /*Seg�˵����Ͳ��Ϸ�*/
                chReturnValue=0u;
                break;
            }

            /* ���Ҵ�SEG�Ƿ�Ϊ�յ�SEG,���ǣ�����ҳɹ�*/

            if (pCursegStru != NULL)
            {
                if (pCursegStru->segId == endSegId)
                {
                    if(1u == includePoint)
                    {
                        /*��ӵ�ǰ��ʼseg*/
                        segIdBuff[includeSegIdNum] = endSegId;
                        includeSegIdNum=includeSegIdNum+1;
                    }

                    chReturnValue = 1u;
                    break;
                }
                else
                {
                    segIdBuff[includeSegIdNum] = pCursegStru->segId;
                    includeSegIdNum=includeSegIdNum+1;
                }
            }
        }
    }
    else if ((1u == isErrorFlag)&&(dir == LINESEG_CONVER_DIR)&&(0u == chReturnValue))
    {
        /*ConverDir���ҵ�ǰSeg*/
        for (k=0;(k<lineSegNum)&&(NULL != pCursegStru);k++)
        {
            /*�˴�ѭ������Ϊ�˱���Seg������Ϊ��ѭ����������ѭ���������ܳ���lineSegNum*/
            /*ͨ����ǰSeg��ȡ��һ��Seg��������һ��Seg���Ͳ�ͬ���в�ͬ�Ĵ���*/
            if ((pCursegStru->segStartJointMainSegId==UINT16_NULL)||(BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG == includeSegIdNum))
            {
                /*Seg�յ�����·�յ�,�����Ѿ���ѯ����վID,����ջ��������Ϊ��һ��Seg*/
                if (stackSegIdTop==0u)
                {
                    /*���ջ�ѿգ�˵���Ѿ�ȫ��������ϣ����ز���ǰ��*/
                    chReturnValue = 0u;
                    break;
                }
                else
                {
                    /*ջ�ǿգ���ջ*/
                    stackSegIdTop--;
                    MemorySet(segIdBuff,sizeof(UINT16_S)*BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG,0u,sizeof(UINT16_S)*BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG);
                    includeSegIdNum = tmpSegInfoStru[stackSegIdTop].includeSegIdNum;

                    MemoryCpy(segIdBuff,sizeof(UINT16_S)*includeSegIdNum,tmpSegInfoStru[stackSegIdTop].SegIdBuff,sizeof(UINT16_S)*includeSegIdNum);
                    pCursegStru = GetIndexIdSegDataStru(stackSegId[stackSegIdTop]);
                }

            }
            else if(pCursegStru->startPointType==POINTTYPE_AXLE)
            {
                /*Seg����Ǽ���㣬����������Seg��Ϊ��һ��Seg*/
                pCursegStru = GetIndexIdSegDataStru(pCursegStru->segStartJointMainSegId);
            }
            else if(pCursegStru->startPointType==POINTTYPE_SWITCH)
            {
                /*����㣬���������*/
                /*�жϵ�ǰseg�Ƿ�Ϊ����Ļ��Seg*/
                if(pCursegStru->segStartJointSideSegId==UINT16_NULL)
                {
                    /*�ǻ��Seg����������SegΪ��һ��Seg*/
                    pCursegStru = GetIndexIdSegDataStru(pCursegStru->segStartJointMainSegId);
                }
                else
                {
                    if (stackSegIdTop==STACK_PUSH_SEG_MAX_NUM)
                    {
                        /*���ջ��������Ӧ������*/
                        chReturnValue = 0u;
                        break;
                    }
                    else
                    {
                        /*����ID��ջ*/
                        stackSegId[stackSegIdTop]=pCursegStru->segStartJointSideSegId;
                        MemoryCpy(tmpSegInfoStru[stackSegIdTop].SegIdBuff,sizeof(UINT16_S)*includeSegIdNum,segIdBuff,sizeof(UINT16_S)*includeSegIdNum);

                        tmpSegInfoStru[stackSegIdTop].includeSegIdNum = includeSegIdNum;
                        stackSegIdTop++;
                    }
                    /*����Ϊ��һSeg,������ջ*/
                    pCursegStru = GetIndexIdSegDataStru(pCursegStru->segStartJointMainSegId);
                }

            }
            else
            {
                /*Seg�˵����Ͳ��Ϸ�*/
                chReturnValue=0u;
                break;
            }
            if (pCursegStru != NULL)
            {
                /* ���Ҵ�SEG�Ƿ�Ϊ�յ�SEG,���ǣ�����ҳɹ�*/
                if (pCursegStru->segId == endSegId)
                {
                    if(1u == includePoint)
                    {
                        /*��ӵ�ǰ��ʼseg*/
                        segIdBuff[includeSegIdNum] = endSegId;
                        includeSegIdNum=includeSegIdNum+1;
                    }
                    chReturnValue = 1u;
                    break;
                }
                else
                {
                    segIdBuff[includeSegIdNum] = pCursegStru->segId;
                    includeSegIdNum =includeSegIdNum+1;
                }
            }
        }
    }
    else
    {
        /*Do nothing currently !*/
    }

    if(1 == isErrorFlag)
    {
        if (1u == chReturnValue)
        {
            *segIdNum = includeSegIdNum;
        }
        else
        {
            *segIdNum = 0u;
        }
    }


    return chReturnValue;
}

/*��ѯ�˵�ID�����ͻ�ȡ�˵��״̬*/
static UINT8_S SearchPointTypeStatus(const UINT16_S tmnlJointMainSegId,const UINT16_S tmnlJointSideSegId,UINT16_S pointId,UINT16_S pointType)
{
    UINT8_S switchStatus = 0u;/*����״̬*/

    if (pointType == POINTTYPE_SWITCH)
    {
        if ((tmnlJointMainSegId != UINT16_NULL)&&(tmnlJointSideSegId != UINT16_NULL))
        {
            switchStatus = GetSwitchStatus(pointId);
        }
        else if (tmnlJointMainSegId != UINT16_NULL)
        {
            switchStatus = SWITCH_STATUS_SAME;
        }
        else if (tmnlJointSideSegId != UINT16_NULL)
        {
            switchStatus = SWITCH_STATUS_CONTRA;
        }
        else
        {
            /*Do nothing currently !*/
        }
    }
    else
    {
        switchStatus = SWITCH_STATUS_SAME;
    }

    return switchStatus;
}

/*
* ���������� ��ѯ����Seg�������(����״̬��֪)
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      segEndID        UINT16_S    �յ�SegID
*                      includePoint  UINT8_S      1�����˵�  0�������˵�
*             �������:pSegId        UINT8_S*    SEGID����
*                      segIdNum        UINT8_S*      SEGID����    
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    

static UINT8_S GetNoDirSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    /*�������*/
    retVal = GetDirSegArray(segStartID,segEndID,LINESEG_SAME_DIR,includePoint,segIdNum,pSegId);

    if (0u == retVal)
    {
        /*�������*/
        retVal = GetDirSegArray(segStartID,segEndID,LINESEG_CONVER_DIR,includePoint,segIdNum,pSegId);
    }

    return retVal;
}

/*
* ���������� ��ѯ����Seg�������(����״̬��֪)
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      segEndID        UINT16_S    �յ�SegID
*                      dir            UINT8_S     ���з���
*                      includePoint     UINT8_S     1�����˵�  0�������˵�
*             �������:pSegId        UINT16_S*    SEGID����
*                      segIdNum        UINT8_S*      SEGID����    
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    

UINT8_S GetDirSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S dir,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S nextSegId = 0u;/*��ȡ��һ��SegID*/
    UINT16_S tmpSegId = 0u;
    UINT8_S index = 0u;/*�����±�ƫ��*/

    if((NULL != pSegId) && (NULL != segIdNum))
    {

        if(1u == includePoint)
        {
            /*��ӵ�ǰ��ʼseg*/
            pSegId[index] = segStartID;
            index=index+1;
        }
        
        if (segStartID == segEndID)
        {
            retVal = 1u;
        }
        else
        {
            tmpSegId = segStartID;
            for(;index < BOTHSEG_INCLUDE_MAX_SEG;)
            {
                retVal = GetNextSegId(tmpSegId,dir,&nextSegId);
        
                if (0u == retVal)
                {
                    break;
                }
        
                if (nextSegId == segEndID)
                {
                    if(1u == includePoint)
                    {
                        pSegId[index] = nextSegId;
                        index=index+1;
                    }
                    retVal = 1u;
                    break;
                }
        
                pSegId[index] = nextSegId;
                index = index+1;
                tmpSegId = nextSegId;
            }
        }
        
        if (1u == retVal)
        {
            *segIdNum = index;
        }
        else
        {
            *segIdNum = 0u;
        }

    }

    return retVal;
}

/*
* ���������� ��ѯ����Seg�������(����״̬δ֪)
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      segEndID        UINT16_S    �յ�SegID
*             �������:pSegId        UINT8_S*    SEGID����
*                      segIdNum        UINT8_S*      SEGID����    
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    

UINT8_S GetNoDirNoSwitchStutasSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    /*�������*/
    retVal = GetDirNoSwitchStutasSegArray(segStartID,segEndID,LINESEG_SAME_DIR,includePoint,segIdNum,pSegId);

    if (0u == retVal)
    {
        /*�������*/
        retVal = GetDirNoSwitchStutasSegArray(segStartID,segEndID,LINESEG_CONVER_DIR,includePoint,segIdNum,pSegId);
    }

    return retVal;
}

/*
* ���������� ��ѯ����Seg��ľ���(����Ϊ��ֵ)
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      startOffSet    UINT32_S      ���ƫ����
*                      segEndID        UINT16_S    �յ�SegID
*                      endOffSet        UINT32_S      �յ�ƫ����
*                      dir            UINT8_S     ���з���
*             �������:destDistance  UINT32_S*   Ŀ�����(����Ϊ��ֵ)  
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    
UINT8_S GetDirBothSegPointDisPlus(UINT16_S segStartID,UINT32_S startOffSet,UINT16_S segEndID,UINT32_S endOffSet,UINT8_S dir,UINT32_S* destDistance)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT8_S i = 0u;/*ѭ��ʹ��*/
    UINT32_S startDis=0u;/*��㷶Χ�ڵĳ���*/
    UINT32_S endDis=0u;/*�յ㷶Χ�ڵĳ���*/
    INT32_S bothDis = 0u;/*����ľ���*/
    UINT8_S segIdNum=0u;/*seg�ĸ���*/
    UINT32_S totalSegLength=0u;/*ȫ��SEG�ĳ���֮��*/
    UINT16_S segIdBuff[BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG]={0};/*seg��ID����*/

    if(NULL != destDistance)
    {
        *destDistance = 0u;

        /*�ӿڲ�������*/
        if(((dir == LINESEG_SAME_DIR)||(dir == LINESEG_CONVER_DIR))&&(segStartID > 0u)&&(segEndID > 0u)
            &&(GetSegDataStrulength(segStartID) >= startOffSet)&&(GetSegDataStrulength(segEndID) >= endOffSet))
        {
            if (segStartID == segEndID)
            {
                if (LINESEG_SAME_DIR == dir)
                {
                    bothDis = endOffSet - startOffSet;
                }
                else
                {
                    bothDis = startOffSet - endOffSet;
                }

                retVal = 1u;
            }
            else
            {
                /*������㷶Χ�ڵĳ���*/
                if(LINESEG_SAME_DIR==dir)
                {
                    startDis=GetSegDataStrulength(segStartID)-startOffSet;
                    retVal = GetDirNoSwitchStutasSegArray(segStartID, segEndID, dir,0, &segIdNum, segIdBuff);
                    if(1u == retVal)
                    {
                        /*����ѯ��SEGID�������*/
                        if(0!=segIdNum)
                        {
                            for(i=0u;i<segIdNum;i++)
                            {
                                totalSegLength+=GetSegDataStrulength(segIdBuff[i]);
                            }
                        }
                        else
                        {
                            totalSegLength=0u;
                        }
                        endDis = endOffSet;
                        bothDis = startDis+totalSegLength+endDis;
                    }
                }
                else
                {
                    startDis=startOffSet;
                    /*��ѯ�����㵥λ�ڵ�SEGID,����ѯʧ��,��Ŀ�������Ϊ��Чֵ�����ɹ�������ѯ����SEGID�������*/
                    retVal = GetDirNoSwitchStutasSegArray(segStartID, segEndID, dir,0, &segIdNum, segIdBuff);
                    if(1u == retVal)
                    {
                        /*����ѯ��SEGID�������*/
                        if(0!=segIdNum)
                        {
                            for(i=0u;i<segIdNum;i++)
                            {
                                totalSegLength+=GetSegDataStrulength(segIdBuff[i]);
                            }
                        }
                        else
                        {
                            totalSegLength=0u;
                        }
                        endDis=GetSegDataStrulength(segEndID)-endOffSet;
                        /*�����յ�����ĳ���*/
                        bothDis=startDis+totalSegLength+endDis;
                    }
                }
            }
        }

        if (retVal == 1u)
        {
            if (bothDis >= 0)
            {
                *destDistance = bothDis;
            }
            else
            {
                retVal = 0u;
            }
        }


    
    }

    return retVal;
}

/*
* ���������� ��ѯ����Seg��ľ���
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      startOffSet    UINT32_S      ���ƫ����
*                      segEndID        UINT16_S    �յ�SegID
*                      endOffSet        UINT32_S      �յ�ƫ����
*             �������:destDistance  UINT32_S*   Ŀ�����  
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    
UINT8_S GetNoDirBothSegPointDis(UINT16_S segStartID,UINT32_S startOffSet,UINT16_S segEndID,UINT32_S endOffSet,UINT32_S* destDistance)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    retVal = GetDirBothSegPointDisPlus(segStartID,startOffSet,segEndID,endOffSet,LINESEG_SAME_DIR,destDistance);
    if (0u == retVal)
    {
        retVal = GetDirBothSegPointDisPlus(segStartID,startOffSet,segEndID,endOffSet,LINESEG_CONVER_DIR,destDistance);
    }

    return retVal;
}

/*
* ���������� ����ͬһSEG���Ӧ����ĳ���
* ����˵���� �������:startLoc    UINT16_S    ��ʼSegID
*                      endLoc    UINT32_S      ���ƫ����
*                      dir        UINT8_S     ���з���
*             �������:dis        UINT32_S*   Ŀ�����  
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    
static UINT8_S GetSameSegBothDis(UINT32_S startLoc,UINT32_S endLoc,UINT8_S dir,UINT32_S* dis)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

	if(NULL != dis)
    {
        if (startLoc == endLoc)
        {
            retVal = 1u;
        }
        else
        {
            if(LINESEG_SAME_DIR == dir)
            {
                if (startLoc < endLoc)
                {
                    *dis = endLoc - startLoc;
                    retVal = 1u;
                }
                else
                {
                    *dis = 0u;
                    retVal = 0u;
                }
            }
            else 
            {
                if (startLoc > endLoc)
                {
                    *dis = (UINT32_S)(startLoc - endLoc);
                    retVal = 1u;
                }
                else
                {
                    *dis = 0u;
                    retVal = 0u;
                }
            }
        }
    
    }

    

    return retVal;
}

/*
* ���������� ���µ����ʵʱ״̬
* ����˵���� �������:switchStatusBuff    UINT8_S[]     ����״̬��Ϣ
*                      buffLength        UINT16_S      ���鳤��
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    
UINT8_S UpdateSwitchStatus(const UINT8_S switchStatusBuff[],UINT16_S buffLength)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    if ((switchStatusBuff != NULL)&&(buffLength > 0u)&&(buffLength % SWITCHSTATUS_INFO_SIZE == 0u))
    {
        SwitchNum = buffLength / SWITCHSTATUS_INFO_SIZE;

        if (SwitchNum <= SNGZC_INCLUDE_SWITCH_NUM)
        {
            for (i = 0u;(i < SwitchNum); i++)
            {
                /*����ID*/
                SwitchStatusInfoStru[i].switchId = ShortFromChar(switchStatusBuff);
                switchStatusBuff += 2;

                /*����״̬*/
                SwitchStatusInfoStru[i].switchStatus = *switchStatusBuff;
                switchStatusBuff += 1;
            }

            retVal = 1u;
        }
        else
        {
            SwitchNum = 0u;
        }
    }

    return retVal;
}

/*
* ���������� ��ȡ����״̬
* ����˵���� const UINT16_S switchId ����ID
* ����ֵ  �� >=0  ����״̬   0   ʧ��
*/    
UINT8_S GetSwitchStatus(const UINT16_S switchId)
{
    UINT8_S retVal = SWITCH_STATUS_LOSE;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/

    for (i = 0u; i < SwitchNum; i++)
    {
        if (switchId == SwitchStatusInfoStru[i].switchId)
        {
            retVal = SwitchStatusInfoStru[i].switchStatus;
            break;
        }
    }

    return retVal;
}

/*
* ���������� ��ѯָ�����з������һ����(���ӵ���Ժ�ſ���ʹ��)
* ����˵���� �������:curPointId   UINT16_S    ��ǰ�ĵ�ID
*                         Dir       UINT8_S     ���з���(�������)
*             �������:nextPointId  UINT16_S*   ��һ����ID
*                      curpointType UINT16_S*     ��ǰ������
* ����ֵ  �� 0:ʧ��1���ɹ�
*/
static UINT8_S GetNextPointId(UINT16_S curPointId,UINT8_S dir,UINT16_S* curpointType,UINT16_S* nextPointId)
{
    UINT8_S retVal = 0u;/*��������*/
    UINT8_S errorFlag = 1u;/*�����ʶ  1 ������ȷ  0 �������*/
    UINT8_S switchStatus = 0u;/*����״̬*/
    UINT16_S pointType = 0u;/*������*/
    BnfPointStruct* pointInfoStru = NULL;

	if((NULL != curpointType) && (NULL != nextPointId))
    {
        *nextPointId = 0u;

        /*��ȡ��POINT��Ӧ��POINT��Ϣ*/
        pointInfoStru = GetIndexIdPointDataStru(curPointId);

        if (pointInfoStru != NULL)
        {
            pointType = pointInfoStru->pointType;
        }
        
        if((0u != pointType)&&(LINESEG_SAME_DIR == dir))
        {
            *nextPointId = GetPointDataStrutmnlJointMainLkId(curPointId);
            if (POINTTYPE_SWITCH == pointType)
            {
                switchStatus = GetSwitchStatus(curPointId);

                if(SWITCH_STATUS_SAME == switchStatus)
                {
                    /*Do nothing currently !*/
                }
                else if (SWITCH_STATUS_CONTRA == switchStatus)
                {
                    *nextPointId = GetPointDataStrutmnlJointSideLkId(curPointId);
                }
                else
                {
                    errorFlag = 0u;
                }
            }
        }
        else if((0u != pointType)&&(LINESEG_CONVER_DIR == dir))
        {
            *nextPointId = GetPointDataStrustartJointMainLkId(curPointId);
            if (POINTTYPE_SWITCH == pointType)
            {
                switchStatus = GetSwitchStatus(curPointId);

                if(SWITCH_STATUS_SAME == switchStatus)
                {
                    /*Do nothing currently !*/
                }
                else if (SWITCH_STATUS_CONTRA == switchStatus)
                {
                    *nextPointId = GetPointDataStrustartJointSideLkId(curPointId);
                }
                else
                {
                    errorFlag = 0u;
                }
            }
        }
        else
        {
            errorFlag = 0u;
        }

        if(1u == errorFlag)
        {
            *curpointType = pointType;
            retVal = 1u;
        }
    
    }


    return retVal;
}

/*
*�������ܣ������������������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
*    UINT8_S includeLogicAxleSecNum;                                        �������߼����θ���
    UINT16_S logicSecId[AXLESECTION_BELONG_LOGICSEC_MAX_NUM];                �������߼�����ID
    UINT16_S orgnSegId;                                                    �������seg���
    UINT16_S tmnlSegId;                                                    �յ�����seg���
    UINT32_S orgnSegOfst;                                                    �������segƫ����
    UINT32_S tmnlSegOfst;                                                    �յ�����segƫ����
    UINT16_S  orgnAxleId;                                                    �����������
    UINT16_S  tmnlAxleId;                                                    �յ���������
    UINT16_S  orgnAxleSgmtId[3];                                            ��������������Ӽ������α��
    UINT16_S  tmnlAxleSgmtId[3];                                            ���������յ����Ӽ������α��
    UINT16_S  relatPointNum;                                                ����������Ŀ
    UINT16_S  relatPointId[4];                                            ����������
    UINT16_S  relatPointStatus[4];                                         ��������״̬
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static UINT8_S CalcAxleSectionInfo(void)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    
    UINT16_S lgcSctLineNum = 0u;/*��̬���ٱ�����*/
    BnfLogicSectionStruct* pTempLgcSctStru = NULL;/*�߼����νṹ��ָ��*/
    
    UINT16_S axleSecNum = 0u;/*�������α������*/
    BnfAxleSectionStruct* pTempAxleSecStru = NULL;/*�������νṹ��ָ��*/
    
    BnfAxleSectionStruct*   pAxleSecStruOrgn[3] = {NULL,NULL,NULL};       /*����������θ���ʱ�õ�*/
    BnfAxleSectionStruct*   pAxleSecStruTmnl[3] = {NULL,NULL,NULL};       /*����������θ���ʱ�õ�*/
    UINT8_S AxleSgmtCountOrgn = 0u;
    UINT8_S AxleSgmtCountTmnl = 0u;



    BnfSegStruct* pTempSeg1Stru = NULL;/*SEG�ṹ��ָ��*/
    BnfSegStruct* pTempSeg2Stru = NULL;/*SEG�ṹ��ָ��*/

    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/
    UINT16_S jj = 0u;/*ѭ��ʹ��*/

    UINT8_S isFindStartPoint = 0u;/*1 �ҵ� 0 δ�ҵ�*/
    UINT8_S isFindEndPoint = 0u;/*1 �ҵ� 0 δ�ҵ�*/
    UINT8_S errorFlag = 1u;/*�����ʶ 1 �ɹ� 0 ����*/
    UINT8_S findStartPointNum = 0u;/*�ҵ����Ĵ���*/
    UINT8_S findEndPointNum = 0u;/*�ҵ��յ�Ĵ���*/
    

    UINT16_S index = 0u;/*�����±�*/


    /*��ȡ�߼����εĸ���*/
    pTempLgcSctStru = GetLogicSectionDataInfo(&lgcSctLineNum);
    pTempAxleSecStru = GetAxleSectionDataInfo(&axleSecNum);

    if ((NULL == pTempLgcSctStru)||(NULL == pTempAxleSecStru))
    {
        errorFlag = 0u;
    }
    /*����������ε����SEG���յ�SEG������������ţ��յ���������*/
    for (i = 0;(errorFlag == 1u)&&(i < axleSecNum); i++)
    {
        if (1u == pTempAxleSecStru[i].includeSegNum)
        {
            pTempSeg1Stru = GetIndexIdSegDataStru(pTempAxleSecStru[i].segIdBuff[0]);
            pTempAxleSecStru[i].orgnSegId = pTempAxleSecStru[i].segIdBuff[0];
            pTempAxleSecStru[i].tmnlSegId = pTempAxleSecStru[i].segIdBuff[0];
            pTempAxleSecStru[i].orgnAxleId = pTempSeg1Stru->startPointId;
            pTempAxleSecStru[i].tmnlAxleId = pTempSeg1Stru->endPointId;
        }
        else
        {
            findEndPointNum = 0u;
            findStartPointNum = 0u;
            for (j = 0u;j < pTempAxleSecStru[i].includeSegNum; j++)
            {
                isFindStartPoint = 0u;
                isFindEndPoint = 0u;
                pTempSeg1Stru = GetIndexIdSegDataStru(pTempAxleSecStru[i].segIdBuff[j]);
                for (jj = 0u;(pTempSeg1Stru != NULL)&&(jj < pTempAxleSecStru[i].includeSegNum); jj++)
                {
                    if ((pTempSeg1Stru->segStartJointMainSegId == pTempAxleSecStru[i].segIdBuff[jj])||
                        (pTempSeg1Stru->segStartJointSideSegId == pTempAxleSecStru[i].segIdBuff[jj]))
                    {
                        isFindStartPoint = 1u;
                    }

                    if ((pTempSeg1Stru->segTmnlJointMainSegId == pTempAxleSecStru[i].segIdBuff[jj])||
                        (pTempSeg1Stru->segTmnlJointSideSegId == pTempAxleSecStru[i].segIdBuff[jj]))
                    {
                        isFindEndPoint = 1u;
                    }
                }


                if (1u == isFindStartPoint)
                {
                    if(0u == isFindEndPoint)
                    {
                        pTempAxleSecStru[i].tmnlSegId = pTempAxleSecStru[i].segIdBuff[j];
                        pTempAxleSecStru[i].tmnlAxleId = GetSegDataStruendPointId(pTempAxleSecStru[i].tmnlSegId);
                        findEndPointNum++;
                    }
                }
                else
                {
                   if(1u == isFindEndPoint)
                   {
                        pTempAxleSecStru[i].orgnSegId = pTempAxleSecStru[i].segIdBuff[j];
                        pTempAxleSecStru[i].orgnAxleId = GetSegDataStrustartPointId(pTempAxleSecStru[i].orgnSegId);
                        findStartPointNum++;
                
                   }
                
                }           
            }
            
            if ((findEndPointNum != 1u)||(findStartPointNum != 1u))
            {
                pTempAxleSecStru[i].orgnSegId = 0u;
                pTempAxleSecStru[i].tmnlSegId = 0u;
                pTempAxleSecStru[i].orgnAxleId = 0u;
                pTempAxleSecStru[i].tmnlAxleId = 0u;
            }

        }
    }

    /*����dwOrgnSegOfst,dwTmnlSegOfst*/
    for(i=0;(errorFlag == 1u)&&(i<axleSecNum);i++)
    {
        /*ͨ�������ҵ�seg��Ϣ(ȡ�յ�SEG)*/
        pTempSeg2Stru = GetIndexIdSegDataStru(pTempAxleSecStru[i].tmnlSegId);
        if (pTempSeg2Stru != NULL)
        {
            pTempAxleSecStru[i].orgnSegOfst = 0u;
            pTempAxleSecStru[i].tmnlSegOfst = pTempSeg2Stru->length;
        }

    }

    /*����orgnRelatPointId*/
    for(i=0;(errorFlag == 1u)&&(i<axleSecNum);i++)
    {    
        /*������������Ϊ0*/
        AxleSgmtCountOrgn = 0u;
        AxleSgmtCountTmnl = 0u;
        for(j=0u;j<axleSecNum;j++)
        {
            if(pTempAxleSecStru[i].orgnAxleId == pTempAxleSecStru[j].tmnlAxleId)
            {
                /*�����ָ�룬������*/                        
                pAxleSecStruOrgn[AxleSgmtCountOrgn] = &pTempAxleSecStru[j];
                AxleSgmtCountOrgn++;
            }

            if(pTempAxleSecStru[i].tmnlAxleId  == pTempAxleSecStru[j].orgnAxleId)
            {
                /*�����ָ�룬������*/                        
                pAxleSecStruTmnl[AxleSgmtCountTmnl] = &pTempAxleSecStru[j];
                AxleSgmtCountTmnl++;
            }

        }    
               
        /*һ����������ǰ��������������ϵļ������Σ�����*/
        if((AxleSgmtCountOrgn > 3u ) || (AxleSgmtCountTmnl > 3u))
        {
            retVal = 0u;
            errorFlag = 0u;
            break;
        }
                
        /*�����������������Ӽ������α��*/
        pTempAxleSecStru[i].orgnAxleSecNum = AxleSgmtCountOrgn;                      
        for(jj = 0u;jj < AxleSgmtCountOrgn;jj++)
        {
            pTempAxleSecStru[i].orgnAxleSgmtId[jj] = pAxleSecStruOrgn[jj]->indexId;
        }

        /*������������յ����Ӽ������α��*/
        pTempAxleSecStru[i].tmnlAxleSecNum = AxleSgmtCountTmnl;                                      
        for(jj = 0u;jj < AxleSgmtCountTmnl;jj++)
        {
            pTempAxleSecStru[i].tmnlAxleSgmtId[jj] = pAxleSecStruTmnl[jj]->indexId;
        }


    }

    /*����relatPointNum;      ����������Ŀ
          relatPointId[4];      ����������*/
    for (i = 0;(errorFlag == 1u)&&(i < axleSecNum); i++)
    {
        index = 0u;
        for (j = 0u;(j < (pTempAxleSecStru[i].includeSegNum))&&(pTempAxleSecStru[i].includeSegNum>1); j++)
        {
            pTempSeg1Stru = GetIndexIdSegDataStru(pTempAxleSecStru[i].segIdBuff[j]);
            for (jj = 0u;(pTempSeg1Stru != NULL)&&(jj < pTempAxleSecStru[i].includeSegNum); jj++)
            {
                if ((pTempAxleSecStru[i].segIdBuff[jj] == pTempSeg1Stru->segTmnlJointMainSegId)&&(pTempSeg1Stru->segTmnlJointSideSegId != UINT16_NULL))
                {
                    pTempAxleSecStru[i].relatPointId[index] = pTempSeg1Stru->endPointId;
                    pTempAxleSecStru[i].relatPointStatus[index] = SWITCH_STATUS_SAME;
                    index ++;
                    break;
                }
                else if((pTempAxleSecStru[i].segIdBuff[jj] == pTempSeg1Stru->segTmnlJointSideSegId)&&(pTempSeg1Stru->segTmnlJointMainSegId != UINT16_NULL))
                {
                    pTempAxleSecStru[i].relatPointId[index] = pTempSeg1Stru->endPointId;
                    pTempAxleSecStru[i].relatPointStatus[index] = SWITCH_STATUS_CONTRA;
                    index ++;
                    break;
                }
                else if ((pTempAxleSecStru[i].segIdBuff[jj] == pTempSeg1Stru->segStartJointMainSegId)&&(pTempSeg1Stru->segStartJointSideSegId != UINT16_NULL))
                {
                    pTempAxleSecStru[i].relatPointId[index] = pTempSeg1Stru->startPointId;
                    pTempAxleSecStru[i].relatPointStatus[index] = SWITCH_STATUS_SAME;
                    index ++;
                    break;
                }
                else if((pTempAxleSecStru[i].segIdBuff[jj] == pTempSeg1Stru->segStartJointSideSegId)&&(pTempSeg1Stru->segStartJointMainSegId != UINT16_NULL))
                {
                    pTempAxleSecStru[i].relatPointId[index] = pTempSeg1Stru->startPointId;
                    pTempAxleSecStru[i].relatPointStatus[index] = SWITCH_STATUS_CONTRA;
                    index ++;
                    break;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
        }
        pTempAxleSecStru[i].relatPointNum = index;
    }

    /*����    UINT16_S  manageZCId;                                        ����ZC����ID
            UINT16_S  manageCIId;                                        ����CI����ID */
    for (i = 0;(errorFlag == 1u)&&(i < axleSecNum); i++)
    {
         pTempAxleSecStru[i].manageCIId = GetSegDataStrusegManageCIId(pTempAxleSecStru[i].tmnlSegId);
         pTempAxleSecStru[i].manageZCId = GetSegDataStrusegManageZCId(pTempAxleSecStru[i].tmnlSegId);
    }

    if (1u == errorFlag)
    {
        retVal = 1u;
    }

    return retVal;
}


/*
*�������ܣ������߼�����������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
*    UINT16_S belongAxleSecId;                        ������������ID
    UINT16_S  mainOrgnLogicSgmtId;                ��������������ǰ���߼����εı��
    UINT16_S  mainTmnlLogicSgmtId;                �������������ں����߼����εı��
*/
static UINT8_S CalcLogicSgmtStru(void)
{
    UINT16_S i = 0u,j =0u,jj = 0u;/*ѭ������*/
    UINT16_S indexI = 0u;/*ѭ��ʹ��*/
    UINT16_S k,LgcSgmtIdIndex = 0xFFFFu;              /*ѭ�����������±�����*/
    UINT8_S indexSwNum = 0u;/*д����ʱʹ��*/
    BnfLogicSectionStruct  * pTempLgcSecStru = NULL;     /*��ʱ����*/
    BnfAxleSectionStruct  *pTempAxleSecStru = NULL;        /*��ʱ����*/
    BnfAxleSectionStruct* pTempAxleSgmtStru = NULL;/*��ʱ����*/
    UINT8_S retVal = 1u;
    UINT16_S lgcSecLineNum = 0u;
    UINT16_S axleSecNum = 0u;
    UINT16_S segId = 0u;
    UINT8_S segIdNum = 0u;
    UINT16_S segIdBuff[BOTHSEG_INCLUDE_MAX_SEG+2] = {0};
    UINT16_S tmpSegIdBuff[BOTHSEG_INCLUDE_MAX_SEG+2] = {0};
    UINT8_S isFindNum = 0u;/*�Ƿ���ҵ��ĸ���*/
    BnfSegStruct* tmpCurSegStru = 0;/*��ǰSEGiD�ṹ����Ϣ*/
    BnfSegStruct* tmpStartSegStru = 0;/*��ǰSEGiD�ṹ����Ϣ*/
    BnfSegStruct* tmpendSegStru = 0;/*��ǰSEGiD�ṹ����Ϣ*/

    pTempLgcSecStru = GetLogicSectionDataInfo(&lgcSecLineNum);
    pTempAxleSecStru = GetAxleSectionDataInfo(&axleSecNum);

    if ((pTempLgcSecStru == NULL)||(pTempAxleSecStru == NULL))
    {
        lgcSecLineNum =0u;
        axleSecNum = 0u;
    }
       
    /*�����߼����������ļ�������*/
    for (i = 0u; i < lgcSecLineNum; i++)
    {
        MemorySet(tmpSegIdBuff,sizeof(tmpSegIdBuff),0u,sizeof(tmpSegIdBuff));
        if ((pTempLgcSecStru[i].startSegId == pTempLgcSecStru[i].endSegId))    
        {
            tmpSegIdBuff[0] = pTempLgcSecStru[i].startSegId;
            segIdNum = 1u;
        }
        else
        {
            /*��ȡ�߼����ΰ�����SEGID*/
            tmpSegIdBuff[0] = pTempLgcSecStru[i].startSegId;
            tmpSegIdBuff[1] = pTempLgcSecStru[i].endSegId;
            segIdNum = 0u;
            retVal = GetNoDirNoSwitchStutasSegArray(pTempLgcSecStru[i].startSegId,pTempLgcSecStru[i].endSegId,0,&segIdNum,&tmpSegIdBuff[2]);
            if (1u == retVal)
            {
                segIdNum +=2u;
            }
            else
            {
                
                lgcSecLineNum = 0u;
                axleSecNum = 0u;
                break;
            }
        }
        for (j = 0u; j < axleSecNum; j++)
        {
            isFindNum = 0u;

            for (indexI = 0u; indexI < segIdNum; indexI++)
            {
                for (jj = 0u;jj < pTempAxleSecStru[j].includeSegNum; jj++)
                {
                    if (tmpSegIdBuff[indexI] == pTempAxleSecStru[j].segIdBuff[jj])
                    {
                        isFindNum += 1u;
                        break;
                    }
                }
            }

            if (isFindNum == segIdNum)
            {
                pTempLgcSecStru[i].belongAxleSecId = pTempAxleSecStru[j].indexId;
                break;
            }
        }
    }

    /*����������ΰ������߼�����*/
    for (i = 0u; i < axleSecNum; i++)
    {
        pTempAxleSecStru[i].includeLogicAxleSecNum = 0u;
        for (j = 0u; j < lgcSecLineNum; j++)
        {
            if (pTempAxleSecStru[i].indexId == pTempLgcSecStru[j].belongAxleSecId)
            {
                pTempAxleSecStru[i].logicSecId[pTempAxleSecStru[i].includeLogicAxleSecNum]= pTempLgcSecStru[j].indexId;
                pTempAxleSecStru[i].includeLogicAxleSecNum++;
            }
        }
    }

    for(i=0u;i< lgcSecLineNum;i++)
    {
        pTempLgcSecStru[i].includeSegIdNum = 0u;
        pTempAxleSgmtStru = GetIndexIdAxleSectionDataStru(pTempLgcSecStru[i].belongAxleSecId);

        /*����mainOrgnLogicSgmtId;                ��������������ǰ���߼����εı��
            minTmnlLogicSgmtId;                    �������������ں����߼����εı��*/
        /*����Ϊ��Ч*/
        LgcSgmtIdIndex = 0xFFFFu;
        for(k=0u;(pTempAxleSgmtStru != NULL)&&(k<pTempAxleSgmtStru->includeLogicAxleSecNum);k++)
        {                    
            if(pTempLgcSecStru[i].indexId == pTempAxleSgmtStru->logicSecId[k])
            {
                LgcSgmtIdIndex=k;
            }
        }
            
        /*�߼����α���ڼ���������û�ҵ������ݳ���*/
        if(LgcSgmtIdIndex == 0xFFFFu)
        {
            retVal = 0u;
            break;
        }
        /*����������ֻ��һ���߼�����ʱ��û��ǰ���߼����κͺ����߼�����*/
        else if((LgcSgmtIdIndex == 0u) && (LgcSgmtIdIndex == (pTempAxleSgmtStru->includeLogicAxleSecNum-1)))
        {
            pTempLgcSecStru[i].mainOrgnLogicSgmtId = 0xFFFFu;
            pTempLgcSecStru[i].mainTmnlLogicSgmtId = 0xFFFFu;
        }
        /*��ǰ�߼����δ��ڼ������εĵ�һ���߼�����ʱ��û��ǰ���߼�����*/
        else if (LgcSgmtIdIndex == 0u)
        {
            pTempLgcSecStru[i].mainOrgnLogicSgmtId = 0xFFFFu;
            pTempLgcSecStru[i].mainTmnlLogicSgmtId = pTempAxleSgmtStru->logicSecId[LgcSgmtIdIndex+1];
        }
        /*��ǰ�߼����δ��ڼ������ε����һ���߼�����ʱ��û�к����߼�����*/
        else if(LgcSgmtIdIndex ==(pTempAxleSgmtStru->includeLogicAxleSecNum-1))
        {
            pTempLgcSecStru[i].mainOrgnLogicSgmtId = pTempAxleSgmtStru->logicSecId[LgcSgmtIdIndex-1];
            pTempLgcSecStru[i].mainTmnlLogicSgmtId = 0xFFFFu;
        }
        /*��ǰ�߼����δ��ڼ������ε��м��߼�����ʱ��*/
        else
        {
            pTempLgcSecStru[i].mainOrgnLogicSgmtId = pTempAxleSgmtStru->logicSecId[LgcSgmtIdIndex-1];
            pTempLgcSecStru[i].mainTmnlLogicSgmtId = pTempAxleSgmtStru->logicSecId[LgcSgmtIdIndex+1];
        }

        /*��ȡ�߼����ζ�Ӧ��SEGID*/
        segId = GetLogicSectionDataStrustartSegId(pTempLgcSecStru[i].indexId);

        /*��ȡ��SEGID��Ӧ��ZCID*/
        pTempLgcSecStru[i].manageZCId = GetSegDataStrusegManageZCId(segId);

        /*��ȡ��SEGID��Ӧ��CIID*/
        pTempLgcSecStru[i].manageCIId = GetSegDataStrusegManageCIId(segId);
        
        /*��ȡ�߼����ΰ�����SEGID*/
        if (pTempLgcSecStru[i].startSegId == pTempLgcSecStru[i].endSegId)
        {
            pTempLgcSecStru[i].segIdBuff[pTempLgcSecStru[i].includeSegIdNum] = pTempLgcSecStru[i].endSegId;
            pTempLgcSecStru[i].includeSegIdNum++;
        }
        else
        {
            pTempLgcSecStru[i].segIdBuff[pTempLgcSecStru[i].includeSegIdNum] = pTempLgcSecStru[i].startSegId;
            pTempLgcSecStru[i].includeSegIdNum++;
            retVal = GetNoDirNoSwitchStutasSegArray(pTempLgcSecStru[i].startSegId,pTempLgcSecStru[i].endSegId,0,&segIdNum,segIdBuff);
            if (1u == retVal)
            {
                if (segIdNum > 0u)
                {
                    MemoryCpy(&pTempLgcSecStru[i].segIdBuff[pTempLgcSecStru[i].includeSegIdNum],sizeof(UINT16_S)*segIdNum,segIdBuff,sizeof(UINT16_S)*segIdNum);
                    pTempLgcSecStru[i].includeSegIdNum += segIdNum;
                }
                pTempLgcSecStru[i].segIdBuff[pTempLgcSecStru[i].includeSegIdNum] = pTempLgcSecStru[i].endSegId;
                pTempLgcSecStru[i].includeSegIdNum++;
            }
            else
            {
                break;
            }
            
        }

        if (pTempLgcSecStru[i].includeSegIdNum > LOGICSECTION_OF_SWITCH_MAX_NUM+1)
        {
            retVal = 0u;
            break;
        }

        indexSwNum = 0u;
        if (pTempLgcSecStru[i].includeSegIdNum > 1u)
        {
            for (k = 0u;k < pTempLgcSecStru[i].includeSegIdNum;k++)
            {
                tmpCurSegStru = GetIndexIdSegDataStru(pTempLgcSecStru[i].segIdBuff[k]);
                if(NULL != tmpCurSegStru)
                {                
                    if ((tmpCurSegStru->segTmnlJointMainSegId != UINT16_NULL)&&(tmpCurSegStru->segTmnlJointSideSegId != UINT16_NULL)&&(pTempLgcSecStru[i].endSegId != pTempLgcSecStru[i].segIdBuff[k]))
                    {
                        if (indexSwNum == LOGICSECTION_OF_SWITCH_MAX_NUM)
                        {
                            retVal = 0u;
                            break;
                        }

                        pTempLgcSecStru[i].switchIdStru[indexSwNum].switchId = tmpCurSegStru->endPointId;
                        for (j = 0u; j < pTempLgcSecStru[i].includeSegIdNum; j++)
                        {
                            if (pTempLgcSecStru[i].segIdBuff[j] == tmpCurSegStru->segTmnlJointMainSegId)
                            {
                                pTempLgcSecStru[i].switchIdStru[indexSwNum].switchStatus = SWITCH_STATUS_SAME;
                                indexSwNum++;
                                break;
                            }
                            else if (pTempLgcSecStru[i].segIdBuff[j] == tmpCurSegStru->segTmnlJointSideSegId)
                            {
                                pTempLgcSecStru[i].switchIdStru[indexSwNum].switchStatus = SWITCH_STATUS_CONTRA;
                                indexSwNum++;
                                break;
                            }
                            else
                            {
                                /*Do nothing currently !*/
                            }
                        }
                    }
                    else if ((tmpCurSegStru->segStartJointMainSegId != UINT16_NULL)&&(tmpCurSegStru->segStartJointSideSegId != UINT16_NULL)&&(pTempLgcSecStru[i].startSegId != pTempLgcSecStru[i].segIdBuff[k]))
                    {
                        if (indexSwNum == LOGICSECTION_OF_SWITCH_MAX_NUM)
                        {
                            retVal = 0u;
                            break;
                        }
                        pTempLgcSecStru[i].switchIdStru[indexSwNum].switchId = tmpCurSegStru->startPointId;
                        for (j = 0u; j < pTempLgcSecStru[i].includeSegIdNum; j++)
                        {
                            if (pTempLgcSecStru[i].segIdBuff[j] == tmpCurSegStru->segStartJointMainSegId)
                            {
                                pTempLgcSecStru[i].switchIdStru[indexSwNum].switchStatus = SWITCH_STATUS_SAME;
                                indexSwNum++;
                                break;
                            }
                            else if (pTempLgcSecStru[i].segIdBuff[j] == tmpCurSegStru->segStartJointSideSegId)
                            {
                                pTempLgcSecStru[i].switchIdStru[indexSwNum].switchStatus = SWITCH_STATUS_CONTRA;
                                indexSwNum++;
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
                        /*Do nothing currently !*/
                    }
                }
            }
        }

        pTempLgcSecStru[i].switchIdNum = indexSwNum;
    }

    /*��ѯ���߼����ε���������߼�����ID���������߼�����ID���յ������߼�����ID���յ�����߼�����ID*/
    for(i=0u;(i< lgcSecLineNum)&&(1u == retVal);i++)
    {
        pTempLgcSecStru[i].startJointMainLogicId = UINT16_NULL;
        pTempLgcSecStru[i].startJointSideLogicId = UINT16_NULL;        
        pTempLgcSecStru[i].tmnlJointMainLogicId = UINT16_NULL;
        pTempLgcSecStru[i].tmnlJointSideLogicId = UINT16_NULL;
        pTempLgcSecStru[i].relateLogicNum = 0u;
        MemorySet(pTempLgcSecStru[i].relateLogicInfo,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM,UINT8_NULL,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM);

        if (pTempLgcSecStru[i].includeSegIdNum == 1u)
        {
            tmpCurSegStru = GetIndexIdSegDataStru(pTempLgcSecStru[i].startSegId);
            if (tmpCurSegStru != NULL)
            {
                if (pTempLgcSecStru[i].startSegOffset == 0u)
                {
                    if ((tmpCurSegStru ->segStartJointMainSegId != UINT16_NULL)&&(tmpCurSegStru->segStartJointSideSegId == UINT16_NULL))
                    {
                        /*��ѯ��SEG����һ���߼�����ֱ�ӷ��أ����ж���������߼�����ƫ�������ġ�����SEG�����������߼������У��������������߼�����ID*/
                        GetSegFontSecOfLogSecInfo(tmpCurSegStru->segStartJointMainSegId,GetSegDataStrulength(tmpCurSegStru->segStartJointMainSegId),&pTempLgcSecStru[i].startJointMainLogicId,&pTempLgcSecStru[i].startJointSideLogicId);
                    }
                }

                if ((pTempLgcSecStru[i].startSegOffset != 0u)&&(pTempLgcSecStru[i].endSegOffset == tmpCurSegStru->length))
                {
                    pTempLgcSecStru[i].startJointMainLogicId = pTempLgcSecStru[i].mainOrgnLogicSgmtId;
                }

                if (pTempLgcSecStru[i].endSegOffset == tmpCurSegStru->length)
                {
                    if ((tmpCurSegStru ->segTmnlJointMainSegId != UINT16_NULL)&&(tmpCurSegStru->segTmnlJointSideSegId == UINT16_NULL))
                    {
                        /*��ѯ��SEG����һ���߼�����ֱ�ӷ��أ����ж���������߼�����ƫ������С�ġ�����SEG�����������߼������У��������������߼�����ID*/
                        GetSegRearSecOfLogSecInfo(tmpCurSegStru ->segTmnlJointMainSegId,GetSegDataStrulength(tmpCurSegStru ->segTmnlJointMainSegId),&pTempLgcSecStru[i].tmnlJointMainLogicId,&pTempLgcSecStru[i].tmnlJointSideLogicId);
                    }
                }

                if ((pTempLgcSecStru[i].startSegOffset == 0u)&&(pTempLgcSecStru[i].endSegOffset != tmpCurSegStru->length))
                {
                    pTempLgcSecStru[i].tmnlJointMainLogicId = pTempLgcSecStru[i].mainTmnlLogicSgmtId;
                }

                if ((pTempLgcSecStru[i].startSegOffset > 0u)&&(pTempLgcSecStru[i].endSegOffset < tmpCurSegStru->length))
                {
                    /*��ȡ���ڵ��߼�����*/
                    pTempLgcSecStru[i].startJointMainLogicId = pTempLgcSecStru[i].mainOrgnLogicSgmtId;
                    pTempLgcSecStru[i].tmnlJointMainLogicId = pTempLgcSecStru[i].mainTmnlLogicSgmtId;
                }
            }
            else
            {
                retVal = 0u;
                break;
            }
        }
        else
        {
            tmpStartSegStru = GetIndexIdSegDataStru(pTempLgcSecStru[i].startSegId);
            tmpendSegStru = GetIndexIdSegDataStru(pTempLgcSecStru[i].endSegId);
            if ((NULL != tmpStartSegStru)&&(tmpendSegStru != NULL))
            {
                if ((tmpStartSegStru ->segStartJointMainSegId != UINT16_NULL)&&(tmpStartSegStru->segStartJointSideSegId == UINT16_NULL))
                {
                    /*��ѯ��SEG����һ���߼�����ֱ�ӷ��أ����ж���������߼�����ƫ�������ġ�����SEG�����������߼������У��������������߼�����ID*/
                    GetSegFontSecOfLogSecInfo(tmpStartSegStru->segStartJointMainSegId,GetSegDataStrulength(tmpStartSegStru->segStartJointMainSegId),&pTempLgcSecStru[i].startJointMainLogicId,&pTempLgcSecStru[i].startJointSideLogicId);
                }

                if ((tmpendSegStru ->segTmnlJointMainSegId != UINT16_NULL)&&(tmpendSegStru->segTmnlJointSideSegId == UINT16_NULL))
                {
                    /*��ѯ��SEG����һ���߼�����ֱ�ӷ��أ����ж���������߼�����ƫ������С�ġ�����SEG�����������߼������У��������������߼�����ID*/
                    GetSegRearSecOfLogSecInfo(tmpendSegStru ->segTmnlJointMainSegId,GetSegDataStrulength(tmpendSegStru ->segTmnlJointMainSegId),&pTempLgcSecStru[i].tmnlJointMainLogicId,&pTempLgcSecStru[i].tmnlJointSideLogicId);
                }
            }
            else
            {
                retVal = 0u;
                break;
            }

            retVal = GetLineLogicSectionBelongRelareLc(pTempLgcSecStru[i].indexId,&pTempLgcSecStru[i].relateLogicNum,pTempLgcSecStru[i].relateLogicInfo);
            if (0u == retVal)
            {
                break;
            }
        }
    }


    if ((0u == axleSecNum)||(0u == lgcSecLineNum))
    {
        retVal = 0u;
    }

    return retVal;
}


/*
*�������ܣ��������������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static void CalcSwitchAddStru(void)
{
    UINT16_S i = 0u;
    BnfSwitchStruct* switchStru = NULL;
    BnfSegStruct* tmpLocSegStru = NULL;/*SEG��Ϣ�ṹ��*/
    BnfSegStruct* tmpAntiSegStru = NULL;/*SEG��Ϣ�ṹ��*/
    BnfSegStruct* tmpJoinSegStru = NULL;/*SEG��Ϣ�ṹ��*/
    UINT16_S lineNum = 0u;
    UINT16_S locSegId = 0u;
    UINT16_S antiSegId = 0u;
    UINT16_S joinSegId = 0u;
    UINT8_S retVal = 0u;/*��������ֵ*/

    switchStru = GetSwitchDataInfo(&lineNum);
    if (switchStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        /*��ȡ�˵����Ӧ�Ļ��SEGID*/
        retVal = GetSwitchDataStruSegIdInfo(switchStru[i].switchId,&locSegId,&antiSegId,&joinSegId);

        if (1u == retVal)
        {
            tmpLocSegStru = GetIndexIdSegDataStru(locSegId);
            tmpAntiSegStru = GetIndexIdSegDataStru(antiSegId);
            tmpJoinSegStru = GetIndexIdSegDataStru(joinSegId);
        
            if ((tmpJoinSegStru != NULL)&&(NULL != tmpLocSegStru)&&(NULL != tmpAntiSegStru))
            {
                /*��ȡ��SEGID��Ӧ��ZCID*/
                switchStru[i].manageZCId = tmpJoinSegStru->segManageZCId;

                /*��ȡ��SEGID��Ӧ��CIID*/
                switchStru[i].manageCIId = tmpJoinSegStru->segManageCIId;

                if ((switchStru[i].switchId == tmpLocSegStru->endPointId)&&(POINTTYPE_SWITCH == tmpLocSegStru->endPointType))
                {
                    switchStru[i].joinSegOffset = tmpLocSegStru->length;
                }
                else if((switchStru[i].switchId == tmpLocSegStru->startPointId)&&(POINTTYPE_SWITCH == tmpLocSegStru->startPointType))
                {
                    switchStru[i].joinSegOffset = 0u;
                }
                else
                {
                    switchStru[i].joinSegOffset = UINT32_NULL;
                }

                if ((switchStru[i].switchId == tmpAntiSegStru->endPointId)&&(POINTTYPE_SWITCH == tmpAntiSegStru->endPointType))
                {
                    switchStru[i].joinSegOffset = tmpAntiSegStru->length;
                }
                else if((switchStru[i].switchId == tmpAntiSegStru->startPointId)&&(POINTTYPE_SWITCH == tmpAntiSegStru->startPointType))
                {
                    switchStru[i].joinSegOffset = 0u;
                }
                else
                {
                    switchStru[i].joinSegOffset = UINT32_NULL;
                }

                if ((switchStru[i].switchId == tmpJoinSegStru->endPointId)&&(POINTTYPE_SWITCH == tmpJoinSegStru->endPointType))
                {
                    switchStru[i].joinSegOffset = tmpJoinSegStru->length;
                }
                else if((switchStru[i].switchId == tmpJoinSegStru->startPointId)&&(POINTTYPE_SWITCH == tmpJoinSegStru->startPointType))
                {
                    switchStru[i].joinSegOffset = 0u;
                }
                else
                {
                    switchStru[i].joinSegOffset = UINT32_NULL;
                }
            }
        }
    }

}

/*
*�������ܣ������źŻ�������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
    UINT8_S   signSegId                                                         �źŻ�����SegId
    UINT8_S   signSegOffset                                                     �źŻ�����SegOffset
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static UINT8_S CalcSignInfoAddStru(void)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S segId = 0u;/*SEGID*/
    UINT16_S i = 0u;
    BnfSignStruct* signStru = NULL;
    BnfSegStruct* tmpSegStru = NULL;
    UINT16_S lineNum = 0u;

    signStru = GetSignDataInfo(&lineNum);
    if (signStru == NULL)
    {
        lineNum =0u;
    }
    for ( i = 0u; i < lineNum; i++)
    {
        /*��ȡ�źŻ�ID��Ӧ��SEGID*/
        segId = GetSignDataStrusignProSegId(signStru[i].signId);

        
        tmpSegStru = GetIndexIdSegDataStru(segId);
        if (tmpSegStru != NULL)
        {
            if (signStru[i].protectiveDir == SIGNPRO_DIR_CONTRA)
            {
                signStru[i].signSegId = tmpSegStru->segTmnlJointMainSegId;
                signStru[i].signSegOffset = 0u;
            }
            else if (signStru[i].protectiveDir == SIGNPRO_DIR_SAME)
            {
                signStru[i].signSegId = tmpSegStru->segStartJointMainSegId;
                signStru[i].signSegOffset = GetSegDataStrulength(tmpSegStru->segStartJointMainSegId);
            }
            else
            {
                break;
            }

            /*��ȡ��SEGID��Ӧ��ZCID*/
            signStru[i].manageZCId = tmpSegStru->segManageZCId;

            /*��ȡ��SEGID��Ӧ��ZCID*/
            signStru[i].manageCIId = tmpSegStru->segManageCIId;
        }
        else
        {
            break;
        }
    }

    if (lineNum == i)
    {
        retVal = 1u;
    }

    return retVal;
}

/*
*�������ܣ������·������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static void CalcRouteInfoAddStru(void)
{
    UINT16_S ciId = 0u;/*CIID*/
    UINT16_S i = 0u;
    BnfRouteStruct* routeStru = NULL;
    UINT16_S lineNum = 0u;

    routeStru = GetRouteDataInfo(&lineNum);
    if (routeStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        /*��ȡ��·����ʼ���źŻ�ID*/
        ciId = GetRouteDataStrumanageCI(routeStru[i].routeId);

        /*��ȡ��SEGID��Ӧ��ZCID*/
        routeStru[i].manageZCId = ArrordCiIdGetZcId(ciId);
    }
}

/*
*�������ܣ����������۷�������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static void CalcArInfoAddStru(void)
{
    UINT16_S segId = 0u;/*SEGID*/
    UINT16_S i = 0u;
    BnfArStruct* arStru = NULL;
    UINT16_S lineNum = 0u;
    UINT16_S stopPointid = 0u;/*ͣ����ID*/

    arStru = GetArDataInfo(&lineNum);
    if (arStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        /*��ȡ�����۷���ť��Ӧ��ͣ������*/
        stopPointid = GetArDataStruarInStopPointId(arStru[i].arId);

        /*��ȡͣ����ID��Ӧ��SEGID*/
        segId = GetStopPointDataStrusegId(stopPointid);

        /*��ȡ��SEGID��Ӧ��ZCID*/
        arStru[i].manageZCId = GetSegDataStrusegManageZCId(segId);

        /*��ȡ��SEGID��Ӧ��ZCID*/
        arStru[i].manageCIId = GetSegDataStrusegManageCIId(segId);
    }
}

/*
*�������ܣ�����������������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static void CalcPsdInfoAddStru(void)
{
    UINT16_S segId = 0u;/*SEGID*/
    UINT16_S i = 0u;
    BnfShieldDoorStruct* psdStru = NULL;
    UINT16_S lineNum = 0u;
    UINT16_S stationId = 0u;/*����վ̨ID*/

    psdStru = GetShieldDoorDataInfo(&lineNum);
    if (psdStru == NULL)
    {
        lineNum =0u;
    }
    for ( i = 0u; i < lineNum; i++)
    {
        /*��ȡ��·�������������ļ�������*/
        stationId = GetShieldDoorDataStrustationId(psdStru[i].shieldDoorId);

        /*��ȡվ̨��Ŷ�Ӧ��SEGID*/
        segId = GetPlatFormDataStrusegId(stationId);

        /*��ȡ��SEGID��Ӧ��ZCID*/
        psdStru[i].manageZCId = GetSegDataStrusegManageZCId(segId);

        /*��ȡ��SEGID��Ӧ��ZCID*/
        psdStru[i].manageCIId = GetSegDataStrusegManageCIId(segId);

        /*����PSD���ڵ�SEGID*/
        psdStru[i].segId = segId;

        psdStru[i].dir = GetPlatFormDataStrudir(stationId);
    }
}

/*
*�������ܣ����㱣������������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static void CalcProtectSecInfoAddStru(void)
{
    UINT16_S* axleSecId = NULL;/*��������*/
    UINT16_S* segIdBuff = NULL;/*SEGID*/
    UINT16_S i = 0u;
    BnfProtectZoneStruct* pProtectSecStru = NULL;
    UINT16_S lineNum = 0u;

    pProtectSecStru = GetProtectZoneDataInfo(&lineNum);
    if (pProtectSecStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        /*��ȡ��·�������������ļ�������*/
        axleSecId = GetProtZoDataInAxleSgmtId(pProtectSecStru[i].protectZoneId);

        /*��ȡ�������α�Ŷ�Ӧ��SEGID*/
        segIdBuff = GetAxleSectionDataStrusegIdBuff(axleSecId[0]);

        if (segIdBuff != NULL)
        {
            /*��ȡ��SEGID��Ӧ��ZCID*/
            pProtectSecStru[i].manageZCId = GetSegDataStrusegManageZCId(segIdBuff[0]);

            /*��ȡ��SEGID��Ӧ��CIID*/
            pProtectSecStru[i].manageCIId = GetSegDataStrusegManageCIId(segIdBuff[0]);
        }

    }
}


/*
*�������ܣ������¶ȱ�������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
*/
static UINT8_S CalcGradeInfoAddStru(void)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/
    BnfGradeStruct* pGradeStru = NULL;
    UINT32_S length = 0u;
    UINT16_S lineNum = 0u;

    pGradeStru = GetGradeDataInfo(&lineNum);
    if (pGradeStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        MemorySet(pGradeStru[i].segIdBuff,sizeof(UINT16_S)*GRADE_INCLUDE_LINK_NUM,UINT8_NULL,sizeof(UINT16_S)*GRADE_INCLUDE_LINK_NUM);
        pGradeStru[i].includeSegNum = 0u;
        length = GetSegDataStrulength(pGradeStru[i].orgnSegId);
        pGradeStru[i].orgnSegIdLength = length;
        if (pGradeStru[i].orgnSegId == pGradeStru[i].tmnlSegId)
        {
            
            pGradeStru[i].gradeLength += (pGradeStru[i].tmnlSegOfst - pGradeStru[i].orgnSegOfst);
            
            pGradeStru[i].tmnlSegIdLength = length;
            retVal = 1u;
        }
        else
        {
            retVal = GetNoDirNoSwitchStutasSegArray(pGradeStru[i].orgnSegId,pGradeStru[i].tmnlSegId,0,&pGradeStru[i].includeSegNum,pGradeStru[i].segIdBuff);
            if (0u == retVal)
            {
                break;
            }
            else
            {
                pGradeStru[i].gradeLength = length - pGradeStru[i].orgnSegOfst;
                for(j=0u;j<pGradeStru[i].includeSegNum;j++)
                { 
                    length = GetSegDataStrulength(pGradeStru[i].segIdBuff[j]);
                    pGradeStru[i].gradeLength += length;
                    pGradeStru[i].segIdLength[j] = length;
                }

                pGradeStru[i].gradeLength += pGradeStru[i].tmnlSegOfst;
                pGradeStru[i].tmnlSegIdLength = GetSegDataStrulength(pGradeStru[i].tmnlSegId);
            }
        }
    }

    return retVal;
}

/*
*�������ܣ�����ͣ������������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static void CalcStopSecInfoAddStru(void)
{
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S index = 0u;/*�����±�*/
    BnfStopSectionStruct* stopSectionStru = NULL;/*ͣ��������Ϣ�ṹ��ָ��*/
    UINT16_S lineNum = 0u;
    BnfShieldDoorStruct* psdStru = NULL;/*��������Ϣ�ṹ��ָ��*/
    UINT16_S psdLineNum = 0u;/*�����ű���������*/

    stopSectionStru = GetStopSectionDataInfo(&lineNum);
    psdStru = GetShieldDoorDataInfo(&psdLineNum);
    if ((stopSectionStru == NULL)||(NULL == psdLineNum))
    {
        lineNum =0u;
        psdLineNum = 0u;
    }


    for ( i = 0u; i < lineNum; i++)
    {
        /*��ȡ��SEG����Ӧ��PSDID*/
        index = 0u;
        for ( j = 0u;( j < psdLineNum)&&(index < 2); j++)
        {
            if (stopSectionStru[i].segId == psdStru[j].segId)
            {
                stopSectionStru[i].psdId[index] = psdStru[j].shieldDoorId;
                index=index+1;
            }
        }
        stopSectionStru[i].psdNum = index;

        /*��ȡ��SEGID��Ӧ��ZCID*/
        stopSectionStru[i].manageZCId = GetSegDataStrusegManageZCId(stopSectionStru[i].segId);

        /*��ȡ��SEGID��Ӧ��CIID*/
        stopSectionStru[i].manageCIId = GetSegDataStrusegManageCIId(stopSectionStru[i].segId);
    }
}

/*
*�������ܣ��������ͣ����ť������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
    UINT16_S  manageZCId;                                                    ����ZC����ID
    UINT16_S  manageCIId;                                                    ����CI����ID
*/
static void CalcEsbButtonInfoAddStru(void)
{
    UINT16_S segId = 0u;/*SEGID*/
    UINT16_S i = 0u;
    BnfEmergStopButtonStruct* esbStru = NULL;
    UINT16_S lineNum = 0u;
    UINT16_S stationId = 0u;/*����վ̨ID*/

    esbStru = GetEmergStopButtonDataInfo(&lineNum);
    if (esbStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        /*��ȡ����ͣ����ť����վ̨���*/
        stationId = GetLineEsbBelongStationId(esbStru[i].emergStopButtonId);

        /*��ȡվ̨��Ŷ�Ӧ��SEGID*/
        segId = GetPlatFormDataStrusegId(stationId);

        /*��ȡ��SEGID��Ӧ��ZCID*/
        esbStru[i].manageZCId = GetSegDataStrusegManageZCId(segId);

        /*��ȡ��SEGID��Ӧ��ZCID*/
        esbStru[i].manageCIId = GetSegDataStrusegManageCIId(segId);

        esbStru[i].segId = segId;
    }
}

/*
*�������ܣ������˳�CBTC����������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
*/
static void CalcExitCbtcInfoAddStru(void)
{
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT16_S j = 0u;/*ѭ��ʹ��*/
    UINT16_S k = 0u;/*ѭ��ʹ��*/
    BnfExitCbtcSectionStruct* exitCbtcStru = NULL;/*�˳�CBTC���Խṹ��ָ��*/
    BnfSegStruct* tmpSegStru = NULL;/*SEG��Ϣ�ṹ��ָ��*/
    UINT16_S lineNum = 0u;/*����*/
    UINT8_S isFindStartPoint = 0u;/*1 �ҵ� 0 δ�ҵ�*/
    UINT8_S isFindEndPoint = 0u;/*1 �ҵ� 0 δ�ҵ�*/
    UINT8_S findStartPointNum = 0u;/*�ҵ����Ĵ���*/
    UINT8_S findEndPointNum = 0u;/*�ҵ��յ�Ĵ���*/

    exitCbtcStru = GetExitCbtcSectionDataInfo(&lineNum);
    if (exitCbtcStru == NULL)
    {
        lineNum =0u;
    }

    for (i = 0u;(i < lineNum); i++)
    {
        if (1u == exitCbtcStru[i].segNum)
        {
            exitCbtcStru[i].startSegId = exitCbtcStru[i].segInfoBuff[0];
            exitCbtcStru[i].endSegId = exitCbtcStru[i].segInfoBuff[0];
        }
        else
        {
            findEndPointNum = 0u;
            findStartPointNum = 0u;
            for (j = 0u;j < exitCbtcStru[i].segNum; j++)
            {
                isFindStartPoint = 0u;
                isFindEndPoint = 0u;
                tmpSegStru = GetIndexIdSegDataStru(exitCbtcStru[i].segInfoBuff[j]);
                for (k = 0u;(tmpSegStru != NULL)&&(k < exitCbtcStru[i].segNum); k++)
                {
                    if ((tmpSegStru->segStartJointMainSegId == exitCbtcStru[i].segInfoBuff[k])||
                        (tmpSegStru->segStartJointSideSegId == exitCbtcStru[i].segInfoBuff[k]))
                    {
                        isFindStartPoint = 1u;
                    }

                    if ((tmpSegStru->segTmnlJointMainSegId == exitCbtcStru[i].segInfoBuff[k])||
                        (tmpSegStru->segTmnlJointSideSegId == exitCbtcStru[i].segInfoBuff[k]))
                    {
                        isFindEndPoint = 1u;
                    }
                }

            	if(1u == isFindStartPoint)
                {
                	if(0u == isFindEndPoint)
                    {
                        /*��Seg���ε�������������ڴ�CBTC�˳������յ��������β��ڴ�CBTC�˳�������˵����SegΪ�յ�Seg*/
                    	if (exitCbtcStru[i].dir == LINESEG_SAME_DIR)
                        {
                        	exitCbtcStru[i].endSegId = exitCbtcStru[i].segInfoBuff[j];
                        }
                    	else
                        {
                        	exitCbtcStru[i].startSegId = exitCbtcStru[i].segInfoBuff[j];
                        }
                        findEndPointNum++;                    
                    }
                }
            	else
                {
                	if(1u == isFindEndPoint)
                    {
                        /*��Seg���ε�����������β��ڴ�CBTC�˳������յ����������ڴ�CBTC�˳�������˵����SegΪ���Seg*/
                    	if (exitCbtcStru[i].dir == LINESEG_SAME_DIR)
                        {
                        	exitCbtcStru[i].startSegId = exitCbtcStru[i].segInfoBuff[j];
                        }
                    	else
                        {
                        	exitCbtcStru[i].endSegId = exitCbtcStru[i].segInfoBuff[j];
                        }
                        
                    	findStartPointNum++;
                    }
                }
            }

            if ((findEndPointNum != 1u)||(findStartPointNum != 1u))
            {
                /*һ���˳�CBTC������Ψһһ�����Seg��һ���յ�Seg*/
                exitCbtcStru[i].startSegId = 0u;
                exitCbtcStru[i].endSegId = 0u;
            }
        }
    }
}

/*
* �������ܣ������л���·�е�������
* ����˵������
* ����ֵ��  1 �ɹ�  0 ʧ��
*/
static UINT8_S CalcLineSwitchInfoAddStru(void)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S switchI = 0u;/*ѭ��ʹ��*/
    BnfLineSwitchInfoStruct* lineSwitchStru = NULL;
    BnfSegStruct* tmpSegStru = NULL;/*SEG����Ϣ�ṹ��ָ��*/
    UINT16_S lineNum = 0u;
    UINT16_S tmpNextSegId = 0u;/*��һ��SEGID*/
    UINT16_S tmpCurSegId = 0u;/*��ǰSEGID*/
    UINT8_S isFindError = 1u;/*�Ƿ��д���  1�޴���  0 �д���*/

    lineSwitchStru = GetLineSwitchInfoDataInfo(&lineNum);
    if (lineSwitchStru == NULL)
    {
        isFindError = 0u;
    }

    for ( i = 0u;(i < lineNum)&&(1u == isFindError); i++)
    {
        lineSwitchStru[i].segNum = 0u;
        /*��ѯ������֮�������SEGID�������л�����ĵ���״̬*/
        if (LINESEG_SAME_DIR == lineSwitchStru[i].lineSwitchDir)
        {
            if (lineSwitchStru[i].startSegOffset == 0u)
            {
                tmpCurSegId = lineSwitchStru[i].startLineSwitchInfoId;
                lineSwitchStru[i].segIdBuff[lineSwitchStru[i].segNum] = tmpCurSegId;
                lineSwitchStru[i].segNum++;
            }
            for (j = 0u;( j < BOTHSEG_INCLUDE_MAX_SEG)&&(lineSwitchStru[i].startLineSwitchInfoId != lineSwitchStru[i].endLineSwitchInfoId); j++)
            {
                tmpSegStru = GetIndexIdSegDataStru(tmpCurSegId);
                if (NULL != tmpSegStru)
                {
                    tmpNextSegId = tmpSegStru->segTmnlJointMainSegId;
                    if (tmpSegStru->endPointType == POINTTYPE_SWITCH)
                    {
                        for(switchI = 0u;switchI < lineSwitchStru[i].includeSwitchNum;switchI++)
                        {
                            if (tmpSegStru->endPointId == lineSwitchStru[i].switchInfoStru[switchI].switchId)
                            {
                                break;
                            }
                        }

                        if (switchI == lineSwitchStru[i].includeSwitchNum)
                        {
                            isFindError = 0u;
                            break;
                        }
                        else
                        {
                            if((SWITCH_STATUS_CONTRA == lineSwitchStru[i].switchInfoStru[switchI].switchStatus)&&(UINT16_NULL != tmpSegStru->segTmnlJointSideSegId))
                            {
                                tmpNextSegId = tmpSegStru->segTmnlJointSideSegId;
                            }
                        }
                    }

                    tmpCurSegId = tmpNextSegId;
                    if (tmpCurSegId != lineSwitchStru[i].endLineSwitchInfoId)
                    {
                        lineSwitchStru[i].segIdBuff[lineSwitchStru[i].segNum] = tmpCurSegId;
                        lineSwitchStru[i].segNum++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    isFindError = 0u;
                    break;
                }
            }

            if (lineSwitchStru[i].segEndOffset > 0u)
            {
                lineSwitchStru[i].segIdBuff[lineSwitchStru[i].segNum] = tmpCurSegId;
                lineSwitchStru[i].segNum++;
            }
        }
        else if (LINESEG_CONVER_DIR == lineSwitchStru[i].lineSwitchDir)
        {
            if (lineSwitchStru[i].startSegOffset > 0u)
            {
                tmpCurSegId = lineSwitchStru[i].startLineSwitchInfoId;
                lineSwitchStru[i].segIdBuff[lineSwitchStru[i].segNum] = tmpCurSegId;
                lineSwitchStru[i].segNum++;
            }
            for (j = 0u;( j < BOTHSEG_INCLUDE_MAX_SEG)&&(lineSwitchStru[i].startLineSwitchInfoId != lineSwitchStru[i].endLineSwitchInfoId); j++)
            {
                tmpSegStru = GetIndexIdSegDataStru(tmpCurSegId);
                if (NULL != tmpSegStru)
                {
                    tmpNextSegId = tmpSegStru->segStartJointMainSegId;
                    if (tmpSegStru->startPointType == POINTTYPE_SWITCH)
                    {
                        for(switchI = 0u;switchI < lineSwitchStru[i].includeSwitchNum;switchI++)
                        {
                            if (tmpSegStru->startPointId == lineSwitchStru[i].switchInfoStru[switchI].switchId)
                            {
                                break;
                            }
                        }

                        if (switchI == lineSwitchStru[i].includeSwitchNum)
                        {
                            isFindError = 0u;
                            break;
                        }
                        else
                        {
                            if((SWITCH_STATUS_CONTRA == lineSwitchStru[i].switchInfoStru[switchI].switchStatus)&&(UINT16_NULL != tmpSegStru->segStartJointSideSegId))
                            {
                                tmpNextSegId = tmpSegStru->segStartJointSideSegId;
                            }
                        }
                    }

                    tmpCurSegId = tmpNextSegId;
                    if (tmpCurSegId != lineSwitchStru[i].endLineSwitchInfoId)
                    {
                        lineSwitchStru[i].segIdBuff[lineSwitchStru[i].segNum] = tmpCurSegId;
                        lineSwitchStru[i].segNum++;
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    isFindError = 0u;
                    break;
                }
            }

            if (lineSwitchStru[i].segEndOffset == 0u)
            {
                lineSwitchStru[i].segIdBuff[lineSwitchStru[i].segNum] = tmpCurSegId;
                lineSwitchStru[i].segNum++;
            }
        }
        else
        {
            isFindError = 0u;
        }

        if (1u == isFindError)
        {
            lineSwitchStru[i].acNum = GetAxleSecAccordSegIdBuff(lineSwitchStru[i].segIdBuff,lineSwitchStru[i].segNum,lineSwitchStru[i].acIdBuff);
        }
    }

    if (1u == isFindError)
    {
        retVal = 1u;
    }

    return retVal;
}



/*
*�������ܣ�����ͨ����Ϣ������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
*/
UINT8_S CalcCommAddInfo(void)
{
    UINT8_S retVal = 0u;/*��������ֵ*/

    
    retVal = CalcSignInfoAddStru();
    if (1u == retVal)
    {
        retVal = CalcLogicSgmtStru();
        if (1u == retVal)
        {
            retVal = CalcAxleSectionInfo();

            if (1u != retVal)
            {
                ComBnfInitErrReason |= BNFINITERR_REASON_2;
            }
        }
        else
        {
            ComBnfInitErrReason |= BNFINITERR_REASON_1;
        }
    }
    else
    {
        ComBnfInitErrReason |= BNFINITERR_REASON_11;
    }
    
    
    if (1u == retVal)
    {
        CalcSwitchAddStru();
        CalcRouteInfoAddStru();
        CalcArInfoAddStru();
        CalcPsdInfoAddStru();
        CalcProtectSecInfoAddStru();
        CalcEsbButtonInfoAddStru();
        CalcExitCbtcInfoAddStru();
        CalcStopSecInfoAddStru();
        CalcGradeInfoAddStru();
        retVal = CalcLineSwitchInfoAddStru();
        if (1u != retVal)
        {
            ComBnfInitErrReason |= BNFINITERR_REASON_3;
        }

    }

    return retVal;
}

/*
* ���������� ��ȡCOM��ѯ������ʼ��ʧ��ԭ��
* ����˵���� void
* ����ֵ  �� COM��ѯ������ʼ��ʧ��ԭ��  
*/
UINT32_S GetComBnfInitErrReason(void)
{
    return ComBnfInitErrReason;
}

/*
* �������ܣ��������������жϵ�ǰ�ĵ���״̬�Ƿ�����������ι����ĵ���״̬��
* ��ڲ�����UINT16 axleSgmtID        �������α��
* ���ڲ�������
* ����ֵ��  UINT8_S retVal 
*          ��ѯ�ɹ�:��ǰ�ĵ���״̬������������ι����ĵ���״̬������0xFF;
*          ��ѯ�ɹ�:��ǰ�ĵ���״̬����������ι����ĵ���״̬������1      
*          ��ѯʧ�ܣ�����0
*/ 
static UINT8_S CheckPointFitAxleSgmt(UINT16_S axleSgmtID)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    BnfAxleSectionStruct *pAxleSgmtStru = NULL;/*�������νṹ��*/
    UINT8_S chFlag = 0u;/*��־λ*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/    
    UINT16_S j = 0u;/*ѭ��ʹ��*/

    /*���ù��������õ�����������Ϣ*/
    pAxleSgmtStru = GetIndexIdAxleSectionDataStru(axleSgmtID);

    if ((pAxleSgmtStru != NULL)&&(0u == pAxleSgmtStru->relatPointNum))
    {
        /*����������ֱ�ӷ��ز�ѯ�ɹ�*/
        retVal = 1u;
    }
    if ((pAxleSgmtStru != NULL)&&(4u >= pAxleSgmtStru->relatPointNum))
    {
        for (j = 0u; j< pAxleSgmtStru->relatPointNum; j++)
        {
            chFlag = 0u;
            for (i=0u; i< SwitchNum; i++)
            {
                if (SwitchStatusInfoStru[i].switchId == pAxleSgmtStru->relatPointId[j])
                {
                    /*����״̬����*/
                    if ((SWITCH_STATUS_SAME != SwitchStatusInfoStru[i].switchStatus)&&(SWITCH_STATUS_CONTRA != SwitchStatusInfoStru[i].switchStatus))
                    {
                        /*��ѯʧ�ܣ�����Ĭ��ֵ*/
                        retVal = UINT8_NULL;
                        break;
                    }                        
                    /*�ڵ����ʵʱ״̬��������εĹ�������״̬��ͬʱ,��ǰ�������μ�Ϊ����*/
                    if (((SWITCH_STATUS_SAME == SwitchStatusInfoStru[i].switchStatus) && (SWITCH_STATUS_SAME == pAxleSgmtStru->relatPointStatus[j])) 
                        || ((SWITCH_STATUS_CONTRA == SwitchStatusInfoStru[i].switchStatus) && (SWITCH_STATUS_CONTRA == pAxleSgmtStru->relatPointStatus[j])))
                    {
                        /*����״̬ƥ��*/
                        chFlag = 1u;
                        break;
                    }
                }
            }
            if (0u == chFlag)
            {
                retVal = UINT8_NULL;
                break;
            }
        }

        if (1u == chFlag)
        {
            retVal = 1u;
        }
    }

    return retVal;
}

/*
* �������ܣ������������ǲ�ѯ��ǰ�������ε����ڼ������Ρ����ڼ������η�Ϊ������ڼ������κ��յ����ڼ�������
* ��ڲ�����UINT16 currentACID                    �������α��
*            UINT8_S dir                            ���з���
*            UINT8_S startOrEnd                    �����յ㣨1Ϊ��㣬2Ϊ�յ㣩
* ���ڲ�������
* ����ֵ��  UINT8_S retVal ��ѯʧ��:0
*            1 �ɹ�
*            2 ��·���յ�
*            3 ����״̬δ֪
*/
UINT8_S FindAdjacentACID(const UINT16_S currentACID,const UINT8_S dir,const UINT8_S startOrEnd,UINT8_S* axleSecNum,UINT16_S* axleSecIdBuff)
{

    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT16_S tmpFindAxleSgmtID = 0u;/*��ʱ����--�洢���ڼ�������id*/
    BnfAxleSectionStruct *pAxleSgmtStruct = NULL;/*ָ�����������Ϣ�Ľṹ��ָ��*/
    UINT8_S tmpNum = 0u;/*ѭ������--���ڱ��������������ڼ�������*/
    UINT8_S isFind = 0u;/*�Ƿ��ҵ����ڵļ������Σ�1Ϊ�ҵ���0Ϊû���ҵ�*/
    UINT8_S isErrorFalg = 1u;/*0 ���󷵻�  1 ��ȷ����*/

    if((NULL == axleSecNum) || (NULL == axleSecIdBuff))
    {
        isErrorFalg = 0u;
    }

    /*�ж�������ݷ������ȷ��*/
    if ((0u == isErrorFalg) || ((LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir)))
    {
        /*������ݷ�����󣬲�ѯʧ�ܣ����ش���*/
        isErrorFalg = 0u;
    }

    /*�ж�������ݶ˵����ȷ��*/
    if ((0u == isErrorFalg)||((START_POINT != startOrEnd) && (END_POINT != startOrEnd))||(NULL == axleSecIdBuff)) 
    {
        isErrorFalg = 0u;
    }

    /*���ù������ҵ��������ε������Ϣ*/
    pAxleSgmtStruct =  GetIndexIdAxleSectionDataStru(currentACID);
    if ((0u == isErrorFalg)||(NULL == pAxleSgmtStruct))
    {
        isErrorFalg = 0u;
    }
    /*1. ���з���Ϊͬ�� ��ѯ���˵㷽��
      2. ���з���Ϊ���򣬲�ѯ�յ�˵㷽��
    ��������������£���ѯ��ǰ�������ε�ʼ�����ڼ�������*/
    if ((1u == isErrorFalg)&&(((LINESEG_SAME_DIR == dir) && (START_POINT == startOrEnd))
        || ((LINESEG_CONVER_DIR == dir) && (END_POINT == startOrEnd))))
    {
        /*�������ڼ������Σ�Ȼ����֤����״̬�Ƿ�ƥ���������*/
        if (0u == pAxleSgmtStruct->orgnAxleSecNum)
        {
            /*1.û�����ڼ�������*/
            retVal = 2u;
        }
        else
        {
            isFind=0u;
            for (tmpNum=0u;tmpNum<pAxleSgmtStruct->orgnAxleSecNum;tmpNum++)
            {
                tmpFindAxleSgmtID=pAxleSgmtStruct->orgnAxleSgmtId[tmpNum];

                /*���ڼ������δ���*/
                if (tmpFindAxleSgmtID != 0xffffu)
                {
                    /*���ú������жϵ�ǰ����״̬�Ƿ�����������Ρ�*/
                    retVal = CheckPointFitAxleSgmt(tmpFindAxleSgmtID);
                    if (1u == retVal)
                    {
                        /*�ҵ����ڼ�������*/
                        isFind=1u;
                        /*������ͬʱ���������ڼ�������ͬʱƥ�����,�����ҵ�һ���Ϳ���*/
                        break;
                    }
                    else
                    {
                        /*״̬�����㣬������֤��һ����������*/
                    }
                } 
                else
                {
                    /*���ڼ������β����ڣ�����������һ����������*/
                }
            }

            /*���ڼ������Σ����Ƕ����������״̬*/
            if (isFind != 1u)
            {
                *axleSecNum = pAxleSgmtStruct->orgnAxleSecNum;
                MemoryCpy(axleSecIdBuff,sizeof(UINT16_S)*pAxleSgmtStruct->orgnAxleSecNum,pAxleSgmtStruct->orgnAxleSgmtId,sizeof(UINT16_S)*pAxleSgmtStruct->orgnAxleSecNum);
                retVal = 3u;
            } 
            else
            {
                *axleSecNum = 1u;
                axleSecIdBuff[0] = tmpFindAxleSgmtID;
                retVal = 1u;
            }
        }
    }
    else if ((1u == isErrorFalg)&&(((LINESEG_SAME_DIR == dir) && (END_POINT == startOrEnd))
        || ((LINESEG_CONVER_DIR == dir) && (START_POINT == startOrEnd))))
    {
        /*1. ���з���Ϊ���� ��ѯ���˵㷽��
        2. ���з���Ϊͬ�򣬲�ѯ�յ�˵㷽��
        ��������������£���ѯ��ǰ�������ε�ĩ�����ڼ�������*/        
        if (0u == pAxleSgmtStruct->tmnlAxleSecNum)
        {
            /*1.û�����ڼ�������*/
            retVal = 2u;
        }
        else
        {
            isFind=0u;
            /*�������ڼ������Σ�Ȼ����֤����״̬�Ƿ�ƥ���������*/
            for (tmpNum=0u;tmpNum<pAxleSgmtStruct->tmnlAxleSecNum;tmpNum++)
            {
                tmpFindAxleSgmtID=pAxleSgmtStruct->tmnlAxleSgmtId[tmpNum];

                /*���ڼ������δ���*/
                if (tmpFindAxleSgmtID != UINT16_NULL)
                {
                    /*���ú������жϵ�ǰ����״̬�Ƿ�����������Ρ�*/
                    retVal = CheckPointFitAxleSgmt(tmpFindAxleSgmtID);
                    if (1u == retVal)
                    {
                        /*�ҵ����ڼ�������*/
                        isFind=1u;
                        /*������ͬʱ���������ڼ�������ͬʱƥ�����,�����ҵ�һ���Ϳ���*/
                        break;
                    }
                    else
                    {
                        /*״̬�����㣬������֤��һ����������*/
                    }
                } 
                else
                {
                    /*���ڼ������β����ڣ�����������һ����������*/
                }
            }
            /*���ڼ������Σ����Ƕ����������״̬*/
            if (isFind != 1u)
            {
                *axleSecNum = pAxleSgmtStruct->tmnlAxleSecNum;
                MemoryCpy(axleSecIdBuff,sizeof(UINT16_S)*pAxleSgmtStruct->tmnlAxleSecNum,pAxleSgmtStruct->tmnlAxleSgmtId,sizeof(UINT16_S)*pAxleSgmtStruct->tmnlAxleSecNum);
                retVal = 3u;
            } 
            else
            {
                *axleSecNum = 1u;
                axleSecIdBuff[0] = tmpFindAxleSgmtID;
                retVal = 1u;
            }
        }
    }
    else
    {
        /*Do nothing currently !*/
    }
    return retVal;
}

/*
* ���������� ��ѯ��ǰ����ǰ����һ�����������һ�����λ��
* ����˵���� const UINT16_S seg1,
*            const UINT32_S offset1,
*            const UINT8_S dir,
*            const UINT32_S distance,

*            UINT16_S *outSeg,
*            UINT32_S *outOffset,
*            UINT16_S *errorSwitchId
* ����ֵ��         
0x03��λ�ü���ɹ�
0x02��λ�ü���ʧ�ܣ�ԭ�����λ�ô���
0x01��λ�ü���ʧ�ܣ�ԭ����·��ͷ��
0x00��λ�ü���ʧ�ܣ�ԭ����ڲ�������
*/
UINT8_S CheckNextPointOnDistance(const UINT16_S seg1,const UINT32_S offset1,const UINT8_S dir,const UINT32_S distance,UINT16_S *outSeg,UINT32_S *outOffset,UINT16_S *errorSwitchId)
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT8_S flag = 1u;/*����ֵ��־*/
    UINT32_S segLength = 0u;/*SEG����*/
    UINT16_S pointId = 0u;/*��ID*/
    UINT16_S pointType = 0u;/*������*/
	UINT16_S nextPointType = 0u;/*��һ��Seg�ĵ�����*/
    UINT16_S curSegId = 0u;/*��ǰSEGID*/
    UINT16_S nextMainSegId = 0u;/*��һ������SEGID*/
	UINT16_S nestSideSegId = 0u;/*��һ������SEGID*/
	UINT16_S nextSegId = 0u;/*��һ������SEGID*/
	UINT16_S frontMainSegId = 0u;/*��һ������SEGID*/
	UINT16_S frontSideSegId = 0u;/*��һ������SEGID*/
    UINT32_S findSegLength = 0u;/*�Ѳ��ҵľ�����Ϣ*/
    UINT8_S switchStatus = 0u;/*����״̬*/
    UINT32_S tempNewSegLength = 0u;/*��ʱ���SEG����*/
	UINT8_S flagForWhile = 0u;
    

    if((NULL == outSeg) || (NULL == outOffset) || (NULL == errorSwitchId))
    {
        flag = 0u;
    }

    
    segLength = GetSegDataStrulength(seg1);
    /*�ж����������λ��ƫ��������Ч��*/    
    if ((0u == flag)|| (offset1 > segLength)) 
    {
        flag = 0u;
    }
    
    /*�ж�������ݷ������ȷ��*/
    if ((0u == flag) || ((dir != LINESEG_SAME_DIR) && (dir != LINESEG_CONVER_DIR)))
    {
        flag = 0u;
    }

    /*��1. ƫ����Ϊ���������з�����ǰ��
        2. ƫ����Ϊ���������з������ʱ����ǰ���������λ��*/
    if ((1u == flag)&&(LINESEG_SAME_DIR == dir))
    {
        findSegLength = segLength - offset1;
        curSegId = seg1;
        tempNewSegLength = segLength;
    	retVal = 3u;

        while ((findSegLength < distance) || (1u == flagForWhile))
        {
            /*��ȡ��ǰSEG���յ�ID������*/
        	flagForWhile = 0u;
        	pointType = 0u;
            pointId = GetSegDataStruendPointInfo(curSegId,&pointType);

            nextMainSegId = GetSegDataStrusegTmnlJointMainSegId(curSegId);
        	nestSideSegId = GetSegDataStrusegTmnlJointSideSegId(curSegId);

            if ((nextMainSegId != 65535u) || (nestSideSegId != 65535u))
            {
                /*�жϵ������Ƿ�Ϊ����*/
                if(POINTTYPE_SWITCH == pointType)
                {
                    /*��ȡ����״̬*/
                	switchStatus = GetSwitchStatus(pointId);

                	if ((nextMainSegId != 65535u) && (nestSideSegId != 65535u))
                    {
                    	if (SWITCH_STATUS_SAME == switchStatus)
                        {
                            /*��һ��SEGID�Ѿ���ȡ��Ϊ�յ������SEG*/
                        	nextSegId = nextMainSegId;
                        }
                    	else if(SWITCH_STATUS_CONTRA == switchStatus)
                        {
                        	nextSegId = nestSideSegId;
                        }
                    	else
                        {
                            *errorSwitchId = pointId;
                        	retVal = 0x02u;
                        	break;
                        }
                    }
                	else if((nextMainSegId != 65535u) && (nestSideSegId == 65535u))
                    {
                        /*��ȡ��seg�ķ���Seg(�������Seg)���,��ȷ����ѯ����seg��Ҫ�ĵ�����*/
                    	frontMainSegId = GetSegDataStrusegStartJointMainSegId(nextMainSegId);
                    	frontSideSegId = GetSegDataStrusegStartJointSideSegId(nextMainSegId);

                    	if ((frontMainSegId == curSegId) && (switchStatus == SWITCH_STATUS_SAME))
                        {
                        	nextSegId = nextMainSegId;
                        }
                    	else if((frontSideSegId == curSegId) && (switchStatus == SWITCH_STATUS_CONTRA))
                        {
                        	nextSegId = nextMainSegId;
                        }
                    	else
                        {
                            /*�������,����δ����Ҫλ��*/
                            *errorSwitchId = pointId;
                        	retVal = 0x02u;
                        	break;
                        }
                    }
                	else
                    {
                        /*0x00��λ�ü���ʧ�ܣ�����ԭ��*/
                    	retVal = 0x00u;
                    	break;
                    }
                }
            	else
                {
                    /*�����,��ȡ������һ��SEG���յ�����*/
                	if(POINTTYPE_AXLE == pointType)
                    {
                    	nextPointType = 0u;
                    	GetSegDataStruendPointInfo(nextMainSegId,&nextPointType);

                    	if (POINTTYPE_SWITCH == nextPointType)
                        {
                        	flagForWhile = 1u;
                        }
                    }
                	nextSegId = nextMainSegId;
                }

                /*�����Ѳ�ѯ������Ϣ�͵�ǰseg��Ϣ*/
            	if (findSegLength <= distance)
                {
                	tempNewSegLength = GetSegDataStrulength(nextSegId);
                	findSegLength = findSegLength + tempNewSegLength;
                	curSegId = nextSegId;
                }
            }
            else
            {
                /*0x01��λ�ü���ʧ�ܣ�ԭ����·��ͷ��*/
                retVal = 0x01u;
                break;
            }
        }
        if(retVal == 3u)
        {
            /*�����Ϣ����ѯ�ɹ�*/
            *outSeg = curSegId;
            *outOffset = distance - (findSegLength-tempNewSegLength);
        }
    }
    else if ((1u == flag)&&(LINESEG_CONVER_DIR == dir))
    {
        findSegLength = offset1;
        curSegId = seg1;
        tempNewSegLength = 0u;
    	retVal = 3u;

        while ((findSegLength < distance) || (1u == flagForWhile))
        {
            /*��ȡ��ǰSEG�����ID*/
        	flagForWhile = 0u;
        	pointType = 0u;
            pointId = GetSegDataStrustartPointInfo(curSegId,&pointType);

            nextMainSegId = GetSegDataStrusegStartJointMainSegId(curSegId);
        	nestSideSegId = GetSegDataStrusegStartJointSideSegId(curSegId);

            if ((nextMainSegId != 65535u) || (nestSideSegId != 65535u))
            {
                /*�жϵ������Ƿ�Ϊ����*/
                if(POINTTYPE_SWITCH  == pointType)
                {
                    /*��ȡ����״̬*/
                	switchStatus = GetSwitchStatus(pointId);

                	if ((nextMainSegId != 65535u) && (nestSideSegId != 65535u))
                    {
                    	if (SWITCH_STATUS_SAME == switchStatus)
                        {
                            /*��һ��SEGID�Ѿ���ȡ��Ϊ�յ������SEG*/
                        	nextSegId = nextMainSegId;
                        }
                    	else if(SWITCH_STATUS_CONTRA == switchStatus)
                        {
                        	nextSegId = nestSideSegId;
                        }
                    	else
                        {
                            *errorSwitchId = pointId;
                        	retVal = 0x02u;
                        	break;
                        }
                    }
                	else if((nextMainSegId != 65535u) && (nestSideSegId == 65535u))
                    {
                        /*��ȡ��seg�ķ���Seg(�������Seg)���,��ȷ����ѯ����seg��Ҫ�ĵ�����*/
                    	frontMainSegId = GetSegDataStrusegTmnlJointMainSegId(nextMainSegId);
                    	frontSideSegId = GetSegDataStrusegTmnlJointSideSegId(nextMainSegId);

                    	if ((frontMainSegId == curSegId) && (switchStatus == SWITCH_STATUS_SAME))
                        {
                        	nextSegId = nextMainSegId;
                        }
                    	else if((frontSideSegId == curSegId) && (switchStatus == SWITCH_STATUS_CONTRA))
                        {
                        	nextSegId = nextMainSegId;
                        }
                    	else
                        {
                            /*�������,����δ����Ҫλ��*/
                            *errorSwitchId = pointId;
                        	retVal = 0x02u;
                        	break;
                        }
                    }
                	else
                    {
                        /*0x00��λ�ü���ʧ�ܣ�����ԭ��*/
                    	retVal = 0x00u;
                    	break;
                    }
                }
            	else
                {
                    /*�����,��ȡ������һ��SEG���������*/
                	if(POINTTYPE_AXLE == pointType)
                    {
                    	nextPointType = 0u;
                    	GetSegDataStrustartPointInfo(nextMainSegId,&nextPointType);

                    	if (POINTTYPE_SWITCH == nextPointType)
                        {
                        	flagForWhile = 1u;
                        }
                    }
                	nextSegId = nextMainSegId;
                }

            	if (findSegLength <= distance)
                {
                    /*�����Ѳ�ѯ������Ϣ�͵�ǰseg��Ϣ*/
                	tempNewSegLength =  GetSegDataStrulength(nextSegId);
                	findSegLength = findSegLength + tempNewSegLength;
                	curSegId = nextSegId;
                }
                
            	retVal = 3u;
            }
            else
            {
                /*0x01��λ�ü���ʧ�ܣ�ԭ����·��ͷ��*/
                retVal = 0x01u;
                break;
            }
        }
        if(retVal == 3u)
        {
            /*�����Ϣ����ѯ�ɹ�*/
            *outSeg = curSegId;
            *outOffset = findSegLength - distance;
        }
    }
    else
    {
        /*Do nothing currently !*/
    }

    return retVal;
}

/*
* ���������� ��ȡSEGID�����ļ�������ID
* ����˵���� UINT16_S  segId��SegID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:�������θ���
*/
UINT8_S GetAxleSecAccordSegIdBuff(const UINT16_S* pSegId,const UINT8_S segNum,UINT16_S* pAxleSecId)
{
    UINT8_S retVal = 0u;

    UINT8_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S k = 0u;/*ѭ��ʹ��*/
    UINT8_S tempJ = 0u;/*ѭ��ʹ��*/
    UINT8_S index = 0u;/*�����±�*/

    UINT16_S tmpAcSecBuff[TWO_POINT_AC_NUM_MAX] = {0};
    UINT16_S tmpSegIdBuff[3] = {0};
    UINT8_S tmpSegIdNum = 0u;
    UINT8_S needFindNum = 0u;/*��Ҫ���ҵ��ĸ���*/

    if (((segNum <= BOTHSEG_INCLUDE_MAX_SEG)&&(segNum > 0u))
        &&(pSegId != NULL)&&(pAxleSecId != NULL))
    {
        for (k = 0u;k < segNum; k++)
        {
            /*���ݴ�SEGǰ���Ƿ��е�����SEGID*/
            tmpSegIdNum = GetSegBuffAccordSedIdAndSwitch(pSegId[k],tmpSegIdBuff,&needFindNum);

            tmpAcSecBuff[index] = GetSegIdBelongofAxleSecId(tmpSegIdBuff,tmpSegIdNum,needFindNum);
            if (tmpAcSecBuff[index] > 0u)
            {
                index++;
            }
            else
            {
                index = 0u;
                break;
            }
        }

        for (j = 0u; j < index; j++)
        {
            for (k = 0u;k < tempJ; k++)
            {
                if (tmpAcSecBuff[j] == pAxleSecId[k])
                {
                    break;
                }
            }

            if (k == tempJ)
            {
                pAxleSecId[tempJ] = tmpAcSecBuff[j];
                tempJ=tempJ+1;
            }
        }
    }

    if (tempJ > 0u)
    {
        retVal = tempJ;
    }

    return retVal;
}



/*
* ���������� ���ݵ�ǰλ�ú�λ��,�õ���λ��.(��֪�����״̬)
* ����˵���� const UINT16_S seg1,
*            const UINT32_S offset1,
*            const UINT8_S dir,
*            const INT32_S distance,
*            UINT16_S *outSeg,
*            UINT32_S *outOffset,
*            UINT8_S* outDir
* ����ֵ��   1,�ɹ�
*            0,ʧ��
*/
UINT8_S GetNewLocCalcDis(const UINT16_S seg1,const UINT32_S offset1,const UINT8_S dir,const INT32_S distance,UINT16_S *outSeg,UINT32_S *outOffset,UINT8_S* outDir) 
{
    UINT8_S retVal=0u;/*��������ֵ*/
    UINT8_S isFindError = 1u;/*�Ƿ��д���  1�޴���  0 �д���*/
    UINT16_S curSegId = 0u;/*���ڲ��ҹ�������ʱ���浱ǰSegID*/
    UINT16_S nextSegId = 0u;/*��һ��SEGID*/
    UINT8_S findDir = 0u;/*���ڼ�¼ʵ�ʲ��������еĲ��ҷ���*/
    INT32_S findDis = 0;/*��ʱ����ƫ����*/
    INT32_S findDisSum = 0;/*�����ۼ�λ��ƫ����*/
    UINT32_S tmpNewSegLength = 0u;/*��ʱ���SEG����*/
    BnfSegStruct* tmpSegStru = 0;/*��ʱ���SEG�ṹ��*/


    if((NULL == outSeg) || (NULL == outOffset) || (NULL == outDir))
    {
        isFindError = 0u;
    }

    

    /*��Ч�Լ��*/
    tmpSegStru = GetIndexIdSegDataStru(seg1);
    if((0u == isFindError)|| (NULL == tmpSegStru)||(tmpSegStru->length < offset1)
        ||((dir != LINESEG_SAME_DIR)&&(dir != LINESEG_CONVER_DIR)))
    {
        isFindError = 0u;
    }

    /*�����������ƫ����distanceΪ0*/
    if ((1u == isFindError)&&(distance == 0))
    {
        /*distance���Ϊ0�����ص�ǰλ��Ϊ����*/
        *outSeg = seg1;
        *outOffset = offset1;
        *outDir = dir;

        /*��ѯ�ɹ������ز�ѯ���*/
        retVal = 1u;
    }
    else
    {        
        /*���displacementС��0������displacement����ֵ��������λ�ã�����ȡ��*/
        if((LINESEG_SAME_DIR == dir)&&(distance > 0))
        {
            /*�������*/
            findDir = LINESEG_SAME_DIR;
            findDis = distance;
        }
        else if((LINESEG_CONVER_DIR == dir)&&(distance<0))
        {
            /*�������*/
            findDir = LINESEG_SAME_DIR;
            findDis = -distance;
        }
        else if((LINESEG_SAME_DIR == dir)&&(distance < 0))
        {
            /*�������*/
            findDir = LINESEG_CONVER_DIR;
            findDis = -distance;
        }
        else if((LINESEG_CONVER_DIR == dir)&&(distance > 0))
        {
            /*�������*/
            findDir = LINESEG_CONVER_DIR;
            findDis = distance;
        }
        else
        {
            /*���ɴ��֧*/
        }
    }

    if((isFindError == 1u)&&(0u == retVal)&&(findDir == LINESEG_SAME_DIR))
    {
        /*���ݵ�ǰλ�������ۼ�ƫ����*/
        findDisSum = tmpSegStru->length - offset1;

        /*����λ���ж���λ���Ƿ���ͬһ��SEG��*/
        if(findDisSum >= findDis)
        {
            /*˵����ͬһ��Seg�ϣ��ۼ�λ�Ƶõ���λ��*/
            *outSeg = seg1;
            *outOffset = offset1 + findDis;
            *outDir = dir;
            retVal = 1u;
        }
        else
        {
            curSegId = seg1;
            while (findDisSum <= findDis)
            {
                /*��ȡ��ǰSEG���յ�ID������*/
                retVal = GetNextSegId(curSegId,findDir,&nextSegId);
                if (1u == retVal)
                {
                    /*�����Ѳ�ѯ������Ϣ�͵�ǰseg��Ϣ*/
                    tmpNewSegLength = GetSegDataStrulength(nextSegId);
                    findDisSum = findDisSum + tmpNewSegLength;
                    curSegId = nextSegId;
                }
                else
                {
                    retVal = 0x0u;
                    break;
                }
            }

            if(0u != retVal)
            {
                /*�����Ϣ����ѯ�ɹ�*/
                *outSeg = curSegId;
                *outOffset = findDis - (findDisSum-tmpNewSegLength);
                *outDir = dir;
                retVal = 1u;
            }
        }
    }
    else if((isFindError == 1u)&&(0u == retVal))
    {
        /*�ۼ�ƫ������0*/
        findDisSum=0;

        /*���ݵ�ǰλ�÷����ۼ�ƫ����*/
        findDisSum= offset1;

        if(findDisSum >= findDis)
        {
            /*˵����ͬһ��Seg��*/
            *outSeg = seg1;
            *outOffset =offset1 - findDis;
            *outDir = dir;

            /*��ѯ�ɹ������ز�ѯ���*/
            retVal = 1u;
        }
        else
        {
            curSegId = seg1;
            while (findDisSum <= findDis)
            {
                /*��ȡ��ǰSEG���յ�ID������*/
                retVal = GetNextSegId(curSegId,findDir,&nextSegId);
                if (1u == retVal)
                {
                    /*�����Ѳ�ѯ������Ϣ�͵�ǰseg��Ϣ*/
                    findDisSum = findDisSum + GetSegDataStrulength(nextSegId);
                    curSegId = nextSegId;
                }
                else
                {
                    retVal = 0x0u;
                    break;
                }
            }

            if(0u != retVal)
            {
                /*�����Ϣ����ѯ�ɹ�*/
                *outSeg = curSegId;
                *outOffset = findDisSum - findDis;
                *outDir = dir;
                retVal = 1u;
            }
        }
    }
    else
    {
        /*Do nothing currently !*/
    }

    return retVal;
}

/*
* ���������� ��ȡ����ľ�������,����㵽�յ㷽��
* ����˵���� const UINT16_S startSegId,const UINT32_S startSegoffset,
*            const UINT16_S endSegId,const UINT32_S endSegoffset,const UINT16_S endDir,INT32_S* distance
* ����ֵ  �� 0: ��ȡʧ��
*             1����ȡ�ɹ�
*/
UINT8_S GetDirBothSegPointVectorDis(const UINT16_S startSegId,const UINT32_S startSegoffset,
                        const UINT16_S endSegId,const UINT32_S endSegoffset,const UINT16_S endDir,INT32_S* distance)
{

    UINT8_S retVal = 0u;/*���ں�������ֵ*/
    UINT8_S isFindError = 1u;/*�Ƿ��д���  1�޴���  0 �д���*/
    UINT16_S tmpNextSegId = 0u;/*���ڲ��ҹ�������ʱ������һ��SegID*/
    UINT8_S startFindFlag = 1u;/*0������ʧ��1,�������ҡ�*/
    UINT8_S endFindFlag = 1u;/*0������ʧ��1���������ҡ�*/
    INT32_S startFindDisSum = 0;/*start����end�����е�λ���ۼ�ֵ*/
    INT32_S endFindDisSum = 0;/*end����start������λ���ۼ�ֵ*/
    UINT16_S tmpStartCurSegId = 0u;/*���ڲ��ҹ�������ʱ������㵱ǰSegID*/
    UINT16_S tmpEndCurSegId = 0u;/*���ڲ��ҹ�������ʱ�����յ㵱ǰSegID*/
    BnfSegStruct *pStartCurSegStru = NULL;/*start��ǰSeg*/
    BnfSegStruct *pEndCurSegStru = NULL;/*end��ǰSeg*/
    UINT16_S i = 0u;/*ѭ���ñ���*/

    if(NULL == distance)
    {
        isFindError = 0u;
    }
	else
    {
        /*Ԥ�ú�������ֵΪ0*/
        *distance = 0;
    }
 

    pStartCurSegStru = GetIndexIdSegDataStru(startSegId);
    if ((0u == isFindError)|| (NULL == pStartCurSegStru)||(pStartCurSegStru->length < startSegoffset))
    {
        isFindError = 0u;
    }
    else
    {
        pEndCurSegStru = GetIndexIdSegDataStru(endSegId);
        if ((NULL == pEndCurSegStru)||(pEndCurSegStru->length < endSegoffset)||
            ((LINESEG_SAME_DIR != endDir) && (LINESEG_CONVER_DIR != endDir)))
        {
            isFindError = 0u;
        }
    }

    /*�����������Segstart��Segend����ͬһSeg��*/
    if(startSegId == endSegId)
    {
        /*start,endλ��ͬһseg����������������Ϣ*/
        *distance = endSegoffset - startSegoffset;
        
        if (LINESEG_CONVER_DIR == endDir)
        {
            /*�����෴��ת��λ�Ʒ���*/
            *distance=-(*distance);
        }

        /*������ѯ�ɹ�������*/        
        retVal=1u;
    }

    
    tmpStartCurSegId = startSegId;
    tmpEndCurSegId = endSegId;
    /*����end�ķ���ͬ���з���*/
    /*�����յ�ֱ𰴴˷�����ҶԷ�,����ҵ��Է�,��¼���ҵ���λ��,���ؽ��*/
    if ((1u == isFindError)&&(0u == retVal)&&(LINESEG_SAME_DIR == endDir))
    {
        /*�ۼ�λ��ֵ*/
        startFindDisSum = pStartCurSegStru->length - startSegoffset;
        endFindDisSum = pEndCurSegStru->length - endSegoffset;
        for (i = 0u; i < BOTHSEG_INCLUDE_MAX_SEG;i++)
        {
            /*�˴�ѭ����Ϊ�˼�����ѭ���������ܳ���BOTHSEG_INCLUDE��MAX_SEG*/
            if(1u == startFindFlag)
            {
                /*start��ǰ����һ��seg*/
                retVal = GetNextSegId(tmpStartCurSegId, LINESEG_SAME_DIR, &tmpNextSegId);
                if( 1u==retVal )
                {
                    if(tmpNextSegId == endSegId)
                    {
                        /*���ҳɹ�*/
                        startFindFlag = 1u;
                        /*�ۼ�ƫ������������ֵ*/
                        startFindDisSum += endSegoffset;
                        /*��ʱstart�������ҵ���end��ƫ����Ϊ��*/
                        *distance = startFindDisSum;

                        /*���ҳɹ������ؽ��*/
                        retVal=1u;
                        break;
                    }
                    else
                    {
                        /*startû���ҵ�end���ۼ�ƫ��������������*/
                        startFindDisSum += GetSegDataStrulength(tmpNextSegId);
                        tmpStartCurSegId = tmpNextSegId;
                    }
                }
                else
                {
                    /*��·�յ���ߵ���״̬δ֪��start��ֹͣ����*/
                    startFindFlag = 0u;
                }
            }

            /*end��ǰ����һ��seg*/
            if(1u == endFindFlag)
            {
                retVal=GetNextSegId(tmpEndCurSegId,LINESEG_SAME_DIR,&tmpNextSegId);
                if( 1u== retVal)
                {
                    if(tmpNextSegId == startSegId)
                    {
                        /*�ۼ�ƫ������������ֵ*/
                        endFindDisSum += (startSegoffset);

                        /*��ʱend�������ҵ���start��ƫ����Ϊ��*/
                        *distance =- endFindDisSum;

                        /*���ҳɹ������ؽ��*/
                        retVal=1u;
                        break;
                    }
                    else
                    {
                        /*���endû���ҵ�start���ۼ�ƫ��������������*/
                        endFindDisSum += GetSegDataStrulength(tmpNextSegId);
                        tmpEndCurSegId = tmpNextSegId;
                    }
                }
                else
                {
                    /*��·�յ���ߵ���״̬δ֪��ֹͣ����*/
                    endFindFlag=0u;            
                }
            }

            if((0u == startFindFlag)&&(0u == endFindFlag))
            {
                /*start��end���������Ҳ���û���ҵ��Է�����������ʧ��*/
                retVal=0u;
                break;
            }
        }
    }
    else if ((1u == isFindError)&&(0u == retVal))
    {
        /*start,end���ط��������*/
        startFindDisSum = startSegoffset;
        endFindDisSum = endSegoffset;
        for (i = 0u;i < BOTHSEG_INCLUDE_MAX_SEG;i++)
        {
            if(1u == startFindFlag)
            {
                /*start��ǰ����һ��seg*/
                retVal=GetNextSegId(tmpStartCurSegId, LINESEG_CONVER_DIR,&tmpNextSegId);
                if( 1u==retVal )
                {
                    if(tmpNextSegId == endSegId)
                    {
                        startFindDisSum += (GetSegDataStrulength(tmpNextSegId)- endSegoffset);

                        /*��ʱstart�ط����ҵ���end��ƫ����Ϊ��*/
                        *distance = startFindDisSum;

                        /*���ҳɹ������ؽ��*/
                        retVal=1u;
                        break;
                    }
                    else
                    {
                        /*���startû���ҵ�end���ۼ�ƫ��������������*/
                        startFindDisSum += GetSegDataStrulength(tmpNextSegId);
                        tmpStartCurSegId = tmpNextSegId;
                    }
                }
                else
                {
                    /*��·�յ���ߵ���δ�ҵ���ֹͣ����*/
                    startFindFlag=0u;
                }
            }

            /*end��ǰ����һ��seg*/
            if(1u == endFindFlag)
            {
                retVal = GetNextSegId(tmpEndCurSegId, LINESEG_CONVER_DIR,&tmpNextSegId);
                if( 1u== retVal)
                {
                    if(tmpNextSegId == startSegId)
                    {
                        /*end�ҵ���start*/
                        endFindDisSum += (GetSegDataStrulength(tmpNextSegId)- startSegId);

                        /*��ʱend�ط����ҵ���start��ƫ����Ϊ��*/
                        *distance = -endFindDisSum;

                        /*���ҳɹ������ؽ��*/
                        retVal=1u;
                        break;
                    }
                    else
                    {
                        /*���endû���ҵ�start���ۼ�ƫ��������������*/
                        endFindDisSum += GetSegDataStrulength(tmpNextSegId);
                        tmpEndCurSegId = tmpNextSegId;
                    }
                }
                else
                {
                    /*��·�յ���ߵ���״̬δ֪��ֹͣ����*/
                    endFindFlag=0u;            
                }
            }

            if((0u == startFindFlag)&&(0u == endFindFlag))
            {
                /*start��end���������Ҳ���û���ҵ��Է�����������ʧ��*/
                retVal=0u;
                break;
            }
        }
    }
    else
    {
        /*Do nothing currently !*/
    }

    return retVal;
}

/*
* ���������� ����SEG�Լ�SEG��ǰ���ͺ��Ƿ��е���,���е������ӵ���ǰ����󷽵�SEGID������,֮�䷵�ش�SEGID��
*            (Ŀǰ���ݴ����SEG��ǰ���������2��)
* ����˵���� const UINT16_S segId,SEG��ID
*             UINT16_S* segBuff    SEG��ַ
* ����ֵ  �� 0: ��ȡʧ��
*            >0: SEGID����
*/
UINT8_S GetSegBuffAccordSedIdAndSwitch(const UINT16_S segId,UINT16_S* segBuff,UINT8_S* findNum)
{ 
    BnfSegStruct* bnfSegStru = NULL;
    UINT8_S switchStatus = 0u;/*����״̬*/
    UINT8_S index = 0u;/*ƫ��*/
    UINT16_S tmpSegId = 0u;
    bnfSegStru = GetIndexIdSegDataStru(segId);
    if ((segBuff != NULL) && (NULL != bnfSegStru) && (NULL != findNum))
    {
        *findNum = 0u;
        
        segBuff[index] = segId;
        index=index+1;
        if (bnfSegStru->endPointType == POINTTYPE_SWITCH)
        {
            /*��ȡ����״̬*/            
            switchStatus = GetSwitchStatus(bnfSegStru->endPointId);
            if (SWITCH_STATUS_SAME == switchStatus)
            {    
                if(bnfSegStru->segTmnlJointMainSegId != UINT16_NULL)
                {
                    segBuff[index] = bnfSegStru->segTmnlJointMainSegId;
                    index=index+1;
                    tmpSegId = AccordSwitchAndPointTypeGetSegId(bnfSegStru->segTmnlJointMainSegId,END_POINT);
                    if (tmpSegId > 0u)
                    {
                        segBuff[index] = tmpSegId;
                        index=index+1;
                    }
                }
            }
            else if (SWITCH_STATUS_CONTRA == switchStatus)
            {
                if(bnfSegStru->segTmnlJointSideSegId != UINT16_NULL )
                {
                    segBuff[index] = bnfSegStru->segTmnlJointSideSegId;
                    index=index+1;
                    tmpSegId = AccordSwitchAndPointTypeGetSegId(bnfSegStru->segTmnlJointSideSegId,END_POINT);
                    if (tmpSegId > 0u)
                    {
                        segBuff[index] = tmpSegId;
                        index=index+1;
                    }
                }

            }
            else
            {
                /*Do nothing currently !*/
            }
        }

        if (bnfSegStru->startPointType == POINTTYPE_SWITCH)
        {
            /*��ȡ����״̬*/
            switchStatus = GetSwitchStatus(bnfSegStru->startPointId);
            if (SWITCH_STATUS_SAME == switchStatus)
            {
                if(bnfSegStru->segStartJointMainSegId != UINT16_NULL)
                {
                    segBuff[index] = bnfSegStru->segStartJointMainSegId;
                    index=index+1;
                    tmpSegId = AccordSwitchAndPointTypeGetSegId(bnfSegStru->segStartJointMainSegId,START_POINT);
                    if (tmpSegId > 0u)
                    {
                        segBuff[index] = tmpSegId;
                        index=index+1;
                    }
                }

            }
            else if (SWITCH_STATUS_CONTRA == switchStatus)
            {
                if(bnfSegStru->segStartJointSideSegId != UINT16_NULL)
                {
                    segBuff[index] = bnfSegStru->segStartJointSideSegId;
                    index=index+1;
                    tmpSegId = AccordSwitchAndPointTypeGetSegId(bnfSegStru->segStartJointSideSegId,START_POINT);
                    if (tmpSegId > 0u)
                    {
                        segBuff[index] = tmpSegId;
                        index=index+1;
                    }
                }

            }
            else
            {
                /*Do nothing currently !*/
            }
        }

        if (index >= 2u)
        {
            *findNum = index;
        }
        else
        {
            *findNum = 1u;
        }
    }
    return index;
}



/*
* ���������� ��ѯ������֮����߼�����ID�Ͷ�Ӧ��SEG��Ϣ����(����״̬��֪)
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      segEndID        UINT16_S    �յ�SegID
*                      dir            UINT8_S     ���з���
*                      includePoint     UINT8_S     1�����˵�  0�������˵�
*             �������:pSegId        UINT16_S*    SEGID����
*                      segIdNum        UINT8_S*      SEGID����    
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    
UINT8_S GetDirSegArrayAndLogicSec(UINT16_S segStartID,UINT32_S segStartOffset,UINT16_S segEndID,UINT32_S segEndOffset,UINT8_S dir,UINT8_S* logicNum,UINT16_S* logicId,UINT8_S* relateLogicNumBuff,BnfRelateLogicSecInfoStruct relateLogicInfo[][2])
{
    UINT8_S retVal = 0u;/*��������ֵ*/
    UINT8_S tmpRetVal = 0u;/*��ʱʹ�ú�������ֵ*/
    UINT16_S nextLogicId = 0u;/*��ȡ��һ���߼�����ID*/
    UINT16_S tmpLogic = 0u;
    UINT8_S index = 0u;/*�����±�ƫ��*/
    UINT16_S startLogicId = 0u;/*����߼�����Id*/
    UINT16_S endLogicId = 0u;/*�յ��߼�����Id*/

    UINT8_S tmpStartRelateLogicNum = 0u;
    BnfRelateLogicSecInfoStruct startRelateLogicId[LOGICSECTION_OF_SWITCH_MAX_NUM] = {{0u}};
    UINT8_S tmpEndRelateLogicNum = 0u;
    BnfRelateLogicSecInfoStruct endRelateLogicId[LOGICSECTION_OF_SWITCH_MAX_NUM] = {{0u}};


    /*��ȡ�����յ��Ӧ���߼�����ID*/
    GetPointOfLogSecInfo(segStartID,segStartOffset,&startLogicId,&tmpStartRelateLogicNum,&startRelateLogicId);

    GetPointOfLogSecInfo(segEndID,segEndOffset,&endLogicId,&tmpEndRelateLogicNum,&endRelateLogicId);

    if ((startLogicId != UINT16_NULL)&&(endLogicId != UINT16_NULL)&&(logicId != NULL)&&(relateLogicNumBuff != NULL)&&(relateLogicInfo != NULL)&&(NULL != logicNum))
    {
        if (startLogicId == endLogicId)
        {
            /*��ѯ�˷�Χ�ڵ��߼�����ID*/
            relateLogicNumBuff[index] = tmpStartRelateLogicNum;
            MemoryCpy(relateLogicInfo[index],sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM,startRelateLogicId,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM);
            logicId[index] = startLogicId;
            index=index+1;

            retVal = 1u;
        }
        else
        {
            relateLogicNumBuff[index] = tmpStartRelateLogicNum;
            MemoryCpy(relateLogicInfo[index],sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM,startRelateLogicId,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM);
            logicId[index] = startLogicId;
            index=index+1;
            tmpLogic = startLogicId;
            for(;index < TWO_POINT_LOGICSEC_NUM_MAX;)
            {
                tmpRetVal = GetNextLogicId(tmpLogic,dir,&nextLogicId,&relateLogicNumBuff[index],&relateLogicInfo[index]);

                if (0u == tmpRetVal)
                {
                    break;
                }

                if (nextLogicId == endLogicId)
                {
                    relateLogicNumBuff[index] = tmpEndRelateLogicNum;
                    MemoryCpy(relateLogicInfo[index],sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM,endRelateLogicId,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM);
                    logicId[index] = nextLogicId;
                    index = index + 1u;
                    retVal = 1u;
                    break;
                }

                logicId[index] = nextLogicId;
                index =index + 1u;
                tmpLogic = nextLogicId;
            }
        }

        if (1u == retVal)
        {
            *logicNum = index;
        }
    }

    return retVal;
}

/*
* ���������� ��ѯ��SEG�󷽵��߼�����
*            (1)����һ���߼�����ֱ�ӷ���
*            (2)���ж���������߼�����ƫ��������
*            (3)����SEG�����������߼������У��������������߼�����ID
* ����˵���� const UINT16_S startSegId,const UINT32_S startOffset,const UINT32_S endOffset
             UINT16_S logicSectionIdBuf[];�߼�����ID����
* ����ֵ  :  0: ʧ��
*             1: �ɹ�
*/ 
static void GetPointOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startOffSet,UINT16_S* logicId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct relateLogicInfo[][2])
{
    BnfLogicSectionStruct* tmpLogicSecStru = NULL;/*�߼����νṹ����Ϣָ��*/
    UINT16_S lineLogicNum = 0u;/*�߼���������*/
    UINT16_S tmpSegIdBuff[3] = {0};
    UINT8_S tmpSegIdNum = 0u;
    UINT8_S needFindNum = 0u;/*��Ҫ���ҵ��ĸ���*/
    UINT8_S isfindNum = 0u;/*���ҵ��ĸ���*/
    UINT16_S i = 0u;/*ѭ��ʹ��*/
    UINT8_S j = 0u;/*ѭ��ʹ��*/
    UINT8_S k = 0u;/*ѭ��ʹ��*/


    tmpSegIdNum = GetSegBuffAccordSedIdAndSwitch(startSegId,tmpSegIdBuff,&needFindNum);

    tmpLogicSecStru = GetLogicSectionDataInfo(&lineLogicNum);
    if ((NULL != logicId) && (NULL != tmpLogicSecStru) && (tmpSegIdNum > 0u))
    {
        *logicId = UINT16_NULL;
        for(i = 0u;i < lineLogicNum;i++)
        {

            if (1u == needFindNum)
            {
                /*startSegIdǰ��û�е���*/
                if(1u == tmpLogicSecStru[i].includeSegIdNum)
                {
                    if ((tmpLogicSecStru[i].startSegId == startSegId)&&(tmpLogicSecStru[i].startSegOffset <= startOffSet)&&(tmpLogicSecStru[i].endSegOffset >= startOffSet))
                    {
                        *logicId = tmpLogicSecStru[i].indexId;
                        break;
                    }
                }
                else
                {

                    for (j = 0u;j < tmpLogicSecStru[i].includeSegIdNum;j++)
                    {
                        if (tmpLogicSecStru[i].segIdBuff[j] == startSegId)
                        {
                            *logicId = tmpLogicSecStru[i].indexId;
                            break;
                        }
                    }
    
                    if (*logicId != UINT16_NULL)
                    {
                        break;
                    }
                
                }

            
            }
            else
            {
                /*startSegIdǰ������е���*/
                if(tmpLogicSecStru[i].includeSegIdNum > 1u)
                {
                    for (j = 0u; j < tmpSegIdNum; j++)
                    {
                        for (k = 0u;k < tmpLogicSecStru[i].includeSegIdNum; k++)
                        {
                            if (tmpLogicSecStru[i].segIdBuff[k] == tmpSegIdBuff[j])
                            {
                                isfindNum += 1u;
                                break;
                            }
                        }
                        
                        if (needFindNum == isfindNum)
                        {
                            *logicId = tmpLogicSecStru[i].indexId;
                            break;
                        }
                    }
    
                    if (*logicId != UINT16_NULL)
                    {
                        break;
                    }                
                }
            
            }
        }
        if ((*logicId != UINT16_NULL) && (NULL != relateLogicInfo))
        {
            *relateLogicNum = tmpLogicSecStru[i].relateLogicNum;
            MemoryCpy(relateLogicInfo,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM,tmpLogicSecStru[i].relateLogicInfo,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM);
        }    
    }

}

/*
* ���������� ��ѯָ�����з������һ��SegID(����״̬��֪)
* ����˵���� �������:Seg_ID  UINT16_S    ��ǰ��SegID
*                         Dir  UINT8_S     ���з���
*             �������:nextSegId  UINT16_S*   ��һ��SEGID
* ����ֵ  �� 0:ʧ��1���ɹ�
*/
static UINT8_S GetNextLogicId(UINT16_S logicId,UINT8_S dir,UINT16_S* nextLogicId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct relateLogicInfo[][2])
{
    UINT8_S retVal = 0u;/*��������*/
    BnfLogicSectionStruct* logicInfoStru = NULL;
    BnfLogicSectionStruct* curLogicInfoStru = NULL;
    UINT8_S switchStatus = 0u;/*����״̬*/
    UINT8_S i = 0u;/*ѭ��ʹ��*/
	UINT8_S inParaErrFlag = 1u;

	if((NULL == nextLogicId) || (NULL == relateLogicNum) || (NULL == relateLogicInfo))
    {
        inParaErrFlag = 0u;
    }
	else
    {
        *nextLogicId = UINT16_NULL;
    }


    /*��ȡ��SE�߼�G��Ӧ���߼�������Ϣ*/
    logicInfoStru = GetIndexIdLogicSectionDataStru(logicId);
    
    if((1u == inParaErrFlag) && (logicInfoStru != NULL) && (dir == LINESEG_SAME_DIR))
    {
        if ((logicInfoStru->tmnlJointMainLogicId != UINT16_NULL)&&(logicInfoStru->tmnlJointSideLogicId == UINT16_NULL))
        {
            *nextLogicId = logicInfoStru->tmnlJointMainLogicId;
        }
        else if ((logicInfoStru->tmnlJointMainLogicId == UINT16_NULL)&&(logicInfoStru->tmnlJointSideLogicId != UINT16_NULL))
        {
            *nextLogicId = logicInfoStru->tmnlJointSideLogicId;
        }
        else if((logicInfoStru->tmnlJointMainLogicId != UINT16_NULL)&&(logicInfoStru->tmnlJointSideLogicId != UINT16_NULL))
        {
            *nextLogicId = logicInfoStru->tmnlJointMainLogicId;
            curLogicInfoStru = GetIndexIdLogicSectionDataStru(logicInfoStru->tmnlJointSideLogicId);

            if (curLogicInfoStru != NULL)
            {
                for (i = 0u; i < curLogicInfoStru->switchIdNum; i++)
                {
                    switchStatus = GetSwitchStatus(curLogicInfoStru->switchIdStru[i].switchId);
                    if ((curLogicInfoStru->switchIdStru[i].switchStatus == switchStatus)&&(curLogicInfoStru->switchIdStru[i].switchStatus != UINT8_NULL))
                    {
                        *nextLogicId = logicInfoStru->tmnlJointSideLogicId;
                        break;
                    }
                }
            }
        }
        else
        {
            /*Do nothing currently !*/
        }
    }
    else if((1u == inParaErrFlag) && (logicInfoStru != NULL)&&(dir == LINESEG_CONVER_DIR))
    {
        if ((logicInfoStru->startJointMainLogicId != UINT16_NULL)&&(logicInfoStru->startJointSideLogicId == UINT16_NULL))
        {            
            *nextLogicId = logicInfoStru->startJointMainLogicId;
        }
        else if((logicInfoStru->startJointMainLogicId == UINT16_NULL)&&(logicInfoStru->startJointSideLogicId != UINT16_NULL))
        {
            *nextLogicId = logicInfoStru->startJointSideLogicId;
        }
        else if((logicInfoStru->startJointMainLogicId != UINT16_NULL)&&(logicInfoStru->startJointSideLogicId != UINT16_NULL))
        {
            *nextLogicId = logicInfoStru->startJointMainLogicId;
            curLogicInfoStru = GetIndexIdLogicSectionDataStru(logicInfoStru->startJointSideLogicId);

            if (curLogicInfoStru != NULL)
            {                            
                for (i = 0u; i < curLogicInfoStru->switchIdNum; i++)
                {                                
                    switchStatus = GetSwitchStatus(curLogicInfoStru->switchIdStru[i].switchId);
                 
                    if( (curLogicInfoStru->switchIdStru[i].switchStatus == switchStatus)&&(curLogicInfoStru->switchIdStru[i].switchStatus != UINT8_NULL))
                    {                    
                        *nextLogicId = logicInfoStru->startJointSideLogicId;
                        break;
                    }
                }
            }
        }
        else
        {
            /*Do nothing currently !*/
        }
    }
    else
    {
        /*Do nothing currently !*/
    }



    if ((1u == inParaErrFlag) && (*nextLogicId != UINT16_NULL))
    {
        curLogicInfoStru = GetIndexIdLogicSectionDataStru(*nextLogicId);
        *relateLogicNum = curLogicInfoStru->relateLogicNum;
        MemoryCpy(relateLogicInfo,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM,curLogicInfoStru->relateLogicInfo,sizeof(BnfRelateLogicSecInfoStruct)*LOGICSECTION_OF_SWITCH_MAX_NUM);
        retVal = 1u;
    }

    return retVal;
}


/************************************************************************
* �������ܣ��˺����Ĺ����ǲ�ѯ��ǰGarde������Grade
* ��ڲ�����const UINT16_S curGradeID    ��ǰ�¶ȱ��
            const UINT8_S dir            �������з���        
* ���ڲ�����    ��
* ����ֵ��    UINT16_S findGradeID    ��ѯʧ��: 0xffff; ��ѯ�ɹ�: �������ڵ��¶�ID                                                              
************************************************************************/
UINT16_S FindAdjacentGradeID(const UINT16_S curGradeID, const UCHAR_S dir)
{
    UINT16_S findGradeID = 0u;/*��������ֵ*/
    BnfGradeStruct *pstGrade = NULL;/*ָ���¶���Ϣ�Ľṹ��ָ��*/
    UINT8_S isFindErr = 1u;
    UINT8_S switchStatus = 0u;/*����״̬*/
    
    /*�ж��������Ч��*/
    pstGrade = GetIndexIdGradeDataStru(curGradeID);
    if (pstGrade == NULL)
    {
        isFindErr = 0u;
    }
    else
    {
        /*�ж�������ݷ������Ч��*/
        if ((LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir))
        {
            isFindErr = 0u;
        }
    }

    
    /*���������з�����Seg���߼�������ͬʱ����ǰ�¶ȵ�ĩ�������¶Ƚ��в�ѯ*/
    if ((LINESEG_SAME_DIR == dir)&&(1u == isFindErr))
    {
        if ((0xffffu == pstGrade->tmnlJointSideGradeId)&&(0xffffu == pstGrade->tmnlJointMainGradeId))
        {
            /*��ǰ�¶��Ѿ�û�������¶ȣ���������0*/
            isFindErr = 0u;
        }
        else
        {
            /*�ڵ�ǰ�¶ȵ�ĩ�����ڲ����¶�Ϊ��ʱ����ĩ�����������¶ȼ�Ϊ����*/
            if (0xffffu == pstGrade->tmnlJointSideGradeId)
            {
                /*��ѯ�ɹ������������Ϣ*/
                findGradeID = pstGrade->tmnlJointMainGradeId;
            }
            else
            {
                /*�ڵ�ǰ�¶ȵ�ĩ�����ڲ����¶Ȳ�Ϊ��ʱ��������ʵʱ�ĵ���״̬���ж������¶�*/
                switchStatus = GetSwitchStatus(pstGrade->tmnlRelatePointId);
                /*����ʧȥ��ʾ,�����쳣����ѯʧ�ܣ�����Ĭ��ֵ���˳�*/
                if (SWITCH_STATUS_LOSE == switchStatus)
                {
                    isFindErr = 0u;
                }
                else
                {
                    /*�����ڶ�λ,��ĩ�����������¶ȼ�Ϊ����*/
                    if (SWITCH_STATUS_SAME == switchStatus)
                    {
                        findGradeID = pstGrade->tmnlJointMainGradeId;            
                    }
                    else
                    {
                        /*�����ڷ�λ,��ĩ�����ڲ����¶ȼ�Ϊ����*/
                        findGradeID = pstGrade->tmnlJointSideGradeId;
                    }                            
                }
            }    
        }            
    }
    else if (1u == isFindErr)
    {
        /*���������з�����Seg���߼������෴ʱ����ǰ�¶ȵ�ʼ�˶������¶Ƚ��в�ѯ*/
        /*���ù�����ֱ���ҵ���ǰ�¶ȵ���Ϣ*/
        if ((0xffffu == pstGrade->orgnJointSideGradeId)&&(0xffffu == pstGrade->orgnJointMainGradeId))
        {
            /*��ǰ�¶��Ѿ�û�������¶ȣ���������0*/
            isFindErr = 0u;
        }
        else
        {
            /*�ڵ�ǰ�¶ȵ�ʼ�����ڲ����¶�Ϊ��ʱ����ʼ�����������¶ȼ�Ϊ����*/
            if (0xffffu == pstGrade->orgnJointSideGradeId)
            {
                /*��ѯ�ɹ��������¶�ID*/
                findGradeID = pstGrade->orgnJointMainGradeId;
            }
            else
            {
                /*�ڵ�ǰ�¶ȵ�ʼ�����ڲ����¶Ȳ�Ϊ��ʱ��������ʵʱ�ĵ���״̬���ж������¶�*/
                switchStatus = GetSwitchStatus(pstGrade->orgnRelatePointId);

                /*����ʧȥ��ʾ,�����쳣����ѯʧ�ܣ�����Ĭ��ֵ���˳�*/
                if (SWITCH_STATUS_LOSE == switchStatus)
                {
                    isFindErr = 0u;
                }
                else
                {
                    /*�����ڶ�λ,��ʼ�����������¶ȼ�Ϊ����*/
                    if(SWITCH_STATUS_SAME == switchStatus)
                    {
                        findGradeID = pstGrade->orgnJointMainGradeId;            
                    }
                    else
                    {
                        /*�����ڷ�λ,��ʼ�����ڲ����¶ȼ�Ϊ����*/
                        findGradeID = pstGrade->orgnJointSideGradeId;
                    }                            
                }
            }
        }
        
    }
    else
    {
        /*Do nothing currently !*/
    }

    if (0u == isFindErr)
    {
        findGradeID = UINT16_NULL;
    }

    return findGradeID;
}

/*
* ���������� ����SEG��IDͬʱ�Դ�SEGΪ�������յ�,���Կ��ǵ���״̬,�ҵ����ڵ�Seg��ID
* ����˵����  UINT16_S segId,SEG��ID
*             UINT8_S pointType �����յ�
* ����ֵ  �� 0: ��ȡʧ��
*            >0: SEGID
*/

static UINT16_S AccordSwitchAndPointTypeGetSegId(UINT16_S segId,UINT8_S pointType)
{
    BnfSegStruct* bnfSegStru = NULL;
    UINT8_S switchStatus = 0u;/*����״̬*/
    UINT16_S tmpSegOutId = 0u;

    bnfSegStru = GetIndexIdSegDataStru(segId);
    if (NULL != bnfSegStru)
    {
        if ((END_POINT == pointType)&&(bnfSegStru->endPointType == POINTTYPE_SWITCH))
        {
            /*��ȡ����״̬*/            
            switchStatus = GetSwitchStatus(bnfSegStru->endPointId);
            if (SWITCH_STATUS_SAME == switchStatus)
            {    
                if(bnfSegStru->segTmnlJointMainSegId != UINT16_NULL)
                {
                    tmpSegOutId = bnfSegStru->segTmnlJointMainSegId;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
            else if (SWITCH_STATUS_CONTRA == switchStatus)
            {
                if(bnfSegStru->segTmnlJointSideSegId != UINT16_NULL )
                {
                    tmpSegOutId = bnfSegStru->segTmnlJointSideSegId;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
            else
            {
                /*Do nothing currently !*/
            }
        }
        else if ((START_POINT == pointType)&&(bnfSegStru->startPointType == POINTTYPE_SWITCH))
        {
            /*��ȡ����״̬*/
            switchStatus = GetSwitchStatus(bnfSegStru->startPointId);
            if (SWITCH_STATUS_SAME == switchStatus)
            {
                if(bnfSegStru->segStartJointMainSegId != UINT16_NULL)
                {
                    tmpSegOutId = bnfSegStru->segStartJointMainSegId;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
            else if (SWITCH_STATUS_CONTRA == switchStatus)
            {
                if(bnfSegStru->segStartJointSideSegId != UINT16_NULL)
                {
                    tmpSegOutId = bnfSegStru->segStartJointSideSegId;
                }
                else
                {
                    /*Do nothing currently !*/
                }
            }
            else
            {
                /*Do nothing currently !*/
            }
        }
        else
        {

        }
    }

    return tmpSegOutId;
}
