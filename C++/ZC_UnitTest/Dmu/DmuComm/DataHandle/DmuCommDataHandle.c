/********************************************************
* 
* 文 件 名： DmuCommDataHandle.c   
* 作    者： 董欣 
* 创建时间： 2016-09-03
* 功能描述： 公共查询函数 
* 功能可分解如下： 
*          1）查询指定运行方向的下一个Seg信息； 
*          2）查询指定运行方向的下一个SegID(道岔状态已知)； 
*          3）查询两个Seg间的序列(道岔状态未知)； 
*          4）获取SEGID包含的计轴区段ID	； 
*          5）查询两个Seg间的序列(道岔状态已知)； 
*          6）查询两个Seg间的序列(道岔状态已知)； 
*          7）查询两个Seg间的序列(道岔状态未知)； 
*          8）查询两个Seg间的距离(距离为正值； 
*          9）查询两个Seg间的距离； 
*          10）计算同一SEG相对应方向的长度； 
*          11）更新道岔的实时状态； 
*          12）获取道岔状态； 
*          13）查询指定运行方向的下一个点(增加点表以后才可以使用)； 
*          14）计算计轴区段增加项； 
*          15）计算逻辑区段增加项； 
*          16）计算道岔增加项； 
*          17）计算信号机增加项； 
*          18）计算进路增加项； 
*          19）计算无人折返增加项； 
*          20）计算屏蔽门增加项； 
*          21）计算保护区段增加项； 
*          22）计算坡度表增加项； 
*          23）计算停车区域增加项； 
*          24）计算紧急停车按钮增加项； 
*          25）计算退出CBTC属性增加项； 
*          26）计算切换线路中的增加项； 
*          27）计算通用信息增加项； 
*          28）获取COM查询函数初始化失败原因； 
*          29）本函数功能是判断当前的道岔状态是否满足计轴区段关联的道岔状态； 
*          30）本函数功能是查询当前计轴区段的相邻计轴区段。相邻计轴区段分为起点相邻计轴区段和终点相邻计轴区段； 
*          31）查询当前点向前方向一定距离的另外一个点的位置； 
*          32）获取SEGID包含的计轴区段ID； 
*          33）根据当前位置和位移,得到新位置.(已知道岔的状态)； 
*          34）获取两点的距离向量,从起点到终点方向； 
*          35）根据SEG以及SEG的前方和后方是否有道岔,若有道岔，增加道岔前方或后方的SEGID，若无,之间返回此SEGID 
*          36）查询两个点之间的逻辑区段ID和对应的SEG信息序列(道岔状态已知)； 
*          37）查询此SEG后方的逻辑区段； 
*          38）查询指定运行方向的下一个SegID(道岔状态已知)； 
*          39）此函数的功能是查询当前Garde的相邻Grade； 
*          40）根据SEG的ID同时以此SEG为起点或是终点,加以考虑道岔状态,找到相邻的Seg的ID。 
* 备    注： 无 
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


/**********************************全局变量START**********************************************/
static SwitchStatusInfoStruct SwitchStatusInfoStru[SNGZC_INCLUDE_SWITCH_NUM] = {{0u}};/*实际道岔状态*/
static UINT16_S SwitchNum = 0u;/*道岔个数*/
static UINT32_S ComBnfInitErrReason = 0u;
/**********************************全局变量END************************************************/

/**********************************内部函数START************************************************/    
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
/**********************************内部函数END************************************************/


/*
* 功能描述： 查询指定运行方向的下一个Seg信息
* 参数说明： 输入参数:Seg_ID  UINT16_S    当前的SegID
*                         Dir  UINT8_S     运行方向
* 返回值  ： NULL :失败 !NULL：成功
*/
static BnfSegStruct* GetNextSegInfo(UINT16_S segId,UINT8_S dir)
{
    BnfSegStruct* retVal = NULL;/*函数返回*/
    UINT8_S tmpRetVal = 0u;/*局部函数返回值*/
    UINT16_S nextSegId = 0u;/*下一个SegID*/

    tmpRetVal = GetNextSegId(segId,dir,&nextSegId);
    
    if (1u == tmpRetVal)
    {
        retVal = GetIndexIdSegDataStru(nextSegId);
    }

    return retVal;
}

/*
* 功能描述： 查询指定运行方向的下一个SegID(道岔状态已知)
* 参数说明： 输入参数:Seg_ID  UINT16_S    当前的SegID
*                         Dir  UINT8_S     运行方向
*             输出参数:nextSegId  UINT16_S*   下一个SEGID
* 返回值  ： 0:失败1：成功
*/
UINT8_S GetNextSegId(UINT16_S segId,UINT8_S dir,UINT16_S* nextSegId)
{
    UINT8_S retVal = 0u;/*函数返回*/
    BnfSegStruct* segInfoStru = NULL;
    UINT8_S switchStatus = 0u;/*道岔状态*/

    if(NULL != nextSegId)
    {
        *nextSegId = 0u;

        /*获取此SEG对应的SEG信息*/
        segInfoStru = GetIndexIdSegDataStru(segId);
        /*获取当前SEG对应的点ID*/
        
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
* 功能描述： 查询两个Seg间的序列(道岔状态未知)
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      segEndID        UINT16_S    终点SegID
*                      dir            UINT8_S     运行方向
*             输出参数:pSegId        UINT16_S*    SEGID数组
*                      segIdNum        UINT8_S*      SEGID个数    
* 返回值  ： 0:失败1：成功
*/    

UINT8_S GetDirNoSwitchStutasSegArray(UINT16_S startSegId,UINT16_S endSegId,UINT8_S dir,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S segIdBuff[])
{
    UINT8_S chReturnValue = 0u;/*函数返回值*/
    UINT16_S stackSegId[STACK_PUSH_SEG_MAX_NUM] = {0u};    /*简易栈，用于记录搜索过程中未知道岔处侧线SegID*/
    StackPushSegInfoStruct tmpSegInfoStru[STACK_PUSH_SEG_MAX_NUM] ={{{NULL}}};/*存放查找到的SEGID*/
    UINT16_S stackSegIdTop = 0u;          /*简易栈，栈顶指针*/
    UINT16_S k = 0u;                        /*循环用变量*/
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
        /*查询得到当前SEG的对应相关信息*/
        pCursegStru = GetIndexIdSegDataStru(startSegId);
        tempSegStru = GetSegDataInfo(&lineSegNum);
        if ((NULL == pCursegStru)||(NULL == tempSegStru))
        {
            isErrorFlag = 0u;
        }
        /*清空栈*/
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
            /*添加当前起始seg*/
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
        /*正向查找*/
        for (k=0u;(k<lineSegNum)&&(NULL != pCursegStru);k++)
        {
            /*此处循环不是为了遍历Seg，而是为了循环最大计数，循环次数不能超过lineSegNum*/
            if ((pCursegStru->segTmnlJointMainSegId == UINT16_NULL)||(BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG == includeSegIdNum))
            {
                /*Seg终点是线路终点,或者已经查询到车站ID,弹出栈顶侧线做为下一个Seg*/
                if (stackSegIdTop == 0u)
                {
                    /*如果栈已空，说明已经全部搜索完毕，返回不在前方*/
                    chReturnValue = 0u;
                    break;
                }
                else
                {
                    /*栈非空，弹栈*/
                    stackSegIdTop--;
                    MemorySet(segIdBuff,sizeof(UINT16_S)*BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG,0u,sizeof(UINT16_S)*BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG);
                    includeSegIdNum = tmpSegInfoStru[stackSegIdTop].includeSegIdNum;

                    MemoryCpy(segIdBuff,sizeof(UINT16_S)*includeSegIdNum,tmpSegInfoStru[stackSegIdTop].SegIdBuff,sizeof(UINT16_S)*includeSegIdNum);
                    pCursegStru = GetIndexIdSegDataStru(stackSegId[stackSegIdTop]);
                }

            }
            else if(pCursegStru->endPointType == POINTTYPE_AXLE)
            {
                /*Seg终点是记轴点，将相邻正线Seg做为下一个Seg*/
                pCursegStru = GetIndexIdSegDataStru(pCursegStru->segTmnlJointMainSegId);
            }
            else if (pCursegStru->endPointType == POINTTYPE_SWITCH)
            {
                /*判断当前seg是否为道岔的汇合Seg*/
                if(pCursegStru->segTmnlJointSideSegId == UINT16_NULL)
                {
                    /*当前Seg非汇合Seg，相邻正线Seg为下一个Seg*/
                    pCursegStru = GetIndexIdSegDataStru(pCursegStru->segTmnlJointMainSegId);
                }
                else
                {
                    if (stackSegIdTop == STACK_PUSH_SEG_MAX_NUM)
                    {
                        /*如果栈已满，不应当发生*/
                        chReturnValue = 0u;
                        break;
                    }
                    else
                    {
                        /*侧线ID入栈*/
                        stackSegId[stackSegIdTop] = pCursegStru->segTmnlJointSideSegId;
                        MemoryCpy(tmpSegInfoStru[stackSegIdTop].SegIdBuff,sizeof(UINT16_S)*includeSegIdNum,segIdBuff,sizeof(UINT16_S)*includeSegIdNum);
                        tmpSegInfoStru[stackSegIdTop].includeSegIdNum = includeSegIdNum;
                        stackSegIdTop++;
                        /*将已经查找到的SEGID写入此SEGID*/
                    }

                    /*正线为下一Seg*/
                    pCursegStru = GetIndexIdSegDataStru(pCursegStru->segTmnlJointMainSegId);
                }
            }
            else
            {
                /*Seg端点类型不合法*/
                chReturnValue=0u;
                break;
            }

            /* 查找此SEG是否为终点SEG,若是，则查找成功*/

            if (pCursegStru != NULL)
            {
                if (pCursegStru->segId == endSegId)
                {
                    if(1u == includePoint)
                    {
                        /*添加当前起始seg*/
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
        /*ConverDir查找当前Seg*/
        for (k=0;(k<lineSegNum)&&(NULL != pCursegStru);k++)
        {
            /*此处循环不是为了遍历Seg，而是为了循环最大计数，循环次数不能超过lineSegNum*/
            /*通过当前Seg获取下一个Seg。根据下一个Seg类型不同进行不同的处理*/
            if ((pCursegStru->segStartJointMainSegId==UINT16_NULL)||(BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG == includeSegIdNum))
            {
                /*Seg终点是线路终点,或者已经查询到车站ID,弹出栈顶侧线做为下一个Seg*/
                if (stackSegIdTop==0u)
                {
                    /*如果栈已空，说明已经全部搜索完毕，返回不在前方*/
                    chReturnValue = 0u;
                    break;
                }
                else
                {
                    /*栈非空，弹栈*/
                    stackSegIdTop--;
                    MemorySet(segIdBuff,sizeof(UINT16_S)*BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG,0u,sizeof(UINT16_S)*BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG);
                    includeSegIdNum = tmpSegInfoStru[stackSegIdTop].includeSegIdNum;

                    MemoryCpy(segIdBuff,sizeof(UINT16_S)*includeSegIdNum,tmpSegInfoStru[stackSegIdTop].SegIdBuff,sizeof(UINT16_S)*includeSegIdNum);
                    pCursegStru = GetIndexIdSegDataStru(stackSegId[stackSegIdTop]);
                }

            }
            else if(pCursegStru->startPointType==POINTTYPE_AXLE)
            {
                /*Seg起点是记轴点，将相邻正线Seg做为下一个Seg*/
                pCursegStru = GetIndexIdSegDataStru(pCursegStru->segStartJointMainSegId);
            }
            else if(pCursegStru->startPointType==POINTTYPE_SWITCH)
            {
                /*道岔点，分情况讨论*/
                /*判断当前seg是否为道岔的汇合Seg*/
                if(pCursegStru->segStartJointSideSegId==UINT16_NULL)
                {
                    /*非汇合Seg，相邻正线Seg为下一个Seg*/
                    pCursegStru = GetIndexIdSegDataStru(pCursegStru->segStartJointMainSegId);
                }
                else
                {
                    if (stackSegIdTop==STACK_PUSH_SEG_MAX_NUM)
                    {
                        /*如果栈已满，不应当发生*/
                        chReturnValue = 0u;
                        break;
                    }
                    else
                    {
                        /*侧线ID入栈*/
                        stackSegId[stackSegIdTop]=pCursegStru->segStartJointSideSegId;
                        MemoryCpy(tmpSegInfoStru[stackSegIdTop].SegIdBuff,sizeof(UINT16_S)*includeSegIdNum,segIdBuff,sizeof(UINT16_S)*includeSegIdNum);

                        tmpSegInfoStru[stackSegIdTop].includeSegIdNum = includeSegIdNum;
                        stackSegIdTop++;
                    }
                    /*正线为下一Seg,侧线入栈*/
                    pCursegStru = GetIndexIdSegDataStru(pCursegStru->segStartJointMainSegId);
                }

            }
            else
            {
                /*Seg端点类型不合法*/
                chReturnValue=0u;
                break;
            }
            if (pCursegStru != NULL)
            {
                /* 查找此SEG是否为终点SEG,若是，则查找成功*/
                if (pCursegStru->segId == endSegId)
                {
                    if(1u == includePoint)
                    {
                        /*添加当前起始seg*/
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

/*查询此点ID和类型获取此点的状态*/
static UINT8_S SearchPointTypeStatus(const UINT16_S tmnlJointMainSegId,const UINT16_S tmnlJointSideSegId,UINT16_S pointId,UINT16_S pointType)
{
    UINT8_S switchStatus = 0u;/*道岔状态*/

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
* 功能描述： 查询两个Seg间的序列(道岔状态已知)
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      segEndID        UINT16_S    终点SegID
*                      includePoint  UINT8_S      1包含端点  0不包含端点
*             输出参数:pSegId        UINT8_S*    SEGID数组
*                      segIdNum        UINT8_S*      SEGID个数    
* 返回值  ： 0:失败1：成功
*/    

static UINT8_S GetNoDirSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId)
{
    UINT8_S retVal = 0u;/*函数返回值*/

    /*正向查找*/
    retVal = GetDirSegArray(segStartID,segEndID,LINESEG_SAME_DIR,includePoint,segIdNum,pSegId);

    if (0u == retVal)
    {
        /*反向查找*/
        retVal = GetDirSegArray(segStartID,segEndID,LINESEG_CONVER_DIR,includePoint,segIdNum,pSegId);
    }

    return retVal;
}

/*
* 功能描述： 查询两个Seg间的序列(道岔状态已知)
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      segEndID        UINT16_S    终点SegID
*                      dir            UINT8_S     运行方向
*                      includePoint     UINT8_S     1包含端点  0不包含端点
*             输出参数:pSegId        UINT16_S*    SEGID数组
*                      segIdNum        UINT8_S*      SEGID个数    
* 返回值  ： 0:失败1：成功
*/    

UINT8_S GetDirSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S dir,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S nextSegId = 0u;/*获取下一个SegID*/
    UINT16_S tmpSegId = 0u;
    UINT8_S index = 0u;/*数组下标偏移*/

    if((NULL != pSegId) && (NULL != segIdNum))
    {

        if(1u == includePoint)
        {
            /*添加当前起始seg*/
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
* 功能描述： 查询两个Seg间的序列(道岔状态未知)
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      segEndID        UINT16_S    终点SegID
*             输出参数:pSegId        UINT8_S*    SEGID数组
*                      segIdNum        UINT8_S*      SEGID个数    
* 返回值  ： 0:失败1：成功
*/    

UINT8_S GetNoDirNoSwitchStutasSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId)
{
    UINT8_S retVal = 0u;/*函数返回值*/

    /*正向查找*/
    retVal = GetDirNoSwitchStutasSegArray(segStartID,segEndID,LINESEG_SAME_DIR,includePoint,segIdNum,pSegId);

    if (0u == retVal)
    {
        /*反向查找*/
        retVal = GetDirNoSwitchStutasSegArray(segStartID,segEndID,LINESEG_CONVER_DIR,includePoint,segIdNum,pSegId);
    }

    return retVal;
}

/*
* 功能描述： 查询两个Seg间的距离(距离为正值)
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      startOffSet    UINT32_S      起点偏移量
*                      segEndID        UINT16_S    终点SegID
*                      endOffSet        UINT32_S      终点偏移量
*                      dir            UINT8_S     运行方向
*             输出参数:destDistance  UINT32_S*   目标距离(距离为正值)  
* 返回值  ： 0:失败1：成功
*/    
UINT8_S GetDirBothSegPointDisPlus(UINT16_S segStartID,UINT32_S startOffSet,UINT16_S segEndID,UINT32_S endOffSet,UINT8_S dir,UINT32_S* destDistance)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT8_S i = 0u;/*循环使用*/
    UINT32_S startDis=0u;/*起点范围内的长度*/
    UINT32_S endDis=0u;/*终点范围内的长度*/
    INT32_S bothDis = 0u;/*计算的距离*/
    UINT8_S segIdNum=0u;/*seg的个数*/
    UINT32_S totalSegLength=0u;/*全部SEG的长度之和*/
    UINT16_S segIdBuff[BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG]={0};/*seg的ID数组*/

    if(NULL != destDistance)
    {
        *destDistance = 0u;

        /*接口参数防护*/
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
                /*计算起点范围内的长度*/
                if(LINESEG_SAME_DIR==dir)
                {
                    startDis=GetSegDataStrulength(segStartID)-startOffSet;
                    retVal = GetDirNoSwitchStutasSegArray(segStartID, segEndID, dir,0, &segIdNum, segIdBuff);
                    if(1u == retVal)
                    {
                        /*将查询到SEGID长度相加*/
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
                    /*查询此两点单位内的SEGID,若查询失败,将目标距离置为无效值，若成功，将查询到的SEGID长度相加*/
                    retVal = GetDirNoSwitchStutasSegArray(segStartID, segEndID, dir,0, &segIdNum, segIdBuff);
                    if(1u == retVal)
                    {
                        /*将查询到SEGID长度相加*/
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
                        /*计算终点包含的长度*/
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
* 功能描述： 查询两个Seg间的距离
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      startOffSet    UINT32_S      起点偏移量
*                      segEndID        UINT16_S    终点SegID
*                      endOffSet        UINT32_S      终点偏移量
*             输出参数:destDistance  UINT32_S*   目标距离  
* 返回值  ： 0:失败1：成功
*/    
UINT8_S GetNoDirBothSegPointDis(UINT16_S segStartID,UINT32_S startOffSet,UINT16_S segEndID,UINT32_S endOffSet,UINT32_S* destDistance)
{
    UINT8_S retVal = 0u;/*函数返回值*/

    retVal = GetDirBothSegPointDisPlus(segStartID,startOffSet,segEndID,endOffSet,LINESEG_SAME_DIR,destDistance);
    if (0u == retVal)
    {
        retVal = GetDirBothSegPointDisPlus(segStartID,startOffSet,segEndID,endOffSet,LINESEG_CONVER_DIR,destDistance);
    }

    return retVal;
}

/*
* 功能描述： 计算同一SEG相对应方向的长度
* 参数说明： 输入参数:startLoc    UINT16_S    起始SegID
*                      endLoc    UINT32_S      起点偏移量
*                      dir        UINT8_S     运行方向
*             输出参数:dis        UINT32_S*   目标距离  
* 返回值  ： 0:失败1：成功
*/    
static UINT8_S GetSameSegBothDis(UINT32_S startLoc,UINT32_S endLoc,UINT8_S dir,UINT32_S* dis)
{
    UINT8_S retVal = 0u;/*函数返回值*/

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
* 功能描述： 更新道岔的实时状态
* 参数说明： 输入参数:switchStatusBuff    UINT8_S[]     道岔状态信息
*                      buffLength        UINT16_S      数组长度
* 返回值  ： 0:失败1：成功
*/    
UINT8_S UpdateSwitchStatus(const UINT8_S switchStatusBuff[],UINT16_S buffLength)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/

    if ((switchStatusBuff != NULL)&&(buffLength > 0u)&&(buffLength % SWITCHSTATUS_INFO_SIZE == 0u))
    {
        SwitchNum = buffLength / SWITCHSTATUS_INFO_SIZE;

        if (SwitchNum <= SNGZC_INCLUDE_SWITCH_NUM)
        {
            for (i = 0u;(i < SwitchNum); i++)
            {
                /*道岔ID*/
                SwitchStatusInfoStru[i].switchId = ShortFromChar(switchStatusBuff);
                switchStatusBuff += 2;

                /*道岔状态*/
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
* 功能描述： 获取道岔状态
* 参数说明： const UINT16_S switchId 道岔ID
* 返回值  ： >=0  道岔状态   0   失败
*/    
UINT8_S GetSwitchStatus(const UINT16_S switchId)
{
    UINT8_S retVal = SWITCH_STATUS_LOSE;/*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/

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
* 功能描述： 查询指定运行方向的下一个点(增加点表以后才可以使用)
* 参数说明： 输入参数:curPointId   UINT16_S    当前的点ID
*                         Dir       UINT8_S     运行方向(正向或反向)
*             输出参数:nextPointId  UINT16_S*   下一个点ID
*                      curpointType UINT16_S*     当前点类型
* 返回值  ： 0:失败1：成功
*/
static UINT8_S GetNextPointId(UINT16_S curPointId,UINT8_S dir,UINT16_S* curpointType,UINT16_S* nextPointId)
{
    UINT8_S retVal = 0u;/*函数返回*/
    UINT8_S errorFlag = 1u;/*错误标识  1 代表正确  0 代表错误*/
    UINT8_S switchStatus = 0u;/*道岔状态*/
    UINT16_S pointType = 0u;/*点类型*/
    BnfPointStruct* pointInfoStru = NULL;

	if((NULL != curpointType) && (NULL != nextPointId))
    {
        *nextPointId = 0u;

        /*获取此POINT对应的POINT信息*/
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
*函数功能：计算计轴区段增加项
*参数说明：无
*返回值：0失败，1成功
*    UINT8_S includeLogicAxleSecNum;                                        包含的逻辑区段个数
    UINT16_S logicSecId[AXLESECTION_BELONG_LOGICSEC_MAX_NUM];                包含的逻辑区段ID
    UINT16_S orgnSegId;                                                    起点所处seg编号
    UINT16_S tmnlSegId;                                                    终点所处seg编号
    UINT32_S orgnSegOfst;                                                    起点所处seg偏移量
    UINT32_S tmnlSegOfst;                                                    终点所处seg偏移量
    UINT16_S  orgnAxleId;                                                    起点计轴器编号
    UINT16_S  tmnlAxleId;                                                    终点计轴器编号
    UINT16_S  orgnAxleSgmtId[3];                                            计轴区段起点连接计轴区段编号
    UINT16_S  tmnlAxleSgmtId[3];                                            计轴区段终点连接计轴区段编号
    UINT16_S  relatPointNum;                                                关联道岔数目
    UINT16_S  relatPointId[4];                                            关联道岔编号
    UINT16_S  relatPointStatus[4];                                         关联道岔状态
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
*/
static UINT8_S CalcAxleSectionInfo(void)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    
    UINT16_S lgcSctLineNum = 0u;/*静态限速表行数*/
    BnfLogicSectionStruct* pTempLgcSctStru = NULL;/*逻辑区段结构体指针*/
    
    UINT16_S axleSecNum = 0u;/*计轴区段表的行数*/
    BnfAxleSectionStruct* pTempAxleSecStru = NULL;/*计轴区段结构体指针*/
    
    BnfAxleSectionStruct*   pAxleSecStruOrgn[3] = {NULL,NULL,NULL};       /*计算记轴区段各项时用到*/
    BnfAxleSectionStruct*   pAxleSecStruTmnl[3] = {NULL,NULL,NULL};       /*计算记轴区段各项时用到*/
    UINT8_S AxleSgmtCountOrgn = 0u;
    UINT8_S AxleSgmtCountTmnl = 0u;



    BnfSegStruct* pTempSeg1Stru = NULL;/*SEG结构体指针*/
    BnfSegStruct* pTempSeg2Stru = NULL;/*SEG结构体指针*/

    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j = 0u;/*循环使用*/
    UINT16_S jj = 0u;/*循环使用*/

    UINT8_S isFindStartPoint = 0u;/*1 找到 0 未找到*/
    UINT8_S isFindEndPoint = 0u;/*1 找到 0 未找到*/
    UINT8_S errorFlag = 1u;/*错误标识 1 成功 0 错误*/
    UINT8_S findStartPointNum = 0u;/*找到起点的次数*/
    UINT8_S findEndPointNum = 0u;/*找到终点的次数*/
    

    UINT16_S index = 0u;/*数组下标*/


    /*获取逻辑区段的个数*/
    pTempLgcSctStru = GetLogicSectionDataInfo(&lgcSctLineNum);
    pTempAxleSecStru = GetAxleSectionDataInfo(&axleSecNum);

    if ((NULL == pTempLgcSctStru)||(NULL == pTempAxleSecStru))
    {
        errorFlag = 0u;
    }
    /*计算计轴区段的起点SEG和终点SEG、起点计轴器编号，终点计轴器编号*/
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

    /*计算dwOrgnSegOfst,dwTmnlSegOfst*/
    for(i=0;(errorFlag == 1u)&&(i<axleSecNum);i++)
    {
        /*通过索引找到seg信息(取终点SEG)*/
        pTempSeg2Stru = GetIndexIdSegDataStru(pTempAxleSecStru[i].tmnlSegId);
        if (pTempSeg2Stru != NULL)
        {
            pTempAxleSecStru[i].orgnSegOfst = 0u;
            pTempAxleSecStru[i].tmnlSegOfst = pTempSeg2Stru->length;
        }

    }

    /*计算orgnRelatPointId*/
    for(i=0;(errorFlag == 1u)&&(i<axleSecNum);i++)
    {    
        /*计数器还得设为0*/
        AxleSgmtCountOrgn = 0u;
        AxleSgmtCountTmnl = 0u;
        for(j=0u;j<axleSecNum;j++)
        {
            if(pTempAxleSecStru[i].orgnAxleId == pTempAxleSecStru[j].tmnlAxleId)
            {
                /*保存该指针，并计数*/                        
                pAxleSecStruOrgn[AxleSgmtCountOrgn] = &pTempAxleSecStru[j];
                AxleSgmtCountOrgn++;
            }

            if(pTempAxleSecStru[i].tmnlAxleId  == pTempAxleSecStru[j].orgnAxleId)
            {
                /*保存该指针，并计数*/                        
                pAxleSecStruTmnl[AxleSgmtCountTmnl] = &pTempAxleSecStru[j];
                AxleSgmtCountTmnl++;
            }

        }    
               
        /*一个记轴区段前或后相邻两个以上的记轴区段，出错！*/
        if((AxleSgmtCountOrgn > 3u ) || (AxleSgmtCountTmnl > 3u))
        {
            retVal = 0u;
            errorFlag = 0u;
            break;
        }
                
        /*计算计轴区段起点连接计轴区段编号*/
        pTempAxleSecStru[i].orgnAxleSecNum = AxleSgmtCountOrgn;                      
        for(jj = 0u;jj < AxleSgmtCountOrgn;jj++)
        {
            pTempAxleSecStru[i].orgnAxleSgmtId[jj] = pAxleSecStruOrgn[jj]->indexId;
        }

        /*计算计轴区段终点连接计轴区段编号*/
        pTempAxleSecStru[i].tmnlAxleSecNum = AxleSgmtCountTmnl;                                      
        for(jj = 0u;jj < AxleSgmtCountTmnl;jj++)
        {
            pTempAxleSecStru[i].tmnlAxleSgmtId[jj] = pAxleSecStruTmnl[jj]->indexId;
        }


    }

    /*计算relatPointNum;      关联道岔数目
          relatPointId[4];      关联道岔编号*/
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

    /*计算    UINT16_S  manageZCId;                                        所属ZC区域ID
            UINT16_S  manageCIId;                                        所属CI区域ID */
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
*函数功能：计算逻辑区段增加项
*参数说明：无
*返回值：0失败，1成功
*    UINT16_S belongAxleSecId;                        所属计轴区段ID
    UINT16_S  mainOrgnLogicSgmtId;                所属计轴区段内前向逻辑区段的编号
    UINT16_S  mainTmnlLogicSgmtId;                所属计轴区段内后向逻辑区段的编号
*/
static UINT8_S CalcLogicSgmtStru(void)
{
    UINT16_S i = 0u,j =0u,jj = 0u;/*循环变量*/
    UINT16_S indexI = 0u;/*循环使用*/
    UINT16_S k,LgcSgmtIdIndex = 0xFFFFu;              /*循环变量，及下标索引*/
    UINT8_S indexSwNum = 0u;/*写道岔时使用*/
    BnfLogicSectionStruct  * pTempLgcSecStru = NULL;     /*临时变量*/
    BnfAxleSectionStruct  *pTempAxleSecStru = NULL;        /*临时变量*/
    BnfAxleSectionStruct* pTempAxleSgmtStru = NULL;/*临时变量*/
    UINT8_S retVal = 1u;
    UINT16_S lgcSecLineNum = 0u;
    UINT16_S axleSecNum = 0u;
    UINT16_S segId = 0u;
    UINT8_S segIdNum = 0u;
    UINT16_S segIdBuff[BOTHSEG_INCLUDE_MAX_SEG+2] = {0};
    UINT16_S tmpSegIdBuff[BOTHSEG_INCLUDE_MAX_SEG+2] = {0};
    UINT8_S isFindNum = 0u;/*是否查找到的个数*/
    BnfSegStruct* tmpCurSegStru = 0;/*当前SEGiD结构体信息*/
    BnfSegStruct* tmpStartSegStru = 0;/*当前SEGiD结构体信息*/
    BnfSegStruct* tmpendSegStru = 0;/*当前SEGiD结构体信息*/

    pTempLgcSecStru = GetLogicSectionDataInfo(&lgcSecLineNum);
    pTempAxleSecStru = GetAxleSectionDataInfo(&axleSecNum);

    if ((pTempLgcSecStru == NULL)||(pTempAxleSecStru == NULL))
    {
        lgcSecLineNum =0u;
        axleSecNum = 0u;
    }
       
    /*计算逻辑区段所属的计轴区段*/
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
            /*获取逻辑区段包含的SEGID*/
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

    /*计算计轴区段包含的逻辑区段*/
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

        /*计算mainOrgnLogicSgmtId;                所属计轴区段内前向逻辑区段的编号
            minTmnlLogicSgmtId;                    所属计轴区段内后向逻辑区段的编号*/
        /*先设为无效*/
        LgcSgmtIdIndex = 0xFFFFu;
        for(k=0u;(pTempAxleSgmtStru != NULL)&&(k<pTempAxleSgmtStru->includeLogicAxleSecNum);k++)
        {                    
            if(pTempLgcSecStru[i].indexId == pTempAxleSgmtStru->logicSecId[k])
            {
                LgcSgmtIdIndex=k;
            }
        }
            
        /*逻辑区段编号在记轴区段中没找到，数据出错*/
        if(LgcSgmtIdIndex == 0xFFFFu)
        {
            retVal = 0u;
            break;
        }
        /*当记轴区段只有一个逻辑区段时，没有前向逻辑区段和后向逻辑区段*/
        else if((LgcSgmtIdIndex == 0u) && (LgcSgmtIdIndex == (pTempAxleSgmtStru->includeLogicAxleSecNum-1)))
        {
            pTempLgcSecStru[i].mainOrgnLogicSgmtId = 0xFFFFu;
            pTempLgcSecStru[i].mainTmnlLogicSgmtId = 0xFFFFu;
        }
        /*当前逻辑区段处于记轴区段的第一个逻辑区段时，没有前向逻辑区段*/
        else if (LgcSgmtIdIndex == 0u)
        {
            pTempLgcSecStru[i].mainOrgnLogicSgmtId = 0xFFFFu;
            pTempLgcSecStru[i].mainTmnlLogicSgmtId = pTempAxleSgmtStru->logicSecId[LgcSgmtIdIndex+1];
        }
        /*当前逻辑区段处于记轴区段的最后一个逻辑区段时，没有后向逻辑区段*/
        else if(LgcSgmtIdIndex ==(pTempAxleSgmtStru->includeLogicAxleSecNum-1))
        {
            pTempLgcSecStru[i].mainOrgnLogicSgmtId = pTempAxleSgmtStru->logicSecId[LgcSgmtIdIndex-1];
            pTempLgcSecStru[i].mainTmnlLogicSgmtId = 0xFFFFu;
        }
        /*当前逻辑区段处于记轴区段的中间逻辑区段时段*/
        else
        {
            pTempLgcSecStru[i].mainOrgnLogicSgmtId = pTempAxleSgmtStru->logicSecId[LgcSgmtIdIndex-1];
            pTempLgcSecStru[i].mainTmnlLogicSgmtId = pTempAxleSgmtStru->logicSecId[LgcSgmtIdIndex+1];
        }

        /*获取逻辑区段对应的SEGID*/
        segId = GetLogicSectionDataStrustartSegId(pTempLgcSecStru[i].indexId);

        /*获取此SEGID对应的ZCID*/
        pTempLgcSecStru[i].manageZCId = GetSegDataStrusegManageZCId(segId);

        /*获取此SEGID对应的CIID*/
        pTempLgcSecStru[i].manageCIId = GetSegDataStrusegManageCIId(segId);
        
        /*获取逻辑区段包含的SEGID*/
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

    /*查询此逻辑区段的起点正线逻辑区段ID、起点侧线逻辑区段ID、终点正线逻辑区段ID、终点侧线逻辑区段ID*/
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
                        /*查询此SEG若有一个逻辑区段直接返回，若有多个，返回逻辑区段偏移量最大的。若此SEG包含在两个逻辑区段中，则根据输出两个逻辑区段ID*/
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
                        /*查询此SEG若有一个逻辑区段直接返回，若有多个，返回逻辑区段偏移量最小的。若此SEG包含在两个逻辑区段中，则根据输出两个逻辑区段ID*/
                        GetSegRearSecOfLogSecInfo(tmpCurSegStru ->segTmnlJointMainSegId,GetSegDataStrulength(tmpCurSegStru ->segTmnlJointMainSegId),&pTempLgcSecStru[i].tmnlJointMainLogicId,&pTempLgcSecStru[i].tmnlJointSideLogicId);
                    }
                }

                if ((pTempLgcSecStru[i].startSegOffset == 0u)&&(pTempLgcSecStru[i].endSegOffset != tmpCurSegStru->length))
                {
                    pTempLgcSecStru[i].tmnlJointMainLogicId = pTempLgcSecStru[i].mainTmnlLogicSgmtId;
                }

                if ((pTempLgcSecStru[i].startSegOffset > 0u)&&(pTempLgcSecStru[i].endSegOffset < tmpCurSegStru->length))
                {
                    /*获取相邻的逻辑区段*/
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
                    /*查询此SEG若有一个逻辑区段直接返回，若有多个，返回逻辑区段偏移量最大的。若此SEG包含在两个逻辑区段中，则根据输出两个逻辑区段ID*/
                    GetSegFontSecOfLogSecInfo(tmpStartSegStru->segStartJointMainSegId,GetSegDataStrulength(tmpStartSegStru->segStartJointMainSegId),&pTempLgcSecStru[i].startJointMainLogicId,&pTempLgcSecStru[i].startJointSideLogicId);
                }

                if ((tmpendSegStru ->segTmnlJointMainSegId != UINT16_NULL)&&(tmpendSegStru->segTmnlJointSideSegId == UINT16_NULL))
                {
                    /*查询此SEG若有一个逻辑区段直接返回，若有多个，返回逻辑区段偏移量最小的。若此SEG包含在两个逻辑区段中，则根据输出两个逻辑区段ID*/
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
*函数功能：计算道岔增加项
*参数说明：无
*返回值：0失败，1成功
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
*/
static void CalcSwitchAddStru(void)
{
    UINT16_S i = 0u;
    BnfSwitchStruct* switchStru = NULL;
    BnfSegStruct* tmpLocSegStru = NULL;/*SEG信息结构体*/
    BnfSegStruct* tmpAntiSegStru = NULL;/*SEG信息结构体*/
    BnfSegStruct* tmpJoinSegStru = NULL;/*SEG信息结构体*/
    UINT16_S lineNum = 0u;
    UINT16_S locSegId = 0u;
    UINT16_S antiSegId = 0u;
    UINT16_S joinSegId = 0u;
    UINT8_S retVal = 0u;/*函数返回值*/

    switchStru = GetSwitchDataInfo(&lineNum);
    if (switchStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        /*获取此道岔对应的汇合SEGID*/
        retVal = GetSwitchDataStruSegIdInfo(switchStru[i].switchId,&locSegId,&antiSegId,&joinSegId);

        if (1u == retVal)
        {
            tmpLocSegStru = GetIndexIdSegDataStru(locSegId);
            tmpAntiSegStru = GetIndexIdSegDataStru(antiSegId);
            tmpJoinSegStru = GetIndexIdSegDataStru(joinSegId);
        
            if ((tmpJoinSegStru != NULL)&&(NULL != tmpLocSegStru)&&(NULL != tmpAntiSegStru))
            {
                /*获取此SEGID对应的ZCID*/
                switchStru[i].manageZCId = tmpJoinSegStru->segManageZCId;

                /*获取此SEGID对应的CIID*/
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
*函数功能：计算信号机增加项
*参数说明：无
*返回值：0失败，1成功
    UINT8_S   signSegId                                                         信号机所处SegId
    UINT8_S   signSegOffset                                                     信号机所处SegOffset
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
*/
static UINT8_S CalcSignInfoAddStru(void)
{
    UINT8_S retVal = 0u;/*函数返回值*/
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
        /*获取信号机ID对应的SEGID*/
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

            /*获取此SEGID对应的ZCID*/
            signStru[i].manageZCId = tmpSegStru->segManageZCId;

            /*获取此SEGID对应的ZCID*/
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
*函数功能：计算进路增加项
*参数说明：无
*返回值：0失败，1成功
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
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
        /*获取进路所属始端信号机ID*/
        ciId = GetRouteDataStrumanageCI(routeStru[i].routeId);

        /*获取此SEGID对应的ZCID*/
        routeStru[i].manageZCId = ArrordCiIdGetZcId(ciId);
    }
}

/*
*函数功能：计算无人折返增加项
*参数说明：无
*返回值：0失败，1成功
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
*/
static void CalcArInfoAddStru(void)
{
    UINT16_S segId = 0u;/*SEGID*/
    UINT16_S i = 0u;
    BnfArStruct* arStru = NULL;
    UINT16_S lineNum = 0u;
    UINT16_S stopPointid = 0u;/*停车点ID*/

    arStru = GetArDataInfo(&lineNum);
    if (arStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        /*获取无人折返按钮对应的停车点编号*/
        stopPointid = GetArDataStruarInStopPointId(arStru[i].arId);

        /*获取停车点ID对应的SEGID*/
        segId = GetStopPointDataStrusegId(stopPointid);

        /*获取此SEGID对应的ZCID*/
        arStru[i].manageZCId = GetSegDataStrusegManageZCId(segId);

        /*获取此SEGID对应的ZCID*/
        arStru[i].manageCIId = GetSegDataStrusegManageCIId(segId);
    }
}

/*
*函数功能：计算屏蔽门增加项
*参数说明：无
*返回值：0失败，1成功
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
*/
static void CalcPsdInfoAddStru(void)
{
    UINT16_S segId = 0u;/*SEGID*/
    UINT16_S i = 0u;
    BnfShieldDoorStruct* psdStru = NULL;
    UINT16_S lineNum = 0u;
    UINT16_S stationId = 0u;/*所属站台ID*/

    psdStru = GetShieldDoorDataInfo(&lineNum);
    if (psdStru == NULL)
    {
        lineNum =0u;
    }
    for ( i = 0u; i < lineNum; i++)
    {
        /*获取线路保护区段所属的计轴区段*/
        stationId = GetShieldDoorDataStrustationId(psdStru[i].shieldDoorId);

        /*获取站台编号对应的SEGID*/
        segId = GetPlatFormDataStrusegId(stationId);

        /*获取此SEGID对应的ZCID*/
        psdStru[i].manageZCId = GetSegDataStrusegManageZCId(segId);

        /*获取此SEGID对应的ZCID*/
        psdStru[i].manageCIId = GetSegDataStrusegManageCIId(segId);

        /*设置PSD所在的SEGID*/
        psdStru[i].segId = segId;

        psdStru[i].dir = GetPlatFormDataStrudir(stationId);
    }
}

/*
*函数功能：计算保护区段增加项
*参数说明：无
*返回值：0失败，1成功
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
*/
static void CalcProtectSecInfoAddStru(void)
{
    UINT16_S* axleSecId = NULL;/*计轴区段*/
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
        /*获取线路保护区段所属的计轴区段*/
        axleSecId = GetProtZoDataInAxleSgmtId(pProtectSecStru[i].protectZoneId);

        /*获取计轴区段编号对应的SEGID*/
        segIdBuff = GetAxleSectionDataStrusegIdBuff(axleSecId[0]);

        if (segIdBuff != NULL)
        {
            /*获取此SEGID对应的ZCID*/
            pProtectSecStru[i].manageZCId = GetSegDataStrusegManageZCId(segIdBuff[0]);

            /*获取此SEGID对应的CIID*/
            pProtectSecStru[i].manageCIId = GetSegDataStrusegManageCIId(segIdBuff[0]);
        }

    }
}


/*
*函数功能：计算坡度表增加项
*参数说明：无
*返回值：0失败，1成功
*/
static UINT8_S CalcGradeInfoAddStru(void)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/
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
*函数功能：计算停车区域增加项
*参数说明：无
*返回值：0失败，1成功
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
*/
static void CalcStopSecInfoAddStru(void)
{
    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j = 0u;/*循环使用*/
    UINT8_S index = 0u;/*数组下标*/
    BnfStopSectionStruct* stopSectionStru = NULL;/*停车区域信息结构体指针*/
    UINT16_S lineNum = 0u;
    BnfShieldDoorStruct* psdStru = NULL;/*屏蔽门信息结构体指针*/
    UINT16_S psdLineNum = 0u;/*屏蔽门表数据行数*/

    stopSectionStru = GetStopSectionDataInfo(&lineNum);
    psdStru = GetShieldDoorDataInfo(&psdLineNum);
    if ((stopSectionStru == NULL)||(NULL == psdLineNum))
    {
        lineNum =0u;
        psdLineNum = 0u;
    }


    for ( i = 0u; i < lineNum; i++)
    {
        /*获取此SEG所对应的PSDID*/
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

        /*获取此SEGID对应的ZCID*/
        stopSectionStru[i].manageZCId = GetSegDataStrusegManageZCId(stopSectionStru[i].segId);

        /*获取此SEGID对应的CIID*/
        stopSectionStru[i].manageCIId = GetSegDataStrusegManageCIId(stopSectionStru[i].segId);
    }
}

/*
*函数功能：计算紧急停车按钮增加项
*参数说明：无
*返回值：0失败，1成功
    UINT16_S  manageZCId;                                                    所属ZC区域ID
    UINT16_S  manageCIId;                                                    所属CI区域ID
*/
static void CalcEsbButtonInfoAddStru(void)
{
    UINT16_S segId = 0u;/*SEGID*/
    UINT16_S i = 0u;
    BnfEmergStopButtonStruct* esbStru = NULL;
    UINT16_S lineNum = 0u;
    UINT16_S stationId = 0u;/*所属站台ID*/

    esbStru = GetEmergStopButtonDataInfo(&lineNum);
    if (esbStru == NULL)
    {
        lineNum =0u;
    }

    for ( i = 0u; i < lineNum; i++)
    {
        /*获取紧急停车按钮所属站台编号*/
        stationId = GetLineEsbBelongStationId(esbStru[i].emergStopButtonId);

        /*获取站台编号对应的SEGID*/
        segId = GetPlatFormDataStrusegId(stationId);

        /*获取此SEGID对应的ZCID*/
        esbStru[i].manageZCId = GetSegDataStrusegManageZCId(segId);

        /*获取此SEGID对应的ZCID*/
        esbStru[i].manageCIId = GetSegDataStrusegManageCIId(segId);

        esbStru[i].segId = segId;
    }
}

/*
*函数功能：计算退出CBTC属性增加项
*参数说明：无
*返回值：0失败，1成功
*/
static void CalcExitCbtcInfoAddStru(void)
{
    UINT16_S i = 0u;/*循环使用*/
    UINT16_S j = 0u;/*循环使用*/
    UINT16_S k = 0u;/*循环使用*/
    BnfExitCbtcSectionStruct* exitCbtcStru = NULL;/*退出CBTC属性结构体指针*/
    BnfSegStruct* tmpSegStru = NULL;/*SEG信息结构体指针*/
    UINT16_S lineNum = 0u;/*行数*/
    UINT8_S isFindStartPoint = 0u;/*1 找到 0 未找到*/
    UINT8_S isFindEndPoint = 0u;/*1 找到 0 未找到*/
    UINT8_S findStartPointNum = 0u;/*找到起点的次数*/
    UINT8_S findEndPointNum = 0u;/*找到终点的次数*/

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
                        /*此Seg区段的起点相邻区段在此CBTC退出区域，终点相邻区段不在此CBTC退出区域，则说明此Seg为终点Seg*/
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
                        /*此Seg区段的起点相邻区段不在此CBTC退出区域，终点相邻区段在此CBTC退出区域，则说明此Seg为起点Seg*/
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
                /*一个退出CBTC区域有唯一一个起点Seg和一个终点Seg*/
                exitCbtcStru[i].startSegId = 0u;
                exitCbtcStru[i].endSegId = 0u;
            }
        }
    }
}

/*
* 函数功能：计算切换线路中的增加项
* 参数说明：无
* 返回值：  1 成功  0 失败
*/
static UINT8_S CalcLineSwitchInfoAddStru(void)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/
    UINT8_S switchI = 0u;/*循环使用*/
    BnfLineSwitchInfoStruct* lineSwitchStru = NULL;
    BnfSegStruct* tmpSegStru = NULL;/*SEG表信息结构体指针*/
    UINT16_S lineNum = 0u;
    UINT16_S tmpNextSegId = 0u;/*下一个SEGID*/
    UINT16_S tmpCurSegId = 0u;/*当前SEGID*/
    UINT8_S isFindError = 1u;/*是否有错误  1无错误  0 有错误*/

    lineSwitchStru = GetLineSwitchInfoDataInfo(&lineNum);
    if (lineSwitchStru == NULL)
    {
        isFindError = 0u;
    }

    for ( i = 0u;(i < lineNum)&&(1u == isFindError); i++)
    {
        lineSwitchStru[i].segNum = 0u;
        /*查询两个点之间包含的SEGID，根据切换区域的道岔状态*/
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
*函数功能：计算通用信息增加项
*参数说明：无
*返回值：0失败，1成功
*/
UINT8_S CalcCommAddInfo(void)
{
    UINT8_S retVal = 0u;/*函数返回值*/

    
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
* 功能描述： 获取COM查询函数初始化失败原因
* 参数说明： void
* 返回值  ： COM查询函数初始化失败原因  
*/
UINT32_S GetComBnfInitErrReason(void)
{
    return ComBnfInitErrReason;
}

/*
* 函数功能：本函数功能是判断当前的道岔状态是否满足计轴区段关联的道岔状态。
* 入口参数：UINT16 axleSgmtID        计轴区段编号
* 出口参数：无
* 返回值：  UINT8_S retVal 
*          查询成功:当前的道岔状态不满足计轴区段关联的道岔状态，返回0xFF;
*          查询成功:当前的道岔状态满足计轴区段关联的道岔状态，返回1      
*          查询失败：返回0
*/ 
static UINT8_S CheckPointFitAxleSgmt(UINT16_S axleSgmtID)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    BnfAxleSectionStruct *pAxleSgmtStru = NULL;/*计轴区段结构体*/
    UINT8_S chFlag = 0u;/*标志位*/
    UINT16_S i = 0u;/*循环使用*/    
    UINT16_S j = 0u;/*循环使用*/

    /*利用管理函数，得到计轴区段信息*/
    pAxleSgmtStru = GetIndexIdAxleSectionDataStru(axleSgmtID);

    if ((pAxleSgmtStru != NULL)&&(0u == pAxleSgmtStru->relatPointNum))
    {
        /*不关联道岔，直接返回查询成功*/
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
                    /*道岔状态符合*/
                    if ((SWITCH_STATUS_SAME != SwitchStatusInfoStru[i].switchStatus)&&(SWITCH_STATUS_CONTRA != SwitchStatusInfoStru[i].switchStatus))
                    {
                        /*查询失败，返回默认值*/
                        retVal = UINT8_NULL;
                        break;
                    }                        
                    /*在道岔的实时状态与计轴区段的关联道岔状态相同时,当前计轴区段即为所求*/
                    if (((SWITCH_STATUS_SAME == SwitchStatusInfoStru[i].switchStatus) && (SWITCH_STATUS_SAME == pAxleSgmtStru->relatPointStatus[j])) 
                        || ((SWITCH_STATUS_CONTRA == SwitchStatusInfoStru[i].switchStatus) && (SWITCH_STATUS_CONTRA == pAxleSgmtStru->relatPointStatus[j])))
                    {
                        /*道岔状态匹配*/
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
* 函数功能：本函数功能是查询当前计轴区段的相邻计轴区段。相邻计轴区段分为起点相邻计轴区段和终点相邻计轴区段
* 入口参数：UINT16 currentACID                    计轴区段编号
*            UINT8_S dir                            运行方向
*            UINT8_S startOrEnd                    起点或终点（1为起点，2为终点）
* 出口参数：无
* 返回值：  UINT8_S retVal 查询失败:0
*            1 成功
*            2 线路的终点
*            3 道岔状态未知
*/
UINT8_S FindAdjacentACID(const UINT16_S currentACID,const UINT8_S dir,const UINT8_S startOrEnd,UINT8_S* axleSecNum,UINT16_S* axleSecIdBuff)
{

    UINT8_S retVal = 0u;/*函数返回值*/
    UINT16_S tmpFindAxleSgmtID = 0u;/*临时变量--存储相邻计轴区段id*/
    BnfAxleSectionStruct *pAxleSgmtStruct = NULL;/*指向计轴区段信息的结构体指针*/
    UINT8_S tmpNum = 0u;/*循环变量--用于遍历计轴区段相邻计轴区段*/
    UINT8_S isFind = 0u;/*是否找到相邻的计轴区段：1为找到，0为没有找到*/
    UINT8_S isErrorFalg = 1u;/*0 错误返回  1 正确返回*/

    if((NULL == axleSecNum) || (NULL == axleSecIdBuff))
    {
        isErrorFalg = 0u;
    }

    /*判断入口数据方向的正确性*/
    if ((0u == isErrorFalg) || ((LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir)))
    {
        /*入口数据方向错误，查询失败，返回错误*/
        isErrorFalg = 0u;
    }

    /*判断入口数据端点的正确性*/
    if ((0u == isErrorFalg)||((START_POINT != startOrEnd) && (END_POINT != startOrEnd))||(NULL == axleSecIdBuff)) 
    {
        isErrorFalg = 0u;
    }

    /*利用管理函数找到计轴区段的相关信息*/
    pAxleSgmtStruct =  GetIndexIdAxleSectionDataStru(currentACID);
    if ((0u == isErrorFalg)||(NULL == pAxleSgmtStruct))
    {
        isErrorFalg = 0u;
    }
    /*1. 运行方向为同向， 查询起点端点方向
      2. 运行方向为反向，查询终点端点方向
    在上述两种情况下，查询当前计轴区段的始端相邻计轴区段*/
    if ((1u == isErrorFalg)&&(((LINESEG_SAME_DIR == dir) && (START_POINT == startOrEnd))
        || ((LINESEG_CONVER_DIR == dir) && (END_POINT == startOrEnd))))
    {
        /*遍历相邻计轴区段，然后验证道岔状态是否匹配计轴区段*/
        if (0u == pAxleSgmtStruct->orgnAxleSecNum)
        {
            /*1.没有相邻计轴区段*/
            retVal = 2u;
        }
        else
        {
            isFind=0u;
            for (tmpNum=0u;tmpNum<pAxleSgmtStruct->orgnAxleSecNum;tmpNum++)
            {
                tmpFindAxleSgmtID=pAxleSgmtStruct->orgnAxleSgmtId[tmpNum];

                /*相邻计轴区段存在*/
                if (tmpFindAxleSgmtID != 0xffffu)
                {
                    /*调用函数“判断当前道岔状态是否满足计轴区段”*/
                    retVal = CheckPointFitAxleSgmt(tmpFindAxleSgmtID);
                    if (1u == retVal)
                    {
                        /*找到相邻计轴区段*/
                        isFind=1u;
                        /*不可能同时有两个相邻计轴区段同时匹配道岔,所以找到一个就可以*/
                        break;
                    }
                    else
                    {
                        /*状态不满足，继续验证下一个计轴区段*/
                    }
                } 
                else
                {
                    /*相邻计轴区段不存在，继续查找下一个计轴区段*/
                }
            }

            /*存在计轴区段，但是都不满足道岔状态*/
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
        /*1. 运行方向为反向， 查询起点端点方向
        2. 运行方向为同向，查询终点端点方向
        在上述两种情况下，查询当前计轴区段的末端相邻计轴区段*/        
        if (0u == pAxleSgmtStruct->tmnlAxleSecNum)
        {
            /*1.没有相邻计轴区段*/
            retVal = 2u;
        }
        else
        {
            isFind=0u;
            /*遍历相邻计轴区段，然后验证道岔状态是否匹配计轴区段*/
            for (tmpNum=0u;tmpNum<pAxleSgmtStruct->tmnlAxleSecNum;tmpNum++)
            {
                tmpFindAxleSgmtID=pAxleSgmtStruct->tmnlAxleSgmtId[tmpNum];

                /*相邻计轴区段存在*/
                if (tmpFindAxleSgmtID != UINT16_NULL)
                {
                    /*调用函数“判断当前道岔状态是否满足计轴区段”*/
                    retVal = CheckPointFitAxleSgmt(tmpFindAxleSgmtID);
                    if (1u == retVal)
                    {
                        /*找到相邻计轴区段*/
                        isFind=1u;
                        /*不可能同时有两个相邻计轴区段同时匹配道岔,所以找到一个就可以*/
                        break;
                    }
                    else
                    {
                        /*状态不满足，继续验证下一个计轴区段*/
                    }
                } 
                else
                {
                    /*相邻计轴区段不存在，继续查找下一个计轴区段*/
                }
            }
            /*存在计轴区段，但是都不满足道岔状态*/
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
* 功能描述： 查询当前点向前方向一定距离的另外一个点的位置
* 参数说明： const UINT16_S seg1,
*            const UINT32_S offset1,
*            const UINT8_S dir,
*            const UINT32_S distance,

*            UINT16_S *outSeg,
*            UINT32_S *outOffset,
*            UINT16_S *errorSwitchId
* 返回值：         
0x03：位置计算成功
0x02：位置计算失败（原因道岔位置错误）
0x01：位置计算失败（原因线路尽头）
0x00：位置计算失败（原因入口参数错误）
*/
UINT8_S CheckNextPointOnDistance(const UINT16_S seg1,const UINT32_S offset1,const UINT8_S dir,const UINT32_S distance,UINT16_S *outSeg,UINT32_S *outOffset,UINT16_S *errorSwitchId)
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT8_S flag = 1u;/*返回值标志*/
    UINT32_S segLength = 0u;/*SEG长度*/
    UINT16_S pointId = 0u;/*点ID*/
    UINT16_S pointType = 0u;/*点类型*/
	UINT16_S nextPointType = 0u;/*下一个Seg的点类型*/
    UINT16_S curSegId = 0u;/*当前SEGID*/
    UINT16_S nextMainSegId = 0u;/*下一个正向SEGID*/
	UINT16_S nestSideSegId = 0u;/*下一个侧向SEGID*/
	UINT16_S nextSegId = 0u;/*下一个待查SEGID*/
	UINT16_S frontMainSegId = 0u;/*下一个正向SEGID*/
	UINT16_S frontSideSegId = 0u;/*下一个侧向SEGID*/
    UINT32_S findSegLength = 0u;/*已查找的距离信息*/
    UINT8_S switchStatus = 0u;/*道岔状态*/
    UINT32_S tempNewSegLength = 0u;/*临时存放SEG长度*/
	UINT8_S flagForWhile = 0u;
    

    if((NULL == outSeg) || (NULL == outOffset) || (NULL == errorSwitchId))
    {
        flag = 0u;
    }

    
    segLength = GetSegDataStrulength(seg1);
    /*判断数据输入旧位置偏移量的有效性*/    
    if ((0u == flag)|| (offset1 > segLength)) 
    {
        flag = 0u;
    }
    
    /*判断入口数据方向的正确性*/
    if ((0u == flag) || ((dir != LINESEG_SAME_DIR) && (dir != LINESEG_CONVER_DIR)))
    {
        flag = 0u;
    }

    /*当1. 偏移量为正，且运行方向向前；
        2. 偏移量为负，且运行方向向后；时沿向前方向查找新位置*/
    if ((1u == flag)&&(LINESEG_SAME_DIR == dir))
    {
        findSegLength = segLength - offset1;
        curSegId = seg1;
        tempNewSegLength = segLength;
    	retVal = 3u;

        while ((findSegLength < distance) || (1u == flagForWhile))
        {
            /*获取当前SEG的终点ID和类型*/
        	flagForWhile = 0u;
        	pointType = 0u;
            pointId = GetSegDataStruendPointInfo(curSegId,&pointType);

            nextMainSegId = GetSegDataStrusegTmnlJointMainSegId(curSegId);
        	nestSideSegId = GetSegDataStrusegTmnlJointSideSegId(curSegId);

            if ((nextMainSegId != 65535u) || (nestSideSegId != 65535u))
            {
                /*判断点类型是否为道岔*/
                if(POINTTYPE_SWITCH == pointType)
                {
                    /*获取道岔状态*/
                	switchStatus = GetSwitchStatus(pointId);

                	if ((nextMainSegId != 65535u) && (nestSideSegId != 65535u))
                    {
                    	if (SWITCH_STATUS_SAME == switchStatus)
                        {
                            /*下一个SEGID已经获取，为终点的正向SEG*/
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
                        /*获取该seg的反向Seg(起点相邻Seg)情况,以确定查询到该seg需要的道岔方向*/
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
                            /*计算错误,道岔未在需要位置*/
                            *errorSwitchId = pointId;
                        	retVal = 0x02u;
                        	break;
                        }
                    }
                	else
                    {
                        /*0x00：位置计算失败（其他原因）*/
                    	retVal = 0x00u;
                    	break;
                    }
                }
            	else
                {
                    /*记轴点,获取正向下一个SEG的终点类型*/
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

                /*更新已查询长度信息和当前seg信息*/
            	if (findSegLength <= distance)
                {
                	tempNewSegLength = GetSegDataStrulength(nextSegId);
                	findSegLength = findSegLength + tempNewSegLength;
                	curSegId = nextSegId;
                }
            }
            else
            {
                /*0x01：位置计算失败（原因线路尽头）*/
                retVal = 0x01u;
                break;
            }
        }
        if(retVal == 3u)
        {
            /*输出信息，查询成功*/
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
            /*获取当前SEG的起点ID*/
        	flagForWhile = 0u;
        	pointType = 0u;
            pointId = GetSegDataStrustartPointInfo(curSegId,&pointType);

            nextMainSegId = GetSegDataStrusegStartJointMainSegId(curSegId);
        	nestSideSegId = GetSegDataStrusegStartJointSideSegId(curSegId);

            if ((nextMainSegId != 65535u) || (nestSideSegId != 65535u))
            {
                /*判断点类型是否为道岔*/
                if(POINTTYPE_SWITCH  == pointType)
                {
                    /*获取道岔状态*/
                	switchStatus = GetSwitchStatus(pointId);

                	if ((nextMainSegId != 65535u) && (nestSideSegId != 65535u))
                    {
                    	if (SWITCH_STATUS_SAME == switchStatus)
                        {
                            /*下一个SEGID已经获取，为终点的正向SEG*/
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
                        /*获取该seg的反向Seg(起点相邻Seg)情况,以确定查询到该seg需要的道岔方向*/
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
                            /*计算错误,道岔未在需要位置*/
                            *errorSwitchId = pointId;
                        	retVal = 0x02u;
                        	break;
                        }
                    }
                	else
                    {
                        /*0x00：位置计算失败（其他原因）*/
                    	retVal = 0x00u;
                    	break;
                    }
                }
            	else
                {
                    /*计轴点,获取正向下一个SEG的起点类型*/
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
                    /*更新已查询长度信息和当前seg信息*/
                	tempNewSegLength =  GetSegDataStrulength(nextSegId);
                	findSegLength = findSegLength + tempNewSegLength;
                	curSegId = nextSegId;
                }
                
            	retVal = 3u;
            }
            else
            {
                /*0x01：位置计算失败（原因线路尽头）*/
                retVal = 0x01u;
                break;
            }
        }
        if(retVal == 3u)
        {
            /*输出信息，查询成功*/
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
* 功能描述： 获取SEGID包含的计轴区段ID
* 参数说明： UINT16_S  segId，SegID
* 返回值  ： 0: 获取数据失败
*            >0:计轴区段个数
*/
UINT8_S GetAxleSecAccordSegIdBuff(const UINT16_S* pSegId,const UINT8_S segNum,UINT16_S* pAxleSecId)
{
    UINT8_S retVal = 0u;

    UINT8_S j = 0u;/*循环使用*/
    UINT8_S k = 0u;/*循环使用*/
    UINT8_S tempJ = 0u;/*循环使用*/
    UINT8_S index = 0u;/*数组下标*/

    UINT16_S tmpAcSecBuff[TWO_POINT_AC_NUM_MAX] = {0};
    UINT16_S tmpSegIdBuff[3] = {0};
    UINT8_S tmpSegIdNum = 0u;
    UINT8_S needFindNum = 0u;/*需要查找到的个数*/

    if (((segNum <= BOTHSEG_INCLUDE_MAX_SEG)&&(segNum > 0u))
        &&(pSegId != NULL)&&(pAxleSecId != NULL))
    {
        for (k = 0u;k < segNum; k++)
        {
            /*根据此SEG前后是否有道岔补充SEGID*/
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
* 功能描述： 根据当前位置和位移,得到新位置.(已知道岔的状态)
* 参数说明： const UINT16_S seg1,
*            const UINT32_S offset1,
*            const UINT8_S dir,
*            const INT32_S distance,
*            UINT16_S *outSeg,
*            UINT32_S *outOffset,
*            UINT8_S* outDir
* 返回值：   1,成功
*            0,失败
*/
UINT8_S GetNewLocCalcDis(const UINT16_S seg1,const UINT32_S offset1,const UINT8_S dir,const INT32_S distance,UINT16_S *outSeg,UINT32_S *outOffset,UINT8_S* outDir) 
{
    UINT8_S retVal=0u;/*函数返回值*/
    UINT8_S isFindError = 1u;/*是否有错误  1无错误  0 有错误*/
    UINT16_S curSegId = 0u;/*用于查找过程中临时保存当前SegID*/
    UINT16_S nextSegId = 0u;/*下一个SEGID*/
    UINT8_S findDir = 0u;/*用于记录实际操作过程中的查找方向*/
    INT32_S findDis = 0;/*临时保存偏移量*/
    INT32_S findDisSum = 0;/*用于累加位移偏移量*/
    UINT32_S tmpNewSegLength = 0u;/*临时存放SEG长度*/
    BnfSegStruct* tmpSegStru = 0;/*临时存放SEG结构体*/


    if((NULL == outSeg) || (NULL == outOffset) || (NULL == outDir))
    {
        isFindError = 0u;
    }

    

    /*有效性检查*/
    tmpSegStru = GetIndexIdSegDataStru(seg1);
    if((0u == isFindError)|| (NULL == tmpSegStru)||(tmpSegStru->length < offset1)
        ||((dir != LINESEG_SAME_DIR)&&(dir != LINESEG_CONVER_DIR)))
    {
        isFindError = 0u;
    }

    /*特殊情况处理，偏移量distance为0*/
    if ((1u == isFindError)&&(distance == 0))
    {
        /*distance如果为0，返回当前位置为所求*/
        *outSeg = seg1;
        *outOffset = offset1;
        *outDir = dir;

        /*查询成功，返回查询结果*/
        retVal = 1u;
    }
    else
    {        
        /*如果displacement小于0，则按照displacement绝对值来查找新位置，方向取反*/
        if((LINESEG_SAME_DIR == dir)&&(distance > 0))
        {
            /*正向查找*/
            findDir = LINESEG_SAME_DIR;
            findDis = distance;
        }
        else if((LINESEG_CONVER_DIR == dir)&&(distance<0))
        {
            /*正向查找*/
            findDir = LINESEG_SAME_DIR;
            findDis = -distance;
        }
        else if((LINESEG_SAME_DIR == dir)&&(distance < 0))
        {
            /*反向查找*/
            findDir = LINESEG_CONVER_DIR;
            findDis = -distance;
        }
        else if((LINESEG_CONVER_DIR == dir)&&(distance > 0))
        {
            /*反向查找*/
            findDir = LINESEG_CONVER_DIR;
            findDis = distance;
        }
        else
        {
            /*不可达分支*/
        }
    }

    if((isFindError == 1u)&&(0u == retVal)&&(findDir == LINESEG_SAME_DIR))
    {
        /*根据当前位置正向累加偏移量*/
        findDisSum = tmpSegStru->length - offset1;

        /*根据位移判断新位置是否在同一个SEG上*/
        if(findDisSum >= findDis)
        {
            /*说明在同一个Seg上，累加位移得到新位置*/
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
                /*获取当前SEG的终点ID和类型*/
                retVal = GetNextSegId(curSegId,findDir,&nextSegId);
                if (1u == retVal)
                {
                    /*更新已查询长度信息和当前seg信息*/
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
                /*输出信息，查询成功*/
                *outSeg = curSegId;
                *outOffset = findDis - (findDisSum-tmpNewSegLength);
                *outDir = dir;
                retVal = 1u;
            }
        }
    }
    else if((isFindError == 1u)&&(0u == retVal))
    {
        /*累加偏移量置0*/
        findDisSum=0;

        /*根据当前位置反向累加偏移量*/
        findDisSum= offset1;

        if(findDisSum >= findDis)
        {
            /*说明在同一个Seg上*/
            *outSeg = seg1;
            *outOffset =offset1 - findDis;
            *outDir = dir;

            /*查询成功，返回查询结果*/
            retVal = 1u;
        }
        else
        {
            curSegId = seg1;
            while (findDisSum <= findDis)
            {
                /*获取当前SEG的终点ID和类型*/
                retVal = GetNextSegId(curSegId,findDir,&nextSegId);
                if (1u == retVal)
                {
                    /*更新已查询长度信息和当前seg信息*/
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
                /*输出信息，查询成功*/
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
* 功能描述： 获取两点的距离向量,从起点到终点方向
* 参数说明： const UINT16_S startSegId,const UINT32_S startSegoffset,
*            const UINT16_S endSegId,const UINT32_S endSegoffset,const UINT16_S endDir,INT32_S* distance
* 返回值  ： 0: 获取失败
*             1：获取成功
*/
UINT8_S GetDirBothSegPointVectorDis(const UINT16_S startSegId,const UINT32_S startSegoffset,
                        const UINT16_S endSegId,const UINT32_S endSegoffset,const UINT16_S endDir,INT32_S* distance)
{

    UINT8_S retVal = 0u;/*用于函数返回值*/
    UINT8_S isFindError = 1u;/*是否有错误  1无错误  0 有错误*/
    UINT16_S tmpNextSegId = 0u;/*用于查找过程中临时保存下一个SegID*/
    UINT8_S startFindFlag = 1u;/*0，查找失败1,继续查找。*/
    UINT8_S endFindFlag = 1u;/*0，查找失败1，继续查找。*/
    INT32_S startFindDisSum = 0;/*start查找end过程中的位移累加值*/
    INT32_S endFindDisSum = 0;/*end查找start过程中位移累加值*/
    UINT16_S tmpStartCurSegId = 0u;/*用于查找过程中临时保存起点当前SegID*/
    UINT16_S tmpEndCurSegId = 0u;/*用于查找过程中临时保存终点当前SegID*/
    BnfSegStruct *pStartCurSegStru = NULL;/*start当前Seg*/
    BnfSegStruct *pEndCurSegStru = NULL;/*end当前Seg*/
    UINT16_S i = 0u;/*循环用变量*/

    if(NULL == distance)
    {
        isFindError = 0u;
    }
	else
    {
        /*预置函数返回值为0*/
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

    /*特殊情况处理，Segstart与Segend处于同一Seg上*/
    if(startSegId == endSegId)
    {
        /*start,end位于同一seg，计算两点间距离信息*/
        *distance = endSegoffset - startSegoffset;
        
        if (LINESEG_CONVER_DIR == endDir)
        {
            /*方向相反，转换位移符号*/
            *distance=-(*distance);
        }

        /*函数查询成功，返回*/        
        retVal=1u;
    }

    
    tmpStartCurSegId = startSegId;
    tmpEndCurSegId = endSegId;
    /*按照end的方向不同进行分类*/
    /*起点和终点分别按此方向查找对方,如果找到对方,记录查找到的位移,返回结果*/
    if ((1u == isFindError)&&(0u == retVal)&&(LINESEG_SAME_DIR == endDir))
    {
        /*累加位移值*/
        startFindDisSum = pStartCurSegStru->length - startSegoffset;
        endFindDisSum = pEndCurSegStru->length - endSegoffset;
        for (i = 0u; i < BOTHSEG_INCLUDE_MAX_SEG;i++)
        {
            /*此处循环是为了计数，循环次数不能超过BOTHSEG_INCLUDE＿MAX_SEG*/
            if(1u == startFindFlag)
            {
                /*start向前查找一个seg*/
                retVal = GetNextSegId(tmpStartCurSegId, LINESEG_SAME_DIR, &tmpNextSegId);
                if( 1u==retVal )
                {
                    if(tmpNextSegId == endSegId)
                    {
                        /*查找成功*/
                        startFindFlag = 1u;
                        /*累加偏移量，计算结果值*/
                        startFindDisSum += endSegoffset;
                        /*此时start沿正向找到了end，偏移量为正*/
                        *distance = startFindDisSum;

                        /*查找成功，返回结果*/
                        retVal=1u;
                        break;
                    }
                    else
                    {
                        /*start没有找到end，累加偏移量，继续查找*/
                        startFindDisSum += GetSegDataStrulength(tmpNextSegId);
                        tmpStartCurSegId = tmpNextSegId;
                    }
                }
                else
                {
                    /*线路终点或者道岔状态未知，start点停止查找*/
                    startFindFlag = 0u;
                }
            }

            /*end向前查找一个seg*/
            if(1u == endFindFlag)
            {
                retVal=GetNextSegId(tmpEndCurSegId,LINESEG_SAME_DIR,&tmpNextSegId);
                if( 1u== retVal)
                {
                    if(tmpNextSegId == startSegId)
                    {
                        /*累加偏移量，计算结果值*/
                        endFindDisSum += (startSegoffset);

                        /*此时end沿正向找到了start，偏移量为负*/
                        *distance =- endFindDisSum;

                        /*查找成功，返回结果*/
                        retVal=1u;
                        break;
                    }
                    else
                    {
                        /*如果end没有找到start，累加偏移量，继续查找*/
                        endFindDisSum += GetSegDataStrulength(tmpNextSegId);
                        tmpEndCurSegId = tmpNextSegId;
                    }
                }
                else
                {
                    /*线路终点或者道岔状态未知，停止查找*/
                    endFindFlag=0u;            
                }
            }

            if((0u == startFindFlag)&&(0u == endFindFlag))
            {
                /*start，end均结束查找并且没有找到对方，函数返回失败*/
                retVal=0u;
                break;
            }
        }
    }
    else if ((1u == isFindError)&&(0u == retVal))
    {
        /*start,end均沿反向向查找*/
        startFindDisSum = startSegoffset;
        endFindDisSum = endSegoffset;
        for (i = 0u;i < BOTHSEG_INCLUDE_MAX_SEG;i++)
        {
            if(1u == startFindFlag)
            {
                /*start向前查找一个seg*/
                retVal=GetNextSegId(tmpStartCurSegId, LINESEG_CONVER_DIR,&tmpNextSegId);
                if( 1u==retVal )
                {
                    if(tmpNextSegId == endSegId)
                    {
                        startFindDisSum += (GetSegDataStrulength(tmpNextSegId)- endSegoffset);

                        /*此时start沿反向找到了end，偏移量为正*/
                        *distance = startFindDisSum;

                        /*查找成功，返回结果*/
                        retVal=1u;
                        break;
                    }
                    else
                    {
                        /*如果start没有找到end，累加偏移量，继续查找*/
                        startFindDisSum += GetSegDataStrulength(tmpNextSegId);
                        tmpStartCurSegId = tmpNextSegId;
                    }
                }
                else
                {
                    /*线路终点或者道岔未找到，停止查找*/
                    startFindFlag=0u;
                }
            }

            /*end向前查找一个seg*/
            if(1u == endFindFlag)
            {
                retVal = GetNextSegId(tmpEndCurSegId, LINESEG_CONVER_DIR,&tmpNextSegId);
                if( 1u== retVal)
                {
                    if(tmpNextSegId == startSegId)
                    {
                        /*end找到了start*/
                        endFindDisSum += (GetSegDataStrulength(tmpNextSegId)- startSegId);

                        /*此时end沿反向找到了start，偏移量为负*/
                        *distance = -endFindDisSum;

                        /*查找成功，返回结果*/
                        retVal=1u;
                        break;
                    }
                    else
                    {
                        /*如果end没有找到start，累加偏移量，继续查找*/
                        endFindDisSum += GetSegDataStrulength(tmpNextSegId);
                        tmpEndCurSegId = tmpNextSegId;
                    }
                }
                else
                {
                    /*线路终点或者道岔状态未知，停止查找*/
                    endFindFlag=0u;            
                }
            }

            if((0u == startFindFlag)&&(0u == endFindFlag))
            {
                /*start，end均结束查找并且没有找到对方，函数返回失败*/
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
* 功能描述： 根据SEG以及SEG的前方和后方是否有道岔,若有道岔，增加道岔前方或后方的SEGID，若无,之间返回此SEGID。
*            (目前根据传入的SEG往前和往后各查2次)
* 参数说明： const UINT16_S segId,SEG的ID
*             UINT16_S* segBuff    SEG地址
* 返回值  ： 0: 获取失败
*            >0: SEGID个数
*/
UINT8_S GetSegBuffAccordSedIdAndSwitch(const UINT16_S segId,UINT16_S* segBuff,UINT8_S* findNum)
{ 
    BnfSegStruct* bnfSegStru = NULL;
    UINT8_S switchStatus = 0u;/*道岔状态*/
    UINT8_S index = 0u;/*偏移*/
    UINT16_S tmpSegId = 0u;
    bnfSegStru = GetIndexIdSegDataStru(segId);
    if ((segBuff != NULL) && (NULL != bnfSegStru) && (NULL != findNum))
    {
        *findNum = 0u;
        
        segBuff[index] = segId;
        index=index+1;
        if (bnfSegStru->endPointType == POINTTYPE_SWITCH)
        {
            /*获取道岔状态*/            
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
            /*获取道岔状态*/
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
* 功能描述： 查询两个点之间的逻辑区段ID和对应的SEG信息序列(道岔状态已知)
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      segEndID        UINT16_S    终点SegID
*                      dir            UINT8_S     运行方向
*                      includePoint     UINT8_S     1包含端点  0不包含端点
*             输出参数:pSegId        UINT16_S*    SEGID数组
*                      segIdNum        UINT8_S*      SEGID个数    
* 返回值  ： 0:失败1：成功
*/    
UINT8_S GetDirSegArrayAndLogicSec(UINT16_S segStartID,UINT32_S segStartOffset,UINT16_S segEndID,UINT32_S segEndOffset,UINT8_S dir,UINT8_S* logicNum,UINT16_S* logicId,UINT8_S* relateLogicNumBuff,BnfRelateLogicSecInfoStruct relateLogicInfo[][2])
{
    UINT8_S retVal = 0u;/*函数返回值*/
    UINT8_S tmpRetVal = 0u;/*临时使用函数返回值*/
    UINT16_S nextLogicId = 0u;/*获取下一个逻辑区段ID*/
    UINT16_S tmpLogic = 0u;
    UINT8_S index = 0u;/*数组下标偏移*/
    UINT16_S startLogicId = 0u;/*起点逻辑区段Id*/
    UINT16_S endLogicId = 0u;/*终点逻辑区段Id*/

    UINT8_S tmpStartRelateLogicNum = 0u;
    BnfRelateLogicSecInfoStruct startRelateLogicId[LOGICSECTION_OF_SWITCH_MAX_NUM] = {{0u}};
    UINT8_S tmpEndRelateLogicNum = 0u;
    BnfRelateLogicSecInfoStruct endRelateLogicId[LOGICSECTION_OF_SWITCH_MAX_NUM] = {{0u}};


    /*获取起点和终点对应的逻辑区段ID*/
    GetPointOfLogSecInfo(segStartID,segStartOffset,&startLogicId,&tmpStartRelateLogicNum,&startRelateLogicId);

    GetPointOfLogSecInfo(segEndID,segEndOffset,&endLogicId,&tmpEndRelateLogicNum,&endRelateLogicId);

    if ((startLogicId != UINT16_NULL)&&(endLogicId != UINT16_NULL)&&(logicId != NULL)&&(relateLogicNumBuff != NULL)&&(relateLogicInfo != NULL)&&(NULL != logicNum))
    {
        if (startLogicId == endLogicId)
        {
            /*查询此范围内的逻辑区段ID*/
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
* 功能描述： 查询此SEG后方的逻辑区段
*            (1)若有一个逻辑区段直接返回
*            (2)若有多个，返回逻辑区段偏移量最大的
*            (3)若此SEG包含在两个逻辑区段中，则根据输出两个逻辑区段ID
* 参数说明： const UINT16_S startSegId,const UINT32_S startOffset,const UINT32_S endOffset
             UINT16_S logicSectionIdBuf[];逻辑区段ID数组
* 返回值  :  0: 失败
*             1: 成功
*/ 
static void GetPointOfLogSecInfo(const UINT16_S startSegId,const UINT32_S startOffSet,UINT16_S* logicId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct relateLogicInfo[][2])
{
    BnfLogicSectionStruct* tmpLogicSecStru = NULL;/*逻辑区段结构体信息指针*/
    UINT16_S lineLogicNum = 0u;/*逻辑区段行数*/
    UINT16_S tmpSegIdBuff[3] = {0};
    UINT8_S tmpSegIdNum = 0u;
    UINT8_S needFindNum = 0u;/*需要查找到的个数*/
    UINT8_S isfindNum = 0u;/*查找到的个数*/
    UINT16_S i = 0u;/*循环使用*/
    UINT8_S j = 0u;/*循环使用*/
    UINT8_S k = 0u;/*循环使用*/


    tmpSegIdNum = GetSegBuffAccordSedIdAndSwitch(startSegId,tmpSegIdBuff,&needFindNum);

    tmpLogicSecStru = GetLogicSectionDataInfo(&lineLogicNum);
    if ((NULL != logicId) && (NULL != tmpLogicSecStru) && (tmpSegIdNum > 0u))
    {
        *logicId = UINT16_NULL;
        for(i = 0u;i < lineLogicNum;i++)
        {

            if (1u == needFindNum)
            {
                /*startSegId前后方没有道岔*/
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
                /*startSegId前方或后方有道岔*/
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
* 功能描述： 查询指定运行方向的下一个SegID(道岔状态已知)
* 参数说明： 输入参数:Seg_ID  UINT16_S    当前的SegID
*                         Dir  UINT8_S     运行方向
*             输出参数:nextSegId  UINT16_S*   下一个SEGID
* 返回值  ： 0:失败1：成功
*/
static UINT8_S GetNextLogicId(UINT16_S logicId,UINT8_S dir,UINT16_S* nextLogicId,UINT8_S* relateLogicNum,BnfRelateLogicSecInfoStruct relateLogicInfo[][2])
{
    UINT8_S retVal = 0u;/*函数返回*/
    BnfLogicSectionStruct* logicInfoStru = NULL;
    BnfLogicSectionStruct* curLogicInfoStru = NULL;
    UINT8_S switchStatus = 0u;/*道岔状态*/
    UINT8_S i = 0u;/*循环使用*/
	UINT8_S inParaErrFlag = 1u;

	if((NULL == nextLogicId) || (NULL == relateLogicNum) || (NULL == relateLogicInfo))
    {
        inParaErrFlag = 0u;
    }
	else
    {
        *nextLogicId = UINT16_NULL;
    }


    /*获取此SE逻辑G对应的逻辑区段信息*/
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
* 函数功能：此函数的功能是查询当前Garde的相邻Grade
* 入口参数：const UINT16_S curGradeID    当前坡度编号
            const UINT8_S dir            期望运行方向        
* 出口参数：    无
* 返回值：    UINT16_S findGradeID    查询失败: 0xffff; 查询成功: 返回相邻的坡度ID                                                              
************************************************************************/
UINT16_S FindAdjacentGradeID(const UINT16_S curGradeID, const UCHAR_S dir)
{
    UINT16_S findGradeID = 0u;/*函数返回值*/
    BnfGradeStruct *pstGrade = NULL;/*指向坡度信息的结构体指针*/
    UINT8_S isFindErr = 1u;
    UINT8_S switchStatus = 0u;/*道岔状态*/
    
    /*判断输入的有效性*/
    pstGrade = GetIndexIdGradeDataStru(curGradeID);
    if (pstGrade == NULL)
    {
        isFindErr = 0u;
    }
    else
    {
        /*判断入口数据方向的有效性*/
        if ((LINESEG_SAME_DIR != dir) && (LINESEG_CONVER_DIR != dir))
        {
            isFindErr = 0u;
        }
    }

    
    /*在期望运行方向与Seg的逻辑方向相同时，向当前坡度的末端相邻坡度进行查询*/
    if ((LINESEG_SAME_DIR == dir)&&(1u == isFindErr))
    {
        if ((0xffffu == pstGrade->tmnlJointSideGradeId)&&(0xffffu == pstGrade->tmnlJointMainGradeId))
        {
            /*当前坡度已经没有相邻坡度，函数返回0*/
            isFindErr = 0u;
        }
        else
        {
            /*在当前坡度的末端相邻侧线坡度为空时，其末端相邻正线坡度即为所求*/
            if (0xffffu == pstGrade->tmnlJointSideGradeId)
            {
                /*查询成功，返回相关信息*/
                findGradeID = pstGrade->tmnlJointMainGradeId;
            }
            else
            {
                /*在当前坡度的末端相邻侧线坡度不为空时，需利用实时的道岔状态来判断相邻坡度*/
                switchStatus = GetSwitchStatus(pstGrade->tmnlRelatePointId);
                /*道岔失去表示,数据异常，查询失败，返回默认值，退出*/
                if (SWITCH_STATUS_LOSE == switchStatus)
                {
                    isFindErr = 0u;
                }
                else
                {
                    /*道岔处于定位,其末端相邻正线坡度即为所求*/
                    if (SWITCH_STATUS_SAME == switchStatus)
                    {
                        findGradeID = pstGrade->tmnlJointMainGradeId;            
                    }
                    else
                    {
                        /*道岔处于反位,其末端相邻侧线坡度即为所求*/
                        findGradeID = pstGrade->tmnlJointSideGradeId;
                    }                            
                }
            }    
        }            
    }
    else if (1u == isFindErr)
    {
        /*在期望运行方向与Seg的逻辑方向相反时，向当前坡度的始端端相邻坡度进行查询*/
        /*利用管理函数直接找到当前坡度的信息*/
        if ((0xffffu == pstGrade->orgnJointSideGradeId)&&(0xffffu == pstGrade->orgnJointMainGradeId))
        {
            /*当前坡度已经没有相邻坡度，函数返回0*/
            isFindErr = 0u;
        }
        else
        {
            /*在当前坡度的始端相邻侧线坡度为空时，其始端相邻正线坡度即为所求*/
            if (0xffffu == pstGrade->orgnJointSideGradeId)
            {
                /*查询成功，返回坡度ID*/
                findGradeID = pstGrade->orgnJointMainGradeId;
            }
            else
            {
                /*在当前坡度的始端相邻侧线坡度不为空时，需利用实时的道岔状态来判断相邻坡度*/
                switchStatus = GetSwitchStatus(pstGrade->orgnRelatePointId);

                /*道岔失去表示,数据异常，查询失败，返回默认值，退出*/
                if (SWITCH_STATUS_LOSE == switchStatus)
                {
                    isFindErr = 0u;
                }
                else
                {
                    /*道岔处于定位,其始端相邻正线坡度即为所求*/
                    if(SWITCH_STATUS_SAME == switchStatus)
                    {
                        findGradeID = pstGrade->orgnJointMainGradeId;            
                    }
                    else
                    {
                        /*道岔处于反位,其始端相邻侧线坡度即为所求*/
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
* 功能描述： 根据SEG的ID同时以此SEG为起点或是终点,加以考虑道岔状态,找到相邻的Seg的ID
* 参数说明：  UINT16_S segId,SEG的ID
*             UINT8_S pointType 起点或终点
* 返回值  ： 0: 获取失败
*            >0: SEGID
*/

static UINT16_S AccordSwitchAndPointTypeGetSegId(UINT16_S segId,UINT8_S pointType)
{
    BnfSegStruct* bnfSegStru = NULL;
    UINT8_S switchStatus = 0u;/*道岔状态*/
    UINT16_S tmpSegOutId = 0u;

    bnfSegStru = GetIndexIdSegDataStru(segId);
    if (NULL != bnfSegStru)
    {
        if ((END_POINT == pointType)&&(bnfSegStru->endPointType == POINTTYPE_SWITCH))
        {
            /*获取道岔状态*/            
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
            /*获取道岔状态*/
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
