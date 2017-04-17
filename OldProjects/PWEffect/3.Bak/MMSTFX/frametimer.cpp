/*****************************************************************************
 * module FrameTimer.cpp
 *
 *	implements precision timer
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#include "stdafx.h"

#include "FrameTimer.h"
#include "time.h"
#include "mmsystem.h"

/*****************************************************************************
 * CFrameTimer implementation 
/****************************************************************************/

/******************************************************************************
 * Description: constructor
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
CFrameTimer::CFrameTimer()
{
    if(!QueryPerformanceFrequency((LARGE_INTEGER *) &m_qwTicksPerSec))
        m_qwTicksPerSec = 1000;

    m_fTicksPerSec  = (float) (__int64) m_qwTicksPerSec;
}

/******************************************************************************
 * Description: start the timer
 *
 * float fFramesPerSec - requested precision
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
void CFrameTimer::Start(float fFramesPerSec)
{
	RTN_VOID_IF_FALSE(fFramesPerSec != 0.0);

    m_fFramesPerSec = fFramesPerSec;
    m_fSecsPerFrame = 1.0f / fFramesPerSec;
    m_qwTicksPerFrame = m_qwTicksPerSec / (__int64) fFramesPerSec;

    m_qwTicks = GetTicks();
}

/******************************************************************************
 * Description: calculate time
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
void CFrameTimer::Frame()
{
    UINT64 qw;
    qw = GetTicks();


    if(qw != m_qwTicks)
    {
        m_qwTicksPerFrame = qw - m_qwTicks;
        m_qwTicks = qw;

        m_fFramesPerSec = //0.0f * m_fFramesPerSec +
            1.0f * (m_fTicksPerSec / (float) (__int64) m_qwTicksPerFrame);

        if(m_fFramesPerSec < 1.0f)
            m_fFramesPerSec = 1.0f;

        m_fSecsPerFrame = 1.0f / m_fFramesPerSec;
    }
}


/******************************************************************************
 * Description: Get ticks from counter
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
UINT64 CFrameTimer::GetTicks()
{
    UINT64 qw;

    if(QueryPerformanceCounter((LARGE_INTEGER *) &qw))
    {
        while(!qw)
          QueryPerformanceCounter((LARGE_INTEGER *) &qw);
    }
    else
    {
        qw = (UINT64) timeGetTime();
    }

    return qw;
}