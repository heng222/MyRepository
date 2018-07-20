/************************************************************************
*
* �ļ���   ��  TsrStatusData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��ʱ����״̬����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef TSR_STATUS_DATA_H_
#define TSR_STATUS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "TsrDefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*���嵥����ʱ������Ϣ*/
	typedef struct SingleTsrDataStruct
	{
		UINT8_S  Speed;                                          /*��ʱ������ֵ(��λ��km/h)*/
		UINT8_S  SectionNum;                                     /*��ʱ������������߼���������*/
		UINT16_S  SectionIdBuff[SINGLE_TSR_SECTION_SUM_MAX];      /*��ʱ������������߼�����ID*/
	}SingleTsrDataStruct;


	/*��ʱ���ٽṹ����Ϣ*/
	typedef struct TsrDataStruct
	{
		UINT16_S  BelongZcId;                                 /*��ʱ��������ZC*/
		UINT8_S  TsrNum;                                      /*��ʱ��������*/
		SingleTsrDataStruct  SingleTsrDataStru[SINGLE_ZC_TSR_SUM_MAX];    /*����ZC��Χ�ڵ���ʱ�������ݽṹ*/
	}TsrDataStruct;
	
	/*
	* ���������� ��ȡ��ZC����Χ�ڵ�ǰ��ʱ������������
	*	        ����������ZC���͹������л������ڵ���ʱ���٣�
	* ����˵���� void    
	* ����ֵ  �� TSR_BUFF_SUM_MAX: ��ȡ����ʧ��
	*			>=0: ��ǰZC��������
	*/
	UINT16_S GetTsrOfZcSum(void);

	/*
	* ���������� ��ȡָ�������±��Ӧ������ZCID
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ZCID      
	*/
	UINT16_S GeTsrOfBelongZcId(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ�������±��Ӧ����ʱ������Ϣ
	* ����˵���� const UINT16 bufIndex, �����±�    
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*			!NULL: ��Ϣ      
	*/
	TsrDataStruct* GeTsrDataStructOfIndex(const UINT16_S bufIndex);

	/*
	* ���������� ��ȡָ��ZCID��ʱ�����±�
	* ����˵���� const UINT16 zcId,zcID
	* ����ֵ  �� TSR_BUFF_SUM_MAX; ��ȡ����ʧ��
	*			 >0;���������ɹ�
	*/
	UINT8_S GeZcIdOfTsrBufIndex(const UINT16_S zcId);

	/*
	* ���������� ��ȡָ��ZCID��ʱ��������
	* ����˵���� const UINT16 zcId,zcID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ������Ϣ     
	*/
	UINT8_S GetZcIdOfTsrNum(const UINT16_S zcId);

	/*
	* ���������� ����ָ��ZC�±���ʱ��������
	* ����˵���� const UINT8 tsrOfZcBufIndex,��ʱ���ٶ�Ӧ��ZC�±� 
	*            const UINT8_S tsrNum,��ʱ��������
	* ����ֵ  �� 0: ʧ��
	*			>0: �ɹ�     
	*/
	UINT8_S SetZcIdOfTsrNum(const UINT8_S tsrOfZcBufIndex,const UINT8_S tsrNum);

	/*
	* ���������� ��ȡָ��ZCID��Ӧ��ĳ���±��µ���ʱ���ٶ�Ӧ���ٶ�ֵ
	* ����˵���� const UINT16 zcId, ZCID
	*	         const UINT16_S singleBufIndex buf�±�   
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ĳ����ʱ������Ϣ(���߼�����ID����Ϊ����ֵ)      
	*/
	UINT8_S GetSingleTsrDataOfSpeed(const UINT16_S zcId,const UINT16_S singleBufIndex);

	/*
	* ���������� ����ָ��ZCID��Ӧ��ĳ���±��µ���ʱ���ٶ�Ӧ���ٶ�ֵ
	* ����˵���� const UINT8 tsrOfZcBufIndex,�洢��ʱ���ٹ�����ZCid��Ӧ�±�
	*	         const UINT16_S singleBufIndex,����ZC��ʱ����buf�±�
	*            const UINT16_S speed,��ʱ�����ٶ�
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ĳ����ʱ������Ϣ(���߼�����ID����Ϊ����ֵ)      
	*/
	UINT8_S SetSingleTsrDataOfSpeed(const UINT8_S tsrOfZcBufIndex,const UINT16_S singleBufIndex, const UINT16_S speed);

	/*
	* ���������� ��ȡָ��ZCID��Ӧ��ĳ���±�����ʱ���ٶ�Ӧ���߼���������
	* ����˵���� const UINT16 zcId, ZCID
	*	         const UINT16_S singleBufIndex buf�±�   
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			>0: ����      
	*/
	UINT8_S GetSingleTsrDataOfSectionNum(const UINT16_S zcId,const UINT16_S singleBufIndex);

	/*
	* ���������� ��ȡָ��ZCID��Ӧ��ĳ���±��µ���ʱ���ٶ�Ӧ���߼�����buff
	* ����˵���� const UINT16 zcId, ZCID
	*			 const UINT16_S bufIndex buf�±�   
	*			 const UINT8_S bufSize,�����С
	*            UINT16_S sectionIdBuff[],�������
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 1: ��ȡ�ɹ�      
	*/
	UINT8_S GetSingleTsrDataOfSectionBuff(const UINT16_S zcId,const UINT16_S singleBufIndex,const UINT8_S bufSize,UINT16_S sectionIdBuff[]);

	/*
	* ���������� ����ָ��ZCID��Ӧ��ĳ���±��µ���ʱ���ٵ��߼�����buff
	* ����˵���� const UINT8 tsrOfZcBufIndex,�洢��ʱ���ٹ�����ZCid��Ӧ�±�
	*	         const UINT16_S singleBufIndex,����ZC��ʱ����buf�±�  
	*            const UINT8_S sectionNum,���õ���ʱ��������
	*            const UINT16_S sectionIdBuff[],���õ���ʱ���ٶ�Ӧ���߼�����Id����
	* ����ֵ  �� 0: ��������ʧ��
	*			 1: �������ݳɹ�      
	*/
	UINT8_S SetSingleTsrDataOfSectionInfo(const UINT8_S tsrOfZcBufIndex,const UINT8_S singleBufIndex,const UINT8_S sectionNum,const UINT16_S sectionIdBuff[]);

	/*
	* ���������� ������ʱ���ٶ�Ӧ��ZC�±�
	* ����˵���� const UINT16 zcId, zcId    
	* ����ֵ  �� 0: ����ʧ��
	*			>0: ���óɹ�      
	*/
	UINT8_S AplyTsrIndexOfZcId(const UINT16_S zcId);

#ifdef __cplusplus
}
#endif

#endif
