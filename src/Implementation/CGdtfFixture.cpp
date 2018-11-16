//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfFixture.h"
#include "CGdtfWheel.h"
#include "CGdtfActivationGroup.h"
#include "CGdtfFeatureGroup.h"
#include "CGdtfAttribute.h"
#include "CGdtfModel.h"
#include "CGdtfGeometry.h"
#include "CGdtfDmxMode.h"
#include "CGdtfRevision.h"
#include "CGdtfUserPreset.h"
#include "CGdtfMacro.h"
#include "CGdtfPhysicalEmitter.h"
#include "CMediaRessourceVectorImpl.h"
#include "Utility.h"
#include "CGdtfDmxProfile.h"
#include "CGdtfCRIGroup.h"
#include "CGdtfFTRDM.h"

using namespace VectorWorks::Filing;

VectorworksMVR::CGdtfFixtureImpl::CGdtfFixtureImpl()
{
    fFixtureObject = nullptr;
}

VectorworksMVR::CGdtfFixtureImpl::~CGdtfFixtureImpl()
{
    if (fFixtureObject) {delete fFixtureObject;}
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::ReadFromFile(MvrString fullPath)
{
	TXString strFullPath ( fullPath );
	
    // Create the file pointer on the full path
    IFileIdentifierPtr file (IID_FileIdentifier);
    file->Set(strFullPath);
	
    // Read From File
    return ReadFromFile(file);
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::OpenForWrite(MvrString fullPath, MvrString name, MvrString manufacturer, const MvrUUID& uuid)
{	
	TXString strFullPath ( fullPath );
	
	// Create the file pointer on the full path
	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(strFullPath);
	
	bool fileExists = false;
	file->ExistsOnDisk(fileExists);
	if(fileExists) { file->DeleteOnDisk(); }
	
	// If there is an existing fixture loaded, delete the old one and start from scratch
	if (fFixtureObject) { delete fFixtureObject; }
	
	// Create the newFixture
	fFixtureObject = new SceneData::GdtfFixture();
	
	TXString	vwName			(name);
	TXString	vwManufacturer (manufacturer);
	VWFC::Tools::VWUUID vwUuid = VWFC::Tools::VWUUID(uuid.a, uuid.b, uuid.c, uuid.d);
	
	fFixtureObject->SetName(vwName);
	fFixtureObject->SetManufacturer(vwManufacturer);
	fFixtureObject->SetGuid(vwUuid);
	
	fZipFile = IZIPFilePtr(IID_ZIPFile);
	fZipFile->OpenWrite(file);
	
	
	// Read From File
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::AddFileToGdtfFile(MvrString fullPath)
{
	if(!fFixtureObject) { return kVCOMError_Failed; }
	if(!fZipFile)		{ return kVCOMError_Failed; }
	TXString strFullPath ( fullPath );
	
	// Create the file pointer on the full path
	IFileIdentifierPtr file (IID_FileIdentifier);
	file->Set(strFullPath);
	
	bool fileExisis = false;
	file->ExistsOnDisk(fileExisis);
	
	// Check if the file exists
	if (!fileExisis) { return kVCOMError_Failed; }
	
	TXString fileName;
	file->GetFileName(fileName);
	
	fZipFile->AddFile(fileName, file);
	
	
	// Read From File
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::Close()
{
	if(!fFixtureObject) { return kVCOMError_Failed; }
	if(!fZipFile)		{ return kVCOMError_Failed; }
		
	fFixtureObject->ExportToFile(fZipFile);
	
	fZipFile->Close();
	
	// Read From File
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::ReadFromFile(IFileIdentifierPtr file)
{
	
	// Check there is already a object in here
	if (fFixtureObject) { delete fFixtureObject; }
	
	// Create the new Object
	fFixtureObject = new SceneData::GdtfFixture( file );
	
	// Check if this was good
	if (!fFixtureObject) { return kVCOMError_Failed; }
	
	// Check if you can read it
	if ( ! fFixtureObject->IsReaded()) { return kVCOMError_InvalidArg; }
	
	// If everything is OK
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetName()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetName().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetShortName()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetShortName().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetManufacturer()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetManufacturer().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetFixtureTypeDescription()
{
    if(!fFixtureObject) {return "";}
	
    return fFixtureObject->GetFixtureTypeDescription().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetFixtureGUID(VectorworksMVR::MvrUUID &uuid)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    fFixtureObject->GetGuid().GetUUID(uuid.a, uuid.b, uuid.c, uuid.d);
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetLinkedFixtureGUID(VectorworksMVR::MvrUUID &uuid)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	if(fFixtureObject->HasLinkedGuid() == false)
	{
		uuid.a = 0;
		uuid.b = 0;
		uuid.c = 0;
		uuid.d = 0;
	}
	
	fFixtureObject->GetLinkedGuid().GetUUID(uuid.a, uuid.b, uuid.c, uuid.d);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::HasLinkedFixtureGUID(bool &uuid)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	uuid = fFixtureObject->HasLinkedGuid();
	
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetFixtureThumbnail()
{
    if(!fFixtureObject) {return "";}
	
    
    return fFixtureObject->GetPNGFile().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfFixtureImpl::GetFixtureThumbnailFullPath()
{
	if(!fFixtureObject) {return "";}
	
	
	return fFixtureObject->GetPNGFileFullPath().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetFixtureTypeDescription(MvrString descrip)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwDescrp (descrip);
	fFixtureObject->SetFixtureTypeDescription(vwDescrp);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetShortName(MvrString shortName)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName (shortName);
	fFixtureObject->SetShortName(vwName);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetFixtureThumbnail(MvrString thubnail)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwThumb (thubnail);
	fFixtureObject->SetPNGFile(vwThumb);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::SetLinkedFixtureGUID(const MvrUUID& uuid)
{
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	VWFC::Tools::VWUUID vwUuid = VWFC::Tools::VWUUID(uuid.a, uuid.b, uuid.c, uuid.d);
	fFixtureObject->SetLinkedGuid(vwUuid);
	
	return kVCOMError_NoError;
}



VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetActivationGroupCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetActivationGroupArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetActivationGroupAt(size_t at, VectorworksMVR::IGdtfActivationGroup **activationGroup)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetActivationGroupArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfActivationGroup* gdtfActivationGroup = fFixtureObject->GetActivationGroupArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfActivationGroupImpl* pActivationGroupObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfActivationGroup, (IVWUnknown**) & pActivationGroupObj)))
    {
        // Check Casting
        CGdtfActivationGroupImpl* pResultInterface = dynamic_cast<CGdtfActivationGroupImpl* >(pActivationGroupObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfActivationGroup);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*activationGroup)
    {
        (*activationGroup)->Release();
        *activationGroup		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *activationGroup	= pActivationGroupObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateActivationGroup(MvrString name, IGdtfActivationGroup** activationGroup)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName(name);
	
	SceneData::GdtfActivationGroup* gdtfActivationGroup = fFixtureObject->AddActivationGroup(vwName);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfActivationGroupImpl* pActivationGroupObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfActivationGroup, (IVWUnknown**) & pActivationGroupObj)))
	{
		// Check Casting
		CGdtfActivationGroupImpl* pResultInterface = dynamic_cast<CGdtfActivationGroupImpl* >(pActivationGroupObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfActivationGroup);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*activationGroup)
	{
		(*activationGroup)->Release();
		*activationGroup		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*activationGroup	= pActivationGroupObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetFeatureGroupCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetFeatureGroupArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetFeatureGroupAt(size_t at, VectorworksMVR::IGdtfFeatureGroup **featureGroup)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetFeatureGroupArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfFeatureGroup* gdtfFeatureGroup = fFixtureObject->GetFeatureGroupArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfFeatureGroupImpl* pFeatureGroupObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFeatureGroup, (IVWUnknown**) & pFeatureGroupObj)))
    {
        // Check Casting
        CGdtfFeatureGroupImpl* pResultInterface = dynamic_cast<CGdtfFeatureGroupImpl* >(pFeatureGroupObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfFeatureGroup);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*featureGroup)
    {
        (*featureGroup)->Release();
        *featureGroup		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *featureGroup	= pFeatureGroupObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateFeatureGroup(MvrString name, MvrString prettyName, IGdtfFeatureGroup** featureGroup)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName		(name);
	TXString vwPretty	(prettyName);
	
	SceneData::GdtfFeatureGroup* gdtfFeatureGroup = fFixtureObject->AddFeatureGroup(vwName, vwPretty);
	
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfFeatureGroupImpl* pFeatureGroupObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfFeatureGroup, (IVWUnknown**) & pFeatureGroupObj)))
	{
		// Check Casting
		CGdtfFeatureGroupImpl* pResultInterface = dynamic_cast<CGdtfFeatureGroupImpl* >(pFeatureGroupObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfFeatureGroup);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*featureGroup)
	{
		(*featureGroup)->Release();
		*featureGroup		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*featureGroup	= pFeatureGroupObj;
	
	return kVCOMError_NoError;
}
VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetAttributeCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetAttributeArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetAttributeAt(size_t at, VectorworksMVR::IGdtfAttribute **attribute)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetAttributeArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfAttribute* gdtfAttribute = fFixtureObject->GetAttributeArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfAttributeImpl* pAttributeObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfAttribute, (IVWUnknown**) & pAttributeObj)))
    {
        // Check Casting
        CGdtfAttributeImpl* pResultInterface = dynamic_cast<CGdtfAttributeImpl* >(pAttributeObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfAttribute);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*attribute)
    {
        (*attribute)->Release();
        *attribute		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *attribute	= pAttributeObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateAttribute(MvrString name, MvrString prettyName, IGdtfAttribute** attribute)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName		(name);
	TXString vwPretty	(prettyName);
	
	SceneData::GdtfAttribute* gdtfAttribute = fFixtureObject->AddAttribute(vwName, vwPretty);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfAttributeImpl* pAttributeObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfAttribute, (IVWUnknown**) & pAttributeObj)))
	{
		// Check Casting
		CGdtfAttributeImpl* pResultInterface = dynamic_cast<CGdtfAttributeImpl* >(pAttributeObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfAttribute);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*attribute)
	{
		(*attribute)->Release();
		*attribute		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*attribute	= pAttributeObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetWheelCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetWheelArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetWheelAt(size_t at, VectorworksMVR::IGdtfWheel ** wheel)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetWheelArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfWheel* gdtfWheel = fFixtureObject->GetWheelArray()[at];
   
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfWheelImpl* pWheelObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheel, (IVWUnknown**) & pWheelObj)))
    {
        // Check Casting
        CGdtfWheelImpl* pResultInterface = dynamic_cast<CGdtfWheelImpl* >(pWheelObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfWheel);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*wheel)
    {
        (*wheel)->Release();
        *wheel		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *wheel		= pWheelObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateWheel(MvrString name, IGdtfWheel** wheel)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
		
	SceneData::GdtfWheel* gdtfWheel = fFixtureObject->AddWheel(name);
		
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfWheelImpl* pWheelObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfWheel, (IVWUnknown**) & pWheelObj)))
	{
		// Check Casting
		CGdtfWheelImpl* pResultInterface = dynamic_cast<CGdtfWheelImpl* >(pWheelObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfWheel);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*wheel)
	{
		(*wheel)->Release();
		*wheel		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*wheel		= pWheelObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetModelCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetModelArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetModelAt(size_t at, VectorworksMVR::IGdtfModel **model)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetModelArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfModel* gdtfModel = fFixtureObject->GetModelArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfModelImpl* pModelObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfModel, (IVWUnknown**) & pModelObj)))
    {
        // Check Casting
        CGdtfModelImpl* pResultInterface = dynamic_cast<CGdtfModelImpl* >(pModelObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfModel);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*model)
    {
        (*model)->Release();
        *model		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *model		= pModelObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateModel(MvrString name, IGdtfModel** model)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName (name);
	
	SceneData::GdtfModel* gdtfModel = fFixtureObject->AddModel(vwName);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfModelImpl* pModelObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfModel, (IVWUnknown**) & pModelObj)))
	{
		// Check Casting
		CGdtfModelImpl* pResultInterface = dynamic_cast<CGdtfModelImpl* >(pModelObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfModel);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*model)
	{
		(*model)->Release();
		*model		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*model		= pModelObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetGeometryCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetGeometryArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetGeometryAt(size_t at, VectorworksMVR::IGdtfGeometry **geometry)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetGeometryArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfGeometry* gdtfGeometry = fFixtureObject->GetGeometryArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfGeometryImpl* pGeometryObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeometryObj)))
    {
        // Check Casting
        CGdtfGeometryImpl* pResultInterface = dynamic_cast<CGdtfGeometryImpl* >(pGeometryObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfGeometry);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*geometry)
    {
        (*geometry)->Release();
        *geometry		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *geometry		= pGeometryObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateGeometry(EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry)
{
	// Check if Set
	if(!fFixtureObject) { return kVCOMError_NotInitialized;}
	
	// Check Input
	if (!model)			{ return kVCOMError_InvalidArg;  }
	
	//---------------------------------------------------------------------------
	// Extract Model
	CGdtfModelImpl* modelInterface = dynamic_cast<CGdtfModelImpl*>(model);
	if( ! modelInterface) { return kVCOMError_Failed;  }
	
	
	SceneData::GdtfModelPtr scModel = modelInterface->GetPointer();
	if ( ! scModel) { return kVCOMError_Failed; }
	
	
	//---------------------------------------------------------------------------
	// Create geometry
	TXString			vwName (name);
	VWTransformMatrix	ma;
	Utility::ConvertMatrix(mat, ma);
	
	SceneData::GdtfGeometry* gdtfGeometry = nullptr;
	
	switch (type)
	{
		case eGdtfGeometryReference:	gdtfGeometry = fFixtureObject->AddGeometryReference(vwName, scModel, ma); break;
		case eGdtfGeometryLamp:			gdtfGeometry = fFixtureObject->AddGeometryWithLamp(	vwName, scModel, ma); break;
		case eGdtfGeometryAxis:			gdtfGeometry = fFixtureObject->AddGeometryWithAxis(	vwName, scModel, ma); break;
		case eGdtfGeometryShaperFilter:	gdtfGeometry = fFixtureObject->AddGeometryShaper(	vwName, scModel, ma); break;
		case eGdtfGeometryColorFilter:	gdtfGeometry = fFixtureObject->AddGeometryColor(	vwName, scModel, ma); break;
		case eGdtfGeometryGoboFilter:	gdtfGeometry = fFixtureObject->AddGeometryGobo(		vwName, scModel, ma); break;
		case eGdtfGeometryBeamFilter:	gdtfGeometry = fFixtureObject->AddGeometryBeam(		vwName, scModel, ma); break;
		case eGdtfGeometry:				gdtfGeometry = fFixtureObject->AddGeometry(			vwName, scModel, ma); break;

		default:
			return kVCOMError_InvalidArg;
			break;
	}
	
	if ( ! gdtfGeometry) { return kVCOMError_Failed; }
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfGeometryImpl* pGeometryObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeometryObj)))
	{
		// Check Casting
		CGdtfGeometryImpl* pResultInterface = dynamic_cast<CGdtfGeometryImpl* >(pGeometryObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfGeometry);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*geometry)
	{
		(*geometry)->Release();
		*geometry		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*geometry		= pGeometryObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetDmxModeCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetDmxModeArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetDmxModeAt(size_t at, VectorworksMVR::IGdtfDmxMode **dmxMode)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetDmxModeArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfDmxMode* gdtfDmxMode = fFixtureObject->GetDmxModeArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfDmxModeImpl* pDmxModeObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxMode, (IVWUnknown**) & pDmxModeObj)))
    {
        // Check Casting
        CGdtfDmxModeImpl* pResultInterface = dynamic_cast<CGdtfDmxModeImpl* >(pDmxModeObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfDmxMode);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*dmxMode)
    {
        (*dmxMode)->Release();
        *dmxMode		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *dmxMode		= pDmxModeObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateDmxMode(MvrString name, IGdtfDmxMode** dmxMode)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName (name);
	
	SceneData::GdtfDmxMode* gdtfDmxMode = fFixtureObject->AddDmxMode(vwName);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfDmxModeImpl* pDmxModeObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxMode, (IVWUnknown**) & pDmxModeObj)))
	{
		// Check Casting
		CGdtfDmxModeImpl* pResultInterface = dynamic_cast<CGdtfDmxModeImpl* >(pDmxModeObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfDmxMode);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*dmxMode)
	{
		(*dmxMode)->Release();
		*dmxMode		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*dmxMode		= pDmxModeObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetRevisionCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetRevisionArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetRevisionAt(size_t at, VectorworksMVR::IGdtfRevision **revision)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetRevisionArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfRevision* gdtfRevision = fFixtureObject->GetRevisionArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfRevisionImpl* pRevisionObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRevision, (IVWUnknown**) & pRevisionObj)))
    {
        // Check Casting
        CGdtfRevisionImpl* pResultInterface = dynamic_cast<CGdtfRevisionImpl* >(pRevisionObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfRevision);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*revision)
    {
        (*revision)->Release();
        *revision		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *revision		= pRevisionObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateRevision(MvrString text,IGdtfRevision** revision)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwText (text);
	
	SceneData::GdtfRevision* gdtfRevision = fFixtureObject->AddRevision(vwText);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfRevisionImpl* pRevisionObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfRevision, (IVWUnknown**) & pRevisionObj)))
	{
		// Check Casting
		CGdtfRevisionImpl* pResultInterface = dynamic_cast<CGdtfRevisionImpl* >(pRevisionObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfRevision);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*revision)
	{
		(*revision)->Release();
		*revision		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*revision		= pRevisionObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetPresetCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetPresetArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetPresetAt(size_t at, VectorworksMVR::IGdtfUserPreset **preset)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetPresetArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfUserPreset* gdtfPreset = fFixtureObject->GetPresetArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfUserPresetImpl* pPresetObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfUserPreset, (IVWUnknown**) & pPresetObj)))
    {
        // Check Casting
        CGdtfUserPresetImpl* pResultInterface = dynamic_cast<CGdtfUserPresetImpl* >(pPresetObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfPreset);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*preset)
    {
        (*preset)->Release();
        *preset		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *preset		= pPresetObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreatePreset(VectorworksMVR::IGdtfUserPreset **preset)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	SceneData::GdtfUserPreset* gdtfPreset = fFixtureObject->AddUserPreset();
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfUserPresetImpl* pPresetObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfUserPreset, (IVWUnknown**) & pPresetObj)))
	{
		// Check Casting
		CGdtfUserPresetImpl* pResultInterface = dynamic_cast<CGdtfUserPresetImpl* >(pPresetObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfPreset);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*preset)
	{
		(*preset)->Release();
		*preset		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*preset		= pPresetObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetMacroCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    count = fFixtureObject->GetMacroArray().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetMacroAt(size_t at, VectorworksMVR::IGdtfMacro **macro)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetMacroArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfMacro* gdtfMacro = fFixtureObject->GetMacroArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfMacroImpl* pMacroObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacro, (IVWUnknown**) & pMacroObj)))
    {
        // Check Casting
        CGdtfMacroImpl* pResultInterface = dynamic_cast<CGdtfMacroImpl* >(pMacroObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfMacro);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*macro)
    {
        (*macro)->Release();
        *macro		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *macro		= pMacroObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateMacro(MvrString& name, VectorworksMVR::IGdtfMacro **macro)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	
	SceneData::GdtfMacro* gdtfMacro = fFixtureObject->AddMacro(name);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfMacroImpl* pMacroObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfMacro, (IVWUnknown**) & pMacroObj)))
	{
		// Check Casting
		CGdtfMacroImpl* pResultInterface = dynamic_cast<CGdtfMacroImpl* >(pMacroObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfMacro);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*macro)
	{
		(*macro)->Release();
		*macro		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*macro		= pMacroObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetEmitterCount(size_t &count)
{
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
    count = fFixtureObject->GetPhysicalEmitterArray().size();
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetEmitterAt(size_t at, IGdtfPhysicalEmitter** emitter)
{
    // Check if Set
    if(!fFixtureObject) {return kVCOMError_NotInitialized;}
    
    // Check if no Overflow
    if (at >=  fFixtureObject->GetPhysicalEmitterArray().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfPhysicalEmitter* scEmitter = fFixtureObject->GetPhysicalEmitterArray()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfPhysicalEmitterImpl* pEmitterObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**) & pEmitterObj)))
    {
        // Check Casting
        CGdtfPhysicalEmitterImpl* pResultInterface = dynamic_cast<CGdtfPhysicalEmitterImpl* >(pEmitterObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(scEmitter);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*emitter)
    {
        (*emitter)->Release();
        *emitter		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *emitter		=  pEmitterObj;
    
    return kVCOMError_NoError;
}



VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateEmitter(MvrString name,const CieColor& color, IGdtfPhysicalEmitter** emitter)
{
	// Check if Set
	if(!fFixtureObject) {return kVCOMError_NotInitialized;}
	
	TXString vwName =	TXString(name);
	CCieColor cieCol	(color.fx, color.fy, color.f_Y);
	
	SceneData::GdtfPhysicalEmitter* scEmitter = fFixtureObject->AddEmitter(vwName);
	scEmitter->SetColor(cieCol);
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfPhysicalEmitterImpl* pEmitterObj = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**) & pEmitterObj)))
	{
		// Check Casting
		CGdtfPhysicalEmitterImpl* pResultInterface = dynamic_cast<CGdtfPhysicalEmitterImpl* >(pEmitterObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(scEmitter);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*emitter)
	{
		(*emitter)->Release();
		*emitter		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*emitter		=  pEmitterObj;
	
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetCRIGroupCount(size_t &count)
{
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    count = fFixtureObject->GetCRIGroupArray().size();

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetCRIGroupAt(size_t at, VectorworksMVR::IGdtfCRIGroup** value)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }

    // Check if no Overflow
    if (at >= fFixtureObject->GetCRIGroupArray().size()) { return kVCOMError_OutOfBounds; }
    
    SceneData::GdtfCRIGroup* gdtfCRIGroup = fFixtureObject->GetCRIGroupArray()[at];


    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfCRIGroupImpl* pCRIGroupObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfCRIGroup, (IVWUnknown**)& pCRIGroupObj)))
    {
        // Check Casting
        CGdtfCRIGroupImpl* pResultInterface = dynamic_cast<CGdtfCRIGroupImpl*>(pCRIGroupObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfCRIGroup);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }

    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*value)
    {
        (*value)->Release();
        *value = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *value = pCRIGroupObj;

    return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateCRIGroup(double colorTemp, VectorworksMVR::IGdtfCRIGroup **outVal)
{
    // Check if Set
    if (!fFixtureObject) { return kVCOMError_NotInitialized; }


    SceneData::GdtfCRIGroup* gdtfCRIGroup = fFixtureObject ->AddCRIGroup(colorTemp);

    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfCRIGroupImpl* pCRIGroupObj = nullptr;

    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfCRIGroup, (IVWUnknown**)& pCRIGroupObj)))
    {
        // Check Casting
        CGdtfCRIGroupImpl* pResultInterface = dynamic_cast<CGdtfCRIGroupImpl*>(pCRIGroupObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfCRIGroup);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }

    //---------------------------------------------------------------------------
    // Check Incomming Object
    if (*outVal)
    {
        (*outVal)->Release();
        *outVal = NULL;
    }

    //---------------------------------------------------------------------------
    // Set Out Value
    *outVal = pCRIGroupObj;

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetDMXProfileCount(size_t &count)
 {
     if (!fFixtureObject) { return kVCOMError_NotInitialized; }

     count = fFixtureObject->GetDmxProfileArray().size();

     return kVCOMError_NoError;
 }


 VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetDMXProfileAt(size_t at, VectorworksMVR::IGdtfDMXProfile** value)
 {
     // Check if Set
     if (!fFixtureObject) { return kVCOMError_NotInitialized; }

     // Check if no Overflow
     if (at >= fFixtureObject->GetDmxProfileArray().size()) { return kVCOMError_OutOfBounds; }


     SceneData::GdtfDMXProfile* gdtfDMXProfile = fFixtureObject->GetDmxProfileArray()[at];
     
     //---------------------------------------------------------------------------
     // Initialize Object
     CGdtfDMXProfileImpl* pDMXProfileObj = nullptr;

     // Query Interface
     if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDMXProfile, (IVWUnknown**)& pDMXProfileObj)))
     {
         // Check Casting
         CGdtfDMXProfileImpl* pResultInterface = dynamic_cast<CGdtfDMXProfileImpl*>(pDMXProfileObj);
         if (pResultInterface)
         {
             pResultInterface->SetPointer(gdtfDMXProfile);
         }
         else
         {
             pResultInterface->Release();
             pResultInterface = nullptr;
             return kVCOMError_NoInterface;
         }
     }

     //---------------------------------------------------------------------------
     // Check Incomming Object
     if (*value)
     {
         (*value)->Release();
         *value = NULL;
     }

     //---------------------------------------------------------------------------
     // Set Out Value
     *value = pDMXProfileObj;

     return kVCOMError_NoError;
 }


 VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateDMXProfile(VectorworksMVR::IGdtfDMXProfile **outVal)
 {
     // Check if Set
     if (!fFixtureObject) { return kVCOMError_NotInitialized; }


     SceneData::GdtfDMXProfile* gdtfDMXProfile = fFixtureObject->AddDmxProfile();

     //---------------------------------------------------------------------------
     // Initialize Object
     CGdtfDMXProfileImpl* pDMXProfileObj = nullptr;

     // Query Interface
     if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDMXProfile, (IVWUnknown**)& pDMXProfileObj)))
     {
         // Check Casting
         CGdtfDMXProfileImpl* pResultInterface = dynamic_cast<CGdtfDMXProfileImpl*>(pDMXProfileObj);
         if (pResultInterface)
         {
             pResultInterface->SetPointer(gdtfDMXProfile);
         }
         else
         {
             pResultInterface->Release();
             pResultInterface = nullptr;
             return kVCOMError_NoInterface;
         }
     }

     //---------------------------------------------------------------------------
     // Check Incomming Object
     if (*outVal)
     {
         (*outVal)->Release();
         *outVal = NULL;
     }

     //---------------------------------------------------------------------------
     // Set Out Value
     *outVal = pDMXProfileObj;

     return kVCOMError_NoError;
 }


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::GetRDM(IGdtf_FTRDM ** value)
{
	// Check if Set
	if (!fFixtureObject) { return kVCOMError_NotInitialized; }
	

	SceneData::GdtfFTRDMPtr gdtfRdm = fFixtureObject->GetProtocollContainer().GetRDM();
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtf_FTRDMImpl* pRdm = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfTRDM, (IVWUnknown**)& pRdm)))
	{
		// Check Casting
		CGdtf_FTRDMImpl* pResultInterface = dynamic_cast<CGdtf_FTRDMImpl*>(pRdm);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfRdm);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*value)
	{
		(*value)->Release();
		*value = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*value = pRdm;
	
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfFixtureImpl::CreateRDM(VectorworksMVR::IGdtf_FTRDM ** outFTRDM)
{
	// Check if Set
	if (!fFixtureObject) { return kVCOMError_NotInitialized; }
	
	
	SceneData::GdtfFTRDMPtr gdtfRdm = fFixtureObject->GetProtocollContainer().CreateRDM();
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtf_FTRDMImpl* pRdm = nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDMXProfile, (IVWUnknown**)& pRdm)))
	{
		// Check Casting
		CGdtf_FTRDMImpl* pResultInterface = dynamic_cast<CGdtf_FTRDMImpl*>(pRdm);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfRdm);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incomming Object
	if (*outFTRDM)
	{
		(*outFTRDM)->Release();
		*outFTRDM = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outFTRDM = pRdm;
	
	return kVCOMError_NoError;
}
