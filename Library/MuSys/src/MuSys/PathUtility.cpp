#include "StdAfx.h"
#include "PathUtility.h"


TString CPathUtility::GetDirectoryName(const TString& fullPath)
{
    int ipos;
    ipos = fullPath.find_last_of(_T('\\'));

    TString pathName;
    pathName.insert(0, fullPath.c_str(), ipos + 1);
    return pathName;
}
