// MainUIView.h : CMainUIView ��Ľӿ�
//


#pragma once

#include <SortListCtrl.h>
class CMainUIDoc;

class CLogView : public CView
{
protected: // �������л�����
	CLogView();
	DECLARE_DYNCREATE(CLogView)

// ����
public:
    CMainUIDoc* GetDocument() const;
    CSortListCtrl m_ctrlList;

// ����
public:
    void AddLiveLog(PIMsgAppLogs pNewLog);

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CLogView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
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

#ifndef _DEBUG  // MainUIView.cpp �ĵ��԰汾
inline CMainUIDoc* CLogView::GetDocument() const
   { return reinterpret_cast<CMainUIDoc*>(m_pDocument); }
#endif

