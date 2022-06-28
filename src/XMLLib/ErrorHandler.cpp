#ifndef DONT_USE_XERCES_AS_XMLLIB
// ErrorHandler.cpp
//
// Error handling code for the XML parser.
#include "Prefix/StdAfx.h"

#include "ErrorHandler.h"

using namespace VectorworksMVR::XML;

bool XMLErrorHandler::handleError(const DOMError &domError)
{
    // Display whatever error message passed from the serializer
    if (domError.getSeverity() == DOMError::DOM_SEVERITY_WARNING)
        ::std::strcpy(errorString, "\nWarning Message: ");

    else if (domError.getSeverity() == DOMError::DOM_SEVERITY_ERROR)
        ::std::strcpy(errorString, "\nError Message: ");

    else
        ::std::strcpy(errorString, "\nFatal Message: ");

    char *msg = XMLString::transcode(domError.getMessage());
    ::std::strcpy(errorString, msg);
    XMLString::release(&msg);

    // Instructs the serializer to continue serialization if possible.
    return true;
}
#endif
