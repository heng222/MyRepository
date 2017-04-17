// RandMgr.cpp: implementation of the CRandMgr class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "RandMgr.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CRandMgr::CRandMgr()
{

}

CRandMgr::~CRandMgr()
{

}

void CRandMgr::InitRandSeed()
{
    // Seed the random-number generator with GetTickCount so that
    // the numbers will be different every time we run.
    ::srand(::GetTickCount());
}

/************************************************************************/
/* 产生一个随机数链表
/* 随机数取值范围( >=iMin AND <=iMax )
/************************************************************************/

BOOL  CRandMgr::CreateRandomNum(std::vector<int>& listRand, 
                    INT iMin, INT iMax, INT iNumTotal)
{
    
    // sanity check
    if (iMin>iMax || iNumTotal<0)
    {
        return FALSE;
    }
    
    if ((iMax-iMin)<iNumTotal)
    {
        return FALSE;
    }
    
    // set the size of result.
    listRand.resize(iNumTotal);
    
    // the value included in listRand is between iMin and iMax.
    
    DWORD dwBound = iMax - iMin;
    
    INT i = 0;
    DWORD dwTemp = 0;
    
    while (i<iNumTotal)
    {
        dwTemp = (abs(::rand()) * dwBound) / RAND_MAX; // dwValue>=0 && dwValue<=dwBound
        ASSERT(dwTemp>=0 && dwTemp<=dwBound);
        
        // 
        LONG lActualValue = dwTemp + iMin;
        
        INT j = 0;
        for (; j<i; j++)
        {
            // does the rand position exist?
            if (listRand[j]==lActualValue)
            {
                break;
            }
        }
        
        // doesn't exist, then push back to the array.
        if (j==i)
        {
            listRand[i] = lActualValue;
            i++;
        }
    }    
    
    return TRUE;
}


BOOL CRandMgr::CreateRandomNum(INT& iRandNum, 
                    INT iMin, INT iMax)
{
    
    // sanity check
    if (iMin>iMax)
    {
        return FALSE;
    }
    
    
    // the value included in listRand is between iMin and iMax.
    
    // dwTemp>=0 && dwTemp<=dwBound
    DWORD dwTemp = (abs(::rand()) * (iMax - iMin)) / RAND_MAX;
    
    // 
    iRandNum = dwTemp + iMin;
    
    return TRUE;
    
}

/************************************************************************/
/* 在指定的Rect中随机产生dwNumRequest个数
/************************************************************************/

BOOL CRandMgr::GenerateRandPos(std::vector<POINT>& ptArray,
                    DWORD dwNumRequest,RECT rExtent)
{
    if (rExtent.left>rExtent.right || rExtent.top>rExtent.bottom)
    {
        return FALSE;
    }

    // 
    INT nHeight = rExtent.bottom - rExtent.top;
    INT nWidth = rExtent.right - rExtent.left;
    
    vector<INT> listXValue;
    POINT ptRandom;
    ptArray.resize(dwNumRequest);
    
    //
    INT iNumPerLine = dwNumRequest/nHeight;
    ASSERT(iNumPerLine>=0);
    
    // Create most of the random number.
    if (iNumPerLine>0)
    {      
        for (INT k=0; k<nHeight; k++)
        {
            CRandMgr::CreateRandomNum( listXValue,rExtent.left,
                rExtent.right, iNumPerLine ); 
            //
            for( INT n=0; n<iNumPerLine; n++)
            {      
                ptRandom.x = listXValue[n];
                ptRandom.y = k;
                ptArray[k*iNumPerLine + n] = ptRandom;
            }
        }
    }
    
    // create the remaining numbers.
    INT iLeftNum = dwNumRequest - iNumPerLine*nHeight;
    CRandMgr::CreateRandomNum(listXValue,0,nWidth*nHeight-1,  iLeftNum ); 
    size_t nSize = listXValue.size();
    for (size_t i=0; i<nSize; i++)
    {
        ptRandom.x = listXValue[i] % nWidth;
        ptRandom.y = listXValue[i] / nWidth;
        ptArray[nHeight*iNumPerLine + i] = ptRandom;
    }
    
    
    // 
    return TRUE;
}
