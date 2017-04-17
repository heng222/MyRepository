/*****************************************************************************
 * module FrameTimer.h
 *
 *	Defines precision timer class.  Used to determine elapsed time in CMM3DSpecialEffect.	
 *	
 * Copyright (c) Microsoft Corporation. All rights reserved.
 *****************************************************************************/

#pragma once
#ifndef __FRAMETIMER_H
#define __FRAMETIMER_H

typedef unsigned __int64 UINT64; 


/***************************************************************************
 * class CFrameTimer - precision timer class
/***************************************************************************/
class CFrameTimer
{
public:
    CFrameTimer();

    void Start(float fFramesPerSec);
    void Frame();

    float GetFramesPerSec();
    float GetSecsPerFrame();

    UINT64 GetTicks();
    UINT64 GetTicksPerSec();
    UINT64 GetTicksPerFrame();

protected:
    float m_fTicksPerSec;
    float m_fFramesPerSec;
    float m_fSecsPerFrame;

    UINT64 m_qwTicks;
    UINT64 m_qwTicksPerSec;
    UINT64 m_qwTicksPerFrame;
};



/****************************************************************************/
/* Inline methods 
*****************************************************************************/

inline float CFrameTimer::GetFramesPerSec()
{
    return m_fFramesPerSec;
}

inline float CFrameTimer::GetSecsPerFrame()
{
    return m_fSecsPerFrame;
}

inline UINT64 CFrameTimer::GetTicksPerSec()
{
    return m_qwTicksPerSec;
}

inline UINT64 CFrameTimer::GetTicksPerFrame()
{
    return m_qwTicksPerFrame;
}


#endif __FRAMETIMER_H