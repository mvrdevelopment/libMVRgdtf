//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "SceneDataExchange.h"
#include "HashManager.h"
#include "GDTFManager.h"
#include "XmlFileHelper.h"

using namespace SceneData;

SceneDataGUID::SceneDataGUID(const TXString& uuid)
{
	ASSERTN(kEveryone, uuid != "");
	
	// TODO
	GdtfConverter::ConvertUUID(uuid, nullptr,  _uuid);
	_type	= eNormal;
}

SceneDataGUID::SceneDataGUID(const VectorworksMVR::VWFC::Tools::VWUUID& uuid)
{
	_uuid	= uuid;
	_type	= eNormal;
}

SceneDataGUID::SceneDataGUID(ESceneDataGUIDType type, const TXString& debugMessage)
{
	ASSERTN(kEveryone, type == ePlaceHolder || type == eNoGuid);
	if (type == ePlaceHolder)	{ _typeEntry   = "ePlaceHolder = " + debugMessage; }
	else						{ _typeEntry   = "eNoGuid";                        }
	
	_type	= type;
}

SceneDataGUID::~SceneDataGUID()
{
	
}

ESceneDataGUIDType SceneDataGUID::GetType() const
{
	return _type;
}

TXString SceneDataGUID::GetUUIDString() const
{
	if (_type == eNormal)
	{
		return GdtfConverter::ConvertUUID( _uuid );
	}
	
	DSTOP((kEveryone,"Printig Invalid UUID"));
	return _typeEntry;
}

const VWFC::Tools::VWUUID& SceneDataGUID::GetUuidObj() const
{
	return _uuid;
}

SceneDataGUID::operator TXString()
{
	return GetUUIDString();
}


bool SceneDataGUID::operator ==(const SceneDataGUID& a)
{
	if (this->_uuid == a._uuid) { return true; }
	return false;
}


// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataGDTFSpecObj

SceneDataGDTFSpecObj::SceneDataGDTFSpecObj(const SceneDataGUID& guid):
SceneDataGroupObj(guid)
{

}

SceneDataGDTFSpecObj::~SceneDataGDTFSpecObj()
{

}

void SceneDataGDTFSpecObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	SceneDataGroupObj::OnPrintToFile(pNode, exchange);

	//--------------------------------------------------------------------------------------------
	// Print the GDTF File
	IXMLFileNodePtr pGDTFNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_FixtureGDTFSpec, & pGDTFNode)))
	{
		pGDTFNode->SetNodeValue(GetGdtfFile());
		exchange->AddNeededGdtfFile(GetGdtfFile());
	}
	
	//--------------------------------------------------------------------------------------------
	// Print the DmxMode
	IXMLFileNodePtr pDmxModeNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_FixtureDMXMode, & pDmxModeNode)))
	{
		pDmxModeNode->SetNodeValue(GetGdtfDmxMode());
	}
}

void SceneDataGDTFSpecObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	SceneDataGroupObj::OnReadFromNode(pNode, exchange);

	//--------------------------------------------------------------------------------------------
	// Read the GDTF File name
	IXMLFileNodePtr pGDTFNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_FixtureGDTFSpec, & pGDTFNode))) { pGDTFNode->GetNodeValue(fGdtfFile); }
	
	//--------------------------------------------------------------------------------------------
	// Read the GDTF DMX Mode
	IXMLFileNodePtr pDmxMode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_FixtureDMXMode, & pDmxMode)))	{ pDmxMode->GetNodeValue(fGdtfDmxMode); }
	
}

ESceneDataObjectType SceneDataGDTFSpecObj::GetObjectType(){
	return ESceneDataObjectType::eSceneDataMVRSpecObj;
}


const TXString& SceneDataGDTFSpecObj::GetGdtfFile() const
{
	return fGdtfFile;
}

void SceneDataGDTFSpecObj::SetGDTFFile(const TXString& path)
{
	fGdtfFile = path;
}

const TXString& SceneDataGDTFSpecObj::GetGdtfDmxMode() const
{
	return fGdtfDmxMode;
}

void SceneDataGDTFSpecObj::SetGdtfDmxMode(const TXString& path)
{
	fGdtfDmxMode = path;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataGUID
SceneDataGeometryObj::SceneDataGeometryObj() : SceneDataGeoInstanceObj(SceneDataGUID(eNoGuid, ""), false /* Is No Symbol */)
{

}

SceneDataGeometryObj::~SceneDataGeometryObj()
{
	
}

const TXString& SceneDataGeometryObj::GetFileName() const
{
	return fFileName;
}

const TXString& SceneDataGeometryObj::GetFileFullPath(SceneDataExchange* exchange)
{
	IFileIdentifierPtr geoFile (IID_FileIdentifier);
	if (geoFile)
	{ geoFile->Set(exchange->GetWorkingFolder(), this->GetFileName()); }

	geoFile->GetFileFullPath(fFileFullPath);
	return fFileFullPath;
}

void SceneDataGeometryObj::SetFileName(const TXString& fileName)
{
	ASSERTN(kEveryone, fileName.IsEmpty() == false);
	fFileName = fileName;
}
void SceneDataGeometryObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{	
	// Call Parent
	SceneDataGeoInstanceObj::OnPrintToFile(pNode, exchange);

	pNode->SetNodeAttributeValue(XML_Val_GeometryObjectAttrFile, GetFileName());
}

void SceneDataGeometryObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call Parent
	SceneDataGeoInstanceObj::OnReadFromNode(pNode, exchange);
	
	pNode->GetNodeAttributeValue(XML_Val_GeometryObjectAttrFile, fFileName);	
}

TXString SceneDataGeometryObj::GetNodeName()
{
	return TXString( XML_Val_GeometryObjectNodeName );
}

ESceneDataObjectType SceneDataGeometryObj::GetObjectType()
{
	return ESceneDataObjectType::eGeometryObj;
}

//----------------------------------------------------------------------------------------------------------------------------------
// SceneDataObj
SceneDataObj::SceneDataObj(const SceneDataGUID& guid) : fGuid(guid)
{
	
}

SceneDataObj::~SceneDataObj()
{
	
}

SceneDataGUID& SceneDataObj::getGuid()
{
	return fGuid;
}

const TXString& SceneDataObj::getName() const
{
	return fName;
}

void SceneDataObj::setName(const TXString& value)
{
	fName = value;
}

void SceneDataObj::PrintToFile(IXMLFileNodePtr pContainerNode, SceneDataExchange* exchange)
{
    // Create the new node
	IXMLFileNodePtr pNode;
	if ( VCOM_SUCCEEDED( pContainerNode->CreateChildNode( this->GetNodeName(), & pNode ) ) )
	{
		//-------------------------------------------------------------------------------------
		// Now Print Everything
		this->OnPrintToFile(pNode, exchange);
	}
	
}

void SceneDataObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	//-------------------------------------------------------------------------------------
	// Set the uuid as attribute
	if ( getGuid().GetType()  != eNoGuid )
	{
		pNode->SetNodeAttributeValue(XML_Val_GuidAttrName, getGuid().GetUUIDString());
	}
	
	//-------------------------------------------------------------------------------------
	// Set the name as attribute
	TXString nameAttrStr = getName();
	if ( ! nameAttrStr.IsEmpty())
	{
		pNode->SetNodeAttributeValue(XML_Val_NameAttrName, nameAttrStr);
	}
}

void SceneDataObj::ReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	//--------------------------------------------------------------------
	// Check if you are reading the right thing
	TXString nameNode;
	pNode->GetNodeName(nameNode);
	ASSERTN(kEveryone, nameNode == GetNodeName());
	
	//--------------------------------------------------------------------
	// Read all the other stuff
	this->OnReadFromNode(pNode, exchange);
}

void SceneDataObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	//The guid is already in the object, you only have to read the name here
	TXString name;
	pNode->GetNodeAttributeValue(XML_Val_NameAttrName, name);
	setName(name);
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataProviderObj
SceneDataProviderObj::SceneDataProviderObj(const TXString& provider,const TXString& version) : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fVersion	= version;
	fProvider	= provider;
}

SceneDataProviderObj::SceneDataProviderObj() : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fVersion	= "";
	fProvider	= "";
}

SceneDataProviderObj::~SceneDataProviderObj()
{
	
}

void SceneDataProviderObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// ################################################################################
	// Don't call the parent, as we dont need a name of a guid


	// Add Provider
	pNode->SetNodeAttributeValue(XML_Val_DataNodeAttrProvider,	GetProvider());
	
	// Add version
	pNode->SetNodeAttributeValue(XML_Val_DataNodeAttrVersion,	GetVersion());
	
	
	// ------------------------------------------------------------------------------
	// Dump Data
	ASSERTN(kEveryone, fKeyArr.size() == fDataArr.size());
	for (size_t i = 0; i < fKeyArr.size(); i++)
	{
		IXMLFileNodePtr entryNode;
		if(VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_UserDataVWEntry, &entryNode)))
		{
			entryNode->SetNodeAttributeValue(XML_Val_UserDataVWKeyAttr, fKeyArr[i]);
			entryNode->SetNodeValue(fDataArr[i]);
		}
	}
	
	
}

void SceneDataProviderObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// ################################################################################
	// Don't call the parent, as we dont need a name of a guid
	
	
	// ------------------------------------------------------------------------------
	// Read Version
	pNode->GetNodeAttributeValue(XML_Val_DataNodeAttrProvider,	fProvider);
	
	// ------------------------------------------------------------------------------
	// Read Provider
	pNode->GetNodeAttributeValue(XML_Val_DataNodeAttrVersion,	fVersion);
	
	// ------------------------------------------------------------------------------
	// Read Data
	GdtfConverter::TraverseNodes(pNode, "", XML_Val_UserDataVWEntry, [this] (IXMLFileNodePtr pNode) -> void
								 {
									 // Create memory for values
									 TXString value;
									 TXString key;
									 
									 // Read
									 pNode->GetNodeValue(value);
									 pNode->GetNodeAttributeValue(XML_Val_UserDataVWKeyAttr, key);
									 
									 // Append Data
									 fKeyArr.push_back(key);
									 fDataArr.push_back(value);
								 }
								 );
	
}

TXString SceneDataProviderObj::GetNodeName()
{
	return TXString( XML_Val_DataNodeName );
}

ESceneDataObjectType SceneDataProviderObj::GetObjectType()
{
	return ESceneDataObjectType::eProviderObj;
}

const TXString& SceneDataProviderObj::GetVersion()
{
	return fVersion;
}

const TXString& SceneDataProviderObj::GetProvider()
{
	return fProvider;
}

void SceneDataProviderObj::AddEntry(const TXString& key,const TXString& value)
{
	fKeyArr.push_back(key);
	fDataArr.push_back(value);
}


size_t SceneDataProviderObj::GetEntryCount()
{
	return fKeyArr.size();
}

TXString& SceneDataProviderObj::GetKeyAt(size_t at)
{
	// Check postion
	ASSERTN(kEveryone, at < fKeyArr.size());	
	ASSERTN(kEveryone, at < fDataArr.size());	

	// Set Out Values
	return fKeyArr[at];;
}

TXString& SceneDataProviderObj::GetValueAt(size_t at)
{
	// Check postion
	ASSERTN(kEveryone, at < fKeyArr.size());	
	ASSERTN(kEveryone, at < fDataArr.size());	

	// Set Out Values
	return fDataArr[at];;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataAuxObj
SceneDataAuxObj::SceneDataAuxObj(const SceneDataGUID& guid) : SceneDataObj(guid)
{
	
}

SceneDataAuxObj::~SceneDataAuxObj()
{
	
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataSymDefObj
SceneDataSymDefObj::SceneDataSymDefObj(const SceneDataGUID& guid) : SceneDataAuxObj(guid)
{
	
}

SceneDataSymDefObj::~SceneDataSymDefObj()
{
	for (const auto& i : fGeometries){ delete i; }
}

void SceneDataSymDefObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataAuxObj::OnPrintToFile(pNode, exchange);
	
	// Create the child node
	IXMLFileNodePtr pChildNode;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_ChildObsNodeName, & pChildNode ) ) )
	{
		// Dump the object in the array
		for (SceneDataObj* geometry : fGeometries)
		{
			ASSERTN(kEveryone, geometry->GetObjectType() == eSymbol || geometry->GetObjectType() == eGeometryObj);
			geometry->PrintToFile(pChildNode, exchange);
		}
	}
}

void SceneDataSymDefObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataAuxObj::OnReadFromNode(pNode, exchange);
	
    //-----------------------------------------------------------------------------
    // Child geomtries
	GdtfConverter::TraverseMultiNodes(pNode, XML_Val_ChildObsNodeName, [this, exchange] (IXMLFileNodePtr objNode, const TXString& childNodeName) -> void
	{
		if(XML_Val_GeometryObjectNodeName == childNodeName)
		{
			SceneDataGeometryObjPtr geometry = new SceneDataGeometryObj();
			geometry->ReadFromNode(objNode, exchange);
			fGeometries.push_back(geometry);
		}
		else if(XML_Val_SymbolObjectNodeName == childNodeName)
		{
			TXString uuidSymbol;
			objNode->GetNodeAttributeValue(XML_Val_GuidAttrName,			uuidSymbol);				

			SceneDataSymbolObjPtr symbol = new SceneDataSymbolObj(uuidSymbol);
			symbol->ReadFromNode(objNode, exchange);
			fGeometries.push_back(symbol);		
		}
		else
		{
			ASSERTN(kEveryone, childNodeName == XML_Val_GeometryObjectNodeName || childNodeName == XML_Val_SymbolObjectNodeName);
		}								
	}
	);
}

TXString SceneDataSymDefObj::GetNodeName()
{
	return TXString( XML_Val_SymDefNodeName );
}

ESceneDataObjectType SceneDataSymDefObj::GetObjectType()
{
	return ESceneDataObjectType::eSymDef;
}

const SceneDataGeometryObjArray& SceneDataSymDefObj::getGeometryArray() const
{
	return fGeometries;
}

void SceneDataSymDefObj::Add(SceneDataGeoInstanceObjPtr object)
{
	ASSERTN(kEveryone, object != nullptr);
	if (! object) { return; }
	
	
	ASSERTN(kEveryone, object->GetObjectType() == eSymbol || object->GetObjectType() == eGeometryObj);
	if (object->GetObjectType() == eSymbol || object->GetObjectType() == eGeometryObj)
	{
		fGeometries.push_back(object);
	}
	
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataSymDefObj
SceneDataPositionObj::SceneDataPositionObj(const SceneDataGUID& guid) : SceneDataAuxObj(guid)
{
	
}

SceneDataPositionObj::~SceneDataPositionObj()
{
	
}

void SceneDataPositionObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataAuxObj::OnPrintToFile(pNode, exchange);
	
}

void SceneDataPositionObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataAuxObj::OnReadFromNode(pNode, exchange);
	
}


TXString SceneDataPositionObj::GetNodeName()
{
	return TXString( XML_Val_PositionNodeName );
}

ESceneDataObjectType SceneDataPositionObj::GetObjectType()
{
	return ESceneDataObjectType::ePosition;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataClassObj
SceneDataClassObj::SceneDataClassObj(const SceneDataGUID& guid) : SceneDataAuxObj(guid)
{
	
}

SceneDataClassObj::~SceneDataClassObj()
{
	
}

void SceneDataClassObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataAuxObj::OnPrintToFile(pNode, exchange);
	
}

void SceneDataClassObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataAuxObj::OnReadFromNode(pNode, exchange);
	
}


TXString SceneDataClassObj::GetNodeName()
{
	return TXString( XML_Val_ClassNodeName );
}

ESceneDataObjectType SceneDataClassObj::GetObjectType()
{
	return ESceneDataObjectType::eClassObject;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataSourceObj
SceneDataSourceObj::SceneDataSourceObj() : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	
}

SceneDataSourceObj::SceneDataSourceObj(const TXString& value, const TXString& linkedGeometry, GdtfDefines::ESourceType type) : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fValue 			= value;
	fLinkedGeometry = linkedGeometry;
	fType 			= type;
}

SceneDataSourceObj::~SceneDataSourceObj()
{
	
}

const TXString& SceneDataSourceObj::GetValue()
{
	return fValue;
}

const TXString& SceneDataSourceObj::GetLinkedGeometry()
{
	return fLinkedGeometry;
}

GdtfDefines::ESourceType	SceneDataSourceObj::GetType()
{
	return fType;
}

void SceneDataSourceObj::SetValue(TXString value)
{
	fValue = value;
}

void SceneDataSourceObj::SetLinkedGeometry(TXString linkedGeometry)
{
	fLinkedGeometry = linkedGeometry;
}

void SceneDataSourceObj::SetType(GdtfDefines::ESourceType type)
{
	fType = type;
}

void SceneDataSourceObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnPrintToFile(pNode, exchange);

	// Create the children node
	if(!fLinkedGeometry.IsEmpty())
	{
		pNode->SetNodeAttributeValue(XML_Val_SourceLinkedGeometry, fLinkedGeometry);
	}

	pNode->SetNodeAttributeValue(XML_Val_SourceType, GdtfConverter::ConvertESourceType(fType));

	pNode->SetNodeValue(fValue);
}

void SceneDataSourceObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnReadFromNode(pNode, exchange);

	pNode->GetNodeAttributeValue(XML_Val_SourceLinkedGeometry, fLinkedGeometry);

	TXString sourceTypeStr;
	pNode->GetNodeAttributeValue(XML_Val_SourceType, sourceTypeStr);
	GdtfConverter::ConvertESourceType(sourceTypeStr, pNode, fType);
	
	pNode->GetNodeValue(fValue);
}

TXString SceneDataSourceObj::GetNodeName()
{
	return TXString( XML_Val_SourceNodeName );
}

ESceneDataObjectType SceneDataSourceObj::GetObjectType()
{
	return ESceneDataObjectType::eSourceObject;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataMappingDefinitionObj
SceneDataMappingDefinitionObj::SceneDataMappingDefinitionObj(const SceneDataGUID& guid) : SceneDataAuxObj(guid)
{
	fSource = nullptr;
	fScaleHandling = EScaleHandlingType::ScaleKeepRatio;
	fSizeX = 0;
	fSizeY = 0;
}

SceneDataMappingDefinitionObj::SceneDataMappingDefinitionObj(const SceneDataGUID& guid, Uint32 sizeX, Uint32 sizeY, SceneDataSourceObjPtr source) : SceneDataAuxObj(guid)
{
	fScaleHandling = EScaleHandlingType::ScaleKeepRatio;
	fSizeX 	= sizeX;
	fSizeY 	= sizeY;
	fSource = source;
}

SceneDataMappingDefinitionObj::~SceneDataMappingDefinitionObj()
{
	delete fSource;
}

Uint32 SceneDataMappingDefinitionObj::GetSizeX()
{
	return fSizeX;
}

Uint32 SceneDataMappingDefinitionObj::GetSizeY()
{
	return fSizeY;
}

SceneDataSourceObjPtr SceneDataMappingDefinitionObj::GetSource()
{
	return fSource;
}

EScaleHandlingType	SceneDataMappingDefinitionObj::GetScaleHandling()
{
	return fScaleHandling;
}

void SceneDataMappingDefinitionObj::SetSizeX(Uint32 sizeX)
{
	fSizeX = sizeX;
}

void SceneDataMappingDefinitionObj::SetSizeY(Uint32 sizeY)
{
	fSizeY = sizeY;
}

void SceneDataMappingDefinitionObj::SetSource(const TXString& value, const TXString& linkedGeometry, GdtfDefines::ESourceType type)
{
	if(!fSource)
	{
		fSource = new SceneDataSourceObj(value, linkedGeometry, type);
	} 
	else
	{
		fSource->SetValue(value);
		fSource->SetLinkedGeometry(linkedGeometry);
		fSource->SetType(type);
	}
}

void SceneDataMappingDefinitionObj::SetScaleHandling(GdtfDefines::EScaleHandlingType scaleHandling)
{
	fScaleHandling = scaleHandling;
}

void SceneDataMappingDefinitionObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataAuxObj::OnPrintToFile(pNode, exchange);

	// Create the children nodes
	IXMLFileNodePtr pSizeXNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_MappingDefinitionSizeX, &pSizeXNode)))
	{
		pSizeXNode->SetNodeValue(GdtfConverter::ConvertInteger(fSizeX));
	}

	IXMLFileNodePtr pSizeYNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_MappingDefinitionSizeY, &pSizeYNode)))
	{
		pSizeYNode->SetNodeValue(GdtfConverter::ConvertInteger(fSizeY));
	}

	fSource->PrintToFile(pNode, exchange);

	IXMLFileNodePtr pScaleHandlingNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_MappingDefinitionScaleHandling, &pScaleHandlingNode)))
	{
		pScaleHandlingNode->SetNodeValue(GdtfConverter::ConvertEScaleHandlingType(fScaleHandling));
	}
}

void SceneDataMappingDefinitionObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataAuxObj::OnReadFromNode(pNode, exchange);

	// Read the children nodes
	IXMLFileNodePtr pSizeXNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_MappingDefinitionSizeX, &pSizeXNode)))
	{
		TXString value;
		pSizeXNode->GetNodeValue(value);
		GdtfConverter::ConvertInteger(value, pNode, fSizeX);	
	}

	IXMLFileNodePtr pSizeYNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_MappingDefinitionSizeY, &pSizeYNode)))
	{
		TXString value;
		pSizeYNode->GetNodeValue(value);
		GdtfConverter::ConvertInteger(value, pNode, fSizeY);	
	}

	IXMLFileNodePtr pSourceNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_SourceNodeName, &pSourceNode)))
	{
		if(!fSource)
		{
			fSource = new SceneDataSourceObj();
		}
		
		fSource->ReadFromNode(pSourceNode, exchange);
	}

	IXMLFileNodePtr pScaleHandlingNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_MappingDefinitionScaleHandling, &pScaleHandlingNode)))
	{
		TXString value;
		pScaleHandlingNode->GetNodeValue(value);
		GdtfConverter::ConvertEScaleHandlingType(value, pNode, fScaleHandling);	
	}

}

TXString SceneDataMappingDefinitionObj::GetNodeName()
{
	return TXString(XML_Val_MappingDefinitionNodeName);
}

ESceneDataObjectType SceneDataMappingDefinitionObj::GetObjectType()
{
	return ESceneDataObjectType::eMappingDefinitionObject;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataMappingObj
SceneDataMappingObj::SceneDataMappingObj() : SceneDataObj(SceneDataGUID(eNoGuid,"")),
					 fLinkedDefUuid(SceneDataGUID(eNoGuid,""))
{
	
}

SceneDataMappingObj::SceneDataMappingObj(const SceneDataGUID& linkedDefUuid) : SceneDataObj(SceneDataGUID(eNoGuid,"")),
					 fLinkedDefUuid(linkedDefUuid)
{

}

SceneDataMappingObj::~SceneDataMappingObj()
{
	
}

SceneDataGUID SceneDataMappingObj::GetLinkedDefUuid()
{
	return fLinkedDefUuid;
}

Uint32 SceneDataMappingObj::GetUx()
{
	return fUx;
}

Uint32 SceneDataMappingObj::GetUy()
{
	return fUy;
}

Uint32 SceneDataMappingObj::GetOx()
{
	return fOx;
}

Uint32 SceneDataMappingObj::GetOy()
{
	return fOy;
}

double SceneDataMappingObj::GetRz()
{
	return fRz;
}

void SceneDataMappingObj::SetLinkedDefUuid(const SceneDataGUID& linkedDefUuid)
{
	fLinkedDefUuid = linkedDefUuid;
}

void SceneDataMappingObj::SetUx(Uint32 value)
{
	fUx = value;
}

void SceneDataMappingObj::SetUy(Uint32 value)
{
	fUy = value;
}

void SceneDataMappingObj::SetOx(Uint32 value)
{
	fOx = value;
}

void SceneDataMappingObj::SetOy(Uint32 value)
{
	fOy = value;
}

void SceneDataMappingObj::SetRz(double value)
{
	fRz = value;
}


void SceneDataMappingObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnPrintToFile(pNode, exchange);

	// Set attributes
	pNode->SetNodeAttributeValue(XML_Val_MappingLinkedDefUuid, fLinkedDefUuid.GetUUIDString());

	// Create the children node
	IXMLFileNodePtr pUxNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_MappingUx, &pUxNode)))
	{
		pUxNode->SetNodeValue(GdtfConverter::ConvertInteger(fUx));
	}

	IXMLFileNodePtr pUyNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_MappingUy, &pUyNode)))
	{
		pUyNode->SetNodeValue(GdtfConverter::ConvertInteger(fUy));
	}

	IXMLFileNodePtr pOxNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_MappingOx, &pOxNode)))
	{
		pOxNode->SetNodeValue(GdtfConverter::ConvertInteger(fOx));
	}

	IXMLFileNodePtr pOyNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_MappingOy, &pOyNode)))
	{
		pOyNode->SetNodeValue(GdtfConverter::ConvertInteger(fOy));
	}

	IXMLFileNodePtr pRzNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_MappingRz, &pRzNode)))
	{
		pRzNode->SetNodeValue(GdtfConverter::ConvertDouble(fRz));
	}
	
}

void SceneDataMappingObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnReadFromNode(pNode, exchange);

	TXString uuidStr;
	pNode->GetNodeAttributeValue(XML_Val_MappingLinkedDefUuid, uuidStr);
	fLinkedDefUuid = SceneDataGUID(uuidStr);

	IXMLFileNodePtr pUxNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_MappingUx, &pUxNode)))
	{
		TXString value;
		pUxNode->GetNodeValue(value);
		GdtfConverter::ConvertInteger(value, pUxNode, fUx);
	}

	IXMLFileNodePtr pUyNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_MappingUy, &pUyNode)))
	{
		TXString value;
		pUyNode->GetNodeValue(value);
		GdtfConverter::ConvertInteger(value, pUyNode, fUy);
	}

	IXMLFileNodePtr pOxNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_MappingOx, &pOxNode)))
	{
		TXString value;
		pOxNode->GetNodeValue(value);
		GdtfConverter::ConvertInteger(value, pOxNode, fOx);
	}

	IXMLFileNodePtr pOyNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_MappingOy, &pOyNode)))
	{
		TXString value;
		pOyNode->GetNodeValue(value);
		GdtfConverter::ConvertInteger(value, pOyNode, fOy);
	}

	IXMLFileNodePtr pRzNode;
	if(VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_MappingRz, &pRzNode)))
	{
		TXString value;
		pRzNode->GetNodeValue(value);
		GdtfConverter::ConvertDouble(value, pRzNode, fRz);
	}
}

TXString SceneDataMappingObj::GetNodeName()
{
	return TXString(XML_Val_MappingNodeName);
}

ESceneDataObjectType SceneDataMappingObj::GetObjectType()
{
	return ESceneDataObjectType::eMappingObject;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataConnectionObj
	
SceneDataConnectionObj::SceneDataConnectionObj() : SceneDataObj(SceneDataGUID(eNoGuid,"")), fToObject(SceneDataGUID(eNoGuid,""))
{
}

SceneDataConnectionObj::SceneDataConnectionObj(const TXString& own, const TXString& other, const TXString& toObject) : SceneDataObj(SceneDataGUID(eNoGuid,"")), fOwn(own), fOther(other), fToObject(toObject)
{
}

SceneDataConnectionObj::SceneDataConnectionObj(const TXString& own, const TXString& other, const SceneDataGUID& toObject) : SceneDataObj(SceneDataGUID(eNoGuid,"")), fOwn(own), fOther(other), fToObject(toObject)
{
}

SceneDataConnectionObj::~SceneDataConnectionObj()
{	
}

SceneDataGUID& SceneDataConnectionObj::GetToObject()
{
	return fToObject;
}


void SceneDataConnectionObj::SetToObject(SceneDataGUID uuid){
	fToObject = uuid;
}

TXString& SceneDataConnectionObj::GetOwn(){
	return fOwn;
}


void SceneDataConnectionObj::SetOwn(TXString& own){
	fOwn = own;
}

TXString& SceneDataConnectionObj::GetOther(){
	return fOther;
}


void SceneDataConnectionObj::SetOther(TXString& other){
	fOther = other;
}

TXString				SceneDataConnectionObj::GetNodeName(){
	return XML_Val_ConnectionNodeName;
}

ESceneDataObjectType	SceneDataConnectionObj::GetObjectType(){
	return eConnectionObject;
}

void SceneDataConnectionObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnPrintToFile(pNode, exchange);

	// Set attributes
	pNode->SetNodeAttributeValue(XML_Val_ConnectionOwn, fOwn);
	pNode->SetNodeAttributeValue(XML_Val_ConnectionOther, fOther);
	pNode->SetNodeAttributeValue(XML_Val_ConnectionToObject, fToObject.GetUUIDString());
}

void SceneDataConnectionObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnReadFromNode(pNode, exchange);

	TXString uuidStr;
	pNode->GetNodeAttributeValue(XML_Val_ConnectionOwn, fOwn);
	pNode->GetNodeAttributeValue(XML_Val_ConnectionOther, fOther);
	TXString nUUID;
	pNode->GetNodeAttributeValue(XML_Val_ConnectionToObject, nUUID);
	fToObject = SceneDataGUID(nUUID);
}

// SceneDataCustomCommand
SceneDataCustomCommand::SceneDataCustomCommand() : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fChannelFunction	= "";
	fIsPercentage 		= false;
	fValue				= 0.0;
	
}

SceneDataCustomCommand::SceneDataCustomCommand(const TXString& channelFunction, bool isPercentage, double value) : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fChannelFunction	= channelFunction;
	fIsPercentage 		= isPercentage;
	fValue				= value;	
}

SceneDataCustomCommand::~SceneDataCustomCommand()
{
	
}

const TXString& SceneDataCustomCommand::GetChannelFunction()
{
	return fChannelFunction;
}

bool SceneDataCustomCommand::IsPercentage()
{
	return fIsPercentage;
}

double SceneDataCustomCommand::GetValue()
{
	return fValue;
}

void SceneDataCustomCommand::SetChannelFunction(const TXString& channelFunction)
{
	fChannelFunction = channelFunction;
}

void SceneDataCustomCommand::SetIsPercentage(bool isPercentage)
{
	fIsPercentage = isPercentage;
}

void SceneDataCustomCommand::SetValue(double value)
{
	fValue = value;
}

void SceneDataCustomCommand::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnPrintToFile(pNode, exchange);

	// Set value	
	TXString customCommandString = fChannelFunction;
	customCommandString += fIsPercentage ? "/percent,f " : ",f ";
	customCommandString += std::to_string(fValue);

	pNode->SetNodeValue(customCommandString);
}

void SceneDataCustomCommand::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnReadFromNode(pNode, exchange);

	TXString customCommandString;
	pNode->GetNodeValue(customCommandString);

	// Parse the string
	ptrdiff_t percentP = customCommandString.Find("/percent");
	
	fIsPercentage = percentP != -1;
	if(fIsPercentage)
	{
		fChannelFunction = customCommandString.Left(percentP);
	}
	else
	{
		ptrdiff_t commaP = customCommandString.Find(",");
		fChannelFunction = customCommandString.Left(commaP);
	}

	ptrdiff_t spaceP = customCommandString.TrimRight().ReverseFind(" ");
	TXString valueString = customCommandString.Right(customCommandString.GetLength() - spaceP - 1);
	fValue = valueString.atof();
}

TXString SceneDataCustomCommand::GetNodeName()
{
	return TXString(XML_Val_CustomCommandNodeName);
}

ESceneDataObjectType SceneDataCustomCommand::GetObjectType()
{
	return ESceneDataObjectType::eCustomCommand;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataAlignment
SceneDataAlignment::SceneDataAlignment() : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fBeamGeometry	= "";
	fUpVector 		= VWPoint3D();
	fDirection		= VWPoint3D();
	
}

SceneDataAlignment::SceneDataAlignment(const TXString& beamGeometry, const VWPoint3D& upVector, const VWPoint3D& direction) : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fBeamGeometry	= beamGeometry;
	fUpVector 		= upVector;
	fDirection		= direction;	
}

SceneDataAlignment::~SceneDataAlignment()
{
	
}

const TXString& SceneDataAlignment::GetBeamGeometry()
{
	return fBeamGeometry;
}

const VWPoint3D& SceneDataAlignment::GetUpVector()
{
	return fUpVector;
}

const VWPoint3D& SceneDataAlignment::GetDirection()
{
	return fDirection;
}

void SceneDataAlignment::SetBeamGeometry(const TXString& beamGeometry)
{
	fBeamGeometry = beamGeometry;
}

void SceneDataAlignment::SetUpVector(double x, double y, double z)
{
	fUpVector.SetPoint(x, y, z);
}

void SceneDataAlignment::SetDirection(double x, double y, double z)
{
	fDirection.SetPoint(x, y, z);
}

void SceneDataAlignment::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnPrintToFile(pNode, exchange);

	// Set value
	pNode->SetNodeAttributeValue(XML_Val_AlignmentBeamGeometry,	fBeamGeometry);
	pNode->SetNodeAttributeValue(XML_Val_AlignmentUpVector,		GdtfConverter::ConvertVector3(fUpVector));
	pNode->SetNodeAttributeValue(XML_Val_AlignmentDirection,	GdtfConverter::ConvertVector3(fDirection));
}

void SceneDataAlignment::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnReadFromNode(pNode, exchange);

						pNode->GetNodeAttributeValue(XML_Val_AlignmentBeamGeometry, fBeamGeometry);
	TXString upVector;	pNode->GetNodeAttributeValue(XML_Val_AlignmentUpVector, upVector);		GdtfConverter::ConvertVector3(upVector, pNode, fUpVector);
	TXString direction;	pNode->GetNodeAttributeValue(XML_Val_AlignmentDirection, direction);	GdtfConverter::ConvertVector3(direction, pNode, fDirection);
}

TXString SceneDataAlignment::GetNodeName()
{
	return TXString(XML_Val_AlignmentNodeName);
}

ESceneDataObjectType SceneDataAlignment::GetObjectType()
{
	return ESceneDataObjectType::eAlignment;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataOverwrite
SceneDataOverwrite::SceneDataOverwrite() : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fUniversal	= "";
	fTarget		= "";
}

SceneDataOverwrite::SceneDataOverwrite(const TXString& universal, const TXString& target) : SceneDataObj(SceneDataGUID(eNoGuid,""))
{
	fUniversal	= universal;
	fTarget		= target;	
}

SceneDataOverwrite::~SceneDataOverwrite()
{
	
}

const TXString& SceneDataOverwrite::GetUniversal()
{
	return fUniversal;
}

const TXString& SceneDataOverwrite::GetTarget()
{
	return fTarget;
}

void SceneDataOverwrite::SetUniversal(const TXString& universal)
{
	fUniversal = universal;
}

void SceneDataOverwrite::SetTarget(const TXString& target)
{
	fTarget = target;
}

void SceneDataOverwrite::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnPrintToFile(pNode, exchange);

	// Set value
	pNode->SetNodeAttributeValue(XML_Val_OverwriteUniversal,	fUniversal);
	pNode->SetNodeAttributeValue(XML_Val_OverwriteTarget,		fTarget);
}

void SceneDataOverwrite::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call parent
	SceneDataObj::OnReadFromNode(pNode, exchange);

	pNode->GetNodeAttributeValue(XML_Val_OverwriteUniversal, 	fUniversal);
	pNode->GetNodeAttributeValue(XML_Val_OverwriteTarget, 		fTarget);
}

TXString SceneDataOverwrite::GetNodeName()
{
	return TXString(XML_Val_OverwriteNodeName);
}

ESceneDataObjectType SceneDataOverwrite::GetObjectType()
{
	return ESceneDataObjectType::eOverwrite;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataObjWithMatrix
SceneDataObjWithMatrix::SceneDataObjWithMatrix(const SceneDataGUID& guid) : SceneDataObj(guid)
{
	fInContainer			= nullptr;
	fNextObj				= nullptr;
	fClass					= nullptr;

	fCustomCommands.clear();
	fAlignments.clear();
	fOverwrites.clear();
}

SceneDataObjWithMatrix::~SceneDataObjWithMatrix()
{
	for (SceneDataGeoInstanceObjPtr geoObj : fGeometries) { delete geoObj; }
	for (SceneDataCustomCommandPtr customCommand : fCustomCommands) { delete customCommand; }
	for (SceneDataAlignmentPtr alignment : fAlignments) { delete alignment; }
	for (SceneDataOverwritePtr overwrite : fOverwrites) { delete overwrite; }
	for (SceneDataConnectionObjPtr connection : fConnections) { delete connection; }
	
}

void SceneDataObjWithMatrix::GetTransformMatric(VWTransformMatrix& matrix) const
{
	matrix = fMatrix;
}

void SceneDataObjWithMatrix::SetTransformMatrix(const VWTransformMatrix& matrix)
{
	fMatrix = matrix;
}

SceneDataClassObjPtr SceneDataObjWithMatrix::GetClass() const
{
	return fClass;
}

void SceneDataObjWithMatrix::SetClass(SceneDataClassObjPtr clas)
{
	fClass = clas;
}

const TXString& SceneDataObjWithMatrix::GetUnresolvedClass() const
{
	return fUnresolvedClass;
}

const SceneDataGeometryObjArray& SceneDataObjWithMatrix::GetGeometryArr() const
{
	return fGeometries;
}

void SceneDataObjWithMatrix::AddGeometryObj(SceneDataGeoInstanceObjPtr object)
{
	ASSERTN(kEveryone, object != nullptr);
	if (object) { fGeometries.push_back(object); }
}

const SceneDataConnectionObjArray& SceneDataObjWithMatrix::GetConnectionArr() const
{
	return fConnections;
}

SceneDataConnectionObjPtr SceneDataObjWithMatrix::AddConnectionObj(const TXString& own, const TXString& other, const SceneDataGUID toObject)
{
	SceneDataConnectionObjPtr out = new SceneDataConnectionObj(own, other, toObject);
	if (out) { fConnections.push_back(out); }
	return out;
}


SceneDataCustomCommandPtr SceneDataObjWithMatrix::AddCustomCommand(const TXString& channelFunction, bool isPercentage, double value)
{
	SceneDataCustomCommandPtr customCommand = new SceneDataCustomCommand(channelFunction, isPercentage, value);
	fCustomCommands.push_back(customCommand);
	return customCommand;
}

const SceneDataCustomCommandArray& SceneDataObjWithMatrix::GetCustomCommandArray() const
{
	return fCustomCommands;
}

SceneDataAlignmentPtr SceneDataObjWithMatrix::AddAlignment(const TXString& beamGeometry, const VWPoint3D& upVector, const VWPoint3D& direction)
{
	SceneDataAlignmentPtr alignment = new SceneDataAlignment(beamGeometry, upVector, direction);
	fAlignments.push_back(alignment);
	return alignment;
}

const SceneDataAlignmentArray& SceneDataObjWithMatrix::GetAlignmentArray() const
{
	return fAlignments;
}

SceneDataOverwritePtr SceneDataObjWithMatrix::AddOverwrite(const TXString& universal, const TXString& target)
{
	SceneDataOverwritePtr overwrite = new SceneDataOverwrite(universal, target);
	fOverwrites.push_back(overwrite);
	return overwrite;
}

const SceneDataOverwriteArray& SceneDataObjWithMatrix::GetOverwriteArray() const
{
	return fOverwrites;
}

SceneDataGroupObjPtr SceneDataObjWithMatrix::GetContainer() const
{
	return fInContainer;
}

SceneDataObjWithMatrixPtr SceneDataObjWithMatrix::GetNextObject() const
{
	return fNextObj;
}

void SceneDataObjWithMatrix::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	SceneDataObj::OnPrintToFile(pNode, exchange);
	
	bool noOffset   = (fMatrix.GetOffset().Magnitude() == 0 );
	bool noUVector	= (fMatrix.GetUVector() == VWPoint3D(1,0,0));
	bool noVVector	= (fMatrix.GetVVector() == VWPoint3D(0,1,0));
	bool noWVector	= (fMatrix.GetWVector() == VWPoint3D(0,0,1));
	
	// Check if you need to plot it
	if ( !noOffset || !noUVector || !noVVector || !noWVector )
	{
		// Create the child node
		IXMLFileNodePtr pMatrixNode;
		if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_MatrixNodeName, & pMatrixNode ) ) )
		{
			pMatrixNode->SetNodeValue(GdtfConverter::ConvertMatrix(fMatrix, false));

		}
	}

	// ------------------------------------------------------------------------------------------------------------
	// Print the geometry
	if (fGeometries.size() > 0)
	{
		IXMLFileNodePtr pGeometriesNode;
		if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_GeometriesNodeName, & pGeometriesNode )))
		{
			for(SceneDataGeoInstanceObjPtr geoObj : fGeometries) { geoObj->PrintToFile(pGeometriesNode, exchange); }
		}
		
	}

	// ------------------------------------------------------------------------------------------------------------
	// Print the custom commands
	if (fCustomCommands.size() > 0)
	{
		IXMLFileNodePtr pCustomCommandsNode;
		if(VCOM_SUCCEEDED( pNode->CreateChildNode(XML_Val_CustomCommandsNodeName, &pCustomCommandsNode)))
		{
			for(SceneDataCustomCommandPtr customCommand : fCustomCommands) { customCommand->PrintToFile(pCustomCommandsNode, exchange); }
		}
		
	}

	// ------------------------------------------------------------------------------------------------------------
	// Print the alignments
	if (fAlignments.size() > 0)
	{
		IXMLFileNodePtr pAlignmentsNode;
		if(VCOM_SUCCEEDED( pNode->CreateChildNode(XML_Val_AlignmentsNodeName, &pAlignmentsNode)))
		{
			for(SceneDataAlignmentPtr alignment : fAlignments) { alignment->PrintToFile(pAlignmentsNode, exchange); }
		}
		
	}

	// ------------------------------------------------------------------------------------------------------------
	// Print the overwrites
	if (fOverwrites.size() > 0)
	{
		IXMLFileNodePtr pOverwritesNode;
		if(VCOM_SUCCEEDED( pNode->CreateChildNode(XML_Val_OverwritesNodeName, &pOverwritesNode)))
		{
			for(SceneDataOverwritePtr overwrite : fOverwrites) { overwrite->PrintToFile(pOverwritesNode, exchange); }
		}
		
	}
	
	// ------------------------------------------------------------------------------------------------------------
	// Print the class
	// Create the child node
	if (GetClass())
	{
		IXMLFileNodePtr pNodeClass;
		if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_ClassingNodeName, & pNodeClass ) ) )
		{
			pNodeClass->SetNodeValue(GetClass()->getGuid());
			
		}
	}
	
		// Print the custom commands
	if (fConnections.size() > 0)
	{
		IXMLFileNodePtr pConnectionsNode;
		if(VCOM_SUCCEEDED( pNode->CreateChildNode(XML_Val_ConnectionsNodeName, &pConnectionsNode)))
		{
			for(const auto& connection : fConnections) { connection->PrintToFile(pConnectionsNode, exchange); }
		}
	}
	
}

void SceneDataObjWithMatrix::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	//------------------------------------------------------------------------------------------
	// Call parent
	SceneDataObj::OnReadFromNode(pNode, exchange);
	
	//------------------------------------------------------------------------------------------
	// Preset Values
	VWPoint3D uVector (1,0,0);
	VWPoint3D vVector (0,1,0);
	VWPoint3D wVector (0,0,1);
	VWPoint3D offset  (0,0,0);
	
	// Read the child node
	IXMLFileNodePtr pMatrixNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_MatrixNodeName, & pMatrixNode ) ) )
	{
		// Convert Matrix entry
		TXString value;
		pMatrixNode->GetNodeValue(value);
		
		//
		GdtfConverter::ConvertMatrix(value, pNode, fMatrix);
		
	}
	else
	{
		fMatrix = VWTransformMatrix();
	}

	//------------------------------------------------------------------------------------------------------
	// Get Geometry
	IXMLFileNodePtr pGeometrisNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_GeometriesNodeName, & pGeometrisNode ) ) )
	{
		IXMLFileNodePtr pChild;
		if ( VCOM_SUCCEEDED( pGeometrisNode->GetFirstChildNode( & pChild)))
		{
			while (pChild)
			{
				TXString nodeName;
				pChild->GetNodeName(nodeName);
				if (nodeName == XML_Val_GeometryObjectNodeName)
				{
					SceneDataGeometryObjPtr geometry = new SceneDataGeometryObj();
					geometry->ReadFromNode(pChild, exchange);
					fGeometries.push_back(geometry);
				}
				else if (nodeName == XML_Val_SymbolObjectNodeName)
				{
					TXString uuidSymbol;
					pChild->GetNodeAttributeValue(XML_Val_GuidAttrName,			uuidSymbol);
					
					
					SceneDataSymbolObjPtr symbol = new SceneDataSymbolObj(uuidSymbol);
					symbol->ReadFromNode(pChild, exchange);
					fGeometries.push_back(symbol);
					
					
				}
				else
				{
					ASSERTN(kEveryone, nodeName == XML_Val_GeometryObjectNodeName || nodeName == XML_Val_SymbolObjectNodeName);
				}
				
				// Step to the next object
				IXMLFileNodePtr nextNode;
				pChild->GetNextSiblingNode( & nextNode);
				pChild = nextNode;
			}
			
		}


	}

	//--------------------------------------------------------------------------------------------
	// Read CustomCommands
	GdtfConverter::TraverseNodes(pNode, XML_Val_CustomCommandsNodeName, XML_Val_CustomCommandNodeName, [this, exchange] (IXMLFileNodePtr pNode) -> void
								{
									SceneDataCustomCommandPtr customCommand = new SceneDataCustomCommand();
									customCommand->ReadFromNode(pNode, exchange);
									fCustomCommands.push_back(customCommand);
								}
								);

	//--------------------------------------------------------------------------------------------
	// Read Alignments
	GdtfConverter::TraverseNodes(pNode, XML_Val_AlignmentsNodeName, XML_Val_AlignmentNodeName, [this, exchange] (IXMLFileNodePtr pNode) -> void
								{
									SceneDataAlignmentPtr alignment = new SceneDataAlignment();
									alignment->ReadFromNode(pNode, exchange);
									fAlignments.push_back(alignment);
								}
								);

	//--------------------------------------------------------------------------------------------
	// Read Overwrites
	GdtfConverter::TraverseNodes(pNode, XML_Val_OverwritesNodeName, XML_Val_OverwriteNodeName, [this, exchange] (IXMLFileNodePtr pNode) -> void
								{
									SceneDataOverwritePtr overwrite = new SceneDataOverwrite();
									overwrite->ReadFromNode(pNode, exchange);
									fOverwrites.push_back(overwrite);
								}
								);
	

	GdtfConverter::TraverseNodes(pNode, XML_Val_ConnectionsNodeName, XML_Val_ConnectionNodeName, [this, exchange] (IXMLFileNodePtr pNode) -> void
						{
							SceneDataConnectionObjPtr connection = new SceneDataConnectionObj();
							connection->ReadFromNode(pNode, exchange);
							fConnections.push_back(connection);
						}
						);

	//------------------------------------------------------------------------------------------------------
	// Get Class
	IXMLFileNodePtr pClassNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_ClassingNodeName, & pClassNode ) ) )
	{
		pClassNode->GetNodeValue(fUnresolvedClass);
	}
	
}

void SceneDataObjWithMatrix::ReadMatrixNodeValue(const IXMLFileNodePtr& pNode, VWPoint3D& inOutPoint)
{
	if (pNode)
	{
		TXString value;
		pNode->GetNodeValue(value);
		if (value != "")
		{
			std::vector<double> d_arr;
			
			//------------------------------------------------------------------------------
			// This will find two time the char ","
			ptrdiff_t p =  value.Find(",");
			while ( p > 0)
			{
				TXString strVal;
				for (ptrdiff_t i = 0; i < p; i++)
				{
					strVal += value.GetAt(i);
				}
				
				//------------------------------------------------------------------------------
				// Try to convert
				double dValue = strVal.atof();
				d_arr.push_back(dValue); 
				
				value.Delete(0, p + 1);
				
				 p = value.Find(",");
			}
			
			//------------------------------------------------------------------------------
			// Now get the last part of the string and squeeze a double out
			double dValue = value.atof();
				d_arr.push_back(dValue); 
			
			ASSERTN(kEveryone, d_arr.size() == 3);
			if (d_arr.size() == 3)
			{
				inOutPoint.x = d_arr[0];
				inOutPoint.y = d_arr[1];
				inOutPoint.z = d_arr[2];
			}
			
			
		}
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataAuxObj
SceneDataGeoInstanceObj::SceneDataGeoInstanceObj(const SceneDataGUID& guid, bool isSymbol) : SceneDataObjWithMatrix (guid)
{
	fIsSymbol = isSymbol;
}

SceneDataGeoInstanceObj::~SceneDataGeoInstanceObj()
{
	
}

bool SceneDataGeoInstanceObj::IsSymDef() const
{
	return fIsSymbol;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataAuxObj
SceneDataLayerObj::SceneDataLayerObj(const SceneDataGUID& guid) : SceneDataGroupObj(guid)
{

}

SceneDataLayerObj::~SceneDataLayerObj()
{
	
}

void SceneDataLayerObj::SetNextLayer(SceneDataLayerObj* nextLayer)
{
	ASSERTN(kEveryone, fNextObj == nullptr);
	fNextObj = nextLayer;
}

TXString SceneDataLayerObj::GetNodeName()
{
	return TXString( XML_Val_LayerObjectNodeName );
}

ESceneDataObjectType SceneDataLayerObj::GetObjectType()
{
	return ESceneDataObjectType::eLayer;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataAuxObj
SceneDataDmxAdress::SceneDataDmxAdress(size_t universe, size_t adress, size_t breakId)
{
	// The First Universe starts with 1
	// But Universe 0 is also the first universe. So 0 and 1 are here the same thing
	if (universe != 0 ) { universe--; }
	
	fAbsuluteAdress = universe * 512 + adress;
	fBreak			= breakId;
}

SceneDataDmxAdress::SceneDataDmxAdress(size_t absuluteAdress, size_t breakId)
{
	fAbsuluteAdress = absuluteAdress;
	fBreak			= breakId;
}

size_t SceneDataDmxAdress::GetAdress() const
{
	size_t value = fAbsuluteAdress -( 512 * ( GetUniverse() - 1));
	
	ASSERTN(kEveryone, value <= 512);
	
	return value;
}

size_t SceneDataDmxAdress::GetUniverse() const
{
	size_t universe = 1;
	
	while (fAbsuluteAdress > universe * 512) { universe++; }
	
	return universe;
}

SceneDataFixtureObj::SceneDataFixtureObj(const SceneDataGUID& guid) : SceneDataGDTFSpecObj(guid)
{
	fFocusPoint		= nullptr;
	fPosition		= nullptr;
	fColor			= CCieColor(0.312712,0.329008,100.0);
	fUnitNumber		= 0;
	fFixtureTypeId	= 0;
	fCustomId		= 0;
	fGoboRotation 	= 0.0;
	fCastShadow		= false;
}

SceneDataFixtureObj::~SceneDataFixtureObj()
{
	for(SceneDataMappingObjPtr mapping : fMappings)
	{
		delete mapping;
	}	
}

TXString SceneDataFixtureObj::GetUnresolvedFocusUUID()
{
	return fUnresolvedFocus;
}

TXString SceneDataFixtureObj::GetUnresolvedPositionUUID()
{
	return fUnresolvedPosition;
}

SceneDataFocusPointObjPtr SceneDataFixtureObj::GetFocusPoint()
{
	return fFocusPoint;
}

SceneDataPositionObjPtr SceneDataFixtureObj::GetPosition()
{
	return fPosition;
}

const TXString& SceneDataFixtureObj::GetFixtureId()
{
	return fFixtureId;
}

void SceneDataFixtureObj::SetFunction(const TXString& function)
{
	fFunction = function;
}

const TXString& SceneDataFixtureObj::GetFunction()
{
	return fFunction;
}

Sint32 SceneDataFixtureObj::GetUnitNumber()
{
	return fUnitNumber;
}

CCieColor SceneDataFixtureObj::GetColor()
{
	return fColor;
}

Sint8 SceneDataFixtureObj::GetFixtureTypeId()
{
	return fFixtureTypeId;
}

size_t SceneDataFixtureObj::GetCustomId()
{
	return fCustomId;
}

const TXString& SceneDataFixtureObj::GetGobo()
{
	return fGobo;
}

const TXString& SceneDataFixtureObj::GetGoboFullPath(SceneDataExchange* exchange)
{
	// Reset
	fGoboFullPath = "";

	// Prepare
	IFileIdentifierPtr goboFile (IID_FileIdentifier);
	if (goboFile) { goboFile->Set(exchange->GetWorkingFolder(), this->GetGobo() + ".png"); }

	// 
	bool existsOnDisk = false;
	if(VCOM_SUCCEEDED(goboFile->ExistsOnDisk(existsOnDisk)) && existsOnDisk)
	{
		goboFile->GetFileFullPath(fGoboFullPath);
	}

	
	return fGoboFullPath;
}

double SceneDataFixtureObj::GetGoboRotation()
{
	return fGoboRotation;
}

bool SceneDataFixtureObj::GetCastShadow()
{
	return fCastShadow;
}

SceneDataMappingObjArray SceneDataFixtureObj::GetMappingsArray()
{
	return fMappings;
}

const SceneDataAdressArray& SceneDataFixtureObj::GetAdressesArray()
{
	return fAdresses;
}

TXString SceneDataFixtureObj::GetNodeName()
{
	return TXString( XML_Val_FixtureNodeName );
}

ESceneDataObjectType SceneDataFixtureObj::GetObjectType()
{
	return ESceneDataObjectType::eFixture;
}

void SceneDataFixtureObj::SetPosition(SceneDataPositionObjPtr ptr)
{
	ASSERTN(kEveryone, ptr != nullptr);
	fPosition = ptr;
}

void SceneDataFixtureObj::SetFocusPoint(SceneDataFocusPointObjPtr ptr)
{
	ASSERTN(kEveryone, ptr != nullptr);
	fFocusPoint = ptr;
}

void SceneDataFixtureObj::AddAdress(const SceneDataDmxAdress& adress)
{
	for (const SceneDataDmxAdress& exAdress : fAdresses)
	{
		if (adress.fBreak == exAdress.fBreak)
		{
			DSTOP((kEveryone, "Duplicated Break Ids for one fixture adress"));
			return;
		}
	}
	fAdresses.push_back(adress);
}

void SceneDataFixtureObj::SetColor(const CCieColor& color)
{
	fColor = color;
}

void SceneDataFixtureObj::SetFixtureId(const TXString& value)
{
	fFixtureId = value;
}

void SceneDataFixtureObj::SetUnitNumber(Sint32 value)
{
	fUnitNumber = value;
}

void SceneDataFixtureObj::SetGobo(const TXString& value)
{
	fGobo = value;
}

void SceneDataFixtureObj::SetGoboRotation(double value)
{
	fGoboRotation = value;
}

void SceneDataFixtureObj::SetCustomId(const size_t& value)
{
	fCustomId = value;
}

void SceneDataFixtureObj::SetFixtureTypeId(const Sint8& value)
{
	fFixtureTypeId = value;
}

void SceneDataFixtureObj::SetCastShadow(bool value)
{
	fCastShadow = value;
}

void SceneDataFixtureObj::AddMapping(SceneDataGUID mappingDefinitionUuid)
{
	fMappings.push_back(new SceneDataMappingObj(mappingDefinitionUuid));
}

void SceneDataFixtureObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	SceneDataGDTFSpecObj::OnPrintToFile(pNode, exchange);
	
	//--------------------------------------------------------------------------------------------
	// Print the Focus
	if (GetFocusPoint())
	{
		IXMLFileNodePtr pFocusNode;
		if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureFocus, & pFocusNode ) ) )
		{
			pFocusNode->SetNodeValue(GetFocusPoint()->getGuid());
			
		}
	}
	
	
	//--------------------------------------------------------------------------------------------
	// Print the Position
	if (GetPosition())
	{
		IXMLFileNodePtr ppositionNode;
		if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixturePosition, & ppositionNode ) ) )
		{
			ppositionNode->SetNodeValue(GetPosition()->getGuid());
		}
	}
	
	
	//--------------------------------------------------------------------------------------------
	// Print the Address
	IXMLFileNodePtr pAdressesNode;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureAddresses, & pAdressesNode ) ) )
	{
		for (const SceneDataDmxAdress& adress :fAdresses)
		{
			IXMLFileNodePtr pAdressNode;
			if ( VCOM_SUCCEEDED( pAdressesNode->CreateChildNode( XML_Val_FixtureAddress, & pAdressNode ) ) )
			{
				pAdressNode->SetNodeAttributeValue(XML_Val_FixtureAttrBreak, TXString().itoa(adress.fBreak));
				pAdressNode->SetNodeValue(									 TXString().itoa(adress.fAbsuluteAdress));
			}
		}
		
	}
	
	//--------------------------------------------------------------------------------------------
	// Print the FixtureId
	IXMLFileNodePtr pChannelIdNode;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureFixtureID, & pChannelIdNode ) ) )
	{
		pChannelIdNode->SetNodeValue( GetFixtureId() );
		
	}
	
	//--------------------------------------------------------------------------------------------
	// Print the UnitNumber
	IXMLFileNodePtr pUnitNumberNode;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureUnitNumber, & pUnitNumberNode ) ) )
	{
		pUnitNumberNode->SetNodeValue(GdtfConverter::ConvertInteger(fUnitNumber));
		
	}
	
	//--------------------------------------------------------------------------------------------
	// Print the FixtureTypeId
	IXMLFileNodePtr fixtureTypeId;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureTypeId, & fixtureTypeId ) ) )
	{
		fixtureTypeId->SetNodeValue(GdtfConverter::ConvertInteger(fFixtureTypeId));
		
	}
	
	
	//--------------------------------------------------------------------------------------------
	// Print the CustomId
	IXMLFileNodePtr pCustomId;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureCustomid, & pCustomId ) ) )
	{
		pCustomId->SetNodeValue(GdtfConverter::ConvertInteger( (Sint32)fCustomId ));
	}
	
	//--------------------------------------------------------------------------------------------
	// Print Color
	IXMLFileNodePtr pColorNode;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureColor, & pColorNode ) ) )
	{
		pColorNode->SetNodeValue(GdtfConverter::ConvertColor(fColor));
			
	}

	//--------------------------------------------------------------------------------------------
	// Print Gobo
	IXMLFileNodePtr pGoboNode;
	if ( (! fGobo.IsEmpty()) && VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureGobo, & pGoboNode ) ) )
	{
		pGoboNode->SetNodeValue(fGobo);
		pGoboNode->SetNodeAttributeValue(XML_Val_FixtureGoboRotation, GdtfConverter::ConvertDouble(fGoboRotation));
	}

	//--------------------------------------------------------------------------------------------
	// Print Fixture
	IXMLFileNodePtr pFixtureNode;
	if ( (! fFunction.IsEmpty()) && VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureFunction, & pFixtureNode ) ) )
	{
		pFixtureNode->SetNodeValue(fFunction);
	}


	//--------------------------------------------------------------------------------------------
	// Print the CastShadow
	IXMLFileNodePtr pCastShadowNode;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureCastShadow, & pCastShadowNode ) ) )
	{
		pCastShadowNode->SetNodeValue(GdtfConverter::ConvertBool(fCastShadow));
	}

	//--------------------------------------------------------------------------------------------
	// Print Mappings
	IXMLFileNodePtr pMappingsNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_FixtureMappings, &pMappingsNode)))
	{
		for (const SceneDataMappingObjPtr mapping : fMappings)
		{
			mapping->PrintToFile(pMappingsNode, exchange);
		}
	}
}

void SceneDataFixtureObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	SceneDataGDTFSpecObj::OnReadFromNode(pNode, exchange);
	
	//--------------------------------------------------------------------------------------------
	// Read the Focus
	IXMLFileNodePtr pFocusNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureFocus, & pFocusNode ) ) )				{  pFocusNode->GetNodeValue(fUnresolvedFocus); }

	//--------------------------------------------------------------------------------------------
	// Read the Position
	IXMLFileNodePtr ppositionNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixturePosition, & ppositionNode ) ) )		{  ppositionNode->GetNodeValue(fUnresolvedPosition);  }

	

	//--------------------------------------------------------------------------------------------
	// Read the ChannelID
	IXMLFileNodePtr pFixtureId;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureFixtureID, & pFixtureId ) ) )			{ pFixtureId->GetNodeValue(fFixtureId); }
	
	//--------------------------------------------------------------------------------------------
	// Read the UnitNumber
	IXMLFileNodePtr pUnitNumberNode;
	TXString		unitNumber;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureUnitNumber, & pUnitNumberNode ) ) )	{ pUnitNumberNode->GetNodeValue(unitNumber);		GdtfConverter::ConvertInteger(unitNumber, pNode, fUnitNumber); }
	
	
	//--------------------------------------------------------------------------------------------
	// Read the FixtureTypeId
	IXMLFileNodePtr pFixtureTypeId;
	TXString		fixtureTypeStr;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureTypeId, & pFixtureTypeId ) ) )			{ pFixtureTypeId->GetNodeValue(fixtureTypeStr);		GdtfConverter::ConvertInteger(fixtureTypeStr, pNode, this->fFixtureTypeId); }
	
	

	//--------------------------------------------------------------------------------------------
	// Read the Custom Id
	IXMLFileNodePtr pCustomId;
	TXString		customIdStr;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureCustomid, & pCustomId ) ) )			{ pCustomId->GetNodeValue(customIdStr);			GdtfConverter::ConvertInteger(customIdStr, pNode, this->fCustomId); }
	
	
	//--------------------------------------------------------------------------------------------
	// Read the Addresses

	GdtfConverter::TraverseNodes(pNode, XML_Val_FixtureAddresses, XML_Val_FixtureAddress, [this] (IXMLFileNodePtr pNode) -> void
								 {
									 // Create memory for adresses
									 Sint32 dmx			= 0; TXString dmxStr;
									 Sint32 breakId		= 0; TXString breakIdStr;
									 
									 // Read and Convert
									 pNode->GetNodeValue(dmxStr);											GdtfConverter::ConvertInteger(dmxStr, pNode,		dmx);
									 pNode->GetNodeAttributeValue(XML_Val_FixtureAttrBreak, breakIdStr);	GdtfConverter::ConvertInteger(breakIdStr, pNode,	breakId);
									 
									 fAdresses.push_back(SceneDataDmxAdress(dmx, breakId));
								 }
								 );
	
	
	//--------------------------------------------------------------------------------------------
	// Read Color
	IXMLFileNodePtr pColorNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureColor, & pColorNode ) ) )
	{
		TXString colorStr;
		pColorNode->GetNodeValue(colorStr);
		GdtfConverter::ConvertColor(colorStr, pNode,fColor);
			
	}

	//--------------------------------------------------------------------------------------------
	// Read Gobo
	IXMLFileNodePtr pGoboNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureGobo, & pGoboNode ) ) )
	{
		pGoboNode->GetNodeValue(fGobo);

		TXString rotationStr;
		pGoboNode->GetNodeAttributeValue(XML_Val_FixtureGoboRotation, rotationStr);

		GdtfConverter::ConvertDouble(rotationStr, pGoboNode, fGoboRotation);
	}

	//--------------------------------------------------------------------------------------------
	// Read Gobo
	IXMLFileNodePtr pFunctionNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureFunction, & pFunctionNode ) ) )
	{
		pFunctionNode->GetNodeValue(fFunction);
	}


	//--------------------------------------------------------------------------------------------
	// Read the CastShadow
	IXMLFileNodePtr pCastShadowNode;
	TXString		castShadow;
	if (VCOM_SUCCEEDED(pNode->GetChildNode(XML_Val_FixtureCastShadow, &pCastShadowNode)))
	{
		pCastShadowNode->GetNodeValue(castShadow);
		GdtfConverter::ConvertBool(castShadow, pNode, fCastShadow);
	}

	//--------------------------------------------------------------------------------------------
	// Read Mappings
	GdtfConverter::TraverseNodes(pNode, XML_Val_FixtureMappings, XML_Val_MappingNodeName, [this, exchange] (IXMLFileNodePtr pNode) -> void
								{
									SceneDataMappingObjPtr mapping = new SceneDataMappingObj();
									mapping->ReadFromNode(pNode, exchange);
									fMappings.push_back(mapping);
								}
								);
	
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataGroupObj
SceneDataGroupObj::SceneDataGroupObj(const SceneDataGUID& guid) : SceneDataObjWithMatrix(guid)
{

}

SceneDataGroupObj::~SceneDataGroupObj()
{
	for (SceneDataObjWithMatrixPtr child : fChildObjs ) { delete child; }
}

const SceneDataObjWithMatrixArray& SceneDataGroupObj::GetChildArray() const
{
	return fChildObjs;
}

bool SceneDataGroupObj::AddObject(SceneDataObjWithMatrixPtr obj)
{
	// Set Next Object for previous object
	if (fChildObjs.size() > 0)
	{
		ASSERTN(kEveryone, fChildObjs.back()->fNextObj == nullptr);
		fChildObjs.back()->fNextObj = obj;
	}
	
	// Add to Container
	ASSERTN(kEveryone, obj != nullptr);
	fChildObjs.push_back(obj);
	
	// Set Container
	ASSERTN(kEveryone, obj->fInContainer == nullptr);
	obj->fInContainer = this;
	
	return true;
}

TXString SceneDataGroupObj::GetNodeName()
{
	return TXString( XML_Val_GroupNodeName );
}

void SceneDataGroupObj::PrintToFile(IXMLFileNodePtr pContainerNode, SceneDataExchange * exchange)
{
    if (this->GetNodeName() == XML_Val_GroupNodeName && (fChildObjs.size() == 0))
    {
        return; // Do not print empty groups at all.
    }

    SceneDataObjWithMatrix::PrintToFile(pContainerNode, exchange);
}

ESceneDataObjectType SceneDataGroupObj::GetObjectType()
{
	return ESceneDataObjectType::eGroup;
}

void SceneDataGroupObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
    // Call base class
	SceneDataObjWithMatrix::OnPrintToFile(pNode, exchange);
     
    if ( fChildObjs.size())
    {	
	    IXMLFileNodePtr pChildNode;
	    if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_ChildObsNodeName, & pChildNode ) ) )
	    {
		    // Dump the object in the array
		    for (SceneDataObjWithMatrixPtr objects : fChildObjs)
		    {	                
			    objects->PrintToFile(pChildNode, exchange);
		    }
	    }
	}
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataGroupObj
SceneDataSceneryObj::SceneDataSceneryObj(const SceneDataGUID& guid) : SceneDataGDTFSpecObj(guid)
{
	
}

SceneDataSceneryObj::~SceneDataSceneryObj()
{
	
}

TXString SceneDataSceneryObj::GetNodeName()
{
	return TXString( XML_Val_SceneObjectNodeName );
}

ESceneDataObjectType SceneDataSceneryObj::GetObjectType()
{
	return ESceneDataObjectType::eSceneObject;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataFocusPointObj
SceneDataFocusPointObj::SceneDataFocusPointObj(const SceneDataGUID& guid) : SceneDataGroupObj(guid)
{
	
}

SceneDataFocusPointObj::~SceneDataFocusPointObj()
{
	
}

TXString SceneDataFocusPointObj::GetNodeName()
{
	return TXString( XML_Val_FocusPointObjectNodeName );
}

ESceneDataObjectType SceneDataFocusPointObj::GetObjectType()
{
	return ESceneDataObjectType::eFocusPoint;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataTrussObj
SceneDataTrussObj::SceneDataTrussObj(const SceneDataGUID& guid) : SceneDataGDTFSpecObj(guid)
{
	
}

SceneDataTrussObj::~SceneDataTrussObj()
{
	
}

TXString SceneDataTrussObj::GetNodeName()
{
	return TXString( XML_Val_TrussObjectNodeName );
}

ESceneDataObjectType SceneDataTrussObj::GetObjectType()
{
	return ESceneDataObjectType::eTruss;
}

SceneDataSupportObj::SceneDataSupportObj(const SceneDataGUID& guid) : SceneDataGDTFSpecObj(guid)
{
	
}

SceneDataSupportObj::~SceneDataSupportObj()
{
	
}

TXString SceneDataSupportObj::GetNodeName()
{
	return TXString( XML_Val_SupportObjectNodeName );
}

ESceneDataObjectType SceneDataSupportObj::GetObjectType()
{
	return ESceneDataObjectType::eSupport;
}


// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataVideoScreenObj
SceneDataVideoScreenObj::SceneDataVideoScreenObj(const SceneDataGUID& guid) : SceneDataGDTFSpecObj(guid)
{
	fSource = nullptr;
}

SceneDataVideoScreenObj::~SceneDataVideoScreenObj()
{
	delete fSource;
}

SceneDataSourceObjPtr SceneDataVideoScreenObj::GetVideoSource()
{
	return fSource;
}

void SceneDataVideoScreenObj::SetVideoSource(const TXString& value, const TXString& linkedGeometry, GdtfDefines::ESourceType type)
{
	if(!fSource)
	{
		fSource = new SceneDataSourceObj(value, linkedGeometry, type);
	} 
	else
	{
		fSource->SetValue(value);
		fSource->SetLinkedGeometry(linkedGeometry);
		fSource->SetType(type);
	}

}

TXString SceneDataVideoScreenObj::GetNodeName()
{
	return TXString(XML_Val_VideoScreenObjectNodeName);
}

ESceneDataObjectType SceneDataVideoScreenObj::GetObjectType()
{
	return ESceneDataObjectType::eVideoScreen;
}

void SceneDataVideoScreenObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call Parent
	SceneDataGDTFSpecObj::OnPrintToFile(pNode, exchange);

	IXMLFileNodePtr pSourcesNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_VideoScreenObjectSources, &pSourcesNode)))
	{
		if(fSource) { fSource->PrintToFile(pSourcesNode, exchange); }
	}
}

void SceneDataVideoScreenObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	SceneDataGDTFSpecObj::OnReadFromNode(pNode, exchange);

	IXMLFileNodePtr pSourcesNode;	
	pNode->GetChildNode(XML_Val_VideoScreenObjectSources, &pSourcesNode);
	if(pSourcesNode)
	{
		IXMLFileNodePtr pSourceNode;
		pSourcesNode->GetChildNode(XML_Val_SourceNodeName, &pSourceNode);
		if(pSourceNode)
		{
			if(!fSource)
			{
				fSource = new SceneDataSourceObj();
			}

			fSource->ReadFromNode(pSourceNode, exchange);
		}
	}
		
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataProjectorObj
SceneDataProjectorObj::SceneDataProjectorObj(const SceneDataGUID& guid) : SceneDataGDTFSpecObj(guid)
{
	fSource = nullptr;
}

SceneDataProjectorObj::~SceneDataProjectorObj()
{
	delete fSource;
}

SceneDataSourceObjPtr SceneDataProjectorObj::GetVideoSource()
{
	return fSource;
}

EScaleHandlingType	SceneDataProjectorObj::GetScaleHandling()
{
	return fScaleHandling;
}

void SceneDataProjectorObj::SetVideoSource(const TXString& value, const TXString& linkedGeometry, GdtfDefines::ESourceType type)
{
	if(!fSource)
	{
		fSource = new SceneDataSourceObj(value, linkedGeometry, type);
	} 
	else
	{
		fSource->SetValue(value);
		fSource->SetLinkedGeometry(linkedGeometry);
		fSource->SetType(type);
	}
}

void SceneDataProjectorObj::SetScaleHandling(GdtfDefines::EScaleHandlingType scaleHandling)
{
	fScaleHandling = scaleHandling;
}

TXString SceneDataProjectorObj::GetNodeName()
{
	return TXString(XML_Val_ProjectorObjectNodeName);
}

ESceneDataObjectType SceneDataProjectorObj::GetObjectType()
{
	return ESceneDataObjectType::eProjector;
}

void SceneDataProjectorObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	SceneDataGDTFSpecObj::OnPrintToFile(pNode, exchange);

	IXMLFileNodePtr pProjectionsNode;
	if (VCOM_SUCCEEDED(pNode->CreateChildNode(XML_Val_ProjectorObjectProjections, &pProjectionsNode)))
	{
		IXMLFileNodePtr pProjectionNode;
		if (VCOM_SUCCEEDED(pProjectionsNode->CreateChildNode(XML_Val_ProjectorObjectProjection, &pProjectionNode)))
		{
			if(fSource) { fSource->PrintToFile(pProjectionNode, exchange); }

			IXMLFileNodePtr pScaleHandlingNode;
			if (VCOM_SUCCEEDED(pProjectionNode->CreateChildNode(XML_Val_ProjectorObjectScaleHandling, &pScaleHandlingNode)))
			{
				pScaleHandlingNode->SetNodeValue(GdtfConverter::ConvertEScaleHandlingType(fScaleHandling));
			}
		}
	}
}

void SceneDataProjectorObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	SceneDataGDTFSpecObj::OnReadFromNode(pNode, exchange);

	IXMLFileNodePtr pProjectionsNode;	
	pNode->GetChildNode(XML_Val_ProjectorObjectProjections, &pProjectionsNode);
	if(pProjectionsNode)
	{
		IXMLFileNodePtr pProjectionNode;
		pProjectionsNode->GetChildNode(XML_Val_ProjectorObjectProjection, &pProjectionNode);
		if(pProjectionNode)
		{
			IXMLFileNodePtr pSourceNode;
			pProjectionNode->GetChildNode(XML_Val_SourceNodeName, &pSourceNode);
			if(pSourceNode)
			{
				if(!fSource)
				{
					fSource = new SceneDataSourceObj();
				}

				fSource->ReadFromNode(pSourceNode, exchange);
			}

			IXMLFileNodePtr pScaleHandlingNode;
			if(VCOM_SUCCEEDED(pProjectionNode->GetChildNode(XML_Val_ProjectorObjectScaleHandling, &pScaleHandlingNode)))
			{
				TXString value;
				pScaleHandlingNode->GetNodeValue(value);
				GdtfConverter::ConvertEScaleHandlingType(value, pScaleHandlingNode, fScaleHandling);	
			}
		}
	}
		
}


// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataSymbolObj
SceneDataSymbolObj::SceneDataSymbolObj(const SceneDataGUID& guid) : SceneDataGeoInstanceObj(guid, true /*Is SymbolDef*/)
{
	fSymDef = nullptr;
}

SceneDataSymbolObj::~SceneDataSymbolObj()
{
	
}

TXString SceneDataSymbolObj::GetNodeName()
{
	return TXString( XML_Val_SymbolObjectNodeName );
}

ESceneDataObjectType SceneDataSymbolObj::GetObjectType()
{
	return ESceneDataObjectType::eSymbol;
}

void SceneDataSymbolObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call Parent
	SceneDataGeoInstanceObj::OnPrintToFile(pNode, exchange);
	
	if (fSymDef)	{ pNode->SetNodeAttributeValue(XML_Val_GuidSymdefAttrName,	fSymDef->getGuid()); }
}

void SceneDataSymbolObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	SceneDataObjWithMatrix::OnReadFromNode(pNode, exchange);
	
	TXString value;
	pNode->GetNodeAttributeValue(XML_Val_GuidSymdefAttrName,	fUnresolvedSymDef);
		
}

void SceneDataSymbolObj::SetSymDef(SceneDataSymDefObjPtr symDef)
{
	fSymDef = symDef;
}

SceneDataSymDefObjPtr SceneDataSymbolObj::GetSymDef()
{
	return fSymDef;
}

const TXString& SceneDataSymbolObj::GetUnresolvedSymDef() const
{
	return fUnresolvedSymDef;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataExchange
SceneDataExchange::SceneDataExchange()
{	
	//---------------------------------------------------------------------------------------------
	// Set the working folder
	fWorkingFolder = (IID_FolderIdentifier);
	fWorkingFolder->Set(EFolderSpecifier::kSpotlightFolder, true /*UserFolder*/, "MVR_Export");
	
	
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

	fDuplicatedUuids = false;
}

SceneDataExchange::~SceneDataExchange()
{
	//-------------------------------------------------------------------------------------------------
	// Housekeeping
	for (size_t i = 0; i <  fFilesInZip.size() ; i++)
	{
		fFilesInZip[i]->DeleteOnDisk();
	}
	
	for (SceneDataObjWithMatrixPtr	childObj : fChildObjs )		{ delete childObj; }
	for (SceneDataAuxObjPtr			childAux : fAuxDataObjs )	{ delete childAux; }
	for (SceneDataProviderObjPtr	childPro : fProviderObjs )	{ delete childPro; }
	
}

void SceneDataExchange::InitializeForExport()
{
}

void SceneDataExchange::InitializeForImport()
{
	//------------------------------------------------
	// Start Undo System
	fUndoStarted = true;

	//Reset the flag (back to false)
	fDuplicatedUuids = false;
}

SceneDataProviderObjArray& SceneDataExchange::GetProviderObjects()
{
	return fProviderObjs;
}

SceneDataAuxObjArray& SceneDataExchange::GetAuxDataObjects()
{
	return fAuxDataObjs;
}

SceneDataObjWithMatrixArray& SceneDataExchange::GetChildObjects()
{
	return fChildObjs;
}

SceneDataObjWithMatrixArray& SceneDataExchange::GetSceneDataObjects()
{
	return fSceneObjects;
}

SceneDataSymDefObjPtr SceneDataExchange::GetSymDefByUUID(const SceneDataGUID& guid)
{	
	for (SceneDataAuxObjPtr auxObj: fAuxDataObjs)
	{
		if (auxObj->getGuid() == guid)
		{
			SceneDataSymDefObjPtr symDef = static_cast<SceneDataSymDefObjPtr>(auxObj);
			
			ASSERTN(kEveryone, symDef != nullptr);
			return symDef;
		}
	}
	return nullptr;
}

SceneDataProviderObjPtr SceneDataExchange::CreateDataProviderObject(const TXString& provider, const TXString& version)
{
	SceneDataProviderObjPtr newProvider =  new SceneDataProviderObj(provider, version);
	fProviderObjs.push_back(newProvider);
	
	return newProvider;
}

SceneDataSymDefObjPtr SceneDataExchange::CreateSymDefObject(const SceneDataGUID& guid, const TXString& name)
{
	for (SceneDataAuxObjPtr auxObj : fAuxDataObjs)
	{
		if (auxObj->getGuid() == guid)
		{
			ASSERTN(kEveryone, auxObj->GetObjectType() == eSymDef);
			SceneDataSymDefObjPtr existingSymDef = static_cast<SceneDataSymDefObjPtr>(auxObj);
			if (existingSymDef) { return existingSymDef; }
			
		}
	}
	SceneDataSymDefObjPtr newSymDef =  new SceneDataSymDefObj(guid);
	newSymDef->setName(name);
	
	fAuxDataObjs.push_back(newSymDef);
	
	return newSymDef;
}

SceneDataSymDefObjPtr SceneDataExchange::ReadSymDefObject(const IXMLFileNodePtr& node)
{
	TXString uuid;
	node->GetNodeAttributeValue(XML_Val_GuidAttrName, uuid);
	
	SceneDataSymDefObjPtr newSymDef =  new SceneDataSymDefObj(SceneDataGUID(uuid));
	newSymDef->ReadFromNode(node, this);
	
	fAuxDataObjs.push_back(newSymDef);
	fSymDefMap[uuid] = newSymDef;

	return newSymDef;
}

SceneDataLayerObjPtr SceneDataExchange::CreateLayerObject(const SceneDataGUID& guid, const TXString& name)
{
	SceneDataLayerObjPtr newLayer =  new SceneDataLayerObj(guid);
	newLayer->setName(name);
	
	if(fChildObjs.size() > 0)
	{
		SceneDataLayerObjPtr lastLayer = static_cast<SceneDataLayerObjPtr>(fChildObjs.back());
		ASSERTN(kEveryone, lastLayer != nullptr);
		if(lastLayer)	{ lastLayer->SetNextLayer(newLayer); }
	}	

	fChildObjs.push_back(newLayer); 
	
	return newLayer;
}

SceneDataLayerObjPtr SceneDataExchange::ReadLayerObject(const SceneDataGUID& guid, const IXMLFileNodePtr& node)
{
	// Get Object Before
	SceneDataObjWithMatrixPtr before = nullptr;
	if (fChildObjs.size() > 0) { before = fChildObjs.back(); }
	
	// Create the new Layer
	SceneDataLayerObjPtr newLayer =  new SceneDataLayerObj(guid);
	
	// Set the Next Object properlly
	if (before)
	{
		SceneDataLayerObjPtr lastLayer = static_cast<SceneDataLayerObjPtr>(before);
		
		ASSERTN(kEveryone, lastLayer != nullptr);
		if (lastLayer) { lastLayer->SetNextLayer(newLayer); }
		
	}

	fChildObjs.push_back(newLayer);

	
	// Read stuff
	newLayer->ReadFromNode(node, this);
		
	return newLayer;
}

SceneDataPositionObjPtr SceneDataExchange::CreatePositionObject(const SceneDataGUID& guid, const TXString& name)
{
	// ------------------------------------------------------------------------------------
	// Traverse Existig Obj
	for (SceneDataAuxObjPtr auxObj : fAuxDataObjs)
	{
		// Try to cast
		SceneDataPositionObjPtr position = static_cast<SceneDataPositionObjPtr>(auxObj);
		
		// If this is a position and the name is the same
		if (position && position->getName() == name)
		{
			if (guid.GetType() == eNormal)
			{
				ASSERTN(kEveryone, position->getGuid().GetType() != eNormal);
				position->fGuid = guid;
			}
			
			return position;
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Otherwise generate a new one
	SceneDataPositionObjPtr newPosition =  new SceneDataPositionObj(guid);
	newPosition->setName(name);
	fAuxDataObjs.push_back(newPosition);
	
	return newPosition;
}

SceneDataPositionObjPtr SceneDataExchange::ReadPositionObject(const IXMLFileNodePtr& node)
{
	// ------------------------------------------------------------------------------------
	// Read the uuid
	TXString uuid;
	node->GetNodeAttributeValue(XML_Val_GuidAttrName, uuid);
	
	// ------------------------------------------------------------------------------------
	// Create the object
	SceneDataPositionObjPtr newPostion =  new SceneDataPositionObj(SceneDataGUID(uuid));
	newPostion->ReadFromNode(node, this);
	
	
	// ------------------------------------------------------------------------------------
	// Add to aux Data
	fAuxDataObjs.push_back(newPostion);
	
	// ------------------------------------------------------------------------------------
	// Add to Positions
	fPositions.push_back(newPostion);
	
	return newPostion;
}

SceneDataClassObjPtr SceneDataExchange::CreateClassObject(const SceneDataGUID& guid, const TXString& name)
{
	// ------------------------------------------------------------------------------------
	// Traverse Existig Obj
	for (SceneDataAuxObjPtr auxObj : fAuxDataObjs)
	{
		// Try to cast
		SceneDataClassObjPtr clas = static_cast<SceneDataClassObjPtr>(auxObj);
		
		// If this is a position and the name is the same
		if (clas && clas->getName() == name)
		{
			ASSERTN(kEveryone, clas->getGuid().GetType() == eNormal);
			ASSERTN(kEveryone, guid           .GetType() == eNormal);
			ASSERTN(kEveryone, guid.GetUuidObj() == clas->getGuid().GetUuidObj());
			
			return clas;
		}
	}
	
	// ------------------------------------------------------------------------------------
	// Otherwise generate a new one
	SceneDataClassObjPtr newClass =  new SceneDataClassObj(guid);
	newClass->setName(name);
	fAuxDataObjs.push_back(newClass);
	
	return newClass;
}

SceneDataClassObjPtr SceneDataExchange::ReadClassObject(const IXMLFileNodePtr& node)
{
	// ------------------------------------------------------------------------------------
	// Read the uuid
	TXString uuid;
	node->GetNodeAttributeValue(XML_Val_GuidAttrName, uuid);
	
	// ------------------------------------------------------------------------------------
	// Create the object
	SceneDataClassObjPtr newClass =  new SceneDataClassObj(SceneDataGUID(uuid));
	newClass->ReadFromNode(node, this);
	
	
	// ------------------------------------------------------------------------------------
	// Add to aux Data
	fAuxDataObjs.push_back(newClass);
	
	// ------------------------------------------------------------------------------------
	// Add to Positions
	fClasses.push_back(newClass);
	
	return newClass;
}

SceneDataMappingDefinitionObjPtr SceneDataExchange::CreateMappingDefinitionObject(const SceneDataGUID& guid, const TXString& name)
{
	for (SceneDataAuxObjPtr auxObj : fAuxDataObjs)
	{
		if (auxObj->getGuid() == guid)
		{
			ASSERTN(kEveryone, auxObj->GetObjectType() == eMappingDefinitionObject);
			SceneDataMappingDefinitionObjPtr existingMappingDefinition = static_cast<SceneDataMappingDefinitionObjPtr>(auxObj);
			if (existingMappingDefinition) { return existingMappingDefinition; }
			
		}
	}
	SceneDataMappingDefinitionObjPtr newMappingDefinition = new SceneDataMappingDefinitionObj(guid);
	newMappingDefinition->setName(name);
	
	fAuxDataObjs.push_back(newMappingDefinition);
	
	return newMappingDefinition;
}

SceneDataMappingDefinitionObjPtr SceneDataExchange::ReadMappingDefinitionObject(const IXMLFileNodePtr& node)
{
	TXString uuid;
	node->GetNodeAttributeValue(XML_Val_GuidAttrName, uuid);
	
	SceneDataMappingDefinitionObjPtr newMappingDefinition = new SceneDataMappingDefinitionObj(SceneDataGUID(uuid));
	newMappingDefinition->ReadFromNode(node, this);
	
	fAuxDataObjs.push_back(newMappingDefinition);

	return newMappingDefinition;
}

SceneDataGroupObjPtr SceneDataExchange::CreateGroupObject(const SceneDataGUID& guid, const VWTransformMatrix& offset, SceneDataGroupObjPtr addToContainer)
{
	SceneDataGroupObjPtr newGroup = new SceneDataGroupObj(guid);
	addToContainer->AddObject(newGroup);
	return newGroup;
}

SceneDataGroupObjPtr SceneDataExchange::CreateGroupObject(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name, SceneDataGroupObjPtr addToContainer)
{
	SceneDataGroupObjPtr newGroup = new SceneDataGroupObj(guid);
	addToContainer->AddObject(newGroup);
	newGroup->setName(name);
	return newGroup;
}

SceneDataGroupObjPtr SceneDataExchange::ReadGroupObject(const SceneDataGUID& guid, const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{

	SceneDataGroupObjPtr newGroup =  new SceneDataGroupObj(guid);
	addToContainer->AddObject(newGroup);
	
	// Read stuff
	newGroup->ReadFromNode(node, this);
		
	return newGroup;
	
}

SceneDataFixtureObjPtr SceneDataExchange::CreateFixture(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name, SceneDataGroupObjPtr addToContainer)
{
	//----------------------------------------------------------------------------
	// Create new object
	SceneDataFixtureObjPtr newFixture = new SceneDataFixtureObj(guid);
	addToContainer->AddObject(newFixture);
	

	//----------------------------------------------------------------------------
	// Set Members
	newFixture->setName(name);
	newFixture->SetTransformMatrix(offset);
	
	
	return newFixture;
}

SceneDataFixtureObjPtr SceneDataExchange::ReadFixture(const SceneDataGUID& guid, const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{
	//----------------------------------------------------------------------------
	// Create new object
	SceneDataFixtureObjPtr newFixture =  new SceneDataFixtureObj(guid);
	addToContainer->AddObject(newFixture);
	
	
	//----------------------------------------------------------------------------
	// Read stuff
	newFixture->ReadFromNode(node, this);
	
	//----------------------------------------------------------------------------
	// Add to array to resolve pointers
	fFixtures.push_back(newFixture);
		
	return newFixture;
		

}

SceneDataSceneryObjPtr SceneDataExchange::CreateSceneryObject(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name, SceneDataGroupObjPtr addToContainer)
{
	SceneDataSceneryObjPtr newSceneryObj = new SceneDataSceneryObj(guid);
	addToContainer->AddObject(newSceneryObj);
	
	newSceneryObj->setName(name);
	newSceneryObj->SetTransformMatrix(offset);
	
	return newSceneryObj;
}

SceneDataSceneryObjPtr SceneDataExchange::ReadSceneryObject(const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{
	//----------------------------------------------------------------------------
	// Create new object
	SceneDataSceneryObjPtr newSceneryObj = new SceneDataSceneryObj(guid);
	addToContainer->AddObject(newSceneryObj);
	
	//----------------------------------------------------------------------------
	// Read stuff
	newSceneryObj->ReadFromNode(node, this);
	
	
	return newSceneryObj;
}

SceneDataFocusPointObjPtr SceneDataExchange::CreateFocusPoint(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name, SceneDataGroupObjPtr addToContainer)
{
	//------------------------------------------------------------------------------------
	// Cycle existing focus Point Objects
	for (SceneDataFocusPointObjPtr focusPoint : fFocusPoints)
	{
		// Check if they are sharing the same name
		if (focusPoint->getName() == name)
		{
			// Check if the incomming Guid have value, this is important
			// when the fixture first creates the FocusPoint and there is no real guid for this
			if (guid.GetType() == eNormal)
			{
				// Check what we are assuming
				ASSERTN(kEveryone, focusPoint->getGuid().GetType() != eNormal);
				ASSERTN(kEveryone, addToContainer != nullptr);
				
				// Store the data
				focusPoint->fGuid = guid;
				focusPoint->SetTransformMatrix(offset);
				addToContainer->AddObject(focusPoint);
				
			}
			return focusPoint;
		}
	}
	
	//------------------------------------------------------------------------------------
	// Create the Focus Point
	SceneDataFocusPointObjPtr newFocusPointObj = new SceneDataFocusPointObj(guid);
	if (addToContainer)		{ addToContainer->AddObject(newFocusPointObj); }
	else					{ fFocusPoints.push_back(newFocusPointObj); }
	
	
	//------------------------------------------------------------------------------------
	// Set the parameters for this
	newFocusPointObj->setName(name);
	newFocusPointObj->SetTransformMatrix(offset);
	
	return newFocusPointObj;
}

SceneDataFocusPointObjPtr SceneDataExchange::ReadFocusPoint(const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{
	//----------------------------------------------------------------------------
	// Create new object
	SceneDataFocusPointObjPtr newFocusPointObj = new SceneDataFocusPointObj(guid);
	addToContainer->AddObject(newFocusPointObj);
	
	
	//----------------------------------------------------------------------------
	// Read
	newFocusPointObj->ReadFromNode(node, this);
	
	
	//----------------------------------------------------------------------------
	// Add to Array to resolve
	fFocusPoints.push_back(newFocusPointObj);
	
	return newFocusPointObj;
}

SceneDataTrussObjPtr SceneDataExchange::CreateTruss(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name, SceneDataGroupObjPtr addToContainer)
{
	SceneDataTrussObjPtr newTrussObj = new SceneDataTrussObj(guid);
	addToContainer->AddObject(newTrussObj);
	
	newTrussObj->setName(name);
	newTrussObj->SetTransformMatrix(offset);
	
	return newTrussObj;
}

SceneDataTrussObjPtr SceneDataExchange::ReadTruss(const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{
	//----------------------------------------------------------------------------
	// Create new Object
	SceneDataTrussObjPtr newTrussObj = new SceneDataTrussObj(guid);
	addToContainer->AddObject(newTrussObj);
	
	//----------------------------------------------------------------------------
	//Read
	newTrussObj->ReadFromNode(node, this);
	
	return newTrussObj;
}

SceneDataSupportObjPtr SceneDataExchange::CreateSupport(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name, SceneDataGroupObjPtr addToContainer)
{
	SceneDataSupportObjPtr newSupportObj = new SceneDataSupportObj(guid);
	addToContainer->AddObject(newSupportObj);
	
	newSupportObj->setName(name);
	newSupportObj->SetTransformMatrix(offset);
	
	return newSupportObj;
}

SceneDataSupportObjPtr SceneDataExchange::ReadSupport(const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{
	//----------------------------------------------------------------------------
	// Create new Object
	SceneDataSupportObjPtr newSupportObj = new SceneDataSupportObj(guid);
	addToContainer->AddObject(newSupportObj);
	
	//----------------------------------------------------------------------------
	//Read
	newSupportObj->ReadFromNode(node, this);
	
	return newSupportObj;
}

SceneDataVideoScreenObjPtr SceneDataExchange::CreateVideoScreen(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name, SceneDataGroupObjPtr addToContainer)
{
	SceneDataVideoScreenObjPtr newVSObj = new SceneDataVideoScreenObj(guid);
	addToContainer->AddObject(newVSObj);
	
	newVSObj->setName(name);
	newVSObj->SetTransformMatrix(offset);
		
	return newVSObj;
}

SceneDataVideoScreenObjPtr SceneDataExchange::ReadVideoScreen(const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{
	//----------------------------------------------------------------------------
	// Create new Object
	SceneDataVideoScreenObjPtr newVSObj = new SceneDataVideoScreenObj(guid);
	addToContainer->AddObject(newVSObj);
	
	//----------------------------------------------------------------------------
	// Read
	newVSObj->ReadFromNode(node, this);
	
	return newVSObj;
}

SceneDataProjectorObjPtr SceneDataExchange::CreateProjector(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name, SceneDataGroupObjPtr addToContainer)
{
	SceneDataProjectorObjPtr newProjectorObj = new SceneDataProjectorObj(guid);
	addToContainer->AddObject(newProjectorObj);
	
	newProjectorObj->setName(name);
	newProjectorObj->SetTransformMatrix(offset);
		
	return newProjectorObj;
}

SceneDataProjectorObjPtr SceneDataExchange::ReadProjector(const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{
	//----------------------------------------------------------------------------
	// Create new Object
	SceneDataProjectorObjPtr newProjectorObj = new SceneDataProjectorObj(guid);
	addToContainer->AddObject(newProjectorObj);
	
	//----------------------------------------------------------------------------
	// Read
	newProjectorObj->ReadFromNode(node, this);
	
	return newProjectorObj;
}

SceneDataSymbolObjPtr SceneDataExchange::CreateSymbol(const SceneDataGUID& guid, const VWTransformMatrix& offset, SceneDataSymDefObjPtr symDef)
{
	SceneDataSymbolObjPtr newSymbolObj = new SceneDataSymbolObj(guid);
	
	newSymbolObj->SetTransformMatrix(offset);
	newSymbolObj->SetSymDef(symDef);
	
	return newSymbolObj;
}

bool SceneDataExchange::WriteToFile(const IFileIdentifierPtr& file)
{
	//-------------------------------------------------------------------------------------------------
	// Write the scene file
    IXMLFileIOBufferImpl sceneDataXmlBuffer;
	WriteXml(fWorkingFolder, sceneDataXmlBuffer);
	
	
	//-------------------------------------------------------------------------------------------------
	// Create a ZIP File
	IZIPFilePtr zipfile ( IID_ZIPFile );
	zipfile->OpenNewWrite(file);


	//-------------------------------------------------------------------------------------------------
	// Write the scene file
    TXString filename = "GeneralSceneDescription.xml";
	
	// Prepare Temp Storage for ZIP buffer
    size_t	size = 0;
    void*	data = nullptr;
	
	// Get the data from the XML
    sceneDataXmlBuffer.GetDataSize(size);
    sceneDataXmlBuffer.GetData(data);
	
	
	// Copy into the Buffer for the ZIP
    ISceneDataZipBuffer zipXmlBuffer;
    zipXmlBuffer.SetData(data, size);
	
	// Add the xml zipfile buffer
    SceneDataZip::AddFileToZip(zipfile, zipXmlBuffer, filename);
	
	//-------------------------------------------------------------------------------------------------	
    // Add the Resources

	for (size_t i = 0; i < f3DS_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, f3DS_FilesToAdd.at(i),  ERessourceType::Model3DS, false/*Delete*/);
	}

	for (size_t i = 0; i < f3DSLow_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, f3DSLow_FilesToAdd.at(i),  ERessourceType::Model3DSLow, false/*Delete*/);
	}

	for (size_t i = 0; i < f3DSHigh_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, f3DSHigh_FilesToAdd.at(i),  ERessourceType::Model3DSHigh, false/*Delete*/);
	}

	for (size_t i = 0; i < fSVG_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, fSVG_FilesToAdd.at(i), ERessourceType::ModelSVG, false/*Delete*/);
	}

	for (size_t i = 0; i < fSVGSide_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, fSVGSide_FilesToAdd.at(i), ERessourceType::ModelSVGSide, false/*Delete*/);
	}

	for (size_t i = 0; i < fSVGFront_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, fSVGFront_FilesToAdd.at(i), ERessourceType::ModelSVGFront, false/*Delete*/);
	}

	for (size_t i = 0; i < fGLTF_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, fGLTF_FilesToAdd.at(i),  ERessourceType::ModelGLTF, false/*Delete*/);
	}

	for (size_t i = 0; i < fGLTFLow_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, fGLTFLow_FilesToAdd.at(i),  ERessourceType::ModelGLTFLow, false/*Delete*/);
	}

	for (size_t i = 0; i < fGLTFHigh_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, fGLTFHigh_FilesToAdd.at(i),  ERessourceType::ModelGLTFHigh, false/*Delete*/);
	}

	for (size_t i = 0; i < fWheel_Image_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, fWheel_Image_FilesToAdd.at(i), ERessourceType::ImageWheel, false/*Delete*/);
	}

	for (size_t i = 0; i < fFixtureResources_FilesToAdd.size(); i++)
	{        
		SceneDataZip::AddFileToZip(zipfile, fFixtureResources_FilesToAdd.at(i), ERessourceType::RessoureFixture, false/*Delete*/);
	}

	for (size_t i = 0; i < fBuffersToAdd.size(); i++)
	{        
    	SceneDataZip::AddFileToZip(zipfile, *fBuffersToAdd[i].second, fBuffersToAdd[i].first);
		delete fBuffersToAdd[i].second;
	}
	fBuffersToAdd.clear();
	
	//-------------------------------------------------------------------------------------------------
	// Add the needed
	for (const TXString& gdtfFileName : fRequiredGdtfFiles)
	{
		//
		bool			exported		= false;
		
		for (IFolderIdentifierPtr folder : fGdtfFolderLocations)
		{
			IFileIdentifierPtr gdtfFilePtr (IID_FileIdentifier);
			gdtfFilePtr->Set(folder, gdtfFileName);
			
			if		(SceneDataZip::AddFileToZip(zipfile, gdtfFilePtr, ERessourceType::RessoureFixture, false/*Delete*/, false/*ASSERT*/))	{ exported = true;  break; }
		}
	
		
		// If there is no match, STOP
		if (!exported) { DSTOP((kEveryone,"No matching GDTF File found in one of the selected folders!")); }
		
	}
	

	//-------------------------------------------------------------------------------------------------
	// Store the file on disk
	zipfile->Close();
	
	
	return true;
}

void SceneDataExchange::AddProviderAndProviderVersion(const TXString& provider, const TXString& providerVersion)
{
	fProvider = provider;
	fProviderVersion = providerVersion;
}

bool SceneDataExchange::WriteXml(const IFolderIdentifierPtr& folder, IXMLFileIOBufferImpl& outBuffer)
{
    
    // Try to get a pointer to a XML File
    IXMLFilePtr	pXMLFile ( IID_XMLFile);
    if (! pXMLFile) { return false; }
    
	//-------------------------------------------------------------------------------------------------
	// Create new file
	if ( VCOM_SUCCEEDED( pXMLFile->CreateNew( XML_Val_RootNodeName ) ) )
	{
		//-------------------------------------------------------------------------------------------------
		// Get root node
		IXMLFileNodePtr        pDatabaseRoot;
		if ( VCOM_SUCCEEDED( pXMLFile->GetRootNode( & pDatabaseRoot ) ) )
		{
			//-------------------------------------------------------------------------------------------------
			// Set Version for the export Format
			pDatabaseRoot->SetNodeAttributeValue(XML_Val_RootAttrMainVersion,		TXString() << kMVR_MajorVersion);
			pDatabaseRoot->SetNodeAttributeValue(XML_Val_RootAttrMinorVersion,		TXString() << kMVR_MinorVersion);
			pDatabaseRoot->SetNodeAttributeValue(XML_Val_RootAttrProvider,			fProvider);
			pDatabaseRoot->SetNodeAttributeValue(XML_Val_RootAttrProviderVersion,	fProviderVersion);
			
			
			//-------------------------------------------------------------------------------------------------
			// Create Child Node for User Data
			IXMLFileNodePtr pUserDataNode;
			if ( VCOM_SUCCEEDED( pDatabaseRoot->CreateChildNode( XML_Val_UserDataNodeName, & pUserDataNode ) ) )
			{

				for (SceneDataProviderObjPtr sceneData : fProviderObjs)
				{
					sceneData->PrintToFile(pUserDataNode, this);
				}
			}
			
			//-------------------------------------------------------------------------------------------------
			// Create Child Node for Scene
			IXMLFileNodePtr pSceneNode;
			if ( VCOM_SUCCEEDED( pDatabaseRoot->CreateChildNode( XML_Val_SceneNodeName, & pSceneNode ) ) )
			{
				// ----------------------------------------------------------------------------------------------------------------------------
				// The order here is importand when this runs from Vectorworks. Symdef will be generated by traversing
				// linked geometry handels. So during export, new object will be generated. For this first export the SceneDataObjWithMatrix
				// then the symdefs.
				// ----------------------------------------------------------------------------------------------------------------------------
				
				// Create Child Node for Layers
				IXMLFileNodePtr pLayersDataNode;
				if ( VCOM_SUCCEEDED( pSceneNode->CreateChildNode( XML_Val_LayersNodeName, & pLayersDataNode ) ) )
				{
					for (SceneDataObjWithMatrixPtr obj : fChildObjs)
					{
						obj->PrintToFile(pLayersDataNode, this);
					}
				}
				
				
				// Create Child Node for AuxData
				IXMLFileNodePtr pAuxDataNode;
				if ( VCOM_SUCCEEDED( pSceneNode->CreateChildNode( XML_Val_AuxDataNodeName, & pAuxDataNode ) ) )
				{
					for (SceneDataAuxObjPtr auxObj : fAuxDataObjs)
					{
						auxObj->PrintToFile(pAuxDataNode, this);
					}
				}
				

			}
		}
		//-------------------------------------------------------------------------------------------------
		// Check if all focus position where added to a layer
		for (SceneDataFocusPointObjPtr focusPoint : fFocusPoints)
		{
			ASSERTN(kEveryone, focusPoint->GetContainer() != nullptr);
			
		}
		
		//-------------------------------------------------------------------------------------------------
		// write file

		
        pXMLFile->WriteBuffer(&outBuffer, VectorworksMVR::Filing::EXMLEncoding::eXMLEncoding_UTF8);
		
	}

	return true;
}

bool SceneDataExchange::AddNeededGdtfFile(const TXString& gdtfName)
{
	//-------------------------------------------------------------------------------------------------
	// Check if this is already
	for (const TXString& name : fRequiredGdtfFiles)
	{
		if (name == gdtfName) { return false; }
	}
	
	
	//-------------------------------------------------------------------------------------------------
	fRequiredGdtfFiles.push_back(gdtfName);
	
	return false;
}

void SceneDataExchange::AddLocationForGdtfFiles(IFolderIdentifierPtr folder)
{
	fGdtfFolderLocations.push_back(folder);
}


bool SceneDataExchange::ReadFromFile(const IFileIdentifierPtr& file)
{
	// First clear the array
	fSceneObjects.clear();

	//-------------------------------------------------------------------------------------------------
	// Duplicate ZIP File
	TXString filename;
	file->GetFileName(filename);
	
	
	//-------------------------------------------------------------------------------------------------
	// Create a ZIP File
	IZIPFilePtr zipfile ( IID_ZIPFile );
	zipfile->OpenRead(file);
	
	// Prepare
    ISceneDataZipBuffer xmlFileBuffer;
	
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	std::string outPath	= "";
	std::string inPath	= "";
	while (VCOM_SUCCEEDED( zipfile->GetNextFile(inPath, outPath)))
	{
		// This is the current file that we are reading
        ISceneDataZipBuffer buffer;
		
		zipfile->GetFile(outPath, &buffer);
		
        if (outPath == "GeneralSceneDescription.xml")
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
			// Prepare pointer to the new files
			IFileIdentifierPtr file (IID_FileIdentifier);
			file->Set(fWorkingFolder, outPath);
			
			// dump buffer into file
            buffer.WriteToFile(file);
			
			// Add it into the file list
            fFilesInZip.push_back(file);
		
        }
        inPath = outPath;
	}
	
	//-------------------------------------------------------------------------------------------------
	// Close the zip file
	zipfile->Close();
	
	
	//-------------------------------------------------------------------------------------------------
	// Prepare bools for checksum checks

	ASSERTN(kEveryone, xmlFileBuffer.IsSet());
    if (xmlFileBuffer.IsSet())
    {
		// Read from Scene Description
		ReadFromGeneralSceneDescription(xmlFileBuffer);
    }

	return true;	
}



void SceneDataExchange::ReadFromGeneralSceneDescription(ISceneDataZipBuffer& xmlFile)
{
	// Prepare pointer to XML file
	IXMLFilePtr file ( IID_XMLFile );
	
	
    size_t	size = 0;								xmlFile.GetDataSize(size);
    void*	data = malloc(size * sizeof(char));		xmlFile.CopyDataInto(data, size);
	
	// Set the data
    IXMLFileIOBufferImpl xmlBuffer;
    xmlBuffer.SetData(data, size);
	
	// Housekeeping
	std::free(data);
	
    if (VCOM_SUCCEEDED(file->ReadBuffer(&xmlBuffer, EXMLEncoding::eXMLEncoding_UTF8)))
	{
		// ----------------------------------------------------------------
		// Get the root node
		IXMLFileNodePtr rootNode = nullptr;
		if (VCOM_SUCCEEDED(file->GetRootNode( & rootNode)) && rootNode)
		{
			TXString rootName;
			rootNode->GetNodeName(rootName);
			ASSERTN(kEveryone, rootName == XML_Val_RootNodeName);
			
			// ----------------------------------------------------------------
			// Find the user data Node
			IXMLFileNodePtr userDataNode = nullptr;
			if (VCOM_SUCCEEDED(rootNode->FindChildNode(XML_Val_UserDataNodeName, & userDataNode)))
			{
					GdtfConverter::TraverseNodes(userDataNode, "", XML_Val_DataNodeName, [this] (IXMLFileNodePtr objNode) -> void
						{
							// Create the object
							SceneDataProviderObj* userData = new SceneDataProviderObj();
							
							// Read from node
							userData->ReadFromNode(objNode, this);
							
							// Add to list
							fProviderObjs.push_back(userData);
							return;
						});
			} ASSERTN(kEveryone, userDataNode != nullptr);
			
			
			// ----------------------------------------------------------------
			// Find the Scene Node
			IXMLFileNodePtr sceneNode = nullptr;
			if (VCOM_SUCCEEDED(rootNode->FindChildNode(XML_Val_SceneNodeName, & sceneNode)))
			{
				// ----------------------------------------------------------------
				// Find the Scene Node
				IXMLFileNodePtr auxDataNode = nullptr;
				if (VCOM_SUCCEEDED(sceneNode->FindChildNode(XML_Val_AuxDataNodeName, & auxDataNode)))
				{
					IXMLFileNodePtr auxDataObj = nullptr;
					if (VCOM_SUCCEEDED(auxDataNode->GetFirstChildNode( & auxDataObj)))
					{
						
						while (auxDataObj)
						{
							// ---------------------------------------------------------------------------
							// Check the Node Name
							TXString nodeName;
							auxDataObj->GetNodeName(nodeName);
							
							// ---------------------------------------------------------------------------
							// Do stuff with Layer
							if (nodeName == XML_Val_SymDefNodeName)				{ ReadSymDefObject(auxDataObj);		}
							if (nodeName == XML_Val_PositionNodeName)			{ ReadPositionObject(auxDataObj);	}
							if (nodeName == XML_Val_ClassNodeName)				{ ReadClassObject(auxDataObj);		}
							if (nodeName == XML_Val_MappingDefinitionNodeName)	{ ReadMappingDefinitionObject(auxDataObj); }
							
							// ---------------------------------------------------------------------------
							// Step to the next node
							IXMLFileNodePtr nextNode = nullptr;
							auxDataObj->GetNextSiblingNode( & nextNode);
							auxDataObj = nextNode;
						}
					}
					
				}ASSERTN(kEveryone, auxDataNode != nullptr);
				
				// ----------------------------------------------------------------
				// Find the Scene Node
				IXMLFileNodePtr layersNode = nullptr;
				if (VCOM_SUCCEEDED(sceneNode->FindChildNode(XML_Val_LayersNodeName, & layersNode)))
				{
					IXMLFileNodePtr layerObjNode = nullptr;
					if (VCOM_SUCCEEDED(layersNode->GetFirstChildNode( & layerObjNode)))
					{
						
						while (layerObjNode)
						{
							// ---------------------------------------------------------------------------
							// Check the Node Name
							TXString nodeName;
							layerObjNode->GetNodeName(nodeName);
							ASSERTN(kEveryone, nodeName == XML_Val_LayerObjectNodeName);
							
							// ---------------------------------------------------------------------------
							// Do stuff with Layer
							if (nodeName == XML_Val_LayerObjectNodeName) { ProcessLayer(layerObjNode); }
							
							// ---------------------------------------------------------------------------
							// Step to the next node
							IXMLFileNodePtr nextNode = nullptr;
							layerObjNode->GetNextSiblingNode( & nextNode);
							layerObjNode = nextNode;
						}
					}
					
				}ASSERTN(kEveryone, layersNode != nullptr);
				
			} ASSERTN(kEveryone, sceneNode != nullptr);
			
		}ASSERTN(kEveryone, rootNode != nullptr);
		
	}
	
	
	
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Resolve pointers from uuids
	for (SceneDataFixtureObjPtr fixture : fFixtures)
	{
		TXString focusUuid		= fixture->GetUnresolvedFocusUUID();
		TXString postionUuid	= fixture->GetUnresolvedPositionUUID();
		
		if (focusUuid.IsEmpty() == false)
		{
			bool match  = false;
			for (SceneDataFocusPointObjPtr focusPoint : fFocusPoints)
			{
				if (focusUuid == focusPoint->getGuid().GetUUIDString())
				{
					fixture->SetFocusPoint(focusPoint);
					match = true;
					break;
				}
			}
			// Check if there is a match
			if (!match) { DSTOP((kEveryone, "Could not resolve UUID from Focus to Object")); }
		}
		
		if (postionUuid.IsEmpty() == false)
		{
			bool match  = false;
			for (SceneDataPositionObjPtr position : fPositions)
			{
				if (postionUuid == position->getGuid().GetUUIDString())
				{
					fixture->SetPosition(position);
					match = true;
					break;
				}
			}
			// Check if there is a match
			if (!match) { DSTOP((kEveryone, "Could not resolve UUID from Postion to Object")); }
		}
	}
	
	//------------------------------------------------------------------------------------------------------------------------------------------------------------------------
	// Resolve classes from uuids
	for (SceneDataObjWithMatrixPtr scObj : fSceneObjects)
	{
		TXString classUuid		= scObj->GetUnresolvedClass();
		
		if (classUuid.IsEmpty() == false)
		{
			bool match  = false;
			for (SceneDataClassObjPtr classObj : fClasses)
			{
				if (classUuid.Equal( classObj->getGuid().GetUUIDString() ))
				{
					scObj->SetClass(classObj);
					match = true;
					break;
				}
			}
			
			// Check if there is a match
			if (!match) { DSTOP((kEveryone, "Could not resolve UUID from Class to Object")); }
			
		}

        //-----------------------------------------------------------------------------
        // Resolve Symbols in Symbols
        TSymDefMap::iterator it = fSymDefMap.begin();
        while(it != fSymDefMap.end())
        {
            SceneDataSymDefObjPtr symDef = it->second;

            for (SceneDataGeoInstanceObjPtr geoObj : symDef->getGeometryArray()) 
            {
                if (geoObj->IsSymDef())
                {
				    SceneDataSymbolObjPtr symObj = static_cast<SceneDataSymbolObjPtr>(geoObj);
				    SceneDataSymDefObjPtr ptr    = fSymDefMap[symObj->GetUnresolvedSymDef()];
				
				    ASSERTN(kEveryone, ptr);
				    if(ptr) { symObj->SetSymDef(ptr); }
                }
            }

            it++;
        }

		for(SceneDataGeoInstanceObjPtr geoObj : scObj->GetGeometryArr())
		{
			if(geoObj->IsSymDef())
			{
				SceneDataSymbolObjPtr symObj = static_cast<SceneDataSymbolObjPtr>(geoObj);
				SceneDataSymDefObjPtr ptr    = fSymDefMap[symObj->GetUnresolvedSymDef()];
				
				ASSERTN(kEveryone, ptr);
				if(ptr) { symObj->SetSymDef(ptr); }
			}
		}
		
	}
	
}

void SceneDataExchange::ProcessLayer(const IXMLFileNodePtr& node)
{
	TXString			uuid = "";
	
	if (VCOM_SUCCEEDED(node->GetNodeAttributeValue(XML_Val_GuidAttrName, uuid)))
	{		
		SceneDataLayerObjPtr layerObj = ReadLayerObject(SceneDataGUID(uuid),node);
		
		ASSERTN(kEveryone, layerObj != nullptr);
		if (layerObj)
		{			
            this->ReadChildObjs(node, layerObj);
		}
	}
}

void SceneDataExchange::ReadChildObjs(const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{
	//--------------------------------------------------------------------------------------------
	// Now read the child nodes
	IXMLFileNodePtr childObjsNode = nullptr;
	if (VCOM_SUCCEEDED(node->GetChildNode(XML_Val_ChildObsNodeName, & childObjsNode)))
	{
		IXMLFileNodePtr objNode = nullptr;
		if (VCOM_SUCCEEDED(childObjsNode->GetFirstChildNode( & objNode)))
		{
			while (objNode)
			{
				// ---------------------------------------------------------------------------
				// Check the Node Name
				TXString	nodeName;
				objNode->GetNodeName(nodeName);
				
				// ---------------------------------------------------------------------------
				// Check the Uiid Name
				TXString	groupUuid;
				if (VCOM_SUCCEEDED((objNode->GetNodeAttributeValue(XML_Val_GuidAttrName, groupUuid))))
				{
					SceneDataObjWithMatrixPtr obj = nullptr;
					
					if		( nodeName == XML_Val_FixtureNodeName)				{ obj = ReadFixture(		SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_SceneObjectNodeName)			{ obj = ReadSceneryObject(	SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_FocusPointObjectNodeName)		{ obj = ReadFocusPoint(		SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_TrussObjectNodeName)			{ obj = ReadTruss(			SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_VideoScreenObjectNodeName)	{ obj = ReadVideoScreen(	SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_SupportObjectNodeName)		{ obj = ReadSupport(		SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_ProjectorObjectNodeName)		{ obj = ReadProjector(		SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if ( nodeName == XML_Val_GroupNodeName)				{ obj = ProcessGroup(objNode, addToContainer); }
					     
                    auto grp = dynamic_cast<SceneDataGroupObjPtr>(obj);
                    if (grp)
                    {
                        this->ReadChildObjs(objNode, grp);
                    }
					// ---------------------------------------------------------------------------
					// Add the object to list if it is a scene object
					if(obj && (nodeName != XML_Val_GroupNodeName))
					{
						// Check if the uuid isn't duplicated
						SceneDataGUID guid = SceneDataGUID(groupUuid);
						for(SceneDataObjWithMatrixPtr sceneObject : fSceneObjects)
						{
							if(sceneObject->getGuid() == guid)
							{
								fDuplicatedUuids = true;
								DSTOP((kEveryone, "Some scene object's UUID is duplicated"));
							}
						}

						fSceneObjects.push_back(obj);
					}
				}

				// ---------------------------------------------------------------------------
				// Step to the next node
				IXMLFileNodePtr nextNode = nullptr;
				objNode->GetNextSiblingNode( & nextNode);
				objNode = nextNode;
			}
			
		}
	}
}

SceneDataGroupObjPtr SceneDataExchange::ProcessGroup(const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer)
{	
	SceneDataGroupObjPtr group = nullptr;

	TXString			groupUuid = "";
	if (VCOM_SUCCEEDED(node->GetNodeAttributeValue(XML_Val_GuidAttrName, groupUuid)))
	{
		group = ReadGroupObject(SceneDataGUID(groupUuid),node, addToContainer);
		addToContainer = group;
	}    

	return group;
}

void SceneDataExchange::AddFileToZip(const IFileIdentifierPtr& file, ERessourceType resType)
{
    switch (resType)  
    {
		case ERessourceType::ImageWheel: 		fWheel_Image_FilesToAdd.push_back(file); return;
		case ERessourceType::Model3DS: 			f3DS_FilesToAdd.push_back(file); return;
		case ERessourceType::Model3DSLow: 		f3DSLow_FilesToAdd.push_back(file); return;
		case ERessourceType::Model3DSHigh: 		f3DSHigh_FilesToAdd.push_back(file); return;
		case ERessourceType::ModelSVG: 			fSVG_FilesToAdd.push_back(file); return;
		case ERessourceType::ModelSVGSide: 		fSVGSide_FilesToAdd.push_back(file); return;
		case ERessourceType::ModelSVGFront: 	fSVGFront_FilesToAdd.push_back(file); return;
		case ERessourceType::ModelGLTF: 		fGLTF_FilesToAdd.push_back(file); return;
		case ERessourceType::ModelGLTFLow: 		fGLTFLow_FilesToAdd.push_back(file); return;
		case ERessourceType::ModelGLTFHigh: 	fGLTFHigh_FilesToAdd.push_back(file); return;
		case ERessourceType::RessoureFixture: 	fFixtureResources_FilesToAdd.push_back(file);return;
    }        

	DSTOP((kEveryone, "Unexpected ERessourceType Enum for AddFileToZip"));
}

void SceneDataExchange::AddBufferToZip(const TXString& fileName, ISceneDataZipBuffer* buffer)
{
    fBuffersToAdd.push_back(std::make_pair(fileName, buffer));
}

size_t SceneDataExchange::GetAttachedFileCount()
{
    return fFilesInZip.size();
}

bool SceneDataExchange::GetAttachedFileCountAt(size_t at, IFileIdentifierPtr& outFile)
{
	bool retVal = (at < fFilesInZip.size());
	if(retVal)	{ outFile = fFilesInZip.at(at); }

    return retVal;
}

bool SceneDataExchange::GetDuplicatedUuids() const
{
	return fDuplicatedUuids;
}


