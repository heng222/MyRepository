// TVenetianCtrl.cpp: implementation of the TVenetianCtrl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TVenetianCtrl.h"
#include <math.h>

// #define FLOAT_TOLERANCE 0.0001
// inline bool IsEqual(float f1, float f2)
// {
//     return fabs(f1 - f2) < FLOAT_TOLERANCE;
// }
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TVenetianCtrl::TVenetianCtrl()
{

}

TVenetianCtrl::~TVenetianCtrl()
{
    
}

//////////////////////////////////////////////////////////////////////////

void TVenetianCtrl::BuildExtentSegments()
{
    m_ExtSegments.resize(0);
    m_ExtSegments.push_back(TSegmentVector(m_rExtent.iTl,m_rExtent.TopRight()));
    m_ExtSegments.push_back(TSegmentVector(m_rExtent.TopRight(),m_rExtent.iBr));
    m_ExtSegments.push_back(TSegmentVector(m_rExtent.iBr,m_rExtent.BottomLeft()));
    m_ExtSegments.push_back(TSegmentVector(m_rExtent.BottomLeft(),m_rExtent.iTl));
}

void TVenetianCtrl::BuildEdges(TSegmentVector* pSgmStart/*=NULL*/)
{   
    TSegmentVector segSeed;
    if (pSgmStart==NULL)
    {
        // ������Segment��ֱ���߶�(��Segment�ཻ�����ĵ�)
        segSeed = m_SegmentMove;
        TMPoint ptCenter = segSeed.GetCenterPt();
        segSeed.Rotate(ptCenter,FLOAT(PIRADIAN/2));

        // ��edgeSeed�ƶ���SegmentMove����ʼ��
        TVector vTemp(ptCenter,m_SegmentMove.iStartPoint);
        segSeed.Move(vTemp);
    }
    else
    {
        segSeed = *pSgmStart;
    }
    
    // ���㵥λ����ΪWidth����Segmentƽ�е�����(����)
    TMPoint ptRemote;
    m_SegmentMove.GetRemotePoint(ptRemote,m_iBlindWidth);
    TVector vMoveUnit(m_SegmentMove.iStartPoint,ptRemote);

    // Create edges
    INT iNum = INT(m_SegmentMove.GetLength() / m_iBlindWidth)+1; 
    for (INT i=0; i<iNum; i++)
    {
        m_Edges.push_back(segSeed);
        segSeed.Move(vMoveUnit);
    }
}

void TVenetianCtrl::Initialize(TSegmentVector& sgvMove,
                   INT iWidth,
                   TMRect& rExtent,
                   TSegmentVector* pSgmStart/*=NULL*/)
{
    m_SegmentMove = sgvMove;
    m_iBlindWidth = iWidth;
    m_rExtent = rExtent;
    
    BuildExtentSegments();

    BuildEdges(pSgmStart);

    m_ptVetexes.clear();

}

void TVenetianCtrl::AddVetex(const TMPoint& ptVetex)
{
    m_ptVetexes.push_back(ptVetex);
}

void TVenetianCtrl::UpdateProgress(FLOAT fProgress)
{
    m_fProgress = fProgress;
}

BOOL TVenetianCtrl::GetClipRgn(std::vector<HRGN>& arRgnPt) const
{
    // �õ�����ʼ�����ΪiLenMove�ĵ�
    INT iLenMove = m_iBlindWidth*m_fProgress;
    TMPoint ptRemote;
    m_SegmentMove.GetRemotePoint(ptRemote,iLenMove);
    
    // �����ƶ�����
    TVector vMoveUnit(m_SegmentMove.iStartPoint,ptRemote);

    // �ƶ�ÿ���߲������ƶ�ǰ����Extent�Ľ���
    INT iNumEdges = m_Edges.size();
    for (INT i=0; i<iNumEdges; i++)
    {
        TMPolygon polygonToDraw;
        TSegmentVector segMoved = m_Edges[i];
        segMoved.Move(vMoveUnit);

        // ���㽻��
        INT j = 0;
        for (; j<m_ExtSegments.size(); j++)
        {
            TMPoint ptTemp;
            
            // ��ʼ�߶���˱��Ƿ��ཻ
            BOOL bCrossOrg = m_Edges[i].CalcIntersection(m_ExtSegments[j],ptTemp);
            if (bCrossOrg)
            {
                polygonToDraw.AddVertex(ptTemp);
            }

            // �ƶ�����߶���˱��Ƿ��ཻ
            BOOL bCrossMoved = segMoved.CalcIntersection(m_ExtSegments[j],ptTemp);
            if (bCrossMoved)
            {
                polygonToDraw.AddVertex(ptTemp);
            }
        }
        
        TMPolygon polygonExtent;
        polygonExtent.AddEdge(m_Edges[i]);
        polygonExtent.AddEdge(segMoved);
        polygonExtent.Normalize2Convex();
        
        for (INT m=0; m<m_ptVetexes.size(); m++)
        {
            BOOL bFlag = polygonExtent.Contains(m_ptVetexes[m]);
            if (bFlag)
            {
                polygonToDraw.AddVertex(m_ptVetexes[m]);
            }
        }
        
        // Create HRGN
        polygonToDraw.Normalize2Convex();
        HRGN hrgn = polygonToDraw.ToHRGN();
        if (hrgn)
        {
            arRgnPt.push_back(hrgn);
        }
        
    }

    return TRUE;
}
