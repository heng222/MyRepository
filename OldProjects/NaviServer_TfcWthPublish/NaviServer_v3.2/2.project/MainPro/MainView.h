#pragma once

#include "MainSheet.h"

// CMainView ��ͼ

class CMainView : public CView
{
	DECLARE_DYNCREATE(CMainView)

protected:
	CMainView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMainView();

public:
	virtual void OnDraw(CDC* pDC);      // ��д�Ի��ƴ���ͼ
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

    virtual void OnInitialUpdate();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    
    enum {EOriginHeight=480};   // ��ʼ�߶�
    enum {EMinHeight = 300};    // ��С�߶�
    enum {EMinWidth = 300};     // ��С���

protected:
	DECLARE_MESSAGE_MAP()

private:
    CMainSheet  m_mainSheet;

    // New public functions
public:
    void    AddNewLogs(PIMsgAppLogs pNewLog);
    void    ActivePage(CMainSheet::TPageName nPagename);
    void    ActivePage(int iIdx);
    int     GetPageCount() const;
    void    SetActivedFldID(int aProType,DWORD dwID);
    
};


