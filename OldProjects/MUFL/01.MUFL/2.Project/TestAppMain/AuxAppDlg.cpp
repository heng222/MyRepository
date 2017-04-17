// AuxAppDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "AuxApp.h"
#include "AuxAppDlg.h"
#include <afxinet.h>
#include "AppLogMgr.h"
#include "XTrace.h"
#include "geometry.h"
#include "XFont.h"
#include "MD5Checksum.h"
#include "RC4.h"
#include "BBCChecksum.h"
#include "SysUtils.h"
#include "CommonFunc.h"
#include "RCChecksum.h"

#include <functional>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CAuxAppDlg �Ի���

CAuxAppDlg::CAuxAppDlg(CWnd* pParent /*=NULL*/)
: CDialog(CAuxAppDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
   
    OnContructor();
}

BOOL CAuxAppDlg::OnInitDialog()
{
    SYSTEM_INFO sysInf;
    GetSystemInfo(&sysInf);
    //
    CoInitialize(NULL);
    CDialog::OnInitDialog();

    // ��\������...\���˵�����ӵ�ϵͳ�˵��С�

    // IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
    ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
    ASSERT(IDM_ABOUTBOX < 0xF000);

    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != NULL)
    {
        CString strAboutMenu;
        strAboutMenu.LoadString(IDS_ABOUTBOX);
        if (!strAboutMenu.IsEmpty())
        {
            pSysMenu->AppendMenu(MF_SEPARATOR);
            pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
        }
    }

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
    //  ִ�д˲���
    SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
    SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // Initialize other values
    OnInitialize();

    //	
    return TRUE;  // ���������˿ؼ��Ľ��㣬���򷵻� TRUE
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Hook
static UINT UWM_HOOK_GETMSG      = ::RegisterWindowMessage(UWM_CHAR_MSG);


void CAuxAppDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_ctrlResult);
}

BEGIN_MESSAGE_MAP(CAuxAppDlg, CDialog)
    ON_REGISTERED_MESSAGE(UWM_HOOK_GETMSG, OnMyHookProcedure)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBtnDBTest)
    ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedGeneric)
    ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedXML)
    ON_BN_CLICKED(IDC_BUTTON3, OnBnClickedHttp)
    ON_WM_CLOSE()
    ON_EN_CHANGE(IDC_EDIT1, &CAuxAppDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CAuxAppDlg ��Ϣ�������


void CAuxAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CAuxAppDlg::OnPaint() 
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

// ���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
HCURSOR CAuxAppDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
// Database test
void CAuxAppDlg::OnBtnDBTest()
{
#if 0
    CAdoConnection m_OracleDB;

    if (!m_OracleDB.ConnectOracle("spacesat_lbs","spacesatlbs","spacesatlbs2006"))
    {
        AfxMessageBox("���ӵ����ݿ������ʧ�ܣ�",MB_ICONERROR);
        return;
    }
    CString strSQL;
    //strSQL.Format(_T("SELECT * FROM T_TRFLIVIDX2 WHERE ROAD_ID='11111111'"));
    strSQL.Format(_T("SELECT * FROM T_TRFLIVIDX2"));

    //
    CAdoRecordSet records;
    records = m_OracleDB.Execute(strSQL);
    int number = records.GetRecordCount();
    records.MoveFirst();

    if (number>0)
    {
        BYTE byTemp;
        int iTemp;
        long lTemp;
        CString strName;

        records.GetCollect("ROAD_NAME",strName);


        records.GetCollect("SPEED",byTemp);
        records.GetCollect("SPEED",iTemp);
        records.GetCollect("SPEED",lTemp);

        records.GetCollect("JAM_LEVEL",byTemp);

        records.GetCollect("JAM_REASON",byTemp);
    }
    m_OracleDB.Close();
#endif
}

//
void CAuxAppDlg::OnBnClickedXML()
{

#if 0
    CStdioFile outFile;
    outFile.Open("Output.txt",CFile::modeReadWrite|CFile::modeCreate|CFile::shareDenyNone);
    CString strNewLine;

    //


    TCHAR strFileName[FILENAME_MAX] = ".\\RawTfcInf.xml";
    CXMLFile m_xmlFile;
    BOOL bFlag = m_xmlFile.load( strFileName, "rr_resp" );

    MSXML2::IXMLDOMNodePtr layersNode=NULL,scaleNode=NULL,layerNode=NULL;



    //
    m_xmlFile.GetNode("body",layersNode);
    int iCount = m_xmlFile.GetChildNodeNum(layersNode);
    MSXML2::IXMLDOMNodeListPtr layersList=layersNode->GetchildNodes();
    long iLength=layersList->Getlength();

    for(long i=0;i<iLength;i++)
    {
        layerNode=layersList->Getitem(i);
        strNewLine = "\n";

        //����layerNode��������
        /*CString strName="",strPath="",strType="",strSize="",strSymbol="",strRenderField="";
        MSXML2::IXMLDOMNamedNodeMapPtr attributeList=layerNode->Getattributes();
        MSXML2::IXMLDOMNodePtr Node=attributeList->getNamedItem("name");
        if(Node) strName=Node->GetnodeValue().bstrVal;
        Node=attributeList->getNamedItem("path");
        if(Node) strPath=Node->GetnodeValue().bstrVal;*/
        bFlag = m_xmlFile.MyLoad(layerNode->Getxml());
        if (!bFlag)
        {
            return;
        }

        CString strValue;
        // ��·ID
        m_xmlFile.GetNodeValue(layerNode,"road_info/road_id",strValue);
        strNewLine += strValue;

        // ��ʼ������
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_pt",strValue);
        strNewLine = strNewLine + "," + strValue;

        // ��ֹ������
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_pt",strValue);
        strNewLine = strNewLine + "," + strValue;

        // �ٶ�
        m_xmlFile.GetNodeValue(layerNode,"road_info/velocity",strValue);
        strNewLine = strNewLine + "," + strValue;

        // ��㾭γ��
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_point_x",strValue);
        strNewLine = strNewLine + "," + strValue;
        m_xmlFile.GetNodeValue(layerNode,"road_info/start_point_y",strValue);
        strNewLine = strNewLine + "," + strValue;


        // �յ㾭γ��
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_point_x",strValue);
        strNewLine = strNewLine + "," + strValue;
        m_xmlFile.GetNodeValue(layerNode,"road_info/end_point_y",strValue);
        strNewLine = strNewLine + "," + strValue;


        //
        outFile.WriteString(strNewLine);





        /*
        structLayer ele;
        ele.strName=strName;
        ele.strPath=strPath;
        ele.nType=atoi(strType);
        ele.nSize=atoi(strSize);
        ele.nSymbol=atoi(strSymbol);
        ele.strRenderField=strRenderField;

        xmlfile.MyLoad(layerNode->Getxml());

        xmlfile.GetNodeValue(layerNode,"layer/outlinecolor/r",ele.nOutlineColorR);
        xmlfile.GetNodeValue(layerNode,"layer/outlinecolor/g",ele.nOutlineColorG);
        xmlfile.GetNodeValue(layerNode,"layer/outlinecolor/b",ele.nOutlineColorB);
        xmlfile.GetNodeValue(layerNode,"layer/fillcolor/r",ele.nFillColorR);
        xmlfile.GetNodeValue(layerNode,"layer/fillcolor/g",ele.nFillColorG);
        xmlfile.GetNodeValue(layerNode,"layer/fillcolor/b",ele.nFillColorB);

        CString strMinScale="",strMaxScale="";
        xmlfile.GetNodeValue(layerNode,"layer/visible/minscale",strMinScale);
        xmlfile.GetNodeValue(layerNode,"layer/visible/maxscale",strMaxScale);
        ele.dMinScale=GetScaleFromString(strMinScale);
        ele.dMaxScale=GetScaleFromString(strMaxScale);

        xmlfile.MyDetach();*/

        //m_LayerArray.Add(ele);
    }
    outFile.Close();
#endif
}


// Http client
void CAuxAppDlg::OnBnClickedHttp()
{

    //#define _HTTP_GET_

#ifdef _HTTP_GET_
    CGenericHTTPClient    httpClient;
    if(httpClient.Request(_T("http://www.baidu.com")))
    {
        LPCTSTR szHTML=httpClient.QueryHTTPResponse();
        m_ctrlResult.SetWindowText(szHTML);
    }
    else
    {
        LPVOID     lpMsgBuffer;
        DWORD dwRet=FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            httpClient.GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPTSTR>(&lpMsgBuffer),
            0,
            NULL);

        MessageBox( reinterpret_cast<LPTSTR>(lpMsgBuffer), _T("ERROR"), MB_OK);
        LocalFree(lpMsgBuffer);
    }
#endif


#ifdef _HTTP_POST_

    CGenericHTTPClient *pClient=new GenericHTTPClient();
    pClient->InitilizePostArguments();
    pClient->AddPostArguments(__TAG_USRID, szUserID);
    pClient->AddPostArguments(__TAG_JUMIN, szSocialIndex);
    pClient->AddPostArguments(__TAG_SRC, szSource);
    pClient->AddPostArguments(__TAG_DST, szDestination);            
    pClient->AddPostArguments(__TAG_FORMAT, szFormat);
    pClient->AddPostArguments(__TAG_SUBJECT, szMessage);

    if(bCharge)
    {
        pClient->AddPostArguments(__TAG_CHARGE, "Y");
    }else
    {
        pClient->AddPostArguments(__TAG_CHARGE, "N");
    }
    pClient->AddPostArguments(__TAG_CPCODE, szCPCode);
    pClient->AddPostArguments(__TAG_FILE, szFile, TRUE);

    if(pClient->Request(szURL,GenericHTTPClient::RequestPostMethodMultiPartsFormData))
    {        
        LPCTSTR szResult=pClient->QueryHTTPResponse();
    }
    else
    {
#ifdef    _DEBUG
        LPVOID     lpMsgBuffer;
        DWORD dwRet=FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER |
            FORMAT_MESSAGE_FROM_SYSTEM,
            NULL,
            pClient->GetLastError(),
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPTSTR>(&lpMsgBuffer),
            0,
            NULL);
        OutputDebugString(reinterpret_cast<LPTSTR>(lpMsgBuffer));
        LocalFree(lpMsgBuffer);
#endif
    }

#endif
}
