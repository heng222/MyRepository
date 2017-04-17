#pragma once

#include "afx.h"
#include "NBMapWnd.h"
#include "TfcParsedMgr.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

// CTfcParsedView

class CTfcParsedView : public CNBMapWnd
{
	DECLARE_DYNAMIC(CTfcParsedView)

public:

	CTfcParsedView();
	virtual ~CTfcParsedView();


    RETRIEVE_SELF_ENGINE(CTfcParsedMgr)

    void ShowTipInf(BOOL bErase=FALSE);

    // From CNBMapWnd
    virtual void OnDraw(CDC* pDC,CNBMapEngine* pEngine);
    virtual void PreContextMenu(CMenu& aMenu);
    virtual void OnStateChanged(TOperateState aNewState,TOperateState aOldState);

protected:

	DECLARE_MESSAGE_MAP()


    CMenu   m_Menu;


    CToolTipCtrl m_tipCtrl;
    CPoint m_ptCurrent;


public:
    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnTfcFlash();
    afx_msg void OnTfcManuflash();
};


