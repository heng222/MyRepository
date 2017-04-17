#include "StdAfx.h"
#include "Directory.h"
#include "FileUtility.h"
#include "TDateTime.h"
#include "PathUtility.h"
#include <direct.h>



using namespace std;
//////////////////////////////////////////////////////////////////////////

BOOL CDirectory::Exists(const TString& path)
{
    return (_taccess(path.c_str(), 0) != -1);
}

void CDirectory::CreateDirectory(const TString& path)
{
    TCHAR file_name[MAX_PATH] = {0}; 
    _tcscpy_s(file_name, MAX_PATH, path.c_str());

    LPTSTR t = file_name;

    while (t = _tcschr(++t, _T('\\'))) 
    {
        *t = 0;

        if (_taccess(file_name, 0) != -1)
        {
            *t = _T('\\');
            continue;
        }
        
        _tmkdir(file_name);

        *t = _T('\\');
    }
}

void CDirectory::GetFiles(const TString& path, std::list<TString>& files)
{
    _tfinddata_t fileAttri;  
    long findHandle = _tfindfirst(path.c_str(), &fileAttri);  

    // 
    if(findHandle != -1)
    {
        files.clear();

        //
        TString pathName = CPathUtility::GetDirectoryName(path);

        int rc = 0;
        do
        {
            if (fileAttri.name == _T(".."))
            {   
                continue;   
            }
            else if((fileAttri.attrib & _A_SUBDIR) == 0) 
            {
                TString temp(pathName);
                temp.append(fileAttri.name);
                files.push_back(temp);
            }
            rc = _tfindnext(findHandle, &fileAttri);
        }while(rc == 0);
    }   

    _findclose(findHandle);
}

void CDirectory::DeleteExpiredFiles(const TString& path, int expiredDays)
{
    list<TString> files;
    CDirectory::GetFiles(path, files);

    list<TString>::iterator curFilePath = files.begin();
    for(; curFilePath != files.end(); ++curFilePath)
    {
        time_t dt = CFileUtility::GetCreationTime(*curFilePath);
        double diff = TDateTime() - dt;
        if ((dt != 0) && (diff > expiredDays))
        {
            CFileUtility::Delete(*curFilePath);
        }
    }
}