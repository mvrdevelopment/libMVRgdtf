#ifndef DONT_USE_XERCES_AS_XMLLIB
#pragma once
#include "Include/VectorworksMVR.h"

#include "XercesSupport.h"

namespace VectorworksMVR
{
	namespace XML
	{
		using namespace VectorworksMVR::Filing;

		// ----------------------------------------------------------------------------------------------------
		// {D9B3E5F2-3799-11DB-9C35-00508D5E9851}
		static const VWIID IID_XMLFileNode = { 0xD9B3E5F2, 0x3799, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };

		class CXMLFileNodeImpl : public VCOMImpl<IXMLFileNode>
		{
		public:
			CXMLFileNodeImpl();
			virtual			~CXMLFileNodeImpl();

			void			SetData(DOMDocumentPtr pDomDocument, DOMNodePtr pNode);
			DOMNodePtr		GetNode() const;

			// IXMLFileNode
		public:
			virtual VCOMError	VCOM_CALLTYPE	IsEmpty(bool& outValue);
			virtual VCOMError	VCOM_CALLTYPE	GetNodeName(TXString& outName);
			virtual VCOMError   VCOM_CALLTYPE   SetNodeName(const TXString& newName);
			virtual VCOMError	VCOM_CALLTYPE	GetNodeValue(TXString& outValue);
			virtual VCOMError	VCOM_CALLTYPE	SetNodeValue(const TXString& value);
			virtual VCOMError	VCOM_CALLTYPE	DeleteNode();
			virtual VCOMError	VCOM_CALLTYPE	GetNodeAttributeValue(const TXString& attrName, TXString& outValue);
			virtual VCOMError	VCOM_CALLTYPE	SetNodeAttributeValue(const TXString& attrName, const TXString& value);
			virtual VCOMError	VCOM_CALLTYPE	DeleteNodeAttribute(const TXString& attrName);
			virtual VCOMError	VCOM_CALLTYPE	GetNodeCDATA(TXString& outData);
			virtual VCOMError	VCOM_CALLTYPE   GetNodeCDATA(void* binaryData, size_t& inOutNumBytes);
			virtual VCOMError	VCOM_CALLTYPE	SetNodeCDATA(const TXString& data);
			virtual VCOMError   VCOM_CALLTYPE   SetNodeCDATA(const void* const binaryData, size_t numBytes);
			virtual VCOMError	VCOM_CALLTYPE	DeleteNodeCDATA();
			virtual VCOMError	VCOM_CALLTYPE	CreateChildNode(const TXString& name, IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetChildNode(const TXString& name, IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetChildNode(const TXString& name, size_t arrayIndex, IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetChildNode(const TXString& name, const TXString& attrName, const TXString& attrValue, IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetParentNode(IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetFirstChildNode(IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetLastChildNode(IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetNextSiblingNode(IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetPrevSiblingNode(IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	FindChildNode(const TXString& nodeName, IXMLFileNode** ppOutNode);
			virtual VCOMError	VCOM_CALLTYPE	GetLastError(EXMLFileError& outError);
			virtual VCOMError 	VCOM_CALLTYPE	GetNodeAttributes(TXStringArray& outArrNodeAttributes);
			virtual VCOMError 	VCOM_CALLTYPE	CreateChildNodeBeforeIndex(const TXString& name, size_t index, IXMLFileNode** ppOutNode);
			virtual VCOMError   VCOM_CALLTYPE   AddCopyOfExistingNodeBeforeIndex(const IXMLFileNode* existingNode, size_t index, IXMLFileNode** ppOutNode);
			virtual VCOMError   VCOM_CALLTYPE   GetLineNumber(size_t& line, size_t& column);

		private:
			VCOMError						FindAttribute(const TXString& attrName, DOMAttrPtr& outFoundAttr);

		private:
			DOMDocumentPtr		fpDomDocument;
			DOMNodePtr			fpNode;
		};
	}
}

#endif
