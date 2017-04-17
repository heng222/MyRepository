#ifndef _DISTRICT_MANAGER_FILE_H
#define _DISTRICT_MANAGER_FILE_H

//////////////////////////////////////////////////////////////////////////
#include "afx.h"
#include "UserColors.h"
#include <Geometry.h>
#include "DataModulInterface.h"
#include "NBMapEngine.h"

//////////////////////////////////////////////////////////////////////////
// 
class TDistrict 
{
public:
    enum TState
    {
        EDS_NORMAL,
        EDS_ACTIVE,
    };

    TState          m_iState;

    TMRect          m_boxRect;           // �������Ӿ���
    TMPoint         m_ptCenter;          // ��������ĵ�
    CString         m_strDistName;
    CString         m_strIDistID;

    CMPointArray    m_ptLogicalPosArray; // ������߼���������
    CArray<CPoint,CPoint> m_ptDevicePtArray; // 

    CWthInfList     m_WthInfList;       // ��ص�������Ϣ

public:
    TDistrict()
    {
        m_iState = EDS_NORMAL;
        m_strDistName = "δ֪����";
    }
    ~TDistrict()
    {
        ClearWthList();
    }
    void ClearWthList()
    {
        while (m_WthInfList.GetHeadPosition())
        {
            delete m_WthInfList.RemoveHead();
        }
    }

public:

    //
    void SetActive(BOOL bEnable)
    {
        bEnable? m_iState=EDS_ACTIVE : m_iState=EDS_NORMAL;
    }

    //
    void DrawRegion(CDC* pDC,const MCoorTransProvider& aTransfer) 
    {
        CPen newPen;
        CBrush brush;
        if (m_iState==EDS_ACTIVE)
        {
            newPen.CreatePen(PS_SOLID,2,CLR_RED);
            //brush.CreateHatchBrush(HS_CROSS,CLR_BLACK);
            brush.CreateSolidBrush(CLR_LIGHTYELLOW);
        }
        else
        {
            newPen.CreatePen(PS_SOLID,2,CLR_DARKGREEN);
            brush.CreateHatchBrush(HS_CROSS,CLR_BKG_1);

            /*LOGBRUSH logBrush;
            logBrush. lbStyle = BS_NULL;
            brush.CreateBrushIndirect(&logBrush);*/
        }
        CPen* pOldPen = pDC->SelectObject(&newPen);
        CBrush* pOldBrush = pDC->SelectObject(&brush);
        pDC->SetBkMode(OPAQUE);


        //
        WORD wCount = (WORD)m_ptDevicePtArray.GetCount();
        CPoint* ptArray = m_ptDevicePtArray.GetData();

        // �������
        pDC->Polygon(ptArray,wCount);

        //
        pDC->SelectObject(pOldPen);
        pDC->SelectObject(pOldBrush);

    }

    //
    void DrawName(CDC* pDC,const MCoorTransProvider& aTransfer) 
    {
        WORD wCount = (WORD)m_ptDevicePtArray.GetCount();
        CPoint* ptArray = m_ptDevicePtArray.GetData();
        CRgn rgn;
        rgn.CreatePolygonRgn(ptArray,wCount,ALTERNATE);
        CRect rect;
        rgn.GetRgnBox(rect);
        if (rect.Width()<50)
        {
            return;
        }


        // ���ĵ�
        CPoint pt;
        aTransfer.LpToDp(m_ptCenter,pt);

        // ����Ĭ������
        CFont  font;
        int iFontHeight;
        if (m_iState==EDS_ACTIVE)
        {
            iFontHeight = 14;
            font.CreateFont(iFontHeight,0, 0, 0, FW_BOLD, false, false, 0,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS, "����");
        }
        else
        {
            iFontHeight = 12;
            font.CreateFont(iFontHeight,0, 0, 0, FW_THIN, false, false, 0,
                DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
                DEFAULT_PITCH | FF_SWISS, "����");
        }


        CFont* pOldFont = pDC->SelectObject(&font);
        pDC->SetTextColor(CLR_BLACK);
        pDC->SetBkMode(TRANSPARENT);

        CSize size = pDC->GetTextExtent(m_strDistName);
        if (rect.Width()<rect.Height()) // ����
        {
            BSTR bstr = m_strDistName.AllocSysString();
            int iCount = (int)wcslen(bstr);
            for (int i=0; i<iCount; i++)
            {
                WCHAR wcBuf[5] = {0};
                memcpy(wcBuf,bstr+i,sizeof(WCHAR));
                CString strWord = CString(wcBuf);

                pDC->TextOut(pt.x,pt.y-size.cx/2+i*(iFontHeight+2),strWord);
            }
        }
        else
        {
            pDC->TextOut(pt.x-size.cx/2,pt.y-10,m_strDistName);
        }



        pDC->SelectObject(pOldFont);
    }
};
typedef CTypedPtrList<CPtrList,TDistrict*> CDistrictList;
//////////////////////////////////////////////////////////////////////////
//
//  �����и��������������������ļ�RegionCode.txt�����������ѯ
// 
//
class CBJDistrictMgr :public CNBMapEngine
{
public:
    CBJDistrictMgr(void);
    ~CBJDistrictMgr(void);

public:

    BOOL   ReadRgnData();

    void   Close();

    // ���ݾ�γ�ȵõ��������
    BOOL    GetDistIDByPos(const TMPoint& ptPos,CString& strAreaID) const;
    TDistrict* GetDistrict(const TMPoint& aPt) const;
    TDistrict* GetDistrict(const CPoint& aPt) const;

    void    Draw(CDC* pDC) ;
    BOOL    RetrieveWthInf(); // ���������������������Ϣ
    COleDateTime GetFlashTime() const;

private:

    // From CNBMapEngine
    BOOL OnInitialize(TEgAttri& aAttri,TMRect& mapRect,CSize& sizeGrid);
	void OnActivedRectChanged(const CGridList& listGrid);
    void OnRotatingRadiansChanged(float aNewRotating);

    // 
    void OnBuildingGrid();
    void OnBuildGrid(PTNBMapGrid pGrid);
    void OnGridsBuilt();
    void OnDestroyGrid(PTNBMapGrid pGrid);


private:

    void TransferLogicalPtsToDevicePts(); // ��������߼�����ת��Ϊ�豸����

private:

    TMRect  m_rectMap;
    CDistrictList m_DistrictList;
    COleDateTime  m_timeUpdate;

};


//////////////////////////////////////////////////////////////////////////
#endif