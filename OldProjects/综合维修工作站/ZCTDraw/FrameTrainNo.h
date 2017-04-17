#if !defined(AFX_FRAMETRAINNO_H__AA1CC2CF_1D7D_40BD_9E4C_F628FEDCBC98__INCLUDED_)
#define AFX_FRAMETRAINNO_H__AA1CC2CF_1D7D_40BD_9E4C_F628FEDCBC98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameTrainNo.h : header file
#include "Color.h"
//
#define	UM_LBTNDOWN_ONFRAME (WM_USER+500)	//车次框左键按下消息(由车次框发向其父窗口)

// CFrameTrainNo window
#define	RELSECTMAXNUM	5	//与车次框相关的区段的最大数目


/////////////////////////////////////////////////////////////////////////////
//frame color definition
#define	CLRBKGDTRUCK	WHITECOLOR		//货车车次框底色
#define	CLRTEXTTRUCK	BLUECOLOR		//货车车次文字颜色
#define	CLRBKGDPAGCAR	WHITECOLOR		//客车车次框底色
#define	CLRTEXTPAGCAR	REDCOLOR		//客车车次文字颜色

//早晚点颜色定义
#define	CLRBKGDLATEALL	BLUECOLOR		//(客货车)晚点背景色
#define CLRTEXTLATEALL	WHITECOLOR		//(客货车)晚点文字颜色

#define	CLRBKGDEARLYTK	REDCOLOR		//客车早点背景色
#define	CLRTEXTEARLYTK	WHITECOLOR		//客车早点文字颜色
#define CLRBKGDEARLYPG	BLACKCOLOR		//货车早点背景色
#define CLRTEXTEARLYPG	BLACKCOLOR		//货车早点文字颜色

#define CLRSHARPALL		BLACKCOLOR		//正点时背景与文字颜色

//信息无效时的背景色与文字颜色定义
#define	CLRBKGDINVALID	LIGHTGRAY
#define	CLRTEXTINVALID	WHITECOLOR

//////////////////////////////////////////////////////////////////////////
class CFrameTrainNo : public CWnd
{
	DECLARE_SERIAL(CFrameTrainNo)
		
	friend class CFrameTrainNoList;
// Construction
public:
	CFrameTrainNo();

// Attributes
public:
	enum FrameDirection//车次方向
	{
		FD_IVALID	= 0 /*未知*/,
		FD_UP		= 2	/*上行*/,
		FD_DOWN		= 1	/*下行*/
	};
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFrameTrainNo)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	/*
	 *	得到早晚点信息框，文字显示框、整个背景框区域
	 注：不需要相关的信息时，可带NULL为参数
	 */
	void GetRectangle(CRect* pRtTime,CRect* pRtText,CRgn* pRgBack);
	/*
	 *	使信息无效
	 TRUE:	信息无效
	 FALSE:　信息有效
	 */
	void InvalidInf(BOOL bInvalid);
	/*
	 *	
	 */
	void SetTimeExcur(int iNewExcur,BOOL bRedraw= TRUE);
	void SetDirection(int iDirection,BOOL bRedraw= TRUE);
	void UpdateContent(CString strInf,BOOL bRedraw= TRUE);

	CString GetContent() const;

	/*
	 *	根据父窗口的设备场景，重新计算车次框所有的位置并显示出来
	 */
	void RecalcLayout(CDC* pDC);

	BOOL CreateFrame(CWnd* pParentWnd);
	int GetFrameID() const;
	virtual ~CFrameTrainNo();

	// Generated message map functions
protected:
	/*
	 *	重画自身
	 */
	void ReDrawSlf();
	//{{AFX_MSG(CFrameTrainNo)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	CToolTipCtrl	m_tipCtrl;

private:
	BOOL		m_bInfIvlid;	//信息是否无效
//-------------------------------------------------------
	CPoint		m_pointPos;		//车次框左上角座标
	CSize		m_size;			//车次框大小
	int			m_iFrameID;		//车次框ID
	CString		m_strContent;	//车次框中的内容
//--------------------------------------------------------
	int			m_iSectRelNum;				//与车次框相关的区段的数目
	int			m_iSectRelID[RELSECTMAXNUM];//与车次框相关的区段的ID

	//CString		m_strSectionName;	//与车次框相关的区段名称
//--------------------------------------------------------
	int			m_iDirection;		//车次框方向(1下行<箭头向右>，2上行<箭头向左>)
	int			m_iTimeExcur;		//早晚点时间差(早点为负值，晚点为正值)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMETRAINNO_H__AA1CC2CF_1D7D_40BD_9E4C_F628FEDCBC98__INCLUDED_)
