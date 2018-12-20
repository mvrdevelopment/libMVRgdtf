#include "Prefix/StdAfx.h"
#include "TaggingDOMParser.h"

class TagDataHandler : public DOMUserDataHandler 
{
    private:
        TaggingDOMParser* parser;

    public:
        TagDataHandler() : parser(0)
        {
        }

        virtual ~TagDataHandler()
        {
        }

        inline void setParser(TaggingDOMParser* parser)
        {
            this->parser = parser;
        }

        virtual void handle(DOMOperationType operation,
                        const XMLCh* const key,
                        void* data,
                        const DOMNode* src,
                        DOMNode* dst)
        {
            Tag* srcTag = static_cast<Tag*>(data);
            switch(operation){
                // import and clone are basically the same case, in both, the node
                // is cloned
                case NODE_IMPORTED:
                case NODE_CLONED:
                   srcTag->link();
                    break;
                case NODE_DELETED:
                    srcTag->unlink();
                    break;
                case NODE_RENAMED:
                default:
                    // do nothing on rename
                    break;
            }
        }
};

TaggingDOMParser::TaggingDOMParser() : dataHandler(new TagDataHandler())
{
    dataHandler->setParser(this);
}

TaggingDOMParser::~TaggingDOMParser()
{
}

const XMLCh tagKey = (XMLCh)"VWLineNumber";


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
    
    TXString txchars  = elemDecl.getBaseName();

    const Locator* locator = getScanner()->getLocator();
    std::cout << "startElement " << txchars.GetCharPtr() << " LineNumber " << locator->getLineNumber() << std::endl;


    if(!isEmpty)
    {
        Tag* tag = createTag();
        tag->lineNumber   = locator->getLineNumber();
        tag->columnNumber = locator->getColumnNumber();

        XercesDOMParser::fCurrentNode->setUserData(*tagKey, tag, dataHandler);

        tag->link();
    }
}