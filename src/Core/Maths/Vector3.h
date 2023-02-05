#pragma once

#include <iosfwd>
#include <cmath>
#include <algorithm>
#include <cmath>

#include "Math.h"
#include "Maths/ValidNumber.h"
#include "CA_Assert.h"
#include "Log/LogManager.h"

namespace CasaEngine
{
	template <class T>
	class CVector3
	{
	public:
		T x, y, z;

		static CVector3<T> Zero();
		static CVector3<T> One();
		static CVector3<T> UnitX();
		static CVector3<T> UnitY();
		static CVector3<T> UnitZ();

		static CVector3<T> Up();
		static CVector3<T> Down();
		static CVector3<T> Right();
		static CVector3<T> Left();
		static CVector3<T> Forward();
		static CVector3<T> Backward();

		static T Dot(const CVector3<T>& v1, const CVector3<T>& v2);
		static CVector3<T> Cross(const CVector3<T>& v1, const CVector3<T>& v2);

		CVector3();
		CVector3(T X, T Y, T Z);
		void Set(T X, T Y, T Z);
		T GetX() const;
		T GetY() const;
		T GetZ() const;

		bool IsZero() const;

		static T Distance(CVector3<T> a, CVector3<T> b);
		static T DistanceSquared(CVector3<T> a, CVector3<T> b);

		T Length() const;
		T LengthSquared() const;

		static CVector3<T> Normalize(CVector3<T>& vec);
		void Normalize();
		CVector3<T> GetNormalized();

		static CVector3<T> Min(const CVector3<T>& a, const CVector3<T>& b);
		static CVector3<T> Max(const CVector3<T>& a, const CVector3<T>& b);
		void CheckMin(const CVector3<T>& other);
		void CheckMax(const CVector3<T>& other);

		// returns a vector that consists of absolute values of this one's coordinates
		static CVector3<T> Abs(CVector3<T>);
		CVector3<T> Abs() const;
		static CVector3<T> SquareRoot(CVector3<T>& v);

		bool IsValid() const;

		void SetOrthogonal(const CVector3<T>& v);
		CVector3<T> GetOrthogonal() const;

		static CVector3<T> Reflect(CVector3<T>& vector, CVector3<T>& normal);
		static CVector3<T> Clamp(CVector3<T>& value1, CVector3<T>& min, CVector3<T>& max);
		static CVector3<T> Lerp(const CVector3<T>& v1, const CVector3<T>& v2, float t);

		static CVector3<T> Add(const CVector3<T>& v1, const CVector3<T>& v2);
		static CVector3<T> Subtract(const CVector3<T>& v1, const CVector3<T>& v2);
		static CVector3<T> Multiply(const CVector3<T>& v1, const CVector3<T>& v2);
		static CVector3<T> Divide(const CVector3<T>& v1, const CVector3<T>& v2);

		static CVector3<T> Multiply(const CVector3<T>& v1, T d);
		static CVector3<T> Multiply(T d, const CVector3<T>& v1);
		static CVector3<T> Divide(const CVector3<T>& v1, T d);

		static CVector3<T> Negate(const CVector3<T>& v);

		CVector3<T> operator +() const;
		CVector3<T> operator -() const;
		CVector3<T> operator +(const CVector3<T>& v) const;
		CVector3<T> operator -(const CVector3<T>& v) const;
		CVector3<T> operator * (const CVector3<T>& v);
		CVector3<T> operator / (const CVector3<T>& v);
		CVector3<T> operator * (T t);
		CVector3<T> operator / (T t);

		const CVector3<T>& operator +=(const CVector3<T>& v);
		const CVector3<T>& operator -=(const CVector3<T>& v);
		const CVector3<T>& operator *=(T t);
		const CVector3<T>& operator /=(T t);
		bool operator ==(const CVector3<T>& v) const;
		bool operator !=(const CVector3<T>& v) const;

		operator T* ();

		T& operator [] (int index);
		T operator [] (int index) const;
	};

	typedef CVector3<int>   Vector3I;
	typedef CVector3<float> Vector3;

	template <class T>
	bool operator == (CVector3<T>& v0, CVector3<T>& v1)
	{
		return IsEquivalent(v0, v1);
	}

	template <class T>
	bool IsEquivalent(const CVector3<T>& v0, const CVector3<T>& v1, float epsilon = Epsilon)
	{
		return std::fabs(v0.x - v1.x) <= epsilon &&
			std::fabs(v0.y - v1.y) <= epsilon &&
			std::fabs(v0.z - v1.z) <= epsilon;
	}

	template <class T>
	CVector3<T> CVector3<T>::Zero()
	{
		return CVector3<T>(0, 0, 0);
	}

	template <class T>
	CVector3<T> CVector3<T>::One()
	{
		return CVector3<T>(1, 1, 1);
	}

	template <class T>
	CVector3<T> CVector3<T>::UnitX()
	{
		return CVector3<T>(1, 0, 0);
	}

	template <class T>
	CVector3<T> CVector3<T>::UnitY()
	{
		return CVector3<T>(0, 1, 0);
	}

	template <class T>
	CVector3<T> CVector3<T>::UnitZ()
	{
		return CVector3<T>(0, 0, 1);
	}

	template <class T>
	CVector3<T> CVector3<T>::Up()
	{
		return CVector3<T>(0, 1, 0);
	}

	template <class T>
	CVector3<T> CVector3<T>::Down()
	{
		return CVector3<T>(0, -1, 0);
	}

	template <class T>
	CVector3<T> CVector3<T>::Right()
	{
		return CVector3<T>(1, 0, 0);
	}

	template <class T>
	CVector3<T> CVector3<T>::Left()
	{
		return CVector3<T>(-1, 0, 0);
	}

	template <class T>
	CVector3<T> CVector3<T>::Forward()
	{
		return CVector3<T>(0, 0, 1);
	}

	template <class T>
	CVector3<T> CVector3<T>::Backward()
	{
		return CVector3<T>(0, 0, -1);
	}

	template <class T>
	CVector3<T>::CVector3() :
		CVector3(0, 0, 0)
	{
	}

	template <class T>
	CVector3<T>::CVector3(T X, T Y, T Z) :
		x(X),
		y(Y),
		z(Z)
	{
	}

	template <class T>
	void CVector3<T>::Set(T X, T Y, T Z)
	{
		x = X;
		y = Y;
		z = Z;
	}

	template <class T>
	T CVector3<T>::GetX() const
	{
		return x;
	}

	template <class T>
	T CVector3<T>::GetY() const
	{
		return y;
	}

	template <class T>
	T CVector3<T>::GetZ() const
	{
		return z;
	}

	template <class T>
	bool CVector3<T>::IsZero()const
	{
		return LengthSquared() < Epsilon; // std::numeric_limits<T>::epsilon();
	}

	template <class T>
	T CVector3<T>::Distance(CVector3<T> a, CVector3<T> b)
	{
		return (a - b).Length();
	}

	template <class T>
	T CVector3<T>::DistanceSquared(CVector3<T> a, CVector3<T> b)
	{
		return (a - b).LengthSquared();
	}

	template <class T>
	T CVector3<T>::Length() const
	{
		return std::sqrtf(LengthSquared());
	}

	template <class T>
	T CVector3<T>::LengthSquared() const
	{
		return x * x + y * y + z * z;
	}

	template <class T>
	CVector3<T> CVector3<T>::Normalize(CVector3<T>& vec)
	{
		vec.Normalize();
		return vec;
	}

	template <class T>
	void CVector3<T>::Normalize()
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
	CVector3<T> CVector3<T>::GetNormalized()
	{
		CVector3<T> vec = CVector3<T>(x, y, z);
		vec.Normalize();
		return vec;
	}

	template <class T>
	CVector3<T> CVector3<T>::Min(const CVector3<T>& a, const CVector3<T>& b)
	{
		return { std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z) };
	}

	template <class T>
	CVector3<T> CVector3<T>::Max(const CVector3<T>& a, const CVector3<T>& b)
	{
		return { std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z) };
	}

	//! check for min bounds
	template <class T>
	void CVector3<T>::CheckMin(const CVector3<T>& other)
	{
		x = std::min(other.x, x);
		y = std::min(other.y, y);
		z = std::min(other.z, z);
	}

	//! check for max bounds
	template <class T>
	void CVector3<T>::CheckMax(const CVector3<T>& other)
	{
		x = std::max(other.x, x);
		y = std::max(other.y, y);
		z = std::max(other.z, z);
	}

	template <class T>
	CVector3<T> CVector3<T>::Abs(CVector3<T> v)
	{
		return CVector3<T>(std::fabsf(v.x), std::fabsf(v.y), std::fabsf(v.z));
	}

	template <class T>
	CVector3<T> CVector3<T>::Abs() const
	{
		return CVector3<T>(std::fabsf(x), std::fabsf(y), std::fabsf(z));
	}

	template <class T>
	CVector3<T> CVector3<T>::SquareRoot(CVector3<T>& v)
	{
		return CVector3<T>(std::sqrtf(v.x), std::sqrtf(v.y), std::sqrtf(v.z));
	}

	template <class T>
	bool CVector3<T>::IsValid() const
	{
		if (!NumberValid(x))
		{
			return false;
		}
		if (!NumberValid(y))
		{
			return false;
		}
		if (!NumberValid(z))
		{
			return false;
		}
		return true;
	}

	template<class F>
	F sqr(const F& op) { return op * op; }

	template <class T>
	void CVector3<T>::SetOrthogonal(const CVector3<T>& v)
	{
		std::sqrtf(T(0.9))* (v | v) - v.x * v.x < 0 ? (x = -v.z, y = 0, z = v.x) : (x = 0, y = v.z, z = -v.y);
	}

	template <class T>
	CVector3<T> CVector3<T>::GetOrthogonal() const
	{
		return std::sqrtf(T(0.9)) * (x * x + y * y + z * z) - x * x < 0 ? CVector3<T>(-z, 0, x) : CVector3<T>(0, z, -y);
	}

	template <class T>
	CVector3<T> CVector3<T>::Reflect(CVector3<T>& vector, CVector3<T>& normal)
	{
		float dot = Dot(vector, normal);
		CVector3<T> temp = normal * dot * 2.0f;
		return vector - temp;
		/*else
			{
				float dot = vector.X * normal.X + vector.Y * normal.Y + vector.Z * normal.Z;
				float tempX = normal.X * dot * 2f;
				float tempY = normal.Y * dot * 2f;
				float tempZ = normal.Z * dot * 2f;
				return new Vector3(vector.X - tempX, vector.Y - tempY, vector.Z - tempZ);
			}*/
	}

	template <class T>
	CVector3<T> CVector3<T>::Clamp(CVector3<T>& value1, CVector3<T>& min, CVector3<T>& max)
	{
		// This compare order is very important!!!
		// We must follow HLSL behavior in the case user specified min value is bigger than max value.

		float x = value1.x;
		x = x > max.x ? max.x : x;
		x = x < min.x ? min.x : x;

		float y = value1.y;
		y = y > max.y ? max.y : y;
		y = y < min.y ? min.y : y;

		float z = value1.z;
		z = z > max.z ? max.z : z;
		z = z < min.z ? min.z : z;

		return CVector3<T>(x, y, z);
	}

	template <class T>
	CVector3<T> CVector3<T>::Lerp(const CVector3<T>& v1, const CVector3<T>& v2, float t)
	{
		CVector3<T> v3;
		v3.x += v1.x + (v2.x - v1.x) * t;
		v3.y += v1.y + (v2.y - v1.y) * t;
		v3.z += v1.z + (v2.z - v1.z) * t;
		return v3;
	}

	template <class T>
	CVector3<T> CVector3<T>::Add(const CVector3<T>& v1, const CVector3<T>& v2)
	{
		return { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
	}

	template <class T>
	CVector3<T> CVector3<T>::Subtract(const CVector3<T>& v1, const CVector3<T>& v2)
	{
		return { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
	}

	template <class T>
	CVector3<T> CVector3<T>::Multiply(const CVector3<T>& v1, const CVector3<T>& v2)
	{
		return { v1.x * v2.x, v1.y * v2.y, v1.z * v2.z };
	}

	template <class T>
	CVector3<T> CVector3<T>::Divide(const CVector3<T>& v1, const CVector3<T>& v2)
	{
		return { v1.x / v2.x, v1.y / v2.y, v1.z / v2.z };
	}

	template <class T>
	CVector3<T> CVector3<T>::Multiply(const CVector3<T>& v1, T d)
	{
		return { v1.x * d, v1.y * d, v1.z * d };
	}

	template <class T>
	CVector3<T> CVector3<T>::Multiply(T d, const CVector3<T>& v1)
	{
		return { v1.x * d, v1.y * d, v1.z * d };
	}

	template <class T>
	CVector3<T> CVector3<T>::Divide(const CVector3<T>& v1, T d)
	{
		return { v1.x / d, v1.y / d, v1.z / d };
	}

	template <class T>
	CVector3<T> CVector3<T>::Negate(const CVector3<T>& v)
	{
		return -v;
	}

	template <class T>
	CVector3<T> CVector3<T>::operator +() const
	{
		return this;
	}

	template <class T>
	CVector3<T> CVector3<T>::operator -() const
	{
		return CVector3<T>(-x, -y, -z);
	}

	template <class T>
	CVector3<T> CVector3<T>::operator +(const CVector3<T>& v) const
	{
		return Add(*this, v);
	}

	template <class T>
	CVector3<T> CVector3<T>::operator -(const CVector3<T>& v) const
	{
		return Subtract(*this, v);
	}

	template <class T>
	CVector3<T> CVector3<T>::operator*(const CVector3<T>& v)
	{
		return Multiply(*this, v);
	}

	template <class T>
	CVector3<T> CVector3<T>::operator/(const CVector3<T>& v)
	{
		return Divide(*this, v);
	}

	template<class T>
	CVector3<T> CVector3<T>::operator *(T t)
	{
		return CVector3<T>(x * t, y * t, z * t);
	}

	template<class T>
	CVector3<T> CVector3<T>::operator /(T t)
	{
		return CVector3<T>(x / t, y / t, z / t);
	}

	template <class T>
	const CVector3<T>& CVector3<T>::operator +=(const CVector3<T>& v)
	{
		x += v.x;
		y += v.y;
		z += v.z;

		return *this;
	}

	template <class T>
	const CVector3<T>& CVector3<T>::operator -=(const CVector3<T>& v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;

		return *this;
	}

	template <class T>
	const CVector3<T>& CVector3<T>::operator *=(T t)
	{
		x *= t;
		y *= t;
		z *= t;

		return *this;
	}

	template <class T>
	const CVector3<T>& CVector3<T>::operator /=(T t)
	{
		x /= t;
		y /= t;
		z /= t;

		return *this;
	}

	template <class T>
	bool CVector3<T>::operator ==(const CVector3<T>& v) const
	{
		return std::abs(x - v.x) <= std::numeric_limits<T>::epsilon() &&
			std::abs(y - v.y) <= std::numeric_limits<T>::epsilon() &&
			std::abs(z - v.z) <= std::numeric_limits<T>::epsilon();
	}

	template <class T>
	bool CVector3<T>::operator !=(const CVector3<T>& v) const
	{
		return !(*this == v);
	}

	template <class T>
	CVector3<T>::operator T* ()
	{
		return &x;
	}

	template <class T>
	T& CVector3<T>::operator[](int index)
	{
		CA_ASSERT(index >= 0 && index <= 2, "Vector3 operator[]"); return ((T*)this)[index];
	}

	template <class T>
	T CVector3<T>::operator[](int index) const
	{
		CA_ASSERT(index >= 0 && index <= 2, "Vector3 operator[]"); return ((T*)this)[index];
	}

	template <class T>
	T CVector3<T>::Dot(const CVector3<T>& v1, const CVector3<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	template <class T>
	CVector3<T> CVector3<T>::Cross(const CVector3<T>& v1, const CVector3<T>& v2)
	{
		return CVector3<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	template <class T>
	CVector3<T> operator *(const CVector3<T>& v, T t)
	{
		return CVector3<T>(v.x * t, v.y * t, v.z * t);
	}

	template <class T>
	CVector3<T> operator /(const CVector3<T>& v, T t)
	{
		return CVector3<T>(v.x / t, v.y / t, v.z / t);
	}

	template <class T>
	CVector3<T> operator *(T t, const CVector3<T>& v)
	{
		return v * t;
	}
}
