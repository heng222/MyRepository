/********************************************************
* 
* �� �� ���� DmuCommDataHandle.h 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ������ѯ����ͷ�ļ� 
* ��    ע�� �� 
* 
********************************************************/ 

#ifndef DMU_COMM_DATAHANDLE_H_
#define DMU_COMM_DATAHANDLE_H_

#include "../Load/LoadSeg.h"
#include "DmuCommDataTypeDefine.h"
#include "../Data/LogicSectionData.h"


#define SWITCHSTATUS_INFO_SIZE                           3                                   /*������Ϣ�Ĵ�С*/

/*****************************************   BNF��ʼ��ʧ��ԭ���붨��***************************************/
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
/************************************end of BNF��ʼ��ʧ��ԭ���붨��*************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*��ջSEG��Ϣ*/
typedef struct _StackPushSegInfoStruct
{
    UINT16_S  SegIdBuff[BOTHSEG_NOSWITCHSTATUS_INCLUDE_MAX_SEG];                        /*SEGID*/
    UINT8_S   includeSegIdNum;                                                        /*�Ѿ�д���SGEID*/    
}StackPushSegInfoStruct;

/*
* ���������� ��ȡCOM��ѯ������ʼ��ʧ��ԭ��
* ����˵���� void
* ����ֵ  �� COM��ѯ������ʼ��ʧ��ԭ��  
*/
UINT32_S GetComBnfInitErrReason(void);



/*
* ���������� ��ѯָ�����з������һ��SegID
* ����˵���� �������:Seg_ID  UINT16_S    ��ǰ��SegID
*                         Dir  UINT8_S     ���з���
*             �������:nextSegId  UINT16_S*   ��һ��SEGID
* ����ֵ  �� 0:ʧ��1���ɹ�
*/
UINT8_S GetNextSegId(UINT16_S segId,UINT8_S dir,UINT16_S* nextSegId);
/*
* ���������� ��ѯ����Seg�������(����״̬δ֪)
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      segEndID        UINT16_S    �յ�SegID
*                      dir            UINT8_S     ���з���
*             �������:pSegId        UINT16_S*    SEGID����
*                      segIdNum        UINT8_S*      SEGID����    
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    

UINT8_S GetDirNoSwitchStutasSegArray(UINT16_S startSegId,UINT16_S endSegId,UINT8_S dir,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S segIdBuff[]);




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

UINT8_S GetDirSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S dir,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId);

/*
* ���������� ��ѯ����Seg��ľ���
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      startOffSet    UINT32_S      ���ƫ����
*                      segEndID        UINT16_S    �յ�SegID
*                      endOffSet        UINT32_S      �յ�ƫ����
*                      dir            UINT8_S     ���з���
*             �������:destDistance  UINT32_S*   Ŀ�����  
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    
UINT8_S GetDirBothSegPointDisPlus(UINT16_S segStartID,UINT32_S startOffSet,UINT16_S segEndID,UINT32_S endOffSet,UINT8_S dir,UINT32_S* destDistance);

/*
* ���������� ��ѯ����Seg��ľ���
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      startOffSet    UINT32_S      ���ƫ����
*                      segEndID        UINT16_S    �յ�SegID
*                      endOffSet        UINT32_S      �յ�ƫ����
*             �������:destDistance  UINT32_S*   Ŀ�����  
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    
UINT8_S GetNoDirBothSegPointDis(UINT16_S segStartID,UINT32_S startOffSet,UINT16_S segEndID,UINT32_S endOffSet,UINT32_S* destDistance);



/*
* ���������� ���µ����ʵʱ״̬
* ����˵���� �������:switchStatusBuff    UINT8_S[]     ����״̬��Ϣ
*                      buffLength        UINT16_S      ���鳤��
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    
UINT8_S UpdateSwitchStatus(const UINT8_S switchStatusBuff[],UINT16_S buffLength);

/*
* ���������� ��ȡ����״̬
* ����˵���� const UINT16_S switchId ����ID
* ����ֵ  �� >=0  ����״̬   0   ʧ��
*/    
UINT8_S GetSwitchStatus(const UINT16_S switchId);



/*
*�������ܣ�����ͨ����Ϣ������
*����˵������
*����ֵ��0ʧ�ܣ�1�ɹ�
*/
UINT8_S CalcCommAddInfo(void);









/*
* ���������� ���ݵ�ǰλ�ú�λ��,�õ���λ��.
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
UINT8_S GetNewLocCalcDis(const UINT16_S seg1,const UINT32_S offset1,const UINT8_S dir,const INT32_S distance,UINT16_S *outSeg,UINT32_S *outOffset,UINT8_S* outDir);

/*
* ���������� ����SEG�Լ�SEG��ǰ���ͺ��Ƿ��е���,���е������ӵ���ǰ����󷽵�SEGID�����ޣ�֮�䷵�ش�SEGID
* ����˵���� const UINT16_S segId,SEG��ID
*             UINT16_S* segBuff    SEG��ַ
* ����ֵ  �� 0: ��ȡʧ��
*            >0: SEGID����
*/
UINT8_S GetDirBothSegPointVectorDis(const UINT16_S startSegId,const UINT32_S startSegoffset,
                        const UINT16_S endSegId,const UINT32_S endSegoffset,const UINT16_S endDir,INT32_S* distance);
                        




/************************************************************************
* �������ܣ��˺����Ĺ����ǲ�ѯ��ǰGarde������Grade
* ��ڲ�����const UINT16_S curGradeID    ��ǰ�¶ȱ��
            const UINT8_S dir            �������з���        
* ���ڲ�����    ��
* ����ֵ��    UINT16_S findGradeID    ��ѯʧ��: 0xffff; ��ѯ�ɹ�: �������ڵ��¶�ID                                                              
************************************************************************/
UINT16_S FindAdjacentGradeID(const UINT16_S curGradeID, const UCHAR_S dir);
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
UINT8_S FindAdjacentACID(const UINT16_S currentACID,const UINT8_S dir,const UINT8_S startOrEnd,UINT8_S* axleSecNum,UINT16_S* axleSecIdBuff);

/*
* ���������� ��ȡSEGID�����ļ�������ID
* ����˵���� UINT16_S  segId��SegID
* ����ֵ  �� 0: ��ȡ����ʧ��
*            >0:�������θ���
*/
UINT8_S GetAxleSecAccordSegIdBuff(const UINT16_S* pSegId,const UINT8_S segNum,UINT16_S* pAxleSecId);

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
UINT8_S CheckNextPointOnDistance(const UINT16_S seg1,const UINT32_S offset1,const UINT8_S dir,const UINT32_S distance,UINT16_S *outSeg,UINT32_S *outOffset,UINT16_S *errorSwitchId);
/*
* ���������� ����SEG�Լ�SEG��ǰ���ͺ��Ƿ��е���,���е������ӵ���ǰ����󷽵�SEGID�����ޣ�֮�䷵�ش�SEGID
* ����˵���� const UINT16_S segId,SEG��ID
*             UINT16_S* segBuff    SEG��ַ
* ����ֵ  �� 0: ��ȡʧ��
*            >0: SEGID����
*/
UINT8_S GetSegBuffAccordSedIdAndSwitch(const UINT16_S segId,UINT16_S* segBuff,UINT8_S* findNum);
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
UINT8_S GetDirSegArrayAndLogicSec(UINT16_S segStartID,UINT32_S segStartOffset,UINT16_S segEndID,UINT32_S segEndOffset,UINT8_S dir,UINT8_S* logicNum,UINT16_S* logicId,UINT8_S* relateLogicNumBuff,BnfRelateLogicSecInfoStruct relateLogicInfo[][2]);

/*
* ���������� ��ѯ����Seg�������(����״̬δ֪)
* ����˵���� �������:segStartID    UINT16_S    ��ʼSegID
*                      segEndID        UINT16_S    �յ�SegID
*             �������:pSegId        UINT8_S*    SEGID����
*                      segIdNum        UINT8_S*      SEGID����    
* ����ֵ  �� 0:ʧ��1���ɹ�
*/    

UINT8_S GetNoDirNoSwitchStutasSegArray(UINT16_S segStartID,UINT16_S segEndID,UINT8_S includePoint,UINT8_S* segIdNum,UINT16_S* pSegId);

#ifdef __cplusplus
}
#endif

#endif
