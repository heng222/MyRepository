#pragma once

#include "InterfaceEx.h"

// CSelectionTreeView 视图

class CSelectionTreeView : public CTreeView
{
	DECLARE_DYNCREATE(CSelectionTreeView)

protected:
	CSelectionTreeView();           // 动态创建所使用的受保护的构造函数
	virtual ~CSelectionTreeView();

public:
    
    // Tree's attribute.
    enum TTreeAttri
    {
        ETA_OriginalWidth = 200,
        ETA_MinHeight = 450,
        ETA_MinWidth = 100,
    };


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


protected:
	DECLARE_MESSAGE_MAP()


protected:
    virtual void OnInitialUpdate();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
    afx_msg void OnTvnSelchanged(NMHDR *pNMHDR, LRESULT *pResult);


    // New Private members
private:
    CImageList m_imageList;
    HTREEITEM m_hBalanceServer;
    HTREEITEM m_hSpServer;
    HTREEITEM m_hMobiles_Bin ;
    HTREEITEM m_hMobiles_Char;
    //HTREEITEM m_hWthInf;

    TV_INSERTSTRUCT m_hInsertTvStruc;

    // New public functions
public:

    HTREEITEM FindItem(HTREEITEM hRootItem,LPARAM lParam);
    void AddNewLogs(PIMsgAppLogs pNewLog);
};


