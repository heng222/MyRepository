// DlgUsersRegedMgr.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DlgUsersRegedMgr.h"
#include "GlobalMacro.h"
#include "CommonFunc.h"
#include "TableAttrib.h"




// CDlgUsersRegedMgr �Ի���

IMPLEMENT_DYNAMIC(CDlgUsersRegedMgr, CDialog)
CDlgUsersRegedMgr::CDlgUsersRegedMgr(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgUsersRegedMgr::IDD, pParent)
{
}

CDlgUsersRegedMgr::~CDlgUsersRegedMgr()
{
}

void CDlgUsersRegedMgr::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ctrlList);
}


BEGIN_MESSAGE_MAP(CDlgUsersRegedMgr, CDialog)
END_MESSAGE_MAP()


// CDlgUsersRegedMgr ��Ϣ�������

BOOL CDlgUsersRegedMgr::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    //�����еı���
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | 
        LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("�û���,80;ע������,110;SIM����,100;������к�,100;�ֻ����к�,100") );
    m_ctrlList.LoadColumnInfo();

    //�������ļ��ж�ȡ���ݿ����
    char cTemp[300];
    CString strDataSource;
    CString strUserID;
    CString strPWD;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"DataSource",0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    strDataSource = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"UserID",0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    strUserID = cTemp;
    GetPrivateProfileString(CFG_APPNAME_DATABASE,"Password",0,cTemp,300,GetExePath()+CString(PATH_CONFIGURE_FILE));
    strPWD = cTemp;

    //���ӵ�spacesatlbs���ݿ�
    if (!m_OracleDB.ConnectOracle(strDataSource,strUserID,strPWD))
    {
        AfxMessageBox("���ӵ����ݿ�ʧ�ܣ��޷����мƷѲ�ѯ��",MB_ICONERROR);
        return FALSE;
    }

    //
    InitSubControls();

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgUsersRegedMgr::InitSubControls()
{
    CString strSQL;
    CAdoRecordSet records;

    strSQL.Format(_T("SELECT * FROM %s"), T_USERSREG_NAME);
    records = m_OracleDB.Execute(strSQL);
    records.MoveFirst();
    while (!records.IsEOF())
    {
        CString strUserName;
        records.GetCollect(_T("UserName"),strUserName);

        COleDateTime regDate;
        records.GetCollect(_T("RegDate"),regDate);

        CString strCellPhoneNo;
        records.GetCollect(_T("CellPhoneNo"),strCellPhoneNo);

        CString strSWSerNo;
        records.GetCollect(_T("SWSerNo"),strSWSerNo);

        CString strCPSerNo;
        records.GetCollect(_T("CPSerNo"),strCPSerNo);
        
        //
        m_ctrlList.AddItem(strUserName,
            regDate.Format(_T(" %Y-%m-%D %H-%M-%S ")),
            strCellPhoneNo,
            strSWSerNo,
            strCPSerNo);

        records.MoveNext();
    }
}