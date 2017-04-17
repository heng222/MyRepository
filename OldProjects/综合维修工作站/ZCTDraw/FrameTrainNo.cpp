// FrameTrainNo.cpp : implementation file
//

#include "stdafx.h"
#include <MATH.H>
#include "FrameTrainNo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IMPLEMENT_SERIAL(CFrameTrainNo,CWnd,1)
/////////////////////////////////////////////////////////////////////////////

#define  FRAMENO_CLR	WHITECOLOR	//���κ���ɫ
#define  FRAMERECT_NT	DEEPGRAY	//�޳���ʱ�ı߿���ɫ


//���κŴ���TRUCKTRAINNONUMʱΪ����
#ifdef _DEBUG
	#define  TRUCKTRAINNONUM	2			
#else
	#define  TRUCKTRAINNONUM	5
#endif


// CFrameTrainNo
CFrameTrainNo::CFrameTrainNo():m_bInfIvlid(FALSE),
		m_iDirection(FD_IVALID),m_iTimeExcur(0)
{
}

CFrameTrainNo::~CFrameTrainNo()
{
}


BEGIN_MESSAGE_MAP(CFrameTrainNo, CWnd)
	//{{AFX_MSG_MAP(CFrameTrainNo)
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFrameTrainNo message handlers


void CFrameTrainNo::OnLButtonUp(UINT nFlags, CPoint point) 
{
#ifdef _DEBUG
	m_iDirection == FD_DOWN ? m_iDirection = FD_UP : m_iDirection = FD_DOWN;
	m_iTimeExcur = -(m_iTimeExcur-3);
	ReDrawSlf();
#endif
	
	//���������ο�ʱ���丸���ڷ��Զ�����Ϣ
	GetParent()->PostMessage(UM_LBTNDOWN_ONFRAME,WPARAM(this),0);
	
	// TODO: Add your message handler code here and/or call default
	CWnd::OnLButtonUp(nFlags, point);
}

int CFrameTrainNo::GetFrameID() const
{
	return m_iFrameID;
}

void CFrameTrainNo::OnLButtonDown(UINT nFlags, CPoint point) 
{
/*	if (!m_bCanOper || m_bInfIvlid) {
		CWnd::OnLButtonDown(nFlags, point);
		return;
	}
	SetCapture();
	//
	char cTemp[MAX_PATH];
	CString strExePath;

	//ȷ��ϵͳ��ǰ·��
	GetCurrentDirectory(MAX_PATH,cTemp);
	strExePath.Format("%s\\",cTemp);

	SetCursor(AfxGetApp()->LoadCursor(IDC_LBTN_DOWN));
*/	
	// TODO: Add your message handler code here and/or call default
	CWnd::OnLButtonDown(nFlags, point);
}

void CFrameTrainNo::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_strContent.IsEmpty()) {
		CString strDirection;
		if (m_iDirection == FD_UP) {
			strDirection = "����";
		}
		else if (m_iDirection == FD_DOWN) {
			strDirection = "����";
		}

		//
		CString strTrain;
		if (m_strContent.GetLength() > TRUCKTRAINNONUM) {
			strTrain.Format("����%s",m_strContent);
		}
		else{
			strTrain.Format("�ͳ�%s",m_strContent);
		}
		
		//
		CString strInf;
		if (m_iTimeExcur<0) {
			strInf.Format(",���%d����",abs(m_iTimeExcur));
		}
		else if (m_iTimeExcur>0){	
			strInf.Format(",���%d����",abs(m_iTimeExcur));
		}
		
		
		m_tipCtrl.UpdateTipText(strDirection + strTrain + strInf,this);
	}
	
	
	//// TODO: Add your message handler code here and/or call default
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CFrameTrainNo::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
/*	
	if (m_bCanOper && !m_bInfIvlid) {
		char cTemp[MAX_PATH];
		CString strExePath;
		
		//ȷ��ϵͳ��ǰ·��
		GetCurrentDirectory(MAX_PATH,cTemp);
		strExePath.Format("%s\\",cTemp);
		SetCursor(AfxGetApp()->LoadCursor(IDC_LBTN_UP));
		return TRUE;
	}
	else{
		return CWnd::OnSetCursor(pWnd, nHitTest, message);
	}
*/
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

BOOL CFrameTrainNo::CreateFrame(CWnd *pParentWnd)
{	
	DWORD dwStyle = WS_CHILD|WS_VISIBLE;//|WS_THICKFRAME|WS_SIZEBOX;
	
	//get the frame's rectangle
	CRect rect;
	rect.left	= m_pointPos.x;
	rect.top	= m_pointPos.y;
	rect.right	= m_pointPos.x + m_size.cx;
	rect.bottom = m_pointPos.y + m_size.cy;;
	
	//
	if (!CWnd::Create(NULL,"",dwStyle,rect,pParentWnd,m_iFrameID)) {
		return FALSE;
	}

	//create tool tip
	if (!m_tipCtrl.Create(this,WS_POPUP|WS_EX_TOOLWINDOW|TTS_ALWAYSTIP)){
		return FALSE;
	}
	m_tipCtrl.AddTool(this);
	m_tipCtrl.SetTipTextColor(BLACKCOLOR);  //�趨���ֵ���ɫ
    m_tipCtrl.SetDelayTime(200);            //�趨��ʾ�����ڿؼ���ͣ����ʱ��

	return TRUE;
}

void CFrameTrainNo::RecalcLayout(CDC *pDC)
{
	//Has the frame create?
	if ( GetSafeHwnd() == NULL ){
		return;
	}
	
	//Get the logic region of the frame.
	CRect rectFrame(m_pointPos,m_size);
	
	//rectFrame is now in device coordinates
	pDC->LPtoDP(rectFrame);
	
	//Move the frame and show
	MoveWindow(rectFrame,FALSE);
	ShowWindow(SW_SHOW);

	//
	ReDrawSlf();
}


void CFrameTrainNo::GetRectangle(CRect *pRtTime, CRect *pRtText, CRgn *pRgBack)
{
	//�޳��λ�����Чʱ
	if (m_strContent.IsEmpty() || m_iDirection == FD_IVALID){
		return;
	}


	//get the full rectangle
	CClientDC dc(this);
	CRect rectFrame;//�������ο�ķ�Χ
	GetClientRect(rectFrame);
	
	CRect rectTime(0,0,0,0)/*�������ʾ����*/,rectTextExt(0,0,0,0)/*����������ʾ����*/;
	float fShrink = (m_iTimeExcur == 0) ? (18.6f/20.0f) : (3.0f/4.0f);//��������ռ�����򳤶ȵı���
	CPoint point[5];
	
	////
	if (FD_DOWN == m_iDirection) {//����: --> ��������
		//------------�������Ϣ��----------
		if (m_iTimeExcur==0) {
			rectTime = CRect(0,0,0,rectFrame.bottom);
		}
		else{
			rectTime = CRect(CPoint(0,0),CSize(rectFrame.Width()/5,rectFrame.Height()));
		}
		
		//-----------����������ʾ��Ч��Χ-------------
		rectTextExt = CRect(CPoint(rectTime.right,0),
			CPoint(rectTime.Width()+int(rectFrame.Width()*fShrink),rectFrame.Height()));
		
		//-----------���ο򱳾���Χ(������ͷ)-----------
		point[0] = rectTextExt.TopLeft();
		point[1].x = rectTextExt.right; point[1].y = 0;
		point[2].x = rectFrame.Width(); point[2].y = rectFrame.Height()/2;
		point[3] = rectTextExt.BottomRight();
		point[4] = rectTime.BottomRight();
	}
	else if (FD_UP == m_iDirection){//����: <-- ����Ϊ��
		//------------�������Ϣ��----------
		if (m_iTimeExcur==0) {
			rectTime = CRect(rectFrame.right,0,rectFrame.right,rectFrame.bottom);
		}
		else{
			rectTime = CRect(CPoint(rectFrame.Width()-rectFrame.Width()/5,0),
				CSize(rectFrame.Width()/5,rectFrame.Height()));
		}
		
		
		//-----------����������ʾ��Ч��Χ-------------
		rectTextExt = CRect(CPoint(rectFrame.Width()-rectTime.Width()-int(rectFrame.Width()*fShrink),0),
			CPoint(rectTime.left,rectTime.Height()) );
		
		//-----------���ο򱳾���Χ(������ͷ)-----------
		point[0].x = 0; point[0].y = rectFrame.Height()/2;
		point[1] = rectTextExt.TopLeft();
		point[2].x = rectTextExt.right; point[2].y = 0;
		point[3] = rectTextExt.BottomRight();
		point[4].x = rectTextExt.left; point[4].y = rectFrame.Height();
	}

	//
	if (pRtTime) {*pRtTime = rectTime;}
	if (pRtText) {*pRtText = rectTextExt;}
	if (pRgBack) {pRgBack->CreatePolygonRgn(point,5,ALTERNATE);}
}

void CFrameTrainNo::ReDrawSlf()
{
	if ( GetSafeHwnd() == NULL ){
		return;
	}
	
	//get the full rectangle
	CClientDC dc(this);
	CRect rectFrame;//�������ο�ķ�Χ
	GetClientRect(rectFrame);
	
	//Fill the srceen to black color
	CBrush bsh;
	bsh.CreateSolidBrush(BLACKCOLOR);
	dc.FillRect(rectFrame,&bsh);
	
	//�޳��λ�����Чʱ,��һ�߿�
	if (m_strContent.IsEmpty() || m_iDirection == FD_IVALID){
		CPen newPen,*oldPen;
		newPen.CreatePen(PS_SOLID/*PS_DOT*/,1,FRAMERECT_NT);//���ɫ
		oldPen = dc.SelectObject(&newPen);
		dc.SelectStockObject(BLACK_BRUSH);
		dc.Rectangle(rectFrame);
		dc.SelectObject(oldPen);
		return;
	}

	//�õ���ص�����
	CRect rectTime/*�������ʾ����*/,rectTextExt/*����������ʾ����*/;
	CRgn rgnFrameBKExt/*������������(����ͷ)*/;
	GetRectangle(&rectTime,&rectTextExt,&rgnFrameBKExt);
	
	//
	CBrush brhTimeBk/*����㱳��ɫ*/,brhFrameBKExt/*���ο򱳾�ɫ*/;
	//���������Ϣ����ɫ
	if (m_bInfIvlid) {
		brhTimeBk.CreateSolidBrush(CLRBKGDINVALID);
		dc.SetTextColor(CLRTEXTINVALID);
	}
	else{
		if (0 == m_iTimeExcur) /*���㲻��ʾ*/{
			brhTimeBk.CreateSolidBrush(CLRSHARPALL);
			dc.SetTextColor(CLRSHARPALL);
		}
		else if (m_iTimeExcur>0) {//���
			brhTimeBk.CreateSolidBrush(CLRBKGDLATEALL);
			dc.SetTextColor(CLRTEXTLATEALL);
		}
		else{//���
			if (m_strContent.GetLength() > TRUCKTRAINNONUM) {//��������ʾ
				brhTimeBk.CreateSolidBrush(CLRBKGDEARLYPG);
				dc.SetTextColor(CLRTEXTEARLYPG);
			}
			else{//�г�
				brhTimeBk.CreateSolidBrush(CLRBKGDEARLYTK);
				dc.SetTextColor(CLRTEXTEARLYTK);
			}
		}
	}
	dc.FillRect(rectTime,&brhTimeBk);
	
	//�������ʱ��
	LOGFONT lf;
	CFont font,*pOldFont;
	lf.lfHeight = rectTime.Height()-1;//����߶�
	if (abs(m_iTimeExcur) > 9) {
		lf.lfWidth = rectTime.Height()/3;
	}
	else{
		lf.lfWidth = 0;
	}
	lf.lfStrikeOut = 0;

	lf.lfWeight = FW_THIN;
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfEscapement = lf.lfItalic = lf.lfUnderline = 0;
	lf.lfPitchAndFamily = VARIABLE_PITCH | FF_SWISS;
	strcpy(lf.lfFaceName,"����");
	font.CreateFontIndirect(&lf);
	pOldFont = dc.SelectObject(&font);
	dc.SetBkMode(TRANSPARENT);
	CString strTime;
	strTime.Format("%d",abs(m_iTimeExcur));
	dc.DrawText(strTime,rectTime,DT_CENTER);
	font.DeleteObject();
	
	//�����ο򱳾�
	if (m_bInfIvlid) {
		brhFrameBKExt.CreateSolidBrush(CLRBKGDINVALID);
		dc.SetTextColor(CLRTEXTINVALID);
	}
	else{
		if (m_strContent.GetLength() > TRUCKTRAINNONUM) {//����
			brhFrameBKExt.CreateSolidBrush(CLRBKGDTRUCK);
			dc.SetTextColor(CLRTEXTTRUCK);
		}
		else{
			brhFrameBKExt.CreateSolidBrush(CLRBKGDPAGCAR);
			dc.SetTextColor(CLRTEXTPAGCAR);
		}
	}
	dc.FillRgn(&rgnFrameBKExt,&brhFrameBKExt);
	
	//����������
	lf.lfWidth = 0;
	font.CreateFontIndirect(&lf);
	pOldFont = dc.SelectObject(&font);
	dc.DrawText(m_strContent,rectTextExt,DT_CENTER);
	dc.SelectObject(pOldFont);
}

void CFrameTrainNo::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	ReDrawSlf();
	// Do not call CWnd::OnPaint() for painting messages
}

void CFrameTrainNo::UpdateContent(CString strInf,BOOL bRedraw/*= TRUE*/ )
{
	m_strContent = strInf;
	if (strInf.IsEmpty()) {
		m_iTimeExcur = 0;
		m_iDirection = FD_IVALID;
	}
	
	if (bRedraw) {
		ReDrawSlf();
	}
}

BOOL CFrameTrainNo::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(pMsg->message == WM_MOUSEMOVE ){
		m_tipCtrl.RelayEvent(pMsg); 
	}
	return CWnd::PreTranslateMessage(pMsg);
}

CString CFrameTrainNo::GetContent() const
{
	return m_strContent;
}

void CFrameTrainNo::SetDirection(int iDirection,BOOL bRedraw/*= TRUE*/)
{
	if (1==iDirection) {
		m_iDirection = FD_DOWN;
	}
	else if (2==iDirection) {
		m_iDirection = FD_UP;
	}
	else{
		m_iDirection = FD_IVALID;
	}
	//
	if (bRedraw) {
		ReDrawSlf();
	}
}

void CFrameTrainNo::SetTimeExcur(int iNewExcur,BOOL bRedraw/*= TRUE*/)
{
	m_iTimeExcur = iNewExcur;
	if (bRedraw) {
		ReDrawSlf();
	}
}

void CFrameTrainNo::InvalidInf(BOOL bInvalid)
{
	m_bInfIvlid = bInvalid;
	ReDrawSlf();
}