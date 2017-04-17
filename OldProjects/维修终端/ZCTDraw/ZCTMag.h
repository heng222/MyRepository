#if !defined(AFX_ZCTMAG1_H__69CAF701_A208_462C_BD01_636BAA67FB81__INCLUDED_)
#define AFX_ZCTMAG1_H__69CAF701_A208_462C_BD01_636BAA67FB81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCTMag.h : header file
//

//-------------------------------------------
#include "ZCTWnd.h"
#include "ZCTMultiWnd.h"
#include "ReadStationInf.h"
//-------------------------------------------
/*
	վ��ͼ�����࣬������ʾһ��վ����վ
*/
/////////////////////////////////////////////////////////////////////////////
// CZCTMag command target

class AFX_EXT_CLASS CZCTMag : public CObject
{

// Attributes
public:
	
	CZCTMag();           
	virtual ~CZCTMag();

public:

	/*
	 *	
	 */
	void Create(CWnd *pParentWnd,HWND hMsgHandle,BOOL bSingle = FALSE);

	/*
	 *	FUNC���յ�״̬֡ʱ���¸�LIST�е�����
		pBuffer:��	��վ��ͼ�仯��ص�����
	 */
	void OnReceive(BYTE *pBuffer);


	/*
	 *	FUNC������վ��õ�վ��ͼ��ָ��
	 */
	CZCTWnd* GetZCTbyNo(int iStationNo);

	
	/*
	 *	
	 */
	void ClearStaList();

	/*
	 *	������
	 iReadMode:����ȡģʽ
	 iStatioNo:��ģʽΪ�ն�ʱ��Ч��ָ�ն˳�վ��վ�롣
	 */
	enum StationType
	{	MODE_KONGZHI		/*���ƹ���վ*/,
		MODE_ZHUDIAO		/*��������վ*/,
		MODE_ZONGHEWEIXIU	/*�ۺ�ά�޹���վ*/,
		MODE_DIANWUWEIHU	/*����ά������վ*/,
		MODE_DAPING			/*��������վ*/,
		//------------------
		MODE_ZILVJI			/*���ɻ�*/,
		//-----------------
		MODE_CHEWUZONGDUAN		/*�����ն�*/,
		MODE_WEIXIUZONGDUAN		/*ά���ն�*/,
		MODE_WEIHUZONGDUAN		/*����ά���ն�*/,

		//-------------------------------
		MODE_JIANCE			/*���*/
	};//��վ����

	BOOL ReadStationInf(int iReadMode/*,int iStationNo = -1*/);
	
	/*
	 *	iStationNo��վ�룬С��0ʱ��������վ��
	 */
	void DrawStation(int iStationNo = -1);


// Operations
public:
	void SetPopupMenu(HMENU hMenu,HWND hMsgHandle);
	/*
	 *	����վ��ͼ
		bSingle: ΪTRUEʱ�������е�վ��ΪFALSEʱ���ش���
	 */
	void HideStation(BOOL bSingle);

	/*
	 *	
	 */
	void GetWcQdNameList(int iStationID,CStringList &sNameList);
	
	/*
	 *	�жϽ�·�Ƿ����
	 */

	/*
	 *	���ݰ�ť��ID�����Ƶõ������ƻ�ID
	 */
	CString GetBtnNameByID(int iStationID,int iCommandID);
	int GetBtnIDbyName(int iStationID,CString strName);

	/*
	 *
	 ���ܣ�	����վ�롢�޲����������ҵ������
	 ����:	iStationID վ��
			strWcQdName �޲���������
	 */
	int GetWcQdIDByName(int iStationID, CString strWcQdName);

	/*
	 *
	 ���ܣ�	����վ�롢�޲���������ҵ�������
	 ����:	iStationID վ��
			iWcQdID �޲��������
	 */
	CString GetWcQDNameByID(int iStationID,int iWcQdID);
	
	
	void InvalidateInf(BOOL bNewFlag);
	int GetZCTMapMode(int iStationID = -1);

	/*
	 *	����ָ��վ��DC��ӳ��ģʽ
		
	 */
	void SetZCTMapMode(int nMapMode,int iStationID = -1);

	/*
	 *	
	 */
	DWORD GetZCTStyle(int iStationID=-1);
	void SetZCTStyle(DWORD dwStyle,int iStationID=-1);

private:

//	CWnd		m_MultiStationWnd;
	/*
	 *	��վ��ͼ����
	 */
	CZCTWndList		m_SingleStaList;

	/*
	 *	��վ��ͼ����
	 */
//	CZCTWndList		m_MultiStaList;

	/*
	 *	��վ��ͼ
	 */
	CZCTMultiWnd	m_MultiStationWnd;

	/*
		��ǰ��������·��
	*/
	CString			m_strExePath;

	////////////
	static int m_iObjectNum;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCTMAG1_H__69CAF701_A208_462C_BD01_636BAA67FB81__INCLUDED_)
