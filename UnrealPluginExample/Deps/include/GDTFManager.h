//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Prefix/StdAfx.h"
#include "CieColor.h"
#include "GdtfError.h"
#include "Include/GDTFPrefix.h"

using namespace VectorworksMVR::Filing;
using namespace VectorworksMVR::GdtfDefines;

typedef VectorworksMVR::VWFC::Tools::VWUUID	GdtfFixtureGUID;
typedef TXString							GdtfPNGFile;
typedef TXString							Gdtf3DSFile;
typedef Sint32								StatusID;

namespace SceneData
{
	// Forward declarations
	class GdtfPhysicalEmitter; 
    typedef GdtfPhysicalEmitter*				GdtfPhysicalEmitterPtr;
    typedef std::vector<GdtfPhysicalEmitter*>	TGdtfPhysicalEmitterArray;    	

	class GdtfFeatureGroup;
	class GdtfAttribute;
	class GdtfWheel;	
	class GdtfFixture;
	class GdtfDmxLogicalChannel;
	class GdtfDmxChannel;
    class GdtfMacroDMX;   
    class GdtfMacroVisual;	
	class GdtfDmxChannelFunction;	
    class GdtfFTRDM;
    class GdtfArtNet;
    class GdtfsAcn;
    class GdtfKiNET;
    class GdtfPosiStageNet;
    class GdtfOpenSoundControl;
    class GdtfCITP;
    class GdtfDmxMode;
    class GdtfSoftwareVersionID;
    typedef std::vector<GdtfSoftwareVersionID*>	TGdtfSoftwareVersionIDArray;
    typedef GdtfSoftwareVersionID*	GdtfSoftwareVersionIDPtr;
    
    class GdtfDMXProfile; 
    typedef GdtfDMXProfile*	GdtfDMXProfilePtr;
    typedef std::vector<GdtfDMXProfile*>	TGdtfDMXProfileArray;

    class GdtfCRIGroup;  
    typedef GdtfCRIGroup*	GdtfCRIGroupPtr;
    typedef std::vector<GdtfCRIGroup*>	TGdtf_CRIGroupArray;
    
    class GdtfMeasurementPoint;
    class GdtfMeasurement; typedef std::vector<GdtfMeasurement*>	TGdtfMeasurementArray;
    
    class GdtfFilter; 
    typedef GdtfFilter*	GdtfFilterPtr;
    typedef std::vector<GdtfFilter*>	TGdtfFilterArray;

	class GdtfConnector; 
    typedef GdtfConnector*	GdtfConnectorPtr;
    typedef std::vector<GdtfConnector*>	TGdtfConnectorArray;

	class GdtfPowerConsumption; 
    typedef GdtfPowerConsumption*	GdtfPowerConsumptionPtr;
    typedef std::vector<GdtfPowerConsumption*>	TGdtfPowerConsumptionArray;


	const Sint32 kDmxBreakOverwriteValue = 0;
	//------------------------------------------------------------------------------------
	// Attributes	
	
	class GdtfObject
	{
	public:
		GdtfObject();
		virtual ~GdtfObject();
		
	private:
		void*		    fBindValue;
        IXMLFileNodePtr fNode;
		
		
	public:
		// Write
		void			WriteToNode(IXMLFileNodePtr pContainerNode);
		void			ReadFromNode(const IXMLFileNodePtr& pNode);

        void			GetNode(IXMLFileNodePtr& pNode);
		
		
		// Bind Behavoir
		void	SetBind(void* ptr);
		void*	GetBind();
		
	public:
		virtual EGdtfObjectType			GetObjectType() = 0;
		virtual TXString				GetNodeReference();
		
	protected:
		virtual	TXString				GetNodeName() = 0;
		
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	
	//------------------------------------------------------------------------------------
	// Attribute Definitions
	
	
	//------------------------------------------------------------------------------------
	// GdtfActivationGroup
	class GdtfActivationGroup : public GdtfObject
	{
	public:
        GdtfActivationGroup();
		GdtfActivationGroup(const TXString& name);
		~GdtfActivationGroup();
		
	private:
		TXString					fName;
		
		std::vector<GdtfAttribute*>	fLinkedAttributes;
		
	public:
		
	public:
        const TXString&						GetName() const;
		virtual EGdtfObjectType				GetObjectType();
		virtual TXString					GetNodeReference();
		
		void								SetName(const TXString& name);
	
		const std::vector<GdtfAttribute*>&  GetLinkedAttributes() const;
		void								AddLinkedAttribute(GdtfAttribute* attr);
		
	protected:
		virtual	TXString				    GetNodeName();
		virtual	void					    OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					    OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					    OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfActivationGroup*				GdtfActivationGroupPtr;
	typedef std::vector<GdtfActivationGroupPtr>	TGdtfActivationGroupArray;
		
	//------------------------------------------------------------------------------------
	// Feature Groups
	class GdtfFeature : public GdtfObject
	{
	public:
		GdtfFeature(GdtfFeatureGroup* parent);
		~GdtfFeature();
		
	private:
		TXString					fName;
		GdtfFeatureGroup*			fParent;
		
		std::vector<GdtfAttribute*>	fLinkedAttributes;
		
	public:
        const TXString&							GetName() const;
        GdtfFeatureGroup*						GetFeatureGroup() const;
		void									SetName(const TXString& name);
		
		const std::vector<GdtfAttribute*>&		GetLinkedAttributes() const;
		void									AddLinkedAttribute(GdtfAttribute* attr);
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};

    typedef GdtfFeature*                GdtfFeaturePtr;
	typedef std::vector<GdtfFeature*>   TGdtfFeatureArray;

	class GdtfFeatureGroup : public GdtfObject
	{
	public:
		GdtfFeatureGroup();
		GdtfFeatureGroup(const TXString& name, const TXString& prettyName);
		~GdtfFeatureGroup();
		
	private:
		TXString			fName;
		TXString			fPrettyName;
		//		
		TGdtfFeatureArray	fFeatures;

	public:
		
	public:
        const TXString&                 GetName() const;
        const TXString&                 GetPrettyName() const;
        const TGdtfFeatureArray         GetFeatureArray();
		virtual EGdtfObjectType			GetObjectType();
		
		GdtfFeature*					AddFeature(const TXString& name);
		void							SetName(const TXString& name);
		void							SetPrettyName(const TXString& prettyName);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};	
	typedef GdtfFeatureGroup*				GdtfFeatureGroupPtr;
	typedef std::vector<GdtfFeatureGroupPtr>TGdtfFeatureGroupArray;

	
	class GdtfAttribute : public GdtfObject
	{
	public:
		GdtfAttribute(const TXString& name, const TXString& prettyName);
		GdtfAttribute();
		~GdtfAttribute();
		
	private:
		TXString				fName;
		TXString				fPrettyName;
		GdtfActivationGroupPtr	fActivationGroup;
		GdtfFeaturePtr          fFeature;
        GdtfAttribute*          fMainAttribute;
        EGdtfPhysicalUnit       fPhysicalUnit;
        CCieColor               fColor;
		bool					fHasColor;
		//		
		
	private:
		// Unresolved Ptrs
		TXString fUnresolvedActGroup;
		TXString fUnresolvedFeature;
        TXString fUnresolvedMainAttrib;
		
	public:
        // Getter
        const TXString&                 GetName() const;
        const TXString&                 GetPrettyName() const;
        GdtfActivationGroupPtr          GetActivationGroup() const;
        GdtfFeaturePtr                  GetFeature() const;
        GdtfAttribute*                  GetMainAttribute();
        EGdtfPhysicalUnit               GetPhysicalUnit();
        CCieColor                       GetColor();		
		bool                       		HasColor() const;	
        // Setter
		void							SetName(const TXString& name);
		void							SetPrettyName(const TXString& name);
		void							SetFeature(GdtfFeaturePtr newFeat);
		void							SetActivationGroup(GdtfActivationGroupPtr ptr);
        void                            SetMainAttribute(GdtfAttribute* attr);
        void                            SetPhysicalUnit(EGdtfPhysicalUnit unit);
        void                            SetColor(const CCieColor & col);
		
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference();

		const TXString&					GetUnresolvedActGroup() const;
		const TXString&					GetUnresolvedFeature() const;
		const TXString&					GetUnresolvedMainAttribute() const;

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfAttribute*				GdtfAttributePtr;
	typedef std::vector<GdtfAttribute*> TGdtfAttributeArray;

	
	//------------------------------------------------------------------------------------
	// Wheel Definition
	class GdtfWheelSlotPrismFacet : public GdtfObject
	{
	public:
		GdtfWheelSlotPrismFacet();
		~GdtfWheelSlotPrismFacet();
		
	private:
		CCieColor			fColor;
		VWTransformMatrix	fTransform; // RotationMatrix
		
    public:
        CCieColor           GetColor();
        VWTransformMatrix   GetTransformMatrix();
		
		void				SetColor(const CCieColor& color);
		void				SetTransformMatrix(const VWTransformMatrix& ma);
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfWheelSlotPrismFacet*				GdtfWheelSlotPrismFacetPtr;
	typedef std::vector<GdtfWheelSlotPrismFacetPtr>	TGdtfWheelSlotPrismFacetArray;

	class GdtfWheelSlotAnimationSystem : public GdtfObject
	{
	public:
		GdtfWheelSlotAnimationSystem();
		~GdtfWheelSlotAnimationSystem();
		
	private:
		double	fP1_X;
		double	fP1_Y;
		double	fP2_X;
		double	fP2_Y;
		double	fP3_X;
		double	fP3_Y;
		double	fRadius;
		
    public:
        double GetP1_X();
        double GetP1_Y();
        double GetP2_X();
        double GetP2_Y();
        double GetP3_X();
        double GetP3_Y();
        double GetRadius();

        void SetP1_X(double p1_X);
        void SetP1_Y(double p1_Y);
        void SetP2_X(double p2_X);
        void SetP2_Y(double p2_Y);
        void SetP3_X(double p3_X);
        void SetP3_Y(double p3_Y);
        void SetRadius(double radius);
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfWheelSlotAnimationSystem*				GdtfWheelSlotAnimationSystemPtr;
	
	class GdtfWheelSlot : public GdtfObject
	{
	public:

		GdtfWheelSlot(GdtfWheel* parent);
		GdtfWheelSlot(const TXString& name, GdtfWheel* parent);

		~GdtfWheelSlot();
		
	private:
		TXString						fName;
		CCieColor						fColor;
		TXString						fGobo;
		TGdtfWheelSlotPrismFacetArray	fPrismFacts;
		GdtfWheel*                      fWheelParent;		
		TXString						fGoboFile; // MediaFileName
		GdtfFilter*						fFilter;
		TXString						fUnresolvedFilter;
		GdtfWheelSlotAnimationSystem*	fAnimationSystem;
		
	public:
		const TXString&                 GetGobo() const;
		const TXString&                 GetGoboFileFullPath();
		CCieColor                       GetColor() const;
		const TXString&                 GetName() const;
        TGdtfWheelSlotPrismFacetArray   GetPrismFacets();
		GdtfFilter*                 	GetFilter() const;
		GdtfWheelSlotAnimationSystem*	GetAnimationSystem() const;
		
		void							SetName(const TXString& name);
		void							SetGobo(const GdtfPNGFile& png);
		void							SetColor(const CCieColor& color);
		void							SetFilter(GdtfFilter* filter);
		GdtfWheelSlotPrismFacet*		AddPrismFacet();
		GdtfWheelSlotAnimationSystem*	AddAnimationSystem();

		virtual TXString				GetNodeReference();

		const TXString&                 GetUnresolvedFilter() const;
        
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfWheelSlot*					GdtfWheelSlotPtr;
	typedef std::vector<GdtfWheelSlotPtr>	TGdtfWheelSlotArray;

    class GdtfColorSpace : public GdtfObject
    {
    public:
        GdtfColorSpace();
        ~GdtfColorSpace();
    private:
        EGdtfColorSpace  fColorSpace;

        CCieColor        fRed;
        CCieColor        fGreen;
        CCieColor        fBlue;
        CCieColor        fWhitePoint;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        EGdtfColorSpace		  GetColorSpace();
        CCieColor		      GetRed();
        CCieColor             GetGreen();
        CCieColor		      GetBlue();
		CCieColor             GetWhite();
        // Setter       
        void        		            SetColorSpace(EGdtfColorSpace val);
        void                            SetRed(CCieColor val);
        void                            SetGreen(CCieColor val);
        void    		                SetBlue(CCieColor val);
		void    		                SetWhite(CCieColor val);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

    };


    class GdtfPhysicalDescriptions : public GdtfObject
    {
    public:
        GdtfPhysicalDescriptions();
        ~GdtfPhysicalDescriptions();
    private:        
        GdtfColorSpace                  fColorSpace;
        TGdtfPhysicalEmitterArray		fEmitters;
        TGdtfFilterArray                fFilters;
        TGdtfDMXProfileArray            fDmxProfiles;
        TGdtf_CRIGroupArray             fCRI_Groups;
		TGdtfConnectorArray				fConnectors;

		//Properties Collect
		TGdtfPowerConsumptionArray		fPowerConsumptions;
		double							fOperatingTemperatureLow;
		double							fOperatingTemperatureHigh;
		double							fWeight;
		double							fLegHeight;

    public:
        virtual EGdtfObjectType			GetObjectType();

    public:        
        // Getter        
        GdtfColorSpace*                  GetColorSpace();

        const TGdtfPhysicalEmitterArray& 	GetPhysicalEmitterArray();
        const TGdtfFilterArray&          	GetFilterArray();
        const TGdtfDMXProfileArray&      	GetDmxProfileArray();
        const TGdtf_CRIGroupArray&       	GetCRIGroupArray();
		const TGdtfConnectorArray&       	GetConnectorArray();
		const TGdtfPowerConsumptionArray&   GetPowerConsumptionArray();
		double								GetOperatingTemperatureLow();
		double								GetOperatingTemperatureHigh();
		double								GetWeight();
		double								GetLegHeight();

		void								SetOperatingTemperatureLow(double value);
		void								SetOperatingTemperatureHigh(double value);
		void								SetWeight(double value);
		void								SetLegHeight(double value);
        
        GdtfPhysicalEmitterPtr	        AddEmitter(const TXString& name, CCieColor color);
        GdtfFilterPtr                   AddFilter(const TXString& name,  CCieColor color);
        GdtfDMXProfilePtr               AddDmxProfile();
        GdtfCRIGroupPtr                 AddCRIGroup(double colorTsemp);
		GdtfConnectorPtr                AddConnector(const TXString& name,  const TXString& type);
		GdtfPowerConsumptionPtr			AddPowerConsumption(GdtfConnectorPtr connector);

    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfPhysicalDescriptions*	GdtfPhysicalDescriptionsPtr;	

    class GdtfFilter : public GdtfObject
    {
    public:
        GdtfFilter();
        GdtfFilter(const TXString& name, const CCieColor& col);
        ~GdtfFilter();
    private:
        TXString                        fName;
        CCieColor                       fColor;
        TGdtfMeasurementArray           fMeasurementsArray;
    public:
        virtual EGdtfObjectType		    GetObjectType();
        virtual TXString				GetNodeReference();
    public:            
        const TXString&		            GetName();
        CCieColor                       GetColor();
        const TGdtfMeasurementArray&    GetMeasurementsArray();
        // Setter       
        void						    SetName(const TXString& name);
        void                            SetColor(CCieColor val);
        GdtfMeasurement*                CreateMeasurement();
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);        
    };

	class GdtfWheel : public GdtfObject
	{
	public:
		GdtfWheel(GdtfFixture* parentFixture);
		GdtfWheel(GdtfFixture* parentFixture, const TXString& name);

		~GdtfWheel();
		
	private:
		TXString			fName;		
		TGdtfWheelSlotArray	fWheelSlots;
		
		GdtfFixture*		fParentFixture;
		
	public:
		GdtfWheelSlotPtr            AddWheelSlot(const TXString& name);
		void						SetName(const TXString& name);
		
        const TXString&             GetName() const;        

		const TGdtfWheelSlotArray&	GetWheelSlotArray() const;
		bool						IsGoboWheel() const;
		virtual TXString			GetNodeReference();
		
		
		GdtfFixture*				GetParentFixture() const;

		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfWheel*                  GdtfWheelPtr;
	typedef std::vector<GdtfWheelPtr>	TGdtfWheelArray;
	
	//------------------------------------------------------------------------------------
	// Model Defintion

	
	class GdtfModel : public GdtfObject
	{
	public:
		GdtfModel(GdtfFixture* fixture);
		GdtfModel(const TXString& name, GdtfFixture* fixture);
		~GdtfModel();
		
	private:
		TXString					fUniqueName;
		double						fLength;
		double						fWidth;
		double						fHeight;
		EGdtfModel_PrimitiveType	fPrimitiveType;
		TXString					fGeometryFile;  // FileName without the extension.
		TXString					fFullPath3DS;
        TXString					fFullPathSVG;
		//
		GdtfFixture*				fParentFixture;
		
	public:
		// Getter
        const TXString&                 GetName() const;
        double                          GetLength() const;
        double                          GetWidth() const;
        double                          GetHeight() const;
        EGdtfModel_PrimitiveType		GetPrimitiveType() const;
        //
		const TXString&					GetGeometryFileName() const;
		const TXString&					GetGeometryFile_3DS_FullPath();
        const TXString&				    GetGeometryFile_SVG_FullPath();
		// Setter
		void						    SetName(const TXString& name);
		void					    	SetLength(const double& length);
		void						    SetWidth(const double& width);
		void						    SetHeight(const double& height);
		void						    SetPrimitiveType(const EGdtfModel_PrimitiveType& type);        
		void						    SetGeometryFile(const TXString& file);
	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);	
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
				
	};
	typedef GdtfModel*					GdtfModelPtr;
	typedef std::vector<GdtfModelPtr>	TGdtfModelArray;
	
	//------------------------------------------------------------------------------------
	// Geometry Definition
	class GdtfGeometryAxis;
	class GdtfGeometryBeamFilter;
	class GdtfGeometryColorFilter;
	class GdtfGeometryGoboFilter;
	class GdtfGeometryShaperFilter;
	class GdtfGeometryLamp;
	
	class GdtfGeometry : public GdtfObject
	{
	public:

		GdtfGeometry(GdtfGeometry* parent);
		GdtfGeometry(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometry();
		
	private:
		TXString					fUniqueName;
		GdtfModelPtr				fModelReference;
		TXString					fUnresolvedModelRef;
		VWTransformMatrix			fMatrix;
		//
		std::vector<GdtfGeometry*>	fInternalGeometries;
		GdtfGeometry*				fParent;		
		
	public:
		// Getter
		const TXString&						GetName() const;
		GdtfModelPtr						GetModelRef() const;
		void								GetTransformMatrix(VWTransformMatrix& ma) const;        
        const std::vector<GdtfGeometry*>	GetInternalGeometries();
		virtual TXString					GetNodeReference();
		GdtfGeometry*						GetParentGeometry();

		// Setter	
		void								SetName(const TXString& name);
		void								SetModel(GdtfModelPtr model);
		void								SetTransformMatrix(const VWTransformMatrix& ma);
		
		GdtfGeometry*						AddGeometry(					const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryReference(			const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryShaper(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryColor(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryGobo(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryBeam(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryMediaServerCamera(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryMediaServerLayer(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryMediaServerMaster(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryWithAxis(			const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryWithLamp(			const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryDisplay(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix&	ma);

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	public:
		virtual EGdtfObjectType			GetObjectType();
		
		
	public:
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Resolve Model Ref
		TXString					GetUnresolvedModelRef() const;
		void						SetUnresolvedModelRef(GdtfModelPtr ref);
	};
	typedef GdtfGeometry*					GdtfGeometryPtr;
	typedef std::vector<GdtfGeometryPtr>	TGdtfGeometryArray;
	
	class GdtfGeometryAxis : public GdtfGeometry
	{
	public:
		GdtfGeometryAxis(GdtfGeometry* parent);
		GdtfGeometryAxis(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryAxis();
		
	private:
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfGeometryBeamFilter : public GdtfGeometry
	{
	public:
		GdtfGeometryBeamFilter(GdtfGeometry* parent);
		GdtfGeometryBeamFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryBeamFilter();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfGeometryColorFilter : public GdtfGeometry
	{
	public:
		GdtfGeometryColorFilter(GdtfGeometry* parent);
		GdtfGeometryColorFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryColorFilter();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfGeometryGoboFilter : public GdtfGeometry
	{
	public:
		GdtfGeometryGoboFilter(GdtfGeometry* parent);
		GdtfGeometryGoboFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryGoboFilter();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfGeometryShaperFilter : public GdtfGeometry
	{
	public:
		GdtfGeometryShaperFilter(GdtfGeometry* parent);
		GdtfGeometryShaperFilter(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryShaperFilter();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};

	class GdtfGeometryMediaServerCamera : public GdtfGeometry
	{
	public:
		GdtfGeometryMediaServerCamera(GdtfGeometry* parent);
		GdtfGeometryMediaServerCamera(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryMediaServerCamera();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};

	class GdtfGeometryMediaServerLayer : public GdtfGeometry
	{
	public:
		GdtfGeometryMediaServerLayer(GdtfGeometry* parent);
		GdtfGeometryMediaServerLayer(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryMediaServerLayer();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};

	class GdtfGeometryMediaServerMaster : public GdtfGeometry
	{
	public:
		GdtfGeometryMediaServerMaster(GdtfGeometry* parent);
		GdtfGeometryMediaServerMaster(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryMediaServerMaster();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};

	class GdtfGeometryDisplay : public GdtfGeometry
	{
	public:
		GdtfGeometryDisplay(GdtfGeometry* parent);
		GdtfGeometryDisplay(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);

		~GdtfGeometryDisplay();
	
	private:
		TXString	fTexture;

	public:
		virtual EGdtfObjectType			GetObjectType();
		const TXString&	GetTexture();

		void			SetTexture(const TXString& texture);

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfGeometryDisplay* GdtfGeometryDisplayPtr;
	
	class GdtfGeometryLamp : public GdtfGeometry
	{
	public:
		GdtfGeometryLamp(GdtfGeometry* parent);
		GdtfGeometryLamp(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);
        
		~GdtfGeometryLamp();
		
	private:
		EGdtfLampType	fLampType;
		double			fPowerConsuption;	// Unit ?? -> W cos phi???
		double			fLuminousIntensity;
		double			fColorTemperature;
		double			fBeamAngle;			// Unit ?? -> Degree
        double          fFieldAngle;
		double			fBeamRadius;		// Unit Meter
		double			fThrowRatio;
		double			fRectangleRatio;
		EGdtfBeamType	fBeamType;			// Unit Meter
		Sint32			fColorIndex;
		
	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
        EGdtfLampType                   GetLampType();
        double                          GetPowerConsumption();
        double                          GetLuminousIntensity();
        double                          GetColorTemperature();
        double                          GetBeamAngle();
        double                          GetFieldAngle();
        double                          GetBeamRadius();
        double                          GetThrowRatio();
        double                          GetRectangleRatio();
        EGdtfBeamType                   GetBeamType();
        Sint32                          GetColorIndex();

		// Setter
		void							SetLampType(EGdtfLampType type);
		void							SetPowerConsumption(double powerConsumption);
		void							SetLuminousIntensity(double intensity);
		void							SetColorTemperature(double temperature);
		void							SetBeamAngle(double angle);
        void                            SetFieldAngle(double angle);
        void                            SetBeamRadius(double radius);
        void                            SetThrowRatio(double ratio);
        void                            SetRectangleRatio(double ratio);
        void                            SetBeamType(EGdtfBeamType type);
        void                            SetColorIndex(Sint32 idx);
		
	protected:
        void                            InitializeMembersWithDefaultsVals();
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	
	class GdtfBreak : public GdtfObject
	{
	public:
		GdtfBreak();
		~GdtfBreak();
		
	private:
		Sint32		fDmxBreak;
		DMXAddress	fDmxAdress;
		
		
	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
        Sint32                          GetDmxBreak();
        DMXAddress                      GetDmxAddress();
		// Setter
		void							SetDmxBreak(Sint32 dmxBreak);
		void							SetDmxAddress(DMXAddress dmxAddress);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfBreak*				GdtfBreakPtr;
	typedef std::vector<GdtfBreak*> TGdtfBreakArray;
	
	class GdtfGeometryReference : public GdtfGeometry
	{
		friend GdtfGeometry;
	public:
		GdtfGeometryReference(GdtfGeometry* parent);
		GdtfGeometryReference(const TXString& name, GdtfModelPtr refToModel,const VWTransformMatrix& ma, GdtfGeometry* parent);
		~GdtfGeometryReference();
		
	private:
		TGdtfBreakArray fBreaks;
        GdtfGeometry*   fLinkedGeometry;
        
        TXString        fUnresolvedGeoRef;
		
	public:
		virtual EGdtfObjectType			GetObjectType();
        TGdtfBreakArray                 GetBreakArray();
		GdtfBreakPtr					AddBreak();

        GdtfGeometry*					GetLinkedGeometry();
        void					        SetLinkedGeometry(GdtfGeometry* ptr);
		
        const TXString&					GetUnresolvedLinkedGeometry();

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfGeometryReference*		GdtfGeometryReferencePtr;
	
	//------------------------------------------------------------------------------------
	// DMX Definition
	class GdtfDmxChannelSet : public GdtfObject
	{
	public:
		GdtfDmxChannelSet(GdtfDmxChannelFunction* parent);
		GdtfDmxChannelSet(const TXString& name, GdtfDmxChannelFunction* parent);
		~GdtfDmxChannelSet();
		
	private:
		TXString			fUniqueName;
		DmxValue			fDmxStart;
		DmxValue			fDmxEnd;
		bool				fSetPhysical;
		double				fPhysicalStart;
		double				fPhysicalEnd;
		Sint32				fWheelSlotIdx;
		bool				fValid;

		GdtfDmxChannelFunction* fParentChnlFunction; 
        GdtfDmxChannelSet*      fNextChannelSet;

	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
		//
        const TXString&                 GetName() const;
        DmxValue                        GetDmxStart() const;
        DmxValue                        GetDmxEnd() const;
        double                          GetPhysicalStart() const;
        double                          GetPhysicalEnd() const;        
		Sint32							GetWheelSlot();
		bool							GetUsePhysicalFromParent() const;
		//
		GdtfDmxChannel*					GetParentDMXChannel() const;		
		// Setter
		void							SetName(const TXString& name);
		void							SetDmxStart(DmxValue start);
		void							SetDmxEnd(DmxValue end);
		void							SetPhysicalStart(double start);
		void							SetPhysicalEnd(double end);		
		void							SetWheelSlot(Sint32 slotIndex);

        bool					        SetNextChannelSet(GdtfDmxChannelSet* next, IXMLFileNodePtr objNode);	

		bool 							IsValid();
				
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxChannelSet*				GdtfDmxChannelSetPtr;
	typedef std::vector<GdtfDmxChannelSet*>	TGdtfDmxChannelSetArray;
	
	class GdtfDmxChannelFunction : public GdtfObject
	{
	public:
		GdtfDmxChannelFunction(GdtfDmxLogicalChannel* parent);
		GdtfDmxChannelFunction(const TXString& name, GdtfDmxLogicalChannel* parent);
		~GdtfDmxChannelFunction();
	private:
		TXString				fName;
		GdtfAttribute*		    fAttribute;
		TXString				fOrignalAttribute;
		DmxValue				fDefaultValue;
		DmxValue				fAdressStart;   
		double					fPhysicalStart;
		double					fPhysicalEnd;
		double					fRealFade;
		double					fRealAcceleration;				
		GdtfWheelPtr			fOnWheel;
		GdtfPhysicalEmitter*	fEmitter;

        GdtfDmxChannel*         fModeMaster_Channel;
        GdtfDmxChannelFunction* fModeMaster_Function;
        DmxValue                fDmxModeStart;
        DmxValue                fDmxModeEnd;
        GdtfFilterPtr           fFilter;
		//
		TGdtfDmxChannelSetArray	fChannelSets;		
		
		// Unresolved Refs
		TXString				fUnresolvedAttrRef;
		TXString				fUnresolvedWheelRef;
		TXString				fUnresolvedEmitterRef;
        TXString                fUnresolvedDmxModeStart;
        TXString                fUnresolvedDmxModeEnd;
        TXString                fUnresolvedModeMaster;
        TXString                fUnresolvedFilterRef;

		// Parent Logical Channel
		GdtfDmxLogicalChannel*	fParentLogicalChannel;
        GdtfDmxChannelFunction* fNextFunction;

	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference();
		//
        const TXString&					GetName() const;
        GdtfAttribute*				    GetAttribute();
		const TXString&					GetOriginalAttribute();
		DmxValue						GetDefaultValue() const;
        DmxValue						GetStartAdress() const;
        DmxValue						GetEndAdress() const;
        double							GetPhysicalStart() const;
        double							GetPhysicalEnd() const;
        double							GetRealFade() const;
		double							GetRealAcceleration() const;
        GdtfWheelPtr					GetOnWheel() const;
        GdtfPhysicalEmitter*            GetEmitter() const;   
        GdtfFilterPtr                   GetFilter();


        GdtfDmxChannel*                 GetModeMaster_Channel() const;
        GdtfDmxChannelFunction*         GetModeMaster_Function() const;
        DmxValue                        GetModeMasterDmxStart() const;
        DmxValue                        GetModeMasterDmxEnd() const;

        size_t					        GetNumberInParent() const;
        
        //
		const TGdtfDmxChannelSetArray	GetChannelSets();		
		//
		TXString						getUnresolvedAttrRef() const;
		TXString						getUnresolvedWheelRef() const;
		TXString						getUnresolvedEmitterRef() const;
        TXString						getUnresolvedModeMasterRef() const;
        const TXString&                 getUnresolvedFilterRef();
		GdtfDmxChannel*					GetParentDMXChannel() const;
        GdtfDmxLogicalChannel*			GetParentLogicalChannel() const;
        void						    ResolveModeMasterDmx(EGdtfChannelBitResolution resolution);

        void                            SetNextFunction(GdtfDmxChannelFunction* next);
        GdtfDmxChannelFunction*         GetNextFunction() const;

		
		void							SetWheel(GdtfWheelPtr newWhl);
		void							SetName(const TXString& name);
		void							SetOriginalAttribute(const TXString& attribute);
		void							SetAttribute(GdtfAttribute* newAttr);
		void							SetDefaultValue(DmxValue defaultValue);
		void							SetStartAddress(DmxValue address);
		void							SetPhysicalStart(double start);
		void							SetPhysicalEnd(double end);
		void							SetRealFade(double fade);
		void							SetRealAcceleration(double fade);
		void							SetEmitter(GdtfPhysicalEmitter* newEmit);
        void                            SetFilter(GdtfFilterPtr val);


        void                            SetModeMaster_Channel(GdtfDmxChannel* channel);
        void                            SetModeMaster_Function(GdtfDmxChannelFunction* function);
        void                            SetModeMasterDmxStart(DmxValue start);
        void                            SetModeMasterDmxEnd(DmxValue end);   

		//
		GdtfDmxChannelSet*				AddChannelSet(const TXString& name);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxChannelFunction*					GdtfDmxChannelFunctionPtr;
	typedef std::vector<GdtfDmxChannelFunctionPtr>	TGdtfDmxChannelFuntionArray;
	
	class GdtfDmxLogicalChannel : public GdtfObject
	{
	public:
		GdtfDmxLogicalChannel(GdtfDmxChannel* parent);
		~GdtfDmxLogicalChannel();
	private:
		TXString					fName_AutoGenerated;
		GdtfAttribute*				fAttribute;
		TXString					fUnresolvedAttribRef;
		EGdtfDmxSnap				fSnap;
		EGdtfDmxMaster				fDmxMaster;
		//
		TGdtfDmxChannelFuntionArray	fFunctions;		
		
		GdtfDmxChannel*  			fParentDmxChannel;
        GdtfDmxLogicalChannel*      fNextLogicalChannel;
		double						fMoveInBlackFrames;							//is frames here the best unit
		double						fDmxChangeTimeLimit;		
		
	public:

		virtual EGdtfObjectType				GetObjectType();
		virtual TXString					GetNodeReference();
		
        const TXString&						GetName();
        GdtfAttribute*						GetAttribute();
		EGdtfDmxSnap						GetDmxSnap() const;
		EGdtfDmxMaster						GetDmxMaster() const;
        const TGdtfDmxChannelFuntionArray	GetDmxChannelFunctions();		
		TXString							GetUnresolvedAttribRef() const;
		GdtfDmxChannel*						GetParentDMXChannel() const;        
		GdtfDmxLogicalChannel*			    GetNextLogicalChannel() ;
        double                              GetMoveInBlackFrames() const;
        double								GetDmxChangeTimeLimit() const;				

		void								SetName(const TXString& name);
		void								SetAttribute(GdtfAttributePtr newAttr);
		void								SetDmxSnap(EGdtfDmxSnap snap);
		void								SetDmxMaster(EGdtfDmxMaster master);
		GdtfDmxChannelFunctionPtr			AddDmxChannelFunction(const TXString& name);
        void						        SetNextLogicalChannel(GdtfDmxLogicalChannel* next) ;
        void								SetMoveInBlackFrames(double moveInBlackFrames);
        void								SetDmxChangeTimeLimit(double changeLimit);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxLogicalChannel*				GdtfDmxLogicalChannelPtr;
	typedef std::vector<GdtfDmxLogicalChannel*>	TGdtfDmxLogicalChannelArray;
	
	class GdtfDmxChannel : public GdtfObject
	{
	public:
		GdtfDmxChannel(GdtfDmxMode* parent);
		~GdtfDmxChannel();
	private:
		TXString					fName_AutoGenerated;
		Sint32						fDmxBreak;
		DMXAddress					fCoarse;
		DMXAddress					fFine;			
		DMXAddress					fUltra;			
		DMXAddress                  fUber;
		DmxValue					fHeighlight;	bool fHeighlightNone;
		DmxValue					fDefaultValue_old;
		GdtfGeometryPtr				fGeomRef;
		TXString					fUnresolvedGeomRef;
		GdtfDmxChannelFunctionPtr	fInitialFunction;
		TXString					fUnresolvedInitialFunction;
		//
		TGdtfDmxLogicalChannelArray	fLogicalChannels;		

        //
        GdtfDmxMode*                fParent;
		
		
	public:
		virtual EGdtfObjectType				GetObjectType();
		virtual TXString					GetNodeReference();
		
        const TXString&						GetName();
        Sint32								GetDmxBreak() const;
        Sint32								GetCoarse() const;
        Sint32								GetFine() const;
        Sint32								GetUltra() const;
		Sint32								GetUber() const;
        DmxValue							GetHighlight() const;
		bool								HasHighlight() const;
		DmxValue							GetOldDefaultValue() const;
        const TGdtfDmxLogicalChannelArray	GetLogicalChannelArray();
		GdtfGeometryPtr						GetGeomRef();
		TXString							GetUnresolvedGeomRef() const;
		GdtfDmxChannelFunctionPtr			GetInitialFunction();
		TXString							GetUnresolvedInitialFunction() const;
		EGdtfChannelBitResolution			GetChannelBitResolution();
		DmxValue							GetChannelMaxDmx();
		bool								IsVirtual() const;

		void								SetName(const TXString& name);
		void								SetDmxBreak(Sint32 dmxBreak);
		void								SetDmxCoarse(Sint32 coarse);
		void								SetDmxFine(Sint32 fine);
		void								SetDmxUltra(Sint32 ultra);
		void								SetDmxUber(Sint32 uber);
		void								SetHighlight(DmxValue highlight);
		void								SetModel(GdtfModelPtr ptr);
		GdtfDmxLogicalChannel*				AddLogicalChannel();
		void								SetGeomRef(GdtfGeometryPtr newGeom);
		void								SetInitialFunction(GdtfDmxChannelFunctionPtr initialFunction);

        // Get Parent
        GdtfDmxMode*						GetParentMode();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxChannel*					GdtfDmxChannelPtr;
	typedef std::vector<GdtfDmxChannelPtr>	TGdtfDmxChannelArray;
	
	class GdtfDmxRelation : public GdtfObject
	{
	public:
		GdtfDmxRelation();
		GdtfDmxRelation(GdtfDmxChannelPtr master, GdtfDmxChannelFunctionPtr slave, const TXString& name);
		~GdtfDmxRelation();
	private:
		TXString					fUniqueName;
		GdtfDmxChannelPtr			fMasterDmxChannel;
		GdtfDmxChannelFunctionPtr	fSlaveChannelFunction;
		EGdtfDmxRelationType		fRelationType;
		
		// Pointer Resolve
		TXString					fUnresolvedMasterRef;
		TXString					fUnresolvedSlaveRef;
		
	public:
		TXString					GetUnresolvedMasterRef() const;
		TXString					GetUnresolvedSlaveRef() const;
        		
	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
        const TXString&                 GetName() const;		
        GdtfDmxChannelPtr               GetMasterChannel() const;        		
		GdtfDmxChannelFunctionPtr       GetSlaveChannel() const;
        EGdtfDmxRelationType            GetRelationType() const;
        DmxValue                        GetDmxStart() const;
        DmxValue                        GetDmxEnd() const;
		// Setter
		void							SetName(const TXString& name);
		void							SetMasterChannel(GdtfDmxChannelPtr newMaster);
		void							SetSlaveChannel(GdtfDmxChannelFunctionPtr newSlave);		
		void							SetRelationType(EGdtfDmxRelationType type);
		void							SetDmxStart(DmxValue start);
		void							SetDmxEnd(DmxValue end);
		
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxRelation*				GdtfDmxRelationPtr;
	typedef std::vector<GdtfDmxRelation*>	TGdtfDmxRelationArray;
	
	//------------------------------------------------------------------------------------
	// Macro Definitions

	class GdtfMacro : public GdtfObject
	{
	public:
		GdtfMacro();
		GdtfMacro(const TXString& name);
		~GdtfMacro();

	private:
		TXString fName;
		// Childs
		GdtfMacroDMX*    fMacroDMX;
		GdtfMacroVisual* fMacroVisual;
	public:
		virtual EGdtfObjectType			GetObjectType();
	public:
		// Getter
		const TXString&  GetName() const;
		GdtfMacroDMX*    GetMacroDMX() const;
		GdtfMacroVisual* GetMacroVisual() const;
		// Setter
		void SetName(const TXString & name);
		void SetMacroDMX(GdtfMacroDMX* val);
		void SetMacroVisual(GdtfMacroVisual* val);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfMacro*					GdtfMacroPtr;
	typedef std::vector<GdtfMacroPtr>	TGdtfMacroArray;

	class GdtfMacroDMXValue : public GdtfObject
	{
	public:
		GdtfMacroDMXValue();
		GdtfMacroDMXValue(DmxValue dmxVal, GdtfDmxChannelPtr dmxChannel);
		~GdtfMacroDMXValue();
	private:
		TXString 				funresolvedValue;
		DmxValue				fValue;
		TXString                funresolvedDMXChannel;
		GdtfDmxChannelPtr       fDMXChannel;
	public:
		virtual EGdtfObjectType			GetObjectType();

	public:
		// Getter        
		DmxValue		            GetValue() const;
		const TXString&				GetUnresolvedDMXChannel() const;
		GdtfDmxChannelPtr           GetDMXChannel() const;
		const TXString&      	   	GetUnresolvedDMXValue() const;
		// Setter       
		void						SetValue(DmxValue val);
		void                        SetDMXChannel(GdtfDmxChannelPtr chnl);

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfMacroDMXValue*	GdtfMacroDMXValuePtr;
	typedef std::vector<GdtfMacroDMXValue*>	TGdtfMacroDMXValueArray;

	class GdtfMacroDMXStep : public GdtfObject
	{
	public:
		GdtfMacroDMXStep();
		GdtfMacroDMXStep(double duration);
		~GdtfMacroDMXStep();
	private:
		double fDuration;
		// Childs
		TGdtfMacroDMXValueArray fDMXValues;
	public:
		virtual EGdtfObjectType	GetObjectType();

	public:
		// Getter        
		double GetDuration() const;
		TGdtfMacroDMXValueArray GetDMXValueArray() const;
		// Setter               
		void SetDuration(double d);
		//
		GdtfMacroDMXValuePtr AddDmxValue(DmxValue dmxVal, GdtfDmxChannelPtr dmxChannel);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfMacroDMXStep*	GdtfMacroDMXStepPtr;
	typedef std::vector<GdtfMacroDMXStep*>	TGdtfMacroDMXStepArray;

	class GdtfMacroDMX : public GdtfObject
	{
	public:
		GdtfMacroDMX();
		~GdtfMacroDMX();
	private:
		TGdtfMacroDMXStepArray fDMXSetps;
	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TGdtfMacroDMXStepArray  GetStepArray();
	public:
		GdtfMacroDMXStepPtr AddDmxStep(double& duration);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
	};

	class GdtfMacroVisualValue : public GdtfObject
	{
	public:
		GdtfMacroVisualValue();
		GdtfMacroVisualValue(DmxValue dmxVal, GdtfDmxChannelFunctionPtr channelFunctionRef);
		~GdtfMacroVisualValue();
	private:
		TXString 				  funresolvedValue;
		DmxValue				  fDmxValue;
		TXString                  fUnresolvedChannelFunctionRef;
		GdtfDmxChannelFunctionPtr fChannelFunctionRef;
	public:
		virtual EGdtfObjectType			GetObjectType();

	public:
		// Getter        
		DmxValue                     GetDmxValue() const;
		const TXString&			     GetUnresolvedChannelFunctionRef() const;
		GdtfDmxChannelFunctionPtr    GetChannelFunctionRef() const;
		const TXString&				 GetUnresolvedDMXValue() const;
		// Setter               
		void                         SetDmxValue(DmxValue val);
		void	        			 SetUnresolvedChannelFunctionRef(const TXString& ref);
		void                         SetChannelFunction(GdtfDmxChannelFunctionPtr ref);

	protected:
		virtual	TXString			GetNodeName();
		virtual	void				OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void				OnReadFromNode(const IXMLFileNodePtr& pNode);
		virtual void                OnErrorCheck(const IXMLFileNodePtr& pNode);
	};

	typedef GdtfMacroVisualValue*	GdtfMacroVisualValuePtr;
	typedef std::vector<GdtfMacroVisualValue*>	TGdtfMacroVisualValueArray;

	class GdtfMacroVisualStep : public GdtfObject
	{
	public:
		GdtfMacroVisualStep();
		~GdtfMacroVisualStep();
	private:
		double fDuration;
		double  fFade;
		double  fDelay;
		// Childs
		TGdtfMacroVisualValueArray fVisualValues;

	public:
		TGdtfMacroVisualValueArray GetVisualValueArray();
		virtual EGdtfObjectType	   GetObjectType();

	public:
		// Getter        
		double  getDuration();
		double  getFade();
		double  getDelay();
		// Setter
		void setDuration(double d);
		void setFade(double f);
		void setDelay(double d);
		//
		GdtfMacroVisualValue* AddVisualValue(DmxValue& dmxVal, GdtfDmxChannelFunctionPtr channelFunctionRef);

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfMacroVisualStep*	GdtfMacroVisualStepPtr;
	typedef std::vector<GdtfMacroVisualStep*>	TGdtfMacroVisualStepArray;

	class GdtfMacroVisual : public GdtfObject
	{
	public:
		GdtfMacroVisual();
		~GdtfMacroVisual();
	private:
		TGdtfMacroVisualStepArray	fVisualSteps;
	public:
		virtual EGdtfObjectType		GetObjectType();

	public:
		TGdtfMacroVisualStepArray	GetVisualStepArray();

		GdtfMacroVisualStepPtr		AddVisualStep();

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfMacroVisual*	GdtfMacroVisualPtr;

	class GdtfDmxMode : public GdtfObject
	{
	public:
		GdtfDmxMode(GdtfFixture* fixture, const TXString& name);
		~GdtfDmxMode();
		
	private:
		TXString				fName;			
		GdtfGeometryPtr			fGeomRef;
		GdtfFixture*			fFixture;
		TXString				fUnresolvedGeomRef;
		//
		TGdtfDmxChannelArray	fChannels;
		TGdtfDmxRelationArray	fRelations;
		TGdtfMacroArray			fMacros;


	public:		
		const TXString&				GetModeName() const;
		const TGdtfDmxChannelArray	GetChannelArray() const;		
		GdtfDmxChannelPtr			GetMasterByRef(const TXString& ref) const;
		GdtfDmxChannelFunctionPtr	GetSlaveByRef(const TXString& ref) const;
		GdtfGeometryPtr				GetGeomRef();
		TGdtfDmxChannelArray		GetChannelsForGeometry(GdtfGeometryPtr geometry);
		
        const TXString&				GetUnresolvedGeomRef();
		const TGdtfDmxRelationArray GetDmxRelations();
		size_t     					GetFootPrintForBreak(size_t breakId);
		TSint32Array				GetBreakArray() const;
		void						GetAddressesFromChannel(TDMXAddressArray& addresses, GdtfDmxChannel* channel, DMXAddress offset) const;
		const TGdtfMacroArray		GetDmxMacrosArray();

		
		void						SetName(const TXString& name);
		GdtfDmxChannelPtr			AddChannel();
		void						SetGeomRef(GdtfGeometryPtr ptr);
		void						SetModel(GdtfGeometryPtr ptr);
		GdtfDmxRelation*			AddDmxRelation(GdtfDmxChannel* master, GdtfDmxChannelFunctionPtr slave, const TXString &name);
		GdtfMacroPtr				AddMacro(const TXString &name);
		
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxMode*				GdtfDmxModePtr;
	typedef std::vector<GdtfDmxMode*>	TGdtfDmxModeArray;	
	
	//------------------------------------------------------------------------------------
	// GdtfRevision Definition
	class GdtfRevision : public GdtfObject
	{
	public:
		GdtfRevision();
		~GdtfRevision();
		
	private:
		TXString	fText;
		STime       fDateS;
		size_t		fUserId;
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	public:
        // Getter
		const STime&    GetDate() const;
		const TXString&	GetText() const;
		size_t			GetUserId() const;
        // Setter        
		void			SetText(const TXString& text);
        void            SetDate(const STime& date);
		void 			SetUserId(size_t userId);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfRevision*	GdtfRevisionPtr;
	typedef std::vector<GdtfRevision*>	TGdtfRevisionArray;
	
    //------------------------------------------------------------------------------------
    // Protocolls Definitions
    
    class GdtfProtocols : public GdtfObject
    {
    public:
        GdtfProtocols();
        ~GdtfProtocols();
    private:
        // Childs
        GdtfFTRDM*                  fRDM;             
        GdtfArtNet*                 fArtNet;          
        GdtfsAcn*                   fsACN;            
        GdtfKiNET*                  fKiNET;           
        GdtfPosiStageNet*           fPosiStageNet;    
        GdtfOpenSoundControl*       fOpenSoundControl;
        GdtfCITP*                   fCITP;            
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        GdtfFTRDM*                  GetRDM();              
        GdtfArtNet*                 GetArtNet();            
        GdtfsAcn*                   Get_sACN();              
        GdtfKiNET*                  GetKiNET();             
        GdtfPosiStageNet*           GetPosiStageNet();      
        GdtfOpenSoundControl*       GetOpenSoundControl();  
        GdtfCITP*                   GetCITP();              
        // Setter    
        GdtfFTRDM*                  CreateRDM();
        void                        SetArtNet(GdtfArtNet* val);
        void                        Set_sACN(GdtfsAcn* val);
        void                        SetKiNET(GdtfKiNET* val);
        void                        SetPosiStageNet(GdtfPosiStageNet* val);
        void                        SetOpenSoundControl(GdtfOpenSoundControl* val);
        void                        SetCITP(GdtfCITP* val);

    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfProtocols*	GdtfProtocolsPtr;    

    class GdtfFTRDM : public GdtfObject
    {
    public:
        GdtfFTRDM();
        GdtfFTRDM(size_t manufacturerID, size_t deviceModelID);
        ~GdtfFTRDM();
    private:
        // Attributes
        size_t        fManufacturerID;  // Manufacturer ESTA ID; Size: 2 bytes
        size_t        fDeviceModelID;   // Unique device model ID; Size: 2 bytes        
        
        TGdtfSoftwareVersionIDArray     fSoftwareVersionIDArray;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter
        size_t                              GetManufacturerID() const;
        size_t                              GetDeviceModelID()  const;
        const TGdtfSoftwareVersionIDArray&  GetSoftwareVersIDs() const;        
        // Setter
        void                                SetManufacturerID(size_t val);
        void                                SetDeviceModelID(size_t val);
        GdtfSoftwareVersionIDPtr            AddSoftwareVersID(size_t value);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfFTRDM*	GdtfFTRDMPtr;    

    class GdtfDMXPersonality : public GdtfObject
    {
    public:
        GdtfDMXPersonality();
        GdtfDMXPersonality(size_t value, GdtfDmxModePtr dmxMode);
        ~GdtfDMXPersonality();
    private:        
        size_t          fValue;
        TXString        fDMXMode_Unresolved;
        GdtfDmxModePtr  fDMXMode;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        size_t		                    GetValue() const;
        GdtfDmxModePtr		            GetDMXMode() const;
        const TXString&				    GetUnresolvedDMXMode() const;
        // Setter       
        void                            SetValue(size_t val);
        void						    SetDMXMode(GdtfDmxModePtr mode);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfDMXPersonality*	GdtfDMXPersonalityPtr;
    typedef std::vector<GdtfDMXPersonality*>	TGdtfDMXPersonalityArray;
    

    class GdtfSoftwareVersionID : public GdtfObject
    {
    public:
        GdtfSoftwareVersionID();
        GdtfSoftwareVersionID(size_t value);
        ~GdtfSoftwareVersionID();
    private:
        size_t                      fValue;        
        TGdtfDMXPersonalityArray    fDmxPersonalityArray;

    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        size_t		                    GetValue() const;
        const TGdtfDMXPersonalityArray& GetDMXPersonalityArray();
        // Setter       
        void						    SetValue(size_t val);
        GdtfDMXPersonalityPtr           AddDMXPersonality(size_t value, GdtfDmxModePtr dmxMode);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfSoftwareVersionID*	GdtfSoftwareVersionIDPtr;
    typedef std::vector<GdtfSoftwareVersionID*>	TGdtfSoftwareVersionIDArray;


    class GdtfArtNet : public GdtfObject
    {
    public:
        GdtfArtNet();
        ~GdtfArtNet();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        //...
        // Setter       
        // ...
    protected:
        virtual	TXString				    GetNodeName();
        // virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        // virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfArtNet*	GdtfArtNetPtr;
    
    class GdtfsAcn : public GdtfObject
    {
    public:
        GdtfsAcn();
        ~GdtfsAcn();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        // virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        // virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfsAcn*	GdtfsAcnPtr;    

    class GdtfKiNET : public GdtfObject
    {
    public:
        GdtfKiNET();
        ~GdtfKiNET();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        //virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        //virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfKiNET*	GdtfKiNETPtr;

    class GdtfPosiStageNet : public GdtfObject
    {
    public:
        GdtfPosiStageNet();
        ~GdtfPosiStageNet();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        //virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        //virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfPosiStageNet*	GdtfPosiStageNetPtr;

    class GdtfOpenSoundControl : public GdtfObject
    {
    public:
        GdtfOpenSoundControl();
        ~GdtfOpenSoundControl();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        //virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        //virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfOpenSoundControl*	GdtfOpenSoundControlPtr;

    class GdtfCITP : public GdtfObject
    {
    public:
        GdtfCITP();
        ~GdtfCITP();
    private:
        // Atributes
        // TODO: This TYPE not defined in the docu to this day(26.09.18). Implement later.
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        // ...
        // Setter       
        // ...
    protected:
        virtual	TXString				GetNodeName();
        //virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        //virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfCITP*	GdtfCITPPtr;

	//------------------------------------------------------------------------------------
	// GdtfUserPreset Definition
	class GdtfUserPreset : public GdtfObject
	{
	public:
		GdtfUserPreset();
		~GdtfUserPreset();
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfUserPreset*					GdtfUserPresetPtr;
	typedef std::vector<GdtfUserPresetPtr>	TGdtfUserPresetArray;
	

	class GdtfMeasurementPoint : public GdtfObject
	{
	public:
		GdtfMeasurementPoint();
		~GdtfMeasurementPoint();
		
	private:
		double			fWaveLength;	// Unit nm
		double			fEngergy;		// Unit W/m^2*/nm		
		
	public:
		virtual EGdtfObjectType			GetObjectType();
        double                          GetWavelength();
        double                          GetEnergy();
		
		void							SetWavelength(double wavelength);
		void							SetEnergy(double energy);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfMeasurementPoint*				GdtfMeasurementPointPtr;
	typedef std::vector<GdtfMeasurementPoint*>	TGdtfMeasurementPointArray;
    	

    class GdtfMeasurement : public GdtfObject
    {
    public:
        GdtfMeasurement(bool forFilter);
        ~GdtfMeasurement();
    private:
        double                      fPhysical;
        double                      fLuminousIntensity;
        double                      fTransmission;
        EGdtfInterpolationTo        fInterpolationTo;
		bool						fIsForFilter;


        TGdtfMeasurementPointArray  fMeasurementPoints;
    public:
        virtual EGdtfObjectType		GetObjectType();

    public:
        // Getter                
        double                             GetPhysical();
        double                             GetLuminousIntensity();
        double                             GetTransmission();
        EGdtfInterpolationTo               GetInterpolationTo();
        const TGdtfMeasurementPointArray&  GetMeasurementPointsArray();
        // Setter               
        void                               SetPhysical(double val);
        void                               SetLuminousIntensity(double val);
        void                               SetTransmission(double val);
        void                               SetInterpolationTo(EGdtfInterpolationTo val);
        GdtfMeasurementPoint*              CreateMeasurementPoint();
    protected:
        virtual	TXString				   GetNodeName();
        virtual	void					   OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					   OnReadFromNode(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfMeasurement*	GdtfMeasurementPtr;
        
	//------------------------------------------------------------------------------------
	// GdtfPhysicalDescription Definition
	class GdtfPhysicalEmitter : public GdtfObject
	{
	public:
		GdtfPhysicalEmitter();
		GdtfPhysicalEmitter(const TXString& name, CCieColor color);
		~GdtfPhysicalEmitter();
		
	private:
		TXString					fName;
		CCieColor					fColor;
        double                      fDominantWaveLength;
        TXString                    fDiodePart;
		//		
		TGdtfMeasurementArray	fMeasurements; 
		
	public:
        // Getter
		virtual EGdtfObjectType				GetObjectType();
        const TXString&						GetName() const;
        CCieColor							GetColor() const;        
		virtual TXString					GetNodeReference();
        const TXString&                     GetDiodePart();
        double                              GetDominantWaveLength();
        const TGdtfMeasurementArray         GetMeasurements();
		// Setter
		void							SetName(const TXString& name);
		void							SetColor(CCieColor color);
        void                            SetDiodePart(const TXString& val);
        void                            SetDominantWaveLength(double val);

        GdtfMeasurement*                AddMeasurement();

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	
    class GdtfCRI : public GdtfObject
    {
    public:
        GdtfCRI();
        GdtfCRI(EGdtfColorSample ces, Uint8 cri);
        ~GdtfCRI();
    private:
        // Attributes
        EGdtfColorSample	fCES;
        Uint8           	fCRI;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter                
        EGdtfColorSample 	GetColorSample() const;
        Uint8				GetColorRenderingIndex() const;
        // Setter       
        void SetColorSample(EGdtfColorSample val);
        void SetColorRenderingIndex(Uint8 val);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };
    typedef GdtfCRI*	GdtfCRIPtr;
    typedef std::vector<GdtfCRI*>	TGdtf_CRIArray;

    class GdtfCRIGroup : public GdtfObject
    {
    public:
        GdtfCRIGroup();
        GdtfCRIGroup(double colorTsemp);
        ~GdtfCRIGroup();
    private:
        // Attributes
        double fColorTemperature; // Color temperature; Default value : 6000; Unit: kelvin
		
		// Childs
        TGdtf_CRIArray fCRI_Array;
    public:
        virtual EGdtfObjectType			GetObjectType();

    public:
        // Getter        
        double         GetColorTemperature() const;
        TGdtf_CRIArray GetCRI_Array() const;
        // Setter       
        void            SetColorTemperature(double val);
        GdtfCRIPtr      Add_CRI(EGdtfColorSample ces, Sint32 colorTemp);
    protected:
        virtual	TXString				GetNodeName();
        virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
        virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual void                    OnErrorCheck(const IXMLFileNodePtr& pNode);
    };

	class GdtfDMXProfile : public GdtfObject
	{
	public:
		GdtfDMXProfile();
		~GdtfDMXProfile();
	private:
		// Attributes
	public:
		virtual EGdtfObjectType			GetObjectType();

	public:
		// Getter        
		//
		// Setter       
		//
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
	};

	class GdtfConnector : public GdtfObject
	{
	public:
		GdtfConnector();
		GdtfConnector(const TXString& name, const TXString& type);
		~GdtfConnector();
		
	private:
		TXString	fName;
		TXString	fType;
		Uint32		fDmxBreak;
		Sint32		fGender;
        double		fLength;
		
	public:
        // Getter
		virtual EGdtfObjectType	GetObjectType();
		virtual TXString		GetNodeReference();

        const TXString&			GetName() const;
		const TXString&			GetType() const;
		Uint32					GetDmxBreak();
		Sint32					GetGender();
		double					GetLength();
        
		// Setter
		void	SetName(const TXString& name);
		void	SetType(const TXString& type);
		void	SetDmxBreak(Uint32 dmxBreak);
		void	SetGender(Sint32 gender);
        void	SetLength(double length);

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};

	class GdtfPowerConsumption : public GdtfObject
	{
	public:
		GdtfPowerConsumption();
		GdtfPowerConsumption(GdtfConnector* connector);
		~GdtfPowerConsumption();
		
	private:
        double			fValue;
		double			fPowerFactor;
		GdtfConnector*	fConnector;
		TXString		fUnresolvedConnector;
		double			fVoltageLow;
		double			fVoltageHigh;
		double			fFrequencyLow;
		double			fFrequencyHigh;
		
	public:
        // Getters
		virtual EGdtfObjectType	GetObjectType();

		double			GetValue();
		double			GetPowerFactor();
		GdtfConnector*	GetConnector();
		const TXString& GetUnresolvedConnector();
		double			GetVoltageLow();
		double			GetVoltageHigh();
		double			GetFrequencyLow();
		double			GetFrequencyHigh();
        
		// Setters
		void	SetValue(double value);
        void	SetPowerFactor(double powerFactor);
        void	SetConnector(GdtfConnector* connector);
        void	SetVoltageLow(double voltageLow);
        void	SetVoltageHigh(double voltageHigh);
        void	SetFrequencyLow(double frequencyLow);
        void	SetFrequencyHigh(double frequencyHigh);

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void					OnErrorCheck(const IXMLFileNodePtr& pNode);

	};
	
	//------------------------------------------------------------------------------------
	// GdtfFixture Definition
	class GdtfFixture : public GdtfObject
	{
	public:
		GdtfFixture();
		~GdtfFixture();
		
	private:
		//------------------------------------------------
		// Parameters for a GdtfFixture
		TXString		            fName;
		TXString		            fShortName;
		TXString		            fLongName;
		TXString		            fManufacturer;
		TXString		            fFixtureTypeDescription;
		GdtfFixtureGUID	            fGuid;
		TXString		            fTumbnailName;
		bool						fCanHaveChildren;
		TXString		            fTumbnailFullPath_PNG;
        TXString		            fTumbnailFullPath_SVG;
		
        GdtfFixtureGUID	            fLinkedGuid;
		bool			            fHasLinkedGuid;
        
        GdtfProtocols				fProtocollContainer;
		//------------------------------------------------
		// Storage
        
        // This are not seperated here and placed in the AttributeDefinitions node
        // there is no special class for this
		TGdtfActivationGroupArray		fActivationGroups;
		TGdtfFeatureGroupArray			fFeatureGroups;
		TGdtfAttributeArray				fAttributes;
        
		TGdtfWheelArray					fWheels;
		TGdtfModelArray					fModels;
		TGdtfGeometryArray				fGeometries;
		TGdtfDmxModeArray				fDmxModes;
		TGdtfRevisionArray				fRevisions;
		TGdtfUserPresetArray			fPresets;
        GdtfPhysicalDescriptions        fPhysicalDesciptions; 
		//------------------------------------------------
		// Reading support
		TVWArray_IFileIdentifier		fLocalFiles;
		TXStringArray 					fLocalFilesFullPath;
		bool							fReaded;
		IFolderIdentifierPtr			fWorkingFolder;
        TGdtfParsingErrorArray          fParsingErrors;


		// 
		GdtfAttributePtr 				fNoFeature;

	public:
        static void                     AddError(const GdtfParsingError& error);
        static TGdtfParsingErrorArray*  __ERROR_CONTAINER_POINTER;
        TGdtfParsingErrorArray&         GetParsingErrorArray();
        
        TXString                        GetFullThumbNailPath(const TXString & fileExtension);
		size_t 	GetAttachedFileCount();
		bool	GetAttachedFileCountAt(size_t at, TXString*& outFile);

	private:
        TGdtfParsingErrorArray          fErrorContainer;
  
	public:
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Getter
		const TXString&		        GetName() const;
        const TXString&		        GetShortName() const;
		const TXString&		        GetLongName() const;
        const TXString&		        GetManufacturer() const;
        const TXString&		        GetFixtureTypeDescription() const;
        GdtfFixtureGUID		        GetGuid() const;
		GdtfFixtureGUID		        GetLinkedGuid() const;
		bool				        HasLinkedGuid() const;
        const TXString&             GetThumbnailName() const;
		bool						GetCanHaveChildren() const;
		const GdtfPNGFile&          GetPNGThumnailFullPath();
        const TXString&             GetSVGThumnailFullPath();
        GdtfProtocols&				GetProtocollContainer();
        GdtfPhysicalDescriptions&   GetPhysicalDesciptionsContainer();

		;
        
        // Setter
		void				SetName(const TXString& name);
		void				SetShortName(const TXString& shortName);
		void				SetLongName(const TXString& longName);
		void				SetManufacturer(const TXString& manu);
		void				SetFixtureTypeDescription(const TXString& desc);
		void				SetGuid(const VWFC::Tools::VWUUID& uuid);
		void				SetLinkedGuid(const VWFC::Tools::VWUUID& uuid);
		void				SetThumbnailName(const TXString& fileName);
		void				SetCanHaveChildren(bool canHaveChildren);


	public:
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Add calls
		GdtfRevisionPtr			AddRevision(const TXString& text, const STime& date);
		GdtfAttributePtr		AddAttribute(const TXString& name, const TXString& prettyName);
		
		GdtfModelPtr			AddModel(const TXString& name);
		GdtfGeometryPtr			AddGeometry(					const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryReference(			const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryShaper(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryColor(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryGobo(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryBeam(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryMediaServerCamera(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryMediaServerLayer(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryMediaServerMaster(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryWithAxis(			const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryWithLamp(			const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryDisplay(				const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix&	ma);

		GdtfWheelPtr			AddWheel(TXString name);
		GdtfDmxModePtr			AddDmxMode(const TXString& name);
		GdtfMacroPtr			AddMacro(const TXString& name);        

		GdtfUserPresetPtr		AddUserPreset();
		GdtfFeatureGroupPtr		AddFeatureGroup(const TXString& name, const TXString& prettyName);
		GdtfActivationGroupPtr	AddActivationGroup(const TXString& name);        

		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Read calls
		const TGdtfWheelArray&                  GetWheelArray();
		const TGdtfGeometryArray&               GetGeometryArray();
        const TGdtfActivationGroupArray&        GetActivationGroupArray();
        const TGdtfFeatureGroupArray&           GetFeatureGroupArray();
        const TGdtfAttributeArray&              GetAttributeArray();
        const TGdtfModelArray&                  GetModelArray();
        const TGdtfDmxModeArray&                GetDmxModeArray();
        const TGdtfRevisionArray&               GetRevisionArray();
        const TGdtfUserPresetArray&             GetPresetArray();
        const TGdtfMacroArray&                  GetMacroArray();
        
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
        virtual	void			        OnErrorCheck(const IXMLFileNodePtr& pNode);

		void            			CreateNoFeatureAttribute();      
        GdtfAttributePtr            getAttributeByRef(const TXString& ref);
        GdtfWheelPtr                getWheelByRef(const TXString& ref);	
        GdtfPhysicalEmitterPtr      getEmiterByRef(const TXString& ref);
        GdtfDmxChannelFunctionPtr   getDmxFunctionByRef(const TXString& ref, GdtfDmxModePtr mode);
		GdtfDmxChannelPtr           getDmxChannelByRef(const TXString& ref, GdtfDmxModePtr mode);
        GdtfFilterPtr               getFilterByRef(const TXString& ref);
		GdtfConnectorPtr            getConnectorByRef(const TXString& ref);

		//
		void AutoGenerateNames(GdtfDmxModePtr dmxMode);
		
		// Resolve References		
		void ResolveAllReferences();
		void ResolveGeometryRefs();
		void ResolveGeometryRefs_Recursive(GdtfGeometryPtr geometry);
		
		void            ResolveAttribRefs();		
		void            ResolveWheelSlots();
		void            ResolvePowerConsumptions();
		void            ResolveDmxModeRefs();
        void            ResolveDMXModeMasters();       
        void            ResolveDMXPersonalityRefs();
		void            ResolveDmxRelationRefs(GdtfDmxModePtr dmxMode);
		void            ResolveDmxChannelRefs(GdtfDmxModePtr dmxMode);
		GdtfGeometryPtr ResolveGeometryRef(const TXString& unresolvedGeoRef, const TGdtfGeometryArray& geometryArray);
		GdtfDmxModePtr  ResolveDMXMode(const TXString & unresolvedDMXmode);

		void ResolveDmxLogicalChanRefs(GdtfDmxChannelPtr dmxChnl);
		void ResolveDmxChanelFunctionRefs(GdtfDmxLogicalChannelPtr dmxLogChnl);
		void ResolveMacroRefs(GdtfDmxModePtr dmxMode);
	
	private:
		void CheckForMissingModeMasters();
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		
	private:
		bool							ImportFromZip(IZIPFilePtr& zipfile);
		void 							PrepareWorkingFolder(TXString folderName);

	public:
		bool							ExportToFile(IZIPFilePtr& zipfile);
		void							ImportFromFile(IFileIdentifierPtr inZipFile, const TXString& folder);
		void							ImportFromBuffer(const char*buffer, size_t length, const TXString& folder);


		bool							IsReaded();
		void							GetWorkingFolder(IFolderIdentifierPtr& folder);        
	};    
 
}