#include "XercesSupport.h"


class TaggingDOMParser : public XercesDOMParser 
{
    public:
    TaggingDOMParser();
    virtual void startElement (const XMLElementDecl &elemDecl, const unsigned int uriId, const XMLCh *const prefixName, const RefVectorOf< XERCES_CPP_NAMESPACE::XMLAttr > &attrList, const unsigned int attrCount, const bool isEmpty, const bool isRoot);
    virtual void startDocument ();
    virtual void docCharacters
    (
        const   XMLCh* const    chars
        , const XMLSize_t       length
        , const bool            cdataSection
    );
};