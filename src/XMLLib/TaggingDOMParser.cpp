#include "Prefix/StdAfx.h"

#include "TaggingDOMParser.h"

TaggingDOMParser::TaggingDOMParser()
{
    std::cout << "INIT TaggingDOMParser" << std::endl;
}

void TaggingDOMParser::startElement(
    const XMLElementDecl &elemDecl,
    const unsigned int uriId,
    const XMLCh *const prefixName,
    const RefVectorOf< XMLAttr > &attrList,
    const unsigned int attrCount,
    const bool isEmpty,
    const bool isRoot
    ) 
{
    std::cout << "startElement" << std::endl;

    // supercall
    XercesDOMParser::startElement(elemDecl, uriId, prefixName, attrList, attrCount, isEmpty, isRoot);

}

void TaggingDOMParser::startDocument() 
{
        std::cout << "startDocument" << std::endl;

    // supercall
    XercesDOMParser::startDocument();

}

void TaggingDOMParser::docCharacters
(
    const   XMLCh* const    chars
    , const XMLSize_t       length
    , const bool            cdataSection
)
{
    TXString txchars (chars, length);
    const Locator* locator = getScanner()->getLocator();
    std::cout << "docCharacters " << txchars.GetCharPtr() << " LineNumber " << locator->getLineNumber() << std::endl;

    // supercall
    XercesDOMParser::docCharacters(chars, length, cdataSection);
};