// Venetian.cpp : Implementation of CVenetian
#include "stdafx.h"
#include "Venetian.h"


/////////////////////////////////////////////////////////////////////////////
// CVenetian

#define     MAXWIDTH     64
#define     MINWIDTH     4
//
//  --------------- CVenetian ----------------
//
HRESULT CVenetian::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    //
    m_bDisplayOn = TRUE;
    m_iDirection = ED_LEFT;
    m_iBlindWidth = 4;
    

    return S_OK;
}

HRESULT CVenetian::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here

        
    // output width and height
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();
    
    // generate slots
    TMRect rectExtent(0,0,nWidth,nHeight);        
    _thisx::Initialize(rectExtent);
    
    //
    return S_OK;
}

HRESULT CVenetian::OnTerminate()
{
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CVenetian::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CVenetian::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    m_VenetianMgr.UpdateProgress(fProgress);

    // 
    return S_OK;
}

HRESULT CVenetian::Initialize(TMRect rectExtent)
{
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();

    // 
    if (m_iDirection==ED_LEFT) // 0
    {
        TMPoint ptStart(nWidth,0);
        TMPoint ptEnd(0,0);
        TSegmentVector seg(ptStart,ptEnd);
        m_VenetianMgr.Initialize(seg,m_iBlindWidth,rectExtent,
            &TSegmentVector(TMPoint(nWidth,0),TMPoint(nWidth,nHeight)));
        m_VenetianMgr.AddVetex(TMPoint(0,nHeight));
        m_VenetianMgr.AddVetex(TMPoint(0,0));
    }
    else if (m_iDirection==ED_RIGHT) // 1
    {
        TMPoint ptStart(0,0);
        TMPoint ptEnd(nWidth,0);
        TSegmentVector seg(ptStart,ptEnd);
        m_VenetianMgr.Initialize(seg,m_iBlindWidth,rectExtent,
            &TSegmentVector(TMPoint(0,0),TMPoint(0,nHeight)));
        m_VenetianMgr.AddVetex(TMPoint(nWidth,nHeight));
        m_VenetianMgr.AddVetex(TMPoint(nWidth,0));
    }
    else if (m_iDirection==ED_UP) // 2
    {
        TMPoint ptStart(0,nHeight);
        TMPoint ptEnd(0,0);
        TSegmentVector seg(ptStart,ptEnd);
        m_VenetianMgr.Initialize(seg,m_iBlindWidth,rectExtent,
            &TSegmentVector(TMPoint(0,nHeight),TMPoint(nWidth,nHeight)));
        m_VenetianMgr.AddVetex(TMPoint(0,0));
        m_VenetianMgr.AddVetex(TMPoint(nWidth,0));
    }
    else if (m_iDirection==ED_DOWN) // 3
    {
        TMPoint ptStart(0,0);
        TMPoint ptEnd(0,nHeight);
        TSegmentVector seg(ptStart,ptEnd);
        m_VenetianMgr.Initialize(seg,m_iBlindWidth,rectExtent,
            &TSegmentVector(TMPoint(0,0),TMPoint(nWidth,0)));
        m_VenetianMgr.AddVetex(TMPoint(nWidth,nHeight));
        m_VenetianMgr.AddVetex(TMPoint(0,nHeight));
    }
    else if (m_iDirection==ED_UPPERLEFT) // 6
    {
        TSegmentVector seg(TMPoint(nWidth,nHeight),TMPoint(0,0));
        m_VenetianMgr.Initialize(seg,m_iBlindWidth,rectExtent);
        m_VenetianMgr.AddVetex(TMPoint(0,nHeight));
        m_VenetianMgr.AddVetex(TMPoint(nWidth,0));
    }
    else if (m_iDirection==ED_UPPERRIGHT) // 7
    {
        TSegmentVector seg(TMPoint(0,nHeight),TMPoint(nWidth,0));
        m_VenetianMgr.Initialize(seg,m_iBlindWidth,rectExtent);
        m_VenetianMgr.AddVetex(TMPoint(0,0));
        m_VenetianMgr.AddVetex(TMPoint(nWidth,nHeight));
    }
    else if (m_iDirection==ED_LOWERLEFT) // 8
    {
        TSegmentVector seg(TMPoint(nWidth,0),TMPoint(0,nHeight));
        m_VenetianMgr.Initialize(seg,m_iBlindWidth,rectExtent);
        m_VenetianMgr.AddVetex(TMPoint(0,0));
        m_VenetianMgr.AddVetex(TMPoint(nWidth,nHeight));
    }
    else if (m_iDirection==ED_LOWERRIGHT) // 9
    {
        TSegmentVector seg(TMPoint(0,0),TMPoint(nWidth,nHeight));
        m_VenetianMgr.Initialize(seg,m_iBlindWidth,rectExtent);
        m_VenetianMgr.AddVetex(TMPoint(0,nHeight));
        m_VenetianMgr.AddVetex(TMPoint(nWidth,0));
    }

    //
    return S_OK;
}

HRESULT CVenetian::DrawLiveBitmap(IN HDC hdcHide,
                                IN HDC hdcShow,
                                IN HDC hdcOutput)
{

    INT iWidth = _basex::Width();
    INT iHeight = _basex::Height();

    //
    std::vector<HRGN> arRgnPt;
    BOOL bFlag = m_VenetianMgr.GetClipRgn(arRgnPt);    

    INT iRc = 0;
    
    if (!m_bDisplayOn)
    {        
        // Input1 -> OutputDC
        ::BitBlt(hdcOutput,0,0,iWidth,iHeight,hdcShow,0,0,SRCCOPY);
        
        for (INT n=0; n<arRgnPt.size(); n++)
        {
            iRc = ::SelectClipRgn(hdcOutput,arRgnPt[n]);            
            
            // Transfer (draw) the bitmap into the clipped rectangle. 
            BOOL bRc = ::BitBlt(hdcOutput, 
                0, 0, 
                iWidth, 
                iHeight,
                hdcHide, 
                0, 0, 
                SRCCOPY);  
            
            ::DeleteObject(arRgnPt[n]);
        }
    }
    else
    {
        for (INT n=0; n<arRgnPt.size(); n++)
        {
            iRc = ::SelectClipRgn(hdcOutput,arRgnPt[n]);
            
            // Transfer (draw) the bitmap into the clipped rectangle. 
            BOOL bRc = ::BitBlt(hdcOutput, 
                0, 0, 
                iWidth, 
                iHeight,
                hdcShow, 
                0, 0, 
                SRCCOPY);  
            
            ::DeleteObject(arRgnPt[n]);
        }
    }    

#ifdef _DEBUG
    if (iRc==NULLREGION)
    {
        ATLTRACE(_T("NULLREGION Region is empty. \n"));
    }
    else if (iRc==SIMPLEREGION)
    {
        ATLTRACE(_T("SIMPLEREGION Region is a single rectangle. \n"));
    }
    else if (iRc==COMPLEXREGION)
    {
        ATLTRACE(_T("COMPLEXREGION Region is more than one rectangle. \n"));
    }
    else if (iRc==ERROR)
    {
        ATLTRACE(_T("ERROR An error occurred. (The previous clipping region is unaffected.) \n"));
    }
#endif

    // remove the device-context's clipping region
    ::SelectClipRgn(hdcOutput,NULL);

    // 
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CVenetian::get_State(BOOL *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
    return S_OK;
}

STDMETHODIMP CVenetian::put_State(BOOL newVal)
{
    // TODO: Add your implementation code here
    m_bDisplayOn = newVal;
    return S_OK;
}

STDMETHODIMP CVenetian::get_Direction(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iDirection;
    return S_OK;
}

STDMETHODIMP CVenetian::put_Direction(INT newVal)
{
    // TODO: Add your implementation code here    
    m_iDirection = (TSingleDir)newVal;
    
    return S_OK;
}

STDMETHODIMP CVenetian::get_BlindWidth(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iBlindWidth;

	return S_OK;
}

STDMETHODIMP CVenetian::put_BlindWidth(INT newVal)
{
	// TODO: Add your implementation code here
    m_iBlindWidth = newVal;
    if (m_iBlindWidth>MAXWIDTH || m_iBlindWidth<MINWIDTH)
    {
        m_iBlindWidth = MINWIDTH;
    }
	return S_OK;
}
