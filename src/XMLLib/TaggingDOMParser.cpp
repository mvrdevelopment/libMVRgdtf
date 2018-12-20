#include "Prefix/StdAfx.h"

#include "TaggingDOMParser.h"

TaggingDOMParser::~TaggingDOMParser()
{
}

void TaggingDOMParser::endElement
    (
        const   XMLElementDecl& elemDecl
        , const unsigned int    urlId
        , const bool            isRoot
        , const XMLCh* const    elemPrefix
    )
{
        TXString txchars  = elemDecl.getBaseName();

        const Locator* locator = getScanner()->getLocator();
        std::cout << "endElement " << txchars.GetCharPtr() << " LineNumber " << locator->getLineNumber() << std::endl;

    // supercall
    XercesDOMParser::endElement(elemDecl, urlId, isRoot, elemPrefix);
};