#pragma once

#include "afx.h"

#include "NBMapWnd.h"

#include "DistrictMgr.h"


// CRegionView

class CDistrictView : public CNBMapWnd
{
	DECLARE_DYNAMIC(CDistrictView)

public:

	CDistrictView();
	virtual ~CDistrictView();

    RETRIEVE_SELF_ENGINE(CBJDistrictMgr)

protected:
	DECLARE_MESSAGE_MAP()

    void ShowTipInf(BOOL bErase=FALSE);

    // From CNBMapWnd
    //virtual void PreInitMapengine(TEgAttri& ea);
    virtual void OnDraw(CDC* pDC,CNBMapEngine* pEngine);
    virtual void PreContextMenu(CMenu& aMenu);
    virtual void OnStateChanged(int aNewState,int aOldState);

private:

    TDistrict*  m_pActiveDistrict;

    CMenu m_Menu;

    CToolTipCtrl m_tipCtrl;

    BOOL m_bInfTip;

    CPoint m_ptCurrent;


public:
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnMapoperInfPrompt();
    afx_msg void OnMapoperWthinf();
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg void OnWthmenuFlashweather();
};


