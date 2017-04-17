#pragma once

#include "MainSheet.h"

// CMainView 视图

class CMainView : public CView
{
	DECLARE_DYNCREATE(CMainView)

protected:
	CMainView();           // 动态创建所使用的受保护的构造函数
	virtual ~CMainView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制此视图
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

    virtual void OnInitialUpdate();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    
    enum {EOriginHeight=480};   // 起始高度
    enum {EMinHeight = 300};    // 最小高度
    enum {EMinWidth = 300};     // 最小宽度

protected:
	DECLARE_MESSAGE_MAP()

private:
    CMainSheet  m_mainSheet;

    // New public functions
public:
    void    AddNewLogs(PIMsgAppLogs pNewLog);
    void    ActivePage(CMainSheet::TPageName nPagename);
    void    ActivePage(int iIdx);
    int     GetPageCount() const;
    void    SetActivedFldID(int aProType,DWORD dwID);
    
};


