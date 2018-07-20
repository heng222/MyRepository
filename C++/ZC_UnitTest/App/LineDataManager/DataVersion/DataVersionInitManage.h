/************************************************************************
*
* �ļ���   ��  DataVersionInitManage.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ���ݰ汾��ʼ������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef DATA_VERSION_INIT_MANAGE_H_
#define DATA_VERSION_INIT_MANAGE_H_

#include "../../../Common/CommonTypes.h"


#ifdef __cplusplus
extern "C" {
#endif
	
	/*
	* ���������� ��ʼ���������ݰ汾��Ϣ
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			 1: ��ʼ���ɹ�
	*/
	UINT8_S InitLocalDataVersion(void);

	/*
	* ���������� ��ʼ���������ݰ汾��Ϣ(ZC�ֽ����ݰ汾)
	* ����˵���� ��   
	* ����ֵ  �� 0: ��ʼ��ʧ��
	*			 1: ��ʼ���ɹ�
	*/
	UINT8_S InitLocalZcSelfDataVersion(void);

    /*
    * ���������� ��ʼ���������ݰ汾��Ϣ(ZC��ATP���ݰ汾)
    * ����˵���� ��   
    * ����ֵ  �� 0: ��ʼ��ʧ��
    *			 1: ��ʼ���ɹ�
    */
    UINT8_S InitZcAtpDataVersion(void);

#ifdef __cplusplus
}
#endif

#endif
