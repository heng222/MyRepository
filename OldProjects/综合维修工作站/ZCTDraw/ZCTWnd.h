#if !defined(AFX_ZCTWND_H__AFC51B94_300A_4994_9D2D_0F455A2D5CF2__INCLUDED_)
#define AFX_ZCTWND_H__AFC51B94_300A_4994_9D2D_0F455A2D5CF2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZCTWnd.h : header file

//////////////////////////////////////////////////////////////////////////

#define	 STATIONINFO_FRAME_TYPE				0x02	//ȫ��֡
#define	 STATIONCHANGE_FRAME_TYPE			0x03	//�仯֡
#define	 GUDAOLOCK_FRAME_TYPE				0x34	//�ɵ�����
#define  GUDAOALLLOCK_FRAME_TYPE			0X48	//ȫ���ɵ�����
#define  QUJIANLOCK_FRAME_TYPE				0x36	//�������
#define	 QUJIANALLLOCK_FRAME_TYPE			0X50	//ȫ���������
#define  TRAINFRAMECHANGE_FRAME_TYPE		0x05	//�仯�ĳ��ο�����
#define  TRAINFRAMEALL_FRAME_TYPE			0x52	//���ο�ȫ������
#define	 BAODIANXINXI_FRAME_TYPE			0X0C	//������Ϣ


/*
	�����湦�ܰ�ť��Ч�򵥻����ο�ʱ���򸸴��ڷ��ʹ���Ϣ��

	������wParam: StationMsgָ��
		��lParam: ������Ϣ
*/
#define		UM_FORMSTATION	(WM_USER+0x700)

/*
 *	վ��ͼ���ڲ�������Ϣ�Ľṹ
 */
struct StationMsg {
	int		iStationID;		//վ��ID	
	BYTE	byMsgType;		//��Ϣ����(���ο���Ϣ�����ܰ�ť��Ϣ��)
	int		iValueRelative;	//���IDֵ
							//byMsgTypeΪ���ο���Ϣʱ����ʾ���ο��ID,
							//byMsgTypeΪ���ܰ�ťʱ����ʾ���ܰ�ť��ID
	void*	m_pAttachValue;	//������Ϣ
	
};
enum StaMsgType { 
	MSGTYPE_FRAME	/*���ο���Ϣ*/, 
	MSGTYPE_FUNCBTN /*���ܰ�ť��Ϣ*/,
	MSGTYPE_STANCHNG/*վ��ͼ�����ر���ʾʱ*/
};

//////////////////////////////////////////////////////////////////////////

/*
 *	�����˸��ʱ��ID��ʱ��������
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
	��վ��ͼ�ࣺ
		1������վ��ʱ���������DC�ϻ���
		2������ʱ������վ�������丸�����ϻ���
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
	 *	��ʾ���
		(0XFFFFFFFF����ʾ�����豸��0�����������豸)
	 */
	enum StationShowStyle	{
		//--------
		SHOW_DIAOCHEAN = 0X00000001L /*������ť*/,	
		SHOW_LIECHEBTN = 0X00000002L /*�г���ť*/,
		SHOW_DAOCHAAN  = 0X00000004L /*����ť*/,
		SHOW_OTHERBTN  = 0X00000008L /*��ť�����г������У�������ť����������Ͱ�ť*/,
		SHOW_ALLBUTTON = 0X0000000FL /*���а�ť*/,
		//---------
		SHOW_GNENGAN   = 0X00000010L /*���ܰ�ť*/,	
		SHOW_XINHAOJI  = 0X00000020L /*�źŻ�*/,
		SHOW_PMHANZI   = 0X00000040L /*��Ļ����*/,
		SHOW_BSHIDENG  = 0X00000080L /*��ʾ��*/, 
		SHOW_XHJNAME   = 0x00000100L /*�źŻ�����*/,		
		SHOW_DCNAME	   = 0x00000200L /*��������*/,
		SHOW_WCQDNAME  = 0x00000400L /*�޲���������*/,
		SHOW_GDLIGHT   = 0X00000800L /*�ɵ�״̬��*/,
		SHOW_QJLIGHT   = 0X00001000L /*����״̬��*/, 
		SHOW_ANNAME	   = 0X00002000L /*��ť����*/,
		//---------
		SHOW_FRAMENO   = 0X00010000L /*���ο�*/,
		//---------
		SHOW_POPMENU   = 0x00020000L /*�����˵�*/
	};
	
	/*
	*  ��������
	����
	*/
	enum OperatorAttr{
		OPER_FRAMETRANO = 0X00000001 /*���ο�ɲ���*/,
		OPER_DIAOCHENAN = 0X00000002 /*������ť�ɲ���*/,
		OPER_LIECHEBTN  = 0X00000004 /*�г���ť�ɲ���*/,
		OPER_DAOCHABTN  = 0X00000008 /*����ť�ɲ���*/,
		OPER_FUNCTNBTN  = 0x00000010 /*���ܰ�ť�ɲ���*/
	};
	
	/*
	 *	��ȡģʽ
	 */
	enum __ReadMode{
		RDMD_SYARD = 0x00000001 /*��yard.dat*/,
		RDMD_MYARD = 0X00000002 /*��yard_M.dat*/,
		RDMD_MASK  = 0x00000004 /*��mask.ini*/,
		RDMD_SFRAM = 0x00000008 /*��frame.dat*/,
		RDMD_MFRAM = 0x00000010 /*��frame_M.dat*/,
		RDMD_GUDAO = 0x00000020 /*��gd.dat*/,
		RDMD_DESK  = 0x00000040 /*��desk.dat*/,
		RDMD_OFFSET= 0x00000080 /*��offset.dat*/,
		RDMD_JINLU = 0x00000100 /*��jl.ini*/
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
	

//վ������		
private:
	/*
	 *	վ��ͼ���ڻ���(m_pCanvasWnd)���߼��ߴ�
		cx: վ��ͼ���߼����
		cy: վ��ͼ���߼��߶�
	 */
	CSize	m_sLogicalCanvas;

	/*
	*	��վ��ͼʱ�Ĳο�����
		>:�ڸı�ӳ��ģʽʱʹ��
	*/
	CWnd*	m_pReferenceWnd;

	/*
	 *	վ��ͼ���ű���
		m_fStationShrink = n����ʾ�Ŵ�n����
	 */
	float	m_fStationShrink;

	/*
	 *	վ��ͼ�Ļ�������
		>: �ڵõ�DCʱʹ��
		
		��վ����������Ϊ����
		��������������ΪCZCTMultiWnd����
	 */
	CWnd*	m_pCanvasWnd;
	
	/*
	 *	վ��ͼ��Ϣ������
	 */
	HWND	m_hMsgHandle;
	
	/*
	 *	�ϲ㸽�Ӳ˵����
	 */
	HMENU	m_hPUMenu;
	/*
	 *	�ϲ㸽�Ӳ˵���Ϣ������
	 */
	HWND	m_hPMHandle;

	/*
	 *	��ʾ���(Ĭ��ȫ��ʾ0xFFFFFFFF)
	 */
	DWORD	m_dwShowStyle;
	
	/*
	 *	��������
	 */
	WORD	m_wOperatorAttr;

	/*
	 *	ӳ��ģʽ
	 */
	int		m_nMapMode;

	/*
	 *	������ʱʹ�ã������ݴ�offset.dat�ж�ȡ
	 */
	CSize	m_sizeShrink;	//վ��ͼ��ѹ������(cx��ʾX����С����,cy��ʾY����С����)
	CSize	m_sizeExcursion;//վ��ͼ��ƫ�Ƴߴ�(cx��ʾX��ƫ�Ƴߴ�,cy��ʾY��ƫ�Ƴߴ�)

	/*
		FUNC������ʶ��վ��ͼ����Ϊ��վ��ʾ�����ڴ�������ʾ
	 *	VALUE��TRUE ��ʾ��վ��FALSE ��ʾ��վ
	 */
	BOOL	m_bSingle;

	int		m_iStationNo;	//��վվ��
	CString	m_strPassword[2];//��������

//	CString		m_strCurWorkDirec;	//��ǰ������·��

	//վ����Ϣ�Ƿ���Ч������Ϣ�ж�ʱ������վ���豸����ʾ�л�ɫ���Ҳ��ɲ�����
	BOOL	m_bInfIvlid;	
	
//���������йصı���
private:

	enum _CursorPos{
		MSFL_INVALID  /*��Ч״̬*/,
		MSFL_FUNTBTN  /*���λ�ô������湦�ܰ�ť��*/,
		MSFL_GDLIGHT  /*���λ�ô��ڹɵ�״̬�����ҹɵ�������ť���ڼ���״̬*/,
		MSFL_QJLIGHT  /*���λ�ô�������״̬���������������ť���ڼ���״̬*/,
		MSFL_DLCHEAN  /*���λ�ô��ڵ�����ť���г���������ť��*/,
		MSFL_DAOCHAN  /*���λ�ô��ڵ���ť��*/,
		MSFL_WCQDNAME /*���λ�ô����޲����������������ʽⰴť���ڼ���״̬*/,
		MSFL_DCQDNAME /*���λ�ô��ڵ��������������ʽⰴť���ڼ���״̬*/
	};
	int		m_iMouseFlag;		//һ���־λ

	/*
	 *	��ʱ�豸ָ�롣
		>����m_iHandFlag��ֵ��ָ��ͬ���豸��
		m_iHandFlag == MSFL_FUNTBTNʱ�����湦�ܰ�ť��ָ��
		m_iHandFlag == MSFL_DLCHEAN��MSFL_DAOCHANʱ,���水ťָ��
		m_iHandFlag == MSFL_WCQDNAMEʱ,�����޲�����ָ��
		m_iHandFlag == MSFL_DCQDNAMEʱ,�������ť(CDCAN)ָ��
		m_iHandFlag == MSFL_GDLIGHTʱ������ɵ�״̬��ָ��
		m_iHandFlag == MSFL_QJLIGHTʱ,��������״̬��ָ��
	 */
	CBaseElement* m_pTempDevice;


	/*
	 *	���ڼ���״̬�İ�ť�б�
	 */
	CAnNList	m_AnNActiveList;
	
	/*
	 *	��һ�β����Ĺ��ܰ�ť
	 */
	CFuncBtn*	m_pFuncBtnLast;
	/*
	 *	��ǰ���ڼ���״̬�Ĺ��ܰ�ť
	 */
	CFuncBtn*	m_pFuncBtnActive;

	/*
	 *	����OnTimer������
	 */
	BOOL m_bFlashFlag;

//վ��ͼ�и��豸����
private:

	/*
	 *	�����ж϶���
	 */
	CZCTInterlockJuge	m_InterlockJuge;

	/*
		��λ
	*/
	CParseStationInfo m_ParseStaInfo;

	/*
		վ��ͼ�и���ʾ����Ĵ洢����
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
	 *	ͨ����ť�õ���·����2
	 */
	int GetJLProAccordBtn(const WORD* pBtnList,const int& iBtnNum);

	/*
	 *	�õ������޲����ε�����
		[out]sNameList: ������������
	 */
	void GetWcQdNameList(CStringList& sNameList);
	/*
	 *	���ݰ�ť���Ƶõ�ID
	 */
	int GetBtnIDByName(CString strName);
	/*
	 *	���ݰ�ťID�õ�����
	 */
	CString GetBtnNameByID(int iCommandID);
	/*
	 *	�����޲��������Ƶõ�ID
	 */
	int GetWcQdIDByName(CString strName);
	/*
	 *	�����޲�����ID�õ�����
	 */
	CString GetWcQdNameByID(int iIndex);

public:
	
	/*
	 *	����վ��ͼ�����˵�
	 */
	void SetPopupMenu(HMENU hMenu,HWND hMsgHandle);
	
	
	/*
	 *	����վ��ͼ�·�񣬷��ؾɷ��
	 */
	DWORD SetZCTStyle(DWORD dwNewStyle,BOOL bRedraw = TRUE);
	/*
	 *	�õ�վ��ͼ��ǰ����ʾ���
	 */
	DWORD GetZCTStyle(){return m_dwShowStyle;}

	/*
	 *	����վ��ͼ�µ�ӳ��ģʽ���������ӳ��ģʽ
	 */
	int SetZCTMapMode( int nNewMapMode);
	/*
	 *	�õ�վ��ͼ��ǰ��ӳ��ģʽ
	 */
	int GetZCTMapMode(){return m_nMapMode;}

	/*
	 *	���ò�������
	 */
	WORD SetOperAttri(WORD wNewAttri);
	/*
	 *	�õ���������
	 */
	WORD GetOperAttri() { return m_wOperatorAttr;}

	/*
	 *	�����߼��ߴ�
	 */
	void SetLogicSize(CSize sNewSize) {m_sLogicalCanvas = sNewSize;}

	/*
	*  ��ӡ
	*/
	void PrintZCT(CPoint ptOrigin,CSize SizeZoom);


	/*
	 *	���ݶ�ȡģʽ��ȡվ��ͼ��������
	 */
	BOOL ReadStationInf(CString strPath,int iReadMode = RDMD_SYARD|RDMD_SFRAM);

	/*
	���ͷ���Դ
	*/
	void DeleteObject();

	/*
	 *	����վ����վ��
	 */
	int GetStationID() const {return m_iStationNo;}
	/*
	 *	����վ��ͼID
	 */
	void SetStationID(int iStationID) {m_iStationNo = iStationID;}

	/*
	 *	������Ϣ�Ƿ���Ч(����Ϣ�ж�ʱ����)
		TRUE����վ���豸��Ч��ȫ�Ի�ɫ�����ɲ���
		FALSE������Ч
	 */
	BOOL InvalidateInf(BOOL bFlag);

	/*
	 	pReferWnd:  ��վ��ͼʱ�Ĳο�����(һ��ΪCView����)
		pCanvasWnd: վ��ͼ���ڻ�������(��վΪ������վΪCZCTMultiWnd����)
		hMsgHandle: վ��ͼ��Ϣ������(��������վ��ͼ��������Ϣ����Ϊ��)
	 */
	BOOL Create(CWnd* pReferWnd,CWnd* pCanvasWnd=NULL,HWND hMsgHandle=NULL);

	/*
	 *	�����վ��ͼ�йص���Ϣ֡��EX��ȫ��֡���仯֡������֡�ȣ�
	 */
	void OnReceiveInf(LPBYTE pInfBuf);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZCTWnd)
	protected:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL


//�յ���Ϣ֡ʱ�Ĵ���	
protected:			
	/*
		FUNC:��վ��ͼ
	*/
	void DrawZCT(CDC* pDC = NULL);

	/*
	 *	���»����е���������ƻ��ǹɵ������Ƶķ���״̬
	 */
	void UpdateQjStatus(int iYHH, int iXHNo, int iQjStatus);
	void UpdateGdStatus(int iGdNo, int iGdStatus);
	
	/*
	 *	����վ��ͼ��������
	 */
	BOOL UpdateZCTSource(LPBYTE pBuffer);
	BOOL UpdateZCTStatus(LPBYTE pBuffer,WORD);

	/*
	 *	�����յ���֡���͸���վ��ͼ��ʾ
	     iFrameType:֡����
	 */
	void UpdateZCT (int iFrameType,CDC* pDC = NULL);

private:
	int GetWcQdValidNums();//�õ��޲����ε���Ч������Index�ظ�����һ����
	void DrawActiveBtn(CDC* pDC,BOOL bShow);//�����ڼ���״̬�İ�ť����Ӧ���źŻ�
	void DrawQGJ(CDC* pDC,BOOL bIsQGJ=TRUE);//���ʽ�ʱʹ��
	void initialization(BOOL bShow = TRUE);//�л�վ��ͼʱʹ��
	inline char* fgetline(char* strLine,int n,FILE* fp);
	inline void ltrim(char* str);	
	void SetRWCBand(short iDC,BYTE btClr,BOOL bIsSet);	
    void RemoveJCHWBand();
		

	/*
	 *	����վ��ͼ���ڵ��ض�Device Context
		pDC:	�豸����
	 */
	void SetDeviceContext(CDC* pDC);

	
	/*
	 *	�ɰ�ť�ҵ���Ӧ���źŻ�
	 */
	CXinHJ* GetXHJByAn(CAnN* pAnN);
	/*
	 *	�ɵ����ҵ���Ӧ�ĵ���ť
	 */
	CAnN*	GetBtnByDC(CDaoC* pDaoC);
	
	/*
	 *	��ǰ��ʾ��״̬�Ƿ�Ϊ����ģʽ
	 */
	BOOL	IsZLMode();
	
	/*
	 *	��⵱ǰ����Ƿ�������iFlagָ�����豸��
	 */
	BOOL	PtInDevices(CDC* pDC,CPoint pt,int iFlag);


	/*
		����Ӧ�������ļ�
	*/
	BOOL ReadGd(CString strFileName);//�ɵ���������ʾ��
	BOOL ReadYard(CString strFileName);//վ����ʾ
	BOOL ReadDesk(CString strFileName);//���湦�ܰ�ť
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
