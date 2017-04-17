// ReadResponse.h: interface for the CReadResponse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READRESPONSE_H__772D2E5E_07B9_4697_A639_1110F4F90921__INCLUDED_)
#define AFX_READRESPONSE_H__772D2E5E_07B9_4697_A639_1110F4F90921__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//-------------------------------------
struct ResponseNode
{
	DWORD				dwOrder;			//���������
	CString				strStationName;		//����վ����
	COleDateTime		tTime;				//��ִʱ��
	CString				strReceiver;		//��ִ��

	ResponseNode* Next;		//
};
class CReadResponse : public CObject  
{
public:
	void Add(DWORD dwOrder,CString strStationName,COleDateTime resTime,CString sRever);
	DWORD GetLength();
	ResponseNode* GetAt(const DWORD& iIndex);
	void ClearList();
	BOOL WriteFile(CString strPathName="");
	void Add(const ResponseNode& item);
	BOOL ReadFile(CString strPathName = "");
	CReadResponse();
	virtual ~CReadResponse();

private:
	DWORD m_dwResNum;				//�����л�ִ��Ϣ�ĸ���
	CString m_strPathName;		//�ļ�·��
	ResponseNode* m_pHead;		//ͷָ��
};

#endif // !defined(AFX_READRESPONSE_H__772D2E5E_07B9_4697_A639_1110F4F90921__INCLUDED_)
