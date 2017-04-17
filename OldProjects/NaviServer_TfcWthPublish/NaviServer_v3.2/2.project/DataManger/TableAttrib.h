
#ifndef _DATABASE_TABLE_ATTRBITUE_2938
#define _DATABASE_TABLE_ATTRBITUE_2938


// 数据库相关宏定义 
//////////////////////////////////////////////////////////////////////////
//
//#define _TEST_DB_LIVE_

// ------------------------   交通信息   ------------------------------

//////////////////////////////////////////////////////////////////////////
// 交通事件

#define     T_TFC_EVENT_LIVE    _T("T_TFC_EVENT_LIVE")

#define     TI_TE_EVENTID       _T("EVENTID")       // 事件ID
#define     TI_TE_ALARMTIME     _T("ALARMTIME")     // 报警时间
#define     TI_TE_EVETTYPE      _T("EVETTYPE")      // 
#define     TI_TE_HANLDEDSTATE  _T("HANLDEDSTATE")  // 处理状态
#define     TI_TE_VALIDFLAG     _T("VALIDFLAG")     // 是否有效
#define     TI_TE_PHONENO       _T("PHONENO")       // 电话
#define     TI_TE_PHONEX        _T("PHONEX")        // 电话定位的经度，精确到1/24秒
#define     TI_TE_PHONEY        _T("PHONEY")        // 
#define     TI_TE_ADDRX         _T("ADDRX")         // 案发地点的经度，精确到1/24秒
#define     TI_TE_ADDRY         _T("ADDRY")         // 
#define     TI_TE_CASEADDR      _T("CASEADDR")      // 案发地点
#define     TI_TE_CONTENT       _T("CONTENT")       // 报警内容


//////////////////////////////////////////////////////////////////////////
// 交通流（原始）实时数据表

//#ifdef _DEBUG
//#define    T_RAW_TRAFFICNAME    _T("t_trfrawdata")
//#else
#define    T_RAW_TRAFFICNAME    _T("T_TFC_RAWDATA_LIVE")
//#endif

#define    TI_RT_ROADID_OLD     _T("ROADID")        // 提供商的道路ID
#define    TI_RT_ROADID_NEW     _T("ROADID_NEW")    // 我方的道路ID
#define    TI_RT_ROADNAME       _T("ROADNAME")      // 道路名称
#define    TI_RT_ROADLEVEL      _T("LINKLEVEL")     // 道路等级
#define    TI_RT_STARTPOSX      _T("STARTPOSX")
#define    TI_RT_STARTPOSY      _T("STARTPOSY")
#define    TI_RT_CORSTAPX       _T("CORSTAPX")      // 对应到瑞图数据的起点经度
#define    TI_RT_CORSTAPY       _T("CORSTAPY")      // 
#define    TI_RT_STARTNAME      _T("STARTNAME")     // 起点名称
#define    TI_RT_ENDPOSX        _T("ENDPOSX")
#define    TI_RT_ENDPOSY        _T("ENDPOSY")
#define    TI_RT_CORENDPX       _T("CORENDPX")      // 对应到瑞图数据的终点经度
#define    TI_RT_CORENDPY       _T("CORENDPY")
#define    TI_RT_ENDNAME        _T("ENDNAME")       // 终点名称
#define    TI_RT_SPEED          _T("SPEED")
#define    TI_RT_JAMREASON      _T("JAMREASON")
#define    TI_RT_GATHERTIME     _T("GATHERTIME")


//////////////////////////////////////////////////////////////////////////
// 交通流（原始）历史数据表 

#define    T_TFC_RAWDATA_HISTORY            _T("T_TFC_RAWDATA_HISTORY")
#define    TI_TFCRDH_ROADID                 _T("ROADID")
#define    TI_TFCRDH_ROADNAME               _T("ROADNAME")      
#define    TI_TFCRDH_ROADLEVEL              _T("LINKLEVEL")     
#define    TI_TFCRDH_STARTPOSX              _T("STARTPOSX")
#define    TI_TFCRDH_STARTPOSY              _T("STARTPOSY")
#define    TI_TFCRDH_CORSTAPX               _T("CORSTAPX")      // 对应到瑞图数据的起点经度
#define    TI_TFCRDH_CORSTAPY               _T("CORSTAPY")      // 
#define    TI_TFCRDH_STARTNAME              _T("STARTNAME")     
#define    TI_TFCRDH_ENDPOSX                _T("ENDPOSX")
#define    TI_TFCRDH_ENDPOSY                _T("ENDPOSY")
#define    TI_TFCRDH_CORENDPX               _T("CORENDPX")      // 对应到瑞图数据的终点经度
#define    TI_TFCRDH_CORENDPY               _T("CORENDPY")
#define    TI_TFCRDH_ENDNAME                _T("ENDNAME")       
#define    TI_TFCRDH_SPEED                  _T("SPEED")
#define    TI_TFCRDH_JAMREASON              _T("JAMREASON")
#define    TI_TFCRDH_GATHERTIME             _T("GATHERTIME")


//////////////////////////////////////////////////////////////////////////
// 交通流（解析后）实时数据表
//
#ifdef _TEST_DB_LIVE_
#define		T_TRFFICINF_NAME    _T("TEST_T_TFC_PARSEDDATA_LIVE")
#else
#define		T_TRFFICINF_NAME    _T("T_TFC_PARSEDDATA_LIVE")
#endif


#define     TI_TP_UPDATETIME    _T("U_DATE")        // 更新时间
#define     TI_TP_LINKID        _T("LINKID")        // Link ID
#define     TI_TP_ROADID        _T("ROADID")        // Road ID
#define     TI_TP_STARTPOSX     _T("START_POSX")    // 
#define     TI_TP_STARTPOSY     _T("START_POSY")    // 
#define     TI_TP_ENDPOSX       _T("END_POSX")      // 
#define     TI_TP_ENDPOSY       _T("END_POSY")      // 
#define     TI_TP_LINKNAME      _T("ROAD_NAME")     // 
#define     TI_TP_SPEED         _T("SPEED")         // 速度
#define     TI_TP_JAMLEVEL      _T("JAM_LEVEL")
#define     TI_TP_JAMREASON     _T("JAM_REASON")

//////////////////////////////////////////////////////////////////////////
// 交通流（解析后）历史数据表

#define     T_TFC_PARSEDDATA_HISTORY        _T("T_TFC_PARSEDDATA_HISTORY")
#define     TI_TFCPDH_UPDATETIME            _T("U_DATE")   
#define     TI_TFCPDH_LINKID                _T("LINKID")
#define     TI_TFCPDH_ROADID                _T("ROADID")        // Road ID
#define     TI_TFCPDH_STARTPOSX             _T("START_POSX")    
#define     TI_TFCPDH_STARTPOSY             _T("START_POSY")    
#define     TI_TFCPDH_ENDPOSX               _T("END_POSX")      
#define     TI_TFCPDH_ENDPOSY               _T("END_POSY")      
#define     TI_TFCPDH_LINKNAME              _T("ROAD_NAME")     
#define     TI_TFCPDH_SPEED                 _T("SPEED")         
#define     TI_TFCPDH_JAMLEVEL              _T("JAM_LEVEL")
#define     TI_TFCPDH_JAMREASON             _T("JAM_REASON")


// ------------------------   气象信息   ------------------------------

//////////////////////////////////////////////////////////////////////////
// 北京市气象信息表名

#define		T_WTHTABLE_NAME		_T("T_WTHPREARE")
#define     TI_WT_PUBDATE       _T("PUB_DATE")      // 发布时间字段
#define     TI_WT_PERIOD        _T("PERIOD")
#define     TI_WT_AREAID        _T("AREA_ID")
#define     TI_WT_AREANAME      _T("AREA_NAME")
#define     TI_WT_WEATHER       _T("WEATHER")
#define     TI_WT_MAXTEMP       _T("TEMPERATURE_MAX")
#define     TI_WT_MINTEMP       _T("TEMPERATURE_MIN")
#define     TI_WT_MAXWINDPOWER  _T("WIND_POWER_MAX")
#define     TI_WT_MINWINDPOWER  _T("WIND_POWER_MIN")
#define     TI_WT_WIDDIRECTION  _T("WIND_DIRECTION")
#define     TI_WT_HUMIDITY      _T("HUMIDITY")


//////////////////////////////////////////////////////////////////////////
// 全国主要城市气象信息表名

#define     T_WTH_MAINCITYS     _T("T_CITYWEATHER")
#define     TI_WM_CITYCODE      _T("CITY_CODE")         // 字段：城市编码
#define     TI_WM_CITYNAME      _T("CITY_NAME")         // 字段：城市名称
#define     TI_WM_CURWTH        _T("CUR_WEATHER_DES")   // 字段：当前气象描述
#define     TI_WM_LIFEIDX       _T("LIFE_INDEX")        // 字段：生活指数


// ------------------------   其它   ------------------------------

//////////////////////////////////////////////////////////////////////////
// 包月用户表

#define     T_FEEUSERS_NAME     _T("T_NAVICP_MONTHLYPAY_USERS" )



//////////////////////////////////////////////////////////////////////////
// 用户注册信息表

#define     T_USERSREG_NAME     _T("T_NAVICP_USERS_REGED")













//////////////////////////////////////////////////////////////////////////
// End of file
#endif