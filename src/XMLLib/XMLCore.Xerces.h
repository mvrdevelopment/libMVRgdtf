// XMLCore.Xerces.h
#pragma once

#ifndef XMLCore_h
#define XMLCore_h

XERCES_CPP_NAMESPACE_USE


namespace XML
{
	using namespace VectorWorks::Filing;
	using namespace VectorWorks::Scripting;

	// ------------------------------------------------------------------------------------------------------
	// Error constants
	const short kNoError				=  0;
	const short kUnknownError			= -1;
	const short kInvalidPath			= -2;	// I.e., XML path, not file path
	const short kElementNotFound		= -3;
	const short kAttributeNotFound		= -4;
	const short kCDATASectionNotFound	= -5;
	const short kMemoryError			= -20;
	const short	kInvalidXMLHandle		= -21;
	const short	kInvalidParameters		= -22;
	const short kParserError			= -23;	// From Xerces
	const short kNoChildOrSiblingNodes	= -24;	// Node has no children, or succeeding or preceding sibling

	// errors -30 - -60 are reserved for DOM errors
	// errors -1000 - -2000 are reserved for XML errors

	// ------------------------------------------------------------------------------------------------------
	typedef DOMImplementation *		DOMImplementationPtr;
	typedef	XercesDOMParser *		XercesDOMParserPtr;
	typedef	DOMErrorHandler *		DOMErrorHandlerPtr;
	typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument * DOMDocumentPtr;
	typedef DOMElement *			DOMElementPtr;
	typedef DOMNode *				DOMNodePtr;
	typedef	DOMAttr *				DOMAttrPtr;

	/////////////////////////////////////////////////////////////////////////////

	class DOMData
	{
		public:
			DOMData();

			void Initialize(void);
			short ReleaseXML(void);
			short CreateNewXMLDocument(const TXString& rootElementName);
			short ReadXMLFile(short whichPath, const TXString& fileName);
			short ReadXMLMemory(const TXString& xmlData);
			short WriteXMLFile(short whichPath, const TXString& fileName);
			short WriteXMLMemory(TXString& outXmlData);
			short GetElementValue(const TXString& elementPath, TXString& value);
			short SetElementValue(const TXString& elementPath, const TXString& value);
			short DeleteElement(const TXString& elementPath);
			short GetFirstChild(const TXString& elementPath, TXString& childName);
			short GetNextElement(const TXString& elementPath, TXString& nextElementName);
			short GetPreviousElement(const TXString& elementPath, TXString& nextElementName);
			short SearchForElement(const TXString& elementPath, const TXString& searchElement, TXString& foundPath);
			short GetAttributeValue(const TXString& element, const TXString& attribute, TXString& value);
			short SetAttributeValue(const TXString& elementPath, const TXString& attribute, const TXString& value);
			short DeleteAttribute(const TXString& elementPath, const TXString& attribute);
			short SearchForAttribute(const TXString& startElementPath, const TXString& searchAttribute,
									 TXString& foundPath, TXString& attributeValue);
			short GetCDATA(const TXString& elementPath, TXString& outData);
			short SetCDATA(const TXString& elementPath, const TXString& data);
			short DeleteCDATA(const TXString& elementPath);

		// tools
		public:
			static TXString GetFullPath(short whichPath, const TXString& filename, bool inCreateIfMissing = false);

		protected:
			bool					m_bDocLoaded;
			DOMImplementationPtr	m_pImpl;
			XercesDOMParserPtr		m_pXercesDOMParser;		// Pointer to Xerces DOM parser structure
			DOMErrorHandlerPtr		m_pErrorHandler;		// Pointer to error handler structure
			DOMDocumentPtr			m_plDomDocument;
			DOMElementPtr			m_pDocRoot;
			DOMNodePtr				m_pCurNode;
			int						m_pSkipCount;
			int						m_pCurSkipCount;

			DOMNodePtr FindElementSearch(DOMNodePtr pStartNode, const TXString& element);
			DOMNodePtr FindElement(DOMNodePtr pStartNode, const TXString& element, int skip = 0);
			DOMNodePtr FindAttributeSearch(DOMNodePtr pStartNode, const TXString& attribute, TXString& value);
			int FindChild(DOMNodePtr pParent, const TXString& element, DOMNodePtr& pFoundChild, int skip = 1);
			TXString GetDelimitedString(const TXString& str, TXString& delimitedStr, const TXString& beginDelimiter, const TXString& endDelimiter);
			short ParsePath(const TXString& nodePathStr, DOMNodePtr& pFoundNode, bool bCreate = false);
			bool ValidTag(const TXString& tag);
			DOMNodePtr GetTextNode(DOMNodePtr pNode);
			short CreatePath(DOMNodePtr pNode, TXString& path);
			short FindAttribute(const TXString& elementPath, const TXString& attribute, DOMNodePtr& pElement, DOMAttrPtr& pFoundAttr, bool bCreate = false);
			short FindCDATASection(const TXString& elementPath, DOMNodePtr& pFoundNode, bool bCreate);
	};

	/////////////////////////////////////////////////////////////////////////////

	class CXMLMemoryIOBuffer : public IXMLFileIOBuffer
	{
	public:
				CXMLMemoryIOBuffer();
		virtual ~CXMLMemoryIOBuffer();

	public:
		virtual	VCOMError VCOM_CALLTYPE	GetDataSize(size_t& outSize);
		virtual VCOMError VCOM_CALLTYPE	CopyDataInto(void* pBuffer, size_t bufferSize);
		virtual VCOMError VCOM_CALLTYPE	SetData(void* pBuffer, size_t bufferSize);

	public:
		TXString	fBuffer;
	};

	/////////////////////////////////////////////////////////////////////////////

	class CXMLSAXListener : public IXMLSAXListener
	{
	public:
					CXMLSAXListener(Sint32 nSAXID, void* callbackRef);
		virtual		~CXMLSAXListener();

		bool		IsReadyAndReportError() const;

	public:
		virtual void VCOM_CALLTYPE 	OnDocument(const bool isStart);
		virtual void VCOM_CALLTYPE 	OnNode(const bool isStart, const SXMLURI& uri, const TXString& name, IXMLSAXAttributes* attributes);
		virtual void VCOM_CALLTYPE 	OnNodeValue(const TXString&  value);

	private:
		IVectorScriptEnginePtr	fScriptEngine;
		Sint32					fSAXID;
		void*					fCallbackRef;
		TXString				fLastNodeName;
	};

	/////////////////////////////////////////////////////////////////////////////
	struct SAXData
	{
		IXMLSAXFilePtr			fSAXFile;
		CXMLMemoryIOBuffer		fMemoryBuffer;
	};

	/////////////////////////////////////////////////////////////////////////////

	struct SXMLData
	{
		 DOMData*			fDOMData;	// Pointer to DOMData structure
		 SAXData			fSAXData;
	};

	/////////////////////////////////////////////////////////////////////////////

	typedef std::map< Sint32 /* Context ID */, SXMLData>  TXMLDataMap;

	class DOMManager
	{
		public:
							DOMManager();
							~DOMManager();
			Sint32			InitXML();
			short			ReleaseXML(Sint32 nDOMID);
			DOMData*		GetDOMPtr(Sint32 nDOMID);		// Returns DOMData pointer to specified DOM context
			SAXData*		GetSAXPtr(Sint32 nSAXID);

		private:
			TXMLDataMap		fXMLDataMap;
			Sint32			fXMLDataMapNextID;
	};
}

#endif
