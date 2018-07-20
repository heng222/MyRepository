/************************************************************************
*
* �ļ���   ��  ParsePackTrainData.h
* ����ʱ�� ��  2015.04.14
* ����     ��  ZC��
* �������� ��  ��������г����ݹ���
* ��  ע	��  ��
*
************************************************************************/

#ifndef PARSE_PACK_TRAIN_DATA_H_
#define PARSE_PACK_TRAIN_DATA_H_

#include "../../../Common/CommonTypes.h"
#include "ParsePackIODefine.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*ZC�복��ATP��̬���ݽṹ��*/
	typedef struct ZcAndTrainIODataStruct
	{
		UINT8_S TrainId;                                       /*ͨ�ŵ�Id*/
		UINT16_S ValueBuffLen;                                  /*ͨ�ŵ�Buf����*/
		UINT8_S ValueBuff[ZC_TRAIN_COM_BYTE_SUM_MAX];           /*ͨ�ŵ�Bufֵ*/
	}ZcAndTrainIODataStruct;

	/*
	* ���������� ��ȡ����ATP������������
	* ����˵���� void
	* ����ֵ  �� SIZE_MAX_LINE_TRAIN+1: ʧ��
	*			>=0: ����      
	*/
	UINT8_S GetTrainToZcCurSum(void);

	/*
	* ������������ȡ����ATP����Zc��Id��Ӧ�г�ID
	* ����˵���� const UINT8 trainIdOfIndex
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT16_S GetTrainToZcBuffIndexOfTrainId(const UINT8_S trainIdOfIndex);

	/*
	* ������������ȡ����ATP����Zc��Id��Ӧ���ݳ���
	* ����˵���� const UINT8 ciIdOfIndex
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT16_S GetTrainToZcIdDataBufLen(const UINT8_S trainIdOfIndex);

	/*
	* ���������� ��ȡ����ATP����Zc��Id��Ӧ������Ϣ
	* ����˵���� const UINT8 trainIdOfIndex
	* ����ֵ  �� NULL: ʧ��
	*			 !NULL: �ɹ�       
	*/
	UINT8_S* GetTrainToZcBufDataOfIndex(const UINT8_S trainIdOfIndex);

	/*
	* ���������� ��������ATP����ĵ�֡����
	* ����˵���� const UINT8_S dataBuff[], ���ݻ�����
	*            const UINT16_S dataLength, ���ݳ���
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseTrainToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength);

	/*
	* ���������� У�鳵��ATP�����������ȷ��
	* ����˵���� const UINT8_S dataBuff[],��������   
	*            const UINT16_S dataLen,���ݳ���
	* ����ֵ  �� 0:�Ϸ���У��ʧ��
	*			 1:�Ϸ���У��ɹ�      
	*/
	UINT8_S TrainInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen);

	/*
	* ���������� ��ȡZC�������Atp���������
	* ����˵���� void
	* ����ֵ  �� SIZE_MAX_LINE_TRAIN+1,ʧ��
	*			 1: �ɹ�      
	*/
	UINT8_S GetToTrainCurSum(void);

	/*
	* ���������� ��ȡZC�������ATP��Id��Ӧ���ݳ���
	* ����˵���� const UINT8 trainIdOfIndex
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT16_S GetToTrainIdDataBufLen(const UINT8_S trainIdOfIndex);

	/*
	* ���������� ��ȡZC�������Atp��Id�±��Ӧ������
	* ����˵���� const UINT8 trainIdOfIndex
	* ����ֵ  �� NULL: ʧ��
	*			 !NULL: �ɹ�      
	*/
	UINT8_S* GetToTrainBufDataOfIndex(const UINT8_S trainIdOfIndex);

	/*
	* ���������� �鳵��ATP����
	* ����˵���� const UINT8* dataBuff,���ݻ���
	*            const UINT16_S dataLength,���ݳ���
	*            const UINT16_S destId, Ŀ��ID   
	* ����ֵ  �� 0:������ʧ��
	*			 1:�����ݳɹ�      
	*/
	UINT8_S PackZcToTrainFrameData(const UINT8_S* dataBuff,const UINT16_S dataLength,const UINT16_S destId);

	/*
	* ���������� ��ձ��������г���Atp������Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleTrainInputData(void);

	/*
	* ���������� ��ձ������������������Atp��Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleTrainOutputData(void);

#ifdef __cplusplus
}
#endif
#endif
