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
	DWORD				dwOrder;			//调度命令号
	CString				strStationName;		//受令站名字
	COleDateTime		tTime;				//回执时间
	CString				strReceiver;		//回执人

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
	DWORD m_dwResNum;				//链表中回执信息的个数
	CString m_strPathName;		//文件路径
	ResponseNode* m_pHead;		//头指针
};

#endif // !defined(AFX_READRESPONSE_H__772D2E5E_07B9_4697_A639_1110F4F90921__INCLUDED_)
