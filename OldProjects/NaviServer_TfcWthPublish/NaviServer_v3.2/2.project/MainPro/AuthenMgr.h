#pragma once
#include "afx.h"
#include "afxtempl.h"
//////////////////////////////////////////////////////////////////////////

// Passport,comes from BALANCE SERVER

struct TAuthenPassport
{
    CString     strUserName;    // a registered username

    BYTE        byLenValid;     // the valid length of passport
    enum {EMaxLenPst= 10};
    BYTE        byPassport[EMaxLenPst];   // The passport

    CTime       timeExpired;    // Expired date

    // Constructor
    TAuthenPassport::TAuthenPassport()
    {
        memset(byPassport,0,sizeof(byPassport));
        timeExpired = CTime::GetCurrentTime();
    }

    // Functions
    void SetPassport(LPBYTE lpbyPassport,BYTE byLen)
    {
        if (byLen<=EMaxLenPst)
        {
            memcpy(byPassport,lpbyPassport,byLen);
            byLenValid = byLen;
        }
    }

    BOOL operator==(const TAuthenPassport& another) const
    {
        if (strUserName!=another.strUserName || byLenValid!=another.byLenValid)
        {
            return FALSE;
        }

        for(int i=0; i<byLenValid; i++)
        {
            if (byPassport[i]!=another.byPassport[i])
            {
                return FALSE;
            }
        }

        return TRUE;
    }
};
typedef TAuthenPassport* PTAuthenPassport;
typedef CList<PTAuthenPassport,PTAuthenPassport> CAuthenPassportList;

//////////////////////////////////////////////////////////////////////////
class CAuthenMgr :   public CObject
{
public:
    CAuthenMgr(void);
    ~CAuthenMgr(void);

public:
    void    AddPassport(PTAuthenPassport aNewPassport);

    // Is the passport specified valid?
    // bDel indicates if delete the passport existing in the list when it's valid.
    BOOL    IsValidPassport(const CString& strUserName,LPBYTE byPassport,int iLenPassport,
                        BOOL bDel=TRUE); 

private:
    CAuthenPassportList     m_PassportList;

};

//////////////////////////////////////////////////////////////////////////
