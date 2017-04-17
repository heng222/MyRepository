// PicTravelView.h : CPicTravelView 类的接口
//


#pragma once


class CPicTravelView : public CView
{
protected: // 仅从序列化创建
	CPicTravelView();
	DECLARE_DYNCREATE(CPicTravelView)

private:

    CDC m_dcPic, m_dcCache;

    // 
    CBitmap m_bmpPic, m_bmpCache;

    // 
    BITMAP m_bmp;

    // 
    int m_xPos, m_yPos;

    bool m_xIncrease, m_yIncrease;

    void UpdatePosition();

// 属性
public:
	CPicTravelDoc* GetDocument() const;

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
    virtual void OnInitialUpdate();

// 实现
public:
	virtual ~CPicTravelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnSize(UINT nType, int cx, int cy);

};

#ifndef _DEBUG  // PicTravelView.cpp 中的调试版本
inline CPicTravelDoc* CPicTravelView::GetDocument() const
   { return reinterpret_cast<CPicTravelDoc*>(m_pDocument); }
#endif

