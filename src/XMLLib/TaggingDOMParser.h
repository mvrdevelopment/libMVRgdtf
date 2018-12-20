#include "XercesSupport.h"

class TagDataHandler;

struct Tag {
    public:
        inline Tag()
        :    lineNumber(-1),
            columnNumber(-1),
            referenceCount(0){
        }

        inline void link(){
            ++referenceCount;
        }

        inline void unlink(){
            assert(referenceCount>0);
            --referenceCount;
            if(referenceCount <= 0)
                delete this;
        }

    public:
        std::string systemID;
        int lineNumber;
        int columnNumber;

    private:
        int referenceCount;

    protected:
        inline ~Tag(){}
};

class TaggingDOMParser : public XercesDOMParser 
{
    public:
    TaggingDOMParser();
    ~TaggingDOMParser();
        virtual void startElement
    (
        const   XMLElementDecl&         elemDecl
        , const unsigned int            urlId
        , const XMLCh* const            elemPrefix
        , const RefVectorOf<XMLAttr>&   attrList
        , const XMLSize_t               attrCount
        , const bool                    isEmpty
        , const bool                    isRoot
    ); 

    private:
    TagDataHandler* dataHandler;

    protected:
        Tag* createTag();
   

};

