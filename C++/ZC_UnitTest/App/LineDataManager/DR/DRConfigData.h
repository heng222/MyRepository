/************************************************************************
*
* �ļ���   ��  DRConfigData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �����۷���������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef DR_CONFIG_DATA_H_
#define DR_CONFIG_DATA_H_


#include "DRDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif


	/*DR��ť�������ݽṹ��*/
	typedef struct DRButtonConfigDataStruct
	{
		UINT16_S DRButtonId;                /*�����۷���ťID*/
		UINT8_S BelongCiId;                 /*��������ID*/
		UINT8_S BelongZcId;                 /*����ZCID*/
		UINT8_S ChangeAttribute;       /*������������(��־�Ƿ�����ĳ����������)*/
	} DRButtonConfigDataStruct;

	/*DR���������ݽṹ��*/
	typedef struct DRLampConfigDataStruct
	{
		UINT16_S DRLampId;                  /*�����۷���ID*/
		UINT8_S BelongCiId;                 /*��������ID*/
		UINT8_S BelongZcId;                 /*����ZCID*/
		UINT8_S ChangeAttribute;       /*������������(��־�Ƿ�����ĳ����������)*/
	} DRLampConfigDataStruct;


	/*
	* ���������� ��ȡ�����۷���ť��������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �����۷���ť��ǰ����
	*/
	UINT16_S GetDRButtonSum(void);

	/*
	* ���������� ��ȡ�����۷��ƹ�������
	* ����˵���� void    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �����۷��Ƶ�ǰ����
	*/
	UINT16_S GetDRLampSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ�������۷���ťID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �����۷���ťID      
	*/
	UINT16_S GetDRButtonId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ�������±��Ӧ�������۷�����ID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: �����۷���ID    
	*/
	UINT16_S GetDRLampId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ�������۷���ťID������
	* ����˵���� const UINT16 drButtonId, �����۷���ťID
	* ����ֵ  �� DR_BUTTON_LOCAL_SUM_MAX: ��ȡ����ʧ��
	*			<DR_BUTTON_LOCAL_SUM_MAX: ���ҳɹ�
	*/
	UINT16_S GetDRButtonConfigBufIndex(const UINT16_S drButtonId);

	/*
	* ���������� ��ȡָ�������۷���ID������
	* ����˵���� const UINT16 drLampId, �����۷���ID
	* ����ֵ  �� DR_LAMP_LOCAL_SUM_MAX: ��ȡ����ʧ��
	*			<DR_LAMP_LOCAL_SUM_MAX: ���ҳɹ�
	*/
	UINT16_S GetDRLampConfigBufIndex(const UINT16_S drLampId);

	/*
	* ���������� ��ȡָ��ID�����۷���ť��������ID
	* ����˵���� const UINT16 drButtonId ,�����۷���ťID   
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT8_S GetDRButtonBelongCiId(const UINT16_S drButtonId);

	/*
	* ���������� ��ȡָ��ID�����۷�����������ID
	* ����˵���� const UINT16 drLampId  ,�����۷���ID 
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ��������ID      
	*/
	UINT8_S GetDRLampBelongCiId(const UINT16_S drLampId);

	/*
	* ���������� ��ȡָ��ID�����۷���ť����ZCID
	* ����˵���� const UINT16 drButtonId ,�����۷���ťID
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZC��ID      
	*/
	UINT8_S GetDRButtonBelongZcId(const UINT16_S drButtonId);

	/*
	* ���������� ��ȡָ��ID�����۷�������ZCID
	* ����˵���� const UINT16 drLampId,�����۷���ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����ZC��ID      
	*/
	UINT8_S GetDRLampBelongZcId(const UINT16_S drLampId);

	/*
	* ���������� ��ȡָ��ID�����۷���ť������������
	* ����˵���� const UINT16 drButtonId, �����۷���ťID    
	* ����ֵ  �� 0: ������
	*			 FLAG_SET: ����      
	*/
	UINT8_S GetDRButtonChangeAttribute(const UINT16_S drButtonId);

	/*
	* ���������� ��ȡָ��ID�����۷��ƹ�����������
	* ����˵���� const UINT16 drLampId, �����۷���ID    
	* ����ֵ  �� 0: ������
	*			 FLAG_SET: ����      
	*/
	UINT8_S GetDRLampChangeAttribute(const UINT16_S drLampId);

#ifdef __cplusplus
}
#endif

#endif
