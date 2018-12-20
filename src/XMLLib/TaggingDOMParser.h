#include "XercesSupport.h"


class TaggingDOMParser : public XercesDOMParser 
{
    public:
    ~TaggingDOMParser();
    void endElement(const   XMLElementDecl& elemDecl, const unsigned int    urlId, const bool            isRoot, const XMLCh* const    elemPrefix
    
    );
};