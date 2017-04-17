#pragma once

#include "afx.h"
#include "NBMapWnd.h"
#include "TfcInfMgr.h"

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



    // From CNBMapWnd
    virtual void OnDraw(CDC* pDC,CNBMapEngine* pEngine);
    virtual void PreContextMenu(CMenu& aMenu);
    virtual void OnStateChanged(TOperateState aNewState,TOperateState aOldState);

protected:
	DECLARE_MESSAGE_MAP()


    CMenu   m_Menu;

    BOOL    m_bShowNodeName;

    CToolTipCtrl m_tipCtrl;

    PTTfcEventAttri m_pActiveEvent;

    CPoint  m_ptCurrent;

public:
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg void OnPopmenuFlash();
    afx_msg void OnPopmenuNodename();
    afx_msg void OnPopmenuTfcevent();
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnPopmenuAutoflash();
};


