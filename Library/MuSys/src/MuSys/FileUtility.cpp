#include "StdAfx.h"
#include "FileUtility.h"  
#include <io.h> 
//////////////////////////////////////////////////////////////////////////

#include "TDateTime.h"
void CFileUtility::Delete(const TString& path)
{
    _tremove(path.c_str());
}

time_t CFileUtility::GetCreationTime(const TString& path)
{
    time_t rc = 0;

    _tfinddata_t fileAttri;  
    long findHandle = _tfindfirst(path.c_str(), &fileAttri);   

    if(findHandle != -1)
    {
        rc = fileAttri.time_create;
    }

    _findclose(findHandle);
    return rc;

}
