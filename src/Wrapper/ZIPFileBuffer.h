//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

namespace VectorworksMVR
{
	namespace Filing
	{

		class ZIPFileBuffer
		{
		public:
			ZIPFileBuffer();
			~ZIPFileBuffer();

		public:
			VCOMError	Open(VectorworksMVR::Filing::IFileIdentifier* pFileID,  bool openForRead);
			VCOMError	Open(const char* buffer, size_t length);
			VCOMError	Close();
			VCOMError	GetFileSize(Uint64& outValue);
			VCOMError 	Read(Uint64 position, Uint64& inoutSize, void* pOutBuffer);
			VCOMError 	Write(Uint64 position, Uint64 size, const void* pBuffer);
			VCOMError 	CleanBuffer();
			void 		Copy(char*& p, size_t& inLength);

		private:
			Uint8*						fpZIPFileBuffer;
			Uint64						fZIPFileBufferSize;
			Uint64						fAllocatedMemorySize;
			VCOMPtr<IFileIdentifier>	fpOpenedFileID;
			bool						fOpenForRead;

		};

	}
}