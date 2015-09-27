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


/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
/// \param A : Composante A du plan
/// \param B : Composante B du plan
/// \param C : Composante C du plan
/// \param D : Composante D du plan
///
////////////////////////////////////////////////////////////
inline CPlane::CPlane(float A, float B, float C, float D) :
	n(A, B, C),
	d(D)
{

}


/////////////////////////////////////////////////////////////
/// Constructeur à partir de trois points
///
/// \param v0 : Point 1
/// \param v1 : Point 2
/// \param v2 : Point 3
///
////////////////////////////////////////////////////////////
inline CPlane::CPlane(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2)
{
    BuildFromPoints(v0, v1, v2);
}


/////////////////////////////////////////////////////////////
/// Constructeur à partir d'une normale et d'un point
///
/// \param Normal : Normale
/// \param Point :  Point appartenant au plan
///
////////////////////////////////////////////////////////////
inline CPlane::CPlane(const Vector3F& Normal, const Vector3F& Point) :
n(Normal),
d(Point.Length())
{

}


/////////////////////////////////////////////////////////////
/// Construit le plan à partir de trois points
///
/// \param v0 : Point 1
/// \param v1 : Point 2
/// \param v2 : Point 3
///
////////////////////////////////////////////////////////////
inline void CPlane::BuildFromPoints(const Vector3F& v0, const Vector3F& v1, const Vector3F& v2)
{
    // Calcul de la normale du plan
    n = Vector3F::Cross(v1 - v0, v2 - v0);
    n.Normalize();

    // Calcul de la distance à l'origine
    d = -Vector3F::Dot(n, v0);
}


/////////////////////////////////////////////////////////////
/// Renvoie la plus courte distance entre le plan et un point 3D
///
/// \param Point : Point 3D
///
/// \return Distance entre le point et le plan
///
////////////////////////////////////////////////////////////
inline float CPlane::DistanceToPoint(const Vector3F& Point) const
{
    return Vector3F::Dot(n, Point) + d;
}


/////////////////////////////////////////////////////////////
/// Renvoie la plus courte distance entre le plan et un point 4D
///
/// \param Point : Point 4D
///
/// \return Distance entre le point et le plan
///
////////////////////////////////////////////////////////////
inline float CPlane::DistanceToPoint(const Vector4F& Point) const
{
    return n.x * Point.x + n.y * Point.y + n.z * Point.z + d * Point.w;
}

/**
 * 
 */
inline bool CPlane::IntersectLine(const Vector3F& p1_, const Vector3F& p2_, Vector3F *pOut_)
{
	Vector3F out;
	Vector3F direction, normal;
	float dot, temp;

	normal.x = n.x;
	normal.y = n.y;
	normal.z = n.z;
	direction.x = p2_.x - p1_.x;
	direction.y = p2_.y - p1_.y;
	direction.z = p2_.z - p1_.z;

	dot = Vector3F::Dot(normal, direction);

	if (!dot) return false;

	temp = (d + Vector3F::Dot(normal, p1_) ) / dot;

	pOut_->x = p1_.x - temp * direction.x;
	pOut_->y = p1_.y - temp * direction.y;
	pOut_->z = p1_.z - temp * direction.z;

	return true;
}


/////////////////////////////////////////////////////////////
/// Opérateur de comparaison ==
///
/// \param p : Plan à comparer
///
/// \return True si les deux plans sont identiques
///
////////////////////////////////////////////////////////////
inline bool CPlane::operator ==(const CPlane& p) const
{
    return ((n == p.n) && (fabs(d - p.d) <= std::numeric_limits<float>::epsilon()));
}


/////////////////////////////////////////////////////////////
/// Opérateur de comparaison !=
///
/// \param p : Plan à comparer
///
/// \return True si les deux plans sont différents
///
////////////////////////////////////////////////////////////
inline bool CPlane::operator !=(const CPlane& p) const
{
    return !(*this == p);
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur >> entre un flux et un plan
///
/// \param  Stream : Flux d'entrée
/// \param Plane :  Plan
///
/// \return Référence sur le flux d'entrée
///
////////////////////////////////////////////////////////////
inline std::istream& operator >>(std::istream& Stream, CPlane& Plane)
{
    return Stream >> Plane.n >> Plane.d;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur << entre un flux et un plan
///
/// \param  Stream : Flux de sortie
/// \param Plane :  Plan
///
/// \return Référence sur le flux de sortie
///
////////////////////////////////////////////////////////////
inline std::ostream& operator <<(std::ostream& Stream, const CPlane& Plane)
{
    return Stream << Plane.n << " " << Plane.d;
}

