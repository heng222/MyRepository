/************************************************************************
*
* �ļ���   ��  ParsePackProcessManager.h
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  ���������ZC���ݹ���
* ��  ע	��  ��
*
************************************************************************/

#ifndef PARSE_PACK_PROCESS_MANAGER_H_
#define PARSE_PACK_PROCESS_MANAGER_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ������������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	void ParseInputData(void);

	/*
	* ���������� ����������ݴ���
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearInputDataProcess(void);

	/*
	* ���������� ����������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	void PackOutputData(void);

	/*
	* ���������� ���������ݴ���
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void ClearOutputDataProcess(void);

	/*
	* ���������� ����CI��������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	UINT8_S ParseCiToZcData(void);

	/*
	* ���������� ��������ATP��������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	UINT8_S ParseTrainToZcData(void);

	/*
	* ���������� ����NZc��������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	/*����CI��������*/
	UINT8_S ParseNZcToZcData(void);

	/*
	* ���������� ����ats��������
	* ����˵���� void
	* ����ֵ  �� �ɹ����������ݰ�������    
	*/
	extern UINT8_S ParseAtsToZcData(void);

	/*
	* ���������� ����Ntp��������
	* ����˵���� void
	* ����ֵ  �� 1,��ӳɹ�
	*            0,���ʧ��      
	*/
	UINT8_S ParseNtpToZcData(void);
	
	/*
	* ���������� ��֡�����CI������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	UINT8_S PackZcToCiData(void);

	/*
	* ���������� ��֡���������ATP������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	UINT8_S PackZcToTrainData(void);

	/*
	* ���������� ��֡�����Ntp������
	* ����˵���� void
	* ����ֵ  �� 1,��ӳɹ�
	*            0,���ʧ��      
	*/
	UINT8_S PackZcToNtpData(void);

	/*
	* ���������� ��֡�����NZc������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	UINT8_S PackZcToNZcData(void);

	/*
	* ���������� ��֡�����Ats������
	* ����˵���� void
	* ����ֵ  �� void      
	*/
	void PackZcToAtsData(void);/*-bye-*/

#ifdef __cplusplus
}
#endif

#endif
