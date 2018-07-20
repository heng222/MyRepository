/********************************************************                                                                                                           
�� �� ���� OverlapConfigData.h  
��    �ߣ� ZC��
����ʱ�䣺 2015.04.18
������ ����������������  
��ע�� ��  
********************************************************/ 

#ifndef OVERLAP_CONFIG_DATA_H_
#define OVERLAP_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "OverlapDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


/*�����������ݽṹ��*/
typedef struct OverlapConfigDataStruct
{
	UINT16_S OverlapId;                     /*��������ID*/
	UINT8_S BelongCiId;                     /*��������ID*/
	UINT8_S BelongZcId;                     /*����ZCID*/
	UINT8_S ChangeAttribute;                /*������������(��־�Ƿ�����ĳ����������)*/
	UINT8_S SwitchAttribute;                /*�������ε�������(��־�Ƿ���е���)*/
	UINT8_S ContainAcNum;                   /*�������ΰ����ļ�����������*/
	UINT16_S ContainAcBuff[OVERLAP_OF_AC_SUM_MAX];  /*�������ΰ����ļ�����������*/
} OverlapConfigDataStruct;

/*************************************************
������:   GetOverlapSum   
��������: ��ȡ�������ι�������
����: void    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: �������ε�ǰ����
*************************************************/
UINT16_S GetOverlapSum(void);

/*************************************************
������:   GetOverlapId   
��������: ��ȡָ�������±��Ӧ�ı�������ID
����: const UINT16 bufIndex, �����±�  
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ��������ID      
*************************************************/
UINT16_S GetOverlapId(const UINT16_S bufIndex);

/*************************************************
������:   GetOverlapConfigBufIndex   
��������: ��ȡָ��ID��������������
����: const UINT16 overlapId,��������ID
���: ��
����ֵ:  OVERLAP_SUM_MAX;��ȡ����ʧ��
			>0;���������ɹ�
*************************************************/
UINT16_S GetOverlapConfigBufIndex(const UINT16_S overlapId);

/*************************************************
������:   GetOverlapBelongCiId   
��������: ��ȡָ��IDվ̨����������������ID
����: const UINT16 overlapId,��������ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ��������ID      
*************************************************/
UINT8_S GetOverlapBelongCiId(const UINT16_S overlapId);

/*************************************************
������:   GetOverlapBelongZcId   
��������: ��ȡָ��ID������������ZC��ID
����: const UINT16 overlapId, ��������ID    
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ����ZcID      
*************************************************/
UINT8_S GetOverlapBelongZcId(const UINT16_S overlapId);

/*************************************************
������:   GetOverlapChangeAttribute   
��������: ��ȡָ��ID�������ι�����������
����: const UINT16 overlapId, ��������ID   
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ��ȡ�ɹ�      
*************************************************/
UINT16_S GetOverlapChangeAttribute(const UINT16_S overlapId);

/*************************************************
������:    GetOverlapSwitchAttribute  
��������: ��ȡָ��ID�������ε�������
����: const UINT16 overlapId, ��������ID   
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ��ȡ�ɹ�      
*************************************************/
UINT16_S GetOverlapSwitchAttribute(const UINT16_S overlapId);

/*************************************************
������:  GetOverlapContainAcNum    
��������: ��ȡָ��ID�������ΰ���������������
����: const UINT16 overlapId, ��������ID     
���: ��
����ֵ: 0: ��ȡ����ʧ��
		>0: ��ȡ����      
*************************************************/
UINT8_S GetOverlapContainAcNum(const UINT16_S overlapId);

/*************************************************
������:   GetOverlapContainAcBuff   
��������: ��ȡָ��ID�������ΰ���������������
����: const UINT16 overlapId, ��������ID    
        const UINT8_S bufSzie, ��������С
        UINT16_S containAcIdBuff[]���������
���: UINT16_S containAcIdBuff[] �����ļ�����������
����ֵ: 0: ��ȡ����ʧ��
		>0: ��ȡ������������      
*************************************************/
UINT8_S GetOverlapContainAcBuff(const UINT16_S overlapId,const UINT8_S bufSzie,UINT16_S containAcIdBuff[]);

#ifdef __cplusplus
}
#endif

#endif
