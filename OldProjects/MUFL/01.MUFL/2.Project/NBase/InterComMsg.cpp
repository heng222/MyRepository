

#include "stdafx.h"

#include "InterComMsg.h"

//////////////////////////////////////////////////////////////////////////

// 这是导出变量的一个示例
// It's recommend that never ever export a variable.
NBASE_EXT_API int nWDLL = 0;
 
// Constructor && Destructor
TImcMsg::TImcMsg()
{
    SetSourceModule(ID_MODULE_NONE);
    SetDestModule(ID_MODULE_NONE);
    m_iDispatchType = EDT_SYNCHRONOUS;
    m_bAutoDel = TRUE;
    
    m_wMsgType = 0;
    m_wParam = NULL;
    m_lParam = NULL;
}

TImcMsg::TImcMsg(WORD wMsgType,TModuleID iSourceMod,TModuleID iDestMod)
{
    m_wMsgType = wMsgType;
    SetSourceModule(iSourceMod);
    SetDestModule(iDestMod);
    m_iDispatchType = EDT_SYNCHRONOUS;
    m_bAutoDel = TRUE;

    m_wParam = NULL;
    m_lParam = NULL;
}

TImcMsg::~TImcMsg()
{}

IMPLEMENT_DYNCREATE(TImcMsg,CObject)

// 
TImcMsg* TImcMsg::Duplicate() const
{
    TImcMsg* pDump = new TImcMsg;
    if (pDump!=NULL)
    {
        pDump->operator =(*this);
    }
    return pDump;
}

void TImcMsg::Serialize(CArchive& ar)
{
    if ( ar.IsStoring() )
    {
        ar<<m_wMsgType<<m_SourceModID;
        ar<<m_byNumDestModule;
        for (int i=0; i<m_byNumDestModule; i++)
        {
            ar<<m_DestModule[i];
        }
    }
    else
    {
        ar>>m_wMsgType>>m_SourceModID;
        ar>>m_byNumDestModule;
        for (int i=0; i<m_byNumDestModule; i++)
        {
            ar>>m_DestModule[i];
        }
    }
}


// New functions
TImcMsg& TImcMsg::operator= (const TImcMsg& other)
{
    if (this != &other)
    {
        m_byNumDestModule = other.m_byNumDestModule;
        for (int i=0; i<other.m_byNumDestModule; i++)
        {
            m_DestModule[i] = other.m_DestModule[i];
        }
        m_SourceModID = other.m_SourceModID;
        m_iDispatchType = other.m_iDispatchType;
        m_wMsgType = other.m_wMsgType;
        m_wParam = other.m_wParam;
        m_lParam = other.m_lParam;
        m_bAutoDel = other.m_bAutoDel;
    }

    return *this;
}

void TImcMsg::Copy(const TImcMsg& other)
{
    *this = other;
}

BYTE TImcMsg::GetNumDestMod() const
{
    return m_byNumDestModule;
}

TModuleID TImcMsg::GetDestMod(int aIndex) const
{
    if (aIndex<m_byNumDestModule && aIndex>=0)
    {
        return m_DestModule[aIndex];
    }
    else
    {
        return ID_MODULE_NONE;
    }
}

TModuleID TImcMsg::GetSourceModul() const
{
    return m_SourceModID;
}

void TImcMsg::SetSourceModule(TModuleID aSourceID)
{
    m_SourceModID = aSourceID;
}

void TImcMsg::SetDestModule(TModuleID aDest)
{
    memset(m_DestModule,0,sizeof(m_DestModule));
    m_byNumDestModule = 1;
    m_DestModule[0] = aDest;
}

void TImcMsg::SetSynchronous(BOOL bEnable)
{
    if (bEnable)
    {
        m_iDispatchType = EDT_SYNCHRONOUS ;
    }
    else
    {
        m_iDispatchType = EDT_ASYNCHRONOUS ;
    }
}

void TImcMsg::SetAutoDel(BOOL bFlag)
{
    m_bAutoDel = bFlag;
}

void TImcMsg::AutoDelete()
{
    if (m_iDispatchType==TImcMsg::EDT_ASYNCHRONOUS && m_bAutoDel)
    {
        delete this;
    }
}

BOOL TImcMsg::IsSynchronous() const
{
    return (m_iDispatchType==TImcMsg::EDT_SYNCHRONOUS);
}

int TImcMsg::AddDestModule(TModuleID aDest)
{
    if (GetNumDestMod()<EMaxNumDestMod)
    {
        if (!IsExistDestModule(aDest))
        {
            m_DestModule[m_byNumDestModule] = aDest;
            m_byNumDestModule++;
        }
        else
        {
            return ERR_ALREADYEXIST;
        }
    }
    else
    {
        return ERR_OVERFLOW;
    }

    return 0;
}

void TImcMsg::DelDestModule(TModuleID aDest)
{
    TModuleID temp[EMaxNumDestMod] = {0};

    memcpy(temp,m_DestModule,sizeof(temp));
    memset(m_DestModule,0,sizeof(m_DestModule));

    int i=0;
    int j=0;
    for (; i<m_byNumDestModule; i++,j++)
    {
        if (temp[i] != aDest)
        {
            m_DestModule[j] = temp[i];
        }
        else
        {
            j--;
        }
    }

    m_byNumDestModule = j;
}

BOOL TImcMsg::IsExistDestModule(TModuleID aID) const
{
    for (int i=0; i<m_byNumDestModule; i++)
    {
        if (m_DestModule[i]==aID)
        {
            return TRUE;
        }
    }
    return FALSE;
}

NB_MSGID TImcMsg::GetMsgType() const
{
    return m_wMsgType;
}
