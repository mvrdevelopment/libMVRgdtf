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

		class DYNAMIC_ATTRIBUTE IZIPFileBuffer
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	Open(IFileIdentifier* pFileID, bool bReadable, bool bWritable, bool bRandomAccess, bool bTruncateExisting) = 0;
			virtual VCOMError VCOM_CALLTYPE	Close() = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFileSize(Uint64& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer) = 0;
			virtual VCOMError VCOM_CALLTYPE	Write(Uint64 position, Uint64 size, const void* pBuffer) = 0;
		};
		
	}
}