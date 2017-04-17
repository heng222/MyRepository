#if !defined(AFX_ZCTMAG1_H__69CAF701_A208_462C_BD01_636BAA67FB81__INCLUDED_)
#define AFX_ZCTMAG1_H__69CAF701_A208_462C_BD01_636BAA67FB81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCTMag.h : header file
//

//-------------------------------------------
#include "ZCTSingleWnd.h"
#include "ZCTMultiWnd.h"
#include "ReadStationInf.h"
//-------------------------------------------
/*
	站场图管理类，可以显示一个站或多个站
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
	 *	FUNC：收到状态帧时更新各LIST中的内容
		pBuffer:　	与站场图变化相关的内容
	 */
	void OnReceive(BYTE *pBuffer);

	
	/*
	 *	
	 */
	void ClearStaList();

	/*
	 *	读数据
	 iReadMode:　读取模式
	 iStatioNo:　模式为终端时有效，指终端车站的站码。
	 */
	enum StationType
	{	MODE_KONGZHI		/*控制工作站*/,
		MODE_ZHUDIAO		/*助调工作站*/,
		MODE_ZONGHEWEIXIU	/*综合维修工作站*/,
		MODE_DIANWUWEIHU	/*电务维护工作站*/,
		MODE_DAPING			/*大屏工作站*/,
		//------------------
		MODE_ZILVJI			/*自律机*/,
		//-----------------
		MODE_CHEWUZONGDUAN		/*车务终端*/,
		MODE_WEIXIUZONGDUAN		/*维修终端*/,
		MODE_WEIHUZONGDUAN		/*电务维护终端*/,

		//-------------------------------
		MODE_JIANCEZHANJI			/*监测站机*/,
		MODE_JIANCEZONGDUAN			/*监测终端*/

	};//车站类型

	BOOL ReadStationInf(int iReadMode,CString strPath="");
	
	/*
	 *	iStationNo：站码，小于0时，画所有站。
	 */
	void DrawStation(int iStationNo = -1);


// Operations
public:
	int GetJLProAccordBtn(const WORD wStationID,const WORD *pBtnList, const int &iBtnNum);
	void SetPopupMenu(HMENU hMenu,HWND hMsgHandle);
	/*
	 *	隐藏站场图
		bSingle: 为TRUE时隐藏所有单站，为FALSE时隐藏大屏
	 */
	void HideStation(BOOL bSingle);

	/*
	 *	
	 */
	void GetWcQdNameList(int iStationID,CStringList &sNameList);
	
	/*
	 *	判断进路是否存在
	 */

	/*
	 *	根据按钮的ID或名称得到其名称或ID
	 */
	CString GetBtnNameByID(int iStationID,int iCommandID);
	int GetBtnIDbyName(int iStationID,CString strName);

	/*
	 *
	 功能：	根据站码、无岔区段名字找到其序号
	 参数:	iStationID 站码
			strWcQdName 无岔区段名字
	 */
	int GetWcQdIDByName(int iStationID, CString strWcQdName);

	/*
	 *
	 功能：	根据站码、无岔区段序号找到其名字
	 参数:	iStationID 站码
			iWcQdID 无岔区段序号
	 */
	CString GetWcQDNameByID(int iStationID,int iWcQdID);
	
	
	void InvalidateInf(BOOL bNewFlag);


private:

	/*
	 *	单站场图数据
	 */
	CZCTSingleWnd	m_SingleStationWnd;


	/*
	 *	多站场图
	 */
	CZCTMultiWnd	m_MultiStationWnd;

	/*
		当前程序所在路径
	*/
	//CString			m_strExePath;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCTMAG1_H__69CAF701_A208_462C_BD01_636BAA67FB81__INCLUDED_)
