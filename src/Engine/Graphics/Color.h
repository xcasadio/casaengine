#pragma once

#include <iostream>
#include "CA_Export.h"

namespace CasaEngine
{
	class CA_EXPORT Color
	{
	public:
		Color(unsigned long Color = 0xFFFFFFFF);
		Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);

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

		bool operator ==(const Color& c) const;
		bool operator !=(const Color& c) const;
		const Color& operator +=(const Color& c);
		const Color& operator -=(const Color& c);
		Color operator +(const Color& c) const;
		Color operator -(const Color& c) const;
		Color operator *(float v) const;
		const Color& operator *=(float v);
		Color operator /(float v) const;
		const Color& operator /=(float v);

		Color Add(const Color& c) const;
		Color Modulate(const Color& c) const;

		friend std::istream& operator >>(std::istream& Stream, Color& Color);
		friend std::ostream& operator <<(std::ostream& Stream, const Color& Color);

	private:
		void SetInt(int r, int g, int b, int a = 0xFF);

		unsigned long m_Color; ///< Couleur sous forme ARGB 32 bits

	public:
		static const Color ActiveBorder;
		static const Color ActiveCaption;
		static const Color ActiveCaptionText;
		static const Color AppWorkspace;
		static const Color Control;
		static const Color ControlDark;
		static const Color ControlDarkDark;
		static const Color ControlLight;
		static const Color ControlLightLight;
		static const Color ControlText;
		static const Color Desktop;
		static const Color GrayText;
		static const Color Highlight;
		static const Color HighlightText;
		static const Color HotTrack;
		static const Color InactiveBorder;
		static const Color InactiveCaption;
		static const Color InactiveCaptionText;
		static const Color Info;
		static const Color InfoText;
		static const Color Menu;
		static const Color MenuText;
		static const Color ScrollBar;
		static const Color Window;
		static const Color WindowFrame;
		static const Color WindowText;
		static const Color Transparent;
		static const Color AliceBlue;
		static const Color AntiqueWhite;
		static const Color Aqua;
		static const Color Aquamarine;
		static const Color Azure;
		static const Color Beige;
		static const Color Bisque;
		static const Color Black;
		static const Color BlanchedAlmond;
		static const Color Blue;
		static const Color BlueViolet;
		static const Color Brown;
		static const Color BurlyWood;
		static const Color CadetBlue;
		static const Color Chartreuse;
		static const Color Chocolate;
		static const Color Coral;
		static const Color CornflowerBlue;
		static const Color Cornsilk;
		static const Color Crimson;
		static const Color Cyan;
		static const Color DarkBlue;
		static const Color DarkCyan;
		static const Color DarkGoldenrod;
		static const Color DarkGray;
		static const Color DarkGreen;
		static const Color DarkKhaki;
		static const Color DarkMagenta;
		static const Color DarkOliveGreen;
		static const Color DarkOrange;
		static const Color DarkOrchid;
		static const Color DarkRed;
		static const Color DarkSalmon;
		static const Color DarkSeaGreen;
		static const Color DarkSlateBlue;
		static const Color DarkSlateGray;
		static const Color DarkTurquoise;
		static const Color DarkViolet;
		static const Color DeepPink;
		static const Color DeepSkyBlue;
		static const Color DimGray;
		static const Color DodgerBlue;
		static const Color Firebrick;
		static const Color FloralWhite;
		static const Color ForestGreen;
		static const Color Fuchsia;
		static const Color Gainsboro;
		static const Color GhostWhite;
		static const Color Gold;
		static const Color Goldenrod;
		static const Color Gray;
		static const Color Green;
		static const Color GreenYellow;
		static const Color Honeydew;
		static const Color HotPink;
		static const Color IndianRed;
		static const Color Indigo;
		static const Color Ivory;
		static const Color Khaki;
		static const Color Lavender;
		static const Color LavenderBlush;
		static const Color LawnGreen;
		static const Color LemonChiffon;
		static const Color LightBlue;
		static const Color LightCoral;
		static const Color LightCyan;
		static const Color LightGoldenrodYellow;
		static const Color LightGray;
		static const Color LightGreen;
		static const Color LightPink;
		static const Color LightSalmon;
		static const Color LightSeaGreen;
		static const Color LightSkyBlue;
		static const Color LightSlateGray;
		static const Color LightSteelBlue;
		static const Color LightYellow;
		static const Color Lime;
		static const Color LimeGreen;
		static const Color Linen;
		static const Color Magenta;
		static const Color Maroon;
		static const Color MediumAquamarine;
		static const Color MediumBlue;
		static const Color MediumOrchid;
		static const Color MediumPurple;
		static const Color MediumSeaGreen;
		static const Color MediumSlateBlue;
		static const Color MediumSpringGreen;
		static const Color MediumTurquoise;
		static const Color MediumVioletRed;
		static const Color MidnightBlue;
		static const Color MintCream;
		static const Color MistyRose;
		static const Color Moccasin;
		static const Color NavajoWhite;
		static const Color Navy;
		static const Color OldLace;
		static const Color Olive;
		static const Color OliveDrab;
		static const Color Orange;
		static const Color OrangeRed;
		static const Color Orchid;
		static const Color PaleGoldenrod;
		static const Color PaleGreen;
		static const Color PaleTurquoise;
		static const Color PaleVioletRed;
		static const Color PapayaWhip;
		static const Color PeachPuff;
		static const Color Peru;
		static const Color Pink;
		static const Color Plum;
		static const Color PowderBlue;
		static const Color Purple;
		static const Color Red;
		static const Color RosyBrown;
		static const Color RoyalBlue;
		static const Color SaddleBrown;
		static const Color Salmon;
		static const Color SandyBrown;
		static const Color SeaGreen;
		static const Color SeaShell;
		static const Color Sienna;
		static const Color Silver;
		static const Color SkyBlue;
		static const Color SlateBlue;
		static const Color SlateGray;
		static const Color Snow;
		static const Color SpringGreen;
		static const Color SteelBlue;
		static const Color Tan;
		static const Color Teal;
		static const Color Thistle;
		static const Color Tomato;
		static const Color Turquoise;
		static const Color Violet;
		static const Color Wheat;
		static const Color White;
		static const Color WhiteSmoke;
		static const Color Yellow;
		static const Color YellowGreen;
		static const Color ButtonFace;
		static const Color ButtonHighlight;
		static const Color ButtonShadow;
		static const Color GradientActiveCaption;
		static const Color GradientInactiveCaption;
		static const Color MenuBar;
		static const Color MenuHighlight;
	};
}
