//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//
#include "Prefix/StdAfx.h"
#include "RGBColor.h"

using namespace VectorworksMVR;

CRGBColor::CRGBColor()
{
	this->red		= 0;
	this->green		= 0;
	this->blue		= 0;
}

CRGBColor::CRGBColor(Sint32 r, Sint32 g, Sint32 b)
{
	this->red		= r;
	this->green		= g;
	this->blue		= b;
}

CRGBColor::CRGBColor(const CRGBColor& clr)
{
	this->red		= clr.red;
	this->green		= clr.green;
	this->blue		= clr.blue;
}

// create gradient color from 'leftColor' to 'rightColor' using percentage
// 0% = leftColor; 100% = rightColor
CRGBColor::CRGBColor(const CRGBColor& leftColor, const CRGBColor& rightColor, double dPercent)
{

	Sint32	r	= (Sint32) ( (double)( rightColor.GetRed() - leftColor.GetRed() ) * (dPercent/100) + leftColor.GetRed() );
	Sint32	g	= (Sint32) ( (double)( rightColor.GetGreen() - leftColor.GetGreen() ) * (dPercent/100) + leftColor.GetGreen() );
	Sint32	b	= (Sint32) ( (double)( rightColor.GetBlue() - leftColor.GetBlue() ) * (dPercent/100) + leftColor.GetBlue() );

	this->SetColor( r, g, b );
}

CRGBColor::~CRGBColor()
{
}

CRGBColor& CRGBColor::operator=(const CRGBColor& clr)
{
	this->red		= clr.red;
	this->green		= clr.green;
	this->blue		= clr.blue;
	return *this;
}

bool CRGBColor::operator==(const CRGBColor& clr) const
{
	return
		this->red == clr.red &&
		this->green == clr.green &&
		this->blue == clr.blue ;
}

bool CRGBColor::operator!=(const CRGBColor& clr) const
{
	return ! ( this->operator == ( clr ) );
}

Sint32 CRGBColor::GetRed() const
{
	return red;
}

void CRGBColor::SetRed(Sint32 red)
{
	this->red		= red;
}

Sint32 CRGBColor::GetGreen() const
{
	return green;
}

void CRGBColor::SetGreen(Sint32 green)
{
	this->green		= (green << 8) | green;
}

Sint32 CRGBColor::GetBlue() const
{
	return blue;
}

void CRGBColor::SetBlue(Sint32 blue)
{
	this->blue		= blue;
}

void CRGBColor::GetColor(Sint32& r, Sint32& g, Sint32& b) const
{
	r = red;
	g = green;
	b = blue;
}

void CRGBColor::SetColor(Sint32 r, Sint32 g, Sint32 b)
{
	this->red		= r;
	this->green		= g;
	this->blue		= b;
}
