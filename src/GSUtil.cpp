//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//


#include "StdHeaders.h"	// DO NOT MOVE THIS LINE FROM BEING FIRST NON-COMMENT LINE.  [DMB, 10/30/95]

#include <stdarg.h>
#include <time.h>
#if _WINDOWS
#include <process.h>
#else
#include <unistd.h>
#endif

#if GS_MAC
#include "NNAVectorworksSDKProbes.h"
#endif

#ifndef _MINICAD_
#include "VectorworksSDK.h"
#endif

#ifdef _MINICAD_
	#include "File.X.h"
	#include "ApplicationFolders.h"
    #include "AppProtection.h"
    #include "ApplicationUpdater.h"
    #include "UVersionNumber.h"
	#include "Kernel/GSLogging.h"
	#include "Singleton.X.h"
	#include "TMutex.X.h"
	// from Builtins.h/.cpp
	double GetSecondsSinceLaunch(void);
    double GetTimeAtLaunch(void);

	double gLogTime = 0.0;
#elif _WINDOWS
	//
#endif

#if _WINDOWS
#include "..\..\..\..\ShellWin\Resource.h"
#include "..\..\..\..\Include\URegKey.h"
#endif

#if _WINDOWS
#include "..\..\..\..\ShellWin\Resource.h"
#include "..\..\..\..\Include\URegKey.h"
#endif

#include "Kernel/MiniCadHookIntf.h"

// This must follow all header files.
#undef THIS_FILE
DECLARE_THIS_FILE


Boolean _setmember(Sint32 c, ...)
/*
	Tests if c == any of the following parameters.  The parameter
	list is zero-terminated, so c == 0 must be tested separately.
*/
{
	va_list	ap;
	Sint32		i;

	va_start(ap, c);

	while ((i = va_arg(ap, Sint32)) != 0) {
		if (c == i) { va_end(ap); return true; }
	}
	va_end(ap);
	return false;
}

IntegerSet::IntegerSet()
{
	for (short i = numLongs-1; i >= 0; i--) this->bits[i] = 0;
}

IntegerSet::IntegerSet(short i0, short i1, short i2, short i3,
							short i4, short i5, short i6, short i7,
							short i8, short i9)
{
	for (short i = numLongs-1; i >= 0; i--) this->bits[i] = 0;
	if (i0 >= 0) *this += i0;
	if (i1 >= 0) *this += i1;
	if (i2 >= 0) *this += i2;
	if (i3 >= 0) *this += i3;
	if (i4 >= 0) *this += i4;
	if (i5 >= 0) *this += i5;
	if (i6 >= 0) *this += i6;
	if (i7 >= 0) *this += i7;
	if (i8 >= 0) *this += i8;
	if (i9 >= 0) *this += i9;
}

IntegerSet::IntegerSet(const IntegerSet &s)
{
	for (short i = numLongs-1; i >= 0; i--) this->bits[i] = s.bits[i];
}

void IntegerSet::operator +=(short i)
{
	if (i < 0 || i > maxElement) {
		#if 0
		DebugStr("\p### Set element out of range.");
		#endif
		return;
	}
	this->bits[i / 32] |= 1L << (i % 32);
}

Boolean IntegerSet::contains(short i) const
{
	if (i < 0 || i > maxElement) {
		#if 0
		DebugStr("\p### Set element out of range.");
		#endif
		return false;
	}
	return ((this->bits[i / 32] & (1L<<(i % 32))) != 0);
}

void IntegerSet::operator -=(short i)
{
	if (i < 0 || i > maxElement) {
		#if 0
		DebugStr("\p### Set element out of range.");
		#endif
		return;
	}
	this->bits[i / 32] &= ~(1L << (i % 32));
}

void IntegerSet::operator +=(const IntegerSet &s)
{
	for (short i = numLongs-1; i >= 0; i--)
		this->bits[i] |= s.bits[i];
}

void IntegerSet::operator -=(const IntegerSet &s)
{
	for (short i = numLongs-1; i >= 0; i--)
		this->bits[i] &= ~s.bits[i];
}

#ifdef _MINICAD_

Boolean OSIsMetric()
//
// Description:
//   This function determines if the operating system is set to use metric units.
//
// Returns:
//   Boolean - whether it is set to metric.
//
// Created by Bruce Ferguson on 10/29/02.  Moved to this file on 10/24/05.
//
{
	Boolean isMetric;

#if GS_WIN
	const short kCharBufSize = 2;	// 1-character string plus 1 for null char
	wchar_t buffer[kCharBufSize];

	GetRegistryValue(HKEY_CURRENT_USER, IDS_REGKEY_INTERNATIONAL, IDS_REGVAL_MEASURE, &buffer, kCharBufSize * 2); 
	isMetric = (buffer[0] == '0');
#else
	isMetric = IsMetric();
#endif
	return isMetric;
}
#endif

/////////////////////////
// Cross-Platform byte swapping functions
/////////////////////////

// ByteSwapDWORD swaps 4 consecutive bytes (msb to lsb)

#if 0
void GS_API ByteSwapLONG(Sint32 *pl)
{
	char t;
	char* p1 = (char*)pl;
	char* p2 = p1 + 3;

	t = *p1;
	*p1 = *p2;
	*p2 = t;

	++p1; --p2;

	t = *p1;
	*p1 = *p2;
	*p2 = t;
}
#endif

TJsonType::TJsonType(){
	fStringData = "";
	fNonStringData.uint8_val = 0;
	fIsStr = true;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(const TXString& msg){
    fStringData = msg;
	fNonStringData.uint8_val = 0;
	fIsStr = true;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(const char* msg){
    fStringData = msg;
	fNonStringData.uint8_val = 0;
	fIsStr = true;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(Sint64 val){
    fStringData = "";
	fNonStringData.sint64_val = val;
    fIsStr = false;
    fIsSint64 = true;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}


TJsonType::TJsonType(Sint32 val){
    fStringData = "";
    fNonStringData.sint32_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = true;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(Sint16 val){
    fStringData = "";
    fNonStringData.sint16_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = true;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(Sint8 val){
    fStringData = "";
    fNonStringData.sint8_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = true;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

#ifndef _LINUX
TJsonType::TJsonType(long val){
    fStringData = "";
    fNonStringData.sint64_val = (Sint64)val;
    fIsStr = false;
    fIsSint64 = true;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}
#endif

TJsonType::TJsonType(Uint64 val){
    fStringData = "";
    fNonStringData.uint64_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = true;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(Uint32 val){
    fStringData = "";
    fNonStringData.uint32_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = true;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(Uint16 val){
    fStringData = "";
    fNonStringData.uint16_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = true;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(Uint8 val){
    fStringData = "";
    fNonStringData.uint8_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = true;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}

#ifndef _LINUX
TJsonType::TJsonType(unsigned long val){
    fStringData = "";
    fNonStringData.uint64_val = (Uint64)val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = true;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = false;
}
#endif

TJsonType::TJsonType(double val){
    fStringData = "";
    fNonStringData.double_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = true;
    fIsBool = false;
    fIsNull = false;
}

TJsonType::TJsonType(bool val){
    fStringData = "";
    fNonStringData.bool_val = val;
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = true;
    fIsNull = false;
}

TJsonType::TJsonType(std::nullptr_t val){
    fStringData = "";
    fIsStr = false;
    fIsSint64 = false;
    fIsSint32 = false;
    fIsSint16 = false;
    fIsSint8 = false;
    fIsUint64 = false;
    fIsUint32 = false;
    fIsUint16 = false;
    fIsUint8 = false;
    fIsDouble = false;
    fIsBool = false;
    fIsNull = true;
}

TJsonType::~TJsonType(){
}

//Returns a TXString already escaped to be printed out to JSON.
//Characters need to be escaped to fit the JSON format
TXString TJsonType::GetJsonFormattedValue(){
    TXString jsonFormattedValue = "\"\""; //Default to a blank string
    if(fIsNull){
        jsonFormattedValue = "null";
    }
    else if(fIsBool){
		bool dataValue = fNonStringData.bool_val;
        jsonFormattedValue = (dataValue) ? "true" : "false";
    }
    else if(fIsDouble){
		double dataValue = fNonStringData.double_val;
		jsonFormattedValue = TXString::ToStringReal(dataValue);
    }
    else if(fIsSint64){
        Sint64 dataValue = fNonStringData.sint64_val;
        jsonFormattedValue = TXString::ToStringInt(dataValue);
    }
    else if(fIsSint32){
        Sint32 dataValue = fNonStringData.sint32_val;
		jsonFormattedValue = TXString::ToStringInt(dataValue);
    }
    else if(fIsSint16){
        Sint16 dataValue = fNonStringData.sint16_val;
        jsonFormattedValue.Format("%d", dataValue);
    }
    else if(fIsSint8){
        Sint8 dataValue = fNonStringData.sint8_val;
        jsonFormattedValue.Format("%d", dataValue);
    }
    else if(fIsUint64){
        Uint64 dataValue = fNonStringData.uint64_val;
        jsonFormattedValue.Format("%lu", dataValue);
    }
    else if(fIsUint32){
        Uint32 dataValue = fNonStringData.uint32_val;
        jsonFormattedValue.Format("%u", dataValue);
    }
    else if(fIsUint16){
        Uint16 dataValue = fNonStringData.uint16_val;
        jsonFormattedValue.Format("%u", dataValue);
    }
    else if(fIsUint8){
        Uint8 dataValue = fNonStringData.uint8_val;
        jsonFormattedValue.Format("%u", dataValue);
    }
    else if(fIsStr){
        jsonFormattedValue = this->GetJsonFormattedString();
    }
    return jsonFormattedValue;
}

// Need to verify all json escape characters are escaped correctly.
TXString TJsonType::GetJsonFormattedString(){
    TXString jsonStringOriginal = fStringData;
    jsonStringOriginal.Replace("\\", "\\\\");
    jsonStringOriginal.Replace("\n", "\\t");
    jsonStringOriginal.Replace("\b", "\\b");
    jsonStringOriginal.Replace("\f", "\\f");
    jsonStringOriginal.Replace("\r", "\\r");
    jsonStringOriginal.Replace("\t", "\\t");
    jsonStringOriginal.Replace("\"", "\\\"");
    TXString jsonString = "";
    jsonString += "\"";
    jsonString += jsonStringOriginal;
    jsonString += "\"";
    return jsonString;
}

TJsonKeyPair CreateJsonKeyPair(TXString key, TJsonType value){
	TJsonKeyPair keyPair(key, value);
	return keyPair;
}

#ifdef _MINICAD_
const TXString noLogTagPlaceholder = txu("\"sn\":\"\"");
TXString ReplaceSerialNumberToLog(TXString logEntry){
    //If N/A is not even in the log just return
    if(logEntry.Find(noLogTagPlaceholder) == -1){
        return logEntry;
    }
    
    TXString sn = TAppProtection::MaskSerialNumber(TAppProtection::GetCurrentSerialNumber(), true);
    TXString buffer;
    buffer += txu("\"sn\":\"");
    buffer += sn;
    buffer += txu("\"");
    logEntry.Replace(noLogTagPlaceholder, buffer);
    return logEntry;
}

template<typename T>
T addToAtomic(std::atomic<T> *obj, T arg) {
	T expected = obj->load();
	while (!atomic_compare_exchange_weak(obj, &expected, expected + arg))
		;
	return expected;
}

typedef std::vector<std::pair<Uint16, TXString> > TLogBufferList;
/*
 TApplicationLogger is a singleton that controls the logging variables as well as the logging file.
 */
class TApplicationLogger : public TSingleton<TApplicationLogger>
{
public:
	~TApplicationLogger();
	void SendToLogFile(Uint16 level, TXString message);
	void CloseLog();
	bool IsLoggingInitialized();
	void SetLoggingInitialized(bool initialized);
	bool IsLoggingBuffering();
	void SetLogBuffering(bool isBuffering);
	Uint16 GetLoggingLevel();
	void SetLoggingLevel(Uint16 level);
    double GetLoggingTime();
protected:
	friend class TSingleton<TApplicationLogger>;
	TApplicationLogger();
private:
	FILE* fLogFile;
    TMutex fLogFileGuard;
	bool fIsLoggingInitialized;
	std::atomic<bool> fAreLogsBuffering;
	std::atomic<bool> fIsBufferFlushed;
	TLogBufferList fLogBuffer;
	std::atomic<Uint16> fLoggingLevel;
	std::atomic<double> fLoggingTime;
	void SendToLogBuffer(Uint16 level, TXString message);
	void WriteToLogFile(Uint16 level, TXString message);
	void FlushLogBuffer();
};

TApplicationLogger::TApplicationLogger(){
	fLogFile = NULL;
	fIsLoggingInitialized = false;
	fAreLogsBuffering.store(true);
	fLoggingLevel.store(kDefaultLoggingLevel);
	fLoggingTime.store(0.0);
	fIsBufferFlushed.store(false);
}

TApplicationLogger::~TApplicationLogger(){
	CloseLog();
    /*
	if(!fIsBufferFlushed.load()){
		FlushLogBuffer();
	}
	CloseLog();
     */
}

void TApplicationLogger::CloseLog(){
    TMutex::TAutoLock autoLock(&fLogFileGuard);
	if(fLogFile){
		fclose(fLogFile);
		fLogFile = NULL;
	}
}

//Buffers Log/writes message to disk regardless of level. Level is checked when writing buffer (Once we load current logging level setting)
void TApplicationLogger::SendToLogFile(Uint16 level, TXString message){
	if(fAreLogsBuffering.load()){
		SendToLogBuffer(level, message);
	}
	else{
		if(!fIsBufferFlushed.exchange(true)){
			FlushLogBuffer();
		}
		WriteToLogFile(level, message);
	}
}

bool TApplicationLogger::IsLoggingInitialized(){
	return fIsLoggingInitialized;
}

void TApplicationLogger::SetLoggingInitialized(bool initialized){
	fIsLoggingInitialized = initialized;
}

bool TApplicationLogger::IsLoggingBuffering(){
	return fAreLogsBuffering.load();
}

void TApplicationLogger::SetLogBuffering(bool isBuffering){
	//If we are setting to false be sure to close the log first
    fAreLogsBuffering.store(isBuffering);
    /*
	bool originalValue = fAreLogsBuffering.exchange(isBuffering);
	if(isBuffering){
		if(!originalValue){
			CloseLog();
			fIsBufferFlushed.store(false); //Set to false since they will need to be flushed once bufferings over
		}
	}
     */
}

double TApplicationLogger::GetLoggingTime(){
	return fLoggingTime.load();
}

Uint16 TApplicationLogger::GetLoggingLevel(){
	return fLoggingLevel.load();
}

void TApplicationLogger::SetLoggingLevel(Uint16 level){
#if GS_BETA_PROGRAM_SUPPORT
    fLoggingLevel.store(kDefaultLoggingLevel);
#else
	fLoggingLevel.store(level);
#endif
}

void TApplicationLogger::SendToLogBuffer(Uint16 level, TXString message){
	fLogBuffer.push_back(std::make_pair(level, message));
}

void TApplicationLogger::FlushLogBuffer(){
	if(fLogBuffer.size() > 0){
		for(Uint32 i=0; i < fLogBuffer.size(); i++)
		{
			if (fLogBuffer[i].first <= fLoggingLevel) {
				//Process each log to add the S/N as it is now avaliable
				TXString newLogLine = ReplaceSerialNumberToLog(fLogBuffer[i].second);
				WriteToLogFile(fLogBuffer[i].first, newLogLine);
			}
		}
		fLogBuffer.clear();
	}
	fIsBufferFlushed.store(true);
}

void TApplicationLogger::WriteToLogFile(Uint16 level, TXString message){
	if(level <= fLoggingLevel.load()){
		TMutex::TAutoLock autoLock(&fLogFileGuard);
		double startTime = ::GetSecondsSinceLaunch();
		if(!fLogFile){
			TFolderIdentifier logFolder;
				if ( GetAppDataFolder(logFolder) ) {
					TFileIdentifier logFile(logFolder, kUserLogFileName);
					#if GS_MAC
					fLogFile = fopen((const char*) logFile.GetPosixFilePath(), "a+");
					#else
					fLogFile = _wfopen(logFile.GetFilePath().GetData(), L"a+");
					#endif
				}
		}
        if(fLogFile) {
            fprintf(fLogFile, "%s", (const char*) message);
            CloseLog();
        }
		double endTime = ::GetSecondsSinceLaunch();
		addToAtomic<double>(&fLoggingTime, (endTime - startTime));
	}
}

double LocalLog_GetLoggingTime(){
	return TApplicationLogger::Instance().GetLoggingTime();
}

void LocalLog_SetLoggingInitialized(bool isInitialized){
	TApplicationLogger::Instance().SetLoggingInitialized(isInitialized);
}

void LocalLog_SetLogBuffering(bool isBuffering){
	TApplicationLogger::Instance().SetLogBuffering(isBuffering);
}

Uint16 LocalLog_GetLoggingLevel(){
	return TApplicationLogger::Instance().GetLoggingLevel();
}

void LocalLog_SetLoggingLevel(Uint16 level){
#if GS_BETA_PROGRAM_SUPPORT
	TApplicationLogger::Instance().SetLoggingLevel(kDefaultLoggingLevel);
#else
	TApplicationLogger::Instance().SetLoggingLevel(level);
#endif
}
//----------------------------------------------
void CheckForBackgroundLogUpload(){
	//Every ~5 minutes spawn a thread. (It's approximiate because its the next log call after 5 minutes.
    //If TErrorReporting is disabled once it is enabled the next staging will flush all of those logs
    //And upload them ALL in the background once it is enabled.
    if (TErrorReporting::Instance().IsEnabled() && !TErrorReporting::Instance().IsUploadInProgress() && TErrorReporting::Instance().IsLaunchUploadComplete()
        && TErrorReporting::Instance().IsTimeForBackgroundUpload()){
        //Prep logs to be uploaded in background
        //Copy them over to a staging file
        //Start thread to upload in background
		TApplicationLogger::Instance().CloseLog(); //Close the log file as staging will not occur
        TErrorReporting::Instance().BeginThreadedLogUpload();
    }
}

#define JSON_TXESCAPE(str)	"\"" + str + "\""
#define JSON_KEY_PAIR(msg, key, val)	msg << "\"";\
                                        msg << txu(key);\
                                        msg << "\"";\
										msg << ":";\
										msg << val;
#if GS_MAC
const TXString kLocalLogOSName = txu("MAC");
#else
const TXString kLocalLogOSName = txu("WIN");
#endif
const TXString kLocalLogOSNameJSON = JSON_TXESCAPE(kLocalLogOSName);

#define JSON_KEY_PAIR_CONT(msg, key, val)	JSON_KEY_PAIR(msg,key,val);\
											msg << ",";
//Takes the description of the event and returns a JSON object of it
//To allow easier parsing for analysis
//Also escapes all forward slashes so it is able to be parsed correctly.
TXString CreateJsonLogEvent(TXString description){
    if(description.GetLength() < 1)
        return description;
    //Special Case for OpenGL driver
    //Its message is json so just return it
    if(description[0] == '{'){
        description.Replace("{", " ");
        description.Replace("}", " ");
        return description;
    }
	description.Replace("\\", "\\\\");
    description.Replace("\"", "\\\"");
	ptrdiff_t categoryIndex = description.Find(": ");
	TXString jsonLog;
    TXString category;
	if(categoryIndex != -1){
		category = description.Left(categoryIndex);
	}
	else{
		categoryIndex = description.Find(' ');
        if(categoryIndex != -1){
            category = description.Left(categoryIndex);
        }
        else{
            category = txu("no_cat");
        }
	}
	JSON_KEY_PAIR_CONT(jsonLog, "cat", JSON_TXESCAPE(category));
	JSON_KEY_PAIR(jsonLog, "message", JSON_TXESCAPE(description));
	return jsonLog;
}

TXString SearchForLogType(const TXString& jsonDescription){
	TXString logType = txu("INFO");
	if(jsonDescription.Find("\"type\"", 0 , true) == -1){
		if(jsonDescription.Find("error", 0, true) != -1 && jsonDescription.Find("ferror", 0, true) == -1)
			logType = txu("ERROR");
		if(jsonDescription.Find("fail", 0, true) != -1)
			logType = txu("ERROR");
		if(jsonDescription.Find("exception", 0, true) != -1)
			logType = txu("ERROR");
		if(jsonDescription.Find("failure", 0, true) != -1)
			logType = txu("ERROR");
		if(jsonDescription.Find("warn", 0, true) != -1)
			logType = txu("WARN");
		if(jsonDescription.Find("warning", 0, true) != -1)
			logType = txu("WARN");
	}
	else{
		logType = txu("");
	}
	return logType;
}

TXString ParseJsonLogDataMap(const TJsonLogDataMap& logFields){
	TJsonLogDataMap::const_iterator mapIterator;
	TXString logMessageFields = "";
	for(mapIterator = logFields.begin(); mapIterator != logFields.end(); mapIterator++){
		TXString key = mapIterator->first;
		TJsonType second = mapIterator->second;
		TXString value = second.GetJsonFormattedValue();
		logMessageFields << "\"" << key << "\":" << value;
		if(std::next(mapIterator) != logFields.end()){
			logMessageFields << ",";
		}
	}
	return logMessageFields;
}

TXString CreateFormattedLogMessage(const Uint16& level, const TXString& message){
	time_t theTime;
    char dateBuffer[255];
    time(&theTime);
    tm* tp = gmtime(&theTime);
    strftime(dateBuffer, 255, "%m/%d/%Y %H:%M:%S", tp);
	TXString dateStr;
	dateStr << dateBuffer;
	dateStr << txu(" ");
	dateStr << ::GetSecondsSinceLaunch();
	dateStr << txu(" +0000");
    //Serial Number will be N/A when serial number isn't avaliable during startup.
    //It will be replaced once the buffer is written to disk
    TXString serialNumberStr = TAppProtection::MaskSerialNumber(TAppProtection::GetCurrentSerialNumber());
    TVersionNumber versNum;
	static const TXString osJSON = JSON_TXESCAPE(GetUniformOSSystemVersion(false));
	static const TXString sessionJSON = JSON_TXESCAPE(TXString::ToStringHex(static_cast<long long>(::GetTimeAtLaunch()), false));
	static const TXString vwVersionJSON = JSON_TXESCAPE(GetVersionNumberString(eShortWithBuild));

	TXString logMessage;
	logMessage << "{";
	JSON_KEY_PAIR_CONT(logMessage, "ts", JSON_TXESCAPE(dateStr));
	JSON_KEY_PAIR_CONT(logMessage, "log_lvl", (Uint32)level);
	JSON_KEY_PAIR_CONT(logMessage, "sn", JSON_TXESCAPE(serialNumberStr));
	JSON_KEY_PAIR_CONT(logMessage, "session", sessionJSON);
	JSON_KEY_PAIR_CONT(logMessage, "vw_ver", vwVersionJSON);
	JSON_KEY_PAIR_CONT(logMessage, "platform", kLocalLogOSNameJSON);
	JSON_KEY_PAIR_CONT(logMessage, "os_ver", osJSON);
	logMessage << message;
	logMessage << "}\n";

    return logMessage;
}

void LLLocalLogStrCore(Uint16 level, bool doDebugWindow, const char *description)
{
	// we do not want to respond to log requests at early init time
	if (TApplicationLogger::Instance().IsLoggingInitialized()) {

		// levelzero is defined to output nothing to the log

		// 1-3 should happen on a session frequency
		// 4-6 can happen on a per-user-event frequency
		// 7-10 can happen up to once every few seconds on average
		// > 10 are special purpose and should not be used without
		// prior arrangement - Paul

		ASSERTN(kPaul, level > 0);

		//Check if we're going to write this log before parsing it into a JSON string.
		if (TApplicationLogger::Instance().IsLoggingBuffering() || level <= TApplicationLogger::Instance().GetLoggingLevel()) {
			TXString jsonDescription = CreateJsonLogEvent(description);
            TXString type = SearchForLogType(jsonDescription);
			TXString logMessageFields = "";
			if(type.GetLength() != 0){
				JSON_KEY_PAIR_CONT(logMessageFields, "type", JSON_TXESCAPE(type));
			}
			logMessageFields << jsonDescription;
			TXString logMessage = CreateFormattedLogMessage(level, logMessageFields);
			TApplicationLogger::Instance().SendToLogFile(level, logMessage);

			if (doDebugWindow) {
				#if !DaveD	// Too much noise in the debug window from resource lists.  -DLD 1/12/2012
					// send to the debug window - in future need to pass time and process also
					DMSG((kEveryone, "%s\n", description));
				#endif	// !DaveD
			}

            CheckForBackgroundLogUpload();
		}
	}
}

void WriteLocalLog(Uint16 level, const TJsonLogDataMap& logFields){
	if (TApplicationLogger::Instance().IsLoggingInitialized()) {
        ASSERTN(kOKadry, level > 0);
		if (TApplicationLogger::Instance().IsLoggingBuffering() || level <= TApplicationLogger::Instance().GetLoggingLevel()) {
			TXString logMessageFields = ParseJsonLogDataMap(logFields);
            TXString logMessage = CreateFormattedLogMessage(level, logMessageFields);
    
			TApplicationLogger::Instance().SendToLogFile(level, logMessage);

            CheckForBackgroundLogUpload();
        }
    }
}
#endif


static void LLLocalLogStr(Uint16 level, bool doDebugWindow, const char *description)
{

#ifdef _MINICAD_
		// the VCOM interface is not yet registered
		// use default in-place implementation

		LLLocalLogStrCore(level, doDebugWindow, description);

#else
	using namespace VectorWorks::Debug;
	::GS_InitializeVCOM( gCBP );
	VCOMPtr<IDebugOutputLog> pOutInst( IID_DebugOutputLog );

	if ( pOutInst ) {
		pOutInst->LocalLogStr(level, doDebugWindow, description);
	}
	else {
		// remove log being called before VCOM initialization
		ASSERTN( kVStanev, false );
	}
#endif

}




void LocalLogStr(Uint16 level, const char *description)
{
	LLLocalLogStr(level, true, description);
}

void LocalLogStrTight(Uint16 level, const char *description)
{
	LLLocalLogStr(level, false, description);
}

Sint32 LLLocalLog(Uint16 level, bool doDebugWindow, const char *format, va_list ap)
//
//	Log to local file.  Accept variable arguments.
//	This is similar to the function _Log( ) above.
//	JAK 1/31/05
//
{
	const size_t kBuf_size = 1024;

	static Sint32 r = 0;
	char buf[kBuf_size];
#if GS_MAC
	r = vsnprintf(buf, sizeof(buf), format, ap);
    // result is negative on error, or >= size on truncation.
    if (r >= sizeof(buf))
    {
        // for truncation, adjust return value.
        r = sizeof(buf) - 1;
    }
#elif GS_LIN
	r = vsnprintf(buf, sizeof(buf), format, ap);
    // result is negative on error, or >= size on truncation.
    if (r >= sizeof(buf))
    {
        // for truncation, adjust return value.
        r = sizeof(buf) - 1;
    }
#else
    errno = 0;
    r = _vsnprintf_s(buf, sizeof(buf), _TRUNCATE, format, ap);
    // result is -1 on error or truncation
    if ((r == -1 && errno == 0) || r >= sizeof(buf))
    {
        // for truncation, adjust return value. for exact length, need to fix null termination.
        r = sizeof(buf) - 1;
        buf[r] = 0;
    }
#endif
    if (r > 0)  // nothing to do with an empty string/erronous result
        LLLocalLogStr(level, doDebugWindow, buf);
	return r;
}


//Route depending on if this is called from the main application or an SDK plugin
void RouteLocalLog(Uint16 level, const TJsonLogDataMap& logFields){
#ifdef _MINICAD_
    WriteLocalLog(level, logFields);
#else
	using namespace VectorWorks::Debug;
	::GS_InitializeVCOM( gCBP );
	VCOMPtr<IDebugOutputLog> pOutInst( IID_DebugOutputLog );

	if ( pOutInst ) {
		pOutInst->SendToLogWriter(level, logFields);
	}
	else {
		// remove log being called before VCOM initialization
		ASSERTN( kVStanev, false );
	}
#endif
}

TXString GetLogType(Uint16 logType){
    TXString typeStr = "INFO";
    if(logType == kErrorLog){
        typeStr = "ERROR";
    }
    else if(logType == kWarnLog){
        typeStr = "WARN";
    }
    return typeStr;
}

Sint32 LocalLog(Uint16 level, const char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	Sint32 result = LLLocalLog(level, true, format, ap);
	va_end(ap);

	return result;
}

void LocalLog(Uint16 level, Uint16 type, const TXString& cat, const TXString& message){
	TJsonLogDataMap logFields;
    logFields.insert(KEYPAIR("cat", cat));
    logFields.insert(KEYPAIR("type", GetLogType(type)));
    logFields.insert(KEYPAIR("message", message));
	DMSG((kEveryone, "%s\n", (const char*)message));
    RouteLocalLog(level, logFields);
}

//=======================================================================================
// VFormat(...) is used in Format(...). Note the buffer size is 1024.
static void _VFormat(TXString& outString, const char* format, va_list argPtr)
{
	static const Sint32 kBufferSize = 1024;
	char localBuffer[kBufferSize];

	Sint32 len = vsnprintf(localBuffer, kBufferSize, (const char *)format, argPtr);

	ASSERTN(kPChang, len >= 0 && len < kBufferSize);

	if (len >= 0)
		outString = localBuffer;
	else
		outString.Clear();
}

void LocalLog(Uint16 level, Uint16 type, const TXString& cat, const char* format, ...){
    va_list ap;
    va_start (ap, format);
    TXString formattedMessage;
    ::_VFormat(formattedMessage, format, ap);
    va_end(ap);
	LocalLog(level, type, cat, formattedMessage);
}

void LocalLog(Uint16 level, Uint16 type, const TXString& cat,
                TJsonLogDataMap logFields){
    logFields.insert(KEYPAIR("cat", cat));
    logFields.insert(KEYPAIR("type", GetLogType(type)));
    RouteLocalLog(level, logFields);
}

void LocalLog(const TLogEnum& logEnum, const TXString& message){
	LocalLog(logEnum.GetLevel(), logEnum.GetType(), logEnum.GetCategory(), message);
}

void LocalLog(const TLogEnum& logEnum, const char* format, ...){
	va_list ap;
    va_start (ap, format);
    TXString formattedMessage;
    ::_VFormat(formattedMessage, format, ap);
    va_end(ap);
	LocalLog(logEnum.GetLevel(), logEnum.GetType(), logEnum.GetCategory(), formattedMessage);

}

void LocalLog(const TLogEnum& logEnum, const TJsonLogDataMap customData){
	LocalLog(logEnum.GetLevel(), logEnum.GetType(), logEnum.GetCategory(), customData);
}

Sint32 LocalLogTight(Uint16 level, const char *format, ...)
{
	va_list	ap;
	va_start(ap, format);
	Sint32 result = LLLocalLog(level, false, format, ap);
	va_end(ap);

	return result;
}

Sint32 LocalLogTiming(Uint16 level, double timing, const char *format, ...)
{
	const size_t kBuf_size = 1124;

	va_list	ap;
	va_start(ap, format);

	char modifiedFormat[kBuf_size];
	sprintf(modifiedFormat, "TIMER: %f sec | %s", timing, format);

	Sint32 result = LLLocalLog(level, true, modifiedFormat, ap);
	va_end(ap);

	return result;
}

void LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat,
                      const TXString& message){
    TJsonLogDataMap logFields;
    logFields.insert(KEYPAIR("cat", cat));
    logFields.insert(KEYPAIR("type", GetLogType(type)));
    logFields.insert(KEYPAIR("timing", timing));
    logFields.insert(KEYPAIR("message", message));
	DMSG((kEveryone, "TIMER: %f sec | %s\n", timing, (const char*)message));
    RouteLocalLog(level, logFields);
}

void LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat,
                      const char* format, ...){
    va_list ap;
    va_start (ap, format);
    TXString formattedMessage;
    ::_VFormat(formattedMessage, format, ap);
    va_end(ap);
	LocalLogTiming(level, type, timing, cat, formattedMessage);
}

void LocalLogTiming(Uint16 level, Uint16 type, double timing, const TXString& cat,
                     TJsonLogDataMap logFields){
    logFields.insert(KEYPAIR("cat", cat));
    logFields.insert(KEYPAIR("type", GetLogType(type)));
    logFields.insert(KEYPAIR("timing", timing));
    RouteLocalLog(level, logFields);
}

void LocalLogTiming(const TLogEnum& logEnum, double timing, const TXString& message){
	LocalLogTiming(logEnum.GetLevel(), logEnum.GetType(), timing, logEnum.GetCategory(), message);
}

void LocalLogTiming(const TLogEnum& logEnum, double timing, const char* format, ...){
	va_list ap;
    va_start (ap, format);
    TXString formattedMessage;
    ::_VFormat(formattedMessage, format, ap);
    va_end(ap);
	LocalLogTiming(logEnum.GetLevel(), logEnum.GetType(), timing, logEnum.GetCategory(), formattedMessage);
}

void LocalLogTiming(const TLogEnum& logEnum, double timing, TJsonLogDataMap customData){
	LocalLogTiming(logEnum.GetLevel(), logEnum.GetType(), timing, logEnum.GetCategory(), customData);
}
