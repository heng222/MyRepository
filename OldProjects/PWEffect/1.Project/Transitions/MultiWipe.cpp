// MultiWipe.cpp : Implementation of CMultiWipe
#include "stdafx.h"
#include "MultiWipe.h"

/////////////////////////////////////////////////////////////////////////////
// CMultiWipe

#define     MAXGRIDNUM     50
//
//  --------------- CMultiWipe ----------------
//
HRESULT CMultiWipe::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    //
    m_iHWNum = 2;
    m_iVWNum = 2;
    m_bDisplayOn = TRUE;
    

    return S_OK;
}

HRESULT CMultiWipe::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here

    // 
    if (m_iHWNum>MAXGRIDNUM 
        || m_iHWNum<=0 
        || m_iVWNum<=0
        || m_iVWNum>MAXGRIDNUM)
    {
        return E_FAIL;
    }
    
    // output width and height
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();
    
    // generate slots
    TMRect rectExtent(0,0,nWidth,nHeight);        
    _thisx::Initialize(rectExtent);
    
    //
    return S_OK;
}

HRESULT CMultiWipe::OnTerminate()
{
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CMultiWipe::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CMultiWipe::UpdateControlValue()
{
    // 
    return S_OK;
}

HRESULT CMultiWipe::Initialize(TMRect rectExtent)
{
    m_arMultiWipe.resize(0);

    // Initialize mosaic
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();

    // Grid's width and height.
    m_iGridWidth = nWidth/m_iHWNum;
    m_iGridHeight = nHeight/m_iVWNum;
        
    // numbers of grid on horizontal.
    INT iNumPerRow = m_iHWNum;
    if (nWidth%m_iHWNum!=0)
    {
        iNumPerRow ++;
    } 
    
    // numbers of grid on vertical.
    INT iNumPerCol = m_iVWNum;
    if (nHeight%m_iVWNum!=0)
    {
        iNumPerCol ++;
    } 

    // Create grids...
    TMRect rGridSeed(0,0,m_iGridWidth,m_iGridHeight);
    for (INT i=0; i<iNumPerCol; i++)
    {
        // grid seed on every row.
        TMRect rMscRowSeed = rGridSeed;
        rMscRowSeed.MoveTop(i*m_iGridHeight);
        
        // create row grid
        for (INT j=0; j<iNumPerRow; j++)
        {
            TMRect rOriginal = rMscRowSeed;
            rOriginal.MoveRight( j * m_iGridWidth );
                        
            if (m_bDisplayOn)
            {
                TMPoint ptCenter = rOriginal.Center();
                TMRect rDot(ptCenter,ptCenter);
                m_arMultiWipe.push_back(rDot);
            }
            else
            {
                m_arMultiWipe.push_back(rOriginal);
            }            
        } 
    }
    
    //
    return S_OK;
}

HRESULT CMultiWipe::DrawLiveBitmap(IN HDC hInDC1,
                                IN HDC hdcShow,
                                IN HDC hOutDC)
{
    FLOAT fProgress = _basex::GetProgress();
    
    // 
    RECT rDest;  
    TMSize sizeChange;
    sizeChange.iWidth = INT(m_iGridWidth*fProgress/2);
    sizeChange.iHeight = INT(m_iGridHeight*fProgress/2);

    INT iSize = m_arMultiWipe.size();
    for (INT i=0; i<iSize; i++)
    {        
        TMRect rTemp = m_arMultiWipe[i];
        if (m_bDisplayOn)
        {
            rTemp.Grow(sizeChange);
        }
        else
        {
            rTemp.Shrink(sizeChange);
        }
        
        // 
        rDest = rTemp.ToRECT();
        
        ::BitBlt(hOutDC, 
            rDest.left,
            rDest.top, 
            rDest.right-rDest.left,
            rDest.bottom-rDest.top, 
            hdcShow, 
            rDest.left, 
            rDest.top,
            SRCCOPY);
    }
    // 
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CMultiWipe::get_State(BOOL *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
    return S_OK;
}

STDMETHODIMP CMultiWipe::put_State(BOOL newVal)
{
    // TODO: Add your implementation code here
    m_bDisplayOn = newVal;
    return S_OK;
}


STDMETHODIMP CMultiWipe::get_HWNum(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iHWNum;
	return S_OK;
}

STDMETHODIMP CMultiWipe::put_HWNum(INT newVal)
{
	// TODO: Add your implementation code here
    m_iHWNum = newVal;
	return S_OK;
}

STDMETHODIMP CMultiWipe::get_VWNum(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iVWNum;
	return S_OK;
}

STDMETHODIMP CMultiWipe::put_VWNum(INT newVal)
{
	// TODO: Add your implementation code here
    m_iVWNum = newVal;
	return S_OK;
}
