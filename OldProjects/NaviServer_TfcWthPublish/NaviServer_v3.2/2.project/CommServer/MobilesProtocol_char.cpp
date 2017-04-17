#include "stdafx.h"
#include "MobilesProtocol_char.h"
#include "CommonFunc.h"

#pragma warning(disable:4244)

//////////////////////////////////////////////////////////////////////////
// _content_header
_mobile_comm_frame_char::_mobile_comm_frame_char()
{
    cHeader[0] = '@';
    cHeader[1] = '@';
    
#ifdef _NEW_CHAR_PROTOCOL
    memset(cVersion,'1',sizeof(cVersion));
#endif

    wCmdID = 0;
    wBlockSize = 0;

    //request ID
    /*SYSTEMTIME sysTime;
    COleDateTime curTime = COleDateTime::GetCurrentTime();
    curTime.GetAsSystemTime(sysTime);
    CString strRst;
    strRst.Format("%04d%02d%02d%02d%02d%02d%02d",
        sysTime.wYear,
        sysTime.wMonth,
        sysTime.wDay,
        sysTime.wHour,
        sysTime.wMinute,
        sysTime.wSecond,
        sysTime.wMilliseconds);
    memcpy(cMobileNo,strRst.GetBuffer(0),sizeof(cMobileNo));*/

    // Mobile number
    //memset(strMobileNo,'0',sizeof(strMobileNo));
}
_mobile_comm_frame_char::~_mobile_comm_frame_char()
{

}
WORD _mobile_comm_frame_char::GetCommandID() const
{
    return 0;
}
int _mobile_comm_frame_char::GetProType()
{
    return E_PRO_FLAG;
}
CString _mobile_comm_frame_char::GetProName()
{
    return _T("与手机终端的通信协议-Character");
}
void _mobile_comm_frame_char::CalculateBlockSize()
{
    wBlockSize = 0;
}
void _mobile_comm_frame_char::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    CString strTmp;
    CString strFormat;

    // 帧头
    memcpy(lpBuffer+aIndex,cHeader,sizeof(cHeader));
    aIndex += sizeof(cHeader);

    // Version
#ifdef _NEW_CHAR_PROTOCOL
    memcpy(lpBuffer+aIndex,cVersion,sizeof(cVersion));
    aIndex += sizeof(cVersion);
#endif

    // 指令码
    strFormat.Format("%%0%dX",ELenCommand);
    strTmp.Format(strFormat,wCmdID);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),ELenCommand);
    aIndex += ELenCommand;

    // 协议体大小
    strFormat.Format("%%0%dX",ESizeBlock);
    strTmp.Format(strFormat,wBlockSize);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),ESizeBlock);
    aIndex += ESizeBlock;

    // Cellphone number
    strFormat.Format("%%0%ds",ELenOfCellphoneNo);
    strTmp.Format(strFormat,strMobileNo);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
    aIndex += ELenOfCellphoneNo;

#ifdef _NEW_CHAR_PROTOCOL
    // 计费类型
    strFormat.Format("%%0%dX",ELenOfFeeType);
    strTmp.Format(strFormat,byFeeType);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
    aIndex += ELenOfFeeType;
#endif

}
BOOL _mobile_comm_frame_char::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Head's flag
    memcpy(cHeader,lpBuffer+aIndex,sizeof(cHeader));
    aIndex += sizeof(cHeader);

#ifdef _NEW_CHAR_PROTOCOL
    // Version
    memcpy(cVersion,lpBuffer+aIndex,sizeof(cVersion));
    aIndex += sizeof(cVersion);
#endif

    // Command ID  
    char cTmp[20] = {0};
    memcpy(cTmp,lpBuffer+aIndex,ELenCommand);
    wCmdID = (WORD)StrHextoDeci(cTmp);
    aIndex += ELenCommand;

    // Block size
    memset(cTmp,0,sizeof(cTmp));
    memcpy(cTmp,lpBuffer+aIndex,ESizeBlock);
    wBlockSize = (WORD)StrHextoDeci(cTmp);
    aIndex += ESizeBlock;

    // Cellphone number
    memset(cTmp,0,sizeof(cTmp));
    memcpy(cTmp,lpBuffer+aIndex,ELenOfCellphoneNo);
    strMobileNo = CString(cTmp).TrimLeft("0");
    aIndex += ELenOfCellphoneNo;

#ifdef _NEW_CHAR_PROTOCOL
    // Type of payment
    memset(cTmp,0,sizeof(cTmp));
    memcpy(cTmp,lpBuffer+aIndex,ELenOfFeeType);
    byFeeType = (BYTE)StrHextoDeci(cTmp);
    aIndex += ELenOfFeeType;
#endif

    return TRUE;
}
void _mobile_comm_frame_char::SetMobileNo(__int64 llMobileNo)
{
    strMobileNo.Format("%I64d",llMobileNo);
}
_mobile_comm_frame_char* _mobile_comm_frame_char::GetInstance(WORD wCommandID)
{
    PTMobileFrame_Char pContent = NULL;
    switch(wCommandID)
    {
        // Register
    case TRegRequest_Char::ECommandID:
        pContent = new TRegRequest_Char;
        break;
    case TRegisterRsp::ECommandID:
        pContent = new TRegisterRsp;
        break;

        // Login
    case TLoginReq_Char::ECommandID:
        pContent = new TLoginReq_Char;
        break;
    case TLoginRsp_Char::ECommandID:
        pContent = new TLoginRsp_Char;
        break;

        // Exit
    case TClientExit_Char::ECommandID:
        pContent = new TClientExit_Char;
        break;

    case TOnlineTest::ECommandID:
        pContent = new TOnlineTest;
        break;

        // Weather
    case TWeatherReq_Char::ECommandID:
        pContent = new TWeatherReq_Char;
        break;
    case TWeatherRsp1_char::ECommandID:
        pContent = new TWeatherRsp1_char;
        break;
    case TWeatherRsp2_char::ECommandID:
        pContent = new TWeatherRsp2_char;
        break;

        // Traffic
    case TTfcReqByPos_char::ECommandID:
        pContent = new TTfcReqByPos_char;
        break;
    case TTfcReqByRoadName_Char::ECommandID:
        pContent = new TTfcReqByRoadName_Char;
        break;
    case TTfcRsp1_Char::ECommandID:
        pContent = new TTfcRsp1_Char;
        break;
    case TTfcRsp2_Char::ECommandID:
        pContent = new TTfcRsp2_Char;
        break;
    }

    if (pContent!=NULL)
    {
        pContent->SetAutoDel(TRUE);
    }

    return pContent;
}

/////////////////////////////////////////////////////////////////////////////////
// REG1. 用户注册请求
_register_request_char::_register_request_char()
{
    wCmdID = GetCommandID();
}
WORD _register_request_char::GetCommandID() const
{
    return ECommandID;
}
//void _register_request_char::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
//{
//
//}
BOOL _register_request_char::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    BOOL rc = _mobile_comm_frame_char::ParseBuffer(lpBuffer,aIndex);
    if (!rc)
    {
        return FALSE;
    }

    //user name
    char cLen[5] = {0};
    memcpy(cLen,lpBuffer+aIndex,2);
    aIndex += 2;
    int iLen = atoi(cLen);
    char cUserName[50] = {0};
    memcpy(cUserName,lpBuffer+aIndex,iLen);
    aIndex += iLen;
    strUserName = cUserName;

    // Password
    memset(cLen,0,sizeof(cLen));
    memcpy(cLen,lpBuffer+aIndex,2);
    aIndex += 2;
    iLen = atoi(cLen);
    char cPassword[50] = {0};
    memcpy(cPassword,lpBuffer+aIndex,iLen);
    aIndex += iLen;
    strUserPwd = cPassword;

    // Cellphone no.
    memset(cLen,0,sizeof(cLen));
    memcpy(cLen,lpBuffer+aIndex,2);
    aIndex += 2;
    iLen = atoi(cLen);
    char cPhone[50] = {0};
    memcpy(cPhone,lpBuffer+aIndex,iLen);
    aIndex += iLen;
    strPhoneSimNo = cPhone;

    // Software serial no.
    memset(cLen,0,sizeof(cLen));
    memcpy(cLen,lpBuffer+aIndex,2);
    aIndex += 2;
    iLen = atoi(cLen);
    char cSWSerNo[50] = {0};
    memcpy(cSWSerNo,lpBuffer+aIndex,iLen);
    aIndex += iLen;
    strSoftwareSerNo = cSWSerNo;

    // Cellphone serial no.
    memset(cLen,0,sizeof(cLen));
    memcpy(cLen,lpBuffer+aIndex,2);
    aIndex += 2;
    iLen = atoi(cLen);
    char cPhoneSerNo[50] = {0};
    memcpy(cPhoneSerNo,lpBuffer+aIndex,iLen);
    aIndex += iLen;
    strPhoneSerNo = cPhoneSerNo;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////////
// REG2. 用户注册回复
_register_response::_register_response()
{
    wCmdID = ECommandID;
}
WORD _register_response::GetCommandID() const
{
    return ECommandID;
}
void _register_response::CalculateBlockSize()
{
    wBlockSize = ELenRegRspCode;
}
void _register_response::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);

    //const int startPos = aIndex;
    //aIndex += LEN_PROTOCAL_HEAD;

    CString strTemp;
    // Get the buffer myself.
    strTemp.Format("%02d",wRegRspCode);
    memcpy(lpBuffer+aIndex,strTemp.GetBuffer(0),ELenRegRspCode);
    aIndex += ELenRegRspCode;

    // Get the header of frame
    /*BYTE header[LEN_PROTOCAL_HEAD];
    int lenHeader = 0;
    _content_header::GetBuffer(header,lenHeader);
    memcpy(lpBuffer+startPos,header,LEN_PROTOCAL_HEAD);*/
}


//////////////////////////////////////////////////////////////////////////
// _login_request
WORD _login_request_char::GetCommandID() const
{
    return ECommandID;
}
_login_request_char::_login_request_char()
{
    wCmdID = GetCommandID();
}
void _login_request_char::CalculateBlockSize()
{
    wBlockSize = 2;
    wBlockSize += strUserName.GetLength();

    wBlockSize += 2;
    wBlockSize += strUserPwd.GetLength();
}

void _login_request_char::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);


    //
    CString strTemp;

    // Get the buffer myself.

    // user name
    int iLen = strUserName.GetLength();
    strTemp.Format("%02d",iLen);
    memcpy(lpBuffer+aIndex,strTemp.GetBuffer(0),2);
    aIndex += 2;
    memcpy(lpBuffer+aIndex,(const char*)strUserName,iLen);
    aIndex += iLen;

    // password
    iLen = strUserPwd.GetLength();
    strTemp.Format("%02d",iLen);
    memcpy(lpBuffer+aIndex,strTemp.GetBuffer(0),2);
    aIndex += 2;
    memcpy(lpBuffer+aIndex,(const char*)strUserPwd,iLen);
    aIndex += iLen;


}

BOOL _login_request_char::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    BOOL rc = _mobile_comm_frame_char::ParseBuffer(lpBuffer,aIndex);
    if (!rc)
    {
        return FALSE;
    }

    // Parse myself...
    //user name
    char cLen[5] = {0};
    memcpy(cLen,lpBuffer+aIndex,2);
    aIndex += 2;
    int iLen = atoi(cLen);
    char cUserName[50] = {0};
    memcpy(cUserName,lpBuffer+aIndex,iLen);
    aIndex += iLen;
    strUserName = cUserName;
    
    //password
    memset(cLen,0,sizeof(cLen));
    memcpy(cLen,lpBuffer+aIndex,2);
    aIndex += 2;
    iLen = atoi(cLen);
    char cPassword[50] = {0};
    memcpy(cPassword,lpBuffer+aIndex,iLen);
    aIndex += iLen;
    strUserPwd = cPassword;

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// _login_response
_login_response_char::_login_response_char()
{
    wCmdID = ECommandID;
}
WORD _login_response_char::GetCommandID() const
{
    return ECommandID;
}
void _login_response_char::CalculateBlockSize()
{
    wBlockSize = 4;
}
void _login_response_char::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);

    //const int startPos = aIndex;
    //aIndex += LEN_PROTOCAL_HEAD;

    CString strTemp;
    // Get the buffer myself.
    strTemp.Format("%04X",wLoginRst);
    memcpy(lpBuffer+aIndex,strTemp.GetBuffer(0),4);
    aIndex += 4;
    
    // Get the header of frame
    /*BYTE header[LEN_PROTOCAL_HEAD];
    int lenHeader = 0;
    _content_header::GetBuffer(header,lenHeader);
    memcpy(lpBuffer+startPos,header,LEN_PROTOCAL_HEAD);*/
}

//////////////////////////////////////////////////////////////////////////
// _online_test
_online_test::_online_test()
{
    wCmdID = ECommandID;
}
WORD _online_test::GetCommandID() const
{
    return ECommandID;
}

//////////////////////////////////////////////////////////////////////////
// _client_exit
_client_exit_char::_client_exit_char()
{
    wCmdID = GetCommandID();
}
WORD _client_exit_char::GetCommandID() const
{
    return ECommandID;
}
void _client_exit_char::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);
}
BOOL _client_exit_char::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    BOOL rc = _mobile_comm_frame_char::ParseBuffer(lpBuffer,aIndex);
    if (!rc)
    {
        return FALSE;
    }

    return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// _forecast_weather_request
_weather_request_::_weather_request_()
{
    wCmdID = GetCommandID();
}

WORD _weather_request_::GetCommandID() const
{
    return ECommandID;
}

void _weather_request_::CalculateBlockSize()
{
    wBlockSize = 1;         // 参见TReqType 

    wBlockSize += 8;    // longitude (unit: 1/24s)
    wBlockSize += 8;     // 

    wBlockSize += 1;       // 时段指示码
}

void _weather_request_::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{

    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);

    /*const int startPos = aIndex;
    aIndex += LEN_PROTOCAL_HEAD;*/

    CString strTmp;

    // Get the buffer myself.

    //请求类型
    memcpy(lpBuffer+aIndex,&byType,1);
    aIndex++;


    //longitude
    strTmp.Format("%08d",dwLongitude);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),8);
    aIndex += 8;

    //latitude
    strTmp.Format("%08d",dwLatitude);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),8);
    aIndex += 8;


    // 时段指示码
    memcpy(lpBuffer+aIndex,&byPeriod,1);
    aIndex++;

    // Get the header of frame
    /*BYTE header[LEN_PROTOCAL_HEAD];
    int lenHeader = 0;
    _content_header::GetBuffer(header,lenHeader);
    memcpy(lpBuffer+startPos,header,LEN_PROTOCAL_HEAD);*/

}

BOOL _weather_request_::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    BOOL rc = _mobile_comm_frame_char::ParseBuffer(lpBuffer,aIndex);
    if (!rc)
    {
        return FALSE;
    }

    // Parse myself

    // Type
    byType = *(lpBuffer+aIndex);
    aIndex ++;
    if (byType == ERT_POSITION)
    {
        // longitude(单位1/24秒)
        char cLongitude[10] = {0};
        memcpy(cLongitude,lpBuffer+aIndex,8);
        aIndex += 8;
        dwLongitude = (LONG)_atoi64(cLongitude);

        // latitude(单位1/24秒)
        char cLatitude[10] = {0};
        memcpy(cLatitude,lpBuffer+aIndex,8);
        aIndex += 8;
        dwLatitude = (LONG)_atoi64(cLatitude);

    }
    else
    {
        return FALSE;
    }

    // Period
    byPeriod = *(lpBuffer+aIndex);
    aIndex ++;

    return TRUE;
}



//////////////////////////////////////////////////////////////////////////
// _weather_inf_rsp
_weather_response1::_weather_response1()
{
    wCmdID = ECommandID;
}
WORD _weather_response1::GetCommandID() const
{
    return ECommandID;
}
void _weather_response1::CalculateBlockSize()
{
    // Get the buffer myself.
    //指令执行结果
    wBlockSize = 1;

    if (byExcuteRst==EExeFailure)
    {
        return;
    }

    //类型标识
    wBlockSize += 1;
    //经度(单位：1/24秒)
    wBlockSize += 8;
    //纬度(单位：1/24秒)
    wBlockSize += 8;
    //区域码长度
    wBlockSize += 2;
    //区域码
    wBlockSize += weatherInf.strDistID.GetLength();
    //时段指示码
    wBlockSize += 1;
    //天气状况长度
    wBlockSize += 2;
    //天气状况
    wBlockSize += weatherInf.strWeatherDes.GetLength();
    //最高气温
    wBlockSize += 3;
    //最低气温
    wBlockSize += 3;
    //最小风力强度
    wBlockSize += 2;
    //最大风力强度
    wBlockSize += 2;
    //风向长度
    wBlockSize += 2;
    //风向
    wBlockSize += weatherInf.strWindDirec.GetLength();
    //相对湿度
    wBlockSize += 2;
}
void _weather_response1::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);

    /*const int startPos = aIndex;
    aIndex += LEN_PROTOCAL_HEAD;*/

    CString strTmp;

    // Get the buffer myself.

    // Execute result
    *(lpBuffer+aIndex) = byExcuteRst;
    aIndex++;

    if (byExcuteRst==EExeFailure)
    {
        return;
    }

    // flag to indicate the result type
    strTmp.Format("%c",byFlag);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),1);
    aIndex++;

    // longitude
    strTmp.Format("%08d",dwLongitude);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),8);
    aIndex += 8;
    // latitude
    strTmp.Format("%08d",dwLatitude);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),8);
    aIndex += 8;

    // area's length
    int iLen = weatherInf.strDistID.GetLength();
    strTmp.Format("%02d",iLen);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),2);
    aIndex += 2;

    //area
    memcpy(lpBuffer+aIndex,(const char*)weatherInf.strDistID,iLen);
    aIndex += iLen;

    //时段指示码
    *(lpBuffer+aIndex) = BYTE(weatherInf.cPeriodFlag);
    aIndex++;

    //weather's length
    iLen = weatherInf.strWeatherDes.GetLength();
    strTmp.Format("%02d",iLen);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),2);
    aIndex += 2;
    //weather
    memcpy(lpBuffer+aIndex,(const char*)weatherInf.strWeatherDes,iLen);
    aIndex += iLen;

    // TemperatureMax
    strTmp.Format("%03.0f",weatherInf.fTempMax);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),3);
    aIndex += 3;
    // TemperatureMin
    strTmp.Format("%03.0f",weatherInf.fTempMin);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),3);
    aIndex += 3;

    // WindPowerMin
    strTmp.Format("%02d",weatherInf.byWindPowerMin);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),2);
    aIndex += 2;
    // WindPowerMax
    strTmp.Format("%02d",weatherInf.byWindPowerMax);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),2);
    aIndex += 2;

    // LenWindDirect
    iLen = weatherInf.strWindDirec.GetLength();
    strTmp.Format("%02d",iLen);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),2);
    aIndex += 2;
    // WindDirection
    memcpy(lpBuffer+aIndex,(const char*)weatherInf.strWindDirec,iLen);
    aIndex += iLen;

    // Humidity
    strTmp.Format("%02d",weatherInf.byHumidity);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),2);
    aIndex += 2;

    // Get the header of frame
    /*BYTE header[LEN_PROTOCAL_HEAD];
    int lenHeader = 0;
    _content_header::GetBuffer(header,lenHeader);
    memcpy(lpBuffer+startPos,header,LEN_PROTOCAL_HEAD);*/
}
BOOL _weather_response1::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    BOOL rc = _mobile_comm_frame_char::ParseBuffer(lpBuffer,aIndex);
    if (!rc)
    {
        return FALSE;
    }

    // Parse myself

    byExcuteRst = *(lpBuffer+aIndex);
    aIndex ++;

    if (byExcuteRst!=EExeSuccess)
    {
        return TRUE;
    }

    // 类型标识
    byFlag = *(lpBuffer+aIndex);
    aIndex ++;

    // longitude(单位1/24秒)
    char cLongitude[10] = {0};
    memcpy(cLongitude,lpBuffer+aIndex,8);
    aIndex += 8;
    dwLongitude = (LONG)_atoi64(cLongitude);

    // latitude(单位1/24秒)
    char cLatitude[10] = {0};
    memcpy(cLatitude,lpBuffer+aIndex,8);
    aIndex += 8;
    dwLatitude = (LONG)_atoi64(cLatitude);

    // 天气信息
    char cTemp[300]={0};
    int iLen;

    // 区域码
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,2);
    iLen = atoi(cTemp);
    aIndex += 2;
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,iLen);
    weatherInf.strDistID = CString(cTemp);
    aIndex += iLen;

    // 时段指示码
    weatherInf.cPeriodFlag = TWeatherInf::TPeriodCode(*(lpBuffer+aIndex));
    aIndex++;

    // 天气状况
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,2);
    iLen = atoi(cTemp);
    aIndex += 2;
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,iLen);
    weatherInf.strWeatherDes = CString(cTemp);
    aIndex += iLen;

    // 最高气温
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,3);
    weatherInf.fTempMax = atof(cTemp);
    aIndex += 3;

    // 最低气温
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,3);
    weatherInf.fTempMin = atof(cTemp);
    aIndex += 3;

    // 最小风力
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,2);
    weatherInf.byWindPowerMin = atoi(cTemp);
    aIndex += 2;

    // 最大风力
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,2);
    weatherInf.byWindPowerMax = atoi(cTemp);
    aIndex += 2;

    // 风向
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,2);
    iLen = atoi(cTemp);
    aIndex += 2;
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,iLen);
    weatherInf.strWindDirec = CString(cTemp);
    aIndex += iLen;

    // 相对湿度
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,2);
    weatherInf.byHumidity = atoi(cTemp);
    aIndex += 2;

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// _response_weather_main_citys
_weather_response2::_weather_response2()
{
    wCmdID = ECommandID;
}
WORD _weather_response2::GetCommandID() const
{
    return ECommandID;
}
void _weather_response2::CalculateBlockSize()
{
    // 指令执行结果
    wBlockSize = 1;
    // 时段
    wBlockSize += 1;
    // 天气状况长度
    wBlockSize += 4;
    // 天气状况
    //wBlockSize += strCityName.GetLength() + strWthDes.GetLength();
    wBlockSize += strWthDes.GetLength();
}
void _weather_response2::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);

    CString strTmp;

    // Get the buffer myself.
    //execute result
    strTmp.Format("%c",byExcuteRst);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),1);
    aIndex++;
    //Period
    strTmp.Format("%c",byPeriod);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),1);
    aIndex++;

    // assemble weather information
    CString strResult = strWthDes;

    // weather's length
    int iLen = strResult.GetLength();
    strTmp.Format("%04d",iLen);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),4);
    aIndex += 4;
    // weather description
    memcpy(lpBuffer+aIndex,(const char*)strResult,iLen);
    aIndex += iLen;
}
BOOL _weather_response2::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    BOOL rc = _mobile_comm_frame_char::ParseBuffer(lpBuffer,aIndex);
    if (!rc)
    {
        return FALSE;
    }

    // Parse myself
    byExcuteRst = *(lpBuffer+aIndex);
    aIndex ++;

    if (byExcuteRst==EExeFailure)
    {
        return TRUE;
    }

    // 类型标识
    byPeriod = *(lpBuffer+aIndex);
    aIndex ++;

    // 天气状况
    char cTemp[5000];
    int iLen = 0;
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,4);
    iLen = atoi(cTemp);
    aIndex += 4;
    memset(cTemp,0,sizeof(cTemp));
    memcpy(cTemp,lpBuffer+aIndex,iLen);
    strWthDes = CString(cTemp);
    aIndex += iLen;

    return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// _traffic_req_by_linkPosition
_traffic_req_by_linkPosition_char::_traffic_req_by_linkPosition_char()
{
    wCmdID = GetCommandID();
}
_traffic_req_by_linkPosition_char::~_traffic_req_by_linkPosition_char()
{
    linkPosList.ClearList();
}
WORD _traffic_req_by_linkPosition_char::GetCommandID() const
{
    return ECommandID;
}
BOOL _traffic_req_by_linkPosition_char::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    BOOL rc = _mobile_comm_frame_char::ParseBuffer(lpBuffer,aIndex);
    if (!rc)
    {
        return FALSE;
    }

    char cTmp[100] = {0};

    // Link的个数
    int  nCount	= 0;
    memcpy(cTmp,lpBuffer+aIndex,2);
    nCount = atoi(cTmp);
    aIndex += 2;

    // 取出所有Link属性（起止经纬度、名称）
    PTLinkAttri pItem = NULL;
    for (int i = 0; i<nCount; i++)
    {
        pItem = new TLinkAttri;
        
        // start longitude(单位1/24秒)   
        memset(cTmp,0,sizeof(cTmp));
        memcpy(cTmp,lpBuffer+aIndex,8);
        aIndex += 8;
        pItem->m_StartPos.iX = (LONG)_atoi64(cTmp);
        // start latitude(单位1/24秒)
        memset(cTmp,0,sizeof(cTmp));
        memcpy(cTmp,lpBuffer+aIndex,8);
        aIndex += 8;
        pItem->m_StartPos.iY = (LONG)_atoi64(cTmp);

        // End longitude(单位1/24秒)
        memset(cTmp,0,sizeof(cTmp));
        memcpy(cTmp,lpBuffer+aIndex,8);
        aIndex += 8;
        pItem->m_EndPos.iX = (LONG)_atoi64(cTmp);
        // End latitude(单位1/24秒)
        memset(cTmp,0,sizeof(cTmp));
        memcpy(cTmp,lpBuffer+aIndex,8);
        aIndex += 8;
        pItem->m_EndPos.iY = (LONG)_atoi64(cTmp);

        // Link name
        int iNameLen = 0;
        memset(cTmp,0,sizeof(cTmp));
        memcpy(cTmp,lpBuffer+aIndex,2);
        iNameLen = atoi(cTmp);
        aIndex += 2;
        if (iNameLen>0)
        {
            memset(cTmp,0,sizeof(cTmp));
            memcpy(cTmp,lpBuffer+aIndex,iNameLen);
            pItem->m_strLinkName = CString(cTmp);
            aIndex += iNameLen;
        }

        linkPosList.AddTail(pItem);
    }


    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// _traffic_req_by_roadname
_traffic_req_by_roadname_char::_traffic_req_by_roadname_char()
{
    wCmdID = GetCommandID();
}
WORD _traffic_req_by_roadname_char::GetCommandID() const
{
    return ECommandID;
}
BOOL _traffic_req_by_roadname_char::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    BOOL rc = _mobile_comm_frame_char::ParseBuffer(lpBuffer,aIndex);
    if (!rc)
    {
        return FALSE;
    }

	// Len
	char	cLen[5]={0};
	int		nLen=0;
	memcpy(cLen,lpBuffer+aIndex,2);
	nLen = atoi(cLen);
	aIndex += 2;

	// Name
	char	cTmp[100] = {0};
	memcpy(cTmp,lpBuffer+aIndex,nLen);
	strRoadName.Format("%s",cTmp);
	aIndex += nLen;

    // Longitude
    memset(cTmp,0,sizeof(cTmp));
    memcpy(cTmp,lpBuffer+aIndex,8);
    aIndex += 8;
    dwLongitude = (DWORD)_atoi64(cTmp);

 
    // latitude(单位1/24秒)
    memset(cTmp,0,sizeof(cTmp));
    memcpy(cTmp,lpBuffer+aIndex,8);
    aIndex += 8;
    dwLatitude = (DWORD)_atoi64(cTmp);


    return TRUE;
}

//
////////////////////////////////////////////////////////////////////////////
////

//////////////////////////////////////////////////////////////////////////
// 路况信息回复1
_traffic_response_1_char::_traffic_response_1_char()
{
    wCmdID =ECommandID;
}
WORD _traffic_response_1_char::GetCommandID() const
{
    return ECommandID;
}
_traffic_response_1_char::~_traffic_response_1_char()
{
    DtiList.ClearList();

}
void _traffic_response_1_char::CalculateBlockSize()
{
    wBlockSize = 0;
    // execute flag
    wBlockSize++;
    // indicator
    wBlockSize++;
    // DTI Count;
    wBlockSize += 2;
    // DTI information
    POSITION pos = DtiList.GetHeadPosition();
    while (pos)
    {
        PTLinkAttri pDti = DtiList.GetNext(pos);

        // jam level
        wBlockSize += 2;
        // jam reason
        wBlockSize += 2;
    } 
}
void _traffic_response_1_char::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);

    /*const int startPos = aIndex;
    aIndex += LEN_PROTOCAL_HEAD;*/

    CString strTmp;

    // Get the buffer myself.
    //execute flag
    strTmp.Format("%1d",byExcuteRst%10);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
    aIndex += strTmp.GetLength();

    // DTI Count
    WORD wDTICount = DtiList.GetCount();
    if (wDTICount>EMaxDTI)
    {
        wDTICount = EMaxDTI;
    }
    strTmp.Format("%02d",wDTICount);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
    aIndex += strTmp.GetLength();

    // DTI information
    POSITION pos = DtiList.GetHeadPosition();
    for (int jj=0; jj<wDTICount; jj++)
    {
        PTLinkAttri pDti = DtiList.GetNext(pos);
        
        // jam level
        strTmp.Format("%02d",(pDti->m_iJamLevel)%100);
        memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
        aIndex += strTmp.GetLength();
        
        // jam reason
        strTmp.Format("%02d",(pDti->m_iJamReason)%100);
        memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
        aIndex += strTmp.GetLength();
        
    }


    // Get the header of frame
    /*BYTE header[LEN_PROTOCAL_HEAD];
    int lenHeader = 0;
    _content_header::GetBuffer(header,lenHeader);
    memcpy(lpBuffer+startPos,header,LEN_PROTOCAL_HEAD);*/
}


//////////////////////////////////////////////////////////////////////////
// 路况信息回复2
_traffic_response_2_char::_traffic_response_2_char()
{
    wCmdID = ECommandID;
}
_traffic_response_2_char::~_traffic_response_2_char()
{
    ClearList();
}

void _traffic_response_2_char::ClearList()
{
    while(m_RoadTfcList.GetHeadPosition())
    {
        delete m_RoadTfcList.RemoveHead();
    }

}

WORD _traffic_response_2_char::GetCommandID() const
{
    return ECommandID;
}

void _traffic_response_2_char::CalculateBlockSize()
{
    // execute flag
    wBlockSize = 1;
    // DTI Count;
    wBlockSize += 4;
    // DTI information
    POSITION pos = m_RoadTfcList.GetHeadPosition();
    while (pos)
    {
        m_RoadTfcList.GetNext(pos);

        // RoadID
        wBlockSize += 5;
        // jam level
        wBlockSize += 2;
        // jam reason
        wBlockSize += 2;
    } 
}

void _traffic_response_2_char::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    _mobile_comm_frame_char::GetBuffer(lpBuffer,aIndex);

    /*const int startPos = aIndex;
    aIndex += LEN_PROTOCAL_HEAD;*/

    CString strTmp;

    // Get the buffer myself.

    // execute flag
    strTmp.Format("%01d",m_byResult);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
    aIndex += strTmp.GetLength();

    // DTI Count
    WORD wDTICount = m_RoadTfcList.GetCount();
    if (wDTICount>EMaxNum)
    {
        wDTICount = EMaxNum;
    }
    strTmp.Format("%04d",wDTICount);
    memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
    aIndex += strTmp.GetLength();

    // DTI information
    POSITION pos = m_RoadTfcList.GetHeadPosition();
    for (int jj=0; jj<wDTICount; jj++)
    {
        PTRawRoadTfcInf pUnit = m_RoadTfcList.GetNext(pos);

        // Road ID
        strTmp.Format("%05d",pUnit->dwRoadID);
        memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
        aIndex += strTmp.GetLength();

        // jam level
        int iJamLevel = pUnit->GetJamLevel();
        strTmp.Format("%02d",(iJamLevel)%100);
        memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
        aIndex += strTmp.GetLength();

        // jam reason
        strTmp.Format("%02d",(pUnit->iJamReason)%100);
        memcpy(lpBuffer+aIndex,strTmp.GetBuffer(0),strTmp.GetLength());
        aIndex += strTmp.GetLength();

    }


    // Get the header of frame
    /*BYTE header[LEN_PROTOCAL_HEAD];
    int lenHeader = 0;
    _content_header::GetBuffer(header,lenHeader);
    memcpy(lpBuffer+startPos,header,LEN_PROTOCAL_HEAD);*/
}

//////////////////////////////////////////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////////
//


//////////////////////////////////////////////////////////////////////////
//