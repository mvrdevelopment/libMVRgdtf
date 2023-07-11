#ifndef DONT_USE_XERCES_AS_XMLLIB
#include "Prefix/StdAfx.h"

#include "XMLCore.Xerces.h"

#include "XMLFileImpl.h"
#include "XMLFileNodeImpl.h"
#include "TaggingDOMParser.h"

using namespace VectorworksMVR::Filing;
using namespace VectorworksMVR::XML;

// ----------------------------------------------------------------------------------------------------
CXMLFileNodeImpl::CXMLFileNodeImpl()
{
	fpDomDocument	= NULL;
	fpNode			= NULL;
}

CXMLFileNodeImpl::~CXMLFileNodeImpl()
{
	fpDomDocument	= NULL;
	fpNode			= NULL;
}

void CXMLFileNodeImpl::SetData(DOMDocumentPtr pDomDocument, DOMNodePtr pNode)
{
	fpDomDocument	= pDomDocument;
	fpNode			= pNode;
}

DOMNodePtr CXMLFileNodeImpl::GetNode() const
{
	return fpNode;
}

VCOMError CXMLFileNodeImpl::IsEmpty(bool& outValue)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpDomDocument == NULL )
		return kVCOMError_NotInitialized;

	outValue	= fpNode == NULL;
	return kVCOMError_NoError;
}

VCOMError CXMLFileNodeImpl::GetNodeName(TXString& outName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpDomDocument == NULL || fpNode == NULL )
		return kVCOMError_NotInitialized;

	outName	= fpNode->getNodeName();
	
	return kVCOMError_NoError;
}

VCOMError CXMLFileNodeImpl::GetNodeValue(TXString& outValue)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpDomDocument == NULL || fpNode == NULL )
		return kVCOMError_NotInitialized;

	VCOMError	error		= kVCOMError_Failed;

	outValue.Clear();
	if ( fpNode->hasChildNodes() ) {
		DOMNodePtr	pFirstChild = fpNode->getFirstChild();
		if ( pFirstChild ) {
			outValue	= pFirstChild->getNodeValue();
	
	
			error					= kVCOMError_NoError;
		}
	}

	return error;
}

VCOMError CXMLFileNodeImpl::SetNodeValue(const TXString& value)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpDomDocument == NULL || fpNode == NULL )
		return kVCOMError_NotInitialized;


	VCOMError	error		= kVCOMError_Failed;

	// If the node already has a text node, simply set the text node's value.  If
	// it does not have a text node, create a new text node and set its value.
	DOMNodePtr	pTextNode	= NULL;
	if ( fpNode->hasChildNodes() ) {
		// Scan all children for a text node
		for (DOMNodePtr pCurNode = fpNode->getFirstChild(); NULL != pCurNode; pCurNode = pCurNode->getNextSibling())
		{
			if ( pCurNode->getNodeType() == DOMNode::TEXT_NODE ) {
				pTextNode	= pCurNode;		// Found a text node
				break;
			}
		}
	}

	if (pTextNode == NULL) {
        DOMText*    nodeDataVal = fpDomDocument->createTextNode(value);

        fpNode->appendChild( nodeDataVal );
		error					= kVCOMError_NoError;
	}
	else {
        pTextNode->setNodeValue( value );
		error					= kVCOMError_NoError;
	}


	return error;
}

VCOMError CXMLFileNodeImpl::DeleteNode()
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;

	if ( fpDomDocument == NULL || fpNode == NULL )
		return kVCOMError_NotInitialized;

	VCOMError	error		= kVCOMError_Failed;

	DOMNodePtr	pParentNode = fpNode->getParentNode();
	if ( pParentNode != NULL ) {
		DOMNodePtr	nextNode	= fpNode->getNextSibling();

		fpNode 		= pParentNode->removeChild( fpNode );
		fpNode->release();
		fpNode		= NULL;

		if ( nextNode )
		{
			// make sure we delete the text after the node if any
			// this fixes VB-97365SDK: Delete an xml node via the class IXMLFileNode and the function DeleteNode() creates an empty row
			// (mac only) the user is complaining about new line that's left after deleting a node
			if ( nextNode->getNodeType() == DOMNode::TEXT_NODE )
			{
				nextNode 		= pParentNode->removeChild( nextNode );
				nextNode->release();
			}
		}

		error		= kVCOMError_NoError;
	}

	return error;
}

VCOMError CXMLFileNodeImpl::FindAttribute(const TXString& attrName, DOMAttrPtr& outFoundAttr)
{
	outFoundAttr					= NULL;

	VCOMError			error		= kVCOMError_Failed;
	DOMNamedNodeMap*	pAttrMap	= fpNode->getAttributes();
	if ( pAttrMap ) {


		error				= kVCOMError_XMLFile_NoAttribute;
		for (XMLSize_t i = 0; i < pAttrMap->getLength(); i++) {
			DOMNodePtr		pAttr			= pAttrMap->item( i );
			const XMLCh*	xmlElementName	= pAttr->getNodeName();

			if ( XMLString::compareString( xmlElementName, attrName ) == 0 ) {
				// Attribute found
				outFoundAttr	= (DOMAttrPtr) pAttr;
				error			= kVCOMError_NoError;
				break;
			}
		}

	}

	return error;
}

VCOMError CXMLFileNodeImpl::GetNodeAttributeValue(const TXString& attrName, TXString& outValue)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpDomDocument == NULL || fpNode == NULL )
		return kVCOMError_NotInitialized;

	DOMAttrPtr		pFoundAttrNode	= NULL;
	VCOMError		error			= this->FindAttribute( attrName, pFoundAttrNode );
	if ( pFoundAttrNode ) {
		outValue	= pFoundAttrNode->getNodeValue();
		



		error							= kVCOMError_NoError;
	}
	else {
			outValue.Clear();
	}
	
	return error;
}

VCOMError CXMLFileNodeImpl::SetNodeAttributeValue(const TXString& attrName, const TXString& value)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpDomDocument == NULL || fpNode == NULL )
		return kVCOMError_NotInitialized;

	DOMAttrPtr		pFoundAttrNode	= NULL;
	VCOMError		error			= this->FindAttribute( attrName, pFoundAttrNode );
	
	if ( error == kVCOMError_XMLFile_NoAttribute || error == kVCOMError_NoError) {

		if ( error == kVCOMError_NoError && pFoundAttrNode ) {
			// if the attribute was found, set the value.
			pFoundAttrNode->setValue( value );
		}
		else if ( error == kVCOMError_XMLFile_NoAttribute ) {
			// if the attribute was not found, create a new attribute with the given value.

			((DOMElementPtr) fpNode)->setAttribute( attrName, value );


		
			error = kVCOMError_NoError;
		}

	}

	return error;
}

VCOMError CXMLFileNodeImpl::DeleteNodeAttribute(const TXString& attrName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpDomDocument == NULL || fpNode == NULL )
		return kVCOMError_NotInitialized;

	DOMAttrPtr		pFoundAttrNode	= NULL;
	VCOMError		error			= this->FindAttribute( attrName, pFoundAttrNode );
	if ( VCOM_SUCCEEDED( error ) ) {
		((DOMElementPtr) fpNode)->removeAttributeNode( pFoundAttrNode );
	}

	return error;
}

VCOMError CXMLFileNodeImpl::GetNodeCDATA(TXString& outData)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;

	CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );

	outData.Clear();
	if ( fpNode->hasChildNodes() ) {

		// Scan all children for element
		for (	DOMNodePtr pCurNode = fpNode->getFirstChild();
				NULL != pCurNode;
				pCurNode = pCurNode->getNextSibling() )
		{
			if ( pCurNode->getNodeType() == DOMNode::CDATA_SECTION_NODE ) {


					outData		= pCurNode->getNodeValue();


				CXMLFileImpl::SetLastError( kVCOMError_NoError );

				break;
			}
		}
	}

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::GetNodeCDATA(void* binaryData, size_t& inOutNumBytes)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;

	CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );

	if ( fpNode->hasChildNodes() ) {

		DOMNodePtr pDataNode = NULL;

		// Scan all children for element
		// Give preference to CDATA nodes, but text nodes are ok too, if 
		// there's only one of them
		for (	DOMNodePtr pCurNode = fpNode->getFirstChild();
			NULL != pCurNode;
			pCurNode = pCurNode->getNextSibling() )
		{
			if ( pCurNode->getNodeType() == DOMNode::CDATA_SECTION_NODE ) {
				pDataNode = pCurNode;
				break;
			}
		}

		if (pDataNode == NULL) {
			for (	DOMNodePtr pCurNode = fpNode->getFirstChild();
				NULL != pCurNode;
				pCurNode = pCurNode->getNextSibling() )
			{
				if ( pCurNode->getNodeType() == DOMNode::TEXT_NODE ) {
					pDataNode = pCurNode;
					break;
				}
			}
		}

		if (pDataNode != NULL) {
			const XMLCh*	xmlNodeData	= pDataNode->getNodeValue();
			if (xmlNodeData) {
				XMLSize_t decodeNumBytes;
				XMLByte* tmpBinaryData = Base64::decodeToXMLByte(xmlNodeData, &decodeNumBytes);

				if (tmpBinaryData != NULL) {
					if (decodeNumBytes > inOutNumBytes) {
						CXMLFileImpl::SetLastError( kVCOMError_XMLFile_MemoryError );
						inOutNumBytes = 0;
					} else {
						memcpy(binaryData, tmpBinaryData, decodeNumBytes); //-V106
						inOutNumBytes = decodeNumBytes;
						CXMLFileImpl::SetLastError( kVCOMError_NoError );
					}
                    delete[] tmpBinaryData;
				} else {
					CXMLFileImpl::SetLastError( kVCOMError_XMLFile_Parser );
				}
			} else {
				CXMLFileImpl::SetLastError( kVCOMError_XMLFile_Parser );
			}
		} else {
			return kVCOMError_Failed;
		}
	}

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::SetNodeCDATA(const TXString& data)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;

	// delete all existing CDATA
	this->DeleteNodeCDATA();

	CXMLFileImpl::SetLastError( kVCOMError_NoError );


	// create the CDATA section
	DOMCDATASection*	pCDATA			= fpDomDocument->createCDATASection( data );
	fpNode->appendChild( pCDATA );



	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::SetNodeCDATA(const void* const binaryData, size_t numBytes)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;

	// delete all existing CDATA
	this->DeleteNodeCDATA();

	CXMLFileImpl::SetLastError( kVCOMError_NoError );

	XMLSize_t encodeNumBytes;
	const char*	xmlByteText = (const char *)Base64::encode((const XMLByte* const)binaryData, (unsigned int) numBytes, &encodeNumBytes); //-V202
	if (xmlByteText != NULL) {



			// create the CDATA section
			DOMCDATASection*	pCDATA			= fpDomDocument->createCDATASection( TXString(xmlByteText) );
			fpNode->appendChild( pCDATA );

        delete[] xmlByteText;
	} else {
		CXMLFileImpl::SetLastError( kVCOMError_XMLFile_MemoryError );
	}

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::DeleteNodeCDATA()
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;

	CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );

	if ( fpNode->hasChildNodes() ) {

		// Scan all children for element
		DOMNodePtr pCurNode = fpNode->getFirstChild();
		while( NULL != pCurNode ) {
			if ( pCurNode->getNodeType() == DOMNode::CDATA_SECTION_NODE ) {
				pCurNode	= fpNode->removeChild( pCurNode );
			}
			
			pCurNode	= pCurNode->getNextSibling();
		}
	}

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::CreateChildNode(const TXString& name, IXMLFileNode** ppOutNode)
{
    return CreateChildNodeBeforeIndex(name, -1, ppOutNode);
}

VCOMError CXMLFileNodeImpl::GetChildNode(const TXString& name, IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	return this->GetChildNode( name, 0, ppOutNode );
}

VCOMError CXMLFileNodeImpl::GetChildNode(const TXString& name, size_t arrayIndex, IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	DOMNodePtr	pFoundChild			= NULL;
	size_t		theSubNodeIndex		= 0;


	if ( ! CXMLFileImpl::IsNameXMLValid( name, name.GetLength()) ) {
		CXMLFileImpl::SetLastError( kVCOMError_XMLFile_BadName );
	}
	else {
		// Scan all children for element
		for (	DOMNodePtr pCurNode = fpNode->getFirstChild();
				NULL != pCurNode;
				pCurNode = pCurNode->getNextSibling())
		{
			if ( pCurNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
				
				const XMLCh*	xmlElementName = pCurNode->getNodeName();

				if ( XMLString::compareString( name, xmlElementName ) == 0 ) {
					if ( theSubNodeIndex == arrayIndex ) {
						pFoundChild		= pCurNode;

						// FOUND!! STOP !!!!
						break;
					}

					theSubNodeIndex++;
				}
			}
		}
	}

	IXMLFileNode*	pResultNode		= NULL;

	if ( pFoundChild ) {
		CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );
		if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
			CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
			if ( pOutNodeImpl ) {
				pOutNodeImpl->SetData( fpDomDocument, pFoundChild );
				CXMLFileImpl::SetLastError( kVCOMError_NoError );

			}
			else {
				pResultNode->Release();
				pResultNode	= NULL;
			}
		}
	}
	else {
		if ( theSubNodeIndex == 0 )
			CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );
		else
			CXMLFileImpl::SetLastError( kVCOMError_XMLFile_BadArrayIndex );
	}

	if ( *ppOutNode ) {
		(*ppOutNode)->Release();
	}
	*ppOutNode		= pResultNode;

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::GetChildNode(const TXString& name, const TXString& attrName, const TXString& attrValue, IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	DOMNodePtr	pFoundChild			= NULL;
	size_t		theSubNodeIndex		= 0;

	if ( ! CXMLFileImpl::IsNameXMLValid( name, XMLString::stringLen((const XMLCh*)name) ) ) {
		CXMLFileImpl::SetLastError( kVCOMError_XMLFile_BadName );
	}
	else {
		CXMLFileNodeImpl	tempNode;
		tempNode.AddRef();
		TXString			tempAttrValue;

		// Scan all children for element
		for (	DOMNodePtr pCurNode = fpNode->getFirstChild();
				NULL != pCurNode;
				pCurNode = pCurNode->getNextSibling())
		{
			if ( pCurNode->getNodeType() == DOMNode::ELEMENT_NODE ) {
				
				const XMLCh*	xmlElementName = pCurNode->getNodeName();

				if ( XMLString::compareString( name, xmlElementName ) == 0 )
				{
					tempNode.SetData( fpDomDocument, pCurNode );
					if ( VCOM_SUCCEEDED( tempNode.GetNodeAttributeValue( attrName, tempAttrValue ) ) )
					{
						if ( attrValue == tempAttrValue ) {
							pFoundChild		= pCurNode;

							// FOUND!! STOP !!!!
							break;
						}
					}
				}
			}
		}
	}

	IXMLFileNode*	pResultNode		= NULL;

	if ( pFoundChild ) {
		CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );
		if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
			CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
			if ( pOutNodeImpl ) {
				pOutNodeImpl->SetData( fpDomDocument, pFoundChild );
				CXMLFileImpl::SetLastError( kVCOMError_NoError );

			}
			else {
				pResultNode->Release();
				pResultNode	= NULL;
			}
		}
	}
	else {
		if ( theSubNodeIndex == 0 )
			CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );
		else
			CXMLFileImpl::SetLastError( kVCOMError_XMLFile_BadArrayIndex );
	}

	if ( *ppOutNode ) {
		(*ppOutNode)->Release();
	}
	*ppOutNode		= pResultNode;

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::GetParentNode(IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	IXMLFileNode*	pResultNode		= NULL;

	CXMLFileImpl::SetLastError( kVCOMError_NoError );
	DOMNodePtr	pParentNode = fpNode->getParentNode();
	if ( pParentNode == NULL ) {
		CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );
	}
	else {
		if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
			CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
			if ( pOutNodeImpl ) {
				pOutNodeImpl->SetData( fpDomDocument, pParentNode );
				CXMLFileImpl::SetLastError( kVCOMError_NoError );
			}
			else {
				pResultNode->Release();
				pResultNode		= NULL;
			}
		}
	}

	if ( *ppOutNode ) {
		(*ppOutNode)->Release();
	}
	*ppOutNode		= pResultNode;

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::GetFirstChildNode(IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );

	IXMLFileNode*	pResultNode		= NULL;

	if ( fpNode->hasChildNodes() ) {

		// Scan all children for element
		for (	DOMNodePtr pCurNode = fpNode->getFirstChild();
				NULL != pCurNode;
				pCurNode = pCurNode->getNextSibling() )
		{
			if ( pCurNode->getNodeType() == DOMNode::ELEMENT_NODE ) {

				CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );

				if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
					CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
					if ( pOutNodeImpl ) {
						pOutNodeImpl->SetData( fpDomDocument, pCurNode );
						CXMLFileImpl::SetLastError( kVCOMError_NoError );
					}
					else {
						pResultNode->Release();
						pResultNode		= NULL;
					}
				}

				break;
			}
		}
	}

	if (*ppOutNode) {
		(*ppOutNode)->Release();
		*ppOutNode		= NULL;
	}
	*ppOutNode		= pResultNode;

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::GetLastChildNode(IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );

	IXMLFileNode*	pResultNode		= NULL;

	if ( fpNode->hasChildNodes() ) {

		// Scan all children for element
		for (	DOMNodePtr pCurNode = fpNode->getLastChild();
				NULL != pCurNode;
				pCurNode = pCurNode->getPreviousSibling() )
		{
			if ( pCurNode->getNodeType() == DOMNode::ELEMENT_NODE ) {

				CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );

				if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
					CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
					if ( pOutNodeImpl ) {
						pOutNodeImpl->SetData( fpDomDocument, pCurNode );
						CXMLFileImpl::SetLastError( kVCOMError_NoError );
					}
					else {
						pResultNode->Release();
						pResultNode		= NULL;
					}
				}

				break;
			}
		}
	}

	if (*ppOutNode) {
		(*ppOutNode)->Release();
		*ppOutNode		= NULL;
	}
	*ppOutNode		= pResultNode;

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::GetNextSiblingNode(IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );

	IXMLFileNode*	pResultNode		= NULL;

	// Scan all children for element
	for (	DOMNodePtr pCurNode = fpNode->getNextSibling();
			NULL != pCurNode;
			pCurNode = pCurNode->getNextSibling() )
	{
		TXString nodeName = pCurNode->getNodeName();
		DOMNode::NodeType nt = pCurNode->getNodeType();

		if ( nt /*pCurNode->getNodeType()*/ == DOMNode::ELEMENT_NODE ) {

			CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );

			if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
				CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
				if ( pOutNodeImpl ) {
					pOutNodeImpl->SetData( fpDomDocument, pCurNode );
					CXMLFileImpl::SetLastError( kVCOMError_NoError );
				}
				else {
					pResultNode->Release();
					pResultNode		= NULL;
				}
			}

			break;
		}
	}

	if (*ppOutNode) {
		(*ppOutNode)->Release();
		*ppOutNode		= NULL;
	}
	*ppOutNode		= pResultNode;

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::GetPrevSiblingNode(IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );

	IXMLFileNode*	pResultNode		= NULL;

	// Scan all children for element
	for (	DOMNodePtr pCurNode = fpNode->getPreviousSibling();
			NULL != pCurNode;
			pCurNode = pCurNode->getPreviousSibling() )
	{
		if ( pCurNode->getNodeType() == DOMNode::ELEMENT_NODE ) {

			CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );

			if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
				CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
				if ( pOutNodeImpl ) {
					pOutNodeImpl->SetData( fpDomDocument, pCurNode );
					CXMLFileImpl::SetLastError( kVCOMError_NoError );
				}
				else {
					pResultNode->Release();
					pResultNode		= NULL;
				}
			}

			break;
		}
	}

	if (*ppOutNode) {
		(*ppOutNode)->Release();
		*ppOutNode		= NULL;
	}
	*ppOutNode		= pResultNode;

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::FindChildNode(const TXString& nodeName, IXMLFileNode** ppOutNode)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;
	if ( ppOutNode == NULL )
		return kVCOMError_InvalidArg;

	CXMLFileImpl::SetLastError( kVCOMError_XMLFile_ElementNotFound );

	IXMLFileNode*	pResultNode		= NULL;

	if ( fpNode->hasChildNodes() ) {

		// Scan all children for element
		for (	DOMNodePtr pCurNode = fpNode->getFirstChild();
				NULL != pCurNode;
				pCurNode = pCurNode->getNextSibling() )
		{
			if ( pCurNode->getNodeType() == DOMNode::ELEMENT_NODE ) {

				const XMLCh*	xmlElementName = pCurNode->getNodeName();

				if ( XMLString::compareString( nodeName, xmlElementName ) == 0 ) {
					CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );

					if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
						CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
						if ( pOutNodeImpl ) {
							pOutNodeImpl->SetData( fpDomDocument, pCurNode );
							CXMLFileImpl::SetLastError( kVCOMError_NoError );
						}
						else {
							pResultNode->Release();
							pResultNode	= NULL;
						}
					}

					break;
				}
			}
		}

	}

	if (*ppOutNode) {
		(*ppOutNode)->Release();
		*ppOutNode		= NULL;
	}
	*ppOutNode		= pResultNode;

	return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::GetLastError(EXMLFileError& outError)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	outError	= CXMLFileImpl::GetLastEXMLFileError();
	return kVCOMError_NoError;
}

VCOMError CXMLFileNodeImpl::GetNodeAttributes(TXStringArray& outArrNodeAttributes)
{
	outArrNodeAttributes.clear();

	VCOMError			error		= kVCOMError_NoError;
	DOMNamedNodeMap*	pAttrMap	= fpNode->getAttributes();
	if ( pAttrMap ) {
		for (XMLSize_t i = 0; i < pAttrMap->getLength(); i++) {
			DOMNodePtr		pAttr			= pAttrMap->item( i );
			const XMLCh*	xmlElementName	= pAttr->getNodeName();



			outArrNodeAttributes.push_back( xmlElementName );


		}
	}

	return error;
}

VCOMError CXMLFileNodeImpl::CreateChildNodeBeforeIndex(const TXString& name, size_t index, IXMLFileNode** ppOutNode)
{
    ASSERTN( kEveryone, fRefCnt > 0 );
    if ( fRefCnt <= 0 )
        return kVCOMError_NotInitialized;
    if ( fpNode == NULL || fpDomDocument == NULL )
        return kVCOMError_NotInitialized;
    if ( ppOutNode == NULL )
        return kVCOMError_InvalidArg;
	
    
    IXMLFileNode*	pResultNode		= NULL;
    
    if ( ! CXMLFileImpl::IsNameXMLValid( name, XMLString::stringLen((const XMLCh*)name) ) ) {
        CXMLFileImpl::SetLastError( kVCOMError_XMLFile_BadName );
    }
    else {
        
        try {
            DOMNodePtr	pChildNode		= fpDomDocument->createElement( name );
            
            if ( pChildNode != NULL ) {
                
                //===================================================================
                // We need to skip whitespace node to get the correct index. [PChang]
  
				bool bInserted = false;

				if(index != size_t(-1))
				{
					DOMNodeList *	list 		= fpNode->getChildNodes();
                	size_t 			listLength 	= list->getLength();
					size_t 			nodeIndex 	= 0;

					for(size_t listItemIndex = 0; listItemIndex < listLength; listItemIndex++)
					{
						DOMNode *pCurrentNode = list->item(listItemIndex);
						
						if ((pCurrentNode->getNodeType() == DOMNode::TEXT_NODE)			// Empty text node
							|| (pCurrentNode->getNodeType() == DOMNode::COMMENT_NODE))	// Comment
						{
							// Skip uninteresting nodes
							continue;
						}
						
						if(nodeIndex == index)	// Match
						{
							fpNode->insertBefore( pChildNode, fpNode->getChildNodes()->item(listItemIndex) );
							bInserted = true;
							break;
						}
						
						++nodeIndex;
					}
				}
				
				// If not inserted, append the child.
				if(!bInserted)
				{
					fpNode->appendChild( pChildNode );
				}
				
				
                CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );
                if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
                    CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
                    if ( pOutNodeImpl ) {
                        pOutNodeImpl->SetData( fpDomDocument, pChildNode );
                        CXMLFileImpl::SetLastError( kVCOMError_NoError );
                        
                    }
                    else {
                        pResultNode->Release();
                        pResultNode	= NULL;
                    }
                }
            }
            else {
                CXMLFileImpl::SetLastError( kVCOMError_XMLFile_CannotCreateNode );
            }
        }
        catch(DOMException ex)
        {
            CXMLFileImpl::SetLastError( kVCOMError_XMLFile_DOMError );
        }
    }
 
    
    if (*ppOutNode) {
        (*ppOutNode)->Release();
        *ppOutNode		= NULL;
    }
    *ppOutNode		= pResultNode;
    
    return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::AddCopyOfExistingNodeBeforeIndex(const IXMLFileNode* existingNode, size_t index, IXMLFileNode** ppOutNode)
{
    ASSERTN( kEveryone, fRefCnt > 0 );
    if ( fRefCnt <= 0 )
        return kVCOMError_NotInitialized;
    if ( fpNode == NULL || fpDomDocument == NULL )
        return kVCOMError_NotInitialized;
    
    IXMLFileNode*	pResultNode		= NULL;
    
    const CXMLFileNodeImpl* nodeToCopy = static_cast<const CXMLFileNodeImpl*>(existingNode);
    if ( nodeToCopy == NULL )
        return kVCOMError_InvalidArg;
    
    try
    {
        DOMNodePtr	pChildNode = fpDomDocument->importNode(nodeToCopy->GetNode(), true);
        
//        nodeToCopy->GetNode()->cloneNode(true);
        
        if ( pChildNode != NULL ) {
            
            //pChildNode = fpDomDocument->adoptNode(pChildNode);
            
            //===================================================================
            // We need to skip whitespace node to get the correct index. [PChang]
            DOMNodeList *list = fpNode->getChildNodes();
            size_t listLength = list->getLength();
            
            if (index < listLength)
            {
                size_t nodeIndex = 0;
                
                for(size_t listItemIndex = 0; listItemIndex < listLength; listItemIndex++)
                {
                    DOMNode *pCurrentNode = list->item(listItemIndex);
                    
                    if ((pCurrentNode->getNodeType() == DOMNode::TEXT_NODE)			// Empty text node
                        || (pCurrentNode->getNodeType() == DOMNode::COMMENT_NODE))	// Comment
                    {
                        // Skip uninteresting nodes
                        continue;
                    }
                    
                    if(nodeIndex == index)	// Match
                    {
                        fpNode->insertBefore( pChildNode, fpNode->getChildNodes()->item(listItemIndex) );
                    }
                    
                    ++nodeIndex;
                }
                
                //===================================================================
                
            }
            else
                fpNode->appendChild( pChildNode );
            
            CXMLFileImpl::SetLastError( kVCOMError_XMLFile_UnknownError );
            
            if ( VCOM_SUCCEEDED( ::VWQueryInterface( IID_XMLFileNode, (IVWUnknown**) & pResultNode ) ) ) {
                CXMLFileNodeImpl*	pOutNodeImpl	= static_cast<CXMLFileNodeImpl*>( pResultNode );
                if ( pOutNodeImpl ) {
                    pOutNodeImpl->SetData( fpDomDocument, pChildNode );
                    CXMLFileImpl::SetLastError( kVCOMError_NoError );
                    
                }
                else {
                    pResultNode->Release();
                    pResultNode	= NULL;
                }
            }
        }
        else {
            CXMLFileImpl::SetLastError( kVCOMError_XMLFile_CannotCreateNode );
        }
    }
    catch(DOMException ex)
    {
        CXMLFileImpl::SetLastError( kVCOMError_XMLFile_DOMError );
    }
    
    
    if (ppOutNode)
    {
        // I'm not sure this necessarily makes sense here...  But if out param referenced something coming in, release
        if (*ppOutNode)
        {
            (*ppOutNode)->Release();
            *ppOutNode		= NULL;
        }
        
        *ppOutNode		= pResultNode;
    }
    
    return CXMLFileImpl::GetLastError();
}

VCOMError CXMLFileNodeImpl::SetNodeName(const TXString &newName)
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;

	VCOMError		error		= kVCOMError_NoError;
	
	const XMLCh*			xmlNamespaceURI	= TXString();
	const XMLCh*			xmlNewName		= newName;
	
	if(!fpDomDocument->renameNode(fpNode, xmlNamespaceURI, xmlNewName))
	{
		error = kVCOMError_Failed;
	}
	
	
	return error;
}

VCOMError CXMLFileNodeImpl::GetLineNumber(size_t& line, size_t& column)
{
	line 	= 0;
	column 	= 0;
	
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt <= 0 )
		return kVCOMError_NotInitialized;
	if ( fpNode == NULL || fpDomDocument == NULL )
		return kVCOMError_NotInitialized;



	void* taggedData = fpNode->getUserData(tagKey);

	Tag* tagObj = (Tag*)taggedData;

	if(tagObj)
	{
		line 	= tagObj->lineNumber;
		column 	= tagObj->columnNumber;

		return kVCOMError_NoError;

	}
	
	return kVCOMError_Failed;
}

#endif
