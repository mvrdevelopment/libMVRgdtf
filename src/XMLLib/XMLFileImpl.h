#ifndef DONT_USE_XERCES_AS_XMLLIB
#pragma once
#include "XercesSupport.h"



namespace VectorworksMVR
{
	namespace XML
	{
		using namespace VectorworksMVR::Filing;



		// ----------------------------------------------------------------------------------------------------
		class CXMLFileImpl : public VCOMImpl<IXMLFile>, DOMErrorHandler
		{
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

			// DOMErrorHandler
		public:
			bool							handleError(const DOMError& domError);
			void							resetErrors();

		public:
			static	char					GetPathDelimiter();
			static	char					GetArrayStartDelimiter();
			static	void					ConvertXMLError(XMLExcepts::Codes error);
			static	void					ConvertXMLError(DOMException::ExceptionCode error);
			static	VCOMError				GetLastError();
			static	void					SetLastError(VCOMError error);
			static	bool					IsNameXMLValid(const XMLCh* szString, size_t len);
			static	EXMLFileError			GetLastEXMLFileError();
		static void						Tokenize(const TXString& string, TXStringArray& outArray, const char* szTokens, size_t tokensLen, bool doStopTokenizeForSpecialCh = false, char stopStartCh = '\'');

		private:
			typedef EXMLFileError (*TWriteCallback)(void* pData, size_t dataSize, void* pEnv);
			void							WriteXML(TWriteCallback pCallback, EXMLEncoding encoding, void* pEnv);
			virtual VCOMError				DoSimpleNode(IXMLFileNode* pRefNode, const TXString& nodePath, IXMLFileNode** ppOutNode, TXString& outValue, bool doWrite);

		private:
			DOMImplementationPtr	fpImpl;

			XercesDOMParserPtr		fpXercesDOMParser;		// Pointer to Xerces DOM parser structure

			DOMDocumentPtr			fpDomDocument;
			DOMElementPtr			fpDocRoot;

			// features
			bool					fbDoFormatPrettyPrint;
			XMLCh					fTheNewLine[5];

		private:
			static VCOMError		fLastError;
		};
	}
}
#endif
