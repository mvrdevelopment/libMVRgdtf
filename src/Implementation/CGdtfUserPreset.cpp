//-----------------------------------------------------------------------------
//----- Copyright MVR Group
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfUserPreset.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfUserPresetImpl::CGdtfUserPresetImpl()
{
	fUserPreset = nullptr;
};

VectorworksMVR::CGdtfUserPresetImpl::~CGdtfUserPresetImpl()
{
    
};

void VectorworksMVR::CGdtfUserPresetImpl::setPointer(SceneData::GdtfUserPreset *userPreset)
{
    fUserPreset = userPreset;
}
