// ZCTInterlockJuge.h: interface for the CZCTInterlockJuge class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ZCTINTERLOCKJUGE_H__6BC7E8D2_0151_41B1_B92E_0BF11CBC0401__INCLUDED_)
#define AFX_ZCTINTERLOCKJUGE_H__6BC7E8D2_0151_41B1_B92E_0BF11CBC0401__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "EntRailway.h"
#include "PasRailway.h"
#include "AnN.h"

/*
 *	根据联锁条件判断能否排列进路
 */

class CZCTInterlockJuge : public CObject  
{
	friend class CZCTWnd;

protected:
	void SetInf(CZCTWnd* pParentObt);
	CZCTInterlockJuge();
	virtual ~CZCTInterlockJuge();

	
	/*
	*	判断进路是否存在
		[out]strCause:　无法排路的原因
		[out]strFrameContent: 排列列车进路时返回相关的车次框内容
		[in] iBtnType: 功能按钮类型（试排进路、排列进路）
	*/
	virtual BOOL IsExistER(CString& strCause,CString& strFrameContent,int iBtnType);

private:
	/*
	 *	
	 */
	BOOL WcQDIsUsableness(WORD,CString&);
	/*
	 *	
	 */
	BOOL DaoCIsUsableness(WORD,BOOL,CString&,BOOL bQud=FALSE);
	/*
	 *	
	 */
	BOOL EnemySignalIsUsableness(CString&,WORD,BOOL);
	/*
	 *	
	 */
	BOOL GuDaoCloseoffIsUsableness(CString&,WORD);
	/*
	 *	
	 */
	BOOL QuJianCloseoffIsUsableness(CString&,WORD);
	//
private:
	/*
	 *	父对象(即数据来源)
	 */
	CZCTWnd*	m_pParentObject;

	/*
	 *	进路文件所在目录
	 */
	//CString		m_strJLFilePath;
	/*
	 *	存放父对象的所有进路信息
	 */
	CEntRailway	m_EntRailWay;
	CPasRailway m_PasRailWay;
};

#endif // !defined(AFX_ZCTINTERLOCKJUGE_H__6BC7E8D2_0151_41B1_B92E_0BF11CBC0401__INCLUDED_)
