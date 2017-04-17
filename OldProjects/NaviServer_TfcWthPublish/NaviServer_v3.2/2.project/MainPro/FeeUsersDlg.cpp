// FeeUsersDlg.cpp : 实现文件
//

#include "stdafx.h"
#include ".\feeusersdlg.h"
#include "GlobalMacro.h"
#include "TableAttrib.h"
#include "CommonFunc.h"

// CFeeUsersDlg 对话框

IMPLEMENT_DYNAMIC(CFeeUsersDlg, CDialog)
CFeeUsersDlg::CFeeUsersDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFeeUsersDlg::IDD, pParent)
{
}

CFeeUsersDlg::~CFeeUsersDlg()
{
}

void CFeeUsersDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_LIST1, m_ctrlList);
    DDX_Control(pDX, IDC_DP_REGDATE, m_ctrlComRegDate);
    DDX_Control(pDX, IDC_CHECK_REGDATE, m_ctrlCheckRegDate);
    DDX_Control(pDX, IDC_CHECK_SERVICECODE, m_ctrlCheckSerCode);
    DDX_Control(pDX, IDC_CB_SERCODE, m_ctrlComSerCode);
    DDX_Control(pDX, IDC_CHECK_CITYNAME, m_ctrlCheckCity);
    DDX_Control(pDX, IDC_CB_CITY, m_ctrlComCity);
    DDX_Control(pDX, IDC_CB_CELLPHON, m_ctrlComCellphone);
    DDX_Control(pDX, IDC_CHECK_CELLPHONE, m_ctrlCheckCellPhone);
}


BEGIN_MESSAGE_MAP(CFeeUsersDlg, CDialog)
    ON_BN_CLICKED(IDC_CHECK_REGDATE, OnBnClickedCheckRegdate)
    ON_BN_CLICKED(IDC_CHECK_SERVICECODE, OnBnClickedCheckServicecode)
    ON_BN_CLICKED(IDC_CHECK_CITYNAME, OnBnClickedCheckCityname)
    ON_BN_CLICKED(ID_QUERY, OnBnClickedQuery)
    ON_WM_CLOSE()
    ON_BN_CLICKED(IDC_CHECK_CELLPHONE, OnBnClickedCheckCellphone)
END_MESSAGE_MAP()


// CFeeUsersDlg 消息处理程序

BOOL CFeeUsersDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // TODO:  在此添加额外的初始化
    m_ctrlCheckRegDate.SetCheck(BST_CHECKED);
    m_ctrlCheckSerCode.SetCheck(BST_UNCHECKED);
    m_ctrlCheckCity.SetCheck(BST_UNCHECKED);
    m_ctrlCheckCellPhone.SetCheck(BST_UNCHECKED);

    m_ctrlComRegDate.EnableWindow(m_ctrlCheckRegDate.GetCheck()==BST_CHECKED);
    m_ctrlComSerCode.EnableWindow(m_ctrlCheckSerCode.GetCheck()==BST_CHECKED);
    m_ctrlComCity.EnableWindow(m_ctrlCheckCity.GetCheck()==BST_CHECKED);
    m_ctrlComCellphone.EnableWindow(m_ctrlCheckCellPhone.GetCheck()==BST_CHECKED);


    //设置列的标题
    m_ctrlList.SetExtendedStyle(LVS_EX_GRIDLINES | 
        LVS_EX_FULLROWSELECT | LVS_EX_HEADERDRAGDROP);
    m_ctrlList.SetHeadings( _T("手机号码,120;注册日期,110;注销日期,110;运营商,60;SP号码,60;业务代码,60;城市名称,60") );
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
    InitControls();

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CFeeUsersDlg::OnBnClickedCheckRegdate()
{
    int iState = m_ctrlCheckRegDate.GetCheck();
    if (iState==BST_CHECKED)
    {
        m_ctrlComRegDate.EnableWindow(TRUE);
    }
    else if (iState==BST_UNCHECKED)
    {
        m_ctrlComRegDate.EnableWindow(FALSE);
    }
}

void CFeeUsersDlg::OnBnClickedCheckServicecode()
{
    int iState = m_ctrlCheckSerCode.GetCheck();
    if (iState==BST_CHECKED)
    {
        m_ctrlComSerCode.EnableWindow(TRUE);
    }
    else if (iState==BST_UNCHECKED)
    {
        m_ctrlComSerCode.EnableWindow(FALSE);
    }
}

void CFeeUsersDlg::OnBnClickedCheckCityname()
{
    int iState = m_ctrlCheckCity.GetCheck();
    if (iState==BST_CHECKED)
    {
        m_ctrlComCity.EnableWindow(TRUE);
    }
    else if (iState==BST_UNCHECKED)
    {
        m_ctrlComCity.EnableWindow(FALSE);
    }
}

void CFeeUsersDlg::OnBnClickedCheckCellphone()
{
    int iState = m_ctrlCheckCellPhone.GetCheck();
    if (iState==BST_CHECKED)
    {
        m_ctrlComCellphone.EnableWindow(TRUE);
    }
    else if (iState==BST_UNCHECKED)
    {
        m_ctrlComCellphone.EnableWindow(FALSE);
    }
}

// 根据条件进行查询
void CFeeUsersDlg::OnBnClickedQuery()
{
    m_ctrlList.DeleteAllItems();

    //
    CString strSQL;
    strSQL.Format(_T("SELECT * FROM %s"),T_FEEUSERS_NAME);
    int iNewState = BST_UNCHECKED;
    BOOL bFlag = FALSE;
    CString strClause;

    // 注册时间
    iNewState = m_ctrlCheckRegDate.GetCheck();
    if (iNewState==BST_CHECKED)
    {
        if (!bFlag)
        {
            strSQL += " WHERE ";
            bFlag = TRUE;
        }
        else
        {
            strSQL += " AND ";
        }

        COleDateTime    dtCurrent;
        m_ctrlComRegDate.GetTime(dtCurrent);
        strClause.Format(_T("to_char(regdate,'YYYY-MM')='%s'"),
            dtCurrent.Format(_T("%Y-%m")));
        strSQL += strClause;
    }

    // 业务代码    
    iNewState = m_ctrlCheckSerCode.GetCheck();
    if (iNewState==BST_CHECKED)
    {
        if (!bFlag)
        {
            strSQL += " WHERE ";
            bFlag = TRUE;
        }
        else
        {
            strSQL += " AND ";
        }

        CString strServiceCode;
        m_ctrlComSerCode.GetWindowText(strServiceCode);
        strClause.Format(_T("ServiceCode='%s'"),strServiceCode);

        strSQL += strClause;
    }

    // 城市
    iNewState = m_ctrlCheckCity.GetCheck();
    if (iNewState==BST_CHECKED)
    {
        if (!bFlag)
        {
            strSQL += " WHERE ";
            bFlag = TRUE;
        }
        else
        {
            strSQL += " AND ";
        }

        CString strCity;
        m_ctrlComCity.GetWindowText(strCity);
        strClause.Format(_T("CityName='%s'"),strCity);

        strSQL += strClause;
    }


    // 手机代码
    iNewState = m_ctrlCheckCellPhone.GetCheck();
    if (iNewState==BST_CHECKED)
    {
        if (!bFlag)
        {
            strSQL += " WHERE ";
            bFlag = TRUE;
        }
        else
        {
            strSQL += " AND ";
        }

        CString strCellPhone;
        m_ctrlComCellphone.GetWindowText(strCellPhone);
        strClause.Format(_T("CellphoneNo='%s'"),strCellPhone);

        strSQL += strClause;
    }

    // 根据条件查询
    try
    {
        CAdoRecordSet records;
        records = m_OracleDB.Execute(strSQL);
        //int count = records.GetRecordCount();
        records.MoveFirst();
        while (!records.IsEOF())
        {
            CString strCellPhone;
            records.GetCollect(_T("CellphoneNo"),strCellPhone);

            COleDateTime regDate;
            records.GetCollect(_T("RegDate"),regDate);

            COleDateTime CancelDate;
            records.GetCollect(_T("CancelDate"),CancelDate);

            CString strAgency;
            records.GetCollect(_T("Agency"),strAgency);

            CString strSpNum;
            records.GetCollect(_T("SpNum"),strSpNum);

            CString strServiceCode;
            records.GetCollect(_T("ServiceCode"),strServiceCode);

            CString strCityName;
            records.GetCollect(_T("CityName"),strCityName);

            // 
            m_ctrlList.AddItem(strCellPhone,
                regDate.Format(_T(" %Y-%m-%d %H-%M-%S ")),
                CancelDate.Format(_T(" %Y-%m-%d %H-%M-%S ")),
                strAgency,
                strSpNum,
                strServiceCode,
                strCityName);

            records.MoveNext();
        }
    }
    catch (CException* e)
    {
        e->ReportError();
        e->Delete();
    }
    	
}

void CFeeUsersDlg::OnClose()
{
    m_OracleDB.Close();
    // TODO: 在此添加消息处理程序代码和/或调用默认值

    CDialog::OnClose();
}

//////////////////////////////////////////////////////////////////////////
// Member functions

// 初始化控件变量 
void CFeeUsersDlg::InitControls()
{
    CString strSQL;
    CAdoRecordSet records;
    CString strValue;

    // 取出所有业务代码
    strSQL.Format(_T("SELECT DISTINCT ServiceCode FROM %s"), T_FEEUSERS_NAME);
    records = m_OracleDB.Execute(strSQL);
    //int count = records.GetRecordCount();
    records.MoveFirst();
    while (!records.IsEOF())
    {
        records.GetCollect(_T("ServiceCode"),strValue);
        m_ctrlComSerCode.AddString(strValue);
        records.MoveNext();
    }

    // 取出所有城市代码 
    strSQL.Format(_T("SELECT DISTINCT CityName FROM %s"), T_FEEUSERS_NAME);
    records = m_OracleDB.Execute(strSQL);
    records.MoveFirst();
    while (!records.IsEOF())
    {
        records.GetCollect(_T("CityName"),strValue);
        m_ctrlComCity.AddString(strValue);
        records.MoveNext();
    }

    // 取出所有手机号码    
    strSQL.Format(_T("SELECT DISTINCT CellphoneNo FROM %s"), T_FEEUSERS_NAME);
    records = m_OracleDB.Execute(strSQL);
    records.MoveFirst();
    while (!records.IsEOF())
    {
        records.GetCollect(_T("CellphoneNo"),strValue);
        m_ctrlComCellphone.AddString(strValue);
        records.MoveNext();
    }
}
