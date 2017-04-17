/*
 * $ Generic HTTP Client
 * ----------------------------------------------------------------------------------------------------------------
 *
 * name :          CGenericHTTPClient
 *
 * version tag :     0.1.0
 *
 * description :    HTTP Client using WININET
 *
 * author :          Heo Yongsun ( gooshin@opentown.net )
 *
 * This code distributed under BSD LICENSE STYLE.
 */

#ifndef __GENERIC_HTTP_CLIENT_A45YUI89
#define __GENERIC_HTTP_CLIENT_A45YUI89

#include <afxwin.h>
#include <tchar.h>
#include <wininet.h>

// use stl
#include <vector>

// PRE-DEFINED CONSTANTS
#define __DEFAULT_AGENT_NAME	_T("MERONG(0.9/;p)")

// PRE-DEFINED BUFFER SIZE
#define	__SIZE_HTTP_ARGUMENT_NAME	256
#define __SIZE_HTTP_ARGUMENT_VALUE	1024

#define __HTTP_VERB_GET	    _T("GET")
#define __HTTP_VERB_POST    _T("POST")
#define __HTTP_ACCEPT_TYPE  _T("*/*")
#define __HTTP_ACCEPT       _T("Accept: */*\r\n")
#define __SIZE_HTTP_BUFFER	100000
#define __SIZE_HTTP_RESPONSE_BUFFER	100000
#define __SIZE_HTTP_HEAD_LINE	2048

#define __SIZE_BUFFER	1024
#define __SIZE_SMALL_BUFFER	256

class AFX_EXT_CLASS CGenericHTTPClient 
{
public:

    // ARGUMENTS STRUCTURE
	typedef struct __GENERIC_HTTP_ARGUMENT
    {							
		TCHAR	szName[__SIZE_HTTP_ARGUMENT_NAME];
		TCHAR	szValue[__SIZE_HTTP_ARGUMENT_VALUE];
		DWORD	dwType;
		BOOL operator==(const __GENERIC_HTTP_ARGUMENT &argV)
    {
			return !_tcscmp(szName, argV.szName) && !_tcscmp(szValue, argV.szValue);
		}
	}GenericHTTPArgument;

    // REQUEST METHOD
	enum RequestMethod
    {															
		RequestUnknown=0,
		RequestGetMethod=1, // HTTP GET REQUEST 
		RequestPostMethod=2,    // HTTP POST REQUEST 
		RequestPostMethodMultiPartsFormData=3 // HTTP POST REQUEST with BINARY FORM DATA
	};

    // POST TYPE 
	enum TypePostArgument
    {													
		TypeUnknown=0,
		TypeNormal=1,
		TypeBinary=2
	};

	// CONSTRUCTOR & DESTRUCTOR
	CGenericHTTPClient();
	virtual ~CGenericHTTPClient();

	static CGenericHTTPClient::RequestMethod GetMethod(int nMethod);
	static CGenericHTTPClient::TypePostArgument GetPostArgumentType(int nType);

	
    /*
        Connection handler
    */
    // connects to HTTP Server. 
	BOOL Connect(   LPCTSTR szAddress, 
                    LPCTSTR szAgent = __DEFAULT_AGENT_NAME, 
                    unsigned short nPort = INTERNET_DEFAULT_HTTP_PORT, 
                    LPCTSTR szUserAccount = NULL, 
                    LPCTSTR szPassword = NULL);
    // closes connection. These are used with RequestOfURI(...).
	BOOL Close();
    // initializes post arguments. 
	VOID InitilizePostArguments();

	// HTTP Arguments handler	
    // is supported so that you can add new post arguments of the following 3 types ( TCHAR, DWORD, FILE).
	VOID AddPostArguments(LPCTSTR szName, DWORD nValue);
	VOID AddPostArguments(LPCTSTR szName, LPCTSTR szValue, BOOL bBinary = FALSE);

	// HTTP Method handler 
    // method is for you to attempt request for HTTP REQUEST( GET, POST, POST-MULTIPARTFORMDATA) with URL. HTTP METHOD indirector have 3 types. 
	BOOL Request(LPCTSTR szURL, int nMethod = CGenericHTTPClient::RequestGetMethod, LPCTSTR szAgent = __DEFAULT_AGENT_NAME);

    // method is that you could have attempt request for HTTP REQUEST with URI. This method is used with Connect(...) and Close(). 
    BOOL RequestOfURI(LPCTSTR szURI, int nMethod = CGenericHTTPClient::RequestGetMethod);

    // method is that you have HTTP Response by BYTES. 
    BOOL Response(PBYTE pHeaderBuffer, DWORD dwHeaderBufferLength, PBYTE pBuffer, DWORD dwBufferLength, DWORD &dwResultSize);	
	
    // method is you have receive HTML of your HTTP REQUEST. 
    LPCTSTR QueryHTTPResponse();

    // method is you have receive HTTP HEADER about QueryHTTPResponse(). 
    LPCTSTR QueryHTTPResponseHeader();	

	// General Handler
    // method is you get windows error code. 
	DWORD GetLastError();
    // method is you have get MIME-TYPE. 
	LPCTSTR GetContentType(LPCTSTR szName);
    // method parse URL to protocol(HTTP, HTTPS) and address(or hostname) and port, URI.
	VOID ParseURL(LPCTSTR szURL, LPTSTR szProtocol, LPTSTR szAddress, DWORD &dwPort, LPTSTR szURI);

	
protected:				
	std::vector<GenericHTTPArgument> _vArguments;				// POST ARGUMENTS VECTOR

	TCHAR		_szHTTPResponseHTML[__SIZE_HTTP_BUFFER];		// RECEIVE HTTP BODY
	TCHAR		_szHTTPResponseHeader[__SIZE_HTTP_BUFFER];	// RECEIVE HTTP HEADR

	HINTERNET _hHTTPOpen;				// internet open handle
	HINTERNET _hHTTPConnection;		// internet connection handle
	HINTERNET _hHTTPRequest;		// internet request handle

	DWORD		_dwError;					// LAST ERROR CODE
	LPCTSTR		_szHost;					 //	 HOST NAME
	DWORD		_dwPort;					//  PORT

	// HTTP Method handler
	DWORD ResponseOfBytes(PBYTE pBuffer, DWORD dwSize);
	DWORD GetPostArguments(LPTSTR szArguments, DWORD dwLength);
	BOOL RequestPost(LPCTSTR szURI);
	BOOL RequestPostMultiPartsFormData(LPCTSTR szURI);
	BOOL RequestGet(LPCTSTR szURI);
	DWORD AllocMultiPartsFormData(PBYTE &pInBuffer, LPCTSTR szBoundary = _T("--MULTI-PARTS-FORM-DATA-BOUNDARY-"));
	VOID FreeMultiPartsFormData(PBYTE &pBuffer);
	DWORD GetMultiPartsFormDataLength();
};

#endif	// #ifndef __GENERIC_HTTP_CLIENT

/************************************************************************/
/*  Usage:

    1. Simple  HTTP GET REQUEST iteration.

    CGenericHTTPClient    httpClient;
    if(httpClient.Request("http://www.baidu.com"))
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

        MessageBox( reinterpret_cast<LPTSTR>(lpMsgBuffer), "ERROR", MB_OK);
        LocalFree(lpMsgBuffer);
    }


    // -------------------------------------------------------------------------------
    2. HTTP POST REQUEST with file posting ( HTTP POST Multipart/form-data)    

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

*/
/*********************************************************************************************/