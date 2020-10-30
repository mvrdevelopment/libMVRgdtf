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
	fHasColor 			= false;

}

GdtfAttribute::GdtfAttribute(const TXString& name, const TXString& prettyName)
{
	fName				= name;
	fPrettyName			= prettyName;
	fActivationGroup	= nullptr;
	fFeature            = nullptr;    
    fMainAttribute      = nullptr;
    fPhysicalUnit       = EGdtfPhysicalUnit::None;
	fHasColor 			= false;
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
	fHasColor = true;
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
	if(fHasColor) 			{ pNode->SetNodeAttributeValue(XML_GDTF_AttributeColor, GdtfConverter::ConvertColor(fColor)); }

    pNode->SetNodeAttributeValue(XML_GDTF_AttributePhysicalUnit, GdtfConverter::ConvertPhysicalUnitEnum(fPhysicalUnit));
	
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

	TXString colorStr; 
	if(VCOM_SUCCEEDED(pNode->GetNodeAttributeValue(XML_GDTF_AttributeColor, colorStr)))
	{
		GdtfConverter::ConvertColor(colorStr, pNode, fColor);
		fHasColor = true;
	}	
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

bool GdtfAttribute::HasColor() const
{
	return fHasColor;
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
// GdtfWheelSlotAnimationSystem
GdtfWheelSlotAnimationSystem::GdtfWheelSlotAnimationSystem()
{
}

GdtfWheelSlotAnimationSystem::~GdtfWheelSlotAnimationSystem()
{
}

double GdtfWheelSlotAnimationSystem::GetP1_X()
{
	return fP1_X;
}

double GdtfWheelSlotAnimationSystem::GetP1_Y()
{
	return fP1_Y;
}

double GdtfWheelSlotAnimationSystem::GetP2_X()
{
	return fP2_X;
}

double GdtfWheelSlotAnimationSystem::GetP2_Y()
{
	return fP2_Y;
}

double GdtfWheelSlotAnimationSystem::GetP3_X()
{
	return fP3_X;
}

double GdtfWheelSlotAnimationSystem::GetP3_Y()
{
	return fP3_Y;
}

double GdtfWheelSlotAnimationSystem::GetRadius()
{
	return fRadius;
}

void GdtfWheelSlotAnimationSystem::SetP1_X(double p1_X)
{
	fP1_X = p1_X;
}

void GdtfWheelSlotAnimationSystem::SetP1_Y(double p1_Y)
{
	fP1_Y = p1_Y;
}

void GdtfWheelSlotAnimationSystem::SetP2_X(double p2_X)
{
	fP2_X = p2_X;
}

void GdtfWheelSlotAnimationSystem::SetP2_Y(double p2_Y)
{
	fP2_Y = p2_Y;
}

void GdtfWheelSlotAnimationSystem::SetP3_X(double p3_X)
{
	fP3_X = p3_X;
}

void GdtfWheelSlotAnimationSystem::SetP3_Y(double p3_Y)
{
	fP3_Y = p3_Y;
}

void GdtfWheelSlotAnimationSystem::SetRadius(double radius)
{
	fRadius = radius;
}

void GdtfWheelSlotAnimationSystem::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	pNode->SetNodeAttributeValue(XML_GDTF_AnimationSystemP1,		GdtfConverter::Convert2DPoint(fP1_X, fP1_Y));
	pNode->SetNodeAttributeValue(XML_GDTF_AnimationSystemP2,		GdtfConverter::Convert2DPoint(fP2_X, fP2_Y));
	pNode->SetNodeAttributeValue(XML_GDTF_AnimationSystemP3,		GdtfConverter::Convert2DPoint(fP3_X, fP3_Y));
	pNode->SetNodeAttributeValue(XML_GDTF_AnimationSystemRadius,	GdtfConverter::ConvertDouble(fRadius));
}

void GdtfWheelSlotAnimationSystem::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	TXString p1;		pNode->GetNodeAttributeValue(XML_GDTF_AnimationSystemP1,		p1);		GdtfConverter::Convert2DPoint(p1, pNode, fP1_X, fP1_Y);
	TXString p2;		pNode->GetNodeAttributeValue(XML_GDTF_AnimationSystemP2,		p2);		GdtfConverter::Convert2DPoint(p2, pNode, fP2_X, fP2_Y);
	TXString p3;		pNode->GetNodeAttributeValue(XML_GDTF_AnimationSystemP3,		p3);		GdtfConverter::Convert2DPoint(p3, pNode, fP3_X, fP3_Y);
	TXString radius;	pNode->GetNodeAttributeValue(XML_GDTF_AnimationSystemRadius,	radius);	GdtfConverter::ConvertDouble(radius, pNode, fRadius);
}

void GdtfWheelSlotAnimationSystem::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_AnimationSystemP1);
	needed.push_back(XML_GDTF_AnimationSystemP2);
	needed.push_back(XML_GDTF_AnimationSystemP3);
	needed.push_back(XML_GDTF_AnimationSystemRadius);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfWheelSlotAnimationSystem::GetObjectType()
{
	return EGdtfObjectType::eGdtfAnimationSystem;
}

TXString GdtfWheelSlotAnimationSystem::GetNodeName()
{
	return XML_GDTF_AnimationSystemNodeName;
}

//------------------------------------------------------------------------------------
// GdtfWheelSlot
GdtfWheelSlot::GdtfWheelSlot(GdtfWheel* parent)
{
	fWheelParent 		= parent;
	fFilter 	 		= nullptr;
	fAnimationSystem	= nullptr;
}

GdtfWheelSlot::GdtfWheelSlot(const TXString& name, GdtfWheel* parent)
{
	fName		 		= name;
	fWheelParent 		= parent;
	fFilter		 		= nullptr;
	fAnimationSystem	= nullptr;
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

void GdtfWheelSlot::SetFilter(GdtfFilter* filter)
{
	fFilter = filter;
}

GdtfWheelSlotPrismFacet* GdtfWheelSlot::AddPrismFacet()
{
	GdtfWheelSlotPrismFacet* prism = new GdtfWheelSlotPrismFacet();
	fPrismFacts.push_back(prism);
	return prism;
}

GdtfWheelSlotAnimationSystem* GdtfWheelSlot::AddAnimationSystem()
{
	GdtfWheelSlotAnimationSystem* animationSystem = new GdtfWheelSlotAnimationSystem();
	fAnimationSystem = animationSystem;
	return animationSystem;
}

const TXString&	GdtfWheelSlot::GetGobo() const
{
	return fGobo;
}

GdtfFilter*	GdtfWheelSlot::GetFilter() const
{
	return fFilter;
}

const TXString&	GdtfWheelSlot::GetUnresolvedFilter() const
{
	return fUnresolvedFilter;
}

const TXString&	GdtfWheelSlot::GetGoboFileFullPath()
{
	fGoboFile = "";

	IFolderIdentifierPtr	folder;
	fWheelParent->GetParentFixture()->GetWorkingFolder(folder);

	IFolderIdentifierPtr wheelsFolder (IID_FolderIdentifier);
 	wheelsFolder->Set(folder, "wheels");
	
	IFileIdentifierPtr file (IID_FileIdentifier);		 	
 	file->Set(wheelsFolder, fGobo + ".png");
	bool fileExists = false;
 	if(VCOM_SUCCEEDED(file->ExistsOnDisk(fileExists)) && fileExists)		 	
	{			
		file->GetFileFullPath(fGoboFile);				
	}			

	
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
	if(fFilter)	{ pNode->SetNodeAttributeValue(XML_GDTF_WheelSlotFilter,		fFilter->GetNodeReference()); }
	
	//------------------------------------------------------------------------------------
	// Print the children
	for (GdtfWheelSlotPrismFacet* prism : fPrismFacts)
	{
		prism->WriteToNode(pNode);
	}

	//------------------------------------------------------------------------------------
	// Print the animation system
	if(fAnimationSystem) { fAnimationSystem->WriteToNode(pNode); }
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
	

	pNode->GetNodeAttributeValue(XML_GDTF_WheelSlotFilter,	fUnresolvedFilter);
	
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
	
	//Animation System
	IXMLFileNodePtr animationSystemNode;
	pNode->GetChildNode(XML_GDTF_AnimationSystemNodeName, &animationSystemNode);
	if(animationSystemNode != nullptr)
	{
		GdtfWheelSlotAnimationSystemPtr animationSystem = new GdtfWheelSlotAnimationSystem();
		animationSystem->ReadFromNode(animationSystemNode);
		fAnimationSystem = animationSystem;
	}
	

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
	optional.push_back(XML_GDTF_WheelSlotFilter);

	
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

GdtfWheelSlotAnimationSystem* GdtfWheelSlot::GetAnimationSystem() const
{
	return fAnimationSystem;
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

	IFolderIdentifierPtr model3DsFolter (IID_FolderIdentifier);
	model3DsFolter->Set(folder, "models3ds");

	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(model3DsFolter, fGeometryFile + ".3ds");

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

	IFolderIdentifierPtr modelsvgFolter (IID_FolderIdentifier);
	modelsvgFolter->Set(folder, "modelssvg");

	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(modelsvgFolter, fGeometryFile + ".svg");


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

GdtfGeometryPtr GdtfGeometry::AddGeometryMediaServerCamera(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryMediaServerCamera(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryMediaServerLayer(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryMediaServerLayer(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryMediaServerMaster(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryMediaServerMaster(name, refToModel, ma, this);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryDisplay(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryDisplay(name, refToModel, ma, this);

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
										bool hasBreak = false;
										
										GdtfGeometryPtr geometry = nullptr;
										if	  (childNodeName == XML_GDTF_GeometryAxisNodeName)			{ geometry = new GdtfGeometryAxis(this);}
										else if (childNodeName == XML_GDTF_GeometryNodeName)			{ geometry = new GdtfGeometry(this);}
										else if (childNodeName == XML_GDTF_FilterBeamNodeName)			{ geometry = new GdtfGeometryBeamFilter(this);}
										else if (childNodeName == XML_GDTF_FilterColorNodeName)			{ geometry = new GdtfGeometryColorFilter(this);}
										else if (childNodeName == XML_GDTF_FilterGoboNodeName)			{ geometry = new GdtfGeometryGoboFilter(this);}
										else if (childNodeName == XML_GDTF_FilterShaperNodeName)		{ geometry = new GdtfGeometryShaperFilter(this);}
										else if (childNodeName == XML_GDTF_LampNodeName)				{ geometry = new GdtfGeometryLamp(this);}
										else if (childNodeName == XML_GDTF_MediaServerCameraNodeName)	{ geometry = new GdtfGeometryMediaServerCamera(this);}
										else if (childNodeName == XML_GDTF_MediaServerLayerNodeName)	{ geometry = new GdtfGeometryMediaServerLayer(this);}
										else if (childNodeName == XML_GDTF_MediaServerMasterNodeName)	{ geometry = new GdtfGeometryMediaServerMaster(this);}
										else if (childNodeName == XML_GDTF_GeometryReferenceNodeName)	{ geometry = new GdtfGeometryReference(this);}
										else if (childNodeName == XML_GDTF_DisplayNodeName)				{ geometry = new GdtfGeometryDisplay(this);}
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
												
												GdtfGeometryReferencePtr refGeo = static_cast<GdtfGeometryReferencePtr>(this);
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

GdtfGeometryPtr GdtfGeometry::GetParentGeometry()
{
	return fParent;
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
	optional.push_back(XML_GDTF_GeometryModelRef);
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
	optional.push_back(XML_GDTF_GeometryModelRef);
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
	optional.push_back(XML_GDTF_GeometryModelRef);
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
	optional.push_back(XML_GDTF_GeometryModelRef);
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
	optional.push_back(XML_GDTF_GeometryModelRef);
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
// GdtfGeometryMediaServerCamera
GdtfGeometryMediaServerCamera::GdtfGeometryMediaServerCamera(GdtfGeometry* parent) : GdtfGeometry(parent)
{
	
}

GdtfGeometryMediaServerCamera::GdtfGeometryMediaServerCamera(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma, GdtfGeometry* parent) 
					  		 : GdtfGeometry(name, refToModel, ma, parent)
{
	
}

GdtfGeometryMediaServerCamera::~GdtfGeometryMediaServerCamera()
{
}

void GdtfGeometryMediaServerCamera::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
}

void GdtfGeometryMediaServerCamera::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
}

void GdtfGeometryMediaServerCamera::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	optional.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryMediaServerCamera::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryMediaServerCamera;
}

TXString GdtfGeometryMediaServerCamera::GetNodeName()
{
	return XML_GDTF_MediaServerCameraNodeName;
}

//------------------------------------------------------------------------------------
// GdtfGeometryMediaServerLayer
GdtfGeometryMediaServerLayer::GdtfGeometryMediaServerLayer(GdtfGeometry* parent) : GdtfGeometry(parent)
{
	
}

GdtfGeometryMediaServerLayer::GdtfGeometryMediaServerLayer(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) 
					  		: GdtfGeometry(name,refToModel,ma, parent)
{
	
}

GdtfGeometryMediaServerLayer::~GdtfGeometryMediaServerLayer()
{
}

void GdtfGeometryMediaServerLayer::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
}

void GdtfGeometryMediaServerLayer::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
}

void GdtfGeometryMediaServerLayer::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	optional.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryMediaServerLayer::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryMediaServerLayer;
}

TXString GdtfGeometryMediaServerLayer::GetNodeName()
{
	return XML_GDTF_MediaServerLayerNodeName;
}

//------------------------------------------------------------------------------------
// GdtfGeometryMediaServerMaster
GdtfGeometryMediaServerMaster::GdtfGeometryMediaServerMaster(GdtfGeometry* parent) : GdtfGeometry(parent)
{
	
}

GdtfGeometryMediaServerMaster::GdtfGeometryMediaServerMaster(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) 
					  		 : GdtfGeometry(name,refToModel,ma, parent)
{
	
}

GdtfGeometryMediaServerMaster::~GdtfGeometryMediaServerMaster()
{
}

void GdtfGeometryMediaServerMaster::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	
}

void GdtfGeometryMediaServerMaster::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
}

void GdtfGeometryMediaServerMaster::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	optional.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryMediaServerMaster::GetObjectType()
{
	return EGdtfObjectType::eGdtfGeometryMediaServerMaster;
}

TXString GdtfGeometryMediaServerMaster::GetNodeName()
{
	return XML_GDTF_MediaServerMasterNodeName;
}

//------------------------------------------------------------------------------------
// GdtfGeometryDisplay
GdtfGeometryDisplay::GdtfGeometryDisplay(GdtfGeometry* parent)
					:GdtfGeometry(parent)
{
	fTexture = "";
}

GdtfGeometryDisplay::GdtfGeometryDisplay(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) 
					:GdtfGeometry(name,refToModel,ma, parent)
{
	fTexture = "";	
}

GdtfGeometryDisplay::~GdtfGeometryDisplay()
{
}

const TXString& GdtfGeometryDisplay::GetTexture() 
{
	return fTexture;
}

void GdtfGeometryDisplay::SetTexture(const TXString& texture) 
{
	fTexture = texture;
}

void GdtfGeometryDisplay::OnPrintToFile(IXMLFileNodePtr pNode) 
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnPrintToFile(pNode);
	pNode->SetNodeAttributeValue(XML_GDTF_DisplayTexture, fTexture);
}

void GdtfGeometryDisplay::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);

	pNode->GetNodeAttributeValue(XML_GDTF_DisplayTexture, fTexture);
}

void GdtfGeometryDisplay::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_GeometryName);
	optional.push_back(XML_GDTF_GeometryModelRef);
	needed.push_back(XML_GDTF_GeometryMatrix);
	needed.push_back(XML_GDTF_DisplayTexture);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfGeometryDisplay::GetObjectType() 
{
	return EGdtfObjectType::eGdtfGeometryDisplay;
}

TXString GdtfGeometryDisplay::GetNodeName()
{
	return XML_GDTF_DisplayNodeName;
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
	fLuminousIntensity	= 10000;
	fColorTemperature	= 6000;
	fBeamAngle			= 25;
    fFieldAngle         = 25;
	fBeamRadius			= 50; //0.05m
	fThrowRatio			= 1;
	fRectangleRatio		= 1.7777;
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

void SceneData::GdtfGeometryLamp::SetThrowRatio(double ratio)
{
    fThrowRatio = ratio;
}

void SceneData::GdtfGeometryLamp::SetRectangleRatio(double ratio)
{
    fRectangleRatio = ratio;
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
	pNode->SetNodeAttributeValue(XML_GDTF_ThrowRatio,				GdtfConverter::ConvertDouble(fThrowRatio));
	pNode->SetNodeAttributeValue(XML_GDTF_RectangleRatio,			GdtfConverter::ConvertDouble(fRectangleRatio));
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
	TXString lampType;		pNode->GetNodeAttributeValue(XML_GDTF_LampLampType,				lampType);		GdtfConverter::ConvertLampeType(lampType, 	pNode,	fLampType);
	TXString power;			pNode->GetNodeAttributeValue(XML_GDTF_LampPowerConsumption,		power);			GdtfConverter::ConvertDouble(power, 		pNode,	fPowerConsuption);
	TXString lum;			pNode->GetNodeAttributeValue(XML_GDTF_LampLuminousFlux,			lum);			GdtfConverter::ConvertDouble(lum, 			pNode,	fLuminousIntensity);
	TXString colorTemp;		pNode->GetNodeAttributeValue(XML_GDTF_ColorTemperature,			colorTemp);		GdtfConverter::ConvertDouble(colorTemp, 	pNode,	fColorTemperature);
	TXString angle;			pNode->GetNodeAttributeValue(XML_GDTF_BeamAngle,				angle);			GdtfConverter::ConvertDouble(angle, 		pNode,	fBeamAngle);
	TXString radius;		pNode->GetNodeAttributeValue(XML_GDTF_BeamRadius,				radius);		GdtfConverter::ConvertDouble(radius, 		pNode,	fBeamRadius);
	TXString fieldAngle;	pNode->GetNodeAttributeValue(XML_GDTF_FieldAngle,				fieldAngle);	GdtfConverter::ConvertDouble(fieldAngle, 	pNode,	fFieldAngle);
	TXString throwRatio;	pNode->GetNodeAttributeValue(XML_GDTF_ThrowRatio,				throwRatio);	GdtfConverter::ConvertDouble(throwRatio, 	pNode,	fThrowRatio);
	TXString rectangleRatio;pNode->GetNodeAttributeValue(XML_GDTF_RectangleRatio,			rectangleRatio);GdtfConverter::ConvertDouble(rectangleRatio,pNode,	fRectangleRatio);
	TXString type;			pNode->GetNodeAttributeValue(XML_GDTF_BeamType,					type);			GdtfConverter::ConvertBeamType(type, 		pNode,	fBeamType);
	TXString colorIndex;	pNode->GetNodeAttributeValue(XML_GDTF_BeamColorRenderingIndex,	colorIndex);	GdtfConverter::ConvertInteger(colorIndex, 	pNode,	fColorIndex);
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
	needed.push_back(XML_GDTF_GeometryMatrix);
	optional.push_back(XML_GDTF_LampLampType);
	optional.push_back(XML_GDTF_LampPowerConsumption);
	optional.push_back(XML_GDTF_LampLuminousFlux);
	optional.push_back(XML_GDTF_ColorTemperature);
	optional.push_back(XML_GDTF_BeamAngle);
	optional.push_back(XML_GDTF_FieldAngle);
	optional.push_back(XML_GDTF_BeamRadius);
	optional.push_back(XML_GDTF_ThrowRatio);
	optional.push_back(XML_GDTF_RectangleRatio);
	optional.push_back(XML_GDTF_BeamType);
	optional.push_back(XML_GDTF_BeamColorRenderingIndex);
	optional.push_back(XML_GDTF_GeometryModelRef);

	
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

double SceneData::GdtfGeometryLamp::GetThrowRatio()
{
	return fThrowRatio;
}

double SceneData::GdtfGeometryLamp::GetRectangleRatio()
{
	return fRectangleRatio;
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
	optional.push_back(XML_GDTF_GeometryModelRef);
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

GdtfDmxMode::GdtfDmxMode(GdtfFixture* fixture, const TXString& name)
{
	fName		= name;
	fGeomRef    = nullptr;
	fFixture    = fixture;
}

GdtfDmxMode::~GdtfDmxMode()
{
    // Housekeeping
    for (GdtfDmxChannelPtr	ptr : fChannels)	{ delete ptr; }
	for (GdtfDmxRelationPtr	ptr : fRelations)	{ delete ptr; }
	for (GdtfMacroPtr		ptr : fMacros)		{ delete ptr; }
    
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
	
	// ------------------------------------------------------------------------------------
	// Print Macros
	IXMLFileNodePtr macros;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_DMXModeMacros, &macros)))
	{
		for (GdtfMacro* macrosObj : fMacros)
		{
			macrosObj->WriteToNode(macros);
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
									 GdtfDmxRelationPtr relation = new GdtfDmxRelation();
									 relation->ReadFromNode(pNode);
									 fRelations.push_back(relation);
								 }
								 );
	

	// ------------------------------------------------------------------------------------
	// Print Macros
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_DMXModeMacros, XML_GDTF_MacroNodeName, [this](IXMLFileNodePtr pNode) -> void
								{
									GdtfMacroPtr macro = new GdtfMacro();
									macro->ReadFromNode(pNode);
									fMacros.push_back(macro);
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

GdtfMacro* GdtfDmxMode::AddMacro(const TXString &name)
{
	GdtfMacro* macro = new GdtfMacro(name);
	fMacros.push_back(macro);
	return macro;
}

GdtfGeometryPtr	GdtfDmxMode::GetGeomRef()
{
	return fGeomRef;
}

TGdtfDmxChannelArray GdtfDmxMode::GetChannelsForGeometry(GdtfGeometryPtr geometry)
{
	TGdtfDmxChannelArray array;
	for (GdtfDmxChannelPtr channel : GetChannelArray())
	{
		if(channel->GetGeomRef() == geometry)
		{
			array.push_back(channel);
		}
	}
	
	return array;
}

const TXString& GdtfDmxMode::GetUnresolvedGeomRef()
{
	return fUnresolvedGeomRef;
}

const TGdtfDmxRelationArray GdtfDmxMode::GetDmxRelations()
{
	return fRelations;
}

TSint32Array GdtfDmxMode::GetBreakArray() const
{
	//------------------------------------------------------------------------------------------------------------
	// Prepare Arrays
	TSint32Array 							breaks;
	std::vector<GdtfGeometryReferencePtr>  	geometryRefs;
	TGdtfGeometryArray  					geometrysToCheck = {fGeomRef};

	//------------------------------------------------------------------------------------------------------------
	// Get All Geometry References
	while(geometrysToCheck.size() > 0)
	{
		// Get First Entry and delete it then
		GdtfGeometryPtr geometry = geometrysToCheck.back();
		geometrysToCheck.pop_back();

		// Get all the internal geometries and prepare to chekc them
		for(GdtfGeometryPtr child : geometry->GetInternalGeometries()) { geometrysToCheck.push_back(child); }

		// Handle Geo Refs
		if(geometry->GetObjectType() == eGdtfGeometryReference )
		{
			GdtfGeometryReferencePtr geoRef = static_cast<GdtfGeometryReferencePtr>(geometry);
			ASSERTN(kEveryone, geoRef != nullptr);
			if(geoRef)
			{
				geometrysToCheck.push_back(geoRef->GetLinkedGeometry());
				geometryRefs.push_back(geoRef);
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------
	// Check all the channels
	for (GdtfDmxChannelPtr channel : fChannels)
	{
		Sint32 breakId = channel->GetDmxBreak();
		
		// Check if Override
		if(breakId == kDmxBreakOverwriteValue)
		{
			for(GdtfGeometryReferencePtr geoRef : geometryRefs)
			{
				if(geoRef->GetLinkedGeometry() == channel->GetGeomRef())
				{
					TGdtfBreakArray refBreaks = geoRef->GetBreakArray();
					if(std::find(breaks.begin(), breaks.end(), refBreaks.back()->GetDmxBreak()) == breaks.end())
					{
						breaks.push_back(refBreaks.back()->GetDmxBreak());
					}
				}
			}
		}
		else
		{
			if(std::find(breaks.begin(), breaks.end(), breakId) == breaks.end())
			{
				breaks.push_back(breakId);
			}
		}
	}

	//------------------------------------------------------------------------------------------------------------
	// Sort the found break
	std::sort(breaks.begin(), breaks.end());

	return breaks;
}

size_t GdtfDmxMode::GetFootPrintForBreak(size_t breakId)
{
	//------------------------------------------------------------------------------------------------------------
	// check if break exists
	TSint32Array breaks = this->GetBreakArray();
	if(std::find(breaks.begin(), breaks.end(), breakId) == breaks.end()) 
	{ 
		return 0; 
	}

	//------------------------------------------------------------------------------------------------------------
	// Prepare arrays
	TDMXAddressArray 	addresses;
	TGdtfGeometryArray  geometriesInGeoTree = {fGeomRef};

	// iterate through every geometry in the geometry tree of the mode 
	while(geometriesInGeoTree.size() > 0)
	{
		TDMXAddressArray addressesOfGeo;
		GdtfGeometryPtr  geoToCheck = geometriesInGeoTree.back();
		geometriesInGeoTree.pop_back();

		for (GdtfGeometryPtr child : geoToCheck->GetInternalGeometries()) { geometriesInGeoTree.push_back(child); }

		// if channel is linked to the current geometry and the breaks match add the dmx addresses to the footprint 
		for (GdtfDmxChannelPtr channel : fChannels)
		{
			if(channel->GetGeomRef() == geoToCheck && channel->GetDmxBreak() == (Sint32)breakId) 
			{
				GetAddressesFromChannel(addressesOfGeo, channel, 0);
			}
		}

		// if the current geometry is a geometry reference do stuff
		if(geoToCheck->GetObjectType() == eGdtfGeometryReference)
		{
			GdtfGeometryReferencePtr geoRef 	= static_cast<GdtfGeometryReferencePtr>(geoToCheck); ASSERTN(kEveryone, geoRef);
			GdtfGeometryPtr 		 refedGeo   = geoRef->GetLinkedGeometry();
			TSint32Array 			 breakIdsOfReference;
			TGdtfGeometryArray 		 geometriesInReferencedTree = {refedGeo};
			bool 				     overwrite = false;
			
			// go through every child of the referenced geometry and get every used break id
			while (geometriesInReferencedTree.size() > 0)
			{
				GdtfGeometryPtr geometryInRefToCheck = geometriesInReferencedTree.back();
				geometriesInReferencedTree.pop_back();

				for (GdtfGeometryPtr childOfRef : geometryInRefToCheck->GetInternalGeometries()){ geometriesInReferencedTree.push_back(childOfRef); }

				for (GdtfDmxChannelPtr channel : fChannels)
				{
					if(channel->GetGeomRef() == geometryInRefToCheck)
					{
						if(channel->GetDmxBreak() != kDmxBreakOverwriteValue)
						{
							if(std::find(breakIdsOfReference.begin(), breakIdsOfReference.end(), channel->GetDmxBreak()) == breakIdsOfReference.end())
							{
								breakIdsOfReference.push_back(channel->GetDmxBreak());
							}
						}
						else 
						{
							overwrite = true;
						}
					}
				}
			}

			std::sort(breakIdsOfReference.begin(), breakIdsOfReference.end());

			TSint32Array::iterator foundIndex = std::find(breakIdsOfReference.begin(), breakIdsOfReference.end(), breakId);
			// if the reference contains geometries that are linked to a dmx channel that has a matching break, then add the address + offset to the footprint
			if(foundIndex != breakIdsOfReference.end())
			{
				size_t 				indexOfBreak 				= std::distance(breakIdsOfReference.begin(),foundIndex);
				size_t 				offset 						= geoRef->GetBreakArray()[indexOfBreak]->GetDmxAddress()-1;
				TGdtfGeometryArray  geometriesInReferencedTree 	= {refedGeo};

				while (geometriesInReferencedTree.size() > 0)
				{
					GdtfGeometryPtr geometryInRefToCheck = geometriesInReferencedTree.back();
					geometriesInReferencedTree.pop_back();

					for (GdtfGeometryPtr childOfRef : geometryInRefToCheck->GetInternalGeometries()) { geometriesInReferencedTree.push_back(childOfRef); }

					for(GdtfDmxChannelPtr channel : fChannels)
					{
						if(channel->GetGeomRef() == geometryInRefToCheck && channel->GetDmxBreak() == (Sint32)breakId) 
						{
							GetAddressesFromChannel(addressesOfGeo, channel, offset);
						}
					}
				}
			}

			// if the channel of a child geometry has the break value overwrite and the last break of the ref has a matching break Id, then add addresses + offset 
			if(overwrite)
			{
				GdtfBreakPtr overwriteBreak = geoRef->GetBreakArray().back();
				if(overwriteBreak->GetDmxBreak() == (Sint32)breakId)
				{
					TGdtfGeometryArray geometriesInReferencedTree = {refedGeo};
					while (geometriesInReferencedTree.size() > 0)
					{
						GdtfGeometryPtr geometryInRefToCheck = geometriesInReferencedTree.back();
						geometriesInReferencedTree.pop_back();

						for (GdtfGeometryPtr childOfRef : geometryInRefToCheck->GetInternalGeometries()) { geometriesInReferencedTree.push_back(childOfRef); }

						for(GdtfDmxChannelPtr channel : fChannels)
						{
							if(channel->GetGeomRef() == geometryInRefToCheck && channel->GetDmxBreak() == kDmxBreakOverwriteValue) 
							{
								GetAddressesFromChannel(addressesOfGeo, channel, overwriteBreak->GetDmxAddress()-1);
							}
						}
					}
				}
			}
		}

		// make addresses unique
		for(DMXAddress address : addressesOfGeo)
		{
			if(std::find(addresses.begin(), addresses.end(), address) == addresses.end())
			{
				addresses.push_back(address);
			}
		}
	}

	DMXAddress max = 0, min = 512;
	for (DMXAddress adr : addresses)
	{
		if(adr > max) max = adr;
		if(adr < min) min = adr;
	}

	DMXAddress footprint = max - min + 1;

	return footprint;
}
void GdtfDmxMode::GetAddressesFromChannel(TDMXAddressArray& addresses, GdtfDmxChannel* channel, DMXAddress offset) const
{
	EGdtfChannelBitResolution resolution = channel->GetChannelBitResolution();
	if(resolution >= eGdtfChannelBitResolution_8) 	{ addresses.push_back(channel->GetCoarse()  + offset);}
	if(resolution >= eGdtfChannelBitResolution_16) 	{ addresses.push_back(channel->GetFine()	+ offset);}
	if(resolution >= eGdtfChannelBitResolution_24) 	{ addresses.push_back(channel->GetUltra()   + offset);}
	if(resolution >= eGdtfChannelBitResolution_32) 	{ addresses.push_back(channel->GetUber()	+ offset);}

}

const TGdtfMacroArray GdtfDmxMode::GetDmxMacrosArray()
{
	return fMacros;
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
	fHeighlight				= 0;	fHeighlightNone = true;
	fDefaultValue_old		= 0;
	fGeomRef				= nullptr;
	fInitialFunction		= nullptr;

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
	ASSERTN(kEveryone, fUltra > 0);
	fUber = uber;
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
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelHighlight,			GdtfConverter::ConvertDMXValue(fHeighlight,	chanelReso, fHeighlightNone));
	if (fGeomRef) 			{ pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelGeometry,			fGeomRef->GetNodeReference()); }
	if (fInitialFunction) 	{ pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelInitialFunction,	fInitialFunction->GetNodeReference()); }
	
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

	// In GDTF 1.0, default value was in the DMX channel, this is for old files :
	TXString defVal;	
	if (pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDefault, defVal) == kVCOMError_NoError)
	{
		GdtfConverter::ConvertDMXValue(defVal, pNode, this->GetChannelBitResolution(), fDefaultValue_old);
	}
	// ------------------------------------------------------------------------------------

	//
	TXString highlight;	
	if(VCOM_SUCCEEDED(pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelHighlight,			highlight)	))
	{
		GdtfConverter::ConvertDMXValue(highlight, pNode, this->GetChannelBitResolution(), fHeighlight, fHeighlightNone);
	}	
	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelGeometry, 			fUnresolvedGeomRef);
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelInitialFunction, 	fUnresolvedInitialFunction);	
	
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
	optional.push_back(XML_GDTF_DMXChannelInitialFunction);
	optional.push_back(XML_GDTF_DMXChannelDMXBreak);
	optional.push_back(XML_GDTF_DMXChannelOffset);
	optional.push_back(XML_GDTF_DMXChannelHighlight);
	//Default for GDTF 1.0 files
	optional.push_back(XML_GDTF_DMXChannelFuntionDefault);
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

DmxValue GdtfDmxChannel::GetHighlight() const
{
	return fHeighlight;
}

bool GdtfDmxChannel::HasHighlight() const
{
	return !fHeighlightNone;
}

DmxValue GdtfDmxChannel::GetOldDefaultValue() const
{
	return fDefaultValue_old;
}

void GdtfDmxChannel::SetGeomRef(GdtfGeometryPtr newGeom)
{
	fGeomRef = newGeom;
}

GdtfGeometryPtr GdtfDmxChannel::GetGeomRef()
{
	return fGeomRef;
}

TXString GdtfDmxChannel::GetUnresolvedGeomRef() const
{
	return fUnresolvedGeomRef;
}

void GdtfDmxChannel::SetInitialFunction(GdtfDmxChannelFunctionPtr initialFunction)
{
	fInitialFunction = initialFunction;
}

GdtfDmxChannelFunctionPtr GdtfDmxChannel::GetInitialFunction()
{
	return fInitialFunction;
}

TXString GdtfDmxChannel::GetUnresolvedInitialFunction() const
{
	return fUnresolvedInitialFunction;
}

const TGdtfDmxLogicalChannelArray GdtfDmxChannel::GetLogicalChannelArray()
{
	return fLogicalChannels;
}

EGdtfChannelBitResolution SceneData::GdtfDmxChannel::GetChannelBitResolution()
{
	// 0 is false, everything else is true
	if		((!fCoarse) && !fFine  &&  !fUltra &&    !fUber)	{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_32; }
	else if	(( fCoarse) && !fFine  &&  !fUltra &&    !fUber)	{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_8; }
	else if (( fCoarse) &&( fFine) &&  !fUltra  &&   !fUber )	{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_16; }
	else if (( fCoarse) &&( fFine) && ( fUltra) &&   !fUber )	{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_24; }
	else if (( fCoarse) &&( fFine) && ( fUltra) && (  fUber))	{ return EGdtfChannelBitResolution::eGdtfChannelBitResolution_32; }
    	
	// Other states are invalid. This line should never be reached.
	DSTOP((kEveryone, "Invalid state in GetChannelBitResolution()"));
	return EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;	
}

DmxValue SceneData::GdtfDmxChannel::GetChannelMaxDmx()
{
	return GdtfConverter::GetChannelMaxDmx(this->GetChannelBitResolution());
}

bool SceneData::GdtfDmxChannel::IsVirtual() const
{
	if(fCoarse == 0 && fFine == 0 && fUltra == 0 && fUber == 0)	return true;
	else 														return false;
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
									 
									 if(fFunctions.size() == 0)	
									 { 
										if(function->GetStartAdress() != 0)
										{
											GdtfParsingError error (GdtfDefines::EGdtfParsingError::eChannelFunctionNotStartingWithZero, objNode);
        									SceneData::GdtfFixture::AddError(error);
											function->SetStartAddress(0);
										}
									 }
									 
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
	fDefaultValue			= 0;
	fAdressStart			= 0;
	fPhysicalStart			= 0;
	fPhysicalEnd			= 1;
	fRealFade				= 0;
	fRealAcceleration 		= 0;
	fOnWheel				= nullptr;
	fEmitter				= nullptr;
	fAttribute				= nullptr;
	fParentLogicalChannel	= parent;
	fNextFunction			= nullptr;

	fModeMaster_Channel		= nullptr;
	fModeMaster_Function	= nullptr;
	fDmxModeStart			= 0;
	fDmxModeEnd				= 0;

	fFilter                = nullptr;
    fUnresolvedFilterRef = "";
}

GdtfDmxChannelFunction::GdtfDmxChannelFunction(const TXString& name, GdtfDmxLogicalChannel* parent)
{
	fName					= name;
	fDefaultValue			= 0;
	fAdressStart			= 0;
	fPhysicalStart			= 0;
	fPhysicalEnd			= 1;
	fRealFade				= 0;
	fRealAcceleration 		= 0;
	fOnWheel				= nullptr;
	fEmitter				= nullptr;				
	fAttribute				= nullptr;
	fParentLogicalChannel	= parent;
	fNextFunction			= nullptr;

	fModeMaster_Channel		= nullptr;
	fModeMaster_Function	= nullptr;
	fDmxModeStart			= 0;
	fDmxModeEnd				= 0;

    fFilter                = nullptr;
    fUnresolvedFilterRef   = "";
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

void GdtfDmxChannelFunction::SetDefaultValue(DmxValue defaultValue)
{
	fDefaultValue = defaultValue;
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

void GdtfDmxChannelFunction::SetRealAcceleration(double acceleration)
{
	fRealAcceleration = acceleration;
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

	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionName,				fName);

	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDefault,				GdtfConverter::ConvertDMXValue(fDefaultValue, chanelReso));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDMXFrom,				GdtfConverter::ConvertDMXValue(fAdressStart, chanelReso));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalFrom,		GdtfConverter::ConvertDouble(fPhysicalStart));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalTo,			GdtfConverter::ConvertDouble(fPhysicalEnd));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionRealFade,			GdtfConverter::ConvertDouble(fRealFade));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionRealAcceleration,	GdtfConverter::ConvertDouble(fRealAcceleration));

	
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

    if (fFilter) 
    {
        pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelFuntionFilter, fFilter->GetNodeReference());
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
			noFeature->SetDmxEnd(firstChannelSet->GetDmxStart()-1);
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
	TXString defaultValue;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDefault,				defaultValue);		GdtfConverter::ConvertDMXValue(defaultValue,	pNode,	channelReso,fDefaultValue);
	TXString dmxFrom;		pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionDMXFrom,				dmxFrom);			GdtfConverter::ConvertDMXValue(dmxFrom, 		pNode,	channelReso,fAdressStart);
	TXString physFrom;		pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalFrom,		physFrom);			GdtfConverter::ConvertDouble(physFrom, 			pNode,				fPhysicalStart);
	TXString physTo;		pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionPhysicalTo,			physTo);			GdtfConverter::ConvertDouble(physTo, 			pNode,				fPhysicalEnd);
	TXString realFade;		pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionRealFade,			realFade);			GdtfConverter::ConvertDouble(realFade, 			pNode,				fRealFade);
	TXString realAcc;		pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionRealAcceleration,	realAcc);			GdtfConverter::ConvertDouble(realAcc, 			pNode,				fRealAcceleration);

	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionAttribute, 	fUnresolvedAttrRef);	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionWheelRef, 	fUnresolvedWheelRef);
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelEmitter, 			fUnresolvedEmitterRef);

	// Read Mode Master
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeMaster,				fUnresolvedModeMaster);	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeFrom,				fUnresolvedDmxModeStart);	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionModeTo,					fUnresolvedDmxModeEnd);	

    // Filter
    pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionFilter,					fUnresolvedFilterRef);	

	// ------------------------------------------------------------------------------------
	// GdtfDmxChannelSet
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_DMXChannelSetNodeName, [this] (IXMLFileNodePtr objNode) -> void
	{
		// Create the object
		GdtfDmxChannelSetPtr channelSet = new GdtfDmxChannelSet(this);
		
		// Read from node
		channelSet->ReadFromNode(objNode);

		if( ! channelSet->IsValid()) { delete channelSet; return; }

	
		// Link with next
		if(!fChannelSets.empty()) 
		{ 
			bool validDmxRange = fChannelSets.back()->SetNextChannelSet(channelSet, objNode);
			if(! validDmxRange) { delete channelSet; return; }
		}
		
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
	optional.push_back(XML_GDTF_DMXChannelFuntionDefault);
	optional.push_back(XML_GDTF_DMXChannelFuntionDMXFrom);
	optional.push_back(XML_GDTF_DMXChannelFuntionPhysicalFrom);
	optional.push_back(XML_GDTF_DMXChannelFuntionPhysicalTo);
	optional.push_back(XML_GDTF_DMXChannelFuntionWheelRef);
	optional.push_back(XML_GDTF_DMXChannelEmitter);	
	optional.push_back(XML_GDTF_DMXChannelFuntionModeMaster);
	optional.push_back(XML_GDTF_DMXChannelFuntionModeFrom);
	optional.push_back(XML_GDTF_DMXChannelFuntionModeTo);
	optional.push_back(XML_GDTF_DMXChannelFuntionRealFade);
    optional.push_back(XML_GDTF_DMXChannelFuntionFilter);
	optional.push_back(XML_GDTF_DMXChannelFuntionRealAcceleration);
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
			functionName += TXString().itoa(GetNumberInParent());
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

DmxValue GdtfDmxChannelFunction::GetDefaultValue() const
{
	return fDefaultValue;
}

DmxValue GdtfDmxChannelFunction::GetStartAdress() const
{
	return fAdressStart;
}

DmxValue GdtfDmxChannelFunction::GetEndAdress() const
{
	if(fNextFunction)
	{
		// There could be serveral Channel Function that have the same start adress, step over them 
		if(fNextFunction->GetStartAdress() <= this->GetStartAdress()) { fParentLogicalChannel->GetParentDMXChannel()->GetChannelMaxDmx(); }
		// If the Start Adress differrs, the end Adress is based on the start adress of this channel 
		else { return(fNextFunction->GetStartAdress() - 1);  }	
	}
 
	
	// The last channel function will have a nullptr for the next function 
	

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

double GdtfDmxChannelFunction::GetRealAcceleration() const
{
	return fRealAcceleration;
}

GdtfWheelPtr GdtfDmxChannelFunction::GetOnWheel() const
{
	return fOnWheel;
}

GdtfPhysicalEmitter * SceneData::GdtfDmxChannelFunction::GetEmitter() const
{
    return fEmitter;
}

GdtfFilterPtr SceneData::GdtfDmxChannelFunction::GetFilter()
{
    return fFilter;
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

void SceneData::GdtfDmxChannelFunction::SetFilter(GdtfFilterPtr val)
{
    fFilter = val;
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

const TXString & SceneData::GdtfDmxChannelFunction::getUnresolvedFilterRef()
{
    return fUnresolvedFilterRef;
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
	fValid = true;
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
	fValid = true;
}

GdtfDmxChannelSet::~GdtfDmxChannelSet()
{
}

bool GdtfDmxChannelSet::SetNextChannelSet(GdtfDmxChannelSet* next, IXMLFileNodePtr objNode)
{
	if(this->GetDmxStart() >= next->GetDmxStart())
	{
		GdtfParsingError error (GdtfDefines::EGdtfParsingError::eValueError_DmxValueHasWrongValue, objNode);
        SceneData::GdtfFixture::AddError(error);
		return false;
	}

	ASSERTN(kEveryone, fNextChannelSet == nullptr);
	fNextChannelSet = next;
	return true;
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

bool GdtfDmxChannelSet::IsValid()
{
	return fValid;
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

	TXString dmxfrom;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetDMXFrom,				dmxfrom);	fValid = GdtfConverter::ConvertDMXValue (dmxfrom, pNode, channelReso, fDmxStart);
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
    fDominantWaveLength = 0;
    fDiodePart = "";
}

GdtfPhysicalEmitter::GdtfPhysicalEmitter(const TXString& name, CCieColor color)
{
	fColor		= color;
	fName		= name;
    fDominantWaveLength = 0;
    fDiodePart = "";
}

GdtfPhysicalEmitter::~GdtfPhysicalEmitter()
{
	for (GdtfMeasurementPtr ptr : fMeasurements) { delete ptr; }
}

void GdtfPhysicalEmitter::SetName(const TXString &name)
{
	fName = name;
}

void GdtfPhysicalEmitter::SetColor(CCieColor color)
{
	fColor = color;
}

void SceneData::GdtfPhysicalEmitter::SetDiodePart(const TXString& val)
{
    fDiodePart = val;
}

void SceneData::GdtfPhysicalEmitter::SetDominantWaveLength(double val)
{
    fDominantWaveLength = val;
}

GdtfMeasurement* GdtfPhysicalEmitter::AddMeasurement()
{
	GdtfMeasurement* mes = new GdtfMeasurement(false);
	fMeasurements.push_back(mes);
	return mes;
}

void GdtfPhysicalEmitter::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_EmitterName,				 fName);
	pNode->SetNodeAttributeValue(XML_GDTF_EmitterColor,				 GdtfConverter::ConvertColor(fColor) );
    pNode->SetNodeAttributeValue(XML_GDTF_EmitterDominantWaveLength, GdtfConverter::ConvertDouble(fDominantWaveLength) );
    pNode->SetNodeAttributeValue(XML_GDTF_EmitterDiodePart,          fDiodePart );
	//------------------------------------------------------------------------------------
	// Write Measurement
	for (GdtfMeasurement* mes: fMeasurements)
	{
		mes->WriteToNode(pNode);
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
	
    TXString color;		   pNode->GetNodeAttributeValue(XML_GDTF_EmitterColor,	color);		
    GdtfConverter::ConvertColor(color, pNode, fColor);

    TXString waveLenStr;   pNode->GetNodeAttributeValue(XML_GDTF_EmitterDominantWaveLength,	waveLenStr);		
    GdtfConverter::ConvertDouble(waveLenStr, pNode, fDominantWaveLength);

    pNode->GetNodeAttributeValue(XML_GDTF_EmitterDiodePart, fDiodePart);
	
	// ------------------------------------------------------------------------------------
	// Read Measurements
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_MeasurementNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfMeasurementPtr mes = new GdtfMeasurement(false);
									 
									 // Read from node
									 mes->ReadFromNode(objNode);
									 
									 // Add to list
									 fMeasurements.push_back(mes);
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
	    
		
	optional.push_back(XML_GDTF_EmitterDominantWaveLength);
    optional.push_back(XML_GDTF_EmitterDiodePart);

	
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

const TGdtfMeasurementArray GdtfPhysicalEmitter::GetMeasurements()
{
	return fMeasurements;
}

TXString GdtfPhysicalEmitter::GetNodeReference()
{
	return GetName();
}

const TXString& SceneData::GdtfPhysicalEmitter::GetDiodePart()
{
    return fDiodePart;
}

double SceneData::GdtfPhysicalEmitter::GetDominantWaveLength()
{
    return fDominantWaveLength;
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
GdtfMacro::GdtfMacro()
{
	fMacroDMX = nullptr;
	fMacroVisual = nullptr;
}

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
    
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_MacroName, fName);

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
	IXMLFileNodePtr macroDmxNode;
    if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_MacroDMX, &macroDmxNode)))
	{
		if (fMacroDMX) { delete fMacroDMX; }
		this->fMacroDMX = new GdtfMacroDMX();
		this->fMacroDMX->ReadFromNode(macroDmxNode);
	}
	
	IXMLFileNodePtr macroVisualNode;
    if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_MacroVisual, &macroVisualNode)))
	{
		if (fMacroVisual) { delete fMacroVisual; }
		this->fMacroVisual = new GdtfMacroVisual();
		this->fMacroVisual->ReadFromNode(macroVisualNode);
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
	if(fMacroDMX) {delete fMacroDMX; }
    fMacroDMX = val;
}

void SceneData::GdtfMacro::SetMacroVisual(GdtfMacroVisual* val)
{
	if(fMacroVisual) {delete fMacroVisual; }
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
	return XML_GDTF_MeasurementPointNode;
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

void GdtfFixture::ImportFromFile(IFileIdentifierPtr inZipFile, const TXString& folder)
{
	PrepareWorkingFolder(folder);
	
	IZIPFilePtr zipfile ( IID_ZIPFile );
	zipfile->OpenRead(inZipFile);

	ImportFromZip(zipfile);
}

void GdtfFixture::ImportFromBuffer(const char*buffer, size_t length, const TXString& folder)
{
	PrepareWorkingFolder(folder);
	
	IZIPFilePtr zipfile ( IID_ZIPFile );
	zipfile->OpenRead(buffer, length);

	ImportFromZip(zipfile);
}

void GdtfFixture::PrepareWorkingFolder(TXString folderName)
{
	//-------------------------------------------------------------------------------------------------
	// Working Directory
	if(folderName.IsEmpty()){ folderName = "GdtfGroup"; }

	fWorkingFolder = (IID_FolderIdentifier);
	fWorkingFolder->Set(EFolderSpecifier::kSpotlightFolder, true /*UserFolder*/, folderName);
	
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
}

bool GdtfFixture::ImportFromZip(IZIPFilePtr& zipfile)
{
	ASSERTN(kEveryone, __ERROR_CONTAINER_POINTER == nullptr);
	__ERROR_CONTAINER_POINTER = & this->fErrorContainer; 

	ISceneDataZipBuffer xmlFileBuffer;
		
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	TXString fileName				= "";
	TXString inPath					= "";
	while (VCOM_SUCCEEDED( zipfile->GetNextFile(inPath, fileName)))
	{
		// This is the current file that we are reading
		ISceneDataZipBuffer buffer;
		if(VCOM_SUCCEEDED(zipfile->GetFile(fileName, &buffer)))
		{
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
	#ifndef _WINDOWS
				fileNameWithoutFolder          = TXString(fileName).Replace("\\", TXString(kSeperator) ); // It seems some zips come also with this.
	#endif
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

				TXString fullPathRessource;
				file->GetFileFullPath(fullPathRessource);
				fLocalFilesFullPath.push_back(fullPathRessource);


			}
		}
		
		inPath = fileName;
	}
		
	zipfile->Close();
	
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

	return true;
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
	// Check fi there
	for (GdtfAttributePtr attr : fAttributes)
	{
		if (fNoFeature == nullptr && XML_GDTF_AttributeNoFeature_nullptr == ref) { fNoFeature = attr; }
		if (attr->GetNodeReference() == ref) { return attr; };
	}
	if(ref.IsEmpty() || ref == XML_GDTF_AttributeNoFeature_nullptr)							   
	{
		if(fNoFeature == nullptr)
		{
			CreateNoFeatureAttribute();
		} 
		return fNoFeature; 
	}
	

	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfAttributePtr."));
	return fNoFeature;
}

void GdtfFixture::CreateNoFeatureAttribute()
{
	//------------------------------------------------------------
	// Create Attribute
	ASSERTN(kEveryone, fNoFeature == nullptr);
	fNoFeature = new GdtfAttribute("NoFeature", "NoFeature");
	fAttributes.push_back(fNoFeature);

	//------------------------------------------------------------
	// Create Feature Group
	GdtfFeatureGroupPtr controlFeatureGroup = nullptr;
	for (GdtfFeatureGroupPtr featGrp : fFeatureGroups)
	{	
		if(featGrp->GetName() == "Control")
		{
			controlFeatureGroup = featGrp;
			break;
		}
	}

	if(controlFeatureGroup == nullptr)
	{
		controlFeatureGroup = new GdtfFeatureGroup("Control", "Control");
		fFeatureGroups.push_back(controlFeatureGroup);
	}
	ASSERTN(kEveryone, controlFeatureGroup != nullptr)

	//------------------------------------------------------------
	// Create Feature
	GdtfFeaturePtr linkedFeature = nullptr;
	for (GdtfFeaturePtr feature : controlFeatureGroup->GetFeatureArray())
	{	
		if(feature->GetName() == "Control")
		{
			linkedFeature = feature;
			break;
		}
	}

	if(linkedFeature == nullptr)
	{
		linkedFeature = controlFeatureGroup->AddFeature("Control");
	}

	fNoFeature->SetFeature(linkedFeature);

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
	for (GdtfPhysicalEmitterPtr emt : fPhysicalDesciptions.GetPhysicalEmitterArray() )
	{
		if (emt->GetNodeReference() == ref){ return emt;};
	}

	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfPhysicalEmitterPtr."));
	return nullptr;
}

GdtfFilterPtr GdtfFixture::getFilterByRef(const TXString& ref) 
{
    for (GdtfFilterPtr fltr : fPhysicalDesciptions.GetFilterArray())
    {
        if (fltr->GetNodeReference() == ref) { return fltr; }
    }

	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfFilter."));
	return nullptr;
}

GdtfConnectorPtr GdtfFixture::getConnectorByRef(const TXString& ref) 
{
    for (GdtfConnectorPtr connector : fPhysicalDesciptions.GetConnectorArray())
    {
        if (connector->GetNodeReference() == ref) { return connector; }
    }

	// When this line is reached nothing was found.
	DSTOP ((kEveryone, "Failed to resolve GdtfConnectorPtr."));
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
	ResolveDmxModeRefs();	
	ResolveDMXModeMasters();
    ResolveDMXPersonalityRefs();
	ResolveAttribRefs();
	ResolveWheelSlots();
	ResolvePowerConsumptions();
	CheckForMissingModeMasters();
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
		GdtfGeometryReferencePtr geoRef = static_cast<GdtfGeometryReferencePtr>(geometry);
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

void GdtfFixture::ResolveWheelSlots()
{
	for(GdtfWheelPtr wheel : fWheels)
	{
		for(GdtfWheelSlotPtr slot :  wheel->GetWheelSlotArray())
		{
			TXString ref = slot->GetUnresolvedFilter();
			if( ! ref.IsEmpty())
			{
				GdtfFilterPtr filter = getFilterByRef(ref);
				slot->SetFilter(filter);
			}
		}
	}
}

void GdtfFixture::ResolvePowerConsumptions()
{
	for(GdtfPowerConsumptionPtr powerConsumption : fPhysicalDesciptions.GetPowerConsumptionArray())
	{
		TXString ref = powerConsumption->GetUnresolvedConnector();
		if( ! ref.IsEmpty())
		{
			GdtfConnectorPtr connector = getConnectorByRef(ref);
			powerConsumption->SetConnector(connector);
		}
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

void GdtfFixture::ResolveMacroRefs(GdtfDmxModePtr dmxMode)
{
	for (GdtfMacroPtr macro : dmxMode->GetDmxMacrosArray())
	{
		if(macro->GetMacroDMX())
		{
			for (GdtfMacroDMXStepPtr step : macro->GetMacroDMX()->GetStepArray())
			{
				for(GdtfMacroDMXValuePtr value : step->GetDMXValueArray())
				{
					IXMLFileNodePtr node;
					value->GetNode(node);

					for(GdtfDmxChannelPtr channel : dmxMode->GetChannelArray())
					{
						if (channel->GetNodeReference() == value->GetUnresolvedDMXChannel()) { value->SetDMXChannel(channel); break; }
					}

					if(value->GetDMXChannel())
					{
						
						DmxValue dmxVal = 0;						
						GdtfConverter::ConvertDMXValue(value->GetUnresolvedDMXValue(), node, value->GetDMXChannel()->GetChannelBitResolution(), dmxVal);
						value->SetValue(dmxVal);
					}
					else
					{
						GdtfParsingError error (GdtfDefines::EGdtfParsingError::eDmxMacroDmxValueChannelReference, node);
						SceneData::GdtfFixture::AddError(error);
					}
				}
			}
		}

		if(macro->GetMacroVisual())
		{
			for (GdtfMacroVisualStepPtr step : macro->GetMacroVisual()->GetVisualStepArray())
			{
				for (GdtfMacroVisualValuePtr value : step->GetVisualValueArray())
				{
					for (GdtfDmxChannelPtr channel : dmxMode->GetChannelArray())
					{
						for (GdtfDmxLogicalChannelPtr logChannel : channel->GetLogicalChannelArray())
						{
							for (GdtfDmxChannelFunctionPtr channelFunction : logChannel->GetDmxChannelFunctions())
							{
								if (channelFunction->GetNodeReference() == value->GetUnresolvedChannelFunctionRef())
								{
									value->SetChannelFunction(channelFunction);

									IXMLFileNodePtr node;
									value->GetNode(node);
								
									DmxValue dmxVal = 0;
									GdtfConverter::ConvertDMXValue(value->GetUnresolvedDMXValue(), node, channelFunction->GetParentDMXChannel()->GetChannelBitResolution(), dmxVal);
									value->SetDmxValue(dmxVal);
								}
							}
						}
					}
				}
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

		ResolveMacroRefs(dmxMode);
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

		// ----------------------------------------------------------------------------------------
		// DmxChannel.InitialFunction
		GdtfDmxChannelFunctionPtr initialFunctionPtr = nullptr;
		TXString unresolvedInitialFunction = chnl->GetUnresolvedInitialFunction();
		if (!unresolvedInitialFunction.IsEmpty())
		{
			for (GdtfDmxLogicalChannelPtr logicalChannel : chnl->GetLogicalChannelArray())
			{
				for (GdtfDmxChannelFunctionPtr channelFunction : logicalChannel->GetDmxChannelFunctions())
				{
					if (channelFunction->GetNodeReference() == unresolvedInitialFunction) { initialFunctionPtr = channelFunction; break;}
				}
				
				if (initialFunctionPtr != nullptr) { break; }
			}
			
			ASSERTN(kEveryone, initialFunctionPtr != nullptr);
			if (initialFunctionPtr) { chnl->SetInitialFunction(initialFunctionPtr); }
			else
			{
				IXMLFileNodePtr node;
				chnl->GetNode(node);
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureDMXChannelUnresolvedChannelFunction, node);
				SceneData::GdtfFixture::AddError(error);
			}
		}
		else
		{
			//If there is no initialfunction defined, we set the first one by default
			if(chnl->GetLogicalChannelArray().size() > 0 && chnl->GetLogicalChannelArray()[0]->GetDmxChannelFunctions().size() > 0)
			{
				chnl->SetInitialFunction(chnl->GetLogicalChannelArray()[0]->GetDmxChannelFunctions()[0]);
			}
			else
			{
				IXMLFileNodePtr node;
				chnl->GetNode(node);
				GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureDMXChannelMissingChannelFunction, node);
				SceneData::GdtfFixture::AddError(error);
			}
			
		}
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
		GdtfAttributePtr attrPtr = getAttributeByRef(logChnl->GetUnresolvedAttribRef());
				
		ASSERTN(kEveryone, attrPtr != nullptr);
		if (attrPtr != nullptr)	{ logChnl->SetAttribute(attrPtr); }
		else
		{
			IXMLFileNodePtr node;
			logChnl->GetNode(node);
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureLogicalChannelMissingAttribute, node); SceneData::GdtfFixture::AddError(error);
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
		GdtfAttributePtr attrPtr = getAttributeByRef(chnlFunc->getUnresolvedAttrRef());

		ASSERTN(kEveryone, attrPtr != nullptr);
		if (attrPtr != nullptr)	{ chnlFunc->SetAttribute(attrPtr); }
		else
		{
			IXMLFileNodePtr node;
			chnlFunc->GetNode(node);
			GdtfParsingError error (GdtfDefines::EGdtfParsingError::eChannelFunctionMissingAttribute, node); SceneData::GdtfFixture::AddError(error);
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
		TXString unresolvedEmitterRef = chnlFunc->getUnresolvedEmitterRef();
		if ( ! unresolvedEmitterRef.IsEmpty())
		{
			GdtfPhysicalEmitterPtr emtPtr = getEmiterByRef(unresolvedEmitterRef);
			chnlFunc->SetEmitter(emtPtr);
		}

        // ----------------------------------------------------------------------------------------		
        // Filter Refs
        TXString unresolvedFilterRef = chnlFunc->getUnresolvedFilterRef();
        if (!unresolvedFilterRef.IsEmpty()) 
        {
            GdtfFilter* filter = getFilterByRef(unresolvedFilterRef);
            chnlFunc->SetFilter(filter);
        }
        // ----------------------------------------------------------------------------------------
		// DmxChannelFunction.Default (For GDTF 1.0 files)
		if(chnlFunc->GetDefaultValue() == 0)
		{
			DmxValue oldDefault = dmxLogChnl->GetParentDMXChannel()->GetOldDefaultValue();
			if(oldDefault > 0)
			{
				chnlFunc->SetDefaultValue(oldDefault);
			}
		}
		

	}
}

void GdtfFixture::CheckForMissingModeMasters()
{	
	for (GdtfDmxModePtr mode : fDmxModes)
	{
		for(GdtfDmxChannelPtr channel : mode->GetChannelArray())
		{
			for(GdtfDmxLogicalChannelPtr logicalChannel : channel->GetLogicalChannelArray())
			{
				TGdtfDmxChannelFuntionArray channelFunctions = logicalChannel->GetDmxChannelFunctions();

                if(channelFunctions.size() > 0)
                {
                    for(size_t i = 0; i < channelFunctions.size() - 1; i++)
                    {
                        GdtfDmxChannelFunctionPtr function = channelFunctions[i];
                        // ----------------------------------------------------------------------------------------
                        DmxValue functionStart 	= function->GetStartAdress();
                        DmxValue functionEnd	= function->GetEndAdress();

                        for(size_t j = i+1; j < channelFunctions.size(); j++)
                        {
                            GdtfDmxChannelFunctionPtr currentFunction = channelFunctions[j];

                            DmxValue currentFunctionStart	= currentFunction->GetStartAdress();
                            DmxValue currentFunctionEnd		= currentFunction->GetEndAdress();
                            
                            if(functionStart <= currentFunctionEnd && currentFunctionStart <= functionEnd)
                            {
                                //These two functions have conflicting DMX ranges.

                                GdtfDmxChannel* 		functionMMChannel 	= function->GetModeMaster_Channel();
                                GdtfDmxChannelFunction* functionMMFunction 	= function->GetModeMaster_Function();

                                //First we check if a mode master is defined
                                if(!functionMMChannel && !functionMMFunction)
                                {
                                    //If not, we throw an error.
                                    GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureChannelFunctionMissingModeMaster);
                                    SceneData::GdtfFixture::AddError(error);
                                }
                                else
                                {
                                    //If there is one, we have to check if they're the same.
                                    GdtfDmxChannel* 		currentFunctionMMChannel 	= currentFunction->GetModeMaster_Channel();
                                    GdtfDmxChannelFunction* currentFunctionMMFunction	= currentFunction->GetModeMaster_Function();
                                    if(functionMMChannel == currentFunctionMMChannel || functionMMFunction == currentFunctionMMFunction)
                                    {
                                        //If they're the same we have to check that their ranges don't overlap.
                                        DmxValue functionMMStart 		= function->GetModeMasterDmxStart();
                                        DmxValue functionMMEnd			= function->GetModeMasterDmxEnd();

                                        DmxValue currentFunctionMMStart	= currentFunction->GetModeMasterDmxStart();
                                        DmxValue currentFunctionMMEnd	= currentFunction->GetModeMasterDmxEnd();
                                        
                                        if(functionMMStart <= currentFunctionMMEnd && currentFunctionMMStart <= functionMMEnd)
                                        {
                                            //If they do, we throw an error.
                                            GdtfParsingError error (GdtfDefines::EGdtfParsingError::eFixtureChannelFunctionMissingModeMaster);
                                            SceneData::GdtfFixture::AddError(error);
                                        }
                                    }
                                }
                                break;
                            }
                        }
                    }
                }
			}
		}
	}	
}

GdtfFixture::GdtfFixture()
{
	fReaded					= false;
	fHasLinkedGuid			= false;     
	fNoFeature				= nullptr;   
}

GdtfFixture::~GdtfFixture()
{   

    for (GdtfActivationGroupPtr obj		: fActivationGroups){ delete obj; }
    for (GdtfFeatureGroupPtr obj		: fFeatureGroups)   { delete obj; }
    for (GdtfAttributePtr obj			: fAttributes)      { delete obj; }
	for (GdtfWheelPtr obj				: fWheels)			{ delete obj; }
	for (GdtfGeometry* obj				: fGeometries)		{ delete obj; }
	for (GdtfModel* obj					: fModels)			{ delete obj; }	
	for (GdtfDmxModePtr obj				: fDmxModes)		{ delete obj; }
	for (GdtfRevisionPtr obj			: fRevisions)		{ delete obj; }

    // Delete Local Files
	for (size_t i = 0; i < fLocalFiles.size(); i++)
	{
		IFileIdentifierPtr file = fLocalFiles[i];
		file->DeleteOnDisk();
	}
}

size_t GdtfFixture::GetAttachedFileCount()
{
    return fLocalFilesFullPath.size();
}

bool GdtfFixture::GetAttachedFileCountAt(size_t at, TXString*& outFile)
{
	bool retVal = (at < fLocalFilesFullPath.size());
	if(retVal)	{ outFile = &fLocalFilesFullPath.at(at); }

    return retVal;
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
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureName,				fName);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureShortName,			fShortName);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureLongName,			fLongName);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureManufacturer,		fManufacturer);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureDescription,		fFixtureTypeDescription);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureTypeID,			GdtfConverter::ConvertUUID(fGuid));
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureThumbnail,			fTumbnailName);
	pNode->SetNodeAttributeValue(XML_GDTF_FixtureCanHaveChildren,	GdtfConverter::ConvertEGdtfCanHaveChildren(fCanHaveChildren));
	
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
	// Print PhysicalDescriptions    
    fPhysicalDesciptions.WriteToNode(pNode);
    	
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
	// Print Prorocols
    fProtocollContainer.WriteToNode(pNode);
}

void GdtfFixture::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureName,						fName);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureShortName,					fShortName);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureLongName,					fLongName);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureManufacturer,				fManufacturer);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureDescription,				fFixtureTypeDescription);
	TXString uuid; pNode->GetNodeAttributeValue(XML_GDTF_FixtureTypeID,		uuid );	GdtfConverter::ConvertUUID(uuid, pNode, fGuid);
	pNode->GetNodeAttributeValue(XML_GDTF_FixtureThumbnail,					fTumbnailName);
	TXString canHaveChildren; pNode->GetNodeAttributeValue(XML_GDTF_FixtureCanHaveChildren,	 canHaveChildren); GdtfConverter::ConvertEGdtfCanHaveChildren(canHaveChildren, pNode, fCanHaveChildren);
	
	
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

    // Read PhysicalDesciptions
    IXMLFileNodePtr physDescrNode;
    if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_FixtureChildNodePhysicalDesrip, &physDescrNode) ))
    {
        fPhysicalDesciptions.ReadFromNode(physDescrNode);
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
							else if (childNodeName == XML_GDTF_FilterColorNodeName)			{ geometry = new GdtfGeometryColorFilter(nullptr);}
							else if (childNodeName == XML_GDTF_FilterGoboNodeName)			{ geometry = new GdtfGeometryGoboFilter(nullptr);}
							else if (childNodeName == XML_GDTF_FilterShaperNodeName)		{ geometry = new GdtfGeometryShaperFilter(nullptr);}
							else if (childNodeName == XML_GDTF_LampNodeName)				{ geometry = new GdtfGeometryLamp(nullptr);}
							else if (childNodeName == XML_GDTF_MediaServerCameraNodeName)	{ geometry = new GdtfGeometryMediaServerCamera(nullptr);}
							else if (childNodeName == XML_GDTF_MediaServerLayerNodeName)	{ geometry = new GdtfGeometryMediaServerLayer(nullptr);}
							else if (childNodeName == XML_GDTF_MediaServerMasterNodeName)	{ geometry = new GdtfGeometryMediaServerMaster(nullptr);}
							else if (childNodeName == XML_GDTF_GeometryReferenceNodeName)	{ geometry = new GdtfGeometryReference(nullptr);}
							else if (childNodeName == XML_GDTF_DisplayNodeName)				{ geometry = new GdtfGeometryDisplay(nullptr);}
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
									 GdtfDmxModePtr dmxMode = new GdtfDmxMode(this, "");
									 
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
    // -
	
	// ------------------------------------------------------------------------------------
	// Read macros
    // -
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
	needed.push_back(XML_GDTF_FixtureLongName);
	needed.push_back(XML_GDTF_FixtureManufacturer);
	needed.push_back(XML_GDTF_FixtureDescription);
	needed.push_back(XML_GDTF_FixtureTypeID);
	optional.push_back(XML_GDTF_FixtureThumbnail);
	optional.push_back(XML_GDTF_LinkedUuid);
	optional.push_back(XML_GDTF_FixtureCanHaveChildren);

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

GdtfGeometryPtr GdtfFixture::AddGeometryMediaServerCamera(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryMediaServerCamera(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfFixture::AddGeometryMediaServerLayer(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryMediaServerLayer(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfFixture::AddGeometryMediaServerMaster(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryMediaServerMaster(name, refToModel, ma, nullptr);
	
	fGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfFixture::AddGeometryDisplay(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryDisplay(name, refToModel, ma, nullptr);

	fGeometries.push_back(geo);
	
	return geo;
}

GdtfDmxMode* GdtfFixture::AddDmxMode(const TXString& name)
{
	GdtfDmxMode* mode = new  GdtfDmxMode(this, name);
	
	fDmxModes.push_back(mode);
	
	return mode;
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

const TXString& GdtfFixture::GetLongName() const
{
    return fLongName;
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

bool GdtfFixture::GetCanHaveChildren() const
{
    return fCanHaveChildren;
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

GdtfPhysicalDescriptions& SceneData::GdtfFixture::GetPhysicalDesciptionsContainer()
{
    return fPhysicalDesciptions;
}

void GdtfFixture::SetName(const TXString& name)
{
	fName = name;
}

void GdtfFixture::SetShortName(const TXString& shortName)
{
	fShortName = shortName;
}

void GdtfFixture::SetLongName(const TXString& longName)
{
	fLongName = longName;
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

void GdtfFixture::SetCanHaveChildren(bool canHaveChildren)
{
	fCanHaveChildren = canHaveChildren;
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
    pNode->SetNodeAttributeValue(XML_GDTF_ColorRenderingIndexGroup_ColorTemp, GdtfConverter::ConvertDouble(fColorTemperature) );

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
    TXString colorTempStr; pNode->GetNodeAttributeValue(XML_GDTF_ColorRenderingIndexGroup_ColorTemp, colorTempStr);
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
	optional.push_back(XML_GDTF_ColorRenderingIndexGroup_ColorTemp);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfCRI::GdtfCRI()
{
    fCES = EGdtfColorSample::CES_01;  // Default CES01
    fCRI = 100;          // The color rendering index for this sample.Size: 1 byte; Default value : 100
}

SceneData::GdtfCRI::GdtfCRI(EGdtfColorSample ces, Uint8 cri)
{
    fCES = ces;
    fCRI = cri;
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

Uint8 SceneData::GdtfCRI::GetColorRenderingIndex() const
{
    return fCRI;
}

void SceneData::GdtfCRI::SetColorSample(EGdtfColorSample val)
{
    fCES = val;
}

void SceneData::GdtfCRI::SetColorRenderingIndex(Uint8 val)
{
    fCRI = val;
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
    pNode->SetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_CES, GdtfConverter::ConvertEGdtfColorSampleEnum(fCES) );
    
    pNode->SetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_CRI, GdtfConverter::ConvertInteger(fCRI) );
}

void SceneData::GdtfCRI::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnReadFromNode(pNode);

    //------------------------------------------------------------------------------------
    // Get the attributes	
    TXString cesStr;  pNode->GetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_CES, cesStr);
    GdtfConverter::ConvertEGdtfColorSampleEnum(cesStr, pNode, fCES);
    //
    TXString colorRenderingIndexStr; pNode->GetNodeAttributeValue(XML_GDTF_ColorRenderingIndex_CRI, colorRenderingIndexStr);
    GdtfConverter::ConvertInteger(colorRenderingIndexStr, pNode, fCRI);
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
	optional.push_back(XML_GDTF_ColorRenderingIndex_CES);
	optional.push_back(XML_GDTF_ColorRenderingIndex_CRI);

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
	pNode->SetNodeAttributeValue(XML_GDTF_FTRDM_AttrManufacturerID, GdtfConverter::ConvertHexValue(fManufacturerID) );
	pNode->SetNodeAttributeValue(XML_GDTF_FTRDM_AttrDeviceModelID,  GdtfConverter::ConvertHexValue(fDeviceModelID)  );	 
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
	GdtfConverter::ConvertHexValue(manufactStr, pNode, fManufacturerID);
	
	TXString deviceModelStr;  pNode->GetNodeAttributeValue(XML_GDTF_FTRDM_AttrDeviceModelID, deviceModelStr);
	GdtfConverter::ConvertHexValue(deviceModelStr, pNode, fDeviceModelID);
    
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

SceneData::GdtfFTRDM::GdtfFTRDM(size_t manufacturerID, size_t deviceModelID) : GdtfFTRDM()
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

size_t SceneData::GdtfFTRDM::GetManufacturerID() const
{
	return fManufacturerID;
}

size_t SceneData::GdtfFTRDM::GetDeviceModelID() const
{
	return fDeviceModelID;
}

const TGdtfSoftwareVersionIDArray& SceneData::GdtfFTRDM::GetSoftwareVersIDs() const
{
	return fSoftwareVersionIDArray;
}

void SceneData::GdtfFTRDM::SetManufacturerID(size_t val)
{
	fManufacturerID = val;
}

void SceneData::GdtfFTRDM::SetDeviceModelID(size_t val)
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
    pNode->SetNodeAttributeValue(XML_GDTF_DMXPersonalityValue, GdtfConverter::ConvertHexValue(fValue));
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
    GdtfConverter::ConvertHexValue(valueStr, pNode, fValue);

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

GdtfMacroDMXStepPtr SceneData::GdtfMacroDMX::AddDmxStep(double& duration)
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
	fDMXChannel = nullptr;
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

SceneData::GdtfMacroDMXStep::GdtfMacroDMXStep(double duration)
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

double SceneData::GdtfMacroDMXStep::GetDuration() const
{
	return fDuration;
}

TGdtfMacroDMXValueArray SceneData::GdtfMacroDMXStep::GetDMXValueArray() const
{
	return fDMXValues;
}

void SceneData::GdtfMacroDMXStep::SetDuration(double d)
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
	pNode->SetNodeAttributeValue(XML_GDTF_MacroDMXStepDuration, GdtfConverter::ConvertDouble(fDuration) );
	
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
	GdtfConverter::ConvertDouble(durationStr, pNode, fDuration);
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

const TXString & SceneData::GdtfMacroDMXValue::GetUnresolvedDMXValue() const
{
	return funresolvedValue;
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

	EGdtfChannelBitResolution resolution = EGdtfChannelBitResolution::eGdtfChannelBitResolution_8;
	ASSERTN(kEveryone, fDMXChannel != nullptr);
	if(fDMXChannel)
	{
		resolution = fDMXChannel->GetChannelBitResolution();
	}

	//------------------------------------------------------------------------------------
	// Print the attributes
	pNode->SetNodeAttributeValue(XML_GDTF_MacroDMXValue_AttrValue, GdtfConverter::ConvertDMXValue(fValue, resolution));
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
	pNode->GetNodeAttributeValue(XML_GDTF_MacroDMXValue_AttrValue, funresolvedValue);
	//
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

double SceneData::GdtfMacroVisualStep::getDuration()
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

void SceneData::GdtfMacroVisualStep::setDuration(double d)
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
	pNode->SetNodeAttributeValue(XML_GDTF_MacroVisualStep_AttrDuration, GdtfConverter::ConvertDouble(fDuration));
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
	GdtfConverter::ConvertDouble(durationStr, pNode, fDuration);
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

const TXString & SceneData::GdtfMacroVisualValue::GetUnresolvedDMXValue() const
{
	return funresolvedValue;
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
	if(fChannelFunctionRef) {resolution = fChannelFunctionRef->GetParentDMXChannel()->GetChannelBitResolution(); }
	
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

	pNode->GetNodeAttributeValue(XML_GDTF_MacroVisualValue_AttrValue, funresolvedValue);
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
    pNode->SetNodeAttributeValue(XML_GDTF_SoftwareVersionID_Value, GdtfConverter::ConvertHexValue(fValue));

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
    GdtfConverter::ConvertHexValue( valueStr, pNode, fValue);

    // Read the childs
    GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_DMXPersonalityNodeNam, [this](IXMLFileNodePtr objNode) -> void
    {
        GdtfDMXPersonalityPtr dmxPerso = new GdtfDMXPersonality();

        dmxPerso->ReadFromNode(objNode);

        fDmxPersonalityArray.push_back(dmxPerso);
        return;
    });
}

SceneData::GdtfPhysicalDescriptions::GdtfPhysicalDescriptions()
{
	fOperatingTemperatureLow 	= 0.0;
	fOperatingTemperatureHigh 	= 40.0;
	fWeight 					= 0.0;
	fLegHeight 					= 0.0;
}

SceneData::GdtfPhysicalDescriptions::~GdtfPhysicalDescriptions()
{
    for (GdtfPhysicalEmitter* 	o : fEmitters)    		{ delete o; }
    for (GdtfFilter*          	o : fFilters)     		{ delete o; }
    for (GdtfDMXProfile*      	o : fDmxProfiles) 		{ delete o; }
    for (GdtfCRIGroup*        	o : fCRI_Groups)  		{ delete o; }
	for (GdtfConnector*       	o : fConnectors)  		{ delete o; }

	for (GdtfPowerConsumption*	o : fPowerConsumptions) { delete o; }
}

EGdtfObjectType SceneData::GdtfPhysicalDescriptions::GetObjectType()
{
    return EGdtfObjectType::eGdtfPhysicalDescription;
}

GdtfColorSpace* SceneData::GdtfPhysicalDescriptions::GetColorSpace()
{
    return & fColorSpace;
}

const TGdtfPhysicalEmitterArray& SceneData::GdtfPhysicalDescriptions::GetPhysicalEmitterArray()
{
    return fEmitters;
}

const TGdtfFilterArray & SceneData::GdtfPhysicalDescriptions::GetFilterArray()
{
    return fFilters;
}

const TGdtfDMXProfileArray& SceneData::GdtfPhysicalDescriptions::GetDmxProfileArray()
{
    return fDmxProfiles;
}

const TGdtf_CRIGroupArray & SceneData::GdtfPhysicalDescriptions::GetCRIGroupArray()
{
    return fCRI_Groups;
}

const TGdtfConnectorArray & SceneData::GdtfPhysicalDescriptions::GetConnectorArray()
{
    return fConnectors;
}

const TGdtfPowerConsumptionArray & SceneData::GdtfPhysicalDescriptions::GetPowerConsumptionArray()
{
    return fPowerConsumptions;
}

double GdtfPhysicalDescriptions::GetOperatingTemperatureLow()
{
    return fOperatingTemperatureLow;
}

double GdtfPhysicalDescriptions::GetOperatingTemperatureHigh()
{
    return fOperatingTemperatureHigh;
}

double GdtfPhysicalDescriptions::GetWeight()
{
    return fWeight;
}

double GdtfPhysicalDescriptions::GetLegHeight()
{
    return fLegHeight;
}

void GdtfPhysicalDescriptions::SetOperatingTemperatureLow(double value)
{
	fOperatingTemperatureLow = value;
}

void GdtfPhysicalDescriptions::SetOperatingTemperatureHigh(double value)
{
	fOperatingTemperatureHigh = value;
}

void GdtfPhysicalDescriptions::SetWeight(double value)
{
	fWeight = value;
}

void GdtfPhysicalDescriptions::SetLegHeight(double value)
{
	fLegHeight = value;
}

GdtfPhysicalEmitterPtr SceneData::GdtfPhysicalDescriptions::AddEmitter(const TXString & name, CCieColor color)
{
	GdtfPhysicalEmitterPtr emitter = new  GdtfPhysicalEmitter(name, color);
	
	fEmitters.push_back(emitter);
	
	return emitter;
}

GdtfFilterPtr SceneData::GdtfPhysicalDescriptions::AddFilter(const TXString& name, CCieColor color)
{
    GdtfFilterPtr filter = new GdtfFilter(name, color);

    fFilters.push_back(filter);

    return filter;
}

GdtfDMXProfilePtr SceneData::GdtfPhysicalDescriptions::AddDmxProfile()
{
    GdtfDMXProfilePtr dmxProf = new GdtfDMXProfile();
    
    fDmxProfiles.push_back(dmxProf);
    
    return dmxProf;
}

GdtfCRIGroupPtr SceneData::GdtfPhysicalDescriptions::AddCRIGroup(double colorTsemp)
{
    GdtfCRIGroupPtr criGroup = new GdtfCRIGroup(colorTsemp);
    fCRI_Groups.push_back(criGroup);

    return criGroup;
}

GdtfConnectorPtr SceneData::GdtfPhysicalDescriptions::AddConnector(const TXString& name,  const TXString& type)
{
    GdtfConnectorPtr connector = new GdtfConnector(name, type);
    fConnectors.push_back(connector);

    return connector;
}

GdtfPowerConsumptionPtr SceneData::GdtfPhysicalDescriptions::AddPowerConsumption(GdtfConnectorPtr connector)
{
    GdtfPowerConsumptionPtr powerConsumption = new GdtfPowerConsumption(connector);
    fPowerConsumptions.push_back(powerConsumption);

    return powerConsumption;
}

TXString SceneData::GdtfPhysicalDescriptions::GetNodeName()
{
    return XML_GDTF_FixtureChildNodePhysicalDesrip;
}

void SceneData::GdtfPhysicalDescriptions::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);
    
    //------------------------------------------------------------------------------------
    // Print the attributes        
    fColorSpace.WriteToNode(pNode);
    
    //------------------------------------------------------------------------------------
    // Print Filter        
    IXMLFileNodePtr filtersGroupNode;
    if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FiltersCollect, &filtersGroupNode))) 
    {
        for (GdtfFilter* filter : fFilters)
        {
            filter->WriteToNode(filtersGroupNode);
        }
    }
    
    // Print Emitters (physicalDescription child)
	IXMLFileNodePtr emittersGroupNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_PhysicalDescriptionsEmitterCollect, & emittersGroupNode)))
	{
		for (GdtfPhysicalEmitterPtr emitter : fEmitters)
		{
			emitter->WriteToNode(emittersGroupNode);
		}
	}
		
	// Print DmxProfiles (physicalDescription child)
	IXMLFileNodePtr dmxProfGroupNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_DMX_ProfileCollect, &dmxProfGroupNode)))
	{
		for (GdtfDMXProfilePtr dmxProfile : fDmxProfiles)
		{
			dmxProfile->WriteToNode(dmxProfGroupNode);
		}
	}
		
	// CRI_Collect (PhysicalDescription child)
	IXMLFileNodePtr CRI_CollectNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_ColorRenderingIndexCollect, &CRI_CollectNode)))
	{
		for (GdtfCRIGroupPtr criGroup : fCRI_Groups)
		{
			criGroup->WriteToNode(CRI_CollectNode);
		}
		
	}

	// Print Connectors (physicalDescription child)
	IXMLFileNodePtr ConnectorNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_ConnectorCollect, &ConnectorNode)))
	{
		for (GdtfConnectorPtr connector : fConnectors)
		{
			connector->WriteToNode(ConnectorNode);
		}
		
	}

	// Print Properties (physicalDescription child)
	IXMLFileNodePtr PropertiesNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_PropertiesCollect, &PropertiesNode)))
	{
		for (GdtfPowerConsumptionPtr powerConsumption : fPowerConsumptions)
		{
			powerConsumption->WriteToNode(PropertiesNode);
		}

		IXMLFileNodePtr OperatingTemperatureNode;
		if(VCOM_SUCCEEDED(PropertiesNode->CreateChildNode(XML_GDTF_OperatingTemperatureNodeName, &OperatingTemperatureNode)))
		{
			OperatingTemperatureNode->SetNodeAttributeValue(XML_GDTF_OperatingTemperatureLow,	GdtfConverter::ConvertDouble(fOperatingTemperatureLow));
			OperatingTemperatureNode->SetNodeAttributeValue(XML_GDTF_OperatingTemperatureHigh, GdtfConverter::ConvertDouble(fOperatingTemperatureHigh));
		}

		IXMLFileNodePtr WeightNode;
		if(VCOM_SUCCEEDED(PropertiesNode->CreateChildNode(XML_GDTF_WeightNodeName, &WeightNode)))
		{
			WeightNode->SetNodeAttributeValue(XML_GDTF_WeightValue,	GdtfConverter::ConvertDouble(fWeight));
		}

		IXMLFileNodePtr LegHeightNode;
		if(VCOM_SUCCEEDED(PropertiesNode->CreateChildNode(XML_GDTF_LegHeightNodeName, &LegHeightNode)))
		{
			LegHeightNode->SetNodeAttributeValue(XML_GDTF_LegHeightValue,	GdtfConverter::ConvertDouble(fLegHeight));
		}

	}

}

void SceneData::GdtfPhysicalDescriptions::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
	IXMLFileNodePtr colorSpace;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_ColorSpaceNode, & colorSpace)))
	{
		fColorSpace.ReadFromNode(colorSpace);
	}

	// ------------------------------------------------------------------------------------
	// Read Filters
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_FiltersCollect, XML_GDTF_FilterNode, [this] (IXMLFileNodePtr objNode) -> void
									{
										// Create the object
										GdtfFilterPtr filter = new GdtfFilter();
										 
										// Read from node
										filter->ReadFromNode(objNode);
										 
										// Add to list
										fFilters.push_back(filter);
										return;
									});

    // Read Emitters (PhysicalDescription Child)
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_PhysicalDescriptionsEmitterCollect, XML_GDTF_EmitterNodeName, [this] (IXMLFileNodePtr objNode) -> void
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
    // Read CRIs
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_ColorRenderingIndexCollect, XML_GDTF_ColorRenderingIndexGroup, [this](IXMLFileNodePtr objNode) -> void
									{
										GdtfCRIGroupPtr criGroup = new GdtfCRIGroup();
											
										// Read from node
										criGroup->ReadFromNode(objNode);
											
										fCRI_Groups.push_back(criGroup);
										return;
									});
	
	// Read Connectors (PhysicalDescription Child)
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_ConnectorCollect, XML_GDTF_ConnectorNodeName, [this] (IXMLFileNodePtr objNode) -> void
									{
										// Create the object
										GdtfConnectorPtr connector = new GdtfConnector();
										 
										// Read from node
										connector->ReadFromNode(objNode);
										 
										// Add to list
										fConnectors.push_back(connector);
										return;
									});
	
	// Read Properties (PhysicalDescription Child)
		//PowerConsumption
	GdtfConverter::TraverseNodes(pNode, XML_GDTF_PropertiesCollect, XML_GDTF_PowerConsumptionNodeName, [this] (IXMLFileNodePtr objNode) -> void
									{
										// Create the object
										GdtfPowerConsumptionPtr powerConsumption = new GdtfPowerConsumption();
										 
										// Read from node
										powerConsumption->ReadFromNode(objNode);
										 
										// Add to list
										fPowerConsumptions.push_back(powerConsumption);
										return;
									});
	
	IXMLFileNodePtr PropertiesNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_GDTF_PropertiesCollect, & PropertiesNode)))
	{
		//OperatingTemperature
		IXMLFileNodePtr OperatingTemperatureNode;
		PropertiesNode->GetChildNode(XML_GDTF_OperatingTemperatureNodeName, &OperatingTemperatureNode);
		if(OperatingTemperatureNode != nullptr)
		{
			TXString operatingTemperatureLowStr; OperatingTemperatureNode->GetNodeAttributeValue(XML_GDTF_OperatingTemperatureLow, operatingTemperatureLowStr);
			GdtfConverter::ConvertDouble(operatingTemperatureLowStr, OperatingTemperatureNode, fOperatingTemperatureLow);

			TXString operatingTemperatureHighStr; OperatingTemperatureNode->GetNodeAttributeValue(XML_GDTF_OperatingTemperatureHigh, operatingTemperatureHighStr);
			GdtfConverter::ConvertDouble(operatingTemperatureHighStr, OperatingTemperatureNode, fOperatingTemperatureHigh);	
		}

		//Weight
		IXMLFileNodePtr WeightNode;
		PropertiesNode->GetChildNode(XML_GDTF_WeightNodeName, &WeightNode);
		if(WeightNode != nullptr)
		{
			TXString weightStr; WeightNode->GetNodeAttributeValue(XML_GDTF_WeightValue, weightStr);
			GdtfConverter::ConvertDouble(weightStr, WeightNode, fWeight);	
		}

		//LegHeight
		IXMLFileNodePtr LegHeightNode;
		PropertiesNode->GetChildNode(XML_GDTF_LegHeightNodeName, &LegHeightNode);
		if(LegHeightNode != nullptr)
		{
			TXString legHeightStr; LegHeightNode->GetNodeAttributeValue(XML_GDTF_LegHeightValue, legHeightStr);
			GdtfConverter::ConvertDouble(legHeightStr, LegHeightNode, fLegHeight);	
		}
	}
	
}

SceneData::GdtfColorSpace::GdtfColorSpace()
{
    fColorSpace = EGdtfColorSpace::sRGB;
}

SceneData::GdtfColorSpace::~GdtfColorSpace()
{
}

EGdtfObjectType SceneData::GdtfColorSpace::GetObjectType()
{
    return EGdtfObjectType::eGdtfColorSpace;
}

EGdtfColorSpace SceneData::GdtfColorSpace::GetColorSpace()
{
    return fColorSpace;
}

CCieColor SceneData::GdtfColorSpace::GetRed()
{
	CCieColor color = fRed;
	if(fColorSpace == EGdtfColorSpace::ANSI) 		{ color = CCieColor(0.7347, 0.2653, 100); }
	if(fColorSpace == EGdtfColorSpace::ProPhoto) 	{ color = CCieColor(0.7347, 0.2653, 100); }
	if(fColorSpace == EGdtfColorSpace::sRGB) 		{ color = CCieColor(0.6400, 0.3300, 21.26); }
    return color;
}

CCieColor SceneData::GdtfColorSpace::GetGreen()
{
	CCieColor color = fGreen;
	if(fColorSpace == EGdtfColorSpace::ANSI) 		{ color = CCieColor(0.1596, 0.8404, 100); }
	if(fColorSpace == EGdtfColorSpace::ProPhoto) 	{ color = CCieColor(0.1596, 0.8404, 100); }
	if(fColorSpace == EGdtfColorSpace::sRGB) 		{ color = CCieColor(0.3000, 0.6000, 71.52); }
    return color;
}

CCieColor SceneData::GdtfColorSpace::GetBlue()
{
	CCieColor color = fBlue;
	if(fColorSpace == EGdtfColorSpace::ANSI) 		{ color = CCieColor(0.0366, 0.001, 100); }
	if(fColorSpace == EGdtfColorSpace::ProPhoto) 	{ color = CCieColor(0.0366, 0.0001, 100); }
	if(fColorSpace == EGdtfColorSpace::sRGB) 		{ color = CCieColor(0.1500, 0.0600, 7.22); }
    return color;
}

CCieColor SceneData::GdtfColorSpace::GetWhite()
{
	CCieColor color = fWhitePoint;
	if(fColorSpace == EGdtfColorSpace::ANSI) 		{ color = CCieColor(0.4254, 0.4044, 100); }
	if(fColorSpace == EGdtfColorSpace::ProPhoto) 	{ color = CCieColor(0.3457, 0.3585, 100); }
	if(fColorSpace == EGdtfColorSpace::sRGB) 		{ color = CCieColor(0.3127, 0.3290, 100); }
    return color;
}

void SceneData::GdtfColorSpace::SetColorSpace(EGdtfColorSpace val)
{
    fColorSpace = val;
}

void SceneData::GdtfColorSpace::SetRed(CCieColor val)
{
    fRed = val;
}

void SceneData::GdtfColorSpace::SetGreen(CCieColor val)
{
    fGreen = val;
}

void SceneData::GdtfColorSpace::SetBlue(CCieColor val)
{
    fBlue = val;
}

void SceneData::GdtfColorSpace::SetWhite(CCieColor val)
{
    fWhitePoint = val;
}

TXString SceneData::GdtfColorSpace::GetNodeName()
{
    return XML_GDTF_ColorSpaceNode;
}

void SceneData::GdtfColorSpace::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);

    //------------------------------------------------------------------------------------
    // Print the attributes        
    pNode->SetNodeAttributeValue(XML_GDTF_ColorSpace_Mode, GdtfConverter::ConvertEGdtfColorSpace(fColorSpace) );
    
    if (fColorSpace == EGdtfColorSpace::Custom)
    {
        pNode->SetNodeAttributeValue(XML_GDTF_ColorSpace_Red,        GdtfConverter::ConvertColor(fRed) );
        pNode->SetNodeAttributeValue(XML_GDTF_ColorSpace_Green,      GdtfConverter::ConvertColor(fGreen) );
        pNode->SetNodeAttributeValue(XML_GDTF_ColorSpace_Blue,	     GdtfConverter::ConvertColor(fBlue) );
        pNode->SetNodeAttributeValue(XML_GDTF_ColorSpace_WhitePoint, GdtfConverter::ConvertColor(fWhitePoint) );
    }
}

void SceneData::GdtfColorSpace::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnReadFromNode(pNode);

    //------------------------------------------------------------------------------------
    // Get the attributes	
    TXString colorSpaceStr; pNode->GetNodeAttributeValue(XML_GDTF_ColorSpace_Mode, colorSpaceStr);
    GdtfConverter::ConvertEGdtfColorSpace( colorSpaceStr, pNode, fColorSpace);
    
    if (fColorSpace == EGdtfColorSpace::Custom)
    {
		TXString value_red;     pNode->GetNodeAttributeValue(XML_GDTF_ColorSpace_Red,     	 value_red );  	GdtfConverter::ConvertColor(value_red   , pNode, fRed);
		TXString value_green;   pNode->GetNodeAttributeValue(XML_GDTF_ColorSpace_Green,      value_green ); GdtfConverter::ConvertColor(value_green , pNode, fGreen);
		TXString value_blue;    pNode->GetNodeAttributeValue(XML_GDTF_ColorSpace_Blue,       value_blue );  GdtfConverter::ConvertColor(value_blue  , pNode, fBlue);
		TXString value_white;   pNode->GetNodeAttributeValue(XML_GDTF_ColorSpace_WhitePoint, value_white ); GdtfConverter::ConvertColor(value_white , pNode, fWhitePoint);
    }
}

void SceneData::GdtfColorSpace::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	optional.push_back(XML_GDTF_ColorSpace_Red);
	optional.push_back(XML_GDTF_ColorSpace_Green);
	optional.push_back(XML_GDTF_ColorSpace_Blue);
	optional.push_back(XML_GDTF_ColorSpace_WhitePoint);
	optional.push_back(XML_GDTF_ColorSpace_Mode);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

SceneData::GdtfFilter::GdtfFilter()
{
    fName = "";
}

SceneData::GdtfFilter::GdtfFilter(const TXString & name, const CCieColor &col)
{
    fName = name;
    fColor = col;
}

SceneData::GdtfFilter::~GdtfFilter()
{
    for (GdtfMeasurement* o : fMeasurementsArray) { delete o; };
}

EGdtfObjectType SceneData::GdtfFilter::GetObjectType()
{
    return EGdtfObjectType::eGdtfFilter;
}

const TXString & SceneData::GdtfFilter::GetName()
{
    return fName;
}

CCieColor SceneData::GdtfFilter::GetColor()
{
    return fColor;
}

const TGdtfMeasurementArray & SceneData::GdtfFilter::GetMeasurementsArray()
{
    return fMeasurementsArray;
}

void SceneData::GdtfFilter::SetName(const TXString & name)
{
    fName = name;
}

void SceneData::GdtfFilter::SetColor(CCieColor val)
{
    fColor = val;
}

GdtfMeasurement* SceneData::GdtfFilter::CreateMeasurement()
{
    GdtfMeasurement* m= new GdtfMeasurement(true);    
    fMeasurementsArray.push_back(m);

    return m;
}

TXString SceneData::GdtfFilter::GetNodeName()
{
    return XML_GDTF_FilterNode;
}

void SceneData::GdtfFilter::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);

    //------------------------------------------------------------------------------------
    // Print the attributes
    pNode->SetNodeAttributeValue(XML_GDTF_Filter_Name, fName);
    pNode->SetNodeAttributeValue(XML_GDTF_FilterColor, GdtfConverter::ConvertColor(fColor));

    //------------------------------------------------------------------------------------
    // Print the childs
    for (GdtfMeasurement* mes : fMeasurementsArray)
    {
         mes->WriteToNode(pNode);
    }
}

void SceneData::GdtfFilter::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnReadFromNode(pNode);

    //------------------------------------------------------------------------------------
    // Get the attributes	
    pNode->GetNodeAttributeValue(XML_GDTF_Filter_Name, fName);    
    
	// ------------------------------------------------------------------------------------
	// Get Color
	TXString color;
    if (VCOM_SUCCEEDED(pNode->GetNodeAttributeValue(XML_GDTF_FilterColor, color)))
    {
        if (color.IsEmpty() == false)
        {
            GdtfConverter::ConvertColor(color, pNode, fColor);
        }
    }	

    // Read the childs
    GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_MeasurementNodeName, [this](IXMLFileNodePtr objNode) -> void
    {
        GdtfMeasurement* measurePt = new GdtfMeasurement(true);

        measurePt->ReadFromNode(objNode);

        fMeasurementsArray.push_back(measurePt);
        return;
    });
}

TXString SceneData::GdtfFilter::GetNodeReference() 
{
    return GetName();
}

SceneData::GdtfMeasurement::GdtfMeasurement(bool forFilter)
{
    fPhysical 				= 0;
    fLuminousIntensity 		= 0;
    fTransmission 			= 0;
    fInterpolationTo 		= EGdtfInterpolationTo::Linear;
	fIsForFilter 			= forFilter;
}

SceneData::GdtfMeasurement::~GdtfMeasurement()
{
    for (GdtfMeasurementPoint* o : fMeasurementPoints) { delete o; };
}

EGdtfObjectType SceneData::GdtfMeasurement::GetObjectType()
{
    return EGdtfObjectType::eGdtfMeasurement;
}

double SceneData::GdtfMeasurement::GetPhysical()
{
    return fPhysical;
}

double SceneData::GdtfMeasurement::GetLuminousIntensity()
{
    return fLuminousIntensity;
}

double SceneData::GdtfMeasurement::GetTransmission()
{
    return fTransmission;
}

EGdtfInterpolationTo SceneData::GdtfMeasurement::GetInterpolationTo()
{
    return fInterpolationTo;
}

const TGdtfMeasurementPointArray & SceneData::GdtfMeasurement::GetMeasurementPointsArray()
{
    return fMeasurementPoints;
}

void SceneData::GdtfMeasurement::SetPhysical(double val)
{
    fPhysical = val;
}

void SceneData::GdtfMeasurement::SetLuminousIntensity(double val)
{
    fLuminousIntensity = val;
}

void SceneData::GdtfMeasurement::SetTransmission(double val)
{
    fTransmission = val;
}

void SceneData::GdtfMeasurement::SetInterpolationTo(EGdtfInterpolationTo val)
{
    fInterpolationTo = val;
}

GdtfMeasurementPoint* SceneData::GdtfMeasurement::CreateMeasurementPoint()
{
    GdtfMeasurementPointPtr mP = new GdtfMeasurementPoint();
    fMeasurementPoints.push_back(mP);
	return mP;
}

TXString SceneData::GdtfMeasurement::GetNodeName()
{
    return XML_GDTF_MeasurementNodeName;
}

void SceneData::GdtfMeasurement::OnPrintToFile(IXMLFileNodePtr pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnPrintToFile(pNode);

    //------------------------------------------------------------------------------------
    // Print the attributes 
    pNode->SetNodeAttributeValue(XML_GDTF_MeasurementPhysical,          GdtfConverter::ConvertDouble(fPhysical) );

	if(fIsForFilter) { pNode->SetNodeAttributeValue(XML_GDTF_MeasurementTransmission,      GdtfConverter::ConvertDouble(fTransmission) ); }
	else			 { pNode->SetNodeAttributeValue(XML_GDTF_MeasurementLuminousIntensity, GdtfConverter::ConvertDouble(fLuminousIntensity) ); }

    
    pNode->SetNodeAttributeValue(XML_GDTF_MeasurementInterpolationTo,   GdtfConverter::ConvertEGdtfInterpolationTo(fInterpolationTo) );
    //------------------------------------------------------------------------------------
    // Print the childs
    for (GdtfMeasurementPoint* mesPt: fMeasurementPoints)
    {
        mesPt->WriteToNode(pNode);
    }
}

void SceneData::GdtfMeasurement::OnReadFromNode(const IXMLFileNodePtr & pNode)
{
    //------------------------------------------------------------------------------------
    // Call the parent
    GdtfObject::OnReadFromNode(pNode);

    //------------------------------------------------------------------------------------
    // Get the attributes	
    TXString   physStr; pNode->GetNodeAttributeValue(XML_GDTF_MeasurementPhysical, physStr);
    GdtfConverter::ConvertDouble( physStr, pNode, fPhysical);

    TXString   lumiStr; pNode->GetNodeAttributeValue(XML_GDTF_MeasurementLuminousIntensity,  lumiStr);
    GdtfConverter::ConvertDouble( lumiStr, pNode, fLuminousIntensity);

	if(fIsForFilter)
	{
		TXString   transmStr; pNode->GetNodeAttributeValue(XML_GDTF_MeasurementTransmission,  transmStr);    
		GdtfConverter::ConvertDouble( transmStr, pNode, fTransmission);
	}
	else
	{
		TXString   interpolStr; pNode->GetNodeAttributeValue(XML_GDTF_MeasurementInterpolationTo, interpolStr);
		GdtfConverter::ConvertEGdtfInterpolationTo(interpolStr, pNode, fInterpolationTo);
	}


    // Read the childs
    GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_MeasurementPointNode, [this](IXMLFileNodePtr objNode) -> void
    {
        GdtfMeasurementPoint* measurePt = new GdtfMeasurementPoint();

        measurePt->ReadFromNode(objNode);

        fMeasurementPoints.push_back(measurePt);
        return;
    });
}

//------------------------------------------------------------------------------------
// GdtfConnector
GdtfConnector::GdtfConnector()
{
	fDmxBreak 	= 0;
    fGender 	= 0;
    fLength 	= 0.0;
}

GdtfConnector::GdtfConnector(const TXString& name, const TXString& type)
{
	fName		= name;
	fType		= type;
	fDmxBreak 	= 0;
    fGender 	= 0;
    fLength 	= 0.0;
}

GdtfConnector::~GdtfConnector()
{
}

void GdtfConnector::SetName(const TXString &name)
{
	fName = name;
}

void GdtfConnector::SetType(const TXString &type)
{
	fType = type;
}

void SceneData::GdtfConnector::SetDmxBreak(Uint32 dmxBreak)
{
    fDmxBreak = dmxBreak;
}

void SceneData::GdtfConnector::SetGender(Sint32 gender)
{
    fGender = gender;
}

void SceneData::GdtfConnector::SetLength(double length)
{
    fLength = length;
}

void GdtfConnector::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
	pNode->SetNodeAttributeValue(XML_GDTF_ConnectorName,		fName);
	pNode->SetNodeAttributeValue(XML_GDTF_ConnectorType,		fType);
	pNode->SetNodeAttributeValue(XML_GDTF_ConnectorDmxBreak, 	GdtfConverter::ConvertInteger(fDmxBreak));
	pNode->SetNodeAttributeValue(XML_GDTF_ConnectorGender,		GdtfConverter::ConvertInteger(fGender));
    pNode->SetNodeAttributeValue(XML_GDTF_ConnectorLength, 		GdtfConverter::ConvertDouble(fLength));
}

void GdtfConnector::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	// ------------------------------------------------------------------------------------
	// Read node attributes
	pNode->GetNodeAttributeValue(XML_GDTF_ConnectorName, fName);
	pNode->GetNodeAttributeValue(XML_GDTF_ConnectorType, fType);

    TXString dmxBreakStr;   pNode->GetNodeAttributeValue(XML_GDTF_ConnectorDmxBreak, dmxBreakStr);		
    GdtfConverter::ConvertInteger(dmxBreakStr, pNode, fDmxBreak);
	TXString genderStr;   pNode->GetNodeAttributeValue(XML_GDTF_ConnectorGender, genderStr);		
    GdtfConverter::ConvertInteger(genderStr, pNode, fGender);
	TXString lengthStr;   pNode->GetNodeAttributeValue(XML_GDTF_ConnectorLength, lengthStr);		
    GdtfConverter::ConvertDouble(lengthStr, pNode, fLength);
}

void GdtfConnector::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_ConnectorName);
	needed.push_back(XML_GDTF_ConnectorType);
	    
	optional.push_back(XML_GDTF_ConnectorDmxBreak);
	optional.push_back(XML_GDTF_ConnectorGender);
    optional.push_back(XML_GDTF_ConnectorLength);

	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfConnector::GetObjectType()
{
	return EGdtfObjectType::eGdtfConnector;
}

TXString GdtfConnector::GetNodeReference() 
{
    return GetName();
}

TXString GdtfConnector::GetNodeName()
{
	return XML_GDTF_ConnectorNodeName;
}

const TXString& GdtfConnector::GetName() const
{
	return fName;
}

const TXString& GdtfConnector::GetType() const
{
	return fType;
}

Uint32 GdtfConnector::GetDmxBreak()
{
	return fDmxBreak;
}

Sint32 GdtfConnector::GetGender()
{
    return fGender;
}

double GdtfConnector::GetLength()
{
    return fLength;
}

//------------------------------------------------------------------------------------
// GdtfPowerConsumption
GdtfPowerConsumption::GdtfPowerConsumption()
{
	fValue 			= 0.0;
	fPowerFactor 	= 1.0;
	fConnector 		= nullptr;
    fVoltageLow 	= 90.0;
    fVoltageHigh 	= 240.0;
	fFrequencyLow 	= 50.0;
    fFrequencyHigh 	= 60.0;
}

GdtfPowerConsumption::GdtfPowerConsumption(GdtfConnector* connector)
{
	fValue 			= 0.0;
	fPowerFactor 	= 1.0;
	fConnector 		= connector;
    fVoltageLow 	= 90.0;
    fVoltageHigh 	= 240.0;
	fFrequencyLow 	= 50.0;
    fFrequencyHigh 	= 60.0;
}

GdtfPowerConsumption::~GdtfPowerConsumption()
{
}

// Setters
void GdtfPowerConsumption::SetValue(double value)
{
	fValue = value;
}

void GdtfPowerConsumption::SetPowerFactor(double powerFactor)
{
	fPowerFactor = powerFactor;
}

void GdtfPowerConsumption::SetConnector(GdtfConnector* connector)
{
	fConnector = connector;
}

void GdtfPowerConsumption::SetVoltageLow(double voltageLow)
{
	fVoltageLow = voltageLow;
}

void GdtfPowerConsumption::SetVoltageHigh(double voltageHigh)
{
	fVoltageHigh = voltageHigh;
}

void GdtfPowerConsumption::SetFrequencyLow(double frequencyLow)
{
	fFrequencyLow = frequencyLow;
}

void GdtfPowerConsumption::SetFrequencyHigh(double frequencyHigh)
{
	fFrequencyHigh = frequencyHigh;
}

void GdtfPowerConsumption::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
	
	// ------------------------------------------------------------------------------------
	// Print node attributes
    pNode->SetNodeAttributeValue(XML_GDTF_PowerConsumptionValue, 			GdtfConverter::ConvertDouble(fValue));
	pNode->SetNodeAttributeValue(XML_GDTF_PowerConsumptionPowerFactor,		GdtfConverter::ConvertDouble(fPowerFactor));
	if(fConnector)	{ pNode->SetNodeAttributeValue(XML_GDTF_PowerConsumptionConnector,	fConnector->GetNodeReference()); }
	pNode->SetNodeAttributeValue(XML_GDTF_PowerConsumptionVoltageLow, 		GdtfConverter::ConvertDouble(fVoltageLow));
	pNode->SetNodeAttributeValue(XML_GDTF_PowerConsumptionVoltageHigh, 		GdtfConverter::ConvertDouble(fVoltageHigh));
	pNode->SetNodeAttributeValue(XML_GDTF_PowerConsumptionFrequencyLow, 	GdtfConverter::ConvertDouble(fFrequencyLow));
	pNode->SetNodeAttributeValue(XML_GDTF_PowerConsumptionFrequencyHigh,	GdtfConverter::ConvertDouble(fFrequencyHigh));

}

void GdtfPowerConsumption::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
	
	// ------------------------------------------------------------------------------------
	// Read node attributes
	TXString valueStr;   pNode->GetNodeAttributeValue(XML_GDTF_PowerConsumptionValue, valueStr);		
    GdtfConverter::ConvertDouble(valueStr, pNode, fValue);
	TXString powerFactorStr;   pNode->GetNodeAttributeValue(XML_GDTF_PowerConsumptionPowerFactor, powerFactorStr);		
    GdtfConverter::ConvertDouble(powerFactorStr, pNode, fPowerFactor);

	pNode->GetNodeAttributeValue(XML_GDTF_PowerConsumptionConnector, fUnresolvedConnector);

	TXString voltageLowStr;   pNode->GetNodeAttributeValue(XML_GDTF_PowerConsumptionVoltageLow, voltageLowStr);		
    GdtfConverter::ConvertDouble(voltageLowStr, pNode, fVoltageLow);
	TXString voltageHighStr;   pNode->GetNodeAttributeValue(XML_GDTF_PowerConsumptionVoltageHigh, voltageHighStr);		
    GdtfConverter::ConvertDouble(voltageHighStr, pNode, fVoltageHigh);
	TXString frequencyLowStr;   pNode->GetNodeAttributeValue(XML_GDTF_PowerConsumptionFrequencyLow, frequencyLowStr);		
    GdtfConverter::ConvertDouble(frequencyLowStr, pNode, fFrequencyLow);
	TXString frequencyHighStr;   pNode->GetNodeAttributeValue(XML_GDTF_PowerConsumptionFrequencyHigh, frequencyHighStr);		
    GdtfConverter::ConvertDouble(frequencyHighStr, pNode, fFrequencyHigh);
}

void GdtfPowerConsumption::OnErrorCheck(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnErrorCheck(pNode);

	//------------------------------------------------------------------------------------
	// Create needed and optional Attribute Arrays
	TXStringArray needed;
	TXStringArray optional;
	needed.push_back(XML_GDTF_PowerConsumptionConnector);
	    
	optional.push_back(XML_GDTF_PowerConsumptionValue);
	optional.push_back(XML_GDTF_PowerConsumptionPowerFactor);
	optional.push_back(XML_GDTF_PowerConsumptionVoltageLow);
	optional.push_back(XML_GDTF_PowerConsumptionVoltageHigh);
	optional.push_back(XML_GDTF_PowerConsumptionFrequencyLow);
	optional.push_back(XML_GDTF_PowerConsumptionFrequencyHigh);
	
	//------------------------------------------------------------------------------------
	// Check Attributes for node
	GdtfParsingError::CheckNodeAttributes(pNode, needed, optional);
}

EGdtfObjectType GdtfPowerConsumption::GetObjectType()
{
	return EGdtfObjectType::eGdtfPowerConsumption;
}

TXString GdtfPowerConsumption::GetNodeName()
{
	return XML_GDTF_PowerConsumptionNodeName;
}

double GdtfPowerConsumption::GetValue()
{
    return fValue;
}

double GdtfPowerConsumption::GetPowerFactor()
{
    return fPowerFactor;
}

GdtfConnector* GdtfPowerConsumption::GetConnector()
{
	return fConnector;
}

const TXString& GdtfPowerConsumption::GetUnresolvedConnector()
{
	return fUnresolvedConnector;
}

double GdtfPowerConsumption::GetVoltageLow()
{
	return fVoltageLow;
}

double GdtfPowerConsumption::GetVoltageHigh()
{
	return fVoltageHigh;
}

double GdtfPowerConsumption::GetFrequencyLow()
{
	return fFrequencyLow;
}

double GdtfPowerConsumption::GetFrequencyHigh()
{
	return fFrequencyHigh;
}