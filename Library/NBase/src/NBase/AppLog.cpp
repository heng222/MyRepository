#include "StdAfx.h"
#include "AppLog.h"
#include "NBaseModule.h"


// Constructor
CAppLog::CAppLog()
{
    //
    m_wMsgType = CImcMessage::AppLogMsg;
    //
    iLogType = ELL_INFORMATION;


    EnableStorage(TRUE);

}

CAppLog::CAppLog(const CAppLog& aOther)
{
    *this = aOther;
}

CAppLog::CAppLog(const TString& strMsg)
{
    //
    m_wMsgType = CImcMessage::AppLogMsg;

    //
    iLogType = ELL_INFORMATION;
    strComments = strMsg.c_str();


    EnableStorage(TRUE);

}


CAppLog::~CAppLog()
{
}

IMPLEMENT_SERIAL(CAppLog,CImcMessage,1)

// 
CAppLog& CAppLog::operator= (const CAppLog& other)
{
    if (this != &other)
    {
        CImcMessage::operator =(other);

        iLogType = other.iLogType;
        iLogType = other.iLogType;
        timestamp = other.timestamp;
        strComments = other.strComments;
        m_bIsStorage = other.m_bIsStorage;
    }

    return *this;
}

// From TImcMsg

CAppLog* CAppLog::Duplicate() const
{
    CAppLog* pDump = new CAppLog;
    if (pDump!=NULL)
    {
        *pDump = *this;
    }
    return pDump;
}


TString CAppLog::GetStringLogType(TLogType type)
{
    if (type == ELL_INFORMATION)
    {
        return _T("ÐÅÏ¢");
    }
    else if (type == ELL_WARNING)
    {
        return _T("¾¯¸æ");
    }
    else if (type == ELL_ERROR)
    {
        return _T("´íÎó");
    }
    else
    {
        return CStringUtility::Format(_T("%d"), (int)type);
    }
}

void CAppLog::Serialize(CArchive& ar)
{
    if ( ar.IsStoring() )
    {
        //ar<<(int)iLogType<<logTime<<strComments;
    }
    else
    {
        //ar>>(int)iLogType>>logTime>>strComments;
    }
}

// New Functions

void CAppLog::UpdateToCurrentTime()
{
    timestamp.LoadCurrentDateTime();
}

void CAppLog::EnableStorage(BOOL bEnable/* =FALSE */)
{
    m_bIsStorage = bEnable;
}

BOOL CAppLog::IsStorage() const
{
    return m_bIsStorage;
}

// insertion operations
CArchive& AFXAPI operator<<(CArchive& ar, const CAppLog* pOb)
{
    //ar<<pOb->iLogType<<pOb->iLogType<<pOb->timestamp<<pOb->strComments;
    return ar;
}


