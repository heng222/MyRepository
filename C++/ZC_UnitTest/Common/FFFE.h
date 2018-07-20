/************************************************************************
*
* �ļ���   ��  FFFE.h
* ��Ȩ˵�� ��  
* �汾��   ��  1.0  
* ����ʱ�� ��  2009.08.17
* ����     ��  
* �������� ��  FFFEЭ��ת�弰�����ļ� 
* ʹ��ע�� ��  1.���ܴ���ĳ���Ϊ65535����Ϊ�ܳ��ȵ�����UINT16���ơ�
* �޸ļ�¼ ��  
*
************************************************************************/
#ifndef _FFFE_H
#define _FFFE_H

#include "CommonTypes.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct  
{
  UINT8_S *pRawDataRcvBuf;/*δ��ת�����ݽ��ջ�����*/
  UINT16_S RawDataRcvBufferSize;/*δ��ת�����ݽ��ջ�������С*/
  UINT8_S RcvState ;/*FFFE���ݽ���״̬*/
  UINT8_S GotFrame ;/*FFFE�Ƿ��յ�������֡*/
  UINT16_S DataCount ;/* �յ�����֮֡ǰ�����յ���FFFE�����ܳ��ȣ�ÿ���յ�����֡������*/
}FFFE_STATE_STRU;

/*
* ���������� �����ݽ���FFFEת�崦������ͷFFFE��βFFFD����
* ��������� const UINT8_S *pSrc    ����(��FFFEת��)
*            UINT16_S SrcLen        ����(��FFFEת��)�ĳ���
* ��������� UINT8_S *pTgt          ����(����FFFEת��)
* ����ֵ��   ת���ĳ���   
*/
UINT16_S TranslateToFFFE(const UINT8_S *pSrc, UINT8_S *pTgt,UINT16_S SrcLen);


/*
* ����������  ������FFFEת�崦�������ݣ��Ѿ�ȥ����ͷFFFE��βFFFD����ԭΪԭʼ����
* ���������  const UINT8_S *pSrc,    ����(FFFEת��)
*             UINT16_S SrcLen,        ����(FFFEת��)�ĳ���
* ���������  UINT8_S *pTgt,          ����(ȥ��FFFEת��)
* ����ֵ��    ����0,  ת��ɹ�,����ת�������ݳ���
*             0,   �в���ת����ַ���ת��ʧ�ܡ�����ת�������ݳ���Ϊ0   
*/
UINT16_S TranslateFromFFFE(const UINT8_S *pSrc,UINT8_S *pTgt,UINT16_S SrcLen);

/*
* ����������  FFFE�ṹ���ʼ������
* ���������  UINT16_S FFFEBufferSize, ���ڽ���һ֡���ݵĻ���������   
*             PORT_STATE_STRU *pFFFEStatStru, FFFE״̬�ṹ��
* ����ֵ��    0,����ִ��ʧ��
*             1,����ִ�гɹ�
*/
UINT8_S FFFEInit(FFFE_STATE_STRU *pFFFEStatStru,UINT16_S FFFEBufferSize);

/*
* ����������   ���ַ����մ���ת������ݣ������֡FFFE���ģ�����FFFE��FFFD����
* ���������   UINT8_S RcvChar,      ��ǰ���յ��ַ�
*              PORT_STATE_STRU *pFFFEStatStru,
* ���������   UINT8_S *pRawDataRcv,  ���ݽ��ջ�����ָ��
* ����ֵ��     ����0,  ��ʾ�յ�����֡�����ݳ��ȣ������յ�������֡���������ջ�������
*              0,   δ�յ���֡���ݣ� 
*/

UINT16_S FFFERcv(FFFE_STATE_STRU *pFFFEStatStru,UINT8_S RcvChar, UINT8_S *pRawDataRcv);

/*
* ����������  FFFE״̬������
* ���������  PORT_STATE_STRU *pFFFEStatStru, FFFE״̬�ṹ��
* ����ֵ��     
*/
void FFFEFree(FFFE_STATE_STRU *pFFFEStatStru);

/*
* ���������� �����ݽ���FFFEת�崦��,��ͷFFFE��βFFFD
* ��������� const UINT8_S *pSrc    ����(��FFFEת��)
*            UINT16_S SrcLen        ����(��FFFEת��)�ĳ���
* ��������� UINT8_S *pTgt          ����(����FFFEת��),�����FFFEͷ��FFFDβ
* ����ֵ��   ת���ĳ���   
*/
UINT16_S FFFEPack(const UINT8_S *pSrc, UINT8_S *pTgt,UINT16_S SrcLen);

#ifdef __cplusplus
}
#endif

#endif
