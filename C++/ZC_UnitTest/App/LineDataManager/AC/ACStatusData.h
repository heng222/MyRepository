/********************************************************
*                                                                                                            
* �� �� ���� ACStatusData.h  
* ����ʱ�䣺 2015-05-01
* ��    �ߣ� 
* ���������� ����״̬���ݹ���  
* ��  ע  ��  ��
*
********************************************************/ 
#ifndef AC_STATUS_DATA_H_
#define AC_STATUS_DATA_H_
#include "../../../Common/CommonTypes.h"
#include "ACDefine.h"

#ifdef __cplusplus
extern "C" 
{
#endif

	/*���������������ݽṹ��*/
	typedef struct AcStatusDataStruct
	{
		UINT16_S AcId;      		                                    /*��������ID*/
		UINT8_S AcDirection;    	                                    /*�������շ���*/
		UINT8_S AcBelock;			                                    /*��������*/
		UINT8_S AcStatusNow;                                          /*����ռ�ÿ���*/
		UINT8_S AcUtFlag;                                             /*����UT��־λ*/
		UINT8_S AcUtRedundance;                                       /*UT�������ֵ*/
		UINT8_S AcArbFlag;                                            /*����UT��־λ*/
		UINT8_S AcArbRedundance;                                      /*UT�������ֵ*/
		UINT16_S LastTrainEnterAc;                                    /*���һ�����������г�ID*/
		UINT16_S CleanTrainId;                                        /*��¼��ɨ�г�ID*/
		UINT8_S TrainCleanFlag;                                       /*RM�г�����ɨ��־*/
		UINT8_S  TrainOfAcNum;                                        /*���������ڵ�ǰ�г�����*/
		UINT16_S TrainSequenceBuff[SIZE_MAX_TRAINOFAC];	            /*�г���������*/
		UINT8_S LastTrainOfAcNum;                                     /*�����ڼ������г�����*/
		UINT16_S LastTrainSequenceBuff[SIZE_MAX_TRAINOFAC];	        /*�����ڼ������г���������*/
	} AcStatusDataStruct;

	/*
	* ���������� ��ȡָ��ID�������շ���
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ�ܻ����޷���
	*			 0x55: ���շ������߼���������ͬ
	*			 0xaa: ���շ������߼��������෴
	*/
	UINT8_S GetAcDirection(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID�������շ���
	* ����˵���� const UINT16 acId, ����ID  
	*            const UINT8_S acDirection
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ�ܻ����޷���
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcDirection(const UINT16_S acId,const UINT8_S acDirection);

	/*
	* ���������� ��ȡָ��ID�������շ���
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ�ܻ���Ĭ��ֵ
	*			 0x55: ����
	*			 0xaa: δ����
	*/
	UINT8_S GetAcBelock(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID��������״̬
	* ����˵���� const UINT16 acId, ����ID 
	*            const UINT8_S acBelock
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcBelock(const UINT16_S acId,const UINT8_S acBelock);

	/*
	* ���������� ��ȡָ��ID����ռ��״̬
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ�ܻ���Ĭ��ֵ
	*			 0x55: ռ��
	*			 0xaa: ����
	*/
	UINT8_S GetAcStatusNow(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID���ᵱǰռ��״̬
	* ����˵���� const UINT16 acId, ����ID 
	*            const UINT8_S acStatus
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcStatusNow(const UINT16_S acId,const UINT8_S acStatus);

	/*
	* ���������� ��ȡָ��ID����UT��־
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 0x55: UT
	*			 0xaa: ��UT
	*/
	UINT8_S GetAcUtFlag(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID����UT��־
	* ����˵���� const UINT16 acId, ����ID 
	*            const UINT8_S acUtFlag
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcUtFlag(const UINT16_S acId,const UINT8_S acUtFlag);

	/*
	* ���������� ��ȡָ��ID����ARB��־
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 0x55: ARB
	*			 0xaa: ��ARB
	*/
	UINT8_S GetAcArbFlag(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID����ARB��־
	* ����˵���� const UINT16 acId, ����ID    
	*            const UINT8_S acArbFlag
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcArbFlag(const UINT16_S acId,const UINT8_S acArbFlag);

	/*
	* ���������� ��ȡָ��ID�������һ��������г�ID
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 1: ��ȡ���ݳɹ�
	*/
	UINT8_S GetAcLastTrain(const UINT16_S acId,UINT16_S *trainId);

	/*
	* ���������� ����ָ��ID�������һ��������г�ID
	* ����˵���� const UINT16 acId, ����ID   
	*            const UINT16_S acLastTrainId�����һ�г�
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcLastTrain(const UINT16_S acId,const UINT16_S acLastTrainId);

	/*
	* ���������� ��ȡָ��ID����UT�����ʱλ
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >=0:�����ʱλ
	*/
	UINT8_S GetAcUtRedundance(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID����UT�����־λ
	* ����˵���� const UINT16 acId, ����ID  
	*            const UINT8_S acUtRedundance
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcUtRedundance(const UINT16_S acId,const UINT8_S acUtRedundance);

	/*
	* ���������� ��ȡָ��ID����ARB�����ʱλ
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >=0:�����ʱλ
	*/
	UINT8_S GetAcArbRedundance(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID����ARB�����־λ
	* ����˵���� const UINT16 acId, ����ID  
	*            const UINT8_S acArbRedundance
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcArbRedundance(const UINT16_S acId,const UINT8_S acArbRedundance);

	/*
	* ���������� ��ȡָ��ID�����г�����
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� DEFAULT_UINT8_VALUE: ��ȡ����ʧ��
	*			 >=0:�г�����
	*/
	UINT8_S GetAcTrainOfAcNum(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID�����г�����
	* ����˵���� const UINT16 acId, ����ID   
	*            const UINT8_S acTrainOfAcNum
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetAcTrainOfAcNum(const UINT16_S acId,const UINT8_S acTrainOfAcNum);

	/*
	* ���������� ��ȡָ��ID�����г�������Ϣ
	* ����˵���� const UINT16 acId, ����ID    
	*            const UINT8_S bufSzie,�����С
	*            UINT16_S trainIdSequBuff[],�������
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS:�ɹ�
	*/
	UINT8_S GetAcTrainSequenceBuff(const UINT16_S acId,const UINT8_S bufSzie,UINT16_S trainIdSequBuff[]);

	/*
	* ���������� ����ָ��ID�����г�������Ϣ
	* ����˵���� const UINT16 acId,
	*            const UINT16_S trainIdSequBuff[],����ID
	*            const UINT8_S trainNum,�г�����    
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS:�ɹ�
	*/
	UINT8_S SetAcTrainSequenceBuff(const UINT16_S acId,const UINT16_S trainIdSequBuff[],const UINT8_S trainNum);

	/*
	* ���������� �ж�ָ���г�IDλ�ڼ����г����е�λ��
	* ����˵���� const UINT16 acId ����Id
	*            const UINT16_S trainId���г�Id
	* ����ֵ  �� 0xff: û���ڸü����г�������
	*			 0>=: ����λ��    
	*/
	UINT8_S GetTrainIdInTrainSequence(const UINT16_S acId,const UINT16_S trainId);

	/*
	* ���������� ��ѯָ�����������ڵ�ָ���±��Ӧ���г�Id
	* ����˵���� const UINT16 acId ����Id
	*            const UINT8_S index�������±�
	*            UINT16_S *trainIdInAC������г�ID
    * ����ֵ  �� RETURN_ERROR: ��ѯʧ��
    *			 RETURN_SUCCESS: ��ѯ�ɹ�    
	*/
	UINT8_S GetTrainIdInTrainSequenceOfIndex(const UINT16_S acId,const UINT8_S index,UINT16_S *trainIdInAC);

	/*
	* ���������� ��ȡ������ָ��ID�����г�����
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� -1: ��ȡ����ʧ��
	*			 >=0:�г�����
	*/
	UINT8_S GetLastTrainOfAcNum(const UINT16_S acId);

	/*
	* ���������� ����������ָ��ID�����г�����
	* ����˵���� const UINT16 acId, ����ID  
	*            const UINT8_S acTrainOfAcNum
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS: �ɹ�
	*/
	UINT8_S SetLastTrainOfAcNum(const UINT16_S acId,const UINT8_S acTrainOfAcNum);

	/*
	* ���������� ��ȡ������ָ��ID�����г�������Ϣ
	* ����˵���� const UINT16 acId, ����ID    
	*            const UINT8_S bufSzie,�����С
	*            const UINT16_S trainIdSequBuff[],�������
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS:�ɹ�
	*/
	UINT8_S GetLastTrainSequenceBuf(const UINT16_S acId,const UINT8_S bufSzie,UINT16_S trainIdSequBuff[]);

	/*
	* ���������� ����������ָ��ID�����г�������Ϣ
	* ����˵���� const UINT16 acId,
	*            const UINT16_S trainIdSequBuff[],����ID
	*            const UINT8_S trainNum,�г�����    
	* ����ֵ  �� RETURN_ERROR: ��ȡ����ʧ��
	*			 RETURN_SUCCESS:�ɹ�
	*/
	UINT8_S SetLastTrainSequenceBuf(const UINT16_S acId,const UINT16_S trainIdSequBuff[],const UINT8_S trainNum);

	/*
	* ���������� ��ȡָ��ID�����г�����ɨ��־
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� RETURN_UINT8_MAX_VALUE: ��ȡ����ʧ��
	*			 FLAG_SET:����ɨ
	*			 FLAG_UNSET:δ��ɨ
	*/
	UINT8_S GetAcTrainCleanFlag(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID�����г�����ɨ��־
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� RETURN_SUCCESS: ���óɹ�
	*			 RETURN_ERROR:����ʧ��			 
	*/
	UINT8_S SetAcTrainCleanFlag(const UINT16_S acId,const UINT8_S cleanFlag);

	/*
	* ���������� ��ȡָ��ID��������ɨ�г�ID
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� 0: ��ȡ����ʧ��
	*			 >0:��ɨ�г�ID
	*/
	UINT16_S GetAcCleanTrainId(const UINT16_S acId);

	/*
	* ���������� ����ָ��ID��������ɨ�г�ID
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� RETURN_ERROR: ��������ʧ��
	*			 RETURN_SUCCESS:���óɹ�
	*/
	UINT8_S SetAcCleanTrainId(const UINT16_S acId,const UINT16_S cleanTrainId);

	/*
	* ���������� ��ȡ���������ڵĵ�һ�г�
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� RETURN_UINT16_MAX_VALUE: ��ȡ����ʧ��
	*			>0: ��һ���г�ID
	*/
	UINT16_S GetFirstIdInTrainSequence(const UINT16_S acId);

	/*
	* ���������� ��ȡ���������ڵ����һ�г�
	* ����˵���� const UINT16 acId, ����ID    
	* ����ֵ  �� RETURN_UINT16_MAX_VALUE: ��ȡ����ʧ��
	*			>0: ���һ���г�ID
	*/
	UINT16_S GetLastIdInTrainSequence(const UINT16_S acId);
	
#ifdef __cplusplus
}
#endif

#endif
