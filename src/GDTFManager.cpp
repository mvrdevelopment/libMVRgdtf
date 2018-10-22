//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "GDTFManager.h"
#include "SceneDataExchange.h"
#include "XmlFileHelper.h"
#include <iostream>
#include "Prefix/CommonPrefix.h"

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
		//-------------------------------------------------------------------------------------
		// Now Print Everything
		this->OnPrintToFile(pNode);
	}
}

void GdtfObject::ReadFromNode(const IXMLFileNodePtr& pNode)
{
	TXString nodeName;
	pNode->GetNodeName(nodeName);
	ASSERTN(kEveryone, nodeName == GetNodeName());
	
	this->OnReadFromNode(pNode);
}

void GdtfObject::OnPrintToFile(IXMLFileNodePtr pNode)
{
	// Nothing to do here
}

void GdtfObject::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	// Nothing to read here
}

void GdtfObject::SetBind(void* ptr)
{
	fBindValue = ptr;
}

void* GdtfObject::GetBind()
{
	return fBindValue;
}

TXString GdtfObject::GetNodeReference() const
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

TXString GdtfActivationGroup::GetNodeReference() const
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

TXString GdtfFeature::GetNodeReference() const
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

TXString GdtfAttribute::GetNodeReference() const
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

TXString GdtfWheel::GetNodeReference() const
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
	
	TXString subAttrStr;
	pNode->GetNodeAttributeValue(XML_GDTF_WhhelSubAttribute,	subAttrStr); // TODO
	
	
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

const TGdtfWheelSlotArray GdtfWheel::GetWheelSlotArray()
{
	return fWheelSlots;
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
	pNode->SetNodeAttributeValue(XML_GDTF_WhhelSlotColor,		GdtfConverter::ConvertColor(fColor));
	if(fGobo != "")	{ pNode->SetNodeAttributeValue(XML_GDTF_WhhelSlotPicture,	fGobo); }
	
	
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
	if (VCOM_SUCCEEDED(pNode->GetNodeAttributeValue(XML_GDTF_WhhelSlotColor, color)))
	{
		if (color.IsEmpty() == false)
		{
			if (GdtfConverter::ConvertColor(color, this->fColor)) { return; }
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Get Gobo
	pNode->GetNodeAttributeValue(XML_GDTF_WhhelSlotPicture, fGobo);
	
	
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

TXString GdtfWheelSlot::GetNodeReference() const
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

EGdtfObjectType GdtfModel::GetObjectType()
{
	return EGdtfObjectType::eGdtfModel;
}
TXString GdtfModel::GetNodeName()
{
	return XML_GDTF_ModelNodeName;
}

TXString GdtfModel::GetNodeReference() const
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
	GdtfGeometryAxis* axis = new GdtfGeometryAxis(name, refToModel, ma, nullptr);
	
	fInternalGeometries.push_back(axis);
	
	return axis;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryWithLamp(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometryLamp* lamp = new GdtfGeometryLamp(name, refToModel, ma, nullptr);
	
	fInternalGeometries.push_back(lamp);
	
	return lamp;
}

GdtfGeometryPtr GdtfGeometry::AddGeometry(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometry(name, refToModel, ma, nullptr);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryReference(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryReference(name, refToModel, ma, nullptr);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryShaper(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryShaperFilter(name, refToModel, ma, nullptr);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryColor(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryColorFilter(name, refToModel, ma, nullptr);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryGobo(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryGoboFilter(name, refToModel, ma, nullptr);
	
	fInternalGeometries.push_back(geo);
	
	return geo;
}

GdtfGeometryPtr GdtfGeometry::AddGeometryBeam(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma)
{
	GdtfGeometry* geo = new GdtfGeometryBeamFilter(name, refToModel, ma, nullptr);
	
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
	
	pNode->SetNodeAttributeValue(XML_GDTF_GeometryMatrix,			GdtfConverter::ConvertMatrix(fMatrix));

	ASSERTN(kEveryone, fModelReference != nullptr);
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
										  if (geometry)
										  {
											  geometry->ReadFromNode(objNode);
											  fInternalGeometries.push_back(geometry);
										  }
										  return;
									  });
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

TXString GdtfGeometry::GetNodeReference() const
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
	pNode->SetNodeAttributeValue(XML_GDTF_BeamType,					GdtfConverter::ConvertBeamType(fBeamType));
	pNode->SetNodeAttributeValue(XML_GDTF_ColorRenderingIndex,		GdtfConverter::ConvertInteger(fColorIndex));
	
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
	TXString radius;	pNode->SetNodeAttributeValue(XML_GDTF_BeamRadius,				radius);	GdtfConverter::ConvertDouble(radius,		fBeamRadius);
	TXString type;		pNode->SetNodeAttributeValue(XML_GDTF_BeamType,					type);		GdtfConverter::ConvertBeamType(type,		fBeamType);
	TXString colorIndex;pNode->SetNodeAttributeValue(XML_GDTF_ColorRenderingIndex,		colorIndex);GdtfConverter::ConvertInteger(colorIndex,	fColorIndex);
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

}

GdtfGeometryReference::GdtfGeometryReference(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent) 
					 : GdtfGeometry(name,refToModel,ma, parent)
{

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
	
}

void GdtfGeometryReference::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfGeometry::OnReadFromNode(pNode);
	
	//------------------------------------------------------------------------------------
	// Read the content
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_BreakNodeName, [this] (IXMLFileNodePtr pNode) -> void
								 {
									 GdtfBreakPtr breakObj = new GdtfBreak();
									 breakObj->ReadFromNode(pNode);
									 fBreaks.push_back(breakObj);
								 }
								 );
	
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
									 GdtfDmxChannelPtr channel = new GdtfDmxChannel();
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

EGdtfObjectType GdtfDmxMode::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxMode;
}

TXString GdtfDmxMode::GetNodeName()
{
	return XML_GDTF_DMXModeNodeName;
}

GdtfDmxChannel* GdtfDmxMode::AddChannel(const TXString& name)
{
	GdtfDmxChannel* channel = new GdtfDmxChannel(name);
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
GdtfDmxChannel::GdtfDmxChannel()
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
}

GdtfDmxChannel::GdtfDmxChannel(const TXString& name)
{
	fName_AutoGenerated		= name;
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
	fFine = fine;
}

void GdtfDmxChannel::SetDmxUltra(Sint32 ultra)
{
	fUltra = ultra;
}

void SceneData::GdtfDmxChannel::SetDmxUber(Sint32 uber)
{
	fUber = uber;
}

void GdtfDmxChannel::SetFrequency(EGdtfDmxFrequency frequency)
{
	fFrequenz = frequency;
}

void GdtfDmxChannel::SetDefaultValue(DmxValue defaultValue)
{
	fDefaultValue = defaultValue;
}

void GdtfDmxChannel::SetHighlight(Sint32 highlight)
{
	fHeighlight = highlight;
}

void GdtfDmxChannel::SetMoveInBlackFrames(double moveInBlackFrames)
{
	fMoveInBlackFrames = moveInBlackFrames;
}

void GdtfDmxChannel::SetDmxChangeTimeLimit(double changeLimit)
{
	fDmxChangeTimeLimit = changeLimit;
}

GdtfDmxLogicalChannel* GdtfDmxChannel::AddLogicalChannel(const TXString &name)
{
	GdtfDmxLogicalChannel* channel = new GdtfDmxLogicalChannel(name, this);
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
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelDMXBreak,			GdtfConverter::ConvertInteger(fDmxBreak));
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
	TXString dmxBreak;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelDMXBreak,			dmxBreak);	GdtfConverter::ConvertInteger(dmxBreak,		fDmxBreak);
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
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelHighlight,			highlight);	
	GdtfConverter::ConvertDMXValue(highlight, this->GetChannelBitResolution(), fHeighlight, fHeighlightNone);
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
								
									 fLogicalChannels.push_back(logicalChan);
									 return;
								 });
}

EGdtfObjectType GdtfDmxChannel::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxChannel;
}

TXString GdtfDmxChannel::GetNodeReference() const
{
	return GetName();
}

TXString GdtfDmxChannel::GetNodeName()
{
	return XML_GDTF_DMXChannelNodeName;
}

const TXString& GdtfDmxChannel::GetName() const
{
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

Sint32 GdtfDmxChannel::GetHighlight() const
{
	return fHeighlight;
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

//------------------------------------------------------------------------------------
// GdtfDmxChannel
GdtfDmxLogicalChannel::GdtfDmxLogicalChannel(GdtfDmxChannel* parent)
{
	fSnap				= EGdtfDmxSnap::eGdtfDmxMaster_No;
	fAttribute			= nullptr;
	fDmxMaster				= eGdtfDmxMaster_None;
	fParentDmxChannel	= parent;
}

GdtfDmxLogicalChannel::GdtfDmxLogicalChannel(const TXString& name, GdtfDmxChannel* parent)
{
	fName_AutoGenerated		= name;
	fSnap		= EGdtfDmxSnap::eGdtfDmxMaster_No;	
	fAttribute	= nullptr;
	fDmxMaster				= eGdtfDmxMaster_None;
	fParentDmxChannel	= parent;
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

GdtfDmxChannelFunctionPtr GdtfDmxLogicalChannel::AddDmxChannelFunction(const TXString &name)
{
	GdtfDmxChannelFunctionPtr function = new GdtfDmxChannelFunction(name, this);
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
									 
									 // Add to list
									 fFunctions.push_back(function);
									 return;
								 });
}

EGdtfObjectType GdtfDmxLogicalChannel::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxLogicalChannel;
}

TXString GdtfDmxLogicalChannel::GetNodeReference() const
{
	return fParentDmxChannel->GetNodeReference() + "." + GetName();
}

TXString GdtfDmxLogicalChannel::GetNodeName()
{
	return XML_GDTF_DMXLogicalChannelNodeName;
}

const TXString& GdtfDmxLogicalChannel::GetName() const
{
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
	fAttribute			= nullptr;
	fParentLogicalChannel	= parent;
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
	fAttribute			= nullptr;
	fParentLogicalChannel	= parent;
}

GdtfDmxChannelFunction::~GdtfDmxChannelFunction()
{
	for (GdtfDmxChannelSetPtr ptr : fChannelSets) { delete ptr; }
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
	
	// ------------------------------------------------------------------------------------
	// LogicalChannels
	for (GdtfDmxChannelSet* channelObj : fChannelSets)
	{
		channelObj->WriteToNode(pNode);
	}
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
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionAttribute, fUnresolvedAttrRef);	
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelFuntionWheelRef, fUnresolvedWheelRef);
	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelEmitter, fUnresolvedEmitterRef);
	
	// ------------------------------------------------------------------------------------
	// GdtfDmxChannelSet
	GdtfConverter::TraverseNodes(pNode, "", XML_GDTF_DMXChannelSetNodeName, [this] (IXMLFileNodePtr objNode) -> void
								 {
									 // Create the object
									 GdtfDmxChannelSetPtr channelSet = new GdtfDmxChannelSet(this);
									 
									 // Read from node
									 channelSet->ReadFromNode(objNode);
									 
									 // Add to list
									 fChannelSets.push_back(channelSet);
									 return;
								 });
}

EGdtfObjectType GdtfDmxChannelFunction::GetObjectType()
{
	return EGdtfObjectType::eGdtfDmxChannelFuntion;
}

TXString GdtfDmxChannelFunction::GetNodeName()
{
	return XML_GDTF_DMXChannelFuntionNodeName;
}

TXString GdtfDmxChannelFunction::GetNodeReference() const
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

GdtfDmxChannel * SceneData::GdtfDmxChannelFunction::GetParentDMXChannel() const
{
	return fParentLogicalChannel->GetParentDMXChannel();
}


//------------------------------------------------------------------------------------
// GdtfDmxChannelSet
GdtfDmxChannelSet::GdtfDmxChannelSet(GdtfDmxChannelFunction* parent)
{
	fDmxStart		= 0;
	fDmxEnd			= 16777215;
	fPhysicalStart	= 0.0;
	fPhysicalEnd	= 1.0;	
	fWheelSlotIdx	= 0;

	fParentChnlFunction = parent;
}

GdtfDmxChannelSet::GdtfDmxChannelSet(const TXString& name, GdtfDmxChannelFunction* parent)
{
	fUniqueName = name;
	fDmxStart		= 0;
	fDmxEnd			= 16777215;
	fPhysicalStart	= 0.0;
	fPhysicalEnd	= 1.0;	
	fWheelSlotIdx	= 0;

	fParentChnlFunction = parent;
}

GdtfDmxChannelSet::~GdtfDmxChannelSet()
{
}

void GdtfDmxChannelSet::SetName(const TXString& name)
{
	fUniqueName = name;
}

void GdtfDmxChannelSet::SetDmxStart(DmxValue start)
{
	fDmxStart = start;
}

void GdtfDmxChannelSet::SetDmxEnd(DMXAddress end)
{
	fDmxEnd = end;
}

void GdtfDmxChannelSet::SetPhysicalStart(double start)
{
	fPhysicalStart = start;
}

void GdtfDmxChannelSet::SetPhysicalEnd(double end)
{
	fPhysicalEnd = end;
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
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelSetDMXTo,				GdtfConverter::ConvertInteger(fDmxEnd));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalFrom,		GdtfConverter::ConvertDouble(fPhysicalStart));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalTo,			GdtfConverter::ConvertDouble(fPhysicalEnd));	
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
	TXString dmxTo;		pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetDMXTo,				dmxTo);		GdtfConverter::ConvertInteger(dmxTo,	fDmxEnd);  // XXX MS: The DmxEnd is not defined in this node and needs to be calculated by us.
	TXString physFrom;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalFrom,		physFrom);	GdtfConverter::ConvertDouble(physFrom,	fPhysicalStart);
	TXString physTo;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetPhysicalTo,			physTo);	GdtfConverter::ConvertDouble(physTo,	fPhysicalEnd);	
	TXString wheelId;	pNode->GetNodeAttributeValue(XML_GDTF_DMXChannelSetWheelSlotIndexRef,	wheelId);	GdtfConverter::ConvertInteger(wheelId,  fWheelSlotIdx);
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

DmxValue GdtfDmxChannelSet::GetDmxStart() const
{
	return fDmxStart;
}

DMXAddress GdtfDmxChannelSet::GetDmxEnd() const
{
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
	fDmxStart				= 0;
	fDmdEnd					= 0;
	fRelationType			= EGdtfDmxRelationType::eGdtfDmxRelationType_Mode;

}

GdtfDmxRelation::GdtfDmxRelation(GdtfDmxChannelPtr master, GdtfDmxChannelFunctionPtr slave, const TXString& name)
{
	fUniqueName				= name;
	fMasterDmxChannel		= master;
	fSlaveChannelFunction	= slave;
	fDmxStart				= 0;
	fDmdEnd					= 0;
	fRelationType			= EGdtfDmxRelationType::eGdtfDmxRelationType_Mode;
}

GdtfDmxRelation::~GdtfDmxRelation()
{
}

void GdtfDmxRelation::ResolveDmxRange()
{
	ASSERTN(kEveryone, fMasterDmxChannel != nullptr);
	if (fMasterDmxChannel)
	{
		GdtfConverter::ConvertDMXValue(fUnresolvedDmxStart,	fMasterDmxChannel->GetChannelBitResolution(),	fDmxStart);
		GdtfConverter::ConvertDMXValue(fUnresolvedDmxEnd,   fMasterDmxChannel->GetChannelBitResolution(),	fDmdEnd);
	}
}

void GdtfDmxRelation::SetName(const TXString& name)
{
	fUniqueName = name;
}

void GdtfDmxRelation::SetRelationType(EGdtfDmxRelationType type)
{
	fRelationType = type;
}

void GdtfDmxRelation::SetDmxStart(DmxValue start)
{
	fDmxStart = start;
}

void GdtfDmxRelation::SetDmxEnd(DmxValue end)
{
	fDmdEnd = end;
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
	pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationType,				GdtfConverter::ConvertRelationEnum(fRelationType));
	pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationDMXFrom,			GdtfConverter::ConvertDMXValue (fRelationType, chanelReso) );
	pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationDMXTo,				GdtfConverter::ConvertDMXValue (fDmdEnd, chanelReso));
	if (fMasterDmxChannel) { pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationMaster,			fMasterDmxChannel->GetNodeReference());}
	if (fSlaveChannelFunction)  { pNode->SetNodeAttributeValue(XML_GDTF_DMXRelationSlave,			fSlaveChannelFunction->GetNodeReference());}

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
	pNode->GetNodeAttributeValue(XML_GDTF_DMXRelationDMXFrom,	fUnresolvedDmxStart);
	pNode->GetNodeAttributeValue(XML_GDTF_DMXRelationDMXTo,		fUnresolvedDmxEnd);
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

DmxValue GdtfDmxRelation::GetDmxStart() const
{
	return fDmxStart;
}

DmxValue GdtfDmxRelation::GetDmxEnd() const
{
	return fDmdEnd;
}

//------------------------------------------------------------------------------------
// GdtfRevision
GdtfRevision::GdtfRevision()
{
	
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
	// TODO
	// fText = text;
	// fDate = "";
	// fDate += gSDK->GetFormattedDateTimeString(EDateTimeFormat::DDMMYYYY);
	// fDate += " ";
	// fDate += gSDK->GetFormattedDateTimeString(EDateTimeFormat::H_MM_S);
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

TXString GdtfPhysicalEmitter::GetNodeReference() const
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
GdtfMacro::GdtfMacro()
{
}

GdtfMacro::~GdtfMacro()
{
}

void GdtfMacro::OnPrintToFile(IXMLFileNodePtr pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnPrintToFile(pNode);
}

void GdtfMacro::OnReadFromNode(const IXMLFileNodePtr& pNode)
{
	//------------------------------------------------------------------------------------
	// Call the parent
	GdtfObject::OnReadFromNode(pNode);
}

const TXString & SceneData::GdtfMacro::GetName() const
{
    return fName;
}

void SceneData::GdtfMacro::SetName(const TXString & name)
{
    fName = name;
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
GdtfFixture::GdtfFixture(IFileIdentifierPtr inZipFile)
{
	fReaded = false;
	
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
	ASSERTN(kEveryone, exists = true);
	
	
	//-------------------------------------------------------------------------------------------------
	// Create a ZIP File
	IZIPFilePtr zipfile ( IID_ZIPFile );
	zipfile->OpenRead(inZipFile);
	
	
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	TXString outPath				= "";
	TXString inPath					= "";
	while (VCOM_SUCCEEDED( zipfile->GetNextFile(inPath, outPath)))
	{
		// This is the current file that we are reading
		ISceneDataZipBuffer buffer;
		
		zipfile->GetFile(outPath, &buffer);
		
		
		// Prepare pointer to the new files
		IFileIdentifierPtr file (IID_FileIdentifier);
		file->Set(fWorkingFolder, outPath);
		
		// dump buffer into file
		buffer.WriteToFile(file);
		
		// Add it into the file list
		fLocalFiles.push_back(file);
		
		//
		inPath = outPath;
		
	}
	
	//-------------------------------------------------------------------------------------------------
	// Prepare bools for checksum checks
	bool hasCheckSum	= false;
	bool checksumIsFine = false;
	
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	IFileIdentifierPtr gdtfFile (IID_FileIdentifier);
	
	if ( ! SceneDataZip::GetFile(XML_GDTF_GDTFFILENAME, fWorkingFolder, gdtfFile, hasCheckSum, checksumIsFine, true))
	{
		DSTOP((kEveryone, "Failed to get gdtf file."));
		fReaded = false;
		return;
	}
	if (hasCheckSum) { ASSERTN(kEveryone, checksumIsFine == true); }
	
	
	//-------------------------------------------------------------------------------------------------
	// Read XML
	IXMLFilePtr xmlFile (IID_XMLFile);
	
	if (VCOM_SUCCEEDED(xmlFile->ReadFile( gdtfFile )))
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
}

void GdtfFixture::AutoGenerateNames(GdtfDmxModePtr dmxMode)
{
		for (GdtfDmxChannelPtr dmxChannel : dmxMode->GetChannelArray())
		{
			//------------------------------------------------------------------------------------------------
			//  Create Names for DMX Channel
			ASSERTN(kEveryone, dmxChannel->GetGeomRef());
			if ( ! dmxChannel->GetGeomRef()) { continue; }
			
			TXString geometryRef = dmxChannel->GetGeomRef()->GetName();
			TXString firstAttr;
			
			for (GdtfDmxLogicalChannelPtr logicalChannel : dmxChannel->GetLogicalChannelArray())
			{
				//------------------------------------------------------------------------------------------------
				//  Create Names for Logical Channels
				ASSERTN(kEveryone, !logicalChannel->GetUnresolvedAttribRef().IsEmpty());
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

void GdtfFixture::ResolveAllReferences()
{
	ResolveGeometryRefs();
	ResolveAttribRefs();
	ResolveDmxModeRefs();	
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
		
		
		// ------------------------------------------------------------------------------------------
		// Main Attribute
		TXString mainAttributeRef = attr->GetUnresolvedMainAttribute();
		if ( ! mainAttributeRef.IsEmpty())
		{
			GdtfAttributePtr mainAttribute = getAttributeByRef(mainAttributeRef);
			
			ASSERTN(kEveryone, mainAttribute != nullptr);
			if (mainAttribute != nullptr)	{ attr->SetMainAttribute(mainAttribute); }

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
			if (geomPtr != nullptr) { dmxMode->SetGeomRef(geomPtr);		 }
		}
		
		// First Link all the stuff for DMX Channels
		ResolveDmxChannelRefs(dmxMode);
		
		// Afer Geometry is linked to the base geometry, we can generate the names
        AutoGenerateNames(dmxMode);
		
		// Then we have all the information for this
		ResolveDmxRelationRefs(dmxMode);
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

		rel->ResolveDmxRange();
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
	// Print dmxModes
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
	// Print physicalDescription
	IXMLFileNodePtr physicalDescription;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_GDTF_FixtureChildNodePhysicalDesrip, & physicalDescription)))
	{
		IXMLFileNodePtr emittersGroupNode;
		if (VCOM_SUCCEEDED(physicalDescription->CreateChildNode(XML_GDTF_PhysicalDescriptionsEmitterCollect, & emittersGroupNode)))
		{
			for (GdtfPhysicalEmitterPtr emitter : fEmitters)
			{
				emitter->WriteToNode(emittersGroupNode);
			}
			
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
	// Print geometries
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
	// Print presets

	
	// ------------------------------------------------------------------------------------
	// Print macros

	
	// ------------------------------------------------------------------------------------
	// Print physicalDescription
	IXMLFileNodePtr physicalDescription;
	if (VCOM_SUCCEEDED( pNode->GetChildNode(XML_GDTF_FixtureChildNodePhysicalDesrip, & physicalDescription)))
	{
		GdtfConverter::TraverseNodes(physicalDescription,XML_GDTF_PhysicalDescriptionsEmitterCollect , XML_GDTF_EmitterNodeName, [this] (IXMLFileNodePtr objNode) -> void
									 {
										 // Create the object
										 GdtfPhysicalEmitterPtr emitter = new GdtfPhysicalEmitter();
										 
										 // Read from node
										 emitter->ReadFromNode(objNode);
										 
										 // Add to list
										 fEmitters.push_back(emitter);
										 return;
									 });
	}
	
	
	
	

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

GdtfMacroPtr GdtfFixture::AddMacro()
{
	GdtfMacroPtr macro = new  GdtfMacro();
	
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

void GdtfFixture::SetGuid(const VWFC::Tools::UUID& uuid)
{
	fGuid = uuid;
}

void GdtfFixture::SetPNGFile(const GdtfPNGFile& png)
{
	fTumbnail = png;
}
