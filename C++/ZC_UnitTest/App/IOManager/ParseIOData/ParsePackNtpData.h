/************************************************************************
*
* �ļ���   ��  ParsePackNtpData.h
* ����ʱ�� ��  2014.04.14
* ����     ��  ZC��
* �������� ��  �������Ntp���ݹ���
* ��  ע	��  ��
*
************************************************************************/

#ifndef PARSE_PACK_NTP_DATA_H_
#define PARSE_PACK_NTP_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ParsePackIODefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*ZC��Ntp��̬���ݽṹ��*/
	typedef struct ZcAndNtpIODataStruct
	{
		UINT8_S NtpId;                                       /*ͨ�ŵ�NtpId*/
		UINT16_S ValueBuffLen;                                /*ͨ�ŵ�Buf����*/
		UINT8_S ValueBuff[ZC_NTP_COM_BYTE_SUM_MAX];           /*ͨ�ŵ�Bufֵ*/
	}ZcAndNtpIODataStruct;

	/*
	* ���������� ��ȡNtp�����ZC�����ݳ���
	* ����˵���� ��
	* ����ֵ  �� 0: ��ȡʧ��
	*			 >0: ���ݳ���      
	*/
	UINT16_S GetNtpToZcDataLen(void);

	/*
	* ���������� ��ȡNtp�����ZC��������Ϣ
	* ����˵���� ��
	* ����ֵ  ��  NULL: ��ȡʧ��
	*			 !NULL: ��ȡ�ɹ�       
	*/
	UINT8_S* GetNtpToZcDataBuff(void);

	/*
	* ���������� ��ȡZC�����Ntp�����ݳ���
	* ����˵���� ��
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 >0: ���ݳ���      
	*/
	UINT16_S GetZcToNtpDataLen(void);

	/*
	* ���������� ��ȡZC�����Ntp��������Ϣ
	* ����˵���� ��
	* ����ֵ  �� NULL: ��ȡʧ��
	*			 !NULL: ��ȡ�ɹ�       
	*/
	UINT8_S* GetZcToNtpDataBuff(void);

	/*
	* ���������� ����Ntp����ĵ�֡����
	* ����˵���� const UINT8_S dataBuff[], ���ݻ�����
	*            const UINT16_S dataLength, ���ݳ���
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseNtpToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength);

    /*
    * ���������� ��Ntp֡����
    * ����˵���� UINT8* dataBuff,��������   
    *            const UINT16_S dataLen,���ݳ���
    *            const UINT16_S commNtpId,ͨ�ŵ�NtpId(Ԥ��)
    * ����ֵ  �� 0:������ʧ��
    *			 1:�����ݳɹ�      
    */
	UINT8_S PackZcToNtpFrameData(const UINT8_S* dataBuff,const UINT16_S dataLen,const UINT16_S commNtpId);

	/*
	* ���������� ��ձ��������������Ntp������Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleNtpInputData(void);

	/*
	* ���������� ��ձ��������������Ntp������Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleNtpOutputData(void);

#ifdef __cplusplus
}
#endif
#endif
