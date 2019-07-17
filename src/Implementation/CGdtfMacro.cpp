//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfMacro.h"


using namespace VectorworksMVR::Filing;

VectorworksMVR::CGdtfMacroImpl::CGdtfMacroImpl()
{
	fMacro = nullptr;
};

VectorworksMVR::CGdtfMacroImpl::~CGdtfMacroImpl()
{
    
}
MvrString VectorworksMVR::CGdtfMacroImpl::GetName()
{
   	if( ! fMacro) return "";

    return fMacro->GetName();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfMacroImpl::SetName(MvrString name)
{
  	// Check if valid
	if( ! fMacro) return kVCOMError_NotInitialized;

    fMacro->SetName(name);

    return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfMacroImpl::setPointer(SceneData::GdtfMacro *macro)
{
    fMacro = macro;
}

SceneData::GdtfMacro* VectorworksMVR::CGdtfMacroImpl::getPointer()
{
    return fMacro;
}
