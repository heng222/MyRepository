/*
**   ConstDefine.h
**   定义常量
**
*/
#if !defined _CONSTDEFINE_H
#define _CONSTDEFINE_H

#define SOH	   0x7D//帧头
#define ETX    0x7E//帧尾
#define SBC	   0x04//首部长
#define VER    0x10//版本号
//转义
#define DLE    0x7F
//帧类型
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

#define  ANNIUCOMMAND_FRAME_TYPE			0x01	//按钮命令

#define  TRAINFRAMEQUEUE_FRAME_TYPE			0x06	//车次队列
#define  DIAODOCOMMAND_FRAME_TYPE			0x07	//调度命令
#define  DIAODORETURN_FRAME_TYPE			0x08	//调度命令回执
#define  JIEDUANPLAN_FRAME_TYPE				0x09	//阶段计划
#define  JIEDUANPLANRETURN_FRAME_TYPE		0x0A	//阶段计划回执
#define  SHUAIGUAPLAN_FRAME_TYPE			0x0B	//甩挂计划
#define  BAODIAN_FRAME_TYPE					0x0C	//报点
#define  GUZHANG_FRAME_TYPE					0x0D	//故障
#define  DIAOCHEPLAN_FRAME_TYPE				0x0E	//调车计划
#define  DIAOCHEPLANRETURN_FRAME_TYPE		0x0F	//调车计划回执
#define  BIANZUINFO_FRAME_TYPE				0x14	//编组信息
#define  DIAOCHEREQ_FRAME_TYPE				0x15	//调车请求
#define  DIAOCHEDELETE_FRAME_TYPE			0x25	//调车计划删除
#define  DIAOCHEJINLUSTATE_FRAME_TYPE		0x26	//调车进路状态

#define  ACKLOCK_FRAME_TYPE					0x38	//封锁信息请求帧
#define  TRAINFRAMEREQ_FRAME_TYPE			0x41	//车次框全部内容请求
#define  DIAOCHEPLANREQ_FRAME_TYPE			0x42	//调车计划请求

#define  LOGIN_FRAME_TYPE					0x60	//登录帧
#define  LOGINRETURN_FRAME_TYPE				0x62	//登录回执
#define  ACKALLSTATIONINFO_FRAME_TYPE		0xEE	//请求全场数据
//##########################################################################################
/*施工登记或消记		*/
#define		CONSTFAMEMAXLEN				500				//施工请求帧的最大长度
#define		CONSTFRAMEKIND				0X28			//施工登记消记帧类型
#define		CONSTREGISTER				0x00			//施工请求帧中请求类别为登记
#define		CONSTCLEARREG				0X01			//施工请求帧中请求类别为消记
#define		CONSTMENDCLEARSTORY			0X01			//天窗修
#define		CONSTMENDSECTION			0X02			//区间修
//##########################################################################################
/*调度命令帧			*/
#define		DISPHCOMINITNUM				1000				//调度命令编号的初始值
#define		DISPHFRAMEMAXLEN			1024				//调度命令帧的最大长度
#define		DISPHFRAMEKIND				0x07				//调度命令帧类型
#define		DISPHFUNTCODE				0X40				//功能码，第七位为1，表示有关维修的命令
#define		DISPHFROMDISPH				144					//由行调台编写下达
#define		DISPHFROMMEND				LOCAL_MACHINE_CODE	//由维修台编写下达
#define		DISPHCHECKSTATUSF			0X00				//未审核且不需要审核（命令下达）
#define		DISPHCHECKSTATUSS			0X01				//未审核且需要审核（请求审核）
#define		DISPHCHECKSTATUST			0X11				//需要审核且已审核（命令下达）
#define		DISPHKINDCLOSE				0X01				//封锁命令
#define		DISPHKINDOPEN				0X02				//开通命令
//##########################################################################################
/*调度命令回执帧		*/
#define		DISPHCONFIRMMAXLEN			50			//调度命令回执帧的最大长度
#define		DISPHCONFIRMKIND			0X08		//调度命令回执帧类型
#define		DISPHCONFIRMMACHINE			0X01		//机器回执
#define		DISPHCONFIRMHUMAN			0X02		//人工回执
//##########################################################################################
#define		RECORDMAXNUM				50			//一天中的最多施工数目(//本地记录数据类)
#define		OPERATORMAXNUM				20			//允许操作员的最大个数(//合法用户类)
//##########################################################################################
//各种文件所在的路径
#define		NEWMESSAGEPATHNAME			"ini\\NewMessage.msg"	//尚未查看的新消息
#define		STATIONINFOPATHNAME			"ini\\main.ini"			//站场信息
#define		MENDTEMPLATEPATHNAME		"ini\\MendKind.dat"		//施工模板
#define		OPERATORINFOPATHNAME		"ini\\OperatorInf"		//操作员信息
#define		RESPONSEINFPATHNAME			"ResponseContent\\"		//回执信息所在的目录
//##########################################################################################
#define		LOCAL_MACHINE_CODE					0X30			//综合维修工作站的代码
//##########################################################################################
#define		ASKALLSTATIONINFO_FRAME_TYPE		0xEE			//请求全场帧的帧类型
#define		ASKLOCK_FRAME_TYPE					0x38			//封锁信息请求帧的帧类型
//##########################################################################################

#endif