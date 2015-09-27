
template <class T>
inline CVector3<T> CVector3<T>::Zero()
{
	return CVector3<T>();
}

template <class T>
inline CVector3<T> CVector3<T>::One()
{
	return CVector3<T>(1, 1, 1);
}

template <class T>
inline CVector3<T> CVector3<T>::UnitX()
{
	return CVector3<T>(1);
}

template <class T>
inline CVector3<T> CVector3<T>::UnitY()
{
	return CVector3<T>(0, 1);
}

template <class T>
inline CVector3<T> CVector3<T>::UnitZ()
{
	return CVector3<T>(0, 0, 1);
}

template <class T>
inline CVector3<T> CVector3<T>::Up()
{
	return CVector3<T>(0, 1, 0);
}

template <class T>
inline CVector3<T> CVector3<T>::Down()
{
	return CVector3<T>(0, -1, 0);
}

template <class T>
inline CVector3<T> CVector3<T>::Right()
{
	return CVector3<T>(1, 0, 0);
}

template <class T>
inline CVector3<T> CVector3<T>::Left()
{
	return CVector3<T>(-1, 0, 0);
}

template <class T>
inline CVector3<T> CVector3<T>::Forward()
{
	return CVector3<T>(0, 0, 1);
}

template <class T>
inline CVector3<T> CVector3<T>::Backward()
{
	return CVector3<T>(0, 0, -1);
}


/////////////////////////////////////////////////////////////
/// Constructeur par défaut
///
/// \param X : Composante X du vecteur
/// \param Y : Composante Y du vecteur
/// \param Z : Composante Z du vecteur
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector3<T>::CVector3(T X, T Y, T Z) :
x(X),
y(Y),
z(Z)
{

}


/////////////////////////////////////////////////////////////
/// Réinitialise le vecteur
///
/// \param X : Composante X du vecteur
/// \param Y : Composante Y du vecteur
/// \param Z : Composante Z du vecteur
///
////////////////////////////////////////////////////////////
template <class T>
inline void CVector3<T>::Set(T X, T Y, T Z)
{
    x = X;
    y = Y;
    z = Z;
}

template <class T>
inline T CVector3<T>::getX() const
{
	return x;
}

template <class T>
inline T CVector3<T>::getY() const
{
	return y;
}

template <class T>
inline T CVector3<T>::getZ() const
{
	return z;
}


//returns true if both x and y are zero
template <class T>
inline bool CVector3<T>::IsZero()const
{
	return LengthSquared() < MinDouble; 
}

/////////////////////////////////////////////////////////////
/// Renvoie la norme du vecteur
///
/// \return Valeur de la norme du vecteur sqrt(x² + y² + z²)
///
////////////////////////////////////////////////////////////
template <class T>
inline T CVector3<T>::Length() const
{
    return std::sqrt(static_cast<float>(LengthSquared()));
}


/////////////////////////////////////////////////////////////
/// Renvoie la norme au carré du vecteur
///
/// \return Carré de la norme du vecteur (x² + y² + z²)
///
////////////////////////////////////////////////////////////
template <class T>
inline T CVector3<T>::LengthSquared() const
{
    return x * x + y * y + z * z;
}


/////////////////////////////////////////////////////////////
/// Normalise le vecteur
///
////////////////////////////////////////////////////////////
template <class T>
inline void CVector3<T>::Normalize()
{
    T Norm = Length();

    if (std::abs(Norm) > std::numeric_limits<T>::epsilon())
    {
        x /= Norm;
        y /= Norm;
        z /= Norm;
    }
}

template <class T>
inline CVector3<T> CVector3<T>::GetNormalized()
{
	CVector3<T> vec = CVector3<T>(x, y, z);
	vec.Normalize();
	return vec;
}

//! check for min bounds
template <class T>
inline void CVector3<T>::CheckMin(const CVector3<T>& other)
{ 
	x = std::min(other.x,x);
	y = std::min(other.y,y);
	z = std::min(other.z,z);
}

//! check for max bounds
template <class T>
inline void CVector3<T>::CheckMax(const CVector3<T>& other)
{
	x = std::max(other.x,x);
	y = std::max(other.y,y);
	z = std::max(other.z,z);
}

template <class T>
inline CVector3<T> CVector3<T>::Abs() const
{
	return CVector3<T>(fabsf(x), fabsf(y), fabsf(z));
}

template <class T>
inline bool CVector3<T>::IsValid() const
{
	if (!NumberValid(x)) return false;
	if (!NumberValid(y)) return false;
	if (!NumberValid(z)) return false;
	return true;
}

template<class F> inline F sqr(const F &op) { return op*op; }

template <class T>
inline void CVector3<T>::SetOrthogonal( const CVector3<T>& v )
{
	sqr(T(0.9))*(v|v)-v.x*v.x<0 ? (x=-v.z,y=0,z=v.x) : (x=0,y=v.z,z=-v.y);
}

template <class T>
inline CVector3<T> CVector3<T>::GetOrthogonal() const
{
	return sqr(T(0.9))*(x*x+y*y+z*z)-x*x<0 ? CVector3<T>(-z,0,x) : CVector3<T>(0,z,-y);
}

/////////////////////////////////////////////////////////////
/// Opérateur unaire +
///
/// \return Résultat de l'opération
///
////////////////////////////////////////////////////////////
template <class T>
inline CVector3<T> CVector3<T>::operator +() const
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
inline CVector3<T> CVector3<T>::operator -() const
{
    return CVector3<T>(-x, -y, -z);
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
inline CVector3<T> CVector3<T>::operator +(const CVector3<T>& v) const
{
    return CVector3<T>(x + v.x, y + v.y, z + v.z);
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
inline CVector3<T> CVector3<T>::operator -(const CVector3<T>& v) const
{
    return CVector3<T>(x - v.x, y - v.y, z - v.z);
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
inline const CVector3<T>& CVector3<T>::operator +=(const CVector3<T>& v)
{
    x += v.x;
    y += v.y;
    z += v.z;

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
inline const CVector3<T>& CVector3<T>::operator -=(const CVector3<T>& v)
{
    x -= v.x;
    y -= v.y;
    z -= v.z;

    return *this;
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
inline const CVector3<T>& CVector3<T>::operator *=(T t)
{
    x *= t;
    y *= t;
    z *= t;

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
inline const CVector3<T>& CVector3<T>::operator /=(T t)
{
    x /= t;
    y /= t;
    z /= t;

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
inline bool CVector3<T>::operator ==(const CVector3<T>& v) const
{
    return ((std::abs(x - v.x) <= std::numeric_limits<T>::epsilon()) &&
            (std::abs(y - v.y) <= std::numeric_limits<T>::epsilon()) &&
            (std::abs(z - v.z) <= std::numeric_limits<T>::epsilon()));
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
inline bool CVector3<T>::operator !=(const CVector3<T>& v) const
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
inline CVector3<T>::operator T*()
{
    return &x;
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
inline T CVector3<T>::Dot(const CVector3<T>& v1, const CVector3<T>& v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
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
inline CVector3<T> CVector3<T>::Cross(const CVector3<T>& v1, const CVector3<T>& v2)
{
	return CVector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
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
inline CVector3<T> operator *(const CVector3<T>& v, T t)
{
    return CVector3<T>(v.x * t, v.y * t, v.z * t);
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
inline CVector3<T> operator /(const CVector3<T>& v, T t)
{
    return CVector3<T>(v.x / t, v.y / t, v.z / t);
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
inline CVector3<T> operator *(T t, const CVector3<T>& v)
{
    return v * t;
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
inline std::istream& operator >>(std::istream& Stream, CVector3<T>& Vector)
{
    return Stream >> Vector.x >> Vector.y >> Vector.z;
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
inline std::ostream& operator <<(std::ostream& Stream, const CVector3<T>& Vector)
{
    return Stream << Vector.x << " " << Vector.y << " " << Vector.z;
}
