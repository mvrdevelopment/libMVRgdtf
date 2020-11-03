#ifndef __DONT_USE_XERCES_AS_XMLLIB
#include "XercesSupport.h"

namespace VectorworksMVR
{
	namespace XML
	{
		struct Tag {
			public:
				inline Tag()
				:	lineNumber(-1),
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
					size_t lineNumber;
					size_t columnNumber;

				private:
					int referenceCount;

				protected:
					inline ~Tag(){}
		};

		class TagDataHandler : public DOMUserDataHandler
		{
			private:
				// TaggingDOMParser* parser;

			public:
				TagDataHandler() //: parser(0)
				{
				}

				virtual ~TagDataHandler()
				{
				}

				// inline void setParser(TaggingDOMParser* parser)
				// {
				//     this->parser = parser;
				// }

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
			TagDataHandler dataHandler;

		protected:
			Tag* createTag();


		};
		static const XMLCh        tagKey[] =
		{
			chLatin_V, chLatin_W, chLatin_D, chLatin_a, chLatin_t, chLatin_a, chNull
		};
	}
}
#endif
