//##########################################################################################
/*ʩ���Ǽǻ�����		*/
#define		CONSTFAMEMAXLEN				500			//ʩ������֡����󳤶�
#define		CONSTFRAMEKIND				0X28		//ʩ���Ǽ�����֡����
#define		CONSTREGISTER				0x00		//ʩ������֡���������Ϊ�Ǽ�
#define		CONSTCLEARREG				0X01		//ʩ������֡���������Ϊ����
#define		CONSTMENDCLEARSTORY			0X01		//�촰��
#define		CONSTMENDSECTION			0X02		//������
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
#define		NEWMESSAGEPATHNAME			"ini\\NewMessage.msg"		//��δ�鿴������Ϣ
#define		REACORDPATHNAME				"Record\\"				//ά���ն���ʩ����¼��ŵ�λ��
#define		STATIONINFOPATHNAME			"ini\\StationInf.ini"			//վ����Ϣ
#define		MENDTEMPLATEPATHNAME		"ini\\MendKind.dat"		//ʩ��ģ��
#define		OPERATORINFOPATHNAME		"ini\\OperatorInf"		//����Ա��Ϣ
//##########################################################################################
#define		LOCAL_MACHINE_CODE					48			//�ۺ�ά�޹���վ�Ĵ���
//##########################################################################################
#define		ASKALLSTATIONINFO_FRAME_TYPE		0xEE		//����ȫ��֡��֡����
#define		ASKLOCK_FRAME_TYPE					0x38		//������Ϣ����֡��֡����
//##########################################################################################
#define		WM_ANALYSEDISPATCHFRAME		(WM_USER+201)		//��������˵ĵ�������֡
#define		WM_SENDCONFIRMFRAME			(WM_USER+203)		//���ͻ�ִ��Ϣ���ۺ�ά�޹���վ
