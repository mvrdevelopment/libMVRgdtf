//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#if defined(GS_MAC) || defined(DEV_BLD) || defined(_DEBUG_FAST) // Added to create bogus release version of GSDebug lib. [VML 01/09/04]
#if _MINICAD_
	#include "Kernel/SharedDefines.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-SYSTEM INCLUDE FILE.  [DMB, 4/10/96]
#else
	#include "Kernel/CoreDefines.h"	// DO NOT MOVE THIS LINE FROM BEING THE FIRST NON-SYSTEM INCLUDE FILE.  [DMB, 4/10/96]
#endif

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#if _WINDOWS
	#include <Windows.h>
	#include <Float.h>
#else
    #include <inttypes.h>
#endif

#if _WINDOWS
	
	#include "Kernel/QTHeader.h"
	
	#if !_GSDEBUG_DLL_
//		#include <UndoName.h>
	#endif
#endif

#if _WINDOWS
	#include "Kernel/GSIntTypes.h"
#endif

#include "Kernel/GSDebug.h"

#include "Kernel/MiniCadHookIntf.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////


#if TEST
	#if !_MINICAD_EXTERNAL_ && !_GSESDK_ && !_GSWINSDK_
		#if _WINDOWS
			#if BUG && !_GSDEBUG_DLL_
				#define	_CRTDBG_MAP_ALLOC 1
				#include <crtdbg.h>
			#endif
		#else
			#define DEBUG_NEW	DEBUG_NEW_OFF
		#endif
	#endif

	#if _MINICAD_EXTERNAL_ || _GSESDK_
		#include "Kernel/MiniCadCallBacks.h"
	#endif
#endif // TEST
#include "Kernel/GSLogging.h"
#include "Interfaces/VectorWorks/Debug/IDebugSupport.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#if TEST

#ifndef WIN_ONLY
	#if _WINDOWS
		#define WIN_ONLY(x)  x
	#else
		#define WIN_ONLY(x)
	#endif
#endif

const size_t kBuf_size = 1024;

char gDebugAppName[32] = "";

#if BUG
	// Set by GS_DebugInit( ).
	static Uint32 gDebugFlags = GSDebug::kNoFlags;
#endif


/////////////////////////////////////////////////////////////////////////////////////////

#if _WINDOWS

// Instance handle of the application using GSDebug. Set by GS_DebugSetExeHandle().
extern "C" HINSTANCE gExeInstance = NULL;

void GDB_DebugSetExeHandle(HINSTANCE hInst)
{
	// Set the global handle to the calling application.
	gExeInstance = hInst;
}

#endif //_WINDOWS

/////////////////////////////////////////////////////////////////////////////////////////

#if _WINDOWS

// The window to use as the parent of the next debug dialog.
static HWND g_hParentWnd = NULL;

void GDB_SetDebugMessageParentWindow(HWND hParentWnd)
{
	g_hParentWnd = hParentWnd;
}

#endif

/////////////////////////////////////////////////////////////////////////////////////////

static bool GSDebugRunningMacOSX(void)
{
#if GS_MAC
	return true;
#else
	return false;
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////

DECLAREWHO(gProgrammerFilter, "Default Filter");
TProgrammer registrationGlobalValue = kEveryoneUsedForRegistration;

TProgrammer TProgrammer::operator &(const TProgrammer& a) const
{
	TProgrammer dest(*this);

	// Combine ID's
	dest.fID2 |= a.fID2;
	dest.fID1 |= a.fID1;


	// we don't want to combine names because that steps on the assert categories
	// passed to the debug server. We may find a better way to do this later, but
	// for now, the first programmer on the list is the primary programmer


	// the alternative here is to filter the special modifier bits in both the constructor
	// and in this code, but I'll leave that for later - PCP

	// Combine names.
	//strcat(strcat(dest.fName, " & "), a.fName);

	// Combine sending.
	if (a.fSendOnOwn) dest.fSendOnOwn = true;

	return dest;
}

bool TProgrammer::LogOnOwn() const
{
	return (_IsUser(*this) ? fSendOnOwn : true);
}

bool TProgrammer::ContainsCurrentUser() const
{
#if _MINICAD_EXTERNAL_ || _GSESDK_
	return true;
#else
	if (IsEveryone())
		return true;	// Save some time.  This will be a common occurance.

	for (Sint32 i = 0; i < fMaxProgrammers; ++i) {
		if (fRegistered[i].fID1 == 0 && fRegistered[i].fID2 == 0)
			break;	// we've reached the end of the set registered array, shortcut out.
		if (_IsUser(fRegistered[i].fName)) {
			if (IsIn(fRegistered[i].fID2, fRegistered[i].fID1))
				return true;
			break;
		}
	}
	return false;
#endif
}

const Sint32 TProgrammer::fMaxProgrammers = 120;
TProgrammer::TRegistered TProgrammer::fRegistered[fMaxProgrammers];

Uint64 GetID(int index);	// A way to iterate through the indices of ID's


bool TProgrammer::IsIn(Uint64 id2, Uint64 id1) const
{
	id2 &= kEveryoneConst; // strip off any extra bits

	Uint64 thisID2 = GetID2(true); // this strips off extra bits from this value
	Uint64 thisID1 = GetID1();

	bool result = (thisID2 & id2) == thisID2 && (thisID1 & id1) == thisID1;

	return result;
}


void TProgrammer::Register(const char *name, Uint64 id2, Uint64 id1)
{
	id2 &= kEveryoneConst;
	if (id2 != kEveryoneConst) {
		// Find available slot.
		Sint32 i;
		for (i=0; i<fMaxProgrammers; ++i) 
		{
			if ((fRegistered[i].fID2 & id2) == id2 && (fRegistered[i].fID1 & id1) == id1)
			{
					return; // reject multiples
			}
			if (fRegistered[i].fID2 == 0 && fRegistered[i].fID1 == 0) break;
		}
		// Fill it in.
		if (i<fMaxProgrammers) 
		{
			fRegistered[i].fID2 = id2;
			fRegistered[i].fID1 = id1;
			strcpy(fRegistered[i].fName, name);
		}
	}
}

bool TProgrammer::GetProgrammerName(Uint64 id2, Uint64 id1, char *name)
{
	for (Sint32 i=0; i<fMaxProgrammers; ++i) {
		if (fRegistered[i].fID2 == id2 && fRegistered[i].fID1 == id1) {
			strcpy(name, fRegistered[i].fName);
			return true;
		}
	}
	return false;
}

bool TProgrammer::ExtractProgrammer(TProgrammer &who, TProgrammer &one)
{
	Uint64 id=1;
	if (who.fID1 != 0 || who.fID2 != 0) // Make sure we actually have something to search for.
	{
		for (Uint32 i=0; i<fMaxProgrammers; ++i, id*=2) {
			if ((who.fID2 == 0  || who.fID2 & fRegistered[i].fID2) && (who.fID1 == 0 || who.fID1 & fRegistered[i].fID1)) {
				one.Set(fRegistered[i].fName, fRegistered[i].fID2, fRegistered[i].fID1,  who.fSendOnOwn);
				who.fID2 &= ~fRegistered[i].fID2;
				who.fID1 &= ~fRegistered[i].fID1;
				return true;
			}
		}
	}
	return false;
}


/////////////////////////////////////////////////////////////////////////////////////////
// We use this to cause paint messages not to be dispatched by the MessageBox we create

#if _WINDOWS

static bool gl_InDebugMessageBox = false;

extern "C" Bool8 GSDebug_IsInDebugMessage()
// This function must return 'Bool8' becuase it is used by C modules which to not
// support the 'bool' datatype.
{
	return gl_InDebugMessageBox ? kTrue : kFalse;
}

#endif // _WINDOWS

/////////////////////////////////////////////////////////////////////////////////////////
// DebugLevel( )

/*

// when do my DMSG statements print?
//   left column id the level of various DMSG calls
//   top row is the global debug level (can be set in the debug dialog (command-'))
//
// NOTE - when the global state is set to dlNever, you should get NO debug output
//        except for ASSERT and DSTOP

                 gDebugLevel     dlAlways   brief   verbose   mongo   dlNever
DMSG level

dlAlways                            Y         Y         Y       Y        N
brief                               N         Y         Y       Y        N
verbose                             N         N         Y       Y        N
mongo                               N         N         N       Y        N
dlNever                             N         N         N       N        N

*/

//---------------------------------------------------------------------------------------
static EDebugLevel gDebugLevel = brief;

//---------------------------------------------------------------------------------------
EDebugLevel GSDebug::DebugLevel()
// Returns the current debug level setting.
{
	return gDebugLevel;
}

//---------------------------------------------------------------------------------------
#if BUG && !_MINICAD_EXTERNAL_ && !_GSESDK_
static bool AllowDebugPrinting(EDebugLevel messageLevel)
// Returns whether messages with messageLevel should be printed.
// not in the namespace because it should only be used in the implementation of debugging code
{
	// this has changed behavior slightly to allow messages to be
	// completely turned off. If gDebugLevel is dlAlways, brief, verbose,
	// or mongo, then we will print messages as their permissions allow.
	// If gDebugLevel is dlNever, that guarantees that no messages get printed.
	return (gDebugLevel >= messageLevel) && gDebugLevel != dlNever;
}
#endif

//---------------------------------------------------------------------------------------
EDebugLevel GSDebug::DebugLevel(EDebugLevel newDebuglevel)
// Change the current debug level setting. Returns the previous debug level.
{
	const EDebugLevel savedDebugLevel = gDebugLevel;
	gDebugLevel = newDebuglevel;
	return savedDebugLevel;
}


/////////////////////////////////////////////////////////////////////////////////////////
// WantToDebug( )

//---------------------------------------------------------------------------------------
static bool gWantToDebug = true;

//---------------------------------------------------------------------------------------
bool GSDebug::WantToDebug()
// Returns the current WantToDebug setting.
{
	return gWantToDebug;
}

//---------------------------------------------------------------------------------------
bool GSDebug::WantToDebug(bool bWantToDebug)
// Change the current WantToDebug setting. Returns the previous setting.
{
	const bool savedWantToDebug = gWantToDebug;
	gWantToDebug = bWantToDebug;
	return savedWantToDebug;
}


/////////////////////////////////////////////////////////////////////////////////////////
// UseSourceDebugger

//---------------------------------------------------------------------------------------
static bool gUseSourceDebugger = true;

//---------------------------------------------------------------------------------------
bool GSDebug::UseSourceDebugger()
// Returns the current UseSourceDebugger setting.
{
	return gUseSourceDebugger;
}

//---------------------------------------------------------------------------------------
bool GSDebug::UseSourceDebugger(bool bUseSourceDebugger)
// Change the current UseSourceDebugger setting. Returns the previous setting.
{
	const bool savedUseSourceDebugger = gUseSourceDebugger;
	gUseSourceDebugger = bUseSourceDebugger;
	return savedUseSourceDebugger;
}


/////////////////////////////////////////////////////////////////////////////////////////
// WantToBreak

//---------------------------------------------------------------------------------------
static bool gWantToBreak = true;

//---------------------------------------------------------------------------------------
bool GSDebug::WantToBreak()
// Returns the current WantToBreak setting.
{
	return gWantToBreak;
}

//---------------------------------------------------------------------------------------
bool GSDebug::WantToBreak(bool bWantToBreak)
// Change the current WantToBreak setting. Returns the previous setting.
{
	const bool savedWantToBreak = gWantToBreak;
	gWantToBreak = bWantToBreak;
	return savedWantToBreak;
}


/////////////////////////////////////////////////////////////////////////////////////////
// DrawToScreen

//---------------------------------------------------------------------------------------
static bool gDrawToScreen = false;

//---------------------------------------------------------------------------------------
bool GSDebug::DrawToScreen()
// Returns the current DrawToScreen setting.
{
	return gDrawToScreen;
}

//---------------------------------------------------------------------------------------
bool GSDebug::DrawToScreen(bool bDrawToScreen)
// Change the current DrawToScreen setting. Returns the previous setting.
{
	const bool savedDrawToScreen = gDrawToScreen;
	gDrawToScreen = bDrawToScreen;
	return savedDrawToScreen;
}

//---------------------------------------------------------------------------------------

Uint32 GSDebug::Flags()
{
	return gDebugFlags;
}

//---------------------------------------------------------------------------------------

Uint32 GSDebug::Flags(Uint32 inNewFlags)
{
	gDebugFlags = inNewFlags;
	return gDebugFlags;
}


/////////////////////////////////////////////////////////////////////////////////////////
// DSTOP variables
std::atomic_flag gDSTOPLock = ATOMIC_FLAG_INIT;

//---------------------------------------------------------------------------------------
static ConstGSCStrPtr gDStopFileName = NULL;
static Sint32 gDStopLineNumber = -1;

//---------------------------------------------------------------------------------------
void GSDEBUG_EXPORT GSDebug::SetDStopFileName(ConstGSCStrPtr szFileName)
{
	gDStopFileName = szFileName;
}

//---------------------------------------------------------------------------------------
void GSDEBUG_EXPORT GSDebug::SetDStopLineNumber(Sint32 nLineNumber)
{
	gDStopLineNumber = nLineNumber;
}

#if _WINDOWS
/////////////////////////////////////////////////////////////////////////////////////////
static bool IsWindowsNT()
{
	OSVERSIONINFO os;
	os.dwOSVersionInfoSize = sizeof(os);
	GetVersionEx(&os);
	return os.dwPlatformId == VER_PLATFORM_WIN32_NT;
}
#endif

/////////////////////////////////////////////////////////////////////////////////////////


class OutputMessage {

	public:
		OutputMessage(bool sendToFile)
		{
		#if Paul | Jeff | AutoBuild
			if (sendToFile) {
				#if GS_WIN

				// get the path of the application and append the name of the debug output file
				wchar_t szDebugPath[MAX_PATH];
				GetModuleFileName(NULL, szDebugPath, MAX_PATH);

				size_t length = wcslen(szDebugPath);

				for (size_t i = length; i > 0; i--) {
					if (szDebugPath[i] == L'\\') {
						szDebugPath[i+1] = 0;
						break;
					}
				}

				wcscat(szDebugPath, L"VW debug output.txt");

				theFile = _wfopen(szDebugPath, L"a+");

				#else
					theFile = fopen("VW debug output.txt", "a+");
				#endif
			}
			else
				theFile = nil;
		#else
			sendToFile;
			theFile = nil;
		#endif
		}

		~OutputMessage()
		{
			if(theFile)
				fclose(theFile);
		}


		void SendString(const char* s)
		{
			// this first section sends the string to the debug window of the IDE
		#if GS_MAC
			fprintf(stderr, "%s", s);
		#elif GS_LIN
			fprintf(stderr, "%s", s);
		#else
			OutputDebugStringA(s);
		#endif


			// next we send it to the debug output file
			if(theFile)
				fprintf(theFile, "%s", s);
		}

	private:
		FILE* theFile;
};

/////////////////////////////////////////////////////////////////////////////////////////

bool __ShowAlertDialog(const char* szMsgText, const char* szFile = NULL, Sint32 line = 0)
{
	using namespace VectorWorks::Debug;

	if ( szFile == NULL )	szFile	= gDStopFileName;
	if ( line == 0 )		line	= gDStopLineNumber;

	VCOMPtr<IDebugSupport> pDebugTools( IID_DebugSupport );

	bool	bDoBreak	= false;
	if ( pDebugTools == NULL ) {
		bDoBreak	= true;
	}
	else {
		pDebugTools->ShouldBreak( szFile, line, bDoBreak );

		if ( bDoBreak ) {
			static char	fileText[ kBuf_size ];
			size_t	len		= sprintf( fileText, "%s(%d)", szFile, line );
			DSTOPIF(len>kBuf_size, (kEveryone, "MAYDAY!!!  Your assertion message is too big. IT IS CORRUPTING THE DATA SEGMENT."));

			short dlgRes	= 1;
			pDebugTools->ShowAlertDialog(
				szMsgText,
				fileText,
				0,
				"Break",
				"Close",
				"Never Show This",
				"Stop All Asserts",
				dlgRes );

			if ( dlgRes == 0 ) {
				// Close
				bDoBreak	= false;
			}
			else if ( dlgRes == 1 ) {
				// Break
				bDoBreak	= true;
			}
			else if ( dlgRes == 2 ) {
				// Abort or Never Show This
				bDoBreak	= false;
				pDebugTools->StopBreaks( szFile, line );
			}
			else if ( dlgRes == 3 ) {
				// Options
				/*bDoBreak	= false;
				pDebugTools->ShowOptionsDialog();

				bool bWantToBreak	= true;
				pDebugTools->GetStopAtBreaks( bWantToBreak );
				GSDebug::WantToBreak( bWantToBreak );*/
				pDebugTools->SetStopAtBreaks( false );
				GSDebug::WantToBreak( false );
			}
		}
	}
	return bDoBreak;
}

#if _WINDOWS
#define snprintf _snprintf
#endif

/////////////////////////////////////////////////////////////////////////////////////////

static Bool8 DoDebugMessage(const char* szFuncName, const TProgrammer &who, EDebugLevel level, Bool8 bFile, Bool8 bToDebugger, va_list &ap, const char *szFmt)
{
	Bool8 bStopOnReturn = false;

	// Change bFile and bToDebugger if they are true (DSTOP) and the flag to NOT use debug windows is set.
	//	Avoids crash on quit.
	if (bFile && bToDebugger && (gDebugFlags & GSDebug::kNeverUseDebugWindows)) {
#if NETBUG
		bFile = false;
#endif
		bToDebugger = false;
	}

	if (!who.IsActLikeRelease()) {

		#if _MINICAD_EXTERNAL_ || _GSESDK_
			level;
			Bool8 doStop = true;
		#elif defined(BUG)
			Bool8 doStop = GSDebug::WantToBreak();
		#else
			Bool8 doStop = false;
		#endif


		#if BUG && !_MINICAD_EXTERNAL_ && !_GSESDK_
		if (AllowDebugPrinting(level))
		#endif
		{
			// Determine if the message should be displayed or not.
			bool bDoTheMessage = false;
			if (bToDebugger) {
				// It's something like a DSTOP.
				if (who.IsOnlyIfActiveUserBitSet())
					bDoTheMessage = _IsUser(who);
				else
					bDoTheMessage = true;
			}
			else {
				// It's something like a DMSG.
				bDoTheMessage = _IsUser(who);
			}

			if (bDoTheMessage) {

				char szMsg[kBuf_size];
				if ( szFmt ) {
					VERIFYN(kDave, vsnprintf(szMsg, kBuf_size, szFmt, ap) < kBuf_size);
				}
				else {
					szMsg[0]	= 0;	// no string
				}
				va_end(ap);

				#if NETBUG
				// Send message to server in network debugging.
					if (bFile) {						// Check if message is destined for the server.
					#if !_MINICAD_EXTERNAL_ && !_GSESDK_
						if (bToDebugger && gDStopLineNumber > 0) {
							char msg2[kBuf_size + 128];
							sprintf(msg2, "DSTOP: File %s, Line %d\n  %s", gDStopFileName, gDStopLineNumber, szMsg);
							RemoteDebug(who, msg2);
						}
						else
					#endif
							RemoteDebug(who, szMsg);
					}
				#endif
				#if _WINDOWS && !_GSDEBUG_DLL_ && !_GSESDK_
					if (!bFile && bToDebugger && doStop && IsWindowsNT()) {
						Beep(1500, 20);
					}
				#endif

				#ifdef BUG
				// Send message to user.


					OutputMessage out(true);

					if (bToDebugger) {
						// Add a new-line character if not supplied one.
						if (szMsg[strlen(szMsg)-1] != '\n')
							strcat(szMsg, "\n");

						out.SendString("DEBUGSTOP DSTOP");

						// Output who the message is from.
						if (!who.IsEveryone()) {
							out.SendString("(");
							out.SendString((char *)who.GetName());
							out.SendString(")");
						}
						out.SendString(": ");
					}

					// Output the message.
					out.SendString(szMsg);

					if (bToDebugger && doStop && who.ShouldBreak()) {
						static char szMessage1[] = "%s: %s: %s";
						static char szMessage2[] = "%s: %s";
						static char szMessage3[] = "%s";
						static char szMessage4[] = "Unknown STOP";

						static char szAlertText[kBuf_size];
						Sint32			len;
						if ( who != NULL && (szFuncName && szFuncName[0]) && szMsg != NULL )
							len = snprintf(szAlertText, kBuf_size, (const char*) szMessage1, (const char*) who, szFuncName, szMsg);
						else if ( who != NULL && szMsg != NULL )
							len = snprintf(szAlertText, kBuf_size, (const char*) szMessage2, (const char*) who, szMsg );
						else if ( who != NULL && (szFuncName && szFuncName[0]) )
							len = snprintf(szAlertText, kBuf_size, (const char*) szMessage2, (const char*) who, szFuncName );
						else if ( (szFuncName && szFuncName[0]) && (szMsg != NULL) )
							len = snprintf(szAlertText, kBuf_size, (const char*) szMessage2, szFuncName, szMsg );
						else if ( szMsg != NULL )
							len = snprintf(szAlertText, kBuf_size, (const char*) szMessage3, szMsg );
						else
							len = snprintf(szAlertText, kBuf_size, "%s", (const char*) szMessage4 );
						DSTOPIF(len>kBuf_size, (who, "MAYDAY!!!  Your assertion message is too big. IT IS CORRUPTING THE DATA SEGMENT."));

						bStopOnReturn = __ShowAlertDialog( szAlertText, gDStopFileName, gDStopLineNumber );
					}
				#endif
			}
		}
	}

	return bStopOnReturn;
}

inline static Bool8 DoDebugMessage(const char *szFuncName, EDebugLevel level, Bool8 bFile, Bool8 bToDebugger, va_list &ap, const char *szFmt)
{ return DoDebugMessage(szFuncName, kEveryone, level, bFile, bToDebugger, ap, szFmt); }

inline static Bool8 DoDebugMessage(const char *szFuncName, const TProgrammer &who, Bool8 bFile, Bool8 bToDebugger, va_list &ap, const char *szFmt)
{ return DoDebugMessage(szFuncName, who, dlAlways, bFile, bToDebugger, ap, szFmt); }

inline static Bool8 DoDebugMessage(const char *szFuncName, Bool8 bFile, Bool8 bToDebugger, va_list &ap, const char *szFmt)
{ return DoDebugMessage(szFuncName, kEveryone, dlAlways, bFile, bToDebugger, ap, szFmt); }

static const char *const DebugMsgNames[] = {"DMSG", "DMSG w/IF", "DSTOP", "DSTOP w/IF"};

#if !_MAGICFOLDER_
// These functions do not require a TProgrammer parameter.

#if BUG && __EXTERNDEFINES__
void GSDEBUG_EXPORT __DebugMessage(EDebugLevel level, const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(Bool8 exp, EDebugLevel level, const char *szFmt, ...);
void GSDEBUG_EXPORT __DebugMessage(Bool8 exp, const char *szFmt, ...);
#endif

void __DebugMessage(EDebugLevel level, const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	DoDebugMessage(DebugMsgNames[0], level, false, false, ap, szFmt);
}

void __DebugMessage(const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	DoDebugMessage(DebugMsgNames[0], false, false, ap, szFmt);
}

#if 0
void __DebugMessage(Bool8 exp, EDebugLevel level, const char *szFmt, ...)
{
	if (exp) {
		va_list ap;
		va_start(ap, szFmt);
		DoDebugMessage(DebugMsgNames[1], level, false, false, ap, szFmt);
	}
}

void __DebugMessage(Bool8 exp, const char *szFmt, ...)
{
	if (exp) {
		va_list ap;
		va_start(ap, szFmt);
		DoDebugMessage(DebugMsgNames[1], false, false, ap, szFmt);
	}
}
#endif

#endif // !_MAGICFOLDER_

void __DebugMessage(const TProgrammer &toWhom, EDebugLevel level, const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	DoDebugMessage(DebugMsgNames[0], toWhom, level, false, false, ap, szFmt);
}

void __DebugMessage(EDebugLevel level, const TProgrammer& toWhom, const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	DoDebugMessage(DebugMsgNames[0], toWhom, level, false, false, ap, szFmt);
}

void __DebugMessage(const TProgrammer &toWhom, const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	DoDebugMessage(DebugMsgNames[0], toWhom, false, false, ap, szFmt);
}

#if 0
void __DebugMessage(Bool8 exp, const TProgrammer& toWhom, EDebugLevel level, const char *szFmt, ...)
{
	if (exp) {
		va_list ap;
		va_start(ap, szFmt);
		DoDebugMessage(DebugMsgNames[1], toWhom, level, false, false, ap, szFmt);
	}
}

void __DebugMessage(Bool8 exp, EDebugLevel level, const TProgrammer& toWhom, const char *szFmt, ...)
{
	if (exp) {
		va_list ap;
		va_start(ap, szFmt);
		DoDebugMessage(DebugMsgNames[1], toWhom, level, false, false, ap, szFmt);
	}
}

void __DebugMessage(Bool8 exp, const TProgrammer& toWhom, const char *szFmt, ...)
{
	if (exp) {
		va_list ap;
		va_start(ap, szFmt);
		DoDebugMessage(DebugMsgNames[1], toWhom, false, false, ap, szFmt);
	}
}
#endif

Bool8 __DebugMessageStop(const TProgrammer& toWhom, EDebugLevel level, const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[2], toWhom, level, true, true, ap, szFmt);
}

Bool8 __DebugMessageStop(EDebugLevel level, const TProgrammer& toWhom, const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[2], toWhom, level, true, true, ap, szFmt);
}

Bool8 __DebugMessageStop(EDebugLevel level, const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[2], level, true, true, ap, szFmt);
}

Bool8 __DebugMessageStop(const TProgrammer& toWhom, const char *szFmt, ...)
{
	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[2], toWhom, true, true, ap, szFmt);
}

#if 0
Bool8 __DebugMessageStop(Bool8 exp, const TProgrammer& toWhom, EDebugLevel level, const char *szFmt, ...)
{
	if (!exp) return false;

	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[3], toWhom, level, true, true, ap, szFmt);
}

Bool8 __DebugMessageStop(Bool8 exp, EDebugLevel level, const TProgrammer& toWhom, const char *szFmt, ...)
{
	if (!exp) return false;

	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[3], toWhom, level, true, true, ap, szFmt);
}

Bool8 __DebugMessageStop(Bool8 exp, EDebugLevel level, const char *szFmt, ...)
{
	if (!exp) return false;

	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[3], level, true, true, ap, szFmt);
}

Bool8 __DebugMessageStop(Bool8 exp, const TProgrammer& toWhom, const char *szFmt, ...)
{
	if (!exp) return false;

	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[3], toWhom, true, true, ap, szFmt);
}

Bool8 __DebugMessageStop(Bool8 exp, const char *szFmt, ...)
{
	if (!exp) return false;

	va_list ap;
	va_start(ap, szFmt);
	return DoDebugMessage(DebugMsgNames[3], true, true, ap, szFmt);
}
#endif


//////////////////////////////////////////////////////////////////////////////
// _IsUser

Bool8 _IsUser(const TProgrammer& who)
{
	#if _MINICAD_EXTERNAL_ || _GSESDK_
		who;
		return true;
	#else
		return who.ContainsCurrentUser();
	#endif
}

Bool8 _IsUser(const char *szUser)
// [DMB, 5/1/95]
{
#if !_MINICAD_EXTERNAL_ && !_GSESDK_
	const Sint32	nBufferSize = 24;
	static char	szCurrentUser[nBufferSize] = "";

	if (szCurrentUser[0] == 0) {
		#if _WINDOWS
			DWORD size = nBufferSize;
			if (!GetUserNameA(szCurrentUser, &size)) {
				if (!GetEnvironmentVariableA("USERNAME", szCurrentUser, nBufferSize))
					strcpy(szCurrentUser, "error");
			}
		#else

			CFStringRef cfstrUserName;
			cfstrUserName = CSCopyUserName(true);
			if (cfstrUserName) {
				CFStringGetCString(cfstrUserName, szCurrentUser, sizeof(szCurrentUser), kCFStringEncodingUTF8);
				CFRelease(cfstrUserName);
			}
			else {
				strcpy(szCurrentUser, "error");
			}
		#endif
	}

	return _stricmp(szUser, szCurrentUser) == 0;
#else
	szUser;
	return true;
#endif
}

//////////////////////////////////////////////////////////////////////////////
#if BUG && !_MINICAD_EXTERNAL_ && !_GSESDK_

TDumpDevice::TDumpDevice()
{
	fIndent = 0;
	fWho = kEveryone;
}

Sint32 TDumpDevice::printf(const TProgrammer &toWhom, Sint32 indent, const char *fmt, ...) const
{
	va_list marker;
	va_start(marker, fmt);
	vprintf(toWhom, indent, fmt, marker);
	return 0;
}

Sint32 TDumpDevice::printf(const char *fmt, ...) const
{
	va_list marker;
	va_start(marker, fmt);
	vprintf(fWho, fIndent, fmt, marker);
	return 0;
}


TTextDumpDevice gl_stdDumpDevice;

Sint32 TTextDumpDevice::vprintf(const TProgrammer &who, Sint32 indent, const char *fmt, va_list &params) const
{
	// Indent the format string.
	const size_t kBufferSize = 256;

	const size_t extra = indent * 3; //-V101
	const size_t len = strlen(fmt) + extra + 1;
	if (len > kBufferSize)
		DSTOP((kDave & kNoBreak, "TTextDumpDevice::printf(): Someone exceeded buffer limit: %d > %d", len, kBufferSize));
	char indentedStr[kBufferSize];
	memset(indentedStr, ' ', extra);
	strncpy(&indentedStr[extra], fmt, kBufferSize - extra);

	DoDebugMessage("TTextDumpDevice::printf", who, false, false, params, indentedStr);
	return 0;
}

#endif // BUG

//////////////////////////////////////////////////////////////////////////////

#if _WINDOWS && BUG

#if !_GSDEBUG_DLL_ && !_GSESDK_

Sint32 __cdecl RedirectCRTDebugOutput(Sint32 nReportType, char* szMsg, Sint32* pnRet)
{
	Sint32 nRet = FALSE;

	static bool lastCRTMessageWasTerminated = true;
	static Sint32 lastCRTMessageType = _CRT_WARN;

	switch (nReportType)
	{
		case _CRT_ASSERT:
		{
			DSTOP((kPaul, "CRT ASSERT: %s", szMsg));
			break;
		}

		case _CRT_WARN:
		{
			if (lastCRTMessageWasTerminated || lastCRTMessageType != nReportType) {
				DMSG(("CRT WARN : "));
			}

			DMSG(("%s", szMsg));
			break;
		}

		case _CRT_ERROR:
		{
			if (lastCRTMessageWasTerminated || lastCRTMessageType != nReportType) {
				DMSG(("CRT ERROR : "));
			}

			DMSG(("%s", szMsg));
			break;
		}

		default:
		{
			DSTOP((kPaul, "Unexpected CRT report type: %d", nReportType));
			break;
		}
	}

	size_t msgSize = strlen(szMsg);
	lastCRTMessageWasTerminated = (szMsg[msgSize-1] == '\n');
	lastCRTMessageType = nReportType;

	if   (pnRet)
		*pnRet = 0;

	return   nRet;
}
#endif




void InitDebugCRT()
// This function sets C Run-Time library debug heap flags.
{
#if !_GSDEBUG_DLL_ && !_GSESDK_
	// Get the current state of the flag.
	Sint32 flags = _CrtSetDbgFlag( _CRTDBG_REPORT_FLAG );

	//
	// Below are the various flags you can use.  The top choice is always the
	// most thorough.
	//

	#if 1
		// Store additional debug information with CRT heap allocations.
		flags |= _CRTDBG_ALLOC_MEM_DF;
	#else
		// Do NOT store additional debug information with CRT heap allocations.
		// This turns off all CRT heap checking.
		flags &= ~_CRTDBG_ALLOC_MEM_DF;
	#endif

	#if 0
		// Check the CRT heap after every allocation and deallocation request.
		flags |= _CRTDBG_CHECK_ALWAYS_DF;
	#else
		// Only check the heap only during ASSERVALIDHEAP().
		flags &= ~_CRTDBG_CHECK_ALWAYS_DF;
	#endif

	#if 0
		// Include CRT internal memory blocks in heap validation.
		flags |= _CRTDBG_CHECK_CRT_DF;
	#else
		// Exclude CRT internal memory blocks in heap validation.
		flags &= ~_CRTDBG_CHECK_CRT_DF;
	#endif

	#if 0
		// Fill freed blocks with 0xDD and keep in CRT heap list.
		flags |= _CRTDBG_DELAY_FREE_MEM_DF;
	#else
		// Do not keep freed blocks in CRT heap list.
		flags &= ~_CRTDBG_DELAY_FREE_MEM_DF;
	#endif

	// Do leak detection at program exit.
	flags |= _CRTDBG_LEAK_CHECK_DF;

	// Set the new state for the flag
	_CrtSetDbgFlag(flags);


	_CrtSetReportHook2(_CRT_RPTHOOK_INSTALL, RedirectCRTDebugOutput);

	// since our hook function is now handling these, turn off the default handling so
	// we don't get two copies of each message
	_CrtSetReportMode( _CRT_ASSERT, 0 );
	_CrtSetReportMode( _CRT_WARN, 0 );
	_CrtSetReportMode( _CRT_ERROR, 0 );


#endif // _GSDEBUG_DLL_
}
#endif // _WINDOWS && BUG


#if !_MINICAD_EXTERNAL_ && !_GSESDK_

GSDEBUG_EXPORT void GDB_DebugInit (const char* appName, Uint32 flags)
{
	short	nameLen = sizeof(gDebugAppName);
	strncpy(gDebugAppName, appName, nameLen);
	gDebugAppName[nameLen-1] = '\0';  // For safety

	#ifdef BUG
		GSDebug::WantToDebug(false);
		GSDebug::DebugLevel(brief);
		GSDebug::DrawToScreen(false);

		gDebugFlags = flags;
	#endif

	#if _WINDOWS && BUG
		InitDebugCRT();
	#endif

	#if NETBUG
		LogVersionStamp();
	#endif

	#if !_GSDEBUG_DLL_
		#ifdef BUG
			InitBugMem();
		#endif

		#if TEST
			PerformLaunchAsserts();
		#endif
	#endif
} // GDB_DebugInit

void GSDEBUG_EXPORT GDB_DebugTerminate()
{
	#if NETBUG
		// this is really ugly & we'll have to streamline the API in the future, but it solves the
		// immediate problem in all cases. We need to de-allocate RemoteDebug memory here, before
		// we check for leaks, but it will be re-allocated if there are leaks reported by the DSTOP below
		KillRemoteDebug();
	#endif

	#if _WINDOWS && BUG
		// Check for memory leaks in the C run-time heap.
		//   RMEOVE this for a while.  There is a bug in the Microsoft
		//   implementation of typeid().name that leaves memory around
		//   (see Q140670 in KnowledgeBase).  [DMB 4/30/96]
		//DSTOP((_CrtDumpMemoryLeaks(), MAKEWHO("MemoryLeaks"), "C run-time heap memory leak(s) detected.  Check debug output window for more info."));
	#endif
} // GDB_DebugTerminate

#endif


#if _MINICAD_EXTERNAL_ || _GSESDK_

/*

Here's how all this works:

The external includes GSDebug.h which defines debugging macros to call these bottlenecks for the
appropriate test versions. These functions set up parameter passing blocks and pass the request to
Kludge, which then calls the real versions inside MiniCad

The implementations of the functions which receive these calls are in UCallBack.cp
*/


// the external debugging capability depends on gCBP being defined and maintained as a global
// this should already be done at global setup time


void RemoteLog(Uint16 level, const char *description)
{
	if (gCBP) {
		GS_Kludge(gCBP, kKludgeSendLog, (char*)description, nil);
	}
}

void CheckHeap(const TProgrammer &toWhom)
{
	if (gCBP) {
		GS_Kludge(gCBP, kKludgeCheckHeap, (char *)toWhom.GetName(), nil);
	}
}

void RemoteDebug(const char *toWhom, const char *description, Bool8 /*UNUSED(doStackCrawl)*/)
{
	AssertParameters pb;

	pb.toWhom = (char *)toWhom;
	pb.description = (char *)description;

	if (gCBP) {
		GS_Kludge(gCBP, kKludgeSendAssert, &pb, nil);
	}
}

void RemoteDebug(const TProgrammer& toWhom, const char *description)
{
	RemoteDebug(toWhom.GetName(), description, toWhom.ShouldDoStackCrawl());
}


// these asserts and verifys call back to MiniCad to actually do the verifications
// they are only defined for _MINICAD_EXTERNAL_ builds
// internal defs are in Builtins.cp

Sint32 _AssertValidPointer(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, const void *ptr, size_t lCount, Bool8 /*bReadOnly*/)
{
	ValidateParameters vp;
	Sint32 result = 0L;

	vp.toWhom = (char *)toWhom.GetName();
	vp.file = (char*)file;
	vp.line = line;
	vp.itemName = (char*)itemName;
	vp.thePointerOrHandle = (void*)ptr;
	vp.expectedSize = (Sint32)lCount;

	if (gCBP) {
		GS_Kludge(gCBP, kKludgeValidatePointer, &vp, &result);
	}
	return (Sint32)result;
}

Bool8 _VerifyValidPointer(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, const void *ptr, size_t lCount, Bool8 /*bReadOnly*/)
{
	if (_AssertValidPointer(toWhom, file, line, itemName, ptr, lCount))
		STOP();
	return (ptr != nil);
}

Sint32 _AssertValidHandle(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, Handle h, size_t lCount)
{
	ValidateParameters vp;
	Sint32 result = 0L;

	vp.toWhom = (char *)toWhom.GetName();
	vp.file = (char*)file;
	vp.line = line;
	vp.itemName = (char*)itemName;
	vp.thePointerOrHandle = (void*)h;
	vp.expectedSize = (Sint32)lCount;

	if (gCBP) {
		GS_Kludge(gCBP, kKludgeValidateHandle, &vp, &result);
	}

	return (Sint32)result;
}

Bool8 _VerifyValidHandle(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, Handle h, size_t lCount)
{
	if(_AssertValidHandle(toWhom, file, line, itemName, h, lCount))
		STOP();
	return (h != nil);
}

Sint32 _AssertValidString(Bool8 isAssert, const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, const char *psz, Sint32 cbMin, Sint32 cbMax)
{
	ValidateParameters vp;
	Sint32 result = 0L;

	vp.toWhom = (char *)toWhom.GetName();
	vp.file = (char*)file;
	vp.line = line;
	vp.itemName = (char*)itemName;
	vp.thePointerOrHandle = (void*)psz;
	vp.expectedSize = cbMin;
	vp.expectedSize2 = cbMax;
	vp.isAssert = isAssert;

	if (gCBP) {
		GS_Kludge(gCBP, kKludgeValidateString, &vp, &result);
	}

	if(isAssert) {
		return (Sint32)result;
	}
	else {
		// #dwd 4/10/00
		//if (result)
		//	STOP();
		return (psz != nil);
	}
}

Sint32 _AssertValidPString(Bool8 isAssert, const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, ConstGSStringPtr ps, Sint32 cbMin, Sint32 cbMax)
{
	ValidateParameters vp;
	Sint32 result = 0L;

	vp.toWhom = (char *)toWhom.GetName();
	vp.file = (char*)file;
	vp.line = line;
	vp.itemName = (char*)itemName;
	vp.thePointerOrHandle = (void*)ps;
	vp.expectedSize = cbMin;
	vp.expectedSize2 = cbMax;
	vp.isAssert = isAssert;

	if (gCBP) {
		GS_Kludge(gCBP, kKludgeValidatePString, &vp, &result);
	}

	if(isAssert) {
		return (Sint32)result;
	}
	else {
		// #dwd 4/10/00
		//if (result)
		//	STOP();
		return (ps != nil);
	}
}



#if DO_PORT_CHECKING && !_WINDOWS

Sint32 _AssertLegalPort(char *message, const char* file, Sint32 line, Bool8 allowWMgrPort)
{
	Sint32 result = 0L;
	ValidatePortParameters vp;

	vp.message = (char*)message;
	vp.file = (char*)file;
	vp.line = line;
	vp.flags = 0L;

	if (allowWMgrPort)
		vp.flags |= kAllowWMgrPort;

	if (gCBP) {
		GS_Kludge(gCBP, kKludgeCheckPorts, &vp, &result);
	}

	return (Sint32)result;
}
#endif


#endif // _MINICAD_EXTERNAL_




//////////////////////////////////////////////////////////////////////////////
// _Log

#if NETBUG

Sint32 _Log(Uint16 level, const char *format, ...)
{
	va_list		ap;
	va_start(ap, format);

	static Sint32		r = 0;	// 'static' so that it's off the stack and won't be messed up by an overflow of "buf[]".

	char		buf[kBuf_size];

	r = vsprintf(buf, format, ap);
	if (r > kBuf_size - 1) {
		#ifdef _WINDOWS

		#else
		GSBreakStrToLowLevelDebugger_("\p### logprintf: vsprintf overflowed buffer!!!!");
		#endif
	}
	va_end(ap);

	RemoteLog(level, buf);
	return r;
}


static void RemoteAssert(const TProgrammer& toWhom, const char *file, Sint32 line, const char *message)
{
	static Sint32 len;
	char buf[kBuf_size];

	#ifdef _WINDOWS
		if (message)
			len = sprintf(buf, "%s\r  file %s && line %d\r", message, file, line);
		else
			len = sprintf(buf, "  file %s && line %d\r", file, line);
	#else
		if (message)
			len = sprintf(buf, "%s\n  file %s && line %d\n", message, file, line);
		else
			len = sprintf(buf, "  file %s && line %d\n", file, line);
	#endif
	#if TEST
	if (len > kBuf_size-1)
		DSTOP((toWhom, "MAYDAY!!!  Your assertion message is too big. IT IS CORRUPTING DATA !!!"));
	#endif
	RemoteDebug(toWhom, buf);
}

#endif // NETBUG


// Function called when an ASSERTN, or VERIFYN fails.
Sint32 _FileDebugMessage(const TProgrammer& toWhom, const char *file, Sint32 line, const char *message)
{
	static std::recursive_mutex gMutex;
	std::lock_guard<std::recursive_mutex> lg(gMutex);

	Sint32 ret = 0;

	if (!toWhom.IsActLikeRelease()) {
#ifdef _WINDOWS
		#ifdef NETBUG
			RemoteAssert(toWhom, file, line, message);
		#endif
#else
		#if NETBUG
			RemoteAssert(toWhom, file, line, message);
		#endif
#endif

		// Create string to show to user.
		static char szTitle[] = "Assertion Failed!";
		//static char szMessage1[] = "%s: File %s, Line %d,\n  %s";
		static char szMessage1[] = "%s: %s";
		static char szMessage2[] = "%s";
		static char szMessage3[] = "%s";
		static char szMessage4[] = "ASSERTN";
		static char szMsg[kBuf_size];

		Sint32 len;
		if (toWhom != NULL && message != NULL)
			len = sprintf(szMsg, (const char*) szMessage1, (const char*) toWhom, (const char*) message);
		else if (message != NULL)
			len = sprintf(szMsg, (const char*) szMessage2, (const char*) message);
		else if (message == NULL && toWhom != NULL)
			len = sprintf(szMsg, (const char*) szMessage3, (const char*) toWhom);
		else
			len = sprintf(szMsg, "%s", (const char*) szMessage4 );
		DSTOPIF(len>511, (toWhom, "MAYDAY!!!  Your assertion message is too big. IT IS CORRUPTING THE DATA SEGMENT."));

		// Write to debug window or serial port.

		OutputMessage out(true);

		out.SendString(szMsg);
		out.SendString(", ");
		out.SendString(szTitle);
		out.SendString("\n");

		#ifdef BUG

		ret = __ShowAlertDialog( szMsg, file, line );

		#endif
	}

	return ret;
}

// I know we are double buffering these messages, but I don't have the time right now to fix it
// and I don't expect it to cause any problems - PCP

Sint32 _Assert(const TProgrammer& toWhom, const char *file, Sint32 line, const char *expr)
{
	static Sint32 len;
	char buf[kBuf_size];

	len = sprintf(buf, "DEBUGSTOP ASSERT(%s) failed!", expr);
	if (len > kBuf_size-1)
		DSTOP((toWhom, "MAYDAY!!!  Your assertion message is too big. IT IS CORRUPTING DATA !!!"));

	return _FileDebugMessage(toWhom, file, line, buf);
}

Sint32 _AssertEx(const TProgrammer & inProgrammer, const char * inAssertFile, 
		Sint32 inAssertLine, const char * inMessage, ...)
{
	va_list args;
	va_start(args, inMessage);

	static Sint32 len;
	const int kBufSize = 2048;
	char buf[kBufSize];

	len = vsprintf(buf, inMessage, args);;
	if( len >= kBufSize )
		DSTOP((inProgrammer, "MAYDAY!!!  Your assertion message is too big. IT IS CORRUPTING DATA !!!"));

	va_end(args);

	return _FileDebugMessage(inProgrammer, inAssertFile, inAssertLine, buf);
}


// this function is available in the application as well as plug-ins - PCP
Sint32 GSDEBUG_EXPORT _AssertValidMenuHandle(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, GSHandle h)
{
	if (GSDebugRunningMacOSX()) {
		// Under MacOS X, MenuHandles are not handles, so there isn't much we can say about them - PCP
		return 0;
	}
	else {
		return _AssertValidHandle(toWhom, file, line, itemName, h);
	}
}





#if !_MINICAD_EXTERNAL_ && !_GSESDK_








#if _WINDOWS
///////////////////////////////////////////////////////////////////////////////

BOOL IsValidDC(HDC hdc)
// Try to validate an HDC.
// [DMB 6/25/96]
{
	BOOL bValid = FALSE;

	if (hdc) {
		// Try to get the HWND associated with the HDC.
		HWND hwnd = WindowFromDC(hdc);
		if (hwnd) {
			// Window DC.  Validate by verifying that the associated HWND is valid.
			bValid = IsWindow(hwnd);
		}
		else {
			// Maybe memory DC or printer DC.  Validate by trying to get text
			// alignment setting.
			bValid = ( GetTextAlign(hdc) != GDI_ERROR );
		}
	}

	return bValid;
}

///////////////////////////////////////////////////////////////////////////////


bool GSDEBUG_EXPORT _ValidateHWND(const TProgrammer& toWhom, bool bAssert, const char* file, Sint32 line, const char* itemName, void *hWnd)
// This is the TEST version of the function to validate an HWND.  For the release version, see GSDebug,h,
{
	bool valid = IsWindow((HWND)hWnd);

	if (!valid) {
		char buf[kBuf_size];
		sprintf(buf, "%s(%s) failed!\n%s", bAssert ? "AssertHWND" : "VerifyHWND", itemName, "Invalid HWND");
		Sint32 ret = _FileDebugMessage(toWhom, file, line, buf);
		if (bAssert) {
			valid = (ret == 0);
		}
		else {
			if (ret) STOP();
			valid = (hWnd != NULL);
		}
	}
	return valid;
}


bool GSDEBUG_EXPORT _ValidateHDC(const TProgrammer& toWhom, bool bAssert, const char* file, Sint32 line, const char* itemName, void *hdc)
// This is the TEST version of the function to validate an HDC.  For the release version, see GSDebug,h,
{
	bool valid = IsValidDC((HDC)hdc);

	if (!valid) {
		char buf[kBuf_size];
		sprintf(buf, "%s(%s) failed!\n%s", bAssert ? "AssertHDC" : "VerifyHDC", itemName, "Invalid HDC");
		Sint32 ret = _FileDebugMessage(toWhom, file, line, buf);
		if (bAssert) {
			valid = (ret == 0);
		}
		else {
			if (ret) STOP();
			valid = (hdc != NULL);
		}
	}
	return valid;
}


#endif // _WINDOWS


enum  {
	kVPNoErr = 0,
	kVPNegativeCount,
	kVPPtrIsNil,
	kVPNotReadable,
	kVPNotWritable,
	kVPNotInAppHeap,
	kVPPStringTooLong,
	kVPStringMinSizeTooLong,
	kVPStringBadLength,
	kVPHandleIsPurgeable,
	kVPBadHWND,
	kVPBadHDC,
	kVPHandleIsNil = 100,
	kVPHandleIsMisaligned,
	kVPMasterPtrIsNil,
	kVPMasterPtrIsAllF,
	kVPMasterPtrIsMisaligned,
	kVPMemErrorReturnedError,
	kVPHandleBlockTooSmall,
	kVPHandleFailsOSTest,
	kVPHandlePointerBase = 200,
	kVPHandleNegativeCount,
	kVPHandlePtrIsNil,
	kVPHandleNotReadable,
	kVPHandleNotWritable,
	kVPHandleNotInAppHeap,
	kVPMasterPointerBase = 300,
	kVPMasterPointerNegativeCount,
	kVPMasterPointerPtrIsNil,
	kVPMasterPointerNotReadable,
	kVPMasterPointerNotWritable,
	kVPMasterPointerNotInAppHeap,
	kVPBadlyFormattedPath
};


class UserError {
	public:
		short myErr;
		#if _GSDEBUG_DLL_
			UserError()				{ myErr = kVPNoErr; }
		#else
			OSErr sysErr;
			UserError()				{ myErr = kVPNoErr; sysErr = noErr; }
		#endif

		Bool8 IsError(Bool8 bCheckPointer = false) const;
};

Bool8 UserError::IsError(Bool8 bCheckPointer) const
{
	if (bCheckPointer)
		return myErr == kVPPtrIsNil || myErr == kVPHandleIsNil;
	else
#if _GSDEBUG_DLL_
		return myErr != kVPNoErr;
#else
		return myErr != kVPNoErr || sysErr != noErr;
#endif
}


static UserError IsValidAddress(const void *ptr, SintptrT lCount, Bool8 WIN_ONLY(bReadOnly))
//
// ***  If you change any of the tests below (including the testing order),
//      please let David Bowman know so that he can update the documentation.
//
{
	UserError result;
	if (lCount < 0) {
		DMSG((dlAlways, kEveryone, "IsValidAddress(): Bad size parameter. (lCount = %" PRIdPTR ")\n", lCount));
		result.myErr = kVPNegativeCount;
	}
	else if (ptr == NULL) {
		DMSG((dlAlways, kEveryone, "IsValidAddress(): Pointer is nil. (ptr == nil)\n"));
		result.myErr = kVPPtrIsNil;
		return result;
	}
/*
	else if (!VWMM::PointerIsValid(ptr, true))
	{
		DMSG((kEveryone, dlAlways, "IsValidAddress(): Pointer is invalid memory.\n"));
		result.myErr = kVPHandlePointerBase;
		return result;
	}
	*/
	return result;
}

static UserError IsValidHandle(const GSHandle h, SintptrT lCount, Bool8 bReadOnly)
// If 'lCount' is zero or negative, handles that point to nil (*h==nil)
// will be considered valid.
//
// ***  If you change any of the tests below (including the testing order),
//      please let David Bowman know so that he can update the documentation.
//
{
	UserError result;
	if (h == NULL) {
		DMSG((kEveryone, dlAlways, "IsValidHandle(): Handle is nil. (h == nil)\n"));
		result.myErr = kVPHandleIsNil;
	}
	else if (lCount > 0 && *h == NULL)
	{
		DMSG((kEveryone, dlAlways, "IsValidHandle(): Master Ptr is nil. (*h == nil)\n"));
		result.myErr = kVPMasterPtrIsNil;
		return result;
	}
//	Note, the next block is expensive so comment out for now
//	else if (!gVWMM->HandleIsValid(h, true))	
//	{
//		DMSG((kEveryone, dlAlways, "IsValidHandle(): Handle is invalid memory. (h == bad_mem)\n"));
//		result.myErr = kVPHandlePointerBase;
//		return result;
//	}
	return result;
}

#if 0
Bool8 VerifyHandle(const void *ptr, Sint32 lCount)
{
	return ! IsValidHandle((GSHandle)ptr, lCount, false).IsError();
}
#endif

static UserError IsValidString(const char *psz, Sint32 cbMin, Sint32 cbMax)
{
	UserError	result;
	Sint32		i;
#if !_WINDOWS
	Sint32		minLen;
#endif

	// 20480 is just a really big number
	if (cbMax==0) cbMax = 20480;

	if (cbMin > cbMax) {
		result.myErr = kVPStringMinSizeTooLong;
		return result;
	}

	if (psz == NULL) {
		result.myErr = kVPPtrIsNil;
		return result;
	}

	#if _WINDOWS
		if (IsBadStringPtrA(psz, cbMin==0 ? 1 : (size_t)cbMin)) { //-V201
			result.myErr = kVPNotReadable;
			return result;
		}
	#else
		// This relies on the OS _not_ stopping us from reading beyond the
		// end of a block of memory.  The MacOS will let us do this.  This
		// makes the function easier to write and much faster to execute
		// since we don't have to check each character of the string to see
		// if it is in valid memory before we access it.
	#endif

	for (i=0; i<=cbMax && psz[i]; ++i) ;			// Find end of string.
	if (i<cbMin || i>cbMax) {
		result.myErr = kVPStringBadLength;
		return result;
	}

#if !_WINDOWS
	minLen = (cbMax < (i+1)) ? cbMax : (i+1);
	return IsValidAddress(psz, minLen, false);	// Check for read/write permission on memory.
#elif _MSC_VER < 1200
	return IsValidAddress(psz, min(cbMax, i+1), false);	// Check for read/write permission on memory.
#else
	return IsValidAddress(psz, min(cbMax, i+1), true);	// Check for read permission on memory. //-V106
#endif
}

static UserError IsValidPString(ConstGSStringPtr ps, Sint32 cbMin, Sint32 cbMax)
// [DMB, 3/9/95]
{
	UserError result;
	UserError ptrResult;

	if (cbMax == 0)
		cbMax = 255;						// Caller does not care about a maximum.
	else if (cbMax>255){
		result.myErr = kVPPStringTooLong;
		return result;
	}
	if (cbMin > cbMax){
		result.myErr = kVPStringMinSizeTooLong;
		return result;
	}
	if (ps == NULL) {
		result.myErr = kVPPtrIsNil;
		return result;
	}

#if _MSC_VER < 1200
	ptrResult = IsValidAddress(ps, 1, false);				// Test if length byte is in valid memory.
#else
	ptrResult = IsValidAddress(ps, 1, true);				// Test if length byte is in valid memory.
#endif
	if (ptrResult.myErr != kVPNoErr) {
		return ptrResult;
	}
#if _MSC_VER < 1200
	ptrResult = IsValidAddress(ps+1, ps[0], false);		// Test if string characters are in valid memory.
#else
	ptrResult = IsValidAddress(ps+1, ps[0], true);		// Test if string characters are in valid memory.
#endif
	if (ptrResult.myErr != kVPNoErr) {
		return ptrResult;
	}

	if (ps[0] < cbMin || ps[0] > cbMax) {			// Test if length falls within bounds.
		result.myErr = kVPStringBadLength;
		return result;
	}

	// Passed all of the tests.
	return result;
}


static Sint32 _SendErrorMessage(const TProgrammer& toWhom, const char* file, Sint32 line, const char* theAssert, const char* itemName, UserError theErr, const void* theData, SintptrT lCount)
{
	if (theErr.myErr == kVPNoErr)
		return 0;

	static Sint32 len;
	char buf[kBuf_size];
	char reason[512];
	const char* errString;

	Bool8 displayPtr = false;
	Bool8 displayMasterPtr = false;
	Bool8 specialError = false;

	switch (theErr.myErr) {
		case kVPNegativeCount:						specialError = true; break;
		case kVPPtrIsNil:							errString = "Pointer is NIL"; break;
		case kVPNotReadable:						errString = "Pointer is not readable"; displayPtr = true; break;
		case kVPNotWritable:						errString = "Pointer is not writable"; displayPtr = true; break;
		case kVPNotInAppHeap:						errString = "Pointer does not point into our partition"; displayPtr = true; break;

		case kVPPStringTooLong:						specialError = true; break;
		case kVPStringMinSizeTooLong:				specialError = true; break;
		case kVPStringBadLength:					specialError = true; break;

		case kVPHandleIsNil:						errString = "Handle is nil"; break;
		case kVPHandleIsMisaligned:					errString = "Handle is misaligned"; displayPtr = true; break;
		case kVPHandleFailsOSTest:					errString = "Handle fails operating system validity test"; displayPtr = true; break;
		case kVPMasterPtrIsNil:						errString = "Master Pointer is nil"; displayPtr = true; displayMasterPtr = true; break;
		case kVPMasterPtrIsAllF:					errString = "Master Pointer is 0xFFFFFFFF"; displayPtr = true; displayMasterPtr = true; break;
		case kVPMasterPtrIsMisaligned:				errString = "Master Pointer is misaligned"; displayPtr = true; displayMasterPtr = true; break;
		case kVPMemErrorReturnedError:				specialError = true; break;
		case kVPHandleBlockTooSmall:				specialError = true; break;

		case kVPHandleNegativeCount:				errString = "INTERNAL ERROR"; break;
		case kVPHandlePtrIsNil:						errString = "INTERNAL ERROR"; break;
		case kVPHandleNotReadable:					errString = "Handle is not readable"; displayPtr = true; break;
		case kVPHandleNotWritable:					errString = "Handle is not writable"; displayPtr = true; break;
		case kVPHandleNotInAppHeap:					errString = "Handle does not point into our partition"; displayPtr = true; break;

		case kVPHandleIsPurgeable:					errString = "Handle is purgeable"; displayPtr = true; displayMasterPtr = true; break;

		case kVPBadHWND:							errString = "Invalid HWND"; break;
		case kVPBadHDC:								errString = "Invalid HDC"; break;

		case kVPMasterPointerNegativeCount:			errString = "INTERNAL ERROR"; break;
		case kVPMasterPointerPtrIsNil:				errString = "INTERNAL ERROR"; break;
		case kVPMasterPointerNotReadable:			errString = "Master Pointer is not readable"; displayPtr = true; displayMasterPtr = true; break;
		case kVPMasterPointerNotWritable:			errString = "Master Pointer is not writable"; displayPtr = true; displayMasterPtr = true; break;
		case kVPMasterPointerNotInAppHeap:			errString = "Master Pointer does not point into our partition"; displayPtr = true; displayMasterPtr = true; break;

		case kVPBadlyFormattedPath:					errString = "Badly Formatted Path"; break;

		default:									errString = "REASON UNKNOWN"; break;
	}

	if (specialError) {
		switch (theErr.myErr) {
#if !_GSDEBUG_DLL_
			case kVPMemErrorReturnedError:	{

				const void* theMaster = 0;
				if (theData) {
					theMaster = *(const void **)theData;
				}
				len = sprintf(reason, "MemError returned error %d\n   %s: (0x%p)->(0x%p)->data", theErr.sysErr, itemName, theData, theMaster); //-V111
				break;
			}
			case kVPHandleBlockTooSmall: {
				size_t theSize = gVWMM->GetHandleSize((Handle) theData);
				len = sprintf(reason, "Handle %s is too small\n   actual: %" PRIuPTR "bytes  specified: %" PRIdPTR " bytes", itemName, theSize, lCount); //-V111
				break;
			}
#endif
			case kVPPStringTooLong: {
				len = sprintf(reason, "String max size param (cbMax == %" PRIdPTR ") too big", lCount); //-V111
				break;
			}
			case kVPStringMinSizeTooLong: {
				len = sprintf(reason, "String min size param (cbMin) too big ( > cbMax (%" PRIdPTR "))", lCount); //-V111
				break;
			}
			case kVPStringBadLength: {
				len = sprintf(reason, "String length out of bounds (cbMin to cbMax (%" PRIdPTR "))", lCount); //-V111
				break;
			}
			case kVPNegativeCount: {
				len = sprintf(reason, "Pointer size param (lCount = %" PRIdPTR ") is negative", lCount); //-V111
				break;
			}

			default:
				len = sprintf(reason, "UNKNOWN ERROR");
		}
	}
	else if (displayMasterPtr) {
		const void* theMaster = 0;
		if (theData) {
			theMaster = *(const void **)theData;
		}

		len = sprintf(reason, "%s\n   %s: (0x%p)->(0x%p)->data", errString, itemName, theData, theMaster); //-V111
	}
	else if (displayPtr) {
		len = sprintf(reason, "%s\n   %s: (0x%p)->", errString, itemName, theData); //-V111
	}
	else {
		len = sprintf(reason, "%s", errString);
	}

	if (len > kBuf_size-1)
		DSTOP((kPaul, "_SendErrorMessage -  reason message is too big. IT IS CORRUPTING DATA !!!"));

	len = sprintf(buf, "%s(%s) failed!\n%s", theAssert, itemName, reason);
	if (len > kBuf_size-1)
		DSTOP((kPaul, "_SendErrorMessage -  buf message is too big. IT IS CORRUPTING DATA !!!"));
	return _FileDebugMessage(toWhom, file, line, buf);
}


//---------------------------------------------------------------------------------------
Sint32 _AssertValidPointer(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName,
						const void *ptr, size_t lCount, Bool8 bReadOnly)
// Returns non-zero if breaking to debugger.
{
	if (toWhom.IsActLikeRelease())
		return 0;
	UserError theErr = IsValidAddress(ptr, lCount, bReadOnly);
	Sint32 ret = _SendErrorMessage(toWhom, file, line, "AssertValidPointer", itemName, theErr, ptr, lCount);
	if (ret)
		STOP();
	return ret;
}

//---------------------------------------------------------------------------------------
Bool8 _VerifyValidPointer(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName,
						  const void *ptr, size_t lCount, Bool8 bReadOnly)
{
	if (toWhom.IsActLikeRelease())
		return ptr != NULL;
	UserError theErr = IsValidAddress(ptr, lCount, bReadOnly);
	if (_SendErrorMessage(toWhom, file, line, "VerifyValidPointer", itemName, theErr, ptr, lCount))
		STOP();
	return !theErr.IsError(true);
}

//---------------------------------------------------------------------------------------
Sint32 _AssertValidHandle(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, GSHandle h, size_t lCount)
{
	if (toWhom.IsActLikeRelease())
		return 0;
	UserError theErr = IsValidHandle(h, lCount, false);
	Sint32 ret = _SendErrorMessage(toWhom, file, line, "AssertValidHandle", itemName, theErr, h, lCount);
	if (ret)
		STOP();
	return ret;
}

//---------------------------------------------------------------------------------------
Bool8 _VerifyValidHandle(const TProgrammer& toWhom, const char* file, Sint32 line, const char* itemName, GSHandle h, size_t lCount)
{
	if (toWhom.IsActLikeRelease())
		return h != NULL;
	UserError theErr = IsValidHandle(h, lCount, false);
	if (_SendErrorMessage(toWhom, file, line, "VerifyValidHandle", itemName, theErr, h, lCount))
		STOP();
	return !theErr.IsError(true);
}

//---------------------------------------------------------------------------------------
Sint32 _AssertValidPString(Bool8 isAssert, const TProgrammer& toWhom, const char* file, Sint32 line,
						const char* itemName, ConstGSStringPtr ps, Sint32 cbMin, Sint32 cbMax)
{
	if (toWhom.IsActLikeRelease())
		return isAssert ? 0 : ps != NULL;
	UserError theErr = IsValidPString(ps, cbMin, cbMax);
	Sint32 ret = _SendErrorMessage(toWhom, file, line, "AssertValidPString", itemName, theErr, ps, cbMax); //-V106
	if (!isAssert) {
		if (ret)
			STOP();
		ret = !theErr.IsError(true);
	}
	return ret;
}

//---------------------------------------------------------------------------------------
Sint32 _AssertValidString(Bool8 isAssert, const TProgrammer& toWhom, const char* file, Sint32 line,
					   const char* itemName, const char *psz, Sint32 cbMin, Sint32 cbMax)
{
	if (toWhom.IsActLikeRelease())
		return isAssert ? 0 : psz != NULL;
	UserError theErr = IsValidString(psz, cbMin, cbMax);
	Sint32 ret = _SendErrorMessage(toWhom, file, line, "AssertValidString", itemName, theErr, psz, cbMax); //-V106
	if (!isAssert) {
		if (ret)
			STOP();
		ret = !theErr.IsError(true);
	}
	return ret;
}


#if _WINDOWS

//---------------------------------------------------------------------------------------
Sint32 GSDEBUG_EXPORT _AssertValidFilePath(Bool8 isAssert, const TProgrammer& toWhom, const char* file,
									  Sint32 line, const char* itemName, const char* fullPath)
{
	UserError theErr = IsValidString(fullPath, 3, MAX_PATH-1);
	if (theErr.myErr == kVPNoErr) {
		Bool8 validPath = false;

		validPath = ((fullPath[0] >= 'a' && fullPath[0] <= 'z') || (fullPath[0] >= 'A' && fullPath[0] <= 'Z')) &&
					fullPath[1] == ':' &&
					fullPath[2] == '\\';

		if (!validPath) {
			validPath = (fullPath[0] == '\\' && fullPath[1] == '\\') &&
						strchr(&fullPath[2], '\\');
		}

		if (!validPath)
			theErr.myErr = kVPBadlyFormattedPath;
	}

	Sint32 ret = _SendErrorMessage(toWhom, file, line, "AssertValidPath", itemName, theErr, fullPath, 0);
	if (!isAssert) {
		if (ret)
			STOP();
		ret = !theErr.IsError(true);
	}
	return ret;
}

#endif // _WINDOWS


#if !_WINDOWS

// this is a set of low level routine which walks the application heap manually. They must be updated
// if the memory manager changes

// call this on pointers or references passed to routines which may move memory
// this includes any routines which are not in Pre-loaded segments
// this should be used liberally

// (it only checks the application heap. If an object is in another heap, we will never assert!!)

enum {
	k24Heap = 1,
	k32Heap = 2,
	kModernHeap = 3
};

const unsigned char k24SizeCorrectionMask = 0x0F;

const unsigned char kBlockTypeMask = 0xC0;

const unsigned char kHandleBlock24 = 0x80;
const unsigned char kPtrBlock24 = 0x40;
const unsigned char kFreeBlock24 = 0x00;

const unsigned char kHandleBlock32 = 0x80;
const unsigned char kPtrBlock32 = 0x40;
const unsigned char kFreeBlock32 = 0x00;

const unsigned char kHandleBlockModern = 0x80;


typedef struct Header24 {
	unsigned char blockType;
	unsigned char highSize;
	unsigned short lowSize;
	void* zonePtr;
	unsigned char startData;
} *Header24Ptr;


typedef struct Header32 {
	unsigned char blockType;
	unsigned char masterPtrFlags;
	unsigned char reserved1;
	unsigned char sizeCorrection;
	size_t blockSize;
	void* zonePtr;
	unsigned char startData;
} *Header32Ptr;


// NOTE - the type of result is specified by the return value - kNoBlock, kHandle, kPointer, or kFree
// for free blocks, result is a pointer to the block header

Sint32 _AssertNotVolatile(const TProgrammer& /*toWhom*/, const char* /*file*/, Sint32 /*line*/, const char* /*ptrName*/, void* /*ptr*/)
{
	return 0;
}


#endif // !_WINDOWS



// call CheckHeap any time memory ops are legal. It checks that the heap is valid & checks
// available block sizes & fragmentation.

void GSDEBUG_EXPORT CheckHeap(const TProgrammer &WIN_ONLY(toWhom))
{
#if _WINDOWS
	#if BUG
		#if _GSDEBUG_DLL_ || _GSESDK_
			HANDLE heaps[40];
			const DWORD nHeaps = GetProcessHeaps(40, heaps);
			DSTOP((nHeaps > 40, toWhom, "Cannot check heaps because too many"));
			for (DWORD i = 0; i < nHeaps; ++i)
				DSTOP((!HeapValidate(heaps[i], 0, NULL), toWhom, "Invalid heap found!!"));
		#else
			// Check the C run-time heap.
			DSTOPIF(!_CrtCheckMemory(), (toWhom, "C run-time heap is not valid. Check "
				"debug output window for more info. Use _CRTDBG_CHECK_ALWAYS_DF flag "
				"in InitDebugCRT() to help locate problem."));

			// Check Altura's heaps.
// Dec 19, 2001 AlturaRemoval, jg
//			ASI_MemCheck();
		#endif
	#endif // BUG

#else
	//DSTOP ((kVictor, "XXX:Carbon - ApplicationZone and GetApplLimit not available in Carbon.\n"));
#endif
}

#endif // _MINICAD_EXTERNAL_



#if !_WINDOWS

Bool8 __IsHandleLocked(GSHandle h)
{
	return (gVWMM->HGetState(h) & 0x80) ? true : false;
}

#endif


#endif // TEST



/////////////////////////////////////////////////////////////////////////////////////////
// TDebugObject

//---------------------------------------------------------------------------------------
#if TEST
void TDebugObject::AssertValid(const TProgrammer &toWhom, Bool8 bCheckMem) const
{
	if (bCheckMem)
		ASSERTPOINTER(toWhom, this, 1);
}
#endif // TEST

//---------------------------------------------------------------------------------------
#if BUG && GS_USE_CLASS_DEBUGGING
void TDebugObject::Dump(const TProgrammer &toWhom, TDumpDevice &dd, Sint32 indent) const
{
	dd.printf(toWhom, indent, "----------------------------------------\n" //-V111
							  "TDebugObject derived class at $%p\n", this);
}
#endif // BUG && GS_USE_CLASS_DEBUGGING

/////////////////////////////////////////////////////////////////////////////////////////
// TVirtualDebugObject

//---------------------------------------------------------------------------------------
#if TEST && GS_USE_CLASS_DEBUGGING
void TVirtualDebugObject::AssertValid(const TProgrammer &toWhom, Bool8 bCheckMem) const
{
	if (bCheckMem)
		ASSERTPOINTER(toWhom, this, 1);
}
#endif // TEST

//---------------------------------------------------------------------------------------
#if BUG && GS_USE_CLASS_DEBUGGING
void TVirtualDebugObject::Dump(const TProgrammer &toWhom, TDumpDevice &dd, Sint32 indent) const
{
	dd.printf(toWhom, indent, "----------------------------------------\n" //-V111
							  "TVirtualDebugObject derived class at $%p\n", this);
}
#endif // BUG && GS_USE_CLASS_DEBUGGING


#if _WINDOWS
/////////////////////////////////////////////////////////////////////////////////////////
// TWinErrorCode

//---------------------------------------------------------------------------------------
TWinErrorCode::TWinErrorCode()
{
	// Call GetLastError() and use FormatMessage() to get the message string
	// for the error
	::FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
					NULL, GetLastError(), MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
					(LPTSTR) &fMessageBuffer, 0, NULL);

	// strip carriage return, linefeed from message string
	char *string = (char *)fMessageBuffer;

	size_t n = strlen(string)-1;
	while (string[n] == '\n' || string[n] == '\r') {
		string[n] = '\0';
		n--;
	}
}

TWinErrorCode::~TWinErrorCode()
{
	::LocalFree(fMessageBuffer);
}
#endif	// _WINDOWS


/////////////////////////////////////////////////////////////////////////////////////////
// Timers

#if BUG
	#if _WINDOWS
		// Windows implementation.

		TDebugTimer::TDebugTimer()
		{
			ASSERTN(kDave, sizeof(LARGE_INTEGER) == sizeof(fStartTime));
			QueryPerformanceCounter((PLARGE_INTEGER)&fStartTime);
		}

		void TDebugTimer::Stop(const TProgrammer &who, ConstGSCStrPtr name, bool bWindow)
		{
			// Get end time.
			Uint64 stopTime;
			if (QueryPerformanceCounter((PLARGE_INTEGER)&stopTime)) {

				// Get number of units per second in the timer.
				Sint64 perSecond;
				if (QueryPerformanceFrequency((PLARGE_INTEGER)&perSecond)) {

					// Compute seconds.
					const double seconds = (Sint64)(stopTime - fStartTime) / (double)perSecond;

					// Display results.
					char szMessage[256];
					sprintf(szMessage, "Timer '%s' took %.3f seconds.\n", name, seconds);
					DMSG((who, szMessage));
					if (bWindow)
						::MessageBoxA(g_hParentWnd, szMessage, "Timer Results", MB_OK | MB_ICONINFORMATION);
					return;
				}
			}
			DMSG((who, "Performance counters not supported by hardware.\n"));
		}

	#else
		// Mac implementaion.

	#endif // _WINDOWS
#endif // BUG
#endif //defined(GS_MAC) || defined(DEV_BLD) - Added to create bogus release version of GSDebug lib. [VML 01/09/04]
