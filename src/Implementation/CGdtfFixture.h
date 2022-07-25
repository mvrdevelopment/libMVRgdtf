//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"
#include "../Wrapper/ZIPFileImpl.h"
#include <utility>


namespace VectorworksMVR
{	
	//----------------------------------------------------------------------------------------
	class CGdtfFixtureImpl : public VCOMImpl<IGdtfFixture>
	{
	public:
		CGdtfFixtureImpl();
		virtual ~CGdtfFixtureImpl();
		
        virtual VCOMError VCOM_CALLTYPE		ReadFromFile(MvrString fullPath);
		
		virtual VCOMError VCOM_CALLTYPE		OpenForWrite(MvrString fullPath, MvrString name, MvrString manufacturer, const MvrUUID& uuid);
		virtual VCOMError VCOM_CALLTYPE		OpenForWrite(MvrString name, MvrString manufacturer, const MvrUUID& uuid);

        virtual VCOMError VCOM_CALLTYPE		AddFileToGdtfFile(MvrString fullPath, ERessourceType resType, MvrString newFileName = "");
        virtual VCOMError VCOM_CALLTYPE		AddBufferToGdtfFile(MvrString filename, const char* inBuffer, size_t length, GdtfDefines::ERessourceType resType);
		virtual VCOMError VCOM_CALLTYPE		Close();
		
        virtual MvrString VCOM_CALLTYPE		GetName();
        virtual MvrString VCOM_CALLTYPE		GetShortName();
		virtual MvrString VCOM_CALLTYPE		GetLongName();
        virtual MvrString VCOM_CALLTYPE     GetManufacturer();
        virtual MvrString VCOM_CALLTYPE     GetFixtureTypeDescription();
        virtual VCOMError VCOM_CALLTYPE     GetFixtureGUID(MvrUUID& uuid);
        
        virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail();
		virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail_PNG_FullPath();
        virtual MvrString VCOM_CALLTYPE     GetFixtureThumbnail_SVG_FullPath();

        virtual VCOMError VCOM_CALLTYPE		GetThumbnailOffsetX(Sint32& offsetX);
		virtual VCOMError VCOM_CALLTYPE		SetThumbnailOffsetX(Sint32 offsetX);	

		virtual VCOMError VCOM_CALLTYPE		GetThumbnailOffsetY(Sint32& offsetY);
		virtual VCOMError VCOM_CALLTYPE		SetThumbnailOffsetY(Sint32 offsetY);

		virtual VCOMError VCOM_CALLTYPE		GetLinkedFixtureGUID(MvrUUID& uuid);
		virtual VCOMError VCOM_CALLTYPE		HasLinkedFixtureGUID(bool& has);
		
		
		virtual VCOMError VCOM_CALLTYPE     SetFixtureTypeDescription(MvrString descrip);
		virtual VCOMError VCOM_CALLTYPE		SetShortName(MvrString shortName);
		virtual VCOMError VCOM_CALLTYPE		SetLongName(MvrString longname);
		virtual VCOMError VCOM_CALLTYPE     SetFixtureThumbnail(MvrString thubnail);
		virtual VCOMError VCOM_CALLTYPE		SetLinkedFixtureGUID(const MvrUUID& uuid);
        
        
        virtual VCOMError VCOM_CALLTYPE		GetActivationGroupCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetActivationGroupAt(size_t at, IGdtfActivationGroup** activationGroup);
		virtual VCOMError VCOM_CALLTYPE		CreateActivationGroup(MvrString name, IGdtfActivationGroup** activationGroup);
        
        virtual VCOMError VCOM_CALLTYPE		GetFeatureGroupCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetFeatureGroupAt(size_t at, IGdtfFeatureGroup** featureGroup );
		virtual VCOMError VCOM_CALLTYPE		CreateFeatureGroup(MvrString name, MvrString prettyName, IGdtfFeatureGroup** featureGroup );
        
        virtual VCOMError VCOM_CALLTYPE		GetAttributeCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetAttributeAt(size_t at, IGdtfAttribute** attribute);
		virtual VCOMError VCOM_CALLTYPE		CreateAttribute(MvrString name, MvrString prettyName, IGdtfAttribute** attribute);
        
        virtual VCOMError VCOM_CALLTYPE		GetWheelCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetWheelAt(size_t at, IGdtfWheel** wheel );
		virtual VCOMError VCOM_CALLTYPE		CreateWheel(MvrString name, IGdtfWheel** wheel );
        
        virtual VCOMError VCOM_CALLTYPE		GetModelCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetModelAt(size_t at, IGdtfModel** model );
		virtual VCOMError VCOM_CALLTYPE		CreateModel(MvrString name,IGdtfModel** model );
        
        virtual VCOMError VCOM_CALLTYPE		GetGeometryCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetGeometryAt(size_t at, IGdtfGeometry** geometry);
		virtual VCOMError VCOM_CALLTYPE		CreateGeometry(EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry);
        
        virtual VCOMError VCOM_CALLTYPE		GetDmxModeCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetDmxModeAt(size_t at, IGdtfDmxMode** dmxMode );
		virtual VCOMError VCOM_CALLTYPE		CreateDmxMode(MvrString name, IGdtfDmxMode** dmxMode);
        
        virtual VCOMError VCOM_CALLTYPE		GetRevisionCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetRevisionAt(size_t at, IGdtfRevision** revision );
		virtual VCOMError VCOM_CALLTYPE     CreateRevision(MvrString text, STime date, IGdtfRevision** revision);
        
        virtual VCOMError VCOM_CALLTYPE		GetPresetCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetPresetAt(size_t at, IGdtfUserPreset** preset );
		virtual VCOMError VCOM_CALLTYPE     CreatePreset(IGdtfUserPreset** macro);
        
		// Protocols
		virtual VCOMError VCOM_CALLTYPE     GetRDM(IGdtf_FTRDM ** newFTRDM);
		virtual VCOMError VCOM_CALLTYPE     CreateRDM(VectorworksMVR::IGdtf_FTRDM ** outFTRDM);

        virtual VCOMError VCOM_CALLTYPE     GetArtNet(IGdtfArtNet** artNet);
		virtual VCOMError VCOM_CALLTYPE     CreateArtNet(IGdtfArtNet** artNet);

		virtual VCOMError VCOM_CALLTYPE     GetSACN(IGdtfSACN** sACN);
		virtual VCOMError VCOM_CALLTYPE     CreateSACN(IGdtfSACN** sACN);
        
        // PhysicalDescriptions
        virtual VCOMError                             GetColorSpace(VectorworksMVR::IGdtfColorSpace ** outColorSpace);

        virtual VCOMError VCOM_CALLTYPE  GetAdditionalColorSpaceCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE  CreateAdditionalColorSpace(MvrString name, GdtfDefines::EGdtfColorSpace colorSpace, VectorworksMVR::IGdtfColorSpace** outVal);
        virtual VCOMError VCOM_CALLTYPE  GetAdditionalColorSpaceAt(size_t at, VectorworksMVR::IGdtfColorSpace** value);

        virtual VCOMError VCOM_CALLTYPE  GetGamutCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE  CreateGamut(MvrString name, CieColor color, VectorworksMVR::IGdtfGamut** outVal);
        virtual VCOMError VCOM_CALLTYPE  GetGamutAt(size_t at, VectorworksMVR::IGdtfGamut** value);

        virtual VCOMError VCOM_CALLTYPE  GetEmitterCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE  CreateEmitter(MvrString name, CieColor color, VectorworksMVR::IGdtfPhysicalEmitter** outVal);
        virtual VCOMError VCOM_CALLTYPE  GetEmitterAt(size_t at, VectorworksMVR::IGdtfPhysicalEmitter** value);

        virtual VCOMError VCOM_CALLTYPE  GetFilterCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE  CreateFilter(MvrString name, CieColor color, VectorworksMVR::IGdtfFilter** outVal);
        virtual VCOMError VCOM_CALLTYPE  GetFilterAt(size_t at, VectorworksMVR::IGdtfFilter** value);

        virtual VCOMError VCOM_CALLTYPE  GetDMXProfileCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE  CreateDMXProfile(VectorworksMVR::IGdtfDMXProfile** outVal);
        virtual VCOMError VCOM_CALLTYPE  GetDMXProfileAt(size_t at, VectorworksMVR::IGdtfDMXProfile** value);

        virtual VCOMError VCOM_CALLTYPE  GetCRIGroupCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE  CreateCRIGroup(double colorTemp, VectorworksMVR::IGdtfCRIGroup** outVal);
        virtual VCOMError VCOM_CALLTYPE  GetCRIGroupAt(size_t at, VectorworksMVR::IGdtfCRIGroup** value);
        //-----------------------------------------------------------------------------

		// Parsing Errors
        virtual VCOMError VCOM_CALLTYPE		GetParsingErrorCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE		GetParsingErrorAt(size_t at, IGdtfXmlParsingError** value);

		//Internal
		VectorworksMVR::VCOMError			ReadFromFile(IFileIdentifierPtr file, TXString gdtfFileName);

        virtual VCOMError VCOM_CALLTYPE		GetImageRessourcesCount(size_t& count);
		virtual MvrString VCOM_CALLTYPE		GetImageRessourcesPathAt(size_t at);

        //-----------------------------------------------------------------------------               
        // BufferWorkflow
		virtual VCOMError VCOM_CALLTYPE		GetBufferLength(size_t& length);		
		virtual VCOMError VCOM_CALLTYPE		ToBuffer(char* outBuffer);	
		virtual VCOMError VCOM_CALLTYPE		FromBuffer(const char* buffer, size_t length);
        virtual VCOMError VCOM_CALLTYPE		FromBufferInternal(const char* buffer, size_t length, TXString gdtfFileName);

        
        virtual VCOMError VCOM_CALLTYPE     RefreshBuffer();

        private:
        void FreeBuffer();

        // GDTF 1.1
        virtual VCOMError VCOM_CALLTYPE     GetCanHaveChildren(bool& value);
        virtual VCOMError VCOM_CALLTYPE     SetCanHaveChildren(bool value);

        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetConnectorCount(size_t& count);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE CreateConnector(MvrString name, MvrString type, VectorworksMVR::IGdtfConnector** outVal);
        virtual VCOMError VCOM_CALLTYPE VCOM_CALLTYPE GetConnectorAt(size_t at, VectorworksMVR::IGdtfConnector** value);

        virtual VCOMError VCOM_CALLTYPE		GetOperatingTemperatureLow(double& value);
		virtual VCOMError VCOM_CALLTYPE		SetOperatingTemperatureLow(double value);

		virtual VCOMError VCOM_CALLTYPE		GetOperatingTemperatureHigh(double& value);
		virtual VCOMError VCOM_CALLTYPE		SetOperatingTemperatureHigh(double value);

		virtual VCOMError VCOM_CALLTYPE		GetWeight(double& value);
		virtual VCOMError VCOM_CALLTYPE		SetWeight(double value);

		virtual VCOMError VCOM_CALLTYPE		GetLegHeight(double& value);
		virtual VCOMError VCOM_CALLTYPE		SetLegHeight(double value);
		
	private:
        SceneData::GdtfFixture*             fFixtureObject;
		IZIPFilePtr				            fZipFile;
        std::vector<std::pair<TXString, CZIPFileIOBufferImpl*>>  fBuffersAdded;

        char*                   fBuffer = nullptr;
        size_t                  fBufferLength;
        
	};
	

}
