/********************************************************
* 
* �� �� ���� DmuCommStructDefine.h 
* ��    �ߣ� ���� 
* ����ʱ�䣺 2016-09-03  
* ���������� ������ѯ�����ṹ�嶨��ͷ�ļ� 
* ��    ע�� �� 
* 
********************************************************/ 

#ifndef DMU_COMM_STRUCTDEFINE_H_
#define DMU_COMM_STRUCTDEFINE_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif
/*����״̬��Ϣ*/
typedef struct _SwitchStatusInfoStruct
{
    UINT16_S  switchId;                        /*����ID*/
    UINT8_S   switchStatus;                    /*����״̬*/    
}SwitchStatusInfoStruct;

/*��ʱ���ٽṹ��*/
typedef struct TmpLimitSpeedInfoStruct
{
    UINT16_S limitSpeed;                        /*����ֵ*/
    UINT16_S startSegId;                        /*���SEGID*/
    UINT32_S startOffSet;                        /*���Offset*/
    UINT16_S endSegID;                        /*�յ�SEGiD*/
    UINT32_S endSegOffset;                    /*�յ�Offset*/
}TmpLimitSpeedInfoStruct;

/*MA�е��ϰ�����Ϣ�ṹ��*/
typedef struct obstInfoStruct
{
    UINT8_S  type;                /*�ϰ�������*/
    UINT16_S obstId;                /*�ϰ���ID*/
    UINT16_S segId;                /*�ϰ�������SEGID*/
    UINT32_S    offSet;                /*�ϰ�������SEG��ƫ����*/
    UINT8_S    status;                /*�ϰ��ﵱǰ״̬*/
    UINT8_S    realStatus;            /*�ϰ���ʵ��״̬*/
}ObstInfoStruct;

#ifdef __cplusplus
}
#endif

#endif
