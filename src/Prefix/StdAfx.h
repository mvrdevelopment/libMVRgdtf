// StdAfx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
//	Copyright � Nemetschek North America, Inc  2005.
//	All Rights Reserved.

#pragma once

#if _WINDOWS

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#define __FP__

#pragma warning(disable:4786)
#pragma warning( disable : 4800)
#endif	// _WINDOWS

#include "GSTypes.h"
#include "CommonPrefix.h"
#include "Include/VectorworksMVR.h"
#include <iostream>
using namespace VectorworksMVR;

#define VCOM_SUCCEEDED(x)   (x==0)
#define	VCOM_FAILED(x)      (x != kVCOMError_NoError)

//---------------------------------------------------------------------------------
// Add defines

#define __PrintDebugValue__(x, y) std::cout << #x << " " << #y <<" Failed!" << std::endl
#define __PrintDebugValue2__(x) std::cout << #x << " Failed!" << std::endl

#define ASSERTN(x,y)                if(!(y))    { __PrintDebugValue__(x, y); }
#define DSTOP(params)                           { __PrintDebugValue2__(params); }
#define VERIFYN(x,y)                (!(y))    
#define VWFC_ASSERT(x)              if(!(x))    { __PrintDebugValue2__(x); }
#define THROW_VWFC_EXCEPTION(x,y,z )            { __PrintDebugValue__(x, z); }

#define kEveryone 1
#define kMCCoordTypes "2"

#define GS_API

// Check windows
#if _WIN32 || _WIN64
#if _WIN64
#define IS64BIT
#else
#define IS32BIT
#endif
#else
#if (INTPTR_MAX == INT32_MAX)
# define IS32BIT
#else
# define IS64BIT
#endif
#endif



//---------------------------------------------------------------------------------
// Add includes from VWSDK
#include "MCCoordTypes.h"
#include "FolderSpecifiers.h"
#include "GSString.h"
#include "VWPoint2D.h"
#include "VWPoint3D.h"
#include "VWLine2D.h"
#include "VWLine3D.h"
#include "VWMathUtils.h"
#include "VWTransformMatrix.h"
#include "UUID.h"
#include "RGBColor.h"

using namespace VWFC::Math;
using namespace VWFC::Tools;

// Interfaces
#include "Interface/IFileIdentifier.h"
#include "Interface/IFolderIdentifier.h"
#include "Interface/IRawOSFile.h"
#include "Interface/IZIPFile.h"
#include "Interface/IStdFile.h"
#include "Interface/IXMLFile.h"

#ifdef DONT_USE_XERCES_AS_XMLLIB
#include "rapidxmlsupport/mvr_xml_impl.h"
#endif

// Needed typedefs
typedef std::vector<double>     TDoubleArray;
typedef std::vector<Sint32>     TSint32Array;
typedef std::vector<Uint16>     TUint16Array;
typedef std::vector<VectorworksMVR::GdtfDefines::DMXAddress> TDMXAddressArray;


//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//  This file contains the type definitions for the Graphsoft core.
//

#pragma once
#if GS_WIN

#ifdef EXPORT_STATIC
	#define GS_HIDDEN_VISIBILITY
#else
	#ifdef EXPORT_SYMBOLS
	#define GS_HIDDEN_VISIBILITY	__declspec(dllexport)
	#else
	#define GS_HIDDEN_VISIBILITY	__declspec(dllimport)
	#endif // EXPORT_SYMBOLS
#endif

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Komponenten aus Windows-Headern ausschließen
// Windows-Headerdateien
#include <windows.h>

#elif GS_LIN
#define GS_HIDDEN_VISIBILITY

#elif GS_MAC
#define GS_HIDDEN_VISIBILITY    __attribute__((visibility("default")))

#endif

#define VW_EXPORT GS_HIDDEN_VISIBILITY 


typedef uint32_t RefNumType;



// VCOM interface implementation with immediate destruction
template<class Interface> class VCOMImmediateImpl : public Interface
{
public:
                VCOMImmediateImpl()                        { fRefCnt = 0; fParent = NULL; }
                VCOMImmediateImpl(IVWUnknown* parent)    { fRefCnt = 0; fParent = parent; if ( fParent ) { fParent->AddRef(); } }
    virtual        ~VCOMImmediateImpl()                    { }

// IVWUnknown
public:
    virtual uint32_t VCOM_CALLTYPE        AddRef()    { fRefCnt++; return fRefCnt; }
    virtual uint32_t VCOM_CALLTYPE        Release()
                                    {
                                        ASSERTN( kEveryone, fRefCnt > 0 );
                                        if ( fRefCnt > 0 ) {
                                            fRefCnt --;

                                            // mechanizm for immediate delete of the interface instance
                                            if ( fRefCnt == 0 ) {
                                                this->OnRefCountZero();
                                                delete this;
                                                //::GS_VWNotifyDeleteInterface( this );
                                                // EXIT IMMEDIATELY! 'this' no longer exist!!!
                                                return 0;
                                            }
                                        }
                                        return fRefCnt;
                                    }

protected:
    // notification when this instance ref count goes down to zero
    virtual void                    OnRefCountZero()
    {
        if ( fParent ) 
        { fParent->Release(); } 
        fParent = NULL;
    }

protected:
    RefNumType    fRefCnt;
    IVWUnknown* fParent;
};

// Local VCOM interface implementation with late destruction
template<class Interface> class VCOMImpl : public Interface
{
public:
                VCOMImpl()						{ fRefCnt = 0; fParent = NULL; }
                VCOMImpl(IVWUnknown* parent)	{ fRefCnt = 0; fParent = parent; if ( fParent ) { fParent->AddRef(); } }
    virtual		~VCOMImpl()						{ }

// IVWUnknown
public:
    virtual uint32_t VCOM_CALLTYPE		AddRef()	{ fRefCnt++; return fRefCnt; }
    virtual uint32_t VCOM_CALLTYPE		Release()
                                                    {
                                                        ASSERTN( kEveryone, fRefCnt > 0 );
                                                        if ( fRefCnt > 0 ) {
                                                            fRefCnt --;
                                                        }
                                                        if ( fRefCnt == 0 ) {
                                                            delete this;
                                                            // exit immediatelly. 'this' may no longer be valid
                                                            return 0;
                                                        }
                                                        return fRefCnt;
                                                    }

protected:
    // notification when this instance ref count goes down to zero
    virtual void					OnRefCountZero()
    {
        if ( fParent )
        { fParent->Release(); }
        fParent = NULL;
    }

protected:
    RefNumType	fRefCnt;
    IVWUnknown* fParent;
};


