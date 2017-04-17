#include "stdafx.h"
#include ".\areaidmgr.h"

CAreaIDMgr::CAreaIDMgr(void)
{
}

CAreaIDMgr::~CAreaIDMgr(void)
{
    ClearInf();
}

// �������������Ϣ
void CAreaIDMgr::ClearInf(void)
{
    while (GetHeadPosition())
    {
        delete (PTAreaInf)RemoveHead();
    }
}

// �������ļ��ж�ȡ������
BOOL CAreaIDMgr::ReadFile(LPCSTR lpFileName)
{
    CFile fAreaFile;
    if (!fAreaFile.Open(lpFileName,CFile::modeRead))
    {
        return FALSE;
    }
    fAreaFile.Close();
    
    //
    CString strLine;
    PTAreaInf pAreaInf = NULL;
    CStdioFile stdioFile(lpFileName,CFile::modeRead|CFile::shareDenyNone);
    while (stdioFile.ReadString(strLine))
    {
        strLine.TrimLeft();
        strLine.TrimRight();
        //
        if (strLine=="[ITEM]")
        {
            pAreaInf = new TAreaInf;
            AddTail(pAreaInf);
        }
        else if (strLine.Left(3) == "FID")
        {
            pAreaInf->strFID = GetSValue(strLine);
        }
        else if (strLine.Left(5) == "FNAME")
        {
            pAreaInf->strFName = GetSValue(strLine);
        }
        else if (strLine.Left(3)=="TID")
        {
            pAreaInf->strTID = GetSValue(strLine);
        }
        else if (strLine.Left(5)=="TNAME")
        {
            pAreaInf->strTName = GetSValue(strLine);
        }
    }
    //
    return TRUE;
}

// ת������ID
void CAreaIDMgr::TransferID(const CString strAreaID, BOOL bDirection,CStringList& strList)
{
    POSITION pos = GetHeadPosition();
    while (pos)
    {
        PTAreaInf pAreaInf = (PTAreaInf)GetNext(pos);
        //
        if (bDirection)
        {
            if (pAreaInf->strTID==strAreaID)
            {
                strList.AddTail(pAreaInf->strFID);
            }
        }
        else
        {
            if (pAreaInf->strFID==strAreaID)
            {
                strList.AddTail(pAreaInf->strTID);
            }
        }
    }
}
// ����AreaID�õ�AreaName
void CAreaIDMgr::GetAreaName(const CString& strAreaID,CString& strAreaName) const
{
    POSITION pos = GetHeadPosition();
    while (pos)
    {
        PTAreaInf pAreaInf = (PTAreaInf)GetNext(pos);
        //
        if (pAreaInf->strTID.CompareNoCase(strAreaID)==0)
        {
            strAreaName = pAreaInf->strTName;
            break;
        }
    }
}
CString CAreaIDMgr::GetSValue(const CString& strLine)
{
    int iStart = strLine.Find("=");
    CString strValue = strLine.Right(strLine.GetLength()-iStart-1);
    strValue.TrimLeft();
    strValue.TrimRight();
    return strValue;
}
