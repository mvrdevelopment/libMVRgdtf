//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfUserPreset.h"


using namespace VectorWorks::Filing;

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
