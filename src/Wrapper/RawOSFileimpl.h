#pragma once

#include <cstdio>

namespace VectorworksMVR
{
	namespace Filing
	{

		class CRawOSFileImpl : public VCOMImmediateImpl<VectorworksMVR::Filing::IRawOSFile>
		{
		public:
			CRawOSFileImpl();
			virtual	~CRawOSFileImpl();

		public:
			virtual VCOMError VCOM_CALLTYPE	Open(VectorworksMVR::Filing::IFileIdentifier* pFileID, bool bReadable, bool bWritable, bool bRandomAccess, bool bTruncateExisting);
			virtual VCOMError VCOM_CALLTYPE	Close();
			virtual VCOMError VCOM_CALLTYPE	GetFileSize(Uint64& outValue);
			virtual VCOMError VCOM_CALLTYPE	Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer);
			virtual VCOMError VCOM_CALLTYPE	Write(Uint64 position, Uint64 size, const void* pBuffer);

		private:
			std::FILE*	fTheFile;
		};

	}
}