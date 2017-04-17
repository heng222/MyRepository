// Bijou.cpp : Implementation of CBijou
#include "stdafx.h"
#include "PWEffect.h"
#include "Bijou.h"

//#define         _DRAW_BOTTOM_BIJOU_
/////////////////////////////////////////////////////////////////////////////
// CBijou

#define			TIME_OUT		10

// 
//  --------------- CBijou ----------------
//////////////////////////////////////////////////////////////////////////
// From base class
HRESULT CBijou::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());

	m_iTimeOut = 1;
    m_iCurrentDir = EClockwise;
    // 
    m_iDirection = EClockwise;
    m_iRate = 1;
    
    m_iLampHeight = 3;
    m_iLampLength = 3;
    m_bCornersOn = TRUE;
    m_iGapLength = 3;
    m_clrLamp = RGB(255,0,0);
    m_clrGap = RGB(0,0,0);

    m_hLampBrush = NULL;
    m_hGapBrush  = NULL;
    
    return S_OK;
}

HRESULT CBijou::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your codes here.

    // adjust the rate.
    m_iRate %= ((m_iLampLength+m_iGapLength)/2+1);
	
	//
	int iBkgWidth   = _basex::Width();
	int iBkgHeight  = _basex::Height();

	m_rectCanvas    = TMRect(TMPoint(0,0),
        TMSize(iBkgWidth,iBkgHeight),EPCScreen);    

    // Create brushes
    if (m_hLampBrush==NULL)
    {
        m_hLampBrush = ::CreateSolidBrush(m_clrLamp);
    }

    if (m_hGapBrush==NULL)
    {
        m_hGapBrush = ::CreateSolidBrush(m_clrGap);
    }
    //
	RTN_HR_IF_FALSE(InitializeBijou());

    return S_OK;
}

HRESULT CBijou::OnStart()
{
    return S_OK;
}

HRESULT CBijou::OnTerminate()
{
    if (m_hGapBrush)
    {
        ::DeleteObject(m_hGapBrush);
        m_hGapBrush = NULL;
    }

    if (m_hLampBrush)
    {
        ::DeleteObject(m_hLampBrush);
        m_hLampBrush = NULL;
    }
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


// 
HRESULT CBijou::OnImplEffect(IN DWORD* pInputBuf,
                             IN DWORD* pOutputBuf,
                             IN INT iWidth,  IN INT iHeight)
{
    // 
    BOOL rc = S_OK;

	// move and update Bijou.
	UpdateBijou();  


    // Create a bitmap of input surface.    
    HBITMAP hInputBitmap = _basex::CreateSufaceBitmap(
        iWidth,iHeight,pInputBuf);
    
    // Select it to the DC.
    HDC hMemDC = _basex::GetMemDC();
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,hInputBitmap);
    
    // Draw Title
    DrawBijou(hMemDC);
    
    //
    // the DIB info we used to get title pixel-mapping.
    BITMAPINFO bmi;
    _basex::GetSurfaceBmpInfo(bmi);
    
    //
    
    // get DIB's bits.
    LONG lLines = ::GetDIBits( CAutoDeskDC(), hInputBitmap, 0, iHeight, 
        (PVOID)pOutputBuf, 
        (BITMAPINFO *)&bmi, 
        DIB_RGB_COLORS);
    
    // 
    ::SelectObject(hMemDC,hOldBmp);
    ::DeleteObject(hInputBitmap);
    _basex::ReleaseMemDC();

    //
	return rc;
}

//////////////////////////////////////////////////////////////////////////
// private methods

BOOL CBijou::InitializeBijou()
{
	// generate some seed to grow/move.
	
	TMPoint ptOffset;

	// left
	GetLeftStartPos(m_ptLeftStart);
	GetLeftOffset(ptOffset);

	GenerateLamps( m_LeftLamps, 
		m_ptLeftStart,
		m_iLampHeight,		
		m_iLampLength,
		ptOffset,
		m_rectCanvas.Height() );


	// top
	GetTopStartPos(m_ptTopStart);
	GetTopOffset(ptOffset);

	GenerateLamps( m_TopLamps, 
		m_ptTopStart,
		m_iLampLength,		
		m_iLampHeight,
		ptOffset,
		m_rectCanvas.Width() );



	// right
	GetRightStartPos(m_ptRightStart);
	GetRightOffset(ptOffset);

	GenerateLamps( m_RightLamps, 
		m_ptRightStart,
		m_iLampHeight,		
		m_iLampLength,
		ptOffset,
		m_rectCanvas.Height() );

    // bottom
    GetBottomStartPos(m_ptBottomStart);
    GetBottomOffset(ptOffset);
    
    GenerateLamps( m_BottomLamps, 
        m_ptBottomStart,		
        m_iLampLength,
        m_iLampHeight,
        ptOffset,
		m_rectCanvas.Width() );
	
	// 
	return TRUE;
}


BOOL CBijou::GenerateLamps(CMRectVector& arrayLamp,
						   TMPoint ptStart,INT iWidth,INT iHeight,
						   TMPoint ptOffset,LONG lExtentLen )
{
	arrayLamp.resize(0);

	// how many lamps should be create.
	double fStep = sqrt(ptOffset.iX*ptOffset.iX + ptOffset.iY*ptOffset.iY);
	INT iNum = INT(lExtentLen / fStep);
	
	// Create lamp seed.
	TMRect rLampSeed(ptStart,TMSize(iWidth,iHeight),EPCScreen);

	// save the lamp
	arrayLamp.push_back(rLampSeed);

	for (INT n=0; n<iNum; n++)
	{
		// offset seed
		rLampSeed.Offset(ptOffset);
		
		// save the lamp to the array.(add to tail)
		arrayLamp.push_back(rLampSeed);
	}


	return TRUE;
}

void CBijou::UpdateBijou()
{
	TMPoint ptOffset;
	INT iValue = 0;
	TRoundDir iCurDir = m_iDirection;

	// if the mode is EAlternating, then ...
	if (m_iDirection==EAlternating)
	{

		if (m_iTimeOut%TIME_OUT==0)
		{
			m_iCurrentDir = (m_iCurrentDir==EClockwise)?ECounterClockwise:EClockwise;
            GetLeftLastLampPos(m_ptLeftStart);
            GetTopLastLampPos(m_ptTopStart);
            GetRightLastLampPos(m_ptRightStart);
            GetBottomLastLampPos(m_ptBottomStart);
		}

		m_iTimeOut ++;

		iCurDir = m_iCurrentDir;
	}


	// 1. update left lamps's position.
	GetLeftOffset(ptOffset);
	if (iCurDir==EClockwise)
	{
		m_ptLeftStart.iY -= m_iRate;
		iValue = (m_rectCanvas.Height() - m_ptLeftStart.iY -
						m_iLampLength - m_iGapLength);
		
		// recalculate start position.
		if (iValue>0)
		{
			m_ptLeftStart.iY = m_rectCanvas.Height()-iValue;
		}
	}
	else if (iCurDir==ECounterClockwise)
	{
		m_ptLeftStart.iY += m_iRate;
		iValue = (m_ptLeftStart.iY-m_iGapLength);
		
		// recalculate start position.
		if (iValue>0)
		{
			m_ptLeftStart.iY = iValue-m_iLampLength;
		}
	}
	//
	GenerateLamps( m_LeftLamps, m_ptLeftStart,
		m_iLampHeight,	m_iLampLength,
		ptOffset,	m_rectCanvas.Height() );
	

	
	// 2. update right's lamps
	GetRightOffset(ptOffset);
	if (iCurDir==EClockwise)
	{
		m_ptRightStart.iY += m_iRate;
		iValue = (m_ptRightStart.iY-m_iGapLength);
		
		// recalculate start position.
		if (iValue>0)
		{
			m_ptRightStart.iY = iValue-m_iLampLength;
		}
	}
	else if (iCurDir==ECounterClockwise)
	{
		m_ptRightStart.iY -= m_iRate;

		iValue = (m_rectCanvas.Height() - m_ptRightStart.iY -
			m_iLampLength - m_iGapLength);
		
		// recalculate start position.
		if (iValue>0)
		{
			m_ptRightStart.iY = m_rectCanvas.Height()-iValue;
		}
	}
	//
	GenerateLamps( m_RightLamps, 	m_ptRightStart,
		m_iLampHeight,			m_iLampLength,
		ptOffset,		m_rectCanvas.Height() );
	

	// 3. update Top's lamps
	GetTopOffset(ptOffset);
	if (iCurDir==EClockwise)
	{
		m_ptTopStart.iX += m_iRate;
		iValue = (m_ptTopStart.iX-m_iGapLength);
		
		// recalculate start position.
		if (iValue>0)
		{
			m_ptTopStart.iX -= m_iGapLength;
            m_ptTopStart.iX -= m_iLampLength;
		}
	}
	else if (iCurDir==ECounterClockwise)
	{
		m_ptTopStart.iX -= m_iRate;
		
		iValue = (m_rectCanvas.Width() - m_ptTopStart.iX -
			m_iLampLength - m_iGapLength);
		
		// recalculate start position.
		if (iValue>0)
		{
			m_ptTopStart.iX = m_rectCanvas.Width()-iValue;
		}
	}
	//
	GenerateLamps( m_TopLamps,	m_ptTopStart,
		m_iLampLength,	m_iLampHeight,				
		ptOffset,		m_rectCanvas.Width() );

    // 4. update bottom's lamps
    GetBottomOffset(ptOffset);
    if (iCurDir==EClockwise)
    {
        m_ptBottomStart.iX -= m_iRate;
        
        iValue = (m_rectCanvas.Width() - m_ptBottomStart.iX -
            m_iLampLength - m_iGapLength);
        
        // recalculate start position.
        if (iValue>0)
        {
            m_ptBottomStart.iX = m_rectCanvas.Width()-iValue;
        }
    }
    else if (iCurDir==ECounterClockwise)
    {
        m_ptBottomStart.iX += m_iRate;
        iValue = (m_ptBottomStart.iX-m_iGapLength);
        
        // recalculate start position.
        if (iValue>0)
        {
            m_ptBottomStart.iX -= m_iGapLength;
            m_ptBottomStart.iX -= m_iLampLength;
        }
    }
    //
    GenerateLamps( m_BottomLamps,	m_ptBottomStart,
        m_iLampLength,	m_iLampHeight,				
		ptOffset,		m_rectCanvas.Width() );

}

void CBijou::DrawLamp(HDC hDC,const RECT& rRect) const
{
    if (m_clrLamp==CLR_TRANSPARENT_AGENT) // Transparent
    {
        return;
    }

    ::FillRect(hDC,&rRect,m_hLampBrush);
}

void CBijou::DrawGap(HDC hDC,const RECT& rRect) const
{
    if (m_clrGap==CLR_TRANSPARENT_AGENT) // Transparent
    {
        return;
    }
    
    ::FillRect(hDC,&rRect,m_hGapBrush);

}

void    CBijou::DrawBijou(HDC hDC)
{
    INT nWidth = _basex::Width();
    INT nHeight = _basex::Height();

    // 1. Draw gaps
    RECT rLeftRect = {0,0,m_iLampHeight,nHeight};
    DrawGap(hDC, rLeftRect);
    
    RECT rRightRect = {nWidth-m_iLampHeight,0,nWidth,nHeight};
    DrawGap(hDC, rRightRect);
    
    RECT rTopRect = {0,0,nWidth,m_iLampHeight};
    DrawGap(hDC, rTopRect);
    
#ifdef _DRAW_BOTTOM_BIJOU_
    RECT rBottomRect = {0,nHeight-m_iLampHeight,nWidth,nHeight};
    DrawGap(hDC, rBottomRect);
#endif
    
    // 2. Draw lamps
    TMRect rLamp;
    
    // left
    vector<TMRect>::iterator iCur;
    for( iCur = m_LeftLamps.begin(); iCur != m_LeftLamps.end(); ++iCur )
    {
        rLamp = *iCur;
        DrawLamp(hDC,rLamp.ToRECT());
    }
    
    // top
    for( iCur = m_TopLamps.begin(); iCur != m_TopLamps.end(); ++iCur )
    {
        rLamp = *iCur;
        DrawLamp(hDC,rLamp.ToRECT());
    }
    
    // Right
    for( iCur = m_RightLamps.begin(); iCur != m_RightLamps.end(); ++iCur )
    {
        rLamp = *iCur;
        DrawLamp(hDC,rLamp.ToRECT());
    }
    
#ifdef _DRAW_BOTTOM_BIJOU_
    // Bottom
    for( iCur = m_BottomLamps.begin(); iCur != m_BottomLamps.end(); ++iCur )
    {
        rLamp = *iCur;
        DrawLamp(hDC,rLamp.ToRECT());
    }
#endif
    
    // Draw corners if the flag is set.
    if (m_bCornersOn)
    {
        TMRect rTopLeft(TMPoint(0,0),TMSize(m_iLampHeight,m_iLampHeight),EPCScreen);
        
        TMRect rTopRight( TMPoint(m_rectCanvas.Width()-m_iLampHeight,0),
            TMSize(m_iLampHeight,m_iLampHeight),EPCScreen);
        
        TMRect rBottomRight( 
            TMPoint(m_rectCanvas.Width()-m_iLampHeight, m_rectCanvas.Height()-m_iLampHeight),
            TMSize(m_iLampHeight,m_iLampHeight),EPCScreen);
        
        TMRect rBottomLeft( TMPoint(0,m_rectCanvas.Height()-m_iLampHeight),
            TMSize(m_iLampHeight,m_iLampHeight),EPCScreen);
        
        //
        TMRect rLamp = rTopLeft;
        DrawLamp(hDC,rLamp.ToRECT());
        rLamp = rTopRight;
        DrawLamp(hDC,rLamp.ToRECT());
        
#ifdef _DRAW_BOTTOM_BIJOU_
        rLamp = rBottomRight;
        DrawLamp(hDC,rLamp.ToRECT());
        rLamp = rBottomLeft;
        DrawLamp(hDC,rLamp.ToRECT());
#endif
	}
}

void	CBijou::GetLeftStartPos(TMPoint& ptStart) const
{
    TRoundDir iDir = m_iDirection;
    if(iDir==EAlternating)
    {
        iDir = m_iCurrentDir;
    }

	if (iDir==EClockwise)
	{
		ptStart = TMPoint(0,m_rectCanvas.Height()-m_iLampLength);
	}
	else 
	{
		ptStart = TMPoint(0,0);
	}
}


void	CBijou::GetTopStartPos(TMPoint& ptStart) const
{
    TRoundDir iDir = m_iDirection;
    if(iDir==EAlternating)
    {
        iDir = m_iCurrentDir;
    }

	if (iDir==EClockwise)
	{
		ptStart = TMPoint(0,0);
	}
	else
	{
		ptStart = TMPoint(m_rectCanvas.Width()-m_iLampLength,0);
	}
}

void CBijou::GetBottomStartPos(TMPoint& ptStart) const
{
    TRoundDir iDir = m_iDirection;
    if(iDir==EAlternating)
    {
        iDir = m_iCurrentDir;
    }

    if (iDir==EClockwise)
    {
        ptStart = TMPoint(m_rectCanvas.Width()-m_iLampLength,
            m_rectCanvas.Height()-m_iLampHeight);
    }
    else
    {
        ptStart = TMPoint(0,m_rectCanvas.Height()-m_iLampHeight);
    }
}


void	CBijou::GetRightStartPos(TMPoint& ptStart) const
{
    TRoundDir iDir = m_iDirection;
    if(iDir==EAlternating)
    {
        iDir = m_iCurrentDir;
    }

	// right
	if (iDir==EClockwise)
	{
		ptStart = TMPoint(m_rectCanvas.Width()-m_iLampHeight,0);
	}
	else
	{
		ptStart = TMPoint(m_rectCanvas.Width()-m_iLampHeight,
			m_rectCanvas.Height()-m_iLampLength);
	}

}
void  CBijou::GetLeftOffset(TMPoint& ptOffset) const
{
    TRoundDir iDir = m_iDirection;
    if(iDir==EAlternating)
    {
        iDir = m_iCurrentDir;
    }

	if (iDir==EClockwise)
	{
		ptOffset = TMPoint(0, -(m_iGapLength+m_iLampLength));
	}
	else
	{
		ptOffset = TMPoint( 0, m_iGapLength+m_iLampLength );
	}
}
void  CBijou::GetTopOffset(TMPoint& ptOffset) const
{
    
    TRoundDir iDir = m_iDirection;
    if(iDir==EAlternating)
    {
        iDir = m_iCurrentDir;
    }

	if (iDir==EClockwise)
	{
		ptOffset = TMPoint(m_iGapLength+m_iLampLength,0);
	}
	else
	{
		ptOffset = TMPoint(-(m_iGapLength+m_iLampLength),0);
	}
}

void  CBijou::GetRightOffset(TMPoint& ptOffset) const
{
    TRoundDir iDir = m_iDirection;
    if(iDir==EAlternating)
    {
        iDir = m_iCurrentDir;
    }

	if (iDir==EClockwise)
	{
		ptOffset = TMPoint(0, m_iGapLength+m_iLampLength);
	}
	else
	{
		ptOffset = TMPoint( 0, -(m_iGapLength+m_iLampLength) );
	}
}
void CBijou::GetBottomOffset(TMPoint& ptOffset) const
{
    
    TRoundDir iDir = m_iDirection;
    if(iDir==EAlternating)
    {
        iDir = m_iCurrentDir;
    }

    if (iDir==EClockwise)
    {
        ptOffset = TMPoint(-(m_iGapLength+m_iLampLength),0);
    }
    else
    {
        ptOffset = TMPoint((m_iGapLength+m_iLampLength),0);
	}
}

//
void CBijou::GetLeftLastLampPos(TMPoint& ptLast) const
{
	INT iSize = m_LeftLamps.size();
	ASSERT(iSize>0);
    m_LeftLamps[iSize-1].GetLocation(&ptLast);
}


// 
void CBijou::GetTopLastLampPos(TMPoint& ptLast) const
{
    INT iSize = m_TopLamps.size();
    ASSERT(iSize>0);
    m_TopLamps[iSize-1].GetLocation(&ptLast);
}

void CBijou::GetRightLastLampPos(TMPoint& ptLast) const
{
    INT iSize = m_RightLamps.size();
    ASSERT(iSize>0);
    m_RightLamps[iSize-1].GetLocation(&ptLast);
}

void CBijou::GetBottomLastLampPos(TMPoint& ptLast) const
{
    INT iSize = m_BottomLamps.size();
    ASSERT(iSize>0);
    m_BottomLamps[iSize-1].GetLocation(&ptLast);
}



//////////////////////////////////////////////////////////////////////////
// interface implementation
STDMETHODIMP CBijou::get_Direction(INT *pVal)
{
    RTN_HR_IF_BADPTR(pVal);
    *pVal = (INT)m_iDirection;

    return S_OK;
}

STDMETHODIMP CBijou::put_Direction(INT newVal)
{
    if (newVal<0)
    {
        return E_FAIL;
    }

    m_iDirection = (TRoundDir)newVal;

    return S_OK;
}

STDMETHODIMP CBijou::get_Rate(INT *pVal)
{
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iRate;
    return S_OK;
}
STDMETHODIMP CBijou::put_Rate(INT newVal)
{
    if (newVal<0)
    {
        return E_FAIL;
    }

    m_iRate = newVal;

    return S_OK;
}

STDMETHODIMP CBijou::get_LampHeight(INT *pVal)
{
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iLampHeight;
    return S_OK;
}
STDMETHODIMP CBijou::put_LampHeight(INT newVal)
{
    if (newVal<=0)
    {
        return E_FAIL;
    }

    m_iLampHeight = newVal;
    return S_OK;
}

STDMETHODIMP CBijou::get_LampLength(INT *pVal)
{
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iLampLength;
    return S_OK;
}
STDMETHODIMP CBijou::put_LampLength(INT newVal)
{
    if (newVal<=0)
    {
        return E_FAIL;
    }
    m_iLampLength = newVal;
    return S_OK;
}

STDMETHODIMP CBijou::get_GapLength(INT *pVal)
{
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_iGapLength;
    return S_OK;
}
STDMETHODIMP CBijou::put_GapLength(INT newVal)
{
    if (newVal<0)
    {
        return E_FAIL;
    }
    m_iGapLength = newVal;
    return S_OK;
}


STDMETHODIMP CBijou::get_CornersOn(BOOL *pVal)
{
	// TODO: Add your implementation code here
	
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bCornersOn;
	return S_OK;
}

STDMETHODIMP CBijou::put_CornersOn(BOOL newVal)
{
	// TODO: Add your implementation code here
	m_bCornersOn = newVal;
	return S_OK;
}

STDMETHODIMP CBijou::get_LampColor(OLE_COLOR *pVal)
{
	// TODO: Add your implementation code here
    
    RTN_HR_IF_BADPTR(pVal);
	*pVal = m_clrLamp;
	return S_OK;
}

STDMETHODIMP CBijou::put_LampColor(OLE_COLOR newVal)
{
    // TODO: Add your implementation code here    
    if (_basex::IsTransparent(newVal))
    {
        m_clrLamp = CLR_TRANSPARENT_AGENT;
    }
    else
    {
        m_clrLamp = (newVal&0x00FFFFFF);
        
        if (m_clrLamp==0)
        {
            m_clrLamp = _basex::GetBlackAgentClr();
        }
    }
	return S_OK;
}

STDMETHODIMP CBijou::get_GapColor(OLE_COLOR *pVal)
{
	// TODO: Add your implementation code here
    
    RTN_HR_IF_BADPTR(pVal);
	*pVal = m_clrGap;
	return S_OK;
}

STDMETHODIMP CBijou::put_GapColor(OLE_COLOR newVal)
{
    // TODO: Add your implementation code here    
    if (_basex::IsTransparent(newVal))
    {
        m_clrGap = CLR_TRANSPARENT_AGENT;
    }
    else
    {
        m_clrGap = (newVal&0x00FFFFFF);
        
        if (m_clrGap==0)
        {
            m_clrGap = _basex::GetBlackAgentClr();
        }
    }

	return S_OK;
}
