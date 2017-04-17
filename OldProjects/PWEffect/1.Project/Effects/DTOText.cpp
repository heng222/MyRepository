// DTOText.cpp : Implementation of CDTOText
#include "stdafx.h"
#include "DTOText.h"

/////////////////////////////////////////////////////////////////////////////
// CDTOText


//
//   --------------- CDTOText ----------------
//
HRESULT CDTOText::FinalConstruct()
{
	RTN_HR_IF_FAILED(_basex::FinalConstruct());
	
	// This is the Base effect control
	// used to perform the effect.
    InitLogFont();
    m_hFont = NULL;
    
    m_iEType = EStatic;
    m_clrText = RGB(255,255,255); // default text color
    m_strTitle = L"Please set title.";
    
    // 
    m_iScrollStride = 15;
    m_ptStart.x = m_ptStart.y = 0;
    m_fBounceIndex = 2;
    m_bBounceState = FALSE;
	m_iBounceHeight = 0;

	
	// 
	return S_OK;
}

//
HRESULT CDTOText::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    
    // add your code after here
    
    // Create DC.
    InitializeDC();
    
    // calculate the size of title under the current DC.
    CalculateTitleSize();  

    // 
    return S_OK;
}

HRESULT CDTOText::OnStart()
{
    // initialize parameters for bouncing.
    InitBounceParameter();

    return S_OK;
}

// 
HRESULT CDTOText::OnTerminate()
{
    _basex::ReleaseMemDC();

    // 
    if (m_hFont)
    {
        ::DeleteObject(m_hFont);
        m_hFont = NULL;
    }
    
    
    // add your code before here.
    
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    // 
    return S_OK;
}

/******************************************************************************
 * Description: Default Execute() operation is to simply copy buffer.
 * and apply dynamic color adjustment properties specified in the XML file.
 * For 3D effects and transitions, this method is overridden by CMM3DSpecialEffect.
 *
 * Returns: 
 *   HRESULT
 ******************************************************************************/
HRESULT CDTOText::OnImplEffect(IN DWORD* pInputBuf, 
                               IN DWORD *pOutputBuf,
                               IN INT iWidth,
                               IN INT iHeight)  
{
	
    // Create a bitmap of input surface. 
    HBITMAP hInputBitmap = _basex::CreateSufaceBitmap(
        iWidth,iHeight,pInputBuf);
    
    // Select it to the DC.
    HDC hMemDC = _basex::GetMemDC();
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,hInputBitmap);

	// Draw Title
	DrawTitle(hMemDC);
	
    //
    // the DIB info we used to get title pixel-mapping.
    BITMAPINFO bmi;
    _basex::GetSurfaceBmpInfo(bmi);
        
    // get DIB's bits.
    LONG lLines = ::GetDIBits( hMemDC, hInputBitmap, 0, iHeight, 
		(PVOID)pOutputBuf, 
		(BITMAPINFO *)&bmi, 
		DIB_RGB_COLORS);
    
    // 
    ::SelectObject(hMemDC,hOldBmp);
    ::DeleteObject(hInputBitmap);
    _basex::ReleaseMemDC();

    //
    return S_OK;
}

// 
HRESULT CDTOText::DrawTitle(IN HDC hDC)
{
    INT iHeight = _basex::Height();
    
    // Switch to handle
    if (m_iEType==ESystemTime)
    {
        TCHAR pTemp[100] = {0};
        // Update the current system time
        SYSTEMTIME    systemTime, localTime;
        GetSystemTime(&systemTime);   // This is Coordinated Universal Time (UTC)
        SystemTimeToTzSpecificLocalTime(NULL, &systemTime, &localTime);
        swprintf(pTemp, L"%4d-%02d-%02d %02d:%02d:%02d", localTime.wYear, localTime.wMonth, 
            localTime.wDay, localTime.wHour, localTime.wMinute, localTime.wSecond);
        m_strTitle = pTemp;

        // 
        CalculateTitleSize();
    }
    
    // calculate the position where the DC output the title.
    CalcStartPos();
    

    // Draw the text.
    ::TextOut(hDC,m_ptStart.x,m_ptStart.y,m_strTitle,m_strTitle.Length());
    
    
    return S_OK;
}


// 
HRESULT	 CDTOText::InitLogFont()
{
    // LogFont
    memset(&(m_logFont), 0, sizeof(m_logFont));
    m_logFont.lfHeight = 20;
    m_logFont.lfWidth = 0;
    m_logFont.lfEscapement = 0;
    m_logFont.lfOrientation = 0;
    m_logFont.lfWeight = FW_NORMAL;
    m_logFont.lfItalic = FALSE;
    m_logFont.lfUnderline = FALSE;
    m_logFont.lfStrikeOut = 0;
    m_logFont.lfCharSet = DEFAULT_CHARSET;
    m_logFont.lfOutPrecision = OUT_DEFAULT_PRECIS;
    m_logFont.lfClipPrecision = CLIP_DEFAULT_PRECIS ;
    m_logFont.lfQuality = DRAFT_QUALITY/*NONANTIALIASED_QUALITY*/;
    m_logFont.lfPitchAndFamily = DEFAULT_PITCH | FF_DONTCARE;
    wcscpy(m_logFont.lfFaceName,_T("Arial"));
    
    return S_OK;
}

// 
HRESULT	 CDTOText::InitializeDC()
{
    m_hdcText = _basex::GetMemDC();

	// set background mode, transparent or Opaque
	::SetBkMode(m_hdcText,TRANSPARENT);

	// Set text color
	::SetTextColor(m_hdcText,m_clrText);

	// select the font to it.
	CreateFontAndSelect();

    _basex::ReleaseMemDC();

	//
	return S_OK;
}

// create a new font and select it to DC.
HRESULT CDTOText::CreateFontAndSelect()
{
	RTN_HR_IF_BADPTR(m_hdcText);

    // Delete the old font
    if (m_hFont==NULL)
    {
        // create a new font
        m_hFont = ::CreateFontIndirect(&m_logFont);
        RTN_HR_IF_BADNEW(m_hFont);
    }	
	
    // select it to current DC.
    if (m_hFont)
    {
        ::SelectObject(m_hdcText,m_hFont);
    }
    else
    {
        return E_FAIL;
    }
	
    return S_OK;
}

HRESULT CDTOText::CalculateTitleSize()
{
	RTN_HR_IF_BADNEW(m_hdcText);
    ::GetTextExtentPoint32(m_hdcText, m_strTitle, 
					m_strTitle.Length(), &m_sizeTitle);

	return S_OK;
}

HRESULT CDTOText::InitBounceParameter()
{
	// Get width and height of surfaces
	int nWidth = Width();
    int nHeight = Height();

	// 
	m_ptStart.x = m_ptStart.y = 0;
    m_fBounceIndex = 2;
    m_iBottomBorder = nHeight - m_sizeTitle.cy;
    m_iBounceHeight = m_iBottomBorder;

	// 
	//CalculateScrollStride();
	return S_OK;
}

// Calculate the stride according to the title duration
HRESULT CDTOText::CalculateScrollStride(void)
{
	// Get width and height of surfaces
	int nWidth = GetInputWidth();
    int nHeight = GetInputHeight();

	double scrollingLength = nHeight-m_sizeTitle.cy;
	double fHeight = scrollingLength/m_fBounceIndex;
	for (; fHeight>1E-6; fHeight/=m_fBounceIndex)
	{
		scrollingLength += 2*fHeight;
	}

	//
	float fDuration = 0;
	//m_pDTOBase->get_Duration(&fDuration);
	double fStride = scrollingLength / fDuration*10;
	//m_iScrollStride = INT(fStride+1);


	return S_OK;
}

void CDTOText::CalcStartPos(void)
{
	// 计算X值（水平居中）
	int nWidth = Width();
	m_ptStart.x = (nWidth-m_sizeTitle.cx)/2;
	

    // 计算Y值
	if (!m_bBounceState) // 下落
	{
		m_ptStart.y += m_iScrollStride;
		if (m_ptStart.y>m_iBottomBorder)
		{
			m_ptStart.y = m_iBottomBorder;
			m_iBounceHeight = int(m_iBounceHeight/m_fBounceIndex);
			m_bBounceState = TRUE;
		}
	}
	else // 弹起
	{
		m_ptStart.y -= m_iScrollStride;
		if (m_ptStart.y<m_iBottomBorder-m_iBounceHeight)
		{
			m_ptStart.y = m_iBottomBorder-m_iBounceHeight;
			m_bBounceState = FALSE;
		}
	}
	
}
 

void CDTOText::SetFontLogicHeight(WORD wlogicHeight)
{
    // here, that is logic unit, we needn't transform.
    m_logFont.lfHeight = wlogicHeight;
    
}

int CDTOText::GetFontLogicHeight(BOOL bIcdInternalLeading) const
{
    int iHeight = 0;
    
    if (m_logFont.lfHeight!=0)
    {
        TEXTMETRIC tm;
        ::GetTextMetrics(m_hdcText,&tm);
        if (bIcdInternalLeading)
        {
            iHeight = tm.tmHeight;
        }
        else
        {
            iHeight = tm.tmHeight-tm.tmInternalLeading;
        }
    }
    
    return iHeight;
}

void CDTOText::SetFontPointHeight(IN WORD wHeight)
{
    // For the MM_TEXT mapping mode, use the following formula 
    // to specify a logic height for a font with a specified point size.
    LONG lLHeight = -(LONG)(wHeight*::GetDeviceCaps(m_hdcText,LOGPIXELSY)/72.0);
    //LONG lLHeight = -MulDiv(iFointHeight,::GetDeviceCaps(m_hDC,LOGPIXELSY), 72.0);
    m_logFont.lfHeight = lLHeight;
    
}

int	CDTOText::GetFontPointHeight() const
{
    int iPointHeight = (int)(GetFontLogicHeight(FALSE)*72.0/::GetDeviceCaps(m_hdcText,LOGPIXELSY));// 72:Inch per Point
    
    return iPointHeight;
    
}


//////////////////////////////////////////////////////////////////////////
// Properties
STDMETHODIMP CDTOText::get_Title(BSTR* pstrTitle)
{
	RTN_HR_IF_BADPTR(pstrTitle);
	*pstrTitle = m_strTitle.Copy();
	return S_OK;
}

STDMETHODIMP CDTOText::put_Title(BSTR strTitle)
{
	m_strTitle = strTitle;
	return S_OK;
}

STDMETHODIMP CDTOText::get_TitleType(INT *pVal)
{
	RTN_HR_IF_BADPTR(pVal);
	*pVal = m_iEType;

	return S_OK;
}

STDMETHODIMP CDTOText::put_TitleType(INT newVal)
{
	m_iEType = (TTextType)newVal;
	return S_OK;
}

STDMETHODIMP CDTOText::get_TextColor(OLE_COLOR *pVal)
{
	RTN_HR_IF_BADPTR(pVal);
	*pVal = m_clrText;

	return S_OK;
}

STDMETHODIMP CDTOText::put_TextColor(OLE_COLOR newVal)
{
	m_clrText = newVal;
	return S_OK;
}


STDMETHODIMP CDTOText::get_FontName(BSTR *pVal)
{
	*pVal = CComBSTR(m_logFont.lfFaceName).Copy();
	return S_OK;
}

STDMETHODIMP CDTOText::put_FontName(BSTR newVal)
{
    if(wcslen(newVal)>sizeof(m_logFont.lfFaceName)-1)
    {
        return S_FALSE;
    }
    else
    { 
        wcscpy(m_logFont.lfFaceName,newVal);
        return S_OK;
    }
}

STDMETHODIMP CDTOText::get_FontHeight(WORD *pVal)
{
	*pVal = GetFontLogicHeight(TRUE);
	return S_OK;
}

STDMETHODIMP CDTOText::put_FontHeight(WORD newVal)
{
	SetFontLogicHeight(newVal);
	return S_OK;
}
