/************************************************************************
*
* �ļ���   ��  InputDataProcess.h
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  ������ZC�յ������ݹ���
* ��  ע	��  ��
*
************************************************************************/

#ifndef INPUT_DATA_PROCESS_H_
#define INPUT_DATA_PROCESS_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� �������ݴ���
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void InputDataProcess(void);

	/*
	* ���������� ����CI��������
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void CiToZcInputDataProcess(void);

	/*
	* ���������� ����CI����ĵ�֡����
	* ����˵���� const UINT8 ciInValueBuff[],��������
	*            const UINT16_S dataLength,���볤��
	*            const UINT16_S maskSum,��λ����
	*            UINT8_S maskValueBuff[],�����λ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseCiInMaskDataToMaskBuf(const UINT8_S ciInValueBuff[],const UINT16_S dataLength,const UINT16_S maskSum,UINT8_S maskValueBuff[]);

	/*
	* ���������� ����CI�������λ���ݵ����豸������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT8_S maskValueBuff[],������λ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToDeviceData(const UINT16_S commTargetId,const UINT8_S maskValueBuff[]);

	/*
	* ���������� ����CI�������λ���ݵ������豸λ��������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskMainValue,����λ��λֵ
	*            const UINT8_S maskSideValue,����λ��λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToSwitchPostData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskMainValue,const UINT8_S maskSideValue);

	/*
	* ���������� ����CI�������λ���ݵ������豸����������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskValue,����������λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToSwitchLockData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ����CI�������λ���ݵ��źŻ��豸״̬������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*             const UINT8_S maskValue,�źŻ�״̬��λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToSignalStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ����CI�������λ���ݵ�Psd�豸״̬������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskValue,������״̬��λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToPsdStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ����CI�������λ���ݵ�Esb�豸״̬������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskValue,����ͣ����ť״̬��λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToEsbStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ����CI�������λ���ݵ����������豸����������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskUpDirValue,��������������λֵ
	*            const UINT8_S maskDownDirValue,��������������λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToACDirData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskUpDirValue,const UINT8_S maskDownDirValue);

	/*
	* ���������� ����CI�������λ���ݵ���������ռ��������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskValue,��������ռ����λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToAcOccStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ����CI�������λ���ݵ�������������������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskValue,������������״̬��λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToAcLockStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ����CI�������λ���ݵ���·״̬������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskValue,��·״̬��λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToRouteStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ����CI�������λ���ݵ���������״̬������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskValue,��������״̬��λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToOverlapStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ����CI�������λ���ݵ������۷���ť״̬������
	* ����˵���� const UINT16 commTargetId,ͨ��CIid
	*            const UINT16_S maskId,��λID
	*            const UINT8_S maskValue,�����۷���ť״̬��λֵ
	* ����ֵ  �� 0: ���ݽ���ʧ��
	*			 1: ���ݽ����ɹ�      
	*/
	UINT8_S ParseMaskValueToDRButtonStatusData(const UINT16_S commTargetId,const UINT16_S maskId,const UINT8_S maskValue);

	/*
	* ���������� ��������ZC��������
	* ����˵���� ��
	* ����ֵ  �� ��      
	*/
	void NextZcInputDataProcess(void);

	/*
	* ���������� ��������ZC���뵥֡����
	* ����˵���� const UINT16 zcId,ZC�ı��
	*            const UINT8_S pBuff[],ָ�����ݻ�������ָ��
	* ����ֵ  �� 0: ʧ��
	*            1: �ɹ�
	*/
	UINT8_S ParseNextZcInput(const UINT16_S zcId,const UINT8_S pBuff[]);

	/*
	* ���������� ��������ZC�����ϰ�������
	* ����˵���� const UINT16_S zcId,ZC�ı��
	*            const UINT8_S *pBuff,ָ�����ݻ�������ָ��
	*            UINT16_S *dataIndex,
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcObsMsgParse(const UINT16_S zcId,const UINT8_S *pBuff,UINT16_S *dataIndex);

	/*
	* ���������� ��ȡ����ZC�����ϰ�����λ����
	* ����˵���� const UINT16_S bitIndex, ��λֵ
	*            const UINT16_S baseBufIndex,��������±�
	*            const UINT8_S baseAddr[]����������
	* ����ֵ  �� ��λֵ
	*/
	UINT8_S GetZcBitValue(const UINT16_S bitIndex, const UINT16_S baseBufIndex,const UINT8_S baseAddr[]);

	/*
	* ���������� ��������ZC�����ϰ����·������
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcRouteMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC�����ϰ���������Σ�����
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcOverLapMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC�����ϰ���źŻ�������
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcSignalMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC�����ϰ����������
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcSwitchMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC�����ϰ�������ţ�����
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcPsdMsgParse(const UINT16_S zcId,const UINT8_S pBuff[], UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC�����ϰ������ͣ����ť������
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcEsbMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC�����ϰ�������۷���ť������
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcDrButtonMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC�����ϰ�������۷��ƣ�����
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcDrLampMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC�����ϰ���������Σ�����
	* ����˵���� const UINT16 zcId,zcId
	*            UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcAcMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC������ʱ��������
	* ����˵���� const UINT16_S zcId,zcId
	*            const UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcTsrMsgParse(const UINT16_S zcId,const UINT8_S pBuff[], UINT16_S *dataIndex);


	/*
	* ���������� ��������ZC���뵥֡�������г���Ϣ
	* ����˵���� const UINT16_S trainId,�г���ID
	*            const UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcTrainMsgParse(const UINT16_S trainId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC���뵥֡�������г��ƶ���Ȩ��Ϣ
	* ����˵���� const UINT16_S zcId,����ZC�ı��
    *            const UINT16_S trainId,�г���ID
	*            const UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcMaMsgParse(const UINT16_S zcId,const UINT16_S trainId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ��������ZC���뵥֡�������г����ƶ���Ȩ��Ϣ
	* ����˵���� const UINT16_S zcId,ZC���
	*            const UINT8_S pBuff[],��������
	*            UINT16_S *dataIndex,������������±�
	* ����ֵ  �� 0,����ʧ��
	*            1,����ɹ�
	*/
	UINT8_S NextZcTrainAndMaMsgParse(const UINT16_S zcId,const UINT8_S pBuff[],UINT16_S *dataIndex);

	/*
	* ���������� ����Ntp����ZC������
	* ����˵���� ��
	* ����ֵ  �� ��    
	*/
	void NtpToZcInputDataProcess(void);

	/*
	* ���������� ��������ATP����ĵ�֡����
	* ����˵���� ��
	* ����ֵ  �� ��     
	*/
	void TrainToZcInputDataProcess(void);

    /*
    * ���������� �����г���������
    * ����˵���� const UINT16_S trainId,�г�ID            
    *            const UINT16_S dataLen,���ݳ���(Ԥ��)
    *            const UINT8_S *pDataBuff,���ݻ���
    * ����ֵ  �� 0: ʧ��
    *������������1; �ɹ�
    */
	UINT8_S UpdateTrainInputData(const UINT16_S trainId,const UINT16_S dataLen,const UINT8_S pDataBuff[]);

#ifdef __cplusplus
}
#endif

#endif
