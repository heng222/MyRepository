// Flash.cpp : Implementation of CFlash
#include "stdafx.h"
#include "Flash.h"
#include "RandMgr.h"

/////////////////////////////////////////////////////////////////////////////
// CFlash


//
//   --------------- CFlash ----------------
//
HRESULT CFlash::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // This is the Base effect control
    // used to perform the effect.
    m_iFashStyle = EBlank;
    m_clrText = RGB(255,255,255);
    m_dwOnTime = 500;
    m_dwOffTime = 200;
    m_fWEDistance = 20.0f;
    m_clrBackground = RGB(0,0,0);

    // 
    m_dwPeriod = 5000;
    m_bFlashFlag = TRUE;

    // 
    return S_OK;
}

//
HRESULT CFlash::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    
    // add your code after here
    
    // generate a random color.
    if (m_iFashStyle==ERandom)
    {
        OnFlashStateChanged();
        m_bFlashFlag = TRUE; // must be set TRUE
    }

    // Get the duration
    float fDuration = _basex::GetDuration();
    m_dwPeriod = fDuration*1000; // Convert to millisecond
    
//     TCHAR strTitle[100] = {0};
//     swprintf(strTitle,_T("%f"),m_Duration);
//     ::MessageBox(NULL,strTitle,_T("Duration Value"),MB_ICONINFORMATION);

    
    // 
    return S_OK;
}

// On start to play
HRESULT CFlash::OnStart()
{
    float fDuration;
    _basex::get_Duration(&fDuration);
    m_dwPeriod = fDuration*1000; // convert to millisecond
    return S_OK;
}


// On duration changed.
HRESULT CFlash::OnDurationChanged(FLOAT fNewDur)
{
    m_dwPeriod = fNewDur*1000; // convert to millisecond
    return S_OK;
}
// 
HRESULT CFlash::OnTerminate()
{
    // add your code before here.

    RTN_HR_IF_FAILED(_basex::OnTerminate());

    // 
    return S_OK;
}


HRESULT CFlash::OnImplEffect(IN DWORD* pInputBuf,
                             IN DWORD* pOutputBuf,
                             IN INT iWidth,   IN INT iHeight)
{

    // If it's on-time, then ...
    float fProgress = 0;
    _basex::get_Progress(&fProgress);

    if ( IsFlashOn(fProgress) )
    {
        if (!m_bFlashFlag)
        {
            m_bFlashFlag = TRUE;
            OnFlashStateChanged();
        }
    }
    else // it's off-time.
    {
        if (m_bFlashFlag)
        {
            m_bFlashFlag = FALSE;
            OnFlashStateChanged();
        }
    }

    // Convert the surface data to corresponding color.
    _thisx::ConvertData((DXSAMPLE*)pInputBuf,
        (DXSAMPLE*)pOutputBuf,iWidth,iHeight,m_bFlashFlag);

    //
    return S_OK;
}



//////////////////////////////////////////////////////////////////////////
// Private methods

void CFlash::ConvertData(const DXSAMPLE* pInput,
                         DXSAMPLE* pOutput,
                         INT iWidth, 
                         INT iHeight, 
                         BOOL bOnTime) const
{

    INT i=0,j=0;
    
    for ( i=0; i<iHeight; i++)
    {
        for ( j=0; j<iWidth; j++)
        {
            if (bOnTime)
            {
                Conver2FlashOn(pInput,pOutput);
            }
            else
            {
                Convert2FlashOff(pInput,pOutput);
            }
            //
            pInput ++;
            pOutput ++;
        }
    }
}

void CFlash::Conver2FlashOn(const DXSAMPLE* pClrOrg,DXSAMPLE* pClrDest) const
{
    
    // The color is NOT equal the back color, then...
    if (m_iFashStyle==EBlank)
    {
        *pClrDest = *pClrOrg;
    }
    else if (m_iFashStyle==EInvert)
    {
        *pClrDest = *pClrOrg;
    } 
    else if (m_iFashStyle==ERandom)
    {
        COLORREF clrRef = _basex::DX2COLORREF(*pClrOrg);
        
        //if ( clrRef == m_clrBackground)
        if ( _basex::WEDistanceOfColors(m_clrBackground,clrRef) <= m_fWEDistance )
        {
            *pClrDest = *pClrOrg;
        }
        //else if(clrRef == m_clrText)
        else if(_basex::WEDistanceOfColors(m_clrText,clrRef) <= m_fWEDistance )
        {
            *pClrDest = m_clrTextRdm;
        }
        else
        {
            *pClrDest = m_clrOtherRdm;
        }
    } 
    else
    {
        ASSERT(0);
    }
}

void CFlash::Convert2FlashOff(const DXSAMPLE* pClrOrg,DXSAMPLE* pClrDest) const
{
    DXSAMPLE clrOrg = *pClrOrg;
    COLORREF clrCurrent = _basex::DX2COLORREF(*pClrOrg);

    // The color is NOT equal the back color, then...
    if (m_iFashStyle==EBlank)
    {
        *pClrDest = _basex::COLORREF2DX(m_clrBackground);
    }
    else if (m_iFashStyle==EInvert)
    {
        if ( _basex::WEDistanceOfColors(m_clrBackground,clrCurrent)<=m_fWEDistance )
        {
            *pClrDest = clrOrg;
        }
        else
        {
            *pClrDest = ~clrOrg;
        }
    } 
    else if (m_iFashStyle==ERandom)
    {
        //if ( clrRef == m_clrBackground)
        if ( _basex::WEDistanceOfColors(m_clrBackground,clrCurrent) <= m_fWEDistance )
        {
            *pClrDest = clrOrg;
        }
        //else if(clrRef == m_clrText)
        else if(_basex::WEDistanceOfColors(m_clrText,clrCurrent) <= m_fWEDistance )
        {
            *pClrDest = m_clrTextRdm;
        }
        else
        {
            *pClrDest = m_clrOtherRdm;
        }
    } 
    else
    {
        ASSERT(0);
    }
        
}

BOOL CFlash::IsFlashOn(float fProgress) const
{
    DWORD dwExpired = (DWORD)(m_dwPeriod*fProgress);   
    
    //ATLTRACE("Expired = %ld\n",dwExpired);

    if (dwExpired%(m_dwOffTime+m_dwOnTime)>m_dwOnTime)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }

}


void CFlash::OnFlashStateChanged()
{    
    if (m_iFashStyle==ERandom)
    {
        INT iR,iG,iB;
        
        CRandMgr::InitRandSeed();

        // Create random text color
        CRandMgr::CreateRandomNum(iR,0,255);
        CRandMgr::CreateRandomNum(iG,0,255);
        CRandMgr::CreateRandomNum(iB,0,255);        
        m_clrTextRdm = _basex::MakeDXSAMPLE(iR,iG,iB);

        // Create random color for others
        CRandMgr::CreateRandomNum(iR,0,255);
        CRandMgr::CreateRandomNum(iG,0,255);
        CRandMgr::CreateRandomNum(iB,0,255);        
        m_clrOtherRdm = _basex::MakeDXSAMPLE(iR,iG,iB);

    }
}


//////////////////////////////////////////////////////////////////////////
// Properties



STDMETHODIMP CFlash::get_TextColor(OLE_COLOR *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_clrText;
	return S_OK;
}

STDMETHODIMP CFlash::put_TextColor(OLE_COLOR newVal)
{
    // TODO: Add your implementation code here    
    if (_basex::IsTransparent(newVal))
    {
        m_clrText = CLR_TRANSPARENT_AGENT;
    }
    else
    {
        m_clrText = (newVal&0x00FFFFFF);
        
        if (m_clrText==0)
        {
            m_clrText = _basex::GetBlackAgentClr();
        }
    }
	return S_OK;
}

STDMETHODIMP CFlash::get_FlashStyle(INT *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_iFashStyle;
	return S_OK;
}

STDMETHODIMP CFlash::put_FlashStyle(INT newVal)
{
	// TODO: Add your implementation code here
    m_iFashStyle = (TFlashStyle)newVal;
	return S_OK;
}

STDMETHODIMP CFlash::get_OnTime(DWORD *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_dwOnTime;
	return S_OK;
}

STDMETHODIMP CFlash::put_OnTime(DWORD newVal)
{
	// TODO: Add your implementation code here
    m_dwOnTime = newVal;
	return S_OK;
}

STDMETHODIMP CFlash::get_OffTime(DWORD *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_dwOffTime;
	return S_OK;
}

STDMETHODIMP CFlash::put_OffTime(DWORD newVal)
{
	// TODO: Add your implementation code here
    m_dwOffTime = newVal;
	return S_OK;
}

STDMETHODIMP CFlash::get_WED(FLOAT *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_fWEDistance;

	return S_OK;
}

STDMETHODIMP CFlash::put_WED(FLOAT newVal)
{
	// TODO: Add your implementation code here
    if (newVal<0 || newVal>300)
    {
        return E_FAIL;
    }

    m_fWEDistance = newVal;

	return S_OK;
}
