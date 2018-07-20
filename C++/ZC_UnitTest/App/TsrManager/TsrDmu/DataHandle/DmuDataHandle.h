/*******************************************
�ļ���	��DmuDataHandle.h
����	������
����ʱ�䣺2016-10
����	��DSU��ѯ����
��ע	����
*******************************************/
#ifndef _DMU_DATA_HANDLE_H_
#define _DMU_DATA_HANDLE_H_

#include "DmuStruct.h"

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************
������	��CheckLogicRealteZc
������������ѯ���߼������漰��ZC��ID
����	��UINT16* logicIds,   �߼�����ID
		  UINT8 logicNum,     �߼����θ���
		  UINT8 maxZcNum,     ZC����	
���	��UINT8* pRelateZcId, ����ZCID������(ע���߼����������ĸ�ZC���Ͱ���ӦZCIDд��������)
����ֵ	��1:�ɹ���	0:ʧ��
*******************************************/
extern UINT8_S CheckLogicRealteZc(const UINT16_S* logicIds, UINT8_S logicNum, UINT8_S maxZcNum, UINT8_S* pRelateZcId,UINT8_S *relateZcNum);

/*******************************************
������	��CheckSingleTSRSpeedValid
�����������ж���ʱ������ֵ�Ƿ�������õ���ʱ�����漰�����߼����ε���·����������ֵ
����	��UINT16* pLogicId   �߼�����ID
		  UINT8 logicNum     �߼���������
		  UINT8 speed       �趨��ʱ�����ٶ�
���	����
����ֵ	��2    ���õ���ʱ������ֵ����ĳһ���߼����ε���·����������ֵ
		  1    ���õ���ʱ������ֵû�и����κ�һ���߼����ε���·����������ֵ
		  0    ��ѯʧ�ܣ������������������������Ϊ��ѯʧ�ܣ�
*******************************************/
extern UINT8_S CheckSingleTSRSpeedValid(const UINT16_S* pLogicId,UINT8_S logicNum,UINT8_S speed);

/*******************************************
������	��CheckSingleTsrLogicIdsValid
�����������ж���ʱ�����������߼����ε���Ч��
����	��UINT16* pLogicId   �߼�����ID
		  UINT8 logicNum     �߼���������
���	����
����ֵ	��1: ����ʱ������ͬʱ������ͬһ����Ķ�λ�ͷ�λ��
		  2: ����ʱ�����ڵ��߼����β�����;
		  3: ����ʱ�����ڴ���ID���Ϸ����߼�����;
		  4: ����ԭ��ʧ��
		  0:�ɹ�
*******************************************/
extern UINT8_S CheckSingleTsrLogicIdsValid(UINT16_S* pLogicId,UINT8_S logicNum);

#ifdef __cplusplus
}
#endif

#endif
