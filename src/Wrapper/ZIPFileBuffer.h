#pragma once

#include <cstdio>

namespace VectorworksMVR
{
	namespace Filing
	{

		class ZIPFileBuffer
		{
		public:
			ZIPFileBuffer();
			virtual	~ZIPFileBuffer();

		public:
			virtual VCOMError VCOM_CALLTYPE	Open(VectorworksMVR::Filing::IFileIdentifier* pFileID,  bool openForRead);
			virtual VCOMError VCOM_CALLTYPE	Close();
			virtual VCOMError VCOM_CALLTYPE	GetFileSize(Uint64& outValue);
			virtual VCOMError VCOM_CALLTYPE	Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer);
			virtual VCOMError VCOM_CALLTYPE	Write(Uint64 position, Uint64 size, const void* pBuffer);

		private:
			Uint8*						fpZIPFileBuffer;
			size_t						fZIPFileBufferSize;
			VCOMPtr<IFileIdentifier>	fpOpenedFileID;
			bool						fOpenForRead;

		};

	}
}