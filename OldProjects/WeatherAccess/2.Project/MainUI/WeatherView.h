#pragma once


// CWeatherView ��ͼ

class CWeatherView : public CView
{
	DECLARE_DYNCREATE(CWeatherView)

protected:
	CWeatherView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CWeatherView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��ƴ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnSize(UINT nType, int cx, int cy);
};


