#pragma once


// CParsedTfcView ��ͼ

class CParsedTfcView : public CView
{
	DECLARE_DYNCREATE(CParsedTfcView)

protected:
	CParsedTfcView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CParsedTfcView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��ƴ���ͼ
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


