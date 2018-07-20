
/********************************************************                                                                                                           
�� �� ���� ChangeLogicManager.h
��    �ߣ� ZC��
����ʱ�䣺 2015.04.18
������ �л������߼��������  
��ע�� ��  
********************************************************/ 

#ifndef CHANGE_LOGIC_MANAGER_H
#define CHANGE_LOGIC_MANAGER_H

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************
������:  JudgeACIsChangeEnd    
��������: ����������ID�Ƿ������л������ն˼���
����: const UINT16 acId ���ж�����
        const UINT8_S dir ���з���
���: ��
����ֵ: RETURN_ERROR ʧ��
            FLAG_SET  ����
			FLAG_UNSET ������
*************************************************/
UINT8_S JudgeACIsChangeEnd(const UINT16_S acId,const UINT8_S dir);

/*************************************************
  ������: JudgeAcIsInChangeLine     
  ��������: ����������ID�Ƿ�������ָ�������л�����
  ����: const UINT16 acId ���ж�����   
       const UINT8_S trainDir ����
  ���: ��
  ����ֵ: RETURN_SUCESS  ����
			 RETURN_ERROR ������
*************************************************/
UINT8_S JudgeAcIsInChangeLine(const UINT16_S acId,const UINT8_S trainDir);

/*
* ���������� �����л������ڱ�ZC��Ͻ��Χ�ڵ��߼�������Ϣ
* ����˵���� UINT16_S *logicNum��
*            UINT16_S logicIdBuff[]
* ����ֵ  �� 1,����ɹ�
*            2,����ʧ��
*/
UINT8_S CalculatChangeAreaLogicInfoOfZc(UINT16_S zcId,UINT16_S *logicNum,UINT16_S logicIdBuff[]);

#ifdef __cplusplus
}
#endif

#endif 
