//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFileIdentifier.h"

namespace VectorworksMVR
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		enum ELineEndType
		{
			eLineEndType_Mac,
			eLineEndType_Win,
			eLineEndType_Unix,
			eLineEndType_Native,
		};

		// ----------------------------------------------------------------------------------------------------
		class IStdFileProgressListener
		{
		public:
			virtual						~IStdFileProgressListener()			{}

			virtual void VCOM_CALLTYPE	OnStdFileProgress(Uint64 position, Uint64 bytesCnt) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {B88D157C-3796-11DB-9C35-00508D5E9851}
		static const VWIID IID_StdFile = { 0xB88D157C, 0x3796, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };

		class DYNAMIC_ATTRIBUTE IStdFile : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	OpenRead(IFileIdentifier* pFileID, bool bRandomAccess) = 0;
			virtual VCOMError VCOM_CALLTYPE	OpenReadWrite(IFileIdentifier* pFileID, bool bRandomAccess, bool bTruncateExisting) = 0;
			virtual VCOMError VCOM_CALLTYPE	OpenNewWrite(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	Close() = 0;
			virtual VCOMError VCOM_CALLTYPE	SetProgressListener(IStdFileProgressListener* pListener) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileSize(Uint64& outSize) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetPosition(Uint64& outPosition) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetPosition(Uint64 position) = 0;
			virtual VCOMError VCOM_CALLTYPE	SeekForward(Uint64 offset) = 0;
			virtual VCOMError VCOM_CALLTYPE	SeekBackward(Uint64 offset) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetBytesLeft(Uint64& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	IsAtEndOfFile(bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Uint64& inoutBytes, void* pBuffer) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Uint64 bytes, const void* pBuffer) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Sint64& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Sint64 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Uint64& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Uint64 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Sint32& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Sint32 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Uint32& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Uint32 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Sint16& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Sint16 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Uint16& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Uint16 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Sint8& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Sint8 value) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Uint8& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Uint8 value) = 0;

			virtual VCOMError VCOM_CALLTYPE	SetDefaultNewLine(ELineEndType type) = 0;
			virtual VCOMError VCOM_CALLTYPE	ReadBOM(ETXEncoding& encoding) = 0;

			// UTF-8 encoding
			virtual VCOMError VCOM_CALLTYPE	WriteUTF8Marker() = 0;

			virtual VCOMError VCOM_CALLTYPE	Read(TXString& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(TXString& outValue, size_t len) = 0;
			virtual VCOMError VCOM_CALLTYPE	ReadStringLine(TXString& outLine) = 0;

			virtual VCOMError VCOM_CALLTYPE	Write(const TXString& value, bool bIncludeZero) = 0;
			virtual VCOMError VCOM_CALLTYPE	WriteStringLine(const TXString& line) = 0;

			virtual VCOMError VCOM_CALLTYPE	WriteNewLine() = 0;
			virtual VCOMError VCOM_CALLTYPE	WriteNewLine(ELineEndType type) = 0;

			// UTF-16 encoding
			virtual VCOMError VCOM_CALLTYPE	WriteUTF16Marker() = 0;

			virtual VCOMError VCOM_CALLTYPE	ReadUTF16(TXString& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	ReadUTF16(TXString& outValue, size_t len) = 0;
			virtual VCOMError VCOM_CALLTYPE	ReadStringLineUTF16(TXString& outLine) = 0;

			virtual VCOMError VCOM_CALLTYPE	WriteUTF16(const TXString& value, bool bIncludeZero) = 0;
			virtual VCOMError VCOM_CALLTYPE	WriteStringLineUTF16(const TXString& line) = 0;

			virtual VCOMError VCOM_CALLTYPE	WriteNewLineUTF16() = 0;
			virtual VCOMError VCOM_CALLTYPE	WriteNewLineUTF16(ELineEndType type) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IStdFile>		IStdFilePtr;
	}
}