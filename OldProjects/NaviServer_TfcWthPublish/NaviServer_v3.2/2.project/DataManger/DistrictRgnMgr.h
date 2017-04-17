#pragma once

#include <Geometry.h>

//////////////////////////////////////////////////////////////////////////
/*
    区域管理器(依赖文件MapCity.can)，用于气象查询

    功能：根据坐标查询所在的城市
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

    // 根据经纬度得到其所在区域的索引值
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