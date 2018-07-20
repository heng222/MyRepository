/*******************************************
�ļ���	��TsrInterface.c
����	������
����ʱ�䣺2016-10
����	��TSR�ӿ�
��ע	����
*******************************************/

#include "TsrInterface.h"

/*******************************************
������	��TsrInit
����������Tsr��ʼ������
����	����
���	����
����ֵ	��0:��ʼ��ʧ�ܣ�1����ʼ���ɹ���
*******************************************/
UINT8_S TsrInit(void)
{
	UINT8_S  rtnValue = TSR_SUCCESS;/*��������ֵ*/
	rtnValue = InitialProcess();
	return rtnValue;
}

/*******************************************
������	: TsrIFGetZcWorkState
������������ȡ����״̬
����	����
���	����
����ֵ	��ZC����״̬
*******************************************/
UINT8_S TsrIFGetZcWorkState(void)
{
	UINT8_S  rtnValue = TSR_SUCCESS;/*��������ֵ*/
	rtnValue = GetZcWorkState();
	return rtnValue;
}

/*******************************************
������	: TsrIFSetZcWorkState
�������������ù���״̬
����	����
���	����
����ֵ	����
*******************************************/
void TsrIFSetZcWorkState(UINT8_S workState)
{
	SetZcWorkState(workState);
}

/*******************************************
������	��ParseTsrCommandsFromAts
��������������ATS����������
����	����
���	����
����ֵ	��retVal�ɹ����������ݰ�������
*******************************************/
UINT8_S ParseTsrCommandsFromAts(void)
{
	UINT8_S pktQuan = DEFAULT_ZERO;
	pktQuan = Tsr_ParseIncomingDatas();
	return pktQuan;
}

/*******************************************
������	��ProcessTsrCommandsFromAts
�������������� ATS��������
����	����
���	����
����ֵ	��0:����ʧ��,1:����ɹ�
*******************************************/
UINT8_S ProcessTsrCommandsFromAts(void)
{
	UINT8_S retVal = DEFAULT_ZERO;
	retVal = ProcessRcvFromAtsData();
	return retVal;
}

/*******************************************
������	��ProcessTsrCommandsToAts
�������������� �ظ���Ats����
����	����
���	����
����ֵ	��0��ʧ�ܣ�1���ɹ�
*******************************************/
UINT8_S ProcessTsrCommandsToAts(void)
{
	UINT8_S retVal = DEFAULT_ZERO;
	retVal = ProcessReplyToAtsData();
	return retVal;
}

/*******************************************
������	��PackTsrCommandsToAts
�������������ATS�������
����	����
���	����
����ֵ	����
*******************************************/

void PackTsrCommandsToAts(void)
{
	Tsr_PackOutletDatas();
}
