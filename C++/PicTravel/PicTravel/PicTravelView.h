// PicTravelView.h : CPicTravelView ��Ľӿ�
//


#pragma once


class CPicTravelView : public CView
{
protected: // �������л�����
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

// ����
public:
	CPicTravelDoc* GetDocument() const;

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
    virtual void OnInitialUpdate();

// ʵ��
public:
	virtual ~CPicTravelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:


// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnTimer(UINT_PTR nIDEvent);
    afx_msg void OnSize(UINT nType, int cx, int cy);

};

#ifndef _DEBUG  // PicTravelView.cpp �еĵ��԰汾
inline CPicTravelDoc* CPicTravelView::GetDocument() const
   { return reinterpret_cast<CPicTravelDoc*>(m_pDocument); }
#endif

