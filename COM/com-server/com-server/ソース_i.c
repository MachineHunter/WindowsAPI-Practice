

/* this ALWAYS GENERATED file contains the IIDs and CLSIDs */

/* link this file in with the server and any clients */


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



#ifdef __cplusplus
extern "C"{
#endif 


#include <rpc.h>
#include <rpcndr.h>

#ifdef _MIDL_USE_GUIDDEF_

#ifndef INITGUID
#define INITGUID
#include <guiddef.h>
#undef INITGUID
#else
#include <guiddef.h>
#endif

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        DEFINE_GUID(name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8)

#else // !_MIDL_USE_GUIDDEF_

#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

#define MIDL_DEFINE_GUID(type,name,l,w1,w2,b1,b2,b3,b4,b5,b6,b7,b8) \
        EXTERN_C __declspec(selectany) const type name = {l,w1,w2,{b1,b2,b3,b4,b5,b6,b7,b8}}

#endif // !_MIDL_USE_GUIDDEF_

MIDL_DEFINE_GUID(IID, IID_IEngine,0xA405CD91,0xB2EB,0x4E99,0x87,0x30,0xEF,0x4D,0xAF,0xD8,0x22,0x6C);


MIDL_DEFINE_GUID(IID, IID_ICreateMyCar,0xE7F7CF95,0x9F5F,0x4851,0x90,0xC7,0xEE,0xB9,0x2A,0x0D,0x31,0xC8);


MIDL_DEFINE_GUID(IID, LIBID_CarLocalServerLib,0x7C0034F1,0x63EE,0x468C,0x90,0x9C,0x88,0x2B,0x65,0x8E,0x59,0x3B);


MIDL_DEFINE_GUID(CLSID, CLSID_MyCar,0xEFD64C65,0xCE74,0x441A,0xA3,0x1A,0x4B,0x89,0xE2,0xA9,0x95,0xF0);

#undef MIDL_DEFINE_GUID

#ifdef __cplusplus
}
#endif



