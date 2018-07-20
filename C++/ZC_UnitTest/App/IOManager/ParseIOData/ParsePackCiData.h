/************************************************************************
*
* �ļ���   ��  ParsePackCiData.h
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  �����ʹ����������
* ��  ע	��  ��
*
************************************************************************/

#ifndef PARSE_PACK_CI_DATA_H_
#define PARSE_PACK_CI_DATA_H_

#include "../../LineDataManager/Mask/MaskDefine.h"
#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif

	/*ZC��CI��̬���ݽṹ��*/
	typedef struct ZcAndCiIODataStruct
	{
		UINT8_S CiId;                                        /*ͨ�ŵ�CiId*/
		UINT16_S MaskValueBuffLen;                            /*��λֵBuf����*/
		UINT8_S MaskValueBuff[ZC_TO_CI_MASK_SUM_MAX];         /*��λ�����ֵ*/
	}ZcAndCiIODataStruct;

	/*
	* ���������� ����CI����ĵ�֡����
	* ����˵���� const UINT8 dataBuff[], ���ݻ�����
	*            const UINT16_S dataLength, ���ݳ���	
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseCiToZcFrameData(const UINT8_S dataBuff[], UINT16_S dataLength);

    /*
    * ���������� У��CI�����������ȷ��
    * ����˵���� const UINT8_S dataBuff[],��������   
    *            const UINT16_S dataLen,���ݳ���
    * ����ֵ  �� 0:�Ϸ���У��ʧ��
    *			 1:�Ϸ���У��ɹ�      
    */
    UINT8_S CiInputDataValidityCheck(const UINT8_S dataBuff[], UINT16_S dataLen);

	/*
	* ���������� ��ȡCi����Zc���������
	* ����˵���� void
	* ����ֵ  �� 0: ʧ��
	*			 >0: ����         
	*/
	UINT8_S GetCiToZcCurSum(void);

    /*
    * ������������ȡCi����Zc��Id��ӦCIid
    * ����˵���� const UINT8 ciIdOfIndex
    * ����ֵ  �� COMM_CI_SUM_MAX: ʧ��
    *			 >=0U: �ɹ�      
    */
	UINT16_S GetCiToZcBuffIndexOfCiId(const UINT8_S ciIdOfIndex);

	/*
	* ������������ȡCi����Zc��Id��Ӧ���ݳ���
	* ����˵���� const UINT8 ciIdOfIndex
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT16_S GetCiToZcIdDataBuffLen(const UINT8_S ciIdOfIndex);

	/*
	* ���������� ��ȡCi����Zc��Id��Ӧ�±�
	* ����˵���� const UINT8 ciIdOfIndex
	* ����ֵ  ��  NULL: ʧ��
	*			 ��NULL: �ɹ�     
	*/
	UINT8_S* GetCiToZcDataBuffByIndex(const UINT8_S ciIdOfIndex);

	/*
	* ���������� ��������Ci�ĵ�֡����
	* ����˵����  const UINT8_S dataBuff[], ���ݻ�����
	*             UINT16_S dataLength, ���ݳ���
	*             UINT16_S destId, Ŀ��CI�豸ID
	* ����ֵ  �� 0: ���ݴ��ʧ��
	*			 1: ���ݴ���ɹ�      
	*/
	UINT8_S PackZcToCiFrameData(const UINT8_S dataBuff[], UINT16_S dataLength,UINT16_S destId);

	/*
	* ���������� ��ȡZC���CI���������
	* ����˵���� void
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT8_S GetToCiCurSum(void);

	/*
	* ���������� ��ȡZC���CI��Id��Ӧ���ݳ���
	* ����˵���� const UINT8 ciIdOfIndex
	* ����ֵ  �� 0: ʧ��
	*			 >0: �ɹ�      
	*/
	UINT16_S GetToCiIdDataBuffLen(const UINT8_S ciIdOfIndex);

	/*
	* ���������� ��ȡZC���CI��Id�±��Ӧ������
	* ����˵���� const UINT8 ciIdOfIndex
	* ����ֵ  ��  NULL: ʧ��
	*			 ��NULL: �ɹ�     
	*/
	UINT8_S* GetToCiDataBuffByIndex(const UINT8_S ciIdOfIndex);

	/*
	* ���������� ��ձ��������������CI������Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleCiInputData(void);

	/*
	* ���������� ��ձ��������������CI������Ϣ
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearCycleCiOutputData(void);

#ifdef __cplusplus
}
#endif

#endif
