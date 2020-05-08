#include "Base.h"
#include "Color.h"

namespace CasaEngine
{
CColor::CColor(unsigned long Color) :
m_Color(Color)
{

}

CColor::CColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    Set(r, g, b, a);
}

void CColor::SetFloats(float r, float g, float b, float a)
{
    int R = static_cast<int>(r * 255.0f);
    int G = static_cast<int>(g * 255.0f);
    int B = static_cast<int>(b * 255.0f);
    int A = static_cast<int>(a * 255.0f);

	SetInt(R, G, B, A);
}

void CColor::Set(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    m_Color = (a << 24) | (r << 16) | (g << 8) | (b << 0);
}

void CColor::SetInt(int r, int g, int b, int a)
{
	unsigned char R = static_cast<unsigned char>((r >= 0) ? (r <= 255 ? r : 255) : 0);
	unsigned char G = static_cast<unsigned char>((g >= 0) ? (g <= 255 ? g : 255) : 0);
	unsigned char B = static_cast<unsigned char>((b >= 0) ? (b <= 255 ? b : 255) : 0);
	unsigned char A = static_cast<unsigned char>((a >= 0) ? (a <= 255 ? a : 255) : 0);

	Set(R, G, B, A);
}

bool CColor::operator ==(const CColor& c) const
{
    return m_Color == c.m_Color;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur != pour comparer deux couleurs
///
/// \param c : Couleur à comparer
///
/// \return True si les deux couleurs sont différentes
///
////////////////////////////////////////////////////////////
bool CColor::operator!=(const CColor& c) const
{
    return !(*this == c);
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur +=
///
/// \param c : Couleur à ajouter
///
/// \return Nouvelle couleur
///
////////////////////////////////////////////////////////////
const CColor& CColor::operator +=(const CColor& c)
{
	int R = GetRed()   + c.GetRed();
	int G = GetGreen() + c.GetGreen();
	int B = GetBlue()  + c.GetBlue();
	int A = GetAlpha() + c.GetAlpha();

    SetInt(R, G, B, A);

	return *this;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur -=
///
/// \param c : Couleur à soustraire
///
/// \return Nouvelle couleur
///
////////////////////////////////////////////////////////////
const CColor& CColor::operator -=(const CColor& c)
{
	int R = GetRed()   - c.GetRed();
	int G = GetGreen() - c.GetGreen();
	int B = GetBlue()  - c.GetBlue();
	int A = GetAlpha() - c.GetAlpha();

    SetInt(R, G, B, A);

    return *this;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur +
///
/// \param c : Couleur à ajouter
///
/// \return Nouvelle couleur
///
////////////////////////////////////////////////////////////
CColor CColor::operator +(const CColor& c) const
{
	int R = GetRed()   + c.GetRed();
	int G = GetGreen() + c.GetGreen();
	int B = GetBlue()  + c.GetBlue();
	int A = GetAlpha() + c.GetAlpha();

    CColor Ret;
    Ret.SetInt(R, G, B, A);

	return Ret;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur -
///
/// \param c : Couleur à soustraire
///
/// \return Nouvelle couleur
///
////////////////////////////////////////////////////////////
CColor CColor::operator -(const CColor& c) const
{
	int R = GetRed()   - c.GetRed();
	int G = GetGreen() - c.GetGreen();
	int B = GetBlue()  - c.GetBlue();
	int A = GetAlpha() - c.GetAlpha();

    CColor Ret;
    Ret.SetInt(R, G, B, A);

	return Ret;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur *
///
/// \param v : Multiplicateur
///
/// \return Nouvelle couleur
///
////////////////////////////////////////////////////////////
CColor CColor::operator *(float v) const
{
	int R = static_cast<int>(GetRed()   * v);
	int G = static_cast<int>(GetGreen() * v);
	int B = static_cast<int>(GetBlue()  * v);
	int A = static_cast<int>(GetAlpha() * v);

    CColor Ret;
    Ret.SetInt(R, G, B, A);

	return Ret;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur *=
///
/// \param v : Multiplicateur
///
/// \return Nouvelle couleur
///
////////////////////////////////////////////////////////////
const CColor& CColor::operator *=(float v)
{
	int R = static_cast<int>(GetRed()   * v);
	int G = static_cast<int>(GetGreen() * v);
	int B = static_cast<int>(GetBlue()  * v);
	int A = static_cast<int>(GetAlpha() * v);

	SetInt(R, G, B, A);

    return *this;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur /
///
/// \param v : Diviseur
///
/// \return Nouvelle couleur
///
////////////////////////////////////////////////////////////
CColor CColor::operator /(float v) const
{
	return *this * (1.0f / v);
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur /=
///
/// \param v : Diviseur
///
/// \return Nouvelle couleur
///
////////////////////////////////////////////////////////////
const CColor& CColor::operator /=(float v)
{
    return *this *= (1.0f / v);
}


/////////////////////////////////////////////////////////////
/// Ajoute deux couleurs
///
/// \param c : Couleur à ajouter
///
/// \return Somme des deux couleurs
///
////////////////////////////////////////////////////////////
CColor CColor::Add(const CColor& c) const
{
    return *this + c;
}


/////////////////////////////////////////////////////////////
/// Module deux couleurs
///
/// \param c : Couleur à moduler
///
/// \return Modulation des deux couleurs
///
////////////////////////////////////////////////////////////
CColor CColor::Modulate(const CColor& c) const
{
    unsigned char R = static_cast<unsigned char>(GetRed()   * c.GetRed()   / 255);
    unsigned char G = static_cast<unsigned char>(GetGreen() * c.GetGreen() / 255);
    unsigned char B = static_cast<unsigned char>(GetBlue()  * c.GetBlue()  / 255);
    unsigned char A = static_cast<unsigned char>(GetAlpha() * c.GetAlpha() / 255);

    return CColor(R, G, B, A);
}


/////////////////////////////////////////////////////////////
/// Récupère le canal alpha
///
/// \return Valeur du canal alpha
///
////////////////////////////////////////////////////////////
unsigned char CColor::GetAlpha() const
{
    return static_cast<unsigned char>((m_Color & 0xFF000000) >> 24);
}


/////////////////////////////////////////////////////////////
/// Récupère le canal rouge
///
/// \return Valeur du canal rouge
///
////////////////////////////////////////////////////////////
unsigned char CColor::GetRed() const
{
    return static_cast<unsigned char>((m_Color & 0x00FF0000) >> 16);
}


/////////////////////////////////////////////////////////////
/// Récupère le canal vert
///
/// \return Valeur du canal vert
///
////////////////////////////////////////////////////////////
unsigned char CColor::GetGreen() const
{
    return static_cast<unsigned char>((m_Color & 0x0000FF00) >> 8);
}


/////////////////////////////////////////////////////////////
/// Récupère le canal bleu
///
/// \return Valeur du canal bleu
///
////////////////////////////////////////////////////////////
unsigned char CColor::GetBlue() const
{
    return static_cast<unsigned char>((m_Color & 0x000000FF) >> 0);
}


/////////////////////////////////////////////////////////////
/// Convertit en 4 floats RGBA
///
/// \param Dest : Tableau de destination
///
////////////////////////////////////////////////////////////
void CColor::ToFloat(float Dest[]) const
{
    Dest[0] = GetRed()   / 255.0f;
    Dest[1] = GetGreen() / 255.0f;
    Dest[2] = GetBlue()  / 255.0f;
    Dest[3] = GetAlpha() / 255.0f;
}


/////////////////////////////////////////////////////////////
/// Renvoie la couleur en nuance de gris
///
/// \return Octet représentant le niveau de gris associé
///
////////////////////////////////////////////////////////////
unsigned char CColor::ToGrey() const
{
    return static_cast<unsigned char>(GetRed() * 0.30f + GetGreen() * 0.59f + GetBlue() * 0.11f);
}

/**
 * 
 */
unsigned int CColor::ToABGR() const
{
	return ((GetRed()	<< 0) 
		| (GetGreen()	<< 8) 
		| (GetBlue()	<< 16) 
		| (GetAlpha()	<< 24));
}

/**
 * 
 */
unsigned int CColor::ToRGBA() const
{
	return ((GetAlpha() << 0) 
		| (GetBlue()	<< 8) 
		| (GetGreen()	<< 16) 
		| (GetRed()		<< 24));
}

/**
 * used for vertex
 */
unsigned int CColor::ToARGB() const
{
	return m_Color;
}

/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur >> entre un flux et une couleur
///
/// \param Stream : Flux d'entrée
/// \param Color :  Couleur
///
/// \return Référence sur le flux d'entrée
///
////////////////////////////////////////////////////////////
std::istream& operator >>(std::istream& Stream, CColor& Color)
{
    int R, G, B, A;
    Stream >> R >> G >> B >> A;
    Color.SetInt(R, G, B, A);

    return Stream;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur << entre un flux et une couleur
///
/// \param Stream : Flux de sortie
/// \param Color :  Couleur
///
/// \return Référence sur le flux de sortie
///
////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& Stream, const CColor& Color)
{
    return Stream << static_cast<int>(Color.GetRed())   << " "
                  << static_cast<int>(Color.GetGreen()) << " "
                  << static_cast<int>(Color.GetBlue())  << " "
                  << static_cast<int>(Color.GetAlpha());
}

/////////////////////////////////////////////////////////////
// Données membres statiques
/////////////////////////////////////////////////////////////
const CColor CColor::ActiveBorder(180, 180, 180, 255);
const CColor CColor::ActiveCaption(153, 180, 209, 255);
const CColor CColor::ActiveCaptionText(0, 0, 0, 255);
const CColor CColor::AppWorkspace(171, 171, 171, 255);
const CColor CColor::Control(240, 240, 240, 255);
const CColor CColor::ControlDark(160, 160, 160, 255);
const CColor CColor::ControlDarkDark(105, 105, 105, 255);
const CColor CColor::ControlLight(227, 227, 227, 255);
const CColor CColor::ControlLightLight(255, 255, 255, 255);
const CColor CColor::ControlText(0, 0, 0, 255);
const CColor CColor::Desktop(0, 0, 0, 255);
const CColor CColor::GrayText(109, 109, 109, 255);
const CColor CColor::Highlight(51, 153, 255, 255);
const CColor CColor::HighlightText(255, 255, 255, 255);
const CColor CColor::HotTrack(0, 102, 204, 255);
const CColor CColor::InactiveBorder(244, 247, 252, 255);
const CColor CColor::InactiveCaption(191, 205, 219, 255);
const CColor CColor::InactiveCaptionText(67, 78, 84, 255);
const CColor CColor::Info(255, 255, 225, 255);
const CColor CColor::InfoText(0, 0, 0, 255);
const CColor CColor::Menu(240, 240, 240, 255);
const CColor CColor::MenuText(0, 0, 0, 255);
const CColor CColor::ScrollBar(200, 200, 200, 255);
const CColor CColor::Window(255, 255, 255, 255);
const CColor CColor::WindowFrame(100, 100, 100, 255);
const CColor CColor::WindowText(0, 0, 0, 255);
const CColor CColor::Transparent(255, 255, 255, 0);
const CColor CColor::AliceBlue(240, 248, 255, 255);
const CColor CColor::AntiqueWhite(250, 235, 215, 255);
const CColor CColor::Aqua(0, 255, 255, 255);
const CColor CColor::Aquamarine(127, 255, 212, 255);
const CColor CColor::Azure(240, 255, 255, 255);
const CColor CColor::Beige(245, 245, 220, 255);
const CColor CColor::Bisque(255, 228, 196, 255);
const CColor CColor::Black(0, 0, 0, 255);
const CColor CColor::BlanchedAlmond(255, 235, 205, 255);
const CColor CColor::Blue(0, 0, 255, 255);
const CColor CColor::BlueViolet(138, 43, 226, 255);
const CColor CColor::Brown(165, 42, 42, 255);
const CColor CColor::BurlyWood(222, 184, 135, 255);
const CColor CColor::CadetBlue(95, 158, 160, 255);
const CColor CColor::Chartreuse(127, 255, 0, 255);
const CColor CColor::Chocolate(210, 105, 30, 255);
const CColor CColor::Coral(255, 127, 80, 255);
const CColor CColor::CornflowerBlue(100, 149, 237, 255);
const CColor CColor::Cornsilk(255, 248, 220, 255);
const CColor CColor::Crimson(220, 20, 60, 255);
const CColor CColor::Cyan(0, 255, 255, 255);
const CColor CColor::DarkBlue(0, 0, 139, 255);
const CColor CColor::DarkCyan(0, 139, 139, 255);
const CColor CColor::DarkGoldenrod(184, 134, 11, 255);
const CColor CColor::DarkGray(169, 169, 169, 255);
const CColor CColor::DarkGreen(0, 100, 0, 255);
const CColor CColor::DarkKhaki(189, 183, 107, 255);
const CColor CColor::DarkMagenta(139, 0, 139, 255);
const CColor CColor::DarkOliveGreen(85, 107, 47, 255);
const CColor CColor::DarkOrange(255, 140, 0, 255);
const CColor CColor::DarkOrchid(153, 50, 204, 255);
const CColor CColor::DarkRed(139, 0, 0, 255);
const CColor CColor::DarkSalmon(233, 150, 122, 255);
const CColor CColor::DarkSeaGreen(143, 188, 139, 255);
const CColor CColor::DarkSlateBlue(72, 61, 139, 255);
const CColor CColor::DarkSlateGray(47, 79, 79, 255);
const CColor CColor::DarkTurquoise(0, 206, 209, 255);
const CColor CColor::DarkViolet(148, 0, 211, 255);
const CColor CColor::DeepPink(255, 20, 147, 255);
const CColor CColor::DeepSkyBlue(0, 191, 255, 255);
const CColor CColor::DimGray(105, 105, 105, 255);
const CColor CColor::DodgerBlue(30, 144, 255, 255);
const CColor CColor::Firebrick(178, 34, 34, 255);
const CColor CColor::FloralWhite(255, 250, 240, 255);
const CColor CColor::ForestGreen(34, 139, 34, 255);
const CColor CColor::Fuchsia(255, 0, 255, 255);
const CColor CColor::Gainsboro(220, 220, 220, 255);
const CColor CColor::GhostWhite(248, 248, 255, 255);
const CColor CColor::Gold(255, 215, 0, 255);
const CColor CColor::Goldenrod(218, 165, 32, 255);
const CColor CColor::Gray(128, 128, 128, 255);
const CColor CColor::Green(0, 128, 0, 255);
const CColor CColor::GreenYellow(173, 255, 47, 255);
const CColor CColor::Honeydew(240, 255, 240, 255);
const CColor CColor::HotPink(255, 105, 180, 255);
const CColor CColor::IndianRed(205, 92, 92, 255);
const CColor CColor::Indigo(75, 0, 130, 255);
const CColor CColor::Ivory(255, 255, 240, 255);
const CColor CColor::Khaki(240, 230, 140, 255);
const CColor CColor::Lavender(230, 230, 250, 255);
const CColor CColor::LavenderBlush(255, 240, 245, 255);
const CColor CColor::LawnGreen(124, 252, 0, 255);
const CColor CColor::LemonChiffon(255, 250, 205, 255);
const CColor CColor::LightBlue(173, 216, 230, 255);
const CColor CColor::LightCoral(240, 128, 128, 255);
const CColor CColor::LightCyan(224, 255, 255, 255);
const CColor CColor::LightGoldenrodYellow(250, 250, 210, 255);
const CColor CColor::LightGray(211, 211, 211, 255);
const CColor CColor::LightGreen(144, 238, 144, 255);
const CColor CColor::LightPink(255, 182, 193, 255);
const CColor CColor::LightSalmon(255, 160, 122, 255);
const CColor CColor::LightSeaGreen(32, 178, 170, 255);
const CColor CColor::LightSkyBlue(135, 206, 250, 255);
const CColor CColor::LightSlateGray(119, 136, 153, 255);
const CColor CColor::LightSteelBlue(176, 196, 222, 255);
const CColor CColor::LightYellow(255, 255, 224, 255);
const CColor CColor::Lime(0, 255, 0, 255);
const CColor CColor::LimeGreen(50, 205, 50, 255);
const CColor CColor::Linen(250, 240, 230, 255);
const CColor CColor::Magenta(255, 0, 255, 255);
const CColor CColor::Maroon(128, 0, 0, 255);
const CColor CColor::MediumAquamarine(102, 205, 170, 255);
const CColor CColor::MediumBlue(0, 0, 205, 255);
const CColor CColor::MediumOrchid(186, 85, 211, 255);
const CColor CColor::MediumPurple(147, 112, 219, 255);
const CColor CColor::MediumSeaGreen(60, 179, 113, 255);
const CColor CColor::MediumSlateBlue(123, 104, 238, 255);
const CColor CColor::MediumSpringGreen(0, 250, 154, 255);
const CColor CColor::MediumTurquoise(72, 209, 204, 255);
const CColor CColor::MediumVioletRed(199, 21, 133, 255);
const CColor CColor::MidnightBlue(25, 25, 112, 255);
const CColor CColor::MintCream(245, 255, 250, 255);
const CColor CColor::MistyRose(255, 228, 225, 255);
const CColor CColor::Moccasin(255, 228, 181, 255);
const CColor CColor::NavajoWhite(255, 222, 173, 255);
const CColor CColor::Navy(0, 0, 128, 255);
const CColor CColor::OldLace(253, 245, 230, 255);
const CColor CColor::Olive(128, 128, 0, 255);
const CColor CColor::OliveDrab(107, 142, 35, 255);
const CColor CColor::Orange(255, 165, 0, 255);
const CColor CColor::OrangeRed(255, 69, 0, 255);
const CColor CColor::Orchid(218, 112, 214, 255);
const CColor CColor::PaleGoldenrod(238, 232, 170, 255);
const CColor CColor::PaleGreen(152, 251, 152, 255);
const CColor CColor::PaleTurquoise(175, 238, 238, 255);
const CColor CColor::PaleVioletRed(219, 112, 147, 255);
const CColor CColor::PapayaWhip(255, 239, 213, 255);
const CColor CColor::PeachPuff(255, 218, 185, 255);
const CColor CColor::Peru(205, 133, 63, 255);
const CColor CColor::Pink(255, 192, 203, 255);
const CColor CColor::Plum(221, 160, 221, 255);
const CColor CColor::PowderBlue(176, 224, 230, 255);
const CColor CColor::Purple(128, 0, 128, 255);
const CColor CColor::Red(255, 0, 0, 255);
const CColor CColor::RosyBrown(188, 143, 143, 255);
const CColor CColor::RoyalBlue(65, 105, 225, 255);
const CColor CColor::SaddleBrown(139, 69, 19, 255);
const CColor CColor::Salmon(250, 128, 114, 255);
const CColor CColor::SandyBrown(244, 164, 96, 255);
const CColor CColor::SeaGreen(46, 139, 87, 255);
const CColor CColor::SeaShell(255, 245, 238, 255);
const CColor CColor::Sienna(160, 82, 45, 255);
const CColor CColor::Silver(192, 192, 192, 255);
const CColor CColor::SkyBlue(135, 206, 235, 255);
const CColor CColor::SlateBlue(106, 90, 205, 255);
const CColor CColor::SlateGray(112, 128, 144, 255);
const CColor CColor::Snow(255, 250, 250, 255);
const CColor CColor::SpringGreen(0, 255, 127, 255);
const CColor CColor::SteelBlue(70, 130, 180, 255);
const CColor CColor::Tan(210, 180, 140, 255);
const CColor CColor::Teal(0, 128, 128, 255);
const CColor CColor::Thistle(216, 191, 216, 255);
const CColor CColor::Tomato(255, 99, 71, 255);
const CColor CColor::Turquoise(64, 224, 208, 255);
const CColor CColor::Violet(238, 130, 238, 255);
const CColor CColor::Wheat(245, 222, 179, 255);
const CColor CColor::White(255, 255, 255, 255);
const CColor CColor::WhiteSmoke(245, 245, 245, 255);
const CColor CColor::Yellow(255, 255, 0, 255);
const CColor CColor::YellowGreen(154, 205, 50, 255);
const CColor CColor::ButtonFace(240, 240, 240, 255);
const CColor CColor::ButtonHighlight(255, 255, 255, 255);
const CColor CColor::ButtonShadow(160, 160, 160, 255);
const CColor CColor::GradientActiveCaption(185, 209, 234, 255);
const CColor CColor::GradientInactiveCaption(215, 228, 242, 255);
const CColor CColor::MenuBar(240, 240, 240, 255);
const CColor CColor::MenuHighlight(51, 153, 255, 255);

}
