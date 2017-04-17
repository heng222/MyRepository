#include "stdafx.h"
#include ".\authenmgr.h"

//////////////////////////////////////////////////////////////////////////
CAuthenMgr::CAuthenMgr(void)
{
}

CAuthenMgr::~CAuthenMgr(void)
{
    while (m_PassportList.GetHeadPosition())
    {
        delete m_PassportList.RemoveHead();
    }
}

//////////////////////////////////////////////////////////////////////////
void CAuthenMgr::AddPassport(PTAuthenPassport aNewPassport)
{
    m_PassportList.AddTail(aNewPassport);
}

BOOL CAuthenMgr::IsValidPassport(const CString& strUserName,LPBYTE byPassport,int iLenPassport,BOOL bDel/*=TRUE*/)
{
    POSITION posDel;
    POSITION pos = m_PassportList.GetHeadPosition();

    // Construct a passport
    TAuthenPassport passport;
    passport.strUserName = strUserName;
    passport.SetPassport(byPassport,sizeof(byPassport));


    while (pos)
    {
        posDel = pos;
        PTAuthenPassport pPassport = m_PassportList.GetNext(pos); 
        if (*pPassport==passport)
        {
            if (bDel)
            {
                PTAuthenPassport pDel = m_PassportList.GetAt(posDel);
                m_PassportList.RemoveAt(posDel);
                delete pDel;
            }
            return TRUE;
        }
    }

    return FALSE;
}

