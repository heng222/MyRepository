// GDI+SampleDoc.h : CGDISampleDoc ��Ľӿ�
//


#pragma once


class CGDISampleDoc : public CDocument
{
protected: // �������л�����
	CGDISampleDoc();
	DECLARE_DYNCREATE(CGDISampleDoc)

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
	virtual ~CGDISampleDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


