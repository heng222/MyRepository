// TVenetianCtrl.h: interface for the TVenetianCtrl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TVENETIANCTRL_H__B01750B6_2CDE_4276_B9F2_D4B0FC1F958B__INCLUDED_)
#define AFX_TVENETIANCTRL_H__B01750B6_2CDE_4276_B9F2_D4B0FC1F958B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TMPoint.h"
//////////////////////////////////////////////////////////////////////////

class TVenetianCtrl  
{
public:

	TVenetianCtrl();
	virtual ~TVenetianCtrl();

public:
    
    void    Initialize(TSegmentVector& sgvMove,
                       INT iWidth,
                       TMRect& rExtent,
                       TSegmentVector* pSgmStart=NULL);

    void    AddVetex(const TMPoint& ptVetex);

    void    UpdateProgress(FLOAT fProgress);

    BOOL    GetClipRgn(std::vector<HRGN>& arRgnPt) const;

private:

    void    BuildEdges(TSegmentVector* pSgmStart=NULL);
    void    BuildExtentSegments();

private:
    
    TSegmentVector  m_SegmentMove;  // �����߶�����

    TMRect  m_rExtent;      // ��Χ
    CMSegmentArray m_ExtSegments;   // ��Χ�ĸ���
    
    INT     m_iBlindWidth; // width
    
    FLOAT   m_fProgress;    // ����
    
    CMSegmentArray  m_Edges; // ��Ҷ������ʼ��

    CMPointVector     m_ptVetexes;    // ����HRGNʱ�ĸ�������

};


//////////////////////////////////////////////////////////////////////////
#endif // !defined(AFX_TVENETIANCTRL_H__B01750B6_2CDE_4276_B9F2_D4B0FC1F958B__INCLUDED_)
