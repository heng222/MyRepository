// Sparkle.h : Declaration of the CSparkle

#ifndef __SPARKLE_H_
#define __SPARKLE_H_

#include "resource.h"       // main symbols
#include "DTOEffectBase.h"

//////////////////////////////////////////////////////////////////////////
// TStars
class TStar
{
public:
    
    POINT   m_ptPos;
    INT     m_nOrgSize;
    INT     m_nCurSize;
    
private:

    INT     m_iStep;
    BOOL    m_bShrink;

public:

    TStar();

    void    Initialize();
    void    Update();
    void    Draw(HDC hdc) const;

};
typedef     vector<TStar*>   CStarArray;

/////////////////////////////////////////////////////////////////////////////
// CSparkle
class CSparkle : 
	public CDTOEffectBase,
	public CComCoClass<CSparkle, &CLSID_Sparkle>,
	public IDispatchImpl<ISparkle, &IID_ISparkle, &LIBID_ISSPWEffectLib>
{
    
    typedef CDTOEffectBase _basex;
    typedef CSparkle _thisx;
    typedef ISparkle _selfI;
    
public:
    
    // ATL Setup
    BEGIN_COM_MAP(_thisx)
        COM_INTERFACE_ENTRY(_selfI)
        COM_INTERFACE_ENTRY2(IDispatch,_selfI)
        COM_INTERFACE_ENTRY_CHAIN( _basex )
    END_COM_MAP()
        
    // _selfI Interface
public:
    
    STDMETHOD(get_Size)(/*[out, retval]*/ INT *pVal);
    STDMETHOD(put_Size)(/*[in]*/ INT newVal);
    STDMETHOD(get_Amount)(/*[out, retval]*/ FLOAT *pVal);
    STDMETHOD(put_Amount)(/*[in]*/ FLOAT newVal);
    STDMETHOD(get_SparkleColor)(/*[out, retval]*/ OLE_COLOR *pVal);
	STDMETHOD(put_SparkleColor)(/*[in]*/ OLE_COLOR newVal);
    
    
public: 
    
    //Implement registration for DX Transform
    DECLARE_REGISTER_DX_IMAGE_TRANS(IDR_SPARKLE)
        
    DECLARE_POLY_AGGREGATABLE(_thisx)
    
    //Implement IDXEffect properties: Progress, Duration, etc..
    //DECLARE_IDXEFFECT_METHODS(DXTET_MORPH)
    
    // From IPWEffect
    DECLARE_IPWEFFECT_METHODS(_basex)
        
        
    // From _basex
public:
    
    virtual HRESULT FinalConstruct();
    
    virtual HRESULT OnInitialize();
    virtual HRESULT OnTerminate();
    
    
    virtual HRESULT OnImplEffect(IN DWORD* pInputBuf,
        IN DWORD* pOutputBuf,
        IN INT iWidth,
        IN INT iHeight);
    
    // Private utilities methods
private:

    DWORD   GetSparkleArea() const;

    BOOL    BuildStars(CStarArray& aStars) const;

    void    UpdateStars();
    
    void    DrawSparkle(HDC hdc) const;
    
    // Properties
private:

    COLORREF     m_clrSparkle;
    FLOAT        m_fAmount;
    INT          m_iSizeStar;
    
    // Members
private:

    CPointArray m_arrayStarPos;
    HPEN        m_hPenSparkle;

    CStarArray  m_arrayStars;

	
};

#endif //__SPARKLE_H_
