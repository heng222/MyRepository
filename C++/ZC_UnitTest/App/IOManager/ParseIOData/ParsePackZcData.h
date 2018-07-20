/************************************************************************
*
* �ļ���   ��  ParsePackZcData.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �������������ZC���ݹ���
* ��  ע	��  ��
*
************************************************************************/

#ifndef PARSE_PACK_ZC_DATA_H_
#define PARSE_PACK_ZC_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ParsePackIODefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*ZC������ZC��̬���ݽṹ��*/
	typedef struct ZcAndNzcIODataStruct
	{
		UINT8_S ZcId;                                        /*ͨ�ŵ�Id*/
		UINT16_S ValueBuffLen;                                /*ͨ�ŵ�Buf����*/
		UINT8_S ValueBuff[ZC_NZC_COM_BYTE_SUM_MAX];           /*ͨ�ŵ�Bufֵ*/
	}ZcAndNzcIODataStruct;

	/*
	* ���������� ��ȡ����ZC����Zc���������
	* ����˵���� void
	* ����ֵ  ��  SINGLE_TYPE_COMM_TARGET_SUM_MAX: ʧ��
	*			>0: ����            
	*/
	UINT8_S GetNZcToZcCurSum(void);

	/*
	* ������������ȡ����ZC��������������±��Ӧ��ZCID
	* ����˵���� const UINT8 nZcIdOfIndex
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT16_S GetNZcToZcBuffIndexOfNZcId(const UINT8_S nZcIdOfIndex);

	/*
	* ������������ȡ����ZC��������������±��Ӧ�����ݳ���
	* ����˵���� const UINT8 nZcIdOfIndex
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT16_S GetNZcToZcIdDataBufLen(const UINT8_S nZcIdOfIndex);

	/*
	* ���������� ��ȡNZc����Zc��Id��Ӧ������Ϣ
	* ����˵���� const UINT8 nZcIdOfIndex
	* ����ֵ  �� NULL: ʧ��
	*			 !NULL: �ɹ�      
	*/
	UINT8_S* GetNZcToZcBufDataOfIndex(const UINT8_S nZcIdOfIndex);

	/*
	* ���������� ����NZC����ĵ�֡����
	* ����˵���� const UINT8_S dataBuff[], ���ݻ�����
	*            const UINT16_S dataLength, ���ݳ���
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseNzcToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength);

    /*
    * ���������� ����ZC����ĵ�֡���ݺϷ��Լ��
    * ����˵���� const UINT8_S dataBuff[], ���ݻ�����
    *            const UINT16_S dataLen, ���ݳ���
    * ����ֵ  �� 0: �Ϸ��Լ��ʧ��
    *			 1: �Ϸ��Լ��ɹ�      
    */
	UINT8_S NzcInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen);

	/*
	* ���������� ��ȡZC�����NZc���������
	* ����˵���� void
	* ����ֵ  �� SINGLE_TYPE_COMM_TARGET_SUM_MAX: ʧ��
	*			>0: ����      
	*/
	UINT8_S GetZcToNZcCurSum(void);

	/*
	* ������������ȡ���������ZC���������±��Ӧ�����ݳ���
	* ����˵���� const UINT8 nZcIdOfIndex
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT16_S GetZcToNZcIdDataBufLen(const UINT8_S nZcIdOfIndex);

	/*
	* ���������� ��ȡ���������ZC���������±��Ӧ��������Ϣ
	* ����˵���� const UINT8 nZcIdOfIndex
	* ����ֵ  �� NULL: ʧ��
	*			 !NULL: �ɹ�         
	*/
	UINT8_S* GetZcToNZcBufDataOfIndex(const UINT8_S nZcIdOfIndex);

    /*
    * ���������� ������ZC����
    * ����˵���� const UINT8* dataBuf,���ݻ���
    *            const UINT16_S dataLength,���ݳ���
    *            const UINT16_S destId, Ŀ��ID   
    * ����ֵ  �� RETURN_ERROR:������ʧ��
    *			 RETURN_SUCCESS:�����ݳɹ�      
    */
	UINT8_S PackZcToNzcFrameData(const UINT8_S* dataBuf,const UINT16_S dataLength,const UINT16_S destId);

	/*
	* ���������� ��ձ�������������ZC������Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleNZcInputData(void);

	/*
	* ���������� ��ձ�������������ZC�����Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleNZcOutputData(void);

#ifdef __cplusplus
}
#endif
#endif
