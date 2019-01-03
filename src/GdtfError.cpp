//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "GdtfError.h"
#include "XmlFileHelper.h"
#include <algorithm>
#include "GDTFManager.h"

//------------------------------------------------------------------------------------
// Parsing Errors
//------------------------------------------------------------------------------------
// GdtfObject
GdtfParsingError::GdtfParsingError(GdtfDefines::EGdtfParsingError type)
{
    fErrorType  = type;
    fLineNumber = 0;
    fColumn     = 0;
}

GdtfParsingError::GdtfParsingError(GdtfDefines::EGdtfParsingError type, size_t lineNumber, size_t column)
{
    fErrorType  = type;
    fLineNumber = lineNumber;
    fColumn     = column;
}


GdtfParsingError::~GdtfParsingError()
{
}

GdtfDefines::EGdtfParsingError GdtfParsingError::GetError() const
{
    return fErrorType;
}

const TXString& GdtfParsingError::GetErrorMessage() const
{
    return fAttributeNodeName;
}

const TXString& GdtfParsingError::GetNodeName() const
{
    return fNodeName;
}

size_t GdtfParsingError::GetLineNumber() const
{
    return fLineNumber;
}

size_t GdtfParsingError::GetColumnNumber() const
{
    return fColumn;
}

/*static*/ void GdtfParsingError::CheckNodeAttributes(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional) 
{
   	TXStringArray nodeAttributes;
	pNode->GetNodeAttributes(nodeAttributes);

    TXString nodeName;
    pNode->GetNodeName(nodeName);

    // Check required Attributes
    for(const TXString &attribute : needed)
    {
        if (std::find(nodeAttributes.begin(), nodeAttributes.end(), attribute) != nodeAttributes.end())
        {
            nodeAttributes.erase(std::find(nodeAttributes.begin(), nodeAttributes.end(), attribute));
        }
        else
        {
            GdtfParsingError error (GdtfDefines::EGdtfParsingError::eMissingMandatoryAttribute);
            error.fAttributeNodeName = attribute + " " + nodeName;
            pNode->GetLineNumber(error.fLineNumber, error.fColumn);
            SceneData::GdtfFixture::AddError(error);
        }
    }
    
    // Check optional Attributes
    for(const TXString &attribute : optional)
    {
        if (std::find(nodeAttributes.begin(), nodeAttributes.end(), attribute) != nodeAttributes.end())
        {
            nodeAttributes.erase(std::find(nodeAttributes.begin(), nodeAttributes.end(), attribute));
        }
    }

    for (const TXString& attribute : nodeAttributes)
    {
            GdtfParsingError error(GdtfDefines::EGdtfParsingError::eWrongAttribute);
            error.fAttributeNodeName = attribute + " " + nodeName;
            pNode->GetLineNumber(error.fLineNumber, error.fColumn);
            SceneData::GdtfFixture::AddError(error);
    }

}
