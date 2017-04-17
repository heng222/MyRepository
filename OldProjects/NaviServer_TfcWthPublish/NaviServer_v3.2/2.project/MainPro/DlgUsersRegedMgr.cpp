// DlgUsersRegedMgr.cpp : 实现文件
//

#include "stdafx.h"
#include "DlgUsersRegedMgr.h"
#include "GlobalMacro.h"
#include "CommonFunc.h"
#include "TableAttrib.h"




// CDlgUsersRegedMgr 对话框

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


// CDlgUsersRegedMgr 消息处理程序

BOOL CDlgUsersRegedMgr::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    //设置列的标题
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | 
        LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("用户名,80;注册日期,110;SIM卡号,100;软件序列号,100;手机序列号,100") );
    m_ctrlList.LoadColumnInfo();

    //从配置文件中读取数据库参数
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

    //连接到spacesatlbs数据库
    if (!m_OracleDB.ConnectOracle(strDataSource,strUserID,strPWD))
    {
        AfxMessageBox("连接到数据库失败，无法进行计费查询！",MB_ICONERROR);
        return FALSE;
    }

    //
    InitSubControls();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
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