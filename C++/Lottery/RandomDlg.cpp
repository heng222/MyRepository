// RandomDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Random.h"
#include "RandomDlg.h"
#include ".\randomdlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRandomDlg �Ի���



CRandomDlg::CRandomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRandomDlg::IDD, pParent)
    , m_iMaxNum(30)
    , m_strResult(_T(""))
    , m_wNumber(7)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CRandomDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_MAXNUM, m_iMaxNum);
    DDX_Text(pDX, IDC_EDIT_RESULT, m_strResult);
    DDX_Text(pDX, IDC_EDIT_NUMBER, m_wNumber);
	DDV_MinMaxShort(pDX, m_wNumber, 1, 50);
}

BEGIN_MESSAGE_MAP(CRandomDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
    ON_BN_CLICKED(ID_GENERATE, OnBnClickedGenerate)
    ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
END_MESSAGE_MAP()


// CRandomDlg ��Ϣ�������

BOOL CRandomDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CRandomDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CRandomDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CRandomDlg::OnBnClickedGenerate()
{
    /*double longi = 2334.1234;
    int degree = int(longi) - int(longi)%100;
    double minute = longi - degree;*/


    UpdateData();
    if (m_wNumber>100)
    {
        m_wNumber = 10;
    }

    m_strResult = _T("");
    //srand( (unsigned)time( NULL ) );

    CWordArray wordArray;
    wordArray.SetSize(10);
    WORD temp;
    for (int ii=0; ii<m_wNumber && ii<m_iMaxNum; ii++)
    {
        srand( GetTickCount() );

        temp = (WORD)((rand()%m_iMaxNum)+1);

        if (!IsExist(wordArray,temp))
        {
            wordArray.Add(temp);
            char cResult[10];
            itoa(temp,cResult,10);
            m_strResult = m_strResult+ CString(cResult) + _T(" ");
        }
        else
        {
            ii--;
            continue;
        }
    }


    UpdateData(FALSE);

}

BOOL CRandomDlg::IsExist(const CWordArray& aWordArray,WORD aNewNum)
{
    INT_PTR number = aWordArray.GetCount();
    for (INT_PTR ii=0; ii<number; ii++)
    {
        if (aNewNum==aWordArray[ii])
        {
            return TRUE;
        }
    }
    return FALSE;
}
void CRandomDlg::OnBnClickedCancel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    OnCancel();
}
