#ifdef DONT_USE_XERCES_AS_XMLLIB
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2019 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "XMLFileImpl.h"
#include "XMLFileNodeImpl.h"

using namespace VectorworksMVR::Filing;
using namespace VectorworksMVR::XML;
using namespace VectorworksMVR::VWFC::Tools;

// ----------------------------------------------------------------------------------------------------
CXMLFileNodeImpl::CXMLFileNodeImpl()
{
	fElement = nullptr;
}

CXMLFileNodeImpl::~CXMLFileNodeImpl()
{
}

uint32_t CXMLFileNodeImpl::AddRef()
{
	fRefCnt ++;
	return fRefCnt;
}

uint32_t CXMLFileNodeImpl::Release()
{
	ASSERTN( kEveryone, fRefCnt > 0 );
	if ( fRefCnt > 0 ) {
		fRefCnt --;

		// mechanizm for immediate delete of the interface instance
		if ( fRefCnt == 0 ) {
			// ::GS_VWNotifyDeleteInterface( this ); TODO
			// EXIT IMMEDIATELY! 'this' no longer exist!!!
			return 0;
		}
	}
	return fRefCnt;
}

VCOMError CXMLFileNodeImpl::IsEmpty(bool& outValue)
{
	outValue = fElement;
	return kVCOMError_NoError;
}

VCOMError CXMLFileNodeImpl::GetNodeName(TXString& outName)
{
	if(fElement)
	{
		outName = fElement->Value();
		return kVCOMError_NoError;
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetNodeValue(TXString& outValue)
{
	if(fElement)
	{
		outValue = fElement->GetText();
		return kVCOMError_NoError;
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::SetNodeValue(const TXString& value)
{
	if(fElement)
	{
		fElement->SetText(value.GetCharPtr());
		return kVCOMError_NoError;
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::DeleteNode()
{
	return kVCOMError_NotInitialized;

}

VCOMError CXMLFileNodeImpl::GetNodeAttributeValue(const TXString& attrName, TXString& outValue)
{
	if(fElement)
	{
        const char* attr = fElement->Attribute(attrName);
        if(attr)
        {
            outValue = attr;
            return kVCOMError_NoError;
        }
		
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::SetNodeAttributeValue(const TXString& attrName, const TXString& value)
{
	if(fElement)
	{
		fElement->SetAttribute(attrName.GetCharPtr(), value.GetCharPtr());
		return kVCOMError_NoError;
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::DeleteNodeAttribute(const TXString& attrName)
{
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetNodeCDATA(TXString& outData)
{
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetNodeCDATA(void* binaryData, size_t& inOutNumBytes)
{
	return kVCOMError_NotInitialized;;
}

VCOMError CXMLFileNodeImpl::SetNodeCDATA(const TXString& data)
{
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::SetNodeCDATA(const void* const binaryData, size_t numBytes)
{
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::DeleteNodeCDATA()
{
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::CreateChildNode(const TXString& name, IXMLFileNode** ppOutNode)
{
	if(fElement)
	{
		return GetInterface(fElement->InsertNewChildElement(name), ppOutNode);
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetChildNode(const TXString& name, IXMLFileNode** ppOutNode)
{
	if(fElement)
	{
		tinyxml2::XMLElement* child = fElement->FirstChildElement(name);
        if(child)
        {
            return GetInterface(child, ppOutNode);
        }

		return kVCOMError_Failed;
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetChildNode(const TXString& name, size_t arrayIndex, IXMLFileNode** ppOutNode)
{
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetChildNode(const TXString& name, const TXString& attrName, const TXString& attrValue, IXMLFileNode** ppOutNode)
{
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetParentNode(IXMLFileNode** ppOutNode)
{
	if(fElement)
	{
		return GetInterface(fElement->Parent()->ToElement(), ppOutNode);
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetFirstChildNode(IXMLFileNode** ppOutNode)
{
	if(fElement)
	{
		return GetInterface(fElement->FirstChildElement(), ppOutNode);
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetLastChildNode(IXMLFileNode** ppOutNode)
{
	if(fElement)
	{
		return GetInterface(fElement->FirstChildElement(), ppOutNode);
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetNextSiblingNode(IXMLFileNode** ppOutNode)
{
	if(fElement)
	{
		return GetInterface(fElement->NextSiblingElement(), ppOutNode);
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetPrevSiblingNode(IXMLFileNode** ppOutNode)
{
	if(fElement)
	{
		return GetInterface(fElement->PreviousSiblingElement(), ppOutNode);
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::FindChildNode(const TXString& nodeName, IXMLFileNode** ppOutNode)
{
	if(fElement){
		return GetInterface(fElement->FirstChildElement(nodeName.GetCharPtr()), ppOutNode);
	}
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetLastError(EXMLFileError& outError)
{
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetNodeAttributes(TXStringArray& outArrNodeAttributes)
{
	if(fElement)
	{
		const tinyxml2::XMLAttribute* attr = fElement->FirstAttribute();
		while (attr)
		{
			outArrNodeAttributes.push_back(attr->Name());
			
			attr = attr->Next();
		}
	}
	return kVCOMError_NoError;;
}

VCOMError CXMLFileNodeImpl::CreateChildNodeBeforeIndex(const TXString& name, size_t index, IXMLFileNode** ppOutNode)
{
    return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::SetNodeName(const TXString &newName)
{
	
	return kVCOMError_NotInitialized;
}

VCOMError CXMLFileNodeImpl::GetLineNumber(size_t& line, size_t& column)
{
	if(fElement)
	{
		line 	= fElement->GetLineNum();
		column 	= 0;
		return kVCOMError_NoError;
	}
	return kVCOMError_Failed;
}


VCOMError CXMLFileNodeImpl::AddCopyOfExistingNodeBeforeIndex(const IXMLFileNode* existingNode, size_t index, IXMLFileNode** ppOutNode)
{
	return kVCOMError_NotInitialized;
}

void CXMLFileNodeImpl::SetElement(tinyxml2::XMLElement* element)
{
	fElement = element;
}

VCOMError CXMLFileNodeImpl::GetInterface(tinyxml2::XMLElement* element, IXMLFileNode** ppOutNode)
{
    if(!element){
        return kVCOMError_NoObj;
    }
	//---------------------------------------------------------------------------
	// Initialize Object
	CXMLFileNodeImpl* pDmxVal = nullptr;

	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_XMLFileNode, (IVWUnknown**)& pDmxVal)))
	{
		// Check Casting
		CXMLFileNodeImpl* pResultInterface = dynamic_cast<CXMLFileNodeImpl* >(pDmxVal);
		if (pResultInterface)
		{
			pResultInterface->SetElement(element);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}


	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*ppOutNode)
	{
		(*ppOutNode)->Release();
		*ppOutNode = NULL;
	}
	//---------------------------------------------------------------------------
	// Set Out Value
	*ppOutNode = pDmxVal;

	return kVCOMError_NoError;

}
#endif