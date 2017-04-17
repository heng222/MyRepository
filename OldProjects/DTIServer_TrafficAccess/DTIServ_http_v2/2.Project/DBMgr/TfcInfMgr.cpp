#include "StdAfx.h"
#include ".\tfcinfmgr.h"
#include <CommonFunc.h>
#include "InterfaceEx.h"
#include "GlobalMacro.h"

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// 
CTfcInfMgr::CTfcInfMgr(void)
{
    m_timeFlash.SetStatus(COleDateTime::null);
    m_rectMap.SetNull();
}

CTfcInfMgr::~CTfcInfMgr(void)
{
    CNBMapEngine::Close();
}

//////////////////////////////////////////////////////////////////////////
// From CMapEngine
BOOL CTfcInfMgr::OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid)
{
    // 修改比例尺
    aAttri.dwMaxScale = 1500;
    aAttri.dwMinScale = 740000;
    aAttri.dwZoomScale = 125000;
    aAttri.fUnitZoom = 2;
    aAttri.fPhysicPerLogic = 1000;  

    // 修改网格属性
    /*mapRect = m_rectMap;
    sizeGrid.cx = 1000;
    sizeGrid.cy = 1000;*/

    return TRUE;
}



//////////////////////////////////////////////////////////////////////////
//

BOOL CTfcInfMgr::Open()
{
#ifdef _DEBUG
    CStdioFile  tfcEventFile;
    if ( !tfcEventFile.Open(GetExePath()+PATH_DATA_FILE+_T("TEST_TFCEVENT.txt"),CFile::modeRead|CFile::shareDenyNone) )
    {
        return FALSE;
    }

    CString strLine;

    while ( tfcEventFile.ReadString(strLine) )
    {
        int iIdx = 0;
        CString strValue;

        PTTfcEventAttri pTfcEvent = new TTfcEventAttri;

        pTfcEvent->m_strEventID = GetSFStr((LPCTSTR)strLine,iIdx++,"@").c_str();
        pTfcEvent->m_strEventID.Trim();

        strValue = GetSFStr((LPCTSTR)strLine,iIdx++,"@").c_str();
        pTfcEvent->m_timeAlarm.ParseDateTime(strValue);

        pTfcEvent->m_iEventType = (int)GetNFStr(strLine,iIdx++,"@");

        pTfcEvent->m_strContent = GetSFStr((LPCTSTR)strLine,iIdx++,"@").c_str();
        pTfcEvent->m_strContent.Trim();

        pTfcEvent->m_iHandledState = (int)GetNFStr(strLine,iIdx++,"@");

        pTfcEvent->m_iValid = (int)GetNFStr(strLine,iIdx++,"@");

        pTfcEvent->m_strCaseAddr = GetSFStr((LPCTSTR)strLine,iIdx++,"@").c_str();
        pTfcEvent->m_strCaseAddr.Trim();

        pTfcEvent->m_strPhoneNo = GetSFStr((LPCTSTR)strLine,iIdx++,"@").c_str();
        pTfcEvent->m_strPhoneNo.Trim();

        pTfcEvent->m_ptPhonePos.iX = LONG(GetFloatFromStr(strLine,iIdx++,"@")*3600*24);
        pTfcEvent->m_ptPhonePos.iY = LONG(GetFloatFromStr(strLine,iIdx++,"@")*3600*24);

        pTfcEvent->m_ptAddrPos.iX = LONG(GetFloatFromStr(strLine,iIdx++,"@")*3600*24);
        pTfcEvent->m_ptAddrPos.iY = LONG(GetFloatFromStr(strLine,iIdx++,"@")*3600*24);

        // Save to database
        m_TfcEvtList.AddTail(pTfcEvent);
        
    }

    tfcEventFile.Close();
#endif

    return TRUE;
}

void CTfcInfMgr::SetAt(LPCTSTR key,PIMsgRawTrafInf newValue)
{
    m_RawTfcList.AddItem(key,newValue);
}

INT_PTR CTfcInfMgr::GetRoadCount() const
{
    return m_RawTfcList.GetCount();        
}

COleDateTime CTfcInfMgr::GetUpdateTime() const
{
	if (m_RawTfcList.GetCount()>0)
	{
		POSITION pos = m_RawTfcList.GetStartPosition();

		CString key;

		PIMsgRawTrafInf pa;

		while (pos)
        {
            m_RawTfcList.GetNextAssoc( pos, key, (void*&)pa );
            if (pa->m_tfcRawRoadInf.timePublish.GetStatus()==COleDateTime::valid)
            {
                return pa->m_tfcRawRoadInf.timePublish;
            }
		}

        COleDateTime invalidTime;
        invalidTime.SetStatus(COleDateTime::null);
        return invalidTime;

	}
	else
	{
		COleDateTime invalidTime;
		invalidTime.SetStatus(COleDateTime::null);
		return invalidTime;
	}
}

COleDateTime CTfcInfMgr::GetFlashTime() const
{
    return m_timeFlash;
}

void CTfcInfMgr::UpdateFlashTime()
{
    m_timeFlash = COleDateTime::GetCurrentTime();
}

void CTfcInfMgr::DrawTfcStream(CDC* pDC,BOOL bDrawName)
{
    m_RawTfcList.DrawRoad(pDC,*this);

    if (bDrawName)
    {
        m_RawTfcList.DrawNodeName(pDC,*this);
    }
}
void CTfcInfMgr::Close()
{
    // clear traffic stream information
    m_RawTfcList.ClearList();

    // clear traffic events information
    while (m_TfcEvtList.GetHeadPosition())
    {
        delete m_TfcEvtList.RemoveHead();
    }
}

CTfcEventList&  CTfcInfMgr::RetrieveTfcEvents()
{
    return m_TfcEvtList;
}

PTTfcEventAttri CTfcInfMgr::GetTfcEvent(CPoint ptPos) const
{
    POSITION pos = m_TfcEvtList.GetHeadPosition();
    while (pos)
    {
        PTTfcEventAttri pTfcEvt = m_TfcEvtList.GetNext(pos);

        // Draw Event
        if (pTfcEvt->m_ptPhonePos.iX!=0)
        {
            CPoint point;
            LpToDp(pTfcEvt->m_ptPhonePos,point);
            CRect rect(point,CSize(8,8));
            if (rect.PtInRect(ptPos))
            {
                return pTfcEvt;
            }
        }
    }

    return  NULL;

}

void CTfcInfMgr::DrawTfcEvent(CDC* pDC)
{
    POSITION pos = m_TfcEvtList.GetHeadPosition();

    CBrush brush;
    brush.CreateSolidBrush(CLR_RED);
    CBrush* pOldBrush = pDC->SelectObject(&brush);

    CPen pen;
    pen.CreatePen(PS_SOLID,1,CLR_DARKYELLOW);
    CPen* pOldPen = pDC->SelectObject(&pen);

    while (pos)
    {
        PTTfcEventAttri pTfcEvt = m_TfcEvtList.GetNext(pos);
        
        pTfcEvt->DrawSelf(pDC,*this);
    }

    pDC->SelectObject(pOldBrush);
    pDC->SelectObject(pOldPen);

}