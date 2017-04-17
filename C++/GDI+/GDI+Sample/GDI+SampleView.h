// GDI+SampleView.h : CGDISampleView 类的接口
//


#pragma once


class CGDISampleView : public CView
{
protected: // 仅从序列化创建
	CGDISampleView();
	DECLARE_DYNCREATE(CGDISampleView)

// 属性
public:
	CGDISampleDoc* GetDocument() const;

// 操作
public:

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
	virtual ~CGDISampleView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
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

#ifndef _DEBUG  // GDI+SampleView.cpp 中的调试版本
inline CGDISampleDoc* CGDISampleView::GetDocument() const
   { return reinterpret_cast<CGDISampleDoc*>(m_pDocument); }
#endif

