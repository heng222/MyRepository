// DlgRoadAttri.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgRoadAttri.h"
#include ".\dlgroadattri.h"


// CDlgRoadAttri 对话框

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


// CDlgRoadAttri 消息处理程序

BOOL CDlgRoadAttri::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化

    m_strFilePath = GetExePath()+_T("TfcRoad2Link.ini");


    // 设置列的标题
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("原ID,100;新ID,50;起点,180;终点,180") );

    //
    AddRoadToList();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
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



// 解析
void CDlgRoadAttri::OnBnClickedBtnParse()
{
    if (m_pTrdParse!=NULL)
    {
        return;
    }

    SetWindowText("道路解析：正在解析，请稍候……");
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
    // 解析完毕
    TImcMsg msg(EMSG_PARSE_FINISHED,ID_MODULE_DATABASE,ID_MODULE_DATABASE);
    NbsSendModuleMsg(&msg);

    //
    SetWindowText("道路解析：解析已完成！");
    GetDlgItem(IDC_BTN_PARSE)->EnableWindow(TRUE);
    GetDlgItem(IDC_BTN_SAVE)->EnableWindow(TRUE);
}

//  保存
void CDlgRoadAttri::OnBnClickedBtnSave()
{
    TCHAR szFilters[]= _T("配置文件(*.ini)|*.ini|All Files (*.*)|*.*||");


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
    // TODO: 在此添加控件通知处理程序代码
    ShowWindow(SW_HIDE);
}


void CDlgRoadAttri::OnNMClickList1(NMHDR *pNMHDR, LRESULT *pResult)
{
    //得到单击行的序号
    POSITION lpos = m_ctrlList.GetFirstSelectedItemPosition();
    int nItem = m_ctrlList.GetNextSelectedItem(lpos);
   
    if(nItem != -1)
    {
        CString strRoadID = m_ctrlList.GetItemText(nItem,0);
        strRoadID.Trim();

        // 解析指定的道路
        TImcMsg msg(EMSG_PARSE_LOOKUP,ID_MODULE_DATABASE,ID_MODULE_DATABASE);
        msg.m_wParam = (WPARAM)(&strRoadID);
        NbsSendModuleMsg(&msg);

        TRACE("解析道路（%s）\n",strRoadID);

    }

    //=====================
    *pResult = 0;
}
