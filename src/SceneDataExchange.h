//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

using namespace VectorworksMVR::Filing;
using namespace VectorworksMVR::VWFC;

#include <unordered_map>

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
    typedef std::unordered_map<TXString, SceneDataSymDefObj*>  TSymDefMap;
	
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
		eSupport					= 9,
		eSymDef						= -1,
		eProviderObj				= -2,
		ePosition					= -3,
		eGeometryObj				= -4,
		eClassObject				= -5,
		eSourceObject				= -6,
		eMappingDefinitionObject	= -7,
		eMappingObject				= -8,
		eCustomCommand				= -9,
		eConnectionObject 			= -10,
		eAlignment					= -11,
		eOverwrite					= -12,
		eSceneDataMVRSpecObj		= -13
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
		virtual void	PrintToFile(IXMLFileNodePtr pContainerNode, SceneDataExchange* exchange);
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
	// SceneDataCustomCommand
	class SceneDataCustomCommand : public SceneDataObj
	{

	public:
		SceneDataCustomCommand();
		SceneDataCustomCommand(const TXString& channelFunction, bool isPercentage, double value);
		virtual ~SceneDataCustomCommand();
		
	private:

		TXString	fChannelFunction;
		bool		fIsPercentage;
		double		fValue;
		
	public:
		virtual const TXString&	GetChannelFunction();
		virtual bool 			IsPercentage();
		virtual double 			GetValue();

		virtual void 			SetChannelFunction(const TXString& channelFunction);
		virtual void			SetIsPercentage(bool isPercentage);
		virtual void 			SetValue(double value);

	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);

	};
	typedef SceneDataCustomCommand*				    SceneDataCustomCommandPtr;
	typedef std::vector<SceneDataCustomCommandPtr>	SceneDataCustomCommandArray;

	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataAlignment
	class SceneDataAlignment : public SceneDataObj
	{

	public:
		SceneDataAlignment();
		SceneDataAlignment(const TXString& beamGeometry, const VWPoint3D& upVector, const VWPoint3D& direction);
		virtual ~SceneDataAlignment();
		
	private:

		TXString	fBeamGeometry;
		VWPoint3D	fUpVector;
		VWPoint3D	fDirection;
		
	public:
		virtual const TXString&		GetBeamGeometry();
		virtual const VWPoint3D&	GetUpVector();
		virtual const VWPoint3D&	GetDirection();

		virtual void 			SetBeamGeometry(const TXString& beamGeometry);
		virtual void			SetUpVector(double x, double y, double z);
		virtual void 			SetDirection(double x, double y, double z);

	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);

	};
	typedef SceneDataAlignment*				    SceneDataAlignmentPtr;
	typedef std::vector<SceneDataAlignmentPtr>	SceneDataAlignmentArray;

	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataOverwrite
	class SceneDataOverwrite : public SceneDataObj
	{

	public:
		SceneDataOverwrite();
		SceneDataOverwrite(const TXString& universal, const TXString& target);
		virtual ~SceneDataOverwrite();
		
	private:

		TXString	fUniversal;
		TXString	fTarget;
		
	public:
		virtual const TXString&	GetUniversal();
		virtual const TXString&	GetTarget();

		virtual void SetUniversal(const TXString& universal);
		virtual void SetTarget(const TXString& target);

	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);

	};
	typedef SceneDataOverwrite*				    SceneDataOverwritePtr;
	typedef std::vector<SceneDataOverwritePtr>	SceneDataOverwriteArray;
	
	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataConnectionObj
	class SceneDataConnectionObj : public SceneDataObj
	{

	public:
		SceneDataConnectionObj();
		SceneDataConnectionObj(const TXString& own, const TXString& other, const TXString& toObject);
		SceneDataConnectionObj(const TXString& own, const TXString& other, const SceneDataGUID& toObject);
		
		virtual ~SceneDataConnectionObj();
		
	private:

		TXString 		fOwn;
		TXString 		fOther;
		SceneDataGUID	fToObject;		

	public:
		virtual SceneDataGUID&	GetToObject();
		virtual TXString&		GetOwn();
		virtual TXString&		GetOther();

		
		virtual void 			SetToObject(SceneDataGUID uuid);
		virtual void			SetOwn(TXString& own);
		virtual void			SetOther(TXString& other);

	protected:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);

	};
	typedef SceneDataConnectionObj*				SceneDataConnectionObjPtr;
	typedef std::vector<SceneDataConnectionObjPtr>	SceneDataConnectionObjArray;
	
	
	
	
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

		SceneDataCustomCommandArray fCustomCommands;
		SceneDataAlignmentArray 	fAlignments;
		SceneDataOverwriteArray 	fOverwrites;
		
		SceneDataConnectionObjArray fConnections;
		
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

		SceneDataCustomCommandPtr			AddCustomCommand(const TXString& channelFunction, bool isPercentage, double value);
		const SceneDataCustomCommandArray&	GetCustomCommandArray() const;

		SceneDataAlignmentPtr			AddAlignment(const TXString& beamGeometry, const VWPoint3D& upVector, const VWPoint3D& direction);
		const SceneDataAlignmentArray&	GetAlignmentArray() const;

		SceneDataOverwritePtr			AddOverwrite(const TXString& universal, const TXString& target);
		const SceneDataOverwriteArray&	GetOverwriteArray() const;
		
		SceneDataConnectionObjPtr			AddConnectionObj(const TXString& own, const TXString& other, const SceneDataGUID toObject);
		const SceneDataConnectionObjArray&	GetConnectionArr() const;
		

	protected:
		void						ReadMatrixNodeValue(const IXMLFileNodePtr& pNode, VWPoint3D& inOutPoint);
		virtual	void				OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void				OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataObjWithMatrix*					SceneDataObjWithMatrixPtr;
	typedef std::vector<SceneDataObjWithMatrixPtr>	SceneDataObjWithMatrixArray;
	
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
		virtual void	                PrintToFile(IXMLFileNodePtr pContainerNode, SceneDataExchange* exchange);
	protected:
		virtual	TXString				GetNodeName();		
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		
	};
	typedef SceneDataGroupObj* SceneDataGroupObjPtr;	
    
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
	// SceneDataGDTFSpecObj
	class SceneDataGDTFSpecObj : public SceneDataGroupObj
	{
	public:
		SceneDataGDTFSpecObj(const SceneDataGUID& guid);
		~SceneDataGDTFSpecObj();
		virtual ESceneDataObjectType	GetObjectType();

		
		const TXString&				GetGdtfFile() const;
		void						SetGDTFFile(const TXString& path);
		
		const TXString&				GetGdtfDmxMode() const;
		void						SetGdtfDmxMode(const TXString& path);
		
	protected:
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode, SceneDataExchange* exchange);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode, SceneDataExchange* exchange);

	private:
		TXString					fGdtfFile;
		TXString					fGdtfDmxMode;
	};

	typedef SceneDataGDTFSpecObj*					SceneDataGDTFSpecObjPtr;

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
	class SceneDataFocusPointObj : public SceneDataGroupObj
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
	
	
	class SceneDataFixtureObj : public SceneDataGDTFSpecObj
	{
		
	public:
		SceneDataFixtureObj(const SceneDataGUID& guid);
		virtual ~SceneDataFixtureObj();
		
		
		
	private:
		TXString						fFunction;
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
		
		const TXString&					GetFunction();
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
		
		void							SetFunction(const TXString& str);
		void							SetPosition(SceneDataPositionObjPtr ptr);
		void							SetFocusPoint(SceneDataFocusPointObjPtr ptr);
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
	class SceneDataSceneryObj : public SceneDataGDTFSpecObj
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
	class SceneDataTrussObj : public SceneDataGDTFSpecObj
	{
		
	public:
		SceneDataTrussObj(const SceneDataGUID& guid);
		virtual ~SceneDataTrussObj();
		
	private:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		
	};
	typedef SceneDataTrussObj* SceneDataTrussObjPtr;
	
	
	class SceneDataSupportObj : public SceneDataGDTFSpecObj
	{
		
	public:
		SceneDataSupportObj(const SceneDataGUID& guid);
		virtual ~SceneDataSupportObj();
		
	private:
		virtual	TXString				GetNodeName();
		virtual ESceneDataObjectType	GetObjectType();
		
	};
	typedef SceneDataSupportObj* SceneDataSupportObjPtr;
	

	// ----------------------------------------------------------------------------------------------------------------------------------
	// SceneDataVideoScreenObj
	class SceneDataVideoScreenObj : public SceneDataGDTFSpecObj
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
	class SceneDataProjectorObj : public SceneDataGDTFSpecObj
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
        TFileIdentifierPtrArray				f3DSLow_FilesToAdd;
        TFileIdentifierPtrArray				f3DSHigh_FilesToAdd;
        TFileIdentifierPtrArray				fSVG_FilesToAdd;
        TFileIdentifierPtrArray				fSVGSide_FilesToAdd;
        TFileIdentifierPtrArray				fSVGFront_FilesToAdd;
		TFileIdentifierPtrArray				fGLTF_FilesToAdd;
		TFileIdentifierPtrArray				fGLTFLow_FilesToAdd;
		TFileIdentifierPtrArray				fGLTFHigh_FilesToAdd;
        TFileIdentifierPtrArray				fWheel_Image_FilesToAdd;
        TFileIdentifierPtrArray				fFixtureResources_FilesToAdd;
		
		std::vector<std::pair<TXString, ISceneDataZipBuffer*> > fBuffersToAdd;
        //
		TFileIdentifierPtrArray				fFilesInZip;
		TXStringArray						fRequiredGdtfFiles;
		TFolderIdentifierArray				fGdtfFolderLocations;
		
		// Resolve map
		TSymDefMap fSymDefMap;
		
		//
		size_t							fCountExportedGeometryProviders;
		TXString						fProvider;
		TXString						fProviderVersion;

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
		SceneDataGroupObjPtr		CreateGroupObject(	const SceneDataGUID& guid, const VWTransformMatrix& offset,	const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataFixtureObjPtr		CreateFixture(		const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataSceneryObjPtr		CreateSceneryObject(const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataFocusPointObjPtr	CreateFocusPoint(	const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataTrussObjPtr		CreateTruss(		const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
		SceneDataSupportObjPtr		CreateSupport(		const SceneDataGUID& guid, const VWTransformMatrix& offset, const TXString& name,	SceneDataGroupObjPtr addToContainer);
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
		SceneDataSupportObjPtr		ReadSupport(			const SceneDataGUID& guid,const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
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
		void AddProviderAndProviderVersion(const TXString& provider, const TXString& providerVersion );

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
        void ReadChildObjs(const IXMLFileNodePtr & node, SceneDataGroupObjPtr addToContainer);
		SceneDataGroupObjPtr ProcessGroup(const IXMLFileNodePtr& node, SceneDataGroupObjPtr addToContainer);
		
		
		
	};
	

}
