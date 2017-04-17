

#include "stdafx.h"

#include "ImcMessage.h"
#include "NBaseModule.h"

//////////////////////////////////////////////////////////////////////////

const int CImcMessage::ReservedID = 0x0100;
const int CImcMessage::RestartApp = 0x0001;
const int CImcMessage::CloseAllModule = 0x0002;
const int CImcMessage::AppLogMsg = CImcMessage::ReservedID + 1;
 
// Constructor && Destructor
CImcMessage::CImcMessage()
{
    SetSourceModule(CNBaseModule::ModuleIDNone);
    SetDestModule(CNBaseModule::ModuleIDNone);
    m_iDispatchType = EDT_SYNCHRONOUS;
    m_bAutoDel = TRUE;
    
    m_wMsgType = 0;
    m_wParam = NULL;
    m_lParam = NULL;
}

CImcMessage::CImcMessage(WORD wMsgType,int iSourceMod,int iDestMod)
{
    m_wMsgType = wMsgType;
    SetSourceModule(iSourceMod);
    SetDestModule(iDestMod);
    m_iDispatchType = EDT_SYNCHRONOUS;
    m_bAutoDel = TRUE;

    m_wParam = NULL;
    m_lParam = NULL;
}

CImcMessage::~CImcMessage()
{}

IMPLEMENT_DYNCREATE(CImcMessage,CObject)

// 
CImcMessage* CImcMessage::Duplicate() const
{
    CImcMessage* pDump = new CImcMessage;
    if (pDump!=NULL)
    {
        pDump->operator =(*this);
    }
    return pDump;
}

void CImcMessage::Serialize(CArchive& ar)
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
CImcMessage& CImcMessage::operator= (const CImcMessage& other)
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

void CImcMessage::Copy(const CImcMessage& other)
{
    *this = other;
}

BYTE CImcMessage::GetNumDestMod() const
{
    return m_byNumDestModule;
}

int CImcMessage::GetDestMod(int aIndex) const
{
    if (aIndex<m_byNumDestModule && aIndex>=0)
    {
        return m_DestModule[aIndex];
    }
    else
    {
        return CNBaseModule::ModuleIDNone;
    }
}

int CImcMessage::GetSourceModul() const
{
    return m_SourceModID;
}

void CImcMessage::SetSourceModule(int aSourceID)
{
    m_SourceModID = aSourceID;
}

void CImcMessage::SetDestModule(int aDest)
{
    memset(m_DestModule,0,sizeof(m_DestModule));
    m_byNumDestModule = 1;
    m_DestModule[0] = aDest;
}

void CImcMessage::SetSynchronous(BOOL bEnable)
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

void CImcMessage::SetAutoDel(BOOL bFlag)
{
    m_bAutoDel = bFlag;
}

void CImcMessage::AutoDelete()
{
    if (m_iDispatchType==CImcMessage::EDT_ASYNCHRONOUS && m_bAutoDel)
    {
        delete this;
    }
}

BOOL CImcMessage::IsSynchronous() const
{
    return (m_iDispatchType==CImcMessage::EDT_SYNCHRONOUS);
}

int CImcMessage::AddDestModule(int aDest)
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

void CImcMessage::DelDestModule(int aDest)
{
    int temp[EMaxNumDestMod] = {0};

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

BOOL CImcMessage::IsExistDestModule(int aID) const
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

unsigned short CImcMessage::GetMsgType() const
{
    return m_wMsgType;
}

//////////////////////////////////////////////////////////////////////////

// It's recommend that never ever export a variable.
// There, it's just a demo to show how to do that.
NBASE_EXT_API int nWDLL = 0;