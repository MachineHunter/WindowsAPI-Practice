

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 8.01.0622 */
/* at Tue Jan 19 12:14:07 2038
 */
/* Compiler settings for É\Å[ÉX.idl:
    Oicf, W1, Zp8, env=Win64 (32b run), target_arch=AMD64 8.01.0622 
    protocol : all , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */



/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 500
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif /* __RPCNDR_H_VERSION__ */

#ifndef COM_NO_WINDOWS_H
#include "windows.h"
#include "ole2.h"
#endif /*COM_NO_WINDOWS_H*/

#ifndef ___835C815B83X_h_h__
#define ___835C815B83X_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IEngine_FWD_DEFINED__
#define __IEngine_FWD_DEFINED__
typedef interface IEngine IEngine;

#endif 	/* __IEngine_FWD_DEFINED__ */


#ifndef __ICreateMyCar_FWD_DEFINED__
#define __ICreateMyCar_FWD_DEFINED__
typedef interface ICreateMyCar ICreateMyCar;

#endif 	/* __ICreateMyCar_FWD_DEFINED__ */


#ifndef __MyCar_FWD_DEFINED__
#define __MyCar_FWD_DEFINED__

#ifdef __cplusplus
typedef class MyCar MyCar;
#else
typedef struct MyCar MyCar;
#endif /* __cplusplus */

#endif 	/* __MyCar_FWD_DEFINED__ */


/* header files for imported files */
#include "oaidl.h"

#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IEngine_INTERFACE_DEFINED__
#define __IEngine_INTERFACE_DEFINED__

/* interface IEngine */
/* [helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_IEngine;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("A405CD91-B2EB-4E99-8730-EF4DAFD8226C")
    IEngine : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SpeedUp( void) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetMaxSpeed( 
            /* [retval][out] */ int *maxSpeed) = 0;
        
        virtual HRESULT STDMETHODCALLTYPE GetCurSpeed( 
            /* [retval][out] */ int *curSpeed) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct IEngineVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IEngine * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IEngine * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *SpeedUp )( 
            IEngine * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetMaxSpeed )( 
            IEngine * This,
            /* [retval][out] */ int *maxSpeed);
        
        HRESULT ( STDMETHODCALLTYPE *GetCurSpeed )( 
            IEngine * This,
            /* [retval][out] */ int *curSpeed);
        
        END_INTERFACE
    } IEngineVtbl;

    interface IEngine
    {
        CONST_VTBL struct IEngineVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IEngine_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IEngine_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IEngine_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IEngine_SpeedUp(This)	\
    ( (This)->lpVtbl -> SpeedUp(This) ) 

#define IEngine_GetMaxSpeed(This,maxSpeed)	\
    ( (This)->lpVtbl -> GetMaxSpeed(This,maxSpeed) ) 

#define IEngine_GetCurSpeed(This,curSpeed)	\
    ( (This)->lpVtbl -> GetCurSpeed(This,curSpeed) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __IEngine_INTERFACE_DEFINED__ */


#ifndef __ICreateMyCar_INTERFACE_DEFINED__
#define __ICreateMyCar_INTERFACE_DEFINED__

/* interface ICreateMyCar */
/* [helpstring][oleautomation][uuid][object] */ 


EXTERN_C const IID IID_ICreateMyCar;

#if defined(__cplusplus) && !defined(CINTERFACE)
    
    MIDL_INTERFACE("E7F7CF95-9F5F-4851-90C7-EEB92A0D31C8")
    ICreateMyCar : public IUnknown
    {
    public:
        virtual HRESULT STDMETHODCALLTYPE SetMaxSpeed( 
            /* [in] */ int maxSp) = 0;
        
    };
    
    
#else 	/* C style interface */

    typedef struct ICreateMyCarVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            ICreateMyCar * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            _COM_Outptr_  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            ICreateMyCar * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            ICreateMyCar * This);
        
        HRESULT ( STDMETHODCALLTYPE *SetMaxSpeed )( 
            ICreateMyCar * This,
            /* [in] */ int maxSp);
        
        END_INTERFACE
    } ICreateMyCarVtbl;

    interface ICreateMyCar
    {
        CONST_VTBL struct ICreateMyCarVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define ICreateMyCar_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define ICreateMyCar_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define ICreateMyCar_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define ICreateMyCar_SetMaxSpeed(This,maxSp)	\
    ( (This)->lpVtbl -> SetMaxSpeed(This,maxSp) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */




#endif 	/* __ICreateMyCar_INTERFACE_DEFINED__ */



#ifndef __CarLocalServerLib_LIBRARY_DEFINED__
#define __CarLocalServerLib_LIBRARY_DEFINED__

/* library CarLocalServerLib */
/* [helpstring][version][uuid] */ 


EXTERN_C const IID LIBID_CarLocalServerLib;

EXTERN_C const CLSID CLSID_MyCar;

#ifdef __cplusplus

class DECLSPEC_UUID("EFD64C65-CE74-441A-A31A-4B89E2A995F0")
MyCar;
#endif
#endif /* __CarLocalServerLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


