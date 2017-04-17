// SimpleTrans.cpp : Implementation of CSimpleTrans
#include "stdafx.h"
#include "SimpleTrans.h"

/////////////////////////////////////////////////////////////////////////////
// CSimpleTrans

//
//   --------------- CSimpleTrans ----------------
//
HRESULT CSimpleTrans::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // This is the Base effect control
    // used to perform the effect.

    
    // 
    return S_OK;
}

//
HRESULT CSimpleTrans::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    
    // add your code after here
    
    
    
    // 
    return S_OK;
}

// 
HRESULT CSimpleTrans::OnTerminate()
{
    
    
    // add your code before here.
    
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    // 
    return S_OK;
}


HRESULT CSimpleTrans::OnTransform(IN DWORD* pInputBuf,
                                  IN DWORD* pInput2Buf,
                                  IN DWORD* pOutputBuf)
{
    //
    return E_NOTIMPL;
}




//////////////////////////////////////////////////////////////////////////
// Private methods


//////////////////////////////////////////////////////////////////////////
// Properties


