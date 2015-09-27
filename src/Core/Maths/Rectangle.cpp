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


//==========================================================
// En-têtes
//==========================================================
#include "Base.h"

#include "Maths/Rectangle.h"
#include <algorithm>

namespace CasaEngine
{

/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
/// \param Start : Origine
/// \param Size :  Taille
///
////////////////////////////////////////////////////////////
CRectangle::CRectangle(const Vector2I& Start, const Vector2I& Size) :
Origin(Start),
End   (Start + Size)
{

}


/////////////////////////////////////////////////////////////
/// Constructeur à partir de 2 coordonnées et 2 dimensions
///
/// \param Left :   Gauche
/// \param Top :    Haut
/// \param Width :  Largeur
/// \param Height : Hauteur
///
////////////////////////////////////////////////////////////
CRectangle::CRectangle(int Left, int Top, int Width, int Height) :
Origin(Left, Top),
End   (Left + Width, Top + Height)
{

}


/////////////////////////////////////////////////////////////
/// Réinitialise le rectangle
///
/// \param Left :   Gauche
/// \param Top :    Haut
/// \param Width :  Largeur
/// \param Height : Hauteur
///
////////////////////////////////////////////////////////////
void CRectangle::Set(int Left, int Top, int Width, int Height)
{
    Origin.Set(Left, Top);
    End.Set(Left + Width, Top + Height);
}


/////////////////////////////////////////////////////////////
/// Renvoie le coté gauche du rectangle
///
/// \return Gauche du rectangle
///
////////////////////////////////////////////////////////////
int CRectangle::Left() const
{
    return Origin.x;
}


/////////////////////////////////////////////////////////////
/// Renvoie le coté droit du rectangle
///
/// \return Droite du rectangle
///
////////////////////////////////////////////////////////////
int CRectangle::Right() const
{
    return End.x;
}


/////////////////////////////////////////////////////////////
/// Renvoie le coté haut du rectangle
///
/// \return Haut du rectangle
///
////////////////////////////////////////////////////////////
int CRectangle::Top() const
{
    return Origin.y;
}


/////////////////////////////////////////////////////////////
/// Renvoie le coté bas du rectangle
///
/// \return Bas du rectangle
///
////////////////////////////////////////////////////////////
int CRectangle::Bottom() const
{
    return End.y;
}


/////////////////////////////////////////////////////////////
/// Renvoie la largeur du rectangle
///
/// \return Largeur du rectangle
///
////////////////////////////////////////////////////////////
int CRectangle::Width() const
{
    return End.x - Origin.x;
}


/////////////////////////////////////////////////////////////
/// Renvoie la hauteur du rectangle
///
/// \return Hauteur du rectangle
///
////////////////////////////////////////////////////////////
int CRectangle::Height() const
{
    return End.y - Origin.y;
}


/////////////////////////////////////////////////////////////
/// Renvoie la taille du rectangle
///
/// \return Taille du rectangle
///
////////////////////////////////////////////////////////////
Vector2I CRectangle::Size() const
{
    return End - Origin;
}


/////////////////////////////////////////////////////////////
/// Test d'intersection avec un point
///
/// \param Point : Point à tester
///
/// \return Type d'intersection
///
////////////////////////////////////////////////////////////
TIntersection CRectangle::Intersects(const Vector2I& Point) const
{
    if ((Point.x >= Origin.x) && (Point.y >= Origin.y) && (Point.x <= End.x) && (Point.y <= End.y))
        return INT_IN;
    else
        return INT_OUT;
}


/////////////////////////////////////////////////////////////
/// Test d'intersection avec un rectangle
///
/// \param Rect : Rectangle à tester
///
/// \return Type d'intersection
///
////////////////////////////////////////////////////////////
TIntersection CRectangle::Intersects(const CRectangle& Rect) const
{
    // Calcul du rectangle d'intersection
    Vector2I Start(::std::max(Origin.x, Rect.Origin.x), ::std::max(Origin.y, Rect.Origin.y));
    Vector2I End(::std::min(End.x, Rect.End.x), ::std::min(End.y, Rect.End.y));
    CRectangle Overlap(Start, End - Start);

    if ((Start.x > End.x) || (Start.y > End.y))
        return INT_OUT;
    else if ((Overlap == *this) || (Overlap == Rect))
        return INT_IN;
    else
        return INT_INTERSECTS;
}


/////////////////////////////////////////////////////////////
/// Opérateur de comparaison ==
///
/// \param Rect : Rectangle à comparer
///
/// \return True si les deux rectangles sont identiques
///
////////////////////////////////////////////////////////////
bool CRectangle::operator ==(const CRectangle& Rect) const
{
    return (Origin == Rect.Origin) && (End == Rect.End);
}


/////////////////////////////////////////////////////////////
/// Opérateur de comparaison !=
///
/// \param Rect : Rectangle à comparer
///
/// \return True si les deux rectangles sont différents
///
////////////////////////////////////////////////////////////
bool CRectangle::operator !=(const CRectangle& Rect) const
{
    return !(*this == Rect);
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur >> pour saisir un rectangle
///
/// \param  Stream : Flux d'entrée
/// \param Rect :   Rectangle à saisir
///
/// \return Référence sur le flux d'entrée
///
////////////////////////////////////////////////////////////
std::istream& operator >>(std::istream& Stream, CRectangle& Rect)
{
    return Stream >> Rect.Origin >> Rect.End;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur << pour afficher un rectangle
///
/// \param Stream : Flux de sortie
/// \param Rect :   Rectangle à afficher
///
/// \return Référence sur le flux de sortie
///
////////////////////////////////////////////////////////////
std::ostream& operator <<(std::ostream& Stream, const CRectangle& Rect)
{
    return Stream << Rect.Origin << " " << Rect.End;
}

} // namespace CasaEngine
