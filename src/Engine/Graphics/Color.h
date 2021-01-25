//==========================================================
// CasaEngine - Free C++ 3D engine
//
// Copyright (C) 2004-2005 Laurent Gomila
//
// This program is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either version 2
// of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc.,
// 59 Temple Place - Suite 330,
// Boston, MA  02111-1307, USA.
//
// E-mail : laurent.gom@gmail.com
//==========================================================

#ifndef COLOR_H
#define COLOR_H

#include <iostream>

#include "CA_Export.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	////////////////////////////////////////////////////////////
	/// Classe manipulant les couleurs
	////////////////////////////////////////////////////////////
	class CA_EXPORT CColor :
		public AllocatedObject<CColor>
	{
	public:

		//----------------------------------------------------------------
		// Constructeur par défaut
		//----------------------------------------------------------------
		CColor(unsigned long Color = 0xFFFFFFFF);

		//----------------------------------------------------------------
		// Constructeur à partir de 4 composantes
		//----------------------------------------------------------------
		CColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);

		//----------------------------------------------------------------
		// Renvoie la couleur en nuance de gris
		//----------------------------------------------------------------
		unsigned char ToGrey() const;

		unsigned int ToRGBA() const;
		unsigned int ToABGR() const;
		unsigned int ToARGB() const;

		//----------------------------------------------------------------
		// Récupére le canal alpha
		//----------------------------------------------------------------
		unsigned char GetAlpha() const;

		//----------------------------------------------------------------
		// Récupére le canal rouge
		//----------------------------------------------------------------
		unsigned char GetRed() const;

		//----------------------------------------------------------------
		// Récupére le canal vert
		//----------------------------------------------------------------
		unsigned char GetGreen() const;

		//----------------------------------------------------------------
		// Récupére le canal bleu
		//----------------------------------------------------------------
		unsigned char GetBlue() const;

		//----------------------------------------------------------------
		// Nouvelle couleur sous forme de 4 floats [0..1]
		//----------------------------------------------------------------
		void SetFloats(float r, float g, float b, float a = 1.0f);

		//----------------------------------------------------------------
		// Nouvelle couleur sous forme de 4 unsigned char [0..255]
		//----------------------------------------------------------------
		void Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a = 0xFF);

		//----------------------------------------------------------------
		// Convertit en 4 floats
		//----------------------------------------------------------------
		void ToFloat(float Dest[]) const;

		//----------------------------------------------------------------
		// Operateur ==
		//----------------------------------------------------------------
		bool operator ==(const CColor& c) const;

		//----------------------------------------------------------------
		// Operateur !=
		//----------------------------------------------------------------
		bool operator !=(const CColor& c) const;

		//----------------------------------------------------------------
		// Opérateur +=
		//----------------------------------------------------------------
		const CColor& operator +=(const CColor& c);

		//----------------------------------------------------------------
		// Opérateur -=
		//----------------------------------------------------------------
		const CColor& operator -=(const CColor& c);

		//----------------------------------------------------------------
		// Opérateur +
		//----------------------------------------------------------------
		CColor operator +(const CColor& c) const;

		//----------------------------------------------------------------
		// Opérateur -
		//----------------------------------------------------------------
		CColor operator -(const CColor& c) const;

		//----------------------------------------------------------------
		// Opérateur *
		//----------------------------------------------------------------
		CColor operator *(float v) const;

		//----------------------------------------------------------------
		// Opérateur *=
		//----------------------------------------------------------------
		const CColor& operator *=(float v);

		//----------------------------------------------------------------
		// Opérateur /
		//----------------------------------------------------------------
		CColor operator /(float v) const;

		//----------------------------------------------------------------
		// Opérateur /=
		//----------------------------------------------------------------
		const CColor& operator /=(float v);

		//----------------------------------------------------------------
		// Ajoute deux couleurs
		//----------------------------------------------------------------
		CColor Add(const CColor& c) const;

		//----------------------------------------------------------------
		// Module deux couleurs
		//----------------------------------------------------------------
		CColor Modulate(const CColor& c) const;

		//----------------------------------------------------------------
		// Surcharges des opérateurs pour les flux
		//----------------------------------------------------------------
		friend std::istream& operator >>(std::istream& Stream, CColor& Color);
		friend std::ostream& operator <<(std::ostream& Stream, const CColor& Color);

	private:

		//----------------------------------------------------------------
		// Nouvelle couleur sous forme de 4 int [0..255] - sert à clamper
		// les valeurs
		//----------------------------------------------------------------
		void SetInt(int r, int g, int b, int a = 0xFF);

		//----------------------------------------------------------------
		// Données membres
		//----------------------------------------------------------------
		unsigned long m_Color; ///< Couleur sous forme ARGB 32 bits

	public:
		/**
		 * Predefined colors
		 */
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
