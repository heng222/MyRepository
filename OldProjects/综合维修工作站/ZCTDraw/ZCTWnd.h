#if !defined(AFX_ZCTWND_H__AFC51B94_300A_4994_9D2D_0F455A2D5CF2__INCLUDED_)
#define AFX_ZCTWND_H__AFC51B94_300A_4994_9D2D_0F455A2D5CF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCTWnd.h : header file

//////////////////////////////////////////////////////////////////////////

#define	 STATIONINFO_FRAME_TYPE				0x02	//全场帧
#define	 STATIONCHANGE_FRAME_TYPE			0x03	//变化帧
#define	 GUDAOLOCK_FRAME_TYPE				0x34	//股道封锁
#define  GUDAOALLLOCK_FRAME_TYPE			0X48	//全部股道封锁
#define  QUJIANLOCK_FRAME_TYPE				0x36	//区间封锁
#define	 QUJIANALLLOCK_FRAME_TYPE			0X50	//全部区间封锁
#define  TRAINFRAMECHANGE_FRAME_TYPE		0x05	//变化的车次框内容
#define  TRAINFRAMEALL_FRAME_TYPE			0x52	//车次框全部内容
#define	 BAODIANXINXI_FRAME_TYPE			0X0C	//报点信息


/*
	当桌面功能按钮有效或单击车次框时，向父窗口发送此消息。

	参数：wParam: StationMsg指针
		　lParam: 附加信息
*/
#define		UM_FORMSTATION	(WM_USER+0x700)

/*
 *	站场图窗口产生的消息的结构
 */
struct StationMsg {
	int		iStationID;		//站场ID	
	BYTE	byMsgType;		//消息类型(车次框消息、功能按钮消息等)
	int		iValueRelative;	//相关ID值
							//byMsgType为车次框消息时，表示车次框的ID,
							//byMsgType为功能按钮时，表示功能按钮的ID
	void*	m_pAttachValue;	//附加信息
	
};
enum StaMsgType { 
	MSGTYPE_FRAME	/*车次框消息*/, 
	MSGTYPE_FUNCBTN /*功能按钮消息*/,
	MSGTYPE_STANCHNG/*站场图由隐藏变显示时*/
};

//////////////////////////////////////////////////////////////////////////

/*
 *	组件闪烁计时器ID及时间间隔定义
 */
#define		ID_CLOCK_BTNFLASH	10 
#define		TIMERBTNFSHELAPSE	500


/////////////////////////////////////////////////////////////////////////////

#define MAXDC		100  /* dao cha */
#define MAXJCHW     15  /* jiao cha huan wei */

/////////////////////////////////////////////////////////////////////////////
#include "XinHJ.h"
#include "WcQD.h"
#include "JYJ.h"
#include "NQD.h"
#include "JT.h"
#include "DaoC.h"
#include "HanZ.h"
#include "AnN.h"
#include "DCAN.h"
#include "BSD.h"
#include "FuncBtn.h"
#include "GdStatus.h"
#include "QjStatus.h"
#include "FrameTrainNoList.h"
#include "ParseStationInfo.h"
#include "ZCTInterlockJuge.h"
#include "ReadStationInf.h"
#include "PassWordDlg.h"
//----------------------------------------------------------

/*
	画站场图类：
		1、单个站场时，在自身的DC上画。
		2、大屏时，所有站场均在其父窗口上画。
*/
class AFX_EXT_CLASS CZCTWnd : public CWnd
{
	friend class CZCTInterlockJuge;
	friend class CZCTMultiWnd;
	friend class CParseStationInfo;
public:
	CZCTWnd();
	virtual ~CZCTWnd();

	DECLARE_DYNCREATE(CZCTWnd)

// Attributes
public:
	/*
	 *	显示风格
		(0XFFFFFFFF：显示所有设备；0：隐藏所有设备)
	 */
	enum StationShowStyle	{
		//--------
		SHOW_DIAOCHEAN = 0X00000001L /*调车按钮*/,	
		SHOW_LIECHEBTN = 0X00000002L /*列车按钮*/,
		SHOW_DAOCHAAN  = 0X00000004L /*道岔按钮*/,
		SHOW_OTHERBTN  = 0X00000008L /*按钮链表中除调，列，引导按钮外的其余类型按钮*/,
		SHOW_ALLBUTTON = 0X0000000FL /*所有按钮*/,
		//---------
		SHOW_GNENGAN   = 0X00000010L /*功能按钮*/,	
		SHOW_XINHAOJI  = 0X00000020L /*信号机*/,
		SHOW_PMHANZI   = 0X00000040L /*屏幕汉字*/,
		SHOW_BSHIDENG  = 0X00000080L /*表示灯*/, 
		SHOW_XHJNAME   = 0x00000100L /*信号机名称*/,		
		SHOW_DCNAME	   = 0x00000200L /*道岔名称*/,
		SHOW_WCQDNAME  = 0x00000400L /*无岔区段名称*/,
		SHOW_GDLIGHT   = 0X00000800L /*股道状态灯*/,
		SHOW_QJLIGHT   = 0X00001000L /*区间状态灯*/, 
		SHOW_ANNAME	   = 0X00002000L /*按钮名称*/,
		//---------
		SHOW_FRAMENO   = 0X00010000L /*车次框*/,
		//---------
		SHOW_POPMENU   = 0x00020000L /*弹出菜单*/
	};
	
	/*
	*  操作属性
	　　
	*/
	enum OperatorAttr{
		OPER_FRAMETRANO = 0X00000001 /*车次框可操作*/,
		OPER_DIAOCHENAN = 0X00000002 /*调车按钮可操作*/,
		OPER_LIECHEBTN  = 0X00000004 /*列车按钮可操作*/,
		OPER_DAOCHABTN  = 0X00000008 /*道岔按钮可操作*/,
		OPER_FUNCTNBTN  = 0x00000010 /*功能按钮可操作*/
	};
	
	/*
	 *	读取模式
	 */
	enum __ReadMode{
		RDMD_SYARD = 0x00000001 /*读yard.dat*/,
		RDMD_MYARD = 0X00000002 /*读yard_M.dat*/,
		RDMD_MASK  = 0x00000004 /*读mask.ini*/,
		RDMD_SFRAM = 0x00000008 /*读frame.dat*/,
		RDMD_MFRAM = 0x00000010 /*读frame_M.dat*/,
		RDMD_GUDAO = 0x00000020 /*读gd.dat*/,
		RDMD_DESK  = 0x00000040 /*读desk.dat*/,
		RDMD_OFFSET= 0x00000080 /*读offset.dat*/,
		RDMD_JINLU = 0x00000100 /*读jl.ini*/
	};


private:	
	/**/
	DCQDMAP			DCQDMap[MAXDC];
	JCHW			JCHW[MAXJCHW];
	
	/**/
	int iDCQDMaps,/*iDCNums,*//*iWCQDNums,*//*iJYJNums,*/
		/*iNQDNums,iJTNums,*//*iHZNums,*/
		/*iDCDevOffset,iDCANNums,*//*iBSDNums,*/
		LXNums,DXNums,iJCHWNums/*,iFuncBtnNums*/;
	

//站场属性		
private:
	/*
	 *	站场图所在画布(m_pCanvasWnd)的逻辑尺寸
		cx: 站场图的逻辑宽度
		cy: 站场图的逻辑高度
	 */
	CSize	m_sLogicalCanvas;

	/*
	*	画站场图时的参考窗口
		>:在改变映射模式时使用
	*/
	CWnd*	m_pReferenceWnd;

	/*
	 *	站场图缩放比例
		m_fStationShrink = n，表示放大n倍，
	 */
	float	m_fStationShrink;

	/*
	 *	站场图的画布窗口
		>: 在得到DC时使用
		
		单站：画布窗口为自身
		大屏：画布窗口为CZCTMultiWnd对象
	 */
	CWnd*	m_pCanvasWnd;
	
	/*
	 *	站场图消息处理句柄
	 */
	HWND	m_hMsgHandle;
	
	/*
	 *	上层附加菜单句柄
	 */
	HMENU	m_hPUMenu;
	/*
	 *	上层附加菜单消息处理句柄
	 */
	HWND	m_hPMHandle;

	/*
	 *	显示风格(默认全显示0xFFFFFFFF)
	 */
	DWORD	m_dwShowStyle;
	
	/*
	 *	操作属性
	 */
	WORD	m_wOperatorAttr;

	/*
	 *	映射模式
	 */
	int		m_nMapMode;

	/*
	 *	画大屏时使用，其数据从offset.dat中读取
	 */
	CSize	m_sizeShrink;	//站场图的压缩比例(cx表示X轴缩小倍数,cy表示Y轴缩小倍数)
	CSize	m_sizeExcursion;//站场图的偏移尺寸(cx表示X轴偏移尺寸,cy表示Y轴偏移尺寸)

	/*
		FUNC：　标识本站场图是作为单站显示还是在大屏上显示
	 *	VALUE：TRUE 表示单站，FALSE 表示多站
	 */
	BOOL	m_bSingle;

	int		m_iStationNo;	//本站站码
	CString	m_strPassword[2];//两级密码

//	CString		m_strCurWorkDirec;	//当前程序工作路径

	//站场信息是否无效（当信息中断时，所有站场设备都显示有灰色，且不可操作）
	BOOL	m_bInfIvlid;	
	
//与鼠标操作有关的变量
private:

	enum _CursorPos{
		MSFL_INVALID  /*无效状态*/,
		MSFL_FUNTBTN  /*鼠标位置处于桌面功能按钮里*/,
		MSFL_GDLIGHT  /*鼠标位置处于股道状态灯里且股道封锁按钮处于激活状态*/,
		MSFL_QJLIGHT  /*鼠标位置处于区间状态灯里且区间封锁按钮处于激活状态*/,
		MSFL_DLCHEAN  /*鼠标位置处于调车按钮或列车或引导按钮里*/,
		MSFL_DAOCHAN  /*鼠标位置处于道岔按钮里*/,
		MSFL_WCQDNAME /*鼠标位置处于无岔区段名称里且区故解按钮处于激活状态*/,
		MSFL_DCQDNAME /*鼠标位置处于道岔名称里且区故解按钮处于激活状态*/
	};
	int		m_iMouseFlag;		//一组标志位

	/*
	 *	临时设备指针。
		>根据m_iHandFlag的值，指向不同的设备。
		m_iHandFlag == MSFL_FUNTBTN时，保存功能按钮的指针
		m_iHandFlag == MSFL_DLCHEAN或MSFL_DAOCHAN时,保存按钮指针
		m_iHandFlag == MSFL_WCQDNAME时,保存无岔区段指针
		m_iHandFlag == MSFL_DCQDNAME时,保存道岔按钮(CDCAN)指针
		m_iHandFlag == MSFL_GDLIGHT时，保存股道状态灯指针
		m_iHandFlag == MSFL_QJLIGHT时,保存区间状态灯指针
	 */
	CBaseElement* m_pTempDevice;


	/*
	 *	处于激活状态的按钮列表
	 */
	CAnNList	m_AnNActiveList;
	
	/*
	 *	上一次操作的功能按钮
	 */
	CFuncBtn*	m_pFuncBtnLast;
	/*
	 *	当前处于激活状态的功能按钮
	 */
	CFuncBtn*	m_pFuncBtnActive;

	/*
	 *	用在OnTimer函数里
	 */
	BOOL m_bFlashFlag;

//站场图中各设备数据
private:

	/*
	 *	联锁判断对象
	 */
	CZCTInterlockJuge	m_InterlockJuge;

	/*
		码位
	*/
	CParseStationInfo m_ParseStaInfo;

	/*
		站场图中各显示对象的存储链表
	*/
	CDaoCList		m_DCList;
	CXinHJList		m_XHJList;
	CWcQDList		m_WcQDList;
	CJYJList		m_JYJList;
	CNQDList		m_NQDList;
	CJTList			m_JTList;
	CHanZList		m_HZList;
	CAnNList		m_ANList;
	CDCANList		m_DCANList;
	CBSDList		m_BSDList;
	CFuncBtnList		m_FuncBtnList;
	CGdStatusList		m_GdStatusList;
	CQjStatusList		m_QjStatusList;
	CFrameTrainNoList	m_FrameTrainNoList;


// Operations
public:

	/*
	 *	通过按钮得到进路性质2
	 */
	int GetJLProAccordBtn(const WORD* pBtnList,const int& iBtnNum);

	/*
	 *	得到所有无岔区段的名称
		[out]sNameList: 返回名字链表
	 */
	void GetWcQdNameList(CStringList& sNameList);
	/*
	 *	根据按钮名称得到ID
	 */
	int GetBtnIDByName(CString strName);
	/*
	 *	根据按钮ID得到名称
	 */
	CString GetBtnNameByID(int iCommandID);
	/*
	 *	根据无岔区段名称得到ID
	 */
	int GetWcQdIDByName(CString strName);
	/*
	 *	根据无岔区段ID得到名称
	 */
	CString GetWcQdNameByID(int iIndex);

public:
	
	/*
	 *	设置站场图弹出菜单
	 */
	void SetPopupMenu(HMENU hMenu,HWND hMsgHandle);
	
	
	/*
	 *	设置站场图新风格，返回旧风格
	 */
	DWORD SetZCTStyle(DWORD dwNewStyle,BOOL bRedraw = TRUE);
	/*
	 *	得到站场图当前的显示风格
	 */
	DWORD GetZCTStyle(){return m_dwShowStyle;}

	/*
	 *	设置站场图新的映射模式，返回其旧映射模式
	 */
	int SetZCTMapMode( int nNewMapMode);
	/*
	 *	得到站场图当前的映射模式
	 */
	int GetZCTMapMode(){return m_nMapMode;}

	/*
	 *	设置操作属性
	 */
	WORD SetOperAttri(WORD wNewAttri);
	/*
	 *	得到操作属性
	 */
	WORD GetOperAttri() { return m_wOperatorAttr;}

	/*
	 *	设置逻辑尺寸
	 */
	void SetLogicSize(CSize sNewSize) {m_sLogicalCanvas = sNewSize;}

	/*
	*  打印
	*/
	void PrintZCT(CPoint ptOrigin,CSize SizeZoom);


	/*
	 *	根据读取模式读取站场图所需数据
	 */
	BOOL ReadStationInf(CString strPath,int iReadMode = RDMD_SYARD|RDMD_SFRAM);

	/*
	　释放资源
	*/
	void DeleteObject();

	/*
	 *	返回站场的站码
	 */
	int GetStationID() const {return m_iStationNo;}
	/*
	 *	设置站场图ID
	 */
	void SetStationID(int iStationID) {m_iStationNo = iStationID;}

	/*
	 *	设置信息是否无效(当信息中断时调用)
		TRUE：　站场设备无效，全显灰色，不可操作
		FALSE：　有效
	 */
	BOOL InvalidateInf(BOOL bFlag);

	/*
	 	pReferWnd:  画站场图时的参考窗口(一般为CView对象)
		pCanvasWnd: 站场图所在画布窗口(单站为自身，多站为CZCTMultiWnd对象)
		hMsgHandle: 站场图消息处理句柄(若不处理站场图产生的消息，则为空)
	 */
	BOOL Create(CWnd* pReferWnd,CWnd* pCanvasWnd=NULL,HWND hMsgHandle=NULL);

	/*
	 *	处理跟站场图有关的信息帧（EX：全场帧、变化帧，车次帧等）
	 */
	void OnReceiveInf(LPBYTE pInfBuf);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZCTWnd)
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL


//收到信息帧时的处理	
protected:			
	/*
		FUNC:画站场图
	*/
	void DrawZCT(CDC* pDC = NULL);

	/*
	 *	更新缓冲中的区间封锁灯或是股道封锁灯的封锁状态
	 */
	void UpdateQjStatus(int iYHH, int iXHNo, int iQjStatus);
	void UpdateGdStatus(int iGdNo, int iGdStatus);
	
	/*
	 *	更新站场图缓冲数据
	 */
	BOOL UpdateZCTSource(LPBYTE pBuffer);
	BOOL UpdateZCTStatus(LPBYTE pBuffer,WORD);

	/*
	 *	根据收到的帧类型更新站场图显示
	     iFrameType:帧类型
	 */
	void UpdateZCT (int iFrameType,CDC* pDC = NULL);

private:
	int GetWcQdValidNums();//得到无岔区段的有效个数（Index重复的算一个）
	void DrawActiveBtn(CDC* pDC,BOOL bShow);//画处于激活状态的按钮与相应的信号机
	void DrawQGJ(CDC* pDC,BOOL bIsQGJ=TRUE);//区故解时使用
	void initialization(BOOL bShow = TRUE);//切换站场图时使用
	inline char* fgetline(char* strLine,int n,FILE* fp);
	inline void ltrim(char* str);	
	void SetRWCBand(short iDC,BYTE btClr,BOOL bIsSet);	
    void RemoveJCHWBand();
		

	/*
	 *	设置站场图所在的特定Device Context
		pDC:	设备场景
	 */
	void SetDeviceContext(CDC* pDC);

	
	/*
	 *	由按钮找到相应的信号机
	 */
	CXinHJ* GetXHJByAn(CAnN* pAnN);
	/*
	 *	由道岔找到相应的道岔按钮
	 */
	CAnN*	GetBtnByDC(CDaoC* pDaoC);
	
	/*
	 *	当前表示灯状态是否为自律模式
	 */
	BOOL	IsZLMode();
	
	/*
	 *	检测当前鼠标是否落在由iFlag指定的设备中
	 */
	BOOL	PtInDevices(CDC* pDC,CPoint pt,int iFlag);


	/*
		读相应的配置文件
	*/
	BOOL ReadGd(CString strFileName);//股道、区间显示灯
	BOOL ReadYard(CString strFileName);//站场显示
	BOOL ReadDesk(CString strFileName);//桌面功能按钮
	BOOL ReadOffset(CString strFileName);//


// Implementation
protected:

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

	// Generated message map functions
protected:

	//{{AFX_MSG(CZCTWnd)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	afx_msg LRESULT OnMsgFromFrameNo( WPARAM wParam, LPARAM lParam );
	afx_msg void OnPopMenu(UINT nID);
	afx_msg void OnUpdateDeviceName(CCmdUI* pCmdUI);

	
	DECLARE_MESSAGE_MAP()
};

typedef CTypedPtrList<CObList,CZCTWnd*> CZCTWndList;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZCTWND_H__AFC51B94_300A_4994_9D2D_0F455A2D5CF2__INCLUDED_)
