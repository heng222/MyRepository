#pragma once

#include "NBMapEngine.h"

//////////////////////////////////////////////////////////////////////////

#define RETRIEVE_SELF_ENGINE(class_engine_name) \
    class_engine_name* GetRefEngine() \
                 { \
                     return (class_engine_name*)RetrieveEngine(); \
                 }

#define GET_SELF_ENGIN() GetRefEngine()

//////////////////////////////////////////////////////////////////////////

// CNBMapWnd

class AFX_EXT_CLASS CNBMapWnd : public CWnd
{
    DECLARE_DYNAMIC(CNBMapWnd)

public:

    CNBMapWnd();
    virtual ~CNBMapWnd();

    void            AttachEngine(CNBMapEngine* pEngine);
    CNBMapEngine*   RetrieveEngine();

    BOOL    Create(CWnd* pReferWnd);

protected:

    // Menu ID
    enum TMenuID
    {
        ID_MAPOPER_START = 0xC000,

        ID_MAPOPER_MOVE,
        ID_MAPOPER_ZOOMIN,
        ID_MAPOPER_ZOOMOUT,
        ID_MAPOPER_RESET,
        ID_MAPOPER_GRID,

        ID_MAPOPER_RESERVED = 0xC020,
    };

    // State
    enum TOperateState
    {
        EOPER_NORMAL = 0,       // Init state
        //EOPER_PREMOVE,      // Preparing to move
        EOPER_MOVING = 5,       // moving map
        EOPER_ZOOMIN,       // zoom in
        EOPER_ZOOMOUT,      // zoom out

        EPER_RESERVED = 20,
    };

    // Show style
    enum TShowStyle
    {
        ESS_GRID = 0x00000001,      // Show Grid.

        ESS_RESERVED = 0x00000008, // Reserved for Base class.
    };


    // Operation and show attributes
private:

    CPoint  m_ptNbStart;
    CPoint  m_ptNbEnd;

    CWnd*   m_pWndParent;
    CNBMapEngine* m_pEngineRef;

    int	    m_iOperState;    // state of mouse
    DWORD   m_wNbShowStyle;  // show style.


protected:

    DECLARE_MESSAGE_MAP()


    afx_msg void OnPaint();
    afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
    afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
    afx_msg void OnSize(UINT nType, int cx, int cy);
    afx_msg BOOL OnEraseBkgnd(CDC* pDC);

protected:

    // Map operation.
    void  SetStartPosition(CPoint newPoint);
    void  MoveMap();
    void  ZoomMap(CPoint newCenter,BOOL bZoomIn  = TRUE );

    // Operation state
    void  SetOperationState(int aState);
    int   GetOperationState() const;

    // Show style operation
    DWORD GetShowStyle() const;

    // Update/Painting Functions
    // the ReleaseMemDC method must be called to release the context after painting. 
    CDC*  GetMemDC();
    void  ReleaseMemDC();

    /*void  Invalidate(BOOL bErase = TRUE);*/
    //void  InvalidateRect(LPCRECT lpRect, BOOL bErase = TRUE);

public:

    void  ReDraw(BOOL bErase = TRUE);


    // New virtual functions
protected:

    virtual void OnMenuOperation(UINT nID);
    virtual void OnDraw(CDC* pDC,CNBMapEngine* pEngine)=0;
    virtual void PreContextMenu(CMenu& pMenu);
    virtual void OnStateChanged(int aNewState,int aOldState);

private:

    // Point array of Grid for drawing.
    CArray<TMPoint,TMPoint> m_ptArrayGrid;

    void    DrawGrid(CDC* pDC);

    // Drawing members
private:

    CRITICAL_SECTION    m_CriticalSection;
    CDC         m_dcMemory;
    CBitmap     m_bmpMemory;

    void        CreateMemDC();
};


