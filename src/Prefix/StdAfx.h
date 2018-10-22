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

#include "CommonPrefix.h"

#elif _LINUX

#include "CommonPrefix.h"

#endif	// _WINDOWS

#include "../Include/VectorworksMVR.h"
using namespace VectorworksMVR;

#define VCOM_SUCCEEDED(x) (x==0)
//---------------------------------------------------------------------------------
// Add defines

// TODO
#define ASSERTN 
#define DSTOP 
#define VERIFYN
#define VWFC_ASSERT
#define THROW_VWFC_EXCEPTION

#define kEveryone 1
#define kMCCoordTypes "2"

#define GS_API

//---------------------------------------------------------------------------------
// Add includes from VWSDK
#include "../MCCoordTypes.h"
#include "../FolderSpecifiers.h"
#include "../GSString.h"
#include "../VWPoint2D.h"
#include "../VWPoint3D.h"
#include "../VWLine2D.h"
#include "../VWMathUtils.h"
#include "../VWTransformMatrix.h"
#include "../UUID.h"
#include "../RGBColor.h"

using namespace VWFC::Math;
using namespace VWFC::Tools;

// Interfaces
#include "../Interface/IFileIdentifier.h"
#include "../Interface/IFolderIdentifier.h"
#include "../Interface/IRawOSFile.h"
#include "../Interface/IZIPFile.h"
#include "../Interface/IStdFile.h"
#include "../Interface/IXMLFile.h"



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

#ifdef EXPORT_SYMBOLS
#define GS_HIDDEN_VISIBILITY	__declspec(dllexport)
#else
#define GS_HIDDEN_VISIBILITY	__declspec(dllimport)
#endif // EXPORT_SYMBOLS

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Komponenten aus Windows-Headern ausschließen
// Windows-Headerdateien
#include <windows.h>

#elif GS_LIN
#define GS_HIDDEN_VISIBILITY	 __attribute__((visibility("default")))

#elif GS_MAC
#define GS_HIDDEN_VISIBILITY    __attribute__((visibility("default")))

#endif

#define VW_EXPORT GS_HIDDEN_VISIBILITY 


typedef size_t RefNumType;

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
                                                //::GS_VWNotifyDeleteInterface( this );
                                                // EXIT IMMEDIATELY! 'this' no longer exist!!!
                                                return 0;
                                            }
                                        }
                                        return fRefCnt;
                                    }

protected:
    // notification when this instance ref count goes down to zero
    virtual void                    OnRefCountZero() { if ( fParent ) { fParent->Release(); } fParent = NULL; }

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
    virtual void					OnRefCountZero() { if ( fParent ) { fParent->Release(); } fParent = NULL; }

protected:
    RefNumType	fRefCnt;
    IVWUnknown* fParent;
};
