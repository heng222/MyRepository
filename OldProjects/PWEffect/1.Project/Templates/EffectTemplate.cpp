// PixelPlay.cpp : Implementation of CNewEffect
#include "stdafx.h"


/////////////////////////////////////////////////////////////////////////////
// CNewEffect


//
//  --------------- CNewEffect ----------------
//
HRESULT CNewEffect::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // 
    
    return S_OK;
}

HRESULT CNewEffect::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    //
    return S_OK;
}

// On start to play
HRESULT CNewEffect::OnStart()
{
    return S_OK;
}


// On duration changed.
HRESULT CNewEffect::OnDurationChanged(FLOAT fNewDur)
{
    return S_OK;
}


HRESULT CNewEffect::OnTerminate()
{

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


// 
HRESULT CNewEffect::OnImplEffect(IN DWORD* pInputBuf,
                                    IN DWORD* pOutputBuf,
                                    IN INT iWidth,
                                    IN INT iHeight)
{
    
    return E_NOTIMPL;
}


//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CNewEffect::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CNewEffect::UpdateControlValue()
{
    // 
    return S_OK;
}

 
//////////////////////////////////////////////////////////////////////////
// Properties


