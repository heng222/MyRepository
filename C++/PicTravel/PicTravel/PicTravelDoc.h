// PicTravelDoc.h : CPicTravelDoc ��Ľӿ�
//


#pragma once


class CPicTravelDoc : public CDocument
{
protected: // �������л�����
	CPicTravelDoc();
	DECLARE_DYNCREATE(CPicTravelDoc)

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
	virtual ~CPicTravelDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


