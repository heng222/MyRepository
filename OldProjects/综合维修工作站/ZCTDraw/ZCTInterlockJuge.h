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
 *	�������������ж��ܷ����н�·
 */

class CZCTInterlockJuge : public CObject  
{
	friend class CZCTWnd;

protected:
	void SetInf(CZCTWnd* pParentObt);
	CZCTInterlockJuge();
	virtual ~CZCTInterlockJuge();

	
	/*
	*	�жϽ�·�Ƿ����
		[out]strCause:���޷���·��ԭ��
		[out]strFrameContent: �����г���·ʱ������صĳ��ο�����
		[in] iBtnType: ���ܰ�ť���ͣ����Ž�·�����н�·��
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
	 *	������(��������Դ)
	 */
	CZCTWnd*	m_pParentObject;

	/*
	 *	��·�ļ�����Ŀ¼
	 */
	//CString		m_strJLFilePath;
	/*
	 *	��Ÿ���������н�·��Ϣ
	 */
	CEntRailway	m_EntRailWay;
	CPasRailway m_PasRailWay;
};

#endif // !defined(AFX_ZCTINTERLOCKJUGE_H__6BC7E8D2_0151_41B1_B92E_0BF11CBC0401__INCLUDED_)
