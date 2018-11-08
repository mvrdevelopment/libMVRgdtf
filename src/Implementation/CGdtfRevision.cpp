//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfRevision.h"


using namespace VectorWorks::Filing;

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

MvrString VectorworksMVR::CGdtfRevisionImpl::GetDate()
{
	// Check if valid
	if(!fRevision) return "";
	
    return fRevision->GetDate().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfRevisionImpl::SetText(MvrString txt)
{
	// Check if valid
	if(!fRevision) { return kVCOMError_NotInitialized; }
    
    fRevision->SetText(txt);

    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfRevisionImpl::setPointer(SceneData::GdtfRevision *revision)
{
    fRevision = revision;
}
