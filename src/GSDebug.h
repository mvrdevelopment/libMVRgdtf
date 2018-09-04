//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
//
// This header file contains all prototypes and related information for all
// debugging functions and variables.  It is completely cross-platform and
// can be included in 100% Mac, 100% Windows and hybrid files.
//
// ------------------------------------------------------------------
// TProgrammer Addition and Removal Process:
// ------------------------------------------------------------------
// Adding a new Engineer:
// 1) Search for @1. Add a new entry, finding an empty slot or appending.
// 2) Search for @3. Add a new entry at the same relative position as you added for step 1 (to keep things in sync).
// 3) Search for @5. Add a new entry at the same relative position.

// Removing a departed Engineer:
// 1) Search for @1. Remove from this table. Just comment the whole line, change the name/constant to XXXXX, and leave a space with a comment that says // Empty. We no longer add "kNoOne" placeholders.
// 2) Search for @2. Append an entry for this engineer.
// 3) Search for @3. Remove the entry for this engineer (cut it).
// 4) Search for @4. Append an entry for this engineer (paste from previous)
// 5) Search for @5. Remove the entry for this engineer.
// ------------------------------------------------------------------



#ifndef _GSDEBUG_H_
#define _GSDEBUG_H_ 1

#pragma once

///////////////////////////////////////////////////////////////////////////////
// _GSDEBUG_DLL_
//
// To use the DLL version of GSDebug, define _GSDEBUG_DLL_ to be non-zero in
// the project settings. If you do not define it, the default will be to use
// the object file version.

#if !defined(_GSDEBUG_DLL_)
	#define _GSDEBUG_DLL_ 0
#endif


///////////////////////////////////////////////////////////////////////////////
// _GSDEBUG_LIB_
//
// To use the LIB version of GSDebug, define _GSDEBUG_LIB_ to be non-zero in
// the project settings. If you do not define it, the default will be to use
// the object file version.

#if !defined(_GSDEBUG_LIB_)
	#define _GSDEBUG_LIB_ 0
#endif


///////////////////////////////////////////////////////////////////////////////
// GS_USE_ONLY_MODERN
//
// Define GS_USE_ONLY_MODERN to be non-zero to force more modern behavior.
// Modern behavior includes requiring a TProgrammer attached to all debug
// calls. If you do not define it, the default will be to not use it.

#if !defined(GS_USE_ONLY_MODERN)
	#define GS_USE_ONLY_MODERN 1
#endif


///////////////////////////////////////////////////////////////////////////////
// GS_HWND_CHECK
//
// Define GS_HWND_CHECK to non-zero if you want to include Windows HWND
// validation functions.

#if !defined(GS_HWND_CHECK)
	#if defined(_INC_WINDOWS) || defined(_GSWIN_)
		#define GS_HWND_CHECK 1
	#else
		#define GS_HWND_CHECK 0
	#endif
#endif


///////////////////////////////////////////////////////////////////////////////
// GS_USE_OBSOLETE
//
// Define GS_USE_OBSOLETE to be non-zero to include very old debugging
// functions. You really don't want to do this unless you have to.
#if !defined(GS_USE_OBSOLETE)
	#if !_MINICAD_EXTERNAL_ && !_GSWINSDK_ && !_MAGICFOLDER_ && !_GSESDK_ && !GS_SHELL_BUILD && !GS_COMP_BUILD && !GS_PROTECTION_BUILD && !GS_GSDEBUG_BUILD
		#define GS_USE_OBSOLETE 1
	#else
		#define GS_USE_OBSOLETE 0
	#endif
#endif


///////////////////////////////////////////////////////////////////////////////
// GS_USE_CLASS_DEBUGGING
//
// Define GS_USE_CLASS_DEBUGGING to be non-zero to enable class debugging.

#if !defined(GS_USE_CLASS_DEBUGGING)
	#if !_MINICAD_EXTERNAL_
		#define GS_USE_CLASS_DEBUGGING	1
	#else
		#define GS_USE_CLASS_DEBUGGING	0
	#endif
#endif


/////////////////////////////////////////////////////////////////////////////////////////
// _GSDEBUG_
//
// When building the GSDebug.dll or GSDebug.lib, you must define _GSDEBUG_ in the
// compiler preprocessor flags settings.

#if _GSDEBUG_ && !_GSDEBUG_DLL_ && !_GSDEBUG_LIB_
	#error if _GSDEBUG_ is defined, _GSDEBUG_DLL_ or _GSDEBUG_LIB_ must also be defined
#endif


/////////////////////////////////////////////////////////////////////////////////////////
// Not allowed to use the DLL and LIB versions at the same time.

#if _GSDEBUG_DLL_ && _GSDEBUG_LIB_
	#error Not allowed to define both _GSDEBUG_DLL_ and _GSDEBUG_LIB_
#endif
#if !_GSDEBUG_DLL_ && !_GSDEBUG_LIB_
	#define _GSDEBUG_OBJ_	1
#endif


#if GS_MAC
	//  Turn off effect of DEBUG_DO_NOTHING applied to GS_MAC_SYMBOL_TABLE_BUG_FIX_LEVEL_n
	//	Set GS_DSTOP_ALWAYS for MAC environment that DOES NOT skip Debugging stops.
	#define GS_DSTOP_ALWAYS SteveJ	// Turn off effect of DEBUG_DO_NOTHING applied to GS_MAC_SYMBOL_TABLE_BUG_FIX_LEVEL_n
#endif


///////////////////////////////////////////////////////////////////////////////
// Implementation Starts Here
///////////////////////////////////////////////////////////////////////////////


/* Includes */
/* -------- */

// Debugging library is only useful under C++. This allows it to be globally included in externals.
#ifdef __cplusplus

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <map>
#include <chrono>
#include <ctime>
#include <fstream>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>

#if !_WINDOWS
	#include <stdarg.h>
#endif


///////////////////////////////////////////////////////////////////////////////
// AS OF 8/20/98 -
//		On Windows, GSESDK code is called without special calling conventions

#if _WINDOWS && _GSDEBUG_DLL_
	#if _GSDEBUG_
		// Building GSDebug.dll
		#define GSDEBUG_EXPORT			__declspec(dllexport)

	#else
		// Building a module that uses GSDebug.dll
		#define GSDEBUG_EXPORT			__declspec(dllimport)
	#endif
#else
	// Building a module that compiles GSDebug.cpp directly (no GSDebug.dll).
	#define GSDEBUG_EXPORT
#endif


/////////////////////////////////////////////////////////////////////////////////////////

#include "GSTypes.h"


/* End of Includes */


/* Basic Types */
/* ----------- */

typedef GSStringPtr BugStringPtr;

#if _WINDOWS
	#if _MAGICFOLDER_
		#define Boolean	Bool8
		#define Byte	Uint8
	#endif
#endif


/* Private Variables */
/* ----------------- */
#if GS_GSDEBUG_BUILD || (APPBUILD && !GS_INTERFACE_FACTORING)
extern char		gDebugAppName[32];
#endif


///////////////////////////////////////////////////////////////////////////////
// Timers
//
//	Use like this:
//		...code....
//		START_TIMER(NameOfTimer);
//		...code.to.time...
//		END_TIMER(kProgrammer, NameOfTimer);
//		...code...

#if _WINDOWS && BUG

	class GSDEBUG_EXPORT TProgrammer;
	class GSDEBUG_EXPORT TDebugTimer
	{
		public:
			TDebugTimer();
			void Stop(const TProgrammer &who, ConstGSCStrPtr name, bool bWindow);

		private:
			#if _WINDOWS
				Uint64 fStartTime;
			#else
			#endif
	};

	#define START_TIMER(name)		TDebugTimer timer_##name
	#define END_TIMER(who, name)	timer_##name##.Stop(who, #name, false)

#else
	#define START_TIMER(name)
	#define END_TIMER(who, name)
#endif

#if _WINDOWS && _MAGICFOLDER_
	#define START_TIMER_RELEASE(name)	const Uint32 timer_##name = ::GetTickCount()
	#define END_TIMER_RELEASE(name) do { \
		const Uint32 elapsed = ::GetTickCount() - timer_##name; \
		Uint32 seconds = elapsed / 1000; \
		Uint32 tenths = (elapsed - seconds*1000 + 50) / 100; \
		if (tenths > 9) { tenths = 0; ++seconds; } \
		char szMessage[60]; \
		::sprintf(szMessage, "Timer '" #name "' took %d.%d seconds.", seconds, tenths); \
		::AfxMessageBox(szMessage); \
	} while (0)
#else
	#define START_TIMER_RELEASE(name)
	#define END_TIMER_RELEASE(name)
#endif


/////////////////////////////////////////////////////////////////////////////////////////
// Compiler messages
//
//	Use like this:
//		#pragma CMSG(kProgrammer, "Your message")

#define CMSG_makeString1(x)	#x
#define CMSG_makeString(x)	CMSG_makeString1(x)
#define CMSG(who, desc)		message(__FILE__ "(" CMSG_makeString(__LINE__) ") : " #who ": " desc)


/////////////////////////////////////////////////////////////////////////////////////////
// Print preprocessor definition
//
// use this is see what something has been defined to be. For example:
//    #pragma PRINTDEFINE(kDave, BUG)
// Will, when compiling, generate a line in the compiler output window telling you what
// "BUG" is currently defined to.

#define PRINTDEFINE(who, what)		message(__FILE__ "(" CMSG_makeString(__LINE__) ") : " #who ": " #what " = " CMSG_makeString(what))


/////////////////////////////////////////////////////////////////////////////////////////
// Macro to mark something as un-implemented.
//
// For example:
//
//   void TMyClass::CalulateComplexNumber()
//   {
//      NOT_IMPLEMENTED(kDave, TMyClass::CalulateComplexNumber);
//   }

#define NOT_IMPLEMENTED(who, func)	DSTOP((who, "Not implemented: " #func))


/////////////////////////////////////////////////////////////////////////////////////////

#if (_WINDOWS && _MINICAD_ && !defined(_INC_WINDOWS)) || !_WINDOWS

	// if Windows.h has not been included, then we may need to use
	// the standard library implementations even under Windows

	//this must follow: #include "GSWin.h"

	#ifndef _INC_STRING

		#if _WINDOWS
		__declspec(dllimport)
		#endif
		Sint32 stricmp(const char *a, const char *b);
	#endif

		#if !_WINDOWS
			#define strcmpi		stricmp
		#endif

#endif


#if !_WINDOWS
	// use the Debug window externally
	#if defined(_MINICAD_EXTERNAL_)
		#define OutputDebugString	Debug
	#else
		#define OutputDebugString(msg)	printf("%s", msg)
	#endif
#else
	extern "C" __declspec(dllimport) void _stdcall DebugBreak(void);
#endif



////////////////////////////////////////////////////////////////////////////////
// Setup for "THIS_FILE" macro.  Use THIS_FILE instead of __FILE__ to reduce
// the size of the executable. [DMB]

#if TEST
	#define DECLARE_THIS_FILE	static const char THIS_FILE[] = __FILE__;
#else
	#define DECLARE_THIS_FILE
#endif
#ifndef THIS_FILE
	#define THIS_FILE __FILE__
#endif



////////////////////////////////////////////////////////////////////////////////
// Use the following macro to print Pascal strings or Rect's in a printf type
// format string.  For example:
//
//		DMSG((dlAlways, "File name: %.*s\n", PASCALPRINT(filename)));
//		DMSG((dlAlways, "myRect: (%d,%d)-(%d,%d)\n", RECTPRINT(myRect)));

#define PASCALPRINT(pascal_string)	\
	((ConstGSStringPtr)(pascal_string))[0], &((ConstGSStringPtr)(pascal_string))[1]

#define RECTPRINT(r)	\
	(r).Left(), (r).Top(), (r).Right(), (r).Bottom()

#define TXSTRINGPRINT(txstring)	\
	(const char*)txstring

//---------------------------------------------------------------------------------------
// --- Debugging
//
// TEST is true if either BUG or NETBUG are true.
// Most general testing code should be in "#ifdef TEST" blocks.
//
// Anything which causes a break or writes to the debug window
// should be in "#ifdef BUG" blocks.

#define	DEBUG_DO_NOTHING	((void) 0)


// Debug levels.
enum EDebugLevel { dlAlways, brief, verbose, mongo, dlNever };


// Include all obsolete functions and macros. DO NOT USE them anymore.
#if GS_USE_OBSOLETE
	#include "GSDebug.obsolete.h"
#endif


/////////////////////////////////////////////////////////////////////////////////////////
#if !_WINDOWS
	// this is really ugly - but it allows our DSTOPs to land us at the right
	// line even if they take place in an ANSI cross platform file - PCP

	#if !defined(__MACTYPES__)
		extern "C" void Debugger(void);
	#endif

	#define	Int13BreakMacro	{ __asm__("int $3\n" : : ); }
	#define	GSBreakToLowLevelDebugger_()		Int13BreakMacro
	#define	GSBreakStrToLowLevelDebugger_(s)	::DebugStr(s)
	#define	GSBreakToSourceDebugger_()			::SysBreak()
	#define	GSBreakStrToSourceDebugger_(s)		::SysBreakStr(s)
#endif



/////////////////////////////////////////////////////////////////////////////////////////
// This hack allows the Mac to build until this code moves back into GSDebug.h for good

#if !_WINDOWS
	#define ASSERTNOFPEXCEPTION() 	DEBUG_DO_NOTHING
	#define ASSERTFPSTACKVALID()	DEBUG_DO_NOTHING
#endif


/////////////////////////////////////////////////////////////////////////////////////////
// The following structure defs are used by externals to communicate back to UCallBacks.cp
// so that they can assert valid handles and pointers. This structure must be compiled
// into the same byte offsets by every compiler we use, so beware of tricky changes. - PCP
//
// If these are changed, then the current crop of externals built with BUG or TEST
// will not work with the new MiniCad, so be careful.

#if !_MAGICFOLDER_
	const short kKludgeSendAssert			= 2001;
	const short kKludgeSendLog				= 2002;
	const short kKludgeValidatePointer		= 2003;
	const short kKludgeValidateHandle		= 2004;
	const short kKludgeCheckHeap			= 2005;
	const short kKludgeCheckPorts			= 2006;
	const short kKludgeValidateString		= 2007;
	const short kKludgeValidatePString		= 2008;
#endif


/////////////////////////////////////////////////////////////////////////////////////////
// kCrashTrapConstant
//
// kCrashTrapConstant is defined to a value which will likely cause an immediate crash
// (of some variety) on any platform. It is used in the TEST and BUG versions to flag
// pointers which are dangerous to use. These pointers should typically be set to nil in
// the release version, but that decision must be made on a case by case basis, so
// kCrashTrapConstant is not defined for the release version

// The above statement is no longer true. We should stop using it this pointer value as a trap. [Hugues 11/21/13] X64PRJ_REVISIT
#if TEST
	const void* const kCrashTrapConstant = (void*) 0x50ff8001;
#endif


/////////////////////////////////////////////////////////////////////////////////////////
#if TEST
	struct AssertParameters {
		char*	toWhom;
		char*	description;
	};

	struct ValidateParameters {
		Bool8	isAssert;
		char*	toWhom;
		char*	file;
		Sint32	line;
		char*	itemName;
		void*	thePointerOrHandle;
		Sint32	expectedSize;
		Sint32	expectedSize2;
	};

	// flag values for ValidatePortParameters
	const Sint32 kAllowWMgrPort = 1L;

	struct ValidatePortParameters {
		char*	message;
		char*	file;
		Sint32	line;
		Sint32	flags;
	};
#endif // TEST


/////////////////////////////////////////////////////////////////////////////////////////
// PORT testing functions

// XXX_JDW_ALTURA CLEANUP [2003-05-28]
//#if TEST && !_MAGICFOLDER_ && (!_WINDOWS || !defined(_INC_WINDOWS)) && !_GSESDK_ && !GS_INTERFACE_FACTORING  && !_WIN_EXTERNAL_
//#if TEST && !_MAGICFOLDER_ && !_GSESDK_ && !_WIN_EXTERNAL_ && defined(_WINDOWS)
#if 0
	// Only do port checking when doing a TEST or BUG build and only when compiling
	// a Mac/Altura module.
	// Don't check the ports if GS_INTERFACE_FACTORING because the core shouldn't know
	// anything about the port in that case.
	#include <QuickDraw.h>
	#define DO_PORT_CHECKING	1
#else 
	#define DO_PORT_CHECKING	0
#endif

#if DO_PORT_CHECKING

	Bool8 IsValidMacPort(GrafPtr port);
	#define __ASSERTPORT(toWhom, msg, port)			DSTOP((!::IsValidMacPort((GrafPtr)(port)), toWhom, "%s: Invalid port (0x%08x)", (const char*)(msg), (GrafPtr)(port)))
	#if _WINDOWS
		#define __ASSERTCURRENTPORT(toWhom, msg)	do { GrafPtr curPort; ::GetPort(&curPort); __ASSERTPORT(toWhom, msg, curPort); } while (0)
	#else
		#define __ASSERTCURRENTPORT(toWhom, msg)	ASSERTLEGALPORTM(msg)
	#endif

	// The LL versions allow the port to be set to the window manager port without
	// complaining. They still check to make sure all handles in the window manager
	// port are in the system heap so we won't crash the system later on. - PCP

	#if _WINDOWS
		#define ASSERTLEGALPORTM(message)			__ASSERTCURRENTPORT(kGrafPortCheck, (message) ? (message) : "ASSERTLEGALPORTM")
		#define LLASSERTLEGALPORTM(message)			__ASSERTCURRENTPORT(kGrafPortCheck, (message) ? (message) : "LLASSERTLEGALPORTM")
	#else
		Sint32 _AssertLegalPort(char *message, const char* file, Sint32 line, Bool8 allowWMgrPort);
		
		#define ASSERTLEGALPORTM(message)			((void)_AssertLegalPort(message, THIS_FILE, __LINE__, false))
		#define LLASSERTLEGALPORTM(message)			((void)_AssertLegalPort(message, THIS_FILE, __LINE__, true))
	#endif
#else
	#if !_MAGICFOLDER_
		#define __ASSERTPORT(toWhom, msg, port)		DEBUG_DO_NOTHING
		#define __ASSERTCURRENTPORT(toWhom, msg)	DEBUG_DO_NOTHING
		#define ASSERTLEGALPORTM(message)			DEBUG_DO_NOTHING
		#define LLASSERTLEGALPORTM(message)			DEBUG_DO_NOTHING
	#endif
#endif // DO_PORT_CHECKING

#if !_MAGICFOLDER_
	// New port checking functions. [DMB 12/13/96]
	#define ASSERTPORT(toWhom, port)				__ASSERTPORT(toWhom, "ASSERTPORT", port)
	#define ASSERTCURRENTPORT(toWhom)				__ASSERTCURRENTPORT(toWhom, "ASSERTCURRENTPORT")

	// Old port checking functions. DO NOT USE THESE.
	#define ASSERTLEGALPORT()						ASSERTLEGALPORTM(NULL)
	#define LLASSERTLEGALPORT()						LLASSERTLEGALPORTM(NULL)
#endif


/////////////////////////////////////////////////////////////////////////////////////////
// Functions and macros to stop the application.  Defines STOP().

#if BUG
	// Define the method used to break into the debugger,
	#if _WINDOWS
		#define DO_STOP()			__debugbreak()
	#else
		#define DO_STOP()			GSBreakToLowLevelDebugger_()
	#endif
	#define STOP()					do { if (GSDebug::WantToBreak()) DO_STOP(); } while(0)
#else
	#define STOP()					DEBUG_DO_NOTHING
#endif // BUG


/////////////////////////////////////////////////////////////////////////////////////////
// Functions to change debug library behavior.

#if TEST

	#if _WINDOWS
		extern "C" Bool8 GSDebug_IsInDebugMessage();
		// Description:
		//   Determine if a debug dialog is currently being displayed.
		//
		// Returns:
		//   BOOL - 'TRUE' if a debug dialog is currently being displayed. 'FALSE' if
		//     no debug dialogs are being displayed.
	#endif

	namespace GSDebug {

		// Replaces 'iWantToDebug'.
		bool GSDEBUG_EXPORT WantToDebug();
		bool GSDEBUG_EXPORT WantToDebug(bool bWantToDebug);

		// Replaces 'debugLevel'.
		EDebugLevel GSDEBUG_EXPORT DebugLevel();
		EDebugLevel GSDEBUG_EXPORT DebugLevel(EDebugLevel newDebuglevel);

		// Replaces 'useSourceDebugger'.
		bool GSDEBUG_EXPORT UseSourceDebugger();
		bool GSDEBUG_EXPORT UseSourceDebugger(bool bUseSourceDebugger);

		// Replaces 'drawToScreen'.
		// Choosing drawToScreen disables GWorlds
		bool GSDEBUG_EXPORT DrawToScreen();
		bool GSDEBUG_EXPORT DrawToScreen(bool bDrawToScreen);

		// Replaces 'iWantToStop'.
		// 'true' to stop application on a STOP(), 'false' to keep going.
		bool GSDEBUG_EXPORT WantToBreak();
		bool GSDEBUG_EXPORT WantToBreak(bool bWantToBreak);

		// Replace the debug flags.
		Uint32 GSDEBUG_EXPORT Flags();
		Uint32 GSDEBUG_EXPORT Flags(Uint32 inNewFlags);


		// Flags for TProgrammer IDs.
		const Uint64 kNoNetDebugFlag		= 0x8000000000000000ULL;
		const Uint64 kNoDebuggerBreakFlag	= 0x4000000000000000ULL;
		const Uint64 kNoDebugWindowFlag		= 0x2000000000000000ULL;
		const Uint64 kNoStackCrawlFlag		= 0x1000000000000000ULL;
		const Uint64 kOnlyIfActiveUserFlag	= 0x0800000000000000ULL;

		// Flags for GS_DebugInit( )
		const Uint32 kNoFlags				= 0x00000000UL;
		const Uint32 kNeverUseDebugWindows	= 0x00000001UL;

	} // namespace GSDebug
#endif	// TEST


/////////////////////////////////////////////////////////////////////////////////////////
// Functions used by DSTOP implementation. Do not use these.

#if TEST
	namespace GSDebug {
		void GSDEBUG_EXPORT SetDStopFileName(ConstGSCStrPtr szFileName);
		void GSDEBUG_EXPORT SetDStopLineNumber(Sint32 nLineNumber);
	} // namespace GSDebug
#endif

#if NETBUG
	// Implementation functions. Do not call these directly.
	#if !_MINICAD_EXTERNAL_
		void InitRemoteDebug(void);
		void KillRemoteDebug(void);
		void LogVersionStamp(void);
	#endif
	class GSDEBUG_EXPORT TProgrammer;
	void GSDEBUG_EXPORT RemoteDebug(const TProgrammer& toWhom, const char *description);
	void GSDEBUG_EXPORT RemoteDebug(const char *toWhom, const char *description, Bool8 doStackCrawl=true);
	void GSDEBUG_EXPORT RemoteLog(Uint16 level, const char *description);
	Sint32  GSDEBUG_EXPORT _Log(Uint16 level, const char *format, ...); // For internal use by LOG macro.
#endif

////////////////////////////////////////////////////////////////////////////////
// TProgrammer class

#if TEST

const short kDebugStringLength = 50;

#define kEveryoneConst		0x0FFFFFFFFFFFFFFFULL // This filters the most significant bits
#define kEveryoneConstLSB	0xFFFFFFFFFFFFFFFFULL // This filters the lesser significant bits
#define kProgrammerMask		0x0FFFFFFFFFFFFFFFULL // this filters the most significant bits
#define kProgrammerMask		0x0FFFFFFFFFFFFFFFULL // this filters the most significant bits
#define kProgrammerMaskLSB	0xFFFFFFFFFFFFFFFFULL // this filters the most significant bits
#define kOptionBitsMask	(~kProgrammerMask)

class GSDEBUG_EXPORT TProgrammer
{
	public:
		TProgrammer()											{ Set("Unnamed", 0, 0, true); }

		TProgrammer(const char *name, Uint64 id2, Uint64 id1, bool sendOwn=true) { Register(name, id2, id1); Set(name, id2, id1, sendOwn); }
		TProgrammer(const TProgrammer& a)						{ Set(a.fName, a.fID2, a.fID1, a.fSendOnOwn); }
	
		const char *GetName() const 							{ return fName; }
		Uint64 GetID2(bool filter=false) const					{ return filter ? (fID2 & kEveryoneConst) : fID2; }
		Uint64 GetID1() const									{ return fID1; }

		bool IsEveryone() const									{ return (fID1 & kEveryoneConstLSB) == kEveryoneConstLSB && (fID2 & kEveryoneConst) == kEveryoneConst; }
		bool IsActLikeRelease() const							{ return (fID1 & kProgrammerMaskLSB) == 0 && (fID2 & kProgrammerMask) == 0;}

		bool LogOnOwn() const;
		bool ShouldBreak() const								{ return !IsActLikeRelease() && !IsNoBreakBitSet(); }
		bool ShouldNetDebug() const								{ return !IsActLikeRelease() && !IsNoNetDebugBitSet(); }
		bool ShouldShowWindow() const							{ return !IsActLikeRelease() && !IsNoWindowBitSet(); }
		bool ShouldDoStackCrawl() const							{ return !IsNoStackCrawlBitSet(); }
	
		TProgrammer operator &(const TProgrammer& a) const;
		TProgrammer operator |(const TProgrammer& a) const		{ return this->operator &(a); }
	
		operator const char *() const							{ return GetName(); }
	
		bool operator ==(const TProgrammer& a) const			{ return MatchExact(a); }
		bool operator !=(const TProgrammer& a) const			{ return !MatchExact(a); }
		bool operator ==(const char *sz) const					{ return _strcmpi(sz, fName)!=0; }
		bool MatchExact(const TProgrammer& a) const				{ return fID2 == a.fID2 && fID1 == a.fID1; }
		bool IsIn(const TProgrammer& a) const					{ return IsIn(a.fID2, a.fID1); }

		// Return true if this "is in" the passed id pair -- which could be a single programmer or a group.
		bool IsIn(Uint64 id2, Uint64 id1) const;

		bool ContainsCurrentUser() const;

		static bool GetProgrammerName(Uint64 id2, Uint64 id1, char *name);
		static bool ExtractProgrammer(TProgrammer &who, TProgrammer &one);
	
		bool IsNoNetDebugBitSet() const							{ return (fID2 & GSDebug::kNoNetDebugFlag) != 0; }
		bool IsNoBreakBitSet() const							{ return (fID2 & GSDebug::kNoDebuggerBreakFlag) != 0; }
		bool IsNoWindowBitSet() const							{ return (fID2 & GSDebug::kNoDebugWindowFlag) != 0; }
		bool IsNoStackCrawlBitSet() const						{ return (fID2 & GSDebug::kNoStackCrawlFlag) != 0; }
		bool IsOnlyIfActiveUserBitSet() const					{ return (fID2 & GSDebug::kOnlyIfActiveUserFlag) != 0; }

	protected:
		void Set(const char *name, Uint64 id2, Uint64 id1, bool sendOwn)		{ strncpy(fName, name, kDebugStringLength-1); fID2 = id2; fID1 = id1; fSendOnOwn = sendOwn; }

	private:

		class GSDEBUG_EXPORT TRegistered
		{
			public:
				TRegistered()									{ fID2 = 0; fID1 = 0; fName[0] = 0; }
				char fName[kDebugStringLength];
				Uint64 fID2, fID1;
		};
		static void Register(const char *name, Uint64 id2, Uint64 id1);
		static const Sint32 fMaxProgrammers;
		static TRegistered fRegistered[];

		char fName[kDebugStringLength];
		Uint64 fID2, fID1;	// Values in significance - so fID2 is higher significant bits than fID1.
		bool fSendOnOwn;
	};

#else

	#define TProgrammer Sint32

#endif // TEST


#if BUG && !defined(_MINICAD_EXTERNAL_)
void InitBugMem();
#endif


/////////////////////////////////////////////////////////////////////////////////////////
#if TEST && !defined(_MINICAD_EXTERNAL_)
	// Implementation functions. Do not call these directly, use the macros.
	GSDEBUG_EXPORT void GDB_DebugInit (const char* appName, Uint32 flags);
	GSDEBUG_EXPORT void GDB_DebugTerminate();
	#if defined(_INC_WINDOWS)
		extern "C" GSDEBUG_EXPORT void GDB_DebugSetExeHandle(HINSTANCE hInst);
		extern "C" GSDEBUG_EXPORT void GDB_SetDebugMessageParentWindow(HWND hParentWnd);
	#endif

	void PerformLaunchAsserts(void);

	// Call DEBUG_INIT() to initialize the GSDebug library. For flags, see GSDebug namespace.
	#define DEBUG_INIT(appName, flags)	::GDB_DebugInit(appName, flags)

	#if defined(_INC_WINDOWS)
		// Set the handle of the executable being run.
		#define DEBUG_SETEXE(hInst)		::GDB_DebugSetExeHandle(hInst)

		// Set the parent window for the next dialog that the debug system displays.
		#define DEBUG_SETPARENTWINDOW(hParentWnd) ::GDB_SetDebugMessageParentWindow(hParentWnd)
	#else
		#define DEBUG_SETEXE(hInst)		DEBUG_DO_NOTHING
	#endif

	// Call DEBUG_TERMINATE to shut down the GSDebug library.
	#define DEBUG_TERMINATE()			::GDB_DebugTerminate()

#endif


/////////////////////////////////////////////////////////////////////////////////////////
#if TEST
	#define MAKEWHO(name)			TProgrammer(name, kEveryoneConst, kEveryoneConstLSB, true)
	#define DECLAREWHO(var, name)	TProgrammer var(name, kEveryoneConst, kEveryoneConstLSB, true)
	#define TEST_ONLY(x)			x
#else
	#define MAKEWHO(name)			0
	#define DECLAREWHO(var, name)	TProgrammer var
	#define TEST_ONLY(x)
#endif // TEST

#if BUG
	#define BUG_ONLY(x)				x
#else
	#define BUG_ONLY(x)
#endif
	

/////////////////////////////////////////////////////////////////////////////////////////
// Routing objects for network asserts

#if TEST
// TProgrammer Defines Table - @1
// This table contains a define and TProgrammer line for every active engineer.
// Note that the "File Value" line must be the same as the actual username used to login to the machine. It is case-insensitive.
//
//	Define name								File Value				fID2					fID1					sendOwn
	#define kJStrouse			TProgrammer("JStrouse",				0x0000000000000000ULL,	0x0000000000000001ULL, true)
	#define kMLieblein			TProgrammer("MLieblein",			0x0000000000000000ULL,	0x0000000000000002ULL, false)
	#define kMVorobyev			TProgrammer("MVorobyev",			0x0000000000000000ULL,	0x0000000000000004ULL, true)
	#define kSteve				TProgrammer("Steve Johnson",		0x0000000000000000ULL,	0x0000000000000008ULL, true)
	#define kZTavor				TProgrammer("ZTavor",				0x0000000000000000ULL,	0x0000000000000010ULL, true)
	#define kPaul				TProgrammer("Paul",					0x0000000000000000ULL,	0x0000000000000020ULL, true)
    #define kAyo				TProgrammer("AOshinnaiye",			0x0000000000000000ULL,	0x0000000000000040ULL, true)
	#define kDave				TProgrammer("Dave",					0x0000000000000000ULL,	0x0000000000000080ULL, false)
	#define kDaveD				TProgrammer("DaveD",				0x0000000000000000ULL,	0x0000000000000100ULL, true)
	#define kAOwens				TProgrammer("AlanOwens", 			0x0000000000000000ULL,	0x0000000000000200ULL, true)
	#define kSPotter			TProgrammer("SPotter",				0x0000000000000000ULL,	0x0000000000000400ULL, true)
	#define kDarick				TProgrammer("Darick",				0x0000000000000000ULL,	0x0000000000000800ULL, false)
	#define kAndrewB			TProgrammer("AndrewB",				0x0000000000000000ULL,	0x0000000000001000ULL | GSDebug::kNoDebugWindowFlag, false)
	#define kIStanchev			TProgrammer("IStanchev",			0x0000000000000000ULL,	0x0000000000002000ULL, true)
	#define kMark				TProgrammer("MFarnan",				0x0000000000000000ULL,	0x0000000000004000ULL, false)
	#define kSPrabu				TProgrammer("Senthil Prabu",		0x0000000000000000ULL,	0x0000000000008000ULL, true)
	#define kBruce				TProgrammer("Bruce",				0x0000000000000000ULL,	0x0000000000010000ULL, false)
    #define kHernan				TProgrammer("Hernan",				0x0000000000000000ULL,	0x0000000000020000ULL, true)
    #define kRobert				TProgrammer("Robert",				0x0000000000000000ULL,	0x0000000000040000ULL, false)
	#define kKKitanov			TProgrammer("KKitanov",				0x0000000000000000ULL,	0x0000000000080000ULL, false)
	#define kMao				TProgrammer("Charlene",				0x0000000000000000ULL,	0x0000000000100000ULL, false)
	#define kTShin				TProgrammer("tshin",				0x0000000000000000ULL,	0x0000000000200000ULL, true)
	#define kKLalkovski			TProgrammer("KLalkovski",			0x0000000000000000ULL,	0x0000000000400000ULL, true)
	#define kEJKerr				TProgrammer("EJKerr",				0x0000000000000000ULL,	0x0000000000800000ULL, true)
	#define kSasha				TProgrammer("Sasha",				0x0000000000000000ULL,	0x0000000001000000ULL, true)
	#define kBStanchev			TProgrammer("BStanchev",			0x0000000000000000ULL,	0x0000000002000000ULL, true)
	#define kYKostadinov		TProgrammer("YKostadinov",			0x0000000000000000ULL,	0x0000000004000000ULL, true)
	#define kVPeichev			TProgrammer("VPeichev",				0x0000000000000000ULL,	0x0000000008000000ULL, true)
	#define kVictor				TProgrammer("Victor",				0x0000000000000000ULL,	0x0000000010000000ULL, true)
	#define kAbdel				TProgrammer("Abdel",				0x0000000000000000ULL,	0x0000000020000000ULL, true)
	#define kAGhosh				TProgrammer("AGhosh",				0x0000000000000000ULL,	0x0000000040000000ULL, true)
	#define kAlex				TProgrammer("Alex",					0x0000000000000000ULL,	0x0000000080000000ULL, true)
	#define kBiplab				TProgrammer("Biplab",				0x0000000000000000ULL,	0x0000000100000000ULL, true)
	#define kFAbbasinejad		TProgrammer("FAbbasinejad",			0x0000000000000000ULL,	0x0000000200000000ULL, true)
	#define kNIvanova			TProgrammer("nivanova",				0x0000000000000000ULL,	0x0000000400000000ULL, true)
	#define kVStanev			TProgrammer("vstanev",				0x0000000000000000ULL,	0x0000000800000000ULL, true)
	#define kMRizov				TProgrammer("MRizov",				0x0000000000000000ULL,	0x0000001000000000ULL, true)
	#define kNHilendarov		TProgrammer("NHilendarov",			0x0000000000000000ULL,	0x0000002000000000ULL, true)
	#define kLArsenyuk			TProgrammer("LArsenyuk",			0x0000000000000000ULL,	0x0000004000000000ULL, true)
	#define kAValchev			TProgrammer("AValchev",				0x0000000000000000ULL,	0x0000008000000000ULL, true)
	#define kRBerge		 		TProgrammer("RBerge",				0x0000000000000000ULL,	0x0000010000000000ULL, true)
	#define kPChang				TProgrammer("PChang",				0x0000000000000000ULL,	0x0000020000000000ULL, true)
	#define kKIvanov			TProgrammer("KIvanov",				0x0000000000000000ULL,	0x0000040000000000ULL, true)
	#define kDKasavetova		TProgrammer("DKasavetova",			0x0000000000000000ULL,	0x0000080000000000ULL, true)
	#define kJHutchison			TProgrammer("JHutchison",			0x0000000000000000ULL,	0x0000100000000000ULL, true)
	#define kCGraye				TProgrammer("CGraye",				0x0000000000000000ULL,	0x0000200000000000ULL, true)
	#define kILane 				TProgrammer("ILane",				0x0000000000000000ULL,	0x0000400000000000ULL, true)
	#define kNZhelyazkov		TProgrammer("NZhelyazkov", 			0x0000000000000000ULL,	0x0000800000000000ULL, true)
	#define kHTsafak			TProgrammer("HTsafak",				0x0000000000000000ULL,	0x0001000000000000ULL, true)
	#define kJLoy				TProgrammer("JLoy",					0x0000000000000000ULL,	0x0002000000000000ULL, true)
	#define kTolu				TProgrammer("Tolu",					0x0000000000000000ULL,	0x0004000000000000ULL, true)
	#define kDSanford			TProgrammer("DSanford",				0x0000000000000000ULL,	0x0008000000000000ULL, true)
	#define kDNguyen			TProgrammer("DNguyen",				0x0000000000000000ULL,	0x0010000000000000ULL, true)
	#define kBGeiger			TProgrammer("BGeiger",				0x0000000000000000ULL,	0x0020000000000000ULL, true)
	#define kJWarshaw			TProgrammer("JWarshaw",				0x0000000000000000ULL,	0x0040000000000000ULL, true)
	#define kBAtwood			TProgrammer("BAtwood",				0x0000000000000000ULL,	0x0080000000000000ULL, true)
	#define kTArdoin			TProgrammer("TArdoin",				0x0000000000000000ULL,	0x0100000000000000ULL, true)
	#define kMFlamer			TProgrammer("MarkFlamer",			0x0000000000000000ULL,	0x0200000000000000ULL, true)
	#define kGDixon				TProgrammer("GDixon",				0x0000000000000000ULL,	0x0400000000000000ULL, true)
	#define kVKitanov			TProgrammer("VKitanov",				0x0000000000000000ULL,	0x0800000000000000ULL, true)
	#define kAGorbaty			TProgrammer("AGorbaty",				0x0000000000000000ULL,	0x1000000000000000ULL, true)
	#define kFZafar				TProgrammer("FZafar",				0x0000000000000000ULL,	0x2000000000000000ULL, true)
	#define kMGeorgiev			TProgrammer("MGeorgiev",			0x0000000000000000ULL,	0x4000000000000000ULL, true)
	#define kHLiatis			TProgrammer("HLiatis",				0x0000000000000000ULL,	0x8000000000000000ULL, true)
	#define kHema				TProgrammer("Hema",					0x0000000000000001ULL,	0x0000000000000000ULL, true)
	#define kMAydin				TProgrammer("MAydin",				0x0000000000000002ULL,	0x0000000000000000ULL, true)
	#define kJGruendler			TProgrammer("JGruendler",			0x0000000000000004ULL,	0x0000000000000000ULL, true)
	#define kCPHsiao			TProgrammer("CPHsiao",				0x0000000000000008ULL,	0x0000000000000000ULL, true)
	#define kIBorisov			TProgrammer("IBorisov",				0x0000000000000010ULL,	0x0000000000000000ULL, true)
	#define kGKutleva			TProgrammer("GKutleva",				0x0000000000000020ULL,	0x0000000000000000ULL, true)
	#define kEKolev				TProgrammer("EKolev",				0x0000000000000040ULL,	0x0000000000000000ULL, true)
	#define kNBeshevliev		TProgrammer("NBeshevliev",			0x0000000000000080ULL,	0x0000000000000000ULL, true)
	#define kKGoranov			TProgrammer("KGoranov",				0x0000000000000100ULL,	0x0000000000000000ULL, true)
	#define kBBudzon			TProgrammer("BBudzon",				0x0000000000000200ULL,	0x0000000000000000ULL, true)
    #define kOKadry				TProgrammer("OKadry",				0x0000000000000400ULL,	0x0000000000000000ULL, true)
	#define kVGenchev			TProgrammer("VGenchev",				0x0000000000000800ULL,	0x0000000000000000ULL, true)
	#define kYRusev				TProgrammer("YRusev",				0x0000000000001000ULL,	0x0000000000000000ULL, true)
	#define kBMarinov			TProgrammer("BMarinov",				0x0000000000002000ULL,	0x0000000000000000ULL, true)
	#define kGTaylor			TProgrammer("GTaylor",				0x0000000000004000ULL,	0x0000000000000000ULL, true)

	// Special values
	#define kEveryone			MAKEWHO("Everyone")
	#define kActLikeRelease		TProgrammer("No One (null)",		0x0000000000000000ULL,			0x0000000000000000ULL, false))
	#define kNoNetDebug			TProgrammer("No Net Debug",			GSDebug::kNoNetDebugFlag,		0x0000000000000000ULL, false)
	#define kNoBreak			TProgrammer("No Debugger Break",	GSDebug::kNoDebuggerBreakFlag,	0x0000000000000000ULL, false)
	#define kNoWindow			TProgrammer("No Window",			GSDebug::kNoDebugWindowFlag,	0x0000000000000000ULL, false)
	#define kNoStackCrawl		TProgrammer("No Stack Crawl",		GSDebug::kNoStackCrawlFlag,		0x0000000000000000ULL, false)
	#define kOnlyIfActiveUser	TProgrammer("Only If Active user",	GSDebug::kOnlyIfActiveUserFlag,	0x0000000000000000ULL, false)


	// @2 Departed Engineers whose ASSERTs have been transferred to some-one/thing else
	#define	kMatt				kEveryone
	#define kIRovelov			kKIvanov
	#define kANikolova			kSasha
	#define kJim				kEveryone
	#define kJimG				kEveryone
	#define kJeff				kEveryone
	#define kJGeraci			kEveryone
	#define kAStanton			kEveryone
	#define kRFoster			kEveryone
	#define kChris				kEveryone
	#define kRich				kEveryone
	#define kShirley			kEveryone
	#define kSean               kEveryone
    #define kRamsey             kEveryone
    #define kNBhandari          kEveryone
	#define	kCStulberger		kEveryone
	#define kNHenkel			kEveryone
    #define kMike               kEveryone
	#define kChao				kEveryone
	#define kKarim				kEveryone
	#define kAbouzar			kEveryone
	#define kPKameo 			kEveryone
	#define kSLam 				kEveryone
	#define kRichn 				kEveryone
	#define kTroy  				kEveryone
	#define kCaleb  			kEveryone
	#define kLewis  			kEveryone
	#define kGeorge 			kEveryone
	#define kRLevin  			kEveryone
	#define kZPage  			kEveryone
	#define kCarrie  			kEveryone
	#define kEGorr  			kEveryone
	#define kMikeD  			kEveryone
	#define	kJSingh				kEveryone
	#define kAStevanovic		kEveryone
	#define kCAllen				kEveryone
	#define	kMMcDonnell			kEveryone
	#define kLyndsey			kEveryone
	#define kKKasinathan		kEveryone
	#define kDan				kEveryone
	#define kASowayan			kEveryone
	#define kPSorensen			kEveryone
	#define kESaari				kEveryone
	#define kDBiser				kEveryone
	#define kPFletcher			kEveryone
	#define kSGruber			kEveryone
	#define kYSimeonov			kNBeshevliev
	#define kMVelichkova		kKGoranov
	#define kBMarinari			kEveryone
	#define kKMarsh				kEveryone
	#define kBWilliams			kEveryone
	#define kDonne				kEveryone


	#if _MAGICFOLDER_
		#define kOpenLog			MAKEWHO("MFOpenLog")
	#else
		#define	kAbortLowMem		MAKEWHO("AbortLowMem")
		#define	kDialogError		MAKEWHO("Dialog Class")
		#define	kFastMul			MAKEWHO("FastMul")
		#define	kFastMulInterim		MAKEWHO("FastMul")
		#define	kGrafPortCheck		MAKEWHO("GrafPortCheck")
		#define	kHandleCheck		MAKEWHO("Handle Check")
		#define	kListFailure		MAKEWHO("ListFailure")
		#define kMCCoordTypes		MAKEWHO("MCCoordTypes")
		#define	kMemTiming			MAKEWHO("New Memory Timing")
		#define	kMiniPascal			MAKEWHO("MiniPascal")
		#define	kOverflows			MAKEWHO("Overflows")
		#define	kPointerCheck		MAKEWHO("Pointer Check")
		#define	kRefListFailure		MAKEWHO("RefListFailure")
		#define	kStaticArrayToWhom	MAKEWHO("Static Array Overflow")
		#define	kUnlabled			MAKEWHO("Unlabled Breaks")
		#define	kWorksheetFailure	MAKEWHO("WorksheetFailure")
		#define	kTextFailure		MAKEWHO("TextFailure")
	#endif

	Bool8 GSDEBUG_EXPORT _IsUser(const char *szUser);
	Bool8 GSDEBUG_EXPORT _IsUser(const TProgrammer& who);
	#define ONUSER(user, func)	do { if (::_IsUser(user)) { func; } } while(0)

#else // TEST
// Release version definitions:

	#define __ignore_programmer Sint32(0)

	// @3: Release mode empty programmer defines for active engineers:
	#define kJStrouse			__ignore_programmer
	#define	kMLieblein 			__ignore_programmer
	#define kMVorobyev			__ignore_programmer
	#define kSteve				__ignore_programmer
	#define kZTavor 			__ignore_programmer
	#define kPaul				__ignore_programmer
	#define kAyo				__ignore_programmer
	#define kDave				__ignore_programmer
	#define kDaveD				__ignore_programmer
	#define kAOwens				__ignore_programmer
	#define kSPotter			__ignore_programmer
	#define kDarick				__ignore_programmer
	#define kAndrewB			__ignore_programmer
	#define	kIStanchev			__ignore_programmer
	#define	kMark				__ignore_programmer
	#define kSPrabu				__ignore_programmer
	#define kBruce				__ignore_programmer
	#define kHernan				__ignore_programmer
	#define kRobert				__ignore_programmer
	#define	kKKitanov			__ignore_programmer
	#define kMao				__ignore_programmer
	#define kTShin				__ignore_programmer
	#define	kKLalkovski			__ignore_programmer
	#define kEJKerr				__ignore_programmer
	#define kSasha				__ignore_programmer
	#define	kBStanchev			__ignore_programmer
	#define	kYKostadinov		__ignore_programmer
	#define kVPeichev  			__ignore_programmer
	#define kVictor				__ignore_programmer
	#define kAbdel				__ignore_programmer
	#define kAGhosh 			__ignore_programmer
	#define kAlex				__ignore_programmer
	#define kBiplab				__ignore_programmer
	#define kFAbbasinejad		__ignore_programmer
	#define kNIvanova			__ignore_programmer
	#define kVStanev			__ignore_programmer
	#define kMRizov				__ignore_programmer
	#define kNHilendarov		__ignore_programmer
	#define kLArsenyuk			__ignore_programmer
	#define kAValchev			__ignore_programmer
	#define kRBerge				__ignore_programmer
	#define kPChang				__ignore_programmer
	#define kKIvanov			__ignore_programmer
	#define	kDKasavetova		__ignore_programmer
	#define kJHutchison			__ignore_programmer
	#define kCGraye				__ignore_programmer
	#define kILane				__ignore_programmer
	#define kNZhelyazkov		__ignore_programmer
	#define kHTsafak			__ignore_programmer
	#define kJLoy				__ignore_programmer
	#define	kTolu				__ignore_programmer
	#define kDSanford			__ignore_programmer
	#define kDNguyen			__ignore_programmer
	#define kBGeiger			__ignore_programmer 
	#define kJWarshaw			__ignore_programmer
	#define kBAtwood			__ignore_programmer
	#define	kTArdoin			__ignore_programmer
	#define	kMFlamer			__ignore_programmer
	#define kGDixon				__ignore_programmer
	#define	kVKitanov			__ignore_programmer
	#define kAGorbaty			__ignore_programmer
	#define kFZafar				__ignore_programmer
	#define kMGeorgiev			__ignore_programmer
	#define kHLiatis			__ignore_programmer
	#define kHema				__ignore_programmer
	#define kMAydin				__ignore_programmer
	#define kJGruendler			__ignore_programmer
	#define kCPHsiao			__ignore_programmer
	#define kIBorisov			__ignore_programmer
	#define kGKutleva			__ignore_programmer
	#define kEKolev				__ignore_programmer
	#define kNBeshevliev		__ignore_programmer
	#define kKGoranov			__ignore_programmer
	#define kBBudzon			__ignore_programmer
	#define kOKadry				__ignore_programmer
	#define kVGenchev			__ignore_programmer
	#define kYRusev				__ignore_programmer
	#define kBMarinov			__ignore_programmer
	#define kGTaylor			__ignore_programmer

	// Special Values
	#define kEveryone			__ignore_programmer
	#define kActLikeRelease		__ignore_programmer
	#define kNoNetDebug			__ignore_programmer
	#define kNoBreak			__ignore_programmer
	#define kNoWindow			__ignore_programmer
	#define kNoStackCrawl		__ignore_programmer
	#define kOnlyIfActiveUser	__ignore_programmer


	// @4: Release mode empty programmer defines for departed engineers:
	#define kMatt				__ignore_programmer
	#define	kIRovelov			__ignore_programmer
	#define kANikolova			__ignore_programmer
	#define kJim				__ignore_programmer
	#define kJimG				__ignore_programmer
	#define kJeff				__ignore_programmer
	#define kJGeraci			__ignore_programmer
	#define kAStanton			__ignore_programmer
	#define kRFoster			__ignore_programmer
	#define kChris				__ignore_programmer
	#define kRich				__ignore_programmer
	#define kShirley			__ignore_programmer
	#define kSean				__ignore_programmer
	#define kRamsey				__ignore_programmer
	#define kNBhandari			__ignore_programmer
	#define	kCStulberger		__ignore_programmer
	#define kAyo				__ignore_programmer
	#define kNHenkel			__ignore_programmer
	#define	kMike				__ignore_programmer
	#define kChao				__ignore_programmer
	#define kKarim				__ignore_programmer
	#define kAbouzar			__ignore_programmer
	#define kPKameo				__ignore_programmer
	#define kSLam				__ignore_programmer
	#define kRichn				__ignore_programmer
	#define kTroy				__ignore_programmer
	#define kCaleb				__ignore_programmer
	#define kLewis				__ignore_programmer
	#define kGeorge				__ignore_programmer
	#define kRLevin				__ignore_programmer
	#define kZPage				__ignore_programmer
	#define	kCarrie				__ignore_programmer
	#define kEGorr				__ignore_programmer
	#define kMikeD  			__ignore_programmer
	#define kJSingh				__ignore_programmer
	#define kAStevanovic		__ignore_programmer
	#define kCAllen             __ignore_programmer
	#define kMMcDonnell			__ignore_programmer
	#define kLyndsey			__ignore_programmer
	#define kKKasinathan 		__ignore_programmer
	#define kDan				__ignore_programmer
	#define kASowayan			__ignore_programmer
	#define kPSorensen			__ignore_programmer
	#define kESaari				__ignore_programmer
	#define kDBiser		 		__ignore_programmer
	#define	kPFletcher			__ignore_programmer
	#define kSGruber			__ignore_programmer
	#define kYSimeonov			__ignore_programmer	
	#define kBMarinari			__ignore_programmer
	#define	kMVelichkova		__ignore_programmer
	#define kKMarsh				__ignore_programmer
	#define kBWilliams			__ignore_programmer
	#define	kDonne				__ignore_programmer

#endif // TEST

#define kWinOnly				( kJimG | kDave )
#define kDXFers					( kNIvanova | kVKitanov | kIStanchev | kDKasavetova )


//----------------------------------------------------
// @5: The following list is a big "or" of ever active programmer.
// This is necessary because of how the registration was written. Until an assert is reached, the #define is not used
// Thus they are not registered. So for asserts that use kEveryone may not fire for a user unless they just happen to have
// had an assert/verify/etc in their name before that point. In GSDebug.cpp we just make a global variable from this macro,
// registering everyone at an early stage.
//
#define kEveryoneUsedForRegistration ( \
kJStrouse			| \
kMLieblein			| \
kMVorobyev			| \
kSteve				| \
kZTavor				| \
kPaul				| \
kAyo				| \
kDave				| \
kDaveD				| \
kAOwens				| \
kSPotter			| \
kDarick				| \
kAndrewB			| \
kIStanchev			| \
kMark				| \
kSPrabu				| \
kBruce				| \
kHernan				| \
kRobert				| \
kKKitanov			| \
kMao				| \
kTShin				| \
kKLalkovski			| \
kEJKerr				| \
kSasha				| \
kBStanchev			| \
kYKostadinov		| \
kVPeichev			| \
kVictor				| \
kAbdel				| \
kAGhosh				| \
kAlex				| \
kBiplab				| \
kFAbbasinejad		| \
kNIvanova			| \
kVStanev			| \
kMRizov				| \
kNHilendarov		| \
kLArsenyuk			| \
kAValchev			| \
kRBerge				| \
kPChang				| \
kKIvanov			| \
kDKasavetova		| \
kJHutchison			| \
kCGraye				| \
kILane 				| \
kNZhelyazkov		| \
kHTsafak			| \
kJLoy				| \
kTolu				| \
kDSanford			| \
kDNguyen			| \
kBGeiger			| \
kJWarshaw			| \
kBAtwood			| \
kTArdoin			| \
kMFlamer			| \
kGDixon				| \
kVKitanov			| \
kAGorbaty			| \
kFZafar				| \
kMGeorgiev			| \
kHLiatis			| \
kHema				| \
kMAydin				| \
kJGruendler			| \
kCPHsiao			| \
kIBorisov			| \
kGKutleva			| \
kEKolev				| \
kNBeshevliev		| \
kKGoranov			| \
kBBudzon			| \
kOKadry			    | \
kVGenchev			| \
kYRusev				| \
kBMarinov			| \
kGTaylor			| \
kEveryone)
// End of list of all active programmers or'd together to ensure registration




#if TEST

#if BUG
	#if 1 || _MINICAD_EXTERNAL_ || _MAGICFOLDER_ || _GSESDK_ || _GSWINSDK_
		inline void LIMITMESSAGES(const TProgrammer &)								{ }
		inline void LIMITMESSAGES(const EDebugLevel &)								{ }
		inline void LIMITMESSAGES(const TProgrammer &, const EDebugLevel &)			{ }
		inline void LIMITMESSAGES(const EDebugLevel &, const TProgrammer &)			{ }
		inline void LIMITMESSAGES()													{ }
	#else
		extern TProgrammer gProgrammerFilter;
		
		inline void LIMITMESSAGES(const TProgrammer &who)							{ gProgrammerFilter = who; }
		inline void LIMITMESSAGES(const EDebugLevel &level)							{ debugLevel = level; }
		inline void LIMITMESSAGES(const TProgrammer &who, const EDebugLevel &level)	{ LIMITMESSAGES(who); LIMITMESSAGES(level); }
		inline void LIMITMESSAGES(const EDebugLevel &level, const TProgrammer &who)	{ LIMITMESSAGES(who, level); }
		inline void LIMITMESSAGES()													{ LIMITMESSAGES(kEveryone, brief); }
	#endif
#endif // BUG


/*
The following routines and macros are hooked into the network debugging system. You will receive a file
describing when these breaks occur on any Graphsoft Macintosh machine (Engineering, Tech Support, etc.).
*/

Sint32 GSDEBUG_EXPORT _FileDebugMessage(const TProgrammer& toWhom, const char *file, Sint32 line, const char *message);
Sint32 GSDEBUG_EXPORT _Assert(const TProgrammer& toWhom, const char *file, Sint32 line, const char *expr);
Sint32 GSDEBUG_EXPORT _AssertEx(const TProgrammer & inProgrammer, const char * inAssertFile, Sint32 inAssertLine, const char * inMessage, ...);

	// For internal use by ASSERT macro only.

#if !_WINDOWS

	enum {
		kNoBlock = 0,
		kHandle = 1,
		kPointer = 2,
		kFree = 3
	};

	short _FindContainingBlock(const TProgrammer& toWhom, void* ptr, Sint32& result);

	Sint32 _AssertNotVolatile(const TProgrammer& toWhom, const char* file, Sint32 line, const char* ptrName, void* ptr);
		// For internal use by ASSERTNOTVOLATILE macro only.

#endif // !_WINDOWS

void GSDEBUG_EXPORT CheckHeap(const TProgrammer &toWhom = kEveryone);
	// checks the heap for a number of problems - hooked into the new memory system - checks fragmentation
	// this may be called at any time memory operations are legal - it can take a while with full heaps
	// this is primarily called from the main event loop - you should probably not need to call it



Sint32 GSDEBUG_EXPORT _AssertValidPointer(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, const void *ptr, size_t lByteCount=1, Bool8 bReadOnly=false);
Bool8 GSDEBUG_EXPORT _VerifyValidPointer(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, const void *ptr, size_t lCount=1, Bool8 bReadOnly=false);
Sint32 GSDEBUG_EXPORT _AssertValidString(Bool8 isAssert, const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, const char *psz, Sint32 cbMin=0, Sint32 cbMax=0);
Sint32 GSDEBUG_EXPORT _AssertValidHandle(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, GSHandle h, size_t lCount=1);
Sint32 GSDEBUG_EXPORT _AssertValidMenuHandle(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, GSHandle h);
Bool8 GSDEBUG_EXPORT _VerifyValidHandle(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, GSHandle h, size_t lCount=1);
Sint32 GSDEBUG_EXPORT _AssertValidPString(Bool8 isAssert, const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, ConstGSStringPtr ps, Sint32 cbMin=0, Sint32 cbMax=0);



#if defined(_INC_WINDOWS) || defined(_GSWIN_) || GS_HWND_CHECK
	extern "C" {
		bool GSDEBUG_EXPORT _ValidateHWND(const TProgrammer& toWhom, bool bAssert, const char* file, Sint32 line, const char* itemName, void *hWnd);
		bool GSDEBUG_EXPORT _ValidateHDC(const TProgrammer& toWhom, bool bAssert, const char* file, Sint32 line, const char* itemName, void *hdc);

		// *PCP* - we may want to move this back from the structured exceptions file
		//void GSDEBUG_EXPORT ForceFPException_( void );
	}
#endif



/* Debugging macros.  All of these may be used without #ifdef BUG...#endif. */

//
//	ASSERTs
//

inline Bool8 VerifyStop(Bool8 b) { STOP(); return b; }	// Special function since one can not put an "_asm" instruction in the middle of a "?:" expression. [DMB, 11/30/94]
#if _WINDOWS
// These are the Windows ASSERT macros.
	#define ASSERTN(toWhom, exp) \
				do { \
					if (!(exp) && _Assert(toWhom, THIS_FILE, __LINE__, #exp)) STOP(); \
				} while (0)

	#define ASSERTLOCKED(toWhom, h) do {;} while (0)
	#define ASSERTUNLOCKED(toWhom, h) do {;} while (0)
	#define ASSERTNOTVOLATILE(toWhom, p) do {;} while (0)
	#define ASSERTHANDLE(toWhom, h, bytes) do {;} while (0)
	#define ASSERTPSTRING(toWhom, ps, min, max) do {;} while (0)
	#define VERIFYN(toWhom, exp)	\
				((Bool8)( (exp) ? true : (_Assert(toWhom, THIS_FILE, __LINE__, #exp) ? VerifyStop(false) : false ) ))

	#define VERIFYMSG(toWhom, exp, failMsg, ...)	\
				((Bool8)( (exp) ? true : (_AssertEx(toWhom, THIS_FILE, __LINE__, failMsg, __VA_ARGS__) ? VerifyStop(false) : false ) ))

	#define ASSERTPOINTER_READONLY(toWhom, ptr, bytes) do {;} while (0)
	#define ASSERTPOINTER(toWhom, ptr, bytes) do {;} while (0)
	#define ASSERTSTRING(toWhom, psz, min, max)  \
				do { \
					if (_AssertValidString(true,toWhom,THIS_FILE,__LINE__,#psz,(const char *)psz,min,max)) STOP(); \
				} while (0)

	#if GS_HWND_CHECK

		#define ASSERTHWND(toWhom, hWnd) \
					do { \
						if (!_ValidateHWND(toWhom,true,THIS_FILE,__LINE__,#hWnd,hWnd)) STOP(); \
					} while (0)
		#define VERIFYHWND(toWhom, hWnd) \
					( _ValidateHWND(toWhom,FALSE,THIS_FILE,__LINE__,#hWnd,hWnd) ? true : false )
		#define ASSERTHDC(toWhom, hdc) \
					do { \
						if (!_ValidateHDC(toWhom,true,THIS_FILE,__LINE__,#hdc,hdc)) STOP(); \
					} while (0)
		#define VERIFYHDC(toWhom, hdc) \
					( _ValidateHDC(toWhom,FALSE,THIS_FILE,__LINE__,#hdc,hdc) ? true : false )
	#endif


#if 0
	#define ASSERTNOFPEXCEPTION() \
				ForceFPException_()
#endif

#else	// !_WINDOWS

// These are the Mac ASSERT macros.

	#define ASSERTN(toWhom, expression) \
				do { \
					if (!(expression) && _Assert(toWhom, THIS_FILE, __LINE__, #expression)) STOP(); \
				} while (0)


	#define VERIFYN(toWhom, exp)	\
				((Bool8)( (exp) ? true : (_Assert(toWhom, THIS_FILE, __LINE__, #exp) ? VerifyStop(false) : false ) ))

	#define VERIFYMSG(toWhom, exp, failMsg, ...)	\
				((Bool8)( (exp) ? true : (_AssertEx(toWhom, THIS_FILE, __LINE__, failMsg, ##__VA_ARGS__) ? VerifyStop(false) : false ) ))

	#define ASSERTSTRING(toWhom, psz, min, max) \
					((void)_AssertValidString(true,toWhom,THIS_FILE,__LINE__,#psz,(const char *)psz,min,max))

	#define ASSERTPOINTER(toWhom, ptr, bytes) \
					((void)_AssertValidPointer(toWhom,THIS_FILE,__LINE__,#ptr,ptr,bytes))

	#define ASSERTPOINTER_READONLY(toWhom, ptr, bytes) ASSERTPOINTER(toWhom, ptr, bytes)

	Bool8 __IsHandleLocked(GSHandle h);

//	#define ASSERTLOCKED(toWhom,h) \
//			( h?(__IsHandleLocked((GSHandle)h) ? (void)0 : (void)_Assert(toWhom,THIS_FILE,__LINE__,"\"" #h " locked\"")) : (void)0 )
//	#define ASSERTUNLOCKED(toWhom,h) \
//			( h?(__IsHandleLocked((GSHandle)h) ? (void)_Assert(toWhom,THIS_FILE,__LINE__,"\"" #h " unlocked\"") : (void)0) : (void)0 )

	// The concept of locked/unlocked handles no longer exists
	#define ASSERTLOCKED(toWhom,h) ((void) 0)
	#define ASSERTUNLOCKED(toWhom,h) ((void) 0)

	#define ASSERTNOTVOLATILE(toWhom, p) \
				( ((void)_AssertNotVolatile(toWhom, THIS_FILE, __LINE__, #p, p)) )
	#define ASSERTHANDLE(toWhom, h, bytes) \
				((void)_AssertValidHandle(toWhom,THIS_FILE,__LINE__,#h,(GSHandle)h,bytes))

	#define ASSERTPSTRING(toWhom, ps, min, max) \
				((void)_AssertValidPString(true,toWhom,THIS_FILE,__LINE__,#ps,(const BugStringPtr)ps,min,max))

	#if GS_HWND_CHECK
		#define ASSERTHWND(toWho, hWnd) \
						DEBUG_DO_NOTHING
		#define VERIFYHWND(toWho, hWnd) \
						(FALSE)
	#endif

#if 0
	#define ASSERTNOFPEXCEPTION() \
						DEBUG_DO_NOTHING
#endif

#endif // _WINDOWS


// these apply to both Mac and Win versions

	
#define VERIFYHANDLE(toWhom, h, bytes)	\
			::_VerifyValidHandle(toWhom,THIS_FILE,__LINE__,#h,(GSHandle)h,bytes)

#define ASSERTHEAP(toWhom) \
			::CheckHeap(toWhom)

#define VERIFYPOINTER(toWhom, ptr, bytes)	\
			::_VerifyValidPointer(toWhom,THIS_FILE,__LINE__,#ptr,ptr,bytes,false)

#define VERIFYPOINTER_READONLY(toWhom, ptr, bytes)	\
			::_VerifyValidPointer(toWhom,THIS_FILE,__LINE__,#ptr,ptr,bytes,true)

#define VERIFYSTRING(toWhom, psz, min, max)  \
			::_AssertValidString(false,toWhom,THIS_FILE,__LINE__,#psz,(const char*)psz,min,max)

#define VERIFYPSTRING(toWhom, ps, min, max)  \
			::_AssertValidPString(false,toWhom,THIS_FILE,__LINE__,#ps,(const BugStringPtr)ps,min,max)

#define ASSERTMENUHANDLE(toWhom, menu) \
			::_AssertValidMenuHandle(toWhom,THIS_FILE,__LINE__,#menu,(GSHandle)menu)


/////////////////////////////////////////////////////////////////////////////////////////
//	DSTOP
extern std::atomic_flag gDSTOPLock;

#define DSTOP(params)	do { \
							if ( ! gDSTOPLock.test_and_set()) { \
								GSDebug::SetDStopFileName(THIS_FILE); \
								GSDebug::SetDStopLineNumber(__LINE__); \
								if (::__DebugMessageStop params) STOP(); \
								GSDebug::SetDStopLineNumber(-1); \
								gDSTOPLock.clear(); \
							} \
						} while(0)



#define GS_REMOVE_CONDITIONAL_DebugMessageStop 1

#if GS_REMOVE_CONDITIONAL_DebugMessageStop
#define DSTOPIF(condition, params) if (condition) DSTOP(params);
#else
#define DSTOPIF(condition, params) DEBUG_DO_NOTHING
#endif

// DSTOP implementation functions.
Bool8 GSDEBUG_EXPORT __DebugMessageStop(const TProgrammer& toWhom, EDebugLevel level, const char *szFmt, ...);
Bool8 GSDEBUG_EXPORT __DebugMessageStop(EDebugLevel level, const TProgrammer& toWhom, const char *szFmt, ...);
Bool8 GSDEBUG_EXPORT __DebugMessageStop(EDebugLevel level, const char *szFmt, ...);
Bool8 GSDEBUG_EXPORT __DebugMessageStop(const TProgrammer& toWhom, const char *szFmt, ...);
//
#if ! GS_REMOVE_CONDITIONAL_DebugMessageStop
Bool8 GSDEBUG_EXPORT __DebugMessageStop(Bool8 exp, const TProgrammer& toWhom, EDebugLevel level, const char *szFmt, ...);
Bool8 GSDEBUG_EXPORT __DebugMessageStop(Bool8 exp, EDebugLevel level, const TProgrammer& toWhom, const char *szFmt, ...);
Bool8 GSDEBUG_EXPORT __DebugMessageStop(Bool8 exp, EDebugLevel level, const char *szFmt, ...);
Bool8 GSDEBUG_EXPORT __DebugMessageStop(Bool8 exp, const TProgrammer& toWhom, const char *szFmt, ...);
Bool8 GSDEBUG_EXPORT __DebugMessageStop(Bool8 exp, const char *szFmt, ...);
#endif
/////////////////////////////////////////////////////////////////////////////////////////

#define INLINE


#endif	// TEST


#ifdef BUG

//
//	DMSG
//
#define DMSG(params)					::__DebugMessage params
//


#define DMSGIF(condition, params) if (condition) DMSG(params);

// the modern behavior is to require a TProgrammer attached to all debug calls
#if !GS_USE_ONLY_MODERN || GS_GSDEBUG_BUILD
void GSDEBUG_EXPORT __DebugMessage(EDebugLevel level, const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(const char *szFmt, ...);
#if ! GS_REMOVE_CONDITIONAL_DebugMessageStop
void GSDEBUG_EXPORT __DebugMessage(Bool8 exp, EDebugLevel level, const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(Bool8 exp, const char *szFmt, ...);
#endif
#endif
void GSDEBUG_EXPORT __DebugMessage(const TProgrammer& toWhom, EDebugLevel level, const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(EDebugLevel level, const TProgrammer& toWhom, const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(const TProgrammer& toWhom, const char *szFmt, ...);
#if ! GS_REMOVE_CONDITIONAL_DebugMessageStop
void GSDEBUG_EXPORT __DebugMessage(Bool8 exp, const TProgrammer& toWhom, EDebugLevel level, const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(Bool8 exp, EDebugLevel level, const TProgrammer& toWhom, const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(Bool8 exp, const TProgrammer& toWhom, const char *szFmt, ...);
#endif
#endif	// ifdef BUG

// New class debugging stuff.

#if GS_USE_CLASS_DEBUGGING
#ifdef BUG
	class GSDEBUG_EXPORT TDumpDevice
	{
	public:
		TDumpDevice();


		virtual ~TDumpDevice() {}
		
		Sint32 printf(const TProgrammer &toWhom, Sint32 indent, const char *fmt, ...) const;
		Sint32 printf(const char *fmt, ...) const;

		void SetIndent(Sint32 indent)				{ fIndent = indent; }
		void SetWho(const TProgrammer &toWhom)	{ fWho = toWhom; }

	protected:
		virtual Sint32 vprintf(const TProgrammer &toWhom, Sint32 indent, const char *fmt, va_list &params) const = 0;

		Sint32 fIndent;
		TProgrammer fWho;
	};

	class GSDEBUG_EXPORT TTextDumpDevice : public TDumpDevice
	{
	public:
		virtual ~TTextDumpDevice() {}
	protected:
		Sint32 vprintf(const TProgrammer &toWhom, Sint32 indent, const char *fmt, va_list &params) const;
	};

	extern TTextDumpDevice gl_stdDumpDevice;

	#define DUMPCLASS(toWhom, ptr)				(ptr)->Dump(toWhom, gl_stdDumpDevice, 0)
#else
	#define DUMPCLASS(toWhom, ptr)				DEBUG_DO_NOTHING
#endif
#define DUMPCLASSH(toWhom, hType, h)			DUMPCLASS(toWhom, *(hType)(h))
#define DUMPCLASSHANDLE(toWhom, h)				DUMPCLASS(toWhom, *(h))
#define DUMPTHISCLASS(toWhom)					DUMPCLASS(toWhom, this)

#ifdef TEST
	#define ASSERTCLASS(toWhom, ptr)			(ptr)->AssertValid(toWhom, true)
	#define VERIFYCLASS(toWhom, ptr)			( (ptr) ? ((ptr)->AssertValid(toWhom, true), true) : VerifyStop(false))
#else
	#define ASSERTCLASS(toWhom, ptr)			DEBUG_DO_NOTHING
	#define VERIFYCLASS(toWhom, ptr)			((ptr) != nil)
#endif
#define ASSERTCLASSH(toWhom, type, h)			ASSERTCLASSHANDLE(toWhom, (type)(h))
#define ASSERTCLASSHANDLE(toWhom, h)			do { if (VERIFYHANDLE(toWhom, h, 0)) ASSERTCLASS(toWhom, *(h)); } while (0)
#define ASSERTTHISCLASS(toWhom)					ASSERTCLASS(toWhom, this)
#define VERIFYCLASSH(toWhom, type, h)			VERIFYCLASSHANDLE(toWhom, (type)(h))
#define VERIFYCLASSHANDLE(toWhom, h)			(VERIFYHANDLE(toWhom, h, 0) ? VERIFYCLASS(toWhom, *(h)) : 0)
#define VERIFYTHISCLASS(toWhom)					VERIFYCLASS(toWhom, this)

#ifdef TEST
	#define DECLARE_ASSERTVALID \
			void AssertValid(const TProgrammer &toWhom, Bool8 bCheckMem) const;
	#define DECLARE_VIRTUAL_ASSERTVALID \
			virtual DECLARE_ASSERTVALID
	#define IMPLEMENT_ASSERTVALID(av_classname, av_parentclass, av_checks) \
			void av_classname::AssertValid(const TProgrammer &toWhom, Bool8 bCheckMem) const \
			{ \
				if (bCheckMem) ASSERTPOINTER(toWhom, this, sizeof(av_classname)); \
				av_parentclass::AssertValid(toWhom, false); \
				av_checks \
			}
#else
	#define DECLARE_ASSERTVALID
	#define DECLARE_VIRTUAL_ASSERTVALID
	#define IMPLEMENT_ASSERTVALID(av_classname, av_parentclass, av_checks)
#endif

#if BUG
	#define DECLARE_DUMP \
			void Dump(const TProgrammer &toWhom, TDumpDevice &dd, Sint32 indent) const;
	#define DECLARE_VIRTUAL_DUMP \
			virtual DECLARE_DUMP
	#define IMPLEMENT_DUMP(d_classname, d_parentclass, d_checks) \
			void d_classname::Dump(const TProgrammer &toWhom, TDumpDevice &dd, Sint32 indent) const \
			{ \
				if (_IsUser(toWhom)) { \
					d_parentclass::Dump(toWhom, dd, indent); \
					dd.printf(toWhom, indent, #d_classname " class:\n"); \
					++indent; \
					d_checks \
				} \
			}
#else
	#define DECLARE_DUMP
	#define DECLARE_VIRTUAL_DUMP
	#define IMPLEMENT_DUMP(d_classname, d_parentclass, d_checks)
#endif

#if 1 //!_MINICAD_EXTERNAL_
// Use the following macros to dump individual class members.
#define DUMP_BOOL(dp) \
			dd.printf(toWhom, indent, #dp " = %s (%d)\n", (dp) ? "true" : "false", (Sint32)(dp))
#define DUMP_CHAR(dp) \
			DUMP_ITEM("%c", dp)
#define DUMP_CLASS(dp) \
			do { \
				dd.printf(toWhom, indent, #dp " =\n"); \
				(dp).Dump(toWhom, dd, indent+1); \
			} while (0)
#define DUMP_CLASSHANDLE(dp) \
			do { \
				if (dp) DUMP_CLASSPTR(*dp); \
				else DUMP_NULL(dp); \
			} while (0)
#define DUMP_CLASSPTR(dp) \
			do { \
				if (dp) DUMP_CLASS(*dp); \
				else DUMP_NULL(dp); \
			} while (0)
#define DUMP_DOUBLE(dp) \
			DUMP_ITEM("%f", dp)
#define DUMP_HANDLE(dp) \
			do { \
				if (dp && *dp) dd.printf(toWhom, indent, #dp " = 0x%p, *" #dp " = 0x%p\n", dp, *dp); \
				else if (dp) dd.printf(toWhom, indent, #dp " = 0x%p, *" #dp " = NULL\n", dp); \
				else DUMP_NULL(dp); \
			} while (0)
#define DUMP_INT(dp) \
			DUMP_ITEM("%d", dp)
#define DUMP_ITEM(fmt, dp) \
			dd.printf(toWhom, indent, #dp " = " fmt "\n", dp)
#define DUMP_MSG(msg) \
			do { \
				dd.SetIndent(indent); \
				dd.SetWho(toWhom); \
				dd.printf msg; \
			} while (0)
#define DUMP_NULL(dp) \
			dd.printf(toWhom, indent, #dp " = NULL\n")
#define DUMP_PSTR(dp) \
			do { \
				if ((const unsigned char*)(dp)) dd.printf(toWhom, indent, #dp " = len:%d, \"%s\"\n", strlen(dp), TXSTRINGPRINT(dp)); \
				else DUMP_NULL(dp); \
			} while (0)
#define DUMP_PTR(dp) \
			do { \
				if (dp) DUMP_ITEM("0x%p", dp); \
				else DUMP_NULL(dp); \
			} while (0)
#define DUMP_RECT(dp) \
			dd.printf(toWhom, indent, #dp " = (%d,%d)-(%d,%d)\n", RECTPRINT(dp))
#define DUMP_STR(dp) \
			do { \
				if ((const char*)(dp)) dd.printf(toWhom, indent, #dp " = len:%d, \"%s\"\n", strlen(dp), TXSTRINGPRINT(dp)); \
				else DUMP_NULL(dp); \
			} while (0)
#endif // !_MINICAD_EXTERNAL_


#define DECLARE_SIZEOF \
	size_t SizeOf() const;
#define IMPLEMENT_SIZEOF(classname) \
	size_t classname::SizeOf() const
#define DECLIMP_SIZEOF(classname) \
	size_t SizeOf() const	{ return sizeof(classname); }


#else

#define DECLARE_ASSERTVALID
#define DECLARE_VIRTUAL_ASSERTVALID
#define IMPLEMENT_ASSERTVALID(av_classname, av_parentclass, av_checks)

#define DECLARE_DUMP
#define DECLARE_VIRTUAL_DUMP
#define IMPLEMENT_DUMP(d_classname, d_parentclass, d_checks)


#endif // GS_USE_CLASS_DEBUGGING


#define DECLARE_CLASS_DEBUGGING \
			DECLARE_ASSERTVALID \
			DECLARE_DUMP

#define DECLARE_VIRTUAL_CLASS_DEBUGGING \
			DECLARE_VIRTUAL_ASSERTVALID \
			DECLARE_VIRTUAL_DUMP

//---------------------------------------------------------------------------------------
class GSDEBUG_EXPORT TDebugObject
// This object is not allowed to have ANY member variables.  sizeof(TDebugObject) == 0
{
	public:
		#if TEST
			void AssertValid(const TProgrammer &toWhom, Bool8 bCheckMem) const;
		#endif
		DECLARE_DUMP
};

//---------------------------------------------------------------------------------------
class GSDEBUG_EXPORT TVirtualDebugObject
{
	public:
		virtual ~TVirtualDebugObject() {}
		DECLARE_VIRTUAL_CLASS_DEBUGGING
};


#if _WINDOWS
////////////////////////////////////////////////////////////////////////////////
// Use the following class to get the message for GetLastError() return code.
// Created by Lewis Kapell on 10/30/98.

class GSDEBUG_EXPORT TWinErrorCode
{
	public:
		TWinErrorCode();
		~TWinErrorCode();

		operator const char *() const		{ return (const char *)fMessageBuffer; }

	private:
		void *fMessageBuffer;
};
#endif	// _WINDOWS


///////////////////////////////////////////////////////////////////////////////
#if _WINDOWS && TEST

	Sint32 GSDEBUG_EXPORT _AssertValidFilePath(Bool8 isAssert, const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, const char* fullPath);

	#define ASSERTPATH(who, fullPath) \
			do { \
				if (::_AssertValidFilePath(true, who, THIS_FILE, __LINE__, #fullPath, fullPath)) STOP(); \
			} while (0)

	#define VERIFYPATH(who, fullPath) \
				::_AssertValidFilePath(false, who, THIS_FILE, __LINE__, #fullPath, fullPath)

#else

	#define ASSERTPATH(who, fullPath)				DEBUG_DO_NOTHING
	#define VERIFYPATH(who, fullPath)				((BOOL)( (fullPath) != 0 ))

#endif // _MAGICFOLDER_ && TEST


// Put anything in this block which should not be defined in the final version,
// but is defined in the bug version & test version.

#if !defined(TEST)
	// These macros do nothing in release code.

	#if !defined(_MINICAD_EXTERNAL_)
		#define DEBUG_INIT(appName, flags)				DEBUG_DO_NOTHING
		#define DEBUG_SETEXE(hInst)						DEBUG_DO_NOTHING
		#define DEBUG_TERMINATE()						DEBUG_DO_NOTHING
		#define DEBUG_SETPARENTWINDOW(h)				DEBUG_DO_NOTHING
	#endif

	#define ASSERTN(toWhom, goodval)					DEBUG_DO_NOTHING
	#define ASSERTSTRING(toWhom, psz, min, max)			DEBUG_DO_NOTHING
	#define ASSERTPOINTER(toWhom, h, bytes)				DEBUG_DO_NOTHING
	#define ASSERTPOINTER_READONLY(toWhom, h, bytes)	DEBUG_DO_NOTHING

	#define ASSERTLOCKED(toWhom, h)						DEBUG_DO_NOTHING
	#define ASSERTUNLOCKED(toWhom, h)					DEBUG_DO_NOTHING
	#define ASSERTHANDLE(toWhom, ptr, bytes)			DEBUG_DO_NOTHING
	#define ASSERTMENUHANDLE(toWhom, menu)				DEBUG_DO_NOTHING
	#define ASSERTNOTVOLATILE(toWhom, p)				DEBUG_DO_NOTHING
	#define ASSERTHEAP(who)								DEBUG_DO_NOTHING

	#define ASSERTPSTRING(toWhom, ps, min, max)			DEBUG_DO_NOTHING

	#define ONUSER(user, func)							DEBUG_DO_NOTHING
	#define DSTOP(params)								DEBUG_DO_NOTHING
	#define DMSGIF(condition, params) 					DEBUG_DO_NOTHING
	#define DSTOPIF(condition, params) 					DEBUG_DO_NOTHING
	#define DSTOPIF(condition, params) 					DEBUG_DO_NOTHING

//	#define ASSERTNOFPEXCEPTION()						DEBUG_DO_NOTHING

	#if GS_HWND_CHECK
		#define ASSERTHWND(toWho, hWnd)					DEBUG_DO_NOTHING
		#define ASSERTHDC(toWhom, hdc)					DEBUG_DO_NOTHING
	#endif


	// These macros still do something in release code.
	#define INLINE										inline
	#define VERIFYSTRING(toWhom, psz, min, max)			((Bool8)( (psz) != 0 ))
	#define VERIFYN(toWhom, exp)						((Bool8)( (exp) ? true : false ))
	#define VERIFYMSG(toWhom, exp, failMsg, ...)		((Bool8)( (exp) ? true : false ))
	#define VERIFYPOINTER(toWhom, ptr, bytes)			((Bool8)( (ptr) != 0 ))
	#define VERIFYPOINTER_READONLY(toWhom, ptr, bytes)	((Bool8)( (ptr) != 0 ))
	#define VERIFYHANDLE(toWhom, h, bytes)				((Bool8)( (h) != 0 ))
	#define VERIFYPSTRING(toWhom, ps, min, max)			((Bool8)( (ps) != 0 ))

	#if GS_HWND_CHECK
		#define VERIFYHDC(toWhom, hdc)					((Bool8)( (hdc) != NULL ))
		#define VERIFYHWND(toWhom, hwnd)				((Bool8)( (hwnd) != NULL ))
	#endif
	
#endif	// !TEST

// Put anything in this block which should not be defined in the test version,
// or the final version, but is defined in the bug version

#if !defined(BUG)
	#define DMSG(params)	DEBUG_DO_NOTHING

	inline void LIMITMESSAGES(const TProgrammer &)							{}
	inline void LIMITMESSAGES(const EDebugLevel &)							{}
	inline void LIMITMESSAGES(const TProgrammer &, const EDebugLevel &)		{}
	inline void LIMITMESSAGES(const EDebugLevel &, const TProgrammer &)		{}
	inline void LIMITMESSAGES()												{}

#endif	// !BUG

// Common expression shorthand
#define for_i(size) for( size_t i=0; i<size; i++ )
#define for_j(size) for( size_t j=0; j<size; j++ )
#define for_k(size) for( size_t k=0; k<size; k++ )
#define for_m(size) for( size_t m=0; m<size; m++ )

#define for_it( container ) for( auto it = (container).begin(); it != (container).end(); ++it ) 
#define for_jt( container ) for( auto jt = (container).begin(); jt != (container).end(); ++jt ) 
#define for_kt( container ) for( auto kt = (container).begin(); kt != (container).end(); ++kt ) 
#define for_mt( container ) for( auto mt = (container).begin(); mt != (container).end(); ++mt ) 

// TDebugFile is used to aid in debugging.  The possibilities are endless...
// Example
// original code:
//	void f(int i) 
//	{
//		if( g() ) 
//			DoStuff(i);
//	}
//
// debugging enhanced code:
//  void f() 
//	{
//		if( TDebugFile::GetBool("AlwaysCallDoStuff") )
//			DoStuff( (TDebugFile::GetBool("use_i") ? i : TDebugFile::GetInt("i"));
//		else if( g() )
//			DoStuff(i);
//	}
//
// with /a/debug.txt having the following contents:
//	AlwaysCallDoStuff = true
//	use_i = true
//	i = 4
//
class TDebugFile
{
public:

	TDebugFile()
	{
	}

	static std::string GetString(const std::string & inKey)
	{
		TDebugFile & db = GetInstance();

		db.Reload();
		return db.fData[inKey];
	}

	static int GetInt(const std::string & inKey)
	{
		TDebugFile & db = GetInstance();

		db.Reload();
		try
		{
			auto it = db.fData.find(inKey);
			if( it != db.fData.end() )
				return std::stoi(it->second);
		}
		catch( ... )
		{
		}

		return 0;
	}

	static float GetFloat(const std::string & inKey)
	{
		TDebugFile & db = GetInstance();

		db.Reload();
		try
		{
			auto it = db.fData.find(inKey);
			if( it != db.fData.end() )
				return std::stof(it->second);
		}
		catch( ... )
		{
		}

		return 0.0f;
	}

	static double GetDouble(const std::string & inKey)
	{
		TDebugFile & db = GetInstance();

		db.Reload();
		try 
		{
			auto it = db.fData.find(inKey);
			if( it != db.fData.end() )
				return std::stod(it->second);
		} 
		catch( ... )
		{
		}

		return 0.0;
	}

	static bool GetBool(const std::string & inKey)
	{
		TDebugFile & db = GetInstance();

		db.Reload();
		
		try 
		{
#if _WINDOWS
#pragma warning(disable:4996)  //  stricmp deprecated
#endif
			auto it = db.fData.find(inKey);
			if( it != db.fData.end() )
			{
				if( stricmp(it->second.c_str(), "true") == 0 )
					return true;
				else if( stricmp(it->second.c_str(), "false") == 0 )
					return false;
			}
			return false;

		}
		catch( ... )
		{
		}

		return false;

	}
	
	static std::ostream & GetOutputStream()
	{
		std::ofstream & outStream = GetInstance().fOutputStream;

		if( !outStream.is_open() )
			outStream.open("c:\\a\\debugOutput.txt");
		else
			outStream.flush();

		return outStream;
	}

private:

	void Reload()
	{
		static bool first = true;
		static auto lastTick = std::chrono::high_resolution_clock::now();
		auto tick = std::chrono::high_resolution_clock::now();

		if( first || std::chrono::duration_cast<std::chrono::milliseconds>(tick-lastTick).count() > 1000 )  // reload every 1 second
		{
			first = false;
			lastTick = tick;

#if _WINDOWS
			std::ifstream dbgFile("c:\\a\\debug.txt");
#else
			std::ifstream dbgFile("/a/debug.txt");
#endif
			if( dbgFile.is_open() )
			{
				fData.clear();

				dbgFile.seekg(0, std::ios::end);
				size_t size = size_t(dbgFile.tellg());
				dbgFile.seekg(0, std::ios::beg);

				std::string contents;
				contents.resize(size+1);
				dbgFile.read(&contents[0], size);
				contents[size] = 0;

				dbgFile.close();

				size_t offset = 0;

#define CheckEOF(index) if( index >= contents.size() ) break

				while( offset < contents.size() )
				{
					std::string key;
					std::string value;


					offset = contents.find_first_not_of(" \t\n\r", offset);
					CheckEOF(offset);

					size_t endOffset = offset;

					if( contents[offset] == '"' )
						endOffset = contents.find_first_of("\"", ++offset);
					else
						endOffset = contents.find_first_of(" \t\n\r=", offset);

					if( offset == endOffset )
						endOffset++;
					CheckEOF(endOffset);

					key = contents.substr(offset, endOffset-offset);
					offset = endOffset;

					offset = contents.find_first_of("=", offset);
					offset++;
					CheckEOF(offset);

					offset = contents.find_first_not_of(" \t\n\r", offset);
					CheckEOF(offset);


					endOffset = offset;

					if( contents[endOffset] == '"' )
						endOffset = contents.find_first_of("\"", ++offset);					
					else
						endOffset = contents.find_first_of(" \t\n\r", endOffset);

					CheckEOF(endOffset);

					value = contents.substr(offset, endOffset-offset);
					fData[key] = value;

					offset = endOffset;

					offset = contents.find_first_of("\n\r", offset);
					offset++;
					CheckEOF(endOffset);
					
#undef CheckEOF
				}
			}
		}
	}

	// The one and only
	static TDebugFile & GetInstance()
	{
		static TDebugFile gDebugFile;
		return gDebugFile;
	}

	std::map<std::string, std::string> fData;  // key-value table of data read from disk
	std::ofstream fOutputStream;

};


#endif  // __cplusplus

#endif // _GSDEBUG_H_
