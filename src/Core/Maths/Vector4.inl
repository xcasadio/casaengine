
/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
/// \param X : Composante X du vecteur
/// \param Y : Composante Y du vecteur
/// \param Z : Composante Z du vecteur
/// \param W : Composante W du vecteur
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T>::CVector4(T X, T Y, T Z, T W) :
	x(X),
	y(Y),
	z(Z),
	w(W)
{

}


/////////////////////////////////////////////////////////////
/// Réinitialise le vecteur
///
/// \param X : Composante X du vecteur
/// \param Y : Composante Y du vecteur
/// \param Z : Composante Z du vecteur
/// \param W : Composante W du vecteur
///
////////////////////////////////////////////////////////////
template <class T>
inline void CVector4<T>::Set(T X, T Y, T Z, T W)
{
    x = X;
    y = Y;
    z = Z;
    w = W;
}


template <class T>
inline T CVector4<T>::getX() const
{
	return x;
}

template <class T>
inline T CVector4<T>::getY() const
{
	return y;
}

template <class T>
inline T CVector4<T>::getZ() const
{
	return z;
}

template <class T>
inline T CVector4<T>::getW() const
{
	return w;
}

/////////////////////////////////////////////////////////////
/// Renvoie la norme du vecteur
///
/// \return Valeur de la norme du vecteur sqrt(x² + y² + z² + w²)
///
////////////////////////////////////////////////////////////
template <class T>
inline T CVector4<T>::Length() const
{
    return std::sqrt(LengthSquared());
}


/////////////////////////////////////////////////////////////
/// Renvoie la norme au carré du vecteur
///
/// \return Carré de la norme du vecteur (x² + y² + z² + w²)
///
////////////////////////////////////////////////////////////
template <class T>
inline T CVector4<T>::LengthSquared() const
{
    return x * x + y * y + z * z + w * w;
}


/////////////////////////////////////////////////////////////
/// Normalise le vecteur
///
////////////////////////////////////////////////////////////
template <class T>
inline void CVector4<T>::Normalize()
{
    T Norm = Length();

    if (std::abs(Norm) > std::numeric_limits<T>::epsilon())
    {
        x /= Norm;
        y /= Norm;
        z /= Norm;
        w /= Norm;
    }
}


/////////////////////////////////////////////////////////////
/// Opérateur unaire +
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> CVector4<T>::operator +() const
{
    return this;
}


/////////////////////////////////////////////////////////////
/// Opérateur unaire -
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> CVector4<T>::operator -() const
{
    return CVector4<T>(-x, -y, -z, -w);
}


/////////////////////////////////////////////////////////////
/// Opérateur binaire +
///
/// \param v : Vecteur à additionner
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> CVector4<T>::operator +(const CVector4<T>& v) const
{
    return CVector4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
}


/////////////////////////////////////////////////////////////
/// Opérateur binaire -
///
/// \param v : Vecteur à soustraire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> CVector4<T>::operator -(const CVector4<T>& v) const
{
    return CVector4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
}

/////////////////////////////////////////////////////////////
/// Opérateur +=
///
/// \param v : Vecteur à additioner
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline const CVector4<T>& CVector4<T>::operator +=(const CVector4<T>& v)
{
    x += v.x;
    y += v.y;
    z += v.z;
    w += v.w;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur -=
///
/// \param v : Vecteur à soustraire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline const CVector4<T>& CVector4<T>::operator -=(const CVector4<T>& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;
    w -= v.w;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateurs de multiplication avec un scalaire
///
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> CVector4<T>::operator *(T t) const
{
    return CVector4<T>(x * t, y * t, z * t, w * t);
}


/////////////////////////////////////////////////////////////
/// Opérateurs de division par un scalaire
///
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> CVector4<T>::operator /(T t) const
{
    return CVector4<T>(x / t, y / t, z / t, w / t);
}


/////////////////////////////////////////////////////////////
/// Opérateur *= avec un scalaire
///
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline const CVector4<T>& CVector4<T>::operator *=(T t)
{
    x *= t;
    y *= t;
    z *= t;
    w *= t;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur /= avec un scalaire
///
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline const CVector4<T>& CVector4<T>::operator /=(T t)
{
    x /= t;
    y /= t;
    z /= t;
    w /= t;

    return *this;
}


/////////////////////////////////////////////////////////////
/// Opérateur de comparaison ==
///
/// \param v : Vecteur à comparer
///
/// \return True si les deux vecteurs sont identiques
///
////////////////////////////////////////////////////////////
template <class T>
inline bool CVector4<T>::operator ==(const CVector4<T>& v) const
{
    return ((std::abs(x - v.x) <= std::numeric_limits<T>::epsilon()) &&
            (std::abs(y - v.y) <= std::numeric_limits<T>::epsilon()) &&
            (std::abs(z - v.z) <= std::numeric_limits<T>::epsilon()) &&
            (std::abs(w - v.w) <= std::numeric_limits<T>::epsilon()));
}


/////////////////////////////////////////////////////////////
/// Opérateur de comparaison !=
///
/// \param v : Vecteur à comparer
///
/// \return True si les deux vecteurs sont différents
///
////////////////////////////////////////////////////////////
template <class T>
inline bool CVector4<T>::operator !=(const CVector4<T>& v) const
{
    return !(*this == v);
}


/////////////////////////////////////////////////////////////
/// Opérateur de cast en T*
///
/// \return Pointeur sur les composantes du vecteur
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T>::operator T*()
{
    return &x;
}


/////////////////////////////////////////////////////////////
/// Opérateurs de multiplication avec un scalaire
///
/// \param v : Vecteur
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> operator *(const CVector4<T>& v, T t)
{
    return CVector4<T>(v.x * t, v.y * t, v.z * t, v.w * t);
}


/////////////////////////////////////////////////////////////
/// Opérateurs de division par un scalaire
///
/// \param v : Vecteur
/// \param t : Scalaire
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> operator /(const CVector4<T>& v, T t)
{
    return CVector4<T>(v.x / t, v.y / t, v.z / t, v.w / t);
}


/////////////////////////////////////////////////////////////
/// Opérateurs de multiplication avec un scalaire
///
/// \param t : Scalaire
/// \param v : Vecteur
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> operator *(T t, const CVector4<T>& v)
{
    return v * t;
}


/////////////////////////////////////////////////////////////
/// Effectue le produit scalaire entre deux vecteurs
///
/// \param v1 : Vecteur 1
/// \param v2 : Vecteur 2
///
/// \return Résultat du produit scalaire
///
////////////////////////////////////////////////////////////
template <class T>
inline T VectorDot(const CVector4<T>& v1, const CVector4<T>& v2)
{
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
}


/////////////////////////////////////////////////////////////
/// Effectue le produit vectoriel entre deux vecteurs
///
/// \param v1 : Vecteur 1
/// \param v2 : Vecteur 2
///
/// \return Résultat du produit vectoriel
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector4<T> VectorCross(const CVector4<T>& v1, const CVector4<T>& v2)
{
    // ?? Correct ??
    return CVector4<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.w - v1.w * v2.z, v1.w * v2.x - v1.x * v2.w, v1.x * v2.y - v1.y * v2.x);
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur >> entre un flux et un vecteur
///
/// \param Stream : Flux d'entrée
/// \param Vector : Vecteur
///
/// \return Référence sur le flux d'entrée
///
////////////////////////////////////////////////////////////
template <class T>
inline std::istream& operator >>(std::istream& Stream, CVector4<T>& Vector)
{
    return Stream >> Vector.x >> Vector.y >> Vector.z >> Vector.w;
}


/////////////////////////////////////////////////////////////
/// Surcharge de l'opérateur << entre un flux et un vecteur
///
/// \param Stream : Flux de sortie
/// \param Vector : Vecteur
///
/// \return Référence sur le flux de sortie
///
////////////////////////////////////////////////////////////
template <class T>
inline std::ostream& operator <<(std::ostream& Stream, const CVector4<T>& Vector)
{
    return Stream << Vector.x << " " << Vector.y << " " << Vector.z << " " << Vector.w;
}
