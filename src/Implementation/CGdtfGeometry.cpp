//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfGeometry.h"
#include "CGdtfModel.h"
#include "CGdtfBreak.h"
#include "CMediaRessourceVectorImpl.h"
#include "Utility.h"
#include "CGdtfDmxMode.h"
#include "CGdtfDmxChannel.h"
#include "CGdtfPhysicalEmitter.h"
#include "CGdtfLaserProtocol.h"
#include "CGdtfPinPatch.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfGeometryImpl::CGdtfGeometryImpl()
{
	fGeometry = nullptr;
};

VectorworksMVR::CGdtfGeometryImpl::~CGdtfGeometryImpl()
{
    
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetGeometryType(EGdtfObjectType& type)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	type = fGeometryType;
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfGeometryImpl::GetName()
{
	// Check Pointer
	if ( ! fGeometry) { return ""; }
	
    return fGeometry->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetModel(VectorworksMVR::IGdtfModel **model)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfModel*	gdtfModel = fGeometry->GetModelRef();
	if ( ! gdtfModel)	{ return kVCOMError_NotSet; }

    CGdtfModelImpl*			pModelObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfModel, (IVWUnknown**) & pModelObj)))
    {
        // Check Casting
        CGdtfModelImpl* pResultInterface = static_cast<CGdtfModelImpl* >(pModelObj);
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
    // Check Incoming Object
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetTransformMatrix(VectorworksMVR::STransformMatrix &transformMatrix)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
    VWFC::Math::VWTransformMatrix ma;
    
    fGeometry->GetTransformMatrix(ma);
    
	GdtfUtil::ConvertMatrix(ma, transformMatrix);
	
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetParent(VectorworksMVR::IGdtfGeometry **geometry)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfGeometry*	gdtfGeometry = fGeometry->GetParentGeometry();
	if ( ! gdtfGeometry)	{ return kVCOMError_NotSet; }

    CGdtfGeometryImpl*			pGeometry = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeometry)))
    {
        // Check Casting
        CGdtfGeometryImpl* pResultInterface = static_cast<CGdtfGeometryImpl* >(pGeometry);
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
    *geometry		= pGeometry;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetInternalGeometryCount(size_t &count)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
    count = fGeometry->GetInternalGeometries().size();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetInternalGeometryAt(size_t at, VectorworksMVR::IGdtfGeometry **geometry)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
    // Check if no Overflow
    if (at >=  fGeometry->GetInternalGeometries().size()) { return kVCOMError_OutOfBounds;  }
    
    
    SceneData::GdtfGeometry* gdtfGeometry = fGeometry->GetInternalGeometries()[at];
    
    
    //---------------------------------------------------------------------------
    // Initialize Object
    CGdtfGeometryImpl* pGeometryObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeometryObj)))
    {
        // Check Casting
        CGdtfGeometryImpl* pResultInterface = static_cast<CGdtfGeometryImpl* >(pGeometryObj);
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::CreateGeometry(EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry)
{
	// Check if Set
	if(!fGeometry) { return kVCOMError_NotInitialized;}
		
	//---------------------------------------------------------------------------
	// Extract Model
	SceneData::GdtfModelPtr scModel = nullptr;

	CGdtfModelImpl* modelInterface = static_cast<CGdtfModelImpl*>(model);
	if( modelInterface)
	{
		scModel = modelInterface->GetPointer();
	}
	
	//---------------------------------------------------------------------------
	// Create geometry
	TXString			vwName (name);
	VWTransformMatrix	ma;
	GdtfUtil::ConvertMatrix(mat, ma);
	
	
	
	SceneData::GdtfGeometry* gdtfGeometry = nullptr;
	
	switch (type)
	{
		case eGdtfGeometryReference:			gdtfGeometry = fGeometry->AddGeometryReference(			vwName, scModel, ma); break;
		case eGdtfGeometryLamp:					gdtfGeometry = fGeometry->AddGeometryWithLamp(			vwName, scModel, ma); break;
		case eGdtfGeometryAxis:					gdtfGeometry = fGeometry->AddGeometryWithAxis(			vwName, scModel, ma); break;
		case eGdtfGeometryShaperFilter:			gdtfGeometry = fGeometry->AddGeometryShaper(			vwName, scModel, ma); break;
		case eGdtfGeometryColorFilter:			gdtfGeometry = fGeometry->AddGeometryColor(				vwName, scModel, ma); break;
		case eGdtfGeometryGoboFilter:			gdtfGeometry = fGeometry->AddGeometryGobo(				vwName, scModel, ma); break;
		case eGdtfGeometryBeamFilter:			gdtfGeometry = fGeometry->AddGeometryBeam(				vwName, scModel, ma); break;
		case eGdtfGeometryMediaServerCamera:	gdtfGeometry = fGeometry->AddGeometryMediaServerCamera(	vwName, scModel, ma); break;
		case eGdtfGeometryMediaServerLayer:		gdtfGeometry = fGeometry->AddGeometryMediaServerLayer(	vwName, scModel, ma); break;
		case eGdtfGeometryMediaServerMaster:	gdtfGeometry = fGeometry->AddGeometryMediaServerMaster(	vwName, scModel, ma); break;
        case eGdtfGeometryDisplay:              gdtfGeometry = fGeometry->AddGeometryDisplay(          	vwName, scModel, ma); break;
        case eGdtfGeometryLaser:              	gdtfGeometry = fGeometry->AddGeometryLaser(          	vwName, scModel, ma); break;
        case eGdtfGeometryWiringObject:         gdtfGeometry = fGeometry->AddGeometryWiringObject(      vwName, scModel, ma); break;
        case eGdtfGeometryInventory:            gdtfGeometry = fGeometry->AddGeometryInventory(         vwName, scModel, ma); break;
        case eGdtfGeometryStructure:            gdtfGeometry = fGeometry->AddGeometryStructure(         vwName, scModel, ma); break;
        case eGdtfGeometrySupport:              gdtfGeometry = fGeometry->AddGeometrySupport(          	vwName, scModel, ma); break;
        case eGdtfGeometryMagnet:              	gdtfGeometry = fGeometry->AddGeometryMagnet(          	vwName, scModel, ma); break;
		case eGdtfGeometry:						gdtfGeometry = fGeometry->AddGeometry(					vwName, scModel, ma); break;
			
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
		CGdtfGeometryImpl* pResultInterface = static_cast<CGdtfGeometryImpl* >(pGeometryObj);
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetLampType(EGdtfLampType &lampType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lampType = lamp->GetLampType();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetPowerConsumption(double &powerConsumption)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	powerConsumption = lamp->GetPowerConsumption();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetLuminousIntensity(double &luminousIntensity)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	luminousIntensity = lamp->GetLuminousIntensity();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetColorTemperature(double &colorTemperature)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	colorTemperature = lamp->GetColorTemperature();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBeamAngle(double &beamAngle)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	beamAngle = lamp->GetBeamAngle();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetFieldAngle(double & fldAngle)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	fldAngle = lamp->GetFieldAngle();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBeamRadius(double & radius)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	radius= lamp->GetBeamRadius();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetThrowRatio(double & ratio)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	ratio= lamp->GetThrowRatio();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetRectangleRatio(double & ratio)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	ratio= lamp->GetRectangleRatio();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBeamType(GdtfDefines::EGdtfBeamType & type)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	type = lamp->GetBeamType();
	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetColorIndex(Sint32 & idx)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	idx= lamp->GetColorIndex();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetEmitterSpectrum(IGdtfPhysicalEmitter** outEmitter)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfPhysicalEmitterImpl*		pEmitterObj		= nullptr;
	SceneData::GdtfPhysicalEmitter*	gdtfEmitter 	= lamp->GetEmitterSpectrum();

	if(!gdtfEmitter) { return kVCOMError_NotSet; }
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**) & pEmitterObj)))
	{
		// Check Casting
		CGdtfPhysicalEmitterImpl* pResultInterface = static_cast<CGdtfPhysicalEmitterImpl* >(pEmitterObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfEmitter);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*outEmitter)
	{
		(*outEmitter)->Release();
		*outEmitter		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outEmitter		= pEmitterObj;

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetName(MvrString name)
{
	if( ! fGeometry) return kVCOMError_NotInitialized;	
	
    fGeometry->SetName(name);

   	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetModel(IGdtfModel ** model)
{
    // Check Data	
    if( ! fGeometry) return kVCOMError_NotInitialized;
    
	//---------------------------------------------------------------------------
	// Initialize Object
	SceneData::GdtfModel*	gdtfModel = fGeometry->GetModelRef();
	if ( ! gdtfModel)	{ return kVCOMError_NotSet; }
	
    CGdtfModelImpl*			pModelObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfModel, (IVWUnknown**) & pModelObj)))
    {
        // Check Casting
        CGdtfModelImpl* pResultInterface = static_cast<CGdtfModelImpl* >(pModelObj);
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
    // Check Incoming Object
    if (*model)
    {
        (*model)->Release();
        *model		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *model	= pModelObj;
    
    return kVCOMError_NoError;   
}
    

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetTransformMatrix(STransformMatrix & transformMatrix)
{
    // Check Data
	if( ! fGeometry) return kVCOMError_NotInitialized;	
	
    VWTransformMatrix vwMatrix;
    GdtfUtil::ConvertMatrix(transformMatrix, vwMatrix);

    fGeometry->SetTransformMatrix(vwMatrix);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetLampType(EGdtfLampType lampType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetLampType(lampType);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetPowerConsumption(double powerConsumption)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetPowerConsumption(powerConsumption);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetLuminousIntensity(double luminousIntensity)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetLuminousIntensity(luminousIntensity);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetColorTemperature(double colorTemperature)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetColorTemperature(colorTemperature);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetBeamAngle(double beamAngle)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetBeamAngle(beamAngle);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetFieldAngle(double fldAngle)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetFieldAngle(fldAngle);
	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetBeamRadius(double radius)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetBeamRadius(radius);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetThrowRatio(double ratio)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetThrowRatio(ratio);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetRectangleRatio(double ratio)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetRectangleRatio(ratio);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetBeamType(EGdtfBeamType type)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
    lamp->SetBeamType(type);
	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetColorIndex(Sint32 idx)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetColorIndex(idx);
	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetEmitterSpectrum(IGdtfPhysicalEmitter* newEmitter)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = static_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfPhysicalEmitterImpl* pEmitterObj = static_cast<CGdtfPhysicalEmitterImpl*> (newEmitter);
	if(!pEmitterObj) { return kVCOMError_InvalidArg; }
	
	SceneData::GdtfPhysicalEmitter* gdtfEmitter = pEmitterObj->GetPointer();
	lamp->SetEmitterSpectrum(gdtfEmitter);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBreakCount(size_t &count)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryReference) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryReferencePtr ref = static_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
	if ( ! ref) { return kVCOMError_Failed; }
	
	count = ref->GetBreakArray().size();
	return kVCOMError_NoError;
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBreakAt(size_t at, VectorworksMVR::IGdtfBreak **gdtfBreak)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryReference) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryReferencePtr ref = static_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
	if ( ! ref) { return kVCOMError_Failed; }
	
	// check overflow
	if (ref->GetBreakArray().size() < at) { return kVCOMError_OutOfBounds; }
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfBreakImpl*			pBreakObj	= nullptr;
	SceneData::GdtfBreak*	gdtfBreakP = ref->GetBreakArray()[at];
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfBreak, (IVWUnknown**) & pBreakObj)))
	{
		// Check Casting
		CGdtfBreakImpl* pResultInterface = static_cast<CGdtfBreakImpl* >(pBreakObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfBreakP);
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
	if (*gdtfBreak)
	{
		(*gdtfBreak)->Release();
		*gdtfBreak		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*gdtfBreak		= pBreakObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::CreateBreak(Sint32 dmxBreak, DMXAddress address, IGdtfBreak** gdtfBreak)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryReference) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryReferencePtr ref = static_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
	if ( ! ref) { return kVCOMError_Failed; }
	
	
	SceneData::GdtfBreakPtr cdBreak = ref->AddBreak();
	cdBreak->SetDmxBreak(dmxBreak);
	cdBreak->SetDmxAddress(address);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfBreakImpl*			pBreakObj	= nullptr;
	
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfBreak, (IVWUnknown**) & pBreakObj)))
	{
		// Check Casting
		CGdtfBreakImpl* pResultInterface = static_cast<CGdtfBreakImpl* >(pBreakObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(cdBreak);
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
	if (*gdtfBreak)
	{
		(*gdtfBreak)->Release();
		*gdtfBreak		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*gdtfBreak		= pBreakObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetGeometryReference(IGdtfGeometry** geometry)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryReference) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryReferencePtr ref = static_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
	if ( ! ref) { return kVCOMError_Failed; }
	
		
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfGeometryImpl*			pGeoObj			= nullptr;
	SceneData::GdtfGeometry*	gdtfGeometry 	= ref->GetLinkedGeometry();

	if(!gdtfGeometry) { return kVCOMError_NotSet; }
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeoObj)))
	{
		// Check Casting
		CGdtfGeometryImpl* pResultInterface = static_cast<CGdtfGeometryImpl* >(pGeoObj);
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
	// Check Incoming Object
	if (*geometry)
	{
		(*geometry)->Release();
		*geometry		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*geometry		= pGeoObj;
	
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetGeometryReference(IGdtfGeometry*  geometry)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryReference) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryReferencePtr ref = static_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
	if ( ! ref) { return kVCOMError_Failed; }
	
		
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfGeometryImpl*			pGeoObj			= static_cast<CGdtfGeometryImpl*> (geometry);
	if(!pGeoObj) { return kVCOMError_InvalidArg; }
	
	SceneData::GdtfGeometry*	gdtfGeometryToSet 	= pGeoObj->GetPointer();
	ref->SetLinkedGeometry(gdtfGeometryToSet);
	
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfGeometryImpl::GetTexture() 
{
	if(!fGeometry) return "";

	if( fGeometryType != EGdtfObjectType::eGdtfGeometryDisplay) return "";

	SceneData::GdtfGeometryDisplayPtr display = static_cast<SceneData::GdtfGeometryDisplayPtr>(fGeometry);
	if(!display) return "";

	return display->GetTexture().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetTexture(MvrString texture)
{
	if (!fGeometry) return kVCOMError_NotInitialized;
	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryDisplay) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryDisplayPtr display = static_cast<SceneData::GdtfGeometryDisplayPtr>(fGeometry);
	if(!display) return kVCOMError_Failed;

	display->SetTexture(texture);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCountLinkedDmxChannel(size_t& count, IGdtfDmxMode * forMode)
{
	// Get Count
	count = 0;

	// Check interface
	CGdtfDmxModeImpl* modeInterface = static_cast<CGdtfDmxModeImpl*>(forMode);
	if( ! modeInterface) { return kVCOMError_InvalidArg; }

	// Get Array
	SceneData::GdtfDmxModePtr 		scMode 	 = modeInterface->getPointer();
	SceneData::TGdtfDmxChannelArray channels = scMode->GetChannelsForGeometry(fGeometry);

	count = channels.size();
	

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetLinkedDmxChannelAt(size_t at, IGdtfDmxChannel** outChannel, IGdtfDmxMode * forMode)
{
	// Check interface
	CGdtfDmxModeImpl* modeInterface = static_cast<CGdtfDmxModeImpl*>(forMode);
	if( ! modeInterface) { return kVCOMError_InvalidArg; }

	// Get Array
	SceneData::GdtfDmxModePtr 		scMode 	 = modeInterface->getPointer();
	SceneData::TGdtfDmxChannelArray channels = scMode->GetChannelsForGeometry(fGeometry);

	// Check Bound
	if( at >= channels.size()) {return kVCOMError_OutOfBounds; }

	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfDmxChannelImpl*			pChannObj			= nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxChannel, (IVWUnknown**) & pChannObj)))
	{
		// Check Casting
		CGdtfDmxChannelImpl* pResultInterface = static_cast<CGdtfDmxChannelImpl* >(pChannObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(channels[at]);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*outChannel)
	{
		(*outChannel)->Release();
		*outChannel		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*outChannel		= pChannObj;

	return kVCOMError_NoError;
}

//---------------------------------------------------------------------------
// Laser

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetColorType(EGdtfLaserColorType& colorType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	colorType = laser->GetColorType();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetLaserColor(double& wavelength)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	wavelength = laser->GetColor();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetOutputStrength(double& outputStrength)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	outputStrength = laser->GetOutputStrength();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetEmitter(VectorworksMVR::IGdtfPhysicalEmitter** emitter)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }

	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfPhysicalEmitter*	gdtfEmitter = laser->GetEmitter();
	if ( ! gdtfEmitter)	{ return kVCOMError_NotSet; }

    CGdtfPhysicalEmitterImpl* pEmitterObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPhysicalEmitter, (IVWUnknown**) & pEmitterObj)))
    {
        // Check Casting
        CGdtfPhysicalEmitterImpl* pResultInterface = static_cast<CGdtfPhysicalEmitterImpl* >(pEmitterObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfEmitter);
        }
        else
        {
            pResultInterface->Release();
            pResultInterface = nullptr;
            return kVCOMError_NoInterface;
        }
    }
    
    //---------------------------------------------------------------------------
    // Check Incoming Object
    if (*emitter)
    {
        (*emitter)->Release();
        *emitter = NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *emitter = pEmitterObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBeamDiameter(double& beamDiameter)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	beamDiameter = laser->GetBeamDiameter();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBeamDivergenceMin(double& beamDivergenceMin)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	beamDivergenceMin = laser->GetBeamDivergenceMin();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBeamDivergenceMax(double& beamDivergenceMax)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	beamDivergenceMax = laser->GetBeamDivergenceMax();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetScanAnglePan(double& scanAnglePan)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	scanAnglePan = laser->GetScanAnglePan();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetScanAngleTilt(double& scanAngleTilt)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	scanAngleTilt = laser->GetScanAngleTilt();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetScanSpeed(double& scanSpeed)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	scanSpeed = laser->GetScanSpeed();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetColorType(EGdtfLaserColorType colorType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetColorType(colorType);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetLaserColor(double wavelength)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetColor(wavelength);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetOutputStrength(double outputStrength)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetOutputStrength(outputStrength);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetEmitter(IGdtfPhysicalEmitter* emitter)
{
	// Check Pointer
	if ( ! fGeometry)	{ return kVCOMError_NotInitialized; }
	if ( ! emitter)		{ return kVCOMError_InvalidArg; }

	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;

	// Cast laser	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }

	// Cast emitter	
	CGdtfPhysicalEmitterImpl* emitterImpl = static_cast<CGdtfPhysicalEmitterImpl*>(emitter);
	if ( ! emitterImpl)	{ return kVCOMError_Failed; }
	
	SceneData::GdtfPhysicalEmitter* gdtfEmitter = emitterImpl->GetPointer();
	if ( ! gdtfEmitter)		{ return kVCOMError_Failed; }
	
	laser->SetEmitter(gdtfEmitter);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetBeamDiameter(double beamDiameter)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetBeamDiameter(beamDiameter);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetBeamDivergenceMin(double beamDivergenceMin)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetBeamDivergenceMin(beamDivergenceMin);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetBeamDivergenceMax(double beamDivergenceMax)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetBeamDivergenceMax(beamDivergenceMax);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetScanAnglePan(double scanAnglePan)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetScanAnglePan(scanAnglePan);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetScanAngleTilt(double scanAngleTilt)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetScanAngleTilt(scanAngleTilt);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetScanSpeed(double scanSpeed)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaser* laser = static_cast<SceneData::GdtfGeometryLaser*>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	laser->SetScanSpeed(scanSpeed);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetLaserProtocolCount(size_t &count)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaserPtr laser = static_cast<SceneData::GdtfGeometryLaserPtr>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	count = laser->GetLaserProtocolArray().size();
	return kVCOMError_NoError;
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetLaserProtocolAt(size_t at, VectorworksMVR::IGdtfLaserProtocol** laserProtocol)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaserPtr laser = static_cast<SceneData::GdtfGeometryLaserPtr>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	// check overflow
	if (laser->GetLaserProtocolArray().size() < at) { return kVCOMError_OutOfBounds; }
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfLaserProtocolImpl*			pLaserProtocolObj = nullptr;
	SceneData::GdtfLaserProtocol*	gdtfLaserProtocol = laser->GetLaserProtocolArray()[at];
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfLaserProtocol, (IVWUnknown**) & pLaserProtocolObj)))
	{
		// Check Casting
		CGdtfLaserProtocolImpl* pResultInterface = static_cast<CGdtfLaserProtocolImpl* >(pLaserProtocolObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfLaserProtocol);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*laserProtocol)
	{
		(*laserProtocol)->Release();
		*laserProtocol = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*laserProtocol = pLaserProtocolObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::CreateLaserProtocol(MvrString name, VectorworksMVR::IGdtfLaserProtocol** laserProtocol)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLaser) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLaserPtr laser = static_cast<SceneData::GdtfGeometryLaserPtr>(fGeometry);
	if ( ! laser) { return kVCOMError_Failed; }
	
	SceneData::GdtfLaserProtocolPtr gdtfLaserProtocol = laser->CreateLaserProtocol(name);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfLaserProtocolImpl* pLaserProtocolObj	= nullptr;
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfLaserProtocol, (IVWUnknown**) & pLaserProtocolObj)))
	{
		// Check Casting
		CGdtfLaserProtocolImpl* pResultInterface = static_cast<CGdtfLaserProtocolImpl* >(pLaserProtocolObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfLaserProtocol);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*laserProtocol)
	{
		(*laserProtocol)->Release();
		*laserProtocol = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*laserProtocol = pLaserProtocolObj;
	
	return kVCOMError_NoError;
}

//---------------------------------------------------------------------------
// WiringObject

MvrString VectorworksMVR::CGdtfGeometryImpl::GetConnectorType() 
{
	if(!fGeometry) return "";

	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return "";

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return "";

	return wiringObject->GetConnectorType().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetComponentType(EGdtfComponentType& componentType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	componentType = wiringObject->GetComponentType();
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfGeometryImpl::GetSignalType() 
{
	if(!fGeometry) return "";

	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return "";

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return "";

	return wiringObject->GetSignalType().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetPinCount(size_t& pinCount)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	pinCount = wiringObject->GetPinCount();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetSignalLayer(size_t& signalLayer)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	signalLayer = wiringObject->GetSignalLayer();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetOrientation(EGdtfOrientation& orientation)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	orientation = wiringObject->GetOrientation();
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfGeometryImpl::GetWireGroup() 
{
	if(!fGeometry) return "";

	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return "";

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return "";

	return wiringObject->GetWireGroup().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetElectricalPayLoad(double& electricalPayLoad)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	electricalPayLoad = wiringObject->GetElectricalPayLoad();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetVoltageRangeMin(double& voltageRangeMin)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	voltageRangeMin = wiringObject->GetVoltageRangeMin();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetVoltageRangeMax(double& voltageRangeMax)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	voltageRangeMax = wiringObject->GetVoltageRangeMax();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetFrequencyRangeMin(double& frequencyRangeMin)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	frequencyRangeMin = wiringObject->GetFrequencyRangeMin();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetFrequencyRangeMax(double& frequencyRangeMax)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	frequencyRangeMax = wiringObject->GetFrequencyRangeMax();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCosPhi(double& cosPhi)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	cosPhi = wiringObject->GetCosPhi();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetMaxPayLoad(double& maxPayload)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	maxPayload = wiringObject->GetMaxPayLoad();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetVoltage(double& voltage)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	voltage = wiringObject->GetVoltage();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetFuseCurrent(double& fuseCurrent)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	fuseCurrent = wiringObject->GetFuseCurrent();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetFuseRating(EGdtfFuseRating& fuseRating)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	fuseRating = wiringObject->GetFuseRating();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetConnectorType(MvrString connectorType)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetConnectorType(connectorType);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetComponentType(EGdtfComponentType componentType)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetComponentType(componentType);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetSignalType(MvrString signalType)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetSignalType(signalType);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetPinCount(size_t pinCount)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetPinCount(pinCount);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetSignalLayer(size_t signalLayer)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetSignalLayer(signalLayer);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetOrientation(EGdtfOrientation orientation)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetOrientation(orientation);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetWireGroup(MvrString wireGroup)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetWireGroup(wireGroup);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetElectricalPayLoad(double electricalPayLoad)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetElectricalPayLoad(electricalPayLoad);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetVoltageRangeMin(double voltageRangeMin)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetVoltageRangeMin(voltageRangeMin);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetVoltageRangeMax(double voltageRangeMax)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetVoltageRangeMax(voltageRangeMax);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetFrequencyRangeMin(double frequencyRangeMin)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetFrequencyRangeMin(frequencyRangeMin);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetFrequencyRangeMax(double frequencyRangeMax)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetFrequencyRangeMax(frequencyRangeMax);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCosPhi(double cosPhi)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetCosPhi(cosPhi);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetMaxPayLoad(double maxPayload)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetMaxPayLoad(maxPayload);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetVoltage(double voltage)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetVoltage(voltage);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetFuseCurrent(double fuseCurrent)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetFuseCurrent(fuseCurrent);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetFuseRating(EGdtfFuseRating fuseRating)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if(!wiringObject) return kVCOMError_Failed;

	wiringObject->SetFuseRating(fuseRating);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetPinPatchCount(size_t &count)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	count = wiringObject->GetPinPatchArray().size();
	return kVCOMError_NoError;
};

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetPinPatchAt(size_t at, VectorworksMVR::IGdtfPinPatch** pinPatch)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }
	
	// check overflow
	if (wiringObject->GetPinPatchArray().size() < at) { return kVCOMError_OutOfBounds; }
	
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfPinPatchImpl*			pPinPatchObj = nullptr;
	SceneData::GdtfPinPatch*	gdtfPinPatch = wiringObject->GetPinPatchArray()[at];
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPinPatch, (IVWUnknown**) & pPinPatchObj)))
	{
		// Check Casting
		CGdtfPinPatchImpl* pResultInterface = static_cast<CGdtfPinPatchImpl* >(pPinPatchObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfPinPatch);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*pinPatch)
	{
		(*pinPatch)->Release();
		*pinPatch = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*pinPatch = pPinPatchObj;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::CreatePinPatch(VectorworksMVR::IGdtfGeometry* toWiringObject, size_t fromPin, size_t toPin, VectorworksMVR::IGdtfPinPatch** pinPatch)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryWiringObject) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryWiringObjectPtr wiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(fGeometry);
	if ( ! wiringObject) { return kVCOMError_Failed; }

	// Check the argument type
	if ( ! toWiringObject) { return kVCOMError_InvalidArg; }

	CGdtfGeometryImpl* toWiringObjectImpl = static_cast<CGdtfGeometryImpl*>(toWiringObject);
	if ( ! toWiringObjectImpl)	{ return kVCOMError_InvalidArg; }

	SceneData::GdtfGeometryPtr gdtfGeometry = toWiringObjectImpl->GetPointer();

	if ( gdtfGeometry->GetObjectType() != EGdtfObjectType::eGdtfGeometryWiringObject) { return kVCOMError_InvalidArg; }

	SceneData::GdtfGeometryWiringObjectPtr gdtfToWiringObject = static_cast<SceneData::GdtfGeometryWiringObjectPtr>(gdtfGeometry);
	if ( ! gdtfToWiringObject)		{ return kVCOMError_InvalidArg; }
	
	SceneData::GdtfPinPatchPtr gdtfPinPatch = wiringObject->CreatePinPatch(gdtfToWiringObject, fromPin, toPin);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfPinPatchImpl* pPinPatchObj	= nullptr;
	
	
	// Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfPinPatch, (IVWUnknown**) & pPinPatchObj)))
	{
		// Check Casting
		CGdtfPinPatchImpl* pResultInterface = static_cast<CGdtfPinPatchImpl* >(pPinPatchObj);
		if (pResultInterface)
		{
			pResultInterface->SetPointer(gdtfPinPatch);
		}
		else
		{
			pResultInterface->Release();
			pResultInterface = nullptr;
			return kVCOMError_NoInterface;
		}
	}
	
	//---------------------------------------------------------------------------
	// Check Incoming Object
	if (*pinPatch)
	{
		(*pinPatch)->Release();
		*pinPatch = NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*pinPatch = pPinPatchObj;
	
	return kVCOMError_NoError;
}

//---------------------------------------------------------------------------
// Inventory
VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetInventoryCount(size_t& count)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryInventory) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryInventoryPtr inventory = static_cast<SceneData::GdtfGeometryInventoryPtr>(fGeometry);
	if ( ! inventory) { return kVCOMError_Failed; }
	
	count = inventory->GetCount();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetInventoryCount(size_t count)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryInventory) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryInventoryPtr inventory = static_cast<SceneData::GdtfGeometryInventoryPtr>(fGeometry);
	if(!inventory) return kVCOMError_Failed;

	inventory->SetCount(count);
	return kVCOMError_NoError;
}

//---------------------------------------------------------------------------
// Structure

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetStructureLinkedGeometry(VectorworksMVR::IGdtfGeometry** geometry)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if(!structure) return kVCOMError_Failed;
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfGeometry* gdtfGeometry = structure->GetLinkedGeometry();
	if ( ! gdtfGeometry) { return kVCOMError_NotSet; }

    CGdtfGeometryImpl* pGeometry = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeometry)))
    {
        // Check Casting
        CGdtfGeometryImpl* pResultInterface = static_cast<CGdtfGeometryImpl* >(pGeometry);
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
    // Check Incoming Object
    if (*geometry)
    {
        (*geometry)->Release();
        *geometry = NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *geometry = pGeometry;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetStructureType(GdtfDefines::EGdtfStructureType& structureType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if ( ! structure) { return kVCOMError_Failed; }
	
	structureType = structure->GetStructureType();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCrossSectionType(GdtfDefines::EGdtfCrossSectionType& crossSectionType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if ( ! structure) { return kVCOMError_Failed; }
	
	crossSectionType = structure->GetCrossSectionType();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCrossSectionHeight(double& crossSectionHeight)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if ( ! structure) { return kVCOMError_Failed; }
	
	crossSectionHeight = structure->GetCrossSectionHeight();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCrossSectionWallThickness(double& crossSectionWallThickness)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if ( ! structure) { return kVCOMError_Failed; }
	
	crossSectionWallThickness = structure->GetCrossSectionWallThickness();
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfGeometryImpl::GetTrussCrossSection() 
{
	if(!fGeometry) return "";

	// Check if it is the right type
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return "";

	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if(!structure) return "";

	return structure->GetTrussCrossSection().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetStructureLinkedGeometry(IGdtfGeometry* linkedGeometry)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if ( ! structure) { return kVCOMError_Failed; }
	
		
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfGeometryImpl* pGeoObj = static_cast<CGdtfGeometryImpl*> (linkedGeometry);
	if(!pGeoObj) { return kVCOMError_InvalidArg; }
	
	SceneData::GdtfGeometry* gdtfGeometryToSet = pGeoObj->GetPointer();
	structure->SetLinkedGeometry(gdtfGeometryToSet);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetStructureType(GdtfDefines::EGdtfStructureType structureType)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if(!structure) return kVCOMError_Failed;

	structure->SetStructureType(structureType);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCrossSectionType(GdtfDefines::EGdtfCrossSectionType crossSectionType)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if(!structure) return kVCOMError_Failed;

	structure->SetCrossSectionType(crossSectionType);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCrossSectionHeight(double crossSectionHeight)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if(!structure) return kVCOMError_Failed;

	structure->SetCrossSectionHeight(crossSectionHeight);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCrossSectionWallThickness(double crossSectionWallThickness)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if(!structure) return kVCOMError_Failed;

	structure->SetCrossSectionWallThickness(crossSectionWallThickness);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetTrussCrossSection(MvrString trussCrossSection)
{
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometryStructure) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometryStructurePtr structure = static_cast<SceneData::GdtfGeometryStructurePtr>(fGeometry);
	if(!structure) return kVCOMError_Failed;

	structure->SetTrussCrossSection(trussCrossSection);
	return kVCOMError_NoError;
}

//---------------------------------------------------------------------------
// Support

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetSupportType(GdtfDefines::EGdtfSupportType& supportType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	supportType = support->GetSupportType();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCapacityX(double& capacityX)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	capacityX = support->GetCapacityX();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCapacityY(double& capacityY)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	capacityY = support->GetCapacityY();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCapacityZ(double& capacityZ)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	capacityZ = support->GetCapacityZ();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCapacityXX(double& capacityXX)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	capacityXX = support->GetCapacityXX();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCapacityYY(double& capacityYY)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	capacityYY = support->GetCapacityYY();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetCapacityZZ(double& capacityZZ)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	capacityZZ = support->GetCapacityZZ();
	return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfGeometryImpl::GetRopeCrossSection()
{
	if(!fGeometry) return "";

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return "";

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return "";

	return support->GetRopeCrossSection().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetRopeOffset(SVector3& ropeOffset)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	GdtfUtil::ConvertVector3(support->GetRopeOffset(), ropeOffset);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetResistanceX(double& resistanceX)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	resistanceX = support->GetResistanceX();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetResistanceY(double& resistanceY)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	resistanceY = support->GetResistanceY();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetResistanceZ(double& resistanceZ)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	resistanceZ = support->GetResistanceZ();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetResistanceXX(double& resistanceXX)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	resistanceXX = support->GetResistanceXX();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetResistanceYY(double& resistanceYY)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	resistanceYY = support->GetResistanceYY();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetResistanceZZ(double& resistanceZZ)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;
	
	resistanceZZ = support->GetResistanceZZ();
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetSupportType(GdtfDefines::EGdtfSupportType supportType)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetSupportType(supportType);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCapacityX(double capacityX)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetCapacityX(capacityX);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCapacityY(double capacityY)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetCapacityY(capacityY);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCapacityZ(double capacityZ)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetCapacityZ(capacityZ);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCapacityXX(double capacityXX)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetCapacityXX(capacityXX);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCapacityYY(double capacityYY)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetCapacityYY(capacityYY);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetCapacityZZ(double capacityZZ)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetCapacityZZ(capacityZZ);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetRopeCrossSection(MvrString ropeCrossSection)
{
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetRopeCrossSection(ropeCrossSection);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetRopeOffset(double x, double y, double z)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetRopeOffset(x, y, z);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetResistanceX(double resistanceX)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetResistanceX(resistanceX);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetResistanceY(double resistanceY)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetResistanceY(resistanceY);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetResistanceZ(double resistanceZ)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetResistanceZ(resistanceZ);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetResistanceXX(double resistanceXX)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetResistanceXX(resistanceXX);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetResistanceYY(double resistanceYY)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetResistanceYY(resistanceYY);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetResistanceZZ(double resistanceZZ)
{
	// Check Pointer
	if (!fGeometry) return kVCOMError_NotInitialized;

	// Check if it is the right type	
	if( fGeometryType != EGdtfObjectType::eGdtfGeometrySupport) return kVCOMError_WrongGeometryType;

	SceneData::GdtfGeometrySupportPtr support = static_cast<SceneData::GdtfGeometrySupportPtr>(fGeometry);
	if(!support) return kVCOMError_Failed;

	support->SetResistanceZZ(resistanceZZ);
	return kVCOMError_NoError;
}

//---------------------------------------------------------------------------
void VectorworksMVR::CGdtfGeometryImpl::SetPointer(SceneData::GdtfGeometry* geometry)
{
	fGeometry		= geometry;
	fGeometryType	= geometry->GetObjectType();
	
	ASSERTN(kEveryone,	fGeometryType == EGdtfObjectType::eGdtfGeometryAxis ||
						fGeometryType == EGdtfObjectType::eGdtfGeometry ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryLamp ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryReference ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryBeamFilter ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryGoboFilter ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryColorFilter ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryShaperFilter ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryMediaServerCamera ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryMediaServerLayer	||
						fGeometryType == EGdtfObjectType::eGdtfGeometryMediaServerMaster ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryDisplay ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryLaser ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryWiringObject ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryInventory ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryStructure ||
						fGeometryType == EGdtfObjectType::eGdtfGeometrySupport ||
						fGeometryType == EGdtfObjectType::eGdtfGeometryMagnet);
}

SceneData::GdtfGeometry* VectorworksMVR::CGdtfGeometryImpl::GetPointer()
{
	return fGeometry;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fGeometry) return kVCOMError_NotInitialized;
	
	fGeometry->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfGeometryImpl::GetBoundObject()
{
	// Check if valid
	if(!fGeometry) return nullptr;
	
	return fGeometry->GetBind();
}
