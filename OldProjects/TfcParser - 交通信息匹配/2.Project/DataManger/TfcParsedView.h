#pragma once

#include "afx.h"
#include "NBMapWnd.h"
#include "TfcParsedMgr.h"
#include "DlgLinkAttri.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

// CTfcParsedView

class CTfcParsedView : public CNBMapWnd
{
	DECLARE_DYNAMIC(CTfcParsedView)

public:

	CTfcParsedView();
	virtual ~CTfcParsedView();

    // Menu ID
    enum
    {

    };

    // 
    enum 
    {
        EPER_SELECTION = EPER_RESERVED+1,
    };

    // Show style
    enum
    {
        ES_TFCNODE =  0x00000001,   // 显示节点
        ES_NODENAME = 0x00000002,   // 显示节点名称
        ES_LINKDIRE = 0x00000004,   // Link方向
    };

    RETRIEVE_SELF_ENGINE(CTfcParsedMgr)

    void ShowTipInf(BOOL bErase=FALSE);

    // From CNBMapWnd
    virtual void OnMenuOperation(UINT nID);
    virtual void OnDraw(CDC* pDC,CNBMapEngine* pEngine);
    virtual void PreContextMenu(CMenu& aMenu);
    virtual void OnStateChanged(int aNewState,int aOldState);

protected:

	DECLARE_MESSAGE_MAP()


    CMenu   m_Menu;


    CToolTipCtrl m_tipCtrl;

    DWORD   m_wStyle;

    CPoint  m_ptCurrent;


public:

    afx_msg void OnTimer(UINT nIDEvent);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    virtual BOOL PreTranslateMessage(MSG* pMsg);
    afx_msg void OnLinkSelection();
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLinkTfcnode();
    afx_msg void OnLinkNodename();
    afx_msg void OnLinkDirection();
};


