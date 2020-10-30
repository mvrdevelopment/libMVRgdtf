// StdAfx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//
//	Copyright © Nemetschek North America, Inc  2005.
//	All Rights Reserved.

#pragma once

#if _WINDOWS

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers
#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers


#pragma warning(disable:4786)

#include "CommonPrefix.h"

#elif _LINUX

#include "CommonPrefix.h"

#endif	// _WINDOWS
