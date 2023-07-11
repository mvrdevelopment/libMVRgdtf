//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2018 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

#include "Include/IMediaRessourceVectorInterface.h"
#include "GDTFManager.h"

namespace VectorworksMVR
{
    //----------------------------------------------------------------------------------------
    class CGdtfModelImpl : public VCOMImpl<IGdtfModel>
    {
    public:
        CGdtfModelImpl();
        virtual ~CGdtfModelImpl();
        
        virtual MvrString VCOM_CALLTYPE     GetName();
        virtual VCOMError VCOM_CALLTYPE     GetLength(double& length);
        virtual VCOMError VCOM_CALLTYPE     GetWidth(double& width);
        virtual VCOMError VCOM_CALLTYPE     GetHeight(double& height);
        virtual VCOMError VCOM_CALLTYPE     GetPrimitiveType(EGdtfModel_PrimitiveType& type);
        //        
        virtual MvrString VCOM_CALLTYPE     GetGeometryFileName();
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_3DS_FullPath();
        virtual MvrString VCOM_CALLTYPE     GetGeometryFile_3DSLow_FullPath();
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_3DSHigh_FullPath();
        virtual MvrString VCOM_CALLTYPE     GetGeometryFile_SVG_FullPath();
        virtual MvrString VCOM_CALLTYPE     GetGeometryFile_SVGSide_FullPath();
        virtual MvrString VCOM_CALLTYPE     GetGeometryFile_SVGFront_FullPath();
        virtual MvrString VCOM_CALLTYPE     GetGeometryFile_GLTF_FullPath();
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_GLTFLow_FullPath();
		virtual MvrString VCOM_CALLTYPE     GetGeometryFile_GLTFHigh_FullPath();
        
        virtual VCOMError VCOM_CALLTYPE     GetBuffer3DS(void** bufferToCopy, size_t& length);
        virtual VCOMError VCOM_CALLTYPE     GetBufferSVG(void** bufferToCopy, size_t& length);
        virtual VCOMError VCOM_CALLTYPE     GetBufferGLTF(void** bufferToCopy, size_t& length);

        virtual VCOMError VCOM_CALLTYPE     GetSVGOffsetX(double& svgOffsetX);
        virtual VCOMError VCOM_CALLTYPE     GetSVGOffsetY(double& svgOffsetY);
        virtual VCOMError VCOM_CALLTYPE     GetSVGSideOffsetX(double& svgSideOffsetX);
        virtual VCOMError VCOM_CALLTYPE     GetSVGSideOffsetY(double& svgSideOffsetY);
        virtual VCOMError VCOM_CALLTYPE     GetSVGFrontOffsetX(double& svgFrontOffsetX);
        virtual VCOMError VCOM_CALLTYPE     GetSVGFrontOffsetY(double& svgFrontOffsetY);
        
        virtual VCOMError VCOM_CALLTYPE     SetName(MvrString name);
		virtual VCOMError VCOM_CALLTYPE     SetLength(double length);
		virtual VCOMError VCOM_CALLTYPE     SetWidth(double width);
		virtual VCOMError VCOM_CALLTYPE     SetHeight(double height);
		virtual VCOMError VCOM_CALLTYPE     SetPrimitiveType(EGdtfModel_PrimitiveType type);
		virtual VCOMError VCOM_CALLTYPE     SetGeometryFile(MvrString path);

        virtual VCOMError VCOM_CALLTYPE     SetBuffer3DS(void* bufferToCopy, size_t length);
        virtual VCOMError VCOM_CALLTYPE     SetBufferSVG(void* bufferToCopy, size_t length);
        virtual VCOMError VCOM_CALLTYPE     SetBufferGLTF(void* bufferToCopy, size_t length);

        virtual VCOMError VCOM_CALLTYPE     SetSVGOffsetX(double svgOffsetX);
        virtual VCOMError VCOM_CALLTYPE     SetSVGOffsetY(double svgOffsetY);
        virtual VCOMError VCOM_CALLTYPE     SetSVGSideOffsetX(double svgSideOffsetX);
        virtual VCOMError VCOM_CALLTYPE     SetSVGSideOffsetY(double svgSideOffsetY);
        virtual VCOMError VCOM_CALLTYPE     SetSVGFrontOffsetX(double svgFrontOffsetX);
        virtual VCOMError VCOM_CALLTYPE     SetSVGFrontOffsetY(double svgFrontOffsetY);
		
		virtual VCOMError VCOM_CALLTYPE     BindToObject(void* objAddr);
		virtual void*	  VCOM_CALLTYPE     GetBoundObject();
		
    private:
        SceneData::GdtfModel* fModel;
        
    public:
        void					SetPointer(SceneData::GdtfModel* model);
		SceneData::GdtfModelPtr GetPointer();
        
    };
    const VWIID IID_GdtfModel = { 0xf0ba7bb5, 0xb8e0, 0x4b5b, {0xbe, 0x24, 0x5e, 0xd5, 0x6d, 0xcd, 0x19, 0x56}};

}
