// DlgRoadAttri.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgRoadAttri.h"
#include ".\dlgroadattri.h"


// CDlgRoadAttri �Ի���

IMPLEMENT_DYNAMIC(CDlgRoadAttri, CDialog)
CDlgRoadAttri::CDlgRoadAttri(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgRoadAttri::IDD, pParent)
{
    m_pRoadList = NULL;
    m_pTrdParse = NULL;
}

CDlgRoadAttri::~CDlgRoadAttri()
{
}

void CDlgRoadAttri::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CDlgRoadAttri, CDialog)
    ON_BN_CLICKED(IDC_BTN_PARSE, OnBnClickedBtnParse)
    ON_BN_CLICKED(IDC_BTN_SAVE, OnBnClickedBtnSave)
    ON_BN_CLICKED(IDCANCEL, OnBnClickedCancel)
//    ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnLvnItemchangedList1)
    ON_NOTIFY(NM_CLICK, IDC_LIST1, OnNMClickList1)
END_MESSAGE_MAP()


// CDlgRoadAttri ��Ϣ�������

BOOL CDlgRoadAttri::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��

    m_strFilePath = GetExePath()+_T("TfcRoad2Link.ini");


    // �����еı���
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("ԭID,100;��ID,50;���,180;�յ�,180") );

    //
    AddRoadToList();

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}

void CDlgRoadAttri::AttachRoad(CTfcRoadList* pRoadList)
{
    m_pRoadList = pRoadList;
}

void CDlgRoadAttri::AddRoadToList()
{
    if (m_pRoadList==NULL)
    {
        return;
    }

    m_ctrlList.DeleteAllItems();

    CString strLine;
    POSITION pos = m_pRoadList->GetHeadPosition();
    
    while(pos)
    {
        PTRawRoadTfcInf pRoad = m_pRoadList->GetNext(pos);
        CString strOldID,strNewID;
        strOldID.Format(_T(" %s"),pRoad->strRoadID);
        strNewID.Format(_T(" %d"),pRoad->dwRoadID);
        m_ctrlList.AddItem(strOldID,strNewID," "+pRoad->strStartName,
            " "+pRoad->strEndName);
    }
}



// ����
void CDlgRoadAttri::OnBnClickedBtnParse()
{
    if (m_pTrdParse!=NULL)
    {
        return;
    }

    SetWindowText("��·���������ڽ��������Ժ򡭡�");
    GetDlgItem(IDC_BTN_PARSE)->EnableWindow(FALSE);
    GetDlgItem(IDC_BTN_SAVE)->EnableWindow(FALSE);

    // 

    m_pTrdParse = AfxBeginThread(_ThreadParseEntry,this);

    ASSERT(m_pTrdParse!=NULL);

}


UINT CDlgRoadAttri::_ThreadParseEntry(LPVOID pParam)
{
    CDlgRoadAttri* pObject = (CDlgRoadAttri*)pParam;


    //
    TImcMsg msg(EMSG_PARSE_START,ID_MODULE_DATABASE,ID_MODULE_DATABASE);
    NbsSendModuleMsg(&msg);

    pObject->m_pTrdParse = NULL;

    pObject->OnFinishParsing();

    return 0L;
}

void CDlgRoadAttri::OnFinishParsing()
{ 
    // �������
    TImcMsg msg(EMSG_PARSE_FINISHED,ID_MODULE_DATABASE,ID_MODULE_DATABASE);
    NbsSendModuleMsg(&msg);

    //
    SetWindowText("��·��������������ɣ�");
    GetDlgItem(IDC_BTN_PARSE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
}

//  ����
void CDlgRoadAttri::OnBnClickedBtnSave()
{
    TCHAR szFilters[]= _T("�����ļ�(*.ini)|*.ini|All Files (*.*)|*.*||");


    CFileDialog fileDlg(FALSE, _T("ini"), m_strFilePath,
        OFN_OVERWRITEPROMPT, szFilters, this);

    // Display the file dialog. When the user clicks OK, fileDlg.DoModal()
    // returns IDOK.
    if( fileDlg.DoModal ()==IDOK )
    {
        m_strFilePath = fileDlg.GetPathName();

        //
        TImcMsg msg(EMSG_PARSE_STORAGE,ID_MODULE_DATABASE,ID_MODULE_DATABASE);
        msg.m_wParam = WPARAM(&m_strFilePath);
        NbsSendModuleMsg(&msg);
    }

}

void CDlgRoadAttri::OnBnClickedCancel()
{
    // TODO: �ڴ���ӿؼ�֪ͨ����������
    ShowWindow(SW_HIDE);
}


void CDlgRoadAttri::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    //�õ������е����
    POSITION lpos = m_ctrlList.GetFirstSelectedItemPosition();
    int nItem = m_ctrlList.GetNextSelectedItem(lpos);
   
    if(nItem != -1)
    {
        CString strRoadID = m_ctrlList.GetItemText(nItem,0);
        strRoadID.Trim();

        // ����ָ���ĵ�·
        TImcMsg msg(EMSG_PARSE_LOOKUP,ID_MODULE_DATABASE,ID_MODULE_DATABASE);
        msg.m_wParam = (WPARAM)(&strRoadID);
        NbsSendModuleMsg(&msg);

        TRACE("������·��%s��\n",strRoadID);

    }

    //=====================
    *pResult = 0;
}
