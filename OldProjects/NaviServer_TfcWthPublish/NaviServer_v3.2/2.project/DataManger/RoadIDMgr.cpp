#include "StdAfx.h"
#include ".\roadidmgr.h"
#include "GlobalMacro.h"

CRoadIDMgr::CRoadIDMgr(void)
{
}

CRoadIDMgr::~CRoadIDMgr(void)
{
}

void  CRoadIDMgr::Clear()
{
    // 
    CString key;
    PTRoadIDMap pRoadIDMap = NULL;
    for( POSITION pos = GetStartPosition(); pos != NULL; )
    {
        GetNextAssoc( pos, key, pRoadIDMap );
        delete pRoadIDMap;
    }
    RemoveAll();
}

//////////////////////////////////////////////////////////////////////////


BOOL CRoadIDMgr::ReadMapFile()
{
    // 读取道路编码表
    CString strFileName = GetExePath()+PATH_DATA_FILE+_T("RoadID.ini");
    CStdioFile roadIDFile;
    if (!roadIDFile.Open(strFileName,CFile::modeRead|CFile::shareDenyNone))
    {
        IMsgAppLogs aLog;
        aLog.iLogLevel = IMsgAppLogs::ELL_ERROR;
        aLog.strComments.Format(_T("无法打开文件%s！"),strFileName);
        NbsSendModuleMsg(&aLog);

        return FALSE;
    }

    CString strLine;
    while (roadIDFile.ReadString(strLine))
    {
        strLine.Trim();
        if (!strLine.IsEmpty())
        {
            PTRoadIDMap pRoadIDMap = new TRoadIDMap;
            pRoadIDMap->strRoadID = GetSFStr((LPCTSTR)strLine,0,",").c_str();
            pRoadIDMap->dwRoadID = (DWORD)GetNFStr((LPCTSTR)strLine,1,",");

            SetAt(pRoadIDMap->strRoadID,pRoadIDMap);
        }
    }

    return TRUE;
}