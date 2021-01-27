#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	class CA_EXPORT CColor :
		public AllocatedObject<CColor>
	{
	public:
		CColor(unsigned long Color = 0xFFFFFFFF);
		CColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);

		unsigned char ToGrey() const;

		unsigned int ToRGBA() const;
		unsigned int ToABGR() const;
		unsigned int ToARGB() const;

		unsigned char GetAlpha() const;
		unsigned char GetRed() const;
		unsigned char GetGreen() const;
		unsigned char GetBlue() const;

		void SetFloats(float r, float g, float b, float a = 1.0f);
		void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);

		void ToFloat(float Dest[]) const;

		bool operator ==(const CColor& c) const;
		bool operator !=(const CColor& c) const;
		const CColor& operator +=(const CColor& c);
		const CColor& operator -=(const CColor& c);
		CColor operator +(const CColor& c) const;
		CColor operator -(const CColor& c) const;
		CColor operator *(float v) const;
		const CColor& operator *=(float v);
		CColor operator /(float v) const;
		const CColor& operator /=(float v);

		CColor Add(const CColor& c) const;
		CColor Modulate(const CColor& c) const;

		friend std::istream& operator >>(std::istream& Stream, CColor& Color);
		friend std::ostream& operator <<(std::ostream& Stream, const CColor& Color);

	private:
		void SetInt(int r, int g, int b, int a = 0xFF);

		unsigned long m_Color; ///< Couleur sous forme ARGB 32 bits

	public:
		static const CColor ActiveBorder;
		static const CColor ActiveCaption;
		static const CColor ActiveCaptionText;
		static const CColor AppWorkspace;
		static const CColor Control;
		static const CColor ControlDark;
		static const CColor ControlDarkDark;
		static const CColor ControlLight;
		static const CColor ControlLightLight;
		static const CColor ControlText;
		static const CColor Desktop;
		static const CColor GrayText;
		static const CColor Highlight;
		static const CColor HighlightText;
		static const CColor HotTrack;
		static const CColor InactiveBorder;
		static const CColor InactiveCaption;
		static const CColor InactiveCaptionText;
		static const CColor Info;
		static const CColor InfoText;
		static const CColor Menu;
		static const CColor MenuText;
		static const CColor ScrollBar;
		static const CColor Window;
		static const CColor WindowFrame;
		static const CColor WindowText;
		static const CColor Transparent;
		static const CColor AliceBlue;
		static const CColor AntiqueWhite;
		static const CColor Aqua;
		static const CColor Aquamarine;
		static const CColor Azure;
		static const CColor Beige;
		static const CColor Bisque;
		static const CColor Black;
		static const CColor BlanchedAlmond;
		static const CColor Blue;
		static const CColor BlueViolet;
		static const CColor Brown;
		static const CColor BurlyWood;
		static const CColor CadetBlue;
		static const CColor Chartreuse;
		static const CColor Chocolate;
		static const CColor Coral;
		static const CColor CornflowerBlue;
		static const CColor Cornsilk;
		static const CColor Crimson;
		static const CColor Cyan;
		static const CColor DarkBlue;
		static const CColor DarkCyan;
		static const CColor DarkGoldenrod;
		static const CColor DarkGray;
		static const CColor DarkGreen;
		static const CColor DarkKhaki;
		static const CColor DarkMagenta;
		static const CColor DarkOliveGreen;
		static const CColor DarkOrange;
		static const CColor DarkOrchid;
		static const CColor DarkRed;
		static const CColor DarkSalmon;
		static const CColor DarkSeaGreen;
		static const CColor DarkSlateBlue;
		static const CColor DarkSlateGray;
		static const CColor DarkTurquoise;
		static const CColor DarkViolet;
		static const CColor DeepPink;
		static const CColor DeepSkyBlue;
		static const CColor DimGray;
		static const CColor DodgerBlue;
		static const CColor Firebrick;
		static const CColor FloralWhite;
		static const CColor ForestGreen;
		static const CColor Fuchsia;
		static const CColor Gainsboro;
		static const CColor GhostWhite;
		static const CColor Gold;
		static const CColor Goldenrod;
		static const CColor Gray;
		static const CColor Green;
		static const CColor GreenYellow;
		static const CColor Honeydew;
		static const CColor HotPink;
		static const CColor IndianRed;
		static const CColor Indigo;
		static const CColor Ivory;
		static const CColor Khaki;
		static const CColor Lavender;
		static const CColor LavenderBlush;
		static const CColor LawnGreen;
		static const CColor LemonChiffon;
		static const CColor LightBlue;
		static const CColor LightCoral;
		static const CColor LightCyan;
		static const CColor LightGoldenrodYellow;
		static const CColor LightGray;
		static const CColor LightGreen;
		static const CColor LightPink;
		static const CColor LightSalmon;
		static const CColor LightSeaGreen;
		static const CColor LightSkyBlue;
		static const CColor LightSlateGray;
		static const CColor LightSteelBlue;
		static const CColor LightYellow;
		static const CColor Lime;
		static const CColor LimeGreen;
		static const CColor Linen;
		static const CColor Magenta;
		static const CColor Maroon;
		static const CColor MediumAquamarine;
		static const CColor MediumBlue;
		static const CColor MediumOrchid;
		static const CColor MediumPurple;
		static const CColor MediumSeaGreen;
		static const CColor MediumSlateBlue;
		static const CColor MediumSpringGreen;
		static const CColor MediumTurquoise;
		static const CColor MediumVioletRed;
		static const CColor MidnightBlue;
		static const CColor MintCream;
		static const CColor MistyRose;
		static const CColor Moccasin;
		static const CColor NavajoWhite;
		static const CColor Navy;
		static const CColor OldLace;
		static const CColor Olive;
		static const CColor OliveDrab;
		static const CColor Orange;
		static const CColor OrangeRed;
		static const CColor Orchid;
		static const CColor PaleGoldenrod;
		static const CColor PaleGreen;
		static const CColor PaleTurquoise;
		static const CColor PaleVioletRed;
		static const CColor PapayaWhip;
		static const CColor PeachPuff;
		static const CColor Peru;
		static const CColor Pink;
		static const CColor Plum;
		static const CColor PowderBlue;
		static const CColor Purple;
		static const CColor Red;
		static const CColor RosyBrown;
		static const CColor RoyalBlue;
		static const CColor SaddleBrown;
		static const CColor Salmon;
		static const CColor SandyBrown;
		static const CColor SeaGreen;
		static const CColor SeaShell;
		static const CColor Sienna;
		static const CColor Silver;
		static const CColor SkyBlue;
		static const CColor SlateBlue;
		static const CColor SlateGray;
		static const CColor Snow;
		static const CColor SpringGreen;
		static const CColor SteelBlue;
		static const CColor Tan;
		static const CColor Teal;
		static const CColor Thistle;
		static const CColor Tomato;
		static const CColor Turquoise;
		static const CColor Violet;
		static const CColor Wheat;
		static const CColor White;
		static const CColor WhiteSmoke;
		static const CColor Yellow;
		static const CColor YellowGreen;
		static const CColor ButtonFace;
		static const CColor ButtonHighlight;
		static const CColor ButtonShadow;
		static const CColor GradientActiveCaption;
		static const CColor GradientInactiveCaption;
		static const CColor MenuBar;
		static const CColor MenuHighlight;
	};
}

#endif // COLOR_H
