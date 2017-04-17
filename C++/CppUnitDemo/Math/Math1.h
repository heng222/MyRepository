// Math1.h: interface for the CMath class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATH1_H__E4FE003A_F70C_4FF3_AA1C_7204C9517F03__INCLUDED_)
#define AFX_MATH1_H__E4FE003A_F70C_4FF3_AA1C_7204C9517F03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CMath
{
public:
	static int Add(int a, int b);
	static int Minus(int a, int b);
	CMath();
	virtual ~CMath();

};

#endif // !defined(AFX_MATH1_H__E4FE003A_F70C_4FF3_AA1C_7204C9517F03__INCLUDED_)
