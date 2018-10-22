//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#define XERCES_STATIC_LIBRARY 1

#include "xercesc/framework/LocalFileFormatTarget.hpp"
#include "xercesc/framework/MemBufInputSource.hpp"
#include "xercesc/framework/MemBufFormatTarget.hpp"


#include "xercesc/parsers/XercesDOMParser.hpp"
#include "xercesc/parsers/SAXParser.hpp"

#include "xercesc/dom/DOM.hpp"
#include "xercesc/dom/DOMError.hpp"
#include "xercesc/dom/DOMErrorHandler.hpp"

#include "xercesc/sax/HandlerBase.hpp"
#include "xercesc/sax2/SAX2XMLReader.hpp"
#include "xercesc/sax2/XMLReaderFactory.hpp"
#include "xercesc/sax2/ContentHandler.hpp"
#include "xercesc/sax2/DefaultHandler.hpp"
#include "xercesc/sax2/Attributes.hpp"

#include "xercesc/validators/common/Grammar.hpp"
#include "xercesc/validators/schema/SchemaValidator.hpp"

#include "xercesc/util/PlatformUtils.hpp"
#include "xercesc/util/XMLChar.hpp"
#include "xercesc/util/XMLString.hpp"
#include "xercesc/util/XMLUniDefs.hpp"
#include "xercesc/util/Base64.hpp"
#include "xercesc/util/XMLMsgLoader.hpp"

// TODO
XERCES_CPP_NAMESPACE_USE

// ----------------------------------------------------------------------------------------------------
typedef DOMImplementation *		DOMImplementationPtr;
typedef	XercesDOMParser *		XercesDOMParserPtr;
typedef	DOMErrorHandler *		DOMErrorHandlerPtr;
typedef XERCES_CPP_NAMESPACE_QUALIFIER DOMDocument * DOMDocumentPtr;
typedef DOMElement *			DOMElementPtr;
typedef DOMNode *				DOMNodePtr;
typedef	DOMAttr *				DOMAttrPtr;