/************************************************************************
*
* �ļ���   ��  MainLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  Ӧ�ú������߼�����
* ��  ע   ��  ��
*
************************************************************************/
#ifndef MAIN_LOGIC_MANAGER_H_
#define MAIN_LOGIC_MANAGER_H_

#include "../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
* ���������� ZC��ϵͳӦ�ó������߼�����
* ����˵���� ��
* ����ֵ  �� 1:�߼�ִ������
*            0:�߼�ִ���쳣
*/
UINT8_S ZcAppMainLogicManager(void);

/*
* ���������� ZC��ϵͳӦ�ó�����ں���
* ����˵���� ��
* ����ֵ  �� 1:�߼�ִ������
*            0:�߼�ִ���쳣
*/
INT8_S ZcSystemAppMain(void);

#ifdef __cplusplus
}
#endif

#endif
