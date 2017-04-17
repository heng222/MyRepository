// RandMgr.h: interface for the CRandMgr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RANDMGR_H__535F609F_6DCF_4991_8FF4_372560BDCE72__INCLUDED_)
#define AFX_RANDMGR_H__535F609F_6DCF_4991_8FF4_372560BDCE72__INCLUDED_


//////////////////////////////////////////////////////////////////////////


#include <WinBase.h>

// STL header and namespace
#include <stdio.h>
#include <tchar.h>
#include <list>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

//////////////////////////////////////////////////////////////////////////
// Random manager
class CRandMgr  
{
public:
	CRandMgr();
	virtual ~CRandMgr();

public:

    static void    InitRandSeed();

    static BOOL    CreateRandomNum(std::vector<int>& listRand, 
                    INT iMin, INT iMax, INT iNum);   
    
    static BOOL    CreateRandomNum(INT& iRandNum, 
                    INT iMin, INT iMax);  

    static BOOL    GenerateRandPos(std::vector<POINT>& ptArray,
                    DWORD dwNumRequest,RECT rExtent);
};

//////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_RANDMGR_H__535F609F_6DCF_4991_8FF4_372560BDCE72__INCLUDED_)
