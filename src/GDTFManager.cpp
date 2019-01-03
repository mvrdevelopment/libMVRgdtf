//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "GDTFManager.h"
#include "SceneDataExchange.h"
#include "XmlFileHelper.h"
#include "HashManager.h"
#include <iostream>

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
	if (nodeName != GetNodeName()) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eNodeWrongName, &pnode); SceneData::GdtfFixture::AddError(error); }
	
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
	// TODO
	// internal error - assert only?
	// if ( !parent ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eNoFeatureParent); SceneData::GdtfFixture::AddError(error); }
	
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
	// TODO
	// internal error - assert only?
	// if ( !fFeature ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eAttribute); SceneData::GdtfFixture::AddError(error); }

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
    TXString physicalUnitStr; pNode->GetNodeAttributeValue(XML_GDTF_AttributePhysicalUnit, physicalUnitStr); GdtfConverter::ConvertPhysicalUnitEnum(physicalUnitStr, fPhysicalUnit);
    TXString colorStr;        pNode->GetNodeAttributeValue(XML_GDTF_AttributeColor, colorStr); GdtfConverter::ConvertColor(colorStr, fColor);
	
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
	// TODO
	// internal error - assert only?
	// if ( !(fFeature == nullptr) ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eAttribute); SceneData::GdtfFixture::AddError(error); }
	fFeature = newFeat;
	
	ASSERTN(kEveryone, newFeat != nullptr);
	// TODO
	// internal error - assert only?
	// if ( !(newFeat != nullptr) ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eAttribute); SceneData::GdtfFixture::AddError(error); }
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
	
	TXString color;		pNode->GetNodeAttributeValue(XML_GDTF_PrismFacetColor,		color);		GdtfConverter::ConvertColor(color, fColor);
	TXString transfrom;	pNode->GetNodeAttributeValue(XML_GDTF_PrismFacetRotation,	transfrom);	GdtfConverter::ConvertRotation(transfrom, fTransform);
	
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
	if (folder == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eWheelSlotMissingPNGDirectory); SceneData::GdtfFixture::AddError(error); }
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
            GdtfConverter::ConvertColor(color, this->fColor);
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

void GdtfModel::SetGeometryFile(const Gdtf3DSFile &file)
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
	TXString length;	pNode->GetNodeAttributeValue(XML_GDTF_ModelLength,			length);	GdtfConverter::ConvertDouble(length, fLength);
	TXString width;		pNode->GetNodeAttributeValue(XML_GDTF_ModelWidth,			width);		GdtfConverter::ConvertDouble(width,  fWidth);
	TXString height;	pNode->GetNodeAttributeValue(XML_GDTF_ModelHeight,			height);	GdtfConverter::ConvertDouble(height, fHeight);
	TXString type;		pNode->GetNodeAttributeValue(XML_GDTF_ModelPrimitiveType,	type);		GdtfConverter::ConvertPrimitiveType(type, fPrimitiveType);
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

const TXString& GdtfModel::GetGeometryFile() const
{
	return fGeometryFile;
}

const TXString& GdtfModel::GetGeometryFileFullPath()
{
	TXString				workingFolder;
	IFolderIdentifierPtr	folder;
	fParentFixture->GetWorkingFolder(folder);
	
	ASSERTN(kEveryone, folder != nullptr);
	if (folder == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eModelMissingGeometryDirectory); SceneData::GdtfFixture::AddError(error); }
	if (folder) { folder->GetFullPath(workingFolder); }
	
	// Set to store
	fFullPath = workingFolder + fGeometryFile;
	
	// Return
	return fFullPath;
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

	ASSERTN(kEveryone, fModelReference != nullptr);
	if (fModelReference == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eGeometryMissingModelReference); SceneData::GdtfFixture::AddError(error); }
	if (fModelReference) { pNode->SetNodeAttributeValue(XML_GDTF_GeometryModelRef,			fModelReference->GetNodeReference()); }
	
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
	GdtfConverter::ConvertMatrix(matrix,fMatrix);
	
	// Get Node Reference
	pNode->GetNodeAttributeValue(XML_GDTF_GeometryModelRef,			fUnresolvedModelRef);
	
	// ------------------------------------------------------------------------------------
	// Print geometries
	GdtfConverter::TraverseMultiNodes(pNode, "", [this] (IXMLFileNodePtr objNode,const TXString& childNodeName) -> void
									  {
										  bool hasBreak = false;;
										  
										  GdtfGeometryPtr geometry = nullptr;
										  if	  (childNodeName == XML_GDTF_GeometryAxisNodeName)		{ geometry = new GdtfGeometryAxis(this);}
										  else if (childNodeName == XML_GDTF_GeometryNodeName)			{ geometry = new GdtfGeometry(this);}
										  else if (childNodeName == XML_GDTF_FilterBeamNodeName)		{ geometry = new GdtfGeometryBeamFilter(this);}
										  else if (childNodeName == XML_GDTF_FilterColorNodeName)		{ geometry = new GdtfGeometryColorFilter(this);}
										  else if (childNodeName == XML_GDTF_FilterGoboNodeName)		{ geometry = new GdtfGeometryGoboFilter(this);}
										  else if (childNodeName == XML_GDTF_FilterShaperNodeName)		{ geometry = new GdtfGeometryShaperFilter(this);}
										  else if (childNodeName == XML_GDTF_LampNodeName)				{ geometry = new GdtfGeometryLamp(this);}
										  else if (childNodeName == XML_GDTF_GeometryReferenceNodeName)	{ geometry = new GdtfGeometryReference(this);}
										  else if (childNodeName == XML_GDTF_BreakNodeName)				{ hasBreak = true; }
										  else															{ DSTOP((kEveryone,"There is a node that was not aspected!")); }
										  
										  
										  if (hasBreak)
										  {
											  // This is only allowed in Geometry Refs
											  ASSERTN(kEveryone, this->GetObjectType() == eGdtfGeometryReference);
											  if (this->GetObjectType() != eGdtfGeometryReference) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eGeometryIsNotGeometryReferenceType); SceneData::GdtfFixture::AddError(error); }
											  if (this->GetObjectType() == eGdtfGeometryReference)
											  {
												  GdtfBreakPtr breakObj = new GdtfBreak();
												  breakObj->ReadFromNode(objNode);
												  
												  GdtfGeometryReferencePtr refGeo = dynamic_cast<GdtfGeometryReferencePtr>(this);
												  refGeo->fBreaks.push_back(breakObj);
												  return;
											  }
										  }
										  
										  ASSERTN(kEveryone, geometry != nullptr);
										  if (geometry == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eGeometryMissingGeometryObject); SceneData::GdtfFixture::AddError(error); }
										  if (geometry)
										  {
											  geometry->ReadFromNode(objNode);
											  fInternalGeometries.push_back(geometry);
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
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	needed.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);
	
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
	// TODO
	// Assert only?
	// if (ref == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eGeometry); SceneData::GdtfFixture::AddError(error); }
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

	if (fParent)	{ nodeRef = fParent->GetNodeReference() + "." + GetName(); }
	else			{ nodeRef = GetName();}

	return nodeRef;
}

//------------------------------------------------------------------------------------
// GdtfGeometryAxis
GdtfGeometryAxis::GdtfGeometryAxis(GdtfGeometry* parent) 
				: GdtfGeometry(parent)
{
	fAngleStart = 0;
	fAngleEnd	= 0;
	fSpeed		= 0;	
}

GdtfGeometryAxis::GdtfGeometryAxis(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent)
				: GdtfGeometry(name,refToModel,ma, parent)
{
	fAngleStart = 0;
	fAngleEnd	= 0;
	fSpeed		= 0;
}

GdtfGeometryAxis::~GdtfGeometryAxis()
{
}

void GdtfGeometryAxis::SetStartAngle(double start)
{
	fAngleStart = start;
}

void GdtfGeometryAxis::SetEndAngle(double end)
{
	fAngleEnd = end;
}

void GdtfGeometryAxis::SetSpeed(double speed)
{
	fSpeed = speed;
}

void GdtfGeometryAxis::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_GeometryAxisFrom,			GdtfConverter::ConvertDouble(fAngleStart));
	pNode->SetNodeAttributeValue(XML_GDTF_GeometryAxisTo,			GdtfConverter::ConvertDouble(fAngleEnd));
	pNode->SetNodeAttributeValue(XML_GDTF_GeometryAxisSpeed,		GdtfConverter::ConvertDouble(fSpeed));

}

void GdtfGeometryAxis::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
	
	// Read Axis from
	TXString angleStart;	pNode->GetNodeAttributeValue(XML_GDTF_GeometryAxisFrom,		angleStart);	GdtfConverter::ConvertDouble(angleStart,	fAngleStart);
	TXString angleEnd;		pNode->GetNodeAttributeValue(XML_GDTF_GeometryAxisTo,		angleEnd);		GdtfConverter::ConvertDouble(angleEnd,		fAngleEnd);
	TXString speed;			pNode->GetNodeAttributeValue(XML_GDTF_GeometryAxisSpeed,	speed);			GdtfConverter::ConvertDouble(speed,			fSpeed);

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
	optional.push_back(XML_GDTF_GeometryAxisFrom);
	optional.push_back(XML_GDTF_GeometryAxisTo);
	optional.push_back(XML_GDTF_GeometryAxisSpeed);
	
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

double GdtfGeometryAxis::GetStartAngle()
{
	return fAngleStart;
}

double GdtfGeometryAxis::GetEndAngle()
{
	return fAngleEnd;
}

double GdtfGeometryAxis::GetSpeed()
{
	return fSpeed;
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
	pNode->SetNodeAttributeValue(XML_GDTF_LampLuminousIntensity,	GdtfConverter::ConvertDouble(fLuminousIntensity));
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
	TXString lampType;	pNode->GetNodeAttributeValue(XML_GDTF_LampLampType,				lampType);	GdtfConverter::ConvertLampeType(lampType,	fLampType);
	TXString power;		pNode->GetNodeAttributeValue(XML_GDTF_LampPowerConsumption,		power);		GdtfConverter::ConvertDouble(power,			fPowerConsuption);
	TXString lum;		pNode->GetNodeAttributeValue(XML_GDTF_LampLuminousIntensity,	lum);		GdtfConverter::ConvertDouble(lum,			fLuminousIntensity);
	TXString colorTemp;	pNode->GetNodeAttributeValue(XML_GDTF_ColorTemperature,			colorTemp);	GdtfConverter::ConvertDouble(colorTemp,		fColorTemperature);
	TXString angle;		pNode->GetNodeAttributeValue(XML_GDTF_BeamAngle,				angle);		GdtfConverter::ConvertDouble(angle,			fBeamAngle);
	TXString radius;	pNode->GetNodeAttributeValue(XML_GDTF_BeamRadius,				radius);	GdtfConverter::ConvertDouble(radius,		fBeamRadius);
	TXString fieldAngle;pNode->GetNodeAttributeValue(XML_GDTF_FieldAngle,				fieldAngle);GdtfConverter::ConvertDouble(fieldAngle,	fFieldAngle);
	TXString type;		pNode->GetNodeAttributeValue(XML_GDTF_BeamType,					type);		GdtfConverter::ConvertBeamType(type,		fBeamType);
	TXString colorIndex;pNode->GetNodeAttributeValue(XML_GDTF_BeamColorRenderingIndex,	colorIndex);GdtfConverter::ConvertInteger(colorIndex,	fColorIndex);
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
	optional.push_back(XML_GDTF_LampLuminousIntensity);
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
	TXString dmxbreak;	pNode->GetNodeAttributeValue(XML_GDTF_BreakDMXBreak,dmxbreak	); GdtfConverter::ConvertInteger(dmxbreak, fDmxBreak);
	TXString dmxAdress;	pNode->GetNodeAttributeValue(XML_GDTF_BreakOffset,	dmxAdress	); GdtfConverter::ConvertDMXAdress(dmxAdress, fDmxAdress);
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
	fCoarse					= 0;	fCoarseNone		= true;
	fFine					= 0;	fFineNone		= true;
	fUltra					= 0;	fUltraNone		= true;
	fUber					= 0;    fUberNone		= true;
	fFrequenz				= eGdtfDmxFrequency_30;
	fDefaultValue			= 0;
	fHeighlight				= 0;	fHeighlightNone = true;
	fMoveInBlackFrames		= 0;
	fDmxChangeTimeLimit		= 0;
	fGeomRef				= nullptr;

	ASSERTN(kEveryone, parent != nullptr);
	// TODO
	// assert only?
	// if (parent == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelMissingParent); SceneData::GdtfFixture::AddError(error); }
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
	if(fCoarse > 0) {fCoarseNone = false;}
	
}

void GdtfDmxChannel::SetDmxFine(Sint32 fine)
{
	fFine = fine;
	if(fFine > 0) {fFineNone = false;}
}

void GdtfDmxChannel::SetDmxUltra(Sint32 ultra)
{
	fUltra = ultra;
	if(fUltra > 0) {fUltraNone = false;}
}

void SceneData::GdtfDmxChannel::SetDmxUber(Sint32 uber)
{
	fUber = uber;
	if(fUber > 0) {fUberNone = false;}
}

void GdtfDmxChannel::SetFrequency(EGdtfDmxFrequency frequency)
{
	fFrequenz = frequency;
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

void GdtfDmxChannel::SetMoveInBlackFrames(double moveInBlackFrames)
{
	fMoveInBlackFrames = moveInBlackFrames;
}

void GdtfDmxChannel::SetDmxChangeTimeLimit(double changeLimit)
{
	fDmxChangeTimeLimit = changeLimit;
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
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelCoarse,				GdtfConverter::ConvertInteger(fCoarse ,		fCoarseNone));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFine,				GdtfConverter::ConvertInteger(fFine,		fFineNone));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelUltra,				GdtfConverter::ConvertInteger(fUltra,		fUltraNone));	
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelUber,				GdtfConverter::ConvertInteger(fUber,		fUberNone));	
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFrequency,			GdtfConverter::ConvertFrequenz(fFrequenz));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelDefault,			GdtfConverter::ConvertDMXValue(fDefaultValue, chanelReso));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelHighlight,			GdtfConverter::ConvertDMXValue(fHeighlight,	chanelReso, fHeighlightNone));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelMibFadeFrames,		GdtfConverter::ConvertDouble(fMoveInBlackFrames));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelDMXChangeTimeLimit,	GdtfConverter::ConvertDouble(fDmxChangeTimeLimit));	
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
	TXString dmxBreak;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelDMXBreak,			dmxBreak);	GdtfConverter::ConvertDmxBreak(dmxBreak,		fDmxBreak);
	//
	TXString coarse;	
	if (pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelCoarse, coarse) == kVCOMError_NoError) 
	{
		GdtfConverter::ConvertInteger(coarse, fCoarse, fCoarseNone);
	}	
	//
	TXString fine;		
	if (pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFine, fine) ==  kVCOMError_NoError) 
	{
		GdtfConverter::ConvertInteger(fine,	fFine, fFineNone);
	}
	//
	TXString ultra;		
	if (pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelUltra, ultra) == kVCOMError_NoError) 
	{
		GdtfConverter::ConvertInteger(ultra, fUltra, fUltraNone);
	}	
	//
	TXString uber;
	if (pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelUber, uber) == kVCOMError_NoError) 
	{
		GdtfConverter::ConvertInteger(uber, fUber, fUberNone);
	}
	//
	TXString freq;		pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFrequency,			freq);		GdtfConverter::ConvertFrequenz(freq,		fFrequenz);
	//
	TXString defVal;	
	if (pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelDefault, defVal) == kVCOMError_NoError)
	{
		GdtfConverter::ConvertDMXValue(defVal, this->GetChannelBitResolution(), fDefaultValue);
	}	
	//
	TXString highlight;	
	if(VCOM_SUCCEEDED(pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelHighlight,			highlight)	))
	{
		GdtfConverter::ConvertDMXValue(highlight, this->GetChannelBitResolution(), fHeighlight, fHeighlightNone);
	}
	
	
	//
	TXString mib;		pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelMibFadeFrames,		mib);		GdtfConverter::ConvertDouble(mib,			fMoveInBlackFrames);
	TXString timelimit;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelDMXChangeTimeLimit,	timelimit);	GdtfConverter::ConvertDouble(timelimit,	fDmxChangeTimeLimit);
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
	optional.push_back(XML_GDTF_DMXChannelCoarse);
	optional.push_back(XML_GDTF_DMXChannelFine);
	optional.push_back(XML_GDTF_DMXChannelUltra);
	optional.push_back(XML_GDTF_DMXChannelUber);
	optional.push_back(XML_GDTF_DMXChannelFrequency);
	optional.push_back(XML_GDTF_DMXChannelDefault);
	optional.push_back(XML_GDTF_DMXChannelHighlight);
	optional.push_back(XML_GDTF_DMXChannelMibFadeFrames);
	optional.push_back(XML_GDTF_DMXChannelDMXChangeTimeLimit);

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
		// TODO
		// if (fGeomRef == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelUnresolvedGeometryReference); SceneData::GdtfFixture::AddError(error); }
		ASSERTN(kEveryone, fLogicalChannels.size() > 0);
		// TODO
		// if ( !(fLogicalChannels.size() > 0) ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannel); SceneData::GdtfFixture::AddError(error); }

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

EGdtfDmxFrequency GdtfDmxChannel::GetFrequency() const
{
	return fFrequenz;
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

double GdtfDmxChannel::GetMoveInBlackFrames() const
{
	return fMoveInBlackFrames;
}

double GdtfDmxChannel::GetDmxChangeTimeLimit() const
{
	return fDmxChangeTimeLimit;
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

#include <iostream>

EGdtfChannelBitResolution SceneData::GdtfDmxChannel::GetChannelBitResolution()
{

	if		(  fFineNone  &&   fUltraNone &&    fUberNone)		{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_8; }
	else if ((!fFineNone) &&   fUltraNone  &&   fUberNone )		{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_16; }
	else if ((!fFineNone) && (!fUltraNone) &&   fUberNone )		{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_24; }
	else if ((!fFineNone) && (!fUltraNone) && (!fUberNone))		{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_32; }
    	
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
	// TODO
	// if ( !(fNextLogicalChannel == nullptr) ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxLogicalChannel); SceneData::GdtfFixture::AddError(error); }
	fNextLogicalChannel = next;
}

GdtfDmxLogicalChannelPtr GdtfDmxLogicalChannel::GetNextLogicalChannel()
{
	return fNextLogicalChannel;
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
	TXString snap; pNode->GetNodeAttributeValue(XML_GDTF_DMXLogicalChannelSnap,			snap);	GdtfConverter::ConvertSnapEnum(snap, fSnap);
	TXString master;	pNode->GetNodeAttributeValue(XML_GDTF_DMXLogicalChannelMaster,				master);	GdtfConverter::ConvertMasterEnum(master,	fDmxMaster);
	
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
		if(fAttribute){ name +=fAttribute->GetName(); }
		ASSERTN(kEveryone, fAttribute != nullptr);
		if (fAttribute == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxLogicalChannelMissingName); SceneData::GdtfFixture::AddError(error); }
		

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
	fEncoderInvert			= EGDTFEncoderInvert::eGDTFEncoderInvert_No;
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
	fEncoderInvert			= EGDTFEncoderInvert::eGDTFEncoderInvert_No;
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
	if (fNextFunction != nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelFunctionMissingNextFunction); SceneData::GdtfFixture::AddError(error); }
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
	// TODO
	// if (fAttribute == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelFunction); SceneData::GdtfFixture::AddError(error); }
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionName,				fName);

	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDMXFrom,				GdtfConverter::ConvertDMXValue(fAdressStart, chanelReso));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalFrom,		GdtfConverter::ConvertDouble(fPhysicalStart));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalTo,			GdtfConverter::ConvertDouble(fPhysicalEnd));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionRealFade,			GdtfConverter::ConvertDouble(fRealFade));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelDMXInvert,					GdtfConverter::ConvertDMXInvertEnum(fDmxInvert));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelEncoderInvert,				GdtfConverter::ConvertEncoderInvertEnum(fEncoderInvert));
	
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionOriginalAttribute,								fOrignalAttribute);
	if (fAttribute)		    { pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionAttribute,			    fAttribute->GetNodeReference());}
	if (fOnWheel)			{ pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionWheelRef,				fOnWheel->GetNodeReference()); };
	if (fEmitter)			{ pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelEmitter,						fEmitter->GetNodeReference() ); };
	
	
	// Read Mode Master
	// TODO
	if(fModeMaster_Channel)
	{
		ASSERTN(kEveryone, (fModeMaster_Function == nullptr));
		if (fModeMaster_Function != nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelFunctionMissingModeMasterChannel); SceneData::GdtfFixture::AddError(error); }
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeMaster,				fModeMaster_Channel->GetNodeReference());	
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeFrom,				GdtfConverter::ConvertDMXValue(fDmxModeStart, fModeMaster_Channel->GetChannelBitResolution()));	
		pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeTo,					GdtfConverter::ConvertDMXValue(fDmxModeEnd,   fModeMaster_Channel->GetChannelBitResolution()));	
	}
	if(fModeMaster_Function)
	{
		ASSERTN(kEveryone, (fModeMaster_Channel == nullptr));
		if ( !(fModeMaster_Channel == nullptr) ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelFunctionMissingModeMasterFunction); SceneData::GdtfFixture::AddError(error); }
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
	TXString dmxFrom;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDMXFrom,				dmxFrom);	GdtfConverter::ConvertDMXValue(dmxFrom,	channelReso, fAdressStart);
	TXString physFrom;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalFrom,		physFrom);	GdtfConverter::ConvertDouble(physFrom,		fPhysicalStart);
	TXString physTo;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalTo,			physTo);	GdtfConverter::ConvertDouble(physTo,		fPhysicalEnd);
	TXString realFade;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionRealFade,			realFade);	GdtfConverter::ConvertDouble(realFade,		fRealFade);
	TXString dmxInvert;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelDMXInvert,					dmxInvert);	GdtfConverter::ConvertDMXInvertEnum(dmxInvert,		fDmxInvert);
	TXString encInvert;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelEncoderInvert,				encInvert);	GdtfConverter::ConvertEncoderInvertEnum(encInvert,	fEncoderInvert);
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
	needed.push_back(XML_GDTF_DMXChannelFuntionName);

	TXStringArray optional;
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
	optional.push_back(XML_GDTF_DMXChannelEncoderInvert);

	
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
	return fParentLogicalChannel->GetNodeReference() + "." + GetName();
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

EGDTFDmxInvert SceneData::GdtfDmxChannelFunction::GetDmxInvert() const
{
    return fDmxInvert;
}

EGDTFEncoderInvert SceneData::GdtfDmxChannelFunction::GetEncoderInvert() const
{
    return fEncoderInvert;
}

void GdtfDmxChannelFunction::SetWheel(GdtfWheelPtr newWhl)
{
	fOnWheel = newWhl;
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
	GdtfConverter::ConvertDMXValue(fUnresolvedDmxModeStart, resolution, fDmxModeStart);
	GdtfConverter::ConvertDMXValue(fUnresolvedDmxModeEnd, resolution, fDmxModeEnd);
}

void GdtfDmxChannelFunction::SetModeMaster_Channel(GdtfDmxChannel* channel)
{
	ASSERTN(kEveryone, fModeMaster_Function == nullptr);
	// TODO
	// if ( !(fModeMaster_Function == nullptr) ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelFunction); SceneData::GdtfFixture::AddError(error); }
	fModeMaster_Function = nullptr;
	fModeMaster_Channel = channel;
}

void GdtfDmxChannelFunction::SetModeMaster_Function(GdtfDmxChannelFunction* function)
{
	ASSERTN(kEveryone, fModeMaster_Channel == nullptr);
	// TODO
	// if ( !(fModeMaster_Channel == nullptr) ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelFunction); SceneData::GdtfFixture::AddError(error); }
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

void SceneData::GdtfDmxChannelFunction::SetEncoderInvert(EGDTFEncoderInvert encoderInvert)
{
    fEncoderInvert = encoderInvert;
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
	// TODO
	// if ( !(fNextChannelSet == nullptr) ) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxChannelSet); SceneData::GdtfFixture::AddError(error); }
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

	TXString dmxfrom;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetDMXFrom,				dmxfrom);	GdtfConverter::ConvertDMXValue (dmxfrom, channelReso, fDmxStart);
	TXString wheelId;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetWheelSlotIndexRef,	wheelId);	GdtfConverter::ConvertInteger(wheelId,  fWheelSlotIdx);
	
	
	TXString physFrom; pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalFrom,		physFrom);
	TXString physTo;   pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalTo,	    physTo);
	
	bool b1 = GdtfConverter::ConvertDouble(physTo,	fPhysicalEnd);
	bool b2 = GdtfConverter::ConvertDouble(physFrom,	fPhysicalStart);
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
	if(fNextChannelSet == nullptr && fDmxEnd == -1) {  return fParentChnlFunction->GetEndAdress(); }
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
	
	EGdtfChannelBitResolution chanelReso = fMasterDmxChannel->GetChannelBitResolution();
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
    TXString type;		pNode->GetNodeAttributeValue(XML_GDTF_DMXRelationType,		type);		GdtfConverter::ConvertRelationEnum(type,	fRelationType); 
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
    fText = "";
    fDate = "";
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
	pNode->SetNodeAttributeValue(XML_GDTF_RevisionDate,			fDate);
	
}

void GdtfRevision::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->GetNodeAttributeValue(XML_GDTF_RevisionText,			fText);
	pNode->GetNodeAttributeValue(XML_GDTF_RevisionDate,			fDate);
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
	// TODO Set text
	fText = text;
	fDate = "";
}

const TXString& GdtfRevision::GetDate() const
{
	return fDate;
}

const TXString& GdtfRevision::GetText() const
{
	return fText;
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
	TXString color;		pNode->GetNodeAttributeValue(XML_GDTF_EmitterColor,				color);		GdtfConverter::ConvertColor(color, fColor);
	
	
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
	TXString waveLength;	pNode->GetNodeAttributeValue(XML_GDTF_MeasurementWaveLegth,	waveLength);	GdtfConverter::ConvertDouble(waveLength,fWaveLength);
	TXString energy;		pNode->GetNodeAttributeValue(XML_GDTF_MeasurementEnergy,	energy);		GdtfConverter::ConvertDouble(energy,fEngergy);
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
	if (__ERROR_CONTAINER_POINTER != nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureErrorContainerPointer); SceneData::GdtfFixture::AddError(error); }
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
	if (exists == false) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureWorkingDirDoesNotExist); SceneData::GdtfFixture::AddError(error); }
	
	
	//-------------------------------------------------------------------------------------------------
	// Create a ZIP File
	IZIPFilePtr zipfile ( IID_ZIPFile );
	zipfile->OpenRead(inZipFile);

	ISceneDataZipBuffer xmlFileBuffer;
    ISceneDataZipBuffer xmlFileSHA256Buffer;
	
	
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	TXString outPath				= "";
	TXString inPath					= "";
	while (VCOM_SUCCEEDED( zipfile->GetNextFile(inPath, outPath)))
	{
		// This is the current file that we are reading
		ISceneDataZipBuffer buffer;
		
		zipfile->GetFile(outPath, &buffer);
		//std::cout << "OUTPATH " << outPath.GetCharPtr() << std::endl;
		
		if (outPath == "description.xml")
        {
			// Read the data
			size_t	size = 0;							buffer.GetDataSize(size);
			void*	data = malloc(size * sizeof(char));	buffer.CopyDataInto(data, size);
			
			// Set the buffer object
            xmlFileBuffer.SetData(data, size);
			
			// House keeping
			std::free(data);
        }
        else if (outPath == "description.checksum.txt")
        {
			// Read the data
            size_t	size = 0;							buffer.GetDataSize(size);
            void*	data = malloc(size * sizeof(char));	buffer.CopyDataInto(data, size);
			
			// Set the buffer object
            xmlFileSHA256Buffer.SetData(data, size);
			
			// House keeping
			std::free(data);
        }
		else
		{
			// Prepare pointer to the new files
			IFileIdentifierPtr file (IID_FileIdentifier);
			file->Set(fWorkingFolder, outPath);
			
			// dump buffer into file
			buffer.WriteToFile(file);
			
			// Add it into the file list
			fLocalFiles.push_back(file);

		}
		inPath = outPath;
	}
	
	//-------------------------------------------------------------------------------------------------
	// Prepare bools for checksum checks
	bool hasCheckSum	= false;
	bool checksumIsFine = false;
	
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	IFileIdentifierPtr gdtfFile (IID_FileIdentifier);
	
	if (! xmlFileBuffer.IsSet())
	{
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureNoGdtfFileInXmlBuffer); 
		fReaded = false;
		return;
	}
	
	if (xmlFileSHA256Buffer.IsSet())
	{
		if (HashManager::HashManager::CheckHashForBuffer(xmlFileBuffer, xmlFileSHA256Buffer) == false)
		{ 
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureChecksumError); 
			SceneData::GdtfFixture::AddError(error); 
		}
	}
	
	
	//-------------------------------------------------------------------------------------------------
	// Read XML
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
	
	
	fReaded = true;
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
			ASSERTN(kEveryone, dmxChannel->GetGeomRef());
			if (! dmxChannel->GetGeomRef()) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureDMXChannelMissingName); SceneData::GdtfFixture::AddError(error); }
			if (! dmxChannel->GetGeomRef()) { continue; }
			
			TXString geometryRef = dmxChannel->GetGeomRef()->GetName();
			TXString firstAttr;
			
			for (GdtfDmxLogicalChannelPtr logicalChannel : dmxChannel->GetLogicalChannelArray())
			{
				//------------------------------------------------------------------------------------------------
				//  Create Names for Logical Channels
				ASSERTN(kEveryone, !logicalChannel->GetUnresolvedAttribRef().IsEmpty());
				if (logicalChannel->GetUnresolvedAttribRef().IsEmpty()) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureLogicalChannelMissingName); SceneData::GdtfFixture::AddError(error); }
				logicalChannel->SetName(logicalChannel->GetUnresolvedAttribRef());
				
				// Set first Attribute
				if (firstAttr.IsEmpty()) { firstAttr = logicalChannel->GetUnresolvedAttribRef(); }
				
				//------------------------------------------------------------------------------------------------
				//  Create Names for Channel Functions
				Sint64 channelFunctionNumber = 1;
				for (GdtfDmxChannelFunctionPtr function : logicalChannel->GetDmxChannelFunctions())
				{
					//
					if (function->GetName().IsEmpty())
					{
						ASSERTN(kEveryone, !function->getUnresolvedAttrRef().IsEmpty());
						if (function->getUnresolvedAttrRef().IsEmpty())
						{
							IXMLFileNodePtr node;
							function->GetNode(node);
							GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureChannelFunctionMissingName, node);
							SceneData::GdtfFixture::AddError(error);
						}
						TXString functionName = function->getUnresolvedAttrRef();
						
						functionName += " ";
						functionName += TXString().itoa(channelFunctionNumber);
						
						function->SetName(functionName);
					}
					
					channelFunctionNumber++;
				}
			}
			
			//------------------------------------------------------------------------------------------------
			//  Set the DMX Name
			dmxChannel->SetName(geometryRef + "_" + firstAttr);
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
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedModelRef, node);
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
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedGeomRef, node);
				SceneData::GdtfFixture::AddError(error);
			}

			geoRef->SetLinkedGeometry(geo);
		}
		else
		{
			IXMLFileNodePtr node;
			geometry->GetNode(node);
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedGeomRef, node);
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
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureMissingActivationGroupPtr, node);
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
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureMissingAttributeFeature, node);
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
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureMissingAttributeMainAttribute, node);
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
		TXString unresolvedgeomRef	= dmxMode->GetUnresolvedGeomRef();
		if( ! unresolvedgeomRef.IsEmpty())
		{
			GdtfGeometryPtr geomPtr		= nullptr;
			
			for (GdtfGeometryPtr geo : fGeometries)
			{
				if (geo->GetNodeReference() == unresolvedgeomRef) { geomPtr = geo; break; }
			}
			
			// Check if there is a
			ASSERTN(kEveryone, geomPtr != nullptr);
			if (geomPtr != nullptr) { dmxMode->SetGeomRef(geomPtr); }
			else
			{
				IXMLFileNodePtr node;
				dmxMode->GetNode(node);				
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureMissingDMXModeGeomRef, node);
				SceneData::GdtfFixture::AddError(error);
			}
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
							GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedDMXModeMasters, node);
							SceneData::GdtfFixture::AddError(error);
						}
					}
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
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedDMXChannelGeomPtr, node);
				SceneData::GdtfFixture::AddError(error);
			}
		}
		else
		{
			IXMLFileNodePtr node;
			chnl->GetNode(node);
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedDMXChannelGeomRef, node);
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
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedDMXLogicalAttrRef, node); SceneData::GdtfFixture::AddError(error);
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
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureThumbnail,		fTumbnail);
	
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
	// Print RDM	
	// This is missing today
}

void GdtfFixture::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureName,						fName);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureShortName,					fShortName);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureManufacturer,				fManufacturer);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureDescription,				fFixtureTypeDescription);
	TXString uuid; pNode->GetNodeAttributeValue(XML_GDTF_FixtureTypeID,		uuid );	GdtfConverter::ConvertUUID(uuid, fGuid);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureThumbnail,					fTumbnail);
	
	
	TXString linkedUuid;
	pNode->GetNodeAttributeValue(XML_GDTF_LinkedUuid,		linkedUuid );
	fHasLinkedGuid = GdtfConverter::ConvertUUID(linkedUuid, fLinkedGuid);
	
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
							if (geometry == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eNodeWrongName, objNode); SceneData::GdtfFixture::AddError(error); }
							if (geometry)
							{
								geometry->ReadFromNode(objNode);
								fGeometries.push_back(geometry);
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
	SceneDataZip::AddFileToZip(zipfile, zipXmlBuffer, TXString(XML_GDTF_GDTFFILENAME) , true);

	
	return true;
}


GdtfRevisionPtr GdtfFixture::AddRevision(const TXString& text)
{
	GdtfRevision* revision = new GdtfRevision();;
	revision->SetText(text);
	
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

const GdtfPNGFile& GdtfFixture::GetPNGFile() const
{
    return fTumbnail;
}

const GdtfPNGFile& GdtfFixture::GetPNGFileFullPath()
{
	TXString				workingFolder;
	
	ASSERTN(kEveryone, fWorkingFolder != nullptr);
	if (fWorkingFolder) { fWorkingFolder->GetFullPath(workingFolder); }
	
	// Set to store
	fTumbnailFullPath = workingFolder + fTumbnail;
	
	// Return
	return fTumbnailFullPath;
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

void GdtfFixture::SetPNGFile(const GdtfPNGFile& png)
{
	fTumbnail = png;
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
    GdtfConverter::ConvertDouble(colorTempStr, fColorTemperature);

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
    GdtfConverter::ConvertEGdtfColorSampleEnum(cesStr, fCES);
    //
    TXString colorTempStr; pNode->GetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_AttrColorTemp, colorTempStr);
    GdtfConverter::ConvertInteger(colorTempStr, fColorTemperature);
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
	pNode->SetNodeAttributeValue(XML_GDTF_FTRDM_AttrSoftwareVersionIDs, GdtfConverter::ConvertIntegerArray(fSoftwareVersIDs) );
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfRDMParameter* rdmParam : fRDMParameters)
	{
		rdmParam->WriteToNode(pNode);
	}
	
	if (fRDMNotifications) { fRDMNotifications->WriteToNode(pNode); };
}

void SceneData::GdtfFTRDM::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString manufactStr; pNode->GetNodeAttributeValue(XML_GDTF_FTRDM_AttrManufacturerID, manufactStr);
	GdtfConverter::ConvertInteger(manufactStr, fManufacturerID);
	
	TXString deviceModelStr;  pNode->GetNodeAttributeValue(XML_GDTF_FTRDM_AttrDeviceModelID, deviceModelStr);
	GdtfConverter::ConvertInteger(deviceModelStr, fDeviceModelID);
	
	TXString softwareIDsStr;  pNode->GetNodeAttributeValue(XML_GDTF_FTRDM_AttrSoftwareVersionIDs, softwareIDsStr);
	GdtfConverter::ConvertIntegerArray ( softwareIDsStr, fSoftwareVersIDs);
	//------------------------------------------------------------------------------------
	// Read the childs
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_RDMParameterS, [this](IXMLFileNodePtr objNode) -> void
								 {
									 // Now we are in the <RDMParameters>(pure container) and need to go one deeper to read the <RDMParameter>.
									 GdtfConverter::TraverseNodes(objNode, "", XML_GDTF_RDMParameter, [this](IXMLFileNodePtr objNode) -> void
																  {
																	  GdtfRDMParameter* rdmParam = new GdtfRDMParameter();
																	  
																	  rdmParam->ReadFromNode(objNode);
																	  
																	  fRDMParameters.push_back(rdmParam);
																	  return;
																  } );
								 } );
	
	// Single childs:
	IXMLFileNode* rdmNotifysNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_RDMNotifications, &rdmNotifysNode)))
	{
		fRDMNotifications = new GdtfRDMNotifications();
		fRDMNotifications->ReadFromNode(rdmNotifysNode);
	}
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
	needed.push_back(XML_GDTF_FTRDM_AttrSoftwareVersionIDs);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfFTRDM::GdtfFTRDM()
{
	fManufacturerID = 0;
	fDeviceModelID  = 0;
	fRDMNotifications = nullptr;
}

SceneData::GdtfFTRDM::GdtfFTRDM(Sint32 manufacturerID, Sint32 deviceModelID) : GdtfFTRDM()
{
	fManufacturerID = manufacturerID;
	fDeviceModelID  = deviceModelID;
}

SceneData::GdtfFTRDM::~GdtfFTRDM()
{
	for (GdtfRDMParameterPtr ptr : fRDMParameters) { delete ptr; }
	
	if (fRDMNotifications) { delete fRDMNotifications; }
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

const TSint32Array& SceneData::GdtfFTRDM::GetSoftwareVersIDs() const
{
	return fSoftwareVersIDs;
}

const TGdtfRDMParameterArray & SceneData::GdtfFTRDM::GetRDMParametersArray() const
{
	return fRDMParameters;
}

GdtfRDMNotifications* SceneData::GdtfFTRDM::GetRDMNotifications() const
{
	return fRDMNotifications;
}

void SceneData::GdtfFTRDM::SetManufacturerID(Sint32 val)
{
	fManufacturerID = val;
}

void SceneData::GdtfFTRDM::SetDeviceModelID(Sint32 val)
{
	fDeviceModelID = val;
}

GdtfRDMParameterPtr SceneData::GdtfFTRDM::AddRDMParameter(
    const TXString& name,
    Sint32 PID,
    EGdtf_RDMParam_Type              Type,
    EGdtf_RDMParam_DataType          dataType,
    EGdtf_RDMParam_Command           command,
    EGdtf_RDMParam_SensorUnit        sensorUnit,
    EGdtf_RDMParam_SensorUnitPrefix  sensorUnitPrefix,
    Sint32                           minValue,
    Sint32                           maxValue,
    Sint32                           PDLSize,
    const TXString&                        description)
{
	GdtfRDMParameter* rdmParamPtr = new GdtfRDMParameter(
														 name,
														 PID,
														 Type,
														 dataType,
														 command,
														 sensorUnit,
														 sensorUnitPrefix,
														 minValue,
														 maxValue,
														 PDLSize,
														 description);
	
	fRDMParameters.push_back( rdmParamPtr);
	
	return rdmParamPtr;
}

void SceneData::GdtfFTRDM::SetRDMNotifications(GdtfRDMNotifications * notifications)
{
	fRDMNotifications = notifications;
}

void SceneData::GdtfFTRDM::AddSoftwareVersID(Sint32 ID)
{
	fSoftwareVersIDs.push_back(ID);
}

SceneData::GdtfRDMParameter::GdtfRDMParameter()
{
	fName = ""; // TODO: See Docu: Default value: object type with an index in parent???
	fPID  = 0;
	
	fType             = EGdtf_RDMParam_Type::Fixture;
	fDataType         = EGdtf_RDMParam_DataType::DS_NOT_DEFINED; 
	fCommand          = EGdtf_RDMParam_Command::None; 
	fSensorUnit       = EGdtf_RDMParam_SensorUnit::UNITS_NONE; 
	fSensorUnitPrefix = EGdtf_RDMParam_SensorUnitPrefix::PREFIX_NONE; 
	
	fMinValue = 0;
	fMaxValue = 0;
	fPDLSize =  0;
	fDescription = "";
}

SceneData::GdtfRDMParameter::GdtfRDMParameter(const TXString & name,
											  Sint32 PID,
											  EGdtf_RDMParam_Type Type,
											  EGdtf_RDMParam_DataType dataType,
											  EGdtf_RDMParam_Command command,
											  EGdtf_RDMParam_SensorUnit sensorUnit,
											  EGdtf_RDMParam_SensorUnitPrefix sensorUnitPrefix,
											  Sint32 minValue,
											  Sint32 maxValue,
											  Sint32 PDLSize,
											  const TXString & description) : GdtfRDMParameter()
{
	fName = name;
	fPID = PID;
	fType = Type;
	fDataType = dataType;
	fCommand = command;
	fSensorUnit = sensorUnit;
	fSensorUnitPrefix = sensorUnitPrefix;
	fMinValue = minValue;
	fMaxValue = maxValue;
	fPDLSize = PDLSize;
	fDescription = description;
}

SceneData::GdtfRDMParameter::~GdtfRDMParameter()
{
}

EGdtfObjectType SceneData::GdtfRDMParameter::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMParameter;
}

const TXString & SceneData::GdtfRDMParameter::GetName() const
{
	return fName;
}

Sint32 SceneData::GdtfRDMParameter::GetPID() const
{
	return fPID;
}

EGdtf_RDMParam_Type SceneData::GdtfRDMParameter::GetType() const
{
	return fType;
}

EGdtf_RDMParam_DataType SceneData::GdtfRDMParameter::GetDataType() const
{
	return fDataType;
}

EGdtf_RDMParam_Command SceneData::GdtfRDMParameter::GetCommand() const
{
	return fCommand;
}

EGdtf_RDMParam_SensorUnit SceneData::GdtfRDMParameter::GetSensorUnit() const
{
	return fSensorUnit;
}

EGdtf_RDMParam_SensorUnitPrefix SceneData::GdtfRDMParameter::GetSensorUnitPrefix() const
{
	return fSensorUnitPrefix;
}

Sint32 SceneData::GdtfRDMParameter::GetMinValue() const
{
	return fMinValue;
}

Sint32 SceneData::GdtfRDMParameter::GetMaxValue() const
{
	return fMaxValue;
}

Sint32 SceneData::GdtfRDMParameter::GetPDLSize() const
{
	return fPDLSize;
}

const TXString & SceneData::GdtfRDMParameter::GetDescription() const
{
	return fDescription;
}

const TGdtfRDMParameterValueArray & SceneData::GdtfRDMParameter::GetParameterValueArray() const
{
	return fParameterValueArray;
}

void SceneData::GdtfRDMParameter::SetName(const TXString & val)
{
	fName = val;
}

void SceneData::GdtfRDMParameter::SetPID(Sint32 val)
{
	fPID = val;
}

void SceneData::GdtfRDMParameter::SetType(EGdtf_RDMParam_Type val)
{
	fType = val;
}

void SceneData::GdtfRDMParameter::SetDataType(EGdtf_RDMParam_DataType val)
{
	fDataType = val;
}

void SceneData::GdtfRDMParameter::SetCommand(EGdtf_RDMParam_Command val)
{
	fCommand = val;
}

void SceneData::GdtfRDMParameter::SetSensorUnit(EGdtf_RDMParam_SensorUnit val)
{
	fSensorUnit = val;
}

void SceneData::GdtfRDMParameter::SetSensorUnitPrefix(EGdtf_RDMParam_SensorUnitPrefix val)
{
	fSensorUnitPrefix = val;
}

void SceneData::GdtfRDMParameter::SetMinValue(Sint32 val)
{
	fMinValue = val;
}

void SceneData::GdtfRDMParameter::SetMaxValue(Sint32 val)
{
	fMaxValue = val;
}

void SceneData::GdtfRDMParameter::SetPDLSize(Sint32 val)
{
	fPDLSize = val;
}

void SceneData::GdtfRDMParameter::SetDescription(const TXString & val)
{
	fDescription = val;
}

GdtfRDMParameterValue * SceneData::GdtfRDMParameter::AddRMDValueBool()
{
	GdtfRDMParameterValuePtr value = new GdtfRDMValueBool();
	
	fParameterValueArray.push_back(value);
	
	return value;
}

GdtfRDMParameterValue * SceneData::GdtfRDMParameter::AddDmxPersoalityDescription()
{
	GdtfRDMParameterValuePtr value = new GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION();
	
	fParameterValueArray.push_back(value);
	
	return value;
}

GdtfRDMParameterValue * SceneData::GdtfRDMParameter::AddSensorDefinition()
{
	GdtfRDMParameterValuePtr value = new GdtfRDMValue_SENSOR_DEFINITION();
	
	fParameterValueArray.push_back(value);
	
	return value;
}

GdtfRDMParameterValue * SceneData::GdtfRDMParameter::AddSlotInfo()
{
	GdtfRDMParameterValuePtr value = new GdtfRDMValue_SLOT_INFO();
	
	fParameterValueArray.push_back(value);
	
	return value;
}

GdtfRDMParameterValue * SceneData::GdtfRDMParameter::AddStatusID_Desciption()
{
	GdtfRDMParameterValuePtr value = new GdtfRDMValue_STATUS_ID_DESCRIPTION();
	
	fParameterValueArray.push_back(value);
	
	return value;
}

TXString SceneData::GdtfRDMParameter::GetNodeName()
{
	return XML_GDTF_RDMParameter;
}

void SceneData::GdtfRDMParameter::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrName, fName);
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrPID,  GdtfConverter::ConvertInteger(fPID) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrType, GdtfConverter::ConvertRDMParamTypeEnum(fType) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrDataType, GdtfConverter::Convert_RDMParamDataTypeEnum(fDataType) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrCommand, GdtfConverter::Convert_RDMParam_CommandEnum (fCommand) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrSensorUnit, GdtfConverter::Convert_RDMParam_SensorUnitEnum (fSensorUnit) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrSensorUnitPrefix, GdtfConverter::Convert_RDMParam_SensorUnitPrefixEnum (fSensorUnitPrefix) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrMinValue, GdtfConverter::ConvertInteger (fMinValue) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrMaxValue, GdtfConverter::ConvertInteger (fMaxValue) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrPDLSize, GdtfConverter::ConvertInteger (fPDLSize) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParam_AttrDescription, fDescription);
	
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfRDMParameterValue* paramValue : fParameterValueArray)
	{
		paramValue->WriteToNode(pNode);
	}
}

void SceneData::GdtfRDMParameter::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrName, fName);
	
	TXString pidStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrPID, pidStr);
	GdtfConverter::ConvertInteger(fPID);
	
	TXString typeStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrType, typeStr);
	GdtfConverter::ConvertRDMParamTypeEnum(typeStr, fType);
	
	TXString dataTypeStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrDataType, dataTypeStr);
	GdtfConverter::Convert_RDMParamDataTypeEnum( dataTypeStr, fDataType);
	
	TXString commandStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrCommand, commandStr);
	GdtfConverter::Convert_RDMParam_CommandEnum( commandStr, fCommand);
	
	TXString sensorUnitStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrSensorUnit, sensorUnitStr);
	GdtfConverter::Convert_RDMParam_SensorUnitEnum( sensorUnitStr, fSensorUnit);
	
	TXString sensorUnitPrefxStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrSensorUnitPrefix, sensorUnitPrefxStr);
	GdtfConverter::Convert_RDMParam_SensorUnitPrefixEnum( sensorUnitPrefxStr, fSensorUnitPrefix);
	
	TXString minValueStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrMinValue, minValueStr);
	GdtfConverter::ConvertInteger(minValueStr, fMinValue);
	
	TXString maxValueStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrMaxValue, maxValueStr);
	GdtfConverter::ConvertInteger(maxValueStr, fMaxValue);
	
	TXString pdlSizeStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrPDLSize, pdlSizeStr);
	GdtfConverter::ConvertInteger( pdlSizeStr, fPDLSize);
	
	pNode->GetNodeAttributeValue(XML_GDTF_RDMParam_AttrDescription, fDescription);
	
	// Read the childs
	GdtfConverter::TraverseMultiNodes(pNode, "", [this] (IXMLFileNodePtr objNode,const TXString& childNodeName) -> void
									  {
										  
										  GdtfRDMParameterValue* paramValPtr = nullptr;
										  
										  TXString nodeName;
										  objNode->GetNodeName(nodeName);
										  
										  if	  ( nodeName == XML_GDTF_RDMValue_UNSIGNED_BYTE)				{ paramValPtr = new GdtfRDMValue_UNSIGNED_BYTE(); }
										  else if (nodeName == XML_GDTF_RDMValue_SIGNED_BYTE)					{ paramValPtr = new GdtfRDMValue_SIGNED_BYTE(); }
										  else if (nodeName == XML_GDTF_RDMValue_UNSIGNED_WORD)					{ paramValPtr = new GdtfRDMValue_UNSIGNED_WORD(); }
										  else if (nodeName == XML_GDTF_RDMValue_SIGNED_WORD)					{ paramValPtr = new GdtfRDMValue_SIGNED_WORD(); }
										  else if (nodeName == XML_GDTF_RDMValue_UNSIGNED_DWORD)				{ paramValPtr = new GdtfRDMValue_SIGNED_DWORD(); }
										  else if (nodeName == XML_GDTF_RDMValue_SIGNED_DWORD)					{ paramValPtr = new GdtfRDMValue_UNSIGNED_DWORD(); }
										  else if (nodeName == XML_GDTF_RDMValue_ASCII)							{ paramValPtr = new GdtfRDMValue_ASCII(); }
										  else if (nodeName == XML_GDTF_RDMValueBool)							{ paramValPtr = new GdtfRDMValueBool(); }
										  else if (nodeName == XML_GDTF_RDMValue_DMX_PERSONALITY_DESCRIPTION)	{ paramValPtr = new GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION(); }
										  else if (nodeName == XML_GDTF_RDMValue_SLOT_INFO)						{ paramValPtr = new GdtfRDMValue_SLOT_INFO(); }
										  else if (nodeName == XML_GDTF_RDMValue_STATUS_ID_DESCRIPTION)			{ paramValPtr = new GdtfRDMValue_STATUS_ID_DESCRIPTION();  }
										  else																	{ DSTOP((kEveryone, "Unaspected Node in RDM Parameter"));}
										  
										  
										  if (paramValPtr)
										  {
											  paramValPtr->ReadFromNode(objNode);
											  fParameterValueArray.push_back(paramValPtr);
										  }
									  } );
}

void SceneData::GdtfRDMParameter::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMParam_AttrName);
	needed.push_back(XML_GDTF_RDMParam_AttrType);
	needed.push_back(XML_GDTF_RDMParam_AttrDataType);
	needed.push_back(XML_GDTF_RDMParam_AttrCommand);
	needed.push_back(XML_GDTF_RDMParam_AttrSensorUnit);
	needed.push_back(XML_GDTF_RDMParam_AttrSensorUnitPrefix);
	needed.push_back(XML_GDTF_RDMParam_AttrMinValue);
	needed.push_back(XML_GDTF_RDMParam_AttrMaxValue);
	needed.push_back(XML_GDTF_RDMParam_AttrPDLSize);
	needed.push_back(XML_GDTF_RDMParam_AttrDescription);
	optional.push_back(XML_GDTF_RDMParam_AttrPID);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMParameterValue::GdtfRDMParameterValue()
{
}

SceneData::GdtfRDMParameterValue::~GdtfRDMParameterValue()
{
}

SceneData::GdtfRDMValue_RealTimeClock::GdtfRDMValue_RealTimeClock()
{
	fYear = 0;
	fMonth = 0;
	fDay = 0;
	fHours = 0;
	fMinute = 0;
	fSecond = 0;
}

SceneData::GdtfRDMValue_RealTimeClock::GdtfRDMValue_RealTimeClock(Sint32 year, Sint32 month, Sint32 day, Sint32 hours, Sint32 minute, Sint32 second, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMValue_RealTimeClock()
{
	fYear     = year;
	fMonth    = month;
	fDay      = day;
	fHours    = hours;
	fMinute   = minute;
	fSecond   = second;
	fThresholdOperator = thresholdOperator;
}

SceneData::GdtfRDMValue_RealTimeClock::~GdtfRDMValue_RealTimeClock()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_RealTimeClock::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_REAL_TIME_CLOCK;
}

Sint32 SceneData::GdtfRDMValue_RealTimeClock::GetYear() const
{
	return fYear;
}

Sint32 SceneData::GdtfRDMValue_RealTimeClock::GetMonth() const
{
	return fMonth;
}

Sint32 SceneData::GdtfRDMValue_RealTimeClock::GetDay() const
{
	return fDay;
}

Sint32 SceneData::GdtfRDMValue_RealTimeClock::GetHours() const
{
	return fHours;
}

Sint32 SceneData::GdtfRDMValue_RealTimeClock::GetMinute() const
{
	return fMinute;
}

Sint32 SceneData::GdtfRDMValue_RealTimeClock::GetSecond() const
{
	return fSecond;
}

EGdtf_RDMValue_ThresholdOperator SceneData::GdtfRDMValue_RealTimeClock::GetThresholdOperator() const
{
	return fThresholdOperator;
}

void SceneData::GdtfRDMValue_RealTimeClock::SetYear(Sint32 val)
{
	fYear = val;
}

void SceneData::GdtfRDMValue_RealTimeClock::SetMonth(Sint32 val)
{
	fMonth = val;
}

void SceneData::GdtfRDMValue_RealTimeClock::SetDay(Sint32 val)
{
	fDay = val;
}

void SceneData::GdtfRDMValue_RealTimeClock::SetHours(Sint32 val)
{
	fHours = val;
}

void SceneData::GdtfRDMValue_RealTimeClock::SetMinute(Sint32 val)
{
	fMinute = val;
}

void SceneData::GdtfRDMValue_RealTimeClock::SetSecond(Sint32 val)
{
	fSecond = val;
}

void SceneData::GdtfRDMValue_RealTimeClock::SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator val)
{
	fThresholdOperator = fThresholdOperator;
}

TXString SceneData::GdtfRDMValue_RealTimeClock::GetNodeName()
{
	return XML_GDTF_RDMValue_REAL_TIME_CLOCK;
}

void SceneData::GdtfRDMValue_RealTimeClock::OnPrintToFile(IXMLFileNodePtr pNode)
{
	
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrYear, GdtfConverter::ConvertInteger(fYear));
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrMonth, GdtfConverter::ConvertInteger(fMonth));
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrDay, GdtfConverter::ConvertInteger(fDay));
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrHours, GdtfConverter::ConvertInteger(fHours));
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrMinute, GdtfConverter::ConvertInteger(fMinute));
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrSecond, GdtfConverter::ConvertInteger(fSecond));
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrThresholdOperator,
         GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum (fThresholdOperator));
}

void SceneData::GdtfRDMValue_RealTimeClock::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString yearStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrYear, yearStr);
	GdtfConverter::ConvertInteger(yearStr, fYear);
	
	TXString monthStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrMonth, monthStr);
	GdtfConverter::ConvertInteger(monthStr, fMonth);
	
	TXString dayStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrDay, dayStr);
	GdtfConverter::ConvertInteger(dayStr, fDay);
	
	TXString hourStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrHours, hourStr);
	GdtfConverter::ConvertInteger(hourStr, fHours);
	
	TXString minuteStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrMinute, minuteStr);
	GdtfConverter::ConvertInteger(minuteStr, fMinute);
	
	TXString secondStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrSecond, secondStr);
	GdtfConverter::ConvertInteger(secondStr, fSecond);
	
	TXString thresholdOperStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrThresholdOperator, thresholdOperStr);
	GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum(thresholdOperStr, fThresholdOperator);
}

void SceneData::GdtfRDMValue_RealTimeClock::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrYear);
	needed.push_back(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrMonth);
	needed.push_back(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrDay);
	needed.push_back(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrHours);
	needed.push_back(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrMinute);
	needed.push_back(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrSecond);
	needed.push_back(XML_GDTF_RDMValue_REAL_TIME_CLOCK_AttrThresholdOperator);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMSensorNotification::GdtfRDMSensorNotification()
{
	fSensorOffset = 0;
}

SceneData::GdtfRDMSensorNotification::GdtfRDMSensorNotification(Sint32 sensorOffset) : GdtfRDMSensorNotification()
{
	fSensorOffset = sensorOffset;
}

SceneData::GdtfRDMSensorNotification::~GdtfRDMSensorNotification()
{
	for (GdtfRDMValueSensor* ptr : fSensorValueArray) { delete ptr; }
}

EGdtfObjectType SceneData::GdtfRDMSensorNotification::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMSensorNotification;
}

Sint32 SceneData::GdtfRDMSensorNotification::GetSensorOffset() const
{
	return fSensorOffset;
}

TGdtfRDMValueSensorArray SceneData::GdtfRDMSensorNotification::GetSensorValueArray()
{
	return fSensorValueArray;
}

void SceneData::GdtfRDMSensorNotification::SetSensorOffset(Sint32 val)
{
}

GdtfRDMValueSensor* SceneData::GdtfRDMSensorNotification::AddValueSensor(Sint32 value, Sint32 lowest, Sint32 highest, Sint32 recorded, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
{
	GdtfRDMValueSensor* valueSensor = new GdtfRDMValueSensor(value, lowest, highest, recorded, thresholdOperator);
	
	fSensorValueArray.push_back(valueSensor);
	
	return valueSensor;
}


TXString SceneData::GdtfRDMSensorNotification::GetNodeName()
{
	return XML_GDTF_RDMSensorNotification;
}

void SceneData::GdtfRDMSensorNotification::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMSensorNotif_AttrSensorOffset, GdtfConverter::ConvertInteger(fSensorOffset) );
	
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfRDMValueSensor* sensorDefini : fSensorValueArray)
	{
		sensorDefini->WriteToNode(pNode);
	}
}

void SceneData::GdtfRDMSensorNotification::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString sensorOffStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMSensorNotif_AttrSensorOffset, sensorOffStr);
	GdtfConverter::ConvertInteger(sensorOffStr, fSensorOffset);
	
	// Read the childs
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_RDMValue_SENSOR_DEFINITION, [this](IXMLFileNodePtr objNode) -> void
								 {
									 GdtfRDMValueSensor* valueSensor = new GdtfRDMValueSensor();
									 
									 valueSensor->ReadFromNode(objNode);
									 
									 fSensorValueArray.push_back(valueSensor);
									 return;
								 });
}

void SceneData::GdtfRDMSensorNotification::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMSensorNotif_AttrSensorOffset);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMValueSensor::GdtfRDMValueSensor()
{
	fValue             = 0;
	fLowest            = 0;
	fHighest           = 0;
	fRecorded          = 0;
	fThresholdOperator = EGdtf_RDMValue_ThresholdOperator::IsNot;
}

SceneData::GdtfRDMValueSensor::GdtfRDMValueSensor(Sint32 value, Sint32 lowest, Sint32 highest, Sint32 recorded, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
{
	fValue    = value;
	fLowest   = lowest;
	fHighest  = highest;
	fRecorded = recorded ;
	fThresholdOperator = thresholdOperator;
}

SceneData::GdtfRDMValueSensor::~GdtfRDMValueSensor()
{
}

EGdtfObjectType SceneData::GdtfRDMValueSensor::GetObjectType()
{
	return EGdtfObjectType::eGdtfValueSensor;
}

Sint32 SceneData::GdtfRDMValueSensor::GetValue() const
{
	return fValue;
}

Sint32 SceneData::GdtfRDMValueSensor::GetLowest() const
{
	return fLowest;
}

Sint32 SceneData::GdtfRDMValueSensor::GetHighest() const
{
	return fHighest;
}

Sint32 SceneData::GdtfRDMValueSensor::GetRecorded() const
{
	return fRecorded;
}

EGdtf_RDMValue_ThresholdOperator SceneData::GdtfRDMValueSensor::GetThresholdOperator() const
{
	return fThresholdOperator;
}

void SceneData::GdtfRDMValueSensor::SetValue(Sint32 val)
{
	fValue = val;
}

void SceneData::GdtfRDMValueSensor::SetLowest(Sint32 val)
{
	fLowest = val;
}

void SceneData::GdtfRDMValueSensor::SetHighest(Sint32 val)
{
	fHighest = val;
}

void SceneData::GdtfRDMValueSensor::SetRecorded(Sint32 val)
{
	fRecorded = val;
}

void SceneData::GdtfRDMValueSensor::SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator val)
{
	fThresholdOperator = val;
}

TXString SceneData::GdtfRDMValueSensor::GetNodeName()
{
	return XML_GDTF_RDMValueSensor;
}

void SceneData::GdtfRDMValueSensor::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValueSensorAttrValue, GdtfConverter::ConvertInteger (fValue) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValueSensor_AttrLowest, GdtfConverter::ConvertInteger (fLowest) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValueSensor_AttrHighest, GdtfConverter::ConvertInteger (fHighest) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValueSensor_AttrRecorded, GdtfConverter::ConvertInteger (fRecorded) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValueSensor_AttrThresholdOperator,
         GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum (fThresholdOperator) );
}

void SceneData::GdtfRDMValueSensor::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString valueStr;  pNode->GetNodeAttributeValue(XML_GDTF_RDMValueSensorAttrValue, valueStr);
	GdtfConverter::ConvertInteger(valueStr, fValue);
	
	TXString lowestStr;  pNode->GetNodeAttributeValue(XML_GDTF_RDMValueSensor_AttrLowest, lowestStr);
	GdtfConverter::ConvertInteger(lowestStr, fLowest);
	
	TXString highestStr;  pNode->GetNodeAttributeValue(XML_GDTF_RDMValueSensor_AttrHighest, highestStr);
	GdtfConverter::ConvertInteger(highestStr, fHighest);
	
	TXString recoredStr;  pNode->GetNodeAttributeValue(XML_GDTF_RDMValueSensor_AttrRecorded, recoredStr);
	GdtfConverter::ConvertInteger(recoredStr, fRecorded);
	
	TXString thresholdOperStr;  pNode->GetNodeAttributeValue(XML_GDTF_RDMValueSensor_AttrThresholdOperator, thresholdOperStr);
	GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum(thresholdOperStr, fThresholdOperator);
}

void SceneData::GdtfRDMValueSensor::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMValueSensorAttrValue);
	needed.push_back(XML_GDTF_RDMValueSensor_AttrLowest);
	needed.push_back(XML_GDTF_RDMValueSensor_AttrHighest);
	needed.push_back(XML_GDTF_RDMValueSensor_AttrRecorded);
	needed.push_back(XML_GDTF_RDMValueSensor_AttrThresholdOperator);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMAbsentNotification::GdtfRDMAbsentNotification()
{
}

SceneData::GdtfRDMAbsentNotification::~GdtfRDMAbsentNotification()
{
}

EGdtfObjectType SceneData::GdtfRDMAbsentNotification::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMNotification;
}

TXString SceneData::GdtfRDMAbsentNotification::GetNodeName()
{
	return XML_GDTF_RDMNotification;
}

SceneData::GdtfRDMParameterNotification::GdtfRDMParameterNotification()
{
}

SceneData::GdtfRDMParameterNotification::GdtfRDMParameterNotification(Sint32 PID)
{
	fPID = PID;
}

SceneData::GdtfRDMParameterNotification::~GdtfRDMParameterNotification()
{
	for (GdtfRDMParameterValuePtr ptr : fParameterValueArray) { delete ptr; }
}

EGdtfObjectType SceneData::GdtfRDMParameterNotification::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMParameterNotification;
}

Sint32 SceneData::GdtfRDMParameterNotification::GetPID() const
{
	return fPID;
}

TGdtfRDMParameterValueArray SceneData::GdtfRDMParameterNotification::GetParameterValueArray() const
{
	return fParameterValueArray;
}

void SceneData::GdtfRDMParameterNotification::SetPID(Sint32 val)
{
	fPID = val;
}

GdtfRDMParameterValue* SceneData::GdtfRDMParameterNotification::AddRMDValueBool()
{
	GdtfRDMParameterValuePtr value = new GdtfRDMValueBool();
	
	fParameterValueArray.push_back(value);
	
	return value;
}

GdtfRDMParameterValue* SceneData::GdtfRDMParameterNotification::AddRealTimeClock()
{
	GdtfRDMParameterValue* value = new GdtfRDMValue_RealTimeClock();
	
	fParameterValueArray.push_back(value);
	
	return value;
}

TXString SceneData::GdtfRDMParameterNotification::GetNodeName()
{
	return XML_GDTF_RDMParamNotification;
}

void SceneData::GdtfRDMParameterNotification::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMParamNotification_AttrPID, GdtfConverter::ConvertInteger(fPID) );
	
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfRDMParameterValue* paramValue : fParameterValueArray)
	{
		paramValue->WriteToNode(pNode);
	}
}

void SceneData::GdtfRDMParameterNotification::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString pidStr;  pNode->GetNodeAttributeValue(XML_GDTF_RDMParamNotification_AttrPID, pidStr);
	GdtfConverter::ConvertInteger(pidStr, fPID);
	
	// Read the childs
	GdtfConverter::TraverseMultiNodes(pNode, "", [this] (IXMLFileNodePtr objNode,const TXString& childNodeName) -> void
									  {
										  GdtfRDMParameterValue* paramValPtr = nullptr;
										  
										  TXString nodeName;
										  objNode->GetNodeName(nodeName);
										  
										  if	  ( nodeName == XML_GDTF_RDMValue_UNSIGNED_BYTE)	{ paramValPtr = new GdtfRDMValue_UNSIGNED_BYTE(); }
										  else if (nodeName == XML_GDTF_RDMValue_SIGNED_BYTE)		{ paramValPtr = new GdtfRDMValue_SIGNED_BYTE(); }
										  else if (nodeName == XML_GDTF_RDMValue_UNSIGNED_WORD)		{ paramValPtr = new GdtfRDMValue_UNSIGNED_WORD(); }
										  else if (nodeName == XML_GDTF_RDMValue_SIGNED_WORD)		{ paramValPtr = new GdtfRDMValue_SIGNED_WORD(); }
										  else if (nodeName == XML_GDTF_RDMValue_UNSIGNED_DWORD)	{ paramValPtr = new GdtfRDMValue_SIGNED_DWORD(); }
										  else if (nodeName == XML_GDTF_RDMValue_SIGNED_DWORD)		{ paramValPtr = new GdtfRDMValue_UNSIGNED_DWORD(); }
										  else if (nodeName == XML_GDTF_RDMValueBool)				{ paramValPtr = new GdtfRDMValueBool(); }
										  else if (nodeName == XML_GDTF_RDMValue_REAL_TIME_CLOCK)	{ paramValPtr= new GdtfRDMValue_RealTimeClock(); }

										  if (paramValPtr)
										  {
											  paramValPtr->ReadFromNode(objNode);
											  fParameterValueArray.push_back(paramValPtr);
										  }
										  
										  return;
									  } );
}

void SceneData::GdtfRDMParameterNotification::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMParamNotification_AttrPID);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMValueBool::GdtfRDMValueBool()
{
	fValue				= EGdtf_RDMValueBool_Value::eNo;
	fThresholdOperator	= EGdtf_RDMValue_ThresholdOperator::Is;
}

SceneData::GdtfRDMValueBool::GdtfRDMValueBool(EGdtf_RDMValueBool_Value value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMValueBool()
{
	fValue = value;
	fThresholdOperator = thresholdOperator;
}

SceneData::GdtfRDMValueBool::~GdtfRDMValueBool()
{
}

EGdtfObjectType SceneData::GdtfRDMValueBool::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValueBool;
}

EGdtf_RDMValueBool_Value SceneData::GdtfRDMValueBool::GetValue() const
{
	return fValue;
}

EGdtf_RDMValue_ThresholdOperator SceneData::GdtfRDMValueBool::GetThresholdOperator() const
{
	return fThresholdOperator;
}

void SceneData::GdtfRDMValueBool::SetValue(EGdtf_RDMValueBool_Value value)
{
	fValue = value;
}

void SceneData::GdtfRDMValueBool::SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator value)
{
	fThresholdOperator = value;
}

TXString SceneData::GdtfRDMValueBool::GetNodeName()
{
	return XML_GDTF_RDMValueBool;
}

void SceneData::GdtfRDMValueBool::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValueBool_AttrValue, GdtfConverter::ConvertEGdtf_RDMValueBool_ValueEnum(fValue) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValueBool_AttrThresholdOperator,
								 GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum(fThresholdOperator));
}

void SceneData::GdtfRDMValueBool::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString valueStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValueBool_AttrValue, valueStr);
	GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum(valueStr, fThresholdOperator);
	
	TXString thresHoldOpStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValueBool_AttrThresholdOperator, thresHoldOpStr);
	GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum(thresHoldOpStr, fThresholdOperator);
}

void SceneData::GdtfRDMValueBool::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMValueBool_AttrValue);
	needed.push_back(XML_GDTF_RDMValueBool_AttrThresholdOperator);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMNotifications::GdtfRDMNotifications()
{
	fRDMAbsentNotification = nullptr;
}

SceneData::GdtfRDMNotifications::~GdtfRDMNotifications()
{
	if (fRDMAbsentNotification) { delete fRDMAbsentNotification; }
	
	for (GdtfRDMParameterNotificationPtr ptr : fRDMParamNotificationArray) { delete ptr; }
	for (GdtfRDMSensorNotificationPtr ptr : fRDMSensorNotificationArray)   { delete ptr; }
}

GdtfRDMAbsentNotification* SceneData::GdtfRDMNotifications::GetAbsentNotification() const
{
	return fRDMAbsentNotification;
}

TGdtfRDMParameterNotificationArray SceneData::GdtfRDMNotifications::GetParameterNotificationArray() const
{
	return fRDMParamNotificationArray;
}

TGdtfRDMSensorNotificationArray SceneData::GdtfRDMNotifications::GetSensorNotificationArray() const
{
	return fRDMSensorNotificationArray;
}

void SceneData::GdtfRDMNotifications::SetAbsentNotification(GdtfRDMAbsentNotification * val)
{
	fRDMAbsentNotification = val;
}

GdtfRDMParameterNotification* SceneData::GdtfRDMNotifications::AddRDMParameterNotification(Sint32 PID)
{
	GdtfRDMParameterNotification* paramNotification = new GdtfRDMParameterNotification(PID);
	
	fRDMParamNotificationArray.push_back(paramNotification);
	
	return paramNotification;
}

GdtfRDMSensorNotification* SceneData::GdtfRDMNotifications::AddDMSensorNotification(Sint32 sensorOffset)
{
	GdtfRDMSensorNotification* sensorNotif = new GdtfRDMSensorNotification(sensorOffset);
	
	fRDMSensorNotificationArray.push_back(sensorNotif);
	
	return sensorNotif;
}

EGdtfObjectType SceneData::GdtfRDMNotifications::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMNotifications;
}

TXString SceneData::GdtfRDMNotifications::GetNodeName()
{
	return XML_GDTF_RDMNotifications;
}

void SceneData::GdtfRDMNotifications::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	//------------------------------------------------------------------------------------
	// Print the attributes
	fRDMAbsentNotification->WriteToNode(pNode);
	//------------------------------------------------------------------------------------
	// Print the childs
	for (GdtfRDMParameterNotificationPtr feature : fRDMParamNotificationArray)
	{
		feature->WriteToNode(pNode);
	}
	
	for (GdtfRDMSensorNotificationPtr feature : fRDMSensorNotificationArray)
	{
		feature->WriteToNode(pNode);
	}
}

void SceneData::GdtfRDMNotifications::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	// -
	// Read the childs
	IXMLFileNode* rdmAbsentNotifNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_FTRDM, &rdmAbsentNotifNode)))
	{
		fRDMAbsentNotification = new GdtfRDMAbsentNotification();
		fRDMAbsentNotification->ReadFromNode(rdmAbsentNotifNode);
	}
	
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_RDMParamNotification, [this](IXMLFileNodePtr objNode) -> void
								 {
									 GdtfRDMParameterNotificationPtr paramNotif = new GdtfRDMParameterNotification ();
									 
									 paramNotif->ReadFromNode(objNode);
									 
									 fRDMParamNotificationArray.push_back(paramNotif);
									 return;
								 });
	
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_RDMSensorNotification, [this](IXMLFileNodePtr objNode) -> void
								 {
									 GdtfRDMSensorNotificationPtr sensorNotif = new GdtfRDMSensorNotification();
									 
									 sensorNotif->ReadFromNode(objNode);
									 
									 fRDMSensorNotificationArray.push_back(sensorNotif);
									 return;
								 });
}

void SceneData::GdtfRDMNotifications::OnErrorCheck(const IXMLFileNodePtr& pNode)
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
	
	IXMLFileNode* ftrdmNode;
	if (VCOM_SUCCEEDED( pNode->GetChildNode(XML_GDTF_FTRDM, &ftrdmNode)) )
	{
		fRDM = new GdtfFTRDM();
		fRDM->ReadFromNode(ftrdmNode);
	}
	
	IXMLFileNode* artNetNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_ArtNet, &artNetNode)))
	{
		fArtNet = new GdtfArtNet();
		fArtNet->ReadFromNode(artNetNode);
	}
	
	IXMLFileNode* sAcnNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_sACN, &sAcnNode)))
	{
		fsACN = new GdtfsAcn();
		fsACN->ReadFromNode(sAcnNode);
	}
	
	IXMLFileNode* kinetNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_KiNET, &kinetNode)))
	{
		fKiNET = new GdtfKiNET();
		fKiNET->ReadFromNode(kinetNode);
	}
	
	IXMLFileNode* posiStageNetNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_PosiStageNet, &posiStageNetNode)))
	{
		fPosiStageNet = new GdtfPosiStageNet();
		fPosiStageNet->ReadFromNode(posiStageNetNode);
	}
	
	IXMLFileNode* openSoundControlNode;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_OpenSoundControl, &openSoundControlNode)))
	{
		fOpenSoundControl = new GdtfOpenSoundControl();
		fOpenSoundControl->ReadFromNode(openSoundControlNode);
	}
	
	IXMLFileNode* ctipNode;
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

SceneData::GdtfRDMParameterValue_Numeric::GdtfRDMParameterValue_Numeric()
{
	fThresholdOperator = EGdtf_RDMValue_ThresholdOperator::Is;
	fValue = 0;
}

SceneData::GdtfRDMParameterValue_Numeric::GdtfRDMParameterValue_Numeric(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMParameterValue_Numeric()
{
	fValue = value;
	fThresholdOperator = thresholdOperator;
}

SceneData::GdtfRDMParameterValue_Numeric::~GdtfRDMParameterValue_Numeric()
{
}

Sint32 SceneData::GdtfRDMParameterValue_Numeric::GetValue() const
{
	return fValue;
}

EGdtf_RDMValue_ThresholdOperator SceneData::GdtfRDMParameterValue_Numeric::GetThresholdOperator() const
{
	return fThresholdOperator;
}

void SceneData::GdtfRDMParameterValue_Numeric::SetValue(Sint32 value)
{
	fValue = value;
}

void SceneData::GdtfRDMParameterValue_Numeric::SetThresholdOperator(EGdtf_RDMValue_ThresholdOperator value)
{
	fThresholdOperator = value;
}

void SceneData::GdtfRDMParameterValue_Numeric::OnPrintToFile(IXMLFileNodePtr pNode)
{
	
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_Numeric_AttrValue, GdtfConverter::ConvertInteger(fValue) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_Numeric_AttrThresholdOperator,
         GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum (fThresholdOperator));
}

void SceneData::GdtfRDMParameterValue_Numeric::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);

	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString valueStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_Numeric_AttrValue, valueStr);
	GdtfConverter::ConvertInteger(valueStr, fValue);
	
	TXString thresholdOperatorStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_Numeric_AttrThresholdOperator, thresholdOperatorStr);
	GdtfConverter::ConvertEGdtf_RDMValue_ThresholdOperatorEnum(thresholdOperatorStr, fThresholdOperator);
}

void SceneData::GdtfRDMParameterValue_Numeric::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMValue_Numeric_AttrValue);
	needed.push_back(XML_GDTF_RDMValue_Numeric_AttrThresholdOperator);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMValue_UNSIGNED_BYTE::GdtfRDMValue_UNSIGNED_BYTE()
{
}

SceneData::GdtfRDMValue_UNSIGNED_BYTE::GdtfRDMValue_UNSIGNED_BYTE(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMParameterValue_Numeric(value, thresholdOperator)
{
}

SceneData::GdtfRDMValue_UNSIGNED_BYTE::~GdtfRDMValue_UNSIGNED_BYTE()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_UNSIGNED_BYTE::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_UNSIGNED_BYTE;
}

TXString SceneData::GdtfRDMValue_UNSIGNED_BYTE::GetNodeName()
{
	return XML_GDTF_RDMValue_UNSIGNED_BYTE;
}

SceneData::GdtfRDMValue_SIGNED_BYTE::GdtfRDMValue_SIGNED_BYTE()
{
}

SceneData::GdtfRDMValue_SIGNED_BYTE::GdtfRDMValue_SIGNED_BYTE(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMParameterValue_Numeric(value, thresholdOperator)
{
}

SceneData::GdtfRDMValue_SIGNED_BYTE::~GdtfRDMValue_SIGNED_BYTE()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_SIGNED_BYTE::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_SIGNED_BYTE;
}

TXString SceneData::GdtfRDMValue_SIGNED_BYTE::GetNodeName()
{
	return XML_GDTF_RDMValue_UNSIGNED_BYTE;
}

SceneData::GdtfRDMValue_UNSIGNED_WORD::GdtfRDMValue_UNSIGNED_WORD()
{
}

SceneData::GdtfRDMValue_UNSIGNED_WORD::GdtfRDMValue_UNSIGNED_WORD(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMParameterValue_Numeric(value, thresholdOperator)
{
}

SceneData::GdtfRDMValue_UNSIGNED_WORD::~GdtfRDMValue_UNSIGNED_WORD()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_UNSIGNED_WORD::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_UNSIGNED_WORD;
}

TXString SceneData::GdtfRDMValue_UNSIGNED_WORD::GetNodeName()
{
	return XML_GDTF_RDMValue_UNSIGNED_WORD;
}

SceneData::GdtfRDMValue_SIGNED_WORD::GdtfRDMValue_SIGNED_WORD()
{
}

SceneData::GdtfRDMValue_SIGNED_WORD::GdtfRDMValue_SIGNED_WORD(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMParameterValue_Numeric(value, thresholdOperator)
{
}

SceneData::GdtfRDMValue_SIGNED_WORD::~GdtfRDMValue_SIGNED_WORD()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_SIGNED_WORD::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_SIGNED_WORD;
}

TXString SceneData::GdtfRDMValue_SIGNED_WORD::GetNodeName()
{
	return XML_GDTF_RDMValue_SIGNED_WORD;
}

SceneData::GdtfRDMValue_UNSIGNED_DWORD::GdtfRDMValue_UNSIGNED_DWORD()
{
}

SceneData::GdtfRDMValue_UNSIGNED_DWORD::GdtfRDMValue_UNSIGNED_DWORD(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMParameterValue_Numeric(value, thresholdOperator)
{
}

SceneData::GdtfRDMValue_UNSIGNED_DWORD::~GdtfRDMValue_UNSIGNED_DWORD()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_UNSIGNED_DWORD::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_UNSIGNED_DWORD;
}

TXString SceneData::GdtfRDMValue_UNSIGNED_DWORD::GetNodeName()
{
	return XML_GDTF_RDMValue_UNSIGNED_DWORD;
}


SceneData::GdtfRDMValue_SIGNED_DWORD::GdtfRDMValue_SIGNED_DWORD()
{
}

SceneData::GdtfRDMValue_SIGNED_DWORD::GdtfRDMValue_SIGNED_DWORD(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMParameterValue_Numeric(value, thresholdOperator)
{
}

SceneData::GdtfRDMValue_SIGNED_DWORD::~GdtfRDMValue_SIGNED_DWORD()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_SIGNED_DWORD::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_SIGNED_DWORD;
}

TXString SceneData::GdtfRDMValue_SIGNED_DWORD::GetNodeName()
{
	return XML_GDTF_RDMValue_SIGNED_DWORD;
}

SceneData::GdtfRDMValue_ASCII::GdtfRDMValue_ASCII()
{
}

SceneData::GdtfRDMValue_ASCII::GdtfRDMValue_ASCII(Sint32 value, EGdtf_RDMValue_ThresholdOperator thresholdOperator)
: GdtfRDMParameterValue_Numeric(value, thresholdOperator)
{
}

SceneData::GdtfRDMValue_ASCII::~GdtfRDMValue_ASCII()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_ASCII::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_ASCII;
}

TXString SceneData::GdtfRDMValue_ASCII::GetNodeName()
{
	return XML_GDTF_RDMValue_ASCII;
}

SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION()
{
	fFootPrint = 0;
	fDescription = "";
}

SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION(Sint32 footPrint, TXString& description)
: GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION()
{
	fFootPrint = footPrint;
	fDescription = description;
}

SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::~GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION()
{
}

EGdtfObjectType SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION;
}

Sint32 SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::GetFootPrint() const
{
	return fFootPrint;
}

const TXString & SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::GetDescription() const
{
	return fDescription;
}

void SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::SetFootPrint(Sint32 val)
{
	fFootPrint = val;
}

void SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::SetDescription(const TXString & val)
{
	fDescription = val;
}

TXString SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::GetNodeName()
{
	return XML_GDTF_RDMValue_DMX_PERSONALITY_DESCRIPTION;
}

void SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_DMX_PERSON_DESC_AttrFootPrint,   GdtfConverter::ConvertInteger(fFootPrint) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_DMX_PERSON_DESC_AttrDescription, fDescription);
}

void SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString footPrintStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_DMX_PERSON_DESC_AttrFootPrint, footPrintStr);
	GdtfConverter::ConvertInteger(footPrintStr, fFootPrint);
	
	pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_DMX_PERSON_DESC_AttrDescription, fDescription);
}

void SceneData::GdtfGdtfRDMValue_DMX_PERSONALITY_DESCRIPTION::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMValue_DMX_PERSON_DESC_AttrFootPrint);
	needed.push_back(XML_GDTF_RDMValue_DMX_PERSON_DESC_AttrDescription);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMValue_SENSOR_DEFINITION::GdtfRDMValue_SENSOR_DEFINITION()
{
	fRangeMinValue  = 0;
	fRangeMaxValue  = 0;
	fNormalMinValue = 0;
	fNormalMaxValue = 0;
		
	fType   = EGdtf_RDMValue_SENSOR_DEFINITION_TYPE::SEND_TEMPERATURE;
	fUnit   = EGdtf_RDMParam_SensorUnit::UNITS_NONE;
	fPrefix = EGdtf_RDMParam_SensorUnitPrefix::PREFIX_NONE;
	
	fLowesHighestDetectionSupported = EGdtf_RDMValue_LowesHighestDetectionSupported::eNO;
	fRecordValueSupported           = EGdtf_RDMValue_RecordValueSupported::eNO;
	
	fDescription = "";
}

SceneData::GdtfRDMValue_SENSOR_DEFINITION::GdtfRDMValue_SENSOR_DEFINITION(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE type, EGdtf_RDMParam_SensorUnit unit, EGdtf_RDMParam_SensorUnitPrefix prefix, Sint32 rangeMinValue, Sint32 rangeMaxValue, Sint32 normalMinValue, Sint32 normalMaxValue, EGdtf_RDMValue_LowesHighestDetectionSupported lowesHighestDetectionSupported, EGdtf_RDMValue_RecordValueSupported recordValueSupported, TXString & description)
{
	fType                           = type;
	fUnit                           = unit;
	fPrefix                         = prefix;
	fRangeMinValue                  = rangeMinValue;
	fRangeMaxValue                  = rangeMaxValue;
	fNormalMinValue                 = normalMinValue;
	fNormalMaxValue                 = normalMaxValue;
	fLowesHighestDetectionSupported = lowesHighestDetectionSupported;
	fRecordValueSupported           = recordValueSupported;
	fDescription                    = description;
}

SceneData::GdtfRDMValue_SENSOR_DEFINITION::~GdtfRDMValue_SENSOR_DEFINITION()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetObjectType()
{
	return EGdtfObjectType::eRDMValue_SENSOR_DEFINITION;
}

EGdtf_RDMValue_SENSOR_DEFINITION_TYPE SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetType() const
{
	return fType;
}

EGdtf_RDMParam_SensorUnit SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetUnit() const
{
	return fUnit;
}

EGdtf_RDMParam_SensorUnitPrefix SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetPrefix() const
{
	return fPrefix;
}

Sint32 SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetRangeMinValue() const
{
	return fRangeMinValue;
}

Sint32 SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetRangeMaxValue() const
{
	return fRangeMaxValue;
}

Sint32 SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetNormalMinValue() const
{
	return fNormalMinValue;
}

Sint32 SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetNormalMaxValueype() const // TODO: rename -ype
{
	return fNormalMaxValue;
}

EGdtf_RDMValue_LowesHighestDetectionSupported SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetLowesHighestDetectionSupported() const
{
	return fLowesHighestDetectionSupported;
}

EGdtf_RDMValue_RecordValueSupported SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetRecordValueSupported() const
{
	return fRecordValueSupported;
}

const TXString & SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetDescription() const
{
	return fDescription;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetType(EGdtf_RDMValue_SENSOR_DEFINITION_TYPE val)
{
	fType = val;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetUnit(EGdtf_RDMParam_SensorUnit val)
{
	fUnit = val;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetPrefix(EGdtf_RDMParam_SensorUnitPrefix val)
{
	fPrefix = val;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetRangeMinValue(Sint32 val)
{
	fRangeMinValue = val;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetDescription(const TXString & val)
{
	fDescription = val;
}

TXString SceneData::GdtfRDMValue_SENSOR_DEFINITION::GetNodeName()
{
	return XML_GDTF_RDMValue_SENSOR_DEFINITION;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrType, GdtfConverter::ConvertRDMValue_SENSOR_DEFINITION_TypeEnum(fType) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrUnit, GdtfConverter::Convert_RDMParam_SensorUnitEnum(fUnit) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrPrefix, GdtfConverter::Convert_RDMParam_SensorUnitPrefixEnum(fPrefix) );
	
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRangeMinValue,  GdtfConverter::ConvertInteger(fRangeMinValue) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRangeMaxValue,  GdtfConverter::ConvertInteger(fRangeMaxValue) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrNormalMinValue, GdtfConverter::ConvertInteger(fNormalMinValue) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrNormalMaxValue, GdtfConverter::ConvertInteger(fNormalMaxValue) );
	
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrLowesHighestDetectionSupported,
								 GdtfConverter::Convert_RDMValue_LowesHighestDetectionSupportedEnum (fLowesHighestDetectionSupported) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRecordValueSupported,
								 GdtfConverter::Convert_RDMValue_RecordValueSupportedEnum (fRecordValueSupported) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_Attr_Description, fDescription);
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString TypeStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrType, TypeStr);
	GdtfConverter::ConvertRDMValue_SENSOR_DEFINITION_TypeEnum(TypeStr, fType);
	
	TXString UnitStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrUnit, UnitStr);
	GdtfConverter::Convert_RDMParam_SensorUnitEnum (UnitStr, fUnit);
	
	TXString PrefixStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrPrefix, PrefixStr);
	GdtfConverter::Convert_RDMParam_SensorUnitPrefixEnum(PrefixStr, fPrefix);
	
	TXString RangeMinValueStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRangeMinValue, RangeMinValueStr);
	GdtfConverter::ConvertInteger(RangeMinValueStr, fRangeMinValue);
	
	TXString RangeMaxValueStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRangeMaxValue, RangeMaxValueStr);
	GdtfConverter::ConvertInteger(RangeMaxValueStr, fRangeMaxValue);
	
	TXString NormalMinValueStr;pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrNormalMinValue, NormalMinValueStr);
	GdtfConverter::ConvertInteger(NormalMinValueStr, fNormalMinValue);
	
	TXString NormalMaxValueStr;pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrNormalMaxValue, NormalMaxValueStr);
	GdtfConverter::ConvertInteger(NormalMaxValueStr, fNormalMaxValue);
	
	TXString LowesHighestDetectionSupportedStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrLowesHighestDetectionSupported, LowesHighestDetectionSupportedStr);
	GdtfConverter::Convert_RDMValue_LowesHighestDetectionSupportedEnum(LowesHighestDetectionSupportedStr, fLowesHighestDetectionSupported);
	
	TXString RecordValueSupportedStr;pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRecordValueSupported, RecordValueSupportedStr);
	GdtfConverter::Convert_RDMValue_RecordValueSupportedEnum(RecordValueSupportedStr, fRecordValueSupported);
	
	pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SENSOR_DEFINITION_Attr_Description, fDescription);
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrType);
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrUnit);
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrPrefix);
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRangeMinValue);
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRangeMaxValue);
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrNormalMinValue);
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrNormalMaxValue);
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrLowesHighestDetectionSupported);
	needed.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_AttrRecordValueSupported);
	optional.push_back(XML_GDTF_RDMValue_SENSOR_DEFINITION_Attr_Description);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetRangeMaxValue(Sint32 val)
{
	fRangeMaxValue = val;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetNormalMinValue(Sint32 val)
{
	fNormalMinValue = val;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetNormalMaxValueype(Sint32 val)
{
	fNormalMaxValue = val;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetLowesHighestDetectionSupported(EGdtf_RDMValue_LowesHighestDetectionSupported val)
{
	fLowesHighestDetectionSupported = val;
}

void SceneData::GdtfRDMValue_SENSOR_DEFINITION::SetRecordValueSupported(EGdtf_RDMValue_RecordValueSupported val)
{
	fRecordValueSupported = val;
}

SceneData::GdtfRDMValue_SLOT_INFO::GdtfRDMValue_SLOT_INFO()
{
	fOffset			= 0;
	fType			= EGdtf_RDMValue_SLOT_INFO_Type::ST_PRIMARY;
	fSlotLabelID	= EGdtf_RDMValue_SLOT_INFO_SlotLabelID::SD_BARN_DOOR;
}

SceneData::GdtfRDMValue_SLOT_INFO::GdtfRDMValue_SLOT_INFO(Sint32 offset, EGdtf_RDMValue_SLOT_INFO_Type type, EGdtf_RDMValue_SLOT_INFO_SlotLabelID slotLabelID)
: GdtfRDMValue_SLOT_INFO()
{
	fOffset			= offset;
	fType			= type;
	fSlotLabelID	= slotLabelID;
}

SceneData::GdtfRDMValue_SLOT_INFO::~GdtfRDMValue_SLOT_INFO()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_SLOT_INFO::GetObjectType()
{
	return EGdtfObjectType::eGdtfRDMValue_SLOT_INFO;
}

Sint32 SceneData::GdtfRDMValue_SLOT_INFO::GetOffset() const
{
	return fOffset;
}

EGdtf_RDMValue_SLOT_INFO_Type SceneData::GdtfRDMValue_SLOT_INFO::GetType() const
{
	return fType;
}

EGdtf_RDMValue_SLOT_INFO_SlotLabelID SceneData::GdtfRDMValue_SLOT_INFO::GetSlotLabelID() const
{
	return fSlotLabelID;
}

void SceneData::GdtfRDMValue_SLOT_INFO::SetOffset(Sint32 val)
{
	fOffset = val;
}

void SceneData::GdtfRDMValue_SLOT_INFO::SetType(EGdtf_RDMValue_SLOT_INFO_Type val)
{
	fType = val;
}

void SceneData::GdtfRDMValue_SLOT_INFO::SetSlotLabelID(EGdtf_RDMValue_SLOT_INFO_SlotLabelID val)
{
	fSlotLabelID = val;
}

TXString SceneData::GdtfRDMValue_SLOT_INFO::GetNodeName()
{
	return XML_GDTF_RDMValue_SLOT_INFO;
}

void SceneData::GdtfRDMValue_SLOT_INFO::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SLOT_INFO_AttrOffset,
         GdtfConverter::ConvertInteger(fOffset));
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SLOT_INFO_AttrType,
         GdtfConverter::ConvertRDMValue_SLOT_INFO_TypeEnum(fType) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_SLOT_INFO_AttrSlotLabelID,
         GdtfConverter::ConvertRDMValue_SLOT_INFO_SlotLabelIDEnum (fSlotLabelID) );
}

void SceneData::GdtfRDMValue_SLOT_INFO::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString offStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SLOT_INFO_AttrOffset, offStr);
	GdtfConverter::ConvertInteger(offStr, fOffset);
	
	TXString typeStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SLOT_INFO_AttrType, typeStr);
	GdtfConverter::ConvertRDMValue_SLOT_INFO_TypeEnum(typeStr, fType);
	
	TXString slotLabelIDStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_SLOT_INFO_AttrSlotLabelID, slotLabelIDStr);
	GdtfConverter::ConvertRDMValue_SLOT_INFO_SlotLabelIDEnum (slotLabelIDStr, fSlotLabelID);
}

void SceneData::GdtfRDMValue_SLOT_INFO::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMValue_SLOT_INFO_AttrOffset);
	needed.push_back(XML_GDTF_RDMValue_SLOT_INFO_AttrType);
	needed.push_back(XML_GDTF_RDMValue_SLOT_INFO_AttrSlotLabelID);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::GdtfRDMValue_STATUS_ID_DESCRIPTION()
{
	fStatusID    = 0;
	fDescription = "";
}

SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::GdtfRDMValue_STATUS_ID_DESCRIPTION(Sint32 statusID, const TXString& description)
{
	fStatusID = statusID;
	fDescription = description;
}

SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::~GdtfRDMValue_STATUS_ID_DESCRIPTION()
{
}

EGdtfObjectType SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::GetObjectType()
{
	return EGdtfObjectType::eRDMValue_STATUS_ID_DESCRIPTION;
}

StatusID SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::GetStatusID() const
{
	return fStatusID;
}

const TXString & SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::GetDescription() const
{
	return fDescription;
}

void SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::SetStatusID(StatusID val)
{
	fStatusID = val;
}

void SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::SetDescription(const TXString & val)
{
	fDescription = val;
}

TXString SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::GetNodeName()
{
	return XML_GDTF_RDMValue_STATUS_ID_DESCRIPTION;
}

void SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_STATUS_ID_DESCRIPTION_AttrStatusID, GdtfConverter::ConvertInteger(fStatusID) );
	pNode->SetNodeAttributeValue(XML_GDTF_RDMValue_STATUS_ID_DESCRIPTION_AttrDescription, fDescription);
}

void SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	//------------------------------------------------------------------------------------
	// Get the attributes
	TXString statusIDStr; pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_STATUS_ID_DESCRIPTION_AttrStatusID, statusIDStr);
	GdtfConverter::ConvertInteger(statusIDStr, fStatusID);
	
	pNode->GetNodeAttributeValue(XML_GDTF_RDMValue_STATUS_ID_DESCRIPTION_AttrDescription, fDescription);
}

void SceneData::GdtfRDMValue_STATUS_ID_DESCRIPTION::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_RDMValue_STATUS_ID_DESCRIPTION_AttrStatusID);
	needed.push_back(XML_GDTF_RDMValue_STATUS_ID_DESCRIPTION_AttrDescription);

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
	GdtfConverter::ConvertInteger(durationStr, fDuration);
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
	GdtfConverter::ConvertInteger(durationStr, fDuration);
	TXString fadeStr;     pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrFade, fadeStr);
	GdtfConverter::ConvertDouble(fadeStr, fFade);
	TXString delayStr;    pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrDelay, delayStr);
	GdtfConverter::ConvertDouble(delayStr, fDelay);
	
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
	if(fChannelFunctionRef == nullptr) { GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedChannelFunctionRef,pNode); SceneData::GdtfFixture::AddError(error); }
	if(fChannelFunctionRef)
	{
		fChannelFunctionRef->GetParentDMXChannel()->GetChannelBitResolution();
	}
	
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
	if(fChannelFunctionRef == nullptr) 
	{ 
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureUnresolvedChannelFunctionRef, pNode); 
		SceneData::GdtfFixture::AddError(error); 
	}
	if(fChannelFunctionRef)
	{
		fChannelFunctionRef->GetParentDMXChannel()->GetChannelBitResolution();
	}

	//------------------------------------------------------------------------------------
	// Get the attribute
	TXString dmxValStr; pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualValue_AttrValue, dmxValStr);
	GdtfConverter::ConvertDMXValue(dmxValStr, resolution ,fDmxValue);
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