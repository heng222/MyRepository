/*******************************************
�ļ���	��QueryMange.h
����	������
����ʱ�䣺2016-10
����	����ѯ��������
��ע	����
*******************************************/

#ifndef QUERY_MANAGE_H_
#define QUERY_MANAGE_H_

#include "../../../Common/CommonTypes.h"
#include "../TsrAdministrator/TsrDataAdmin.h"
#include "../../../Common/CircQueueStruct.h"

#define FILE_DATA_LEN      1504u


#ifdef __cplusplus
extern "C" {
#endif 

/*******************************************
������	��CheckLogicIdRealteZc
������������ѯ���߼������漰��ZC��ID
����	��UINT16* logicIds,   �߼�����ID
		  UINT8_S logicNum,     �߼����θ���
          UINT8_S maxZcNum,     ZC����
���	��UINT8_S* pRelateZcId, ����ZCID������(ע���߼����������ĸ�ZC���Ͱ���ӦZCIDд��������)
����ֵ	��1:�ɹ���	0:ʧ��
*******************************************/
extern UINT8_S CheckLogicIdRealteZc(UINT16_S* logicIds, UINT8_S logicNum, UINT8_S maxZcNum, UINT8_S* pRelateZcId,UINT8_S *relateZcNum);

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
extern UINT8_S CheckSingleTSRSpeed(UINT16_S* pLogicId,UINT8_S logicNum,UINT8_S speedValue);

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
extern UINT8_S CheckSingleTsrLogicId(UINT16_S* pLogicId,UINT8_S logicNum);

#ifdef __cplusplus
}
#endif
#endif