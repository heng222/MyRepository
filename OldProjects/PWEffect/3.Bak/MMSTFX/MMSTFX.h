/* this ALWAYS GENERATED file contains the definitions for the interfaces */


/* File created by MIDL compiler version 5.01.0164 */
/* at Tue Oct 14 15:45:46 2008
 */
/* Compiler settings for D:\Exercise\0.DirectShow\MMSTFX\MMSTFX.idl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef __MMSTFX_h__
#define __MMSTFX_h__

#ifdef __cplusplus
extern "C"{
#endif 

/* Forward Declarations */ 

#ifndef __IMMSampleTFX_FWD_DEFINED__
#define __IMMSampleTFX_FWD_DEFINED__
typedef interface IMMSampleTFX IMMSampleTFX;
#endif 	/* __IMMSampleTFX_FWD_DEFINED__ */


#ifndef __MMSampleEffect_FWD_DEFINED__
#define __MMSampleEffect_FWD_DEFINED__

#ifdef __cplusplus
typedef class MMSampleEffect MMSampleEffect;
#else
typedef struct MMSampleEffect MMSampleEffect;
#endif /* __cplusplus */

#endif 	/* __MMSampleEffect_FWD_DEFINED__ */


#ifndef __MMSampleTransition_FWD_DEFINED__
#define __MMSampleTransition_FWD_DEFINED__

#ifdef __cplusplus
typedef class MMSampleTransition MMSampleTransition;
#else
typedef struct MMSampleTransition MMSampleTransition;
#endif /* __cplusplus */

#endif 	/* __MMSampleTransition_FWD_DEFINED__ */


/* header files for imported files */
#include "dxtrans.h"

void __RPC_FAR * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void __RPC_FAR * ); 

#ifndef __IMMSampleTFX_INTERFACE_DEFINED__
#define __IMMSampleTFX_INTERFACE_DEFINED__

/* interface IMMSampleTFX */
/* [unique][helpstring][dual][uuid][object] */ 


EXTERN_C const IID IID_IMMSampleTFX;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("D32D4A9E-229A-4793-8BBD-28E88DCFCD84")
    IMMSampleTFX : public IDXEffect
    {
    public:
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_Blue( 
            /* [retval][out] */ float __RPC_FAR *pfBlue) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_Blue( 
            /* [in] */ float fBlue) = 0;
        
        virtual /* [propget] */ HRESULT STDMETHODCALLTYPE get_MeltIntensity( 
            /* [retval][out] */ float __RPC_FAR *pfMeltIntensity) = 0;
        
        virtual /* [propput] */ HRESULT STDMETHODCALLTYPE put_MeltIntensity( 
            /* [in] */ float fMeltIntensity) = 0;
        
    };
    
#else 	/* C style interface */

    typedef struct IMMSampleTFXVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *QueryInterface )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void __RPC_FAR *__RPC_FAR *ppvObject);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *AddRef )( 
            IMMSampleTFX __RPC_FAR * This);
        
        ULONG ( STDMETHODCALLTYPE __RPC_FAR *Release )( 
            IMMSampleTFX __RPC_FAR * This);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfoCount )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [out] */ UINT __RPC_FAR *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetTypeInfo )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo __RPC_FAR *__RPC_FAR *ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE __RPC_FAR *GetIDsOfNames )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR __RPC_FAR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID __RPC_FAR *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *Invoke )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS __RPC_FAR *pDispParams,
            /* [out] */ VARIANT __RPC_FAR *pVarResult,
            /* [out] */ EXCEPINFO __RPC_FAR *pExcepInfo,
            /* [out] */ UINT __RPC_FAR *puArgErr);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Capabilities )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [retval][out] */ long __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Progress )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Progress )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_StepResolution )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [id][propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Duration )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pVal);
        
        /* [id][propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Duration )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [in] */ float newVal);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_Blue )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pfBlue);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_Blue )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [in] */ float fBlue);
        
        /* [propget] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *get_MeltIntensity )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [retval][out] */ float __RPC_FAR *pfMeltIntensity);
        
        /* [propput] */ HRESULT ( STDMETHODCALLTYPE __RPC_FAR *put_MeltIntensity )( 
            IMMSampleTFX __RPC_FAR * This,
            /* [in] */ float fMeltIntensity);
        
        END_INTERFACE
    } IMMSampleTFXVtbl;

    interface IMMSampleTFX
    {
        CONST_VTBL struct IMMSampleTFXVtbl __RPC_FAR *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IMMSampleTFX_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define IMMSampleTFX_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define IMMSampleTFX_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define IMMSampleTFX_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define IMMSampleTFX_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define IMMSampleTFX_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define IMMSampleTFX_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)


#define IMMSampleTFX_get_Capabilities(This,pVal)	\
    (This)->lpVtbl -> get_Capabilities(This,pVal)

#define IMMSampleTFX_get_Progress(This,pVal)	\
    (This)->lpVtbl -> get_Progress(This,pVal)

#define IMMSampleTFX_put_Progress(This,newVal)	\
    (This)->lpVtbl -> put_Progress(This,newVal)

#define IMMSampleTFX_get_StepResolution(This,pVal)	\
    (This)->lpVtbl -> get_StepResolution(This,pVal)

#define IMMSampleTFX_get_Duration(This,pVal)	\
    (This)->lpVtbl -> get_Duration(This,pVal)

#define IMMSampleTFX_put_Duration(This,newVal)	\
    (This)->lpVtbl -> put_Duration(This,newVal)


#define IMMSampleTFX_get_Blue(This,pfBlue)	\
    (This)->lpVtbl -> get_Blue(This,pfBlue)

#define IMMSampleTFX_put_Blue(This,fBlue)	\
    (This)->lpVtbl -> put_Blue(This,fBlue)

#define IMMSampleTFX_get_MeltIntensity(This,pfMeltIntensity)	\
    (This)->lpVtbl -> get_MeltIntensity(This,pfMeltIntensity)

#define IMMSampleTFX_put_MeltIntensity(This,fMeltIntensity)	\
    (This)->lpVtbl -> put_MeltIntensity(This,fMeltIntensity)

#endif /* COBJMACROS */


#endif 	/* C style interface */



/* [propget] */ HRESULT STDMETHODCALLTYPE IMMSampleTFX_get_Blue_Proxy( 
    IMMSampleTFX __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pfBlue);


void __RPC_STUB IMMSampleTFX_get_Blue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMMSampleTFX_put_Blue_Proxy( 
    IMMSampleTFX __RPC_FAR * This,
    /* [in] */ float fBlue);


void __RPC_STUB IMMSampleTFX_put_Blue_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propget] */ HRESULT STDMETHODCALLTYPE IMMSampleTFX_get_MeltIntensity_Proxy( 
    IMMSampleTFX __RPC_FAR * This,
    /* [retval][out] */ float __RPC_FAR *pfMeltIntensity);


void __RPC_STUB IMMSampleTFX_get_MeltIntensity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);


/* [propput] */ HRESULT STDMETHODCALLTYPE IMMSampleTFX_put_MeltIntensity_Proxy( 
    IMMSampleTFX __RPC_FAR * This,
    /* [in] */ float fMeltIntensity);


void __RPC_STUB IMMSampleTFX_put_MeltIntensity_Stub(
    IRpcStubBuffer *This,
    IRpcChannelBuffer *_pRpcChannelBuffer,
    PRPC_MESSAGE _pRpcMessage,
    DWORD *_pdwStubPhase);



#endif 	/* __IMMSampleTFX_INTERFACE_DEFINED__ */



#ifndef __MMFXLib_LIBRARY_DEFINED__
#define __MMFXLib_LIBRARY_DEFINED__

/* library MMFXLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_MMFXLib;

EXTERN_C const CLSID CLSID_MMSampleEffect;

#ifdef __cplusplus

class DECLSPEC_UUID("294D0DE1-1B57-408d-A33F-FA708A5A28D6")
MMSampleEffect;
#endif

EXTERN_C const CLSID CLSID_MMSampleTransition;

#ifdef __cplusplus

class DECLSPEC_UUID("978DABA8-F330-4f09-BEC5-4D53C541BB4D")
MMSampleTransition;
#endif
#endif /* __MMFXLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif
