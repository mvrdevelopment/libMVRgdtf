//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfRevision.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfRevisionImpl::CGdtfRevisionImpl()
{
	fRevision = nullptr;
};

VectorworksMVR::CGdtfRevisionImpl::~CGdtfRevisionImpl()
{
    
};

MvrString VectorworksMVR::CGdtfRevisionImpl::GetText()
{
	// Check if valid
	if(!fRevision) return "";
	
	return fRevision->GetText().GetCharPtr();
}

VCOMError VectorworksMVR::CGdtfRevisionImpl::GetDate(STime & date)
{
	// Check if valid
	if (!fRevision) { return kVCOMError_NotInitialized; }
	
	STime local  = fRevision->GetDate();
	date.fYear 	 = local.fYear;
	date.fMonth  = local.fMonth;
	date.fDay 	 = local.fDay;
	date.fHour 	 = local.fHour;
	date.fMinute = local.fMinute;
	date.fSecond = local.fSecond;

	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRevisionImpl::SetText(MvrString txt)
{
	// Check if valid
	if(!fRevision) { return kVCOMError_NotInitialized; }
    
    fRevision->SetText(txt);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRevisionImpl::SetDate(STime date)
{
	// Check if valid
	if(!fRevision) { return kVCOMError_NotInitialized; }
    
    fRevision->SetDate(date);

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRevisionImpl::GetUserId(size_t& userId)
{
	// Check if valid
	if(!fRevision) { return kVCOMError_NotInitialized; }
    
    userId = fRevision->GetUserId();

    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRevisionImpl::SetUserId(size_t userId)
{
	// Check if valid
	if(!fRevision) { return kVCOMError_NotInitialized; }
    
    fRevision->SetUserId(userId);

    return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfRevisionImpl::GetModifiedBy()
{
	// Check if valid
	if(!fRevision) return "";
	
	return fRevision->GetModifiedBy().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRevisionImpl::SetModifiedBy(MvrString modifiedBy)
{
	// Check if valid
	if(!fRevision) { return kVCOMError_NotInitialized; }
    
    fRevision->SetModifiedBy(modifiedBy);

    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfRevisionImpl::setPointer(SceneData::GdtfRevision *revision)
{
    fRevision = revision;
}