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
GdtfParsingError::GdtfParsingError()
{
}

GdtfParsingError::~GdtfParsingError()
{
}

/*static*/ void GdtfParsingError::CheckNodeAttributes(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional) 
{
   	TXStringArray nodeAttributes;
	pNode->GetNodeAttributes(nodeAttributes);

    // Check required Attributes
    for(const TXString &attribute : needed)
    {
        if (std::find(nodeAttributes.begin(), nodeAttributes.end(), attribute) != nodeAttributes.end())
        {
            nodeAttributes.erase(std::find(nodeAttributes.begin(), nodeAttributes.end(), attribute));
        }
        else
        {
            GdtfParsingError error;
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

    // Check if AttributesList has still elements
    if ( nodeAttributes.size() > 0) return;

    for (const TXString& nodeName : nodeAttributes)
    {
            GdtfParsingError error;
            SceneData::GdtfFixture::AddError(error);
    }

}
