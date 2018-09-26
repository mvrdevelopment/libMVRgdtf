
//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//  This file contains the type definitions for the Graphsoft core.
//
#if GS_WIN

#define GS_HIDDEN_VISIBILITY	__declspec(dllexport)
#define GS_COMP_API				extern "C" {}

#elif GS_LIN

#define GS_HIDDEN_VISIBILITY	
#define GS_COMP_API

#elif GS_MAC

#define GS_HIDDEN_VISIBILITY
#define GS_COMP_API

#endif
