#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>

#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	template <class T>
	class CVector4 :
		public AllocatedObject<CVector4<T> >
	{
	public:
		CVector4(T X = 0, T Y = 0, T Z = 0, T W = 1);

		void Set(T X, T Y, T Z, T W);
		T getX() const;
		T getY() const;
		T getZ() const;
		T getW() const;

		T Length() const;
		T LengthSquared() const;
		void Normalize();

		CVector4<T> operator +() const;
		CVector4<T> operator -() const;
		CVector4<T> operator +(const CVector4<T>& v) const;
		CVector4<T> operator -(const CVector4<T>& v) const;
		const CVector4<T>& operator +=(const CVector4<T>& v);
		const CVector4<T>& operator -=(const CVector4<T>& v);
		CVector4<T> operator *(T t) const;
		CVector4<T> operator /(T t) const;
		const CVector4<T>& operator *=(T t);
		const CVector4<T>& operator /=(T t);

		bool operator ==(const CVector4<T>& v) const;
		bool operator !=(const CVector4<T>& v) const;

		operator T* ();

		T x;
		T y;
		T z;
		T w;
	};

	template <class T> CVector4<T>   operator * (const CVector4<T>& v, T t);
	template <class T> CVector4<T>   operator / (const CVector4<T>& v, T t);
	template <class T> CVector4<T>   operator * (T t, const CVector4<T>& v);
	template <class T> T             VectorDot(const CVector4<T>& v1, const CVector4<T>& v2);
	template <class T> CVector4<T>   VectorCross(const CVector4<T>& v1, const CVector4<T>& v2);
	template <class T> std::istream& operator >>(std::istream& Stream, CVector4<T>& Vector);
	template <class T> std::ostream& operator <<(std::ostream& Stream, const CVector4<T>& Vector);

	typedef CVector4<int>   Vector4I;
	typedef CVector4<float> Vector4F;

	template <class T>
	CVector4<T>::CVector4(T X, T Y, T Z, T W) :
		x(X),
		y(Y),
		z(Z),
		w(W)
	{
	}
	template <class T>
	void CVector4<T>::Set(T X, T Y, T Z, T W)
	{
		x = X;
		y = Y;
		z = Z;
		w = W;
	}

	template <class T>
	T CVector4<T>::getX() const
	{
		return x;
	}

	template <class T>
	T CVector4<T>::getY() const
	{
		return y;
	}

	template <class T>
	T CVector4<T>::getZ() const
	{
		return z;
	}

	template <class T>
	T CVector4<T>::getW() const
	{
		return w;
	}
	template <class T>
	T CVector4<T>::Length() const
	{
		return std::sqrt(LengthSquared());
	}

	template <class T>
	T CVector4<T>::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	template <class T>
	void CVector4<T>::Normalize()
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

	template <class T>
	CVector4<T> CVector4<T>::operator +() const
	{
		return this;
	}

	template <class T>
	CVector4<T> CVector4<T>::operator -() const
	{
		return CVector4<T>(-x, -y, -z, -w);
	}

	template <class T>
	CVector4<T> CVector4<T>::operator +(const CVector4<T>& v) const
	{
		return CVector4<T>(x + v.x, y + v.y, z + v.z, w + v.w);
	}

	template <class T>
	CVector4<T> CVector4<T>::operator -(const CVector4<T>& v) const
	{
		return CVector4<T>(x - v.x, y - v.y, z - v.z, w - v.w);
	}

	template <class T>
	const CVector4<T>& CVector4<T>::operator +=(const CVector4<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
		w += v.w;

		return *this;
	}

	template <class T>
	const CVector4<T>& CVector4<T>::operator -=(const CVector4<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		w -= v.w;

		return *this;
	}

	template <class T>
	CVector4<T> CVector4<T>::operator *(T t) const
	{
		return CVector4<T>(x * t, y * t, z * t, w * t);
	}

	template <class T>
	CVector4<T> CVector4<T>::operator /(T t) const
	{
		return CVector4<T>(x / t, y / t, z / t, w / t);
	}

	template <class T>
	const CVector4<T>& CVector4<T>::operator *=(T t)
	{
		x *= t;
		y *= t;
		z *= t;
		w *= t;

		return *this;
	}

	template <class T>
	const CVector4<T>& CVector4<T>::operator /=(T t)
	{
		x /= t;
		y /= t;
		z /= t;
		w /= t;

		return *this;
	}

	template <class T>
	bool CVector4<T>::operator ==(const CVector4<T>& v) const
	{
		return ((std::abs(x - v.x) <= std::numeric_limits<T>::epsilon()) &&
			(std::abs(y - v.y) <= std::numeric_limits<T>::epsilon()) &&
			(std::abs(z - v.z) <= std::numeric_limits<T>::epsilon()) &&
			(std::abs(w - v.w) <= std::numeric_limits<T>::epsilon()));
	}

	template <class T>
	bool CVector4<T>::operator !=(const CVector4<T>& v) const
	{
		return !(*this == v);
	}

	template <class T>
	CVector4<T>::operator T* ()
	{
		return &x;
	}

	template <class T>
	CVector4<T> operator *(const CVector4<T>& v, T t)
	{
		return CVector4<T>(v.x * t, v.y * t, v.z * t, v.w * t);
	}

	template <class T>
	CVector4<T> operator /(const CVector4<T>& v, T t)
	{
		return CVector4<T>(v.x / t, v.y / t, v.z / t, v.w / t);
	}

	template <class T>
	CVector4<T> operator *(T t, const CVector4<T>& v)
	{
		return v * t;
	}

	template <class T>
	T VectorDot(const CVector4<T>& v1, const CVector4<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template <class T>
	CVector4<T> VectorCross(const CVector4<T>& v1, const CVector4<T>& v2)
	{
		// ?? Correct ??
		return CVector4<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.w - v1.w * v2.z, v1.w * v2.x - v1.x * v2.w, v1.x * v2.y - v1.y * v2.x);
	}

	template <class T>
	std::istream& operator >>(std::istream& Stream, CVector4<T>& Vector)
	{
		return Stream >> Vector.x >> Vector.y >> Vector.z >> Vector.w;
	}

	template <class T>
	std::ostream& operator <<(std::ostream& Stream, const CVector4<T>& Vector)
	{
		return Stream << Vector.x << " " << Vector.y << " " << Vector.z << " " << Vector.w;
	}
}

#endif
