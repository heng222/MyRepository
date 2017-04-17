// CppUnitTestConsoleApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "CppUnitTestConsoleApp.h"

#include <CONIO.H>
#include "TestRunner.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
    {
        // 
		cout << "使用简单方法的测试类，以TextUi呈现。" << endl;
        CTestRunnerDemo::TextUiRunner_Simple();
        
        // 
		cout << "使用注册方法的测试类，以TextUi呈现。" << endl;
        CTestRunnerDemo::TextUiRunner_Registry();
        
        // 
        cout << "使用注册方法的测试类，以MfcUi呈现。" << endl;
        CTestRunnerDemo::MfcUiRunner_Registry();
        // TODO: code your application's behavior here.
        //CString strHello;
        //strHello.LoadString(IDS_HELLO);
        //cout << (LPCTSTR)strHello << endl;
    }
    
    // 
    cout << "按任意键退出...";
    _getch();
	return nRetCode;
}


