
#ifndef _DATABASE_TABLE_ATTRBITUE_2938
#define _DATABASE_TABLE_ATTRBITUE_2938


// 数据库相关宏定义 
//////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////////
// 交通信息（原始）实时数据表
#ifdef _DEBUG
#define    T_RAW_TRAFFICNAME    _T("t_trfrawdata")
#else
#define    T_RAW_TRAFFICNAME    _T("T_TFC_RAWDATA_LIVE")
#endif

#define    TI_RT_ROADID         _T("ROADID")        // 道路ID字段
#define    TI_RT_ROADNAME       _T("ROADNAME")      // 道路名称
#define    TI_RT_ROADLEVEL      _T("LINKLEVEL")     // 道路等级
#define    TI_RT_STARTPOSX      _T("STARTPOSX")
#define    TI_RT_STARTPOSY      _T("STARTPOSY")
#define    TI_RT_STARTNAME      _T("STARTNAME")     // 起点名称
#define    TI_RT_ENDPOSX        _T("ENDPOSX")
#define    TI_RT_ENDPOSY        _T("ENDPOSY")
#define    TI_RT_ENDNAME        _T("ENDNAME")       // 终点名称
#define    TI_RT_SPEED          _T("SPEED")
#define    TI_RT_JAMREASON      _T("JAMREASON")
#define    TI_RT_GATHERTIME     _T("GATHERTIME")
//////////////////////////////////////////////////////////////////////////
// 交通信息（原始）历史数据表 
#define    T_TFC_RAWDATA_HISTORY            _T("T_TFC_RAWDATA_HISTORY")
#define    TI_TFCRDH_ROADID                 _T("ROADID")
#define    TI_TFCRDH_ROADNAME               _T("ROADNAME")      
#define    TI_TFCRDH_ROADLEVEL              _T("LINKLEVEL")     
#define    TI_TFCRDH_STARTPOSX              _T("STARTPOSX")
#define    TI_TFCRDH_STARTPOSY              _T("STARTPOSY")
#define    TI_TFCRDH_STARTNAME              _T("STARTNAME")     
#define    TI_TFCRDH_ENDPOSX                _T("ENDPOSX")
#define    TI_TFCRDH_ENDPOSY                _T("ENDPOSY")
#define    TI_TFCRDH_ENDNAME                _T("ENDNAME")       
#define    TI_TFCRDH_SPEED                  _T("SPEED")
#define    TI_TFCRDH_JAMREASON              _T("JAMREASON")
#define    TI_TFCRDH_GATHERTIME             _T("GATHERTIME")


//////////////////////////////////////////////////////////////////////////
// 交通信息（解析后）实时数据表
#ifdef _DEBUG
#define		T_TRFFICINF_NAME    _T("t_trflividx2")
#else
#define		T_TRFFICINF_NAME    _T("T_TFC_PARSEDDATA_LIVE")
#endif

#define     TI_TP_UPDATETIME    _T("U_DATE")        // 更新时间
#define     TI_TP_LINKID        _T("ROAD_ID")       // Link ID
#define     TI_TP_STARTPOSX     _T("START_POSX")    // 
#define     TI_TP_STARTPOSY     _T("START_POSY")    // 
#define     TI_TP_ENDPOSX       _T("END_POSX")      // 
#define     TI_TP_ENDPOSY       _T("END_POSY")      // 
#define     TI_TP_LINKNAME      _T("ROAD_NAME")     // 
#define     TI_TP_SPEED         _T("SPEED")         // 速度
#define     TI_TP_JAMLEVEL      _T("JAM_LEVEL")
#define     TI_TP_JAMREASON     _T("JAM_REASON")
//////////////////////////////////////////////////////////////////////////
// 交通信息（解析后）历史数据表
#define     T_TFC_PARSEDDATA_HISTORY        _T("T_TFC_PARSEDDATA_HISTORY")
#define     TI_TFCPDH_UPDATETIME            _T("U_DATE")   
#define     TI_TFCPDH_LINKID                _T("ROAD_ID")       
#define     TI_TFCPDH_STARTPOSX             _T("START_POSX")    
#define     TI_TFCPDH_STARTPOSY             _T("START_POSY")    
#define     TI_TFCPDH_ENDPOSX               _T("END_POSX")      
#define     TI_TFCPDH_ENDPOSY               _T("END_POSY")      
#define     TI_TFCPDH_LINKNAME              _T("ROAD_NAME")     
#define     TI_TFCPDH_SPEED                 _T("SPEED")         
#define     TI_TFCPDH_JAMLEVEL              _T("JAM_LEVEL")
#define     TI_TFCPDH_JAMREASON             _T("JAM_REASON")



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



//////////////////////////////////////////////////////////////////////////
// 包月用户表
#define     T_FEEUSERS_NAME     _T("T_NAVICP_MONTHLYPAY_USERS" )



//////////////////////////////////////////////////////////////////////////
// 用户注册信息表
#define     T_USERSREG_NAME     _T("T_NAVICP_USERS_REGED")













//////////////////////////////////////////////////////////////////////////
// End of file
#endif