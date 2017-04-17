
#include "stdafx.h"
#include "SPPrototocol.h"
#include "CommonFunc.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// _service_provider_frame
_service_provider_frame::_service_provider_frame()
{
    strVersion = "V1";
}
_service_provider_frame::~_service_provider_frame()
{

}

int _service_provider_frame::GetProType()
{
    return E_PRO_FLAG;
}
CString _service_provider_frame::GetProName()
{
    return _T("������ṩ�̣�SP����ͨ��Э��");
}
//CString _service_provider_frame::GetFrameType() const
//{
//    return _T("");
//}
void _service_provider_frame::GetBuffer(CString& strFrame) const
{
    // �õ�Ԫ���б�
    CStringList strFrameList;
    GetElementList(strFrameList);

    // ��ʽ��
    CString strDelimiter;
    _service_provider_frame::GetDelimiter(strDelimiter);
    GetFormattedStrList(strFrameList,strDelimiter,strFrame);
}

BOOL _service_provider_frame::ParseBuffer(const CStringList& cStrList,POSITION& posIdx)
{
    if (cStrList.GetCount()>=ENumMember)
    {
        strVersion = cStrList.GetNext(posIdx);     // Version
        strFrameType = cStrList.GetNext(posIdx);   // Э������
        strSPNo = cStrList.GetNext(posIdx);        // SP����
        strMobilNo = cStrList.GetNext(posIdx);     // �ֻ�����
        strServcieCode = cStrList.GetNext(posIdx); // ҵ�����
        strLinkIdx = cStrList.GetNext(posIdx);     // ��·ID
        iCodeing = atoi(cStrList.GetNext(posIdx)); // �����ʽ
        strCityName = cStrList.GetNext(posIdx);    // ��������
        cDateTime.ParseDateTime(cStrList.GetNext(posIdx));      // ��Ϣ����������
    }
    else
    {
        return FALSE;
    }

    return TRUE;
}
void _service_provider_frame::GetElementList(CStringList& strEleList) const
{
    strEleList.AddTail(strVersion);
    strEleList.AddTail(strFrameType);
    strEleList.AddTail(strSPNo);
    strEleList.AddTail(strMobilNo);
    strEleList.AddTail(strServcieCode);
    strEleList.AddTail(strLinkIdx);
    CString strCode;
    strCode.Format("%d",iCodeing);
    strEleList.AddTail(strCode);
    strEleList.AddTail(strCityName);
    strEleList.AddTail(cDateTime.Format("%Y-%m-%d %H:%M:%S"));
}

// Static functions
_service_provider_frame* _service_provider_frame::GetInstance(const CString& strFrameType)
{
    _service_provider_frame* pContent = NULL;
    if (strFrameType.CompareNoCase(_pay_monthly_register::gMsgType)==0)
    {
        pContent = new _pay_monthly_register;
    }
    /*else if ()
    {
    }*/
    

    return pContent;
}
void _service_provider_frame::Encapsulate(CString& strFrame)
{
    strFrame.Insert(0,EFrameHeader); 
    strFrame.Insert(0,EFrameHeader);
    strFrame.AppendChar(EFrameTail);
    strFrame.AppendChar(EFrameTail);
}
void _service_provider_frame::PellShell(CString& strFrame) // ����Э��֡��֡ͷ��֡β
{
    strFrame.Trim(EFrameHeader);
    strFrame.Trim(EFrameTail);
}
void _service_provider_frame::GetDelimiter(CString& strDelimiter)
{
    strDelimiter.Format("%c",_service_provider_frame::EFrmDelimiter);
}

//////////////////////////////////////////////////////////////////////////
// _pay_monthly_register
const CString _pay_monthly_register::gMsgType = "1BYDZ";
_pay_monthly_register::_pay_monthly_register()
{
    strFrameType = gMsgType;
}
//void _month_register_success::GetBuffer(CString& strFrame) const
//{
//    // �õ�Ԫ���б�
//    CStringList strFrameList;
//    GetElementList(strFrameList);
//
//    // ��ʽ��
//    CString strDelimiter;
//    _service_provider_frame::GetDelimiter(strDelimiter);
//    GetFormattedStrList(strFrameList,strDelimiter,strFrame);
//
//}

BOOL _pay_monthly_register::ParseBuffer(const CStringList& cStrList,POSITION& posIdx)
{
    BOOL bRc = _service_provider_frame::ParseBuffer(cStrList,posIdx);
    if (!bRc)
    {
        return FALSE;
    }

    if (posIdx!=NULL)
    {
        strContent = cStrList.GetNext(posIdx);
    }
    else
    {
        return FALSE;
    }


    return TRUE;
}
void _pay_monthly_register::GetElementList(CStringList& strEleList) const
{
    // Invoking TSpFrame::GetElementList
    _service_provider_frame::GetElementList(strEleList);

    //
    strEleList.AddTail(strContent);
}

//////////////////////////////////////////////////////////////////////////
// ���¸���ȡ��
const CString _pay_monthly_cancel::gMsgType = "2BYQX";
_pay_monthly_cancel::_pay_monthly_cancel()
{
    strFrameType = gMsgType;
}

BOOL _pay_monthly_cancel::ParseBuffer(const CStringList& cStrList,POSITION& posIdx)
{
    BOOL bRc = _service_provider_frame::ParseBuffer(cStrList,posIdx);
    if (!bRc)
    {
        return FALSE;
    }

    if (posIdx!=NULL)
    {
        strContent = cStrList.GetNext(posIdx);
    }
    else
    {
        return FALSE;
    }


    return TRUE;
}
void _pay_monthly_cancel::GetElementList(CStringList& strEleList) const
{
    // Invoking TSpFrame::GetElementList
    _service_provider_frame::GetElementList(strEleList);

    //
    strEleList.AddTail(strContent);
}


//////////////////////////////////////////////////////////////////////////
// 

//////////////////////////////////////////////////////////////////////////
// 

//////////////////////////////////////////////////////////////////////////
// 

//////////////////////////////////////////////////////////////////////////
// 

//////////////////////////////////////////////////////////////////////////
// 

//////////////////////////////////////////////////////////////////////////
// 

//////////////////////////////////////////////////////////////////////////
// 

//////////////////////////////////////////////////////////////////////////
// 