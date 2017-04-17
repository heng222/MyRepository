#if !defined(AFX_FRAMETRAINNO_H__AA1CC2CF_1D7D_40BD_9E4C_F628FEDCBC98__INCLUDED_)
#define AFX_FRAMETRAINNO_H__AA1CC2CF_1D7D_40BD_9E4C_F628FEDCBC98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FrameTrainNo.h : header file
#include "Color.h"
//
#define	UM_LBTNDOWN_ONFRAME (WM_USER+500)	//���ο����������Ϣ(�ɳ��ο����丸����)

// CFrameTrainNo window
#define	RELSECTMAXNUM	5	//�복�ο���ص����ε������Ŀ


/////////////////////////////////////////////////////////////////////////////
//frame color definition
#define	CLRBKGDTRUCK	WHITECOLOR		//�������ο��ɫ
#define	CLRTEXTTRUCK	BLUECOLOR		//��������������ɫ
#define	CLRBKGDPAGCAR	WHITECOLOR		//�ͳ����ο��ɫ
#define	CLRTEXTPAGCAR	REDCOLOR		//�ͳ�����������ɫ

//�������ɫ����
#define	CLRBKGDLATEALL	BLUECOLOR		//(�ͻ���)��㱳��ɫ
#define CLRTEXTLATEALL	WHITECOLOR		//(�ͻ���)���������ɫ

#define	CLRBKGDEARLYTK	REDCOLOR		//�ͳ���㱳��ɫ
#define	CLRTEXTEARLYTK	WHITECOLOR		//�ͳ����������ɫ
#define CLRBKGDEARLYPG	BLACKCOLOR		//������㱳��ɫ
#define CLRTEXTEARLYPG	BLACKCOLOR		//�������������ɫ

#define CLRSHARPALL		BLACKCOLOR		//����ʱ������������ɫ

//��Ϣ��Чʱ�ı���ɫ��������ɫ����
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
	enum FrameDirection//���η���
	{
		FD_IVALID	= 0 /*δ֪*/,
		FD_UP		= 2	/*����*/,
		FD_DOWN		= 1	/*����*/
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
	 *	�õ��������Ϣ��������ʾ����������������
	 ע������Ҫ��ص���Ϣʱ���ɴ�NULLΪ����
	 */
	void GetRectangle(CRect* pRtTime,CRect* pRtText,CRgn* pRgBack);
	/*
	 *	ʹ��Ϣ��Ч
	 TRUE:	��Ϣ��Ч
	 FALSE:����Ϣ��Ч
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
	 *	���ݸ����ڵ��豸���������¼��㳵�ο����е�λ�ò���ʾ����
	 */
	void RecalcLayout(CDC* pDC);

	BOOL CreateFrame(CWnd* pParentWnd);
	int GetFrameID() const;
	virtual ~CFrameTrainNo();

	// Generated message map functions
protected:
	/*
	 *	�ػ�����
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
	BOOL		m_bInfIvlid;	//��Ϣ�Ƿ���Ч
//-------------------------------------------------------
	CPoint		m_pointPos;		//���ο����Ͻ�����
	CSize		m_size;			//���ο��С
	int			m_iFrameID;		//���ο�ID
	CString		m_strContent;	//���ο��е�����
//--------------------------------------------------------
	int			m_iSectRelNum;				//�복�ο���ص����ε���Ŀ
	int			m_iSectRelID[RELSECTMAXNUM];//�복�ο���ص����ε�ID

	//CString		m_strSectionName;	//�복�ο���ص���������
//--------------------------------------------------------
	int			m_iDirection;		//���ο���(1����<��ͷ����>��2����<��ͷ����>)
	int			m_iTimeExcur;		//�����ʱ���(���Ϊ��ֵ�����Ϊ��ֵ)
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FRAMETRAINNO_H__AA1CC2CF_1D7D_40BD_9E4C_F628FEDCBC98__INCLUDED_)
