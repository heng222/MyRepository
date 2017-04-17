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
	 *	更新车次框内容与方向
	 */
	void UpdateFrameInf(int iFrameID,CString strInf,int iDirection=0);
	/*
	 *	更新车次框方向与早晚点信息
	 */
	void UpadateTimeExcur(int iFrameID,int iDirection,int iTimeExcur=0);


	/*
	 *	通过与车次框相关连的区段ID返回车次框的内容
	 */
	CString GetContBySectRel(int iSectRelID);
	/*
	 *	通过与车次框相关连的区段ID返回车次框的ID
	 */
	int GetFrameIDBySectRel(int iSectRelID);
	

	/*
	 *	清除所有车次框内容
	 */
	void ClearFrameContent();
	void ShowFrames(CDC* pDC,int nCmdShow );
	
	void ClearList();
	/*
	 *	从配置文件中读取车次框的有关数据
	 */
	BOOL ReadFrameInf(CString strFileName,CSize sizeShrink = CSize(1,1),CSize sizeExcursion = CSize(0,0));
	
	/*
	 *bEnable:指示创建的车次框可否操作	
	 */
	BOOL CreateFrames(CWnd* pParentWnd);

	
	CFrameTrainNoList();
	virtual ~CFrameTrainNoList();

private:
	

private:

	//总共的车次框数目
	//int		m_nFrameNumber;

};

#endif // !defined(AFX_FRAMETRAINNOLIST_H__4D35A0A3_D56A_46F8_AA8B_DF21CD6D5DBF__INCLUDED_)
