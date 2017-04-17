// ConstructRequest.cpp : implementation file
//

#include "stdafx.h"
#include "maintain.h"
#include "ConstructRequest.h"
#include "mainfrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CMaintainApp theApp;
/////////////////////////////////////////////////////////////////////////////
// CConstructRequest dialog


CConstructRequest::CConstructRequest(CWnd* pParent /*=NULL*/)
	: CDialog(CConstructRequest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConstructRequest)
	m_strEdit1 = _T("��");
	m_strEdit3 = _T("������");
	m_iKind = 0;
	m_strContent = _T("");
	m_strEdit2 = _T("ʩ �� �� �� �� �� �� ��");
	m_strAsker = _T("");
	m_strWatcher = _T("");
	m_strOrder = _T("");
	m_strMendKind = _T("");
	m_strStation = _T("");
	m_timeDateTime = CTime::GetCurrentTime();
	m_iConsumeTime = 30;
	//}}AFX_DATA_INIT

	//��ȡʩ��ģ��
	m_MendTemplate.ReadFile(theApp.m_strExePath+MENDTEMPLATEPATHNAME);

}


void CConstructRequest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConstructRequest)
	DDX_Control(pDX, IDC_MENDKIND, m_ctrlMendKind);
	DDX_Control(pDX, IDC_ORDER, m_ctrlOrder);
	DDX_Control(pDX, IDC_LIST1, m_ctrlList);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_ctrlDateTime);
	DDX_Text(pDX, IDC_EDIT1, m_strEdit1);
	DDX_Text(pDX, IDC_EDIT3, m_strEdit3);
	DDX_Radio(pDX, IDC_REGISTER, m_iKind);
	DDX_Text(pDX, IDC_CONTENT, m_strContent);
	DDV_MaxChars(pDX, m_strContent, 300);
	DDX_Text(pDX, IDC_EDIT2, m_strEdit2);
	DDX_Text(pDX, IDC_ASKER, m_strAsker);
	DDV_MaxChars(pDX, m_strAsker, 20);
	DDX_Text(pDX, IDC_WATCHER, m_strWatcher);
	DDV_MaxChars(pDX, m_strWatcher, 20);
	DDX_Text(pDX, IDC_ORDER, m_strOrder);
	DDX_CBString(pDX, IDC_MENDKIND, m_strMendKind);
	DDX_Text(pDX, IDC_STATION, m_strStation);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_timeDateTime);
	DDX_Text(pDX, IDC_CONSUMETIME, m_iConsumeTime);
	DDV_MinMaxInt(pDX, m_iConsumeTime, 0, 100000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConstructRequest, CDialog)
	//{{AFX_MSG_MAP(CConstructRequest)
	ON_BN_CLICKED(IDC_REGISTER, OnRadioRegister)
	ON_BN_CLICKED(IDC_DELETE, OnBDelete)
	ON_BN_CLICKED(IDC_REQUEST, OnBRequestCommand)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_CBN_SELCHANGE(IDC_MENDKIND, OnSelchangeMendkind)
	ON_BN_CLICKED(IDC_RADIO2, OnRadioRegister)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConstructRequest message handlers

BOOL CConstructRequest::OnInitDialog() 
{
	CDialog::OnInitDialog();
	/////////////////////////////////////////////////////////////////////////////////////
	m_pMainFrame = (CMainFrame*)AfxGetMainWnd();
	
	COleDateTime oleDateTime = COleDateTime::GetCurrentTime();
	//���öԻ���ı���
	this->SetWindowText(oleDateTime.Format("%Y��%m��%d�յ�ʩ����¼"));

	//�������ڸ�ʽ
	m_ctrlDateTime.SetFormat(_T("yyyy-MM-dd HH:mm:ss"));

	//����ʩ������(�촰�ޡ�������)
	m_ctrlMendKind.SetCurSel(0);

	//����վ������
	m_strStation = CReadStationInf::GetInstance()->GetName(CReadStationInf::GetActiveStation());//theApp.m_strStationName;
	
	//�����еı���
	m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	m_ctrlList.SetHeadings( _T("���,60;����վ,80;�Ǽ�ʱ��,150;ʩ��������,100;�Ǽ�ֵ��Ա,100;ʩ������ʱ��(��),120;ʩ������,80;�Ǽ�����,300;����ʱ��,150; ����������,100; ����ֵ��Ա,100; ��������,300;") );
	m_ctrlList.LoadColumnInfo();

	//�򿪵���ļ�¼�ļ���������д�뵽 ���� Records ��
	Records.ReadRecords(theApp.m_strExePath + REACORDPATHNAME+oleDateTime.Format("%Y-%m-%d.rec"));
	
	//��ʼ��ʩ����������
	m_strContent = m_MendTemplate.GetContent(1,!m_iKind);

	//����ListCtrl�ؼ�
	UpdateListCtrl();
	
	//������ſؼ�
	UpdateOrderEdit();

	UpdateData(false);
	//////////////////////////////////////////////////////////////////////////////////////
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//���ݳ�Ա���� Records ���� LISTCTRL
void CConstructRequest::UpdateListCtrl()
{
	//��ɾ��LISTCTRL��ԭ�е�����
	m_ctrlList.DeleteAllItems();
	//
	CString strGroup[25];
	for ( BYTE j=1; j<=Records.GetRecordNum(); j++)//jΪ��ǰ��¼��
	{
		BYTE i = 0;//iָ��LISTCTRL�ĵ�ǰ�к�

		//---------------------------------------
		strGroup[i++] = Records.GetValue(j,"T_Station");
		strGroup[i++] = Records.GetValue(j,"R_DateTime");	
		strGroup[i++] = Records.GetValue(j,"R_Asker");		
		strGroup[i++] = Records.GetValue(j,"R_Watcher");		
		strGroup[i++] = Records.GetValue(j,"R_ConsumeTime");	
		strGroup[i++] = Records.GetValue(j,"R_MendKind");	
		strGroup[i++] = Records.GetValue(j,"R_Content");

		
		strGroup[i++] = Records.GetValue(j,"CR_DateTime");	
		strGroup[i++] = Records.GetValue(j,"CR_Asker");	
		strGroup[i++] = Records.GetValue(j,"CR_Watcher");	
		strGroup[i++] = Records.GetValue(j,"CR_Content");
		

		//��Ӽ�¼��LISTCTRL��ȥ
		CString strOrder;
		strOrder.Format("%d",j);

		m_ctrlList.AddItem(strOrder,strGroup[0],
			strGroup[1],	strGroup[2],	strGroup[3],	strGroup[4],	strGroup[5],	strGroup[6],
			strGroup[7],	strGroup[8],	strGroup[9],	strGroup[10]);
	}
	
}

//���ݼ�¼������IDC_ORDER
void CConstructRequest::UpdateOrderEdit()
{
	m_strOrder.Format( "%d", Records.GetRecordNum() + 1);
	m_ctrlOrder.SetWindowText(m_strOrder);
}


//˫��LISTCTRL
void CConstructRequest::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	UpdateData();
	
	CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	if (nItem < 0)	return;
	//Order
	BYTE byOrder = (BYTE)atoi( m_ctrlList.GetItemText(nItem,0) );
	//Station
	m_strOrder = m_ctrlList.GetItemText(nItem,0);
	m_strStation = pStationInf->GetName(atoi(Records.GetValue(byOrder,"T_Station")));
	//------------------
	COleDateTime oleTime;
	if ( m_iKind == 0 )
	{
		oleTime.ParseDateTime( Records.GetValue(byOrder, "R_DateTime") );
		m_ctrlDateTime.SetTime(oleTime);
		m_ctrlDateTime.GetTime(m_timeDateTime);

		m_strAsker = Records.GetValue(byOrder, "R_Asker");
		m_strWatcher = Records.GetValue(byOrder, "R_Watcher");
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(true);
		m_iConsumeTime = atoi(Records.GetValue(byOrder, "R_ConsumeTime"));
		m_strMendKind = m_MendTemplate.GetName( atoi(Records.GetValue(byOrder, "R_MendKind")) );
		m_strContent = Records.GetValue(byOrder, "R_Content");
	}
	else
	{
		if ( Records.GetValue(byOrder, "CR_DateTime").IsEmpty() )
		{
			MessageBox("������¼��δ����! ��������Ϣ��","��ʾ",MB_ICONINFORMATION);
			return;
		}
		oleTime.ParseDateTime( Records.GetValue(byOrder, "CR_DateTime") );
		m_ctrlDateTime.SetTime(oleTime);
		m_ctrlDateTime.GetTime(m_timeDateTime);
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(false);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(false);
		m_strAsker = Records.GetValue(byOrder, "CR_Asker");
		m_strWatcher = Records.GetValue(byOrder, "CR_Watcher");
		m_strContent = Records.GetValue(byOrder, "CR_Content");

	}
	UpdateData(false);
	//------------------------------------------
	*pResult = 0;
}
//��MENDKIND�仯ʱ
void CConstructRequest::OnSelchangeMendkind() 
{
	UpdateData();
	m_strContent = m_MendTemplate.GetContent(m_strMendKind,!m_iKind);
	UpdateData(false);
	
}
//����RADIO�ؼ�
void CConstructRequest::OnRadioRegister() 
{
	UpdateData();
	//---------------------------------------------
	if(m_iKind == 0)
	{
		//m_strStation = theApp.m_strStationName;
		m_strEdit2 = "ʩ �� �� �� �� �� �� ��";
		m_strEdit1 = "��";
		//m_strContent = theApp.m_MendTemplate.GetContent(m_ctrlMendKind.GetCurSel()+1,TRUE);
		
		GetDlgItem(IDC_REQUEST)->SetWindowText("�������");
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(true);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(true);
		//����IDC_ORDER
		UpdateOrderEdit();
	}
	else
	{
		POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
		int nItem=m_ctrlList.GetNextSelectedItem(lpos);
		if(nItem != -1)
		{
			m_strOrder = m_ctrlList.GetItemText(nItem,0);
		}
		else
		{
			MessageBox("������������б����ѡ��Ҫ���ǵļ�¼��","��ʾ",MB_ICONINFORMATION);
			m_iKind = 0;
			UpdateData(FALSE);
			return;
		}
		m_strEdit1 = "���ǵ�";
		m_strEdit2 = "ʩ �� �� �� �� �� �� ��";		
		m_strContent = m_MendTemplate.GetContent(m_ctrlMendKind.GetCurSel()+1,FALSE);

		GetDlgItem(IDC_REQUEST)->SetWindowText("����ͨ");
		GetDlgItem(IDC_CONSUMETIME)->EnableWindow(false);
		GetDlgItem(IDC_MENDKIND)->EnableWindow(false);
	}
	//����ʱ��
	m_timeDateTime = CTime::GetCurrentTime();
	//-------------------------------------------------------------------------
	UpdateData(FALSE);
}

//����ʩ���Ǽǻ����Ǽ���Records��
void CConstructRequest::AddNewData()
{
	BYTE byRecordIndex = atoi(m_strOrder);
	//
	CString strTemp;
	if(m_iKind==0)//�����Ǽ�
	{
		Records.SetValue(byRecordIndex,"T_Station",CReadStationInf::GetInstance()->GetName(CReadStationInf::GetActiveStation()));
		Records.SetValue(byRecordIndex,"R_DateTime",m_timeDateTime.Format("%Y-%m-%d %H:%M:%S"));
		Records.SetValue(byRecordIndex,"R_Asker",m_strAsker);
		Records.SetValue(byRecordIndex,"R_Watcher",m_strWatcher);
		Records.SetValue(byRecordIndex,"R_ConsumeTime",m_iConsumeTime);
		Records.SetValue(byRecordIndex,"R_MendKind",m_strMendKind);
		Records.SetValue(byRecordIndex,"R_Content",m_strContent);
		//UpdateOrderEdit();
	}
	else//��������
	{
		ASSERT ( byRecordIndex<=Records.GetRecordNum() );

		Records.SetValue(byRecordIndex,"CR_DateTime",m_timeDateTime.Format("%Y-%m-%d %H:%M:%S"));
		Records.SetValue(byRecordIndex,"CR_Asker",m_strAsker);
		Records.SetValue(byRecordIndex,"CR_Watcher",m_strWatcher);
		Records.SetValue(byRecordIndex,"CR_Content",m_strContent);
	}

	//�����б�ؼ�
	UpdateListCtrl();

	//�����º�ļ�¼�����浽�ļ���
	Records.WriteRecords();
}


//����ɾ����ť
void CConstructRequest::OnBDelete()
{
	//�õ�LISTCTRL��ѡ����кţ�Based Zero��
	POSITION lpos=m_ctrlList.GetFirstSelectedItemPosition();
	int nItem=m_ctrlList.GetNextSelectedItem(lpos);
	//
	if ( nItem == -1)
	{
		MessageBox("�������б����ѡ��Ҫɾ������!","��ʾ",MB_OK | MB_ICONINFORMATION);
		return;
	}
	if( MessageBox("ȷ��Ҫɾ��ѡ�еļ�¼�𣿲��ɻָ���","����",MB_YESNO | MB_ICONQUESTION | MB_DEFBUTTON2) == IDNO)
	{
		return;
	}

	//�õ���¼�����
	CString strOrder = m_ctrlList.GetItemText(nItem,0);
	//ɾ��ѡ�еļ�¼�������ĺ������д���ļ�
	Records.DeleteRecord( (BYTE)atoi(strOrder) );
	Records.WriteRecords();

	//ˢ��LISTCTRL
	UpdateListCtrl();

	//ˢ��IDC_ORDER�ؼ�
	if ( m_iKind == 0 )
	{
		//UpdateOrderEdit();
	}
	else
	{
		//m_strOrder = "0";
		//m_ctrlOrder.SetWindowText(m_strOrder);
	}
}

void CConstructRequest::OnBRequestCommand() 
{
	UpdateData(TRUE);
	if (m_strAsker.IsEmpty())
	{
		MessageBox("�����˲���Ϊ��!","������ʾ",MB_ICONERROR);
		return;
	}

	if ( m_strWatcher.IsEmpty() )
	{
		MessageBox("ֵ��Ա����Ϊ��!","������ʾ",MB_ICONERROR);
		return;
	}

	if ( m_iConsumeTime == 0)
	{
		MessageBox("����ʱ�䲻��Ϊ��!","������ʾ",MB_ICONERROR);
		return;
	}

	//��������֡
	//�������״̬
	BOOL bIsConnect = ((CMainFrame*)AfxGetMainWnd())->m_socketClient.IsOpen();
	if ( 1 )
	{
		BYTE byFrame[CONSTFAMEMAXLEN];
		WORD nFrameLen = 0;
		
		//�������֡
		GetFrame(byFrame,nFrameLen);
		((CMainFrame*)AfxGetMainWnd())->m_socketClient.WriteComm(CONSTFRAMEKIND,0X01,byFrame,nFrameLen,INFINITE);
		MessageBox("�����ѷ�������ע����ջ�ִ���","��ʾ",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox("�������Ӵ������⣬���Ժ��͡�","��ʾ�����粻ͨ",MB_ICONINFORMATION);
	}
	
	//�����ݱ��浽�ļ���
	AddNewData();
}

//�������֡
void CConstructRequest::GetFrame(LPBYTE byFrame,WORD& nFrameLen)
{
	//byFrameΪ�����͵�֡��nFrameLenΪ֡����Ч���ȡ�
	UpdateData();

	//-----------------------
	nFrameLen = 0;
	//WORD wTemp;

	//����վվ��(WORD)
	//CReadStationInf* pStationInf = CReadStationInf::GetInstance();
	//WORD wOrder = pStationInf->GetStationID(theApp.m_strStationName);
	WORD wOrder = CReadStationInf::GetActiveStation();
	memcpy(byFrame+nFrameLen,&wOrder,2);
	nFrameLen += 2;

	//�������(�Ǽǣ�����) (BYTE)
	//0Ϊ�Ǽ�,1Ϊ����
	if ( m_iKind == 0 )
	{
		byFrame[nFrameLen++] = CONSTREGISTER;
	}
	else if (m_iKind == 1)
	{
		byFrame[nFrameLen++] = CONSTCLEARREG;
	}
	
	//�Ǽ�����ʱ��(DWORD)
	DWORD dwTemp;
	
	if( m_iKind == 1 )//����
	{
		//����Ӧ���ļ��еõ��Ǽ�����
		COleDateTime oleRDateTime;
		CTime tDT1,tDT2;
		oleRDateTime.ParseDateTime(Records.GetValue(atoi(m_strOrder),"R_DateTime"));
		m_ctrlDateTime.GetTime(tDT2);
		m_ctrlDateTime.SetTime(oleRDateTime);
		m_ctrlDateTime.GetTime(tDT1);
		dwTemp = tDT1.GetTime();
		m_ctrlDateTime.SetTime(&tDT2);
	}
	else//�Ǽ�
	{
		dwTemp = m_timeDateTime.GetTime();
	}
	memcpy( byFrame+nFrameLen, &dwTemp, 4 );
	nFrameLen += 4;
	
	//��������ʱ�� (DWORD)
	if( m_iKind == 1 )//����
	{
		dwTemp = m_timeDateTime.GetTime();
	}
	else
	{
		dwTemp = 0;
	}
	memcpy( byFrame+nFrameLen, &dwTemp, 4 );
	nFrameLen += 4;


	//������(20 BYTES)
	int i = 0;
	for (i = 0; i<20; i++)
	{
		if( i<m_strAsker.GetLength() )
		{
			byFrame[nFrameLen++] = m_strAsker.GetAt(i);
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}

	//ֵ��Ա(20 BYTES)
	for (i = 0; i<20; i++)
	{
		if( i<m_strWatcher.GetLength() )
		{
			byFrame[nFrameLen++] = m_strWatcher.GetAt(i);
		}
		else
		{
			byFrame[nFrameLen++] = 0;
		}
	}


	//ʩ�����(�촰�ޡ�������) (BYTE)
	//1Ϊ�촰��,2Ϊ������, ......
	if( m_iKind == 0 )
	{
		byFrame[nFrameLen++] = m_ctrlMendKind.GetCurSel() + 1;
	}
	else
	{
		byFrame[nFrameLen++] = 0;
	}
	
	//ʩ������ʱ��(WORD)
	if( m_iKind == 0 )
	{
		memcpy( byFrame+nFrameLen, &m_iConsumeTime, 2 );
		nFrameLen += 2;
	}
	else
	{
		byFrame[nFrameLen++] = 0;
		byFrame[nFrameLen++] = 0;
	}

	//�������ݳ���
	WORD wContentLen = m_strContent.GetLength();
	memcpy(byFrame+nFrameLen,&wContentLen,2);
	nFrameLen += 2;

	//��������
	memcpy(byFrame+nFrameLen,m_strContent,wContentLen);

	//--------------------------------------
	//�õ�����֡����Ч����
	nFrameLen += wContentLen;
}
//===============================================================================

void CConstructRequest::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	//DestroyWindow();
	CDialog::OnCancel();
}

void CConstructRequest::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	//delete this;
	CDialog::PostNcDestroy();
	
}

BOOL CConstructRequest::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
//	( (CMainFrame*)AfxGetMainWnd() )->m_pRequestDlg = NULL;
	return CDialog::DestroyWindow();
}

