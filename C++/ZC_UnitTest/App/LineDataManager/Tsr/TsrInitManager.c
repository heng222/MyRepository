/************************************************************************
*
* �ļ���   ��  TsrInitManager.c
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��ʱ���ٳ�ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#include "../../SysDataManager/SysConfigData.h"
#include "TsrStatusData.h"
#include "TsrInitManager.h"
#include "../../MaintainManager/MaintainManager.h"
#include "../../../Common/MemSet.h"

extern TsrDataStruct gTsrDataStruBuff[TSR_BUFF_SUM_MAX];                  /*���ñ��ع������ʱ����������Ϣ*/
extern UINT16_S gTsrOfZcIdBuff[LINE_ZC_SUM_MAX];                         /*������ʱ���٣�ZC��ӳ������*/
extern UINT16_S gTsrOfZcCurSum;                                         /*������ʱ���٣�ZC����ǰ����*/

/*
* ���������� ��ʼ�����ع������ʱ������Ϣ
* ����˵���� ��   
* ����ֵ  �� ��     
*/
void InitTsrLocalInfo(void)
{
	UINT8_S cycle = DEFAULT_ZERO;

	gTsrOfZcCurSum = 0U;

	for (cycle = DEFAULT_ZERO;cycle < LINE_ZC_SUM_MAX;cycle++)
	{
		gTsrOfZcIdBuff[cycle] = TSR_BUFF_SUM_MAX;
	}
}
