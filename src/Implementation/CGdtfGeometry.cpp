//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfGeometry.h"
#include "CGdtfModel.h"
#include "CGdtfBreak.h"
#include "CMediaRessourceVectorImpl.h"
#include "Utility.h"

using namespace VectorWorks::Filing;

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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetTransformMatrix(VectorworksMVR::STransformMatrix &transformMatrix)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
    VWFC::Math::VWTransformMatrix ma;
    
    fGeometry->GetTransformMatrix(ma);
    
	Utility::ConvertMatrix(ma, transformMatrix);
	
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::CreateGeometry(EGdtfObjectType type, MvrString name, IGdtfModel* model, const STransformMatrix& mat, IGdtfGeometry** geometry)
{
	// Check if Set
	if(!fGeometry) { return kVCOMError_NotInitialized;}
		
	//---------------------------------------------------------------------------
	// Extract Model
	SceneData::GdtfModelPtr scModel = nullptr;

	CGdtfModelImpl* modelInterface = dynamic_cast<CGdtfModelImpl*>(model);
	if( modelInterface)
	{
		scModel = modelInterface->GetPointer();
	}
	
	//---------------------------------------------------------------------------
	// Create geometry
	TXString			vwName (name);
	VWTransformMatrix	ma;
	Utility::ConvertMatrix(mat, ma);
	
	
	
	SceneData::GdtfGeometry* gdtfGeometry = nullptr;
	
	switch (type)
	{
		case eGdtfGeometryReference:	gdtfGeometry = fGeometry->AddGeometryReference(	vwName, scModel, ma); break;
		case eGdtfGeometryLamp:			gdtfGeometry = fGeometry->AddGeometryWithLamp(	vwName, scModel, ma); break;
		case eGdtfGeometryAxis:			gdtfGeometry = fGeometry->AddGeometryWithAxis(	vwName, scModel, ma); break;
		case eGdtfGeometryShaperFilter:	gdtfGeometry = fGeometry->AddGeometryShaper(	vwName, scModel, ma); break;
		case eGdtfGeometryColorFilter:	gdtfGeometry = fGeometry->AddGeometryColor(		vwName, scModel, ma); break;
		case eGdtfGeometryGoboFilter:	gdtfGeometry = fGeometry->AddGeometryGobo(		vwName, scModel, ma); break;
		case eGdtfGeometryBeamFilter:	gdtfGeometry = fGeometry->AddGeometryBeam(		vwName, scModel, ma); break;
		case eGdtfGeometry:				gdtfGeometry = fGeometry->AddGeometry(			vwName, scModel, ma); break;
			
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetStartAngle(double &angle)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryAxis) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryAxis* axis = dynamic_cast<SceneData::GdtfGeometryAxis*>(fGeometry);
	if ( ! axis) { return kVCOMError_Failed; }
	
	angle = axis->GetStartAngle();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetEndAngle(double &angle)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryAxis) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryAxis* axis = dynamic_cast<SceneData::GdtfGeometryAxis*>(fGeometry);
	if ( ! axis) { return kVCOMError_Failed; }
	
	angle = axis->GetEndAngle();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetSpeed(double &speed)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryAxis) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryAxis* axis = dynamic_cast<SceneData::GdtfGeometryAxis*>(fGeometry);
	if ( ! axis) { return kVCOMError_Failed; }
	
	speed = axis->GetSpeed();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetStartAngle(double angle)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryAxis) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryAxis* axis = dynamic_cast<SceneData::GdtfGeometryAxis*>(fGeometry);
	if ( ! axis) { return kVCOMError_Failed; }
	
	axis->SetStartAngle(angle);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetEndAngle(double angle)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryAxis) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryAxis* axis = dynamic_cast<SceneData::GdtfGeometryAxis*>(fGeometry);
	if ( ! axis) { return kVCOMError_Failed; }
	
	axis->SetEndAngle(angle);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetSpeed(double speed)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryAxis) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryAxis* axis = dynamic_cast<SceneData::GdtfGeometryAxis*>(fGeometry);
	if ( ! axis) { return kVCOMError_Failed; }
	
	axis->SetSpeed(speed);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetLampType(EGdtfLampType &lampType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	radius= lamp->GetBeamRadius();
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBeamType(GdtfDefines::EGdtfBeamType & type)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	idx= lamp->GetColorIndex();
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
    *model	= pModelObj;
    
    return kVCOMError_NoError;   
 }
    

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetTransformMatrix(STransformMatrix & transformMatrix)
{
    // Check Data
	if( ! fGeometry) return kVCOMError_NotInitialized;	
	
    VWTransformMatrix vwMatrix;
    Utility::ConvertMatrix(transformMatrix, vwMatrix);

    fGeometry->SetTransformMatrix(vwMatrix);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetLampType(EGdtfLampType lampType)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetBeamRadius(radius);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetBeamType(EGdtfBeamType type)
{
	// Check Pointer
	if( ! fGeometry) return kVCOMError_NotInitialized;
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryLamp) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
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
	
	SceneData::GdtfGeometryLamp* lamp = dynamic_cast<SceneData::GdtfGeometryLamp*>(fGeometry);
	if ( ! lamp) { return kVCOMError_Failed; }
	
	lamp->SetColorIndex(idx);
	return kVCOMError_NoError;    
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::GetBreakCount(size_t &count)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryReference) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryReferencePtr ref = dynamic_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
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
	
	SceneData::GdtfGeometryReferencePtr ref = dynamic_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
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
		CGdtfBreakImpl* pResultInterface = dynamic_cast<CGdtfBreakImpl* >(pBreakObj);
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
	
	SceneData::GdtfGeometryReferencePtr ref = dynamic_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
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
		CGdtfBreakImpl* pResultInterface = dynamic_cast<CGdtfBreakImpl* >(pBreakObj);
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
	
	SceneData::GdtfGeometryReferencePtr ref = dynamic_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
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
		CGdtfGeometryImpl* pResultInterface = dynamic_cast<CGdtfGeometryImpl* >(pGeoObj);
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
	*geometry		= pGeoObj;
	
	return kVCOMError_NoError;
}


VectorworksMVR::VCOMError VectorworksMVR::CGdtfGeometryImpl::SetGeometryReference(IGdtfGeometry*  geometry)
{
	// Check Pointer
	if ( ! fGeometry) { return kVCOMError_NotInitialized; }
	
	// Check if it is the right type
	if ( fGeometryType != EGdtfObjectType::eGdtfGeometryReference) return kVCOMError_WrongGeometryType;
	
	SceneData::GdtfGeometryReferencePtr ref = dynamic_cast<SceneData::GdtfGeometryReferencePtr>(fGeometry);
	if ( ! ref) { return kVCOMError_Failed; }
	
		
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfGeometryImpl*			pGeoObj			= dynamic_cast<CGdtfGeometryImpl*> (geometry);
	if(!pGeoObj) { return kVCOMError_InvalidArg; }
	
	SceneData::GdtfGeometry*	gdtfGeometryToSet 	= pGeoObj->GetPointer();
	ref->SetLinkedGeometry(gdtfGeometryToSet);
	
	return kVCOMError_NoError;
}


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
						fGeometryType == EGdtfObjectType::eGdtfGeometryShaperFilter);
	
	
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
