//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CGdtfModel.h"


using namespace VectorworksMVR::Filing;

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

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_3DSLow_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_3DSLow_FullPath().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_3DSHigh_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_3DSHigh_FullPath().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_SVG_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_SVG_FullPath().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_SVGSide_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_SVGSide_FullPath().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_SVGFront_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_SVGFront_FullPath().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_GLTF_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_GLTF_FullPath().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_GLTFLow_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_GLTFLow_FullPath().GetCharPtr();
}

MvrString VectorworksMVR::CGdtfModelImpl::GetGeometryFile_GLTFHigh_FullPath()
{
	// Check Pointer
	if ( ! fModel) return "";
	
	return fModel->GetGeometryFile_GLTFHigh_FullPath().GetCharPtr();
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetBuffer3DS(void** bufferToCopy, size_t& length)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	if (*bufferToCopy != nullptr) return kVCOMError_InvalidArg;

	fModel->GetBuffer3DS(bufferToCopy, length);
	
	if (*bufferToCopy == nullptr) return kVCOMError_NotSet;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetBufferSVG(void** bufferToCopy, size_t& length)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	if (*bufferToCopy != nullptr) return kVCOMError_InvalidArg;

	fModel->GetBufferSVG(bufferToCopy, length);

	if (*bufferToCopy == nullptr) return kVCOMError_NotSet;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetBufferGLTF(void** bufferToCopy, size_t& length)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	if (*bufferToCopy != nullptr) return kVCOMError_InvalidArg;

	fModel->GetBufferGLTF(bufferToCopy, length);

	if (*bufferToCopy == nullptr) return kVCOMError_NotSet;
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetSVGOffsetX(double& svgOffsetX)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    svgOffsetX = fModel->GetSVGOffsetX();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetSVGOffsetY(double& svgOffsetY)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    svgOffsetY = fModel->GetSVGOffsetY();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetSVGSideOffsetX(double& svgSideOffsetX)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    svgSideOffsetX = fModel->GetSVGSideOffsetX();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetSVGSideOffsetY(double& svgSideOffsetY)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    svgSideOffsetY = fModel->GetSVGSideOffsetY();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetSVGFrontOffsetX(double& svgFrontOffsetX)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    svgFrontOffsetX = fModel->GetSVGFrontOffsetX();
    
    return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::GetSVGFrontOffsetY(double& svgFrontOffsetY)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
    svgFrontOffsetY = fModel->GetSVGFrontOffsetY();
    
    return kVCOMError_NoError;
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

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetBuffer3DS(void* bufferToCopy, size_t length)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;

	fModel->SetBuffer3DS(bufferToCopy, length);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetBufferSVG(void* bufferToCopy, size_t length)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;

	fModel->SetBufferSVG(bufferToCopy, length);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetBufferGLTF(void* bufferToCopy, size_t length)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;

	fModel->SetBufferGLTF(bufferToCopy, length);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetSVGOffsetX(double svgOffsetX)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetSVGOffsetX(svgOffsetX);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetSVGOffsetY(double svgOffsetY)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetSVGOffsetY(svgOffsetY);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetSVGSideOffsetX(double svgSideOffsetX)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetSVGSideOffsetX(svgSideOffsetX);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetSVGSideOffsetY(double svgSideOffsetY)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetSVGSideOffsetY(svgSideOffsetY);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetSVGFrontOffsetX(double svgFrontOffsetX)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetSVGFrontOffsetX(svgFrontOffsetX);
	
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CGdtfModelImpl::SetSVGFrontOffsetY(double svgFrontOffsetY)
{
	// Check Pointer
	if ( ! fModel) return kVCOMError_NotInitialized;
	
	fModel->SetSVGFrontOffsetY(svgFrontOffsetY);
	
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
