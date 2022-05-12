#include "Base.h"
#include "Color.h"

namespace CasaEngine
{
	Color::Color(unsigned long Color) :
		m_Color(Color)
	{
	}

	Color::Color(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
		m_Color(0)
	{
		Set(r, g, b, a);
	}

	void Color::SetFloats(float r, float g, float b, float a)
	{
		const int R = static_cast<int>(r * 255.0f);
		const int G = static_cast<int>(g * 255.0f);
		const int B = static_cast<int>(b * 255.0f);
		const int A = static_cast<int>(a * 255.0f);

		SetInt(R, G, B, A);
	}

	void Color::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
	{
		m_Color = a << 24 | r << 16 | g << 8 | b << 0;
	}

	void Color::SetInt(int r, int g, int b, int a)
	{
		const auto R = static_cast<unsigned char>(r >= 0 ? (r <= 255 ? r : 255) : 0);
		const auto G = static_cast<unsigned char>(g >= 0 ? (g <= 255 ? g : 255) : 0);
		const auto B = static_cast<unsigned char>(b >= 0 ? (b <= 255 ? b : 255) : 0);
		const auto A = static_cast<unsigned char>(a >= 0 ? (a <= 255 ? a : 255) : 0);

		Set(R, G, B, A);
	}

	bool Color::operator ==(const Color& c) const
	{
		return m_Color == c.m_Color;
	}

	bool Color::operator!=(const Color& c) const
	{
		return !(*this == c);
	}

	const Color& Color::operator +=(const Color& c)
	{
		const int R = GetRed() + c.GetRed();
		const int G = GetGreen() + c.GetGreen();
		const int B = GetBlue() + c.GetBlue();
		const int A = GetAlpha() + c.GetAlpha();

		SetInt(R, G, B, A);

		return *this;
	}

	const Color& Color::operator -=(const Color& c)
	{
		const int R = GetRed() - c.GetRed();
		const int G = GetGreen() - c.GetGreen();
		const int B = GetBlue() - c.GetBlue();
		const int A = GetAlpha() - c.GetAlpha();

		SetInt(R, G, B, A);

		return *this;
	}

	Color Color::operator +(const Color& c) const
	{
		const int R = GetRed() + c.GetRed();
		const int G = GetGreen() + c.GetGreen();
		const int B = GetBlue() + c.GetBlue();
		const int A = GetAlpha() + c.GetAlpha();

		Color Ret;
		Ret.SetInt(R, G, B, A);

		return Ret;
	}

	Color Color::operator -(const Color& c) const
	{
		const int R = GetRed() - c.GetRed();
		const int G = GetGreen() - c.GetGreen();
		const int B = GetBlue() - c.GetBlue();
		const int A = GetAlpha() - c.GetAlpha();

		Color Ret;
		Ret.SetInt(R, G, B, A);

		return Ret;
	}

	Color Color::operator *(float v) const
	{
		const int R = static_cast<int>(GetRed() * v);
		const int G = static_cast<int>(GetGreen() * v);
		const int B = static_cast<int>(GetBlue() * v);
		const int A = static_cast<int>(GetAlpha() * v);

		Color Ret;
		Ret.SetInt(R, G, B, A);

		return Ret;
	}

	const Color& Color::operator *=(float v)
	{
		const int R = static_cast<int>(GetRed() * v);
		const int G = static_cast<int>(GetGreen() * v);
		const int B = static_cast<int>(GetBlue() * v);
		const int A = static_cast<int>(GetAlpha() * v);

		SetInt(R, G, B, A);

		return *this;
	}

	Color Color::operator /(float v) const
	{
		return *this * (1.0f / v);
	}

	const Color& Color::operator /=(float v)
	{
		return *this *= 1.0f / v;
	}

	Color Color::Add(const Color& c) const
	{
		return *this + c;
	}

	Color Color::Modulate(const Color& c) const
	{
		const auto R = static_cast<unsigned char>(GetRed() * c.GetRed() / 255);
		const auto G = static_cast<unsigned char>(GetGreen() * c.GetGreen() / 255);
		const auto B = static_cast<unsigned char>(GetBlue() * c.GetBlue() / 255);
		const auto A = static_cast<unsigned char>(GetAlpha() * c.GetAlpha() / 255);

		return {R, G, B, A};
	}

	unsigned char Color::GetAlpha() const
	{
		return static_cast<unsigned char>((m_Color & 0xFF000000) >> 24);
	}

	unsigned char Color::GetRed() const
	{
		return static_cast<unsigned char>((m_Color & 0x00FF0000) >> 16);
	}

	unsigned char Color::GetGreen() const
	{
		return static_cast<unsigned char>((m_Color & 0x0000FF00) >> 8);
	}

	unsigned char Color::GetBlue() const
	{
		return static_cast<unsigned char>((m_Color & 0x000000FF) >> 0);
	}

	void Color::ToFloat(float Dest[]) const
	{
		Dest[0] = GetRed() / 255.0f;
		Dest[1] = GetGreen() / 255.0f;
		Dest[2] = GetBlue() / 255.0f;
		Dest[3] = GetAlpha() / 255.0f;
	}

	unsigned char Color::ToGrey() const
	{
		return static_cast<unsigned char>(GetRed() * 0.30f + GetGreen() * 0.59f + GetBlue() * 0.11f);
	}

	unsigned int Color::ToABGR() const
	{
		return GetRed() << 0
			| GetGreen() << 8
			| GetBlue() << 16
			| GetAlpha() << 24;
	}

	unsigned int Color::ToRGBA() const
	{
		return GetAlpha() << 0
			| GetBlue() << 8
			| GetGreen() << 16
			| GetRed() << 24;
	}

	unsigned int Color::ToARGB() const
	{
		return m_Color;
	}

	const Color Color::ActiveBorder(180, 180, 180, 255);
	const Color Color::ActiveCaption(153, 180, 209, 255);
	const Color Color::ActiveCaptionText(0, 0, 0, 255);
	const Color Color::AppWorkspace(171, 171, 171, 255);
	const Color Color::Control(240, 240, 240, 255);
	const Color Color::ControlDark(160, 160, 160, 255);
	const Color Color::ControlDarkDark(105, 105, 105, 255);
	const Color Color::ControlLight(227, 227, 227, 255);
	const Color Color::ControlLightLight(255, 255, 255, 255);
	const Color Color::ControlText(0, 0, 0, 255);
	const Color Color::Desktop(0, 0, 0, 255);
	const Color Color::GrayText(109, 109, 109, 255);
	const Color Color::Highlight(51, 153, 255, 255);
	const Color Color::HighlightText(255, 255, 255, 255);
	const Color Color::HotTrack(0, 102, 204, 255);
	const Color Color::InactiveBorder(244, 247, 252, 255);
	const Color Color::InactiveCaption(191, 205, 219, 255);
	const Color Color::InactiveCaptionText(67, 78, 84, 255);
	const Color Color::Info(255, 255, 225, 255);
	const Color Color::InfoText(0, 0, 0, 255);
	const Color Color::Menu(240, 240, 240, 255);
	const Color Color::MenuText(0, 0, 0, 255);
	const Color Color::ScrollBar(200, 200, 200, 255);
	const Color Color::Window(255, 255, 255, 255);
	const Color Color::WindowFrame(100, 100, 100, 255);
	const Color Color::WindowText(0, 0, 0, 255);
	const Color Color::Transparent(255, 255, 255, 0);
	const Color Color::AliceBlue(240, 248, 255, 255);
	const Color Color::AntiqueWhite(250, 235, 215, 255);
	const Color Color::Aqua(0, 255, 255, 255);
	const Color Color::Aquamarine(127, 255, 212, 255);
	const Color Color::Azure(240, 255, 255, 255);
	const Color Color::Beige(245, 245, 220, 255);
	const Color Color::Bisque(255, 228, 196, 255);
	const Color Color::Black(0, 0, 0, 255);
	const Color Color::BlanchedAlmond(255, 235, 205, 255);
	const Color Color::Blue(0, 0, 255, 255);
	const Color Color::BlueViolet(138, 43, 226, 255);
	const Color Color::Brown(165, 42, 42, 255);
	const Color Color::BurlyWood(222, 184, 135, 255);
	const Color Color::CadetBlue(95, 158, 160, 255);
	const Color Color::Chartreuse(127, 255, 0, 255);
	const Color Color::Chocolate(210, 105, 30, 255);
	const Color Color::Coral(255, 127, 80, 255);
	const Color Color::CornflowerBlue(100, 149, 237, 255);
	const Color Color::Cornsilk(255, 248, 220, 255);
	const Color Color::Crimson(220, 20, 60, 255);
	const Color Color::Cyan(0, 255, 255, 255);
	const Color Color::DarkBlue(0, 0, 139, 255);
	const Color Color::DarkCyan(0, 139, 139, 255);
	const Color Color::DarkGoldenrod(184, 134, 11, 255);
	const Color Color::DarkGray(169, 169, 169, 255);
	const Color Color::DarkGreen(0, 100, 0, 255);
	const Color Color::DarkKhaki(189, 183, 107, 255);
	const Color Color::DarkMagenta(139, 0, 139, 255);
	const Color Color::DarkOliveGreen(85, 107, 47, 255);
	const Color Color::DarkOrange(255, 140, 0, 255);
	const Color Color::DarkOrchid(153, 50, 204, 255);
	const Color Color::DarkRed(139, 0, 0, 255);
	const Color Color::DarkSalmon(233, 150, 122, 255);
	const Color Color::DarkSeaGreen(143, 188, 139, 255);
	const Color Color::DarkSlateBlue(72, 61, 139, 255);
	const Color Color::DarkSlateGray(47, 79, 79, 255);
	const Color Color::DarkTurquoise(0, 206, 209, 255);
	const Color Color::DarkViolet(148, 0, 211, 255);
	const Color Color::DeepPink(255, 20, 147, 255);
	const Color Color::DeepSkyBlue(0, 191, 255, 255);
	const Color Color::DimGray(105, 105, 105, 255);
	const Color Color::DodgerBlue(30, 144, 255, 255);
	const Color Color::Firebrick(178, 34, 34, 255);
	const Color Color::FloralWhite(255, 250, 240, 255);
	const Color Color::ForestGreen(34, 139, 34, 255);
	const Color Color::Fuchsia(255, 0, 255, 255);
	const Color Color::Gainsboro(220, 220, 220, 255);
	const Color Color::GhostWhite(248, 248, 255, 255);
	const Color Color::Gold(255, 215, 0, 255);
	const Color Color::Goldenrod(218, 165, 32, 255);
	const Color Color::Gray(128, 128, 128, 255);
	const Color Color::Green(0, 128, 0, 255);
	const Color Color::GreenYellow(173, 255, 47, 255);
	const Color Color::Honeydew(240, 255, 240, 255);
	const Color Color::HotPink(255, 105, 180, 255);
	const Color Color::IndianRed(205, 92, 92, 255);
	const Color Color::Indigo(75, 0, 130, 255);
	const Color Color::Ivory(255, 255, 240, 255);
	const Color Color::Khaki(240, 230, 140, 255);
	const Color Color::Lavender(230, 230, 250, 255);
	const Color Color::LavenderBlush(255, 240, 245, 255);
	const Color Color::LawnGreen(124, 252, 0, 255);
	const Color Color::LemonChiffon(255, 250, 205, 255);
	const Color Color::LightBlue(173, 216, 230, 255);
	const Color Color::LightCoral(240, 128, 128, 255);
	const Color Color::LightCyan(224, 255, 255, 255);
	const Color Color::LightGoldenrodYellow(250, 250, 210, 255);
	const Color Color::LightGray(211, 211, 211, 255);
	const Color Color::LightGreen(144, 238, 144, 255);
	const Color Color::LightPink(255, 182, 193, 255);
	const Color Color::LightSalmon(255, 160, 122, 255);
	const Color Color::LightSeaGreen(32, 178, 170, 255);
	const Color Color::LightSkyBlue(135, 206, 250, 255);
	const Color Color::LightSlateGray(119, 136, 153, 255);
	const Color Color::LightSteelBlue(176, 196, 222, 255);
	const Color Color::LightYellow(255, 255, 224, 255);
	const Color Color::Lime(0, 255, 0, 255);
	const Color Color::LimeGreen(50, 205, 50, 255);
	const Color Color::Linen(250, 240, 230, 255);
	const Color Color::Magenta(255, 0, 255, 255);
	const Color Color::Maroon(128, 0, 0, 255);
	const Color Color::MediumAquamarine(102, 205, 170, 255);
	const Color Color::MediumBlue(0, 0, 205, 255);
	const Color Color::MediumOrchid(186, 85, 211, 255);
	const Color Color::MediumPurple(147, 112, 219, 255);
	const Color Color::MediumSeaGreen(60, 179, 113, 255);
	const Color Color::MediumSlateBlue(123, 104, 238, 255);
	const Color Color::MediumSpringGreen(0, 250, 154, 255);
	const Color Color::MediumTurquoise(72, 209, 204, 255);
	const Color Color::MediumVioletRed(199, 21, 133, 255);
	const Color Color::MidnightBlue(25, 25, 112, 255);
	const Color Color::MintCream(245, 255, 250, 255);
	const Color Color::MistyRose(255, 228, 225, 255);
	const Color Color::Moccasin(255, 228, 181, 255);
	const Color Color::NavajoWhite(255, 222, 173, 255);
	const Color Color::Navy(0, 0, 128, 255);
	const Color Color::OldLace(253, 245, 230, 255);
	const Color Color::Olive(128, 128, 0, 255);
	const Color Color::OliveDrab(107, 142, 35, 255);
	const Color Color::Orange(255, 165, 0, 255);
	const Color Color::OrangeRed(255, 69, 0, 255);
	const Color Color::Orchid(218, 112, 214, 255);
	const Color Color::PaleGoldenrod(238, 232, 170, 255);
	const Color Color::PaleGreen(152, 251, 152, 255);
	const Color Color::PaleTurquoise(175, 238, 238, 255);
	const Color Color::PaleVioletRed(219, 112, 147, 255);
	const Color Color::PapayaWhip(255, 239, 213, 255);
	const Color Color::PeachPuff(255, 218, 185, 255);
	const Color Color::Peru(205, 133, 63, 255);
	const Color Color::Pink(255, 192, 203, 255);
	const Color Color::Plum(221, 160, 221, 255);
	const Color Color::PowderBlue(176, 224, 230, 255);
	const Color Color::Purple(128, 0, 128, 255);
	const Color Color::Red(255, 0, 0, 255);
	const Color Color::RosyBrown(188, 143, 143, 255);
	const Color Color::RoyalBlue(65, 105, 225, 255);
	const Color Color::SaddleBrown(139, 69, 19, 255);
	const Color Color::Salmon(250, 128, 114, 255);
	const Color Color::SandyBrown(244, 164, 96, 255);
	const Color Color::SeaGreen(46, 139, 87, 255);
	const Color Color::SeaShell(255, 245, 238, 255);
	const Color Color::Sienna(160, 82, 45, 255);
	const Color Color::Silver(192, 192, 192, 255);
	const Color Color::SkyBlue(135, 206, 235, 255);
	const Color Color::SlateBlue(106, 90, 205, 255);
	const Color Color::SlateGray(112, 128, 144, 255);
	const Color Color::Snow(255, 250, 250, 255);
	const Color Color::SpringGreen(0, 255, 127, 255);
	const Color Color::SteelBlue(70, 130, 180, 255);
	const Color Color::Tan(210, 180, 140, 255);
	const Color Color::Teal(0, 128, 128, 255);
	const Color Color::Thistle(216, 191, 216, 255);
	const Color Color::Tomato(255, 99, 71, 255);
	const Color Color::Turquoise(64, 224, 208, 255);
	const Color Color::Violet(238, 130, 238, 255);
	const Color Color::Wheat(245, 222, 179, 255);
	const Color Color::White(255, 255, 255, 255);
	const Color Color::WhiteSmoke(245, 245, 245, 255);
	const Color Color::Yellow(255, 255, 0, 255);
	const Color Color::YellowGreen(154, 205, 50, 255);
	const Color Color::ButtonFace(240, 240, 240, 255);
	const Color Color::ButtonHighlight(255, 255, 255, 255);
	const Color Color::ButtonShadow(160, 160, 160, 255);
	const Color Color::GradientActiveCaption(185, 209, 234, 255);
	const Color Color::GradientInactiveCaption(215, 228, 242, 255);
	const Color Color::MenuBar(240, 240, 240, 255);
	const Color Color::MenuHighlight(51, 153, 255, 255);
}