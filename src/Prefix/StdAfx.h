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

using namespace VWFC::Math;

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
#define GS_HIDDEN_VISIBILITY	

#elif GS_MAC
#define GS_HIDDEN_VISIBILITY

#endif
