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
//##########################################################################################
/*ʩ���Ǽǻ�����		*/
#define		CONSTFAMEMAXLEN				500				//ʩ������֡����󳤶�
#define		CONSTFRAMEKIND				0X28			//ʩ���Ǽ�����֡����
#define		CONSTREGISTER				0x00			//ʩ������֡���������Ϊ�Ǽ�
#define		CONSTCLEARREG				0X01			//ʩ������֡���������Ϊ����
#define		CONSTMENDCLEARSTORY			0X01			//�촰��
#define		CONSTMENDSECTION			0X02			//������
//##########################################################################################
/*��������֡			*/
#define		DISPHCOMINITNUM				1000				//���������ŵĳ�ʼֵ
#define		DISPHFRAMEMAXLEN			1024				//��������֡����󳤶�
#define		DISPHFRAMEKIND				0x07				//��������֡����
#define		DISPHFUNTCODE				0X40				//�����룬����λΪ1����ʾ�й�ά�޵�����
#define		DISPHFROMDISPH				144					//���е�̨��д�´�
#define		DISPHFROMMEND				LOCAL_MACHINE_CODE	//��ά��̨��д�´�
#define		DISPHCHECKSTATUSF			0X00				//δ����Ҳ���Ҫ��ˣ������´
#define		DISPHCHECKSTATUSS			0X01				//δ�������Ҫ��ˣ�������ˣ�
#define		DISPHCHECKSTATUST			0X11				//��Ҫ���������ˣ������´
#define		DISPHKINDCLOSE				0X01				//��������
#define		DISPHKINDOPEN				0X02				//��ͨ����
//##########################################################################################
/*���������ִ֡		*/
#define		DISPHCONFIRMMAXLEN			50			//���������ִ֡����󳤶�
#define		DISPHCONFIRMKIND			0X08		//���������ִ֡����
#define		DISPHCONFIRMMACHINE			0X01		//������ִ
#define		DISPHCONFIRMHUMAN			0X02		//�˹���ִ
//##########################################################################################
#define		RECORDMAXNUM				50			//һ���е����ʩ����Ŀ(//���ؼ�¼������)
#define		OPERATORMAXNUM				20			//�������Ա��������(//�Ϸ��û���)
//##########################################################################################
//�����ļ����ڵ�·��
#define		NEWMESSAGEPATHNAME			"ini\\NewMessage.msg"	//��δ�鿴������Ϣ
#define		STATIONINFOPATHNAME			"ini\\main.ini"			//վ����Ϣ
#define		MENDTEMPLATEPATHNAME		"ini\\MendKind.dat"		//ʩ��ģ��
#define		OPERATORINFOPATHNAME		"ini\\OperatorInf"		//����Ա��Ϣ
#define		RESPONSEINFPATHNAME			"ResponseContent\\"		//��ִ��Ϣ���ڵ�Ŀ¼
//##########################################################################################
#define		LOCAL_MACHINE_CODE					0X30			//�ۺ�ά�޹���վ�Ĵ���
//##########################################################################################
#define		ASKALLSTATIONINFO_FRAME_TYPE		0xEE			//����ȫ��֡��֡����
#define		ASKLOCK_FRAME_TYPE					0x38			//������Ϣ����֡��֡����
//##########################################################################################

#endif