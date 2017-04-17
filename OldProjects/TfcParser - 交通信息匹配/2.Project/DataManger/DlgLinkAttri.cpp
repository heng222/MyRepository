// DlgLinkAttri.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgLinkAttri.h"
#include ".\dlglinkattri.h"


// CDlgLinkAttri �Ի���

IMPLEMENT_DYNAMIC(CDlgLinkAttri, CDialog)
CDlgLinkAttri::CDlgLinkAttri(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgLinkAttri::IDD, pParent)
{
    m_pLinkList = NULL;
}

CDlgLinkAttri::~CDlgLinkAttri()
{
}

void CDlgLinkAttri::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CDlgLinkAttri, CDialog)
END_MESSAGE_MAP()


// CDlgLinkAttri ��Ϣ�������

BOOL CDlgLinkAttri::OnInitDialog()
{
    CDialog::OnInitDialog();

    //�����еı���
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("MapID+LinkID,100; Link����,100;��״�����,150") );

    //
    AddLinkToList();

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgLinkAttri::AttachLink(CLinkList* pLinkList)
{
    m_pLinkList = pLinkList;
}

void CDlgLinkAttri::AddLinkToList()
{
    if (m_pLinkList==NULL)
    {
        return;
    }

    CString strLine;
    POSITION pos = m_pLinkList->GetHeadPosition();

    while(pos)
    {
        PTLinkAttri pLink = m_pLinkList->GetNext(pos);
        CString strNumPoint;
        strNumPoint.Format(" %d",pLink->GetNumofPt());
        CString strLinkID;
        strLinkID.Format(_T("%d+%d"),pLink->m_dwMapID,pLink->m_dwLinkID);
        m_ctrlList.AddItem(strLinkID," "+pLink->m_strLinkName,strNumPoint);
    }
}





