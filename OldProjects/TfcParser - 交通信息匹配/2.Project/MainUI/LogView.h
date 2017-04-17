#pragma once

#include <SortListCtrl.h>

// CLogView ��ͼ
class CMainUIDoc;

class CLogView : public CView
{
	DECLARE_DYNCREATE(CLogView)

protected:
	CLogView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CLogView();
    CSortListCtrl m_ctrlList;


public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��ƴ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


    CMainUIDoc* GetDocument() const;

    void AddLiveLog(PIMsgAppLogs pNewLog);

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg void OnLogDeletesel();
    afx_msg void OnLogClear();
};
#ifndef _DEBUG  // MainUIView.cpp �ĵ��԰汾
inline CMainUIDoc* CLogView::GetDocument() const
{ return reinterpret_cast<CMainUIDoc*>(m_pDocument); }
#endif

