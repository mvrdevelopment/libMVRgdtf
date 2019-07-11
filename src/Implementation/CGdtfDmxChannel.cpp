//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfDmxChannel.h"
#include "CGdtfGeometry.h"
#include "CGdtfDmxLogicalChannel.h"
#include "CGdtfAttribute.h"

using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfDmxChannelImpl::CGdtfDmxChannelImpl()
{
	fChannel = nullptr;
};

VectorworksMVR::CGdtfDmxChannelImpl::~CGdtfDmxChannelImpl()
{
    
};

MvrString VectorworksMVR::CGdtfDmxChannelImpl::GetName()
{
	// Check Pointer
	if ( ! fChannel) { return ""; }
	
    return fChannel->GetName().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetDmxBreak(Sint32 &dmxBreak)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    dmxBreak = fChannel->GetDmxBreak();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetCoarse(Sint32 &coarse)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    coarse = fChannel->GetCoarse();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetFine(Sint32 &fine)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    fine = fChannel->GetFine();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetUltra(Sint32 &ultra)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    ultra = fChannel->GetUltra();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetUber(Sint32& uber)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    uber = fChannel->GetUber();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetDefaultValue(DmxValue &defaultValue)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    defaultValue = fChannel->GetDefaultValue();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetHighlight(DmxValue &highlight)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    highlight = fChannel->GetHighlight();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::HasHighlight(bool &highlight)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	highlight = fChannel->HasHighlight();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetGeometry(VectorworksMVR::IGdtfGeometry **geo)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	

    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfGeometry* gdtfGeo = fChannel->GetGeomRef();
	if ( ! gdtfGeo)	{ return kVCOMError_NotSet; }
    
	CGdtfGeometryImpl*		 pGeoObj = nullptr;
    
    // Query Interface
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfGeometry, (IVWUnknown**) & pGeoObj)))
    {
        // Check Casting
        CGdtfGeometryImpl* pResultInterface = dynamic_cast<CGdtfGeometryImpl*>(pGeoObj);
        if (pResultInterface)
        {
            pResultInterface->SetPointer(gdtfGeo);
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
    if (*geo)
    {
        (*geo)->Release();
        *geo = NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
	*geo = pGeoObj; 
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetResolution(GdtfDefines::EGdtfChannelBitResolution & resolution)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	resolution = fChannel->GetChannelBitResolution();
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::SetDmxBreak(Sint32 dmxBreak)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	fChannel->SetDmxBreak(dmxBreak);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::SetCoarse(Sint32 coarse)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	fChannel->SetDmxCoarse(coarse);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::SetFine(Sint32 fine)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	fChannel->SetDmxFine(fine);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::SetUltra(Sint32 ultra)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	fChannel->SetDmxUltra(ultra);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::SetUber(Sint32 uber)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	fChannel->SetDmxUber(uber);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::SetDefaultValue(DmxValue defaultValue)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	fChannel->SetDefaultValue(defaultValue);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::SetHighlight(DmxValue highlight)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
	fChannel->SetHighlight(highlight);
	
	return kVCOMError_NoError;
}



VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::SetGeometry(IGdtfGeometry* geo)
{
	// Check Pointer
	if ( ! fChannel)	{ return kVCOMError_NotInitialized; }
	if ( ! geo)			{ return kVCOMError_InvalidArg; }
	
	// Cast
	CGdtfGeometryImpl* geoImpl = dynamic_cast<CGdtfGeometryImpl*>(geo);
	if( ! geoImpl)		{ return kVCOMError_Failed; }
	
	//
	SceneData::GdtfGeometryPtr scgeo = geoImpl->GetPointer();
	if ( ! scgeo) { return kVCOMError_Failed;}
	
	fChannel->SetGeomRef(scgeo);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetLogicalChannelCount(size_t &count)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    count = fChannel->GetLogicalChannelArray().size();
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::GetLogicalChannelAt(size_t at, VectorworksMVR::IGdtfDmxLogicalChannel **channel)
{
	// Check Pointer
	if ( ! fChannel) { return kVCOMError_NotInitialized; }
	
    // Check if no Overflow
    if (at >=  fChannel->GetLogicalChannelArray().size()) { return kVCOMError_OutOfBounds;  }
    
    //---------------------------------------------------------------------------
    // Initialize Object
	SceneData::GdtfDmxLogicalChannel*	gdtfDmxLogicalChannel = fChannel->GetLogicalChannelArray()[at];
    CGdtfDmxLogicalChannelImpl*			pDmxLogicalChannelObj = nullptr;
    
    // Query Interface
    if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxLogicalChannel, (IVWUnknown**) & pDmxLogicalChannelObj)))
    {
        // Check Casting
        CGdtfDmxLogicalChannelImpl* pResultInterface = dynamic_cast<CGdtfDmxLogicalChannelImpl* >(pDmxLogicalChannelObj);
        if (pResultInterface)
        {
            pResultInterface->setPointer(gdtfDmxLogicalChannel);
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
    if (*channel)
    {
        (*channel)->Release();
        *channel		= NULL;
    }
    
    //---------------------------------------------------------------------------
    // Set Out Value
    *channel		= pDmxLogicalChannelObj;
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::CreateLogicalChannel(IGdtfAttribute* attribute, IGdtfDmxLogicalChannel** channel)
{
	// Check Pointer
	if ( ! fChannel)  { return kVCOMError_NotInitialized; }
	if ( ! attribute) { return kVCOMError_InvalidArg; }
	
	CGdtfAttributeImpl* attributeImpl = dynamic_cast<CGdtfAttributeImpl*>(attribute);
	if( ! attributeImpl) { return kVCOMError_Failed; }

	SceneData::GdtfAttributePtr scAttribute = attributeImpl->GetPointer();
	if( ! scAttribute) { return kVCOMError_Failed; }
	
	SceneData::GdtfDmxLogicalChannel*	gdtfDmxLogicalChannel = fChannel->AddLogicalChannel();
	gdtfDmxLogicalChannel->SetAttribute(scAttribute);
	
	//---------------------------------------------------------------------------
	// Initialize Object
	CGdtfDmxLogicalChannelImpl*			pDmxLogicalChannelObj = nullptr;
	if (VCOM_SUCCEEDED(VWQueryInterface(IID_GdtfDmxLogicalChannel, (IVWUnknown**) & pDmxLogicalChannelObj)))
	{
		// Check Casting
		CGdtfDmxLogicalChannelImpl* pResultInterface = dynamic_cast<CGdtfDmxLogicalChannelImpl* >(pDmxLogicalChannelObj);
		if (pResultInterface)
		{
			pResultInterface->setPointer(gdtfDmxLogicalChannel);
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
	if (*channel)
	{
		(*channel)->Release();
		*channel		= NULL;
	}
	
	//---------------------------------------------------------------------------
	// Set Out Value
	*channel		= pDmxLogicalChannelObj;
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfDmxChannelImpl::setPointer(SceneData::GdtfDmxChannel *channel)
{
    fChannel = channel;
}

SceneData::GdtfDmxChannel * VectorworksMVR::CGdtfDmxChannelImpl::getPointer()
{
    return fChannel;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfDmxChannelImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fChannel) return kVCOMError_NotInitialized;
	
	fChannel->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfDmxChannelImpl::GetBoundObject()
{
	// Check if valid
	if(!fChannel) return nullptr;
	
	return fChannel->GetBind();
}
