#pragma once


// Type defs
#ifndef _GS_TYPES_
	typedef int8_t		Sint8;
	typedef	int16_t		Sint16;
	typedef	int32_t		Sint32;
	typedef int64_t		Sint64;
	typedef uint8_t		Uint8;
	typedef	uint16_t	Uint16;
	typedef	uint32_t	Uint32;
	typedef uint64_t	Uint64;
#endif

typedef  const char * MvrString;

#include "GDTFPrefix.h"
namespace VectorworksMVR
{
	//-------------------------------------------------------------------------------------------------------------
	struct STransformMatrix
	{
		double ux,uy,uz;
		double vx,vy,vz;
		double wx,wy,wz;
		double ox,oy,oz;
	};

	struct SVector3
	{
		double x, y, z;
	};

    struct STime
	{
		Uint16	fYear;
		Uint16  fMonth;
		Uint16  fDay;
		Uint16  fHour;
		Uint16  fMinute;
		Uint16  fSecond;
	};
	
	struct SDmxAdress
	{
		size_t fAbsuluteAdress;
		size_t fBreakId;
	};
	
	struct CieColor
	{
		double fx;
		double fy;
		double f_Y;
	};

	struct RGBColor
	{
		Sint32 r, g, b;
	};
	
	struct MvrUUID
	{
		MvrUUID()
		{
			a = b = c =d = 0;
		}
		MvrUUID(Uint32 a,Uint32 b,Uint32 c,Uint32 d) { this->a = a; this->b = b; this->c = c; this->d = d;}
		Uint32 a, b, c, d;

        bool operator== (const MvrUUID& uuid) const 
        {
            return ((this->a == uuid.a) &&
                (this->b == uuid.b) &&
                (this->c == uuid.c) &&
                (this->d == uuid.d));                          
        }
	};
	
	//-------------------------------------------------------------------------------------------------------------
	// Predefines for classes
	class ISymDef;
	class IMediaRessourceVectorInterface;
	class IGdtfFixture;
	class IGdtfAttribute;
	class IGdtfGeometry;
    class IGdtfPhysicalEmitter;
    class IGdtfMacroDMXStep;
    class IGdtfMacroDMXValue;
    class IGdtfMacroVisualStep;
    class IGdtfMacroVisualValue;
    class IGdtf_FTRDM;
    class IGdtfArtNet;
    class IGdtfSACN;
	class IGdtfFeatureGroup;
	class IGdtfDmxChannel;
    class IGdtfDmxLogicalChannel;
    class IGdtfXmlParsingError;
    class IGdtfSoftwareVersionID;
    class IGdtfDMXProfile;
    class IGdtfCRIGroup;
    class IGdtfColorSpace;
    class IGdtfGamut;
    class IGdtfFilter;
    class IGdtfDmxMode;
	class IGdtfMacroDMX;
	class IGdtfMacroVisual;
	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE ISceneDataProvider : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		AddKeyValue(MvrString key, MvrString value) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetKeyValueCount(size_t& outVal) = 0;
		virtual MvrString VCOM_CALLTYPE		GetKeyAt(size_t at) = 0;
		virtual MvrString VCOM_CALLTYPE		GetValueAt(size_t at) = 0;
        virtual MvrString VCOM_CALLTYPE		GetProviderName() = 0;
        virtual MvrString VCOM_CALLTYPE		GetVersion() = 0;

	};
	typedef VCOMPtr<ISceneDataProvider>	ISceneDataProviderPtr;
	
	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IPosition : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid) = 0;
	};
	typedef VCOMPtr<IPosition>	IPositionPtr;
	
	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IClass : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid) = 0;
	};
	typedef VCOMPtr<IClass>	IClassPtr;
	
	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IGeometryReference : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		GetIsSymbol(bool& isSymbol) = 0;
		virtual MvrString VCOM_CALLTYPE		GetFileForGeometry() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetSymDef(ISymDef** outSymDef) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetTransfromMatrix(STransformMatrix& outName) = 0;
	};
	typedef VCOMPtr<IGeometryReference>	IGeometryReferencePtr;
	


	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE ISymDef : public IVWUnknown
	{
	public:
        virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid) = 0;
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGeometryReference** outGeometryRef) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		AddGeometry(const STransformMatrix& geometry, MvrString fileName) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddSymbol(const MvrUUID& guid, const STransformMatrix& geometry, ISymDef* symDef) = 0;
		
	};
	typedef VCOMPtr<ISymDef>	ISymDefPtr;

	//-------------------------------------------------------------------------------------------------------------


	class DYNAMIC_ATTRIBUTE ISource : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetValue() = 0;
		virtual MvrString VCOM_CALLTYPE		GetLinkedGeometry() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetType(GdtfDefines::ESourceType& sourceType) = 0;

		virtual VCOMError VCOM_CALLTYPE		SetValue(MvrString value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetLinkedGeometry(MvrString linkedGeometry) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetType(GdtfDefines::ESourceType type) = 0;
	};
	typedef VCOMPtr<ISource> ISourcePtr;

	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IMappingDefinition : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& guid) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetSizeX(Uint32& sizeX) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetSizeY(Uint32& sizeY) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetSource(ISource** outSource) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetScaleHandling(GdtfDefines::EScaleHandlingType& scaleHandling) = 0;

		virtual VCOMError VCOM_CALLTYPE		SetSizeX(Uint32 sizeX) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetSizeY(Uint32 sizeY) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetSource(MvrString value, MvrString linkedGeometry, GdtfDefines::ESourceType) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetScaleHandling(GdtfDefines::EScaleHandlingType scaleHandling) = 0;
		
	};
	typedef VCOMPtr<IMappingDefinition>	IMappingDefinitionPtr;

	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IMapping : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		GetLinkedDefUuid(MvrUUID& linkedDefUuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetUx(Uint32& outValue) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetUy(Uint32& outValue) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetOx(Uint32& outValue) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetOy(Uint32& outValue) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetRz(double& outValue) = 0;

		virtual VCOMError VCOM_CALLTYPE		SetLinkedDefUuid(MvrUUID linkedDefUuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetUx(Uint32 value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetUy(Uint32 value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetOx(Uint32 value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetOy(Uint32 value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetRz(double value) = 0;
		
	};
	typedef VCOMPtr<IMapping>	IMappingPtr;

	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IConnection : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		GetToObject(MvrUUID& objUUID) = 0;
		virtual MvrString VCOM_CALLTYPE		GetOwn() = 0;
		virtual MvrString VCOM_CALLTYPE		GetOther() = 0;

		virtual VCOMError VCOM_CALLTYPE		SetToObject(MvrUUID objUUID) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetOwn(MvrString value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetOther(MvrString value) = 0;
		
	};
	typedef VCOMPtr<IConnection>	IConnectionPtr;

	//-------------------------------------------------------------------------------------------------------------

	class DYNAMIC_ATTRIBUTE ICustomCommand : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetChannelFunction() = 0;
		virtual VCOMError VCOM_CALLTYPE		IsPercentage(bool& isPercentage) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetValue(double& outValue) = 0;

		virtual VCOMError VCOM_CALLTYPE		SetChannelFunction(const MvrString& channelFunction) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetIsPercentage(bool isPercentage) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetValue(double value) = 0;
		
	};
	typedef VCOMPtr<ICustomCommand>	ICustomCommandPtr;

	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IAlignment : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetBeamGeometry() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetUpVector(SVector3& upVector) = 0;
		virtual VCOMError VCOM_CALLTYPE	    GetDirection(SVector3& direction) = 0;

		virtual VCOMError VCOM_CALLTYPE		SetBeamGeometry(const MvrString& beamGeometry) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetUpVector(double x, double y, double z) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetDirection(double x, double y, double z) = 0;
		
	};
	typedef VCOMPtr<IAlignment>	IAlignmentPtr;

	//-------------------------------------------------------------------------------------------------------------
	class DYNAMIC_ATTRIBUTE IOverwrite : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE		GetUniversal() = 0;
		virtual MvrString VCOM_CALLTYPE		GetTarget() = 0;

		virtual VCOMError VCOM_CALLTYPE		SetUniversal(const MvrString& universal) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetTarget(const MvrString& target) = 0;
		
	};
	typedef VCOMPtr<IOverwrite>	IOverwritePtr;
	
	//-------------------------------------------------------------------------------------------------------------
	enum class ESceneObjType
	{
		Layer,
		Group,
		SceneObj,
		FocusPoint,
		Truss,
		VideoScreen,
		Fixture,
		Projector,
		Support,
	};
	
	class DYNAMIC_ATTRIBUTE ISceneObj : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		GetType(ESceneObjType& outType) = 0;
		
		virtual MvrString VCOM_CALLTYPE		GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGuid(MvrUUID& outGuid) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetTransfromMatrix(STransformMatrix& outName) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGeometryReference** outGeometryRef) = 0;
		
		
		virtual VCOMError VCOM_CALLTYPE		AddGeometry(const STransformMatrix& geometry, MvrString fileName) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddSymbol(const MvrUUID& guid, const STransformMatrix& geometry, ISymDef* symDef) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetClass(IClass** outClass) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetClass(IClass* clas) = 0;
		
		virtual MvrString VCOM_CALLTYPE		GetGdtfName() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGdtfFixture(IGdtfFixture** outFixture) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetGdtfName(MvrString gdtfName) = 0;
		
		virtual MvrString VCOM_CALLTYPE		GetGdtfMode() = 0;
		virtual VCOMError VCOM_CALLTYPE		SetGdtfMode(MvrString gdtfMode) = 0;

		// Fixture
		virtual MvrString VCOM_CALLTYPE		GetFunction() = 0;
		virtual VCOMError VCOM_CALLTYPE		SetFunction(MvrString function) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetFocusPoint(ISceneObj** outFocusPoint) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetPosition(IPosition** outPosition) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAdressCount(size_t& outAdresses) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAdressAt(size_t at, SDmxAdress& adress) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetUnitNumber(Sint32& outUnitNumber) = 0;
		virtual MvrString VCOM_CALLTYPE		GetFixtureId() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetColor(CieColor& outColor) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetFixtureTypeId(Sint8& outType) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetCustomId(size_t& outId) = 0;
		virtual MvrString VCOM_CALLTYPE		GetGobo() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetGoboRotation(double& value) = 0;
		virtual MvrString VCOM_CALLTYPE		GetGoboFullPath() = 0;
		virtual VCOMError VCOM_CALLTYPE		GetCastShadow(bool& value) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetMappingCount(size_t& outMappings) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetMappingAt(size_t at, IMapping** outMapping) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		SetFocusPoint(ISceneObj* focusPoint) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetPosition(IPosition* position) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddAdress(const size_t& adresses, const size_t& breakId) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetUnitNumber(const Sint32& unitNumber) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetFixtureId(MvrString fixtureId) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetColor(const CieColor& color) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetFixtureTypeId(const Sint8& type) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCustomId(const size_t& Cid) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetGobo(MvrString gobo) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetGoboRotation(double rotation) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCastShadow(bool castShadow) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddMapping(MvrUUID mapDefUuid) = 0;

		// Video Screen
		virtual VCOMError VCOM_CALLTYPE		SetVideoScreenSource(MvrString value, MvrString linkedGeometry, GdtfDefines::ESourceType) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetVideoScreenSource(ISource** outSource) = 0;

		// Projector
		virtual VCOMError VCOM_CALLTYPE		SetProjectorSource(MvrString value, MvrString linkedGeometry, GdtfDefines::ESourceType) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetProjectorSource(ISource** outSource) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetScaleHandling(GdtfDefines::EScaleHandlingType scaleHandling) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetScaleHandling(GdtfDefines::EScaleHandlingType& outScaleHandling) = 0;	
		virtual VCOMError VCOM_CALLTYPE		GetConnectionCount(size_t& outConnections) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetConnectionAt(size_t at, IConnection** outConnection) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateConnection(MvrString own, MvrString other, MvrUUID ToObject, IConnection** addedObj) = 0;
		// MVR 1.5
		virtual VCOMError VCOM_CALLTYPE		GetCustomCommandCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetCustomCommandAt(size_t at, ICustomCommand** outCustomCommand) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateCustomCommand(MvrString channelFunction, bool isPercentage, double physicalValue, ICustomCommand** outCustomCommand) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetAlignmentCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAlignmentAt(size_t at, IAlignment** outAlignment) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateAlignment(MvrString beamGeometry, const SVector3& upVector, const SVector3& direction, IAlignment** outAlignment) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetOverwriteCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetOverwriteAt(size_t at, IOverwrite** outOverwrite) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateOverwrite(MvrString universal, MvrString target, IOverwrite** outOverwrite) = 0;

	};
	typedef VCOMPtr<ISceneObj>	ISceneObjPtr;
	
	//-------------------------------------------------------------------------------------------------------------
	// Interface to handle Media Ressource Files
	class DYNAMIC_ATTRIBUTE IMediaRessourceVectorInterface : public IVWUnknown
	{
		//----------------------------------------------------------------------------------------
		// methods to write a file
	public:
		// Call this at the start of generating a MVR file
		virtual VCOMError VCOM_CALLTYPE		OpenForWrite(MvrString fullPath) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddGdtfFolderLocation(MvrString fullPathToFolder) = 0;
        virtual VCOMError VCOM_CALLTYPE		AddFileToMvrFile(MvrString fullPath) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddBufferToMvrFile(MvrString filename, char* buffer, size_t length) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddProviderAndProviderVersion( MvrString provider, MvrString providerVersion ) = 0;

		// After this you can generate Aux Objects
		virtual VCOMError VCOM_CALLTYPE		CreateDataProviderObject(		MvrString provider,		MvrString version,	ISceneDataProvider** outSceneDataProvider) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreatePositionObject(	 		const MvrUUID& guid,	MvrString name,		IPosition** outPositionObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateSymDefObject(		 		const MvrUUID& guid,	MvrString name,		ISymDef** outSymDef) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateClassObject(		 		const MvrUUID& guid,	MvrString name,		IClass** outclass) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateMappingDefinitionObject(	const MvrUUID& guid,	MvrString name,		IMappingDefinition** outMapDef) = 0;
		
		// Then you can generate all other objects
		virtual VCOMError VCOM_CALLTYPE		CreateLayerObject(	const MvrUUID& guid,								 MvrString name,								ISceneObj**	outLayerObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateGroupObject(	const MvrUUID& guid, const STransformMatrix& offset,					ISceneObj* addToContainer,	ISceneObj**	outGroupObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateGroupObject(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outGroupObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateFixture(		const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outFixture) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateSceneObject(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outSceneObj) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateFocusPoint(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outFocusPoint) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateVideoScreen(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj** outVideoScreen) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateTruss(		const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outTruss) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateSupport(		const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outSupport) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateProjector(	const MvrUUID& guid, const STransformMatrix& offset, MvrString name,	ISceneObj* addToContainer,	ISceneObj**	outProjector) = 0;

		// Add the end call to write the file to disk
		virtual VCOMError VCOM_CALLTYPE		Close() = 0;
		
		
		//----------------------------------------------------------------------------------------
		// methods to read a file
	public:
		// Call this at the start of generating a MVR file
		virtual VCOMError VCOM_CALLTYPE		OpenForRead(MvrString fullPath) = 0;
		
		// Get data provider objs
		virtual VCOMError VCOM_CALLTYPE		GetDataProviderObjectCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetDataProviderObjectAt(size_t at, ISceneDataProvider** outSceneDataProvider ) = 0;
		
		// Get data position objs
		virtual VCOMError VCOM_CALLTYPE		GetPositionObjectCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetPositionObjectAt(size_t at, IPosition** outPosition ) = 0;
		
		// Get SymDef objs
		virtual VCOMError VCOM_CALLTYPE		GetSymDefCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetSymDefAt(size_t at, ISymDef** outSymDef ) = 0;
		
		// Get Class objs
		virtual VCOMError VCOM_CALLTYPE		GetClassCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetClassAt(size_t at, IClass** outClass ) = 0;

		// Get MappingDefinition objs
		virtual VCOMError VCOM_CALLTYPE		GetMappingDefinitionCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetMappingDefinitionAt(size_t at, IMappingDefinition** outMapDef) = 0;

        // Get File Traversel
        virtual VCOMError VCOM_CALLTYPE		GetAttachedFileCount(size_t& outCount) = 0;
		virtual MvrString VCOM_CALLTYPE		GetAttachedFileCountAt(size_t at ) = 0;

		
		// Traversel call for object tree
		virtual VCOMError VCOM_CALLTYPE		GetFirstLayer(ISceneObj** firstLayer ) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetFirstChild(ISceneObj* container, ISceneObj** outChild) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetNextObject(ISceneObj* object, ISceneObj** outNextObj) = 0;

        // Get Count Scene Object
        virtual VCOMError VCOM_CALLTYPE		GetSceneObjectCount(size_t& countObjects ) = 0;

		// Check for duplicated uuids
		virtual VCOMError VCOM_CALLTYPE		GetDuplicatedUuids(bool& outDuplicated) = 0;
				
	};
	typedef VCOMPtr<IMediaRessourceVectorInterface>	IMediaRessourceVectorInterfacePtr;
	
	// ----------------------------------------------------------------------------------------------------
	const VWIID IID_MediaRessourceVectorInterface = { 0xe64bdd25, 0x865c, 0x4713, {0xaa, 0x5f, 0xfa, 0x76, 0xfd, 0x7a, 0xaa, 0x72}};
    
    
    class DYNAMIC_ATTRIBUTE IGdtfActivationGroup : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfActivationGroup>	IGdtfActivationGroupPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfFeature : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetFeatureGroup(IGdtfFeatureGroup** group) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfFeature>	IGdtfFeaturePtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfFeatureGroup : public IVWUnknown
    {
		public:
		virtual VCOMError VCOM_CALLTYPE     CreateFeature(MvrString name, IGdtfFeature** feature) = 0;


        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual MvrString VCOM_CALLTYPE     GetPrettyName() = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetFeatureCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFeatureAt(size_t at, IGdtfFeature** feature) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		SetPrettyName(MvrString name) = 0;				
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfFeatureGroup>	IGdtfFeatureGroupPtr;

	class DYNAMIC_ATTRIBUTE IGdtfSubPhysicalUnit : public IVWUnknown
    {
		public:
		virtual VCOMError VCOM_CALLTYPE     GetType(GdtfDefines::EGdtfSubPhysicalUnitType& type) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetPhysicalFrom(double& physicalFrom) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetPhysicalTo(double& physicalTo) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetType(GdtfDefines::EGdtfSubPhysicalUnitType type) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalFrom(double physicalFrom) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalTo(double physicalTo) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfSubPhysicalUnit>	IGdtfSubPhysicalUnitPtr;
	
    class DYNAMIC_ATTRIBUTE IGdtfAttribute : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual MvrString VCOM_CALLTYPE     GetPrettyName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetActivationGroup(IGdtfActivationGroup** activationGroup) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFeature(IGdtfFeature** feature) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetMainAttribute(IGdtfAttribute** mainAttrib) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit& unit) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor & col) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetActivationGroup(IGdtfActivationGroup* activationGroup) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetFeature(IGdtfFeature* feature) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetMainAttribute(IGdtfAttribute* mainAttrib) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalUnit(GdtfDefines::EGdtfPhysicalUnit unit) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor & col) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

		// GDTF 1.2
		virtual VCOMError VCOM_CALLTYPE 	GetSubPhysicalUnitCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE 	GetSubPhysicalUnitAt(size_t at, VectorworksMVR::IGdtfSubPhysicalUnit** outSubPhysicalUnit) = 0;
        virtual VCOMError VCOM_CALLTYPE 	CreateSubPhysicalUnit(GdtfDefines::EGdtfSubPhysicalUnitType type, VectorworksMVR::IGdtfSubPhysicalUnit** outSubPhysicalUnit) = 0;
    };
	typedef VCOMPtr<IGdtfAttribute>	IGdtfAttributePtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfWheelSlotPrismFacet : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetTransformMatrix(STransformMatrix& transformMatrix) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor& color) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetTransformMatrix(const STransformMatrix& transformMatrix) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfWheelSlotPrismFacet>	IGdtfWheelSlotPrismFacetPtr;

	class DYNAMIC_ATTRIBUTE IGdtfWheelSlotAnimationSystem : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE     GetP1_X(double& p1_X) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     GetP1_Y(double& p1_Y) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     GetP2_X(double& p2_X) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     GetP2_Y(double& p2_Y) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     GetP3_X(double& p3_X) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     GetP3_Y(double& p3_Y) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     GetRadius(double& radius) 	= 0;

        virtual VCOMError VCOM_CALLTYPE     SetP1_X(double p1_X) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     SetP1_Y(double p1_Y) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     SetP2_X(double p2_X) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     SetP2_Y(double p2_Y) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     SetP3_X(double p3_X) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     SetP3_Y(double p3_Y) 		= 0;
        virtual VCOMError VCOM_CALLTYPE     SetRadius(double radius) 	= 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfWheelSlotAnimationSystem>	IGdtfWheelSlotAnimationSystemPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfWheelSlot : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color) = 0;
        virtual MvrString VCOM_CALLTYPE     GetGobo() = 0;
		virtual MvrString VCOM_CALLTYPE     GetGoboFileFullPath() = 0;
		
        virtual VCOMError VCOM_CALLTYPE		SetName(MvrString name) = 0;				
		virtual VCOMError VCOM_CALLTYPE     SetColor(const CieColor& color) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGobo(MvrString path) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetPrismFacetCount(size_t& outCount) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPrismFacetAt(size_t& at, IGdtfWheelSlotPrismFacet** outFacet) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreatePrismFacet(const STransformMatrix& transformMatrix, IGdtfWheelSlotPrismFacet** outFacet) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

        // 0.3.13
        virtual VCOMError VCOM_CALLTYPE     GetFilter(IGdtfFilter** outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetFilter(IGdtfFilter* val)=0;

		//GDTF 1.1
		virtual VCOMError VCOM_CALLTYPE     GetAnimationSystem(IGdtfWheelSlotAnimationSystem** outAnimationSystem) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateAnimationSystem(double p1_X, double p1_Y, double p2_X, double p2_Y, double p3_X, double p3_Y, double radius, IGdtfWheelSlotAnimationSystem** 	outAnimationSystem) = 0;
    };
	typedef VCOMPtr<IGdtfWheelSlot>	IGdtfWheelSlotPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfWheel : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlotCount(size_t& outCount) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlotAt(size_t at, IGdtfWheelSlot** outPosition) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateWheelSlot(MvrString name, IGdtfWheelSlot** outPosition) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfWheel>	IGdtfWheelPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfModel : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetLength(double& length) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetWidth(double& width) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetHeight(double& height) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPrimitiveType(GdtfDefines::EGdtfModel_PrimitiveType& type) = 0;
        virtual MvrString VCOM_CALLTYPE     GetGeometryFileName() = 0;
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_3DS_FullPath() = 0;
        virtual MvrString VCOM_CALLTYPE     GetGeometryFile_SVG_FullPath() = 0;
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_GLTF_FullPath() = 0;
		
		virtual VCOMError VCOM_CALLTYPE     GetBuffer3DS(void** bufferToCopy, size_t& length) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetBufferSVG(void** bufferToCopy, size_t& length) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetBufferGLTF(void** bufferToCopy, size_t& length) = 0;
                
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetLength(double length) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetWidth(double width) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetHeight(double height) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPrimitiveType(GdtfDefines::EGdtfModel_PrimitiveType type) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGeometryFile(MvrString path) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetBuffer3DS(void* bufferToCopy, size_t length) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetBufferSVG(void* bufferToCopy, size_t length) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetBufferGLTF(void* bufferToCopy, size_t length) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

		// GDTF 1.2
		virtual VCOMError VCOM_CALLTYPE     GetSVGOffsetX(double& svgOffsetX) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSVGOffsetY(double& svgOffsetY) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSVGSideOffsetX(double& svgSideOffsetX) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSVGSideOffsetY(double& svgSideOffsetY) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSVGFrontOffsetX(double& svgFrontOffsetX) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSVGFrontOffsetY(double& svgFrontOffsetY) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetSVGOffsetX(double svgOffsetX) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetSVGOffsetY(double svgOffsetY) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetSVGSideOffsetX(double svgSideOffsetX) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetSVGSideOffsetY(double svgSideOffsetY) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetSVGFrontOffsetX(double svgFrontOffsetX) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetSVGFrontOffsetY(double svgFrontOffsetY) = 0;

		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_3DSLow_FullPath() 	= 0;
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_3DSHigh_FullPath() 	= 0;

		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_GLTFLow_FullPath() 	= 0;
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_GLTFHigh_FullPath() = 0;

		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_SVGSide_FullPath() 	= 0;
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_SVGFront_FullPath() = 0;
	};
	typedef VCOMPtr<IGdtfModel>	IGdtfModelPtr;
	
	class DYNAMIC_ATTRIBUTE IGdtfBreak : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE     GetDmxBreak(Sint32& dmxBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetDmxAddress(GdtfDefines::DMXAddress& dmxAdress) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetDmxBreak(Sint32 dmxBreak) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetDmxAddress(GdtfDefines::DMXAddress dmxAdress) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfBreak>	IGdtfBreakPtr;

	class DYNAMIC_ATTRIBUTE IGdtfLaserProtocol : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfLaserProtocol>	IGdtfLaserProtocolPtr;

	class DYNAMIC_ATTRIBUTE IGdtfPinPatch : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE     GetLinkedWiringObject(IGdtfGeometry** toWiringObject) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetFromPin(size_t& fromPin) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetToPin(size_t& toPin) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetLinkedWiringObject(IGdtfGeometry* toWiringObject) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetFromPin(size_t fromPin) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetToPin(size_t toPin) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfPinPatch>	IGdtfPinPatchPtr;
	
    class DYNAMIC_ATTRIBUTE IGdtfGeometry : public IVWUnknown
    {
		public:
		virtual VCOMError VCOM_CALLTYPE     GetGeometryType(GdtfDefines::EGdtfObjectType& type) = 0;
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetModel(IGdtfModel** model) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetTransformMatrix(STransformMatrix& transformMatrix) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetInternalGeometryCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetInternalGeometryAt(size_t at, IGdtfGeometry** geometry) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateGeometry(GdtfDefines::EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry) = 0;
		
		// Lamp
		virtual VCOMError VCOM_CALLTYPE     GetLampType(GdtfDefines::EGdtfLampType& lampType) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetPowerConsumption(double& powerConsumption) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetLuminousIntensity(double& luminousIntensity) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetColorTemperature(double& colorTemperature) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetBeamAngle(double& beamAngle) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFieldAngle(double& fldAngle) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetBeamRadius(double& radius) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetThrowRatio(double& ratio) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetRectangleRatio(double& ratio) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetBeamType(GdtfDefines::EGdtfBeamType & type) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetColorIndex(Sint32& idx) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetModel(IGdtfModel** model) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetTransformMatrix(STransformMatrix& transformMatrix) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetLampType(GdtfDefines::EGdtfLampType lampType) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPowerConsumption(double powerConsumption) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetLuminousIntensity(double luminousIntensity) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetColorTemperature(double colorTemperature) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetBeamAngle(double beamAngle) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetFieldAngle(double fldAngle) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetBeamRadius(double radius) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetThrowRatio(double ratio) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetRectangleRatio(double ratio) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetBeamType(GdtfDefines::EGdtfBeamType type) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetColorIndex(Sint32 idx) = 0;
		
		// Reference
		virtual VCOMError VCOM_CALLTYPE     GetBreakCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetBreakAt(size_t at, IGdtfBreak** gdtfBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateBreak(Sint32 dmxBreak, GdtfDefines::DMXAddress address, IGdtfBreak** gdtfBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetGeometryReference(IGdtfGeometry** geometry) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGeometryReference(IGdtfGeometry*  geometry) = 0;



		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

        // 0.5.2
        virtual VCOMError VCOM_CALLTYPE     GetCountLinkedDmxChannel(size_t& count, IGdtfDmxMode * forMode) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetLinkedDmxChannelAt(size_t at, IGdtfDmxChannel** outChannel, IGdtfDmxMode * forMode) = 0;

		// 0.6.3
		virtual VCOMError VCOM_CALLTYPE     GetParent(IGdtfGeometry** model) = 0;

		// Display
		virtual MvrString VCOM_CALLTYPE		GetTexture() = 0;
		virtual VCOMError VCOM_CALLTYPE		SetTexture(MvrString texture) = 0;

		// GDTF 1.2
		// Lamp
		virtual VCOMError VCOM_CALLTYPE     GetEmitterSpectrum(IGdtfPhysicalEmitter** outEmitter) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetEmitterSpectrum(IGdtfPhysicalEmitter* newEmitter) = 0;

        // Laser
        virtual VCOMError VCOM_CALLTYPE		GetColorType(GdtfDefines::EGdtfLaserColorType& colorType) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetLaserColor(double& waveLength) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetOutputStrength(double& outputStrength) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetEmitter(IGdtfPhysicalEmitter** emitter) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetBeamDiameter(double& beamDiameter) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetBeamDivergenceMin(double& beamDivergenceMin) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetBeamDivergenceMax(double& beamDivergenceMax) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetScanAnglePan(double& scanAnglePan) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetScanAngleTilt(double& scanAngleTilt) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetScanSpeed(double& scanSpeed) = 0;

        virtual VCOMError VCOM_CALLTYPE		SetColorType(GdtfDefines::EGdtfLaserColorType colorType) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetLaserColor(double waveLength) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetOutputStrength(double outputStrength) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetEmitter(IGdtfPhysicalEmitter* emitter) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetBeamDiameter(double beamDiameter) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetBeamDivergenceMin(double beamDivergenceMin) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetBeamDivergenceMax(double beamDivergenceMax) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetScanAnglePan(double scanAnglePan) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetScanAngleTilt(double scanAngleTilt) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetScanSpeed(double scanSpeed) = 0;

		virtual VCOMError VCOM_CALLTYPE 	GetLaserProtocolCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE 	GetLaserProtocolAt(size_t at, VectorworksMVR::IGdtfLaserProtocol** outLaserProtocol) = 0;
        virtual VCOMError VCOM_CALLTYPE 	CreateLaserProtocol(MvrString name, VectorworksMVR::IGdtfLaserProtocol** outLaserProtocol) = 0;

		// WiringObject
		virtual MvrString VCOM_CALLTYPE     GetConnectorType() = 0;
        virtual VCOMError VCOM_CALLTYPE		GetComponentType(GdtfDefines::EGdtfComponentType& componentType) = 0;
        virtual MvrString VCOM_CALLTYPE     GetSignalType() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPinCount(size_t& pinCount) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSignalLayer(size_t& signalLayer) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetOrientation(GdtfDefines::EGdtfOrientation& orientation) = 0;
        virtual MvrString VCOM_CALLTYPE     GetWireGroup() = 0;
        virtual VCOMError VCOM_CALLTYPE		GetElectricalPayLoad(double& electricalPayLoad) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetVoltageRangeMin(double& voltageRangeMin) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetVoltageRangeMax(double& voltageRangeMax) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetFrequencyRangeMin(double& frequencyRangeMin) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetFrequencyRangeMax(double& frequencyRangeMax) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCosPhi(double& cosPhi) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetMaxPayLoad(double& maxPayload) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetVoltage(double& voltage) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetFuseCurrent(double& fuseCurrent) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetFuseRating(GdtfDefines::EGdtfFuseRating& fuseRating) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetConnectorType(MvrString connectorType) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetComponentType(GdtfDefines::EGdtfComponentType componentType) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetSignalType(MvrString signalType) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetPinCount(size_t pinCount) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetSignalLayer(size_t signalLayer) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetOrientation(GdtfDefines::EGdtfOrientation orientation) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetWireGroup(MvrString wireGroup) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetElectricalPayLoad(double electricalPayLoad) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetVoltageRangeMin(double voltageRangeMin) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetVoltageRangeMax(double voltageRangeMax) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetFrequencyRangeMin(double frequencyRangeMin) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetFrequencyRangeMax(double frequencyRangeMax) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetCosPhi(double cosPhi) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetMaxPayLoad(double maxPayload) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetVoltage(double voltage) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetFuseCurrent(double fuseCurrent) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetFuseRating(GdtfDefines::EGdtfFuseRating fuseRating) = 0;

        virtual VCOMError VCOM_CALLTYPE 	GetPinPatchCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE 	GetPinPatchAt(size_t at, VectorworksMVR::IGdtfPinPatch** outPinPatch) = 0;
        virtual VCOMError VCOM_CALLTYPE 	CreatePinPatch(VectorworksMVR::IGdtfGeometry* toWiringObject, size_t fromPin, size_t toPin, VectorworksMVR::IGdtfPinPatch** outPinPatch) = 0;

		// Inventory
		virtual VCOMError VCOM_CALLTYPE     GetInventoryCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetInventoryCount(size_t count) = 0;

		// Structure
        virtual VCOMError VCOM_CALLTYPE		GetStructureLinkedGeometry(IGdtfGeometry** linkedGeometry) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetStructureType(GdtfDefines::EGdtfStructureType& structureType) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCrossSectionType(GdtfDefines::EGdtfCrossSectionType& crossSectionType) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCrossSectionHeight(double& crossSectionHeight) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCrossSectionWallThickness(double& crossSectionWallThickness) = 0;
        virtual MvrString VCOM_CALLTYPE		GetTrussCrossSection() = 0;

        virtual VCOMError VCOM_CALLTYPE	    SetStructureLinkedGeometry(IGdtfGeometry* linkedGeometry) = 0;
		virtual VCOMError VCOM_CALLTYPE	    SetStructureType(GdtfDefines::EGdtfStructureType structureType) = 0;
		virtual VCOMError VCOM_CALLTYPE	    SetCrossSectionType(GdtfDefines::EGdtfCrossSectionType crossSectionType) = 0;
		virtual VCOMError VCOM_CALLTYPE	    SetCrossSectionHeight(double crossSectionHeight) = 0;
		virtual VCOMError VCOM_CALLTYPE	    SetCrossSectionWallThickness(double crossSectionWallThickness) = 0;
		virtual VCOMError VCOM_CALLTYPE	    SetTrussCrossSection(MvrString trussCrossSection) = 0;

		// Support
		virtual VCOMError VCOM_CALLTYPE     GetSupportType(GdtfDefines::EGdtfSupportType& supportType) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCapacityX(double& capacityX) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCapacityY(double& capacityY) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCapacityZ(double& capacityZ) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCapacityXX(double& capacityXX) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCapacityYY(double& capacityYY) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCapacityZZ(double& capacityZZ) = 0;
		virtual MvrString VCOM_CALLTYPE     GetRopeCrossSection() = 0;
		virtual VCOMError VCOM_CALLTYPE	    GetRopeOffset(SVector3& ropeOffset) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetResistanceX(double& resistanceX) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetResistanceY(double& resistanceY) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetResistanceZ(double& resistanceZ) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetResistanceXX(double& resistanceXX) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetResistanceYY(double& resistanceYY) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetResistanceZZ(double& resistanceZZ) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetSupportType(GdtfDefines::EGdtfSupportType supportType) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCapacityX(double capacityX) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCapacityY(double capacityY) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCapacityZ(double capacityZ) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCapacityXX(double capacityXX) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCapacityYY(double capacityYY) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCapacityZZ(double capacityZZ) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetRopeCrossSection(MvrString ropeCrossSection) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetRopeOffset(double x, double y, double z) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetResistanceX(double resistanceX) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetResistanceY(double resistanceY) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetResistanceZ(double resistanceZ) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetResistanceXX(double resistanceXX) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetResistanceYY(double resistanceYY) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetResistanceZZ(double resistanceZZ) = 0;
	};
	typedef VCOMPtr<IGdtfGeometry>	IGdtfGeometryPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxChannelSet : public IVWUnknown
    {
	public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxStartAddress(GdtfDefines::DmxValue& address) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxEndAddress(GdtfDefines::DmxValue& address) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalStart(double& start) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalEnd(double& end) = 0;        
        virtual VCOMError VCOM_CALLTYPE     GetWheelSlot(Sint32& WheelSlotIdx) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetUsePhysicalFromParent(bool& outUse) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalStart(double start) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalEnd(double end) = 0;		
		virtual VCOMError VCOM_CALLTYPE     SetWheelSlot(Sint32 WheelSlotIdx) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfDmxChannelSet>	IGdtfDmxChannelSetPtr;

	class DYNAMIC_ATTRIBUTE IGdtfDmxSubChannelSet : public IVWUnknown
    {
	public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;		
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalFrom(double& from) = 0;        
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalTo(double& to) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSubPhysicalUnit(IGdtfSubPhysicalUnit** subPhysicalUnit) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetDMXProfile(IGdtfDMXProfile** dmxProfile) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;		
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalFrom(double from) = 0;        
        virtual VCOMError VCOM_CALLTYPE     SetPhysicalTo(double to) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetSubPhysicalUnit(IGdtfSubPhysicalUnit* subPhysicalUnit) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetDMXProfile(IGdtfDMXProfile* dmxProfile) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfDmxSubChannelSet>	IGdtfDmxSubChannelSetPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxChannelFunction : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetAttribute(IGdtfAttribute** attribute) = 0;
        virtual MvrString VCOM_CALLTYPE     GetOriginalAttribute() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetStartAddress(GdtfDefines::DmxValue& address) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetEndAddress(GdtfDefines::DmxValue& address) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalStart(double& start) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetPhysicalEnd(double& end) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetRealFade(double& fade) = 0;        
        virtual VCOMError VCOM_CALLTYPE     GetOnWheel(IGdtfWheel** wheel) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetEmitter(IGdtfPhysicalEmitter** emitter) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFilter(IGdtfFilter** outVal) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetAttribute(IGdtfAttribute* attribute) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetOriginalAttribute(MvrString attr) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetStartAddress(GdtfDefines::DmxValue address) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalStart(double start) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetPhysicalEnd(double end) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetRealFade(double fade) = 0;		
		virtual VCOMError VCOM_CALLTYPE     SetOnWheel(IGdtfWheel* wheel) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetEmitter(IGdtfPhysicalEmitter* emitter) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetFilter(IGdtfFilter* val)=0;

        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelSetCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelSetAt(size_t at, IGdtfDmxChannelSet** set) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxChannelSet(MvrString name, GdtfDefines::DmxValue start, GdtfDefines::DmxValue end, IGdtfDmxChannelSet** set) = 0;
		
		// Mode Master from GDTF 0.88
		virtual VCOMError VCOM_CALLTYPE     GetModeMasterChannel(IGdtfDmxChannel** outChannel, GdtfDefines::DmxValue& start, GdtfDefines::DmxValue& end) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetModeMasterFunction(IGdtfDmxChannelFunction** outFunction, GdtfDefines::DmxValue& start, GdtfDefines::DmxValue& end) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetModeMasterChannel(IGdtfDmxChannel* channel, GdtfDefines::DmxValue start, GdtfDefines::DmxValue end) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetModeMasterFunction(IGdtfDmxChannelFunction* function, GdtfDefines::DmxValue start, GdtfDefines::DmxValue end) = 0;

        virtual VCOMError VCOM_CALLTYPE     GetParentLogicalChannel(IGdtfDmxLogicalChannel** parent) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

        // 0.3.20
        virtual VCOMError VCOM_CALLTYPE     GetResolution(GdtfDefines::EGdtfChannelBitResolution& resolution) = 0;

		// GDTF 1.1
		virtual VCOMError VCOM_CALLTYPE     GetRealAcceleration(double& value) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetRealAcceleration(double value) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetDefaultValue(GdtfDefines::DmxValue& defaultValue) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDefaultValue(GdtfDefines::DmxValue defaultValue) = 0;

		// GDTF 1.2
		virtual VCOMError VCOM_CALLTYPE     GetColorSpace(IGdtfColorSpace** colorSpace) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetGamut(IGdtfGamut** gamut) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetDMXProfile(IGdtfDMXProfile** dmxProfile) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetMin(double& value) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetMax(double& value) = 0;
		virtual MvrString VCOM_CALLTYPE     GetCustomName() = 0;

		virtual VCOMError VCOM_CALLTYPE     SetColorSpace(IGdtfColorSpace* colorSpace) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGamut(IGdtfGamut* gamut) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDMXProfile(IGdtfDMXProfile* dmxProfile) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetMin(double value) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetMax(double value) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetCustomName(MvrString customName) = 0;

		virtual VCOMError VCOM_CALLTYPE     GetDmxSubChannelSetCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxSubChannelSetAt(size_t at, IGdtfDmxSubChannelSet** subChannelSet) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxSubChannelSet(MvrString name, IGdtfSubPhysicalUnit* subPhysicalUnit, IGdtfDmxSubChannelSet** subChannelSet) = 0;
    };
	typedef VCOMPtr<IGdtfDmxChannelFunction>	IGdtfDmxChannelFunctionPtr;
        
    class DYNAMIC_ATTRIBUTE IGdtfDmxLogicalChannel : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetAttribute(IGdtfAttribute** attribute) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxSnap(GdtfDefines::EGdtfDmxSnap& snap) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetDmxMaster(GdtfDefines::EGdtfDmxMaster& master) = 0;		
        virtual VCOMError VCOM_CALLTYPE     GetMoveInBlackFrames(double& frames) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxChangeTimeLimit(double& changeTimeLimit) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetAttribute(IGdtfAttribute* attribute) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxSnap(GdtfDefines::EGdtfDmxSnap snap) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxMaster(GdtfDefines::EGdtfDmxMaster master) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetMoveInBlackFrames(double frames) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxChangeTimeLimit(double changeTimeLimit) = 0;		

        virtual VCOMError VCOM_CALLTYPE     GetDmxFunctionCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxFunctionAt(size_t at, IGdtfDmxChannelFunction** function) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxFunction(MvrString name, IGdtfDmxChannelFunction** function) = 0;

        virtual VCOMError VCOM_CALLTYPE     GetParentDmxChannel(IGdtfDmxChannel** parent) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfDmxLogicalChannel>	IGdtfDmxLogicalChannelPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxChannel : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetDmxBreak(Sint32& dmxBreak) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetCoarse(Sint32& coarse) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFine(Sint32& fine) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetUltra(Sint32& ultra) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetUber(Sint32& uber) = 0;        
        virtual VCOMError VCOM_CALLTYPE     GetHighlight(GdtfDefines::DmxValue& highlight) = 0;
		virtual VCOMError VCOM_CALLTYPE     HasHighlight(bool& highlight) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetGeometry(IGdtfGeometry** model) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     SetDmxBreak(Sint32 dmxBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetCoarse(Sint32 coarse) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetFine(Sint32 fine) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetUltra(Sint32 ultra) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetUber (Sint32  uber) = 0;				
		virtual VCOMError VCOM_CALLTYPE     SetHighlight(GdtfDefines::DmxValue highlight) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGeometry(IGdtfGeometry* model) = 0;
		
        virtual VCOMError VCOM_CALLTYPE     GetLogicalChannelCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetLogicalChannelAt(size_t at, IGdtfDmxLogicalChannel** channel) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateLogicalChannel(IGdtfAttribute* attribute, IGdtfDmxLogicalChannel** channel) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

        // 0.3.20
        virtual VCOMError VCOM_CALLTYPE     GetResolution(GdtfDefines::EGdtfChannelBitResolution& resolution) = 0;

		// GDTF 1.1
		virtual VCOMError VCOM_CALLTYPE     GetInitialFunction(IGdtfDmxChannelFunction** function) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetInitialFunction(IGdtfDmxChannelFunction* function) = 0;
    };
	typedef VCOMPtr<IGdtfDmxChannel>	IGdtfDmxChannelPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxRelation : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetMasterChannel(IGdtfDmxChannel** master) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetSlaveChannel(IGdtfDmxChannelFunction** slave) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetRelationType(GdtfDefines::EGdtfDmxRelationType& relation) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
	typedef VCOMPtr<IGdtfDmxRelation>	IGdtfDmxRelationPtr;

class DYNAMIC_ATTRIBUTE IGdtfMacro : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetMacroDMX(IGdtfMacroDMX** outMacroDmx) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateMacroDMX(IGdtfMacroDMX** outMacroDmx) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		GetMacroVisual(IGdtfMacroVisual** outMacroVisual) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateMacroVisual(IGdtfMacroVisual** outMacroVisual) = 0;

		// GDTF 1.2
		virtual VCOMError VCOM_CALLTYPE     GetChannelFunction(IGdtfDmxChannelFunction** outChannelFunction) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetChannelFunction(IGdtfDmxChannelFunction* newChannelFunction) = 0;
	};
	typedef VCOMPtr<IGdtfMacro>	IGdtfMacroPtr;


	class DYNAMIC_ATTRIBUTE IGdtfMacroDMX : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE    GetStepCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE    GetStepAt(size_t at, IGdtfMacroDMXStep** outStep) = 0;
		virtual VCOMError VCOM_CALLTYPE    CreateStep(double& macroDuration, IGdtfMacroDMXStep** outStep) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfMacroDMX>	IGdtfMacroDMXPtr;


	class DYNAMIC_ATTRIBUTE IGdtfMacroDMXStep : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE     GetDuration(double& outDur) = 0;

		virtual VCOMError VCOM_CALLTYPE GetDMXValueCount(size_t & count) = 0;
		virtual VCOMError VCOM_CALLTYPE GetDMXValueAt(size_t at, IGdtfMacroDMXValue**  outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE CreateDMXValue(GdtfDefines::DmxValue dmxVal, IGdtfDmxChannel* dmxChannel, IGdtfMacroDMXValue** outVal) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfMacroDMXStep>	IGdtfMacroDMXStepPtr;


	class DYNAMIC_ATTRIBUTE IGdtfMacroDMXValue : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE   GetDmxValue(GdtfDefines::DmxValue& outValue) = 0;
		virtual VCOMError VCOM_CALLTYPE   GetDmxChannel(IGdtfDmxChannel** outValue) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfMacroDMXValue>	IGdtfMacroDMXValuePtr;


	class DYNAMIC_ATTRIBUTE IGdtfMacroVisual : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE     GetVisualStepCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetVisualStepAt(size_t at, IGdtfMacroVisualStep**  outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateVisualStep(IGdtfMacroVisualStep** outVal) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfMacroVisual>	IGdtfMacroVisualPtr;


	class DYNAMIC_ATTRIBUTE IGdtfMacroVisualStep : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE GetDuration(double& duration) = 0;
		virtual VCOMError VCOM_CALLTYPE GetFade(double& fade) = 0;
		virtual VCOMError VCOM_CALLTYPE GetDelay(double& delay) = 0;
		//        
		virtual VCOMError VCOM_CALLTYPE SetDuration(double d) = 0;
		virtual VCOMError VCOM_CALLTYPE SetFade(double f) = 0;
		virtual VCOMError VCOM_CALLTYPE SetDelay(double d) = 0;

		virtual VCOMError VCOM_CALLTYPE     GetVisualValueCount(size_t& outCount) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetVisualValueAt(size_t at, IGdtfMacroVisualValue**  outVal) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateVisualValue(GdtfDefines::DmxValue dmxVal, IGdtfDmxChannelFunction* channelFunction, IGdtfMacroVisualValue ** outVal) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfMacroVisualStep>	IGdtfMacroVisualStepPtr;


	class DYNAMIC_ATTRIBUTE IGdtfMacroVisualValue : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE   GetDmxValue(GdtfDefines::DmxValue& outValue) = 0;
		virtual VCOMError VCOM_CALLTYPE   GetDmxChannel(IGdtfDmxChannelFunction** outValue) = 0;

		virtual VCOMError VCOM_CALLTYPE   SetDmxValue(GdtfDefines::DmxValue newValue) = 0;
		virtual VCOMError VCOM_CALLTYPE   SetDmxChannel(IGdtfDmxChannelFunction* newValue) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfMacroVisualValue>	IGdtfMacroVisualValuePtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfDmxMode : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
		virtual VCOMError VCOM_CALLTYPE     GetGeometry(IGdtfGeometry** model) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGeometry(IGdtfGeometry* model) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxChannelAt(size_t at, IGdtfDmxChannel** channel) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxChannel(IGdtfGeometry* geometry, IGdtfDmxChannel** channel) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetDmxRelationCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxRelationAt(size_t at, IGdtfDmxRelation** relation) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxRelation(MvrString name, GdtfDefines::EGdtfDmxRelationType type, IGdtfDmxChannel* master, IGdtfDmxChannelFunction* slave, IGdtfDmxRelation** relation) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     GetDmxMacroCount(size_t& count) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetDmxMacroAt(size_t at, IGdtfMacro** macro) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateDmxMacro(MvrString name, IGdtfMacro** macro) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

        // 0.5.1
        virtual VCOMError VCOM_CALLTYPE     GetBreakCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFootprintForBreak(size_t inBreak, size_t& footprint) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetBreakAt(size_t at, size_t &breakId) = 0;

		// GDTF 1.2
		virtual MvrString VCOM_CALLTYPE		GetDescription() = 0;
		virtual VCOMError VCOM_CALLTYPE 	SetDescription(MvrString description) = 0;
    };
	typedef VCOMPtr<IGdtfDmxMode>	IGdtfDmxModePtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfRevision : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetText() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDate(STime& date) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetText(MvrString txt) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetDate(STime date) = 0;

		// GDTF 1.0
		virtual VCOMError VCOM_CALLTYPE     GetUserId(size_t& userId) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetUserId(size_t userId) = 0;

		// GDTF 1.2
		virtual MvrString VCOM_CALLTYPE     GetModifiedBy() = 0;
		virtual VCOMError VCOM_CALLTYPE     SetModifiedBy(MvrString modifiedBy) = 0;
    };
	typedef VCOMPtr<IGdtfRevision>	IGdtfRevisionPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfUserPreset : public IVWUnknown
    {
    };
	typedef VCOMPtr<IGdtfUserPreset>	IGdtfUserPresetPtr;

    class DYNAMIC_ATTRIBUTE IGdtfMeasurementPoint : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE     GetWaveLength(double& wavelength) = 0;  // in nm
        virtual VCOMError VCOM_CALLTYPE     GetEnergy(double& energy) = 0;          // Unit W/m^2*/nm
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

        virtual VCOMError VCOM_CALLTYPE     SetWaveLength(double wavelength) = 0;  
        virtual VCOMError VCOM_CALLTYPE     SetEnergy(double energy) = 0;
    };
	typedef VCOMPtr<IGdtfMeasurementPoint>	IGdtfMeasurementPointPtr;
        
    class DYNAMIC_ATTRIBUTE IGdtfMeasurement : public IVWUnknown
    {
    public:        
        // Getter
        virtual VCOMError VCOM_CALLTYPE    GetPhysical(double& outVal)=0;
        virtual VCOMError VCOM_CALLTYPE    GetLuminousIntensity(double& outVal)=0;
        virtual VCOMError VCOM_CALLTYPE    GetTransmission(double& outVal)=0;
        virtual VCOMError VCOM_CALLTYPE    GetInterpolationTo(GdtfDefines::EGdtfInterpolationTo& outVal)=0;
        // Setter               
        virtual VCOMError VCOM_CALLTYPE    SetPhysical(double val)=0;
        virtual VCOMError VCOM_CALLTYPE    SetLuminousIntensity(double val)=0;
        virtual VCOMError VCOM_CALLTYPE    SetTransmission(double val)=0;
        virtual VCOMError VCOM_CALLTYPE    SetInterpolationTo(GdtfDefines::EGdtfInterpolationTo val)=0;        
        //
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetMeasurementPointCount(size_t& count)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateMeasurementPoint(VectorworksMVR::IGdtfMeasurementPoint** outVal)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetMeasurementPointAt(size_t at, VectorworksMVR::IGdtfMeasurementPoint** value)=0;
        //

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfMeasurement>	IGdtfMeasurementPtr;
           
    class DYNAMIC_ATTRIBUTE IGdtfFilter : public IVWUnknown
    {
    public:        
        // Getter
        virtual MvrString VCOM_CALLTYPE     GetName()= 0;
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& outVal)= 0;
        // Setter
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name)= 0;
        virtual VCOMError VCOM_CALLTYPE     SetColor(CieColor val)= 0;
        //
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetMeasurementCount(size_t& count)= 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateMeasurement(VectorworksMVR::IGdtfMeasurement** outVal)= 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetMeasurementAt(size_t at, VectorworksMVR::IGdtfMeasurement** value)= 0;
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfFilter>	IGdtfFilterPtr;
    
    class DYNAMIC_ATTRIBUTE IGdtfPhysicalEmitter : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetColor(CieColor& color) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     GetMeasurementCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetMeasurementAt(size_t at, IGdtfMeasurement** ouVal) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateMeasurement(IGdtfMeasurement** ouVal) = 0;
		virtual MvrString VCOM_CALLTYPE     GetDiodePart()=0;
        virtual VCOMError VCOM_CALLTYPE     GetDominantWaveLength(double& outVal)=0;		

        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetColor(CieColor & color) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetDiodePart(MvrString val)=0;		
        virtual VCOMError VCOM_CALLTYPE     SetDominantWaveLength(double val)=0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfPhysicalEmitter>	IGdtfPhysicalEmitterPtr;
        
    class DYNAMIC_ATTRIBUTE IGdtfColorSpace : public IVWUnknown
    {
    public:
        virtual VCOMError VCOM_CALLTYPE GetColorSpace(GdtfDefines::EGdtfColorSpace& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE	GetRed (CieColor& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetGreen(CieColor& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE	GetBlue(CieColor& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE	GetWhite(CieColor& outVal) = 0;

        // Setter       
        virtual VCOMError VCOM_CALLTYPE SetColorSpace(GdtfDefines::EGdtfColorSpace val) = 0;
        virtual VCOMError VCOM_CALLTYPE SetRed(CieColor val) = 0;
        virtual VCOMError VCOM_CALLTYPE SetGreen(CieColor val) = 0;
        virtual VCOMError VCOM_CALLTYPE SetBlue(CieColor val) = 0;
        virtual VCOMError VCOM_CALLTYPE	SetWhite(CieColor outVal) = 0;


        virtual VCOMError VCOM_CALLTYPE BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE GetBoundObject() = 0;

		// GDTF 1.2
		virtual MvrString VCOM_CALLTYPE GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE SetName(MvrString name) = 0;
    };
    typedef VCOMPtr<IGdtfColorSpace>	IGdtfColorSpacePtr;

	class DYNAMIC_ATTRIBUTE IGdtfGamut : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;

		virtual VCOMError VCOM_CALLTYPE 	GetPointCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE 	GetPointAt(size_t at, CieColor& outColor) = 0;
        virtual VCOMError VCOM_CALLTYPE 	CreatePoint(CieColor& color) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfGamut>	IGdtfGamutPtr;

    class DYNAMIC_ATTRIBUTE IGdtfCRI : public IVWUnknown
    {
    public:
        // Getter
        virtual VCOMError VCOM_CALLTYPE GetColorSample(GdtfDefines::EGdtfColorSample outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE GetColorRenderingIndex(Uint8& outVal) = 0;
        // Setter
        virtual VCOMError VCOM_CALLTYPE SetColorSample(GdtfDefines::EGdtfColorSample val) = 0;
        virtual VCOMError VCOM_CALLTYPE SetColorRenderingIndex(Uint8 val) = 0;
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfCRI>	IGdtfCRIPtr;

    class DYNAMIC_ATTRIBUTE IGdtfCRIGroup : public IVWUnknown
    {
    public:

        virtual VCOMError VCOM_CALLTYPE GetColorTemperature(double& outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE SetColorTemperature(double value) = 0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetCRICount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateCRI(GdtfDefines::EGdtfColorSample ces, Sint32 colorTemp, VectorworksMVR::IGdtfCRI **outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetCRIAt(size_t at, VectorworksMVR::IGdtfCRI** value) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
    typedef VCOMPtr<IGdtfCRIGroup>	IGdtfCRIGroupPtr;

	class DYNAMIC_ATTRIBUTE IGdtfPoint : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE		GetDMXPercentage(double& dmxPercentage) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCFC3(double& cfc3) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCFC2(double& cfc2) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCFC1(double& cfc1) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetCFC0(double& cfc0) = 0;


        virtual VCOMError VCOM_CALLTYPE		SetDMXPercentage(double dmxPercentage) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetCFC3(double cfc3) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetCFC2(double cfc2) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetCFC1(double cfc1) = 0;
        virtual VCOMError VCOM_CALLTYPE		SetCFC0(double cfc0) = 0;

		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfPoint>	IGdtfPointPtr;
	
	class DYNAMIC_ATTRIBUTE IGdtfDMXProfile : public IVWUnknown
	{
	public:
		virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;

		// GDTF 1.2
		virtual VCOMError VCOM_CALLTYPE		SetName(MvrString name) = 0;

        virtual VCOMError VCOM_CALLTYPE		GetPointCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetPointAt(size_t at, IGdtfPoint** point) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreatePoint(double DMXPercentage, double CFC3, double CFC2, double CFC1, double CFC0, IGdtfPoint** point) = 0;
	};
	typedef VCOMPtr<IGdtfDMXProfile>	IGdtfDMXProfilePtr;

	class DYNAMIC_ATTRIBUTE IGdtfConnector : public IVWUnknown
    {
		public:
        virtual MvrString VCOM_CALLTYPE     GetName() = 0;
		virtual MvrString VCOM_CALLTYPE     GetType() = 0;
		virtual VCOMError VCOM_CALLTYPE     GetDmxBreak(Uint32& outDmxBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetGender(Sint32& outGender) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetLength(double& outLength) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetType(MvrString type) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetDmxBreak(Uint32 dmxBreak) = 0;
		virtual VCOMError VCOM_CALLTYPE     SetGender(Sint32 gender) = 0;	
        virtual VCOMError VCOM_CALLTYPE     SetLength(double length) = 0;

		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfConnector>	IGdtfConnectorPtr;
	
    class DYNAMIC_ATTRIBUTE IGdtfFixture : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE		ReadFromFile(MvrString fullPath) = 0;
		
		virtual VCOMError VCOM_CALLTYPE		OpenForWrite(MvrString fullPath, MvrString name, MvrString manufacturer, const MvrUUID& uuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		OpenForWrite(MvrString name, MvrString manufacturer, const MvrUUID& uuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		AddFileToGdtfFile(MvrString fullPath, GdtfDefines::ERessourceType resType, MvrString newFileName = "") = 0;
		virtual VCOMError VCOM_CALLTYPE		AddBufferToGdtfFile(MvrString filename, const char* inBuffer, size_t length, GdtfDefines::ERessourceType resType) = 0;

		virtual VCOMError VCOM_CALLTYPE		Close() = 0;
        
        virtual MvrString VCOM_CALLTYPE		GetName() = 0;
        virtual MvrString VCOM_CALLTYPE     GetManufacturer() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetFixtureGUID(MvrUUID& uuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		GetLinkedFixtureGUID(MvrUUID& uuid) = 0;
		virtual VCOMError VCOM_CALLTYPE		HasLinkedFixtureGUID(bool& has) = 0;
		
		virtual MvrString VCOM_CALLTYPE     GetFixtureTypeDescription() = 0;
		virtual MvrString VCOM_CALLTYPE		GetShortName() = 0;

        virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail() = 0;
		virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail_PNG_FullPath() = 0;
        virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail_SVG_FullPath() = 0;
        
		virtual VCOMError VCOM_CALLTYPE     SetFixtureTypeDescription(MvrString descrip) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetShortName(MvrString shortName) = 0;

		virtual VCOMError VCOM_CALLTYPE     SetFixtureThumbnail(MvrString thubnail) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetLinkedFixtureGUID(const MvrUUID& uuid) = 0;
		
        virtual VCOMError VCOM_CALLTYPE		GetActivationGroupCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetActivationGroupAt(size_t at, IGdtfActivationGroup** activationGroup) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateActivationGroup(MvrString name, IGdtfActivationGroup** activationGroup) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetFeatureGroupCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetFeatureGroupAt(size_t at, IGdtfFeatureGroup** featureGroup ) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateFeatureGroup(MvrString name, MvrString prettyName, IGdtfFeatureGroup** featureGroup ) = 0;
		
        virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateAttribute(MvrString name, MvrString prettyName, IGdtfAttribute** attribute) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetWheelCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetWheelAt(size_t at, IGdtfWheel** wheel ) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateWheel(MvrString name, IGdtfWheel** wheel ) = 0;
		
		
        virtual VCOMError VCOM_CALLTYPE		GetModelCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetModelAt(size_t at, IGdtfModel** model ) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateModel(MvrString name,IGdtfModel** model ) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGdtfGeometry** geometry) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateGeometry(GdtfDefines::EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry) = 0;
		
        virtual VCOMError VCOM_CALLTYPE		GetDmxModeCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetDmxModeAt(size_t at, IGdtfDmxMode** dmxMode ) = 0;
		virtual VCOMError VCOM_CALLTYPE		CreateDmxMode(MvrString name, IGdtfDmxMode** dmxMode ) = 0;
        
        virtual VCOMError VCOM_CALLTYPE		GetRevisionCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetRevisionAt(size_t at, IGdtfRevision** revision ) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateRevision(MvrString text, STime date, IGdtfRevision** macro) = 0;
		
        
        virtual VCOMError VCOM_CALLTYPE		GetPresetCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetPresetAt(size_t at, IGdtfUserPreset** preset ) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreatePreset(IGdtfUserPreset** macro) = 0;
                		
		virtual VCOMError VCOM_CALLTYPE     GetRDM(IGdtf_FTRDM ** newFTRDM) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateRDM(VectorworksMVR::IGdtf_FTRDM ** outFTRDM) = 0;

        //-----------------------------------------------------------------------------
        // PhysicalDescriptions
        virtual VCOMError                             GetColorSpace(VectorworksMVR::IGdtfColorSpace ** outColorSpace)=0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetEmitterCount(size_t& count)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateEmitter(MvrString name, CieColor color, VectorworksMVR::IGdtfPhysicalEmitter** outVal)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetEmitterAt(size_t at, VectorworksMVR::IGdtfPhysicalEmitter** value)=0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetFilterCount(size_t& count)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateFilter(MvrString name, CieColor color, VectorworksMVR::IGdtfFilter** outVal)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetFilterAt(size_t at, VectorworksMVR::IGdtfFilter** value)=0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetDMXProfileCount(size_t& count)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateDMXProfile(VectorworksMVR::IGdtfDMXProfile** outVal)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetDMXProfileAt(size_t at, VectorworksMVR::IGdtfDMXProfile** value)=0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetCRIGroupCount(size_t& count)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateCRIGroup(double colorTemp, VectorworksMVR::IGdtfCRIGroup** outVal)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetCRIGroupAt(size_t at, VectorworksMVR::IGdtfCRIGroup** value)=0;
        //-----------------------------------------------------------------------------               
        // Parsing Errors
        virtual VCOMError VCOM_CALLTYPE		GetParsingErrorCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE		GetParsingErrorAt(size_t at, IGdtfXmlParsingError** value) = 0;

		// Gdtf 1.0
		virtual MvrString VCOM_CALLTYPE		GetLongName() = 0;
		virtual VCOMError VCOM_CALLTYPE		SetLongName(MvrString longname) = 0;

		// Get Ressources
		virtual VCOMError VCOM_CALLTYPE		GetImageRessourcesCount(size_t& count) = 0;
		virtual MvrString VCOM_CALLTYPE		GetImageRessourcesPathAt(size_t at) = 0;

		//-----------------------------------------------------------------------------               
        // BufferWorkflow
		virtual VCOMError VCOM_CALLTYPE		GetBufferLength(size_t& length) = 0;		
		virtual VCOMError VCOM_CALLTYPE		ToBuffer(char* outBuffer) = 0;	
		virtual VCOMError VCOM_CALLTYPE		FromBuffer(const char* inBuffer, size_t length) = 0;
		virtual VCOMError VCOM_CALLTYPE     RefreshBuffer() = 0;

		//-----------------------------------------------------------------------------
		// GDTF 1.1
		virtual VCOMError VCOM_CALLTYPE		GetCanHaveChildren(bool& value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetCanHaveChildren(bool value) = 0;

		virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetConnectorCount(size_t& count)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateConnector(MvrString name, MvrString type, VectorworksMVR::IGdtfConnector** outVal)=0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetConnectorAt(size_t at, VectorworksMVR::IGdtfConnector** value)=0;

		virtual VCOMError VCOM_CALLTYPE		GetOperatingTemperatureLow(double& value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetOperatingTemperatureLow(double value) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetOperatingTemperatureHigh(double& value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetOperatingTemperatureHigh(double value) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetWeight(double& value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetWeight(double value) = 0;

		virtual VCOMError VCOM_CALLTYPE		GetLegHeight(double& value) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetLegHeight(double value) = 0;

		//-----------------------------------------------------------------------------
		// GDTF 1.2
		virtual VCOMError VCOM_CALLTYPE     GetArtNet(IGdtfArtNet** artNet) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateArtNet(IGdtfArtNet** artNet) = 0;

		virtual VCOMError VCOM_CALLTYPE     GetSACN(IGdtfSACN** sACN) = 0;
		virtual VCOMError VCOM_CALLTYPE     CreateSACN(IGdtfSACN** sACN) = 0;

		virtual VCOMError VCOM_CALLTYPE 	GetAdditionalColorSpaceCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE 	CreateAdditionalColorSpace(MvrString name, GdtfDefines::EGdtfColorSpace colorSpace, VectorworksMVR::IGdtfColorSpace** outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE 	GetAdditionalColorSpaceAt(size_t at, VectorworksMVR::IGdtfColorSpace** value) = 0;

		virtual VCOMError VCOM_CALLTYPE  	GetGamutCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE  	CreateGamut(MvrString name, CieColor color, VectorworksMVR::IGdtfGamut** outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE  	GetGamutAt(size_t at, VectorworksMVR::IGdtfGamut** value) = 0;

		virtual VCOMError VCOM_CALLTYPE 	GetThumbnailOffsetX(Sint32& offsetX) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetThumbnailOffsetX(Sint32 offsetX) = 0;	

		virtual VCOMError VCOM_CALLTYPE		GetThumbnailOffsetY(Sint32& offsetY) = 0;
		virtual VCOMError VCOM_CALLTYPE		SetThumbnailOffsetY(Sint32 offsetY) = 0;

	};
    typedef VCOMPtr<IGdtfFixture>	IGdtfFixturePtr;
    const   VWIID IID_IGdtfFixture = { 0x8f7bba09, 0x0753, 0x4971, {0xa9, 0x1b, 0x51, 0xce, 0x96, 0xd2, 0xb6, 0x3f}};

    class DYNAMIC_ATTRIBUTE IGdtf_FTRDM : public IVWUnknown
    {
    public:
        virtual VCOMError VCOM_CALLTYPE GetManufacturerID(size_t& outVal) = 0;        
        virtual VCOMError VCOM_CALLTYPE GetDeviceModelID(size_t& outVal) = 0;

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetSoftwareVersionIDCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateSoftwareVersionID(size_t value, VectorworksMVR::IGdtfSoftwareVersionID** outVal) = 0;
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetSoftwareVersionIDAt(size_t at, VectorworksMVR::IGdtfSoftwareVersionID** value) = 0;

        virtual VCOMError VCOM_CALLTYPE SetManufacturerID(size_t value) = 0;
        virtual VCOMError VCOM_CALLTYPE SetDeviceModelID(size_t value) = 0;

        
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtf_FTRDM>	IGdtfTRDMPtr;

	class DYNAMIC_ATTRIBUTE IGdtfMap : public IVWUnknown
	{
	public:
		virtual VCOMError VCOM_CALLTYPE     GetKey(Uint32& key) = 0;
		virtual VCOMError VCOM_CALLTYPE     GetValue(Uint32& value) = 0;

        virtual VCOMError VCOM_CALLTYPE     SetKey(Uint32 key) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetValue(Uint32 value) = 0;
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
		virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
	};
	typedef VCOMPtr<IGdtfMap>	IGdtfMapPtr;

	class DYNAMIC_ATTRIBUTE IGdtfArtNet : public IVWUnknown
    {
    public:
        virtual VCOMError VCOM_CALLTYPE  	GetMapCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE  	GetMapAt(size_t at, IGdtfMap** map) = 0;
        virtual VCOMError VCOM_CALLTYPE  	CreateMap(Uint32 key, Uint32 value, IGdtfMap** map) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfArtNet>	IGdtfArtNetPtr;

	class DYNAMIC_ATTRIBUTE IGdtfSACN : public IVWUnknown
    {
    public:
        virtual VCOMError VCOM_CALLTYPE  	GetMapCount(size_t& count) = 0;
        virtual VCOMError VCOM_CALLTYPE  	GetMapAt(size_t at, IGdtfMap** map) = 0;
        virtual VCOMError VCOM_CALLTYPE  	CreateMap(Uint32 key, Uint32 value, IGdtfMap** map) = 0;
        
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfSACN>	IGdtfSACNPtr;
    
    
    class DYNAMIC_ATTRIBUTE IGdtfDMXPersonality : public IVWUnknown
    {
    public:
        // Getter        
        virtual VCOMError VCOM_CALLTYPE		GetValue(size_t& outValue) const  = 0;
        virtual VCOMError VCOM_CALLTYPE     GetDmxMode(IGdtfDmxMode **outDmxMode) = 0;
        // Setter       
        virtual VCOMError VCOM_CALLTYPE     SetValue(size_t val) = 0;
        virtual VCOMError VCOM_CALLTYPE     SetDmxMode (IGdtfDmxMode * newDmxMode) = 0;
        //
        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfDMXPersonality>	IGdtfDMXPersonalityPtr;
    
    
    class DYNAMIC_ATTRIBUTE IGdtfSoftwareVersionID : public IVWUnknown
    {
    public:
        virtual VCOMError VCOM_CALLTYPE     GetValue(size_t& outVal)= 0;
        virtual VCOMError VCOM_CALLTYPE     SetValue(size_t  value)= 0;

        virtual VCOMError VCOM_CALLTYPE     GetDMXPersonalityCount(size_t& outCount)= 0;
        virtual VCOMError VCOM_CALLTYPE     GetDMXPersonalityAt(size_t at, IGdtfDMXPersonality**  outValue)= 0;
        virtual VCOMError VCOM_CALLTYPE     CreateDMXPersonality(size_t dmxPersonalityValue, IGdtfDmxMode* dmxMode, IGdtfDMXPersonality** outValue)= 0;		

        virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr) = 0;
        virtual void*	  VCOM_CALLTYPE     GetBoundObject() = 0;
    };
    typedef VCOMPtr<IGdtfSoftwareVersionID>	IGdtfSoftwareVersionIDPtr;


    class DYNAMIC_ATTRIBUTE IGdtfXmlParsingError : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE     GetErrorType(GdtfDefines::EGdtfParsingError& error) = 0;
        virtual MvrString VCOM_CALLTYPE     GetErrorMessage() = 0;
        virtual MvrString VCOM_CALLTYPE     GetNodeName() = 0;
        virtual VCOMError VCOM_CALLTYPE     GetLineAndColumnNumber(size_t& line, size_t& column) = 0;
        virtual MvrString VCOM_CALLTYPE     GetObjectName() = 0;
    };
    typedef VCOMPtr<IGdtfXmlParsingError>	IGdtfXmlParsingErrorPtr;

    class DYNAMIC_ATTRIBUTE IUtility : public IVWUnknown
    {
		public:
        virtual VCOMError VCOM_CALLTYPE     CieToRgb(const CieColor& color, RGBColor& out) = 0;
        virtual VCOMError VCOM_CALLTYPE     RgBToCie(const RGBColor& color, CieColor& out) = 0;
    };
    typedef VCOMPtr<IUtility>	IIUtilityPtr;
    const   VWIID IID_IUtility = { 0x706cb180, 0xcd45, 0x4a9a, {0xab, 0xdc, 0x62, 0xab, 0x5f, 0xfe, 0x37, 0x6b}};

	
	class MVRxchangeString
	{
		public:
		MVRxchangeString()
		{
			std::memset(fBuffer,0,1024);
		}
		MVRxchangeString(const char* str)
		{
			std::memset(fBuffer,0,1024);
			this->operator=(str);
		}

		mutable char fBuffer[1024];

		MVRxchangeString& operator=(const char* str)
		{
#pragma warning(push) // Save the current warning state
#pragma warning(disable : 4996) // Disable strncpy warning
			std::strncpy(fBuffer, str, 1024);
#pragma warning(pop)

			fBuffer[1023] = '\0';	// In case str is longer than 1024, no terminator is set by strncpy
			return *this;
		}

		bool operator==(const MVRxchangeString& other) const
		{
			return std::strncmp(fBuffer, other.fBuffer, 1023) == 0;
		}

		operator char*  () const
		{
			return fBuffer;
		}
	};

	#ifdef BUILD_MVR_XCHANGE

	class DYNAMIC_ATTRIBUTE IMVRxchangeService : public IVWUnknown
    {
		public:

		struct ConnectToRemoteServiceArgs
		{
			MVRxchangeString Url;
		};
		/**
		 * @brief Connects to a given Socket Mode Mode MVR-xchange system
		 * 
		 * @param service 
		 * @return VCOMError 
		 */
		virtual VCOMError VCOM_CALLTYPE     ConnectToRemoteService(const ConnectToRemoteServiceArgs& service) = 0;
		/**
		 * @brief Leaves the WebSocket Mode MVR-xchange system when connected
		 * 
		 * @param service 
		 * @return VCOMError 
		 */
		virtual VCOMError VCOM_CALLTYPE     LeaveRemoteService() = 0;
		
		enum class MVRxchangeMessageType
		{
			MVR_UNDEFINED,

			MVR_JOIN,
			MVR_LEAVE,
			MVR_COMMIT,
			MVR_REQUEST,

			MVR_JOIN_RET,
			MVR_LEAVE_RET,
			MVR_COMMIT_RET,
			MVR_REQUEST_RET,

			MVR_NEW_SESSION_HOST
		};

		struct MVR_COMMIT_MESSAGE
		{
			MVRxchangeString 				Comment;
			uint32_t 						VersionMajor;
			uint32_t 						VersionMinor;
			uint64_t 						FileSize;
			MvrUUID							FileUUID;
			MvrUUID							StationUUID;
			std::vector<MvrUUID>			ForStationsUUID;
		};

		struct MVR_JOIN_MESSAGE
		{
			MVRxchangeString 				Provider;
			MVRxchangeString 				StationName;
			MvrUUID							StationUUID;
			uint32_t 						VersionMajor;
			uint32_t 						VersionMinor;
			std::vector<MVR_COMMIT_MESSAGE> Commits;
		};

		struct MVR_REQUEST_MESSAGE
		{
			MvrUUID							FileUUID;
			std::vector<MvrUUID>			FromStationUUID;
		};

		struct MVR_LEAVE_MESSAGE
		{
			MvrUUID							FromStationUUID;
		};
		

		struct IMVRxchangeMessage
		{
			IMVRxchangeMessage()
			{
				Type = MVRxchangeMessageType::MVR_UNDEFINED;
				RetIsOK = true;
				BufferToFileLength = 0;
				BufferToFile = nullptr;
			}
			MVRxchangeMessageType 	Type;
			MVR_JOIN_MESSAGE 		JOIN;
			MVR_COMMIT_MESSAGE 		COMMIT;
			MVR_REQUEST_MESSAGE 	REQUEST;
			MVR_LEAVE_MESSAGE 		LEAVE;

			// Sending files is possible with both, a buffer (and buffer length) or a file path
			// If both are set, buffer is used first
			MVRxchangeString 				PathToFile;
			char*							BufferToFile;
			size_t							BufferToFileLength;
			
			bool 							RetIsOK;
			MVRxchangeString 				RetError;
		};
		struct ConnectToLocalServiceArgs
		{
			MVRxchangeString 	Service;

			MvrUUID 			StationUUID;
			MVRxchangeString 	StationName;
			MVRxchangeString 	Provider;

			uint32_t     		VersionMajor;
			uint32_t         	VersionMinor;

			std::vector<MVR_COMMIT_MESSAGE> InitialFiles;

			// Internal
			std::vector<MVRxchangeString> IPv4_list;
			std::vector<MVRxchangeString> IPv6_list;
			uint16_t         Port;

		};

		
		/**
		 * @brief Connects to a given Local Network Mode MVR-xchange system
		 * 
		 * @param service 
		 * @return VCOMError 
		 */
        virtual VCOMError VCOM_CALLTYPE     ConnectToLocalService(const ConnectToLocalServiceArgs& service) = 0;
		/**
		 * @brief Leaves the Local Network Mode MVR-xchange system when connected
		 * 
		 * @param service 
		 * @return VCOMError 
		 */
        virtual VCOMError VCOM_CALLTYPE     LeaveLocalService() = 0;

		//struct GetLocalServicesArgs
		//{
		//	ConnectToLocalServiceArgs** 	Service;
		//	size_t 							CountServices;
		//};
		/**
		 * @brief Get the local services that are currently available
		 * 
		 * @param service 
		 * @return VCOMError 
		 */
		virtual VCOMError VCOM_CALLTYPE     QueryLocalServices(size_t& out_Count) = 0;
        virtual VCOMError VCOM_CALLTYPE     GetLocalServiceAt(size_t index, ConnectToLocalServiceArgs& outLocalService) = 0;
        
		typedef IMVRxchangeMessage (*IMVRxchangeIncomingMessage)(const IMVRxchangeMessage& args, void* context);
		typedef void (*IMVRxchangeReturningMessage)(const IMVRxchangeMessage& outgoingMsg, const IMVRxchangeMessage& returningMsg, void* context);

		struct OnMessageArgs
		{
			OnMessageArgs()
			{
				IncomingCallback = nullptr;
				ReturningCallback = nullptr;
				Context = nullptr;
			}

			// Called, when a message is received, requires returning of an answer to send back
			// Arguments are (ReceivedMessage, Context) -> MessageToSend
			IMVRxchangeIncomingMessage  IncomingCallback;

			// Called, when an answer to a sent message is received (e.g. all MVR_*_RET message-type)
			// Arguments are (SentMessage, AnswerMessage, Context) -> void
			// [SentMessage] is a reference to the message previously sent using ->Send_message()
			// This callback can be called (possibly asynchronously) multiple times for the same sent message (e.g. when multiple stations answer)
			IMVRxchangeReturningMessage ReturningCallback; 

			// A custom context to passed to the handlers
			void*					 Context;
		};
		/**
		 * @brief Registers the message handlers
		 * 
		 * @param service 
		 * @return VCOMError 
		 */
		virtual VCOMError VCOM_CALLTYPE     OnMessage(OnMessageArgs& messageHandler) = 0;
		
		
		struct SendMessageArgs
		{
			IMVRxchangeMessage 			Message;

			// If this is set, this callback is used instead of the one set by ->OnMessage()
			IMVRxchangeReturningMessage CustomReturnCallback = nullptr;
			void*					 	CustomReturnContext  = nullptr;
		};
		virtual VCOMError VCOM_CALLTYPE     Send_message(const SendMessageArgs& messageHandler) = 0;




    };
    typedef VCOMPtr<IMVRxchangeService>	IMVRxchangeServicePtr;
    const   VWIID IID_IMVRxchangeService = { 0x706cb180, 0xcd45, 0x4a9a, {0xac, 0xfc, 0x62, 0xab, 0x5f, 0xfe, 0x37, 0x6b}};

	#endif // BUILD_MVR_XCHANGE
}
