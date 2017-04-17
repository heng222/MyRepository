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

    TMRect          m_boxRect;           // �������Ӿ���
    TMPoint         m_ptCenter;          // ��������ĵ�
    CString         m_strDistName;
    CString         m_strIDistID;

    CMPointArray    m_ptLogicalPosArray; // ������߼���������
    CArray<CPoint,CPoint> m_ptDevicePtArray; // 

    CWthInfList     m_WthInfList;       // ��ص�������Ϣ

public:
    TDistrict()
    {
        m_iState = EDS_NORMAL;
        m_strDistName = "������";
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
//  �����и��������������������ļ�RegionCode.txt�����������ѯ
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

    // ���ݾ�γ�ȵõ��������
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

    void TransferLogicalPtsToDevicePts(); // ��������߼�����ת��Ϊ�豸����

private:

    CDistrictList m_DistrictList;
    COleDateTime  m_timeUpdate;

};


//////////////////////////////////////////////////////////////////////////
#endif