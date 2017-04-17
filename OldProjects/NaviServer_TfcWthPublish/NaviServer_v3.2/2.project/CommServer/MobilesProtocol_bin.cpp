

#include "stdafx.h"
#include "MobilesProtocol_bin.h"
#include "CommonFunc.h"

//////////////////////////////////////////////////////////////////////////
// _content_header
_mobile_comm_frame_bin::_mobile_comm_frame_bin()
{    
    // Protocol version
    byVersion = EVersion;
    // Command ID
    wCmdID = 0;
    // Content type
    byContentType = 0;
    // cellphone number
    memset(byMobileNo,0,sizeof(byMobileNo));  
    // the code of service
    bySerciveCode = ESuccess;
    // reserved
    memset(byReserved,0,sizeof(byReserved));
}
_mobile_comm_frame_bin::~_mobile_comm_frame_bin()
{

}
WORD _mobile_comm_frame_bin::GetCommandID() const
{
    return 0;
}
int _mobile_comm_frame_bin::GetProType()
{
    return E_PRO_FLAG;
}
CString _mobile_comm_frame_bin::GetProName()
{
    return _T("与手机终端的通信协议-Binary");
}
void _mobile_comm_frame_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Version
    memcpy(lpBuffer+aIndex,&byVersion,sizeof(byVersion));
    aIndex += sizeof(byVersion);
    // Command ID
    memcpy(lpBuffer+aIndex,&wCmdID,sizeof(wCmdID));
    aIndex += sizeof(wCmdID);
    // Content type
    memcpy(lpBuffer+aIndex,&byContentType,sizeof(byContentType));
    aIndex += sizeof(byContentType);
    // Cellphone number
    memcpy(lpBuffer+aIndex,byMobileNo,sizeof(byMobileNo));
    aIndex += sizeof(byMobileNo);
    // service code
    memcpy(lpBuffer+aIndex,&bySerciveCode,sizeof(bySerciveCode));
    aIndex += sizeof(bySerciveCode);
    // Reserved
    memcpy(lpBuffer+aIndex,byReserved,sizeof(byReserved));
    aIndex += sizeof(byReserved);

}
BOOL _mobile_comm_frame_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Version
    memcpy(&byVersion,lpBuffer+aIndex,sizeof(byVersion));
    aIndex += sizeof(byVersion);
    // Command ID
    memcpy(&wCmdID,lpBuffer+aIndex,sizeof(wCmdID));
    aIndex += sizeof(wCmdID);
    // Content type
    memcpy(&byContentType,lpBuffer+aIndex,sizeof(byContentType));
    aIndex += sizeof(byContentType);
    // Cellphone number
    memcpy(&byMobileNo,lpBuffer+aIndex,sizeof(byMobileNo));
    aIndex += sizeof(byMobileNo);
    // Service code
    memcpy(&bySerciveCode,lpBuffer+aIndex,sizeof(bySerciveCode));
    aIndex += sizeof(bySerciveCode);
    // Reserved
    memcpy(&byReserved,lpBuffer+aIndex,sizeof(byReserved));
    aIndex += sizeof(byReserved);

    return TRUE;
}

_mobile_comm_frame_bin* _mobile_comm_frame_bin::GetInstance(WORD wCommandID)
{
    PTMobileFrameBin pContent = NULL;

    switch(wCommandID)
    {
        // Login
    case TLoginReqBin::ECommandID:
        pContent = new TLoginReqBin;
        break;
    case TLoginRspBin::ECommandID:
        pContent = new TLoginRspBin;
        break;

        // Exit
    case TClientExitBin::ECommandID:
        pContent = new TClientExitBin;
        break;

        // Register
    case TRegRequestBin::ECommandID:
        pContent = new TRegRequestBin;
        break;
    case TRegisterRspBin::ECommandID:
        pContent = new TRegisterRspBin;
        break;

        // traffic
    case TTfcReqByRoadNameBin::ECommandID:
        pContent = new TTfcReqByRoadNameBin;
        break;
    case TTfcReqByLinkPosBin::ECommandID:
        pContent = new TTfcReqByLinkPosBin;
        break;
    case TTfcInfRsp1_Bin::ECommandID:
        pContent = new TTfcInfRsp1_Bin;
        break;
    case TTfcInfRsp2_Bin::ECommandID:
        pContent = new TTfcInfRsp2_Bin;
        break;

        // Weather
    case TWthReqByPosBin::ECommandID:
        pContent = new TWthReqByPosBin;
        break;
    case TWthRspBin::ECommandID:
        pContent = new TWthRspBin;
        break;
    }

    if (pContent!=NULL)
    {
        pContent->SetAutoDel(TRUE);
    }

    return pContent;
}


//////////////////////////////////////////////////////////////////////////
//#######################################################################
// _login_req
//Constructor
_login_req_bin::_login_req_bin()
{
    memset(byRadomAuthen,0,sizeof(byRadomAuthen));
    wCmdID = GetCommandID();
}
WORD _login_req_bin::GetCommandID() const
{
    return ECommandID;
}
//
void _login_req_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...
    BYTE len;

    // UserName
    len = (BYTE)strUserName.GetLength();
    memcpy(lpBuffer+aIndex,&len,sizeof(len));
    aIndex += sizeof(len);
    memcpy(lpBuffer+aIndex,(const char*)strUserName,len);
    aIndex += len;

    // Password
    len = (BYTE)strUserPwd.GetLength();
    memcpy(lpBuffer+aIndex,&len,sizeof(len));
    aIndex += sizeof(len);
    memcpy(lpBuffer+aIndex,(const char*)strUserPwd,len);
    aIndex += len;

    // Random number
    memcpy(lpBuffer+aIndex,byRadomAuthen,sizeof(byRadomAuthen));
    aIndex += sizeof(byRadomAuthen);
}
//
BOOL _login_req_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)/*ParseBuffer(const TDesC8& aBuffer,TInt& aIndex)*/
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }

    // to do implement me...

    // UserName
    BYTE len;
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    strUserName = CString((LPCTSTR)(lpBuffer+aIndex),len);
    aIndex += len;
    // Password
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    strUserPwd = CString((LPCTSTR)(lpBuffer+aIndex),len);
    aIndex += len;
    // Random number
    memcpy(byRadomAuthen,lpBuffer+aIndex,sizeof(byRadomAuthen));
    aIndex += sizeof(byRadomAuthen);

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
//#######################################################################
// _login_rsp_bin
// Constructor
_login_rsp_bin::_login_rsp_bin()
{
    wCmdID = ECommandID;
}
WORD _login_rsp_bin::GetCommandID() const
{
    return ECommandID;
}
//
void _login_rsp_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...

    // Return code
    memcpy(lpBuffer+aIndex,&byLoginRst,sizeof(byLoginRst));
    aIndex += sizeof(byLoginRst);

}
BOOL _login_rsp_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...

    // 
    memcpy(&byLoginRst,lpBuffer+aIndex,sizeof(byLoginRst));
    aIndex += sizeof(byLoginRst);



    return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//#######################################################################
// _client_exit_bin
// Constructor
_client_exit_bin::_client_exit_bin()
{
    wCmdID = ECommandID;
}
WORD _client_exit_bin::GetCommandID() const
{
    return ECommandID;
}
void _client_exit_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...

}
BOOL _client_exit_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...


    return TRUE;
}


// ----------------------------------------------------------------------------------------
// -------------------------- 业务协议 ----------------------------------------------------
// ----------------------------------------------------------------------------------------

// 用户注册请求
_register_request_bin::_register_request_bin()
{
    wCmdID = GetCommandID();
}
WORD _register_request_bin::GetCommandID() const
{
    return ECommandID;
}
BOOL _register_request_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...

    BYTE len;
    //user name
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    strUserName = CString((LPCTSTR)(lpBuffer+aIndex),len);
    aIndex += len;

    // Password
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    strUserPwd = CString((LPCTSTR)(lpBuffer+aIndex),len);
    aIndex += len;

    // Cellphone's SIM card No.
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    strPhoneSimNo = CString((LPCTSTR)(lpBuffer+aIndex),len);
    aIndex += len;

    // Software serial no.
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    strSoftwareSerNo = CString((LPCTSTR)(lpBuffer+aIndex),len);
    aIndex += len;

    // Cellphone serial no.
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    strPhoneSerNo = CString((LPCTSTR)(lpBuffer+aIndex),len);
    aIndex += len;

    return TRUE;
}

// REG2. 用户注册回复
_register_response_bin::_register_response_bin()
{
    wCmdID = ECommandID;
}
WORD _register_response_bin::GetCommandID() const
{
    return ECommandID;
}

void _register_response_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...

    // Return code
    memcpy(lpBuffer+aIndex,&byRegRspCode,sizeof(byRegRspCode));
    aIndex += sizeof(byRegRspCode);
}

// TFC1. 通过道路名称请求实时路况信息指令
_traffic_req_by_roadname_bin::_traffic_req_by_roadname_bin()
{
    wCmdID = ECommandID;
}
WORD _traffic_req_by_roadname_bin::GetCommandID() const
{
    return ECommandID;
}
void _traffic_req_by_roadname_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...

    // RoadName
    BYTE len=strRoadName.GetLength();
    memcpy(lpBuffer+aIndex,&len,sizeof(len));
    aIndex += sizeof(len);
    memcpy(lpBuffer+aIndex,(const char*)strRoadName,len);
    aIndex += len;

    // Longitude
    memcpy(lpBuffer+aIndex,&dwLongitude,sizeof(dwLongitude));
    aIndex += sizeof(dwLongitude);

    // Latitude
    memcpy(lpBuffer+aIndex,&dwLatitude,sizeof(dwLatitude));
    aIndex += sizeof(dwLatitude);
}
BOOL _traffic_req_by_roadname_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...

    // RoadName
    BYTE len=0;
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex += sizeof(len);
    strRoadName = CString((LPCTSTR)(lpBuffer+aIndex),len);
    aIndex += len;

    // Longitude
    memcpy(&dwLongitude,lpBuffer+aIndex,sizeof(dwLongitude));
    aIndex += sizeof(dwLongitude);

    // Latitude
    memcpy(&dwLatitude,lpBuffer+aIndex,sizeof(dwLatitude));
    aIndex += sizeof(dwLatitude);

    //

    return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// _traffic_req_by_linkPosition_bin
_traffic_req_by_linkPos_bin::_traffic_req_by_linkPos_bin()
{
    wCmdID = ECommandID;
}
_traffic_req_by_linkPos_bin::~_traffic_req_by_linkPos_bin()
{
    linkPosList.ClearList();
}
WORD _traffic_req_by_linkPos_bin::GetCommandID() const
{
    return ECommandID;
}
void _traffic_req_by_linkPos_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...

    // Link
    BYTE  byCount = (BYTE)linkPosList.GetCount();
    memcpy(lpBuffer+aIndex,&byCount,sizeof(byCount));
    aIndex += sizeof(byCount);
    
    // 取出所有Link属性（起止经纬度、名称）
    POSITION pos = linkPosList.GetHeadPosition();
    PTLinkAttri pItem = NULL;
    while(pos)
    {
        pItem = (PTLinkAttri)linkPosList.GetNext(pos);

        // start longitude(单位1/24秒)
        memcpy(lpBuffer+aIndex,&(pItem->m_StartPos.iX),sizeof(pItem->m_StartPos.iX));
        aIndex += sizeof(pItem->m_StartPos.iX);
        // start latitude(单位1/24秒)
        memcpy(lpBuffer+aIndex,&(pItem->m_StartPos.iY),sizeof(pItem->m_StartPos.iY));
        aIndex += sizeof(pItem->m_StartPos.iY);

        // End longitude(单位1/24秒)
        memcpy(lpBuffer+aIndex,&(pItem->m_EndPos.iX),sizeof(pItem->m_EndPos.iX));
        aIndex += sizeof(pItem->m_EndPos.iX);
        // End latitude(单位1/24秒)
        memcpy(lpBuffer+aIndex,&(pItem->m_EndPos.iX),sizeof(pItem->m_EndPos.iY));
        aIndex += sizeof(pItem->m_EndPos.iY);

        // Link name
        BYTE byLenName = pItem->m_strLinkName.GetLength();
        memcpy(lpBuffer+aIndex,&byLenName,sizeof(byLenName));
        aIndex += sizeof(byLenName);
        memcpy(lpBuffer+aIndex,pItem->m_strLinkName,sizeof(byLenName));
        aIndex += byLenName;

    }
}
BOOL _traffic_req_by_linkPos_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...

    // Link的个数
    BYTE  byCount	= 0;
    memcpy(&byCount,lpBuffer+aIndex,sizeof(byCount));
    aIndex += sizeof(byCount);

    // 取出所有Link属性（起止经纬度、名称）
    PTLinkAttri pItem = NULL;
    for (int i = 0; i<byCount; i++)
    {
        pItem = new TLinkAttri;

        // start longitude(单位1/24秒)
        memcpy(&(pItem->m_StartPos.iX),lpBuffer+aIndex,sizeof(pItem->m_StartPos.iX));
        aIndex += sizeof(pItem->m_StartPos.iX);
        // start latitude(单位1/24秒)
        memcpy(&(pItem->m_StartPos.iY),lpBuffer+aIndex,sizeof(pItem->m_StartPos.iY));
        aIndex += sizeof(pItem->m_StartPos.iY);

        // End longitude(单位1/24秒)
        memcpy(&(pItem->m_EndPos.iX),lpBuffer+aIndex,sizeof(pItem->m_EndPos.iX));
        aIndex += sizeof(pItem->m_EndPos.iX);
        // End latitude(单位1/24秒)
        memcpy(&(pItem->m_EndPos.iX),lpBuffer+aIndex,sizeof(pItem->m_EndPos.iY));
        aIndex += sizeof(pItem->m_EndPos.iY);

        // Link name
        BYTE byLenName = 0;
        memcpy(&byLenName,lpBuffer+aIndex,sizeof(byLenName));
        aIndex += sizeof(byLenName);
        pItem->m_strLinkName = CString((LPCTSTR)(lpBuffer+aIndex),byLenName);
        aIndex += byLenName;

        // ADD TO TAIL
        linkPosList.AddTail(pItem);
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////

// 实时路况信息返回1
_tfc_inf_rsp1_bin::_tfc_inf_rsp1_bin()
{
    wCmdID = ECommandID;
}
WORD _tfc_inf_rsp1_bin::GetCommandID() const
{
    return ECommandID;
}
_tfc_inf_rsp1_bin::~_tfc_inf_rsp1_bin()
{
    m_DtiList.ClearList();
}
void _tfc_inf_rsp1_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...


    // Get the buffer myself.

    // DTI Count
    BYTE dtiNum = (BYTE)m_DtiList.GetCount();
    memcpy(lpBuffer+aIndex,&dtiNum,sizeof(dtiNum));
    aIndex += sizeof(dtiNum);


    // DTI information
    POSITION pos = m_DtiList.GetHeadPosition();
    while (pos)
    {
        PTLinkAttri pDti = (PTLinkAttri)(m_DtiList.GetNext(pos));

        // jam level
        BYTE byJamLevel = (BYTE)(pDti->m_iJamLevel);
        memcpy(lpBuffer+aIndex,&byJamLevel,sizeof(byJamLevel));
        aIndex += sizeof(byJamLevel);

        // jam reason
        BYTE byJameReason = BYTE(pDti->m_iJamReason);
        memcpy(lpBuffer+aIndex,&byJameReason,sizeof(byJameReason));
        aIndex += sizeof(byJameReason);
    }

}
BOOL _tfc_inf_rsp1_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...
    // DTI Count
    BYTE dtiNum = 0;
    memcpy(&dtiNum,lpBuffer+aIndex,sizeof(dtiNum));
    aIndex += sizeof(dtiNum);


    // DTI information
    for(int ii=0; ii<dtiNum; ii++)
    {
        PTLinkAttri pDti = new TLinkAttri;

        // jam level
        BYTE byJamLevel;
        memcpy(&byJamLevel,lpBuffer+aIndex,sizeof(byJamLevel));
        aIndex += sizeof(byJamLevel);
        pDti->m_iJamLevel = byJamLevel;

        // jam reason
        BYTE byJameReason;
        memcpy(&byJameReason,lpBuffer+aIndex,sizeof(byJameReason));
        aIndex += sizeof(byJameReason);
        pDti->m_iJamReason = byJameReason;

        m_DtiList.AddTail(pDti);
    }

    return TRUE;
}

// 实时路况信息返回2
_tfc_inf_rsp2_bin::_tfc_inf_rsp2_bin()
{
    wCmdID = ECommandID;
}
WORD _tfc_inf_rsp2_bin::GetCommandID() const
{
    return ECommandID;
}
_tfc_inf_rsp2_bin::~_tfc_inf_rsp2_bin()
{
    while (m_RoadTfcList.GetHeadPosition())
    {
        delete m_RoadTfcList.RemoveHead();
    }
}
void _tfc_inf_rsp2_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...


    // Get the buffer myself.

    // DTI Count
    WORD dtiNum = (WORD)m_RoadTfcList.GetCount();
    memcpy(lpBuffer+aIndex,&dtiNum,sizeof(dtiNum));
    aIndex += sizeof(dtiNum);


    // DTI information
    POSITION pos = m_RoadTfcList.GetHeadPosition();
    while (pos)
    {
        PTRawRoadTfcInf pDti = m_RoadTfcList.GetNext(pos);

        // Road ID
        DWORD dwRoadID = pDti->dwRoadID;
        memcpy(lpBuffer+aIndex,&dwRoadID,sizeof(dwRoadID));
        aIndex += sizeof(dwRoadID);

        // jam level
        BYTE byJamLevel = (BYTE)(pDti->GetJamLevel());
        memcpy(lpBuffer+aIndex,&byJamLevel,sizeof(byJamLevel));
        aIndex += sizeof(byJamLevel);

        // jam reason
        BYTE byJameReason = BYTE(pDti->iJamReason);
        memcpy(lpBuffer+aIndex,&byJameReason,sizeof(byJameReason));
        aIndex += sizeof(byJameReason);
    }

}
BOOL _tfc_inf_rsp2_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...
    // DTI Count
    WORD dtiNum = 0;
    memcpy(&dtiNum,lpBuffer+aIndex,sizeof(dtiNum));
    aIndex += sizeof(dtiNum);


    // DTI information
    for(WORD ii=0; ii<dtiNum; ii++)
    {
        PTRawRoadTfcInf pDti = new TRawRoadTfcInf;

        // RoadID
        DWORD dwRoadID;
        memcpy(&dwRoadID,lpBuffer+aIndex,sizeof(dwRoadID));
        aIndex += sizeof(dwRoadID);
        pDti->dwRoadID = dwRoadID;

        // jam level
        BYTE byJamLevel;
        memcpy(&byJamLevel,lpBuffer+aIndex,sizeof(byJamLevel));
        aIndex += sizeof(byJamLevel);

        // jam reason
        BYTE byJameReason;
        memcpy(&byJameReason,lpBuffer+aIndex,sizeof(byJameReason));
        aIndex += sizeof(byJameReason);
        pDti->iJamReason = byJameReason;

        m_RoadTfcList.AddTail(pDti);
    }

    return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// 请求小区天气信息
_weather_request_by_position::_weather_request_by_position()
{
    wCmdID = ECommandID;
}
WORD _weather_request_by_position::GetCommandID() const
{
    return ECommandID;
}
void _weather_request_by_position::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...
    // CitypCode
    /*memcpy(lpBuffer+aIndex,byCityID,sizeof(byCityID));
    aIndex += sizeof(byCityID);*/

    // longitude
    memcpy(lpBuffer+aIndex,&dwLongitude,sizeof(dwLongitude));
    aIndex += sizeof(dwLongitude);

    // latitude
    memcpy(lpBuffer+aIndex,&dwLatitude,sizeof(dwLatitude));
    aIndex += sizeof(dwLatitude);

    // Period
    memcpy(lpBuffer+aIndex,&byPeriod,sizeof(byPeriod));
    aIndex += sizeof(byPeriod);

    // byReserved
    memcpy(lpBuffer+aIndex,byReserved,sizeof(byReserved));
    aIndex += sizeof(byReserved);
}
BOOL _weather_request_by_position::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...

    // CitypCode
    /*memcpy(byCityID,lpBuffer+aIndex,sizeof(byCityID));
    aIndex += sizeof(byCityID);*/

    // longitude
    memcpy(&dwLongitude,lpBuffer+aIndex,sizeof(dwLongitude));
    aIndex += sizeof(dwLongitude);

    // latitude
    memcpy(&dwLatitude,lpBuffer+aIndex,sizeof(dwLatitude));
    aIndex += sizeof(dwLatitude);

    // Period
    memcpy(&byPeriod,lpBuffer+aIndex,sizeof(byPeriod));
    aIndex += sizeof(byPeriod);

    // byReserved
    memcpy(byReserved,lpBuffer+aIndex,sizeof(byReserved));
    aIndex += sizeof(byReserved);

    return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// 气象信息回复
_weather_response_bin::_weather_response_bin()
{
    wCmdID = ECommandID;
}
WORD _weather_response_bin::GetCommandID() const
{
    return ECommandID;
}

void _weather_response_bin::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
{
    // Get the header of frame
    TMobileFrameBin::GetBuffer(lpBuffer,aIndex);

    // self-built...

    // Get the buffer myself.
    if (TMobileFrameBin::bySerciveCode==ESuccess)
    {
        CString strWthDes;
        weatherInf.GetWetherDescription(strWthDes);
    }

    //weather's length
    WORD len = strWthDes.GetLength();
    memcpy(lpBuffer+aIndex,&len,sizeof(len));
    aIndex += sizeof(len);
    //weather
    memcpy(lpBuffer+aIndex,(const char*)strWthDes,len);
    aIndex += len;
}
BOOL _weather_response_bin::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
{
    // Parsing the header first
    BOOL bRc = TMobileFrameBin::ParseBuffer(lpBuffer,aIndex);
    if (!bRc)
    {
        return FALSE;
    }


    // to do implement me...

    // Get the buffer myself.
    if (TMobileFrameBin::bySerciveCode==ESuccess)
    {
        // weather's length
        WORD len;
        memcpy(&len,lpBuffer+aIndex,sizeof(len));
        aIndex += sizeof(len);

        strWthDes = CString((LPCTSTR)(lpBuffer+aIndex),len);
    }

    return TRUE;
}

















//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#if 0
//////////////////////////////////////////////////////////////////////////
//#######################################################################
// _function_server_login_req
_function_server_login_req::_function_server_login_req()
{
    iCmdID = CMD_FUNCSERV_REQ;
}
BOOL _function_server_login_req::SetPassport(const TDes& aPassport)
{
    if (aPassport.Length()<EMAXLEN)
    {
        iPassport.Copy(aPassport);
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}
void _function_server_login_req::GetBuffer(TDes8& aBuffer) const
{
    const TInt index = aBuffer.Length();

    // build self
    BYTE len;
    len = (BYTE)iPassport.Length();
    aBuffer.Append(&len,sizeof(len));
    aBuffer.Append((BYTE*)(iPassport.Ptr()),len*sizeof(TText));
    
    // Get the header of frame
    //iLenContext = (TUint16)(aBuffer.Length()-index+_content_header::ELenContent);
    TBuf8<_content_header::ELenOfHead> header;
    _content_header::GetBuffer(header);
    aBuffer.Insert(index,header);
}

//////////////////////////////////////////////////////////////////////////
//#######################################################################
//_function_server_login_rsp
_function_server_login_rsp::_function_server_login_rsp()
{

}
BOOL _function_server_login_rsp::IsSuccess() const
{
    return (iLoginRst==ESuccess);
}
_function_server_login_rsp::ParseBuffer(const TDesC8& aBuffer,TInt& aIndex)
{
    _content_header::ParseBuffer(aBuffer,aIndex);
    if (iRstFlag==_content_header::ESV_Failure)
    {
        return TRUE;
    }

    // to do implement me
    memcpy(&iLoginRst,lpBuffer+aIndex,sizeof(iLoginRst));
    aIndex += sizeof(iLoginRst);

    return TRUE;
}
//////////////////////////////////////////////////////////////////////////
//#######################################################################
// _profile_report
_profile_report::_profile_report()
{
    iCmdID = CMD_INITI_REPORT;
    iInterval = EInterval;
}
void _profile_report::GetBuffer(TDes8& aBuffer) const
{
    const TInt index = aBuffer.Length();

    // build self
    //TUint16 newInterval = iInterval*2;
    aBuffer.Append((BYTE*)&iInterval,sizeof(iInterval));

    // Get the header of frame
    //iLenContext = (TUint16)(aBuffer.Length()-index+_content_header::ELenContent);
    TBuf8<_content_header::ELenOfHead> header;
    _content_header::GetBuffer(header);
    aBuffer.Insert(index,header);
}


//////////////////////////////////////////////////////////////////////////
//#######################################################################
// _poi_inf_request
_poi_inf_request::_poi_inf_request(TUint16 aNumberReq):iNumReq(aNumberReq)
{
    iCityID.Copy(_L8("110000"));
    iCmdID = CMD_POIINF_REQ;
    iStartPoiID = 0;
}
void _poi_inf_request::SetName(const TDesC8& aName)
{
    if (aName.Size()<=0)
    {
        return;
    }

    if (aName[0]<='z' && aName[0]>='a' || aName[0]<='Z' && aName[0]>='A')
    {
        iContentType = EReqByPinYin;
    }
    else
    {
        iContentType = EReqByName;
    }


    if (aName.Size()<=EMaxSize)
    {
        iBuffer.Copy(aName);
    }
    else
    {
        iBuffer.Copy(aName.Ptr(),EMaxSize);
    }
}

void _poi_inf_request::SetRegion(const TRect& aRegion,TUint16 aReqType)
{
    iContentType = EReqByRegion;

    iBuffer.Copy((BYTE*)&(aRegion.iTl.iX),sizeof(TInt));
    iBuffer.Append((BYTE*)&(aRegion.iTl.iY),sizeof(TInt));
    iBuffer.Append((BYTE*)&(aRegion.iBr.iX),sizeof(TInt));
    iBuffer.Append((BYTE*)&(aRegion.iBr.iY),sizeof(TInt));

    iBuffer.Append((BYTE*)&aReqType,sizeof(aReqType));
}
void _poi_inf_request::SetReqType(TUint16 aReqType)
{
    iContentType = EReqByType;

    iBuffer.Copy((BYTE*)&aReqType,sizeof(aReqType));
}
void _poi_inf_request::GetBuffer(TDes8& aBuffer) const
{
    const TInt index = aBuffer.Length();

    // build self
    // CID
    BYTE cid[ELenCityID] = {0};
    memcpy(cid,iCityID.Ptr(),iCityID.Length());
    aBuffer.Append(cid,ELenCityID);

    // Name or PinYin or Region or Type.
    switch(iContentType)
    {
    case EReqByName:
    case EReqByPinYin:
        {
            BYTE len = (BYTE)iBuffer.Size();
            aBuffer.Append((BYTE*)&len,sizeof(len));
        }
        break;
    }
    aBuffer.Append(iBuffer);

    // Number of request
    aBuffer.Append((BYTE*)&iNumReq,sizeof(iNumReq));

    // Start POI's ID
    aBuffer.Append((BYTE*)&iStartPoiID,sizeof(iStartPoiID));

    // Get the header of frame
    //iLenContext = (TUint16)(aBuffer.Length()-index+_content_header::ELenContent);
    TBuf8<_content_header::ELenOfHead> header;
    _content_header::GetBuffer(header);
    aBuffer.Insert(index,header);
}


//////////////////////////////////////////////////////////////////////////
//#######################################################################
// _poi_inf_record
_poi_inf_record::_poi_inf_record()
{
    iPoiName = NULL;		// Name
    iPoiAddress = NULL;	// Address
    iPoiTel = NULL;		// Telephone
    //iDescription = NULL;
}
_poi_inf_record::~_poi_inf_record()
{
    delete iPoiName;	// Name
    delete iPoiAddress;	// Address
    delete iPoiTel;		// Telephone
    //delete iDescription;
}
void _poi_inf_record::SetPoiName(const TDes& aName)
{
    delete iPoiName;
    iPoiName = HBufC16::New(aName.Length());
    iPoiName->Des().Copy(aName);
}
void _poi_inf_record::GetUniName(TDes& aUniName)
{
    if (iPoiName)
    {
        aUniName.Copy(iPoiName->Des());
    }
}
void _poi_inf_record::GetUniAddress(TDes& aUniAddr)
{
    if (iPoiAddress)
    {
        aUniAddr.Copy(iPoiAddress->Des());
    }
}
void _poi_inf_record::GetUniTel(TDes& aUniTel)
{
    if (iPoiTel)
    {
        aUniTel.Copy(iPoiTel->Des());
    }
}
void _poi_inf_record::GetUniDesc(TDes& /*aUniDesc*/)
{
    /*if (iDescription)
    {
    aUniDesc.Copy(iDescription->Des());
    }*/
}
void _poi_inf_record::Copy(const _poi_inf_record& aOther)
{
    if (this!=&aOther)
    {
        iPoiID = aOther.iPoiID;
        
        delete iPoiName;
        iPoiName = NULL;
        if (aOther.iPoiName!=NULL)
        {
            iPoiName = HBufC16::New(aOther.iPoiName->Length());
            iPoiName->Des().Copy(aOther.iPoiName->Des());
        }
        
        delete iPoiAddress;
        iPoiAddress = NULL;
        if (aOther.iPoiAddress!=NULL)
        {
            iPoiAddress = HBufC16::New(aOther.iPoiAddress->Length());
            iPoiAddress->Des().Copy(aOther.iPoiAddress->Des());
        }
        
        delete iPoiTel;
        iPoiTel = NULL;
        if (aOther.iPoiTel!=NULL)
        {
            iPoiTel = HBufC16::New(aOther.iPoiTel->Length());
            iPoiTel->Des().Copy(aOther.iPoiTel->Des());
        }
        
        iLong = aOther.iLong;
        iLati = aOther.iLati;
        iPoiType = aOther.iPoiType;
    }
}
BOOL _poi_inf_record::ParseBuffer(const TDesC8& aBuffer,TInt& aIndex)
{
    // ID
    memcpy(&iPoiID,lpBuffer+aIndex,sizeof(iPoiID));
    aIndex += sizeof(iPoiID);

    // Name
    BYTE len;
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    if (len>EMaxSize)
    {
        return FALSE;
    }
    iPoiName = HBufC16::NewL(len);
    if (len>0)
    {
        // ?????????????????????????????
        TUint16* temp = new TUint16[len];
        memcpy(temp,lpBuffer+aIndex,2*len);
        iPoiName->Des().Copy(temp,len);
        delete temp;
    }
    aIndex = aIndex + 2*len;

    // Address
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    if (len>EMaxSize)
    {
        return FALSE;
    }
    iPoiAddress = HBufC16::NewL(len);
    if (len>0)
    {
        // ?????????????????????????????
        TUint16* temp = new TUint16[len];
        memcpy(temp,lpBuffer+aIndex,2*len);
        iPoiAddress->Des().Copy(temp,len);
        delete temp;
    }
    aIndex = aIndex + 2*len;

    // Telephone
    memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    if (len>EMaxSize)
    {
        return FALSE;
    }
    iPoiTel = HBufC16::NewL(len);
    if (len>0)
    {
        // ?????????????????????????????
        TUint16* temp = new TUint16[len];
        memcpy(temp,lpBuffer+aIndex,2*len);
        iPoiTel->Des().Copy(temp,len);
        delete temp;
    }
    aIndex = aIndex + 2*len;

    // 经度
    memcpy(&iLong,lpBuffer+aIndex,sizeof(iLong));
    aIndex += sizeof(iLong);
    // 纬度
    memcpy(&iLati,lpBuffer+aIndex,sizeof(iLati));
    aIndex += sizeof(iLati);

    // POI类型
    memcpy(&iPoiType,lpBuffer+aIndex,sizeof(iPoiType));
    aIndex += sizeof(iPoiType);

    // POI描述
    /*memcpy(&len,lpBuffer+aIndex,sizeof(len));
    aIndex ++;
    if (len>EMaxSize*2)
    {
    return FALSE;
    }
    iDescription = HBufC16::NewL(len);
    iDescription->Des().Copy((TUint16*)(lpBuffer+aIndex),len);
    aIndex = aIndex + 2*len;*/

    return TRUE;
}

// _poi_inf_response
_poi_inf_response::~_poi_inf_response()
{
    iPOIList.ResetAndDestroy();
    iPOIList.Close();
}
void _poi_inf_response::Copy(const _poi_inf_response& aOther)
{
    if (this!=&aOther)
    {
        iPOIList.ResetAndDestroy();

        for (TInt i=0; i<aOther.iPOIList.Count(); i++)
        {
            _poi_inf_record* pRecord = new _poi_inf_record;
            pRecord->Copy(*(aOther.iPOIList[i]));
            iPOIList.Append(pRecord);
        }
    }
}
void _poi_inf_response::Append(const _poi_inf_response& aOther)
{
    if (this!=&aOther)
    {
        for (TInt i=0; i<aOther.iPOIList.Count(); i++)
        {
            _poi_inf_record* pRecord = new _poi_inf_record;
            pRecord->Copy(*(aOther.iPOIList[i]));
            iPOIList.Append(pRecord);
        }
    }
}
BOOL _poi_inf_response::ParseBuffer(const TDesC8& aBuffer,TInt& aIndex)
{
    _content_header::ParseBuffer(aBuffer,aIndex);
    if (iRstFlag==_content_header::ESV_Failure)
    {
        return TRUE;
    }

    //
    const BYTE* frame = lpBuffer;

    // Number of record
    BYTE count;
    memcpy(&count,frame+aIndex,sizeof(count));
    aIndex += sizeof(count);
    if (count>EMaxNumber)
    {
        return FALSE;
    }

    // POI records.
    for (TInt ii=0; ii<count; ii++)
    {
        PTPoiInfRecord pPoiRecord = new TPoiRecord;

        if (pPoiRecord->ParseBuffer(aBuffer,aIndex))
        {
            iPOIList.Append(pPoiRecord);
        }
        else
        {
            delete pPoiRecord;
        }
    }

    return TRUE;
}

#endif