//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#include "GdtfError.h"
#include "XmlFileHelper.h"
#include <algorithm>
#include <unordered_set>
#include "GDTFManager.h"

//------------------------------------------------------------------------------------
// Parsing Errors
//------------------------------------------------------------------------------------
GdtfParsingError::GdtfParsingError(GdtfDefines::EGdtfParsingError type)
{
    fErrorType          = type;
    fLineNumber         = 0;
    fColumn             = 0;
}

GdtfParsingError::GdtfParsingError(GdtfDefines::EGdtfParsingError type, size_t lineNumber, size_t column)
{
    fErrorType          = type;
    fLineNumber         = lineNumber;
    fColumn             = column;
}

GdtfParsingError::GdtfParsingError(GdtfDefines::EGdtfParsingError type, const IXMLFileNodePtr& pNode)
{
    fErrorType          = type;
    pNode->GetLineNumber(fLineNumber, fColumn);
    pNode->GetNodeName(fNodeName);

    // Fill the Object's name when it exists, is empty otherwise
    pNode->GetNodeAttributeValue("Name", fObjectName);
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
    return fErrorMessage;
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

const TXString& GdtfParsingError::GetObjectName() const
{
    return fObjectName;
}

/*static*/ void GdtfParsingError::CheckNodeAttributes(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional) 
{
    TXStringArray rawAttributes;
    pNode->GetNodeAttributes(rawAttributes);

    // Load all actual node attributes into a set for O(1) lookup and removal
    std::unordered_set<TXString, TXStringNoCaseHash> nodeAttributes(rawAttributes.begin(), rawAttributes.end());

    // Check required attributes: report error if missing, remove from set if found
    for (const TXString& attribute : needed)
    {
        if (!nodeAttributes.erase(attribute))
        {
            GdtfParsingError error(GdtfDefines::EGdtfParsingError::eNodeMissingMandatoryAttribute, pNode);
            error.fErrorMessage = attribute;
            SceneData::GdtfFixture::AddError(error);
        }
    }

    // Remove optional attributes from the set (no error if missing)
    for (const TXString& attribute : optional)
    {
        nodeAttributes.erase(attribute);
    }

    // Any attributes still remaining in the set are unexpected (iterate rawAttributes to preserve XML order)
    for (const TXString& attribute : rawAttributes)
    {
        if (nodeAttributes.count(attribute))
        {
            GdtfParsingError error(GdtfDefines::EGdtfParsingError::eNodeWrongAttribute, pNode);
            error.fErrorMessage = attribute;
            SceneData::GdtfFixture::AddError(error);
        }
    }
}
