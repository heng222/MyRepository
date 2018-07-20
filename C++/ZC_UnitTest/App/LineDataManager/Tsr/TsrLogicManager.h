/************************************************************************
*
* �ļ���   ��  TsrLogicManager.h
* ����ʱ�� ��  2015.04.18
* ����     ��  ZC��
* �������� ��  ��ʱ�����߼��������
* ��  ע   ��  ��
*
************************************************************************/
#ifndef TSR_LOGCI_MANAGER_H_
#define TSR_LOGCI_MANAGER_H_

#include "../../../Common/CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

	/*
	* ���������� ɾ��ĳ��ZCID����ʱ������Ϣ
	* ����˵���� const UINT16 zcId, Id��Ϣ    
	* ����ֵ  �� ��     
	*/
	void DeleteSingleZcTsrInfo(const UINT16_S zcId);

    /*
    * ���������� ��ѯ����ZC��������ʱ������Ϣ�Ƿ��ڱ�ZC��
    * ����˵���� const UINT16_S startLink, ���Link 
    *            const UINT32_S startOffset, ���Offset
    *            const UINT16_S endLink,  �յ�Link
    *            const UINT32_S endOffset �յ�Offset
    * ����ֵ  �� ��     
    */
    UINT8_S CheckMaTsrInLocalZc(const UINT16_S startLink,const UINT32_S startOffset,const UINT16_S endLink,const UINT32_S endOffset);

#ifdef __cplusplus
}
#endif

#endif
