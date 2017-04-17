// Filter.cpp : Implementation of CFilter
#include "stdafx.h"
#include "RandMgr.h"
#include "Filter.h"
/////////////////////////////////////////////////////////////////////////////
// CFilter

#define     LENSPACING      3

//
//  --------------- CFilter ----------------
//
HRESULT CFilter::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // 
    m_iThickness = 10;
    m_iSpacing = 10;
    
    return S_OK;
}

HRESULT CFilter::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
        
    RTN_HR_IF_FAILED(InitFilter());
    
    //
    return S_OK;
}



HRESULT CFilter::OnTerminate()
{    
    // 
    INT nSize = m_Sticks.size();
    for (INT i=0; i<nSize; i++)
    {
        delete m_Sticks[i];
    }
    m_Sticks.resize(0);

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods
HRESULT CFilter::InitFilter()
{
    
    // Initialize mosaic
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();
    
    ASSERT(m_iThickness>0);
    ASSERT(m_iSpacing>=0);
       
    
    // The number of the stick.
    INT iNumStick;
    if (nHeight>m_iThickness)
    {
        iNumStick = nHeight / m_iThickness;
        if (nHeight%m_iThickness!=0)
        {
            iNumStick ++;
        }
    } 
    else
    {
        m_iThickness = nHeight;
        iNumStick = 1;
    }
   
    
    // create the original stick.
    TMRect rectOrg;
    if (m_bDisplayOn)
    {
        rectOrg = TMRect(0,nHeight,nWidth,nHeight-m_iThickness);
    }
    else
    {
        rectOrg = TMRect(0,0,nWidth,m_iThickness);
    }

    CTravelRect* pNewStick = NULL;


    for (INT i=0; i<iNumStick; i++)
    {
        // mosaic seed on every row.
        TMRect rectStick = rectOrg;
        if (m_bDisplayOn)
        {
            rectStick.MoveBottom(i*m_iThickness);
        }
        else
        {
            rectStick.MoveTop(i*m_iThickness);
        }

        // Extent
        TMRect rectExtent(0, 0, nWidth, nHeight );
        if (m_bDisplayOn)
        {
            rectExtent.iBr.iY -= i*m_iSpacing;
            rectExtent.iBr.iY -= i*m_iThickness;
        }
        else
        {
            rectExtent.iTl.iY += i*m_iSpacing;
            rectExtent.iTl.iY += i*m_iThickness;
        }
        

        // create a new TravelRect.
        pNewStick = new CTravelRect;
        pNewStick->Initialize(rectStick,
            rectExtent,
            FLOAT(PIRADIAN/2),
            m_bDisplayOn);
        
        // save
        m_Sticks.push_back(pNewStick);

    }
    
    //
    return S_OK;
}

HRESULT CFilter::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CFilter::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    INT iSize = m_Sticks.size();

    INT iLiveLen = 0;
    if (iSize>0)
    {
        if (m_bDisplayOn)
        {
            iLiveLen= m_Sticks[iSize-1]->GetMaxTravelLen()/2
                * fProgress;
        }
        else
        {
            iLiveLen= ( m_Sticks[0]->GetMaxTravelLen()/2 + (iSize-1)*m_iSpacing ) 
                * fProgress;
        }
    }
    
    for (INT i=0; i<iSize; i++)
    {
        CTravelRect* pTR = m_Sticks[i];
        
        INT iCurTravelLen = pTR->GetMaxTravelLen()/2;

        if (m_bDisplayOn)
        {            
            if (iCurTravelLen<iLiveLen)
            {
                pTR->Travel(iCurTravelLen);
            }
            else
            {
                pTR->Travel(iLiveLen);
            }
        }
        else
        {
            INT iCriticalLen = (iSize-1-i)*m_iSpacing;
            if ( iLiveLen>iCriticalLen )
            {
                pTR->Travel(iLiveLen-iCriticalLen);
            }
        }
    }
    // 
    return S_OK;
}

HRESULT  CFilter::DrawLiveBitmap(IN HDC hInDC1,
                                 IN HDC hdcShow,
                                 IN HDC hOutDC)
{
    
    // travel to draw
    RECT rDest,rSource;    
    INT iSize = m_Sticks.size();
    for (INT i=0; i<iSize; i++)
    {
        CTravelRect* pTR = m_Sticks[i];
        if (!pTR->HasTraveledOut())
        {
            pTR->GetIntersectRect(rDest);
            pTR->GetIntersectRectEx(rSource);
            ::BitBlt(hOutDC, 
                rDest.left,
                rDest.top, 
                rDest.right-rDest.left,
                rDest.bottom-rDest.top, 
                hdcShow, 
                rSource.left, 
                rSource.top, 
                SRCCOPY);
        }
    }
    //
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CFilter::get_Thickness(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iThickness;
	return S_OK;
}

STDMETHODIMP CFilter::put_Thickness(INT newVal)
{
	// TODO: Add your implementation code here
    if (newVal<=0)
    {
        return E_INVALIDARG;
    }

    m_iThickness = newVal;
	return S_OK;
}

STDMETHODIMP CFilter::get_Spacing(INT *pVal)
{
	// TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);

    *pVal = m_iSpacing;
	return S_OK;
}

STDMETHODIMP CFilter::put_Spacing(INT newVal)
{
    // TODO: Add your implementation code here
    if (newVal<=0)
    {
        return E_INVALIDARG;
    }
    m_iSpacing = newVal;
	return S_OK;
}

STDMETHODIMP CFilter::get_State(BOOL *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
    
	return S_OK;
}

STDMETHODIMP CFilter::put_State(BOOL newVal)
{
	// TODO: Add your implementation code here
    m_bDisplayOn = newVal;
	return S_OK;
}
