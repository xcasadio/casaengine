#pragma once

#include <iostream>
#include "Math.h"

namespace CasaEngine
{
	class Matrix4;
	class Quaternion;


	template <class T>
	class CVector2
	{
	public:
		static CVector2<T> Zero();
		static CVector2<T> One();
		static CVector2<T> UnitX();
		static CVector2<T> UnitY();

		CVector2(T X = 0, T Y = 0);
		~CVector2() = default;
		CVector2(const CVector2& rsh) = default;
		//CVector2& operator=(const CVector2& rsh) = default;
		CVector2(CVector2&& rsh) = default;
		CVector2& operator=(CVector2&& rsh) = default;

		void Set(T X, T Y);
		T getX() const;
		T getY() const;

		bool IsZero() const;
		T Length() const;
		T LengthSquared() const;
		void Normalize();
		static CVector2<T> Normalized(const CVector2<T>& v1);

		static float Dot(const CVector2<T>& v1, const CVector2<T>& v2);
		float Dot(const CVector2<T>& v2)const;

		/*
		 * returns positive if v2 is clockwise of this vector,
		 * negative if anticlockwise (assuming the Y axis is pointing down,
		 * X axis to right like a Window app)
		 */
		enum { clockwise = 1, anticlockwise = -1 };

		int       Sign(const CVector2<T>& v2)const;
		CVector2<T>  GetOrthogonal() const;
		void      Truncate(float max);

		static float Distance(const CVector2<T>& v1, const CVector2<T>& v2);
		static float DistanceSquared(const CVector2<T>& v1, const CVector2<T>& v2);
		float    Distance(const CVector2<T>& v2)const;
		float    DistanceSquared(const CVector2<T>& v2)const;

		void      Reflect(const CVector2<T>& normal);
		static CVector2<T> Reflect(const CVector2<T>& vector, const CVector2<T>& normal);
		static CVector2<T> Clamp(const CVector2<T>& value1, const CVector2<T>& min, const CVector2<T>& max);
		static CVector2<T> Lerp(const CVector2<T>& value1, const CVector2<T>& value2, float amount);
		static CVector2<T> Min(const CVector2<T>& v1, const CVector2<T>& v2);
		static CVector2<T> Max(const CVector2<T>& v1, const CVector2<T>& v2);
		static CVector2<T> Abs(const CVector2<T>& v);
		CVector2<T> GetReverse()const;

		static CVector2<T> Transform(CVector2<T> position, Matrix4 matrix);
		static CVector2<T> TransformNormal(CVector2<T> normal, Matrix4 matrix);
		static CVector2<T> Transform(CVector2<T> value, Quaternion rotation);

		CVector2<T>& operator =(const CVector2<T>& v);
		CVector2<T> operator +() const;
		CVector2<T> operator -() const;
		CVector2<T> operator +(const CVector2<T>& v) const;
		CVector2<T> operator -(const CVector2<T>& v) const;
		const CVector2<T>& operator +=(const CVector2<T>& v);
		const CVector2<T>& operator -=(const CVector2<T>& v);
		CVector2<T> operator /(const CVector2<T>& v) const;
		CVector2<T> operator *(const CVector2<T> &v) const;
		CVector2<T> operator *(T t) const;
		CVector2<T> operator /(T t) const;
		const CVector2<T>& operator *=(T t);
		const CVector2<T>& operator /=(T t);
		bool operator ==(const CVector2<T>& v) const;
		bool operator !=(const CVector2<T>& v) const;

		static CVector2<T> Add(CVector2<T> left, CVector2<T> right);
		static CVector2<T> Subtract(CVector2<T> left, CVector2<T> right);
		static CVector2<T> Multiply(CVector2<T> left, CVector2<T> right);
		static CVector2<T> Multiply(CVector2<T> left, T right);
		static CVector2<T> Multiply(T left, CVector2<T> right);
		static CVector2<T> Divide(CVector2<T> left, CVector2<T> right);
		static CVector2<T> Divide(CVector2<T> left, T divisor);
		static CVector2<T> Negate(CVector2<T> value);

		operator T* ();

		T x, y;
	};

	template <class T> CVector2<T>   operator * (const CVector2<T>& v, T t);
	template <class T> CVector2<T>   operator / (const CVector2<T>& v, T t);
	template <class T> CVector2<T>   operator * (T t, const CVector2<T>& v);
	template <class T> T             VectorDot(const CVector2<T>& v1, const CVector2<T>& v2);
	template <class T> CVector2<T>   VectorCross(const CVector2<T>& v1, const CVector2<T>& v2);

	typedef CVector2<int>   Vector2I;
	typedef CVector2<float> Vector2;

	template <class T>
	CVector2<T> CVector2<T>::Zero()
	{
		return CVector2<T>();
	}

	template <class T>
	CVector2<T> CVector2<T>::One()
	{
		return CVector2<T>(1, 1);
	}

	template <class T>
	CVector2<T> CVector2<T>::UnitX()
	{
		return CVector2<T>(1);
	}

	template <class T>
	CVector2<T> CVector2<T>::UnitY()
	{
		return CVector2<T>(0, 1);
	}

	template <class T>
	CVector2<T>::CVector2(T X, T Y) :
		x(X),
		y(Y)
	{
	}

	template <class T>
	void CVector2<T>::Set(T X, T Y)
	{
		x = X;
		y = Y;
	}

	template <class T>
	T CVector2<T>::getX() const
	{
		return x;
	}

	template <class T>
	T CVector2<T>::getY() const
	{
		return y;
	}

	//returns true if both x and y are zero
	template <class T>
	bool CVector2<T>::IsZero()const
	{
		return LengthSquared() < MinDouble;
	}

	template <class T>
	T CVector2<T>::Length() const
	{
		return std::sqrt(static_cast<float>(LengthSquared()));
	}

	template <class T>
	T CVector2<T>::LengthSquared() const
	{
		return (x * x + y * y);
	}

	template <class T>
	void CVector2<T>::Normalize()
	{
		T Norm = Length();

		if (std::abs(Norm) > std::numeric_limits<T>::epsilon())
		{
			x /= Norm;
			y /= Norm;
		}
	}

	template <class T>
	CVector2<T> CVector2<T>::Normalized(const CVector2<T>& v1)
	{
		CVector2<T> result = v1;
		result.Normalize();
		return result;
	}

	template <class T>
	float CVector2<T>::Dot(const CVector2<T>& v1, const CVector2<T>& v2)
	{
		return v1.Dot(v2);
	}

	template <class T>
	float CVector2<T>::Dot(const CVector2<T>& v2) const
	{
		return x * v2.x + y * v2.y;
	}

	//  returns positive if v2 is clockwise of this vector,
	//  minus if anticlockwise (Y axis pointing down, X axis to right)
	template <class T>
	int CVector2<T>::Sign(const CVector2<T>& v2)const
	{
		if (y * v2.x > x * v2.y)
		{
			return anticlockwise;
		}
		return clockwise;
	}

	//  Returns a vector perpendicular to this vector
	template <class T>
	CVector2<T> CVector2<T>::GetOrthogonal() const
	{
		return CVector2<T>(-y, x);
	}

	//  calculates the euclidean distance between two vectors
	template <class T>
	float CVector2<T>::Distance(const CVector2<T>& v2) const
	{
		const float ySeparation = v2.y - y;
		const float xSeparation = v2.x - x;

		return sqrt(ySeparation * ySeparation + xSeparation * xSeparation);
	}

	//  calculates the euclidean distance squared between two vectors
	template <class T>
	float CVector2<T>::DistanceSquared(const CVector2<T>& v2) const
	{
		const float ySeparation = v2.y - y;
		const float xSeparation = v2.x - x;

		return ySeparation * ySeparation + xSeparation * xSeparation;
	}

	//  truncates a vector so that its length does not exceed max
	template <class T>
	void CVector2<T>::Truncate(float max)
	{
		if (this->Length() > max)
		{
			this->Normalize();

			*this *= max;
		}
	}

	template <class T>
	float CVector2<T>::Distance(const CVector2<T>& v1, const CVector2<T>& v2)
	{
		return v1.Distance(v2);
	}

	template <class T>
	float CVector2<T>::DistanceSquared(const CVector2<T>& v1, const CVector2<T>& v2)
	{
		return v1.DistanceSquared(v2);
	}

	//  given a normalized vector this method reflects the vector it
	//  is operating upon. (like the path of a ball bouncing off a wall)
	template <class T>
	void CVector2<T>::Reflect(const CVector2<T>& normal)
	{
		*this = Reflect(*this, normal);
	}

	template <class T>
	CVector2<T> CVector2<T>::Reflect(const CVector2<T>& vector, const CVector2<T>& normal)
	{
		float dot = Dot(vector, normal);
		return vector - (2.0f * dot * normal);
	}

	template <class T>
	CVector2<T> CVector2<T>::Clamp(const CVector2<T>& value1, const CVector2<T>& min, const CVector2<T>& max)
	{
		// This compare order is very important!!!
		// We must follow HLSL behavior in the case user specified min value is bigger than max value.
		float x = value1.x;
		x = (x > max.x) ? max.x : x;
		x = (x < min.x) ? min.x : x;

		float y = value1.y;
		y = (y > max.y) ? max.y : y;
		y = (y < min.y) ? min.y : y;

		return { x, y };
	}

	template <class T>
	CVector2<T> CVector2<T>::Lerp(const CVector2<T>& value1, const CVector2<T>& value2, float amount)
	{
		return {
			value1.x + (value2.x - value1.x) * amount,
			value1.y + (value2.y - value1.y) * amount };
	}

	template <class T>
	CVector2<T> CVector2<T>::Min(const CVector2<T>& v1, const CVector2<T>& v2)
	{
		return { std::min(v1.x, v2.x), std::min(v1.y, v2.y) };
	}

	template <class T>
	CVector2<T> CVector2<T>::Max(const CVector2<T>& v1, const CVector2<T>& v2)
	{
		return { std::max(v1.x, v2.x), std::max(v1.y, v2.y) };
	}

	template <class T>
	CVector2<T> CVector2<T>::Abs(const CVector2<T> &v)
	{
		return CVector2<T>(std::fabsf(v.x), std::fabsf(v.y));
	}

	//  returns the vector that is the reverse of this vector
	template <class T>
	CVector2<T> CVector2<T>::GetReverse() const
	{
		return CVector2<T>(-this->x, -this->y);
	}

	template <class T>
	CVector2<T> CVector2<T>::Transform(CVector2<T> position, Matrix4 matrix)
	{
		return {
			position.x * matrix.m11 + position.y * matrix.m21 + matrix.m41,
			position.x * matrix.m12 + position.y * matrix.m22 + matrix.m42 };
	}

	template <class T>
	CVector2<T> CVector2<T>::TransformNormal(CVector2<T> normal, Matrix4 matrix)
	{
		return {
			normal.x * matrix.m11 + normal.y * matrix.m21,
			normal.x * matrix.m12 + normal.y * matrix.m22 };
	}

	template <class T>
	CVector2<T> CVector2<T>::Transform(CVector2<T> value, Quaternion rotation)
	{
		float x2 = rotation.x + rotation.x;
		float y2 = rotation.y + rotation.y;
		float z2 = rotation.z + rotation.z;

		float wz2 = rotation.w * z2;
		float xx2 = rotation.x * x2;
		float xy2 = rotation.x * y2;
		float yy2 = rotation.y * y2;
		float zz2 = rotation.z * z2;

		return {
			value.x * (1.0f - yy2 - zz2) + value.y * (xy2 - wz2),
			value.x * (xy2 + wz2) + value.y * (1.0f - xx2 - zz2) };
	}

	template <class T>
	CVector2<T>& CVector2<T>::operator=(const CVector2<T>& v)
	{
		x = v.x;
		y = v.y;
		return *this;
	}

	template <class T>
	CVector2<T> CVector2<T>::operator +() const
	{
		return this;
	}

	template <class T>
	CVector2<T> CVector2<T>::operator -() const
	{
		return CVector2<T>(-x, -y);
	}

	template <class T>
	CVector2<T> CVector2<T>::operator +(const CVector2<T>& v) const
	{
		return CVector2<T>(x + v.x, y + v.y);
	}

	template <class T>
	CVector2<T> CVector2<T>::operator -(const CVector2<T>& v) const
	{
		return CVector2<T>(x - v.x, y - v.y);
	}

	template <class T>
	const CVector2<T>& CVector2<T>::operator +=(const CVector2<T>& v)
	{
		x += v.x;
		y += v.y;

		return *this;
	}

	template <class T>
	const CVector2<T>& CVector2<T>::operator -=(const CVector2<T>& v)
	{
		x -= v.x;
		y -= v.y;

		return *this;
	}

	template <class T>
	CVector2<T> CVector2<T>::operator/(const CVector2<T>& v) const
	{
		return CVector2<T>(x / v.x, y / v.y);
	}

	template <class T>
	CVector2<T> CVector2<T>::operator*(const CVector2<T>& v) const
	{
		return CVector2<T>(x * v.x, y * v.y);
	}

	template <class T>
	CVector2<T> CVector2<T>::operator *(T t) const
	{
		return CVector2<T>(x * t, y * t);
	}

	template <class T>
	CVector2<T> CVector2<T>::operator /(T t) const
	{
		return CVector2<T>(x / t, y / t);
	}

	template <class T>
	const CVector2<T>& CVector2<T>::operator *=(T t)
	{
		x *= t;
		y *= t;

		return *this;
	}

	template <class T>
	const CVector2<T>& CVector2<T>::operator /=(T t)
	{
		x /= t;
		y /= t;

		return *this;
	}

	template <class T>
	bool CVector2<T>::operator ==(const CVector2<T>& v) const
	{
		return ((std::abs(x - v.x) <= std::numeric_limits<T>::epsilon()) &&
			(std::abs(y - v.y) <= std::numeric_limits<T>::epsilon()));
	}

	template <class T>
	bool CVector2<T>::operator !=(const CVector2<T>& v) const
	{
		return !(*this == v);
	}

	template <class T>
	CVector2<T> CVector2<T>::Add(CVector2<T> left, CVector2<T> right)
	{
		return left + right;
	}

	template <class T>
	CVector2<T> CVector2<T>::Subtract(CVector2<T> left, CVector2<T> right)
	{
		return left - right;
	}

	template <class T>
	CVector2<T> CVector2<T>::Multiply(CVector2<T> left, CVector2<T> right)
	{
		return left * right;
	}

	template <class T>
	CVector2<T> CVector2<T>::Multiply(CVector2<T> left, T right)
	{
		return left * right;
	}

	template <class T>
	CVector2<T> CVector2<T>::Multiply(T left, CVector2<T> right)
	{
		return left * right;
	}

	template <class T>
	CVector2<T> CVector2<T>::Divide(CVector2<T> left, CVector2<T> right)
	{
		return left / right;
	}

	template <class T>
	CVector2<T> CVector2<T>::Divide(CVector2<T> left, T divisor)
	{
		return left / divisor;
	}

	template <class T>
	CVector2<T> CVector2<T>::Negate(CVector2<T> value)
	{
		return -value;
	}

	template <class T>
	CVector2<T>::operator T* ()
	{
		return &x;
	}

	template <class T>
	CVector2<T> operator *(const CVector2<T>& v, T t)
	{
		return CVector2<T>(v.x * t, v.y * t);
	}

	template <class T>
	CVector2<T> operator /(const CVector2<T>& v, T t)
	{
		return CVector2<T>(v.x / t, v.y / t);
	}

	template <class T>
	CVector2<T> operator *(T t, const CVector2<T>& v)
	{
		return v * t;
	}

	template <class T>
	T VectorDot(const CVector2<T>& v1, const CVector2<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y;
	}

	template <class T>
	CVector2<T> VectorCross(const CVector2<T>& v1, const CVector2<T>& v2)
	{
		return CVector2<T>(/* ??? */);
	}
}
