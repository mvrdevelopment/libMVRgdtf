//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

using namespace VectorworksMVR::Filing;
using namespace VectorworksMVR::VWFC;

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
    class SceneDataSymDefObj;

	typedef SceneDataGeoInstanceObj*				    SceneDataGeoInstanceObjPtr;
	typedef std::vector<SceneDataGeoInstanceObjPtr>	    SceneDataGeometryObjArray;
	typedef std::vector<IFileIdentifierPtr>			    TFileIdentifierPtrArray;
	typedef std::vector<IFolderIdentifierPtr>		    TFolderIdentifierArray;
    typedef std::map<TXString, SceneDataSymDefObj*>     TSymDefMap;
	
	enum ESceneDataGUIDType : short
	{
		ePlaceHolder	= 0,
		eNormal			= 1,
		eNoGuid			= 2,
	};
	
	enum ESceneDataObjectType : short
	{
		eFixture					= 0,
		eLayer						= 1,
		eGroup						= 2,
		eSymbol						= 3,
		eSceneObject				= 4,
		eFocusPoint					= 5,
		eTruss						= 6,
		eVideoScreen				= 7,
		eProjector					= 8,
		eSymDef						= -1,
		eProviderObj				= -2,
		ePosition					= -3,
		eGeometryObj				= -4,
		eClassObject				= -5,
		eSourceObject				= -6,
		eMappingDefinitionObject	= -7,
		eMappingObject				= -8,
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
		Tools::VWUUID		_uuid;
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
		SceneDataProviderObj();
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
		TXString&		GetKeyAt(size_t at);
		TXString&		GetValueAt(size_t at);


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
	// SceneDataClassObj
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
	// SceneDataSourceObj
	class SceneDataSourceObj : public SceneDataObj
	{
		
	public:
		SceneDataSourceObj();
		SceneDataSourceObj(const TXString& value, const TXString& linkedGeometry, GdtfDefines::ESourceType);
		virtual ~SceneDataSourceObj();

	private:
		TXString 	fValue;
		TXString 	fLinkedGeometry;
		GdtfDefines::ESourceType fType;
		
	public:
		virtual const TXString& 	GetValue();
		virtual const TXString& 	GetLinkedGeometry();
		virtual ESourceType			GetType();

		virtual void 		SetValue(TXString value);
		virtual void 		SetLinkedGeometry(TXString linkedGeometry);
		virtual void		SetType(GdtfDefines::ESourceType);

	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();

		virtual	void		OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void		OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataSourceObj* SceneDataSourceObjPtr;
	typedef std::vector<SceneDataSourceObjPtr>	SceneDataSourceObjArray;

	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataMappingDefinitionObj
	class SceneDataMappingDefinitionObj : public SceneDataAuxObj
	{

	public:
		SceneDataMappingDefinitionObj(const SceneDataGUID& guid);
		SceneDataMappingDefinitionObj(const SceneDataGUID& guid, Uint32 sizeX, Uint32 sizeY, SceneDataSourceObjPtr source);
		virtual ~SceneDataMappingDefinitionObj();
		
	private:
		Uint32					fSizeX;
		Uint32					fSizeY;
		SceneDataSourceObjPtr 	fSource;
		EScaleHandlingType		fScaleHandling;
		
	public:
		virtual Uint32 					GetSizeX();
		virtual Uint32 					GetSizeY();
		virtual SceneDataSourceObjPtr	GetSource();
		virtual EScaleHandlingType		GetScaleHandling();

		virtual void 	SetSizeX(Uint32 sizeX);
		virtual void 	SetSizeY(Uint32 sizeY);
		virtual void	SetSource(const TXString& value, const TXString& linkedGeometry, GdtfDefines::ESourceType);
		virtual void	SetScaleHandling(GdtfDefines::EScaleHandlingType scaleHandling);

	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);

	};
	typedef SceneDataMappingDefinitionObj*					SceneDataMappingDefinitionObjPtr;
	typedef std::vector<SceneDataMappingDefinitionObjPtr>	SceneDataMappingDefinitionObjArray;

	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataMappingObj
	class SceneDataMappingObj : public SceneDataObj
	{

	public:
		SceneDataMappingObj();
		SceneDataMappingObj(const SceneDataGUID& linkedDefUuid);
		virtual ~SceneDataMappingObj();
		
	private:

		SceneDataGUID	fLinkedDefUuid;
		Uint32			fUx;
		Uint32			fUy;
		Uint32			fOx;
		Uint32			fOy;
		double			fRz;
		
	public:
		virtual SceneDataGUID	GetLinkedDefUuid();
		virtual Uint32 			GetUx();
		virtual Uint32 			GetUy();
		virtual Uint32 			GetOx();
		virtual Uint32 			GetOy();
		virtual double 			GetRz();

		virtual void			SetLinkedDefUuid(const SceneDataGUID& linkedDefUuid);
		virtual void 			SetUx(Uint32 value);
		virtual void 			SetUy(Uint32 value);
		virtual void 			SetOx(Uint32 value);
		virtual void 			SetOy(Uint32 value);
		virtual void 			SetRz(double value);

	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);

	};
	typedef SceneDataMappingObj*				SceneDataMappingObjPtr;
	typedef std::vector<SceneDataMappingObjPtr>	SceneDataMappingObjArray;
	
	
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
		TXString				fFileName;
		TXString				fFileFullPath;
		
	public:
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
	// SceneDataLayerObj
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
	// SceneDataFocusPointObj
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
		TXString 						fGobo;
		double							fGoboRotation;
		SceneDataFocusPointObjPtr		fFocusPoint;
		SceneDataPositionObjPtr			fPosition;
		SceneDataAdressArray			fAdresses;
		TXString						fFixtureId;
		Sint32							fUnitNumber;
		CCieColor						fColor;
		Sint8							fFixtureTypeId;
		size_t							fCustomId;
		bool							fCastShadow;
		SceneDataMappingObjArray		fMappings;
		
		
		// Reading Storage
	private:
		TXString						fUnresolvedFocus;
		TXString						fUnresolvedPosition;
		TXString						fGoboFullPath;
		
	public:
		TXString						GetUnresolvedFocusUUID();
		TXString						GetUnresolvedPositionUUID();
		const TXString&					GetGoboFullPath(SceneDataExchange* exchange);
		
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
		const TXString&					GetGobo();
		double							GetGoboRotation();
		bool							GetCastShadow();
		SceneDataMappingObjArray		GetMappingsArray();
		
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
		void							SetGobo(const TXString& value);
		void							SetGoboRotation(double value);
		void							SetCastShadow(bool value);
		void							AddMapping(SceneDataGUID mappingDefinitionUuid);
		
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
	// SceneDataVideoScreenObj
	class SceneDataVideoScreenObj : public SceneDataObjWithMatrix
	{
		
	public:
		SceneDataVideoScreenObj(const SceneDataGUID& guid);
		virtual ~SceneDataVideoScreenObj();
	
	private:
		SceneDataSourceObjPtr	fSource;

	public:
		virtual SceneDataSourceObjPtr 	GetVideoSource();
		virtual void 					SetVideoSource(const TXString& value, const TXString& linkedGeometry, GdtfDefines::ESourceType);

	private:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataVideoScreenObj* SceneDataVideoScreenObjPtr;

	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataProjectorObj
	class SceneDataProjectorObj : public SceneDataObjWithMatrix
	{
		
	public:
		SceneDataProjectorObj(const SceneDataGUID& guid);
		virtual ~SceneDataProjectorObj();
	
	private:
		SceneDataSourceObjPtr 	fSource;
		EScaleHandlingType		fScaleHandling;

	public:
		virtual SceneDataSourceObjPtr 	GetVideoSource();
		virtual EScaleHandlingType		GetScaleHandling();

		virtual void 					SetVideoSource(const TXString& value, const TXString& linkedGeometry, GdtfDefines::ESourceType);
		virtual void					SetScaleHandling(GdtfDefines::EScaleHandlingType scaleHandling);

	private:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataProjectorObj* SceneDataProjectorObjPtr;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataSymbolObj
	class SceneDataSymbolObj : public SceneDataGeoInstanceObj
	{
		
	public:
		SceneDataSymbolObj(const SceneDataGUID& guid);
		virtual ~SceneDataSymbolObj();
		
	private:
		SceneDataSymDefObjPtr	fSymDef;
		TXString				fUnresolvedSymDef;		
		
	public:
		void					SetSymDef(SceneDataSymDefObjPtr symDef);
		SceneDataSymDefObjPtr	GetSymDef();
		const TXString&			GetUnresolvedSymDef() const;

		
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
		//
        TFileIdentifierPtrArray				f3DS_FilesToAdd;
        TFileIdentifierPtrArray				fSVG_FilesToAdd;
		TFileIdentifierPtrArray				fGLTF_FilesToAdd;
        TFileIdentifierPtrArray				fWheel_Image_FilesToAdd;
        TFileIdentifierPtrArray				fFixtureResources_FilesToAdd;
		
		std::vector<std::pair<TXString, ISceneDataZipBuffer*>> fBuffersToAdd;
        //
		TFileIdentifierPtrArray				fFilesInZip;
		TXStringArray						fRequiredGdtfFiles;
		TFolderIdentifierArray				fGdtfFolderLocations;
		
		// Resolve map
		TSymDefMap fSymDefMap;
		
		//
		size_t							fCountExportedGeometryProviders;

		//Duplicated Uuids flag
		bool fDuplicatedUuids;
		
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
		SceneDataProviderObjPtr				CreateDataProviderObject(const TXString& provider, const TXString& version);
		SceneDataPositionObjPtr				CreatePositionObject(const SceneDataGUID& guid, const TXString& name);
		SceneDataSymDefObjPtr				CreateSymDefObject(const SceneDataGUID& guid, const TXString& name);
		SceneDataClassObjPtr				CreateClassObject(const SceneDataGUID& guid, const TXString& name);
		SceneDataSymbolObjPtr 				CreateSymbol(const SceneDataGUID& guid, const VWTransformMatrix& offset, SceneDataSymDefObjPtr symDef);
		SceneDataMappingDefinitionObjPtr	CreateMappingDefinitionObject(const SceneDataGUID& guid, const TXString& name);
		
		
		SceneDataLayerObjPtr		CreateLayerObject(	const SceneDataGUID& guid,									const TXString& name);
		SceneDataGroupObjPtr		CreateGroupObject(	const SceneDataGUID& guid, const VWTransformMatrix& offset,							SceneDataGroupObjPtr addToContainer);
		SceneDataFixtureObjPtr		CreateFixture(		const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataSceneryObjPtr		CreateSceneryObject(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataFocusPointObjPtr	CreateFocusPoint(	const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataTrussObjPtr		CreateTruss(		const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataVideoScreenObjPtr	CreateVideoScreen(	const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataProjectorObjPtr	CreateProjector(	const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		
		
		// ---------------------------------------------------------------------------------------------------------------------
		// Read calls
	private:
		SceneDataProviderObjPtr				ReadDataProviderObject(		const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataPositionObjPtr				ReadPositionObject(			const IXMLFileNodePtr& node);
		SceneDataSymDefObjPtr				ReadSymDefObject(			const IXMLFileNodePtr& node);
		SceneDataClassObjPtr				ReadClassObject(			const IXMLFileNodePtr& node);
		SceneDataMappingDefinitionObjPtr	ReadMappingDefinitionObject(const IXMLFileNodePtr& node);
		
		
		SceneDataLayerObjPtr		ReadLayerObject(		const SceneDataGUID& guid,const IXMLFileNodePtr& node);
		SceneDataGroupObjPtr		ReadGroupObject(		const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataFixtureObjPtr		ReadFixture(			const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataSceneryObjPtr		ReadSceneryObject(		const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataFocusPointObjPtr	ReadFocusPoint(			const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataTrussObjPtr		ReadTruss(				const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataVideoScreenObjPtr	ReadVideoScreen(		const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		SceneDataProjectorObjPtr	ReadProjector(			const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		
	private:
		
		
		// ---------------------------------------------------------------------------------------------------------------------
		// Write calls
	public:
		bool WriteToFile(const IFileIdentifierPtr&);
		bool AddNeededGdtfFile(const TXString& gdtfName);
        void AddFileToZip(const IFileIdentifierPtr& file, ERessourceType resType);
		void AddBufferToZip(const TXString& fileName, ISceneDataZipBuffer* buffer);
		void AddLocationForGdtfFiles(IFolderIdentifierPtr folder);
		
	private:
		
		bool WriteXml(const IFolderIdentifierPtr& folder , IXMLFileIOBufferImpl& outBuffer);
		
		
		
		// ---------------------------------------------------------------------------------------------------------------------
		// Read calls
	public:
		bool 	ReadFromFile(const IFileIdentifierPtr&);

		size_t 	GetAttachedFileCount();
		bool	GetAttachedFileCountAt(size_t at, IFileIdentifierPtr& outFile);

		bool	GetDuplicatedUuids() const;		
		
	private:
		void ReadFromGeneralSceneDescription(ISceneDataZipBuffer& xmlFile);
		void ProcessLayer(const IXMLFileNodePtr& node);
		void ProcessGroup(const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer, bool createNewContainer);
		
		
		
	};
	

}
