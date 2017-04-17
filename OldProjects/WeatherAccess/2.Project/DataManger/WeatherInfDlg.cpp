// WeatherInfDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "WeatherInfDlg.h"
#include "DataModulInterface.h"
#include ".\weatherinfdlg.h"


// CWeatherInfDlg 对话框

IMPLEMENT_DYNAMIC(CWeatherInfDlg, CDialog)
CWeatherInfDlg::CWeatherInfDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWeatherInfDlg::IDD, pParent)
    , m_strWeather(_T(""))
{
}

CWeatherInfDlg::~CWeatherInfDlg()
{
}

void CWeatherInfDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_TREE1, m_ctrlTree);
    DDX_Text(pDX, IDC_EDIT_WTHINF, m_strWeather);
    DDX_Control(pDX, IDC_COMBO_PERIOD, m_ctrlPeriod);
}


BEGIN_MESSAGE_MAP(CWeatherInfDlg, CDialog)
    ON_BN_CLICKED(IDC_BTN_QUERY, OnBnClickedBtnQuery)
    ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, OnTvnSelchangedTree)
END_MESSAGE_MAP()


// CWeatherInfDlg 消息处理程序


BOOL CWeatherInfDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    m_ctrlPeriod.SetCurSel(0);

    // TODO:  在此添加额外的初始化
    // 1. Create ImageList and associated it with TreeView
    m_imageList.Create(16,16, ILC_COLOR8|ILC_MASK,300,10);
    //m_imageList.SetBkColor(::GetSysColor(COLOR_BTNFACE));
    m_imageList.Add(AfxGetApp()->LoadIcon(IDI_ICON_CHINA));
    m_ctrlTree.SetImageList(&m_imageList, TVSIL_NORMAL);

    // 2. Initialize tree structure with common values
    TV_INSERTSTRUCT hInsertTvStruc;
    hInsertTvStruc.hParent = NULL;
    hInsertTvStruc.hInsertAfter = TVI_LAST;
    hInsertTvStruc.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;
    hInsertTvStruc.item.hItem = NULL; 
    hInsertTvStruc.item.state = 0;
    hInsertTvStruc.item.stateMask = 0;
    hInsertTvStruc.item.cchTextMax = 20;
    hInsertTvStruc.item.cChildren = 0;
    hInsertTvStruc.item.lParam = 0;
    hInsertTvStruc.item.pszText = "中国";
    hInsertTvStruc.item.iImage = 0;
    hInsertTvStruc.item.iSelectedImage = 0;
    HTREEITEM hRtChina = m_ctrlTree.InsertItem(&hInsertTvStruc);

    // 添加下属元素
    IMsgRetrieveCityInf cityInf;
    NbsSendModuleMsg(&cityInf);
    
    AddCityToTree(hRtChina,cityInf.m_cityInf);

    m_ctrlTree.Expand(hRtChina,TVE_EXPAND   );

   
    return TRUE;
   
}
void CWeatherInfDlg::AddCityToTree(HTREEITEM hParent,CCityList* pCityList)
{
    POSITION pos = pCityList->GetHeadPosition();
    if (pos==NULL)
    {
        return;
    }

    PTCityStruton pCityStru;
    while (pos)
    {
        pCityStru = pCityList->GetNext(pos);

        TV_INSERTSTRUCT hInsertTVI;
        hInsertTVI.hParent = hParent;
        hInsertTVI.hInsertAfter = TVI_LAST;
        hInsertTVI.item.mask = TVIF_IMAGE|TVIF_SELECTEDIMAGE|TVIF_TEXT|TVIF_PARAM;
        hInsertTVI.item.hItem = NULL; 
        hInsertTVI.item.state = 0;
        hInsertTVI.item.stateMask = 0;
        hInsertTVI.item.cchTextMax = 20;
        hInsertTVI.item.cChildren = 0;
        hInsertTVI.item.lParam = 0;
        hInsertTVI.item.pszText = pCityStru->m_strCityName.GetBuffer(0);
        hInsertTVI.item.iImage = 0;
        hInsertTVI.item.iSelectedImage = 0;

        HTREEITEM h = m_ctrlTree.InsertItem(&hInsertTVI);
        AddCityToTree(h,&pCityStru->m_subItemList);
    }
}
void CWeatherInfDlg::OnBnClickedBtnQuery()
{
    IMsgRetriveCityWthInf msg;
    msg.strCityName = m_strCityName;
    NbsSendModuleMsg(&msg);

    m_strWeather = m_strCityName + ": " + msg.strWthInf;
    UpdateData(FALSE);
}

void CWeatherInfDlg::OnTvnSelchangedTree(NMHDR *pNMHDR, LRESULT *pResult)
{
    LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
    // TODO: 在此添加控件通知处理程序代码

    HTREEITEM hSelected = pNMTreeView->itemNew.hItem;

    if (hSelected != NULL && !m_ctrlTree.ItemHasChildren(hSelected)) 
    {
        char text[31];
        TV_ITEM item;
        item.mask = TVIF_HANDLE | TVIF_TEXT| TVIF_PARAM;
        item.hItem = hSelected;
        item.pszText = text;
        item.cchTextMax = sizeof(text)-1;
        VERIFY(m_ctrlTree.GetItem(&item));
        m_strCityName = text;
        OnBnClickedBtnQuery();
    }

    // TODO: 在此添加控件通知处理程序代码
    *pResult = 0;
}
