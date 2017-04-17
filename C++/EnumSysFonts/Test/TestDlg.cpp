// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include <UserColors.h>
#include ".\testdlg.h"
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CTestDlg 对话框



CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	, m_iTimes(6)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_iTimes);
	DDX_Control(pDX, IDC_COMBO1, m_FontCombo);
	DDX_Control(pDX, IDC_RICHEDIT21, m_RichEdit);
	DDX_Control(pDX, IDC_COMBO2, m_FontSizeCombo);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnCbnSelchangeCombo1)
	ON_CBN_SELCHANGE(IDC_COMBO2, OnCbnSelchangeCombo2)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
END_MESSAGE_MAP()

class __declspec(novtable) Interface1
{
public:
	virtual void SomeFunction1(int)=0;
};
class __declspec(novtable) Interface2
{
public:
	virtual void SomeFunction2(int)=0;
};

class CSample : public Interface1, public Interface2
{
	void SomeFunction1(int iP1)
	{
		TRACE("SomeFunction1? = %d\n",iP1);
	}
	void SomeFunction2(int iP1)
	{
		TRACE("SomeFunction2? = %d,%d\n",iP1);
	}
};

// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	/*CSample sample;
	Interface1* p1 = &sample;
	p1->SomeFunction1(1);
	
	Interface2* p2 = (Interface2*)(p1);
	p2->SomeFunction2(2);*/



	//////////////////////////////////////////////////////////////////////////
	CDialog::OnInitDialog();

	// 将\“关于...\”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	FillFontInfo();
	
	return TRUE;  // 除非设置了控件的焦点，否则返回 TRUE
}

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CTestDlg::OnBnClickedOk()
{
	// DIB info we used to create title pixel-mapping.
	// The system default color policy is: 
	// Initial Whole Black, while output area White-background and Black-text.
	struct {
		BITMAPINFOHEADER bmiHeader;
		DWORD rgbEntries[2];
	} bmi =
	{
		{
			sizeof(BITMAPINFOHEADER),
				0,
				0,
				1,	
				1,	
				BI_RGB,
				0,
				0,
				0
		},
		{
			0x00000000,
				0xFFFFFFFF
			}
	};

	SIZE mTitleSize;
	HDC inDC = m_RichEdit.GetDC()->GetSafeHdc();
	char* mTitle = "Hello! Direct Show!";
	long mDIBWidthInBytes;
	unsigned char *     mTitleDIBBits;
	// We change the system default color policy.
	// That is, we use Black-background and White-text.
	// We do so especially for rotation font using.
	SetBkColor(inDC, RGB(0, 0, 0));
	SetTextColor(inDC, RGB(255, 255, 255));

	// Set tile font here, so we can get the exact size of the title
	//CAutoFont  autoFont;
	//if (mIsFontChanged)
	//{
	//	//	autoFont.CreateFont("Arial");  // Testing
	//	autoFont.CreateFont(mTitleFont);
	//	autoFont.SelectToDC(inDC);
	//}
	GetTextExtentPoint32(inDC, mTitle, lstrlen(mTitle), &mTitleSize);


	// Set proper DIB size here! Important!
	bmi.bmiHeader.biHeight = mTitleSize.cy;
	bmi.bmiHeader.biWidth  = mTitleSize.cx;
	HBITMAP hbm = CreateDIBitmap(inDC, &bmi.bmiHeader, 0, NULL, NULL, 0);
	BOOL   pass = (hbm != NULL);
	// Draw title after selecting DIB into the DC
	if (pass)
	{
		HGDIOBJ hobj = SelectObject(inDC, hbm);
		pass = ExtTextOut(inDC, 0, 0, ETO_OPAQUE | ETO_CLIPPED, NULL, 
			mTitle, lstrlen(mTitle), NULL);
		SelectObject(inDC, hobj);
	}
	// Get the title-drew DIB bits
	if (pass)
	{
		// Attention: To get bitmap data from the DIB object,
		// the scan line must be a multiple of 4 (DWORD)!
		// If the actual bitmap data is not exactly fit for DWORD,
		// The rest of DWORD bits will be filled automatically.
		// So we should expand to bytes and round up to a multiple of 4.
		mDIBWidthInBytes = ((mTitleSize.cx + 31) >> 3) & ~3;

		mTitleDIBBits    = new BYTE[mDIBWidthInBytes * mTitleSize.cy];
		memset(mTitleDIBBits, 0, mDIBWidthInBytes * mTitleSize.cy);

		
		LONG lLines = GetDIBits(inDC, hbm, 0, mTitleSize.cy, (PVOID)mTitleDIBBits, 
			(BITMAPINFO *)&bmi, DIB_RGB_COLORS);
		pass = (lLines != 0);
	}

	// Save to File
	//BYTE* pByBitmap = NULL/*new BYTE[sizeof(BITMAPFILEHEADER)+sizeof(bmi)+mDIBWidthInBytes * mTitleSize.cy]*/;
	//HBITMAP hbmp = CreateDIBSection(inDC,(BITMAPINFO *)&bmi,DIB_RGB_COLORS,(PVOID*)(&pByBitmap),NULL,0);
	//CFile file1;
	//file1.Open("222.bmp",CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone);
	//file1.Write(pByBitmap,sizeof(BITMAPFILEHEADER)+sizeof(bmi)+mDIBWidthInBytes * mTitleSize.cy);
	//file1.Close();

	
	DeleteObject(hbm);
	delete[] mTitleDIBBits;
	// TODO: 在此添加控件通知处理程序代码
	//OnOK();
}

void CTestDlg::OnBnClickedButton1()
{
	UpdateData();

	//
	CDC *pdc = m_RichEdit.GetDC();
	CDC dcMemery;

	dcMemery.CreateCompatibleDC( (CDC*)pdc );


	CBitmap bitmap; 
	bitmap.CreateCompatibleBitmap( pdc,  20,  20); 
	


	dcMemery.SelectObject(&bitmap);
	dcMemery.FillSolidRect(0, 0,20 , 20,CLR_BKG_1);// 默认背景色
	//dcMemery.FloodFill(0, 0,RGB(255,255,255) ); 
	
	// Set default font
	CFont  font;
	int iFontHeight;
	iFontHeight = 16;
	font.CreateFont(iFontHeight,0, 0, 0, FW_BOLD, false, false, 0,
		DEFAULT_CHARSET, OUT_PS_ONLY_PRECIS,
		OUT_SCREEN_OUTLINE_PRECIS, DEFAULT_QUALITY,
		FIXED_PITCH | FF_SWISS, "宋体");
	CFont* pOldFont = dcMemery.SelectObject(&font);

	dcMemery.SetTextColor(CLR_BLACK);
	dcMemery.TextOut(3,3,"A");

	pdc->StretchBlt( 0, 0, 20*m_iTimes, 20*m_iTimes,
		&dcMemery, 0, 0, 20, 20, SRCCOPY );

	//pdc->BitBlt( 0, 0,20*m_iTimes, 20*m_iTimes,&dcMemery,0,0,SRCCOPY);

	ReleaseDC(pdc);

}

//////////////////////////////////////////////////////////////////////////
void CTestDlg::FillFontInfo()
{
	//m_bFontsLimited = bLimitFonts;

	HDC hdc = GetDC()->GetSafeHdc();
	LOGFONT stLogFont;
	ZeroMemory(&stLogFont, sizeof(stLogFont));
	stLogFont.lfCharSet = DEFAULT_CHARSET;
	stLogFont.lfFaceName[0] = '\0';
	//strcpy_s(stLogFont.lfFaceName,"宋体");
	m_aFontInfo.clear();
	EnumFontFamiliesEx(hdc, &stLogFont, S_EnumFontProc, (LPARAM)(&m_aFontInfo), 0);
	sort(m_aFontInfo.begin(), m_aFontInfo.end());

	m_FontCombo.ResetContent();

	for(vector<CFontInfo>::iterator iCurFont = m_aFontInfo.begin(); iCurFont != m_aFontInfo.end(); ++iCurFont)
	{
		if(AllowFontAsLimited(iCurFont->m_strFontName))
		{
			m_FontCombo.AddString(iCurFont->m_strFontName.c_str());
		}
	}

	m_FontCombo.SetCurSel(0);
}

int CALLBACK CTestDlg::S_EnumFontProc(										 
	const LOGFONT *lpelfe,    // logical-font data
	const TEXTMETRIC *lpntme,  // physical-font data
	DWORD FontType,           // type of font
	LPARAM lParam)             // application-defined data
{
	vector<CFontInfo> *pFontList = (vector<CFontInfo> *)lParam;
	ENUMLOGFONTEX *pEnumLogFont = (ENUMLOGFONTEX *)lpelfe;

	BOOL bTrueType = FontType & TRUETYPE_FONTTYPE;
	BOOL bRaster = FontType & RASTER_FONTTYPE;


	string strFontName = bTrueType ? (char*)pEnumLogFont->elfFullName : lpelfe->lfFaceName;

	if(!strcmp((char*)pEnumLogFont->elfScript, "西方") && AllowFontAsLimited(strFontName))
	{
		CFontInfo stNewFontInfo;
		stNewFontInfo.m_strFontName = strFontName;
		stNewFontInfo.m_bRasterFont = bRaster;
		pFontList->push_back(stNewFontInfo);//, anSizeList);
	}

	return 1;
}

BOOL CTestDlg::AllowFontAsLimited(string strFontName)
{
	return TRUE;
	//return (strFontName.size() > 2 && strFontName[0] == 'P' && strFontName[1] == 'L');
}

void CTestDlg::OnCbnSelchangeCombo1()
{
	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	m_RichEdit.GetSelectionCharFormat(cf);

	char szFontName[256];
	int nSel = m_FontCombo.GetCurSel();
	if(nSel != CB_ERR)
	{
		m_FontCombo.GetLBText(m_FontCombo.GetCurSel(), szFontName);
		if(!(cf.dwMask & CFM_FACE) || strcmp(szFontName, cf.szFaceName) != 0)
		{
			cf.dwMask |= CFM_FACE;
			strcpy_s(cf.szFaceName, szFontName);
			VERIFY(m_RichEdit.SetSelectionCharFormat(cf));

			UpdateFontSizes(TRUE);
		}
	}

	m_RichEdit.SetFocus();
}

// on font size changed
void CTestDlg::OnCbnSelchangeCombo2()
{
	CHARFORMAT cf;
	ZeroMemory(&cf, sizeof(CHARFORMAT));
	cf.cbSize = sizeof(CHARFORMAT);
	cf.dwMask |= CFM_SIZE;
	m_RichEdit.GetSelectionCharFormat(cf);
	char szFontSize[8];
	m_FontSizeCombo.GetLBText(m_FontSizeCombo.GetCurSel(), szFontSize);
	ATLTRACE("OnSelchangeFont_size_combo, setting size to %s\n", szFontSize);

	int nCharFormatHeight = atoi(szFontSize) * 20;

	if(!(cf.dwMask & CFM_SIZE) || nCharFormatHeight != cf.yHeight)
	{
		cf.dwMask |= CFM_SIZE;
		cf.yHeight = nCharFormatHeight;
		VERIFY(m_RichEdit.SetSelectionCharFormat(cf));
	}


	m_RichEdit.SetFocus();
}

void CTestDlg::UpdateFontSizes(BOOL bResetRasterSize)
{
	char szSavedFontSize[32];
	m_FontSizeCombo.GetWindowText(szSavedFontSize, 32);
	m_FontSizeCombo.ResetContent();
	int nCurSel = m_FontCombo.GetCurSel();	
	BOOL bRasterFont = FALSE;
	if(nCurSel >= 0)
	{
		HDC hdc = GetDC()->GetSafeHdc();
		if(m_aFontInfo[nCurSel].m_bRasterFont)
		{
			bRasterFont = TRUE;
			list<int> anFontSizes;
			EnumFontFamilies(
				hdc, 
				m_aFontInfo[nCurSel].m_strFontName.c_str(), 
				S_EnumFontFamProcRaster, 
				(LPARAM)&anFontSizes);
			anFontSizes.sort();
			for(list<int>::iterator iSize = anFontSizes.begin(); iSize != anFontSizes.end(); ++iSize)
			{
				char szTemp[8];
				m_FontSizeCombo.AddString(itoa(*iSize, szTemp, 10));
			}
		}
		else
		{
			// Microsoft suggested numbers are 8, 9, 10, 11, 12, 14, 16, 18, 20, 22, 24, 26, 28, 36, 48, 72
			m_FontSizeCombo.AddString("3");
			m_FontSizeCombo.AddString("4");
			m_FontSizeCombo.AddString("5");
			m_FontSizeCombo.AddString("6");
			m_FontSizeCombo.AddString("7");
			m_FontSizeCombo.AddString("8");
			m_FontSizeCombo.AddString("9");
			m_FontSizeCombo.AddString("10");
			m_FontSizeCombo.AddString("11");
			m_FontSizeCombo.AddString("12");
			m_FontSizeCombo.AddString("14");
			m_FontSizeCombo.AddString("16");
			m_FontSizeCombo.AddString("18");
			m_FontSizeCombo.AddString("20");
			m_FontSizeCombo.AddString("22");
			m_FontSizeCombo.AddString("24");
			m_FontSizeCombo.AddString("26");
			m_FontSizeCombo.AddString("28");
			m_FontSizeCombo.AddString("36");
			m_FontSizeCombo.AddString("48");
			m_FontSizeCombo.AddString("72");
			m_FontSizeCombo.AddString("108");
			m_FontSizeCombo.AddString("144");
			m_FontSizeCombo.SetCurSel(1);
		}
	}

	m_FontSizeCombo.SetWindowText(szSavedFontSize);

	if(m_FontSizeCombo.GetCount() && bRasterFont && bResetRasterSize)
	{
		m_FontSizeCombo.SetCurSel(0);
		BOOL bTemp = TRUE;
		//OnSelchangeFont_size_combo(NULL, NULL, NULL, bTemp);
	}
}
int CALLBACK CTestDlg::S_EnumFontFamProcRaster(
	const LOGFONT *lpelf,		// logical-font data
	const TEXTMETRIC *lpntm,	// physical-font data
	DWORD FontType,				// type of font
	LPARAM lParam)				// application-defined data
{
	list<int> *panFontSizes = (list<int> *)lParam;
	int nLogPixelsY = GetDeviceCaps(::GetDC(NULL), LOGPIXELSY);
	int nLogCharHeight = lpelf->lfHeight - lpntm->tmInternalLeading;
	int nPointHeight = (nLogCharHeight * 72 + (nLogPixelsY>>1) ) / nLogPixelsY;
	panFontSizes->push_back(nPointHeight);
	return 1;
}

//#include "D:\\Exercise\\MyComSample\\FontBmp\\FontBmp.h"
void CTestDlg::OnBnClickedButton2()
{
#if 0
	HRESULT hResult;

	if ( !SUCCEEDED(CoInitialize(NULL)) ) {
		printf("Initialize COM library failed!\n");
		return;
	}

	GUID fontbmpClsID;
	hResult = ::CLSIDFromProgID(L"FontBmp.GenerateBmp.1", &fontbmpClsID);
	if (hResult != S_OK) 
	{
		printf("Can't find the FontBmp CLSID!\n");
		return;
	}

	// 查询IDictionary接口
	const GUID IID_GenerateBmp = 
	{ 0x2B9AE3CB, 0xBA4A, 0x4015,
	{ 0xaa, 0x65, 0xa5, 0x00, 0xb4, 0x14, 0x1e, 0x55} } ;

	//UUID IID_GenerateBmp = uuid(2B9AE3CB-BA4A-4015-AA65-A500B4141E55);
	IGenerateBmp* pGernerate;
	hResult = CoCreateInstance(fontbmpClsID, NULL, 
		CLSCTX_INPROC_SERVER, IID_GenerateBmp, (void **)&pGernerate);
	if (hResult != S_OK) {
		printf("QueryInterface IDictionary failed!\n");
		return;
	}


	// Create Bitmap
	HBITMAP hBitmap;
	pGernerate->GenerateBmp("AB",&hBitmap);

	// Draw bitmap
	//////////////////////////////////////////////////////////////////////////
	CDC *pdc = m_RichEdit.GetDC();
	CDC dcMemery;
	CBitmap* pBitmap = CBitmap::FromHandle(hBitmap);
	dcMemery.CreateCompatibleDC( (CDC*)pdc );
	dcMemery.SelectObject(pBitmap);

	pdc->StretchBlt( 0, 0, 50, 50,
		&dcMemery, 0, 0, 50, 50, SRCCOPY );


	ReleaseDC(pdc);

	//////////////////////////////////////////////////////////////////////////

	pGernerate->Release();

	CoUninitialize();
#endif
}

