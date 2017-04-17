

#include "stdafx.h"
#include "BusinessProtcl.h"
#include "CommonFunc.h"

//////////////////////////////////////////////////////////////////////////
// _content_header
_business_com_frame_::_business_com_frame_()
{    
    // Protocol version
    byVersion = EVersion;
    // Command ID
    wCmdID = 0;
    // Content type
    byContentType = 0; 
    // the code of service
    bySerciveCode = ESuccess;
    // reserved
    memset(byReserved,0,sizeof(byReserved));
}
_business_com_frame_::~_business_com_frame_()
{

}
WORD _business_com_frame_::GetCommandID() const
{
    return 0;
}
int _business_com_frame_::GetProType()
{
    return E_PRO_FLAG;
}
CString _business_com_frame_::GetProName()
{
    return _T("与手机终端的通信协议-Binary");
}
void _business_com_frame_::GetBuffer(IN OUT LPBYTE lpBuffer,IN OUT int& aIndex) const
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
    // service code
    memcpy(lpBuffer+aIndex,&bySerciveCode,sizeof(bySerciveCode));
    aIndex += sizeof(bySerciveCode);
    // Reserved
    memcpy(lpBuffer+aIndex,byReserved,sizeof(byReserved));
    aIndex += sizeof(byReserved);

}
BOOL _business_com_frame_::ParseBuffer(IN OUT const LPBYTE& lpBuffer,IN OUT int& aIndex)
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
    // Service code
    memcpy(&bySerciveCode,lpBuffer+aIndex,sizeof(bySerciveCode));
    aIndex += sizeof(bySerciveCode);
    // Reserved
    memcpy(&byReserved,lpBuffer+aIndex,sizeof(byReserved));
    aIndex += sizeof(byReserved);

    return TRUE;
}

_business_com_frame_* _business_com_frame_::GetInstance(WORD wCommandID)
{
    PTBusinessFrm pContent = NULL;

    //switch(wCommandID)
    //{
    //    // Login
    //case TLoginReqBin::ECommandID:
    //    pContent = new TLoginReqBin;
    //    break;
    //case TLoginRspBin::ECommandID:
    //    pContent = new TLoginRspBin;
    //    break;

    //    // Exit
    //case TClientExitBin::ECommandID:
    //    pContent = new TClientExitBin;
    //    break;

    //}

    if (pContent!=NULL)
    {
        pContent->SetAutoDel(TRUE);
    }

    return pContent;
}


#if 0
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


#endif
