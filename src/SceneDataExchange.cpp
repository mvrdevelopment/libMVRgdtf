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
	
	GdtfConverter::ConvertUUID(uuid, _uuid);
	_type	= eNormal;
}

SceneDataGUID::SceneDataGUID(const VWFC::Tools::VWUUID& uuid)
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
// SceneDataGUID
SceneDataGeometryObj::SceneDataGeometryObj() : SceneDataGeoInstanceObj(SceneDataGUID(eNoGuid, ""), false /* Is No Symbol */)
{

}

SceneDataGeometryObj::~SceneDataGeometryObj()
{
	
}

void SceneDataGeometryObj::GetTransformMatrix(VWTransformMatrix& matrix) const
{
	matrix = fMatrix;
}

void SceneDataGeometryObj::SetTransformMatrix(const VWTransformMatrix& matrix)
{
	fMatrix = matrix;
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
	// TODO
	SetFileName("empty.3ds");
	
	pNode->SetNodeAttributeValue(XML_Val_GeometryObjectAttrFile, GetFileName());
	
}

void SceneDataGeometryObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	// Call Parent
	SceneDataGeoInstanceObj::OnReadFromNode(pNode, exchange);
	
	TXString file;
	pNode->GetNodeAttributeValue(XML_Val_GeometryObjectAttrFile, file);
	
	SetFileName(file);
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
	pNode->GetNodeAttributeValue(XML_Val_DataNodeAttrProvider,	fVersion);
	
	// ------------------------------------------------------------------------------
	// Read Provider
	pNode->GetNodeAttributeValue(XML_Val_DataNodeAttrVersion,	fProvider);
	
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
	
	
	// Create the child node
	IXMLFileNodePtr pChildNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_ChildObsNodeName, & pChildNode ) ) )
	{
		IXMLFileNodePtr pChild;
		if ( VCOM_SUCCEEDED( pChildNode->GetFirstChildNode( & pChild)))
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
		}
		
	}
	
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
// SceneDataSymDefObj
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
// SceneDataAuxObj
SceneDataObjWithMatrix::SceneDataObjWithMatrix(const SceneDataGUID& guid) : SceneDataObj(guid)
{
	fInContainer			= nullptr;
	fNextObj				= nullptr;
	fClass					= nullptr;
}

SceneDataObjWithMatrix::~SceneDataObjWithMatrix()
{
	for (SceneDataGeoInstanceObjPtr geoObj : fGeometries) { delete geoObj; }
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
		GdtfConverter::ConvertMatrix(value, fMatrix);
		
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
SceneDataGeoInstanceObj::SceneDataGeoInstanceObj(const SceneDataGUID& guid, bool isSymbol) : SceneDataObjWithMatrix(guid)
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

SceneDataFixtureObj::SceneDataFixtureObj(const SceneDataGUID& guid) : SceneDataObjWithMatrix(guid)
{
	fFocusPoint		= nullptr;
	fPosition		= nullptr;
	fColor			= CRGBColor(255,255,255);
	fUnitNumber		= 0;
	fFixtureTypeId	= 0;
	fCustomId		= 0;
}

SceneDataFixtureObj::~SceneDataFixtureObj()
{
	
}

TXString SceneDataFixtureObj::GetUnresolvedFocusUUID()
{
	return fUnresolvedFocus;
}

TXString SceneDataFixtureObj::GetUnresolvedPositionUUID()
{
	return fUnresolvedPosition;
}

const TXString& SceneDataFixtureObj::GetGdtfFile()
{
	return fGdtfFile;
}

const TXString& SceneDataFixtureObj::GetGdtfDmxMode()
{
	return fGdtfDmxMode;
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

void SceneDataFixtureObj::SetGDTFFile(const TXString& path)
{
	fGdtfFile = path;
}

void SceneDataFixtureObj::SetGdtfDmxMode(const TXString& path)
{
	fGdtfDmxMode = path;
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

void SceneDataFixtureObj::SetCustomId(const size_t& value)
{
	fCustomId = value;
}

void SceneDataFixtureObj::SetFixtureTypeId(const Sint8& value)
{
	fFixtureTypeId = value;
}

void SceneDataFixtureObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	SceneDataObjWithMatrix::OnPrintToFile(pNode, exchange);
	
	//--------------------------------------------------------------------------------------------
	// Print the GDTF File
	IXMLFileNodePtr pGDTFNode;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureGDTFSpec, & pGDTFNode ) ) )
	{
		pGDTFNode->SetNodeValue(GetGdtfFile());
		exchange->AddNeededGdtfFile(GetGdtfFile());

	}
	
	//--------------------------------------------------------------------------------------------
	// Print the DmxMode
	IXMLFileNodePtr pDmxModeNode;
	if ( VCOM_SUCCEEDED( pNode->CreateChildNode( XML_Val_FixtureDMXMode, & pDmxModeNode ) ) )
	{
		pDmxModeNode->SetNodeValue(GetGdtfDmxMode());
		
	}
	
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
				pAdressNode->SetNodeAttributeValue(XML_Val_FixtureAttrBreak, TXString() << adress.fBreak);
				pAdressNode->SetNodeValue(									 TXString() << adress.fAbsuluteAdress);
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
	// Print the UnitNumber
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
	
}

void SceneDataFixtureObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	SceneDataObjWithMatrix::OnReadFromNode(pNode, exchange);
	
	//--------------------------------------------------------------------------------------------
	// Read the adress
	IXMLFileNodePtr pGDTFNode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureGDTFSpec, & pGDTFNode ) ) )			{  pGDTFNode->GetNodeValue(fGdtfFile); }
	
	//--------------------------------------------------------------------------------------------
	// Read the adress
	IXMLFileNodePtr pDmxMode;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureDMXMode, & pDmxMode ) ) )				{  pDmxMode->GetNodeValue(fGdtfDmxMode); }
	
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
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureUnitNumber, & pUnitNumberNode ) ) )	{ pUnitNumberNode->GetNodeValue(unitNumber);		GdtfConverter::ConvertInteger(unitNumber, fUnitNumber); }
	
	
	//--------------------------------------------------------------------------------------------
	// Read the FixtureTypeId
	IXMLFileNodePtr pFixtureTypeId;
	TXString		fixtureTypeStr;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureTypeId, & pFixtureTypeId ) ) )			{ pFixtureTypeId->GetNodeValue(fixtureTypeStr);		GdtfConverter::ConvertInteger(fixtureTypeStr, this->fFixtureTypeId); }
	
	

	//--------------------------------------------------------------------------------------------
	// Read the Custom Id
	IXMLFileNodePtr pCustomId;
	TXString		customIdStr;
	if ( VCOM_SUCCEEDED( pNode->GetChildNode( XML_Val_FixtureCustomid, & pCustomId ) ) )			{ pCustomId->GetNodeValue(customIdStr);			GdtfConverter::ConvertInteger(customIdStr, this->fCustomId); }
	
	
	//--------------------------------------------------------------------------------------------
	// Read the Addresses

	GdtfConverter::TraverseNodes(pNode, XML_Val_FixtureAddresses, XML_Val_FixtureAddress, [this] (IXMLFileNodePtr pNode) -> void
								 {
									 // Create memory for adresses
									 Sint32 dmx			= 0; TXString dmxStr;
									 Sint32 breakId		= 0; TXString breakIdStr;
									 
									 // Read and Convert
									 pNode->GetNodeValue(dmxStr);											GdtfConverter::ConvertInteger(dmxStr,		dmx);
									 pNode->GetNodeAttributeValue(XML_Val_FixtureAttrBreak, breakIdStr);	GdtfConverter::ConvertInteger(breakIdStr,	breakId);
									 
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
		GdtfConverter::ConvertColor(colorStr,fColor);
			
	}
	
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

ESceneDataObjectType SceneDataGroupObj::GetObjectType()
{
	return ESceneDataObjectType::eGroup;
}

void SceneDataGroupObj::OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange)
{
	// Call base class
	SceneDataObjWithMatrix::OnPrintToFile(pNode, exchange);

	
	// Create the child node
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

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataGroupObj
SceneDataSceneryObj::SceneDataSceneryObj(const SceneDataGUID& guid) : SceneDataObjWithMatrix(guid)
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
SceneDataFocusPointObj::SceneDataFocusPointObj(const SceneDataGUID& guid) : SceneDataObjWithMatrix(guid)
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
SceneDataTrussObj::SceneDataTrussObj(const SceneDataGUID& guid) : SceneDataObjWithMatrix(guid)
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

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataTrussObj
SceneDataVideoScreenObj::SceneDataVideoScreenObj(const SceneDataGUID& guid) : SceneDataObjWithMatrix(guid)
{
	
}

SceneDataVideoScreenObj::~SceneDataVideoScreenObj()
{
	
}

TXString SceneDataVideoScreenObj::GetNodeName()
{
	return TXString( XML_Val_VideoScreenObjectNodeName );
}

ESceneDataObjectType SceneDataVideoScreenObj::GetObjectType()
{
	return ESceneDataObjectType::eVideoScreen;
}

// ----------------------------------------------------------------------------------------------------------------------------------
// SceneDataTrussObj
SceneDataSymbolObj::SceneDataSymbolObj(const SceneDataGUID& guid) : SceneDataGeoInstanceObj(guid, true /*Is SymbolDef*/), fSymDef(ePlaceHolder, "Missing SymDef")
{
	fIsInitialized = false;
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
	
	if (fIsInitialized)
	{
		pNode->SetNodeAttributeValue(XML_Val_GuidSymdefAttrName,	fSymDef);
	}
}

void SceneDataSymbolObj::OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange)
{
	SceneDataObjWithMatrix::OnReadFromNode(pNode, exchange);
	
	TXString value;
	pNode->GetNodeAttributeValue(XML_Val_GuidSymdefAttrName,	value);
	
	fIsInitialized = true;
	fSymDef = SceneDataGUID(value);
	
}

void SceneDataSymbolObj::SetSymDef(SceneDataSymDefObjPtr symDef)
{
	ASSERTN(kEveryone, fIsInitialized == false);
	fIsInitialized = true;
	fSymDef = SceneDataGUID(symDef->getGuid());;
}

SceneDataGUID SceneDataSymbolObj::GetSymDef()
{
	ASSERTN(kEveryone, fIsInitialized == true);
	return fSymDef;
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
			SceneDataSymDefObjPtr symDef = dynamic_cast<SceneDataSymDefObjPtr>(auxObj);
			
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
			SceneDataSymDefObjPtr existingSymDef = dynamic_cast<SceneDataSymDefObjPtr>(auxObj);
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
	
	return newSymDef;
}

SceneDataLayerObjPtr SceneDataExchange::CreateLayerObject(const SceneDataGUID& guid, const TXString& name)
{
	SceneDataLayerObjPtr newLayer =  new SceneDataLayerObj(guid);
	newLayer->setName(name);
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
	fChildObjs.push_back(newLayer);
	
	// Set the Next Object properlly
	if (before)
	{
		SceneDataLayerObjPtr lastLayer = dynamic_cast<SceneDataLayerObjPtr>(before);
		
		ASSERTN(kEveryone, lastLayer != nullptr);
		if (lastLayer) { lastLayer->SetNextLayer(newLayer); }
		
	}
	
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
		SceneDataPositionObjPtr position = dynamic_cast<SceneDataPositionObjPtr>(auxObj);
		
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
		SceneDataClassObjPtr clas = dynamic_cast<SceneDataClassObjPtr>(auxObj);
		
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

SceneDataGroupObjPtr SceneDataExchange::CreateGroupObject(const SceneDataGUID& guid, const VWTransformMatrix& offset, SceneDataGroupObjPtr addToContainer)
{
	SceneDataGroupObjPtr newGroup = new SceneDataGroupObj(guid);
	addToContainer->AddObject(newGroup);
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
    SceneDataZip::AddFileToZip(zipfile, zipXmlBuffer, filename, true);
	
	//-------------------------------------------------------------------------------------------------
	// Add the 3DS file
	for (size_t i = 0; i < fFilesToAdd.size(); i++)
	{
		SceneDataZip::AddFileToZip(zipfile, fFilesToAdd.at(i), false/*Checksum*/, false/*Delete*/);
	}
	
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
			
			if		(SceneDataZip::AddFileToZip(zipfile, gdtfFilePtr,  true/*Checksum*/, false/*Delete*/, false/*ASSERT*/))	{ exported = true;  break; }
		}
	
		
		// If there is no match, STOP
		if (!exported) { DSTOP((kEveryone,"No matching GDTF File found in one of the selected folders!")); }
		
	}
	

	//-------------------------------------------------------------------------------------------------
	// Store the file on disk
	zipfile->Close();
	
	
	return true;
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
			pDatabaseRoot->SetNodeAttributeValue(XML_Val_RootAttrMainVersion,	TXString() << kMVR_MajorVersion);
			pDatabaseRoot->SetNodeAttributeValue(XML_Val_RootAttrMinorVersion,	TXString() << kMVR_MinorVersion);
			
			
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

		
        pXMLFile->WriteBuffer(&outBuffer, VectorWorks::Filing::EXMLEncoding::eXMLEncoding_UTF8);
		
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
    ISceneDataZipBuffer xmlFileSHA256Buffer;
	
	//-------------------------------------------------------------------------------------------------
	// Decompress the files
	TXString outPath	= "";
	TXString inPath		= "";
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
        else if (outPath == "GeneralSceneDescription.checksum.txt")
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
		// Check the checksum
		ASSERTN(kEveryone, HashManager::HashManager::CheckHashForBuffer(xmlFileBuffer, xmlFileSHA256Buffer) == true);
		
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
							if (nodeName == XML_Val_SymDefNodeName)		{ ReadSymDefObject(auxDataObj);		}
							if (nodeName == XML_Val_PositionNodeName)	{ ReadPositionObject(auxDataObj);	}
							if (nodeName == XML_Val_ClassNodeName)		{ ReadClassObject(auxDataObj);		}
							
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
	}
	
}

void SceneDataExchange::ProcessLayer(const IXMLFileNodePtr& node)
{
	TXString			uuid = "";
	
	if (VCOM_SUCCEEDED(node->GetNodeAttributeValue(XML_Val_GuidAttrName, uuid)))
	{
		// Create the new Layer
		SceneDataLayerObjPtr layerObj = ReadLayerObject(SceneDataGUID(uuid),node);
		
		
		// Now it can be handeled as a group
		ASSERTN(kEveryone, layerObj != nullptr);
		if (layerObj)
		{
			ProcessGroup(node, layerObj, false);
		}
	}
}

void SceneDataExchange::ProcessGroup(const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer, bool createNewContainer)
{
	//--------------------------------------------------------------------------------------------
	// If this was called not by layer object, you need to add a new group object to the tree
	if (createNewContainer)
	{
		// Read the group
		TXString			groupUuid = "";
		if (VCOM_SUCCEEDED(node->GetNodeAttributeValue(XML_Val_GuidAttrName, groupUuid)))
		{
			SceneDataGroupObjPtr group = ReadGroupObject(SceneDataGUID(groupUuid),node, addToContainer);
			addToContainer = group;
		}
		else
		{
			return;
		}

	}
	
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
					// ---------------------------------------------------------------------------
					// Do stuff with Obj
					SceneDataObjWithMatrixPtr obj = nullptr;
					
					if		( nodeName == XML_Val_FixtureNodeName)				{ obj = ReadFixture(		SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_SceneObjectNodeName)			{ obj = ReadSceneryObject(	SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_FocusPointObjectNodeName)		{ obj = ReadFocusPoint(		SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_TrussObjectNodeName)			{ obj = ReadTruss(			SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if	( nodeName == XML_Val_VideoScreenObjectNodeName)	{ obj = ReadVideoScreen(	SceneDataGUID(groupUuid),objNode, addToContainer); }
					else if ( nodeName == XML_Val_GroupNodeName)				{ ProcessGroup(objNode, addToContainer, true); }
					
					
					// ---------------------------------------------------------------------------
					// Add the object to list if it is a scene object
					if (obj) { fSceneObjects.push_back(obj); }
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

void SceneDataExchange::AddFileToZip(const IFileIdentifierPtr& file)
{
    fFilesToAdd.push_back(file);
}