#ifndef VECTOR4_H
#define VECTOR4_H

#include "Math.h"

#include <limits>
#include <iostream>
#include <cmath>

#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
    ////////////////////////////////////////////////////////////
    /// Classe des vecteurs � 4 composantes de type param�trable
    ////////////////////////////////////////////////////////////
    template <class T>
    class CVector4 :
		public AllocatedObject<CVector4<T> >
    {
    public :

        //----------------------------------------------------------
        // Constructeur par d�faut
        //----------------------------------------------------------
        CVector4(T X = 0, T Y = 0, T Z = 0, T W = 1);

        //----------------------------------------------------------
        // R�initialise le vecteur
        //----------------------------------------------------------
        void Set(T X, T Y, T Z, T W);
		T getX() const;
		T getY() const;
		T getZ() const;
		T getW() const;

        //----------------------------------------------------------
        // Renvoie la norme du vecteur
        //----------------------------------------------------------
        T Length() const;

        //----------------------------------------------------------
        // Renvoie la norme au carr� du vecteur
        //----------------------------------------------------------
        T LengthSquared() const;

        //----------------------------------------------------------
        // Normalise le vecteur
        //----------------------------------------------------------
        void Normalize();

        //----------------------------------------------------------
        // Op�rateurs unaires + et -
        //----------------------------------------------------------
        CVector4<T> operator +() const;
        CVector4<T> operator -() const;

        //----------------------------------------------------------
        // Op�rateurs binaires + et -
        //----------------------------------------------------------
        CVector4<T> operator +(const CVector4<T>& v) const;
        CVector4<T> operator -(const CVector4<T>& v) const;

        //----------------------------------------------------------
        // Op�rateurs += et -=
        //----------------------------------------------------------
        const CVector4<T>& operator +=(const CVector4<T>& v);
        const CVector4<T>& operator -=(const CVector4<T>& v);

        //----------------------------------------------------------
        // Op�rateurs * et /
        //----------------------------------------------------------
        CVector4<T> operator *(T t) const;
        CVector4<T> operator /(T t) const;

        //----------------------------------------------------------
        // Op�rateurs *= et /=
        //----------------------------------------------------------
        const CVector4<T>& operator *=(T t);
        const CVector4<T>& operator /=(T t);

        //----------------------------------------------------------
        // Op�rateurs de comparaison
        //----------------------------------------------------------
        bool operator ==(const CVector4<T>& v) const;
        bool operator !=(const CVector4<T>& v) const;

        //----------------------------------------------------------
        // Op�rateur de cast en T*
        //----------------------------------------------------------
        operator T*();

        //----------------------------------------------------------
        // Donn�es membres
        //----------------------------------------------------------
        T x; ///< Composante X
        T y; ///< Composante Y
        T z; ///< Composante Z
        T w; ///< Composante W
    };


    //==========================================================
    // Fonctions globales relatives aux vecteurs
    //==========================================================
    template <class T> CVector4<T>   operator * (const CVector4<T>& v, T t);
    template <class T> CVector4<T>   operator / (const CVector4<T>& v, T t);
    template <class T> CVector4<T>   operator * (T t, const CVector4<T>& v);
    template <class T> T             VectorDot  (const CVector4<T>& v1, const CVector4<T>& v2);
    template <class T> CVector4<T>   VectorCross(const CVector4<T>& v1, const CVector4<T>& v2);
    template <class T> std::istream& operator >>(std::istream& Stream, CVector4<T>& Vector);
    template <class T> std::ostream& operator <<(std::ostream& Stream, const CVector4<T>& Vector);


    //==========================================================
    // D�finition des types de vecteurs usuels
    //==========================================================
    typedef CVector4<int>   Vector4I;
    typedef CVector4<float> Vector4F;

    #include "Vector4.inl"

} // namespace CasaEngine


#endif // VECTOR4_H
