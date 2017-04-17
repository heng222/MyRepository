

#include "stdafx.h"
#include "DTOTransBase.h"

//
//  --------------- CDTOColorAdjustEffect ----------------
//
HRESULT CDTOTransBase::FinalConstruct()
{
	RTN_HR_IF_FAILED(CDTOBase::FinalConstruct());

    // Base class 
    m_ulMaxInputs       = 2;
	m_ulNumInRequired   = 2;

    // self variables
    m_bDisplayOn = TRUE;

    //
    m_hdcInput1 = ::CreateCompatibleDC(NULL);
    m_hdcInput2 = ::CreateCompatibleDC(NULL);
    m_hdcOutput = ::CreateCompatibleDC(NULL);
    m_hBmpOutput = NULL;
	
	return S_OK;
}


HRESULT CDTOTransBase::OnInitialize()
{
    INT iWidth = _basex::GetOutputWidth();
    INT iHeight = _basex::GetOutputHeight();
    if (m_hBmpOutput==NULL)
    {
        m_hBmpOutput = ::CreateCompatibleBitmap(
            CAutoDeskDC(),iWidth,iHeight);
    }

    RTN_HR_IF_BADPTR(m_hBmpOutput);

    ::SelectObject(m_hdcOutput,m_hBmpOutput);

    //
    this->ResetControlValue();

    // 
    return S_OK;
}

// On start to play
HRESULT CDTOTransBase::OnStart()
{
    this->ResetControlValue();
    return S_OK;
}


// On duration changed.
HRESULT CDTOTransBase::OnDurationChanged(FLOAT fNewDur)
{
    this->ResetControlValue();
    return S_OK;
}

HRESULT CDTOTransBase::OnTerminate()
{
    if (m_hdcInput1)
    {
        ::DeleteDC(m_hdcInput1);
        m_hdcInput1 = NULL;
    }
    
    if (m_hdcInput2)
    {
        ::DeleteDC(m_hdcInput2);
        m_hdcInput2 = NULL;
    }

    if (m_hdcOutput)
    {
        ::DeleteDC(m_hdcOutput);
        m_hdcOutput = NULL;
    }

    if (m_hBmpOutput)
    {
        ::DeleteObject(m_hBmpOutput);
        m_hBmpOutput = NULL;
    }

    //
    return S_OK;
}


HRESULT CDTOTransBase::DrawLiveBitmap(IN HDC hdcHide,
                       IN HDC hdcShow,
                       IN HDC hdcOutput)
{
    return E_NOTIMPL;
}

HRESULT CDTOTransBase::OnTransform(IN DWORD* pInputBuf,
                            IN DWORD* pInput2Buf,
                            IN DWORD* pOutputBuf)
{
    HRESULT hRc = this->UpdateControlValue();
    if (!SUCCEEDED(hRc))
    {
        return E_FAIL;
    }
    
    // 
    INT iWidth = Width();
    INT iHeight = Height();
    
    // Create a bitmap of input surface.    
    HBITMAP hBmpInput1 = _basex::CreateSufaceBitmap(
        iWidth,iHeight,pInputBuf);
    
    HBITMAP hBmpInput2 = _basex::CreateSufaceBitmap(
        iWidth,iHeight,pInput2Buf);
    
    // Select it to the DC.
    HDC hDcInput1 = RetrieveDC(EWBInputBuffer);
    HBITMAP hOldBmp1 = (HBITMAP)::SelectObject(hDcInput1,hBmpInput1);
    
    HDC hDcInput2 = RetrieveDC(EWBInput2Buffer);
    HBITMAP hOldBmp2 = (HBITMAP)::SelectObject(hDcInput2,hBmpInput2);
    
    //
    HDC hdcOutput = RetrieveDC(EWBOutputBuffer);
    HBITMAP hbmpOutput = RetrieveOutputBitmap();

    if (m_bDisplayOn)
    {
        // Input1 -> OutputDC
        ::BitBlt(hdcOutput,0,0,iWidth,iHeight,hDcInput1,0,0,SRCCOPY);

        // Draw live bitmap
        hRc = this->DrawLiveBitmap(hDcInput1,hDcInput2,hdcOutput);
    }
    else
    {
        // Input2 -> OutputDC
        ::BitBlt(hdcOutput,0,0,iWidth,iHeight,hDcInput2,0,0,SRCCOPY);
        
        // Draw live bitmap
        hRc = this->DrawLiveBitmap(hDcInput2,hDcInput1,hdcOutput);
    }
    
    // the DIB info we used to get title pixel-mapping.
    BITMAPINFO bmi;
    _basex::GetSurfaceBmpInfo(bmi);
    
    
    // get DIB's bits.
    if (SUCCEEDED(hRc))
    {
        LONG lLines = ::GetDIBits( hdcOutput, hbmpOutput, 0, iHeight, 
            (PVOID)pOutputBuf, 
            (BITMAPINFO *)&bmi, 
            DIB_RGB_COLORS);

        if (lLines!=iHeight)
        {
            hRc = E_FAIL;
        }
    }
    
    // release resource
    ::SelectObject(hDcInput1,hOldBmp1);
    ::SelectObject(hDcInput2,hOldBmp2);
    ::DeleteObject(hBmpInput1);
    ::DeleteObject(hBmpInput2);
    
    //
    return hRc;
}


BOOL CDTOTransBase::IsTransition()
{
    return TRUE;
}


//////////////////////////////////////////////////////////////////////////

INT CDTOTransBase::Width() const
{
    INT iWidth = _basex::GetInputWidth();
    ASSERT(iWidth==_basex::GetInput2Width());
    ASSERT(iWidth==_basex::GetOutputWidth());
    
    return iWidth;
}

INT CDTOTransBase::Height() const
{
    INT iHeight = _basex::GetInputHeight();
    ASSERT(iHeight==_basex::GetInput2Height());
    ASSERT(iHeight==_basex::GetOutputHeight());
    
    return iHeight;
}


HRESULT CDTOTransBase::GetBitmapInfo(BITMAPINFO& bmi) const
{
    // DIB info we used to create title pixel-mapping.
    // The system default color policy is: 
    // Initial Whole Black, while output area White-background and Black-text.
    ZeroMemory(&bmi,sizeof(bmi));
    bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bmi.bmiHeader.biWidth = Width();
    bmi.bmiHeader.biHeight = Height();
    bmi.bmiHeader.biPlanes = 1;
    bmi.bmiHeader.biBitCount = GetBitCount();
    bmi.bmiHeader.biCompression = BI_RGB;
    
    // 
    return S_OK;
}

HDC CDTOTransBase::RetrieveDC(TBufferType iType) const
{
    if (iType==EWBInputBuffer)
    {
        return m_hdcInput1;
    }
    else if (iType==EWBInput2Buffer)
    {
        return m_hdcInput2;
    } 
    else if (iType==EWBOutputBuffer)
    {
        return m_hdcOutput;
    }
    else
    {
        ASSERT(0);
        return NULL;
    }
}

HBITMAP CDTOTransBase::RetrieveOutputBitmap() const
{
    return m_hBmpOutput;
}