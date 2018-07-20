/************************************************************************
*
* �ļ���   ��  IOInterfaceProcess.h
* ����ʱ�� ��  2015.08.14
* ����     ��  ZC��
* �������� ��  ��������ӿڴ���
* ��  ע   ��  ��
*
************************************************************************/
#ifndef IO_INTERFACE_PROCESS_H_
#define IO_INTERFACE_PROCESS_H_

#include "../../../Common/CommonTypes.h"
#include "../../../Common/CircQueueStruct.h"


#define UDP_MAX_BUFF_SIZE 5000U

#ifdef __cplusplus
extern "C" {
#endif


	/*
	* ���������� ��ȡƽ̨��������ݽ���������ͨ�Ŷ�����
	* ����˵���� void
	* ����ֵ  �� ��
	*/
	void InterfaceInputProcessToLocalQueue(void);

	/*
	* ���������� ��֯���ع���ĸ���������Ϣ��������ƽ̨�������
	* ����˵���� void
	* ����ֵ  �� ��
	*/
	void InterfaceOutputProcessToPlatform(void);

	/*
    * ���������� �����ն��е������ݷ��뵥�����ݶ���
    * ����˵���� UINT8_S devType,����
    *            const UIN8_S dataBuff[],��������
    *            UINT32_S datalen,���ݳ���
    * ����ֵ  �� void
    */

    void RecvQueueToLocalSingleQueue(UINT8_S devType,const UINT8_S dataBuff[],UINT32_S datalen);

    /*
    * ���������� �������������ݷ��뷢�͵Ķ��е���
    * ����˵���� CirQueueStruct *pCirQueueStru ����ָ��
    * ����ֵ  �� 0: ʧ��
    *            1: �ɹ�
    */

    UINT8_S LocalSingleQueueToSendQueue(CirQueueStruct *pCirQueueStru);
	 

	/*
	* ���������� ��ȡZcToCi�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetZcToCiDataQueueStru(void);

	/*
	* ���������� ��ȡCiToZc�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetCiToZcDataQueueStru(void);

	/*
	* ���������� ��ȡZcTo����ATP�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetZcToTrainDataQueueStru(void);

	/*
	* ���������� ��ȡ����ATPToZc�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetTrainToZcDataQueueStru(void);

	/*
	* ���������� ��ȡZcToAts�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetZcToAtsDataQueueStru(void);

	/*
	* ���������� ��ȡAtsToZc�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	extern CirQueueStruct* GetAtsToZcDataQueueStru(void);/*-bye-*/

	/*
	* ���������� ��ȡZcToNZc�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetZcToNZcDataQueueStru(void);

	/*
	* ���������� ��ȡNZcToZc�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetNZcToZcDataQueueStru(void);

	/*
	* ���������� ��ȡZcToNtp�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetZcToNtpDataQueueStru(void);

	/*
	* ���������� ��ȡNtpToZc�ӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetNtpToZcDataQueueStru(void);
	
	/*
	* ���������� ��ȡZC����־�Ľӿڶ���
	* ����˵���� void
	* ����ֵ  �� NULL: ��ȡ����ʧ��
	*           !NULL: �ӿڶ���
	*/
	CirQueueStruct* GetZcToLogDataQueueStru(void);

#ifdef __cplusplus
}
#endif

#endif
