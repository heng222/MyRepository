#pragma once

#include "afx.h"
#include "NBMapWnd.h"
#include "TfcInfMgr.h"
#include "DlgRoadAttri.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

// CTfcInfView

class CTfcInfView : public CNBMapWnd
{
	DECLARE_DYNAMIC(CTfcInfView)

public:
	CTfcInfView();
	virtual ~CTfcInfView();


    RETRIEVE_SELF_ENGINE(CTfcInfMgr)

    void ShowTipInf(BOOL bErase=FALSE);

    enum 
    {
        EPER_SELECTION = EPER_RESERVED+1,
    };

    // From CNBMapWnd
    virtual void OnDraw(CDC* pDC,CNBMapEngine* pEngine);
    virtual void PreContextMenu(CMenu& aMenu);
    virtual void OnStateChanged(int aNewState,int aOldState);

protected:
	DECLARE_MESSAGE_MAP()


    CMenu   m_Menu;

    BOOL    m_bShowNodeName;

    CToolTipCtrl m_tipCtrl;

    CDlgRoadAttri   m_dlgRoadAttri;


    CPoint      m_ptCurrent;

public:
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnTfcroadParse();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnTfcroadNodename();
    afx_msg void OnTfcroadSelectroad();
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
};


