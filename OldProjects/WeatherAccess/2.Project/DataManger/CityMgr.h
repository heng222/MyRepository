#pragma once

#include "afx.h"
#include "InterfaceEx.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// 读取配置文件(Citys.txt)中所有省份及其城市的有关信息
//  
// 

class CCityMgr :   public CObject
{
public:

    CCityMgr(void);
    ~CCityMgr(void);

    // New member functions
public:

    BOOL    ReadInf();
    void    ClearList();
    void    GetCityInf(CCityList*& cityList);

    PTCityStruton GetCityByIndex(WORD wCityIdx,const CCityList* pStartAfter=NULL) const;
    PTCityStruton GetCityByCode(const CString& strCode,const CCityList* pStartAfter=NULL) const;
    PTCityStruton GetCityByName(const CString& strName,const CCityList* pStartAfter=NULL) const;

    // Member variables
private:

    CCityList       m_CityList;

};




















