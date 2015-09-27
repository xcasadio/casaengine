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
    /// Classe des vecteurs à 4 composantes de type paramètrable
    ////////////////////////////////////////////////////////////
    template <class T>
    class CVector4 :
		public AllocatedObject<CVector4<T> >
    {
    public :

        //----------------------------------------------------------
        // Constructeur par défaut
        //----------------------------------------------------------
        CVector4(T X = 0, T Y = 0, T Z = 0, T W = 1);

        //----------------------------------------------------------
        // Réinitialise le vecteur
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
        // Renvoie la norme au carré du vecteur
        //----------------------------------------------------------
        T LengthSquared() const;

        //----------------------------------------------------------
        // Normalise le vecteur
        //----------------------------------------------------------
        void Normalize();

        //----------------------------------------------------------
        // Opérateurs unaires + et -
        //----------------------------------------------------------
        CVector4<T> operator +() const;
        CVector4<T> operator -() const;

        //----------------------------------------------------------
        // Opérateurs binaires + et -
        //----------------------------------------------------------
        CVector4<T> operator +(const CVector4<T>& v) const;
        CVector4<T> operator -(const CVector4<T>& v) const;

        //----------------------------------------------------------
        // Opérateurs += et -=
        //----------------------------------------------------------
        const CVector4<T>& operator +=(const CVector4<T>& v);
        const CVector4<T>& operator -=(const CVector4<T>& v);

        //----------------------------------------------------------
        // Opérateurs * et /
        //----------------------------------------------------------
        CVector4<T> operator *(T t) const;
        CVector4<T> operator /(T t) const;

        //----------------------------------------------------------
        // Opérateurs *= et /=
        //----------------------------------------------------------
        const CVector4<T>& operator *=(T t);
        const CVector4<T>& operator /=(T t);

        //----------------------------------------------------------
        // Opérateurs de comparaison
        //----------------------------------------------------------
        bool operator ==(const CVector4<T>& v) const;
        bool operator !=(const CVector4<T>& v) const;

        //----------------------------------------------------------
        // Opérateur de cast en T*
        //----------------------------------------------------------
        operator T*();

        //----------------------------------------------------------
        // Données membres
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
    // Définition des types de vecteurs usuels
    //==========================================================
    typedef CVector4<int>   Vector4I;
    typedef CVector4<float> Vector4F;

    #include "Vector4.inl"

} // namespace CasaEngine


#endif // VECTOR4_H
