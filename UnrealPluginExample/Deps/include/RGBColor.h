//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VectorworksMVR
{
	class CRGBColor
	{
	public:
					CRGBColor();
					CRGBColor(Sint32 r, Sint32 g, Sint32 b);
					CRGBColor(const CRGBColor& clr);
					// create gradient color from 'leftColor' to 'rightColor' using percentage
					// 0% = leftColor; 100% = rightColor
					CRGBColor(const CRGBColor& leftColor, const CRGBColor& rightColor, double dPercent);
		virtual		~CRGBColor();

		CRGBColor&	operator=(const CRGBColor& clr);

		bool		operator==(const CRGBColor& clr) const;
		bool		operator!=(const CRGBColor& clr) const;

		Sint32		GetRed() const;
		Sint32		GetGreen() const;
		Sint32		GetBlue() const;

		void		SetRed(Sint32 red);
		void		SetGreen(Sint32 green);
		void		SetBlue(Sint32 blue);

		void		GetColor(Sint32& r, Sint32& g, Sint32& b) const;
		void		SetColor(Sint32 r, Sint32 g, Sint32 b);

		private:
		Sint32 red;
		Sint32 green;
		Sint32 blue;
	};
	
}
