// GDI+SampleView.h : CGDISampleView ��Ľӿ�
//


#pragma once


class CGDISampleView : public CView
{
protected: // �������л�����
	CGDISampleView();
	DECLARE_DYNCREATE(CGDISampleView)

// ����
public:
	CGDISampleDoc* GetDocument() const;

// ����
public:

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
	virtual ~CGDISampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnDrawline();
public:
	afx_msg void OnRectangle();
public:
	afx_msg void OnDrawstring();
public:
	afx_msg void OnShadowfont();
public:
	afx_msg void OnBubbleSurround();
public:
	afx_msg void OnEmboss();
public:
    afx_msg void OnOutline();
public:
    afx_msg void OnWarped();
public:
    afx_msg void OnBlock();
public:
    afx_msg void OnOutglowing();
public:
    afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
public:
    afx_msg void OnClippath();
    afx_msg void OnDrawimage();
};

#ifndef _DEBUG  // GDI+SampleView.cpp �еĵ��԰汾
inline CGDISampleDoc* CGDISampleView::GetDocument() const
   { return reinterpret_cast<CGDISampleDoc*>(m_pDocument); }
#endif

