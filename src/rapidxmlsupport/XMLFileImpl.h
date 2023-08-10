//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2019 www.deersoft.de
//-----------------------------------------------------------------------------
#ifdef DONT_USE_XERCES_AS_XMLLIB

#pragma once
#include "Prefix/StdAfx.h"
#include "tinyxml2.h"

namespace VectorworksMVR
{
	namespace XML
	{
		using namespace VectorworksMVR::Filing;



		// ----------------------------------------------------------------------------------------------------
		class CXMLFileImpl : public IXMLFile
		{
			/*static*/ void Tokenize(const TXString& string, TXStringArray& outArray, const char* szTokens, size_t tokensLen, bool doStopTokenizeForSpecialCh /*= false*/, char stopStartCh /*= '\''*/);
		public:
			CXMLFileImpl();
			virtual			~CXMLFileImpl();

			// IXMLFile
		public:
			virtual VCOMError	VCOM_CALLTYPE	CreateNew(const TXString& rootName);
			virtual VCOMError	VCOM_CALLTYPE	ReadFile(IFileIdentifier* pFileID);
			virtual VCOMError	VCOM_CALLTYPE	ReadBuffer(IXMLFileIOBuffer* pInputBuffer, EXMLEncoding encoding);
			virtual VCOMError	VCOM_CALLTYPE	WriteFile(IFileIdentifier* pFileID, EXMLEncoding encoding);
			virtual VCOMError	VCOM_CALLTYPE	WriteBuffer(IXMLFileIOBuffer* pOutputBuffer, EXMLEncoding encoding);
			virtual VCOMError	VCOM_CALLTYPE	GetRootNode(IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetLastError(EXMLFileError& outError);
			virtual VCOMError	VCOM_CALLTYPE	SetFeature(EXMLFileFeature feature, bool bValue);

			virtual VCOMError 	VCOM_CALLTYPE 	GetSimpleNode(const TXString& nodePath, IXMLFileNode** ppOutNode);
			virtual VCOMError 	VCOM_CALLTYPE 	GetSimpleNode(IXMLFileNode* pRefNode, const TXString& nodePath, IXMLFileNode** ppOutNode);
			virtual VCOMError 	VCOM_CALLTYPE 	GetSimpleValue(const TXString& nodePath, TXString& outValue);
			virtual VCOMError 	VCOM_CALLTYPE 	GetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, TXString& outValue);
			virtual TXString  	VCOM_CALLTYPE	GetSimpleValue(const TXString& nodePath, const TXString& defaultValue);
			virtual TXString  	VCOM_CALLTYPE	GetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, const TXString& defaultValue);
			virtual VCOMError 	VCOM_CALLTYPE 	SetSimpleValue(const TXString& nodePath, const TXString& value);
			virtual VCOMError 	VCOM_CALLTYPE 	SetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, const TXString& value);
			virtual bool		VCOM_CALLTYPE	GetSimpleExist(const TXString& nodePath);							// check to see if exist -- for organizing loops more efficiently
			virtual bool		VCOM_CALLTYPE	GetSimpleExist(IXMLFileNode* pRefNode, const TXString& nodePath);	// check to see if exist

			
			virtual uint32_t	VCOM_CALLTYPE	AddRef();
			virtual uint32_t	VCOM_CALLTYPE	Release();
			private:
			uint32_t 				fRefCnt;
			tinyxml2::XMLDocument 	fDoc;

		};
	}
}
#endif