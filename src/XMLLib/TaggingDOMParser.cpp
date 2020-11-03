#ifndef __DONT_USE_XERCES_AS_XMLLIB
#include "Prefix/StdAfx.h"
#include "TaggingDOMParser.h"

using namespace VectorworksMVR::XML;


TaggingDOMParser::TaggingDOMParser() //: dataHandler(new TagDataHandler())
{
    // dataHandler.setParser(this);
}

TaggingDOMParser::~TaggingDOMParser()
{
    // delete dataHandler;
}

Tag* TaggingDOMParser::createTag()
{
    return new Tag();
}



void TaggingDOMParser::startElement
    (
        const   XMLElementDecl&         elemDecl
        , const unsigned int            urlId
        , const XMLCh* const            elemPrefix
        , const RefVectorOf<XMLAttr>&   attrList
        , const XMLSize_t               attrCount
        , const bool                    isEmpty
        , const bool                    isRoot
    )
{
    // supercall
    XercesDOMParser::startElement(elemDecl, urlId, elemPrefix, attrList, attrCount, isEmpty, isRoot);
    
    const Locator* locator = getScanner()->getLocator();
    Tag* tag = createTag();
    tag->lineNumber   = locator->getLineNumber();
    tag->columnNumber = locator->getColumnNumber();

    XercesDOMParser::fCurrentNode->setUserData(tagKey, tag, &dataHandler);

    tag->link();
}

#endif
