

#include "stdafx.h"
#include "DTOEffectBase.h"

//
//  --------------- CDTOColorAdjustEffect ----------------
//
HRESULT CDTOEffectBase::FinalConstruct()
{
	RTN_HR_IF_FAILED(_basex::FinalConstruct());

    // base class members
    m_ulMaxInputs       = 1;
	m_ulNumInRequired   = 1;
	
	// create a memory DC.
    m_hMemDC = ::CreateCompatibleDC(NULL);

	// create a bitmap for memory dc and select it to the DC.
	m_hMemBitmap = ::CreateCompatibleBitmap(CAutoDeskDC(),1000,1000);
	RTN_UNEXPECTED_IF_BADPTR(m_hMemBitmap);
	::SelectObject(m_hMemDC,m_hMemBitmap);


    // self variables
    m_bMemDcLock = FALSE;
    m_lPitch = 0;
	
	return S_OK;
}

// 
BOOL CDTOEffectBase::IsTransition()
{
    return FALSE;
}

HRESULT CDTOEffectBase::OnInitialize()
{
    // Get the pitch of the surfaces.
    long lInputPitch = GetInputPitch();
    long lOutputPitch = GetOutputPitch();
    ASSERT(lOutputPitch==lInputPitch);
    
    // Get the pitch in multiples of 4.
	m_lPitch = ( ((long) lInputPitch + 3) / 4) *4; // 每行的字节数

    // 
    return S_OK;
}

// On start to play
HRESULT CDTOEffectBase::OnStart()
{
    return S_OK;
}


// On duration changed.
HRESULT CDTOEffectBase::OnDurationChanged(FLOAT fNewDur)
{
    return E_NOTIMPL;
}

HRESULT CDTOEffectBase::OnTerminate()
{
    if (m_hMemDC)
    {
        ::DeleteDC(m_hMemDC);
        m_hMemDC = NULL;
    }

	if (m_hMemBitmap)
	{
		::DeleteObject(m_hMemBitmap);
		m_hMemBitmap = NULL;
	}

	//
    return S_OK;
}

HRESULT CDTOEffectBase::OnTransform(IN DWORD* pInputBuf,
                                   IN DWORD* pInput2Buf,
                                   IN DWORD* pOutputBuf)
{
    ASSERT( pInputBuf!=NULL );
    ASSERT( pInput2Buf==NULL );
    ASSERT( pOutputBuf!=NULL );

	INT iWidth = Width();
	INT iHeight = Height();
    
    // 
	return OnImplEffect(pInputBuf,pOutputBuf,iWidth,iHeight);
}

// 
HRESULT CDTOEffectBase::OnImplEffect(IN DWORD* pInputBuf,
                                     IN DWORD* pOutputBuf,
                                     IN INT iWidth,
                                     IN INT iHeight)
{
    return E_NOTIMPL;
}


INT CDTOEffectBase::Width() const
{
    INT iWidth = _basex::GetInputWidth();
    ASSERT(iWidth==_basex::GetOutputWidth());

    return iWidth;
}

INT CDTOEffectBase::Height() const
{
    INT iHeight = _basex::GetInputHeight();
    ASSERT(iHeight==_basex::GetOutputHeight());

    return iHeight;
}



LONG CDTOEffectBase::GetBufferSize() const
{
    return (m_lPitch*Height());
}


HDC CDTOEffectBase::GetMemDC()
{
   if (m_bMemDcLock)
   {
       return NULL;
   }

   m_bMemDcLock = TRUE;
   
   return m_hMemDC;
}

void CDTOEffectBase::ReleaseMemDC()
{
    if (m_hMemDC && m_hMemBitmap)
    {
        ::SelectObject(m_hMemDC,m_hMemBitmap);
    }

    m_bMemDcLock = FALSE;
}