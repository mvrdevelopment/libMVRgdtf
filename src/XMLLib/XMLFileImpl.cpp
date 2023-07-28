#ifndef DONT_USE_XERCES_AS_XMLLIB
#include "Prefix/StdAfx.h"

#include "XMLFileImpl.h"
#include "XMLFileNodeImpl.h"
#include "TaggingDOMParser.h"
#include "../GDTFManager.h"

using namespace VectorworksMVR::Filing;
using namespace VectorworksMVR::XML;
using namespace VectorworksMVR::VWFC::Tools;

/*static*/ VCOMError	CXMLFileImpl::fLastError;

class XmlDomErrorHandler: public HandlerBase
{
public:
    XmlDomErrorHandler(ErrorHandler* defaultHandler) : defaultHandler(defaultHandler) { }
    ~XmlDomErrorHandler()
    {
        // someone needs to clean up any chained handlers; may as well be here.
        if (defaultHandler) delete defaultHandler;
    }
    
    void fatalError(const SAXParseException &ex) override
    {
		//TXString temp(ex.getMessage());
		//std::cout << "fatalError: " << temp.GetCharPtr() << std::endl;

		GdtfParsingError error (EGdtfParsingError::eXmlParsingError, ex.getLineNumber(), ex.getColumnNumber());
		SceneData::GdtfFixture::AddError(error);

    }
    
    void error(const SAXParseException &ex) override
    {
		//TXString temp(ex.getMessage());
		//std::cout << "error: " << temp.GetCharPtr() << std::endl;
    }
    
    void warning(const SAXParseException &ex) override
    {
		//TXString temp(ex.getMessage());
		//std::cout << "warning: " << temp.GetCharPtr() << std::endl;
    }
private:
    void msg(const char* const type, const SAXParseException &ex)
    {
        //TXString temp(ex.getMessage());
		//std::cout << "msg: " << temp.GetCharPtr() << std::endl;
    }
    
    ErrorHandler* defaultHandler;
};

// ----------------------------------------------------------------------------------------------------
CXMLFileImpl::CXMLFileImpl()
{
	fLastError				= kVCOMError_NoError;
	fpImpl					= NULL;
	fpXercesDOMParser		= NULL;

	fpDomDocument			= NULL;
	fpDocRoot				= NULL;

	fbDoFormatPrettyPrint	= true;
	fTheNewLine[0]			= chCR;
	fTheNewLine[1]			= chLF;
	fTheNewLine[2]			= chNull;

	XMLPlatformUtils::Initialize();
	
	const XMLCh gLS[]		= { chLatin_L, chLatin_S, chNull };
	fpImpl					= DOMImplementationRegistry::getDOMImplementation(gLS);
}

CXMLFileImpl::~CXMLFileImpl()
{
    if ( fpXercesDOMParser != NULL )
    {
        ErrorHandler* errorHandler = fpXercesDOMParser->getErrorHandler();
        fpXercesDOMParser->setErrorHandler(NULL);
        if (errorHandler)
            delete errorHandler;
        delete fpXercesDOMParser;
    }

	fpImpl			= NULL;
	// I added the following line to eliminate memory leaks reported by the 
	// Visual C++ function _CrtDumpMemoryLeaks. If you just start VW and then
	// quit, there are many leaks reported. This change appears to fix over
	// 3000 leaks. [BAF 10/27/15]
	XMLPlatformUtils::Terminate();
}

VCOMError CXMLFileImpl::CreateNew(const TXString& rootName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpImpl == NULL )
		return kVCOMError_NotInitialized;

	fLastError				= kVCOMError_XMLFile_Parser;
	fpDomDocument			= NULL;
	fpDocRoot				= NULL;


	try {
		DOMDocumentPtr	pDoc	= fpImpl->createDocument( 0, rootName, 0 );

		if ( pDoc != NULL ) {
			fpDomDocument			= pDoc;
			DOMElementPtr	pNode	= pDoc->getDocumentElement();

			if ( pNode != NULL ) {
				fpDocRoot		= pNode;
				fLastError		= kVCOMError_NoError;
			}
		}
	}
	catch (const XMLException& toCatch) {
		CXMLFileImpl::ConvertXMLError( toCatch.getCode() );	// Get XML error code
	}
	catch (const DOMException& toCatch) {
		CXMLFileImpl::ConvertXMLError( (DOMException::ExceptionCode)toCatch.code );	// Get DOM error code
	}
	catch (...) {
		fLastError = kVCOMError_XMLFile_Parser;
	}
	
	return fLastError;
}

VCOMError CXMLFileImpl::ReadFile(IFileIdentifier* pFileID)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpImpl == NULL )
		return kVCOMError_NotInitialized;
	if ( pFileID == NULL )
		return kVCOMError_InvalidArg;

	TXString		fileFullPath;
	if ( VCOM_FAILED( pFileID->GetFileFullPath( fileFullPath ) ) )
		return kVCOMError_Failed;

	if ( fileFullPath.IsEmpty() )
		return kVCOMError_Failed;

	//fileFullPath.Replace( "\\", "/" );
	// This does not create a valid URL. Xerces already correctly handles file paths, so
	// doing extra work to trick it into thinking a path is a URL is misguided. (If one
	// were feeling like being misguided, the #if 0 below would be almost right. Except 
	// it doesn't work, possibly because it creates file://blah/blahblah rather than the 
	// allegedly correct file://///blah/blahblah
	// Anyway, commenting it out to fix  problem with Win UNC paths, 
 	// B061213 "Loss of Data, Registry must be deleted, Saving User folder to Server." - JDW

#if 0 // GS_WIN
	// See comment block above.
	// needs #include <Shlwapi.h>, #include <WinInet.h>

	TCHAR	pszUrl[INTERNET_MAX_URL_LENGTH + 1];
	DWORD	lengthOfURL = INTERNET_MAX_URL_LENGTH;
	HRESULT result = ::UrlCreateFromPath( fileFullPath, pszUrl,	&lengthOfURL, 0 );

	if ( result == S_OK || result == S_FALSE /*already a URL*/ ) 
		fileFullPath = pszUrl;
	else
		return kVCOMError_InvalidArg;
#endif

#ifndef _WINDOWS
	TXChar	firstCh		= fileFullPath.GetAt( 0 );
	if ( firstCh != '/' && firstCh != '\\' && firstCh != ':' ) {
		int				at			= fileFullPath.Find( '\\' );
		int				at1			= fileFullPath.Find( '/' );
		if ( at < 0 )						at			= at1;
		else if ( at1 >= 0 && at1 < at )	at			= at1;

		int				at2			= fileFullPath.Find( ':' );
		if ( at < 0 )						at			= at2;
		else if ( at2 >= 0 && at2 < at )	at			= at2;

		if ( at >= 0 ) {
			TXString	path	= fileFullPath.Mid( at );
			fileFullPath		= path;
		}
	}
#endif
	
	fLastError			= kVCOMError_XMLFile_Parser;
	fpDomDocument		= NULL;
	fpDocRoot			= NULL;
    ErrorHandler* errorHandler = NULL;


	if ( fpXercesDOMParser )
    {
        errorHandler = fpXercesDOMParser->getErrorHandler();
        fpXercesDOMParser->setErrorHandler(NULL);
        if (errorHandler)
            delete errorHandler;
		delete fpXercesDOMParser;
    }

	fpXercesDOMParser	= new TaggingDOMParser();

	if ( fpXercesDOMParser != NULL ) {
		try {
            errorHandler = fpXercesDOMParser->getErrorHandler();    // Null now, but someday maybe...
            fpXercesDOMParser->setErrorHandler(new XmlDomErrorHandler(errorHandler));

#ifdef GS_LIN
            // LINUX_IMPLEMENTATION - done
            fpXercesDOMParser->parse( fileFullPath.operator const char*() );
#else
            fpXercesDOMParser->parse( fileFullPath.operator const char*() );
#endif

			fpDomDocument = fpXercesDOMParser->getDocument();

			// Now that the document is loaded, initialize the root pointer
			if (fpDomDocument != NULL) {
				fpDocRoot	= fpDomDocument->getDocumentElement();
				fLastError	= fpDocRoot ? kVCOMError_NoError : kVCOMError_XMLFile_UnknownError;
			}
			else {
				fLastError = kVCOMError_XMLFile_MemoryError;
			}
		}
		catch (const XMLException& toCatch) {
			CXMLFileImpl::ConvertXMLError( toCatch.getCode() );	// Get XML error code
		}
		catch (const DOMException& toCatch) {
			CXMLFileImpl::ConvertXMLError( (DOMException::ExceptionCode)toCatch.code );	// Get DOM error code
		}
		catch (...) {
			fLastError = kVCOMError_XMLFile_Parser;
		}
	}

	return fLastError;
}

VCOMError CXMLFileImpl::ReadBuffer(IXMLFileIOBuffer* pInputBuffer, EXMLEncoding encoding)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpImpl == NULL )
		return kVCOMError_NotInitialized;
	if ( pInputBuffer == NULL )
		return kVCOMError_InvalidArg;

	fLastError			= kVCOMError_XMLFile_Parser;
	fpDomDocument		= NULL;
	fpDocRoot			= NULL;
    ErrorHandler* errorHandler = NULL;


    if ( fpXercesDOMParser )
    {
        errorHandler = fpXercesDOMParser->getErrorHandler();
        fpXercesDOMParser->setErrorHandler(NULL);
        if (errorHandler)
            delete errorHandler;
        delete fpXercesDOMParser;
    }

	fpXercesDOMParser	= new TaggingDOMParser();

	if ( fpXercesDOMParser != NULL ) {
        errorHandler = fpXercesDOMParser->getErrorHandler();    // Null now, but someday maybe...
        fpXercesDOMParser->setErrorHandler(new XmlDomErrorHandler(errorHandler));

		size_t		xmlBufferSize		= 0;
		if ( VCOM_SUCCEEDED( pInputBuffer->GetDataSize( xmlBufferSize ) ) ) {

            Uint8*		pXMLBuffer		= new Uint8[ xmlBufferSize + 1 ];

			if ( VCOM_SUCCEEDED( pInputBuffer->CopyDataInto( pXMLBuffer, xmlBufferSize ) ) ) {

				// Create memory buf input source for the parser
				MemBufInputSource* pMemBufIS	= new MemBufInputSource( (const XMLByte*) pXMLBuffer, (unsigned int) xmlBufferSize, "bufID", false ); //-V202
				pMemBufIS->setCopyBufToStream( false );
				switch( encoding ) {
					case eXMLEncoding_UTF8	: pMemBufIS->setEncoding( (XMLCh*) XMLUni::fgUTF8EncodingString );	break;
					case eXMLEncoding_UTF16	: pMemBufIS->setEncoding( (XMLCh*) XMLUni::fgUTF16EncodingString );	break;
					default					: pMemBufIS->setEncoding( (XMLCh*) XMLUni::fgUTF8EncodingString );	break;
				}

				fpDomDocument = NULL;

				try {
					fpXercesDOMParser->parse( *pMemBufIS );

					fpDomDocument = fpXercesDOMParser->getDocument();

					// Now that the document is loaded, initialize the root pointer
					if (fpDomDocument != NULL) {
						fpDocRoot	= fpDomDocument->getDocumentElement();
						fLastError	= fpDocRoot ? kVCOMError_NoError : kVCOMError_XMLFile_UnknownError;
					}
					else {
						fLastError = kVCOMError_XMLFile_MemoryError;
					}
				}
				catch (const XMLException& toCatch) {
					CXMLFileImpl::ConvertXMLError( toCatch.getCode() );	// Get XML error code
				}
				catch (const DOMException& toCatch) {
					CXMLFileImpl::ConvertXMLError( (DOMException::ExceptionCode)toCatch.code );	// Get DOM error code
				}
				catch (...) {
					fLastError = kVCOMError_XMLFile_Parser;
				}

				delete pMemBufIS;
			}

			delete[] pXMLBuffer;
			pXMLBuffer		= NULL;
		}
	}

	return fLastError;
}

VCOMError CXMLFileImpl::WriteFile(IFileIdentifier* pFileID, EXMLEncoding encoding)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpImpl == NULL )
		return kVCOMError_NotInitialized;
	if ( pFileID == NULL )
		return kVCOMError_InvalidArg;

	TXString		fileFullPath;
	if ( VCOM_FAILED( pFileID->GetFileFullPath( fileFullPath ) ) )
		return kVCOMError_Failed;
		
	if ( fileFullPath.IsEmpty() )
		return kVCOMError_Failed;

#ifndef _WINDOWS
	char	firstCh	= fileFullPath.GetAt( 0 );
	if ( firstCh != '/' && firstCh != '\\' && firstCh != ':' ) {
		int				at			= fileFullPath.Find( '\\' );
		int				at1			= fileFullPath.Find( '/' );
		if ( at < 0 )						at			= at1;
		else if ( at1 >= 0 && at1 < at )	at			= at1;

		int				at2			= fileFullPath.Find( ':' );
		if ( at < 0 )						at			= at2;
		else if ( at2 >= 0 && at2 < at )	at			= at2;

		if ( at >= 0 ) {
			TXString	path	= fileFullPath.Mid( at );
			fileFullPath		= path;
		}
	}

#endif

	fLastError		= kVCOMError_XMLFile_Parser;

	try
	{
		// get a serializer, an instance of DOMWriter
		DOMLSSerializer*	pSerializer = ((DOMImplementationLS*)fpImpl)->createLSSerializer();
        DOMLSOutput* pOutput = ((DOMImplementationLS*)fpImpl)->createLSOutput();
        
		if ( pSerializer && pOutput) {
            
			switch( encoding ) {
				case eXMLEncoding_UTF8	: pOutput->setEncoding( (XMLCh*) XMLUni::fgUTF8EncodingString );	break;
				case eXMLEncoding_UTF16	: pOutput->setEncoding( (XMLCh*) XMLUni::fgUTF16EncodingString );	break;
				default					: pOutput->setEncoding( (XMLCh*) XMLUni::fgUTF8EncodingString );	break;
			}

            DOMConfiguration* pDOMConfig = pSerializer->getDomConfig();
            pDOMConfig->setParameter(XMLUni::fgDOMErrorHandler, this);
            
			// set new line string
			pSerializer->setNewLine( fTheNewLine );

			bool	bCanFormatPrettyPrint = true;
			if ( pDOMConfig->canSetParameter( XMLUni::fgDOMWRTFormatPrettyPrint, bCanFormatPrettyPrint ) )
				pDOMConfig->setParameter( XMLUni::fgDOMWRTFormatPrettyPrint, fbDoFormatPrettyPrint );

#ifdef GS_LIN
			// LINUX_IMPLEMENTATION - done
			LocalFileFormatTarget  myFormTarget( fileFullPath.operator const char*() );
#else
			//LocalFileFormatTarget  myFormTarget( fileFullPath.GetData() );
			LocalFileFormatTarget  myFormTarget( fileFullPath.operator const char*() );
#endif
			pOutput->setByteStream(&myFormTarget);

			// do the serialization through DOMWriter::writeNode();
			if ( fpDomDocument != NULL ) {
				pSerializer->write(fpDomDocument, pOutput );
				fLastError = kVCOMError_NoError;
			}

            pOutput->release();
			pSerializer->release();
		}
    }
	catch (const XMLException& toCatch) {
		CXMLFileImpl::ConvertXMLError( toCatch.getCode() );	// Get XML error code
	}
	catch (const DOMException& toCatch) {
		CXMLFileImpl::ConvertXMLError( (DOMException::ExceptionCode)toCatch.code );	// Get DOM error code
	}
	catch (...) {
		fLastError = kVCOMError_XMLFile_Parser;
	}

	return fLastError;
}

VCOMError CXMLFileImpl::WriteBuffer(IXMLFileIOBuffer* pOutputBuffer, EXMLEncoding encoding)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpImpl == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( pOutputBuffer == NULL )
		return kVCOMError_InvalidArg;

	try
	{
		// get a serializer, an instance of DOMWriter
		DOMLSSerializer*	pSerializer = ((DOMImplementationLS*)fpImpl)->createLSSerializer();
        DOMLSOutput* pOutput = ((DOMImplementationLS*)fpImpl)->createLSOutput();

		if ( pSerializer && pOutput ) {
            DOMConfiguration* pDOMConfig = pSerializer->getDomConfig();
            pDOMConfig->setParameter(XMLUni::fgDOMErrorHandler, this);

			// set new line string
			pSerializer->setNewLine( fTheNewLine );

			bool	bCanFormatPrettyPrint	= true;
			if ( pDOMConfig->canSetParameter( XMLUni::fgDOMWRTFormatPrettyPrint, bCanFormatPrettyPrint ) ) {
				 pDOMConfig->setParameter( XMLUni::fgDOMWRTFormatPrettyPrint, fbDoFormatPrettyPrint );
			}

			// Do the serialization through DOMWriter::writeToString();
			if ( fpDomDocument != NULL ) {
			    MemBufFormatTarget		destination( 1023, XMLPlatformUtils::fgMemoryManager );
                pOutput->setByteStream(&destination);
                
				switch( encoding ) {
					case eXMLEncoding_UTF8	: pOutput->setEncoding( (XMLCh*) XMLUni::fgUTF8EncodingString );	break;
					case eXMLEncoding_UTF16	: pOutput->setEncoding( (XMLCh*) XMLUni::fgUTF16EncodingString );	break;
					default					: pOutput->setEncoding( (XMLCh*) XMLUni::fgUTF8EncodingString );	break;
				}


				if ( pSerializer->write(fpDomDocument, pOutput ) ) {
					void*	pDataBuffer		= NULL;
					size_t	copySize		= 0;
					if ( encoding == eXMLEncoding_UTF16 ) {
						const XMLCh*	xmlOutputStr	= (const XMLCh*) destination.getRawBuffer();
						size_t	len				= XMLString::stringLen( xmlOutputStr );
						copySize						= sizeof(XMLCh) * len;

						pDataBuffer						= (void*) xmlOutputStr;
					}
					else {
						const char*		xmlOutputStr	= (const char*) destination.getRawBuffer();
						copySize						= strlen( xmlOutputStr );

						pDataBuffer						= (void*) xmlOutputStr;
					}

					// copy into the output data
					if ( pDataBuffer ) {
						if ( VCOM_SUCCEEDED( pOutputBuffer->SetData( pDataBuffer, copySize ) ) ) {
							fLastError	= kVCOMError_NoError;
						}
					}
				}
			}

            pOutput->release();
			pSerializer->release();
		}
	}
	catch (const XMLException& toCatch) {
		CXMLFileImpl::ConvertXMLError( toCatch.getCode() );	// Get XML error code
	}
	catch (const DOMException& toCatch) {
		CXMLFileImpl::ConvertXMLError( (DOMException::ExceptionCode)toCatch.code );	// Get DOM error code
	}
	catch (...) {
		fLastError = kVCOMError_XMLFile_Parser;
	}

	return fLastError;
}

VCOMError CXMLFileImpl::GetRootNode(IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpImpl == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	fLastError			= kVCOMError_XMLFile_Parser;
	*ppOutNode			= NULL;

	VCOMError	error	= kVCOMError_Failed;
	if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) ppOutNode ) ) ) {
		CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( *ppOutNode );
		if ( pOutNodeImpl ) {
			pOutNodeImpl->SetData( fpDomDocument, fpDocRoot );
			error		= kVCOMError_NoError;
		}
	}

	return error;
}

VCOMError CXMLFileImpl::GetLastError(EXMLFileError& outError)
{
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	outError	= CXMLFileImpl::GetLastEXMLFileError();
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::SetFeature(EXMLFileFeature feature, bool bValue)
{
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	VCOMError	err		= kVCOMError_NoError;
	switch ( feature ) {
		case eXMLFileFeature_FormatPrettyPrint:
			fbDoFormatPrettyPrint		= bValue;
			break;
		case eXMLFileFeature_SetNewLineCRLF:
			fTheNewLine[0]			= chCR;
			fTheNewLine[1]			= chLF;
			fTheNewLine[2]			= chNull;
			break;
		case eXMLFileFeature_SetNewLineCR:
			fTheNewLine[0]			= chCR;
			fTheNewLine[1]			= chNull;
			break;
		case eXMLFileFeature_SetNewLineLF:
			fTheNewLine[0]			= chLF;
			fTheNewLine[1]			= chNull;
			break;
		default:
			err		= kVCOMError_InvalidArg;
			break;
	}

	return err;
}

bool CXMLFileImpl::handleError(const DOMError& domError)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	fLastError	= kVCOMError_XMLFile_DOMError;

	// Instructs the serializer to continue serialization if possible.
    return true;
}

void CXMLFileImpl::resetErrors()
{
}

/*static*/ char CXMLFileImpl::GetPathDelimiter()
{
	return	'/';
}

/*static*/ char CXMLFileImpl::GetArrayStartDelimiter()
{
	return	'[';
}

/*static*/ void CXMLFileImpl::ConvertXMLError(XMLExcepts::Codes error)
{
	fLastError	= kVCOMError_XMLFile_XercesException;
}

/*static*/ void CXMLFileImpl::ConvertXMLError(DOMException::ExceptionCode error)
{
	fLastError	= kVCOMError_XMLFile_DOMError;
}

/*static*/ VCOMError CXMLFileImpl::GetLastError()
{
	return fLastError;
}

/*static*/ void CXMLFileImpl::SetLastError(VCOMError error)
{
	fLastError	= error;
}

/*static*/ bool CXMLFileImpl::IsNameXMLValid(const XMLCh* szString, size_t len)
{
	return XMLChar1_0::isValidName( szString, (unsigned int)len ); //-V202
}

/*static*/ EXMLFileError CXMLFileImpl::GetLastEXMLFileError()
{
	EXMLFileError	res	= eXMLFileError_UnknownError;
	if ( fLastError == kVCOMError_NoError )								res = eXMLFileError_NoError;
	else if ( fLastError == kVCOMError_XMLFile_UnknownError )			res = eXMLFileError_UnknownError;
	else if ( fLastError == kVCOMError_XMLFile_MemoryError )			res = eXMLFileError_MemoryError;
	else if ( fLastError == kVCOMError_XMLFile_Parser )					res = eXMLFileError_Parser;
	else if ( fLastError == kVCOMError_XMLFile_NoAttribute )			res = eXMLFileError_NoAttribute;
	else if ( fLastError == kVCOMError_XMLFile_CannotCreateNode )		res = eXMLFileError_CannotCreateNode;
	else if ( fLastError == kVCOMError_XMLFile_ElementNotFound )		res = eXMLFileError_ElementNotFound;
	else if ( fLastError == kVCOMError_XMLFile_BadArrayIndex )			res = eXMLFileError_BadArrayIndex;
	else if ( fLastError == kVCOMError_XMLFile_BadName )				res = eXMLFileError_BadName;
	else if ( fLastError == kVCOMError_XMLFile_DOMError )				res = eXMLFileError_DOMError;
	else if ( fLastError == kVCOMError_XMLFile_XercesException )		res = eXMLFileError_XercesException;

	return res;
}

/*static*/ void CXMLFileImpl::Tokenize(const TXString& string, TXStringArray& outArray, const char* szTokens, size_t tokensLen, bool doStopTokenizeForSpecialCh /*= false*/, char stopStartCh /*= '\''*/)
{
	outArray.clear();

	TXString	currToken;
	bool		isTokenizeStopped = false;

	size_t	strLen	= string.GetEncodingLength(ETXEncoding::eUTF8);
	for(size_t i=0; i<strLen; i++) {
		UCChar	ch		= string.GetAt( i );

		if ( doStopTokenizeForSpecialCh && ch == stopStartCh )
		{
			isTokenizeStopped = !isTokenizeStopped;
		}

		bool	isToken	= false;
		if ( !isTokenizeStopped )
		{
			for(size_t j=0; j<tokensLen; j++) {
				if ( szTokens[j] == ch ) {
					isToken		= true;
					break;
				}
			}
		}

		if ( isToken ) {
			outArray.push_back( currToken );
			currToken.Clear();
		}
		else {
			currToken		+= ch;
		}
	}

	// put the last item if any
	if ( ! currToken.IsEmpty() ) {
		outArray.push_back( currToken );
		currToken.Clear();
	}
}

VCOMError  CXMLFileImpl::DoSimpleNode(IXMLFileNode* pRefNode, const TXString& nodePath, IXMLFileNode** ppOutNode, TXString& outValue, bool doWrite)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpImpl == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;

	fLastError			= kVCOMError_XMLFile_Parser;

	TXStringArray	arrNodeNames;
	this->Tokenize( nodePath, arrNodeNames, "/", 1, true, '\'' );

	VCOMError		err	= kVCOMError_InvalidArg;
	IXMLFileNodePtr	xmlNode, xmlNextNode;
	TXString		xmlNodeName;

	size_t	nodesCnt	= arrNodeNames.size();
	if ( nodesCnt > 0 ) {
		err		= kVCOMError_NoError;
		for(size_t i=0; i<nodesCnt && VCOM_SUCCEEDED( err ); i++) {
			TXString	nodeName	= arrNodeNames[ i ];

			if ( xmlNode == NULL && pRefNode == NULL ) {
				err = this->GetRootNode( & xmlNode );
				if ( VCOM_SUCCEEDED( err ) ) {
					err = xmlNode->GetNodeName( xmlNodeName );
					if ( VCOM_SUCCEEDED( err ) && nodeName != xmlNodeName ) {
						err	= kVCOMError_XMLFile_ElementNotFound;
					}
				}
			}
			else {
				if ( pRefNode ) {
					xmlNode		= pRefNode;
					pRefNode	= NULL;
				}

				if ( nodeName.GetEncodingLength(ETXEncoding::eUTF8) > 0 && nodeName.GetAt(0) == '$' ) {
					nodeName	= nodeName.Mid( 1 );
					if ( doWrite ) {
						err			= xmlNode->SetNodeAttributeValue( nodeName, outValue );
					}
					else {
						err			= xmlNode->GetNodeAttributeValue( nodeName, outValue );
					}
					xmlNode.Release();

					// Force Stop! We have found attribute so we cannot continue
					break;
				}
				else {
					ptrdiff_t	startAt		= nodeName.Find( '[' );
					ptrdiff_t	endAt		= nodeName.Find( ']' );
					bool		hasIndex	= startAt >= 0 && startAt < endAt - 1;
					size_t		index		= size_t(-1);
					TXString	attrName, attrValue;
					if ( hasIndex ) {
						TXString strIndex	= nodeName.Mid( startAt + 1, endAt - startAt - 1 );
						if ( strIndex.GetEncodingLength(ETXEncoding::eUTF8) > 0 && strIndex.GetAt( 0 ) == '$' )
						{
							TXStringArray	arrTokens;
							this->Tokenize( strIndex, arrTokens, "=", 1, true, '\'' );
							if ( arrTokens.size() == 2 )
							{
								attrName	= arrTokens[ 0 ]; attrName.Trim();
								attrValue	= arrTokens[ 1 ]; attrValue.Trim();

								attrName	= attrName.Mid( 1 ); // strip the '$'
								if ( attrValue.GetEncodingLength(ETXEncoding::eUTF8) > 2 && attrValue.GetAt(0) == '\'' && attrValue.GetAt( attrValue.GetEncodingLength(ETXEncoding::eUTF8) - 1 ) == '\'' )
								{
									attrValue	= attrValue.Mid( 1, attrValue.GetEncodingLength(ETXEncoding::eUTF8) - 2 );
								}
							}
						}
						else
						{
							index				= strIndex.atoi();
						}

						nodeName			= nodeName.Left( startAt );
					}

					if ( hasIndex && index != size_t(-1) )
					{
						err		= xmlNode->GetChildNode( nodeName, index, & xmlNextNode );
					}
					else if ( hasIndex && ! attrName.IsEmpty() && ! attrValue.IsEmpty() )
					{
						err		= xmlNode->GetChildNode( nodeName, attrName, attrValue, & xmlNextNode );
					}
					else
					{
						err		= xmlNode->GetChildNode( nodeName, & xmlNextNode );
					}

					if ( doWrite ) {
						if ( err == kVCOMError_XMLFile_ElementNotFound || err == kVCOMError_XMLFile_BadArrayIndex ) {
							err	= xmlNode->CreateChildNode( nodeName, & xmlNextNode );
						}
					}

					xmlNode	= xmlNextNode;
				}
			}
		}
	}

	if ( VCOM_SUCCEEDED( err ) && xmlNode ) {
		if ( doWrite ) {
			xmlNode->SetNodeValue( outValue );
		}
		else {
			xmlNode->GetNodeValue( outValue );
		}
	}

	CXMLFileNodeImpl*	xmlNodeImpl	= static_cast<CXMLFileNodeImpl*>( (IVWUnknown*) xmlNode );
	if ( VCOM_SUCCEEDED( err ) && xmlNodeImpl ) {
		if ( ppOutNode && *ppOutNode == NULL ) {
			::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) ppOutNode );
		}

		if ( ppOutNode ) {
			CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( *ppOutNode );
			if ( pOutNodeImpl ) {
				pOutNodeImpl->SetData( fpDomDocument, xmlNodeImpl->GetNode() );
				err		= kVCOMError_NoError;
			}
		}
	}

	return err;
}

VCOMError CXMLFileImpl::GetSimpleNode(const TXString& nodePath, IXMLFileNode** ppOutNode)
{
	TXString	value;
	return this->DoSimpleNode( NULL, nodePath, ppOutNode, value, false );
}

VCOMError CXMLFileImpl::GetSimpleNode(IXMLFileNode* pRefNode, const TXString& nodePath, IXMLFileNode** ppOutNode)
{
	TXString	value;
	return this->DoSimpleNode( pRefNode, nodePath, ppOutNode, value, false );
}

VCOMError CXMLFileImpl::GetSimpleValue(const TXString& nodePath, TXString& outValue)
{
	CXMLFileNodeImpl	node;
	IXMLFileNode*		nodePtr	= & node;
	return this->DoSimpleNode( NULL, nodePath, & nodePtr, outValue, false );
}

VCOMError CXMLFileImpl::GetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, TXString& outValue)
{
	CXMLFileNodeImpl	node;
	IXMLFileNode*		nodePtr	= & node;
	return this->DoSimpleNode( pRefNode, nodePath, & nodePtr, outValue, false );
}

TXString CXMLFileImpl::GetSimpleValue(const TXString& nodePath, const TXString& defaultValue)
{
	TXString	value;
	if ( VCOM_FAILED( this->GetSimpleValue( nodePath, value ) ) ) {
		value	= defaultValue;
	}

	return value;
}

TXString CXMLFileImpl::GetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, const TXString& defaultValue)
{
	TXString	value;
	if ( VCOM_FAILED( this->GetSimpleValue( pRefNode, nodePath, value ) ) ) {
		value	= defaultValue;
	}

	return value;
}

VCOMError CXMLFileImpl::SetSimpleValue(const TXString& nodePath, const TXString& value)
{
	TXString	localValue	= value;
	return this->DoSimpleNode( NULL, nodePath, NULL, localValue, true );
}

VCOMError CXMLFileImpl::SetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, const TXString& value)
{
	TXString	localValue	= value;
	return this->DoSimpleNode( pRefNode, nodePath, NULL, localValue, true );
}

bool CXMLFileImpl::GetSimpleExist(const TXString& nodePath)
{
	TXString	value;
	return VCOM_SUCCEEDED( this->GetSimpleValue( nodePath, value ) );
}

bool CXMLFileImpl::GetSimpleExist(IXMLFileNode* pRefNode, const TXString& nodePath)
{
	TXString	value;
	return VCOM_SUCCEEDED( this->GetSimpleValue( pRefNode, nodePath, value ) );
}
#endif
