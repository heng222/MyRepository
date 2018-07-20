/************************************************************************
*
* �ļ���   ��  ParsePackAtsData.h
* ����ʱ�� ��  2014.04.14
* ����     ��  ZC��
* �������� ��  �������ATS���ݹ���
* ��  ע   ��  ��
*
************************************************************************/

#ifndef PARSE_PACK_ATS_DATA_H_
#define PARSE_PACK_ATS_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ParsePackIODefine.h"

#ifdef __cplusplus
extern "C" {
#endif
	/*ZC��ATS��̬���ݽṹ��*/
	typedef struct ZcAndAtsIODataStruct
	{
		UINT8_S AtsId;                                       /*ͨ�ŵ�AtsId*/
		UINT16_S ValueBuffLen;                                /*ͨ�ŵ�Buf����*/
		UINT8_S ValueBuff[ZC_ATS_COM_BYTE_SUM_MAX];           /*ͨ�ŵ�Bufֵ*/
	}ZcAndAtsIODataStruct;

	/*
	* ������������ȡ�����ATS���������±��Ӧ�����ݳ���
	* ����˵���� ��
	* ����ֵ  �� ZC��ATS�����ݳ���      
	*/
	UINT16_S GetZcToAtsIdDataBufLen(void);

	/*
	* ���������� ��ȡ�����Ats���������±��Ӧ��������Ϣ
	* ����˵���� ��
	* ����ֵ  �� ZC��ATS��������׵�ַ     
	*/
	UINT8_S* GetZcToAtsDataBuff(void);

	/*
	* ���������� ��ZC��ATS����
	* ����˵���� const UINT8* dataBuf,��������   
	*            const UINT16_S dataLen,���ݳ���
	*            const UINT16_S commAtsId,ͨ�ŵ�AtsId
	* ����ֵ  �� 0:������ʧ��
	*			 1:�����ݳɹ�      
	*/
	UINT8_S PackZcToAtsFrameData(const UINT8_S* dataBuf,const UINT16_S dataLen);/*-bye- ɾ���˵���������*/

	/*
	* ���������� ��ձ�����Ats�����Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleAtsOutputData(void);

#ifdef __cplusplus
}
#endif

#endif

