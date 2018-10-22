//
//	Copyright  Nemetschek Vectorworks, Inc.
//	Use of this file is governed by the Nemetschek Vectorworks SDK License Agreement
//	http://developer.vectorworks.net/index.php?title=Vectorworks_SDK_License
//

#pragma once

namespace VWFC
{
	namespace Tools
	{
		class CRGBColor
		{
		public:
						CRGBColor();
						CRGBColor(Uint8 r, Uint8 g, Uint8 b);
						CRGBColor(const CRGBColor& clr);
						// create gradient color from 'leftColor' to 'rightColor' using percentage
						// 0% = leftColor; 100% = rightColor
						CRGBColor(const CRGBColor& leftColor, const CRGBColor& rightColor, double dPercent);
			virtual		~CRGBColor();

			CRGBColor&	operator=(const CRGBColor& clr);

			bool		operator==(const CRGBColor& clr) const;
			bool		operator!=(const CRGBColor& clr) const;

			Uint8		GetRed() const;
			Uint8		GetGreen() const;
			Uint8		GetBlue() const;

			void		SetRed(Uint8 red);
			void		SetGreen(Uint8 green);
			void		SetBlue(Uint8 blue);

			void		GetColor(Uint8& r, Uint8& g, Uint8& b) const;
			void		SetColor(Uint8 r, Uint8 g, Uint8 b);

			private:
			Uint8 red;
			Uint8 green;
			Uint8 blue;
		};
	}
}
