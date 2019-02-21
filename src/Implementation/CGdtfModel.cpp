//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfModel.h"


using namespace VectorWorks::Filing;

VectorworksMVR::CGdtfModelImpl::CGdtfModelImpl()
{
	fModel = nullptr;
};

VectorworksMVR::CGdtfModelImpl::~CGdtfModelImpl()
{
    
};

MvrString VectorworksMVR::CGdtfModelImpl::GetName()
{
	// Check Pointer
	if ( ! fModel) return "";
	
    return fModel->GetName();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetLength(double &length)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    length = fModel->GetLength();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetWidth(double &width)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    width =  fModel->GetWidth();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetHeight(double &height)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    height = fModel->GetHeight();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetPrimitiveType(EGdtfModel_PrimitiveType &type)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    type = fModel->GetPrimitiveType();
    
    return kVCOMError_NoError;
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFileName()
{
	// Check Pointer
	if ( ! fModel) return "";
	
    return fModel->GetGeometryFileName().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_3DS_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_3DS_FullPath().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_SVG_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_SVG_FullPath().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetName(MvrString name)
{
	if(!fModel) return kVCOMError_NotInitialized;	
	
    fModel->SetName(name);

   	return kVCOMError_NoError;   
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetLength(double length)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetLength(length);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetWidth(double width)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetWidth(width);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetHeight(double height)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetHeight(height);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetPrimitiveType(EGdtfModel_PrimitiveType type)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetPrimitiveType(type);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetGeometryFile(MvrString path)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	TXString vwPath (path);
	fModel->SetGeometryFile(vwPath);
	
	return kVCOMError_NoError;
}

void VectorworksMVR::CGdtfModelImpl::SetPointer(SceneData::GdtfModel *model)
{
    fModel = model;
}

SceneData::GdtfModelPtr VectorworksMVR::CGdtfModelImpl::GetPointer()
{
	return fModel;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::BindToObject(void* objAddr)
{
	// Check if valid
	if(!fModel) return kVCOMError_NotInitialized;
	
	fModel->SetBind(objAddr);
	
	return kVCOMError_NoError;
}

void* VectorworksMVR::CGdtfModelImpl::GetBoundObject()
{
	// Check if valid
	if(!fModel) return nullptr;
	
	return fModel->GetBind();
}
