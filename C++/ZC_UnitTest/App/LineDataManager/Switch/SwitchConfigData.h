/************************************************************************
*
* �ļ���   ��  SwitchConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����������ݹ���
* ��  ע   ��  ��
*
************************************************************************/
#ifndef SWITCH_CONFIG_DATA_H_
#define SWITCH_CONFIG_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "SwitchDefine.h"

#ifdef __cplusplus
extern "C" {
#endif


	/*�������ݽṹ��*/
	typedef struct SwitchConfigDataStruct
	{
		UINT16_S SwitchId;                      /*����ID*/
		UINT8_S BelongCiId;                     /*��������ID*/
		UINT8_S BelongZcId;                     /*����ZCID*/
		UINT8_S ChangeAttribute;           /*������������(��־�Ƿ�����ĳ����������)*/
		UINT8_S SwitchPosition;                 /*����λ��(��־�õ���λ������)*/
	} SwitchConfigDataStruct;

	/*
	* ���������� ��ȡ�����������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ǰ����
	*/
	UINT16_S GetSwitchSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ�ĵ���ID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ID      
	*/
	UINT16_S GetSwitchId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ��ID����������
	* ����˵���� const UINT16 switchId,����ID
	* ����ֵ  �� SWITCH_SUM_MAX; ��ȡ����ʧ��
	*			 >0; ���������ɹ�
	*/
	UINT16_S GetSwitchConfigBufIndex(const UINT16_S switchId);

	/*
	* ���������� ��ȡָ��IDվ̨������������ID
	* ����˵���� const UINT16 switchId,����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT8_S GetSwitchBelongCiId(const UINT16_S switchId);

	/*
	* ���������� ��ȡָ��ID��������ZC��ID
	* ����˵���� const UINT16 switchId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZcID      
	*/
	UINT8_S GetSwitchBelongZcId(const UINT16_S switchId);

	/*
	* ���������� ��ȡָ��ID��������������
	* ����˵���� const UINT16 switchId, ����ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT16_S GetSwitchChangeAttribute(const UINT16_S switchId);

	/*
	* ���������� ��ȡָ��ID����λ������
	* ����˵���� const UINT16 switchId, ����ID     
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��ȡ�ɹ�      
	*/
	UINT16_S GetSwitchPosition(const UINT16_S switchId);

#ifdef __cplusplus
}
#endif

#endif
