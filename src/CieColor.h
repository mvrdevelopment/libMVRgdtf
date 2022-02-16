//-----------------------------------------------------------------------------
//----- Copyright deersoft 2015 - 2017 www.deersoft.de
//-----------------------------------------------------------------------------
#pragma once

//------------------------------------------------------------------------------------
// Cie Color
namespace VectorworksMVR
{
	class CCieColor
	{
	public:
		CCieColor(double x, double y, double Y_luminance);
		CCieColor(const CRGBColor& rgb);
		CCieColor();
		~CCieColor();
		
	private:
		// "CIE 1931" values
		double fx;
		double fy;
		double fY_luminance;
		//--------------------
		
		
	private:
		void	CheckRGBValue(Uint8& value) const;
		
	public:
		double Get_x() const;
		double Get_y() const;
		double Get_Y_luminance() const;
		
		void	GetRGBColor(CRGBColor& rgb) const;
	};
	typedef CCieColor*				CCieColorPtr;
    typedef std::vector<CCieColor*>	TCCieColorArray;
};