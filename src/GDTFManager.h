//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once
#include "Prefix/StdAfx.h"
#include "CieColor.h"
#include "Include/GDTFPrefix.h"

using namespace VectorWorks::Filing;
using namespace VectorworksMVR::GdtfDefines;

typedef VWFC::UUID	GdtfFixtureGUID;
typedef TXString	GdtfPNGFile;
typedef TXString	Gdtf3DSFile;

namespace SceneData
{
	// Forward declarations
	class GdtfPhysicalEmitter;
	class GdtfFeatureGroup;
	class GdtfAttribute;
	class GdtfWheel;	
	class GdtfFixture;
	class GdtfDmxLogicalChannel;
	class GdtfDmxChannel;
	class GdtfDmxChannelFunction;
	
	//------------------------------------------------------------------------------------
	// Attributes
	
	
	class GdtfObject
	{
	public:
		GdtfObject();
		virtual ~GdtfObject();
		
	private:
		void*		fBindValue;
		
		
	public:
		// Write
		void			WriteToNode(IXMLFileNodePtr pContainerNode);
		void			ReadFromNode(const IXMLFileNodePtr& pNode);
		
		
		// Bind Behavoir
		void	SetBind(void* ptr);
		void*	GetBind();
		
	public:
		virtual EGdtfObjectType			GetObjectType() = 0;
		virtual TXString				GetNodeReference() const;
		
	protected:
		virtual	TXString				GetNodeName() = 0;
		
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);

		
	};
	
	//------------------------------------------------------------------------------------
	// Attributes
	
	
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
		virtual TXString					GetNodeReference() const;
		
		void								SetName(const TXString& name);
	
		const std::vector<GdtfAttribute*>&  GetLinkedAttributes() const;
		void								AddLinkedAttribute(GdtfAttribute* attr);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);

		
		
	};
	typedef GdtfActivationGroup*				GdtfActivationGroupPtr;
	typedef std::vector<GdtfActivationGroupPtr>	TGdtfActivationGroupArray;
		
	//------------------------------------------------------------------------------------
	// Feature
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
		void									SetName(const TXString& name);
		
		const std::vector<GdtfAttribute*>&		GetLinkedAttributes() const;
		void									AddLinkedAttribute(GdtfAttribute* attr);
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference() const;
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
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
        // Setter
		void							SetName(const TXString& name);
		void							SetPrettyName(const TXString& name);
		void							SetFeature(GdtfFeaturePtr newFeat);
		void							SetActivationGroup(GdtfActivationGroupPtr ptr);
        void                            SetMainAttribute(GdtfAttribute* attr);
        void                            SetPhysicalUnit(EGdtfPhysicalUnit unit);
        void                            SetColor(const CCieColor & col);
		
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference() const;

		const TXString&					GetUnresolvedActGroup() const;
		const TXString&					GetUnresolvedFeature() const;
		const TXString&					GetUnresolvedMainAttribute() const;

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
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
		
	};
	typedef GdtfWheelSlotPrismFacet*				GdtfWheelSlotPrismFacetPtr;
	typedef std::vector<GdtfWheelSlotPrismFacetPtr>	TGdtfWheelSlotPrismFacetArray;
	
	//------------------------------------------------------------------------------------
	// Wheel Definition
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
		
	public:
		const TXString&                 GetGobo() const;
		const TXString&                 GetGoboFileFullPath();
		CCieColor                       GetColor() const;
		const TXString&                 GetName() const;
        bool                            GetPrintcolor();
        TGdtfWheelSlotPrismFacetArray   GetPrismFacets();
		
		void							SetName(const TXString& name);
		void							SetGobo(const GdtfPNGFile& png);
		void							SetColor(const CCieColor& color);
		GdtfWheelSlotPrismFacet*		AddPrismFacet();
		void							SetPrintColor(const bool& print);

		virtual TXString				GetNodeReference() const;

        
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfWheelSlot*					GdtfWheelSlotPtr;
	typedef std::vector<GdtfWheelSlotPtr>	TGdtfWheelSlotArray;
	
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

        const TGdtfWheelSlotArray   GetWheelSlotArray();
		
		const TGdtfWheelSlotArray&	GetWheelSlotArray() const;
		bool						IsGoboWheel() const;
		virtual TXString			GetNodeReference() const;
		
		
		GdtfFixture*				GetParentFixture() const;

		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
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
		Gdtf3DSFile					fGeometryFile;
		TXString					fFullPath;
		//
		GdtfFixture*				fParentFixture;
		
	public:
		// Getter
        const TXString&                 GetName() const;
        double                          GetLength() const;
        double                          GetWidth() const;
        double                          GetHeight() const;
        EGdtfModel_PrimitiveType		GetPrimitiveType() const;
		const TXString&					GetGeometryFile() const;
		const TXString&					GetGeometryFileFullPath();
		// Setter
		void							SetName(const TXString& name);
		void							SetLength(const double& length);
		void							SetWidth(const double& width);
		void							SetHeight(const double& height);
		void							SetPrimitiveType(const EGdtfModel_PrimitiveType& type);
		void							SetGeometryFile(const Gdtf3DSFile& file);
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference() const;
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);	
				
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
		virtual TXString					GetNodeReference() const;
		// Setter	
		void								SetName(const TXString& name);
		void								SetModel(GdtfModelPtr model);
		void								SetTransformMatrix(const VWTransformMatrix& ma);
		
		GdtfGeometry*						AddGeometry(		const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryReference(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryShaper(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryColor(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryGobo(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryBeam(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryWithAxis(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometry*						AddGeometryWithLamp(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
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
		double	fAngleStart;	// Unit ?? -> Degree
		double	fAngleEnd;		// Unit ?? -> Degree
		double	fSpeed;			// Unit ?? -> mm/s
		
	public:
		virtual EGdtfObjectType			GetObjectType();
        double                          GetStartAngle();
        double                          GetEndAngle();
        double                          GetSpeed();
		
		void							SetStartAngle(double start);
		void							SetEndAngle(double end);
		void							SetSpeed(double speed);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
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
	};
	
	
	
	
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
        void                            SetBeamType(EGdtfBeamType type);
        void                            SetColorIndex(Sint32 idx);
		
	protected:
        void                            InitializeMembersWithDefaultsVals();
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
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
		
		
	public:
		virtual EGdtfObjectType			GetObjectType();
        TGdtfBreakArray                 GetBreakArray();
		GdtfBreakPtr					AddBreak();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
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
		DMXAddress			fDmxStart;
		DMXAddress			fDmxEnd;
		double				fPhysicalStart;	// Units?????
		double				fPhysicalEnd;	// Units?????		
		Sint32				fWheelSlotIdx;

		GdtfDmxChannelFunction* fParentChnlFunction; 

	public:
		// Getter
		virtual EGdtfObjectType			GetObjectType();
		//
        const TXString&                 GetName() const;
        DmxValue                        GetDmxStart() const;
        DMXAddress                      GetDmxEnd() const;
        double                          GetPhysicalStart() const;
        double                          GetPhysicalEnd() const;        
		Sint32							GetWheelSlot();
		//
		GdtfDmxChannel*					GetParentDMXChannel() const;		
		// Setter
		void							SetName(const TXString& name);
		void							SetDmxStart(DmxValue start);
		void							SetDmxEnd(DMXAddress end);
		void							SetPhysicalStart(double start);
		void							SetPhysicalEnd(double end);		
		void							SetWheelSlot(Sint32 slotIndex);
				
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
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
		DmxValue				fAdressStart;   // This is DMXFrom
		double					fPhysicalStart;	// Units?????
		double					fPhysicalEnd;	// Units?????
		double					fRealFade;		// Units?????		
		GdtfWheelPtr			fOnWheel;
		GdtfPhysicalEmitter*	fEmitter;
		EGDTFDmxInvert			fDmxInvert;
		EGDTFEncoderInvert		fEncoderInvert;
		//
		TGdtfDmxChannelSetArray	fChannelSets;		
		
		// Unresolved Refs
		TXString				fUnresolvedAttrRef;
		TXString				fUnresolvedWheelRef;
		TXString				fUnresolvedEmitterRef;
		
		// Parent Logical Channel
		GdtfDmxLogicalChannel*	fParentLogicalChannel;

	public:
		virtual EGdtfObjectType			GetObjectType();
		virtual TXString				GetNodeReference() const;
		//
        const TXString&					GetName() const;
        GdtfAttribute*				    GetAttribute();
		const TXString&					GetOriginalAttribute();
        DmxValue						GetStartAdress() const;
        double							GetPhysicalStart() const;
        double							GetPhysicalEnd() const;
        double							GetRealFade() const;        
        GdtfWheelPtr					GetOnWheel() const;
        GdtfPhysicalEmitter*            GetEmitter() const;
        EGDTFDmxInvert                  GetDmxInvert()const;
        EGDTFEncoderInvert              GetEncoderInvert() const;        
        
        //
		const TGdtfDmxChannelSetArray	GetChannelSets();		
		//
		TXString						getUnresolvedAttrRef() const;
		TXString						getUnresolvedWheelRef() const;
		TXString						getUnresolvedEmitterRef() const;
		GdtfDmxChannel*					GetParentDMXChannel() const;

		
		void							SetWheel(GdtfWheelPtr newWhl);
		void							SetName(const TXString& name);
		void							SetOriginalAttribute(const TXString& attribute);
		void							SetAttribute(GdtfAttribute* newAttr);		
		void							SetStartAddress(DmxValue address);
		void							SetPhysicalStart(double start);
		void							SetPhysicalEnd(double end);
		void							SetRealFade(double fade);				
		void							SetEmitter(GdtfPhysicalEmitter* newEmit);
        void                            SetDmxInvert(EGDTFDmxInvert dmxInvert);
        void                            SetEncoderInvert(EGDTFEncoderInvert encoderInvert);        

		//
		GdtfDmxChannelSet*				AddChannelSet(const TXString& name);
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfDmxChannelFunction*					GdtfDmxChannelFunctionPtr;
	typedef std::vector<GdtfDmxChannelFunctionPtr>	TGdtfDmxChannelFuntionArray;
	
	class GdtfDmxLogicalChannel : public GdtfObject
	{
	public:
		GdtfDmxLogicalChannel(GdtfDmxChannel* parent);
		GdtfDmxLogicalChannel(const TXString& name, GdtfDmxChannel* parent);
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
		
	public:

		virtual EGdtfObjectType				GetObjectType();
		virtual TXString					GetNodeReference() const;
		
        const TXString&						GetName() const;
        GdtfAttribute*						GetAttribute();
		EGdtfDmxSnap						GetDmxSnap() const;
		EGdtfDmxMaster						GetDmxMaster() const;
        const TGdtfDmxChannelFuntionArray	GetDmxChannelFunctions();		
		TXString							GetUnresolvedAttribRef() const;

		GdtfDmxChannel*						GetParentDMXChannel() const;
		
		void								SetName(const TXString& name);
		void								SetAttribute(GdtfAttributePtr newAttr);
		void								SetDmxSnap(EGdtfDmxSnap snap);
		void								SetDmxMaster(EGdtfDmxMaster master);
		GdtfDmxChannelFunctionPtr			AddDmxChannelFunction(const TXString& name);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);

	};
	typedef GdtfDmxLogicalChannel*				GdtfDmxLogicalChannelPtr;
	typedef std::vector<GdtfDmxLogicalChannel*>	TGdtfDmxLogicalChannelArray;
	
	class GdtfDmxChannel : public GdtfObject
	{
	public:
		GdtfDmxChannel();
		GdtfDmxChannel(const TXString& name);
		~GdtfDmxChannel();
	private:
		TXString					fName_AutoGenerated;
		Sint32						fDmxBreak;
		Sint32						fCoarse;		bool fCoarseNone;			// None is not defined as value???
		Sint32						fFine;			bool fFineNone;				// None is not defined as value???
		Sint32						fUltra;			bool fUltraNone;			// None is not defined as value???
		Sint32                      fUber;			bool fUberNone;
		EGdtfDmxFrequency			fFrequenz;
		DmxValue					fDefaultValue;
		DmxValue					fHeighlight;	bool fHeighlightNone;
		double						fMoveInBlackFrames;							//is frames here the best unit
		double						fDmxChangeTimeLimit;		
		GdtfGeometryPtr				fGeomRef;
		TXString					fUnresolvedGeomRef;
		//
		TGdtfDmxLogicalChannelArray	fLogicalChannels;		
		
		
	public:
		virtual EGdtfObjectType				GetObjectType();
		virtual TXString					GetNodeReference() const;
		
        const TXString&						GetName() const;
        Sint32								GetDmxBreak() const;
        Sint32								GetCoarse() const;
        Sint32								GetFine() const;
        Sint32								GetUltra() const;
		Sint32								GetUber() const;
        EGdtfDmxFrequency					GetFrequency() const;
        Sint32								GetDefaultValue() const;
        Sint32								GetHighlight() const;
        double                              GetMoveInBlackFrames() const;
        double								GetDmxChangeTimeLimit() const;				
        const TGdtfDmxLogicalChannelArray	GetLogicalChannelArray();
		GdtfGeometryPtr						GetGeomRef();
		TXString							GetUnresolvedGeomRef() const;
		EGdtfChannelBitResolution			GetChannelBitResolution();

		void								SetName(const TXString& name);
		void								SetDmxBreak(Sint32 dmxBreak);
		void								SetDmxCoarse(Sint32 coarse);
		void								SetDmxFine(Sint32 fine);
		void								SetDmxUltra(Sint32 ultra);
		void								SetDmxUber(Sint32 uber);
		void								SetFrequency(EGdtfDmxFrequency frequency);
		void								SetDefaultValue(Sint32 defaultValue);
		void								SetHighlight(Sint32 highlight);
		void								SetMoveInBlackFrames(double moveInBlackFrames);
		void								SetDmxChangeTimeLimit(double changeLimit);
		void								SetModel(GdtfModelPtr ptr);
		GdtfDmxLogicalChannel*				AddLogicalChannel(const TXString& name);
		void								SetGeomRef(GdtfGeometryPtr newGeom);
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
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
		Sint32						fDmxStart;
		Sint32						fDmdEnd;
		
		// Pointer Resolve
		TXString					fUnresolvedDmxStart;
		TXString					fUnresolvedDmxEnd;
		TXString					fUnresolvedMasterRef;
		TXString					fUnresolvedSlaveRef;
		
	public:
		TXString					GetUnresolvedMasterRef() const;
		TXString					GetUnresolvedSlaveRef() const;
		void						ResolveDmxRange();

		
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
		
	};
	typedef GdtfDmxRelation*				GdtfDmxRelationPtr;
	typedef std::vector<GdtfDmxRelation*>	TGdtfDmxRelationArray;
	
	class GdtfDmxMode : public GdtfObject
	{
	public:
		GdtfDmxMode();
		GdtfDmxMode(const TXString& name);
		~GdtfDmxMode();
		
	private:
		TXString				fName;			
		GdtfGeometryPtr			fGeomRef;
		TXString				fUnresolvedGeomRef;
		//
		TGdtfDmxChannelArray	fChannels;
		TGdtfDmxRelationArray	fRelations;		

	public:		
		const TXString&				GetModeName() const;
		const TGdtfDmxChannelArray	GetChannelArray() const;		
		GdtfDmxChannelPtr			GetMasterByRef(const TXString& ref) const;
		GdtfDmxChannelFunctionPtr	GetSlaveByRef(const TXString& ref) const;
		GdtfGeometryPtr				GetGeomRef();
		
        const TXString&				GetUnresolvedGeomRef();
		const TGdtfDmxRelationArray GetDmxRelations();
		
		void						SetName(const TXString& name);
		GdtfDmxChannelPtr			AddChannel(const TXString& name);
		void						SetGeomRef(GdtfGeometryPtr ptr);
		void						SetModel(GdtfGeometryPtr ptr);
		GdtfDmxRelation*			AddDmxRelation(GdtfDmxChannel* master, GdtfDmxChannelFunctionPtr slave, const TXString &name);
		
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
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
		TXString	fDate;
		
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	public:
        // Getter
		const TXString&	GetDate() const;
		const TXString&	GetText() const;
        // Setter        
		void			SetText(const TXString& text);        
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
	};
	typedef GdtfRevision*	GdtfRevisionPtr;
	typedef std::vector<GdtfRevision*>	TGdtfRevisionArray;
	
	
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
	
	//------------------------------------------------------------------------------------
	// GdtfMacro Definition
	class GdtfMacro : public GdtfObject
	{
	public:
		GdtfMacro();
		~GdtfMacro();
		
	private:
        TXString fName;
		
	public:
        const TXString& GetName() const;
        
        void SetName(const TXString & name);

		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfMacro*					GdtfMacroPtr;
	typedef std::vector<GdtfMacroPtr>	TGdtfMacroArray;
	
	//------------------------------------------------------------------------------------
	// GdtfPhysicalDescription Definition
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
		
	};
	typedef GdtfMeasurementPoint*				GdtfMeasurementPointPtr;
	typedef std::vector<GdtfMeasurementPoint*>	TGdtfMeasurementPointArray;

	
	class GdtfPhysicalEmitter : public GdtfObject
	{
	public:
		GdtfPhysicalEmitter();
		GdtfPhysicalEmitter(const TXString& name);
		~GdtfPhysicalEmitter();
		
	private:
		TXString					fName;
		CCieColor					fColor;
		//		
		TGdtfMeasurementPointArray	fMeasurePoints;
		
	public:
		virtual EGdtfObjectType				GetObjectType();
        const TXString&						GetName() const;
        CCieColor							GetColor() const;
        const TGdtfMeasurementPointArray    GetMeasurementPoints();
		virtual TXString					GetNodeReference() const;
		
		void							SetName(const TXString& name);
		void							SetColor(CCieColor color);
		GdtfMeasurementPoint*			AddMeasurementPoint();

	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		
	};
	typedef GdtfPhysicalEmitter*				GdtfPhysicalEmitterPtr;
	typedef std::vector<GdtfPhysicalEmitter*>	TGdtfPhysicalEmitterArray;
	
	//------------------------------------------------------------------------------------
	// GdtfFixture Definition
	class GdtfFixture : public GdtfObject
	{
	public:
		GdtfFixture(IFileIdentifierPtr file);
		GdtfFixture();
		~GdtfFixture();
		
	private:
		//------------------------------------------------
		// Parameters for a GdtfFixture
		TXString		fName;
		TXString		fShortName;
		TXString		fManufacturer;
		TXString		fFixtureTypeDescription;
		GdtfFixtureGUID	fGuid;
		GdtfPNGFile		fTumbnail;
		TXString		fTumbnailFullPath;

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
		TGdtfMacroArray					fMacros;
		
		TGdtfPhysicalEmitterArray		fEmitters;
		// 
        
        // RDM is not supported by this Lib currenty...
        // So no FTRDM Array here
		
		//------------------------------------------------
		// Reading support
		TVWArray_IFileIdentifier		fLocalFiles;
		bool							fReaded;
		IFolderIdentifierPtr			fWorkingFolder;
		
	public:
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Getter
		const TXString&		GetName() const;
        const TXString&		GetShortName() const;
        const TXString&		GetManufacturer() const;
        const TXString&		GetFixtureTypeDescription() const;
        GdtfFixtureGUID		GetGuid() const;
        const GdtfPNGFile&  GetPNGFile() const;
		const GdtfPNGFile&  GetPNGFileFullPath();
		
		void				SetName(const TXString& name);
		void				SetShortName(const TXString& shortName);
		void				SetManufacturer(const TXString& manu);
		void				SetFixtureTypeDescription(const TXString& desc);
		void				SetGuid(const VWFC::UUID& uuid);
		void				SetPNGFile(const GdtfPNGFile& png);
		
	public:
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		// Add calls
		GdtfRevisionPtr			AddRevision(const TXString& text);
		GdtfAttributePtr		AddAttribute(const TXString& name, const TXString& prettyName);
		
		GdtfModelPtr			AddModel(const TXString& name);
		GdtfGeometryPtr			AddGeometry(		const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryReference(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryShaper(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryColor(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryGobo(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryBeam(	const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryWithAxis(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		GdtfGeometryPtr			AddGeometryWithLamp(const TXString& name, GdtfModelPtr refToModel, const VWTransformMatrix& ma);
		
		
		GdtfWheelPtr			AddWheel(TXString name);
		GdtfDmxModePtr			AddDmxMode(const TXString& name);
		GdtfPhysicalEmitterPtr	AddEmitter(const TXString& name);
		GdtfMacroPtr			AddMacro();
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
        const TGdtfPhysicalEmitterArray&		GetPhysicalEmitterArray();
        
	public:
		virtual EGdtfObjectType			GetObjectType();
		
	protected:
		virtual	TXString				GetNodeName();
		virtual	void					OnPrintToFile(IXMLFileNodePtr pNode);
		virtual	void					OnReadFromNode(const IXMLFileNodePtr& pNode);
		        
        GdtfAttributePtr getAttributeByRef(const TXString& ref);
        GdtfWheelPtr getWheelByRef(const TXString& ref);		
		GdtfPhysicalEmitterPtr getEmiterByRef(const TXString& ref);
		
		//
		void AutoGenerateNames(GdtfDmxModePtr dmxMode);
		
		// Resolve References		
		void ResolveAllReferences();
		void ResolveGeometryRefs();
		void ResolveGeometryRefs_Recursive(GdtfGeometryPtr geometry);
		
		void ResolveAttribRefs();		
		void ResolveDmxModeRefs();
		void ResolveDmxRelationRefs(GdtfDmxModePtr dmxMode);
		void ResolveDmxChannelRefs(GdtfDmxModePtr dmxMode);
		GdtfGeometryPtr ResolveGeometryRef(const TXString& unresolvedGeoRef, const TGdtfGeometryArray& geometryArray);
		
		void ResolveDmxLogicalChanRefs(GdtfDmxChannelPtr dmxChnl);
		void ResolveDmxChanelFunctionRefs(GdtfDmxLogicalChannelPtr dmxLogChnl);		
		//----------------------------------------------------------------------------------------------------------------------------------------------------------------
		
	public:
		bool							ExportToFile(IZIPFilePtr& zipfile);
		
		bool							IsReaded();
		void							GetWorkingFolder(IFolderIdentifierPtr& folder);
		

		
	};
	

}
