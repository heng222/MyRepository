#pragma once

#include <Geometry.h>

//////////////////////////////////////////////////////////////////////////
/*
    ���������(�����ļ�MapCity.can)�����������ѯ

    ���ܣ����������ѯ���ڵĳ���
*/
//////////////////////////////////////////////////////////////////////////

class CDistrictRgnMgr
{

public:

    enum { EINVALID_DISTID =  -1};

    CDistrictRgnMgr(void);
    ~CDistrictRgnMgr(void);



    // Public functions
public:

    BOOL  Open();

    // ���ݾ�γ�ȵõ����������������ֵ
    short  GetDistIdxByPos(DWORD dwLongi,DWORD dwLati) const;


    // Private Functions
private:

    long CalMapID(DWORD curdx,DWORD curdy) const;
    bool bGetCityID( const long x, const long y, const int niDisNumber, short& nsCityId ) const;
    bool bPointInArea( const long dCx, const long dCy, short nsPointArrCount, POINT vPointArr[] ) const;


    // Members
private:

    CString  m_strFilePath;

};

//////////////////////////////////////////////////////////////////////////