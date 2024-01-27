//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#include "Prefix/StdAfx.h"
#include "CieColor.h"

//--------------------------------------------------------------
//
// This implementation is based on a draft from MA Lighting
// sended on 1/18/18. So Handle with care.
//
//--------------------------------------------------------------
using namespace VectorworksMVR;

CCieColor::CCieColor()
{
	// Create with a pure white
	fx = 0.31273;
	fy = 0.32902;
	fY_luminance = 100;
}

CCieColor::CCieColor(double x, double y, double Y_luminance)
{
	// Create based on the entry
	fx				= x;
	fy				= y;
	fY_luminance	= Y_luminance;
}

CCieColor::CCieColor(const CRGBColor& color)
{
	double r = color.GetRed();
	double g = color.GetGreen();
	double b = color.GetBlue();
	
	// Convert the 8bit_RGB to linear_RGB
	r /= UINT8_MAX;
	g /= UINT8_MAX;
	b /= UINT8_MAX;	
	
	// Convert RGB  to CIE_xyz // range [0..1]
	double x_tmp, y_tmp, z_tmp;

	x_tmp = (0.412424 * r + 0.357579  * g + 0.180464  * b);
	y_tmp = (0.212656 * r + 0.715158  * g + 0.0721856 * b);
	z_tmp = (0.0193324 * r + 0.119193 * g + 0.950444  * b);
		
	// Convert CIE_xyz to CIE_xyY
	if ((std::fabs(x_tmp) < 0.000001) || (std::fabs(y_tmp) < 0.000001) || (std::fabs(z_tmp) < 0.000001))
	{
		fx = 0;
		fy = 0;
		fY_luminance = 0;
	}
	else
	{
		fx			  = x_tmp / (x_tmp + y_tmp + z_tmp);
		fy			  = y_tmp / (x_tmp + y_tmp + z_tmp);
		fY_luminance  = y_tmp * 100; // Scale Y_luminance by 100. To be compatible with the scaling in the Mvr-File. Would be good to no the ranges (max x,yY) the mvr uses officialy.
	}
}

CCieColor::~CCieColor()
{
}

double CCieColor::Get_x() const
{
	return fx;
}

double CCieColor::Get_y() const
{
	return fy;
}

double CCieColor::Get_Y_luminance() const
{
	return fY_luminance;
}

void CCieColor::GetRGBColor(CRGBColor& rgb) const
{
	// Convertion Formulars/Matrix from http://www.brucelindbloom.com/
		
	double x_tmp, y_tmp, z_tmp;
	// New Rgb vals
	double r, g, b;

	// Convert CIE_xyY to CIE_XYZ		
	if (std::fabs(fy) < 0.000001) // Watch out for the case where y = 0. In that case, you may want to set X = Y = Z = 0.
	{
		x_tmp = 0;		
		y_tmp = 0;
		z_tmp = 0;
	}
	else
	{
		double fY_luminanceScaled = fY_luminance / 100; // Scale Y_luminance by 100. To be compatible with the scaling in the Mvr-File. Would be good to no the ranges (max x,yY) the mvr uses officialy.

		x_tmp = (fx * fY_luminanceScaled) / fy;
		y_tmp = fY_luminanceScaled;
		z_tmp = ((1 - fx - fy) * fY_luminanceScaled) / fy;		
	}	

	// Convert CIE_XYZ to linear RGB (values[0..1])
	r = (x_tmp * 3.24071	 + y_tmp * (-1.53726)  + z_tmp * (-0.498571));
	g = (x_tmp * (-0.969258) + y_tmp * 1.87599     + z_tmp * 0.0415557);
	b = (x_tmp * 0.0556352   + y_tmp * (-0.203996) + z_tmp * 1.05707);

	if (r > 0.0031308)  { r = 1.055 * (pow(r, (1 / 2.4))) - 0.055; }
    else                { r = 12.92 * r; }
    if (g > 0.0031308)  { g = 1.055 * (pow(g, (1 / 2.4))) - 0.055; }
    else                { g = 12.92 * g; }
    if (b > 0.0031308)  { b = 1.055 * (pow(b, (1 / 2.4))) - 0.055; }
    else             	{ b = 12.92 * b; }

	

	// Clamp between 0 and 1
	if (r < 0) { r = 0; };  if (g < 0){ g = 0; }; if (b < 0){ b = 0; };
	if (r > 1) { r = 1; };  if (g > 1){ g = 1; }; if (b > 1){ b = 1; };

	// Convert linearRGB[0..1] to sRGB [0..255]
	r *= 255;	g *= 255;	b *= 255;

	rgb.SetColor((Sint32) r, (Sint32) g, (Sint32)b);
}

void CCieColor::CheckRGBValue(Uint8& value) const
{
	if		(value < 0)		{ value = 0;	DSTOP((kEveryone, "RGB Value smaler then 0"));  }
	else if (value > 255)	{ value = 255;	DSTOP((kEveryone, "RGB Value smaler then 255"));}
}
