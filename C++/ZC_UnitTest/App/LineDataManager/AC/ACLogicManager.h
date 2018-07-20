/************************************************************************
*
* �ļ���   ��  ACLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  �������ε��߼�����
* ��  ע   ��  ��
*
************************************************************************/

#ifndef AC_LOGIC_MANAGER_DATA_H_
#define AC_LOGIC_MANAGER_DATA_H_


#include "ACDefine.h"
#include "../../../Common/CommonTypes.h"
#include "../Switch/SwitchDefine.h"


#ifdef __cplusplus
extern "C" {
#endif

    /*
    * ���������� ����ǰ�����������ڵ��г����з����Ե�ǰ����Ϊ�ο���λ��
    * ����˵���� const UINT8 dirFlag,������(0x55:ǰ������,0xaa:�󷽼���)
    *            const UINT16_S acId,��ǰ��������(Ԥ��)
    *            const UINT16_S otherAcId
    *            const UINT8_S dir,������Ϣ
    * ����ֵ  �� 1��Զ��ο�����
    *            2���ӽ��ο�����
    *            3���޷���
    *            0������ʧ��
    */
	UINT8_S CalculateTrainDirInOtherAc(const UINT8_S dirFlag,const UINT16_S acId,const UINT16_S otherAcId,const UINT8_S dir);

	/*
	* ���������� �����������г�����
	* ����˵������    
	* ����ֵ  ����
	*/
	void CalculateTrainOrderInAc(void);

	/*
	* ���������� ���������������г�����
	* ����˵����const UINT16 trainId,������г�ID
	*           const UINT16_S acId,����Ӽ������� 
	* ����ֵ  ����
	*/
	void CalculateTrainInSingleAc(const UINT16_S trainId,const UINT16_S acId);

	/*
	* ���������� ��������г���������
	* ����˵����const UINT16 trainId,������г�ID
	*           const UINT16_S acId,����Ӽ�������   
	*           const UINT8_S insertIndex,����λ���±�
	* ����ֵ  ����
	*/
	void JudgeInsertTrainOrderInAc(const UINT16_S trainId,const UINT16_S acId,const UINT8_S insertIndex);

	/*
	* ���������� �������һ�н���������ε��г���Ϣ
	* ����˵������    
	* ����ֵ  ����
	*/
	void CalculateLastTrainToAc(void);

	/*
	* ���������� �жϼ��������Ƿ����㴿��ͨ���г�ռ��״̬
	* ����˵������    
	* ����ֵ  ����
	*/
	void ProcessAcUnCommTrainOccState(void);

	/*
	* ���������� ����ǰ������������Ϣ���㵱ǰ��������
	*			 �Ƿ����㴿��ͨ���г�ռ��״̬
	* ����˵����const UINT8 dirFlag,������(0x55:ǰ������,0xaa:�󷽼���)
	*           const UINT16_S acId,��������ID   
	*           const UINT16_S otherAcId,������������ID��ǰ��/�󷽼��ᣩ
	*           const UINT8_S dir,������Ϣ
	* ����ֵ  ��1:���������÷�ͨ���г�ռ��״̬
	*           0:���������÷�ͨ���г�ռ��״̬
	*/
	UINT8_S JudgeAcUnCommTrainOccStateByOtherAc(const UINT8_S dirFlag,const UINT16_S acId,const UINT16_S otherAcId,const UINT8_S dir);

	/*
	* ���������� �������������ι�����Ϣ
	* ����˵���� const UINT16 acId  
	* ����ֵ  �� void  
	*/
	void InitFailureSingleAc(const UINT16_S acId);

	/*
	* ���������� ����ͨ�Ź���Ci��Ӧ�ļ���������Ϣ
	* ����˵���� const UINT16 ciId��ͨ��CiId    
	* ����ֵ  �� void  
	*/
	void InitFailureCiAc(const UINT16_S ciId);

	/*
	* ���������� ����ͨ�Ź���NZc��Ӧ�ļ���������Ϣ
	* ����˵���� const UINT16 nZcId,ͨ��ZcId    
	* ����ֵ  �� void  
	*/
	void InitFailureNZcAc(const UINT16_S nZcId);

	/*
	* ���������� �жϼ��������Ƿ����г�ͣ��
	* ����˵���� const UINT16 acId,��������ID    
	* ����ֵ  �� 0:û���г�ͣ��
	*            1:���г�ͣ��
	*/
	UINT8_S JudgeAcStopStatus(const UINT16_S acId);
	
	/*
	* ���������� ��ռ������ΰ������г�������Ϣ
	* ����˵���� ��   
	* ����ֵ  �� ��
	*/
	void ClearTrainOrderInAc(void);

	/*
	* ���������� �жϼ��������ڵĵ����Ƿ��������պ�λ��״̬
	* ����˵���� const UINT16 acId,��������ID
	* ����ֵ  �� 0:������
	*            1:����
	*/
	UINT8_S JudgeSwitchLockAndPostionInAc(const UINT16_S acId);

	/*
	* ���������� �жϼ��������ڵĵ����Ƿ�����λ��״̬
	* ����˵���� const UINT16 acId,��������ID
	*            UINT16_S outErrorSwitchId[AC_SWITCH_SUM_MAX],�����������ĵ�������
	*            ,UINT8_S *outErrorSwitchNum�������������ĵ�������
	* ����ֵ  �� 0:�����㣨����ԭ��
	*            1:�����㣨����ԭ��
	*            2:����
	*/
	UINT8_S JudgeSwitchPostionInAc(const UINT16_S acId,UINT16_S outErrorSwitchId[AC_SWITCH_SUM_MAX],UINT8_S *outErrorSwitchNum);

	/*
	* ���������� ����ARB�ж�������
	* ����˵���� ��
	* ����ֵ  �� ��
	*/
	void JudgeAxleARB(void);

	/*
	* ���������� �����м����Ѿ��ж�ΪUT�����г��Ѿ���ɨ�ü���󣬽���ת��ΪARB
	* ����˵���� ��
	* ����ֵ  �� ��
	*/
	void ConvertAxleUtToArb(void);

	/*
	* ���������� �����м����Ѿ��ж�ΪARB��������ռ��״̬��Ϊ���к������ARB��־
	* ����˵���� ��
	* ����ֵ  �� ��
	*/
	void ConvertAxleArbToFree(void);

	/*
	* ���������� �жϼ����Ƿ����ڱ�ZC
	* ����˵���� const UINT16 acId
	* ����ֵ  �� RETURN_ERROR��ʧ��
	*			 FLAG_SET�����ڱ�ZC
	*			 FLAG_UNSET:�����ڱ�ZC
	*/
	UINT8_S CheckAcAttribute(const UINT16_S acId);

	/*
	* ���������� �жϴ��м����������ڼ����Ƿ������ARB�ж�����
	* ����˵���� const UINT16 checkedAcId
	* ����ֵ  �� 1������ARB����
	*			 0��������ARB����			 
	*/
	UINT8_S CheckAdjacentAxleArbCondition(const UINT16_S checkedAcId);

	/*
	* ���������� ���м������ڼ����Ƿ�����ARB����
	* ����˵���� const UINT16  checkedAcId, ���м���ID
	*			 const UINT8_S direction����ѯ����
	* ����ֵ  �� 0: ������ARB����
	*			 1������ARB����
	*/
	UINT8_S CheckOneSideAxleArbCondition(const UINT16_S checkedAcId,const UINT8_S direction);

	/*
	* ���������� ���м����������������Ƿ�����ARB����
	* ����˵���� const UINT16  checkedAcId, ���м���ID
	*			 const UINT16_S  adjacentAcId�����ڼ���ID
	*			 const UINT8_S dir, ����
	* ����ֵ  �� 0: ������ARB����
	*			 1������ARB����
	*/
	UINT8_S CheckOneSideNormalAxleArbCondition(const UINT16_S checkedAcId,const UINT16_S adjacentAcId,const UINT8_S dir);

	/*
	* ���������� ���м��������Ŀ������Ƿ�����ARB����
	* ����˵���� const UINT16  adjacentAcId[]�����ڼ���ID
	*            const UINT8_S adjacentAcNum,���ڼ�������
	* ����ֵ  �� 0: ������ARB����
	*			 1������ARB����
	*/
	UINT8_S CheckOneSideLoseAxleArbCondition(const UINT16_S adjacentAcId[],const UINT8_S adjacentAcNum);

	/*
	* ���������� ������RM�г���ɨ״̬ת��
	* ����˵���� ��
	* ����ֵ  �� ��
	*/
	void AcCleanStatusProcess(void);

	/*
	* ���������� ������ɨĬ��״̬����
	* ����˵���� const UINT16 acId
	* ����ֵ  �� ��
	*/
	void DefaultStatusProcess(const UINT16_S acId);

	/*
	* ���������� ������ɨ��ͷ�ѽ���״̬����
	* ����˵���� const UINT16 acId
	*		     const UINT16_S trainId
	* ����ֵ  �� ��
	*/
	void HeadEntryStatusProcess(const UINT16_S acId,const UINT16_S trainId);


	/*
	* ���������� ������ɨ��ͷ����״̬����
	* ����˵���� const UINT16 acId
	*		     const UINT16_S trainId
	* ����ֵ  �� ��
	*/
	void HeadOutStatusProcess(const UINT16_S acId,const UINT16_S trainId);

	/*
	* ���������� ������ɨ��ͷ��β������״̬����
	* ����˵���� const UINT16 acId
	*		     const UINT16_S trainId
	* ����ֵ  �� ��
	*/
	void AllOutStatusProcess(const UINT16_S acId);

	/*
	* ���������� �����м����п��б�Ϊռ�ã������г�ͨ����ά��ռ�ã���������Ϊ����UT
	* ����˵���� ��
	* ����ֵ  �� ��
	*/
	void ConvertAxleFreetoUT(void);

	/*
	* ���������� �����м����Ѿ��ж�ΪARB������ͨ���г��ӽ�����ռ�øü���󣬽���ת��ΪUT
	* ����˵���� ��
	* ����ֵ  �� ��
	*/
	void ConvertAxleArbToUt(void);

	/*
	* ���������� �����м����Ѿ��ж�ΪUT��������ռ��״̬��Ϊ���к������UT��־
	* ����˵���� ��
	* ����ֵ  �� ��
	*/
	void ConvertAxleUtToFree(void);

	/*
	* ���������� �жϴ��м����������ڼ����Ƿ������UT�ж�����
	* ����˵���� const UINT16 checkedAcId
	* ����ֵ  �� 1������UT����
	*			 0��������UT����			 
	*/
	UINT8_S CheckAdjacentAxleUtCondition(const UINT16_S checkedAcId);
	
	/*
	* ���������� ����UT�ж�������
	* ����˵���� ��
	* ����ֵ  �� ��
	*/
	void JudgeAxleUT(void);

	/*
	* ���������� �жϵ������������Ƿ�λ�ڼ���������
	* ����˵���� const UINT16 acId, �������
	*            const UINT8_S acOrderNum, ������������
	*            const UINT16_S acOrderBuff[], ��������
	* ����ֵ  �� 1��λ��
	*			 0����λ��			 
	*/
	UINT8_S JudgeSingleAcInAcOrder(const UINT16_S acId,const UINT8_S acOrderNum,const UINT16_S acOrderBuff[]);

	/*
	* ���������� ��������ļ����Ƿ��������״̬�����պ�λ�ã�
	* ����˵���� const UINT16 acId����������ID   
	* ����ֵ  �� 0:����������
	*            1:��������
	*/
	UINT8_S CalulateSwtichStateOfAcIsNeed(const UINT16_S acId);

	/*
	* ���������� ������ZC���еļ������Σ��������������ĳһ������ΪUT�����������ARB��������ΪUT
	* ����˵���� ��   
	* ����ֵ  �� ��
	*/
	void ConvertSwitchAxleArbToUt(void);

	/*
	* ���������� ��������������Σ������������ĳһ������ΪUT�����������ARB��������ΪUT
	* ����˵���� const UINT16 acId����������ID   
	* ����ֵ  �� 0:ʧ��
	*            1:�ɹ�
	*/
	UINT8_S ConvertSingleSwitchAxleArbToUt(const UINT16_S acId);

	/*
	* ���������� ��������������Σ������������ĳһ������ΪUT�����������ARB��������ΪUT
	* ����˵���� const UINT16 acId����������ID 
	*            UINT8_S *relatedAcNum,������������
	*            UINT16_S relatedAcId[SWITCH_BELONG_AC_SUM_MAX*5],������������
	* ����ֵ  �� 0:����������
	*            1:��������
	*/
	UINT8_S CheckRelatedAcOfInputAc(const UINT16_S acId,UINT8_S *relatedAcNum,UINT16_S relatedAcId[SWITCH_BELONG_AC_SUM_MAX * 5U]);

	/*
     * ���������� �ж��г������ǳ�ͷ��β���Ƿ�λ��ָ��������
     * ����˵���� const UINT16 trainId
			 const UINT16_S acId����������ID   
     * ����ֵ  �� 0:�Ǳ�
     *            1:λ��ָ������
	 *		      2����λ��ָ������
     */
	UINT8_S JudgeTrainBodyInAc(const UINT16_S trainId,const UINT16_S acId);

	/*
	* ���������� �жϵ�ǰ���������Ƿ�����Ҫ��ĵ���λ��״̬
	* ����˵���� const UINT16 acId ����Id
	* ����ֵ  �� 0: ���������״̬
	*			 1: �������״̬    
	*/
	UINT8_S JudgeAcOfSwitchPosInNeed(const UINT16_S acId);

	/*
	* ���������� �жϵ�ǰ�������ε���λ��״̬�Ƿ�Ϊ�Ŀ�״̬
	* ����˵���� const UINT16 acId ����Id
	* ����ֵ  �� FLAG_UNSET: ���Ŀ�״̬
	*			 FLAG_SET: �Ŀ�״̬    
	*/
	UINT8_S CheckAcOfSwitchPosIsSK(const UINT16_S acId);

#ifdef __cplusplus
}
#endif

#endif
