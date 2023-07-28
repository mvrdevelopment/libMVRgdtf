#ifndef DONT_USE_XERCES_AS_XMLLIB
#pragma once

#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "XercesSupport.h"

namespace VectorworksMVR
{
	namespace XML
	{
		class XMLErrorHandler : public DOMErrorHandler
		{
		public:

			XMLErrorHandler() {};
			~XMLErrorHandler() {};

			/** @name The error handler interface */
			bool handleError(const DOMError& domError);
			void resetErrors() {};

	private :
			/* Unimplemented constructors and operators */
			XMLErrorHandler(const DOMErrorHandler&);
			void operator=(const DOMErrorHandler&);

			char	errorString[256];
		};
	}
}
#endif
#endif
