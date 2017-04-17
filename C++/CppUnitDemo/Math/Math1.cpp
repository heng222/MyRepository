// Math1.cpp: implementation of the CMath class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Math1.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMath::CMath()
{

}

CMath::~CMath()
{

}

int CMath::Add(int a, int b)
{
	return a+b;
}

int CMath::Minus(int a, int b)
{
	return a - b;
}