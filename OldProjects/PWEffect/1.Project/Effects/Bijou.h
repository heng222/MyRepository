// Bijou.h : Declaration of the CBijou

#ifndef __BIJOU_H_
#define __BIJOU_H_

#include "resource.h"       // main symbols

#include "DTOEffectBase.h"
#include "TMPoint.h"
//#include <vfw.h>

//#pragma comment(lib,"Vfw32.lib")

/////////////////////////////////////////////////////////////////////////////
// CBijou
class CBijou : 
	public CDTOEffectBase,
	public CComCoClass<CBijou, &CLSID_Bijou>,
	public IDispatchImpl<IBijou, &IID_IBijou, &LIBID_ISSPWEffectLib>
{
        typedef CDTOEffectBase _basex;
        typedef CBijou _thisx;
        typedef IBijou _selfI;

public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:
    
    STDMETHOD(get_Direction)(INT *pVal);
    STDMETHOD(put_Direction)(INT newVal);

    STDMETHOD(get_Rate)(INT *pVal);
    STDMETHOD(put_Rate)(INT newVal);
    
    STDMETHOD(get_LampHeight)(INT *pVal);
    STDMETHOD(put_LampHeight)(INT newVal);
    
    STDMETHOD(get_LampLength)(INT *pVal);
    STDMETHOD(put_LampLength)(INT newVal);
    
    STDMETHOD(get_GapLength)(INT *pVal);
	STDMETHOD(put_GapLength)(INT newVal);
	
	STDMETHOD(get_CornersOn)(/*[out, retval]*/ BOOL *pVal);
    STDMETHOD(put_CornersOn)(/*[in]*/ BOOL newVal);

    STDMETHOD(get_LampColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_LampColor)(/*[in]*/ OLE_COLOR newVal);
    
    STDMETHOD(get_GapColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_GapColor)(/*[in]*/ OLE_COLOR newVal);
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_BIJOU)
        
    DECLARE_POLY_AGGREGATABLE(_thisx)
    
    //Implement IDXEffect properties: Progress, Duration, etc..
    //DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
    
    // From IPWEffect
    DECLARE_IPWEFFECT_METHODS(_basex)
        
        
    // From CDTOEffectBase
public:
    
    virtual HRESULT FinalConstruct();
    
    virtual HRESULT OnInitialize();

    virtual HRESULT OnStart();

    virtual HRESULT OnTerminate();    
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
        IN DWORD* pOutputBuf,
        IN INT iWidth,
        IN INT iHeight);
    
    // Private utilities methods
private:

	BOOL	InitializeBijou();

	BOOL	GenerateLamps( CMRectVector& arrayLamp,
						   TMPoint ptStart,INT iWidth,INT iHeight,
						   TMPoint ptOffset,LONG lExtentLen );



    void	UpdateBijou();

    void    DrawBijou(HDC hDC);    
    void    DrawLamp(HDC hDC,const RECT& rRect) const;
    void    DrawGap(HDC hDC,const RECT& rRect) const;



    // left lamps operations
	void	GetLeftStartPos(TMPoint& ptStart) const;
	void	GetLeftOffset(TMPoint& ptOffset) const;
	void	GetLeftLastLampPos(TMPoint& ptLast) const;

    // top lamps operations
	void	GetTopStartPos(TMPoint& ptStart) const;
	void	GetTopOffset(TMPoint& ptOffset) const;
	void	GetTopLastLampPos(TMPoint& ptLast) const;

    // right lamps operations
	void	GetRightStartPos(TMPoint& ptStart) const;
    void	GetRightOffset(TMPoint& ptOffset) const;
	void	GetRightLastLampPos(TMPoint& ptLast) const;

    // bottom lamps operations
	void	GetBottomStartPos(TMPoint& ptStart) const;
    void	GetBottomOffset(TMPoint& ptOffset) const;
	void	GetBottomLastLampPos(TMPoint& ptLast) const;
    
    // Private members
private:

    TRoundDir   m_iDirection; // EClockwise,ECounterClockwise,etc..
    int         m_iRate; // pixels per frame.

    int         m_iLampHeight; // lamp height when layout horizontally.
    int         m_iLampLength; // lamp width/length.

    int         m_iGapLength; // length of gap between lamps.

	BOOL		m_bCornersOn;	// are corners always on?
    COLORREF    m_clrLamp; // lamp's color
    COLORREF    m_clrGap;   // gap's color
    
    // logic control members
private:

	TMRect		m_rectCanvas;

	TMPoint		m_ptLeftStart;
	TMPoint		m_ptTopStart;
	TMPoint		m_ptRightStart;
    TMPoint     m_ptBottomStart;


	CMRectVector  m_LeftLamps;
    CMRectVector  m_TopLamps;
	CMRectVector  m_RightLamps;
    CMRectVector  m_BottomLamps;

	// used for Alternating playing
	INT			m_iTimeOut;
	TRoundDir	m_iCurrentDir;	// only valid when m_iDirection is EAlternating.

    HBRUSH      m_hLampBrush;
    HBRUSH      m_hGapBrush;
};


//////////////////////////////////////////////////////////////////////////
#endif //__BIJOU_H_
