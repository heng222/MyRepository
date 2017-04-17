// AuxAppDlg.cpp : 实现文件
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
#include "FontsMgr.h"
#include "TDateTime.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// Hook
static UINT UWM_HOOK_GETMSG      = ::RegisterWindowMessage(UWM_CHAR_MSG);


// CAuxAppDlg 消息处理程序

VOID CAuxAppDlg::OnContructor()
{
}


BOOL CAuxAppDlg::OnInitialize()
{
    //	
    return TRUE;  // 
}

// 
LRESULT CAuxAppDlg::OnMyHookProcedure(WPARAM wParam, LPARAM lParam)
{
    if (!::isprint(wParam) && wParam!=VK_RETURN)
    {
        return 1L;
    }

    CString strOldText;
    m_ctrlResult.GetWindowText(strOldText);

    //
    if (wParam == VK_RETURN)
    {
        m_ctrlResult.SetWindowText(strOldText + _T("\r\n"));
    }
    else
    {
        m_ctrlResult.SetWindowText(strOldText + CString((TCHAR)wParam));
    }

    //
    HDC dcDesktop = ::GetDC(NULL);
    ::TextOut(dcDesktop,10,10,strOldText+CString((TCHAR)wParam),strOldText.GetLength()+1);
    ::ReleaseDC(NULL,dcDesktop);

    return 0L;
}

UINT __cdecl MyControllingFunction( LPVOID pParam )
{
    TRACE("ThreadID = %d!\n",::GetCurrentThreadId());
    Sleep(10000);
    return 1;
}

#define chSTR(x) #x
//#define chMSG(desc) message(__FILE__ "(" chSTR(__LINE__) "):" #desc)
//#define chMSG(desc) message(__LINE__":("#desc")")
#define chMSG(desc) message("(" chSTR(__LINE__) "):" #desc)

#pragma chMSG(Fix this later)

// Generic test
void CAuxAppDlg::OnBnClickedGeneric()
{
	TMPoint pt0(0,0);
	TMPoint pt1(10,30);
	TMPoint pt2;

	try
	{
		CCoordinatesConverter::CartesianToScreen(pt1,pt2);
		CCoordinatesConverter::ScreenToCartesian(pt2,pt1);
	}
	catch(std::exception& e)
	{
		e.what();
	}
	catch(std::exception* p)
	{
		p->what();
		delete p;
	}
	catch(int e)
	{
		int bbb = e;
	}
	catch(...)
	{
		int a = 0;
		int b = 0;
		a = 0;
	}
	return;

	TVector v1(pt0,pt1);
	TVector v2;
	CCoordinatesConverter::CartesianToScreen(v1,v2);
	CCoordinatesConverter::ScreenToCartesian(v2,v1);

	TSegmentVector segV1(pt0,pt1);
	TSegmentVector segV2;
	CCoordinatesConverter::CartesianToScreen(segV1,segV2);
	CCoordinatesConverter::ScreenToCartesian(segV2,segV1);

	TMPolygon polygon1,polygon2;
	polygon1.AddVertex(pt0);
	polygon1.AddVertex(pt1);
	polygon1.AddVertex(pt2);
	CCoordinatesConverter::CartesianToScreen(polygon1,polygon2);
	CCoordinatesConverter::ScreenToCartesian(polygon2,polygon1);
	



    //#define _TEST_HOOK_
#ifdef _TEST_HOOK_
    BOOL bFlag = CSysUtils::LanuchHook(m_hWnd,_T("NotePad.exe"));// 
    if (!bFlag)
    {
        XTRACE(_T("Launch failure!!\n")); 
    }    
#endif
}



void CAuxAppDlg::OnClose()
{
    CSysUtils::UnHook();

    // TODO: Add your message handler code here and/or call default
    CDialog::OnClose();

}

void CAuxAppDlg::OnEnChangeEdit1()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here

}
