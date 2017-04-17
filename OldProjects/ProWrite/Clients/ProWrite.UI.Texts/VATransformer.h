/********************************************************************
	created:	2008/10/24
	created:	24:10:2008   16:21
	filename: 	d:\1.ISoftStone-Project\ProWrite\Clients\ProWrite.UI.Texts\VATransformer.h
	file path:	d:\1.ISoftStone-Project\ProWrite\Clients\ProWrite.UI.Texts
	file base:	VATransformer
	file ext:	h
	author:		
	
	purpose:	虚拟单位与实际单位转换器
*********************************************************************/
#pragma once


//////////////////////////////////////////////////////////////////////////
class CVATransformer
{
public:

    CVATransformer(void);
    ~CVATransformer(void);

public:

    static void SetRatio(INT iRatio) { m_iRatio = iRatio; }
    static INT  GetRatio() { return m_iRatio; }

    // Transformation between virtual value and actual value
public:

    static BOOL    V2A(const LONG& lVValue, LONG& lAValue);
    static BOOL    A2V(const LONG& lAValue, LONG& lVValue);

    static BOOL    V2A(const INT& iVValue, INT& iAValue);
    static BOOL    A2V(const INT& iAValue, INT& iVValue);

    static BOOL    V2A(const SIZE& sVValue, SIZE& sAValue);
    static BOOL    A2V(const SIZE& sAValue, SIZE& sVValue);

private:

    // >0 means virtual/actual greater than 1; 
    // <0 means virtual/actual less than 1 and the absolute value is equal V/A.
    static INT     m_iRatio;

};
