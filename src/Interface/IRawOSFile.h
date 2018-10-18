//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		// {4F7F77DD-3796-11DB-9C35-00508D5E9851}
		static const VWIID IID_RawOSFile = { 0x4F7F77DD, 0x3796, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };

		class DYNAMIC_ATTRIBUTE IRawOSFile : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Open(IFileIdentifier* pFileID, bool bReadable, bool bWritable, bool bRandomAccess, bool bTruncateExisting) = 0;
			virtual VCOMError VCOM_CALLTYPE	Close() = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileSize(Uint64& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Uint64 position, Uint64 size, const void* pBuffer) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IRawOSFile>		IRawOSFilePtr;
	}
}