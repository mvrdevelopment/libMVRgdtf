#ifdef DONT_USE_XERCES_AS_XMLLIB
//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2019 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "XMLFileImpl.h"
#include "XMLFileNodeImpl.h"
#include "GdtfError.h"
#include "../GDTFManager.h"

using namespace VectorworksMVR::Filing;
using namespace VectorworksMVR::XML;
using namespace VectorworksMVR::VWFC::Tools;


// ----------------------------------------------------------------------------------------------------
CXMLFileImpl::CXMLFileImpl()
{
}

CXMLFileImpl::~CXMLFileImpl()
{
}

/*static*/ void CXMLFileImpl::Tokenize(const TXString& string, TXStringArray& outArray, const char* szTokens, size_t tokensLen, bool doStopTokenizeForSpecialCh /*= false*/, char stopStartCh /*= '\''*/)
{
	outArray.clear();

	TXString	currToken;
	bool		isTokenizeStopped = false;

	size_t	strLen	= string.GetEncodingLength(ETXEncoding::eUTF8);
	for(size_t i=0; i<strLen; i++) {
		UCChar	ch		= string.GetAt( i );

		if ( doStopTokenizeForSpecialCh && ch == stopStartCh )
		{
			isTokenizeStopped = !isTokenizeStopped;
		}

		bool	isToken	= false;
		if ( !isTokenizeStopped )
		{
			for(size_t j=0; j<tokensLen; j++) {
				if ( szTokens[j] == ch ) {
					isToken		= true;
					break;
				}
			}
		}

		if ( isToken ) {
			outArray.push_back( currToken );
			currToken.Clear();
		}
		else {
			currToken		+= ch;
		}
	}

	// put the last item if any
	if ( ! currToken.IsEmpty() ) {
		outArray.push_back( currToken );
		currToken.Clear();
	}
}

VCOMError CXMLFileImpl::CreateNew(const TXString& rootName)
{
	auto element =  fDoc.NewElement(rootName);
    fDoc.InsertFirstChild(element);
    
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
	char* buffer = new char[length + 1];
	pInputBuffer->CopyDataInto(buffer, length);
	buffer[length] = 0;
	fDoc.Parse(buffer);
    delete[] buffer;
	if(fDoc.Error()){
		GdtfParsingError error (EGdtfParsingError::eXmlParsingError, fDoc.ErrorLineNum(), 0);
		SceneData::GdtfFixture::AddError(error);
		return kVCOMError_XMLFile_Parser;
	}
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
	printer.PushDeclaration("xml version=\"1.0\" encoding=\"UTF-8\"");
	fDoc.Print(&printer);
	pOutputBuffer->SetData((void*)printer.CStr(), printer.CStrSize()-2);
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
	TXStringArray	arrNodeNames;
	this->Tokenize( nodePath, arrNodeNames, "/", 1, true, '\'' );
	if(arrNodeNames.size() != 1){
		return kVCOMError_InvalidArg;
	}

	return CXMLFileNodeImpl::GetInterface(fDoc.RootElement()->FirstChildElement(arrNodeNames[0].GetCharPtr()), ppOutNode);
}

VCOMError CXMLFileImpl::GetSimpleNode(IXMLFileNode* pRefNode, const TXString& nodePath, IXMLFileNode** ppOutNode)
{
	std::cout << nodePath.GetCharPtr() << std::endl;
	TXStringArray	arrNodeNames;
	this->Tokenize( nodePath, arrNodeNames, "/", 1, true, '\'' );
	if(arrNodeNames.size() != 1){
		return kVCOMError_InvalidArg;
	}
	CXMLFileImpl* imp = dynamic_cast<CXMLFileImpl*>(pRefNode);
	
	return CXMLFileNodeImpl::GetInterface(imp->fDoc.FirstChildElement(arrNodeNames[0].GetCharPtr()), ppOutNode);
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
#endif