// Radar.cpp : Implementation of CRadar
#include "stdafx.h"
#include "Radar.h"

/////////////////////////////////////////////////////////////////////////////
// CRadar

//
//  --------------- CRadar ----------------
//
HRESULT CRadar::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // Properties
    m_bDisplayOn = TRUE;
    m_iDirection = EClockwise;
    m_clrPointer = 0x0;
    m_iPointerWidth = 1;
    m_hrgnArea = NULL;
    m_hPen = NULL;

    //
    return S_OK;
}

HRESULT CRadar::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here

    // Create pen
    if (m_hPen==NULL)
    {
        m_hPen = ::CreatePen(PS_SOLID,
            m_iPointerWidth,
            m_clrPointer);
    }       
    
    // generate    
    m_arVertexes.resize(0);
    m_arEdges.resize(0);  
    _thisx::Initialize();

    //
    return S_OK;
}

HRESULT CRadar::OnTerminate()
{
    if (m_hrgnArea!=NULL)
    {
        ::DeleteObject(m_hrgnArea);
        m_hrgnArea = NULL;
    }

    if (m_hPen!=NULL)
    {
        ::DeleteObject(m_hPen);
        m_hPen = NULL;
    }

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods

HRESULT CRadar::ResetControlValue()
{
    // 
    return S_OK;
}

HRESULT CRadar::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();
    FLOAT fRadian = (FLOAT)(fProgress*2*PIRADIAN);

    // Rotate the pointer
    m_sgPointer = m_sgPtOriginal;
    if (m_iDirection==EClockwise)
    {
        m_sgPointer.Rotate(m_sgPointer.iStartPoint,-fRadian);
    }
    else
    {
        m_sgPointer.Rotate(m_sgPointer.iStartPoint,fRadian);
    }

    // Determine the Index value
    INT   iEdgeNo;       // 与雷达针相交边的编号(依次为0,1,2,3)
    INT iSize = m_arEdges.size();
    for (INT n=0; n<iSize; n++)
    {
        BOOL bFlag = m_sgPointer.CalcIntersection(m_arEdges[n],m_ptCross);
        if (bFlag)
        {            
            iEdgeNo = n;
            break;
        }
    }
    if (fRadian>PIRADIAN && iEdgeNo==0)
    {
        iEdgeNo = 4;
    }

    // Build points
    INT iTemp = 0;
    POINT ptTemp[10] = {0};
    ptTemp[iTemp++] = m_sgPointer.iStartPoint.TOPOINT();
    ptTemp[iTemp++].x = _basex::Width()/2;
    for (INT k=0; k<iEdgeNo; k++)
    {
        ptTemp[iTemp++] = m_arVertexes[k].TOPOINT();
    }
    ptTemp[iTemp++] = m_ptCross.TOPOINT();
    
    // create region
    if (m_hrgnArea!=NULL)
    {
        ::DeleteObject(m_hrgnArea);
    }
    m_hrgnArea = ::CreatePolygonRgn(ptTemp,iTemp,ALTERNATE);
    
    // 
    return S_OK;
}

HRESULT CRadar::Initialize()
{

    TSegmentVector s1(TMPoint(0,0),TMPoint(384,0));
    TSegmentVector s2(TMPoint(192,144),TMPoint(19,-199));
    BOOL bFlag = s1.IsIntersects(s2);

    //
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();

    // 

    // Build Radar's pointer.
    INT nTemp = max(nWidth,nHeight);
    m_sgPointer.iStartPoint = TMPoint(nWidth/2,nHeight/2);
    m_sgPointer.iEndPoint = TMPoint(nWidth/2,m_sgPointer.iStartPoint.iY-nTemp);
    m_sgPtOriginal = m_sgPointer;

    // vertexes
    if (m_iDirection==EClockwise)
    {
        m_arVertexes.push_back(TMPoint(nWidth,0));
        m_arVertexes.push_back(TMPoint(nWidth,nHeight));
        m_arVertexes.push_back(TMPoint(0,nHeight));
        m_arVertexes.push_back(TMPoint(0,0));
    }
    else
    {
        m_arVertexes.push_back(TMPoint(0,0));
        m_arVertexes.push_back(TMPoint(0,nHeight));
        m_arVertexes.push_back(TMPoint(nWidth,nHeight));
        m_arVertexes.push_back(TMPoint(nWidth,0));
    }

    // Edges
    m_arEdges.push_back(TSegmentVector(TMPoint(0,0),TMPoint(nWidth,0)));
    if (m_iDirection==EClockwise)
    {
        m_arEdges.push_back(TSegmentVector(TMPoint(nWidth,0),TMPoint(nWidth,nHeight)));
        m_arEdges.push_back(TSegmentVector(TMPoint(nWidth,nHeight),TMPoint(0,nHeight)));
        m_arEdges.push_back(TSegmentVector(TMPoint(0,nHeight),TMPoint(0,0)));
    }
    else
    {
        m_arEdges.push_back(TSegmentVector(TMPoint(0,nHeight),TMPoint(0,0)));
        m_arEdges.push_back(TSegmentVector(TMPoint(nWidth,nHeight),TMPoint(0,nHeight)));
        m_arEdges.push_back(TSegmentVector(TMPoint(nWidth,0),TMPoint(nWidth,nHeight)));
    }

    //
    return S_OK;
}

HRESULT CRadar::DrawLiveBitmap(IN HDC hdcHide,
                               IN HDC hdcShow,
                               IN HDC hdcOutput)
{

    INT iWidth = _basex::Width();
    INT iHeight = _basex::Height();

    
    if (!m_bDisplayOn)
    {        
        // Input1 -> OutputDC
        ::BitBlt(hdcOutput,0,0,iWidth,iHeight,hdcShow,0,0,SRCCOPY);
        
        // 
        ::SelectClipRgn(hdcOutput, m_hrgnArea); 
        
        // Transfer (draw) the bitmap into the clipped rectangle. 
        ::BitBlt(hdcOutput, 
            0, 0, 
            _basex::Width(), 
            _basex::Height(),
            hdcHide, 
            0, 0, 
            SRCCOPY);  
    }
    else
    {
        ::SelectClipRgn(hdcOutput, m_hrgnArea); 

        // Transfer (draw) the bitmap into the clipped rectangle. 
        ::BitBlt(hdcOutput, 
            0, 0, 
            _basex::Width(), 
            _basex::Height(),
            hdcShow, 
            0, 0, 
            SRCCOPY);     
    }
    
    ::SelectClipRgn(hdcOutput,NULL);

    // Draw pointer.
    if (m_iPointerWidth>0)
    {
        ::SelectObject(hdcOutput,m_hPen);
        ::MoveToEx(hdcOutput,
            m_sgPointer.iStartPoint.iX,
            m_sgPointer.iStartPoint.iY,
            NULL);
        ::LineTo(hdcOutput,
            m_ptCross.iX,
            m_ptCross.iY);
    }
    

    // 
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CRadar::get_State(BOOL *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
    return S_OK;
}

STDMETHODIMP CRadar::put_State(BOOL newVal)
{
    // TODO: Add your implementation code here
    m_bDisplayOn = newVal;
    return S_OK;
}

STDMETHODIMP CRadar::get_Direction(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iDirection;
	return S_OK;
}

STDMETHODIMP CRadar::put_Direction(INT newVal)
{
    // TODO: Add your implementation code here
    if (newVal<0 || newVal>1)
    {
        return E_INVALIDARG;
    }
    
    m_iDirection = (TRoundDir)newVal;
    
	return S_OK;
}

STDMETHODIMP CRadar::get_PointerColor(OLE_COLOR *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_clrPointer;

	return S_OK;
}

STDMETHODIMP CRadar::put_PointerColor(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
    if (_basex::IsTransparent(newVal))
    {
        m_clrPointer = 0;
    }
    else
    {
        m_clrPointer = (newVal&0x00FFFFFF);
        
        if (m_clrPointer==0)
        {
            m_clrPointer = _basex::GetBlackAgentClr();
        }
    }
	return S_OK;
}

STDMETHODIMP CRadar::get_PointerWidth(INT *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iPointerWidth;

	return S_OK;
}

STDMETHODIMP CRadar::put_PointerWidth(INT newVal)
{
	// TODO: Add your implementation code here
    m_iPointerWidth = newVal;
	return S_OK;
}
