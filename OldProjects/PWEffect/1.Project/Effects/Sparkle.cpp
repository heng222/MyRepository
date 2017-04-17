// Sparkle.cpp : Implementation of CSparkle
#include "stdafx.h"
#include "PWEffect.h"
#include "Sparkle.h"

/////////////////////////////////////////////////////////////////////////////
// TStart


TStar::TStar()
{
    m_nOrgSize = 0;
    m_nCurSize = 0;
    m_iStep = 1;
    m_bShrink = TRUE;
}


void TStar::Initialize()
{
    m_iStep = ::rand()*m_nOrgSize/ RAND_MAX;
    m_bShrink = (m_nCurSize % 2==0);
}

void TStar::Update()
{    
    if (m_iStep<0)
    {
        m_iStep = 0;
        m_bShrink = TRUE;
    }
    else if (m_iStep>m_nOrgSize*2)
    {
        m_iStep = m_nOrgSize;
        m_bShrink = FALSE;
    }
    
    // 
    m_nCurSize = m_nOrgSize - m_iStep;    
    
    
    if (m_bShrink)
    {
        m_iStep += 2;
    }
    else
    {
        m_iStep -= 2;
    }
    
}

void TStar::Draw(HDC hdc) const
{
    if (m_nCurSize<=0)
    {
        return;
    }

    POINT pt1,pt2;

    // horizontal line.
    pt1.x = m_ptPos.x - m_nCurSize/2;
    pt1.y = m_ptPos.y;        
    pt2.x = pt1.x + m_nCurSize;
    pt2.y = m_ptPos.y;
    
    ::MoveToEx(hdc,pt1.x,pt1.y,NULL);
    ::LineTo(hdc,pt2.x,pt2.y);
    
    // vertical line.
    pt1.x = m_ptPos.x;
    pt1.y = m_ptPos.y - m_nCurSize/2;
    pt2.x = m_ptPos.x;
    pt2.y = pt1.y + m_nCurSize;
    
    ::MoveToEx(hdc,pt1.x,pt1.y,NULL);
    ::LineTo(hdc,pt2.x,pt2.y);
}

//
//  ----------------------------- CSparkle -----------------------------------
//
HRESULT CSparkle::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    // 
    m_clrSparkle = RGB(255,255,255);
    m_iSizeStar = 5;
    m_fAmount = 0.2f;
    m_hPenSparkle = NULL;
    
    return S_OK;
}

HRESULT CSparkle::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here
    
    // Seed the random-number generator with GetTickCount so that
    // the numbers will be different every time we run.
    ::srand(::GetTickCount());
    
    // create some random position to draw sparkle.
    DWORD dwNumRequest = DWORD(m_fAmount*Width()*Height());
    dwNumRequest /= GetSparkleArea();
    RECT rExtent = {0,0,Width(),Height()};
    CRandMgr::GenerateRandPos(m_arrayStarPos,dwNumRequest,rExtent);

    // build stars to sparkle
    _thisx::BuildStars(m_arrayStars);

    // do random handling.
    //for (INT i=0; i<10; i++)
    //{
        //_thisx::UpdateStars();
    //}

    //
    m_hPenSparkle = ::CreatePen(PS_SOLID,1,m_clrSparkle);
    
    //
    return S_OK;
}

HRESULT CSparkle::OnTerminate()
{
    if (m_hPenSparkle)
    {
        ::DeleteObject(m_hPenSparkle);
        m_hPenSparkle = NULL;
    }

    m_arrayStarPos.resize(0);

    for (INT i=0; i<m_arrayStars.size(); i++)
    {
        delete m_arrayStars[i];
    }
    m_arrayStars.resize(0);
    
    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


// 
HRESULT CSparkle::OnImplEffect(IN DWORD* pInputBuf,
                                 IN DWORD* pOutputBuf,
                                 IN INT iWidth,
                                 IN INT iHeight)
{
    
    if (m_clrSparkle==0) // Transparent
    {
        return E_NOTIMPL;
    }
    
    // Create a bitmap of input surface. 
    HBITMAP hInputBitmap = _basex::CreateSufaceBitmap(
        iWidth,iHeight,pInputBuf);
    
    // Select it to the DC.
    HDC hMemDC = _basex::GetMemDC();
    HBITMAP hOldBmp = (HBITMAP)::SelectObject(hMemDC,hInputBitmap);
    
    // Update
    _thisx::UpdateStars();

    // Draw Sparkle
    _thisx::DrawSparkle(hMemDC);
    
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


//////////////////////////////////////////////////////////////////////////
// Private methods


BOOL CSparkle::BuildStars(CStarArray& aStars) const
{
    int iNum = m_arrayStarPos.size();
    aStars.resize(iNum);

    // 
    for (INT i=0; i<iNum; i++)
    {
        TStar* newStar = new TStar;

        ASSERT(newStar);
        if (newStar==NULL)
        {
            return FALSE;
        }

        newStar->m_ptPos = m_arrayStarPos[i];
        newStar->m_nOrgSize = m_iSizeStar;
        newStar->Initialize();
        aStars[i] = newStar;
    }

    // 
    return TRUE;
}


void CSparkle::UpdateStars()
{
    // 
    INT iNum = m_arrayStars.size();

    // random update
    vector<INT> listXValue;
    CRandMgr::CreateRandomNum(listXValue,0, iNum-1, iNum*0.8 ); 

    // loop to update
    INT iSizeRand = listXValue.size();
    for (INT i=0 ; i<iSizeRand; i++)
    {
        INT iNo = listXValue[i];
        ASSERT(iNo<iNum && iNo>=0);
        m_arrayStars[iNo]->Update();
    }

    //
    listXValue.resize(0);
}
    
DWORD CSparkle::GetSparkleArea() const
{
    return m_iSizeStar*m_iSizeStar;
}


void CSparkle::DrawSparkle(HDC hdc) const
{
    HANDLE hOldPen = ::SelectObject(hdc,m_hPenSparkle);
    
    INT nNumStars = m_arrayStars.size();
    
    //
    for (INT i=0; i<nNumStars; i++)
    {
        m_arrayStars[i]->Draw(hdc);
    }

    ::SelectObject(hdc,hOldPen);

}


//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CSparkle::get_SparkleColor(OLE_COLOR *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_clrSparkle;
	return S_OK;
}

STDMETHODIMP CSparkle::put_SparkleColor(OLE_COLOR newVal)
{
	// TODO: Add your implementation code here
    m_clrSparkle = (newVal&0x00FFFFFF);
    if (m_clrSparkle==0)
    {
        m_clrSparkle = _basex::GetBlackAgentClr();
    }
	return S_OK;
}

STDMETHODIMP CSparkle::get_Amount(FLOAT *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_fAmount;
	return S_OK;
}

STDMETHODIMP CSparkle::put_Amount(FLOAT newVal)
{
	// TODO: Add your implementation code here
    m_fAmount = newVal;
	return S_OK;
}

STDMETHODIMP CSparkle::get_Size(INT *pVal)
{
	// TODO: Add your implementation code here
    *pVal = m_iSizeStar;
	return S_OK;
}

STDMETHODIMP CSparkle::put_Size(INT newVal)
{
	// TODO: Add your implementation code here
    m_iSizeStar = newVal;
	return S_OK;
}
