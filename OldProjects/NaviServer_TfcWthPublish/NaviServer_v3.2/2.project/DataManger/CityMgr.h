#pragma once

#include "afx.h"
#include "InterfaceEx.h"

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

// ��ȡ�����ļ�(Citys.txt)������ʡ�ݼ�����е��й���Ϣ
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




















