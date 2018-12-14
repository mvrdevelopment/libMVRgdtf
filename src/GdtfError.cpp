//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#include "GdtfError.h"
#include "XmlFileHelper.h"
#include <algorithm>

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

static void    GdtfParsingError::CheckAttributesList(IXMLFileNodePtr pNode, const TXStringArray& needed, const TXStringArray& optional) const
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
            // TODO
            // wrong attributes
            // GdtfFixture::AddError(); or parse some error
        }

        // -----------------------------------------------------------
        // // Version 1 | just the original idea
        // if (std::find(nodeAttributes.begin(), nodeAttributes.end(), attribute) != nodeAttributes.end())
        // {
        //     ptrdiff_t pos = std::find(nodeAttributes.begin(), nodeAttributes.end(), attribute);
        //     nodeAttributes.erase(pos);
        // }
        // // Version 2 | smarter
        // auto itr = std::find(v.begin(), v.end(), rnames);
        // if (itr != v.end()) v.erase(itr);
        // -----------------------------------------------------------

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
    if ( nodeAttributes.size()) return;

    // TODO
    // Error created, parse that or specifically error

}
