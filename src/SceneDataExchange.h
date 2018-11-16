//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

using namespace VectorWorks::Filing;
using namespace VWFC;

#include "CieColor.h"
#include "XmlFileHelper.h"

namespace SceneData
{

	// ----------------------------------------------------------------------------------------------------------------------------------
	// Predefines
	class SceneDataExchange;
	class SceneDataGroupObj;
	class SceneDataGeoInstanceObj;
	class SceneDataLayerObj;
	
	typedef SceneDataGeoInstanceObj*				SceneDataGeoInstanceObjPtr;
	typedef std::vector<SceneDataGeoInstanceObjPtr>	SceneDataGeometryObjArray;
	typedef std::vector<IFileIdentifierPtr>			TFileIdentifierPtrArray;
	typedef std::vector<IFolderIdentifierPtr>		TFolderIdentifierArray;
	
	
	enum ESceneDataGUIDType : short
	{
		ePlaceHolder	= 0,
		eNormal			= 1,
		eNoGuid			= 2,
	};
	
	enum ESceneDataObjectType : short
	{
		eFixture		= 0,
		eLayer			= 1,
		eGroup			= 2,
		eSymbol			= 3,
		eSceneObject	= 4,
		eFocusPoint		= 5,
		eTruss			= 6,
		eVideoScreen	= 7,
		eSymDef			= -1,
		eProviderObj	= -2,
		ePosition		= -3,
		eGeometryObj	= -4,
		eClassObject	= -5,
	};
	
	enum class ESearchUuidIn
	{
		Symbols,
		Objects,
		Layers,
		Classes,
	};
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataGUID
	class SceneDataGUID
	{
		
	public:
		SceneDataGUID(const TXString& uuid);
		SceneDataGUID(const Tools::VWUUID& uuid);
		SceneDataGUID(ESceneDataGUIDType type, const TXString& debugMessage);
		~SceneDataGUID();
		
		operator TXString();
		bool operator == (const SceneDataGUID& uuid);
		
		
	private:
		Tools::VWUUID			_uuid;
		ESceneDataGUIDType	_type;
		TXString			_typeEntry;
		
	public:
		ESceneDataGUIDType			GetType() const;
		TXString					GetUUIDString() const;
		const VWFC::Tools::VWUUID&	GetUuidObj() const;
	};
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataObj
	class SceneDataObj
	{
		friend SceneDataExchange;
		
	public:
		SceneDataObj(const SceneDataGUID& guid);
		virtual ~SceneDataObj();
		

	private:
		SceneDataGUID	fGuid;
		TXString		fName;
	public:
		SceneDataGUID&	getGuid();
		const TXString&	getName() const;
		void			setName(const TXString& value);
		
		// Write
		void			PrintToFile(IXMLFileNodePtr pContainerNode, SceneDataExchange* exchange);
		void			ReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	public:
		virtual ESceneDataObjectType	GetObjectType() = 0;
		
	protected:
		virtual	TXString				GetNodeName() = 0;
		
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
		
		
		
	};
	typedef SceneDataObj*					SceneDataObjPtr;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataProviderObj
	class SceneDataProviderObj : public SceneDataObj
	{

	public:
		SceneDataProviderObj(const TXString& proveride,const TXString& version);
		virtual ~SceneDataProviderObj();
		
		
	private:
		TXString		fVersion;
		TXString		fProvider;
		
		
		TXStringArray	fKeyArr;
		TXStringArray	fDataArr;
		
	public:
		const TXString&					GetVersion();
		const TXString&					GetProvider();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNod, SceneDataExchange* exchangee);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	public:
		void			AddEntry(const TXString& key,const TXString& value );
		size_t			GetEntryCount();
		bool			GetEntryAt(size_t at, TXString& key,TXString& value );
		

	public:
	};
	typedef SceneDataProviderObj*					SceneDataProviderObjPtr;
	typedef std::vector<SceneDataProviderObjPtr>	SceneDataProviderObjArray;
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataAuxObj
	class SceneDataAuxObj : public SceneDataObj
	{

	public:
		SceneDataAuxObj(const SceneDataGUID& guid);
		virtual ~SceneDataAuxObj();
		
	private:
		
	};
	typedef SceneDataAuxObj*				SceneDataAuxObjPtr;
	typedef std::vector<SceneDataAuxObjPtr> SceneDataAuxObjArray;
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataSymDefObj
	class SceneDataSymDefObj : public SceneDataAuxObj
	{

	public:
		SceneDataSymDefObj(const SceneDataGUID& guid);
		virtual ~SceneDataSymDefObj();
		
	private:
		SceneDataGeometryObjArray fGeometries;
		
	public:
		const SceneDataGeometryObjArray& getGeometryArray() const;
		void							Add(SceneDataGeoInstanceObjPtr object);

	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);

	};
	typedef SceneDataSymDefObj*					SceneDataSymDefObjPtr;
	typedef std::vector<SceneDataSymDefObjPtr>	SceneDataSymDefObjArray;
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataPositionObj
	class SceneDataPositionObj : public SceneDataAuxObj
	{
		
	public:
		SceneDataPositionObj(const SceneDataGUID& guid);
		virtual ~SceneDataPositionObj();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataPositionObj* SceneDataPositionObjPtr;
	typedef std::vector<SceneDataPositionObjPtr>	SceneDataPositionObjArray;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataPositionObj
	class SceneDataClassObj : public SceneDataAuxObj
	{
		
	public:
		SceneDataClassObj(const SceneDataGUID& guid);
		virtual ~SceneDataClassObj();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataClassObj*					SceneDataClassObjPtr;
	typedef std::vector<SceneDataClassObjPtr>	SceneDataClassObjArray;
	
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataObjWithMatrix
	class SceneDataObjWithMatrix : public SceneDataObj
	{
		friend SceneDataGroupObj;
		friend SceneDataLayerObj; // To Acceses Next Object //
	public:
		SceneDataObjWithMatrix(const SceneDataGUID& guid);
		virtual ~SceneDataObjWithMatrix();
		
		
		
	private:
		VWTransformMatrix			fMatrix;
		SceneDataGroupObj*			fInContainer;
		SceneDataObjWithMatrix*		fNextObj;
		
		SceneDataClassObjPtr		fClass;
		TXString					fUnresolvedClass;
		
		// Geometry stuff
		SceneDataGeometryObjArray	fGeometries;
		
		
	public:
		void						GetTransformMatric(VWTransformMatrix& matrix) const;
		void						SetTransformMatrix(const VWTransformMatrix& matrix);
		
		SceneDataClassObjPtr		GetClass() const;
		void						SetClass(SceneDataClassObjPtr clas);
		const TXString&				GetUnresolvedClass() const;
		
		SceneDataGroupObj*			GetContainer() const;
		SceneDataObjWithMatrix*		GetNextObject() const;
		
		void								AddGeometryObj(SceneDataGeoInstanceObjPtr object);
		const SceneDataGeometryObjArray&	GetGeometryArr() const;
		
	protected:
		void						ReadMatrixNodeValue(const IXMLFileNodePtr& pNode, VWPoint3D& inOutPoint);
		virtual	void				OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void				OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataObjWithMatrix*					SceneDataObjWithMatrixPtr;
	typedef std::vector<SceneDataObjWithMatrixPtr>	SceneDataObjWithMatrixArray;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataObjWithMatrix
	class SceneDataGeoInstanceObj : public SceneDataObjWithMatrix
	{
	public:
		SceneDataGeoInstanceObj(const SceneDataGUID& guid, bool isSymbol);
		virtual ~SceneDataGeoInstanceObj();
		
	private:
		bool fIsSymbol;
		
	public:
		bool IsSymDef() const;


		
	};
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataGeometryObj
	class SceneDataGeometryObj : public SceneDataGeoInstanceObj
	{
		
	public:
		SceneDataGeometryObj();
		~SceneDataGeometryObj();
		
		
		
	private:
		VWTransformMatrix		fMatrix;
		TXString				fFileName;
		TXString				fFileFullPath;
		
	public:
		void			GetTransformMatrix(VWTransformMatrix& matrix) const;
		void			SetTransformMatrix(const VWTransformMatrix& matrix);
		const TXString&	GetFileName() const;
		void			SetFileName(const TXString& fileName);
		const TXString& GetFileFullPath(SceneDataExchange* exchange);
		
	public:
		virtual ESceneDataObjectType	GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataGeometryObj*					SceneDataGeometryObjPtr;
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataGroupObj
	class SceneDataGroupObj : public SceneDataObjWithMatrix
	{
		
	public:
		SceneDataGroupObj(const SceneDataGUID& guid);
		virtual ~SceneDataGroupObj();
		
		
		
	private:
		SceneDataObjWithMatrixArray	fChildObjs;
		
	public:
		const SceneDataObjWithMatrixArray&	GetChildArray() const;
		bool								AddObject(SceneDataObjWithMatrixPtr obj);
		
		virtual ESceneDataObjectType	GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataGroupObj* SceneDataGroupObjPtr;
	
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataObjWithMatrix
	class SceneDataLayerObj : public SceneDataGroupObj
	{
		
	public:
		SceneDataLayerObj(const SceneDataGUID& guid);
		virtual ~SceneDataLayerObj();
		
	public:
		void SetNextLayer(SceneDataLayerObj* nextLayer);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
	};
	typedef SceneDataLayerObj* SceneDataLayerObjPtr;
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataObjWithMatrix
	class SceneDataFocusPointObj : public SceneDataObjWithMatrix
	{
		
	public:
		SceneDataFocusPointObj(const SceneDataGUID& guid);
		virtual ~SceneDataFocusPointObj();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		
	};
	typedef SceneDataFocusPointObj* SceneDataFocusPointObjPtr;
	typedef std::vector<SceneDataFocusPointObjPtr>	SceneDataFocusPointObjArray;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataFixtureObj
	struct SceneDataDmxAdress
	{
		SceneDataDmxAdress(size_t universe, size_t adress, size_t breakId);
		SceneDataDmxAdress(size_t absuluteAdress, size_t breakId);
		
		size_t	fAbsuluteAdress;
		size_t	fBreak;
		
		size_t	GetAdress() const;
		size_t	GetUniverse() const;
	};
	typedef std::vector<SceneDataDmxAdress>	SceneDataAdressArray;
	
	
	class SceneDataFixtureObj : public SceneDataObjWithMatrix
	{
		
	public:
		SceneDataFixtureObj(const SceneDataGUID& guid);
		virtual ~SceneDataFixtureObj();
		
		
		
	private:
		TXString						fGdtfFile;
		TXString						fGdtfDmxMode;
		SceneDataFocusPointObjPtr		fFocusPoint;
		SceneDataPositionObjPtr			fPosition;
		SceneDataAdressArray			fAdresses;
		TXString						fFixtureId;
		Sint32							fUnitNumber;
		CCieColor						fColor;
		Sint8							fFixtureTypeId;
		size_t							fCustomId;
		
		
		// Reading Storage
	private:
		TXString						fUnresolvedFocus;
		TXString						fUnresolvedPosition;
		
	public:
		TXString						GetUnresolvedFocusUUID();
		TXString						GetUnresolvedPositionUUID();
		
	public:
		
		const TXString&					GetGdtfFile();
		const TXString&					GetGdtfDmxMode();
		SceneDataFocusPointObjPtr		GetFocusPoint();
		SceneDataPositionObjPtr			GetPosition();
		const TXString&					GetFixtureId();
		Sint32							GetUnitNumber();
		CCieColor						GetColor();
		Sint8							GetFixtureTypeId();
		size_t							GetCustomId();
		const SceneDataAdressArray&		GetAdressesArray();
		
		void							SetPosition(SceneDataPositionObjPtr ptr);
		void							SetFocusPoint(SceneDataFocusPointObjPtr ptr);
		void							SetGDTFFile(const TXString& path);
		void							SetGdtfDmxMode(const TXString& path);
		void							AddAdress(const SceneDataDmxAdress& adress);
		void							SetColor(const CCieColor& color);
		void							SetFixtureTypeId(const Sint8& value);
		void							SetCustomId(const size_t& value);
		void							SetFixtureId(const TXString& value);
		void							SetUnitNumber(Sint32 value);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataFixtureObj* SceneDataFixtureObjPtr;
	typedef std::vector<SceneDataFixtureObjPtr>	SceneDataFixtureObjArray;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataSceneryObj
	class SceneDataSceneryObj : public SceneDataObjWithMatrix
	{
		
	public:
		SceneDataSceneryObj(const SceneDataGUID& guid);
		virtual ~SceneDataSceneryObj();
		
	private:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
	};
	typedef SceneDataSceneryObj* SceneDataSceneryObjPtr;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataObjWithMatrix
	class SceneDataTrussObj : public SceneDataObjWithMatrix
	{
		
	public:
		SceneDataTrussObj(const SceneDataGUID& guid);
		virtual ~SceneDataTrussObj();
		
	private:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		
	};
	typedef SceneDataTrussObj* SceneDataTrussObjPtr;
	
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataVideoScreneObj
	class SceneDataVideoScreenObj : public SceneDataObjWithMatrix
	{
		
	public:
		SceneDataVideoScreenObj(const SceneDataGUID& guid);
		virtual ~SceneDataVideoScreenObj();

	private:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		
	};
	typedef SceneDataVideoScreenObj* SceneDataVideoScreenObjPtr;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataSymbolObj
	class SceneDataSymbolObj : public SceneDataGeoInstanceObj
	{
		
	public:
		SceneDataSymbolObj(const SceneDataGUID& guid);
		virtual ~SceneDataSymbolObj();
		
	private:
		SceneDataGUID	fSymDef;
		bool			fIsInitialized;
		
	public:
		void				SetSymDef(SceneDataSymDefObjPtr symDef);
		SceneDataGUID		GetSymDef();
		
	private:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
	};
	typedef SceneDataSymbolObj* SceneDataSymbolObjPtr;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataExchange
	class SceneDataExchange
	{
		
	public:
		SceneDataExchange();
		~SceneDataExchange();
		

	private:
		// ---------------------------------------------------------------------------------------------------------------------
		// Database
		SceneDataProviderObjArray	fProviderObjs;
		SceneDataAuxObjArray		fAuxDataObjs;
		SceneDataObjWithMatrixArray	fChildObjs;
		
		
		// Arrays for eachobject type
		SceneDataObjWithMatrixArray fSceneObjects;
		SceneDataFocusPointObjArray fFocusPoints;
		SceneDataPositionObjArray	fPositions;
		SceneDataFixtureObjArray	fFixtures;
		SceneDataClassObjArray		fClasses;
		
		
		// File Operation Handeling
		IFolderIdentifierPtr				fWorkingFolder;
		bool								fUndoStarted;
		TFileIdentifierPtrArray				fGeometryFiles;
		TFileIdentifierPtrArray				fFilesInZip;
		TXStringArray						fRequiredGdtfFiles;
		TFolderIdentifierArray				fGdtfFolderLocations;
		
		
		//
		size_t							fCountExportedGeometryProviders;
		
	public:
		// ---------------------------------------------------------------------------------------------------------------------
		// Database
		SceneDataProviderObjArray&		GetProviderObjects();
		SceneDataAuxObjArray&			GetAuxDataObjects();
		SceneDataObjWithMatrixArray&	GetChildObjects();
		
		SceneDataObjWithMatrixArray&	GetSceneDataObjects();
		
	private:
		SceneDataSymDefObjPtr			GetSymDefByUUID(const SceneDataGUID& guid);

	public:
		// ---------------------------------------------------------------------------------------------------------------------
		// Export
		void						InitializeForExport();
		void						InitializeForImport();
		IFolderIdentifierPtr        GetWorkingFolder() { return fWorkingFolder; }
		
		// ---------------------------------------------------------------------------------------------------------------------
		// Create calls
	public:
		SceneDataProviderObjPtr		CreateDataProviderObject(const TXString& provider, const TXString& version);
		SceneDataPositionObjPtr		CreatePositionObject(const SceneDataGUID& guid, const TXString& name);
		SceneDataSymDefObjPtr		CreateSymDefObject(const SceneDataGUID& guid, const TXString& name);
		SceneDataClassObjPtr		CreateClassObject(const SceneDataGUID& guid, const TXString& name);
		SceneDataSymbolObjPtr 		CreateSymbol(const SceneDataGUID& guid, const VWTransformMatrix& offset, SceneDataSymDefObjPtr symDef);
		
		
		SceneDataLayerObjPtr		CreateLayerObject(	const SceneDataGUID& guid,									const TXString& name);
		SceneDataGroupObjPtr		CreateGroupObject(	const SceneDataGUID& guid, const VWTransformMatrix& offset,							SceneDataGroupObjPtr addToContainer);
		SceneDataFixtureObjPtr		CreateFixture(		const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataSceneryObjPtr		CreateSceneryObject(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataFocusPointObjPtr	CreateFocusPoint(	const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataTrussObjPtr		CreateTruss(		const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataVideoScreenObjPtr	CreateVideoScreen(	const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		
		
		// ---------------------------------------------------------------------------------------------------------------------
		// Read calls
	private:
		SceneDataProviderObjPtr		ReadDataProviderObject(	const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataPositionObjPtr		ReadPositionObject(		const IXMLFileNodePtr& node);
		SceneDataSymDefObjPtr		ReadSymDefObject(		const IXMLFileNodePtr& node);
		SceneDataClassObjPtr		ReadClassObject(		const IXMLFileNodePtr& node);
		
		
		SceneDataLayerObjPtr		ReadLayerObject(		const SceneDataGUID& guid,const IXMLFileNodePtr& node);
		SceneDataGroupObjPtr		ReadGroupObject(		const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataFixtureObjPtr		ReadFixture(			const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataSceneryObjPtr		ReadSceneryObject(		const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataFocusPointObjPtr	ReadFocusPoint(			const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataTrussObjPtr		ReadTruss(				const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataVideoScreenObjPtr	ReadVideoScreen(		const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		
	private:
		
		
		// ---------------------------------------------------------------------------------------------------------------------
		// Write calls
	public:
		bool WriteToFile(const IFileIdentifierPtr&);
		bool AddNeededGdtfFile(const TXString& gdtfName);
		void AddLocationForGdtfFiles(IFolderIdentifierPtr folder);
		
	private:
		
		bool WriteXml(const IFolderIdentifierPtr& folder , IXMLFileIOBufferImpl& outBuffer);
		
		
		
		// ---------------------------------------------------------------------------------------------------------------------
		// Read calls
	public:
		bool ReadFromFile(const IFileIdentifierPtr&);
		
		
	private:
		void ReadFromGeneralSceneDescription(ISceneDataZipBuffer& xmlFile);
		void ProcessLayer(const IXMLFileNodePtr& node);
		void ProcessGroup(const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer, bool createNewContainer);
		
		
		
	};
	

}
