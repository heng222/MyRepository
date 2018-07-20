
/********************************************************                                                                                                           
�� �� ���� ChangeConfigData.h  
��    �ߣ� ZC��
����ʱ�䣺 2015.04.18
������ �л�������������  
��ע�� ��  
********************************************************/ 

#ifndef CHANGE_CONFIG_DATA_H_
#define CHANGE_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ChangeDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

/*�л��������ݽṹ��*/
typedef struct ChangeLineSwitchStruct
{
	UINT16_S SwitchId;                             /*�л���·��Ӧ����ID*/
	UINT8_S SwitchNeedStatus;                      /*��Ӧ������Ҫ��״̬*/
}  ChangeLineSwitchStruct;

/*�л���·���ݽṹ��*/
typedef struct ChangeLineConfigDataStruct
{
	UINT16_S ChangeLineId;                          /*�л���·ID*/
	UINT16_S HandOverZcId;                          /*����·��Ӧ���ƽ�ZCid*/
	UINT16_S TakeOverZcId;                          /*����·��Ӧ�Ľӹ�ZCid*/
	UINT8_S ChangeDir;                              /*�л�����*/
	UINT16_S  ChangeLineStartLink;                  /*���л���·ʼ��Link���*/
	UINT32_S  ChangeLineStartOffset; 	            /*���л���·ʼ��Link��Ӧƫ����*/
	UINT16_S  ChangePointLink;                      /*����·��Ӧ���л�������link���*/
	UINT32_S  ChangePointOffset;                    /*����·��Ӧ���л�������linkƫ����*/
	UINT16_S  ChangeLineEndLink;                    /*���л���·�ն�Link���*/
	UINT32_S  ChangeLineEndOffset;                  /*���л���·�ն�Link��Ӧƫ����*/
	UINT16_S  RelevanceRouteId;                     /*����·��Ӧ�Ľ�·ID*/
	UINT8_S  SwitchNum;                             /*���л���·��Ӧ�ĵ�������*/
	ChangeLineSwitchStruct SwitchStruBuff[CHANGE_LINE_SWITCH_MAX];/*���л���·��Ӧ�ĵ�������*/
} ChangeLineConfigDataStruct;

typedef struct ChangeAreapObsStruct
{
	UINT16_S ObsId;                                /*�л������Ӧ�ϰ���Id*/
	UINT8_S ObsType;                               /*�л������Ӧ�ϰ�������*/
} ChangeAreapObsStruct;

typedef struct ChangeAreaBitTableStruct
{
	UINT16_S ObsId;                                /*�ϰ���ID*/
	UINT16_S StateBitIndex;                        /*�ϰ���״̬��Ӧ��λ*/
	UINT16_S LockBitIndex;                         /*�ϰ���������Ϣ��Ӧ��λ*/
    UINT8_S ChageDir;                              /* �л�����(ֻ��������ʹ��)*/
}ChangeBitTableStruct;

/*�л������������ݽṹ��*/  
typedef struct ChangeAreaConfigStruct
{
	UINT16_S LocalZcId;                                                               /*�����ZcId*/
	UINT16_S NextZcId;                                                                /*�л������Ӧ������ZcId*/
	UINT16_S ObsNum;                                                                  /*�������Ӧ���ϰ������*/
	ChangeAreapObsStruct ObsStruBuff[CHANGE_AREA_OBS_MAX];                            /*�������Ӧ���ϰ�����Ϣ*/
	UINT16_S RouteNum;                                                                /*��·��λ����*/
	ChangeBitTableStruct RouteBitStruBuff[CHANGE_AREA_ROUTE_MAX];                       /*��·��λ*/
	UINT16_S OverlapNum;                                                              /*����������λ����*/
	ChangeBitTableStruct OverlapBitStruBuff[CHANGE_AREA_OVERLAP_MAX];                   /*����������λ*/
	UINT16_S SignalNum;                                                               /*�źŻ���λ����*/
	ChangeBitTableStruct SignalBitStruBuff[CHANGE_AREA_SIGNAL_MAX];                     /*�źŻ���λ*/
	UINT16_S SwitchNum;                                                               /*������λ����*/
	ChangeBitTableStruct SwitchBitStruBuff[CHANGE_AREA_SWITCH_MAX];                     /*������λ*/
	UINT16_S PsdNum;                                                                  /*��������λ����*/
	ChangeBitTableStruct PsdBitStruBuff[CHANGE_AREA_PSD_MAX];                           /*��������λ*/
	UINT16_S EsbNum;                                                                  /*����ͣ����ť��λ����*/
	ChangeBitTableStruct EsbBitStruBuff[CHANGE_AREA_ESB_MAX];                           /*����ͣ����ť��λ*/
	UINT16_S DrButtonNum;                                                             /*�����۷���ť��λ����*/
	ChangeBitTableStruct DrButtonBitStruBuff[CHANGE_AREA_DRBUTTON_MAX];                 /*�����۷���ť��λ*/
	UINT16_S DrLampNum;                                                               /*�����۷�����λ����*/
	ChangeBitTableStruct DrLampBitStruBuff[CHANGE_AREA_DRLAMP_MAX];                     /*�����۷�����λ*/
	UINT16_S AcNum;                                                                   /*����������λ����*/
	ChangeBitTableStruct AcBitStruBuff[CHANGE_AREA_AC_MAX];                             /*����������λ*/
	UINT16_S LogicSectionNum;                                                         /*�߼�������λ����*/
	ChangeBitTableStruct LogicSectionBitStruBuff[CHANGE_AREA_LOGIC_MAX];              /*�߼�������λ*/	
} ChangeAreaConfigStruct;
	
/*************************************************
������:  GetChangeLineSum    
��������: ��ȡ�л���·����
����: void    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �л���·��ǰ����
*************************************************/
UINT16_S GetChangeLineSum(void);

/*************************************************
������:  GetChangeLineId    
��������: ��ȡָ�������±��Ӧ���л���·ID
����: const UINT16 bufIndex, �����±�    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �л���·ID      
*************************************************/
UINT16_S GetChangeLineId(const UINT16_S bufIndex);

/*************************************************
������:  GetChangeLineConfigBufIndex    
��������: ��ȡָ��ID�л���·������
����: const UINT16 changeLineId,�л���·ID
���: ��
����ֵ: CHANGE_LINE_SUM_MAX: ��ȡ����ʧ��
			>=0���������ɹ�
*************************************************/
UINT16_S GetChangeLineConfigBufIndex(const UINT16_S changeLineId);

/*************************************************
������:   GetChangeLineDir   
��������: ��ȡָ���л���·ID��Ӧ���л�����
����: const UINT16 changeLineId, �л���·ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �л�����      
*************************************************/
UINT8_S GetChangeLineDir(const UINT16_S changeLineId);

/*************************************************
������:    GetChangeLineHandOverZcId  
��������: ��ȡָ���л���·ID��Ӧ���ƽ�ZCid
����: const UINT16 changeLineId, �л���·ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �ƽ�ZCid      
*************************************************/
UINT16_S GetChangeLineHandOverZcId(const UINT16_S changeLineId);

/*************************************************
������:   GetChangeLineTakeOverZcId   
��������: ��ȡָ���л���·ID��Ӧ�Ľӹ�ZCid
����: const UINT16 changeLineId, �л���·ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �ӹ�ZCid      
*************************************************/
UINT16_S GetChangeLineTakeOverZcId(const UINT16_S changeLineId);

/*************************************************
������:   GetChangeLineStartLink   
��������: ��ȡָ���л���·ID��Ӧ�����link
����: const UINT16 changeLineId, �л���·ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ���link     
*************************************************/
UINT16_S GetChangeLineStartLink(const UINT16_S changeLineId);

/*************************************************
������:   GetChangeLineStartOffset   
��������: ��ȡָ���л���·ID��Ӧ�����offset
����: const UINT16 changeLineId, �л���·ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: offset      
*************************************************/
UINT32_S GetChangeLineStartOffset(const UINT16_S changeLineId);

/*************************************************
������:   GetChangeLineChangePointLink   
��������: ��ȡָ���л���·ID��Ӧ���л���link
����: const UINT16 changeLineId, �л���·ID  
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �л���link      
*************************************************/
UINT16_S GetChangeLineChangePointLink(const UINT16_S changeLineId);

/*************************************************
������:   GetChangeLineChangePointOffset   
��������: ��ȡָ���л���·ID��Ӧ���л���offset
����: const UINT16 changeLineId, �л���·ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: offset      
*************************************************/
UINT32_S GetChangeLineChangePointOffset(const UINT16_S changeLineId);

/*************************************************
������:   GetChangeLineEndLink   
��������: ��ȡָ���л���·ID��Ӧ���յ�link
����: const UINT16 changeLineId, �л���·ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �յ�Link      
*************************************************/
UINT16_S GetChangeLineEndLink(const UINT16_S changeLineId);

/*************************************************
������:  GetChangeLineEndOffset    
��������: ��ȡָ���л���·ID��Ӧ���յ�offset
����: const UINT16 changeLineId, �л���·ID   
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: offset      
*************************************************/
UINT32_S GetChangeLineEndOffset(const UINT16_S changeLineId);

/*************************************************
������:    GetChangeLineRelevanceRouteId  
��������: ��ȡָ���л���·ID��Ӧ�Ľ�·ID
����: const UINT16 changeLineId, �л���·ID 
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ��·ID      
*************************************************/
UINT16_S GetChangeLineRelevanceRouteId(const UINT16_S changeLineId);

/*************************************************
������:  GetChangeLineSwitchNum    
��������: ��ȡָ���л���·ID��Ӧ�ĵ�������
����: const UINT16 changeLineId, �л���·ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ��������     
*************************************************/
UINT8_S GetChangeLineSwitchNum(const UINT16_S changeLineId);

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
UINT8_S GetChangeLineSwitchStruct(const UINT16_S changeLineId,const UINT8_S switchStruBufSize, ChangeLineSwitchStruct switchStruBuff[]);

/*************************************************
������:  GetChangeAreaConfigSum    
��������: ��ȡ�л���������
����: void    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �л���·��ǰ����
*************************************************/
UINT16_S GetChangeAreaConfigSum(void);

/*************************************************
������: GetChangeAreaOfNextZcId     
��������: ��ȡָ�������±��Ӧ���л������Ӧ��ZCID
����: const UINT16 bufIndex, �����±�    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �л���·ID      
*************************************************/
UINT16_S GetChangeAreaOfNextZcId(const UINT16_S bufIndex);

/*************************************************
������:   GetChangeAreaConfigBufIndex   
��������: ��ȡָ��ID�л�����������
����: const UINT16 nextZcId,����ZCid
        const UINT16_S outputZcId,�����ZcId
���: ��
����ֵ:CHANGE_AREA_SUM_MAX: ��ȡ����ʧ��
		>=0: ���������ɹ�
*************************************************/
UINT16_S GetChangeAreaConfigBufIndex(const UINT16_S outputZcId ,const UINT16_S nextZcId);


/*************************************************
������:    GetChangeAreaObsNum  
��������: ��ȡָ��ID�������ϰ�������
����: const UINT16 nextZcId,����ZCid
        const UINT16_S outputZcId,�����ZcId
���: ��
����ֵ:0: ��ȡ����ʧ��
		>0: ��ѯ�ɹ�
*************************************************/
UINT16_S GetChangeAreaObsNum(const UINT16_S outputZcId ,const UINT16_S nextZcId);

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
UINT8_S GetChangeAreapObsStructBuff(const UINT16_S outputZcId ,const UINT16_S nextZcId,const UINT16_S bufSize,ChangeAreapObsStruct obsStruBuff[]);


/*************************************************
������:    GetAppointObsInChangeArea  
��������: ��ȡָ��ID�����͵��ϰ����Ƿ������л�����
����: const UINT16 obsId �ϰ���ID
    const UINT8_S obsType �ϰ�������
���: ��
����ֵ:0: ��ȡ����ʧ�ܣ��������л����������ZC��
		1: ��ѯ�ɹ��������л����������ZC��
*************************************************/
UINT8_S GetAppointObsInChangeArea(const UINT16_S obsId,const UINT8_S obsType);

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
UINT8_S GetObsBitTableNum(const UINT16_S outputZcId,const UINT16_S nZcId, const UINT8_S obsType, UINT16_S *pObsNum);

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
ChangeBitTableStruct* GetObsBitTableStrInfo(const UINT16_S outputZcId,const UINT16_S nZcId,const UINT8_S obsType);

/*************************************************
������:   GetLineDeviceBelongZcId    
��������: ��ȡ��·�豸����ZC��Ϣ
����: ��   
���: ��
����ֵ: 0: ��ȡʧ��
		>0: ����ZCID      
*************************************************/
UINT16_S GetLineDeviceBelongZcId(const UINT16_S devId,const UINT8_S devType);


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
UINT8_S GetObsBitTableNumOfIndex(const UINT8_S changeAreaIndex, const UINT8_S obsType, UINT16_S *pObsNum);

/*************************************************
������:  GetObsBitTableStrInfoOfIndex    
��������: ��ȡָ�����͵��ϰ�������λ��Ϣ�ṹ���±�������
����: const UINT8 changeAreaIndex �л������±�
        const UINT8_S obsType �ϰ�������
���: ��
����ֵ:NULL: ��ȡ����ʧ��
		!NULL: ��ѯ�ɹ�
*************************************************/
ChangeBitTableStruct* GetObsBitTableStrInfoOfIndex(const UINT8_S changeAreaIndex,const UINT8_S obsType);

#ifdef __cplusplus
}
#endif

#endif
