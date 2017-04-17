// Coalesce.cpp : Implementation of CCoalesce
#include "stdafx.h"
#include "Coalesce.h"
#include "RandMgr.h"
/////////////////////////////////////////////////////////////////////////////
// CCoalesce


#define   MIN_ENTITYSIZE    1
#define   MAX_ENTITYSIZE    32
#define   DEFAULT_SIZE      3

//
//  --------------- CCoalesce ----------------
//
HRESULT CCoalesce::FinalConstruct()
{
    RTN_HR_IF_FAILED(_basex::FinalConstruct());
    
    //
    m_bDisplayOn = TRUE;
    m_sizeEntity.iWidth = DEFAULT_SIZE;
    m_sizeEntity.iHeight = DEFAULT_SIZE;  
    m_iHLines = 0;
    m_iVLines = 0;
    m_iCurrentNum = 0;

    return S_OK;
}

HRESULT CCoalesce::OnInitialize()
{
    RTN_HR_IF_FAILED(_basex::OnInitialize());
    // add your code after here

    // clear travel rectangles
    ClearEntity();

    //
    CRandMgr::InitRandSeed();
    
    // generate slots        
    _thisx::Initialize();
    
    // 
    return S_OK;
}

HRESULT CCoalesce::OnTerminate()
{
    ClearEntity();

    // add your code before here.
    RTN_HR_IF_FAILED(_basex::OnTerminate());
    
    return S_OK;
}


//////////////////////////////////////////////////////////////////////////
// Private methods
HRESULT CCoalesce::ClearEntity()
{
    for (size_t n=0; n<m_Entity.size(); n++)
    {
        delete m_Entity[n];
    }
    m_Entity.clear();

    //
    return S_OK;
}

VOID  CCoalesce::ResetEntity()
{
    for (size_t n=0; n<m_Entity.size(); n++)
    {
        m_Entity[n]->m_bFlag = FALSE;
    }
}

HRESULT CCoalesce::ResetControlValue()
{
    m_iCurrentNum = 0;

    ResetEntity();

    // 
    return S_OK;
}

HRESULT CCoalesce::UpdateControlValue()
{
    FLOAT fProgress = _basex::GetProgress();

    // Reset
    INT iNewNum = INT(fProgress*m_iVLines);
    INT iNumUpdate = iNewNum - m_iCurrentNum;

    // Update
    LONG lIndex = 0;
    for (INT i=0; i<m_iHLines; i++)
    {
        if (iNumUpdate>0)
        {
            for (INT j=0; j<iNumUpdate; )
            {
                INT iTmpIndex;
                if (!CRandMgr::CreateRandomNum(iTmpIndex,0,m_iVLines-1))
                {
                    return E_FAIL;
                }
                
                //
                if (!m_Entity[lIndex+iTmpIndex]->m_bFlag)
                {
                    m_Entity[lIndex+iTmpIndex]->m_bFlag = TRUE;
                    j++;
                }
            }
        }
        else
        {
            for (INT j=0; j<-iNumUpdate; )
            {
                INT iTmpIndex;
                if (!CRandMgr::CreateRandomNum(iTmpIndex,0,m_iVLines-1))
                {
                    return E_FAIL;
                }
                
                //
                if (m_Entity[lIndex+iTmpIndex]->m_bFlag)
                {
                    m_Entity[lIndex+iTmpIndex]->m_bFlag = FALSE;
                    j++;
                }
            }
        }
        
        // pointer to next row
        lIndex += m_iVLines;
    }

    // 
    m_iCurrentNum = iNewNum;

    // 
    return S_OK;
}

HRESULT CCoalesce::Initialize()
{
    // Initialize mosaic
    INT nWidth  = _basex::Width();
    INT nHeight = _basex::Height();
    
    INT iEntityWidth = m_sizeEntity.iWidth;
    INT iEntityHeight = m_sizeEntity.iHeight;
    
    // numbers of mosaic per row    
    if (nWidth>iEntityWidth)
    {
        m_iHLines = nWidth / iEntityWidth;
        if (nWidth%iEntityWidth!=0)
        {
            m_iHLines ++;
        }
    } 
    else
    {
        iEntityWidth = nWidth;
        m_iHLines = 1;
    }
    
    // numbers of mosaic per column
    if (nHeight>iEntityHeight)
    {
        m_iVLines = nHeight / iEntityHeight;
        if (nHeight%iEntityHeight!=0)
        {
            m_iVLines ++;
        }
    } 
    else
    {
        iEntityHeight = nHeight;
        m_iVLines = 1;
    }
        
    // create mosaic
    TMRect rMscOrgSeed(0,0,iEntityWidth,iEntityHeight);
    for (INT i=0; i<m_iVLines; i++)
    {
        // mosaic seed on every row.
        TMRect rMscRowSeed = rMscOrgSeed;
        rMscRowSeed.MoveTop(i*iEntityHeight);
        
        // create row mosaic
        for (INT j=0; j<m_iHLines; j++)
        {
            TMRect rEntityItem = rMscRowSeed;
            rEntityItem.MoveRight( j * iEntityWidth );
            
            // create Entity
            TEntity* pEntity = new TEntity;
            RTN_HR_IF_BADPTR(pEntity);
            pEntity->m_rExtent = rEntityItem;
            m_Entity.push_back(pEntity);
        }
        
    }
    
    // 
    m_iCurrentNum = 0;
    
    //
    return S_OK;
}

HRESULT CCoalesce::DrawLiveBitmap(IN HDC hInDC1,
                               IN HDC hdcShow,
                               IN HDC hOutDC)
{
    // Draw Entity grids
    RECT rDest;    
    INT iSize = m_Entity.size();
    for (INT i=0; i<iSize; i++)
    {
        TEntity* pTR = m_Entity[i];
        rDest = pTR->m_rExtent.ToRECT();
        if (pTR->m_bFlag)
        {   
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
    }

    // 
    return S_OK;
}

//////////////////////////////////////////////////////////////////////////
// Properties

STDMETHODIMP CCoalesce::get_State(BOOL *pVal)
{
    // TODO: Add your implementation code here
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_bDisplayOn;
	return S_OK;
}

STDMETHODIMP CCoalesce::put_State(BOOL newVal)
{
    // TODO: Add your implementation code here
    m_bDisplayOn = newVal;
	return S_OK;
}

STDMETHODIMP CCoalesce::get_EntityWidth(INT *pVal)
{
	// TODO: Add your implementation code here
    
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_sizeEntity.iWidth;
	return S_OK;
}

STDMETHODIMP CCoalesce::put_EntityWidth(INT newVal)
{
	// TODO: Add your implementation code here
    if (newVal>MAX_ENTITYSIZE || newVal<MIN_ENTITYSIZE)
    {
        newVal = DEFAULT_SIZE;
    }

    m_sizeEntity.iWidth = newVal;

	return S_OK;
}

STDMETHODIMP CCoalesce::get_EntityHeight(INT *pVal)
{
	// TODO: Add your implementation code here
    
    RTN_HR_IF_BADPTR(pVal);
    *pVal = m_sizeEntity.iHeight;

	return S_OK;
}

STDMETHODIMP CCoalesce::put_EntityHeight(INT newVal)
{
    // TODO: Add your implementation code here
    if (newVal>MAX_ENTITYSIZE || newVal<MIN_ENTITYSIZE)
    {
        newVal = DEFAULT_SIZE;
    }
    
    m_sizeEntity.iHeight = newVal;

	return S_OK;
}
