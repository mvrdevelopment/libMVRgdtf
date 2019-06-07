//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CUtility.h"
#include"../CieColor.h"

VectorworksMVR::CUtilityImpl::CUtilityImpl()
{
}

VectorworksMVR::CUtilityImpl::~CUtilityImpl()
{
}

VectorworksMVR::VCOMError VectorworksMVR::CUtilityImpl::CieToRgb(const CieColor& color, RGBColor& out)
{
	CCieColor cie (color.fx, color.fy, color.f_Y);

	CRGBColor rgb;
	cie.GetRGBColor(rgb);

	rgb.GetColor(out.r, out.g, out.b);
	return kVCOMError_NoError;
}

VectorworksMVR::VCOMError VectorworksMVR::CUtilityImpl::RgBToCie(const RGBColor& color, CieColor& out)
{
		CCieColor cie (CRGBColor( color.r, color.g, color.b ));
		out.fx  = cie.Get_x();
		out.fy  = cie.Get_y();
		out.f_Y = cie.Get_Y_luminance();

	return kVCOMError_NoError;
}