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

#ifndef VECTOR2_H
#define VECTOR2_H

#include "Math.h"

#include <limits>
#include <iostream>
#include <cmath>

#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Classe des vecteurs à 2 composantes de type paramètrable
    ////////////////////////////////////////////////////////////
    template <class T>
    class CVector2 :
		public AllocatedObject<CVector2<T> >
    {
    public :

		//----------------------------------------------------------
		// Static
		//----------------------------------------------------------
		static CVector2<T> Zero();
		static CVector2<T> One();
		static CVector2<T> UnitX();
		static CVector2<T> UnitY();

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        CVector2(T X = 0, T Y = 0);

        //----------------------------------------------------------
        // Réinitialise le vecteur
        //----------------------------------------------------------
        void Set(T X, T Y);
		T getX() const;
		T getY() const;

		///
		bool IsZero() const;

        //----------------------------------------------------------
        // Renvoie la norme du vecteur
        //----------------------------------------------------------
        T Length() const;

        //----------------------------------------------------------
        // Renvoie la norme au carré du vecteur
        //----------------------------------------------------------
        T LengthSquared() const;

        //----------------------------------------------------------
        // Normalise le vecteur
        //----------------------------------------------------------
        void Normalize();

		/*
		 * calculates the dot product
		 */
		inline float    Dot(const CVector2<T>& v2)const;

		/*
		 * returns positive if v2 is clockwise of this vector,
		 * negative if anticlockwise (assuming the Y axis is pointing down,
		 * X axis to right like a Window app)
		 */
		enum {clockwise = 1, anticlockwise = -1};
		inline int       Sign(const CVector2<T>& v2)const;

		/*
		 * returns the vector that is perpendicular to this one.
		 */
		inline CVector2<T>  GetOrthogonal() const;

		/*
		 * adjusts x and y so that the length of the vector does not exceed max
		 */
		inline void      Truncate(float max);

		/*
		 * returns the distance between this vector and th one passed as a parameter
		 */
		inline float    Distance(const CVector2<T> &v2)const;

		/*
		 * squared version of above.
		 */
		inline float    DistanceSq(const CVector2<T> &v2)const;

		/*
		 * given a normalized vector this method reflects the vector it
		 * is operating upon. (like the path of a ball bouncing off a wall)
		 */
		inline void      Reflect(const CVector2<T>& norm);

		/*
		 * returns the vector that is the reverse of this vector
		 */
		inline CVector2<T>  GetReverse()const;

        //----------------------------------------------------------
        // Opérateurs unaires + et -
        //----------------------------------------------------------
        CVector2<T> operator +() const;
        CVector2<T> operator -() const;

        //----------------------------------------------------------
        // Opérateurs binaires + et -
        //----------------------------------------------------------
        CVector2<T> operator +(const CVector2<T>& v) const;
        CVector2<T> operator -(const CVector2<T>& v) const;

        //----------------------------------------------------------
        // Opérateurs += et -=
        //----------------------------------------------------------
        const CVector2<T>& operator +=(const CVector2<T>& v);
        const CVector2<T>& operator -=(const CVector2<T>& v);

        //----------------------------------------------------------
        // Opérateurs * et /
        //----------------------------------------------------------
        CVector2<T> operator *(T t) const;
        CVector2<T> operator /(T t) const;

        //----------------------------------------------------------
        // Opérateurs *= et /=
        //----------------------------------------------------------
        const CVector2<T>& operator *=(T t);
        const CVector2<T>& operator /=(T t);

        //----------------------------------------------------------
        // Opérateurs de comparaison
        //----------------------------------------------------------
        bool operator ==(const CVector2<T>& v) const;
        bool operator !=(const CVector2<T>& v) const;

        //----------------------------------------------------------
        // Opérateur de cast en T*
        //----------------------------------------------------------
        operator T*();

        //----------------------------------------------------------
        // Données membres
        //----------------------------------------------------------
        T x; ///< Composante X
        T y; ///< Composante Y
    };


    //==========================================================
    // Fonctions globales relatives aux vecteurs
    //==========================================================
    template <class T> CVector2<T>   operator * (const CVector2<T>& v, T t);
    template <class T> CVector2<T>   operator / (const CVector2<T>& v, T t);
    template <class T> CVector2<T>   operator * (T t, const CVector2<T>& v);
    template <class T> T             VectorDot  (const CVector2<T>& v1, const CVector2<T>& v2);
    template <class T> CVector2<T>   VectorCross(const CVector2<T>& v1, const CVector2<T>& v2);
    template <class T> std::istream& operator >>(std::istream& Stream, CVector2<T>& Vector);
    template <class T> std::ostream& operator <<(std::ostream& Stream, const CVector2<T>& Vector);


    //==========================================================
    // Définition des types de vecteurs usuels
    //==========================================================
    typedef CVector2<int>   Vector2I;
    typedef CVector2<float> Vector2F;

    #include "Vector2.inl"

} // namespace CasaEngine


#endif // VECTOR2_H
