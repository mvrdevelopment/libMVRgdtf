//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2019 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "XMLFileImpl.h"
#include "XMLFileNodeImpl.h"

using namespace VectorworksMVR::Filing;
using namespace VectorworksMVR::XML;
using namespace LightRight;

// ----------------------------------------------------------------------------------------------------
CXMLFileImpl::CXMLFileImpl()
{
}

CXMLFileImpl::~CXMLFileImpl()
{
}

VCOMError CXMLFileImpl::CreateNew(const TXString& rootName)
{
	fDoc.NewElement(rootName);
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::ReadFile(IFileIdentifier* pFileID)
{
	TXString fullPath;
	pFileID->GetFileFullPath(fullPath);
	
	fDoc.LoadFile(fullPath);
	
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::ReadBuffer(IXMLFileIOBuffer* pInputBuffer, EXMLEncoding encoding)
{
	size_t length = 0;
	pInputBuffer->GetDataSize(length);
	char* buffer = new char(length + 1);
	pInputBuffer->CopyDataInto(buffer, length);
	buffer[length] = 0;
	fDoc.Parse(buffer);
	delete buffer;
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::WriteFile(IFileIdentifier* pFileID, EXMLEncoding encoding)
{
	TXString fullPath;
	pFileID->GetFileFullPath(fullPath);
	fDoc.SaveFile( fullPath );
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::WriteBuffer(IXMLFileIOBuffer* pOutputBuffer, EXMLEncoding encoding)
{
	tinyxml2::XMLPrinter printer;
	fDoc.Print(&printer);
	pOutputBuffer->SetData((void*)printer.CStr(), printer.CStrSize());
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::GetRootNode(IXMLFileNode** ppOutNode)
{
	return CXMLFileNodeImpl::GetInterface(fDoc.RootElement(), ppOutNode);
}

VCOMError CXMLFileImpl::GetLastError(EXMLFileError& outError)
{
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::SetFeature(EXMLFileFeature feature, bool bValue)
{
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::GetSimpleNode(const TXString& nodePath, IXMLFileNode** ppOutNode)
{
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::GetSimpleNode(IXMLFileNode* pRefNode, const TXString& nodePath, IXMLFileNode** ppOutNode)
{
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::GetSimpleValue(const TXString& nodePath, TXString& outValue)
{
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::GetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, TXString& outValue)
{
	return kVCOMError_NoError;
}

TXString CXMLFileImpl::GetSimpleValue(const TXString& nodePath, const TXString& defaultValue)
{
	return "";
}

TXString CXMLFileImpl::GetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, const TXString& defaultValue)
{
	return "";
}

VCOMError CXMLFileImpl::SetSimpleValue(const TXString& nodePath, const TXString& value)
{
	return kVCOMError_NoError;
}

VCOMError CXMLFileImpl::SetSimpleValue(IXMLFileNode* pRefNode, const TXString& nodePath, const TXString& value)
{
	return kVCOMError_NoInterface;
}

bool CXMLFileImpl::GetSimpleExist(const TXString& nodePath)
{
	return false;
}

bool CXMLFileImpl::GetSimpleExist(IXMLFileNode* pRefNode, const TXString& nodePath)
{
	return false;
}

uint32_t CXMLFileImpl::AddRef()
{
	fRefCnt ++;
	return fRefCnt;
}

uint32_t CXMLFileImpl::Release()
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
