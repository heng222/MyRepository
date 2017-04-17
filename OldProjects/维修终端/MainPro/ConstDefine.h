/*
**   ConstDefine.h
**   ���峣��
**
*/
#if !defined _CONSTDEFINE_H
#define _CONSTDEFINE_H

#define SOH	   0x7D//֡ͷ
#define ETX    0x7E//֡β
#define SBC	   0x04//�ײ���
#define VER    0x10//�汾��
//ת��
#define DLE    0x7F
//֡����
#define DC2    0x12
#define DC3    0x13
#define ACK    0x06
#define NACK   0x15
#define SDI    0x85
#define SDCI   0x8A
#define BCC    0x95
#define TSR    0x9A
#define TSD    0xA5
#define RSR    0xAA
#define ACQ    0x75
#define ACA    0x7A


#define SOCKETINIFILE   _T("ini\\Socket.ini")
#define WSA_VERSION     MAKEWORD(2,0)
#define MAX_HOSTNAME    256
#define MAX_HOSTADDR    40

#define  ANNIUCOMMAND_FRAME_TYPE			0x01	//��ť����

#define  TRAINFRAMEQUEUE_FRAME_TYPE			0x06	//���ζ���
#define  DIAODOCOMMAND_FRAME_TYPE			0x07	//��������
#define  DIAODORETURN_FRAME_TYPE			0x08	//���������ִ
#define  JIEDUANPLAN_FRAME_TYPE				0x09	//�׶μƻ�
#define  JIEDUANPLANRETURN_FRAME_TYPE		0x0A	//�׶μƻ���ִ
#define  SHUAIGUAPLAN_FRAME_TYPE			0x0B	//˦�Ҽƻ�
#define  BAODIAN_FRAME_TYPE					0x0C	//����
#define  GUZHANG_FRAME_TYPE					0x0D	//����
#define  DIAOCHEPLAN_FRAME_TYPE				0x0E	//�����ƻ�
#define  DIAOCHEPLANRETURN_FRAME_TYPE		0x0F	//�����ƻ���ִ
#define  BIANZUINFO_FRAME_TYPE				0x14	//������Ϣ
#define  DIAOCHEREQ_FRAME_TYPE				0x15	//��������
#define  DIAOCHEDELETE_FRAME_TYPE			0x25	//�����ƻ�ɾ��
#define  DIAOCHEJINLUSTATE_FRAME_TYPE		0x26	//������·״̬

#define  ACKLOCK_FRAME_TYPE					0x38	//������Ϣ����֡
#define  TRAINFRAMEREQ_FRAME_TYPE			0x41	//���ο�ȫ����������
#define  DIAOCHEPLANREQ_FRAME_TYPE			0x42	//�����ƻ�����

#define  LOGIN_FRAME_TYPE					0x60	//��¼֡
#define  LOGINRETURN_FRAME_TYPE				0x62	//��¼��ִ
#define  ACKALLSTATIONINFO_FRAME_TYPE		0xEE	//����ȫ������

#endif