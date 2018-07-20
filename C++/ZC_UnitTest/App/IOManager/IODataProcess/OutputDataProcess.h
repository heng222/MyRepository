/************************************************************************
*
* �ļ���   ��  OutputDataProcess.c
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  ���ZC���͵����ݹ���
* ��  ע	��  ��
*
************************************************************************/

#ifndef OUTPUT_DATA_PROCESS_H_
#define OUTPUT_DATA_PROCESS_H_


#ifdef __cplusplus
extern "C" {
#endif
/*
* ���������� ������ݴ���
* ����˵���� ��
* ����ֵ  �� ��      
*/
void OutputDataProcess(void);

/*
* ���������� �������CI������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S CiOutputDataProcess(void);

/*
* ���������� �������CI������
* ����˵���� const UINT16 ciId,�����ı��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S SingleCiOutput(const UINT16_S ciId);

/*
* ���������� ��д��λֵ
* ����˵���� const UINT16 maskId,��λID
*            const UINT16_S buffSize,�����С
*            UINT8_S dataBuff[],�������
* ����ֵ  �� 0: ��дʧ��
*			 1: ��д�ɹ�      
*/
UINT8_S SetMaskValue(const UINT16_S maskId,const UINT16_S buffSize,UINT8_S dataBuff[]);

/*
* ���������� ���������CI���߼�����CT�г�ռ����λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessSectionCtMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� ���������CI���߼�����UT�г�ռ����λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessSectionUtMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� ���������CI�ļ�������ARB��λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessAcArbMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� ���������CI�ļ�������ͣ����λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessAcStopMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� ���������CI�������۷���������λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessDrLampTwinkleMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� ���������CI�������۷����ȵ���λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessDrLampSteadyMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� ���������CI���źŻ���ѹ��Ϣ��λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessSignalCrossMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� ���������CI���źŻ�������Ϣ��λ��Ϣ
* ����˵���� const UINT8 deviceSum,�豸����
*            const UINT16_S deviceIdBuff[],�豸ID����
* ����ֵ  �� 0: ��λֵΪ0
*			 1: ��λֵΪ1      
*/
UINT8_S ProcessSignalLightOffMask(const UINT8_S deviceSum,const UINT16_S deviceIdBuff[]);

/*
* ���������� �������NZC������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
void NZcOutputDataProcess(void);

/*
* ���������� �����������NZC������
* ����˵���� const UINT16 nZcId,ZCID
* ����ֵ  �� ��     
*/
void NextZcOutput(const UINT16_S nZcId);

/*
* ���������� д���������NZC����λ����
* ����˵���� UINT8 bitValue,��λֵ
*            UINT16_S  bitIndex,��λ�±�
*            UINT8_S baseAddr[],������ݻ���ַ
* ����ֵ  �� ��     
*/
void  WriteZcBitValue(UINT8_S bitValue,UINT16_S  bitIndex,UINT8_S baseAddr[]);

/*
* ���������� �����������NZC������
* ����˵���� const UINT16 nZcId,ZCID
*			 UINT8_S *pBuff,�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�    
*/
UINT8_S NextZcObsMsgPack(const UINT16_S zcId,UINT8_S *pBuff, UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ����·������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcRouteMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ���������Σ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcOverlapMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ���źŻ�������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcSignalMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ����������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcSwitchMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ�������ţ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcPsdMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ������ͣ����ť������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcEsbMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ�������۷���ť������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcDrButtonMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ�������۷��ƣ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcDrLampMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC�����ϰ���������Σ�����
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],�������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcAcMsgPack(const UINT16_S zcId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �������ZC������ʱ��������
* ����˵���� const UINT16 zcId,zcId
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� 0,����ʧ��
*            1,����ɹ�
*/
UINT8_S NextZcTsrMsgPack(const UINT16_S zcId,UINT8_S pBuff[], UINT16_S *dataIndex);

/*
* ���������� �����������NZC���г�����
* ����˵���� const UINT16 trainId,�г�ID
*            UINT8_S pBuff[],��������
* ����ֵ  �� �����±�     
*/
UINT8_S NextZcTrainMsgPack(const UINT16_S trainId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �����������NZC���г��ƶ���Ȩ����
* ����˵���� const UINT16 trainId,�г�ID
*            UINT8_S pBuff[],��������
* ����ֵ  �� �����±�     
*/
UINT8_S NextZcMaMsgPack(const UINT16_S trainId,UINT8_S pBuff[],UINT16_S *dataIndex);

/*
* ���������� �����������NZC���г����ƶ���Ȩ����
* ����˵���� const UINT16 zcId,ZC��ID(Ԥ��)
*            UINT8_S pBuff[],��������
*            UINT16_S *dataIndex,������������±�
* ����ֵ  �� RETURN_ERROR,����ʧ��
*            RETURN_SUCCESS,����ɹ�       
*/
UINT8_S NextZcTrainAndMaMsgPack(const UINT16_S zcId,UINT8_S pBuff[], UINT16_S *dataIndex);

/*
* ���������� �������Ntp������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S NtpOutputDataProcess(void);

/*
* ���������� ��֡��Ntp������
* ����˵���� const UINT16 commId��ID��Ϣ
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S NtpOutputDataPack(const UINT16_S commId);

/*
* ���������� �����������ATP������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S TrainOutputDataProcess(void);

/*
* ���������� �����ƶ���Ȩ�����֯
* ����˵���� const UINT16 trainId,�г���ID
*            const UINT8_S trainOutType,�г��������
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S NormalMaOutputProcess(const UINT16_S trainId,const UINT8_S trainOutType);

/*
* ���������������ƶ��ƶ���Ȩ�����֯
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S AbnormalMaOutputProcess(const UINT16_S trainId);

/*
* ����������ͳһ���ƶ���Ȩ�����Ϣ��֯
* ����˵���� const UINT16 trainId,�г�ID
*            const UINT8_S trainOutType,�г��������
*            UINT16_S * addIndex,�����±�
*            UINT8_S dataBuff[],��������
* ����ֵ  �� ��      
*/
void UnifiedMaOutputInfoProcess(const UINT16_S trainId,const UINT8_S trainOutType,UINT16_S *addIndex,UINT8_S dataBuff[]);

/*
* ���������� �������Ats������
* ����˵���� ��
* ����ֵ  �� 0:������ʧ��
*			 1:�����ݳɹ�      
*/
UINT8_S AtsOutputDataProcess(void);

/*
* ���������� CBTC�г�ռ���߼�������֡
* ����˵���� UINT16 *addIndex,�����С;
*            UINT8_S dataBuff[],�������;
* ����ֵ  �� 0>=:�г�����     
*/
UINT8_S SectionOccFromCbtcTrain(UINT16_S *addIndex,UINT8_S dataBuff[]);

/*
* ���������� ��CBTC�г�ռ���߼�������֡
* ����˵���� UINT16 *addIndex,�����С;
*            UINT8_S dataBuff[],�������;
* ����ֵ  �� 0>=:�г�����     
*/
UINT8_S SectionOccFromUnCbtcTrain(UINT16_S *addIndex,UINT8_S dataBuff[]);

#ifdef __cplusplus
}
#endif

#endif
