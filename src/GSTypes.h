//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
//  This file contains the type definitions for the Graphsoft core.
//

#ifndef _GS_TYPES_
#define _GS_TYPES_

#pragma once

#include <stdint.h>
///////////////////////////////////////////////////////////////////////////////
// Fixed-width unsigned integer types.

typedef uint8_t		Uint8;
typedef	uint16_t	Uint16;
typedef	uint32_t	Uint32;
typedef uint64_t	Uint64;


///////////////////////////////////////////////////////////////////////////////
// Fixed-width signed integer types.

typedef char		Sint8;	
typedef	int16_t		Sint16;
typedef	int32_t		Sint32;
typedef int64_t		Sint64;


///////////////////////////////////////////////////////////////////////////////
// Interger type maximums and minimums.

#define kGSMaxUint8		255
#define kGSMaxUint16	65535
#define kGSMaxUint32	4294967295UL
#define kGSMaxUint64	18446744073709551615ULL
#define kGSMaxSint8		127
#define kGSMaxSint16	32767
#define kGSMaxSint32	2147483647L
#define kGSMaxSint64	9223372036854775807LL

#define kGSMinUint8		0
#define kGSMinUint16	0
#define kGSMinUint32	0UL
#define kGSMinUint64	0ULL
#define kGSMinSint8		(-128)
#define kGSMinSint16	(-32768)
#define kGSMinSint32	(-2147483647-1)
#define kGSMinSint64	(-9223372036854775808LL)


///////////////////////////////////////////////////////////////////////////////
// Floating point types.

typedef	float			Real32;
typedef double			Real64;

#ifndef CGFLOAT_EPSILON
	#if CGFLOAT_IS_DOUBLE
		#define CGFLOAT_EPSILON DBL_EPSILON
	#else
		#define CGFLOAT_EPSILON FLT_EPSILON
	#endif
#endif

///////////////////////////////////////////////////////////////////////////////
// Boolean types.

typedef	unsigned char	Bool8;

#if __cplusplus
	const Bool8		kFalse = 0;
	const Bool8		kTrue = 1;
#else
	enum EBool {
		kFalse = 0,
		kTrue = 1
	};
#endif

#if _LINUX
	const bool	FALSE = 0;
	const bool	TRUE  = 1;
#endif

///////////////////////////////////////////////////////////////////////////////
// Integer pointer types. (guaranteed to have the same size as a pointer regardless of the platform.)
typedef intptr_t	SintptrT;
typedef uintptr_t	UintptrT;

#if _LINUX
typedef __SIZE_TYPE__	size_t;
#endif

typedef size_t		GSSize;


///////////////////////////////////////////////////////////////
// XXXKIS : Put this type definition back in temporarily until
//			I find out why it was removed to being with.
typedef unsigned char	Boolean;


///////////////////////////////////////////////////////////////////////////////
// Character types.

// Non-Unicode
typedef unsigned char	Uchar;

// Unicode (Encoding format is UTF-16 in platform-native byte order)
typedef Uint16			UCChar;
typedef UCChar*			UCCharPtr;       // Pointer to one or an array of UCCChars
typedef UCChar**		UCCharHandle;    // Handle to one or an array of UCCChars
typedef UCChar*			UCStrPtr;        // Pointer to NULL-word terminated UCChars
typedef UCChar**		UCStrHandle;     // Handle to NULL-word terminated UCChars
typedef const UCChar*	ConstUCCharPtr;  // Pointer to one or an array of constant UCCChars
typedef const UCChar*	ConstUCStrPtr;   // Pointer to NULL-word terminated constant UCChars
typedef Uint32			UCCharCnt;

#ifdef _LINUX
typedef Uint16			UniChar;
#endif

///////////////////////////////////////////////////////////////////////////////
// String types.
//   Non-Unicode base types used by our cross-platform string code

// Pascal string types
typedef Uchar			GSStr255[256], GSStr63[64], GSStr32[33], GSStr31[32], GSStr27[28], GSStr15[16];
typedef Uchar			*GSStringPtr, **GSStringHandle;
typedef const Uchar		*ConstGSStringPtr, *ConstGSStr255Param, *ConstGSStr31Param, *ConstGSStr15Param;

// C string types
typedef char			*GSCStrPtr;			// C-String Pointer
typedef const char		*ConstGSCStrPtr;	// Constant C-String Pointer


///////////////////////////////////////////////////////////////////////////////
// GSHandle
//   This is the basic resizable handle structure with cross-platform support
//   from the MiniCAD SDK. SDK memory calls can also be used on MCObjectHandle.

typedef char**	GSHandle;


///////////////////////////////////////////////////////////////////////////////
//	ColorRef
typedef Uint16 ColorRef;

///////////////////////////////////////////////////////////////////////////////
//	OpacityRef
typedef Uint8 OpacityRef;

///////////////////////////////////////////////////////////////////////////////
//	kMaxOpacity
const OpacityRef kMaxOpacity = 100;

///////////////////////////////////////////////////////////////////////////////
// PlanarRef identifier type definition
// 3D coordinate definition of the planar object
typedef Uint32 TPlanarRefID;

const TPlanarRefID kPlanarRefID_ScreenPlane	= TPlanarRefID(0);

typedef Uint8 SnapByType;

///////////////////////////////////////////////////////////////////////////////
typedef Uint32 HandleAsUint32;
typedef Uint32 PointerAsUint32;

typedef Uint64 HandleAsUint64;
typedef Uint64 PointerAsUint64;

///////////////////////////////////////////////////////////////////////////////
typedef Real32 ResolutionRef;
const ResolutionRef kHighResolutionDisplay		= 196.0;	//dpi
const ResolutionRef kDefaultWindowResolution	= 110.0;	//dpi
const ResolutionRef kDefaultFeedbackResolution	= 100.0;	//dpi


#endif //_GS_TYPES
