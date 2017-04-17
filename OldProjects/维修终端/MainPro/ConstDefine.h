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

#endif