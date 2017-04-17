#ifndef _DISTRICT_MANAGER_FILE_H
#define _DISTRICT_MANAGER_FILE_H

//////////////////////////////////////////////////////////////////////////
#include "afx.h"
#include <UserColors.h>
#include <Geometry.h>
#include <NBMapEngine.h>
#include "DataModulInterface.h"

//////////////////////////////////////////////////////////////////////////
// 
class TDistrict 
{
public:
    enum TState
    {
        EDS_NORMAL,
        EDS_ACTIVE,
    };

    TState          m_iState;

    TMRect          m_boxRect;           // 区域的外接矩形
    TMPoint         m_ptCenter;          // 区域的中心点
    CString         m_strDistName;
    CString         m_strIDistID;

    CMPointArray    m_ptLogicalPosArray; // 区域的逻辑坐标数组
    CArray<CPoint,CPoint> m_ptDevicePtArray; // 

    CWthInfList     m_WthInfList;       // 相关的气象信息

public:
    TDistrict()
    {
        m_iState = EDS_NORMAL;
        m_strDistName = "行政区";
    }
    ~TDistrict()
    {
        ClearWthList();
    }
    void ClearWthList()
    {
        while (m_WthInfList.GetHeadPosition())
        {
            delete m_WthInfList.RemoveHead();
        }
    }

public:


};
typedef CTypedPtrList<CPtrList,TDistrict*> CDistrictList;
//////////////////////////////////////////////////////////////////////////
//
//  北京市各行政区管理器，依赖文件RegionCode.txt，用于气象查询
// 
//
class CBJDistrictMgr :public CNBMapEngine
{
public:

    CBJDistrictMgr(void);
    ~CBJDistrictMgr(void);

public:

    BOOL   ReadRgnData();

    void   Close();

    // 根据经纬度得到区域编码
    BOOL    GetDistIDByPos(const TMPoint& ptPos,CString& strAreaID) const;
    TDistrict* GetDistrict(const TMPoint& aPt) const;
    TDistrict* GetDistrict(const CPoint& aPt) const;

    COleDateTime GetFlashTime() const;

private:

    // From CNBMapEngine
    BOOL OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid);
	void OnActivedRectChanged(const CGridList& listGrid);
    void OnRotatingRadiansChanged(float aNewRotating);


private:

    void TransferLogicalPtsToDevicePts(); // 将区域的逻辑坐标转换为设备坐标

private:

    CDistrictList m_DistrictList;
    COleDateTime  m_timeUpdate;

};


//////////////////////////////////////////////////////////////////////////
#endif