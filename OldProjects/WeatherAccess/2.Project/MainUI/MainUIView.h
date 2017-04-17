// MainUIView.h : CMainUIView 类的接口
//


#pragma once

class CMainUIDoc;

#include <SortListCtrl.h>


class CMainUIView : public CView
{
protected: // 仅从序列化创建
	CMainUIView();
	DECLARE_DYNCREATE(CMainUIView)

// 属性
public:
	CMainUIDoc* GetDocument() const;

// 操作
public:
    void AddLiveLog(PIMsgAppLogs pNewLog);

// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMainUIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

    CSortListCtrl m_ctrlList;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
    virtual void OnInitialUpdate();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
    afx_msg void OnLogDeletesel();
    afx_msg void OnLogClear();
};

#ifndef _DEBUG  // MainUIView.cpp 的调试版本
inline CMainUIDoc* CMainUIView::GetDocument() const
   { return reinterpret_cast<CMainUIDoc*>(m_pDocument); }
#endif

