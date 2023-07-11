#ifndef DONT_USE_XERCES_AS_XMLLIB
// XMLCore.Xerces.cpp
// XML Core functions

#include "Prefix/StdAfx.h"

#include "XMLCore.Xerces.h"
#include "ErrorHandler.h"
#include "Wrapper/PluginResource.h"

using namespace VectorworksMVR::Filing;
using namespace std;
using namespace XML;

#if GS_WIN
	#define NNA_MAX_PATH_LEN MAX_PATH
#elif GS_MAC
	#include <sys/param.h>
	#define NNA_MAX_PATH_LEN MAXPATHLEN
#endif

#if GS_WIN
//xercesc::DOMDocument;
#endif

// Prototypes
short ConvertDOMErrorToVSError(short DOMErr);
short ConvertXMLErrorToVSError(short XMLErr);


// 4/4/06, JAG:
// Now that our plug-ins are built as Mach-O format on the Mac, the Xerces transcoding functions
// seem to work correctly.
// Using mbstows and wcstombs DO NOT work, so don't use these functions to transcode strings.


short ConvertDOMErrorToVSError(short DOMErr)
// Converts a DOM error to a VectorScript error code.
// DOM errors will map to -30 - -60 range.
{
	short	vsErr;

	if (DOMErr <= 30)
		vsErr = -1 * (DOMErr + 29);		// -30 = index size error
	else
		vsErr = -1;		// The DOM error should never be greater than 30

	return vsErr;
}


short ConvertXMLErrorToVSError(short XMLErr)
// Converts an XML error to a VectorScript error code.  XML error codes are
// less typical than DOM error codes, and probably indicate internal errors,
// rather than errors that the user caused.
// These errors will map to the -1000 - -2000 range.
{
	short	vsErr;

	if (XMLErr < 1000)
		vsErr = -1 * (XMLErr + 1000);	// -1000 = no error
	else
		vsErr = -1;		// The XML error should never be greater than 1000

	return vsErr;
}


// Constructor
DOMManager::DOMManager()
{
	// Initialize Xerces.  Only needs to be done once when the plug-in loads.
	try {
		XMLPlatformUtils::Initialize();
	}

	catch (const XMLException& ) {
		return;
	}

	fXMLDataMap.clear();
	fXMLDataMapNextID = 1;
}


// Destructor
DOMManager::~DOMManager()
{
	if (! fXMLDataMap.empty() ) {
		// The map is not empty - clear out the remaining elements
		TXMLDataMap::iterator  iter;

		for (iter = fXMLDataMap.begin(); iter != fXMLDataMap.end(); iter++) {
			SXMLData&	xmlData	= iter->second;

			DOMData*  pDOMObj = xmlData.fDOMData;
			if ( pDOMObj ) {

				pDOMObj->ReleaseXML();
				delete pDOMObj;
			}
		}
	}

	fXMLDataMap.clear();

	// Release Xerces
	try {
		XMLPlatformUtils::Terminate();
	}

	catch (const XMLException& ) {
	}
}


Sint32 DOMManager::InitXML()
// Initializes a DOM context.  Returns an ID for this context.
{
	// Allocate DOM structure
	DOMData*	pDOMObject = new DOMData;
	Sint32		nDOMObjectID = 0;

	if (pDOMObject) {
		nDOMObjectID = fXMLDataMapNextID;
		pDOMObject->Initialize();

		fXMLDataMapNextID++;

		SXMLData	xmlData;
		xmlData.fDOMData	= pDOMObject;

		//Add to map
		fXMLDataMap[ nDOMObjectID ] = xmlData;
	}

	return nDOMObjectID;
}


short DOMManager::ReleaseXML(Sint32 nDOMID)
// Releases memory for this DOM context.
{
	short		retVal = kUnknownError;
	DOMData*	pDOMObj = this->GetDOMPtr(nDOMID);

	if (pDOMObj != NULL) {
		pDOMObj->ReleaseXML();

		delete pDOMObj;

		// Remove the key from the map
		fXMLDataMap.erase( nDOMID );

		retVal = kNoError;
	}
	else
		retVal = kInvalidXMLHandle;

	return retVal;
}


DOMData* DOMManager::GetDOMPtr(Sint32 nDOMID)
// Returns a pointer to the DOMData for this DOM context ID, or NULL if
// there is no context corresponding to this ID.
{
	TXMLDataMap::const_iterator  iter = fXMLDataMap.find(nDOMID);
	DOMData*	pDOMData = NULL;

	if ( iter != fXMLDataMap.end() ) {
		// The value passed in, nDOMID, was found in the map
		const SXMLData&	xmlData	= iter->second;
		pDOMData				= xmlData.fDOMData;
	}

	return pDOMData;
}

// ******************* DOMData functions *******************

DOMData::DOMData()
{
	m_pImpl = NULL;
	m_pXercesDOMParser = NULL;
	m_pErrorHandler = NULL;
	m_plDomDocument = NULL;
	m_pDocRoot = NULL;

	m_bDocLoaded = false;
}


void DOMData::Initialize(void)
// Initialize DOM and set up an XML document
{
	const XMLCh gLS[] = { chLatin_L, chLatin_S, chNull };

	m_pImpl = DOMImplementationRegistry::getDOMImplementation(gLS);
}


short DOMData::ReleaseXML(void)
// Releases internal memory for the XML parser.
{
	if (m_pXercesDOMParser != NULL)
		delete m_pXercesDOMParser;

	if (m_pErrorHandler)
		delete m_pErrorHandler;

	return kNoError;
}


// Sets up a new document by creating a root element node.
short DOMData::CreateNewXMLDocument(const TXString& rootElementName)
{
	short	retVal = kUnknownError;
	DOMDocumentPtr	doc;

	if (rootElementName.GetLength() > 0) {


		try {
			doc = m_pImpl->createDocument(0, rootElementName, 0);

			if (doc != NULL) {
				m_plDomDocument = doc;
				DOMElementPtr pNode = doc->getDocumentElement();

				if (pNode != NULL) {
					m_pDocRoot = pNode;
					m_bDocLoaded = true;
					retVal = kNoError;
				}
				else
					retVal = kParserError;		// An internal Xerces error
			}
		}

		catch (const XMLException& toCatch) {
			retVal = ConvertXMLErrorToVSError(toCatch.getCode());	// Get XML error code
		}

		catch (const DOMException& toCatch) {
			retVal = ConvertDOMErrorToVSError(toCatch.code);	// Get DOM error code
		}

		catch (...) {
			retVal = kParserError;
		}

	}
	else
		retVal = kInvalidPath;

	return retVal;
}


// ****************************** File I/O functions ******************************

#if defined(GS_WIN)

#elif _LINUX

#else

/*
// Converts a path from OS 9-style to a Posix-style path, and copies the result into
// osxStylePath.  osxStylePath must contain enough storage for the output.  Usually,
// allocating 1024 bytes is safe.
void ConvertToOSXStylePath(const TXString& cstrFileName, TXString& osxStylePath)
{
	CFStringRef cfPathStr = cstrFileName.GetCFStringRef();
	
	if (VERIFYN(kJGeraci, cfPathStr)) {
		
		CFURLRef url = CFURLCreateWithFileSystemPath(kCFAllocatorDefault, cfPathStr, kCFURLHFSPathStyle, true);
		
		if (VERIFYN(kJGeraci, url != NULL)) {
			
			CFStringRef cfFilePath = CFURLCopyFileSystemPath(url, kCFURLPOSIXPathStyle);
			
			if (VERIFYN(kJGeraci, cfFilePath != NULL)) {
				osxStylePath = cfFilePath;
				CFRelease(cfFilePath);
			}
			CFRelease(url);
		}
		CFRelease(cfPathStr);
	}
}

*/
#endif


/*static*/ TXString DOMData::GetFullPath(short whichPath, const TXString& filename, bool inCreateIfMissing /*= false*/)
// Returns a full path given a VectorWorks folder specifier and filename.
// The returned string is allocated by this function.  It is the calling function's responsibility
// to free this string.
{
	TXString xmlFile;

		
		if (whichPath != -1) 
		{



#if defined(GS_WIN)
			//TODO
			//if (GS_GetFolderN(gCBP, whichPath, xmlFile, inCreateIfMissing)) {
			//	xmlFile += filename;			
			//}

#elif _LINUX
			// TODO
			// LINUX_IMPLEMENTATION - done
			// if (GS_GetFolderN(gCBP, whichPath, xmlFile, inCreateIfMissing)) {
			// 	xmlFile += filename;
			// }
#else
			// Mac
			TXString	hfsPath;
			TXString	cstrPath;

			// TODO
			//if (GS_GetFolderN(whichPath, hfsPath, inCreateIfMissing)) 
			{
				//ConvertToOSXStylePath(hfsPath, cstrPath);

				// Concatenate the file name
				xmlFile = cstrPath;
				xmlFile += txu("/");
				xmlFile += filename;
			}
			
#endif
			// Convert '\' and ':' to '/'
			xmlFile.Replace(txu("\\"), txu("/"));
			xmlFile.Replace(txu(":"), txu("/"));
		}
		else {
			// If whichPath is -1, the filename will simply be passed through as the
			// return value.  This is to allow functions to specify an arbitrary place for
			// the XML file.


			//TKludgeHandleIncomingFilePath env;
			//env.fHadError	= true;
			//env.fForWrite	= inCreateIfMissing;
		//	env.fPath = filename;

			// TODO
			//if (GS_Kludge(kKludgeHandleIncomingFilePath, &env, nil) &&
			//	env.fHadError == false &&
			//	env.fPath[0] != 0) 
			{
				//xmlFile = env.fPath;

#if ! _WINDOWS
				if (xmlFile.Find(':') != -1) {
					TXString	osxStylePath;

					// TODO ConvertToOSXStylePath(xmlFile, osxStylePath);

					xmlFile = osxStylePath;
					
				}
#endif
				// Convert '\' and ':' to '/'
				xmlFile.Replace(txu("\\"), txu("/"));
#if GS_MAC
				xmlFile.Replace(txu(":"), txu("/"));
#endif
			}
		}



	return xmlFile;
}


short DOMData::ReadXMLFile(short whichPath, const TXString&  fileName)
// Reads an XML file using a XercesDOMParser.  Returns an error code.
//
// Parameters:
//		whichPath	- VectorWorks folder specifier
//		fileName	- filename to read
{
	short	retVal = kUnknownError;
	TXString xmlFile;

	if (whichPath == -1) {
		xmlFile = GetFullPath(whichPath, fileName);
	}
	else {
		VCOMPtr< IFileIdentifier > pXmlFileID( IID_FileIdentifier );
		VCOMPtr< IFolderIdentifier > pAppFolders( IID_FolderIdentifier );

		whichPath = abs(whichPath);
		//if (!VCOM_SUCCEEDED(pAppFolders->FindFileInStandardFolder((EFolderSpecifier)whichPath, fileName, &pXmlFileID)))
		//	return kUnknownError; TODO
		TXString filePath;

		pXmlFileID->GetFileFullPath(filePath);
		xmlFile = filePath;
	}

	// Parse (load) the XML document

	m_pXercesDOMParser = new XercesDOMParser();

	if (m_pXercesDOMParser != NULL) {

		ErrorHandler*	errHandler = (ErrorHandler*) new HandlerBase();

		if (errHandler != NULL) {
			m_pXercesDOMParser->setErrorHandler(errHandler);

			m_plDomDocument = NULL;

			try {
				if ( xmlFile[0] ) {
					TXString theFilePath = xmlFile;
#ifdef GS_WIN
					theFilePath.Replace( "/", "\\" );
#endif

#if GS_LIN
					m_pXercesDOMParser->parse( theFilePath.operator const char*() );
#else
					//m_pXercesDOMParser->parse( theFilePath.GetData() ); TODO
#endif

					m_plDomDocument = m_pXercesDOMParser->getDocument();

					// Now that the document is loaded, initialize the root pointer
					if (m_plDomDocument != NULL) {
						m_pDocRoot = m_plDomDocument->getDocumentElement();

						if (m_pDocRoot != NULL) {
							m_bDocLoaded = true;
							retVal = kNoError;
						}
						else
							retVal = kParserError;
					}
					else
						retVal = kMemoryError;
				}
				else {
					retVal = kParserError;
				}
			}


			catch (const XMLException& toCatch) {
				retVal = ConvertXMLErrorToVSError(toCatch.getCode());	// Get XML error code
			}

			catch (const DOMException& toCatch) {
				retVal = ConvertDOMErrorToVSError(toCatch.code);	// Get DOM error code
			}
			
			catch (const SAXParseException& /*toCatch*/) {
				//toCatch;
				retVal = kParserError; //ConvertDOMErrorToVSError(toCatch.code);	// Get DOM error code
			}

			catch (...) {
				// See if we can determine the error.
				retVal = kParserError;
			}
		}
	}

	return retVal;
}

short DOMData::ReadXMLMemory(const TXString& inXMLData)
// Reads (parses) XML data from an internal memory source, using the XercesDOMParser.
{
	short			retVal = kUnknownError;

	const char* xmlData = inXMLData;
	size_t xmlDataLen = inXMLData.GetLength();

	// Create memory buf input source for the parser
	MemBufInputSource* memBufIS = new MemBufInputSource((const XMLByte*) xmlData, (unsigned int) xmlDataLen, "bufID", false); //-V202

	m_pXercesDOMParser = new XercesDOMParser();

	if (m_pXercesDOMParser != NULL && xmlData != NULL) {

		ErrorHandler*	errHandler = (ErrorHandler*) new HandlerBase();

		if (errHandler != NULL) {
			m_pXercesDOMParser->setErrorHandler(errHandler);

			m_plDomDocument = NULL;

			try {
				m_pXercesDOMParser->parse(*memBufIS);		// Parse it

				m_plDomDocument = m_pXercesDOMParser->getDocument();

				// Now that the document is loaded, initialize the root pointer
				if (m_plDomDocument != NULL) {

					m_pDocRoot = m_plDomDocument->getDocumentElement();

					m_bDocLoaded = true;
					retVal = kNoError;
				}
				else
					retVal = kMemoryError;
			}

			catch (const XMLException& toCatch) {
				retVal = ConvertXMLErrorToVSError(toCatch.getCode());	// Get XML error code
			}

			catch (const DOMException& toCatch) {
				retVal = ConvertDOMErrorToVSError(toCatch.code);	// Get DOM error code
			}

			catch (...) {
				retVal = kParserError;
			}

			delete memBufIS;
		}
	}

	return retVal;
}


short DOMData::WriteXMLFile(short whichPath, const TXString& fileName)
// Writes an XML file.
//
// Parameters:
//		whichPath	- VectorWorks folder specifier
//		fileName	- filename to write
{
	short	retVal = 0;

	TXString txFileName;
	
	if (whichPath == -1)
		txFileName = GetFullPath(whichPath, fileName, true /*create if missing*/);
	else {
		VCOMPtr< IFileIdentifier > pXmlFileID( IID_FileIdentifier );
		whichPath = abs(whichPath);

		pXmlFileID->GetFileFullPath(txFileName);

	}

	try
	{
		// get a serializer, an instance of DOMWriter
		DOMLSSerializer         *theSerializer = ((DOMImplementationLS*)m_pImpl)->createLSSerializer();
        DOMLSOutput             *pOutput = ((DOMImplementationLS*)m_pImpl)->createLSOutput();
		if (theSerializer && pOutput) {
			// set user specified end of line sequence and output encoding
			//theSerializer->setNewLine(gMyEOLSequence);
			//theSerializer->setEncoding(gOutputEncoding);

			// plug in user's own error handler
			DOMErrorHandler *myErrorHandler = new XMLErrorHandler();

			if (myErrorHandler) {
                DOMConfiguration* pConfig = theSerializer->getDomConfig();
				pConfig->setParameter(XMLUni::fgDOMErrorHandler, myErrorHandler);

				// set feature if the serializer supports the feature/mode
				//if (theSerializer->canSetFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections))
				//    theSerializer->setFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections);

				//if (theSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent))
				//    theSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent);

				bool	bCanFormatPrettyPrint = true, bDoFormatPrettyPrint = true;
				if (pConfig->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, bCanFormatPrettyPrint))
					pConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, bDoFormatPrettyPrint);

				//if (theSerializer->canSetFeature(XMLUni::fgDOMWRTBOM, gWriteBOM))
				//    theSerializer->setFeature(XMLUni::fgDOMWRTBOM, gWriteBOM);

				//
				// Plug in a format target to receive the resultant
				// XML stream from the serializer.
				//
				// StdOutFormatTarget prints the resultant XML stream
				// to stdout once it receives any thing from the serializer.
				//

				XMLFormatTarget  *myFormTarget;
				myFormTarget = new LocalFileFormatTarget((const XMLCh*)txFileName);
                pOutput->setByteStream(myFormTarget);

				if (myFormTarget != NULL) {
					//
					// do the serialization through DOMWriter::writeNode();
					//
					if (m_plDomDocument != NULL) {
						theSerializer->write(m_plDomDocument, pOutput);
						retVal = kNoError;
					}

					delete myFormTarget;
				}

				delete myErrorHandler;
			}
            pOutput->release();
			theSerializer->release();
		}
    }

    catch (XMLException& toCatch)
    {
        //cerr << "An error occurred during creation of output transcoder. Msg is:"
        //    << endl
        //    << StrX(e.getMessage()) << endl;
		retVal = ConvertXMLErrorToVSError(toCatch.getCode());
    }

	catch (const DOMException& toCatch) {
		retVal = ConvertDOMErrorToVSError(toCatch.code);	// Get DOM error code
	}

	catch (...) {
		retVal = kParserError;
	}

	return retVal;
}


short DOMData::WriteXMLMemory(TXString& outXmlData)
// Writes XML data to an internal memory source.
// This function allocates the memory for xmlData and null-terminates it.
//
{
	short	retVal = kUnknownError;
	XMLCh*	xmlOutputStr = NULL;
	char*	charOutputStr = NULL;

	try
	{
		// get a serializer, an instance of DOMWriter
		DOMLSSerializer         *theSerializer = ((DOMImplementationLS*)m_pImpl)->createLSSerializer();
        
		if (theSerializer) {

			// Set error handler
			DOMErrorHandler *myErrorHandler = new XMLErrorHandler();

			if (myErrorHandler) {
                DOMConfiguration* pConfig = theSerializer->getDomConfig();
				pConfig->setParameter(XMLUni::fgDOMErrorHandler, myErrorHandler);

				bool	bCanFormatPrettyPrint = true, bDoFormatPrettyPrint = true;

				if (pConfig->canSetParameter(XMLUni::fgDOMWRTFormatPrettyPrint, bCanFormatPrettyPrint))
					pConfig->setParameter(XMLUni::fgDOMWRTFormatPrettyPrint, bDoFormatPrettyPrint);

				// Do the serialization through DOMWriter::writeToString();
				if (m_plDomDocument != NULL) {

					xmlOutputStr = theSerializer->writeToString(m_plDomDocument);

					// return the result
					outXmlData	= xmlOutputStr;
					retVal		= kNoError;
				}
			}

			theSerializer->release();
			delete myErrorHandler;
		}
	}

	catch (XMLException& toCatch)
	{
	    //cerr << "An error occurred during creation of output transcoder. Msg is:"
	    //    << endl
	    //    << StrX(e.getMessage()) << endl;
		retVal = ConvertXMLErrorToVSError(toCatch.getCode());
	}

	catch (const DOMException& toCatch) {
		retVal = ConvertDOMErrorToVSError(toCatch.code);	// Get DOM error code
	}

	catch (...) {
		retVal = kParserError;
	}

	if (charOutputStr != NULL) {
#if GS_MAC
		delete []charOutputStr;
#else
		XMLString::release(&charOutputStr);
#endif
	}

	if (xmlOutputStr != NULL)
		XMLString::release(&xmlOutputStr);

	return retVal;
}


// ****************************** Find and Path functions ******************************

DOMNodePtr DOMData::FindElementSearch(DOMNodePtr pStartNode, const TXString& element)
// Returns a node pointer to the specified element.
//
// NOTE: this is not the implementation of the Plug-in library call, FindElement.  That
// call is mapped to SearchForElement.
//
// Parameters:
//		pStartNode	- node pointer to start the search
//		element		- string containing element to search for
//		skip		- number of matches to skip; used when finding successive elements
{
	DOMNodePtr	pCurNode, pFoundNode = NULL;

	if (pStartNode == NULL)
		return NULL;		// Nothing to search!

	if (pStartNode->getNodeType() == DOMNode::ELEMENT_NODE) {

		const XMLCh	*xmlElementName = pStartNode->getNodeName();

		if (element == TXString(xmlElementName)) {
			if (m_pCurSkipCount == 0) {
				pFoundNode = pStartNode;	// This will be returned
			}
			else
				m_pCurSkipCount--;			// Decrement count and keep searching
		}
	}

	if (pFoundNode == NULL) {
		// Element text not found in this node; scan all children
		for (pCurNode = pStartNode->getFirstChild(); NULL != pCurNode; pCurNode = pCurNode->getNextSibling())
		{
			// Call recursively
			pFoundNode = this->FindElementSearch(pCurNode, element);

			if (pFoundNode != NULL)
				break;
		}
	}

	return pFoundNode;		// Will be NULL if not found
}


DOMNodePtr DOMData::FindElement(DOMNodePtr pStartNode, const TXString& element, int skip)
// Searches for a node pointer to the specified element.  This is the main entry
// point for FindElementSearch.
// If found, returns a pointer to this node; otherwise, returns NULL.
//
// Parameters:
//		pStartNode	- node pointer to start the search
//		element		- string containing element to search for
//		skip		- number of matches to skip; used when finding successive elements
{
	m_pCurSkipCount = skip;

	return FindElementSearch(pStartNode, element);
}


DOMNodePtr DOMData::FindAttributeSearch(DOMNodePtr pStartNode, const TXString& attribute, TXString& value)
//
// Similar to FindElementSearch, but searches for an attribute, instead of an element.
//
// The function does a depth-first search of the tree, starting at pStartNode, until
// an element is found that contains the specified attribute.  If found the attribute's
// value is will be returned in value.
// If the attribute is found, a pointer to the element containing the attribute will be
// returned; if not found, NULL will be returned.
// Note: the caller is responsible for freeing the string returned in the value parameter.
{
	DOMNodePtr	pCurNode, pFoundNode = NULL;

	if (pStartNode == NULL)
		return NULL;		// Nothing to search!

	if (pStartNode->getNodeType() == DOMNode::ELEMENT_NODE) {

		// Convert user-specified attribute name to Xerces internal format
		const XMLCh  *xmlAttrStr = attribute;

		// Get attributes, if any
		DOMNamedNodeMap  *attr = pStartNode->getAttributes();


		if (attr != NULL && attr->getLength() > 0) {

			// Scan all attributes of this element, looking for the desired one
			for (Sint32 i = 0; DemoteTo<Uint32>(kEveryone, i) < attr->getLength(); i++) {
				DOMNodePtr	attrPtr = attr->item(i);						// Get current attribute
				const XMLCh  *xmlAttributeName = attrPtr->getNodeName();	// Get its name

				// Found it?
				if (XMLString::compareString(xmlAttributeName, xmlAttrStr) == 0) {

					// Attribute found - get its value
					const XMLCh		*xmlAttributeValue = attrPtr->getNodeValue();

					value = xmlAttributeValue;
	

					pFoundNode = pStartNode;
				}
			}
		}



		if (pFoundNode == NULL) {
			// Attribute not found in this node; scan all children
			for (pCurNode = pStartNode->getFirstChild(); NULL != pCurNode; pCurNode = pCurNode->getNextSibling()) {

				// Call recursively
				pFoundNode = this->FindAttributeSearch(pCurNode, attribute, value);

				if (pFoundNode != NULL)
					break;
			}
		}
	}

	return pFoundNode;		// Will be NULL if not found
}


int DOMData::FindChild(DOMNodePtr pParent, const TXString& element, DOMNodePtr& pFoundChild, int skip)
// Searches a given node, pParent, for a specific child, element.  If found, the result
// is returned in pFoundChild.  The default parameter, skip, indicates which occurrence of
// element should be returned.  The return value indicates which occurrence was actually returned,
// in the event that there aren't as many occurrences of element as was requested in skip.
// For example, if part of a DOM tree has the following structure,
//     <able>
//        <baker>
//        <charlie>
//        <charlie>
//        <foxtrot>
//     </able>
//
// and FindChild is called with element set to "charlie", and skip set to 3, the function will
// return a pointer to the second occurrence of charlie (because there are only two), and the
// return value will be 2, indicating that this is the second occurrence.  If the tree contained
// three occurrences, the function would return a pointer to the third occurrence, and the return
// value would have been 3.
//
// Unlike FindElement, this function does not recurse into the tree.  It only looks at the
// immediate children of pParent.
//
// Parameters:
//		pParent			- node under which to scan
//		element			- string representing the desired child element
//		pFoundChild		- (output) if found, the desired node is returned here
//		skip			- which occurrence of element to find (1 = first, 2 = second, etc.)
{
	DOMNodePtr	pCurNode;
	int			count = 0;

	if (pParent == NULL)
		return 0;		// Nothing to search

	const XMLCh*	xmlDesiredElement = element;


	// Scan all children for element
	for (pCurNode = pParent->getFirstChild(); NULL != pCurNode; pCurNode = pCurNode->getNextSibling())
	{
		if (pCurNode->getNodeType() == DOMNode::ELEMENT_NODE) {

			const XMLCh	*xmlElementName = pCurNode->getNodeName();

			if (XMLString::compareString(xmlDesiredElement, xmlElementName) == 0) {
				count++;
				pFoundChild = pCurNode;

				if (count == skip)
					break;
			}
		}
	}

	return count;
}


TXString DOMData::GetDelimitedString(const TXString& str, TXString&  delimitedStr, const TXString& beginDelimiter, const TXString& endDelimiter)
// Retreives a string that is delimited on the left side by beginDelimiter, and on the
// right side by either endDelimiter or the terminating NULL character.
// The return value is a pointer within the original string, str, to the second delimiter.
// If no first or second delimiter is found, the function returns NULL.
// The delimited string is returned in delimitedStr, which must be allocated by the calling function.
{
	ptrdiff_t p1 = str.Find(beginDelimiter);  // Find first delimiter

	if (p1 >= 0) {
		ptrdiff_t p2 = str.Find(endDelimiter, p1+1);		// Find second delimeter

		if (p2 >= 0)
		{
			delimitedStr = str.Mid(p1 + 1, p2 - p1 - 1);
			return str.Mid(p2);
		}
		else
			delimitedStr = str.Mid(p1 + 1);
	}

	return txu("");
}


bool DOMData::ValidTag(const TXString& tag)
// Returns true if the given tag consists of valid characters.  That would be alphanumerics; no spaces.
{
	return tag.GetLength() > 0 && tag.Find(' ') < 0;
}


short DOMData::ParsePath(const TXString& nodePathStr, DOMNodePtr& pFoundNode, bool bCreate)
// Parses a path into its constituent parts.  If found, pFoundNode will point to the
// the desired node.
// If the bCreate flag set to true, any path elements not found will be created.
// The return value is an error code:
//    0   - no error
//    -3  - node (element) not found
{
	TXString	nextPtr = nodePathStr;
	TXString	pathElementStr, countSpecifierStr;
	DOMNodePtr	pCurNode = NULL, pChildNode = NULL;
	int			count = 0;
	bool		bValidPath = true, bFirstPass = true;
	short		retVal = kUnknownError;

	if (nodePathStr.GetLength() == 0)
		return kInvalidPath;

	// First, validate all elements of the path

	// The path must begin with a slash
	if (nodePathStr[0] != '/')
		return kInvalidPath;

	do {
		// Get next element from the path string
		nextPtr = GetDelimitedString(nextPtr, pathElementStr, "/", "/");

		if (pathElementStr.GetLength() == 0) {
			// Invalid path string
			bValidPath = false;
			break;
		}

		// If first pass, pathElementStr should contain the root node.  Verify this.
		if (bFirstPass) {
			bFirstPass = false;

			TXString xmlElementName = m_pDocRoot->getNodeName();
		
			if (xmlElementName != pathElementStr) {
				bValidPath = false;
				retVal = kElementNotFound;
				break;
			}
		}

		// Determine if there is a selection specifier (as in, "[3]")
		TXString countPtr = GetDelimitedString(pathElementStr, countSpecifierStr, "[", "]");
		if (countPtr.GetLength() > 0) {
			count = countSpecifierStr.atoi();
			if (count < 1) {
				bValidPath = false;
				break;
			}
		}

		// Make sure the tag (pathElementStr) doesn't contain invalid characters
		if (! ValidTag(pathElementStr)) {
			bValidPath = false;			// Found an invalid character
			pCurNode = NULL;
			retVal = kInvalidPath;
			break;
		}
	}
	while (nextPtr.GetLength() > 0);


	// Now that the path has been parsed for validity, parse it to determine which node is being specified.
	if (bValidPath) {
		pCurNode = m_pDocRoot;
		count = 0;
		nextPtr = nodePathStr;
		retVal = kNoError;
		bFirstPass = false;

		// Skip the root node part of the path
		nextPtr = GetDelimitedString(nextPtr, pathElementStr, "/", "/");

		while (nextPtr.GetLength() > 0) {
			// Get next element from the path string
			nextPtr = GetDelimitedString(nextPtr, pathElementStr, "/", "/");

			// Determine if there is a selection specifier (as in, "[3]")
			TXString countPtr;

			countPtr = GetDelimitedString(pathElementStr, countSpecifierStr, "[", "]");
			if (countPtr.GetLength() > 0) {
				count = countSpecifierStr.atoi();
				//count--;		// Tag[1] means get the first one, so skip will be 0

				ptrdiff_t bracketIndex = pathElementStr.Find(txu("["));
				if (bracketIndex > 0)
					pathElementStr.SetLength(bracketIndex);

			}
			else
				count = 1;

			// Find this node
			int foundCount = this->FindChild(pCurNode, pathElementStr, pChildNode, count);

			if (foundCount < count) {
				if (bCreate) {

					// Create the necessary nodes (all (count - foundCount) of them)

					for (int i = 0; i < count - foundCount; i++) {
						// Create the path element(s)


						pChildNode = m_plDomDocument->createElement(pathElementStr);



						if (pChildNode != NULL) {
							pCurNode->appendChild(pChildNode);
						}
						else {
							retVal = kUnknownError;		// Should never get here
							nextPtr.SetLength(0);		// Break out of the big do loop
							break;
						}
					}  // for...

					pCurNode = pChildNode;		// This is now the current node
				}
				else {
					// Caller doesn't want nodes created, so return with an error
					retVal = kElementNotFound;
					break;
				}
			}
			else
				pCurNode = pChildNode;		// The child node is now the current node

		}	// while (nextPtr != NULL);
	}

	if (retVal == kNoError)
		pFoundNode = pCurNode;
	else
		pFoundNode = NULL;

	return retVal;
}


DOMNodePtr DOMData::GetTextNode(DOMNodePtr pNode)
// Returns the text node of the given node, or NULL if the node has no text node.
{
	DOMNodePtr	pTextNode = NULL, pCurNode;

	if (pNode == NULL)
		return NULL;

	if (pNode->hasChildNodes()) {

		// Scan all children for a text node
		for (pCurNode = pNode->getFirstChild(); NULL != pCurNode; pCurNode = pCurNode->getNextSibling())
		{
			if (pCurNode->getNodeType() == DOMNode::TEXT_NODE) {
				pTextNode = pCurNode;		// Found a text node
				break;
			}
		}
	}

	return pTextNode;
}


short DOMData::CreatePath(DOMNodePtr pNode, TXString& path)
// Creates a path string to the specified node.  The path is allocated by this function,
// and returned in the path variable.
{
	short	retVal;

		DOMNodePtr	pCurNode = pNode;
		TXString	tempPath;
		path.SetLength(0); 			 // Clear path string

		while (pCurNode != NULL) {
			const XMLCh* nodeName = pCurNode->getNodeName();
		

			tempPath =  txu("/");	// Copy node separator character
			tempPath += nodeName;	// Copy parent string to tempPath
			tempPath += path;		// Copy what was remaining of the path
			path = tempPath;		// Now copy tempPath onto path


			if ( pCurNode->isSameNode(m_pDocRoot))
				break;
			else
				pCurNode = pCurNode->getParentNode();
		}

		retVal = kNoError;
	

	return retVal;
}


// ****************************** Element functions ******************************

short DOMData::GetElementValue(const TXString& elementPath, TXString& value)
// Retrieves an element value.
//
// Parameters:
//		elementPath	- path to the desired element (or node)
//		value		- if found, the value is returned here
//
// If the element is found, true is returned; otherwise false is returned.
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal;
	DOMNodePtr	pNode;


	retVal = ParsePath(elementPath, pNode);

	
	if (retVal == kNoError) {
		if (pNode != NULL) {

			value[0] = '\0';		// The element might not have a value
			retVal = kNoError;		// Even if there is no value, it is not an error

			if (pNode->hasChildNodes()) {
				DOMNodePtr	pFirstChild = pNode->getFirstChild();
				const XMLCh* xmlElementName = pFirstChild->getNodeValue();
				if ( xmlElementName ) {
	
					value = xmlElementName;

				}
			}
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}


short DOMData::SetElementValue(const TXString& elementPath, const TXString& value)
// Sets an element value.
// If the individual elements within the path are not found, they will be created.
//
// Parameters:
//		elementPath	- path to the desired element (or node)
//		value		- if found, the value is returned here
//
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal;
	DOMNodePtr	pNode = NULL;

	retVal = ParsePath(elementPath, pNode, true);

	if (retVal == kNoError) {
		if (pNode != NULL) {

	

			// If the node already has a text node, simply set the text node's value.  If
			// it does not have a text node, create a new text node and set its value.
			DOMNodePtr pTextNode = GetTextNode(pNode);

			if (pTextNode == NULL) {
        		DOMText*    nodeDataVal = m_plDomDocument->createTextNode(value);

        		pNode->appendChild(nodeDataVal);
			}
			else {
        		pTextNode->setNodeValue(value);
			}


		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}


	return retVal;
}


short DOMData::DeleteElement(const TXString& elementPath)
// Deletes an element.
//
// Parameters:
//		elementPath	- path to the desired element (or node)
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal;
	DOMNodePtr	pNode;

	retVal = ParsePath(elementPath, pNode);

	if (retVal == kNoError) {
		if (pNode != NULL) {

			DOMNodePtr	pParentNode = pNode->getParentNode();

			if (pParentNode != NULL)
				pParentNode->removeChild(pNode);
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}


short DOMData::GetFirstChild(const TXString& elementPath, TXString& childName)
// Returns the name of the first child node of the specified element.
//
// Parameters:
//		elementPath		- Path to the desired element (or node)
//		childName		- If the node has child nodes, the first such node is returned here
//
// An error result is returned by the function.
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal;
	DOMNodePtr	pNode;

	retVal = ParsePath(elementPath, pNode);

	
	if (retVal == kNoError) {
		if (pNode != NULL) {

			retVal = kNoError;		// Even if there is no value, it is not an error

			if (pNode->hasChildNodes()) {

				DOMNodePtr	pCurNode;

				// Scan all children for element
				for (pCurNode = pNode->getFirstChild(); NULL != pCurNode;
						pCurNode = pCurNode->getNextSibling()) {

					if (pCurNode->getNodeType() == DOMNode::ELEMENT_NODE) {
						const XMLCh	*xmlElementName = pCurNode->getNodeName();
						childName = xmlElementName;
					}
				}
			}
			else
				retVal = kNoChildOrSiblingNodes;
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}


short DOMData::GetNextElement(const TXString& elementPath, TXString& nextElementName)
// Returns the name of the next element (or node) after the specified element.
//
// Parameters:
//		elementPath		- Path to the desired element (or node)
//		nextElementName	- The name of the succeeding element is returned here
//
// An error result is returned by the function.
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal;
	DOMNodePtr	pNode;

	retVal = ParsePath(elementPath, pNode);
	
	if (retVal == kNoError) {
		if (pNode != NULL) {

			retVal = kNoError;		// Even if there is no value, it is not an error

			DOMNodePtr	pCurNode = pNode->getNextSibling();
			bool		bFound = false;

			// Scan for next element (or node)
			while (NULL != pCurNode) {

				if (pCurNode->getNodeType() == DOMNode::ELEMENT_NODE) {

					const XMLCh	*xmlElementName = pCurNode->getNodeName();
					nextElementName = xmlElementName;

					bFound = true;
					break;
				}
				else
					pCurNode = pCurNode->getNextSibling();
			}

			if (! bFound)
				retVal = kNoChildOrSiblingNodes;
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}


short DOMData::GetPreviousElement(const TXString& elementPath, TXString& nextElementName)
// Returns the name of the previous element (or node) before the specified element.
//
// Parameters:
//		elementPath		- Path to the desired element (or node)
//		nextElementName	- The name of the preceding element is returned here
//
// An error result is returned by the function.
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal;
	DOMNodePtr	pNode;

	retVal = ParsePath(elementPath, pNode);
	
	if (retVal == kNoError) {
		if (pNode != NULL) {

			retVal = kNoError;		// Even if there is no value, it is not an error

			DOMNodePtr	pCurNode = pNode->getPreviousSibling();
			bool		bFound = false;

			// Scan for next element (or node)
			while (NULL != pCurNode) {

				if (pCurNode->getNodeType() == DOMNode::ELEMENT_NODE) {

					const XMLCh	*xmlElementName = pCurNode->getNodeName();
					nextElementName = xmlElementName;

					bFound = true;
					break;
				}
				else
					pCurNode = pCurNode->getPreviousSibling();
			}

			if (! bFound)
				retVal = kNoChildOrSiblingNodes;
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}



// ****************************** Attribute functions ******************************

short DOMData::FindAttribute(const TXString& elementPath, const TXString& attribute, DOMNodePtr& pElement, DOMAttrPtr& pFoundAttr, bool bCreate)
// Finds an attribute of an element at the specified path, and returns a pointer to it.
// If either the element or the attribute can not be found, pFoundAttr will be set to NULL.
// If bCreate is true, elements will be created where needed in order to make the elementPath
// valid; however, attributes will not be created.
// An error code is returned.
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal = kUnknownError;
	DOMNodePtr	pNode;
	DOMAttrPtr	pFoundAttrNode = NULL;


	retVal = ParsePath(elementPath, pNode, bCreate);

	if (retVal == kNoError) {
		if (pNode != NULL) {

			// Get attributes, if any
			DOMNamedNodeMap  *attr = pNode->getAttributes();

			#ifdef TEST
			const XMLCh  *xmlNodeName = pNode->getNodeName();
			char*  nodeName = XMLString::transcode(xmlNodeName);
			XMLString::release(&nodeName);
			#endif

			if (attr != NULL && attr->getLength() > 0) {

				retVal = kAttributeNotFound;	// assume attribute not present, but look for it

				// DOMNamedNodeMap::getLength() returns XMLSize_t which is an unsigned long.
				for (Sint32 i = 0; DemoteTo<Uint32>(kEveryone, i) < attr->getLength(); i++) {
					DOMNodePtr	attrPtr = attr->item(i);
					const XMLCh  *xmlElementName = attrPtr->getNodeName();

					if (XMLString::compareString(xmlElementName, attribute) == 0) {
						// Attribute found
						pFoundAttrNode = (DOMAttrPtr) attrPtr;
						retVal = kNoError;
						break;
					}
				}
			}
			else
				retVal = kAttributeNotFound;

		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}


	pElement = pNode;
	pFoundAttr = pFoundAttrNode;
	return retVal;
}


short DOMData::GetAttributeValue(const TXString& elementPath, const TXString& attribute, TXString& value)
// Retrieves an attribute value.
//
// Parameters:
//		elementPath	- path to the desired element
//		attribute	- desired attribute
//		value		- if found, the value is returned here
//
// If the attribute is found, 0 is returned.  An error code is returned.  Possible errors:
//		-2		- Invalid path
//		-3		- Element not found
//		-4		- Attribute not found
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;			// No document loaded

	short		retVal;
	DOMNodePtr	pElement;
	DOMAttrPtr	pFoundAttr;

	retVal = FindAttribute(elementPath, attribute, pElement, pFoundAttr);

	if (retVal == kNoError) {
		if (pFoundAttr != NULL) {
			// Attribute found - get its value
			const XMLCh  *xmlAttributeValue = pFoundAttr->getNodeValue();
			value = xmlAttributeValue;

			retVal = kNoError;
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pFoundAttr is NULL
	}

	return retVal;
}


short DOMData::SetAttributeValue(const TXString& elementPath, const TXString& attribute, const TXString& value)
// Sets an attribute value.
// If the individual elements within the path are not found, they will be created.
//
// Parameters:
//		elementPath	- path to the desired element
//		attribute	- desired attribute
//		value		- the value to set
//
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;			// No document loaded

	short		retVal;

	DOMNodePtr	pElement, pNode;

	DOMAttrPtr	pFoundAttr;

	retVal = FindAttribute(elementPath, attribute, pElement, pFoundAttr, true);

	if (retVal == kNoError) {
		// Attribute found - set its value

		pFoundAttr->setValue(value);
	}

	else if (retVal == kAttributeNotFound) {
		// Element was either found or created, but the attribute does not exist

		// Find the desired element (or node)

		retVal = ParsePath(elementPath, pNode);

		if (retVal == kNoError) {
			if (pNode != NULL) {
				// Create the attribute
				

				((DOMElementPtr) pNode)->setAttribute(attribute, value);

				retVal = kNoError;
			
			}
			else
				retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
		}


	}

	return retVal;
}


short DOMData::DeleteAttribute(const TXString& elementPath, const TXString& attribute)
// Deletes an attibute.  Returns an error code.
//
// Parameters:
//		elementPath	- path to the desired element
//		attribute	- desired attribute
//
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;			// No document loaded

	short		retVal;
	DOMNodePtr	pElement;		// Element that contains the attribute
	DOMAttrPtr	pFoundAttr;

	retVal = FindAttribute(elementPath, attribute, pElement, pFoundAttr);

	if (retVal == kNoError) {
		if (pFoundAttr != NULL && pElement != NULL) {
			// Attribute found - delete it
			((DOMElementPtr) pElement)->removeAttributeNode(pFoundAttr);
			retVal = kNoError;
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pElement and/or pFoundAttr is NULL
	}

	return retVal;
}


// ****************************** CDATA functions ******************************

short DOMData::FindCDATASection(const TXString& elementPath, DOMNodePtr& pFoundNode, bool bCreate)
// Finds a CDATA section of an element at the specified path.  If found, pFoundNode will
// be set to point to it.
// If either the element or the CDATA section can not be found, NULL is returned.
// If bCreate is true, elements will be created where needed in order to make the elementPath
// valid; same for the attribute.
// Returns an error code.
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal;
	DOMNodePtr	pNode;

	retVal = ParsePath(elementPath, pNode, bCreate);

	
	if (retVal == kNoError) {
		if (pNode != NULL) {
			DOMNodePtr	pChild = pNode;
			pFoundNode = nullptr;
			// Scan for its CDATA node
			for (pChild = pNode->getFirstChild(); pChild != NULL; pChild = pChild->getNextSibling()) {
				if (pChild->getNodeType() == DOMNode::CDATA_SECTION_NODE) {

					pFoundNode = pChild;
					retVal = kNoError;

					break;
				}
			}
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pFoundNode is NULL
	}

	return retVal;
}


short DOMData::GetCDATA(const TXString& elementPath, TXString& outData)
// Retrieves the CDATA section of an element.  Returns an error code.
//
// Parameters:
//		elementPath		- (input)  path to desired element
//		hData			- (output) handle to a block containing the CDATA section
//
// If the element is found, a handle containing the data is returned; otherwise hData is not set.
// The calling function is responsible for deallocating the handle.
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;			// No document loaded

	short		retVal;
	DOMNodePtr	pNode;

	retVal = FindCDATASection(elementPath, pNode, false);

	if (retVal == kNoError) {
		if (pNode != NULL) {
			const XMLCh  *xmlCDATA = pNode->getNodeValue();

			outData	= xmlCDATA;
			retVal = kNoError;


		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}


short DOMData::SetCDATA(const TXString& elementPath, const TXString& data)
// Sets the CDATA section of an element.  Returns an error code.
// Any non-existent elements which make up the path will be created.
//
// Parameters:
//		elementPath		- path to desired element
//		data			- pointer to NULL-terminated data to copy to the CDATA section
//
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	short		retVal;
	DOMNodePtr	pNode;

	retVal = ParsePath(elementPath, pNode, true);


	if (retVal == kNoError) {
		if (pNode != NULL) {


			DOMCDATASection  *pCDATA = m_plDomDocument->createCDATASection(data);
			pNode->appendChild(pCDATA);

			retVal = kNoError;
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}


short DOMData::DeleteCDATA(const TXString& elementPath)
// Deletes the CDATA section of an element.  Returns an error code.
// Any non-existent elements which make up the path will be created.
//
// Parameters:
//		elementPath		- path to desired element
//
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;		// No document loaded

	DOMNodePtr	pNode;
	short		retVal = FindCDATASection(elementPath, pNode, false);

	if (retVal == kNoError) {
		if (pNode != NULL) {
			DOMNodePtr	pParentNode = pNode->getParentNode();

			if (pParentNode != NULL) {
				pParentNode->removeChild(pNode);
				retVal = kNoError;
			}
			else
				retVal = kParserError;	// Should never happen.  Something is messed up in the DOM structure
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}



short DOMData::SearchForElement(const TXString& elementPath, const TXString& searchElement, TXString& foundPath)
// Searches for an element starting at the specified point, elementPath.  This is the
// implementation for the Plug-in library call, FindElement.
//
// Parameters:
//		elementPath			- path to element where search will begin
//		searchElement		- element string to look for
//		foundPath			- if found, the path to the desired element is returned here
//
// An error code is returned (0 = no error)
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;			// No document loaded

	short		retVal;
	DOMNodePtr	pNode, pFoundNode;


	retVal = ParsePath(elementPath, pNode);


	
	if (retVal == kNoError) {
		if (pNode != NULL) {
			pFoundNode = this->FindElement(pNode, searchElement, 0);
			
			if (pFoundNode != NULL) {
				TXString path;

				CreatePath(pFoundNode, path);
				foundPath = path;
			}
			else {
				// Could not find node
				retVal = kElementNotFound;
			}
		}
		else
			retVal = kUnknownError;		// This should never happen: no err, but pNode is NULL
	}

	return retVal;
}


short DOMData::SearchForAttribute(const TXString& elementPath, const TXString& searchAttribute,
								  TXString& foundPath, TXString& attributeValue)
// Retrieves an attribute value from an internal DOM document.  This is the implementation
// for the Plug-in library call, FindAttribute.
//
// Parameters:
//		elementPath			- path to element where search will begin
//		searchAttribute		- desired attribute
//		foundPath			- if found, the path the element containing the desired
//								attribute is returned here.
//		attributeValue		- if found, the attribute's value is returned here
//
// An error code is returned (0 = no error)
{
	if (! m_bDocLoaded)
		return kInvalidXMLHandle;			// No document loaded

	short		retVal = kNoError;
	DOMNodePtr	pNode, pAttrNode;

	retVal = ParsePath(elementPath, pNode);


	
	if (retVal == kNoError) {
		pAttrNode = FindAttributeSearch(pNode, searchAttribute, attributeValue);

		if (pAttrNode != NULL) {
			// Attribute was found
			

			// Create path to this node
			TXString path;
			CreatePath(pAttrNode, path);
			foundPath = path;
		}
	}

	
	return retVal;
}




CXMLMemoryIOBuffer::CXMLMemoryIOBuffer()
{
}

CXMLMemoryIOBuffer::~CXMLMemoryIOBuffer()
{
}

VCOMError CXMLMemoryIOBuffer::GetDataSize(size_t& outSize)
{
	outSize	= fBuffer.GetLength();
	return kVCOMError_NoError;
}

VCOMError CXMLMemoryIOBuffer::CopyDataInto(void* pBuffer, size_t bufferSize)
{
	size_t	copySize	= fBuffer.GetLength();
	if ( bufferSize < copySize ) {
		copySize	= bufferSize;
	}

	memcpy( pBuffer, (const char*) fBuffer, copySize );
	return kVCOMError_NoError;
}

VCOMError CXMLMemoryIOBuffer::SetData(void* pBuffer, size_t bufferSize)
{
	TXString	strBuffer( (const char*) pBuffer, bufferSize );
	fBuffer		+= strBuffer;
	return kVCOMError_NoError;
}

#endif
