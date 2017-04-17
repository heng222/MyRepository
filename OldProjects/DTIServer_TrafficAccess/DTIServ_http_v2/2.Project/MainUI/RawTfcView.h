#pragma once


// RawTfcView 视图

class CRawTfcView : public CView
{
	DECLARE_DYNCREATE(CRawTfcView)

protected:
	CRawTfcView();           // 动态创建所使用的受保护的构造函数
	virtual ~CRawTfcView();

public:
	virtual void OnDraw(CDC* pDC);      // 重写以绘制此视图
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
};


