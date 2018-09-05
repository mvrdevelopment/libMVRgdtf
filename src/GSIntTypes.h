//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//	This file abstracts the inclusion of inttypes.h, which is not included in Visual Studio.  
//  C99 format specifiers can be defined here for Windows. (e.g. for 64 bit arguments to printf())
//

#if GS_MAC 

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

// nonstandard types on mac
#define PRIpPTR		"p"		// p is already prefixed with 0x
#define SCNpPTR		"p"

#else 

// Visual Studio 2013 will include C99 support
#if (_MSC_VER >= 1800)

#define __STDC_FORMAT_MACROS
#include <inttypes.h>

#else

// this is a small subset of the specifiers, for now just add what we need
#define PRId32       "I32d"
#define PRIi32       "I32i"
#define PRIo32       "I32o"
#define PRIu32       "I32u"
#define PRIx32       "I32x"
#define PRIX32       "I32X"

#define PRId64       "I64d"
#define PRIi64       "I64i"
#define PRIo64       "I64o"
#define PRIu64       "I64u"
#define PRIx64       "I64x"
#define PRIX64       "I64X"

#define PRIdPTR     "Id"
#define PRIiPTR     "Ii"
#define PRIoPTR     "Io"
#define PRIuPTR     "Iu"
#define PRIxPTR     "Ix"
#define PRIXPTR     "IX"

#ifdef _WIN64 // [
#  define SCNdPTR     "I64d"
#  define SCNiPTR     "I64i"
#  define SCNxPTR     "I64x"
#else  // _WIN64 ][
#  define SCNdPTR     "ld"
#  define SCNiPTR     "li"
#  define SCNxPTR     "lx"
#endif  // _WIN64 ]

#endif

// nonstandard types on win
#define PRIpPTR		"#p"	// p has no prefix. #p is 0X but no prefix if null. x doesn't pad and has identical problems to p
#define SCNpPTR		SCNxPTR

#endif
