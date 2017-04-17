#include "stdafx.h"
#include "DistrictMgr.h"
#include "CommonFunc.h"
#include "GlobalMacro.h"
#include "UserColors.h"

#pragma warning(disable:4244)
//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////

CBJDistrictMgr::CBJDistrictMgr(void)
{
    
}

CBJDistrictMgr::~CBJDistrictMgr(void)
{
    Close();
}

//////////////////////////////////////////////////////////////////////////
// From CNBMapEngine

BOOL CBJDistrictMgr::OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid)
{
    aAttri.ptMapCenter = TMPoint(10065600,3478464);
    aAttri.dwZoomScale = 950000;

    return TRUE;
}


void CBJDistrictMgr::OnActivedRectChanged(const CGridList& listGrid)
{
    TransferLogicalPtsToDevicePts();
}


void CBJDistrictMgr::OnRotatingRadiansChanged(float /*aNewRotating*/)
{
    TransferLogicalPtsToDevicePts();
}



//////////////////////////////////////////////////////////////////////////
// 

BOOL CBJDistrictMgr::ReadRgnData()
{
    CString strFileName = GetExePath() +PATH_DATA_FILE+CString( _T("RegionCode.txt"));

    CStdioFile  stdFile;
    if (!stdFile.Open(strFileName,CFile::modeRead|CFile::shareDenyNone))
    {
        AfxMessageBox(_T("没有找到RegionCode.txt文件"));
        return FALSE;
    }

    //
    int     iNumber = 0;
    CString strLine;

    // 找到区域的个数
    while (stdFile.ReadString(strLine))
    {
        if (strLine.Find(_T("Number"))!=-1)
        {
            iNumber = atoi(GetSFStr((LPCSTR)strLine,1,"=").c_str());
            break;
        }
    }

    //
    CString strRegion;
    CString strPoint;
    for (int n=0; n<iNumber; n++)
    {
        TDistrict* pNewRegion = NULL;

        // 寻找 [RegionX]
        BOOL bFileEnd = FALSE;
        strRegion.Format(_T("Region%d"),n+1);
        bFileEnd = !stdFile.ReadString(strLine);
        while (!bFileEnd)
        {
            if (strLine.Find(strRegion)!=-1)
            {
                pNewRegion = new TDistrict;
                pNewRegion->m_strIDistID = GetSFStr((LPCSTR)strLine,1,_T("=")).c_str();
                pNewRegion->m_strIDistID.Trim(_T(" "));
                break;
            }
            bFileEnd = !stdFile.ReadString(strLine);
        }
        if (bFileEnd)
        {
            return FALSE;
        }

        // 寻找[PointX]
        int iPtIdx = 0;


        BOOL bFlag = FALSE;
        strPoint.Format(_T("Point%d"),n+1);
        while (stdFile.ReadString(strLine))
        {
            if (!bFlag && strLine.Find(strPoint)!=-1) //[Point1]
            {
                WORD wNumPt = (WORD)atoi(GetSFStr((LPCSTR)strLine,1,_T("=")).c_str());
                pNewRegion->m_ptLogicalPosArray.SetSize(0,wNumPt);
                bFlag = TRUE;
            }
            else if (strLine.Find(_T("Name"))!=-1) // [Name1]
            {
                pNewRegion->m_strDistName = GetSFStr((LPCSTR)strLine,1,_T("=")).c_str();
                pNewRegion->m_strDistName.Trim();
            }
            else if (strLine.Find(_T("PointEnd"))!=-1) // [PointEnd]
            {
            }
            else if (strLine.Find(_T("RegionEnd"))!=-1) // [RegionEnd]
            {
                CRgn rgn;
                CPoint* ptArray = (CPoint*)pNewRegion->m_ptLogicalPosArray.GetData();
                int iCount = pNewRegion->m_ptLogicalPosArray.GetCount();
                rgn.CreatePolygonRgn(ptArray,iCount,ALTERNATE);
                CRect rect;
                rgn.GetRgnBox(rect);
                pNewRegion->m_boxRect.Copy(rect);
                pNewRegion->m_ptCenter.iX = rect.CenterPoint().x;
                pNewRegion->m_ptCenter.iY = rect.CenterPoint().y;
                    
                m_DistrictList.AddTail(pNewRegion);
                break;
            }
            else
            {
                CString strX,strY;
                strX = GetSFStr((LPCSTR)strLine,0,_T(" ")).c_str();
                strY = GetSFStr((LPCSTR)strLine,1,_T(" ")).c_str();
                if (strX.GetLength()!=0 && strY.GetLength()!=0)
                {
                    TMPoint ptPos;
                    ptPos.iX = LONG(atof(strX)*3600*24);
                    ptPos.iY = LONG(atof(strY)*3600*24);
                    pNewRegion->m_ptLogicalPosArray.Add(ptPos);
                    iPtIdx ++;
                }
            }
        }

    }

    stdFile.Close();

    return TRUE;
}

void CBJDistrictMgr::Close()
{
    while (m_DistrictList.GetHeadPosition())
    {
        delete m_DistrictList.RemoveHead();
    }

    // 
    CNBMapEngine::Close();
}

BOOL CBJDistrictMgr::GetDistIDByPos(const TMPoint& ptPos,CString& strAreaID) const
{
    TDistrict* pDist = GetDistrict(ptPos);
    if (pDist!=NULL)
    {
        strAreaID = pDist->m_strIDistID;
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

TDistrict* CBJDistrictMgr::GetDistrict(const CPoint& aPt) const
{
    POSITION pos = m_DistrictList.GetHeadPosition();
    while (pos)
    {
        TDistrict* pRegion = m_DistrictList.GetNext(pos);
        CRgn rgn;
        rgn.CreatePolygonRgn(pRegion->m_ptDevicePtArray.GetData(),
                    pRegion->m_ptLogicalPosArray.GetCount(),ALTERNATE);
        if (rgn.PtInRegion(aPt))
        {
            return pRegion;
        }
    }

    return NULL;
}

TDistrict* CBJDistrictMgr::GetDistrict(const TMPoint& ptPos) const
{
    CPoint point(ptPos.iX,ptPos.iY);
    POSITION pos = m_DistrictList.GetHeadPosition();
    while (pos)
    {
        TDistrict* pRegion = m_DistrictList.GetNext(pos);
        CRgn rgn;
        rgn.CreatePolygonRgn((CPoint*)(pRegion->m_ptLogicalPosArray.GetData()),
            pRegion->m_ptLogicalPosArray.GetCount(),ALTERNATE);
        if (rgn.PtInRegion(point))
        {
            return pRegion;
        }
    }

    return NULL;
}

//////////////////////////////////////////////////////////////////////////
// 

void CBJDistrictMgr::TransferLogicalPtsToDevicePts()
{
    POSITION pos = m_DistrictList.GetHeadPosition();
    while (pos)
    {
        TDistrict* pRegion = (TDistrict*)(m_DistrictList.GetNext(pos));

        // translate the coordinates.
        WORD wCount = pRegion->m_ptLogicalPosArray.GetCount();
        pRegion->m_ptDevicePtArray.SetSize(wCount,1);
        for (WORD ii=0; ii<wCount; ii++)
        {
            TMPoint ptMap = pRegion->m_ptLogicalPosArray[ii];
            CPoint ptScreen;
            LpToDp(ptMap,ptScreen);
            pRegion->m_ptDevicePtArray.SetAt(ii,ptScreen);
        }
    }
}



COleDateTime CBJDistrictMgr::GetFlashTime() const
{
    return m_timeUpdate;
}



