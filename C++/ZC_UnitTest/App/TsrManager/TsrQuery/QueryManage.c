/*******************************************
�ļ���	��QueryMange.c
����	������
����ʱ�䣺2016-10
����	����ѯ��������
��ע	����
*******************************************/

#include "QueryManage.h"
#include "../TsrDmu/DataHandle/DmuDataHandle.h"
/*#include "../TsrMaintenance/MaintainManager.h"*/
#include "../../../Common/Convert.h"
#include "../../../Common/CRC32.h"
#include "../../../Common/MemSet.h"
#include "../../../PlatformAdapter/AppItf/AdptAppServiceInterface.h"
#include "../../../PlatformAdapter/AppItf/AdptAppFileInterface.h"

/*******************************************
������	��CheckLogicIdRealteZc
������������ѯ���߼������漰��ZC��ID
����	��UINT16* logicIds,   �߼�����ID
 		  UINT8_S logicNum,     �߼����θ���
          UINT8_S maxZcNum,     ZC����
���	��UINT8_S* pRelateZcId, ����ZCID������(ע���߼����������ĸ�ZC���Ͱ���ӦZCIDд��������)
����ֵ	��1:�ɹ���	0:ʧ��
*******************************************/
UINT8_S CheckLogicIdRealteZc(UINT16_S* logicIds, UINT8_S logicNum, UINT8_S maxZcNum, UINT8_S* pRelateZcId,UINT8_S *relateZcNum)
{
	UINT8_S rtnValue = DEFAULT_ZERO;
	if((logicIds != NULL)&&(pRelateZcId != NULL)&&(relateZcNum !=NULL))
	{
		rtnValue = CheckLogicRealteZc(logicIds, logicNum, maxZcNum, pRelateZcId, relateZcNum);
	}
	return rtnValue;
}

/*******************************************
������	��CheckSingleTSRSpeed
�����������ж���ʱ������ֵ�Ƿ�������õ���ʱ�����漰�����߼����ε���·����������ֵ
����	��UINT16* pLogicId   �߼�����ID
		  UINT8_S logicNum     �߼���������
		  UINT8_S speed       �趨��ʱ�����ٶ�
���	����
����ֵ	��2    ���õ���ʱ������ֵ����ĳһ���߼����ε���·����������ֵ
		  1    ���õ���ʱ������ֵû�и����κ�һ���߼����ε���·����������ֵ
		  0    ��ѯʧ�ܣ������������������������Ϊ��ѯʧ�ܣ�
*******************************************/
UINT8_S CheckSingleTSRSpeed(UINT16_S* pLogicId,UINT8_S logicNum,UINT8_S speedValue)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if(pLogicId != NULL)
	{
		rtnValue = CheckSingleTSRSpeedValid(pLogicId, logicNum, speedValue);
	}
	return rtnValue;
}

/*******************************************
������	��CheckSingleTsrLogicId
�����������ж���ʱ�����������߼����ε���Ч��
����	��UINT16* pLogicId   �߼�����ID
		  UINT8_S logicNum     �߼���������
���	����
����ֵ	��1: ����ʱ������ͬʱ������ͬһ����Ķ�λ�ͷ�λ��
          2: ����ʱ�����ڵ��߼����β�����;
		  3: ����ʱ�����ڴ���ID���Ϸ����߼�����;
		  4: ����ԭ��ʧ��
		  0:�ɹ�
*******************************************/
UINT8_S CheckSingleTsrLogicId(UINT16_S* pLogicId,UINT8_S logicNum)
{
	UINT8_S rtnValue = DEFAULT_ZERO;

	if(pLogicId != NULL)
	{
		rtnValue = CheckSingleTsrLogicIdsValid(pLogicId,logicNum);
	}
	return rtnValue;
}