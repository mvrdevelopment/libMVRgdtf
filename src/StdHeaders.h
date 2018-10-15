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

	

#define WIN32_LEAN_AND_MEAN             // Selten verwendete Komponenten aus Windows-Headern ausschlieﬂen
// Windows-Headerdateien
#include <windows.h>

#elif GS_LIN

#define GS_HIDDEN_VISIBILITY	

#elif GS_MAC

#define GS_HIDDEN_VISIBILITY

#endif
