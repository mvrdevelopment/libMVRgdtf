//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "GDTFManager.h"
#include "SceneDataExchange.h"
#include "XmlFileHelper.h"
#include "HashManager.h"
#include <iostream>
#include "Utility.h"

using namespace SceneData;

//------------------------------------------------------------------------------------
// GdtfObject
GdtfObject::GdtfObject()
{
	fBindValue = nullptr;
}

GdtfObject::~GdtfObject()
{
}

void GdtfObject::WriteToNode(IXMLFileNodePtr pContainerNode)
{
	// Create the new node
	IXMLFileNodePtr pNode;
	if ( VCOM_SUCCEEDED( pContainerNode->CreateChildNode( this->GetNodeName(), & pNode ) ) )
	{
		// Store Node
		ASSERTN(kEveryone, fNode == nullptr);
		fNode = pNode;
		//-------------------------------------------------------------------------------------
		// Now Print Everything
		this->OnPrintToFile(pNode);
	}
}

void GdtfObject::ReadFromNode(const IXMLFileNodePtr& pNode)
{
	// Store Node
	fNode = pNode;

	TXString nodeName;
	pNode->GetNodeName(nodeName);
	ASSERTN(kEveryone, nodeName == GetNodeName());
	
	this->OnReadFromNode(pNode);
	this->OnErrorCheck(pNode);
}

void GdtfObject::GetNode(IXMLFileNodePtr& pNode)
{
	pNode = fNode;
}

void GdtfObject::OnPrintToFile(IXMLFileNodePtr pNode)
{
	// Nothing to do here
}

void GdtfObject::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	// Nothing to read here
}

void GdtfObject::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	// Nothing to check here
}

void GdtfObject::SetBind(void* ptr)
{
	fBindValue = ptr;
}

void* GdtfObject::GetBind()
{
	return fBindValue;
}

TXString GdtfObject::GetNodeReference()
{
	// Nothing to read here
	DSTOP((kEveryone, "This should be never be executed. You call GetNodeReference on an object that doesn't support this."));
	return "";
}

//------------------------------------------------------------------------------------
// Attributes
GdtfActivationGroup::GdtfActivationGroup(const TXString& name)
{
    fName = name;
}

GdtfActivationGroup::GdtfActivationGroup()
{

}

GdtfActivationGroup::~GdtfActivationGroup()
{
    
}

void GdtfActivationGroup::SetName(const TXString & name)
{
	fName = name;
}

void GdtfActivationGroup::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_ActivationGroupName,				fName);

}

void GdtfActivationGroup::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	pNode->GetNodeAttributeValue(XML_GDTF_AttributeName,			fName);

}

void GdtfActivationGroup::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_ActivationGroupName);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfActivationGroup::GetObjectType()
{
	return EGdtfObjectType::eGdtfActivationGroup;
}

TXString GdtfActivationGroup::GetNodeName()
{
	return XML_GDTF_ActivationGroupNode;
}

const TXString& GdtfActivationGroup::GetName() const
{
	return fName;
}

const TGdtfAttributeArray& GdtfActivationGroup::GetLinkedAttributes() const
{
	return fLinkedAttributes;
}

void GdtfActivationGroup::AddLinkedAttribute(GdtfAttribute* attr)
{
	fLinkedAttributes.push_back(attr);
}

TXString GdtfActivationGroup::GetNodeReference()
{
	return GetName();
}


//------------------------------------------------------------------------------------
// GdtfFeature
GdtfFeature::GdtfFeature(GdtfFeatureGroup* parent)
{    
	ASSERTN (kEveryone, parent);	
	fParent = parent;
}

GdtfFeature::~GdtfFeature()
{
}

void GdtfFeature::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_FeatureName,				fName);

}

void GdtfFeature::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	pNode->GetNodeAttributeValue(XML_GDTF_FeatureName,			fName);

}

void GdtfFeature::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_FeatureName);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfFeature::GetObjectType()
{
	return EGdtfObjectType::eGdtfFeature;
}
TXString GdtfFeature::GetNodeName()
{
	return XML_GDTF_FeatureNode;
}

const TXString& GdtfFeature::GetName() const
{
	return fName;
}

GdtfFeatureGroup* GdtfFeature::GetFeatureGroup() const
{
	return fParent;
}

const TGdtfAttributeArray& GdtfFeature::GetLinkedAttributes() const
{
	return fLinkedAttributes;
}

void GdtfFeature::AddLinkedAttribute(GdtfAttribute* attr)
{
	fLinkedAttributes.push_back(attr);
}


void GdtfFeature::SetName(const TXString & name)
{
	fName = name;
}

TXString GdtfFeature::GetNodeReference()
{
	TXString ref = fParent->GetName() + "." + GetName();
	return ref;
}

//------------------------------------------------------------------------------------
// Attributes
GdtfFeatureGroup::GdtfFeatureGroup()
{
	
}

GdtfFeatureGroup::GdtfFeatureGroup(const TXString& name, const TXString& prettyName)
{
	fName = name;
	fPrettyName = prettyName;
}

GdtfFeatureGroup::~GdtfFeatureGroup()
{
	for (GdtfFeaturePtr pFeature : fFeatures) { delete pFeature; }
}

void GdtfFeatureGroup::SetName(const TXString& name)
{
	fName = name;
}

void GdtfFeatureGroup::SetPrettyName(const TXString& prettyName)
{
	fPrettyName = prettyName;
}

void GdtfFeatureGroup::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_FeatureGroupName,					fName);
	pNode->SetNodeAttributeValue(XML_GDTF_FeatureGroupPrettyName,			fPrettyName);
	
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfFeature* feature : fFeatures)
	{
		feature->WriteToNode(pNode);
	}	
}

void GdtfFeatureGroup::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	pNode->GetNodeAttributeValue(XML_GDTF_FeatureGroupName,					fName);
	pNode->GetNodeAttributeValue(XML_GDTF_FeatureGroupPrettyName,			fPrettyName);
	

	
	//------------------------------------------------------------------------------------
	// Read the childs
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_FeatureNode, [this] (IXMLFileNodePtr objNode) -> void
								 { 
									 GdtfFeaturePtr feature = new GdtfFeature(this);
									 
									 feature->ReadFromNode(objNode);
									 
									 fFeatures.push_back(feature);
									 return;
								 });
	
}

void GdtfFeatureGroup::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_FeatureGroupName);
	needed.push_back(XML_GDTF_FeatureGroupPrettyName);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfFeatureGroup::GetObjectType()
{
	return EGdtfObjectType::eGdtfFeatureGroup;
}
TXString GdtfFeatureGroup::GetNodeName()
{
	return XML_GDTF_FeatureGroupNode;
}

GdtfFeature* GdtfFeatureGroup::AddFeature(const TXString& name)
{
	GdtfFeature* feature = new GdtfFeature(this);
	feature->SetName(name);
	fFeatures.push_back(feature);
	return feature;
}


const TXString& GdtfFeatureGroup::GetName() const
{
	return fName;
}

const TXString& GdtfFeatureGroup::GetPrettyName() const
{
	return fPrettyName;
}

const TGdtfFeatureArray GdtfFeatureGroup::GetFeatureArray()
{
	return fFeatures;
}

//------------------------------------------------------------------------------------
// Attributes
GdtfAttribute::GdtfAttribute()
{
	fActivationGroup	= nullptr;
	fFeature            = nullptr;
    fMainAttribute      = nullptr;
    fPhysicalUnit       = EGdtfPhysicalUnit::None;

}

GdtfAttribute::GdtfAttribute(const TXString& name, const TXString& prettyName)
{
	fName				= name;
	fPrettyName			= prettyName;
	fActivationGroup	= nullptr;
	fFeature            = nullptr;    
    fMainAttribute      = nullptr;
    fPhysicalUnit       = EGdtfPhysicalUnit::None;
}

GdtfAttribute::~GdtfAttribute()
{
}

void GdtfAttribute::SetName(const TXString &name)
{
	fName = name;
}

void GdtfAttribute::SetPrettyName(const TXString &name)
{
	fPrettyName = name;
}

void GdtfAttribute::SetActivationGroup(GdtfActivationGroupPtr ptr)
{
	ASSERTN(kEveryone, fActivationGroup == nullptr);
	fActivationGroup = ptr;
	
	ASSERTN(kEveryone, ptr != nullptr);
	if (ptr) { ptr->AddLinkedAttribute(this); }
}

void SceneData::GdtfAttribute::SetMainAttribute(GdtfAttribute * attr)
{
    fMainAttribute = attr;
}

void SceneData::GdtfAttribute::SetPhysicalUnit(EGdtfPhysicalUnit unit)
{
    fPhysicalUnit = unit;
}

void SceneData::GdtfAttribute::SetColor(const CCieColor & col)
{
    fColor = col;
}

void GdtfAttribute::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	ASSERTN(kEveryone, fFeature);

	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_AttributeName,				fName);
	pNode->SetNodeAttributeValue(XML_GDTF_AttributePrettyName,			fPrettyName);
	if (fActivationGroup)	{ pNode->SetNodeAttributeValue(XML_GDTF_AttributeActGroup,	fActivationGroup->GetNodeReference()); }
	if (fFeature)			{ pNode->SetNodeAttributeValue(XML_GDTF_AttributeFeature,	fFeature->GetNodeReference() );	}	
    if (fMainAttribute)     { pNode->SetNodeAttributeValue(XML_GDTF_AttributefMainAttribute, fMainAttribute->GetNodeReference()); }
	
    pNode->SetNodeAttributeValue(XML_GDTF_AttributePhysicalUnit, GdtfConverter::ConvertPhysicalUnitEnum(fPhysicalUnit));
    pNode->SetNodeAttributeValue(XML_GDTF_AttributeColor, GdtfConverter::ConvertColor(fColor));
	
}

void GdtfAttribute::OnReadFromNode(const IXMLFileNodePtr& pNode)
{    
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	pNode->GetNodeAttributeValue(XML_GDTF_AttributeName,			fName);
	pNode->GetNodeAttributeValue(XML_GDTF_AttributePrettyName,		fPrettyName);
	
	pNode->GetNodeAttributeValue(XML_GDTF_AttributeActGroup, fUnresolvedActGroup);
	pNode->GetNodeAttributeValue(XML_GDTF_AttributeFeature, fUnresolvedFeature);   
    pNode->GetNodeAttributeValue(XML_GDTF_AttributefMainAttribute, fUnresolvedMainAttrib);
    TXString physicalUnitStr; pNode->GetNodeAttributeValue(XML_GDTF_AttributePhysicalUnit, physicalUnitStr); 	GdtfConverter::ConvertPhysicalUnitEnum(physicalUnitStr, pNode, fPhysicalUnit);
    TXString colorStr;        pNode->GetNodeAttributeValue(XML_GDTF_AttributeColor, colorStr); 					GdtfConverter::ConvertColor(colorStr, pNode, fColor);
	
}

void GdtfAttribute::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_AttributeName);
	needed.push_back(XML_GDTF_AttributePrettyName);
	needed.push_back(XML_GDTF_AttributeFeature);
	optional.push_back(XML_GDTF_AttributeActGroup);
	optional.push_back(XML_GDTF_AttributefMainAttribute);
	optional.push_back(XML_GDTF_AttributePhysicalUnit);
	optional.push_back(XML_GDTF_AttributeColor);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfAttribute::GetObjectType()
{
	return EGdtfObjectType::eGdtfAttribute;
}
TXString GdtfAttribute::GetNodeName()
{
	return XML_GDTF_AttributeNode;
}

const TXString& GdtfAttribute::GetName() const
{
	return fName;
}

const TXString& GdtfAttribute::GetPrettyName() const
{
	return fPrettyName;
}

GdtfActivationGroupPtr GdtfAttribute::GetActivationGroup() const
{
	return fActivationGroup;
}

GdtfFeaturePtr GdtfAttribute::GetFeature() const
{
	return fFeature;
}

void GdtfAttribute::SetFeature(GdtfFeaturePtr newFeat)
{
	ASSERTN(kEveryone, fFeature == nullptr);
	fFeature = newFeat;
	
	ASSERTN(kEveryone, newFeat != nullptr);
	if (newFeat) { newFeat->AddLinkedAttribute(this); }
}

GdtfAttribute * SceneData::GdtfAttribute::GetMainAttribute()
{
    return fMainAttribute;
}

EGdtfPhysicalUnit SceneData::GdtfAttribute::GetPhysicalUnit()
{
    return fPhysicalUnit;
}

CCieColor SceneData::GdtfAttribute::GetColor()
{
    return fColor;
}

TXString GdtfAttribute::GetNodeReference()
{
	return GetName();
}

const TXString& GdtfAttribute::GetUnresolvedActGroup() const
{
	return fUnresolvedActGroup;
}

const TXString& GdtfAttribute::GetUnresolvedMainAttribute() const
{
	return fUnresolvedMainAttrib;
}

const TXString& GdtfAttribute::GetUnresolvedFeature() const
{
	return fUnresolvedFeature;
}

//------------------------------------------------------------------------------------
// GdtfWheel
GdtfWheel::GdtfWheel(GdtfFixture* parentFixture)
{
	fParentFixture	= parentFixture;
}

GdtfWheel::GdtfWheel(GdtfFixture* parentFixture, const TXString& name)
{
	fName			= name;
	fParentFixture	= parentFixture;
}

GdtfWheel::~GdtfWheel()
{
	for (GdtfWheelSlotPtr ptr : fWheelSlots) { delete ptr; }
}

GdtfWheelSlotPtr GdtfWheel::AddWheelSlot(const TXString& name)
{
	// Add Slot
	GdtfWheelSlot* slot  = new GdtfWheelSlot(name, this);
	
	fWheelSlots.push_back(slot);
	
	return slot;
}

void GdtfWheel::SetName(const TXString &name)
{
	fName = name;
}

bool GdtfWheel::IsGoboWheel() const
{
	for (GdtfWheelSlot* slot : fWheelSlots)
	{
		if (slot->GetGobo().IsEmpty()) { return false; }
	}
	
	return true;
}

TXString GdtfWheel::GetNodeReference()
{
	return GetName();
}

GdtfFixture* GdtfWheel::GetParentFixture() const
{
	return fParentFixture;
}

const TGdtfWheelSlotArray& GdtfWheel::GetWheelSlotArray() const
{
	return fWheelSlots;
}

void GdtfWheel::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_WheelName,			fName);
	
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfWheelSlot* wheelSlotObj : fWheelSlots)
	{
		wheelSlotObj->WriteToNode(pNode);
	}
}

void GdtfWheel::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	pNode->GetNodeAttributeValue(XML_GDTF_WheelName,			fName);
		
	//------------------------------------------------------------------------------------
	// Read the wheel slots
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_WheelSlotNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfWheelSlotPtr wheelSlot = new GdtfWheelSlot(this);
									 
									 // Read from node
									 wheelSlot->ReadFromNode(objNode);
									 
									 // Add to list
									 fWheelSlots.push_back(wheelSlot);
									 return;
								 });

	
}

void GdtfWheel::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_WheelName);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfWheel::GetObjectType()
{
	return EGdtfObjectType::eGdtfWheel;
}

TXString GdtfWheel::GetNodeName()
{
	return XML_GDTF_WheelNodeName;
}

const TXString& GdtfWheel::GetName() const
{
	return fName;
}

//------------------------------------------------------------------------------------
// GdtfWheelSlotPrismFacet
GdtfWheelSlotPrismFacet::GdtfWheelSlotPrismFacet()
{
	fColor = CCieColor(0.3127,0.3290,100.0);
}

GdtfWheelSlotPrismFacet::~GdtfWheelSlotPrismFacet()
{
}

void GdtfWheelSlotPrismFacet::SetColor(const CCieColor &color)
{
	fColor = color;
}

void GdtfWheelSlotPrismFacet::SetTransformMatrix(const VWFC::Math::VWTransformMatrix &ma)
{
	fTransform = ma;
}

void GdtfWheelSlotPrismFacet::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	pNode->SetNodeAttributeValue(XML_GDTF_PrismFacetColor,		GdtfConverter::ConvertColor(fColor));
	pNode->SetNodeAttributeValue(XML_GDTF_PrismFacetRotation,	GdtfConverter::ConvertRotation(fTransform));
}

CCieColor GdtfWheelSlotPrismFacet::GetColor()
{
	return fColor;
}

VWTransformMatrix GdtfWheelSlotPrismFacet::GetTransformMatrix()
{
	return fTransform;
}

void GdtfWheelSlotPrismFacet::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	TXString color;		pNode->GetNodeAttributeValue(XML_GDTF_PrismFacetColor,		color);		GdtfConverter::ConvertColor(color, pNode, fColor);
	TXString transfrom;	pNode->GetNodeAttributeValue(XML_GDTF_PrismFacetRotation,	transfrom);	GdtfConverter::ConvertRotation(transfrom, pNode, fTransform);
	
}

void GdtfWheelSlotPrismFacet::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_PrismFacetRotation);
	optional.push_back(XML_GDTF_PrismFacetColor);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfWheelSlotPrismFacet::GetObjectType()
{
	return EGdtfObjectType::eGdtfPrismFacet;
}
TXString GdtfWheelSlotPrismFacet::GetNodeName()
{
	return XML_GDTF_PrismFacetNodeName;
}

//------------------------------------------------------------------------------------
// GdtfWheelSlot
GdtfWheelSlot::GdtfWheelSlot(GdtfWheel* parent)
{
	fWheelParent = parent;
}

GdtfWheelSlot::GdtfWheelSlot(const TXString& name, GdtfWheel* parent)
{
	fName		 = name;
	fWheelParent = parent;
}


GdtfWheelSlot::~GdtfWheelSlot()
{
	for(GdtfWheelSlotPrismFacet* facet : fPrismFacts) { delete facet; };
}

void GdtfWheelSlot::SetName(const TXString &name)
{
	fName = name;
}

void GdtfWheelSlot::SetGobo(const GdtfPNGFile& png)
{
	fGobo = png;
}

void GdtfWheelSlot::SetColor(const CCieColor& color)
{
	fColor = color;
}

GdtfWheelSlotPrismFacet* GdtfWheelSlot::AddPrismFacet()
{
	GdtfWheelSlotPrismFacet* prism = new GdtfWheelSlotPrismFacet();
	fPrismFacts.push_back(prism);
	return prism;
}

const TXString&	GdtfWheelSlot::GetGobo() const
{
	return fGobo;
}

const TXString&	GdtfWheelSlot::GetGoboFileFullPath()
{
	TXString				workingFolder;
	IFolderIdentifierPtr	folder;
	fWheelParent->GetParentFixture()->GetWorkingFolder(folder);
	
	ASSERTN(kEveryone, folder != nullptr);
	if (folder) { folder->GetFullPath(workingFolder); }
	
	// Set to store
	fGoboFile = workingFolder + fGobo;
	
	// Return
	return fGoboFile;
}

CCieColor GdtfWheelSlot::GetColor() const
{
	return fColor;
}

const TXString& GdtfWheelSlot::GetName() const
{
	return fName;
}

void GdtfWheelSlot::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_WheelSlotName,	fName);
	pNode->SetNodeAttributeValue(XML_GDTF_WheelSlotColor,		GdtfConverter::ConvertColor(fColor));
	if(fGobo != "")	{ pNode->SetNodeAttributeValue(XML_GDTF_WheelSlotPicture,	fGobo); }
	
	
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfWheelSlotPrismFacet* prism : fPrismFacts)
	{
		prism->WriteToNode(pNode);
	}
}

void GdtfWheelSlot::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);

	
	// ------------------------------------------------------------------------------------
	// Get Name
	pNode->GetNodeAttributeValue(XML_GDTF_WheelSlotName,	fName);
	
	// ------------------------------------------------------------------------------------
	// Get Color
	TXString color;
	if (VCOM_SUCCEEDED(pNode->GetNodeAttributeValue(XML_GDTF_WheelSlotColor, color)))
	{
		if (color.IsEmpty() == false)
		{
            GdtfConverter::ConvertColor(color, pNode, this->fColor);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Get Gobo
	pNode->GetNodeAttributeValue(XML_GDTF_WheelSlotPicture, fGobo);
	
	
	//------------------------------------------------------------------------------------
	// Read the wheel slots
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_PrismFacetNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfWheelSlotPrismFacetPtr facet = new GdtfWheelSlotPrismFacet();
									 
									 // Read from node
									 facet->ReadFromNode(objNode);
									 
									 // Add to list
									 fPrismFacts.push_back(facet);
									 return;
								 });
}

void GdtfWheelSlot::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_WheelSlotName);
	optional.push_back(XML_GDTF_WheelSlotColor);
	optional.push_back(XML_GDTF_WheelSlotPicture);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfWheelSlot::GetObjectType()
{
	return EGdtfObjectType::eGdtfWheelSlot;
}
TXString GdtfWheelSlot::GetNodeName()
{
	return XML_GDTF_WheelSlotNodeName;
}

TGdtfWheelSlotPrismFacetArray GdtfWheelSlot::GetPrismFacets()
{
	return fPrismFacts;
}

TXString GdtfWheelSlot::GetNodeReference()
{
	TXString ref = fWheelParent->GetNodeReference() + "." + GetName();
	return ref;
}

//------------------------------------------------------------------------------------
// GdtfModel
GdtfModel::GdtfModel(GdtfFixture* fixture)
{
	fUniqueName		= "";
	fLength			= 0;
	fWidth			= 0;
	fHeight			= 0;
	fPrimitiveType	= eGdtfModel_PrimitiveType_Undefined;
	fGeometryFile	= "";
	fParentFixture	= fixture;
}

GdtfModel::GdtfModel(const TXString& name, GdtfFixture* fixture)
{
	fUniqueName		= name;
	fLength			= 0;
	fWidth			= 0;
	fHeight			= 0;
	fPrimitiveType	= eGdtfModel_PrimitiveType_Undefined;
	fGeometryFile	= "";
	fParentFixture	= fixture;
}

GdtfModel::~GdtfModel()
{
}

void GdtfModel::SetName(const TXString& name)
{
	fUniqueName = name;
}

void GdtfModel::SetLength(const double& length)
{
	fLength = length;
}

void GdtfModel::SetWidth(const double& width)
{
	fWidth = width;
}

void GdtfModel::SetHeight(const double &height)
{
	fHeight = height;
}

void GdtfModel::SetPrimitiveType(const EGdtfModel_PrimitiveType &type)
{
	fPrimitiveType = type;
}

void GdtfModel::SetGeometryFile(const TXString &file)
{
	fGeometryFile = file;
}

void GdtfModel::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_ModelName,			fUniqueName);
	pNode->SetNodeAttributeValue(XML_GDTF_ModelLength,			GdtfConverter::ConvertDouble(fLength));
	pNode->SetNodeAttributeValue(XML_GDTF_ModelWidth,			GdtfConverter::ConvertDouble(fWidth));
	pNode->SetNodeAttributeValue(XML_GDTF_ModelHeight,			GdtfConverter::ConvertDouble(fHeight));
	pNode->SetNodeAttributeValue(XML_GDTF_ModelPrimitiveType,	GdtfConverter::ConvertPrimitiveType(fPrimitiveType));
	pNode->SetNodeAttributeValue(XML_GDTF_ModelFile,			fGeometryFile);
}

void GdtfModel::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);

	
	// ------------------------------------------------------------------------------------
	// Read node attributes
	pNode->GetNodeAttributeValue(XML_GDTF_ModelName,			fUniqueName);
	
	// Convert Doubles
	TXString length;	pNode->GetNodeAttributeValue(XML_GDTF_ModelLength,			length);	GdtfConverter::ConvertDouble(length, 		pNode, 	fLength);
	TXString width;		pNode->GetNodeAttributeValue(XML_GDTF_ModelWidth,			width);		GdtfConverter::ConvertDouble(width, 		pNode,  fWidth);
	TXString height;	pNode->GetNodeAttributeValue(XML_GDTF_ModelHeight,			height);	GdtfConverter::ConvertDouble(height, 		pNode, 	fHeight);
	TXString type;		pNode->GetNodeAttributeValue(XML_GDTF_ModelPrimitiveType,	type);		GdtfConverter::ConvertPrimitiveType(type, 	pNode, 	fPrimitiveType);
						pNode->GetNodeAttributeValue(XML_GDTF_ModelFile,			fGeometryFile);
}

void GdtfModel::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_ModelName);
	optional.push_back(XML_GDTF_ModelFile);
	optional.push_back(XML_GDTF_ModelLength);
	optional.push_back(XML_GDTF_ModelWidth);
	optional.push_back(XML_GDTF_ModelHeight);
	optional.push_back(XML_GDTF_ModelPrimitiveType);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfModel::GetObjectType()
{
	return EGdtfObjectType::eGdtfModel;
}
TXString GdtfModel::GetNodeName()
{
	return XML_GDTF_ModelNodeName;
}

TXString GdtfModel::GetNodeReference()
{
	return GetName();
}

const TXString& GdtfModel::GetGeometryFileName() const
{
	return fGeometryFile;
}

const TXString& GdtfModel::GetGeometryFile_3DS_FullPath()
{
	fFullPath3DS = "";
	// Set to store
	IFolderIdentifierPtr folder (IID_FolderIdentifier);
	fParentFixture->GetWorkingFolder(folder);

	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(folder, fGeometryFile + ".3ds");

	bool fileExists = false;
	if(VCOM_SUCCEEDED(file->ExistsOnDisk(fileExists)) && fileExists)
	{
		file->GetFileFullPath(fFullPath3DS);
	}
	
	return fFullPath3DS;
}

const TXString & SceneData::GdtfModel::GetGeometryFile_SVG_FullPath()
{
	// Set to store
	fFullPathSVG = "";
	// Set to store
	IFolderIdentifierPtr folder (IID_FolderIdentifier);
	fParentFixture->GetWorkingFolder(folder);

	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(folder, fGeometryFile + ".svg");

	bool fileExists = false;
	if(VCOM_SUCCEEDED(file->ExistsOnDisk(fileExists)) && fileExists)
	{
		file->GetFileFullPath(fFullPathSVG);
	}
	
	return fFullPathSVG;
}

const TXString& GdtfModel::GetName() const
{
	return fUniqueName;
}

double GdtfModel::GetLength() const
{
	return fLength;
}

double GdtfModel::GetWidth() const
{
	return fWidth;
}

double GdtfModel::GetHeight() const
{
	return fHeight;
}

EGdtfModel_PrimitiveType GdtfModel::GetPrimitiveType() const
{
	return fPrimitiveType;
}

//------------------------------------------------------------------------------------
// GdtfGeometry
GdtfGeometry::GdtfGeometry( GdtfGeometry* parent )
{
	fParent			= parent;
	fUniqueName		= "";
	fMatrix			= VWTransformMatrix();
	fModelReference = nullptr;
}

GdtfGeometry::GdtfGeometry(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent)
{
	fParent			= parent;
	fUniqueName		= name;
	fMatrix			= ma;
	fModelReference = refToModel;
}

GdtfGeometry::~GdtfGeometry()
{
	for (GdtfGeometryPtr ptr : fInternalGeometries) { delete ptr; }
}

void GdtfGeometry::SetName(const TXString &name)
{
	fUniqueName = name;
}

void GdtfGeometry::SetTransformMatrix(const VWFC::Math::VWTransformMatrix &ma)
{
	fMatrix = ma;
}

void GdtfGeometry::SetModel(GdtfModelPtr model)
{
	fModelReference = model;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryWithAxis(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma)
{
	GdtfGeometryAxis* axis = new GdtfGeometryAxis(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(axis);
	
	return axis;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryWithLamp(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometryLamp* lamp = new GdtfGeometryLamp(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(lamp);
	
	return lamp;
}

GdtfGeometryPtr GdtfGeometry::AddGeometry(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometry(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryReference(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryReference(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryShaper(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryShaperFilter(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryColor(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryColorFilter(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryGobo(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryGoboFilter(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryBeam(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryBeamFilter(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

void GdtfGeometry::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_GeometryName,				fUniqueName);
	
	pNode->SetNodeAttributeValue(XML_GDTF_GeometryMatrix,			GdtfConverter::ConvertMatrix(fMatrix, true));

	if (fModelReference) { pNode->SetNodeAttributeValue(XML_GDTF_GeometryModelRef,	fModelReference->GetNodeReference()); }
	
	// ------------------------------------------------------------------------------------
	// Print Internal geometry
	for (GdtfGeometry* geoObj : fInternalGeometries)
	{
		geoObj->WriteToNode(pNode);
	}
}

void GdtfGeometry::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	// Get Node Name
	pNode->GetNodeAttributeValue(XML_GDTF_GeometryName,				fUniqueName);
	
	// Get Matrix
	TXString matrix;
	pNode->GetNodeAttributeValue(XML_GDTF_GeometryMatrix,			matrix);
	GdtfConverter::ConvertMatrix(matrix, pNode, fMatrix);
	
	// Get Node Reference
	pNode->GetNodeAttributeValue(XML_GDTF_GeometryModelRef,			fUnresolvedModelRef);
	
	// ------------------------------------------------------------------------------------
	// Print geometries
	GdtfConverter::TraverseMultiNodes(pNode, "", [this] (IXMLFileNodePtr objNode,const TXString& childNodeName) -> void
									{
										bool hasBreak = false;;
										
										GdtfGeometryPtr geometry = nullptr;
										if	  (childNodeName == XML_GDTF_GeometryAxisNodeName)			{ geometry = new GdtfGeometryAxis(this);}
										else if (childNodeName == XML_GDTF_GeometryNodeName)			{ geometry = new GdtfGeometry(this);}
										else if (childNodeName == XML_GDTF_FilterBeamNodeName)			{ geometry = new GdtfGeometryBeamFilter(this);}
										else if (childNodeName == XML_GDTF_FilterColorNodeName)			{ geometry = new GdtfGeometryColorFilter(this);}
										else if (childNodeName == XML_GDTF_FilterGoboNodeName)			{ geometry = new GdtfGeometryGoboFilter(this);}
										else if (childNodeName == XML_GDTF_FilterShaperNodeName)		{ geometry = new GdtfGeometryShaperFilter(this);}
										else if (childNodeName == XML_GDTF_LampNodeName)				{ geometry = new GdtfGeometryLamp(this);}
										else if (childNodeName == XML_GDTF_GeometryReferenceNodeName)	{ geometry = new GdtfGeometryReference(this);}
										else if (childNodeName == XML_GDTF_BreakNodeName)				{ hasBreak = true; }
										else															{ DSTOP((kEveryone,"There is a node that was not aspected!")); }
										
										
										if (hasBreak)
										{
											// This is only allowed in Geometry Refs
											ASSERTN(kEveryone, this->GetObjectType() == eGdtfGeometryReference);
											if (this->GetObjectType() == eGdtfGeometryReference)
											{
												GdtfBreakPtr breakObj = new GdtfBreak();
												breakObj->ReadFromNode(objNode);
												
												GdtfGeometryReferencePtr refGeo = dynamic_cast<GdtfGeometryReferencePtr>(this);
												refGeo->fBreaks.push_back(breakObj);
												return;
											}
											else
											{
												GdtfParsingError error (GdtfDefines::EGdtfParsingError::eBreakObjectInNonGeometryReference, objNode);
												SceneData::GdtfFixture::AddError(error);
											}
										}
										
										ASSERTN(kEveryone, geometry != nullptr);
										if (geometry)
										{
											geometry->ReadFromNode(objNode);
											fInternalGeometries.push_back(geometry);
										}
										else
										{
											GdtfParsingError error (GdtfDefines::EGdtfParsingError::eNodeWrongName, objNode);
											SceneData::GdtfFixture::AddError(error);
										}
										return;
									});
}

void GdtfGeometry::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryMatrix);
	
	TXStringArray optional;
	optional.push_back(XML_GDTF_GeometryModelRef);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

GdtfModelPtr GdtfGeometry::GetModelRef() const
{
	return fModelReference;
}

void GdtfGeometry::GetTransformMatrix(VWTransformMatrix& ma) const
{
	ma = fMatrix;
}

TXString GdtfGeometry::GetUnresolvedModelRef() const
{
	return fUnresolvedModelRef;
}

void GdtfGeometry::SetUnresolvedModelRef(GdtfModelPtr ref)
{
	ASSERTN(kEveryone, ref != nullptr);
	fModelReference = ref;
}

TXString GdtfGeometry::GetNodeName()
{
	return XML_GDTF_GeometryNodeName;
}

EGdtfObjectType GdtfGeometry::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometry;
}

const TXString& GdtfGeometry::GetName() const
{
	return fUniqueName;
}

const std::vector<GdtfGeometry*> GdtfGeometry::GetInternalGeometries()
{
	return fInternalGeometries;
}

TXString GdtfGeometry::GetNodeReference()
{
	TXString nodeRef;
	nodeRef = GetName();
	return nodeRef;
}

//------------------------------------------------------------------------------------
// GdtfGeometryAxis
GdtfGeometryAxis::GdtfGeometryAxis(GdtfGeometry* parent) 
				: GdtfGeometry(parent)
{
	
}

GdtfGeometryAxis::GdtfGeometryAxis(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent)
				: GdtfGeometry(name,refToModel,ma, parent)
{

}

GdtfGeometryAxis::~GdtfGeometryAxis()
{
}

void GdtfGeometryAxis::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	

}

void GdtfGeometryAxis::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
	
}

void GdtfGeometryAxis::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryAxis::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryAxis;
}

TXString GdtfGeometryAxis::GetNodeName()
{
	return XML_GDTF_GeometryAxisNodeName;
}

//------------------------------------------------------------------------------------
// GdtfGeometryBeamFilter
GdtfGeometryBeamFilter::GdtfGeometryBeamFilter(GdtfGeometry* parent) : GdtfGeometry(parent)
{
	
}

GdtfGeometryBeamFilter::GdtfGeometryBeamFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) : GdtfGeometry(name,refToModel,ma, parent)
{

}

GdtfGeometryBeamFilter::~GdtfGeometryBeamFilter()
{
}

void GdtfGeometryBeamFilter::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
}

void GdtfGeometryBeamFilter::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
}

void GdtfGeometryBeamFilter::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryBeamFilter::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryBeamFilter;
}

TXString GdtfGeometryBeamFilter::GetNodeName()
{
	return XML_GDTF_FilterBeamNodeName;
}

//------------------------------------------------------------------------------------
// GdtfGeometryColorFilter
GdtfGeometryColorFilter::GdtfGeometryColorFilter(GdtfGeometry* parent) 
					   : GdtfGeometry(parent)
{
	
}

GdtfGeometryColorFilter::GdtfGeometryColorFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) 
					   : GdtfGeometry(name,refToModel,ma, parent)
{
	
}

GdtfGeometryColorFilter::~GdtfGeometryColorFilter()
{
}

void GdtfGeometryColorFilter::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
}

void GdtfGeometryColorFilter::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
}

void GdtfGeometryColorFilter::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryColorFilter::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryColorFilter;
}

TXString GdtfGeometryColorFilter::GetNodeName()
{
	return XML_GDTF_FilterBeamNodeName;
}

//------------------------------------------------------------------------------------
// GdtfGeometryShaperFilter
GdtfGeometryShaperFilter::GdtfGeometryShaperFilter(GdtfGeometry* parent) 
						: GdtfGeometry(parent)
{
	
}

GdtfGeometryShaperFilter::GdtfGeometryShaperFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) 
						: GdtfGeometry(name,refToModel,ma, parent)
{
	
}

GdtfGeometryShaperFilter::~GdtfGeometryShaperFilter()
{
}

void GdtfGeometryShaperFilter::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
}

void GdtfGeometryShaperFilter::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
}

void GdtfGeometryShaperFilter::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryShaperFilter::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryShaperFilter;
}

TXString GdtfGeometryShaperFilter::GetNodeName()
{
	return XML_GDTF_FilterShaperNodeName;
}

//------------------------------------------------------------------------------------
// GdtfGeometryGoboFilter
GdtfGeometryGoboFilter::GdtfGeometryGoboFilter(GdtfGeometry* parent) : GdtfGeometry(parent)
{
	
}

GdtfGeometryGoboFilter::GdtfGeometryGoboFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) 
					  : GdtfGeometry(name,refToModel,ma, parent)
{
	
}

GdtfGeometryGoboFilter::~GdtfGeometryGoboFilter()
{
}

void GdtfGeometryGoboFilter::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
}

void GdtfGeometryGoboFilter::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
}

void GdtfGeometryGoboFilter::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryGoboFilter::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryGoboFilter;
}

TXString GdtfGeometryGoboFilter::GetNodeName()
{
	return XML_GDTF_FilterGoboNodeName;
}

//------------------------------------------------------------------------------------
// GdtfGeometryLamp
GdtfGeometryLamp::GdtfGeometryLamp(GdtfGeometry* parent) 
				: GdtfGeometry(parent)
{
    InitializeMembersWithDefaultsVals(); // Call this function at first
}

GdtfGeometryLamp::GdtfGeometryLamp(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent)
				: GdtfGeometry(name,refToModel,ma, parent)
{
    InitializeMembersWithDefaultsVals(); // Call this function at first
}

void GdtfGeometryLamp::InitializeMembersWithDefaultsVals() 
{
	fLampType			= EGdtfLampType::eGdtfLampType_Dischange;
	fPowerConsuption	= 1000;
	fLuminousIntensity	= 1000;
	fColorTemperature	= 6000;
	fBeamAngle			= 25;
    fFieldAngle         = 25;
	fBeamRadius			= 50; //0.05m
	fBeamType			= EGdtfBeamType::eGdtfBeamType_Wash;
	fColorIndex			= 100;
}

GdtfGeometryLamp::~GdtfGeometryLamp()
{
}

void GdtfGeometryLamp::SetLampType(EGdtfLampType type)
{
	fLampType = type;
}

void GdtfGeometryLamp::SetPowerConsumption(double powerConsumption)
{
	fPowerConsuption = powerConsumption;
}

void GdtfGeometryLamp::SetLuminousIntensity(double intensity)
{
	fLuminousIntensity = intensity;
}

void GdtfGeometryLamp::SetColorTemperature(double temperature)
{
	fColorTemperature = temperature;
}

void GdtfGeometryLamp::SetBeamAngle(double angle)
{
	fBeamAngle = angle;
}

void SceneData::GdtfGeometryLamp::SetFieldAngle(double angle)
{
    fFieldAngle = angle;
}

void SceneData::GdtfGeometryLamp::SetBeamRadius(double radius)
{
    fBeamRadius = radius;
}

void SceneData::GdtfGeometryLamp::SetBeamType(EGdtfBeamType type)
{
    fBeamType = type;
}

void SceneData::GdtfGeometryLamp::SetColorIndex(Sint32 idx)
{
    fColorIndex = idx;
}

void GdtfGeometryLamp::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_LampLampType,				GdtfConverter::ConvertLampeType(fLampType));
	pNode->SetNodeAttributeValue(XML_GDTF_LampPowerConsumption,		GdtfConverter::ConvertDouble(fPowerConsuption));
	pNode->SetNodeAttributeValue(XML_GDTF_LampLuminousFlux,	        GdtfConverter::ConvertDouble(fLuminousIntensity));
	pNode->SetNodeAttributeValue(XML_GDTF_ColorTemperature,			GdtfConverter::ConvertDouble(fColorTemperature));
	pNode->SetNodeAttributeValue(XML_GDTF_BeamAngle,				GdtfConverter::ConvertDouble(fBeamAngle));
	pNode->SetNodeAttributeValue(XML_GDTF_BeamRadius,				GdtfConverter::ConvertDouble(fBeamRadius));
	pNode->SetNodeAttributeValue(XML_GDTF_FieldAngle,				GdtfConverter::ConvertDouble(fFieldAngle));
	pNode->SetNodeAttributeValue(XML_GDTF_BeamType,					GdtfConverter::ConvertBeamType(fBeamType));
	pNode->SetNodeAttributeValue(XML_GDTF_BeamColorRenderingIndex,	GdtfConverter::ConvertInteger(fColorIndex));
	
}

void GdtfGeometryLamp::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	TXString lampType;	pNode->GetNodeAttributeValue(XML_GDTF_LampLampType,				lampType);	GdtfConverter::ConvertLampeType(lampType, 	pNode,	fLampType);
	TXString power;		pNode->GetNodeAttributeValue(XML_GDTF_LampPowerConsumption,		power);		GdtfConverter::ConvertDouble(power, 		pNode,	fPowerConsuption);
	TXString lum;		pNode->GetNodeAttributeValue(XML_GDTF_LampLuminousFlux,	lum);		GdtfConverter::ConvertDouble(lum, 			pNode,	fLuminousIntensity);
	TXString colorTemp;	pNode->GetNodeAttributeValue(XML_GDTF_ColorTemperature,			colorTemp);	GdtfConverter::ConvertDouble(colorTemp, 	pNode,	fColorTemperature);
	TXString angle;		pNode->GetNodeAttributeValue(XML_GDTF_BeamAngle,				angle);		GdtfConverter::ConvertDouble(angle, 		pNode,	fBeamAngle);
	TXString radius;	pNode->GetNodeAttributeValue(XML_GDTF_BeamRadius,				radius);	GdtfConverter::ConvertDouble(radius, 		pNode,	fBeamRadius);
	TXString fieldAngle;pNode->GetNodeAttributeValue(XML_GDTF_FieldAngle,				fieldAngle);GdtfConverter::ConvertDouble(fieldAngle, 	pNode,	fFieldAngle);
	TXString type;		pNode->GetNodeAttributeValue(XML_GDTF_BeamType,					type);		GdtfConverter::ConvertBeamType(type, 		pNode,	fBeamType);
	TXString colorIndex;pNode->GetNodeAttributeValue(XML_GDTF_BeamColorRenderingIndex,	colorIndex);GdtfConverter::ConvertInteger(colorIndex, 	pNode,	fColorIndex);
}

void GdtfGeometryLamp::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);
	optional.push_back(XML_GDTF_LampLampType);
	optional.push_back(XML_GDTF_LampPowerConsumption);
	optional.push_back(XML_GDTF_LampLuminousFlux);
	optional.push_back(XML_GDTF_ColorTemperature);
	optional.push_back(XML_GDTF_BeamAngle);
	optional.push_back(XML_GDTF_FieldAngle);
	optional.push_back(XML_GDTF_BeamRadius);
	optional.push_back(XML_GDTF_BeamType);
	optional.push_back(XML_GDTF_BeamColorRenderingIndex);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryLamp::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryLamp;
}

TXString GdtfGeometryLamp::GetNodeName()
{
	return XML_GDTF_LampNodeName;
}

EGdtfLampType GdtfGeometryLamp::GetLampType()
{
	return fLampType;
}

double GdtfGeometryLamp::GetPowerConsumption()
{
	return fPowerConsuption;
}

double GdtfGeometryLamp::GetLuminousIntensity()
{
	return fLuminousIntensity;
}

double GdtfGeometryLamp::GetColorTemperature()
{
	return fColorTemperature;
}

double GdtfGeometryLamp::GetBeamAngle()
{
	return fBeamAngle;
}

double SceneData::GdtfGeometryLamp::GetFieldAngle()
{
    return fFieldAngle;
}

double SceneData::GdtfGeometryLamp::GetBeamRadius()
{
    return fBeamRadius;
}

EGdtfBeamType SceneData::GdtfGeometryLamp::GetBeamType()
{
    return fBeamType;
}

Sint32 SceneData::GdtfGeometryLamp::GetColorIndex()
{
    return fColorIndex;
}

//------------------------------------------------------------------------------------
// GdtfGeometryReference
GdtfBreak::GdtfBreak() : GdtfObject()
{
	fDmxBreak	= 1;
	fDmxAdress	= 1;
}


GdtfBreak::~GdtfBreak()
{
}

void GdtfBreak::SetDmxBreak(Sint32 dmxBreak)
{
	fDmxBreak = dmxBreak;
}

void GdtfBreak::SetDmxAddress(DMXAddress dmxAddress)
{
	fDmxAdress = dmxAddress;
}

void GdtfBreak::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_BreakDMXBreak,	GdtfConverter::ConvertInteger(fDmxBreak));
	pNode->SetNodeAttributeValue(XML_GDTF_BreakOffset,		GdtfConverter::ConvertDMXAdress(fDmxAdress));
	
}

void GdtfBreak::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	TXString dmxbreak;	pNode->GetNodeAttributeValue(XML_GDTF_BreakDMXBreak,dmxbreak	); GdtfConverter::ConvertInteger(dmxbreak, pNode, fDmxBreak);
	TXString dmxAdress;	pNode->GetNodeAttributeValue(XML_GDTF_BreakOffset,	dmxAdress	); GdtfConverter::ConvertDMXAdress(dmxAdress, pNode, fDmxAdress);
}

void GdtfBreak::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	optional.push_back(XML_GDTF_BreakOffset);
	optional.push_back(XML_GDTF_BreakDMXBreak);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfBreak::GetObjectType()
{
	return EGdtfObjectType::eGdtfBreak;
}

TXString GdtfBreak::GetNodeName()
{
	return XML_GDTF_BreakNodeName;
}

Sint32 GdtfBreak::GetDmxBreak()
{
	return fDmxBreak;
}

DMXAddress GdtfBreak::GetDmxAddress()
{
	return fDmxAdress;
}



//------------------------------------------------------------------------------------
// GdtfGeometryReference
GdtfGeometryReference::GdtfGeometryReference(GdtfGeometry* parent) 
					 : GdtfGeometry(parent)
{
	fLinkedGeometry = nullptr;
}

GdtfGeometryReference::GdtfGeometryReference(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) 
					 : GdtfGeometry(name,refToModel,ma, parent)
{
	fLinkedGeometry = nullptr;
}

GdtfGeometryReference::~GdtfGeometryReference()
{
	for (GdtfBreakPtr ptr : fBreaks) { delete ptr; }
}

GdtfBreak* GdtfGeometryReference::AddBreak()
{
	GdtfBreak* gdtfBreak = new GdtfBreak();
	fBreaks.push_back(gdtfBreak);
	return gdtfBreak;
}

GdtfGeometry* GdtfGeometryReference::GetLinkedGeometry()
{
	return fLinkedGeometry;
}

const TXString& GdtfGeometryReference::GetUnresolvedLinkedGeometry()
{
	return fUnresolvedGeoRef;
}

void GdtfGeometryReference::SetLinkedGeometry(GdtfGeometry* ptr)
{
	fLinkedGeometry = ptr;
}

void GdtfGeometryReference::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
	
	//------------------------------------------------------------------------------------
	// Print the content
	for (GdtfBreak* breakObj : fBreaks)
	{
		breakObj->WriteToNode(pNode);
	}

	if(fLinkedGeometry) { pNode->SetNodeAttributeValue(XML_GDTF_GeometryReferenceLinkedGeo, fLinkedGeometry->GetNodeReference()); }

	
}

void GdtfGeometryReference::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
	
	// The breaks are read in the parent OnReadFromNode

	pNode->GetNodeAttributeValue(XML_GDTF_GeometryReferenceLinkedGeo, fUnresolvedGeoRef); 

	
}

void GdtfGeometryReference::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryReferenceLinkedGeo);
	needed.push_back(XML_GDTF_GeometryMatrix);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryReference::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryReference;
}

TXString GdtfGeometryReference::GetNodeName()
{
	return XML_GDTF_GeometryReferenceNodeName;
}

TGdtfBreakArray GdtfGeometryReference::GetBreakArray()
{
	return fBreaks;
}

//------------------------------------------------------------------------------------
// GdtfDmxMode
GdtfDmxMode::GdtfDmxMode()
{
	fName		= "";
	fGeomRef	= nullptr;
}

GdtfDmxMode::GdtfDmxMode(const TXString& name)
{
	fName		= name;
	fGeomRef    = nullptr;
}

GdtfDmxMode::~GdtfDmxMode()
{
    // Housekeeping
    for (GdtfDmxChannelPtr	ptr : fChannels)	{ delete ptr; }
	for (GdtfDmxRelationPtr	ptr : fRelations)	{ delete ptr; }
    
}

void GdtfDmxMode::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_DMXModeName,				fName);
	if (fGeomRef) { pNode->SetNodeAttributeValue(XML_GDTF_DMXModeGeometryRef,		fGeomRef->GetNodeReference()); } ;
	
	// ------------------------------------------------------------------------------------
	// Print Channels
	IXMLFileNodePtr wheels;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_DMXModeDMXChannels, & wheels)))
	{
		for (GdtfDmxChannel* channdelObj : fChannels)
		{
			channdelObj->WriteToNode(wheels);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print Relations
	IXMLFileNodePtr models;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_DMXModeRelations, & models)))
	{
		for (GdtfDmxRelation* relObj : fRelations)
		{
			relObj->WriteToNode(models);
		}
	}
	
}

void GdtfDmxMode::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->GetNodeAttributeValue(XML_GDTF_DMXModeName,		  fName);
	pNode->GetNodeAttributeValue(XML_GDTF_DMXModeGeometryRef, fUnresolvedGeomRef);
	// ------------------------------------------------------------------------------------
	// Print Channels
	
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_DMXModeDMXChannels, XML_GDTF_DMXChannelNodeName, [this] (IXMLFileNodePtr pNode) -> void
								 {
									 GdtfDmxChannelPtr channel = new GdtfDmxChannel(this);
									 channel->ReadFromNode(pNode);
									 fChannels.push_back(channel);
								 }
								 );

	
	// ------------------------------------------------------------------------------------
	// Print Relations
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_DMXModeRelations, XML_GDTF_DMXRelationNodeName, [this] (IXMLFileNodePtr pNode) -> void
								 {
									 GdtfDmxRelationPtr relation = new GdtfDmxRelation();;
									 relation->ReadFromNode(pNode);
									 fRelations.push_back(relation);
								 }
								 );
	
}

void GdtfDmxMode::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_DMXModeName);
	needed.push_back(XML_GDTF_DMXModeGeometryRef);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfDmxMode::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxMode;
}

TXString GdtfDmxMode::GetNodeName()
{
	return XML_GDTF_DMXModeNodeName;
}

GdtfDmxChannel* GdtfDmxMode::AddChannel()
{
	GdtfDmxChannel* channel = new GdtfDmxChannel(this);
	fChannels.push_back(channel);
	
	return channel;
}

const TGdtfDmxChannelArray GdtfDmxMode::GetChannelArray() const
{
	return fChannels;
}

GdtfDmxChannelPtr GdtfDmxMode::GetMasterByRef(const TXString& ref) const
{
	for (GdtfDmxChannelPtr chnl : fChannels)
	{
		if (chnl->GetNodeReference() == ref)
		{
			return chnl;
		}
	}

	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfDmxChannelPtr."));
	return nullptr;
}

GdtfDmxChannelFunctionPtr GdtfDmxMode::GetSlaveByRef(const TXString& ref) const
{
	for (GdtfDmxChannelPtr dmxChannel : fChannels)
	{
		for(GdtfDmxLogicalChannelPtr logicalChannel : dmxChannel->GetLogicalChannelArray())
		{
			for (GdtfDmxChannelFunctionPtr function : logicalChannel->GetDmxChannelFunctions())
			{
				TXString nodeRef = function->GetNodeReference();
				if (nodeRef == ref) { return function; }
			}
		}
	}
	
	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfDmxChannelFuntionPtr."));
	return nullptr;
}


const TXString& GdtfDmxMode::GetModeName() const
{
	return fName;
}

void GdtfDmxMode::SetName(const TXString &name)
{
	fName = name;
}

void GdtfDmxMode::SetGeomRef(GdtfGeometryPtr ptr)
{
	fGeomRef = ptr;
}

GdtfDmxRelation* GdtfDmxMode::AddDmxRelation(GdtfDmxChannel* master, GdtfDmxChannelFunctionPtr slave, const TXString &name)
{
	GdtfDmxRelation* relation = new GdtfDmxRelation(master, slave, name);
	fRelations.push_back(relation);
	return relation;
}

GdtfGeometryPtr	GdtfDmxMode::GetGeomRef()
{
	return fGeomRef;
}

const TXString& GdtfDmxMode::GetUnresolvedGeomRef()
{
	return fUnresolvedGeomRef;
}

const TGdtfDmxRelationArray GdtfDmxMode::GetDmxRelations()
{
	return fRelations;
}

//------------------------------------------------------------------------------------
// GdtfDmxChannel
GdtfDmxChannel::GdtfDmxChannel(GdtfDmxMode* parent)
{
	fName_AutoGenerated					= "";
	fDmxBreak				= 1;
	fCoarse					= 0;	
	fFine					= 0;	
	fUltra					= 0;	
	fUber					= 0;   
	fDefaultValue			= 0;
	fHeighlight				= 0;	fHeighlightNone = true;
	fGeomRef				= nullptr;

	ASSERTN(kEveryone, parent != nullptr);
	fParent = parent;
}

GdtfDmxChannel::~GdtfDmxChannel()
{
	for (GdtfDmxLogicalChannelPtr ptr :fLogicalChannels) { delete ptr; }
}

void GdtfDmxChannel::SetName(const TXString& name)
{
	fName_AutoGenerated = name;
}

void GdtfDmxChannel::SetDmxBreak(Sint32 dmxBreak)
{
	fDmxBreak = dmxBreak;
}

void GdtfDmxChannel::SetDmxCoarse(Sint32 coarse)
{
	fCoarse = coarse;
	
}

void GdtfDmxChannel::SetDmxFine(Sint32 fine)
{
	ASSERTN(kEveryone, fCoarse > 0);
	fFine = fine;
}

void GdtfDmxChannel::SetDmxUltra(Sint32 ultra)
{
	ASSERTN(kEveryone, fCoarse > 0);
	ASSERTN(kEveryone, fFine > 0);
	fUltra = ultra;
}

void SceneData::GdtfDmxChannel::SetDmxUber(Sint32 uber)
{
	ASSERTN(kEveryone, fCoarse > 0);
	ASSERTN(kEveryone, fFine > 0);
	ASSERTN(kEveryone, fUber > 0);
	fUber = uber;
}

void GdtfDmxChannel::SetDefaultValue(DmxValue defaultValue)
{
	fDefaultValue = defaultValue;
}

void GdtfDmxChannel::SetHighlight(DmxValue highlight)
{
	fHeighlight = highlight;
	fHeighlightNone = false;
}

GdtfDmxLogicalChannel* GdtfDmxChannel::AddLogicalChannel()
{
	GdtfDmxLogicalChannel* channel = new GdtfDmxLogicalChannel(this);
	if( ! fLogicalChannels.empty()) { fLogicalChannels.back()->SetNextLogicalChannel(channel); }

	fLogicalChannels.push_back(channel);
	return channel;
}

void GdtfDmxChannel::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	EGdtfChannelBitResolution chanelReso = GetChannelBitResolution();
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelDMXBreak,			GdtfConverter::ConvertDmxBreak(fDmxBreak));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelOffset,				GdtfConverter::ConvertDmxOffset(fCoarse, fFine, fUltra, fUber));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelDefault,			GdtfConverter::ConvertDMXValue(fDefaultValue, chanelReso));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelHighlight,			GdtfConverter::ConvertDMXValue(fHeighlight,	chanelReso, fHeighlightNone));
	if (fGeomRef) { pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelGeometry,			fGeomRef->GetNodeReference()); }
	
	// ------------------------------------------------------------------------------------
	// LogicalChannels
	for (GdtfDmxLogicalChannel* channelObj : fLogicalChannels)
	{
		channelObj->WriteToNode(pNode);
	}
}

void GdtfDmxChannel::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
		
	// ------------------------------------------------------------------------------------
	// Print node attributes
	TXString dmxBreak;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelDMXBreak,			dmxBreak);	GdtfConverter::ConvertDmxBreak(dmxBreak, pNode,		fDmxBreak);
	//
	TXString offset;	
	if (pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelOffset, offset) == kVCOMError_NoError) 
	{
		GdtfConverter::ConvertDmxOffset(offset, pNode, fCoarse, fFine, fUltra, fUber);
	}	

	//
	TXString defVal;	
	if (pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelDefault, defVal) == kVCOMError_NoError)
	{
		GdtfConverter::ConvertDMXValue(defVal, pNode, this->GetChannelBitResolution(), fDefaultValue);
	}	
	//
	TXString highlight;	
	if(VCOM_SUCCEEDED(pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelHighlight,			highlight)	))
	{
		GdtfConverter::ConvertDMXValue(highlight, pNode, this->GetChannelBitResolution(), fHeighlight, fHeighlightNone);
	}	
	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelGeometry, fUnresolvedGeomRef);	
	
	// ------------------------------------------------------------------------------------
	// LogicalChannels	
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_DMXLogicalChannelNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfDmxLogicalChannelPtr logicalChan = new GdtfDmxLogicalChannel(this);

									 // Read from node
									 logicalChan->ReadFromNode(objNode);
									
									// If there is already a logical channel
									if( ! fLogicalChannels.empty())
									{
										// Get the prev array and the new array
										const TGdtfDmxChannelFuntionArray& prevArr = fLogicalChannels.back()->GetDmxChannelFunctions();
										const TGdtfDmxChannelFuntionArray& currArr = logicalChan->GetDmxChannelFunctions();

										// If bouth arrays are not empty, link them togheter
										if( (! prevArr.empty()) && (! currArr.empty()) )
										{
											prevArr.back()->SetNextFunction(currArr.front());
										}
									}
								
									 fLogicalChannels.push_back(logicalChan);
									 return;
								 });
}

void GdtfDmxChannel::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_DMXChannelGeometry);
	optional.push_back(XML_GDTF_DMXChannelDMXBreak);
	optional.push_back(XML_GDTF_DMXChannelOffset);
	optional.push_back(XML_GDTF_DMXChannelDefault);
	optional.push_back(XML_GDTF_DMXChannelHighlight);
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfDmxChannel::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxChannel;
}

TXString GdtfDmxChannel::GetNodeReference()
{
	return GetName();
}

GdtfDmxMode* GdtfDmxChannel::GetParentMode()
{
	return fParent;
}

TXString GdtfDmxChannel::GetNodeName()
{
	return XML_GDTF_DMXChannelNodeName;
}

const TXString& GdtfDmxChannel::GetName()
{
	if(fName_AutoGenerated.IsEmpty())
	{
		TXString dmxChannelName;
		if(fGeomRef) { dmxChannelName += fGeomRef->GetName(); }
		dmxChannelName += "_";
		if(fLogicalChannels.size() > 0) { dmxChannelName += fLogicalChannels[0]->GetAttribute()->GetName(); }
		
		this->SetName(dmxChannelName);

		ASSERTN(kEveryone, fGeomRef != nullptr);
		ASSERTN(kEveryone, fLogicalChannels.size() > 0);
	}

	return fName_AutoGenerated;
}

Sint32 GdtfDmxChannel::GetDmxBreak() const
{
	return fDmxBreak;
}

Sint32 GdtfDmxChannel::GetCoarse() const
{
	return fCoarse;
}

Sint32 GdtfDmxChannel::GetFine() const
{
	return fFine;
}

Sint32 GdtfDmxChannel::GetUltra() const
{
	return fUltra;
}

Sint32 GdtfDmxChannel::GetUber() const
{
	return fUber;
}

DmxValue GdtfDmxChannel::GetDefaultValue() const
{
	return fDefaultValue;
}

DmxValue GdtfDmxChannel::GetHighlight() const
{
	return fHeighlight;
}

bool GdtfDmxChannel::HasHighlight() const
{
	return !fHeighlightNone;
}

void GdtfDmxChannel::SetGeomRef(GdtfGeometryPtr newGeom)
{
	fGeomRef = newGeom;
}

GdtfGeometryPtr GdtfDmxChannel::GetGeomRef()
{
	return fGeomRef;
}

const TGdtfDmxLogicalChannelArray GdtfDmxChannel::GetLogicalChannelArray()
{
	return fLogicalChannels;
}

TXString GdtfDmxChannel::GetUnresolvedGeomRef() const
{
	return fUnresolvedGeomRef;
}

EGdtfChannelBitResolution SceneData::GdtfDmxChannel::GetChannelBitResolution()
{
	// 0 is false, everything else is true
	if		( !fFine  &&  !fUltra &&    !fUber)		{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_8; }
	else if (( fFine) &&  !fUltra  &&   !fUber )	{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_16; }
	else if (( fFine) && ( fUltra) &&   !fUber )	{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_24; }
	else if (( fFine) && ( fUltra) && (  fUber))	{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_32; }
    	
	// Other states are invalid. This line should never be reached.
	DSTOP((kEveryone, "Invalid state in GetChannelBitResolution()"));
	return EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;	
}

DmxValue SceneData::GdtfDmxChannel::GetChannelMaxDmx()
{
	return GdtfConverter::GetChannelMaxDmx(this->GetChannelBitResolution());
}

//------------------------------------------------------------------------------------
// GdtfDmxChannel
GdtfDmxLogicalChannel::GdtfDmxLogicalChannel(GdtfDmxChannel* parent)
{
	fSnap					= EGdtfDmxSnap::eGdtfDmxMaster_No;
	fAttribute				= nullptr;
	fDmxMaster				= eGdtfDmxMaster_None;
	fParentDmxChannel		= parent;
	fNextLogicalChannel		= nullptr;
	fMoveInBlackFrames		= 0;
	fDmxChangeTimeLimit		= 0;
}

GdtfDmxLogicalChannel::~GdtfDmxLogicalChannel()
{
	for (GdtfDmxChannelFunctionPtr ptr : fFunctions) { delete ptr; }
}

void GdtfDmxLogicalChannel::SetName(const TXString &name)
{
	fName_AutoGenerated = name;
}

void GdtfDmxLogicalChannel::SetAttribute(GdtfAttributePtr attr)
{
	fAttribute = attr;
}

void GdtfDmxLogicalChannel::SetDmxSnap(EGdtfDmxSnap snap)
{
	fSnap = snap;
}

void GdtfDmxLogicalChannel::SetDmxMaster(EGdtfDmxMaster master)
{
	fDmxMaster = master;
}

void GdtfDmxLogicalChannel::SetNextLogicalChannel(GdtfDmxLogicalChannel* next)
{
	ASSERTN(kEveryone, fNextLogicalChannel == nullptr);
	fNextLogicalChannel = next;
}

void SceneData::GdtfDmxLogicalChannel::SetMoveInBlackFrames(double moveInBlackFrames)
{
    fMoveInBlackFrames = moveInBlackFrames;
}

void SceneData::GdtfDmxLogicalChannel::SetDmxChangeTimeLimit(double changeLimit)
{
    fDmxChangeTimeLimit = changeLimit;
}

GdtfDmxLogicalChannelPtr GdtfDmxLogicalChannel::GetNextLogicalChannel()
{
	return fNextLogicalChannel;
}

double SceneData::GdtfDmxLogicalChannel::GetMoveInBlackFrames() const
{
    return fMoveInBlackFrames;
}

double SceneData::GdtfDmxLogicalChannel::GetDmxChangeTimeLimit() const
{
    return fDmxChangeTimeLimit;
}

GdtfDmxChannelFunctionPtr GdtfDmxLogicalChannel::AddDmxChannelFunction(const TXString &name)
{
	GdtfDmxChannelFunctionPtr function = new GdtfDmxChannelFunction(name, this);

	// Also set next function here
	if(fFunctions.size() > 0)	{ fFunctions.back()->SetNextFunction(function); }

	fFunctions.push_back(function);

	return function;
}

void GdtfDmxLogicalChannel::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	if (fAttribute) {pNode->SetNodeAttributeValue(XML_GDTF_DMXLogicalChannelAttribute, fAttribute->GetNodeReference()); };
	pNode->SetNodeAttributeValue(XML_GDTF_DMXLogicalChannelSnap,		GdtfConverter::ConvertSnapEnum(fSnap));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXLogicalChannelMaster,		GdtfConverter::ConvertMasterEnum(fDmxMaster));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXLogicalChannelMibFadeFrames,		GdtfConverter::ConvertDouble(fMoveInBlackFrames));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXLogicalChannelDMXChangeTimeLimit,	GdtfConverter::ConvertDouble(fDmxChangeTimeLimit));		
	// ------------------------------------------------------------------------------------
	// LogicalChannels
	for (GdtfDmxChannelFunctionPtr functionObj : fFunctions)
	{
		functionObj->WriteToNode(pNode);
	}
}

void GdtfDmxLogicalChannel::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->GetNodeAttributeValue(XML_GDTF_DMXLogicalChannelAttribute, fUnresolvedAttribRef);
	TXString snap; 	pNode->GetNodeAttributeValue(XML_GDTF_DMXLogicalChannelSnap,	snap);		GdtfConverter::ConvertSnapEnum(snap, 	 pNode, fSnap);
	TXString master;pNode->GetNodeAttributeValue(XML_GDTF_DMXLogicalChannelMaster,	master);	GdtfConverter::ConvertMasterEnum(master, pNode,	fDmxMaster);
	//
	TXString mib;		pNode->GetNodeAttributeValue(XML_GDTF_DMXLogicalChannelMibFadeFrames,		mib);		GdtfConverter::ConvertDouble(mib, 		pNode,	fMoveInBlackFrames);
	TXString timelimit;	pNode->GetNodeAttributeValue(XML_GDTF_DMXLogicalChannelDMXChangeTimeLimit,	timelimit);	GdtfConverter::ConvertDouble(timelimit, pNode,	fDmxChangeTimeLimit);
	
	// ------------------------------------------------------------------------------------
	// Read LogicalChannels
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_DMXChannelFuntionNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfDmxChannelFunctionPtr function = new GdtfDmxChannelFunction(this);
									 
									 // Read from node
									 function->ReadFromNode(objNode);

									 if(fFunctions.size() > 0)	{ fFunctions.back()->SetNextFunction(function); }
									 
									 // Add to list
									 fFunctions.push_back(function);

									 
									 return;
								 });
}

void GdtfDmxLogicalChannel::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_DMXLogicalChannelAttribute);
	optional.push_back(XML_GDTF_DMXLogicalChannelSnap);
	optional.push_back(XML_GDTF_DMXLogicalChannelMaster);
    optional.push_back(XML_GDTF_DMXLogicalChannelMibFadeFrames);
	optional.push_back(XML_GDTF_DMXLogicalChannelDMXChangeTimeLimit);	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfDmxLogicalChannel::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxLogicalChannel;
}

TXString GdtfDmxLogicalChannel::GetNodeReference()
{
	return fParentDmxChannel->GetNodeReference() + "." + GetName();
}

TXString GdtfDmxLogicalChannel::GetNodeName()
{
	return XML_GDTF_DMXLogicalChannelNodeName;
}

const TXString& GdtfDmxLogicalChannel::GetName()
{
	if(fName_AutoGenerated.IsEmpty())
	{
		TXString name;
		ASSERTN(kEveryone, fAttribute != nullptr);
		if(fAttribute){ name +=fAttribute->GetName(); }

		this->SetName(name);
	}
	return fName_AutoGenerated;
}

GdtfAttribute* GdtfDmxLogicalChannel::GetAttribute()
{
	return fAttribute;
}

EGdtfDmxSnap GdtfDmxLogicalChannel::GetDmxSnap() const
{
	return fSnap;
}

EGdtfDmxMaster GdtfDmxLogicalChannel::GetDmxMaster() const
{
	return fDmxMaster;
}

const TGdtfDmxChannelFuntionArray GdtfDmxLogicalChannel::GetDmxChannelFunctions()
{
	return fFunctions;
}

TXString GdtfDmxLogicalChannel::GetUnresolvedAttribRef() const
{
	return fUnresolvedAttribRef;
}

GdtfDmxChannel* GdtfDmxLogicalChannel::GetParentDMXChannel() const 
{
	return fParentDmxChannel;
}

//------------------------------------------------------------------------------------
// GdtfDmxChannelFuntion
GdtfDmxChannelFunction::GdtfDmxChannelFunction(GdtfDmxLogicalChannel* parent)
{	
	fAdressStart			= 0;
	fPhysicalStart			= 0;
	fPhysicalEnd			= 1;
	fRealFade				= 0;
	fOnWheel				= nullptr;
	fEmitter				= nullptr;	
	fDmxInvert				= EGDTFDmxInvert::eGDTFDmxInvert_No;
	fAttribute				= nullptr;
	fParentLogicalChannel	= parent;
	fNextFunction			= nullptr;

	fModeMaster_Channel		= nullptr;
	fModeMaster_Function	= nullptr;
	fDmxModeStart			= 0;
	fDmxModeEnd				= 0;
}

GdtfDmxChannelFunction::GdtfDmxChannelFunction(const TXString& name, GdtfDmxLogicalChannel* parent)
{
	fName					= name;
	fAdressStart			= 0;
	fPhysicalStart			= 0;
	fPhysicalEnd			= 1;
	fRealFade				= 0;
	fOnWheel				= nullptr;
	fEmitter				= nullptr;				
	fDmxInvert				= EGDTFDmxInvert::eGDTFDmxInvert_No;	
	fAttribute				= nullptr;
	fParentLogicalChannel	= parent;
	fNextFunction			= nullptr;

	fModeMaster_Channel		= nullptr;
	fModeMaster_Function	= nullptr;
	fDmxModeStart			= 0;
	fDmxModeEnd				= 0;
}

GdtfDmxChannelFunction::~GdtfDmxChannelFunction()
{
	for (GdtfDmxChannelSetPtr ptr : fChannelSets) { delete ptr; }
}

void GdtfDmxChannelFunction::SetNextFunction(GdtfDmxChannelFunction* next)
{
	ASSERTN(kEveryone, fNextFunction == nullptr);
	fNextFunction = next;
}

void GdtfDmxChannelFunction::SetName(const TXString &name)
{
	fName = name;
}

void GdtfDmxChannelFunction::SetAttribute(GdtfAttribute* newAttr)
{
	fAttribute = newAttr;
}

void GdtfDmxChannelFunction::SetOriginalAttribute(const TXString &attribute)
{
	fOrignalAttribute = attribute;
}

void GdtfDmxChannelFunction::SetStartAddress(DmxValue address)
{
	fAdressStart = address;
}

void GdtfDmxChannelFunction::SetPhysicalStart(double start)
{
	fPhysicalStart = start;
}

void GdtfDmxChannelFunction::SetPhysicalEnd(double end)
{
	fPhysicalEnd = end;
}

void GdtfDmxChannelFunction::SetRealFade(double fade)
{
	fRealFade = fade;
}

GdtfDmxChannelSet* GdtfDmxChannelFunction::AddChannelSet(const TXString &name)
{
	GdtfDmxChannelSet* channelSet = new GdtfDmxChannelSet(name, this);
	fChannelSets.push_back(channelSet);
	return channelSet;
}

void GdtfDmxChannelFunction::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	EGdtfChannelBitResolution chanelReso = GetParentDMXChannel()->GetChannelBitResolution();

	ASSERTN(kEveryone, fAttribute!= nullptr);
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionName,				fName);

	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDMXFrom,				GdtfConverter::ConvertDMXValue(fAdressStart, chanelReso));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalFrom,		GdtfConverter::ConvertDouble(fPhysicalStart));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalTo,			GdtfConverter::ConvertDouble(fPhysicalEnd));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionRealFade,			GdtfConverter::ConvertDouble(fRealFade));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelDMXInvert,					GdtfConverter::ConvertDMXInvertEnum(fDmxInvert));	
	
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionOriginalAttribute,								fOrignalAttribute);
	if (fAttribute)		    { pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionAttribute,			    fAttribute->GetNodeReference());}
	if (fOnWheel)			{ pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionWheelRef,				fOnWheel->GetNodeReference()); };
	if (fEmitter)			{ pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelEmitter,						fEmitter->GetNodeReference() ); };
	

	if(fModeMaster_Channel)
	{
		ASSERTN(kEveryone, (fModeMaster_Function == nullptr));

		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeMaster,				fModeMaster_Channel->GetNodeReference());	
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeFrom,				GdtfConverter::ConvertDMXValue(fDmxModeStart, fModeMaster_Channel->GetChannelBitResolution()));	
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeTo,					GdtfConverter::ConvertDMXValue(fDmxModeEnd,   fModeMaster_Channel->GetChannelBitResolution()));	
	}
	if(fModeMaster_Function)
	{
		ASSERTN(kEveryone, (fModeMaster_Channel == nullptr));

		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeMaster,				fModeMaster_Function->GetNodeReference());	
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeFrom,				GdtfConverter::ConvertDMXValue(fDmxModeStart, fModeMaster_Function->GetParentDMXChannel()->GetChannelBitResolution()));	
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeTo,					GdtfConverter::ConvertDMXValue(fDmxModeEnd,   fModeMaster_Function->GetParentDMXChannel()->GetChannelBitResolution()));	
	}

	// ------------------------------------------------------------------------------------
	// Prepare No Feature Channel Set
	TGdtfDmxChannelSetArray tempArr;
	bool					hasChannelSets = fChannelSets.size() > 0;
	
	// Sort from low to high
	std::sort(fChannelSets.begin(), fChannelSets.end(), [](const GdtfDmxChannelSetPtr & a, const GdtfDmxChannelSetPtr & b) -> bool { return a->GetDmxStart() < b->GetDmxStart(); });
	
	// If it has channel sets, process first obj
	if(hasChannelSets)
	{
		GdtfDmxChannelSetPtr firstChannelSet = fChannelSets[0];
		
		if(firstChannelSet->GetDmxStart() > this->GetStartAdress())
		{
			GdtfDmxChannelSetPtr noFeature = new GdtfDmxChannelSet("", this);
			noFeature->SetDmxStart(this->GetStartAdress());
			tempArr.push_back(noFeature);
		}
		
		// add the first one
		tempArr.push_back(firstChannelSet);
	}
	
	// Process the spaces between the channel sets
	for (size_t i = 1; i < fChannelSets.size(); i++)
	{
		GdtfDmxChannelSetPtr first  = fChannelSets[i-1];
		GdtfDmxChannelSetPtr second = fChannelSets[ i ];
		
		DmxValue diff = second ->GetDmxStart() - first->GetDmxEnd();
		
		if (diff > 1)
		{
			GdtfDmxChannelSetPtr noFeature = new GdtfDmxChannelSet("", this);
			noFeature->SetDmxStart(first->GetDmxEnd()  + 1);
			noFeature->SetDmxEnd(second->GetDmxStart() - 1);
			tempArr.push_back(noFeature);
		}
		else if(diff < 1)	{ DSTOP((kEveryone, "Wrong Formated ChannelSet")); }
		
		tempArr.push_back(second);
		
	}
	
	// Process the last channel set
	if(hasChannelSets)
	{
		GdtfDmxChannelSetPtr lastChannelSet = fChannelSets.back();
		if(lastChannelSet->GetDmxEnd() < this->GetEndAdress())
		{
			GdtfDmxChannelSetPtr noFeature = new GdtfDmxChannelSet("", this);
			noFeature->SetDmxStart(lastChannelSet->GetDmxEnd() + 1);
			noFeature->SetDmxEnd(this->GetEndAdress());
			tempArr.push_back(noFeature);
		}
	}
	
	
	// ------------------------------------------------------------------------------------
	// Now print them to the node
	for (GdtfDmxChannelSet* channelObj : tempArr)
	{
		channelObj->WriteToNode(pNode);
	}
	
	fChannelSets = tempArr;
}

void GdtfDmxChannelFunction::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	EGdtfChannelBitResolution channelReso = fParentLogicalChannel->GetParentDMXChannel()->GetChannelBitResolution();

						pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionName,				fName);
						pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionOriginalAttribute,	fOrignalAttribute);
	TXString dmxFrom;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDMXFrom,				dmxFrom);	GdtfConverter::ConvertDMXValue(dmxFrom, 			pNode,	channelReso,fAdressStart);
	TXString physFrom;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalFrom,		physFrom);	GdtfConverter::ConvertDouble(physFrom, 				pNode,				fPhysicalStart);
	TXString physTo;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalTo,			physTo);	GdtfConverter::ConvertDouble(physTo, 				pNode,				fPhysicalEnd);
	TXString realFade;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionRealFade,			realFade);	GdtfConverter::ConvertDouble(realFade, 				pNode,				fRealFade);
	TXString dmxInvert;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelDMXInvert,					dmxInvert);	GdtfConverter::ConvertDMXInvertEnum(dmxInvert, 		pNode,				fDmxInvert);	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionAttribute, 	fUnresolvedAttrRef);	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionWheelRef, 	fUnresolvedWheelRef);
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelEmitter, 			fUnresolvedEmitterRef);

	// Read Mode Master
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeMaster,				fUnresolvedModeMaster);	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeFrom,				fUnresolvedDmxModeStart);	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeTo,					fUnresolvedDmxModeEnd);	

	// ------------------------------------------------------------------------------------
	// GdtfDmxChannelSet
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_DMXChannelSetNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfDmxChannelSetPtr channelSet = new GdtfDmxChannelSet(this);
									 
									 // Read from node
									 channelSet->ReadFromNode(objNode);
									
									// Link with next
									if(!fChannelSets.empty()) { fChannelSets.back()->SetNextChannelSet(channelSet);}
									 
									 // Add to list
									 fChannelSets.push_back(channelSet);
									 return;
								 });
	
	// Now calculate end values
	for (size_t i = 1; i < fChannelSets.size() ; i++)
	{
		GdtfDmxChannelSetPtr first  = fChannelSets[i-1];
		GdtfDmxChannelSetPtr second = fChannelSets[ i ];
		
		first->SetDmxEnd(second->GetDmxStart() - 1);
	}
}

void GdtfDmxChannelFunction::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	optional.push_back(XML_GDTF_DMXChannelFuntionName);
	optional.push_back(XML_GDTF_DMXChannelFuntionAttribute);
	optional.push_back(XML_GDTF_DMXChannelFuntionOriginalAttribute);
	optional.push_back(XML_GDTF_DMXChannelFuntionDMXFrom);
	optional.push_back(XML_GDTF_DMXChannelFuntionPhysicalFrom);
	optional.push_back(XML_GDTF_DMXChannelFuntionPhysicalTo);
	optional.push_back(XML_GDTF_DMXChannelFuntionWheelRef);
	optional.push_back(XML_GDTF_DMXChannelEmitter);	
	optional.push_back(XML_GDTF_DMXChannelFuntionModeMaster);
	optional.push_back(XML_GDTF_DMXChannelFuntionModeFrom);
	optional.push_back(XML_GDTF_DMXChannelFuntionModeTo);
	optional.push_back(XML_GDTF_DMXChannelFuntionRealFade);
	optional.push_back(XML_GDTF_DMXChannelDMXInvert);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfDmxChannelFunction::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxChannelFuntion;
}

TXString GdtfDmxChannelFunction::GetNodeName()
{
	return XML_GDTF_DMXChannelFuntionNodeName;
}

TXString GdtfDmxChannelFunction::GetNodeReference()
{
	TXString functionName = GetName();
	if(functionName.IsEmpty())
	{
		ASSERTN(kEveryone, GetAttribute() != nullptr);
		if(GetAttribute() != nullptr)
		{
			functionName = GetAttribute()->GetName();
			functionName += " ";
			functionName << GetNumberInParent();
		}
		
	}
	return fParentLogicalChannel->GetNodeReference() + "." + functionName;
}

size_t GdtfDmxChannelFunction::GetNumberInParent() const
{
	size_t count = fParentLogicalChannel->GetDmxChannelFunctions().size();
	for(size_t i = 0; i < count; i++)
	{
		if(fParentLogicalChannel->GetDmxChannelFunctions()[i] == this)
		{
			return (i+1);
		}
	}
	
	DSTOP("Failed to get GetNumberInParent");
	return 1;
}

const TXString& GdtfDmxChannelFunction::GetName() const
{
	return fName;
}

GdtfAttribute* GdtfDmxChannelFunction::GetAttribute()
{
	return fAttribute;
}

const TXString& GdtfDmxChannelFunction::GetOriginalAttribute()
{
	return fOrignalAttribute;
}

DmxValue GdtfDmxChannelFunction::GetStartAdress() const
{
	return fAdressStart;
}

DmxValue GdtfDmxChannelFunction::GetEndAdress() const
{
	// If there is a next function, return the end address based on this
	GdtfDmxChannelFunction* nextFunctionForAddress = fNextFunction;
	while(nextFunctionForAddress != nullptr) 
	{
		// There could be serveral Channel Function that have the same start adress, step over them 
		if(nextFunctionForAddress->GetStartAdress() == this->GetStartAdress()) { nextFunctionForAddress = nextFunctionForAddress->GetNextFunction(); }
		// If the Start Adress differrs, the end Adress is based on the start adress of this channel 
		else { return(fNextFunction->GetStartAdress() - 1);  }	 
		// The last channel function will have a nullptr for the next function 
	}

	// If there is a next channel function return the end address based on its frist funxtion
	GdtfDmxLogicalChannelPtr nextLogChannel = fParentLogicalChannel->GetNextLogicalChannel();
	if(nextLogChannel)
	{
		if(!nextLogChannel->GetDmxChannelFunctions().empty())
		{ return (nextLogChannel->GetDmxChannelFunctions().front()->GetStartAdress() - 1); }
		
	}	

	// Otherwise return the max for this feature
	return fParentLogicalChannel->GetParentDMXChannel()->GetChannelMaxDmx();
}

double GdtfDmxChannelFunction::GetPhysicalStart() const
{
	return fPhysicalStart;
}

double GdtfDmxChannelFunction::GetPhysicalEnd() const
{
	return fPhysicalEnd;
}

double GdtfDmxChannelFunction::GetRealFade() const
{
	return fRealFade;
}

GdtfWheelPtr GdtfDmxChannelFunction::GetOnWheel() const
{
	return fOnWheel;
}

GdtfPhysicalEmitter * SceneData::GdtfDmxChannelFunction::GetEmitter() const
{
    return fEmitter;
}

void GdtfDmxChannelFunction::SetWheel(GdtfWheelPtr newWhl)
{
	fOnWheel = newWhl;
}

EGDTFDmxInvert SceneData::GdtfDmxChannelFunction::GetDmxInvert() const
{
    return fDmxInvert;
}

const TGdtfDmxChannelSetArray GdtfDmxChannelFunction::GetChannelSets()
{
	return fChannelSets;
}

GdtfDmxChannel* GdtfDmxChannelFunction::GetModeMaster_Channel() const
{
	return fModeMaster_Channel;
}

GdtfDmxChannelFunction* GdtfDmxChannelFunction::GetModeMaster_Function() const
{
	return fModeMaster_Function;
}

DmxValue GdtfDmxChannelFunction::GetModeMasterDmxStart() const
{
	return fDmxModeStart;
}

DmxValue GdtfDmxChannelFunction::GetModeMasterDmxEnd() const
{
	return fDmxModeEnd;
}

void GdtfDmxChannelFunction::ResolveModeMasterDmx(EGdtfChannelBitResolution resolution)
{
	IXMLFileNodePtr node;
	this->GetNode(node);

	GdtfConverter::ConvertDMXValue(fUnresolvedDmxModeStart, node, resolution, fDmxModeStart);
	GdtfConverter::ConvertDMXValue(fUnresolvedDmxModeEnd,node, resolution, fDmxModeEnd);
}

void GdtfDmxChannelFunction::SetModeMaster_Channel(GdtfDmxChannel* channel)
{
	ASSERTN(kEveryone, fModeMaster_Function == nullptr);
	fModeMaster_Function = nullptr;
	fModeMaster_Channel = channel;
}

void GdtfDmxChannelFunction::SetModeMaster_Function(GdtfDmxChannelFunction* function)
{
	ASSERTN(kEveryone, fModeMaster_Channel == nullptr);
	fModeMaster_Channel = nullptr;
	fModeMaster_Function = function;
}

void GdtfDmxChannelFunction::SetModeMasterDmxStart(DmxValue start)
{
	fDmxModeStart = start;
}

void GdtfDmxChannelFunction::SetModeMasterDmxEnd(DmxValue end)
{
	fDmxModeEnd = end;
}

void GdtfDmxChannelFunction::SetEmitter(GdtfPhysicalEmitter* newEmit)
{
	fEmitter = newEmit;
}

void SceneData::GdtfDmxChannelFunction::SetDmxInvert(EGDTFDmxInvert dmxInvert)
{
    fDmxInvert = dmxInvert;
}

TXString GdtfDmxChannelFunction::getUnresolvedAttrRef() const
{
	return fUnresolvedAttrRef;
}

TXString GdtfDmxChannelFunction::getUnresolvedWheelRef() const
{
	return fUnresolvedWheelRef;
}

TXString GdtfDmxChannelFunction::getUnresolvedEmitterRef() const
{
	return fUnresolvedEmitterRef;
}

TXString GdtfDmxChannelFunction::getUnresolvedModeMasterRef() const
{
	return fUnresolvedModeMaster;
}

GdtfDmxChannel * SceneData::GdtfDmxChannelFunction::GetParentDMXChannel() const
{
	return fParentLogicalChannel->GetParentDMXChannel();
}

GdtfDmxLogicalChannel * SceneData::GdtfDmxChannelFunction::GetParentLogicalChannel() const
{
	return fParentLogicalChannel;
}

GdtfDmxChannelFunction* SceneData::GdtfDmxChannelFunction::GetNextFunction() const
{
	return fNextFunction;
}

//------------------------------------------------------------------------------------
// GdtfDmxChannelSet
GdtfDmxChannelSet::GdtfDmxChannelSet(GdtfDmxChannelFunction* parent)
{
	fDmxStart		= 0;
	fDmxEnd			= -1;
	fPhysicalStart	= 0.0;
	fPhysicalEnd	= 1.0;	
	fWheelSlotIdx	= 0;
	fSetPhysical	= false;
	fNextChannelSet = nullptr;
	fParentChnlFunction = parent;
}

GdtfDmxChannelSet::GdtfDmxChannelSet(const TXString& name, GdtfDmxChannelFunction* parent)
{
	fUniqueName = name;
	fDmxStart		= 0;
	fDmxEnd			= -1;
	fPhysicalStart	= 0.0;
	fPhysicalEnd	= 1.0;	
	fWheelSlotIdx	= 0;
	fSetPhysical	= false;
	fNextChannelSet = nullptr;
	fParentChnlFunction = parent;
}

GdtfDmxChannelSet::~GdtfDmxChannelSet()
{
}

void GdtfDmxChannelSet::SetNextChannelSet(GdtfDmxChannelSet* next)
{
	ASSERTN(kEveryone, fNextChannelSet == nullptr);
	fNextChannelSet = next;
}

void GdtfDmxChannelSet::SetName(const TXString& name)
{
	fUniqueName = name;
}

void GdtfDmxChannelSet::SetDmxStart(DmxValue start)
{
	fDmxStart = start;
}

void GdtfDmxChannelSet::SetDmxEnd(DmxValue end)
{
	fDmxEnd = end;
}

void GdtfDmxChannelSet::SetPhysicalStart(double start)
{
	fPhysicalStart = start;
	fSetPhysical	= true;
}

void GdtfDmxChannelSet::SetPhysicalEnd(double end)
{
	fPhysicalEnd = end;
	fSetPhysical	= true;
}

void GdtfDmxChannelSet::SetWheelSlot(Sint32 slotIndex)
{
	fWheelSlotIdx = slotIndex;
}

void GdtfDmxChannelSet::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	EGdtfChannelBitResolution chanelReso = GetParentDMXChannel()->GetChannelBitResolution();
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelSetName,				fUniqueName);
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelSetDMXFrom,				GdtfConverter::ConvertDMXValue(fDmxStart, chanelReso));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelSetWheelSlotIndexRef,	GdtfConverter::ConvertInteger(fWheelSlotIdx));
	
	if(fSetPhysical)
	{
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalFrom,		GdtfConverter::ConvertDouble(fPhysicalStart));
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalTo,			GdtfConverter::ConvertDouble(fPhysicalEnd));
	}
	
}

void GdtfDmxChannelSet::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetName,				fUniqueName);
	
	EGdtfChannelBitResolution channelReso = fParentChnlFunction->GetParentDMXChannel()->GetChannelBitResolution();

	TXString dmxfrom;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetDMXFrom,				dmxfrom);	GdtfConverter::ConvertDMXValue (dmxfrom, pNode, channelReso, fDmxStart);
	TXString wheelId;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetWheelSlotIndexRef,	wheelId);	GdtfConverter::ConvertInteger(wheelId, pNode,  fWheelSlotIdx);
	
	
	TXString physFrom; pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalFrom,		physFrom);
	TXString physTo;   pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalTo,	    physTo);
	
	bool b1 = GdtfConverter::ConvertDouble(physTo, pNode,	fPhysicalEnd);
	bool b2 = GdtfConverter::ConvertDouble(physFrom, pNode,	fPhysicalStart);
	fSetPhysical = (b1 && b2);

}

void GdtfDmxChannelSet::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	optional.push_back(XML_GDTF_DMXChannelSetName);
	optional.push_back(XML_GDTF_DMXChannelSetDMXFrom);
	optional.push_back(XML_GDTF_DMXChannelSetWheelSlotIndexRef);

	if(fSetPhysical)
	{
		needed.push_back(XML_GDTF_DMXChannelSetPhysicalFrom);
		needed.push_back(XML_GDTF_DMXChannelSetPhysicalTo);

	}
	else
	{
		optional.push_back(XML_GDTF_DMXChannelSetPhysicalFrom);
		optional.push_back(XML_GDTF_DMXChannelSetPhysicalTo);
	}
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfDmxChannelSet::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxChannelSet;
}

TXString GdtfDmxChannelSet::GetNodeName()
{
	return XML_GDTF_DMXChannelSetNodeName;
}

const TXString& GdtfDmxChannelSet::GetName() const
{
	return fUniqueName;
}

bool GdtfDmxChannelSet::GetUsePhysicalFromParent() const
{
	return !fSetPhysical;
}

DmxValue GdtfDmxChannelSet::GetDmxStart() const
{
	return fDmxStart;
}

DmxValue GdtfDmxChannelSet::GetDmxEnd() const
{
	if(fNextChannelSet == nullptr && fDmxEnd == size_t(-1)) {  return fParentChnlFunction->GetEndAdress(); }
	return fDmxEnd;
}

double GdtfDmxChannelSet::GetPhysicalStart() const
{
	return fPhysicalStart;
}

double GdtfDmxChannelSet::GetPhysicalEnd() const
{
	return fPhysicalEnd;
}

Sint32 GdtfDmxChannelSet::GetWheelSlot()
{
	return fWheelSlotIdx;
}

GdtfDmxChannel * SceneData::GdtfDmxChannelSet::GetParentDMXChannel() const
{
	return fParentChnlFunction->GetParentDMXChannel();
}

//------------------------------------------------------------------------------------
// GdtfDmxRelation
GdtfDmxRelation::GdtfDmxRelation()
{
	fMasterDmxChannel		= nullptr;
	fSlaveChannelFunction	= nullptr;
	fRelationType			= EGdtfDmxRelationType::eGdtfDmxRelationType_Override;

}

GdtfDmxRelation::GdtfDmxRelation(GdtfDmxChannelPtr master, GdtfDmxChannelFunctionPtr slave, const TXString& name)
{
	fUniqueName				= name;
	fMasterDmxChannel		= master;
	fSlaveChannelFunction	= slave;
	fRelationType			= EGdtfDmxRelationType::eGdtfDmxRelationType_Override;
}

GdtfDmxRelation::~GdtfDmxRelation()
{
}

void GdtfDmxRelation::SetName(const TXString& name)
{
	fUniqueName = name;
}

void GdtfDmxRelation::SetRelationType(EGdtfDmxRelationType type)
{
	fRelationType = type;
}

void GdtfDmxRelation::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationName,				fUniqueName);
	if (fMasterDmxChannel) 		{ pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationMaster,			fMasterDmxChannel->GetNodeReference());}
	if (fSlaveChannelFunction)  { pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationSlave,			fSlaveChannelFunction->GetNodeReference());}
	pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationType,		GdtfConverter::ConvertRelationEnum(fRelationType));


}

void GdtfDmxRelation::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->GetNodeAttributeValue(XML_GDTF_DMXRelationName,	 fUniqueName);
	pNode->GetNodeAttributeValue(XML_GDTF_DMXRelationMaster, fUnresolvedMasterRef);
	pNode->GetNodeAttributeValue(XML_GDTF_DMXRelationSlave,	 fUnresolvedSlaveRef);
    TXString type;		pNode->GetNodeAttributeValue(XML_GDTF_DMXRelationType,		type);		GdtfConverter::ConvertRelationEnum(type, pNode,	fRelationType); 
}

void GdtfDmxRelation::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_DMXRelationName);
	needed.push_back(XML_GDTF_DMXRelationMaster);
	needed.push_back(XML_GDTF_DMXRelationSlave);
	needed.push_back(XML_GDTF_DMXRelationType);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfDmxRelation::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxRelation;
}

TXString GdtfDmxRelation::GetNodeName()
{
	return XML_GDTF_DMXRelationNodeName;
}

const TXString& GdtfDmxRelation::GetName() const
{
	return fUniqueName;
}

GdtfDmxChannelPtr GdtfDmxRelation::GetMasterChannel() const
{
	return fMasterDmxChannel;
}

void GdtfDmxRelation::SetMasterChannel(GdtfDmxChannelPtr newMaster)
{
	fMasterDmxChannel = newMaster;
}

GdtfDmxChannelFunctionPtr GdtfDmxRelation::GetSlaveChannel() const
{
	return fSlaveChannelFunction;
}

void GdtfDmxRelation::SetSlaveChannel(GdtfDmxChannelFunctionPtr newSlave)
{
	fSlaveChannelFunction = newSlave;
}

TXString GdtfDmxRelation::GetUnresolvedMasterRef() const
{
	return fUnresolvedMasterRef;
}

TXString GdtfDmxRelation::GetUnresolvedSlaveRef() const
{
	return fUnresolvedSlaveRef;
}

EGdtfDmxRelationType GdtfDmxRelation::GetRelationType() const
{
	return fRelationType;
}

//------------------------------------------------------------------------------------
// GdtfRevision
GdtfRevision::GdtfRevision()
{
    fText 			= "";
	fUserId 		= 0;
	fDateS.fYear	= 0;
	fDateS.fMonth	= 0;
	fDateS.fDay		= 0;
	fDateS.fHour	= 0;
	fDateS.fMinute	= 0;
	fDateS.fSecond	= 0;
    
}

GdtfRevision::~GdtfRevision()
{
}

void GdtfRevision::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RevisionText,			fText);
	pNode->SetNodeAttributeValue(XML_GDTF_RevisionDate,			SceneData::GdtfConverter::ConvertDate(fDateS));
	pNode->SetNodeAttributeValue(XML_GDTF_RevisionUserId,		SceneData::GdtfConverter::ConvertInteger(fUserId));
	
}

void GdtfRevision::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
						pNode->GetNodeAttributeValue(XML_GDTF_RevisionText,		fText);
	TXString date;		pNode->GetNodeAttributeValue(XML_GDTF_RevisionDate, 	date);		GdtfConverter::ConvertDate(date, pNode, fDateS);
	TXString userid;	pNode->GetNodeAttributeValue(XML_GDTF_RevisionUserId, 	userid);	GdtfConverter::ConvertInteger(userid, pNode, fUserId);

}

void GdtfRevision::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RevisionDate);
	optional.push_back(XML_GDTF_RevisionText);
	optional.push_back(XML_GDTF_RevisionUserId);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfRevision::GetObjectType()
{
	return EGdtfObjectType::eGdtfRevision;
}

TXString GdtfRevision::GetNodeName()
{
	return XML_GDTF_RevisionNodeName;
}

void GdtfRevision::SetText(const TXString& text)
{
	fText = text;
}

void GdtfRevision::SetDate(const STime& date)
{
	fDateS.fYear	= date.fYear;
	fDateS.fMonth	= date.fMonth;
	fDateS.fDay		= date.fDay;
	fDateS.fHour	= date.fHour;
	fDateS.fMinute	= date.fMinute;
	fDateS.fSecond	= date.fSecond;
}

const STime& GdtfRevision::GetDate() const
{
	return fDateS;
}

const TXString& GdtfRevision::GetText() const
{
	return fText;
}

size_t GdtfRevision::GetUserId() const
{
	return fUserId;
}

void GdtfRevision::SetUserId(size_t value) 
{
	fUserId = value;
}

//------------------------------------------------------------------------------------
// GdtfPhysicalEmitter
GdtfPhysicalEmitter::GdtfPhysicalEmitter()
{
	fColor		= CRGBColor(255, 255, 255);
}

GdtfPhysicalEmitter::GdtfPhysicalEmitter(const TXString& name)
{
	fColor		= CRGBColor(255, 255, 255);
	fName		= name;
}

GdtfPhysicalEmitter::~GdtfPhysicalEmitter()
{
	for (GdtfMeasurementPointPtr ptr : fMeasurePoints) { delete ptr; }
}

void GdtfPhysicalEmitter::SetName(const TXString &name)
{
	fName = name;
}

void GdtfPhysicalEmitter::SetColor(CCieColor color)
{
	fColor = color;
}

GdtfMeasurementPoint* GdtfPhysicalEmitter::AddMeasurementPoint()
{
	GdtfMeasurementPoint* point = new GdtfMeasurementPoint();
	fMeasurePoints.push_back(point);
	return point;
}

void GdtfPhysicalEmitter::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_EmitterName,				fName);
	pNode->SetNodeAttributeValue(XML_GDTF_EmitterColor,				GdtfConverter::ConvertColor(fColor));
	
	//------------------------------------------------------------------------------------
	// Write MeasurePoints
	for (GdtfMeasurementPoint* measurePointObj : fMeasurePoints)
	{
		measurePointObj->WriteToNode(pNode);
	}
}

void GdtfPhysicalEmitter::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->GetNodeAttributeValue(XML_GDTF_EmitterName,				fName);
	TXString color;		pNode->GetNodeAttributeValue(XML_GDTF_EmitterColor,				color);		GdtfConverter::ConvertColor(color, pNode, fColor);
	
	
	// ------------------------------------------------------------------------------------
	// Read MeasurePoints
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_MeasurementNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfMeasurementPointPtr mesPoint = new GdtfMeasurementPoint();
									 
									 // Read from node
									 mesPoint->ReadFromNode(objNode);
									 
									 // Add to list
									 fMeasurePoints.push_back(mesPoint);
									 return;
								 });
}

void GdtfPhysicalEmitter::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_EmitterName);
	needed.push_back(XML_GDTF_EmitterColor);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfPhysicalEmitter::GetObjectType()
{
	return EGdtfObjectType::eGdtfPhysicalEmitter;
}

TXString GdtfPhysicalEmitter::GetNodeName()
{
	return XML_GDTF_EmitterNodeName;
}

const TXString& GdtfPhysicalEmitter::GetName() const
{
	return fName;
}

CCieColor GdtfPhysicalEmitter::GetColor() const
{
	return fColor;
}

const TGdtfMeasurementPointArray GdtfPhysicalEmitter::GetMeasurementPoints()
{
	return fMeasurePoints;
}

TXString GdtfPhysicalEmitter::GetNodeReference()
{
	return GetName();
}

//------------------------------------------------------------------------------------
// Macro
GdtfUserPreset::GdtfUserPreset()
{
}

GdtfUserPreset::~GdtfUserPreset()
{
}

void GdtfUserPreset::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
}

void GdtfUserPreset::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
}

EGdtfObjectType GdtfUserPreset::GetObjectType()
{
	return EGdtfObjectType::eGdtfUserPreset;
}

TXString GdtfUserPreset::GetNodeName()
{
	return XML_GDTF_UserPresetNodeName;
}

//------------------------------------------------------------------------------------
// Macro
GdtfMacro::GdtfMacro(const TXString& name)
{
    fName = name;
    fMacroDMX = nullptr;
    fMacroVisual = nullptr;
}

GdtfMacro::~GdtfMacro()
{    
    if (fMacroDMX)    { delete fMacroDMX; }
    if (fMacroVisual) { delete fMacroVisual; }    
}

void GdtfMacro::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);
    //------------------------------------------------------------------------------------
    // Print the childs
    if (fMacroDMX != nullptr) 
    {
        fMacroDMX->WriteToNode(pNode);
    }    
    if (fMacroVisual != nullptr)
    {
        fMacroVisual->WriteToNode(pNode);
    }
}

void GdtfMacro::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
    //------------------------------------------------------------------------------------
    // Get the attributes	
    pNode->GetNodeAttributeValue(XML_GDTF_MacroName, fName);    
    //------------------------------------------------------------------------------------
    // Read the childs
    // MacroDMX
    IXMLFileNode* macroDmxNode;
    pNode->GetChildNode(XML_GDTF_MacroDMX, &macroDmxNode);
    
    if (macroDmxNode != nullptr) 
    {
        this->fMacroDMX = new GdtfMacroDMX();
        this->fMacroDMX->ReadFromNode(macroDmxNode);
    }
    // MacroVisual    
    IXMLFileNode* MacroVisualNode;
    pNode->GetChildNode(XML_GDTF_MacroVisual, &MacroVisualNode);

    if (MacroVisualNode != nullptr)
    {
        this->fMacroVisual = new GdtfMacroVisual();
        this->fMacroVisual->ReadFromNode(MacroVisualNode);
    }
}

void GdtfMacro::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_MacroName);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

const TXString & SceneData::GdtfMacro::GetName() const
{
    return fName;
}

GdtfMacroDMX* SceneData::GdtfMacro::GetMacroDMX() const
{
    return fMacroDMX;
}

GdtfMacroVisual* SceneData::GdtfMacro::GetMacroVisual() const
{
    return fMacroVisual;
}

void SceneData::GdtfMacro::SetName(const TXString & name)
{
    fName = name;
}

void SceneData::GdtfMacro::SetMacroDMX(GdtfMacroDMX* val)
{
    fMacroDMX = val;
}

void SceneData::GdtfMacro::SetMacroVisual(GdtfMacroVisual* val)
{
    fMacroVisual = val;
}

EGdtfObjectType GdtfMacro::GetObjectType()
{
	return EGdtfObjectType::eGdtfMacro;
}

TXString GdtfMacro::GetNodeName()
{
	return XML_GDTF_MacroNodeName;
}

//------------------------------------------------------------------------------------
// GdtfMeasurementPoint
GdtfMeasurementPoint::GdtfMeasurementPoint()
{
	fWaveLength		= 0;
	fEngergy		= 0;
}

GdtfMeasurementPoint::~GdtfMeasurementPoint()
{
}

void GdtfMeasurementPoint::SetWavelength(double wavelength)
{
	fWaveLength = wavelength;
}

void GdtfMeasurementPoint::SetEnergy(double energy)
{
	fEngergy = energy;
}

void GdtfMeasurementPoint::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_MeasurementWaveLegth,	GdtfConverter::ConvertDouble(fWaveLength));
	pNode->SetNodeAttributeValue(XML_GDTF_MeasurementEnergy,	GdtfConverter::ConvertDouble(fEngergy));
}

void GdtfMeasurementPoint::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	TXString waveLength;	pNode->GetNodeAttributeValue(XML_GDTF_MeasurementWaveLegth,	waveLength);	GdtfConverter::ConvertDouble(waveLength, pNode, fWaveLength);
	TXString energy;		pNode->GetNodeAttributeValue(XML_GDTF_MeasurementEnergy,	energy);		GdtfConverter::ConvertDouble(energy, pNode, fEngergy);
}

void GdtfMeasurementPoint::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_MeasurementWaveLegth);
	needed.push_back(XML_GDTF_MeasurementEnergy);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfMeasurementPoint::GetObjectType()
{
	return EGdtfObjectType::eGdtfMeasurementPoint;
}

TXString GdtfMeasurementPoint::GetNodeName()
{
	return XML_GDTF_MeasurementNodeName;
}

double GdtfMeasurementPoint::GetWavelength()
{
	return fWaveLength;
}

double GdtfMeasurementPoint::GetEnergy()
{
	return fEngergy;
}

//------------------------------------------------------------------------------------
// GdtfFixture
TGdtfParsingErrorArray* GdtfFixture::__ERROR_CONTAINER_POINTER = nullptr;

GdtfFixture::GdtfFixture(IFileIdentifierPtr inZipFile)
{
	fReaded			= false;
	fHasLinkedGuid	= false;
	ASSERTN(kEveryone, __ERROR_CONTAINER_POINTER == nullptr);
	__ERROR_CONTAINER_POINTER = & this->fErrorContainer; 
	
	//-------------------------------------------------------------------------------------------------
	// Working Directory
	fWorkingFolder = (IID_FolderIdentifier);
	fWorkingFolder->Set(EFolderSpecifier::kSpotlightFolder, true /*UserFolder*/, "GDTF_Folder");
	
	//---------------------------------------------------------------------------------------------
	// Always start with a empty folder
	bool exists = false;
	fWorkingFolder->ExistsOnDisk(exists);
	if (exists) { fWorkingFolder->DeleteOnDisk(); }
	
	// Create new Folder
	fWorkingFolder->CreateOnDisk();
	
	//---------------------------------------------------------------------------------------------
	// check if this was good
	fWorkingFolder->ExistsOnDisk(exists);
	ASSERTN(kEveryone, exists == true);
	
	//-------------------------------------------------------------------------------------------------
	// Create a ZIP File
	IZIPFilePtr zipfile ( IID_ZIPFile );
	zipfile->OpenRead(inZipFile);

	ISceneDataZipBuffer xmlFileBuffer;
		
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	TXString fileName				= "";
	TXString inPath					= "";
	while (VCOM_SUCCEEDED( zipfile->GetNextFile(inPath, fileName)))
	{
		// This is the current file that we are reading
		ISceneDataZipBuffer buffer;
		zipfile->GetFile(fileName, &buffer);
		
		if (fileName == "description.xml")
        {
			// Read the data
			size_t	size = 0;							buffer.GetDataSize(size);
			void*	data = malloc(size * sizeof(char));	buffer.CopyDataInto(data, size);
			
			// Set the buffer object
            xmlFileBuffer.SetData(data, size);
			
			// House keeping
			std::free(data);
        }
		else
		{
			//-----------------------------------------------------------------------------
			// Prepare pointer to the new files            
            
            // Seperate filename und folder
            TXString fileNameWithoutFolder = TXString(fileName).Replace("/", TXString(kSeperator) );
            TXString subFolder 			   = SystemUtil::ExtractFolderFromPath(fileNameWithoutFolder);            
            
			// flatten the folder structure
            subFolder = subFolder.Replace(TXString(kSeperator), "");
            subFolder = kSeperator + subFolder;

            //-----------------------------------------------------------------------------
			IFolderIdentifierPtr targetFolder (IID_FolderIdentifier);
            targetFolder->Set(fWorkingFolder, subFolder);
            
			bool exists = false;
			targetFolder->ExistsOnDisk(exists);
			if( ! exists )	{ targetFolder->CreateOnDisk(); }
			
            
			IFileIdentifierPtr file (IID_FileIdentifier);
			file->Set(targetFolder, fileNameWithoutFolder);
			
			// dump buffer into file
			buffer.WriteToFile(file);
			
			// Add it into the file list
			fLocalFiles.push_back(file);

		}
		inPath = fileName;
	}
		
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	fReaded = xmlFileBuffer.IsSet();
	if ( ! fReaded)
	{
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureNoGdtfFileInXmlBuffer);
		SceneData::GdtfFixture::AddError(error); 
		fReaded = false;
	}
	else
	{
		IXMLFilePtr xmlFile (IID_XMLFile);

		size_t	size = 0;								xmlFileBuffer.GetDataSize(size);
		void*	data = malloc(size * sizeof(char));		xmlFileBuffer.CopyDataInto(data, size);
		
		// Set the data
		IXMLFileIOBufferImpl xmlBuffer;
		xmlBuffer.SetData(data, size);
		
		// Housekeeping
		std::free(data);
		
		if (VCOM_SUCCEEDED(xmlFile->ReadBuffer( &xmlBuffer, EXMLEncoding::eXMLEncoding_UTF8)))
		{
			IXMLFileNodePtr rootNode;
			if (VCOM_SUCCEEDED(xmlFile->GetRootNode( & rootNode)))
			{
				IXMLFileNodePtr fixtureNode;
				if (VCOM_SUCCEEDED(rootNode->GetChildNode(XML_GDTF_FixtureNodeName, & fixtureNode)))
				{
					//---------------------------------------------------------------------------------------------
					// Read Stuff
					this->ReadFromNode(fixtureNode);
					this->ResolveAllReferences();		
				}
			}
		}
	}

	__ERROR_CONTAINER_POINTER = nullptr;
}

/*static*/ void	GdtfFixture::AddError(const GdtfParsingError& error)
{
	
	if(__ERROR_CONTAINER_POINTER)
	{
		__ERROR_CONTAINER_POINTER->push_back(error);
	}
}

TGdtfParsingErrorArray& GdtfFixture::GetParsingErrorArray()
{
	return fErrorContainer;
}

void GdtfFixture::AutoGenerateNames(GdtfDmxModePtr dmxMode)
{
		for (GdtfDmxChannelPtr dmxChannel : dmxMode->GetChannelArray())
		{
			//------------------------------------------------------------------------------------------------
			//  Create Names for DMX Channel
			ASSERTN(kEveryone, dmxChannel->GetGeomRef() != nullptr);
			if (dmxChannel->GetGeomRef() == nullptr){ /* Error comes later*/ continue; }
			
			GdtfAttributePtr 	firstAttr = nullptr;
			
			for (GdtfDmxLogicalChannelPtr logicalChannel : dmxChannel->GetLogicalChannelArray())
			{
				//------------------------------------------------------------------------------------------------
				//  Create Names for Logical Channels
				ASSERTN(kEveryone, logicalChannel->GetAttribute() != nullptr);
				logicalChannel->SetName(logicalChannel->GetAttribute()->GetName());
				
				// Set first Attribute
				if (firstAttr == nullptr) { firstAttr = logicalChannel->GetAttribute(); }
				
				//------------------------------------------------------------------------------------------------
				//  Create Names for Channel Functions
				Sint64 channelFunctionNumber = 1;
				for (GdtfDmxChannelFunctionPtr function : logicalChannel->GetDmxChannelFunctions())
				{
					//
					if (function->GetName().IsEmpty())
					{
						ASSERTN(kEveryone, function->GetAttribute() != nullptr);
						if (function->GetAttribute() == nullptr)
						{
							IXMLFileNodePtr node;
							function->GetNode(node);
							GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureChannelFunctionMissingAttribute, node);
							SceneData::GdtfFixture::AddError(error);
							continue;
						}
						TXString functionName; 
						functionName += function->GetAttribute()->GetName();
						functionName += " ";
						functionName += TXString().itoa(channelFunctionNumber);
						
						function->SetName(functionName);
					}
					
					channelFunctionNumber++;
				}
			}
			
			//------------------------------------------------------------------------------------------------
			//  Set the DMX Name
			ASSERTN(kEveryone, firstAttr != nullptr);
			ASSERTN(kEveryone, dmxChannel->GetGeomRef() != nullptr);
			if(firstAttr) { dmxChannel->SetName(dmxChannel->GetGeomRef()->GetName() + "_" + firstAttr->GetName()); }
			
		}
}

GdtfAttributePtr GdtfFixture::getAttributeByRef(const TXString& ref)
{	
	if(ref == XML_GDTF_AttributeNoFeature_nullptr) { return nullptr; }
    
	for (GdtfAttributePtr attr : fAttributes)
	{
		if (attr->GetNodeReference() == ref) {return attr;};
	}

	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfAttributePtr."));
	return nullptr;
}

GdtfWheelPtr GdtfFixture::getWheelByRef(const TXString& ref)
{
	for (GdtfWheelPtr whl : fWheels)
	{
		if (whl->GetNodeReference() == ref){ return whl;};
	}
	
	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfWheelPtr."));
	return nullptr;
}

GdtfPhysicalEmitterPtr GdtfFixture::getEmiterByRef(const TXString& ref)
{
	for (GdtfPhysicalEmitterPtr emt : fEmitters)
	{
		if (emt->GetNodeReference() == ref){ return emt;};
	}
	
	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfPhysicalEmitterPtr."));
	return nullptr;
}

GdtfDmxChannelFunctionPtr GdtfFixture::getDmxFunctionByRef(const TXString& ref, GdtfDmxModePtr mode)
{
	for(GdtfDmxChannelPtr channel : mode->GetChannelArray())
	{
		for(GdtfDmxLogicalChannelPtr logicalChannel : channel->GetLogicalChannelArray())
		{
			for(GdtfDmxChannelFunctionPtr function : logicalChannel->GetDmxChannelFunctions())
			{
				if(function->GetNodeReference() == ref) { return function; }
			}
		}
	}
	
	return nullptr;
}

GdtfDmxChannelPtr GdtfFixture::getDmxChannelByRef(const TXString& ref, GdtfDmxModePtr mode)
{
	for(GdtfDmxChannelPtr channel : mode->GetChannelArray())
	{
		if(channel->GetNodeReference() == ref) { return channel; }
	}

	return nullptr;
}

void GdtfFixture::ResolveAllReferences()
{
	ResolveGeometryRefs();
	ResolveAttribRefs();
	ResolveDmxModeRefs();	
	ResolveDMXModeMasters();
    ResolveDMXPersonalityRefs();
}

void GdtfFixture::ResolveGeometryRefs()
{	
	// Geometry.Model
	for (GdtfGeometryPtr geometry : fGeometries)
	{
		ResolveGeometryRefs_Recursive(geometry);
	}
}

void GdtfFixture::ResolveGeometryRefs_Recursive(GdtfGeometryPtr geometry)
{
	// ----------------------------------------------------------------------------
	// Resolve Model Refs
	TXString		unresolvedModelRef	= geometry->GetUnresolvedModelRef();
	if( ! unresolvedModelRef.IsEmpty())
	{
		GdtfModelPtr	linkedModel			= nullptr;
		
		for (GdtfModelPtr modelRef: fModels)
		{
			if (modelRef->GetNodeReference() == unresolvedModelRef)	{ linkedModel = modelRef; break; }
		}
		
		ASSERTN(kEveryone, linkedModel != nullptr);
		if (linkedModel)	{ geometry->SetUnresolvedModelRef( linkedModel ); }
		else
		{
			IXMLFileNodePtr node;
			geometry->GetNode(node);
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eGeometryUnresolvedModel, node);
			SceneData::GdtfFixture::AddError(error);
		}
	}

	// ----------------------------------------------------------------------------
	// Resolve Geo Refs
	if(geometry->GetObjectType() == eGdtfGeometryReference)
	{
		GdtfGeometryReferencePtr geoRef = dynamic_cast<GdtfGeometryReferencePtr>(geometry);
		ASSERTN(kEveryone, geoRef != nullptr);
		if(geoRef)
		{
			GdtfGeometryPtr geo = this->ResolveGeometryRef(geoRef->GetUnresolvedLinkedGeometry(), fGeometries);
			ASSERTN(kEveryone, geo != nullptr);
			if (geo == nullptr)
			{
				IXMLFileNodePtr node;
				geoRef->GetNode(node);
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eGeometryReferenceUnresolvedLink, node);
				SceneData::GdtfFixture::AddError(error);
			}

			geoRef->SetLinkedGeometry(geo);
		}
		else
		{
			IXMLFileNodePtr node;
			geometry->GetNode(node);
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eGeometryReferenceUnresolvedLink, node);
			SceneData::GdtfFixture::AddError(error);
		}
	}
	
	// Now traverse child geometry
	for (GdtfGeometryPtr internalGeometry : geometry->GetInternalGeometries())
	{
		ResolveGeometryRefs_Recursive(internalGeometry);
	}
}

void GdtfFixture::ResolveAttribRefs()
{
	for (GdtfAttributePtr attr : fAttributes)
	{
		// ------------------------------------------------------------------------------------------
		// Attributes.ActivationGroup
		TXString attrRef = attr->GetUnresolvedActGroup();
		if( ! attrRef.IsEmpty())
		{
			GdtfActivationGroupPtr actGrpPtr = nullptr;
			for (GdtfActivationGroupPtr actGroup : fActivationGroups)
			{
				if (attrRef == actGroup->GetNodeReference() )	{ actGrpPtr = actGroup; break; }
			}
			
			ASSERTN(kEveryone, actGrpPtr != nullptr);
			if (actGrpPtr)	{ attr->SetActivationGroup (actGrpPtr); }
			else
			{
				IXMLFileNodePtr node;
				attr->GetNode(node);
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eAttributeUnresolvedActivationGroup, node);
				SceneData::GdtfFixture::AddError(error);
			}
		}
		
		// ------------------------------------------------------------------------------------------
		// Attributes.Feature
		GdtfFeaturePtr featPtr = nullptr;
		TXString unresolvedFeat = attr->GetUnresolvedFeature();
		if(unresolvedFeat.IsEmpty()) { continue; }

		for (GdtfFeatureGroupPtr featGrp : fFeatureGroups)
		{			
			for (GdtfFeaturePtr feat : featGrp->GetFeatureArray() )
			{				
				if (unresolvedFeat == feat->GetNodeReference() ) { featPtr = feat; break; }
			}
		}
		ASSERTN(kEveryone, featPtr != nullptr);
		if (featPtr != nullptr)	{ attr->SetFeature (featPtr); }
		else
		{
			IXMLFileNodePtr node;
			attr->GetNode(node);
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eAttributeUnresolvedFeature, node);
			SceneData::GdtfFixture::AddError(error);
		}
		
		// ------------------------------------------------------------------------------------------
		// Main Attribute
		TXString mainAttributeRef = attr->GetUnresolvedMainAttribute();
		if ( ! mainAttributeRef.IsEmpty())
		{
			GdtfAttributePtr mainAttribute = getAttributeByRef(mainAttributeRef);
			
			ASSERTN(kEveryone, mainAttribute != nullptr);
			if (mainAttribute != nullptr)	{ attr->SetMainAttribute(mainAttribute); }
			else
			{
				IXMLFileNodePtr node;
				attr->GetNode(node);		
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eAttributeUnresolvedMainAttribute, node);
				SceneData::GdtfFixture::AddError(error);
			}
		}
	}
}

void GdtfFixture::ResolveDmxModeRefs()
{	
	for (GdtfDmxModePtr dmxMode : fDmxModes)
	{
		//---------------------------------------------------------------------------------------
		// DmxMode.Geometry
		TXString 		unresolvedgeomRef	= dmxMode->GetUnresolvedGeomRef();
		GdtfGeometryPtr geomPtr				= nullptr;
		if( ! unresolvedgeomRef.IsEmpty())
		{
			for (GdtfGeometryPtr geo : fGeometries)
			{
				if (geo->GetNodeReference() == unresolvedgeomRef) 
                { 
                    geomPtr = geo; break; 
                }
			}
		}

		// Check if there is a
		ASSERTN(kEveryone, geomPtr != nullptr);
		if (geomPtr != nullptr) { dmxMode->SetGeomRef(geomPtr); }
		else
		{
			IXMLFileNodePtr node;
			dmxMode->GetNode(node);				
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxModeUnresolvedGeometry, node);
			SceneData::GdtfFixture::AddError(error);
		}
		
		// First Link all the stuff for DMX Channels
		ResolveDmxChannelRefs(dmxMode);
		
		// Afer Geometry is linked to the base geometry, we can generate the names
        AutoGenerateNames(dmxMode);
		
		// Then we have all the information for this
		ResolveDmxRelationRefs(dmxMode);
	}	
}

void GdtfFixture::ResolveDMXModeMasters()
{	
	for (GdtfDmxModePtr mode : fDmxModes)
	{
		for(GdtfDmxChannelPtr channel : mode->GetChannelArray())
		{
			for(GdtfDmxLogicalChannelPtr logicalChannel : channel->GetLogicalChannelArray())
			{
				for(GdtfDmxChannelFunctionPtr function : logicalChannel->GetDmxChannelFunctions())
				{
					// ----------------------------------------------------------------------------------------
					// DmxChanelFunction Mode Master Channel (Optional)
					TXString unresolvedModeMaster = function->getUnresolvedModeMasterRef();
					if(! unresolvedModeMaster.IsEmpty())
					{
						bool 						resolved 	= false;
						EGdtfChannelBitResolution 	resolution 	= EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;

						GdtfDmxChannelPtr channelPtr = getDmxChannelByRef(unresolvedModeMaster, mode);
						if(! resolved && channelPtr)
						{ 
							function->SetModeMaster_Channel(channelPtr); 
							resolved = true; 
							resolution = channelPtr->GetChannelBitResolution(); 
						}

						GdtfDmxChannelFunctionPtr functionPtr = getDmxFunctionByRef(unresolvedModeMaster, mode);
						if(! resolved && functionPtr) 
						{ 
							function->SetModeMaster_Function(functionPtr);
							resolved = true; 
							resolution = functionPtr->GetParentDMXChannel()->GetChannelBitResolution();
						}
						
						ASSERTN(kEveryone, resolved);
						if(resolved) { function->ResolveModeMasterDmx(resolution); }
						else
						{
							IXMLFileNodePtr node;
							channel->GetNode(node);
							GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDMXModeMastersUnresolved, node);
							SceneData::GdtfFixture::AddError(error);
						}
					}
				}
			}
		}
	}	
}


GdtfDmxModePtr GdtfFixture::ResolveDMXMode(const TXString& unresolvedDMXmode)
{
    for (GdtfDmxModePtr dmxMode : fDmxModes) 
    {
        if (dmxMode->GetModeName() == unresolvedDMXmode) 
        {
            return dmxMode;
        }    
    }
    
    return nullptr;
}

void GdtfFixture::ResolveDMXPersonalityRefs() 
{
    GdtfFTRDM* rdm =  fProtocollContainer.GetRDM();

    if (rdm)
    {
        for (GdtfSoftwareVersionID* softID : rdm->GetSoftwareVersIDs() ) 
        {
            for (GdtfDMXPersonality* dmxPerso : softID->GetDMXPersonalityArray() ) 
            {
                GdtfDmxModePtr dmxMode =  ResolveDMXMode(dmxPerso->GetUnresolvedDMXMode()); 
            
				ASSERTN(kEveryone, dmxMode != nullptr);
                if (dmxMode != nullptr) { dmxPerso->SetDMXMode(dmxMode);  }
				else
				{
					IXMLFileNodePtr node;
					dmxPerso->GetNode(node);
					GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_UnresolvedRdmPersonalityMode, node);
					SceneData::GdtfFixture::AddError(error);
				}
            }
        }
    }
}

void GdtfFixture::ResolveDmxRelationRefs(GdtfDmxModePtr dmxMode)
{
	for (GdtfDmxRelationPtr rel : dmxMode->GetDmxRelations())
	{	
		// DMXChannel (Master)
		GdtfDmxChannelPtr			master	= dmxMode->GetMasterByRef(rel->GetUnresolvedMasterRef() );
		GdtfDmxChannelFunctionPtr	slave	= dmxMode->GetSlaveByRef(rel->GetUnresolvedSlaveRef() );
		rel->SetMasterChannel(master);
        rel->SetSlaveChannel(slave);

	}	
}

void GdtfFixture::ResolveDmxChannelRefs(GdtfDmxModePtr dmxMode)
{	
	for (GdtfDmxChannelPtr chnl: dmxMode->GetChannelArray() )
	{
		// ----------------------------------------------------------------------------------------
		// DmxChannel.Geometry
		GdtfGeometryPtr geomPtr = nullptr;
		TXString unresolvedGeoRef	= chnl->GetUnresolvedGeomRef();
		ASSERTN(kEveryone, ! unresolvedGeoRef.IsEmpty() );
		if (!unresolvedGeoRef.IsEmpty())
		{
			for (GdtfGeometryPtr geom : fGeometries)
			{
				if (geom->GetNodeReference() == unresolvedGeoRef) { geomPtr = geom; break;}
				
				geomPtr = ResolveGeometryRef(unresolvedGeoRef, geom->GetInternalGeometries());
				if (geomPtr != nullptr) { break; }
			}
			
			ASSERTN(kEveryone, geomPtr != nullptr);
			if (geomPtr){ chnl->SetGeomRef (geomPtr); }
			else
			{
				IXMLFileNodePtr node;
				chnl->GetNode(node);
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureDMXChannelMissingGeometryLink, node);
				SceneData::GdtfFixture::AddError(error);
			}
		}
		else
		{
			IXMLFileNodePtr node;
			chnl->GetNode(node);
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureDMXChannelMissingGeometryLink, node);
			SceneData::GdtfFixture::AddError(error);
		}
		
		// ----------------------------------------------------------------------------------------
		// DmxChannel.LogicalChannelArray
		ResolveDmxLogicalChanRefs(chnl);
	} 	
}

GdtfGeometryPtr GdtfFixture::ResolveGeometryRef(const TXString& unresolvedGeoRef, const TGdtfGeometryArray& geometryArray)
{
	GdtfGeometryPtr matched = nullptr;
	
	for (GdtfGeometryPtr geom : geometryArray)
	{
		if (geom->GetNodeReference() == unresolvedGeoRef) { return geom; }
		
		matched = ResolveGeometryRef(unresolvedGeoRef, geom->GetInternalGeometries());
		if (matched) { return matched; }
	}
	
	return nullptr;
}

void GdtfFixture::ResolveDmxLogicalChanRefs(GdtfDmxChannelPtr dmxChnl)
{		
	for ( GdtfDmxLogicalChannelPtr logChnl : dmxChnl->GetLogicalChannelArray() )
	{
		// ----------------------------------------------------------------------------------------
		// DmxLogicalChannel.Attribute
		TXString unresolvedAttribRef = logChnl->GetUnresolvedAttribRef();
		
		if (!unresolvedAttribRef.IsEmpty())
		{
			GdtfAttributePtr attrPtr = nullptr;
			
			for (GdtfAttributePtr attr : fAttributes)
			{
				if (attr->GetNodeReference() == unresolvedAttribRef)	{ attrPtr = attr; break; }
			}

			
			
			ASSERTN(kEveryone, attrPtr != nullptr);
			if (attrPtr != nullptr)	{ logChnl->SetAttribute(attrPtr); }
			else
			{
				IXMLFileNodePtr node;
				logChnl->GetNode(node);
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureLogicalChannelMissingAttribute, node); SceneData::GdtfFixture::AddError(error);
			}
		}
		
		// ----------------------------------------------------------------------------------------
		// DmxChannelFuntionArray
		ResolveDmxChanelFunctionRefs(logChnl);
	}
}

void GdtfFixture::ResolveDmxChanelFunctionRefs(GdtfDmxLogicalChannelPtr dmxLogChnl)

{
	for (GdtfDmxChannelFunctionPtr chnlFunc : dmxLogChnl->GetDmxChannelFunctions())
	{
		// ----------------------------------------------------------------------------------------
		// DmxChanelFunction.Attribute
		TXString unresolvedAttrRef	= chnlFunc->getUnresolvedAttrRef();
		
		if ( ! unresolvedAttrRef.IsEmpty())
		{
			GdtfAttributePtr attrPtr = getAttributeByRef(unresolvedAttrRef);
			chnlFunc->SetAttribute(attrPtr);
		}
		
		// ----------------------------------------------------------------------------------------
		// DmxChanelFunction.WheelPtr (Optional)
		TXString unresolvedWheelRef = chnlFunc->getUnresolvedWheelRef();
		if( ! unresolvedWheelRef.IsEmpty())
		{
			GdtfWheelPtr whlPtr = getWheelByRef(unresolvedWheelRef);
			chnlFunc->SetWheel(whlPtr);
		}
		
		// ----------------------------------------------------------------------------------------
		// DmxChanelFunction.PhysicalEmitter (Optional)
		TXString unresolvedEmitterRef = chnlFunc->getUnresolvedEmitterRef();
		if ( ! unresolvedEmitterRef.IsEmpty())
		{
			GdtfPhysicalEmitterPtr emtPtr = getEmiterByRef(unresolvedEmitterRef);
			chnlFunc->SetEmitter(emtPtr);
		}
	}
}

GdtfFixture::GdtfFixture()
{
	fReaded					= false;
	fHasLinkedGuid			= false;
}

GdtfFixture::~GdtfFixture()
{
    for (GdtfActivationGroupPtr obj		: fActivationGroups){ delete obj; }
    for (GdtfFeatureGroupPtr obj		: fFeatureGroups)   { delete obj; }
    for (GdtfAttributePtr obj			: fAttributes)      { delete obj; }
	for (GdtfWheelPtr obj				: fWheels)			{ delete obj; }
	for (GdtfGeometry* obj				: fGeometries)		{ delete obj; }
	for (GdtfModel* obj					: fModels)			{ delete obj; }
	for (GdtfPhysicalEmitterPtr obj		: fEmitters)		{ delete obj; }
	for (GdtfDmxModePtr obj				: fDmxModes)		{ delete obj; }
	for (GdtfRevisionPtr obj			: fRevisions)		{ delete obj; }
    for (GdtfDMXProfilePtr obj          : fDmxProfiles)     { delete obj; }
    for (GdtfCRIGroupPtr obj            : fCRI_Groups)      { delete obj; }

    // Delete Local Files
	for (size_t i = 0; i < fLocalFiles.size(); i++)
	{
		IFileIdentifierPtr file = fLocalFiles[i];
		file->DeleteOnDisk();
	}
}

bool  GdtfFixture::IsReaded()
{
	return fReaded;
}

void  GdtfFixture::GetWorkingFolder(IFolderIdentifierPtr& folder)
{
	folder = fWorkingFolder;
}

void GdtfFixture::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureName,			fName);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureShortName,		fShortName);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureManufacturer,	fManufacturer);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureDescription,	fFixtureTypeDescription);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureTypeID,		GdtfConverter::ConvertUUID(fGuid));
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureThumbnail,		fTumbnailName);
	
	if(fHasLinkedGuid)
	{
		pNode->SetNodeAttributeValue(XML_GDTF_LinkedUuid,			GdtfConverter::ConvertUUID(fLinkedGuid));
	}
	else
	{
		pNode->SetNodeAttributeValue(XML_GDTF_LinkedUuid,			"");
	}
	
	// ------------------------------------------------------------------------------------
	// Activation Groups
	IXMLFileNodePtr attributeDefintion;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodeAttributeDef, & attributeDefintion)))
	{
		// Add ActivationsGroupDef
		IXMLFileNodePtr activationGroupContainer;
		if (VCOM_SUCCEEDED(attributeDefintion->CreateChildNode(XML_GDTF_FixtureChildNodeActivationGroupDef, & activationGroupContainer)))
		{
			for (auto  actGroup: fActivationGroups)
			{
				actGroup->WriteToNode(activationGroupContainer);
			}
		}
		
		// Add Feature GroupDef
		IXMLFileNodePtr featureGroupContainer;
		if (VCOM_SUCCEEDED(attributeDefintion->CreateChildNode(XML_GDTF_FixtureChildNodeFeatureGroupDef, & featureGroupContainer)))
		{
			for (auto  featureGroup: fFeatureGroups)
			{
				featureGroup->WriteToNode(featureGroupContainer);
			}
		}
		
		
		// Add Attributes
		// Add Feature GroupDef
		IXMLFileNodePtr attributesContainer;
		if (VCOM_SUCCEEDED(attributeDefintion->CreateChildNode(XML_GDTF_FixtureChildNodeAttributesDef, & attributesContainer)))
		{
			for (auto  featureGroup: fAttributes)
			{
				featureGroup->WriteToNode(attributesContainer);
			}
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print wheels
	IXMLFileNodePtr wheels;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodeWheels, & wheels)))
	{
		for (GdtfWheelPtr wheelObj : fWheels)
		{
			wheelObj->WriteToNode(wheels);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print physicalDescription
	IXMLFileNodePtr physicalDescription;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodePhysicalDesrip, & physicalDescription)))
	{
		// Print Emitters (physicalDescription child)
		IXMLFileNodePtr emittersGroupNode;
		if (VCOM_SUCCEEDED(physicalDescription->CreateChildNode(XML_GDTF_PhysicalDescriptionsEmitterCollect, & emittersGroupNode)))
		{
			for (GdtfPhysicalEmitterPtr emitter : fEmitters)
			{
				emitter->WriteToNode(emittersGroupNode);
			}
		}
		
		// Print DmxProfiles (physicalDescription child)
		IXMLFileNodePtr dmxProfGroupNode;
		if (VCOM_SUCCEEDED(physicalDescription->CreateChildNode(XML_GDTF_DMX_ProfileCollect, &dmxProfGroupNode)))
		{
			for (GdtfDMXProfilePtr dmxProfile : fDmxProfiles)
			{
				dmxProfile->WriteToNode(dmxProfGroupNode);
			}
		}
		
		// ------------------------------------------------------------------------------------
		// CRI_Collect (PhysicalDescription child)
		IXMLFileNodePtr CRI_CollectNode;
		if (VCOM_SUCCEEDED(physicalDescription->CreateChildNode(XML_GDTF_PhysicalDescriptionsEmitterCollect, &CRI_CollectNode)))
		{
			// CRI_Group (CRI_Collect child)
			IXMLFileNodePtr criGroupNode;
			if (VCOM_SUCCEEDED(CRI_CollectNode->CreateChildNode(XML_GDTF_PhysicalDescriptionsEmitterCollect, &criGroupNode)))
			{
				for (GdtfCRIGroupPtr criGroup : fCRI_Groups)
				{
					criGroup->WriteToNode(criGroupNode);
				}
			}
		}
		// ------------------------------------------------------------------------------------
	}
	
	// ------------------------------------------------------------------------------------
	// Print models
	IXMLFileNodePtr models;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodeModels, & models)))
	{
		for (GdtfModel* modelObj : fModels)
		{
			modelObj->WriteToNode(models);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print geometries
	IXMLFileNodePtr geometries;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodeGeomertries, & geometries)))
	{
		for (GdtfGeometry* geometryObj : fGeometries)
		{
			geometryObj->WriteToNode(geometries);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print dmxModes
	IXMLFileNodePtr dmxModes;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodeDMX, & dmxModes)))
	{
		for (GdtfDmxMode* dmxObj : fDmxModes)
		{
			dmxObj->WriteToNode(dmxModes);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print Revisions
	IXMLFileNodePtr revisions;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodeRevisions, & revisions)))
	{
		for (GdtfRevision* revisionObj : fRevisions)
		{
			revisionObj->WriteToNode(revisions);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print presets
	IXMLFileNodePtr presets;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodePresets, & presets)))
	{
		for (GdtfUserPreset* presetObj : fPresets)
		{
			presetObj->WriteToNode(presets);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print macros
	IXMLFileNodePtr macros;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodeMacros, & macros)))
	{
		for (GdtfMacro* macroObj : fMacros)
		{
			macroObj->WriteToNode(macros);
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Print Prorocols
    fProtocollContainer.WriteToNode(pNode);	
}

void GdtfFixture::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureName,						fName);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureShortName,					fShortName);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureManufacturer,				fManufacturer);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureDescription,				fFixtureTypeDescription);
	TXString uuid; pNode->GetNodeAttributeValue(XML_GDTF_FixtureTypeID,		uuid );	GdtfConverter::ConvertUUID(uuid, pNode, fGuid);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureThumbnail,					fTumbnailName);
	
	
	TXString linkedUuid;
	pNode->GetNodeAttributeValue(XML_GDTF_LinkedUuid,		linkedUuid );
	fHasLinkedGuid = GdtfConverter::ConvertUUID(linkedUuid, pNode, fLinkedGuid);
	
    // ------------------------------------------------------------------------------------
	// Read Prorocols
    IXMLFileNodePtr protoNode;
    if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_Protocols, &protoNode))) 
    {        
        fProtocollContainer.ReadFromNode(protoNode); 
    } 

    // ------------------------------------------------------------------------------------
    // Read AttributeDefinitions
    
    IXMLFileNodePtr attrDefs;
    if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_FixtureChildNodeAttributeDef, & attrDefs)))
    
    {
        // ------------------------------------------------------------------------------------
        // Read fActivationGroups
        GdtfConverter::TraverseNodes(attrDefs, XML_GDTF_FixtureChildNodeActivationGroupDef, XML_GDTF_ActivationGroupNode, [this] (IXMLFileNodePtr objNode) -> void
                                     {
                                         GdtfActivationGroupPtr pActicationGroup = new GdtfActivationGroup();
                                         
                                         pActicationGroup->ReadFromNode(objNode);
                                         
                                         fActivationGroups.push_back(pActicationGroup);
                                         
                                         return;
                                     });
        
        // ------------------------------------------------------------------------------------
        // Read fFeatureGroups
        GdtfConverter::TraverseNodes(attrDefs, XML_GDTF_FixtureChildNodeFeatureGroupDef, XML_GDTF_FeatureGroupNode, [this] (IXMLFileNodePtr objNode) -> void
                                     {
										 GdtfFeatureGroupPtr pFeatureGroup = new GdtfFeatureGroup();
										 
										 pFeatureGroup->ReadFromNode(objNode);
										 
										 fFeatureGroups.push_back(pFeatureGroup);
										 
                                         return;
                                     });
        
        // ------------------------------------------------------------------------------------
        // Read fAttributes
        GdtfConverter::TraverseNodes(attrDefs, XML_GDTF_FixtureChildNodeAttributesDef, XML_GDTF_AttributeNode, [this] (IXMLFileNodePtr objNode) -> void
                                     {
										 GdtfAttributePtr pAttr = new GdtfAttribute();
										 
										 pAttr->ReadFromNode(objNode);
										 
										 fAttributes.push_back(pAttr);
										 
                                         return;
                                     });
    }
    
    
	// ------------------------------------------------------------------------------------
	// Read Wheels
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_FixtureChildNodeWheels, XML_GDTF_WheelNodeName, [this] (IXMLFileNodePtr objNode) -> void
						{
							// Create the object
							GdtfWheelPtr wheel = new GdtfWheel(this);
							
							// Read from node
							wheel->ReadFromNode(objNode);
							
							// Add to list
							fWheels.push_back(wheel);
							return;
						});
	
	
	// ------------------------------------------------------------------------------------
	// Read Geometry
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_FixtureChildNodeModels, XML_GDTF_ModelNodeName, [this] (IXMLFileNodePtr objNode) -> void
						{
							// Create the object
							GdtfModel* model = new GdtfModel(this);
							
							// Read from node
							model->ReadFromNode(objNode);
							
							// Add to list
							fModels.push_back(model);
							return;
						});

	


	
	// ------------------------------------------------------------------------------------
	// Read Geometries
	GdtfConverter::TraverseMultiNodes(pNode, XML_GDTF_FixtureChildNodeGeomertries, [this] (IXMLFileNodePtr objNode,const TXString& childNodeName) -> void
						{
							GdtfGeometryPtr geometry = nullptr;
							if		 (childNodeName == XML_GDTF_GeometryAxisNodeName)		{ geometry = new GdtfGeometryAxis(nullptr);}
							else if (childNodeName == XML_GDTF_GeometryNodeName)			{ geometry = new GdtfGeometry(nullptr);}
							else if (childNodeName == XML_GDTF_FilterBeamNodeName)			{ geometry = new GdtfGeometryBeamFilter(nullptr);}
							else if (childNodeName == XML_GDTF_FilterColorNodeName)		{ geometry = new GdtfGeometryColorFilter(nullptr);}
							else if (childNodeName == XML_GDTF_FilterGoboNodeName)			{ geometry = new GdtfGeometryGoboFilter(nullptr);}
							else if (childNodeName == XML_GDTF_FilterShaperNodeName)		{ geometry = new GdtfGeometryShaperFilter(nullptr);}
							else if (childNodeName == XML_GDTF_LampNodeName)				{ geometry = new GdtfGeometryLamp(nullptr);}
							else if (childNodeName == XML_GDTF_GeometryReferenceNodeName)	{ geometry = new GdtfGeometryReference(nullptr);}
							else															{ DSTOP((kEveryone,"There is a node that was not aspected!")); }
							
							ASSERTN(kEveryone, geometry != nullptr);
							if (geometry)
							{
								geometry->ReadFromNode(objNode);
								fGeometries.push_back(geometry);
							}
							else
							{
								GdtfParsingError error (GdtfDefines::EGdtfParsingError::eNodeWrongName, objNode);
								SceneData::GdtfFixture::AddError(error);
							}
							return;
						});
	
	
	
	// ------------------------------------------------------------------------------------
	// Read dmxModes
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_FixtureChildNodeDMX, XML_GDTF_DMXModeNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfDmxModePtr dmxMode = new GdtfDmxMode();
									 
									 // Read from node
									 dmxMode->ReadFromNode(objNode);
									 
									 // Add to list
									 fDmxModes.push_back(dmxMode);
									 return;
								 });
	
	// ------------------------------------------------------------------------------------
	// Read Revision
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_FixtureChildNodeRevisions, XML_GDTF_RevisionNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfRevisionPtr rev = new GdtfRevision();
									 
									 // Read from node
									 rev->ReadFromNode(objNode);
									 
									 // Add to list
									 fRevisions.push_back(rev);
									 return;
								 });
	
	// ------------------------------------------------------------------------------------
	// Read presets

	
	// ------------------------------------------------------------------------------------
	// Read macros

	
	// ------------------------------------------------------------------------------------
	// Read PhysicalDescription
	IXMLFileNodePtr physicalDescription;
	if (VCOM_SUCCEEDED( pNode->GetChildNode(XML_GDTF_FixtureChildNodePhysicalDesrip, & physicalDescription)))
	{
        // Read Emitters (PhysicalDescription Child)
		GdtfConverter::TraverseNodes(physicalDescription, XML_GDTF_PhysicalDescriptionsEmitterCollect, XML_GDTF_EmitterNodeName, [this] (IXMLFileNodePtr objNode) -> void
									 {
										 // Create the object
										 GdtfPhysicalEmitterPtr emitter = new GdtfPhysicalEmitter();
										 
										 // Read from node
										 emitter->ReadFromNode(objNode);
										 
										 // Add to list
										 fEmitters.push_back(emitter);
										 return;
									 });
        // Read DmxProfiles (PhysicalDescription Child) 
        GdtfConverter::TraverseNodes(pNode, XML_GDTF_DMX_ProfileCollect, XML_GDTF_DMX_Profile, [this](IXMLFileNodePtr objNode) -> void
        {
            // Create the object
            GdtfDMXProfilePtr dmxProfile = new GdtfDMXProfile();

            // Read from node
            dmxProfile->ReadFromNode(objNode);

            // Add to list
            fDmxProfiles.push_back(dmxProfile);
            return;
        });
		
		// ------------------------------------------------------------------------------------
		GdtfConverter::TraverseNodes(physicalDescription, XML_GDTF_ColorRenderingIndexCollect, XML_GDTF_ColorRenderingIndexGroup, [this](IXMLFileNodePtr objNode) -> void
										{
											GdtfCRIGroupPtr criGroup = new GdtfCRIGroup();
											
											// Read from node
											criGroup->ReadFromNode(objNode);
											
											fCRI_Groups.push_back(criGroup);
											return;
										});
	}

}

void GdtfFixture::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_FixtureName);
	needed.push_back(XML_GDTF_FixtureShortName);
	needed.push_back(XML_GDTF_FixtureManufacturer);
	needed.push_back(XML_GDTF_FixtureDescription);
	needed.push_back(XML_GDTF_FixtureTypeID);
	optional.push_back(XML_GDTF_FixtureThumbnail);
	optional.push_back(XML_GDTF_LinkedUuid);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfFixture::GetObjectType()
{
	return EGdtfObjectType::eGdtfFixture;
}
TXString GdtfFixture::GetNodeName()
{
	return XML_GDTF_FixtureNodeName;
}

bool GdtfFixture::ExportToFile(IZIPFilePtr& zipfile)
{
	//------------------------------------------------------------------------------------
	// Create XML File
	IXMLFilePtr xmlFile (IID_XMLFile);
	xmlFile->CreateNew(XML_GDTF_ROOTNODENAME);
	
	
	//------------------------------------------------------------------------------------
	// Create root node
	IXMLFileNodePtr rootNode;
	if (VCOM_SUCCEEDED(xmlFile->GetRootNode( & rootNode)))
	{
		// Set Version Tag
		rootNode->SetNodeAttributeValue(XML_GDTF_ROOTNODEATTRVERSION, XML_GDTF_CurrentVersion);
		
		// Write the fixture
		this->WriteToNode(rootNode);
	}
	

	//------------------------------------------------------------------------------------
	// Write to disk
	SceneData::IXMLFileIOBufferImpl buffer;
	xmlFile->WriteBuffer( &buffer, eXMLEncoding_UTF8);
	
	
	// Prepare Temp Storage for ZIP buffer
	size_t	size = 0;
	void*	data = nullptr;
	
	// Get the data from the XML
	buffer.GetDataSize(size);
	buffer.GetData(data);
	
	
	// Copy into the Buffer for the ZIP
	ISceneDataZipBuffer zipXmlBuffer;
	zipXmlBuffer.SetData(data, size);
	
	
	//------------------------------------------------------------------------------------
	// Add tp ZIP
	SceneDataZip::AddFileToZip(zipfile, zipXmlBuffer, TXString(XML_GDTF_GDTFFILENAME) );

	
	return true;
}


GdtfRevisionPtr GdtfFixture::AddRevision(const TXString& text, const STime& date)
{
	GdtfRevision* revision = new GdtfRevision();
	revision->SetText(text);
	revision->SetDate(date);
	
	fRevisions.push_back(revision);
	
	return revision;
}

GdtfAttributePtr GdtfFixture::AddAttribute(const TXString& name, const TXString& prettyName)
{
	GdtfAttributePtr attr = new GdtfAttribute(name, prettyName);

	fAttributes.push_back(attr);
	
	return attr;
}

GdtfWheelPtr GdtfFixture::AddWheel(TXString name)
{
	// Create new Wheel
	GdtfWheel* wheel = new GdtfWheel(this, name);

	// Add to array
	fWheels.push_back(wheel);
	
	return wheel;

}

GdtfModel* GdtfFixture::AddModel(const TXString& name)
{
	GdtfModel* model = new  GdtfModel(name, this);
	fModels.push_back(model);
	
	return model;
}

GdtfGeometryPtr GdtfFixture::AddGeometryWithAxis(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma)
{
	GdtfGeometryAxis* axis = new GdtfGeometryAxis(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(axis);
	
	return axis;
}

GdtfGeometryPtr GdtfFixture::AddGeometryWithLamp(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometryLamp* lamp = new GdtfGeometryLamp(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(lamp);
	
	return lamp;
}

GdtfGeometryPtr GdtfFixture::AddGeometry(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometry(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfFixture::AddGeometryReference(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryReference(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfFixture::AddGeometryShaper(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryShaperFilter(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfFixture::AddGeometryColor(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryColorFilter(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfFixture::AddGeometryGobo(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryGoboFilter(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfFixture::AddGeometryBeam(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryBeamFilter(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfDmxMode* GdtfFixture::AddDmxMode(const TXString& name)
{
	GdtfDmxMode* mode = new  GdtfDmxMode(name);
	
	fDmxModes.push_back(mode);
	
	return mode;
}

GdtfPhysicalEmitterPtr GdtfFixture::AddEmitter(const TXString& name)
{
	GdtfPhysicalEmitterPtr emitter = new  GdtfPhysicalEmitter(name);
	
	fEmitters.push_back(emitter);
	
	return emitter;
}

GdtfDMXProfilePtr SceneData::GdtfFixture::AddDmxProfile()
{
    GdtfDMXProfilePtr dmxProf = new GdtfDMXProfile();
    
    fDmxProfiles.push_back(dmxProf);
    
    return dmxProf;
}

GdtfMacroPtr GdtfFixture::AddMacro(const TXString& name)
{
	GdtfMacroPtr macro = new  GdtfMacro(name);
	
	fMacros.push_back(macro);
	
	return macro;
}

GdtfUserPresetPtr GdtfFixture::AddUserPreset()
{
	GdtfUserPresetPtr preset = new  GdtfUserPreset();
	
	fPresets.push_back(preset);
	
	return preset;
}

GdtfFeatureGroupPtr GdtfFixture::AddFeatureGroup(const TXString& name, const TXString& prettyName)
{
	GdtfFeatureGroupPtr featureGroup = new  GdtfFeatureGroup(name, prettyName);
	
	fFeatureGroups.push_back(featureGroup);
	
	return featureGroup;
}

GdtfActivationGroupPtr GdtfFixture::AddActivationGroup(const TXString& name)
{
	GdtfActivationGroupPtr actGroup = new  GdtfActivationGroup(name);
	
	fActivationGroups.push_back(actGroup);
	
	return actGroup;
}

GdtfCRIGroupPtr SceneData::GdtfFixture::AddCRIGroup(double colorTsemp)
{   
    GdtfCRIGroupPtr criGroup = new GdtfCRIGroup(colorTsemp);
    fCRI_Groups.push_back(criGroup);

    return criGroup;
}

const TGdtfWheelArray& GdtfFixture::GetWheelArray()
{
	return fWheels;
}

const TGdtfActivationGroupArray& GdtfFixture::GetActivationGroupArray()
{
    return fActivationGroups;
}

const TGdtfFeatureGroupArray& GdtfFixture::GetFeatureGroupArray()
{
    return fFeatureGroups;
}

const TGdtfAttributeArray& GdtfFixture::GetAttributeArray()
{
    return fAttributes;
}

const TGdtfGeometryArray& GdtfFixture::GetGeometryArray()
{
	return fGeometries;
}

const TGdtfDmxModeArray& GdtfFixture::GetDmxModeArray()
{
	return fDmxModes;
}

const TGdtfModelArray& GdtfFixture::GetModelArray()
{
    return fModels;
}

const TGdtfRevisionArray& GdtfFixture::GetRevisionArray()
{
    return fRevisions;
}

const TGdtfUserPresetArray& GdtfFixture::GetPresetArray()
{
    return fPresets;
}

const TGdtfMacroArray& GdtfFixture::GetMacroArray()
{
    return fMacros;
}

const TGdtfPhysicalEmitterArray& GdtfFixture::GetPhysicalEmitterArray()
{
    return fEmitters;
}

const TGdtfDMXProfileArray& SceneData::GdtfFixture::GetDmxProfileArray()
{
    return fDmxProfiles;
}

const TGdtf_CRIGroupArray & SceneData::GdtfFixture::GetCRIGroupArray()
{
    return fCRI_Groups;
}

GdtfProtocols& GdtfFixture::GetProtocollContainer()
{
	return fProtocollContainer;
}

const TXString& GdtfFixture::GetName() const
{
	return fName;
}

const TXString& GdtfFixture::GetShortName() const
{
    return fShortName;
}

const TXString& GdtfFixture::GetManufacturer() const
{
    return fManufacturer;
}

const TXString& GdtfFixture::GetFixtureTypeDescription() const
{
    return fFixtureTypeDescription;
}

GdtfFixtureGUID GdtfFixture::GetGuid() const
{
    return fGuid;
}

GdtfFixtureGUID GdtfFixture::GetLinkedGuid() const
{
	return fLinkedGuid;
}

bool GdtfFixture::HasLinkedGuid() const
{
	return fHasLinkedGuid;
}

const TXString& GdtfFixture::GetThumbnailName() const
{
    return fTumbnailName;
}

TXString GdtfFixture::GetFullThumbNailPath (const TXString& fileExtension) 
{
	// Set to store
	TXString fileName = fTumbnailName + fileExtension;

    // Check if file exists:
    IFileIdentifierPtr file (IID_FileIdentifier);
    file->Set(fWorkingFolder, fileName);
    
    bool exists = false;  
	VCOM_SUCCEEDED(file->ExistsOnDisk(exists));
    if ( ! exists)	{ return ""; }

	TXString fullPath;
	file->GetFileFullPath(fullPath);

	return fullPath;
}

const GdtfPNGFile& GdtfFixture::GetPNGThumnailFullPath()
{
	// Set to store
    fTumbnailFullPath_PNG = GetFullThumbNailPath(".png");

	return fTumbnailFullPath_PNG;
}

const TXString & SceneData::GdtfFixture::GetSVGThumnailFullPath()
{
	// Set to store
    fTumbnailFullPath_SVG = GetFullThumbNailPath(".svg");

	return fTumbnailFullPath_SVG;
}

void GdtfFixture::SetName(const TXString& name)
{
	fName = name;
}

void GdtfFixture::SetShortName(const TXString& shortName)
{
	fShortName = shortName;
}

void GdtfFixture::SetManufacturer(const TXString& manu)
{
	fManufacturer = manu;
}

void GdtfFixture::SetFixtureTypeDescription(const TXString& desc)
{
	fFixtureTypeDescription = desc;
}

void GdtfFixture::SetGuid(const VWFC::Tools::VWUUID& uuid)
{
	fGuid = uuid;
}

void GdtfFixture::SetLinkedGuid(const VWFC::Tools::VWUUID& uuid)
{
	fHasLinkedGuid = true;
	fLinkedGuid = uuid;
}

void GdtfFixture::SetThumbnailName(const TXString& fileName)
{
	fTumbnailName = fileName;
}

SceneData::GdtfDMXProfile::GdtfDMXProfile()
{
}

SceneData::GdtfDMXProfile::~GdtfDMXProfile()
{
}

EGdtfObjectType SceneData::GdtfDMXProfile::GetObjectType()
{
    return EGdtfObjectType::eGdtfDMXProfile;
}

TXString SceneData::GdtfDMXProfile::GetNodeName()
{
    return XML_GDTF_DMX_Profile;
}

void SceneData::GdtfDMXProfile::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	//------------------------------------------------------------------------------------
}

void SceneData::GdtfDMXProfile::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	//------------------------------------------------------------------------------------
}

SceneData::GdtfCRIGroup::GdtfCRIGroup()
{
    fColorTemperature = 6000;
}

SceneData::GdtfCRIGroup::GdtfCRIGroup(double colorTemp)
{
    fColorTemperature = colorTemp;
}

SceneData::GdtfCRIGroup::~GdtfCRIGroup()
{
	for(GdtfCRIPtr ptr : fCRI_Array) { delete ptr; }
}

EGdtfObjectType SceneData::GdtfCRIGroup::GetObjectType()
{
    return EGdtfObjectType::eGdtfCRIGroup;
}

double SceneData::GdtfCRIGroup::GetColorTemperature() const
{
    return fColorTemperature;
}

TGdtf_CRIArray SceneData::GdtfCRIGroup::GetCRI_Array() const
{
    return fCRI_Array;
}

void SceneData::GdtfCRIGroup::SetColorTemperature(double val)
{
    fColorTemperature = val;
}

GdtfCRIPtr SceneData::GdtfCRIGroup::Add_CRI(EGdtfColorSample ces, Sint32 colorTemp)
{
    GdtfCRIPtr cri = new GdtfCRI(ces, colorTemp);
    
    fCRI_Array.push_back(cri);

    return cri;
}

TXString SceneData::GdtfCRIGroup::GetNodeName()
{
    return XML_GDTF_ColorRenderingIndexGroup;
}

void SceneData::GdtfCRIGroup::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);

    //------------------------------------------------------------------------------------
    // Print the attributes
    pNode->SetNodeAttributeValue(XML_GDTF_ColorRenderingIndexGrou_AttrColorTemp, GdtfConverter::ConvertDouble(fColorTemperature) );

    //------------------------------------------------------------------------------------
    // Print the childs
    for (GdtfCRI* cri : fCRI_Array)
    {
        cri->WriteToNode(pNode);
    }
}

void SceneData::GdtfCRIGroup::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnReadFromNode(pNode);

    //------------------------------------------------------------------------------------
    // Get the attributes	
    TXString colorTempStr; pNode->GetNodeAttributeValue(XML_GDTF_ColorRenderingIndexGrou_AttrColorTemp, colorTempStr);
    GdtfConverter::ConvertDouble(colorTempStr, pNode, fColorTemperature);

    // Read the childs
    GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_ColorRenderingIndex, [this](IXMLFileNodePtr objNode) -> void
    {
        GdtfCRI* cri = new GdtfCRI();

        cri->ReadFromNode(objNode);

        fCRI_Array.push_back(cri);

        return;
    });
}

void SceneData::GdtfCRIGroup::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	optional.push_back(XML_GDTF_ColorRenderingIndexGrou_AttrColorTemp);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfCRI::GdtfCRI()
{
    fCES = EGdtfColorSample::CES_01;  // Default CES01
    fColorTemperature = 100;          // The color rendering index for this sample.Size: 1 byte; Default value : 100
}

SceneData::GdtfCRI::GdtfCRI(EGdtfColorSample ces, Sint32 colorTemp)
{
    fCES = ces;
    fColorTemperature = colorTemp;
}

SceneData::GdtfCRI::~GdtfCRI()
{
}

EGdtfObjectType SceneData::GdtfCRI::GetObjectType()
{
    return EGdtfObjectType::eGdtfCRI;
}

EGdtfColorSample SceneData::GdtfCRI::GetColorSample() const
{
    return fCES;
}

Sint32 SceneData::GdtfCRI::GetColorTemperature() const
{
    return fColorTemperature;
}

void SceneData::GdtfCRI::SetColorSample(EGdtfColorSample val)
{
    fCES = val;
}

void SceneData::GdtfCRI::SetColorTemperature(Sint32 val)
{
    fColorTemperature = val;
}

TXString SceneData::GdtfCRI::GetNodeName()
{
    return XML_GDTF_ColorRenderingIndex;
}

void SceneData::GdtfCRI::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);

    //------------------------------------------------------------------------------------
    // Print the attributes
    pNode->SetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_AttrCES, GdtfConverter::ConvertEGdtfColorSampleEnum(fCES) );
    
    pNode->SetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_AttrColorTemp, GdtfConverter::ConvertInteger(fColorTemperature) );
}

void SceneData::GdtfCRI::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnReadFromNode(pNode);

    //------------------------------------------------------------------------------------
    // Get the attributes	
    TXString cesStr;  pNode->GetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_AttrCES, cesStr);
    GdtfConverter::ConvertEGdtfColorSampleEnum(cesStr, pNode, fCES);
    //
    TXString colorTempStr; pNode->GetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_AttrColorTemp, colorTempStr);
    GdtfConverter::ConvertInteger(colorTempStr, pNode, fColorTemperature);
}

void SceneData::GdtfCRI::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	optional.push_back(XML_GDTF_ColorRenderingIndex_AttrCES);
	optional.push_back(XML_GDTF_ColorRenderingIndex_AttrColorTemp);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}


TXString SceneData::GdtfFTRDM::GetNodeName()
{
	return XML_GDTF_FTRDM;
}

void SceneData::GdtfFTRDM::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_FTRDM_AttrManufacturerID, GdtfConverter::ConvertInteger(fManufacturerID) );
	pNode->SetNodeAttributeValue(XML_GDTF_FTRDM_AttrDeviceModelID,  GdtfConverter::ConvertInteger(fDeviceModelID)  );	 
	//------------------------------------------------------------------------------------
    // Print the Childs
	for (GdtfSoftwareVersionIDPtr softID : fSoftwareVersionIDArray)
	{
		softID->WriteToNode(pNode);
	}
}

void SceneData::GdtfFTRDM::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString manufactStr; pNode->GetNodeAttributeValue(XML_GDTF_FTRDM_AttrManufacturerID, manufactStr);
	GdtfConverter::ConvertInteger(manufactStr, pNode, fManufacturerID);
	
	TXString deviceModelStr;  pNode->GetNodeAttributeValue(XML_GDTF_FTRDM_AttrDeviceModelID, deviceModelStr);
	GdtfConverter::ConvertInteger(deviceModelStr, pNode, fDeviceModelID);
    
    //------------------------------------------------------------------------------------
	// Read the childs
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_SoftwareVersionID_NodeNam, [this](IXMLFileNodePtr objNode) -> void
								 {
									 GdtfSoftwareVersionIDPtr  softID = new GdtfSoftwareVersionID();
									 
									 softID->ReadFromNode(objNode);
									 
									 fSoftwareVersionIDArray.push_back(softID);
									 return;
								 });	
}

void SceneData::GdtfFTRDM::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_FTRDM_AttrManufacturerID);
	needed.push_back(XML_GDTF_FTRDM_AttrDeviceModelID);	

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfFTRDM::GdtfFTRDM()
{
	fManufacturerID = 0;
	fDeviceModelID  = 0;
}

SceneData::GdtfFTRDM::GdtfFTRDM(Sint32 manufacturerID, Sint32 deviceModelID) : GdtfFTRDM()
{
	fManufacturerID = manufacturerID;
	fDeviceModelID  = deviceModelID;
}

SceneData::GdtfFTRDM::~GdtfFTRDM()
{	    
     for (GdtfSoftwareVersionID* obj : fSoftwareVersionIDArray){ delete obj; }
}

EGdtfObjectType SceneData::GdtfFTRDM::GetObjectType()
{
	return EGdtfObjectType::eGdtfFTRDM;
}

Sint32 SceneData::GdtfFTRDM::GetManufacturerID() const
{
	return fManufacturerID;
}

Sint32 SceneData::GdtfFTRDM::GetDeviceModelID() const
{
	return fDeviceModelID;
}

const TGdtfSoftwareVersionIDArray& SceneData::GdtfFTRDM::GetSoftwareVersIDs() const
{
	return fSoftwareVersionIDArray;
}

void SceneData::GdtfFTRDM::SetManufacturerID(Sint32 val)
{
	fManufacturerID = val;
}

void SceneData::GdtfFTRDM::SetDeviceModelID(Sint32 val)
{
	fDeviceModelID = val;
}


GdtfSoftwareVersionIDPtr SceneData::GdtfFTRDM::AddSoftwareVersID(size_t value)
{
    GdtfSoftwareVersionIDPtr softID = new GdtfSoftwareVersionID(value);
	
    fSoftwareVersionIDArray.push_back(softID);

    return softID;
}

SceneData::GdtfDMXPersonality::GdtfDMXPersonality()
{
    fValue = 0;
    fDMXMode = nullptr;
    fDMXMode_Unresolved = "";
}

SceneData::GdtfDMXPersonality::GdtfDMXPersonality(size_t value, GdtfDmxModePtr dmxMode)
{
    fValue   = value;
    fDMXMode = dmxMode;
    fDMXMode_Unresolved = "";
}

SceneData::GdtfDMXPersonality::~GdtfDMXPersonality()
{     
}

EGdtfObjectType SceneData::GdtfDMXPersonality::GetObjectType()
{
    return EGdtfObjectType::eGdtfDMXPersonality;
}

size_t SceneData::GdtfDMXPersonality::GetValue() const
{
    return fValue;
}

const TXString & SceneData::GdtfDMXPersonality::GetUnresolvedDMXMode() const
{
    return fDMXMode_Unresolved;
}

GdtfDmxModePtr SceneData::GdtfDMXPersonality::GetDMXMode() const
{
    return fDMXMode;
}

void SceneData::GdtfDMXPersonality::SetValue(size_t val)
{
    fValue = val;
}

void SceneData::GdtfDMXPersonality::SetDMXMode(GdtfDmxModePtr mode)
{
    fDMXMode = mode;
}

TXString SceneData::GdtfDMXPersonality::GetNodeName()
{
    return XML_GDTF_DMXPersonalityNodeNam;
}

void GdtfDMXPersonality::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);

    //------------------------------------------------------------------------------------
    // Print the attributes
    pNode->SetNodeAttributeValue(XML_GDTF_DMXPersonalityValue, GdtfConverter::ConvertInteger(fValue));
    pNode->SetNodeAttributeValue(XML_GDTF_DMXPersonalityDMXMode, fDMXMode->GetModeName() );
}

void GdtfDMXPersonality::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnReadFromNode(pNode);

    //------------------------------------------------------------------------------------
    // Get the attributes	
    TXString valueStr;
    pNode->GetNodeAttributeValue(XML_GDTF_DMXPersonalityValue, valueStr);
    GdtfConverter::ConvertInteger(valueStr, pNode, fValue);

    pNode->GetNodeAttributeValue(XML_GDTF_DMXPersonalityDMXMode, fDMXMode_Unresolved);
}

SceneData::GdtfProtocols::GdtfProtocols()
{
	fRDM              = nullptr;
	fArtNet           = nullptr;
	fsACN             = nullptr;
	fKiNET            = nullptr;
	fPosiStageNet     = nullptr;
	fOpenSoundControl = nullptr;
	fCITP             = nullptr;
}

SceneData::GdtfProtocols::~GdtfProtocols()
{
	if (fRDM)              {delete fRDM;}
	if (fArtNet)           {delete fArtNet;}
	if (fsACN)             {delete fsACN;}
	if (fKiNET)            {delete fKiNET;}
	if (fPosiStageNet)     {delete fPosiStageNet;}
	if (fOpenSoundControl) {delete fOpenSoundControl;}
	if (fCITP)             {delete fCITP;}
}

EGdtfObjectType SceneData::GdtfProtocols::GetObjectType()
{
	return EGdtfObjectType::eProtocols;
}

GdtfFTRDM * SceneData::GdtfProtocols::GetRDM()
{
	return fRDM;
}

GdtfArtNet * SceneData::GdtfProtocols::GetArtNet()
{
	return fArtNet;
}

GdtfsAcn * SceneData::GdtfProtocols::Get_sACN()
{
	return fsACN;
}

GdtfKiNET * SceneData::GdtfProtocols::GetKiNET()
{
	return fKiNET;
}

GdtfPosiStageNet * SceneData::GdtfProtocols::GetPosiStageNet()
{
	return fPosiStageNet;
}

GdtfOpenSoundControl * SceneData::GdtfProtocols::GetOpenSoundControl()
{
	return fOpenSoundControl;
}

GdtfCITP * SceneData::GdtfProtocols::GetCITP()
{
	return fCITP;
}

GdtfFTRDM * SceneData::GdtfProtocols::CreateRDM()
{
	fRDM = new GdtfFTRDM();
	return fRDM;
}

void SceneData::GdtfProtocols::SetArtNet(GdtfArtNet * val)
{
	fArtNet = val;
}

void SceneData::GdtfProtocols::Set_sACN(GdtfsAcn * val)
{
	fsACN = val;
}

void SceneData::GdtfProtocols::SetKiNET(GdtfKiNET * val)
{
	fKiNET = val;
}

void SceneData::GdtfProtocols::SetPosiStageNet(GdtfPosiStageNet * val)
{
	fPosiStageNet = val;
}

void SceneData::GdtfProtocols::SetOpenSoundControl(GdtfOpenSoundControl * val)
{
	fOpenSoundControl = val;
}

void SceneData::GdtfProtocols::SetCITP(GdtfCITP * val)
{
	fCITP = val;
}

TXString SceneData::GdtfProtocols::GetNodeName()
{
	return XML_GDTF_Protocols;
}

void SceneData::GdtfProtocols::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	//------------------------------------------------------------------------------------
	// Print the childs
	if (fRDM)              { fRDM->WriteToNode(pNode); }
	if (fArtNet)           { fArtNet->WriteToNode(pNode); }
	if (fsACN)             { fsACN->WriteToNode(pNode); }
	if (fKiNET)            { fKiNET->WriteToNode(pNode); }
	if (fPosiStageNet)     { fPosiStageNet->WriteToNode(pNode); }
	if (fOpenSoundControl) { fOpenSoundControl->WriteToNode(pNode); }
	if (fCITP)             { fCITP->WriteToNode(pNode); }
}

void SceneData::GdtfProtocols::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	 GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Read the childs	
	IXMLFileNodePtr ftrdmNode;
	if (VCOM_SUCCEEDED( pNode->GetChildNode(XML_GDTF_FTRDM, &ftrdmNode)) )
	{
		fRDM = new GdtfFTRDM();
		fRDM->ReadFromNode(ftrdmNode);
	}
	
	IXMLFileNodePtr artNetNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_ArtNet, &artNetNode)))
	{
		fArtNet = new GdtfArtNet();
		fArtNet->ReadFromNode(artNetNode);
	}
	
	IXMLFileNodePtr sAcnNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_sACN, &sAcnNode)))
	{
		fsACN = new GdtfsAcn();
		fsACN->ReadFromNode(sAcnNode);
	}
	
	IXMLFileNodePtr kinetNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_KiNET, &kinetNode)))
	{
		fKiNET = new GdtfKiNET();
		fKiNET->ReadFromNode(kinetNode);
	}
	
	IXMLFileNodePtr posiStageNetNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_PosiStageNet, &posiStageNetNode)))
	{
		fPosiStageNet = new GdtfPosiStageNet();
		fPosiStageNet->ReadFromNode(posiStageNetNode);
	}
	
	IXMLFileNodePtr openSoundControlNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_OpenSoundControl, &openSoundControlNode)))
	{
		fOpenSoundControl = new GdtfOpenSoundControl();
		fOpenSoundControl->ReadFromNode(openSoundControlNode);
	}
	
	IXMLFileNodePtr ctipNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_CITP, &ctipNode)))
	{
		fCITP = new GdtfCITP();
		fCITP->ReadFromNode(ctipNode);
	}
}

void SceneData::GdtfProtocols::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfArtNet::GdtfArtNet()
{
}

SceneData::GdtfArtNet::~GdtfArtNet()
{
}

EGdtfObjectType SceneData::GdtfArtNet::GetObjectType()
{
	return EGdtfObjectType::eGdtfArtNet;
}

TXString SceneData::GdtfArtNet::GetNodeName()
{
	return XML_GDTF_ArtNet;
}

SceneData::GdtfsAcn::GdtfsAcn()
{
}

SceneData::GdtfsAcn::~GdtfsAcn()
{
}

EGdtfObjectType SceneData::GdtfsAcn::GetObjectType()
{
	return EGdtfObjectType::eGdtf_sACN;
}

TXString SceneData::GdtfsAcn::GetNodeName()
{
	return XML_GDTF_sACN;
}

SceneData::GdtfKiNET::GdtfKiNET()
{
}

SceneData::GdtfKiNET::~GdtfKiNET()
{
}

EGdtfObjectType SceneData::GdtfKiNET::GetObjectType()
{
	return EGdtfObjectType::eGdtfKiNET;
}

TXString SceneData::GdtfKiNET::GetNodeName()
{
	return XML_GDTF_KiNET;
}

SceneData::GdtfPosiStageNet::GdtfPosiStageNet()
{
}

SceneData::GdtfPosiStageNet::~GdtfPosiStageNet()
{
}

EGdtfObjectType SceneData::GdtfPosiStageNet::GetObjectType()
{
	return EGdtfObjectType::eGdtfPosiStageNet;
}

TXString SceneData::GdtfPosiStageNet::GetNodeName()
{
	return XML_GDTF_PosiStageNet;
}

SceneData::GdtfOpenSoundControl::GdtfOpenSoundControl()
{
}

SceneData::GdtfOpenSoundControl::~GdtfOpenSoundControl()
{
}

EGdtfObjectType SceneData::GdtfOpenSoundControl::GetObjectType()
{
	return EGdtfObjectType::eGdtfOpenSoundControl;
}

TXString SceneData::GdtfOpenSoundControl::GetNodeName()
{
	return XML_GDTF_OpenSoundControl;
}

SceneData::GdtfCITP::GdtfCITP()
{
}

SceneData::GdtfCITP::~GdtfCITP()
{
}

EGdtfObjectType SceneData::GdtfCITP::GetObjectType()
{
	return EGdtfObjectType::eGdtfCITP;
}

TXString SceneData::GdtfCITP::GetNodeName()
{
	return XML_GDTF_CITP;
}

SceneData::GdtfMacroDMX::GdtfMacroDMX()
{
}

SceneData::GdtfMacroDMX::~GdtfMacroDMX()
{
}

EGdtfObjectType SceneData::GdtfMacroDMX::GetObjectType()
{
	return EGdtfObjectType::eGdtfMacroDMX;
}

TGdtfMacroDMXStepArray SceneData::GdtfMacroDMX::GetStepArray()
{
	return fDMXSetps;
}

GdtfMacroDMXStepPtr SceneData::GdtfMacroDMX::AddDmxStep(Sint32& duration)
{
	GdtfMacroDMXStepPtr dmxStep = new GdtfMacroDMXStep(duration);
	fDMXSetps.push_back(dmxStep);
	
	return dmxStep;
}

TXString SceneData::GdtfMacroDMX::GetNodeName()
{
	return XML_GDTF_MacroDMX;
}

void SceneData::GdtfMacroDMX::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	// -
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfMacroDMXStep* dmxStep : fDMXSetps)
	{
		dmxStep->WriteToNode(pNode);
	}
}

void SceneData::GdtfMacroDMX::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	// -
	// Read the childs
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_MacroDMXStep, [this](IXMLFileNodePtr objNode) -> void
								 {
									 GdtfMacroDMXStepPtr  dmxStep = new GdtfMacroDMXStep();
									 
									 dmxStep->ReadFromNode(objNode);
									 
									 fDMXSetps.push_back(dmxStep);
									 return;
								 });
}

SceneData::GdtfMacroDMXValue::GdtfMacroDMXValue()
{
}

SceneData::GdtfMacroDMXValue::GdtfMacroDMXValue(DmxValue dmxVal, GdtfDmxChannelPtr dmxChannel)
{
	fValue = dmxVal;
	funresolvedDMXChannel = "";
	fDMXChannel = dmxChannel;
}

SceneData::GdtfMacroDMXValue::~GdtfMacroDMXValue()
{
	if (fDMXChannel) { delete fDMXChannel; }
}

SceneData::GdtfMacroDMXStep::GdtfMacroDMXStep()
{
}

SceneData::GdtfMacroDMXStep::GdtfMacroDMXStep(Sint32 duration)
{
	fDuration = duration;
}

SceneData::GdtfMacroDMXStep::~GdtfMacroDMXStep()
{
}

EGdtfObjectType SceneData::GdtfMacroDMXStep::GetObjectType()
{
	return EGdtfObjectType::eGdtfMacroDMXStep;
}

Sint32 SceneData::GdtfMacroDMXStep::GetDuration() const
{
	return fDuration;
}

TGdtfMacroDMXValueArray SceneData::GdtfMacroDMXStep::GetDMXValueArray() const
{
	return fDMXValues;
}

void SceneData::GdtfMacroDMXStep::SetDuration(Sint32 d)
{
	fDuration = d;
}

GdtfMacroDMXValuePtr SceneData::GdtfMacroDMXStep::AddDmxValue(DmxValue dmxVal, GdtfDmxChannelPtr dmxChannel)
{
	GdtfMacroDMXValuePtr val = new GdtfMacroDMXValue(dmxVal, dmxChannel);
	fDMXValues.push_back(val);
	
	return val;
}

TXString SceneData::GdtfMacroDMXStep::GetNodeName()
{
	return XML_GDTF_MacroDMXStep;
}

void SceneData::GdtfMacroDMXStep::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_MacroDMXStepDuration, GdtfConverter::ConvertInteger(fDuration) );
	
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfMacroDMXValuePtr dmxVal : fDMXValues)
	{
		dmxVal->WriteToNode(pNode);
	}
}

void SceneData::GdtfMacroDMXStep::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString durationStr;
	pNode->GetNodeAttributeValue(XML_GDTF_MacroDMXStepDuration, durationStr);
	GdtfConverter::ConvertInteger(durationStr, pNode, fDuration);
	// Read the childs
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_MacroDMXValue, [this](IXMLFileNodePtr objNode) -> void
								 {
									 GdtfMacroDMXValuePtr dmxValue= new GdtfMacroDMXValue();
									 
									 dmxValue->ReadFromNode(objNode);
									 
									 fDMXValues.push_back(dmxValue);
									 return;
								 });
}

void SceneData::GdtfMacroDMXStep::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	optional.push_back(XML_GDTF_MacroDMXStepDuration);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType SceneData::GdtfMacroDMXValue::GetObjectType()
{
	return EGdtfObjectType::eGdtfMacroDMXValue;
}

DmxValue SceneData::GdtfMacroDMXValue::GetValue() const
{
	return fValue;
}

const TXString & SceneData::GdtfMacroDMXValue::GetUnresolvedDMXChannel() const
{
	return funresolvedDMXChannel;
}

GdtfDmxChannelPtr SceneData::GdtfMacroDMXValue::GetDMXChannel() const
{
	return fDMXChannel;
}

void SceneData::GdtfMacroDMXValue::SetValue(DmxValue val)
{
	fValue = val;
}

void SceneData::GdtfMacroDMXValue::SetDMXChannel(GdtfDmxChannelPtr chnl)
{
	fDMXChannel = chnl;
}

TXString SceneData::GdtfMacroDMXValue::GetNodeName()
{
	return XML_GDTF_MacroDMXValue;
}

void SceneData::GdtfMacroDMXValue::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	TXString valStr; // XXX GdtfConverter::ConvertDMXValue(dmxValStr, ???, fDMXValue);  We need Fade/Uber und Fine to calculate the DmxValue; See DMXChannel
	pNode->SetNodeAttributeValue(XML_GDTF_MacroDMXValue_AttrValue, valStr);
	//
	pNode->SetNodeAttributeValue(XML_GDTF_MacroDMXValue_AttrChannel, fDMXChannel->GetNodeReference() );
}

void SceneData::GdtfMacroDMXValue::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString valStr;  pNode->GetNodeAttributeValue(XML_GDTF_MacroDMXValue_AttrValue, valStr);
	// XXX fValue X GdtfConverter::ConvertDMXValue
	pNode->GetNodeAttributeValue(XML_GDTF_MacroDMXValue_AttrChannel, funresolvedDMXChannel);
}

void SceneData::GdtfMacroDMXValue::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_MacroDMXValue_AttrValue);
	needed.push_back(XML_GDTF_MacroDMXValue_AttrChannel);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfMacroVisual::GdtfMacroVisual()
{
}

SceneData::GdtfMacroVisual::~GdtfMacroVisual()
{
}

EGdtfObjectType SceneData::GdtfMacroVisual::GetObjectType()
{
	return EGdtfObjectType::eGdtfMacroVisual;
}

TGdtfMacroVisualStepArray SceneData::GdtfMacroVisual::GetVisualStepArray()
{
	return fVisualSteps;
}

GdtfMacroVisualStepPtr SceneData::GdtfMacroVisual::AddVisualStep()
{
	GdtfMacroVisualStepPtr visuealStep = new GdtfMacroVisualStep();
	fVisualSteps.push_back(visuealStep);
	
	return visuealStep;
}

TXString SceneData::GdtfMacroVisual::GetNodeName()
{
	return XML_GDTF_MacroVisual;
}

void SceneData::GdtfMacroVisual::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	// -
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfMacroVisualStepPtr visualStep : fVisualSteps)
	{
		visualStep->WriteToNode(pNode);
	}
}

void SceneData::GdtfMacroVisual::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	// -
	// Read the childs
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_MacroVisualStep, [this](IXMLFileNodePtr objNode) -> void
								 {
									 GdtfMacroVisualStepPtr macroVisual= new GdtfMacroVisualStep();
									 
									 macroVisual->ReadFromNode(objNode);
									 
									 fVisualSteps.push_back(macroVisual);
									 return;
								 });
}

SceneData::GdtfMacroVisualStep::GdtfMacroVisualStep()
{
	fDuration = 1; // Default value: 1; Size 1 byte; Unit: DMX frame.
	fFade = 0;     // Default value: 0.0. Unit: milliseconds.
	fDelay = 0;    // Default value: 0.0. Unit: milliseconds.
}

SceneData::GdtfMacroVisualStep::~GdtfMacroVisualStep()
{
}

TGdtfMacroVisualValueArray SceneData::GdtfMacroVisualStep::GetVisualValueArray()
{
	return fVisualValues;
}

EGdtfObjectType SceneData::GdtfMacroVisualStep::GetObjectType()
{
	return EGdtfObjectType::eGdtfMacroVisualStep;
}

Sint32 SceneData::GdtfMacroVisualStep::getDuration()
{
	return fDuration;
}

double SceneData::GdtfMacroVisualStep::getFade()
{
	return fFade;
}

double SceneData::GdtfMacroVisualStep::getDelay()
{
	return fDelay;
}

void SceneData::GdtfMacroVisualStep::setDuration(Sint32 d)
{
	fDuration = d;
}

void SceneData::GdtfMacroVisualStep::setFade(double f)
{
	fFade = f;
}

void SceneData::GdtfMacroVisualStep::setDelay(double d)
{
	fDelay = d;
}

GdtfMacroVisualValue* SceneData::GdtfMacroVisualStep::AddVisualValue(DmxValue& dmxVal, GdtfDmxChannelFunctionPtr channelFunctionRef)
{
	GdtfMacroVisualValue* val = new GdtfMacroVisualValue(dmxVal, channelFunctionRef);
	
	fVisualValues.push_back(val);
	
	return val;
}

TXString SceneData::GdtfMacroVisualStep::GetNodeName()
{
	return XML_GDTF_MacroVisualStep;
}

void SceneData::GdtfMacroVisualStep::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrDuration, GdtfConverter::ConvertInteger(fDuration));
	pNode->SetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrFade,     GdtfConverter::ConvertDouble (fFade));
	pNode->SetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrDelay,    GdtfConverter::ConvertDouble (fDelay));
	
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfMacroVisualValuePtr visualVal : fVisualValues)
	{
		visualVal->WriteToNode(pNode);
	}
}

void SceneData::GdtfMacroVisualStep::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString durationStr; pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrDuration, durationStr);
	GdtfConverter::ConvertInteger(durationStr, pNode, fDuration);
	TXString fadeStr;     pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrFade, fadeStr);
	GdtfConverter::ConvertDouble(fadeStr, pNode, fFade);
	TXString delayStr;    pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrDelay, delayStr);
	GdtfConverter::ConvertDouble(delayStr, pNode, fDelay);
	
	// Read the childs
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_MacroVisualValue, [this](IXMLFileNodePtr objNode) -> void
								 {
									 GdtfMacroVisualValuePtr visuealVal = new GdtfMacroVisualValue();
									 
									 visuealVal->ReadFromNode(objNode);
									 
									 fVisualValues.push_back(visuealVal);
									 return;
								 });
}

void SceneData::GdtfMacroVisualStep::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	optional.push_back(XML_GDTF_MacroVisualStep_AttrDuration);
	optional.push_back(XML_GDTF_MacroVisualStep_AttrFade);
	optional.push_back(XML_GDTF_MacroVisualStep_AttrDelay);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfMacroVisualValue::GdtfMacroVisualValue()
{
	fChannelFunctionRef = nullptr;
}

SceneData::GdtfMacroVisualValue::GdtfMacroVisualValue(DmxValue dmxVal, GdtfDmxChannelFunctionPtr channelFunctionRef)
{
	fDmxValue = dmxVal;
	fChannelFunctionRef = channelFunctionRef;
}

SceneData::GdtfMacroVisualValue::~GdtfMacroVisualValue()
{
	if (fChannelFunctionRef) { delete fChannelFunctionRef; }
}

EGdtfObjectType SceneData::GdtfMacroVisualValue::GetObjectType()
{
	return EGdtfObjectType::eGdtfMacroVisualValue;
}

DmxValue SceneData::GdtfMacroVisualValue::GetDmxValue() const
{
	return fDmxValue;
}

const TXString & SceneData::GdtfMacroVisualValue::GetUnresolvedChannelFunctionRef() const
{
	return fUnresolvedChannelFunctionRef;
}

GdtfDmxChannelFunctionPtr SceneData::GdtfMacroVisualValue::GetChannelFunctionRef() const
{
	return fChannelFunctionRef;
}

void SceneData::GdtfMacroVisualValue::SetDmxValue(DmxValue val)
{
	fDmxValue = val;
}

void SceneData::GdtfMacroVisualValue::SetUnresolvedChannelFunctionRef(const TXString& ref)
{
	fUnresolvedChannelFunctionRef = ref;
}

void SceneData::GdtfMacroVisualValue::SetChannelFunction(GdtfDmxChannelFunctionPtr ref)
{
	fChannelFunctionRef = ref;
}

TXString SceneData::GdtfMacroVisualValue::GetNodeName()
{
	return XML_GDTF_MacroVisualValue;
}

void SceneData::GdtfMacroVisualValue::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);

	EGdtfChannelBitResolution resolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;
	ASSERTN(kEveryone, fChannelFunctionRef != nullptr);
	if(fChannelFunctionRef) { fChannelFunctionRef->GetParentDMXChannel()->GetChannelBitResolution(); }
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_MacroVisualValue_AttrValue, GdtfConverter::ConvertDMXValue(fDmxValue, resolution));
	pNode->SetNodeAttributeValue(XML_GDTF_MacroVisualValue_AttrChanFunc, fChannelFunctionRef->GetNodeReference() );
}

void SceneData::GdtfMacroVisualValue::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);


	EGdtfChannelBitResolution resolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;
	ASSERTN(kEveryone, fChannelFunctionRef != nullptr);
	if(fChannelFunctionRef){ fChannelFunctionRef->GetParentDMXChannel()->GetChannelBitResolution(); }


	//------------------------------------------------------------------------------------
	// Get the attribute
	TXString dmxValStr; pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualValue_AttrValue, dmxValStr);
	GdtfConverter::ConvertDMXValue(dmxValStr, pNode, resolution ,fDmxValue);
	//
	pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualValue_AttrChanFunc, fUnresolvedChannelFunctionRef);
}

void SceneData::GdtfMacroVisualValue::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_MacroVisualValue_AttrValue);
	needed.push_back(XML_GDTF_MacroVisualValue_AttrChanFunc);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfSoftwareVersionID::GdtfSoftwareVersionID()
{
    fValue = 0;
}

SceneData::GdtfSoftwareVersionID::GdtfSoftwareVersionID(size_t value)
{
    fValue = value;
}

SceneData::GdtfSoftwareVersionID::~GdtfSoftwareVersionID()
{
     for (GdtfDMXPersonalityPtr obj		: fDmxPersonalityArray){ delete obj; }
}

EGdtfObjectType SceneData::GdtfSoftwareVersionID::GetObjectType()
{
    return EGdtfObjectType::eGdtfSoftwareVersionID;
}

size_t SceneData::GdtfSoftwareVersionID::GetValue() const
{
    return fValue;
}

const TGdtfDMXPersonalityArray& SceneData::GdtfSoftwareVersionID::GetDMXPersonalityArray()
{
    return fDmxPersonalityArray;
}

void SceneData::GdtfSoftwareVersionID::SetValue(size_t val)
{
    fValue = val;
}

GdtfDMXPersonalityPtr SceneData::GdtfSoftwareVersionID::AddDMXPersonality(size_t value, GdtfDmxModePtr dmxMode)
{
    GdtfDMXPersonalityPtr dmxPerso = new GdtfDMXPersonality(value, dmxMode);
    fDmxPersonalityArray.push_back(dmxPerso);

    return dmxPerso;
}

TXString SceneData::GdtfSoftwareVersionID::GetNodeName()
{
    return XML_GDTF_SoftwareVersionID_NodeNam;
}

void SceneData::GdtfSoftwareVersionID::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);

    //------------------------------------------------------------------------------------
    // Print the attributes
    pNode->SetNodeAttributeValue(XML_GDTF_SoftwareVersionID_Value, GdtfConverter::ConvertInteger(fValue));

    //------------------------------------------------------------------------------------
    // Print the childs
    for (GdtfDMXPersonalityPtr dmxPerso: fDmxPersonalityArray)
    {
        dmxPerso->WriteToNode(pNode);
    }
}

void SceneData::GdtfSoftwareVersionID::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnReadFromNode(pNode);

    //------------------------------------------------------------------------------------
    // Get the attributes
    TXString valueStr; pNode->GetNodeAttributeValue(XML_GDTF_SoftwareVersionID_Value, valueStr);
    GdtfConverter::ConvertInteger( valueStr, pNode, fValue);

    // Read the childs
    GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_DMXPersonalityNodeNam, [this](IXMLFileNodePtr objNode) -> void
    {
        GdtfDMXPersonalityPtr dmxPerso = new GdtfDMXPersonality();

        dmxPerso->ReadFromNode(objNode);

        fDmxPersonalityArray.push_back(dmxPerso);
        return;
    });
}
