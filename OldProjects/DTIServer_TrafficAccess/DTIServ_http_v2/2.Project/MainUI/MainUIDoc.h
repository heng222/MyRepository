// MainUIDoc.h :  CMainUIDoc ��Ľӿ�
//


#pragma once

#include "LogView.h"

class CMainUIDoc : public CDocument
{
protected: // �������л�����
	CMainUIDoc();
	DECLARE_DYNCREATE(CMainUIDoc)

// ����
public:

// ����
public:

// ��д
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMainUIDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


