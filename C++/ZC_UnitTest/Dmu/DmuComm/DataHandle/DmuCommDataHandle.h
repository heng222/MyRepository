/********************************************************
* 
* 文 件 名： DmuCommDataHandle.h 
* 作    者： 董欣 
* 创建时间： 2016-09-03  
* 功能描述： 公共查询函数头文件 
* 备    注： 无 
* 
********************************************************/ 

#ifndef DMU_COMM_DATAHANDLE_H_
#define DMU_COMM_DATAHANDLE_H_

#include "../Load/LoadSeg.h"
#include "DmuCommDataTypeDefine.h"
#include "../Data/LogicSectionData.h"


#define SWITCHSTATUS_INFO_SIZE                           3                                   /*道岔信息的大小*/

/*****************************************   BNF初始化失败原因码定义***************************************/
#define BNFINITERR_REASON_1                    ((UINT32_S)0x00000001u)        /**/
#define BNFINITERR_REASON_2                    ((UINT32_S)0x00000002u)     /**/
#define BNFINITERR_REASON_3                    ((UINT32_S)0x00000004u)     /**/
#define BNFINITERR_REASON_4                    ((UINT32_S)0x00000008u)     /**/
#define BNFINITERR_REASON_5                    ((UINT32_S)0x00000010u)     /**/
#define BNFINITERR_REASON_6                    ((UINT32_S)0x00000020u)     /**/
#define BNFINITERR_REASON_7                    ((UINT32_S)0x00000040u)     /**/
#define BNFINITERR_REASON_8                    ((UINT32_S)0x00000080u)     /**/
#define BNFINITERR_REASON_9                    ((UINT32_S)0x00000100u)     /**/
#define BNFINITERR_REASON_10                   ((UINT32_S)0x00000200u)     /**/
#define BNFINITERR_REASON_11                   ((UINT32_S)0x00000400u)     /**/
/************************************end of BNF初始化失败原因码定义*************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*堆栈SEG信息*/
typedef struct _StackPushSegInfoStruct
{
    UINT16_S  SegIdBuff[BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG];                        /*SEGID*/
    UINT8_S   includeSegIdNum;                                                        /*已经写入的SGEID*/    
}StackPushSegInfoStruct;

/*
* 功能描述： 获取COM查询函数初始化失败原因
* 参数说明： void
* 返回值  ： COM查询函数初始化失败原因  
*/
UINT32_S GetComBnfInitErrReason(void);



/*
* 功能描述： 查询指定运行方向的下一个SegID
* 参数说明： 输入参数:Seg_ID  UINT16_S    当前的SegID
*                         Dir  UINT8_S     运行方向
*             输出参数:nextSegId  UINT16_S*   下一个SEGID
* 返回值  ： 0:失败1：成功
*/
UINT8_S GetNextSegId(UINT16_S segId,UINT8_S dir,UINT16_S* nextSegId);
/*
* 功能描述： 查询两个Seg间的序列(道岔状态未知)
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      segEndID        UINT16_S    终点SegID
*                      dir            UINT8_S     运行方向
*             输出参数:pSegId        UINT16_S*    SEGID数组
*                      segIdNum        UINT8_S*      SEGID个数    
* 返回值  ： 0:失败1：成功
*/    

UINT8_S GetDirNoSwitchStutasSegArray(UINT16_S startSegId,UINT16_S endSegId,UINT8_S dir,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S segIdBuff[]);




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

UINT8_S GetDirSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S dir,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId);

/*
* 功能描述： 查询两个Seg间的距离
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      startOffSet    UINT32_S      起点偏移量
*                      segEndID        UINT16_S    终点SegID
*                      endOffSet        UINT32_S      终点偏移量
*                      dir            UINT8_S     运行方向
*             输出参数:destDistance  UINT32_S*   目标距离  
* 返回值  ： 0:失败1：成功
*/    
UINT8_S GetDirBothSegPointDisPlus(UINT16_S segStartID,UINT32_S startOffSet,UINT16_S segEndID,UINT32_S endOffSet,UINT8_S dir,UINT32_S* destDistance);

/*
* 功能描述： 查询两个Seg间的距离
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      startOffSet    UINT32_S      起点偏移量
*                      segEndID        UINT16_S    终点SegID
*                      endOffSet        UINT32_S      终点偏移量
*             输出参数:destDistance  UINT32_S*   目标距离  
* 返回值  ： 0:失败1：成功
*/    
UINT8_S GetNoDirBothSegPointDis(UINT16_S segStartID,UINT32_S startOffSet,UINT16_S segEndID,UINT32_S endOffSet,UINT32_S* destDistance);



/*
* 功能描述： 更新道岔的实时状态
* 参数说明： 输入参数:switchStatusBuff    UINT8_S[]     道岔状态信息
*                      buffLength        UINT16_S      数组长度
* 返回值  ： 0:失败1：成功
*/    
UINT8_S UpdateSwitchStatus(const UINT8_S switchStatusBuff[],UINT16_S buffLength);

/*
* 功能描述： 获取道岔状态
* 参数说明： const UINT16_S switchId 道岔ID
* 返回值  ： >=0  道岔状态   0   失败
*/    
UINT8_S GetSwitchStatus(const UINT16_S switchId);



/*
*函数功能：计算通用信息增加项
*参数说明：无
*返回值：0失败，1成功
*/
UINT8_S CalcCommAddInfo(void);









/*
* 功能描述： 根据当前位置和位移,得到新位置.
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
UINT8_S GetNewLocCalcDis(const UINT16_S seg1,const UINT32_S offset1,const UINT8_S dir,const INT32_S distance,UINT16_S *outSeg,UINT32_S *outOffset,UINT8_S* outDir);

/*
* 功能描述： 根据SEG以及SEG的前方和后方是否有道岔,若有道岔，增加道岔前方或后方的SEGID，若无，之间返回此SEGID
* 参数说明： const UINT16_S segId,SEG的ID
*             UINT16_S* segBuff    SEG地址
* 返回值  ： 0: 获取失败
*            >0: SEGID个数
*/
UINT8_S GetDirBothSegPointVectorDis(const UINT16_S startSegId,const UINT32_S startSegoffset,
                        const UINT16_S endSegId,const UINT32_S endSegoffset,const UINT16_S endDir,INT32_S* distance);
                        




/************************************************************************
* 函数功能：此函数的功能是查询当前Garde的相邻Grade
* 入口参数：const UINT16_S curGradeID    当前坡度编号
            const UINT8_S dir            期望运行方向        
* 出口参数：    无
* 返回值：    UINT16_S findGradeID    查询失败: 0xffff; 查询成功: 返回相邻的坡度ID                                                              
************************************************************************/
UINT16_S FindAdjacentGradeID(const UINT16_S curGradeID, const UCHAR_S dir);
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
UINT8_S FindAdjacentACID(const UINT16_S currentACID,const UINT8_S dir,const UINT8_S startOrEnd,UINT8_S* axleSecNum,UINT16_S* axleSecIdBuff);

/*
* 功能描述： 获取SEGID包含的计轴区段ID
* 参数说明： UINT16_S  segId，SegID
* 返回值  ： 0: 获取数据失败
*            >0:计轴区段个数
*/
UINT8_S GetAxleSecAccordSegIdBuff(const UINT16_S* pSegId,const UINT8_S segNum,UINT16_S* pAxleSecId);

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
UINT8_S CheckNextPointOnDistance(const UINT16_S seg1,const UINT32_S offset1,const UINT8_S dir,const UINT32_S distance,UINT16_S *outSeg,UINT32_S *outOffset,UINT16_S *errorSwitchId);
/*
* 功能描述： 根据SEG以及SEG的前方和后方是否有道岔,若有道岔，增加道岔前方或后方的SEGID，若无，之间返回此SEGID
* 参数说明： const UINT16_S segId,SEG的ID
*             UINT16_S* segBuff    SEG地址
* 返回值  ： 0: 获取失败
*            >0: SEGID个数
*/
UINT8_S GetSegBuffAccordSedIdAndSwitch(const UINT16_S segId,UINT16_S* segBuff,UINT8_S* findNum);
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
UINT8_S GetDirSegArrayAndLogicSec(UINT16_S segStartID,UINT32_S segStartOffset,UINT16_S segEndID,UINT32_S segEndOffset,UINT8_S dir,UINT8_S* logicNum,UINT16_S* logicId,UINT8_S* relateLogicNumBuff,BnfRelateLogicSecInfoStruct relateLogicInfo[][2]);

/*
* 功能描述： 查询两个Seg间的序列(道岔状态未知)
* 参数说明： 输入参数:segStartID    UINT16_S    起始SegID
*                      segEndID        UINT16_S    终点SegID
*             输出参数:pSegId        UINT8_S*    SEGID数组
*                      segIdNum        UINT8_S*      SEGID个数    
* 返回值  ： 0:失败1：成功
*/    

UINT8_S GetNoDirNoSwitchStutasSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId);

#ifdef __cplusplus
}
#endif

#endif
