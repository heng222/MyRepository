//##########################################################################################
/*施工登记或消记		*/
#define		CONSTFAMEMAXLEN				500			//施工请求帧的最大长度
#define		CONSTFRAMEKIND				0X28		//施工登记消记帧类型
#define		CONSTREGISTER				0x00		//施工请求帧中请求类别为登记
#define		CONSTCLEARREG				0X01		//施工请求帧中请求类别为消记
#define		CONSTMENDCLEARSTORY			0X01		//天窗修
#define		CONSTMENDSECTION			0X02		//区间修
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
#define		NEWMESSAGEPATHNAME			"ini\\NewMessage.msg"		//尚未查看的新消息
#define		REACORDPATHNAME				"Record\\"				//维修终端中施工记录存放的位置
#define		STATIONINFOPATHNAME			"ini\\StationInf.ini"			//站场信息
#define		MENDTEMPLATEPATHNAME		"ini\\MendKind.dat"		//施工模板
#define		OPERATORINFOPATHNAME		"ini\\OperatorInf"		//操作员信息
//##########################################################################################
#define		LOCAL_MACHINE_CODE					48			//综合维修工作站的代码
//##########################################################################################
#define		ASKALLSTATIONINFO_FRAME_TYPE		0xEE		//请求全场帧的帧类型
#define		ASKLOCK_FRAME_TYPE					0x38		//封锁信息请求帧的帧类型
//##########################################################################################
#define		WM_ANALYSEDISPATCHFRAME		(WM_USER+201)		//分析已审核的调度命令帧
#define		WM_SENDCONFIRMFRAME			(WM_USER+203)		//发送回执消息给综合维修工作站
