/*******************************************
�ļ���	��TsrParsePackInterface.c
����	������
����ʱ�䣺2016-10
����	���������
��ע	����
*******************************************/
#include"TsrParsePackInterface.h"
/*#include"../TsrMaintenance/MaintainManager.h"*/
/*#include "../TsrMaintenance/EventCode.h"*/
/*#include "../TsrMaintenance/EventCode.h"*/
#include"TsrParsePackAtsData.h"
#include "../../../Common/MemSet.h"
#include "../../IOManager/IOInterfaceProcess/IOInterfaceProcess.h"
/*#ifdef SYS_TYPE_WINDOWS*/
#include "../../../Common/CommonTypes.h"
#include "../../IOManager/ParseIOData/ParsePackIODefine.h"
/*#endif*/

static UINT8_S ParseOneFrameData(const UINT8_S dataBuf[], UINT16_S dataLen);

/*******************************************
������	��Tsr_ParseIncomingDatas
���������������ⲿͨ���豸����������
����	����
���	����
����ֵ	��retVal�ɹ����������ݰ�������
*******************************************/
UINT8_S Tsr_ParseIncomingDatas(void)
{
	CirQueueStruct *pAtsToZcDataQueueStru = NULL;
    UINT32_S dataLen = DEFAULT_ZERO; /*����֡����*/
    UINT8_S tmpDataBuf[DEV_TOTAL_FRAME_LEN] = {DEFAULT_ZERO}; /* ��ʱ���ݻ����� */
    UINT8_S retVal = DEFAULT_ZERO;
	UINT32_S pkgQuan = DEFAULT_ZERO;
	UINT32_S iCyc = DEFAULT_ZERO;

    MemorySet(tmpDataBuf, DEV_TOTAL_FRAME_LEN, DEFAULT_ZERO, DEV_TOTAL_FRAME_LEN);

	/*��ȡats��ZC����������*/
	pAtsToZcDataQueueStru = GetAtsToZcDataQueueStru();

	/*�ж��Ƿ�*/
	if (pAtsToZcDataQueueStru != NULL)
	{
		pkgQuan = GetQueuePkgCount(pAtsToZcDataQueueStru); /*��ȡ�������ݰ�����*/

		for (iCyc = DEFAULT_ZERO; iCyc < pkgQuan; iCyc++)
		{
			/*��ճ���*/
			dataLen = DEFAULT_ZERO;
			MemorySet(tmpDataBuf,((UINT32_S)(DEV_TOTAL_FRAME_LEN)),DEFAULT_ZERO,((UINT32_S)(DEV_TOTAL_FRAME_LEN)));

			/*��ȡһ֡����*/
			dataLen = GetQueuePkgData(pAtsToZcDataQueueStru, tmpDataBuf, DATA_LEN_MAX); 

			if (dataLen > 0U)
			{ 				
				/*��ȡ�ɹ�,��������*/
				ParseOneFrameData(tmpDataBuf,(UINT16_S)dataLen);
				retVal++;
			}
			else
			{
				break;
			}
		}
	}

    return retVal;

}
/*******************************************
������	��ParseOneFrameData
��������������һ���ⲿͨ���豸����������
����	��dataBuf��������֡��dataLen��������֡���ȣ�devType�豸����
���	����
����ֵ	��0���ɹ���1������ATS����ʧ�ܣ�
*******************************************/
static UINT8_S ParseOneFrameData(const UINT8_S dataBuf[], UINT16_S dataLen)
{
    UINT8_S retVal = DEFAULT_ZERO;

    if(dataLen > DEFAULT_ZERO)
    {
		/*LogBuff("RevAtsData:",dataBuf,dataLen);*/

		if (TSR_ERROR == ParseRcvFromAtsDataFrame(&dataBuf[ATS_FRAME_OFFSET], dataLen))/*����ATS����*/
		{
			
			/*LogMsgString(1, "ParseAtsToDmsData error\n");*/
			/*SetEventLogList(DMS_ATS_PARSE_ERROR,LOG_EVENT_ERROR,1u,0u);*/
			retVal = 1u;
		}
        else
        {
            /*do nothing*/
        }
    }

    return retVal;

}
/*******************************************
������	��Tsr_PackOutletDatas
�������������ATS�������
����	����
���	����
����ֵ	����
*******************************************/
void Tsr_PackOutletDatas(void)
{
	PackReplyToAtsData();
	/*PacklogData();*/
}
