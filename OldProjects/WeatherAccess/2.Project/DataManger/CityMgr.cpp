#include "StdAfx.h"
#include ".\citymgr.h"
#include "CommonFunc.h"
#include "GlobalMacro.h"
//////////////////////////////////////////////////////////////////////////


//#define  _TRANSFER  // 
//////////////////////////////////////////////////////////////////////////

CCityMgr::CCityMgr(void)
{
}

CCityMgr::~CCityMgr(void)
{
    
}

//////////////////////////////////////////////////////////////////////////
void CCityMgr::ClearList()
{
    while (m_CityList.GetHeadPosition())
    {
        delete m_CityList.RemoveHead();
    }
}
BOOL CCityMgr::ReadInf()
{
#ifdef _TRANSFER

    //////////////////////////////////////////////////////////////////////////
    // 读取MapCityIdx文件
    CStdioFile fileMapCity;
    fileMapCity.Open(GetExePath()+PATH_DATA_FILE+"mapCityIdx.txt",CFile::modeRead|CFile::shareDenyNone);
    CStringList strFileList;
    CString strTemp;
    while (fileMapCity.ReadString(strTemp))
    {
        strFileList.AddTail(strTemp);
    }

    // New file
    CStdioFile filenewFile;
    filenewFile.Open(GetExePath()+PATH_DATA_FILE+"NewFile.txt",CFile::modeCreate|CFile::modeReadWrite|CFile::shareDenyNone);
    CString strNewLine;

    //////////////////////////////////////////////////////////////////////////
#endif


    CString strFileName = GetExePath() + PATH_DATA_FILE + CString( _T("Citys.txt"));

    CStdioFile  fileCitys;
    if (!fileCitys.Open(strFileName,CFile::modeRead|CFile::shareDenyNone))
    {
        AfxMessageBox(_T("没有找到Citys.txt文件"));
        return FALSE;
    }

    int     iNumber = 0;
    CString strLine;

    // 
    PTCityStruton pField = NULL;
    while (fileCitys.ReadString(strLine))
    {
        strLine.Trim();
        if (strLine.Find(";")!=-1)
        {
            continue;
        }

#ifdef _TRANSFER
        strNewLine = strLine;
#endif
        if (strLine.Find(_T("[Field]"))!=-1)
        {
            pField = new TCityStruton;
        }
        else if (strLine.Find(_T("Attri"))!=-1)
        {
            pField->m_iCityAttri = (TCityStruton::TCityAttri)GetNFStr(strLine,1,_T("="));
        }
        else if (strLine.Find(_T("Name"))!=-1)
        {
            pField->m_strCityName = GetSFStr((LPCTSTR)strLine,1,_T("=")).c_str();
        }
        else if (strLine.Find(_T("Item"))!=-1)
        {
            strLine.TrimLeft("Item=");
            int iAttri = (int)GetNFStr(strLine,0,_T(","));
            CString strID = GetSFStr((LPCTSTR)strLine,1,_T(",")).c_str();
            CString strName = GetSFStr((LPCTSTR)strLine,2,_T(",")).c_str();
            WORD wCityIndex = (WORD)GetNFStr(strLine,3,_T(","));
            if (iAttri==int(pField->m_iCityAttri))
            {
                pField->m_strCityID = strID;
                pField->m_strCityName = strName;
                pField->m_wIndex = wCityIndex;
            }
            else
            {
                PTCityStruton pItem = new TCityStruton;
                pItem->m_iCityAttri = (TCityStruton::TCityAttri)iAttri;
                pItem->m_strCityID = strID;
                pItem->m_strCityName = strName;
                pItem->m_wIndex = wCityIndex;
                pField->m_subItemList.AddTail(pItem);
            }

#ifdef _TRANSFER
            POSITION pos = strFileList.GetHeadPosition();
            while (pos)
            {
                CString str = strFileList.GetNext(pos);

                if (str.Find(strName)!=-1)
                {
                    strNewLine = strNewLine + ","+GetSFStr(str,1,_T(",")).c_str();
                    break;
                }
            }

            if (pos==NULL)
            {
                TRACE("\nWaring - %s",strName);
            }
#endif
        }
        else if (strLine.Find(_T("[/Field]"))!=-1)
        {
            m_CityList.AddTail(pField);
        }

#ifdef _TRANSFER
        filenewFile.WriteString(strNewLine);
        filenewFile.WriteString("\n");
#endif
    }

#ifdef _TRANSFER
    fileMapCity.Close();
    filenewFile.Close();

#endif

    fileCitys.Close();

    return TRUE;
}

void CCityMgr::GetCityInf(CCityList*& cityList)
{
    cityList = &m_CityList;
}

PTCityStruton CCityMgr::GetCityByIndex(WORD wCityIdx,const CCityList* pStartAfter) const
{
    if (pStartAfter==NULL)
    {
        pStartAfter = &m_CityList;
    }

    POSITION pos = pStartAfter->GetHeadPosition();
    while (pos)
    {
        PTCityStruton pCity = pStartAfter->GetNext(pos);
        
        if (pCity->m_wIndex==wCityIdx)
        {
            return pCity;
        }
        else
        {
            pCity = GetCityByIndex(wCityIdx,&(pCity->m_subItemList));
            if (pCity!=NULL)
            {
                return pCity;
            }
        }
    }

    return NULL;
}


PTCityStruton CCityMgr::GetCityByCode(const CString& strCode,const CCityList* pStartAfter) const
{
    if (pStartAfter==NULL)
    {
        pStartAfter = &m_CityList;
    }

    POSITION pos = pStartAfter->GetHeadPosition();
    while (pos)
    {
        PTCityStruton pCity = pStartAfter->GetNext(pos);

        if (pCity->m_strCityID==strCode)
        {
            return pCity;
        }
        else
        {
            pCity = GetCityByCode(strCode,&(pCity->m_subItemList));
            if (pCity!=NULL)
            {
                return pCity;
            }
        }
    }

    return NULL;
}

PTCityStruton CCityMgr::GetCityByName(const CString& strName,const CCityList* pStartAfter) const
{
    if (pStartAfter==NULL)
    {
        pStartAfter = &m_CityList;
    }

    POSITION pos = pStartAfter->GetHeadPosition();
    while (pos)
    {
        PTCityStruton pCity = pStartAfter->GetNext(pos);

        if (pCity->m_strCityName==strName)
        {
            return pCity;
        }
        else
        {
            pCity = GetCityByName(strName,&(pCity->m_subItemList));
            if (pCity!=NULL)
            {
                return pCity;
            }
        }
    }

    return NULL;
}






