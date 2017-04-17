#include "StdAfx.h"
#include "AutoLock.h"

//////////////////////////////////////////////////////////////////////////
CAutoLock::CAutoLock(CCritSec *plock)
{
    plock->Lock();
    m_pCriSec = plock;
}

CAutoLock::~CAutoLock(void)
{
    m_pCriSec->Unlock();
}
