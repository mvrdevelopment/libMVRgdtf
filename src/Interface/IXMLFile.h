//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License


#pragma once

#include "IFileIdentifier.h"

namespace VectorWorks
{
	namespace Filing
	{
		// ----------------------------------------------------------------------------------------------------
		enum EXMLEncoding {
			eXMLEncoding_UTF8,
			eXMLEncoding_UTF16
		};

		// ----------------------------------------------------------------------------------------------------
		const VCOMError		kVCOMError_XMLFile_UnknownError			= 100;
		const VCOMError		kVCOMError_XMLFile_MemoryError			= 101;
		const VCOMError		kVCOMError_XMLFile_Parser				= 102;
		const VCOMError		kVCOMError_XMLFile_NoAttribute			= 103;
		const VCOMError		kVCOMError_XMLFile_CannotCreateNode		= 104;
		const VCOMError		kVCOMError_XMLFile_ElementNotFound		= 105;
		const VCOMError		kVCOMError_XMLFile_BadArrayIndex		= 106;
		const VCOMError		kVCOMError_XMLFile_BadName				= 107;
		const VCOMError		kVCOMError_XMLFile_DOMError				= 108;
		const VCOMError		kVCOMError_XMLFile_XercesException		= 109;

		// ----------------------------------------------------------------------------------------------------
		enum EXMLFileError
		{
			eXMLFileError_NoError,
			eXMLFileError_UnknownError,
			eXMLFileError_MemoryError,
			eXMLFileError_Parser,
			eXMLFileError_NoAttribute,
			eXMLFileError_CannotCreateNode,
			eXMLFileError_ElementNotFound,
			eXMLFileError_BadArrayIndex,
			eXMLFileError_BadName,
			eXMLFileError_DOMError,
			eXMLFileError_XercesException,
		};

		// ----------------------------------------------------------------------------------------------------
		enum EXMLFileFeature
		{
			eXMLFileFeature_FormatPrettyPrint,
			eXMLFileFeature_SetNewLineCRLF,
			eXMLFileFeature_SetNewLineCR,
			eXMLFileFeature_SetNewLineLF,
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IXMLFileNode : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	IsEmpty(bool& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetNodeName(TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetNodeName(const TXString& outName) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetNodeValue(TXString& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetNodeValue(const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteNode() = 0;
			virtual VCOMError VCOM_CALLTYPE	GetNodeAttributeValue(const TXString& attrName, TXString& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetNodeAttributeValue(const TXString& attrName, const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteNodeAttribute(const TXString& attrName) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetNodeCDATA(TXString& outData) = 0;
			virtual VCOMError VCOM_CALLTYPE GetNodeCDATA(void* binaryData, size_t& inOutNumBytes) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetNodeCDATA(const TXString& data) = 0;
			virtual VCOMError VCOM_CALLTYPE SetNodeCDATA(const void* const binaryData, size_t numBytes) = 0;
			virtual VCOMError VCOM_CALLTYPE	DeleteNodeCDATA() = 0;
			virtual VCOMError VCOM_CALLTYPE	CreateChildNode(const TXString& name, IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetChildNode(const TXString& name, IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetChildNode(const TXString& name, size_t arrayIndex, IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetChildNode(const TXString& name, const TXString& attrName, const TXString& attrValue, IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetParentNode(IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetFirstChildNode(IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetLastChildNode(IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetNextSiblingNode(IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetPrevSiblingNode(IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	FindChildNode(const TXString& nodeName, IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetLastError(EXMLFileError& outError) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetNodeAttributes(TXStringArray& outArrNodeAttributes) = 0;
            virtual VCOMError VCOM_CALLTYPE CreateChildNodeBeforeIndex(const TXString& name, size_t index, IXMLFileNode** ppOutNode) = 0;
            virtual VCOMError VCOM_CALLTYPE AddCopyOfExistingNodeBeforeIndex(const IXMLFileNode * existingNode, size_t index, IXMLFileNode** ppOutNode) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		class DYNAMIC_ATTRIBUTE IXMLFileIOBuffer
		{
		public:
			virtual							~IXMLFileIOBuffer()		{}

			virtual	VCOMError VCOM_CALLTYPE	GetDataSize(size_t& outSize) = 0;
			virtual VCOMError VCOM_CALLTYPE	CopyDataInto(void* pBuffer, size_t bufferSize) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetData(void* pBuffer, size_t bufferSize) = 0;
		};

		// ----------------------------------------------------------------------------------------------------
		// {7274D087-3799-11DB-9C35-00508D5E9851}
		static const VWIID IID_XMLFile = { 0x7274D087, 0x3799, 0x11DB, { 0x9C, 0x35, 0x00, 0x50, 0x8D, 0x5E, 0x98, 0x51 } };

		class DYNAMIC_ATTRIBUTE IXMLFile : public IVWUnknown
		{
		public:
			virtual VCOMError VCOM_CALLTYPE	CreateNew(const TXString& rootName) = 0;
			virtual VCOMError VCOM_CALLTYPE	ReadFile(IFileIdentifier* pFileID) = 0;
			virtual VCOMError VCOM_CALLTYPE	ReadBuffer(IXMLFileIOBuffer* pInputBuffer, EXMLEncoding encoding) = 0;
			virtual VCOMError VCOM_CALLTYPE	WriteFile(IFileIdentifier* pFileID, EXMLEncoding encoding) = 0;
			virtual VCOMError VCOM_CALLTYPE	WriteBuffer(IXMLFileIOBuffer* pOutputBuffer, EXMLEncoding encoding) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetRootNode(IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE	GetLastError(EXMLFileError& outError) = 0;
			virtual VCOMError VCOM_CALLTYPE	SetFeature(EXMLFileFeature feature, bool bValue) = 0;

			// nodePath: <NodeName> { '/' <NodeName> [ '[' <itemIndex> ']' ] } [ '$' <AttrName> ]
			// nodePath: <NodeName> { '/' <NodeName> [ '[' <itemIndex> | $<AttrName>= \'<AttrValue>\'']' ] } [ '$' <AttrName> ]
			// nodePath: NodeName1/NodeName2/NodeName3
			// nodePath: NodeName1/NodeName2[1]/NodeName3
			// nodePath: NodeName1/NodeName2/$attrName
			// nodePath: NodeName1/NodeName2[$name='value']/NodeName3
			virtual VCOMError VCOM_CALLTYPE GetSimpleNode(const TXString& nodePath, IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSimpleNode(IXMLFileNode* pRefNode, const TXString& nodePath, IXMLFileNode** ppOutNode) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSimpleValue(const TXString& nodePath, TXString& outValue) = 0;
			virtual VCOMError VCOM_CALLTYPE GetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, TXString& outValue) = 0;
			virtual TXString  VCOM_CALLTYPE	GetSimpleValue(const TXString& nodePath, const TXString& defaultValue) = 0;
			virtual TXString  VCOM_CALLTYPE	GetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, const TXString& defaultValue) = 0;
			virtual VCOMError VCOM_CALLTYPE SetSimpleValue(const TXString& nodePath, const TXString& value) = 0;
			virtual VCOMError VCOM_CALLTYPE SetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, const TXString& value) = 0;
			virtual bool	  VCOM_CALLTYPE	GetSimpleExist(const TXString& nodePath) = 0;							// check to see if exist -- for organizing loops more efficiently
			virtual bool	  VCOM_CALLTYPE	GetSimpleExist(IXMLFileNode* pRefNode, const TXString& nodePath) = 0;	// check to see if exist
		};

		// ----------------------------------------------------------------------------------------------------
		typedef VCOMPtr<IXMLFile>			IXMLFilePtr;
		typedef VCOMPtr<IXMLFileNode>		IXMLFileNodePtr;
	}
}