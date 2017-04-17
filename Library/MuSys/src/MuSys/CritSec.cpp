#include "StdAfx.h"
#include "CritSec.h"

//////////////////////////////////////////////////////////////////////////
CCritSec::CCritSec(void)
{
    InitializeCriticalSection(&m_CriticalSection);
}

CCritSec::~CCritSec(void)
{
    DeleteCriticalSection(&m_CriticalSection);
}

void CCritSec::Lock()
{
    EnterCriticalSection(&m_CriticalSection);
}

void CCritSec::Unlock()
{
    LeaveCriticalSection(&m_CriticalSection);
}