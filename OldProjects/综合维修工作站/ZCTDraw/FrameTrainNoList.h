// FrameTrainNoList.h: interface for the CFrameTrainNoList class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRAMETRAINNOLIST_H__4D35A0A3_D56A_46F8_AA8B_DF21CD6D5DBF__INCLUDED_)
#define AFX_FRAMETRAINNOLIST_H__4D35A0A3_D56A_46F8_AA8B_DF21CD6D5DBF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FrameTrainNo.h"

class CFrameTrainNoList : public CObList  
{
public:
	CString GetContByID(int iFrameID);
	void InvalidateInf(BOOL bInfInvalid);
	
	/*
	 *	���³��ο������뷽��
	 */
	void UpdateFrameInf(int iFrameID,CString strInf,int iDirection=0);
	/*
	 *	���³��ο������������Ϣ
	 */
	void UpadateTimeExcur(int iFrameID,int iDirection,int iTimeExcur=0);


	/*
	 *	ͨ���복�ο������������ID���س��ο������
	 */
	CString GetContBySectRel(int iSectRelID);
	/*
	 *	ͨ���복�ο������������ID���س��ο��ID
	 */
	int GetFrameIDBySectRel(int iSectRelID);
	

	/*
	 *	������г��ο�����
	 */
	void ClearFrameContent();
	void ShowFrames(CDC* pDC,int nCmdShow );
	
	void ClearList();
	/*
	 *	�������ļ��ж�ȡ���ο���й�����
	 */
	BOOL ReadFrameInf(CString strFileName,CSize sizeShrink = CSize(1,1),CSize sizeExcursion = CSize(0,0));
	
	/*
	 *bEnable:ָʾ�����ĳ��ο�ɷ����	
	 */
	BOOL CreateFrames(CWnd* pParentWnd);

	
	CFrameTrainNoList();
	virtual ~CFrameTrainNoList();

private:
	

private:

	//�ܹ��ĳ��ο���Ŀ
	//int		m_nFrameNumber;

};

#endif // !defined(AFX_FRAMETRAINNOLIST_H__4D35A0A3_D56A_46F8_AA8B_DF21CD6D5DBF__INCLUDED_)
