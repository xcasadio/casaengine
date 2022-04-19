#pragma once

#include <iostream>

namespace CasaEngine
{
	template <class T> class CVector2;
	template <class T> class CVector3;
	class Matrix4;
	class Quaternion;

	template <class T>
	class CVector4
	{
	public:
		CVector4(T X = 0, T Y = 0, T Z = 0, T W = 1);

		void Set(T X, T Y, T Z, T W);
		T getX() const;
		T getY() const;
		T getZ() const;
		T getW() const;

		static CVector4<T> Zero();
		static CVector4<T> One();
		static CVector4<T> UnitX();
		static CVector4<T> UnitY();
		static CVector4<T> UnitZ();
		static CVector4<T> UnitW();

		T Length() const;
		T LengthSquared() const;
		void Normalized();
		static CVector4<T> Normalize(const CVector4<T> &v);
		static T Dot(const CVector4<T>& v1, const CVector4<T>& v2);
		static CVector4<T> Cross(const CVector4<T>& v1, const CVector4<T>& v2);
		static float Distance(CVector4<T> value1, CVector4<T> value2);
		static float DistanceSquared(CVector4<T> value1, CVector4<T> value2);
        static CVector4<T> Clamp(CVector4<T> value1, CVector4<T> min, CVector4<T> max);
		static CVector4<T> Lerp(CVector4<T> value1, CVector4<T> value2, float amount);
		static CVector4<T> Transform(CVector2<T> position, Matrix4 matrix);
		static CVector4<T> Transform(CVector3<T> position, Matrix4 matrix);
		static CVector4<T> Transform(CVector4<T> vector, Matrix4 matrix);
		static CVector4<T> Transform(CVector2<T> value, Quaternion rotation);
		static CVector4<T> Transform(CVector3<T> value, Quaternion rotation);
		static CVector4<T> Transform(CVector4<T> value, Quaternion rotation);
		static CVector4<T> Add(CVector4<T> left, CVector4<T> right);
		static CVector4<T> Subtract(CVector4<T> left, CVector4<T> right);
		static CVector4<T> Multiply(CVector4<T> left, CVector4<T> right);
		static CVector4<T> Multiply(CVector4<T> left, float right);
		static CVector4<T> Multiply(float left, CVector4<T> right);
		static CVector4<T> Divide(CVector4<T> left, CVector4<T> right);
		static CVector4<T> Divide(CVector4<T> left, float divisor);
		static CVector4<T> Negate(CVector4<T> value);
		static CVector4<T> Min(const CVector4<T>& a, const CVector4<T>& b);
		static CVector4<T> Max(const CVector4<T>& a, const CVector4<T>& b);
		static CVector4<T> Abs(CVector4<T> v);
		CVector4<T> Abs() const;
		static CVector4<T> SquareRoot(CVector4<T>& v);

		CVector4<T> operator +() const;
		CVector4<T> operator -() const;
		CVector4<T> operator +(const CVector4<T>& v) const;
		CVector4<T> operator -(const CVector4<T>& v) const;
		CVector4<T> operator /(const CVector4<T>& v) const;
		CVector4<T> operator *(const CVector4<T>& v) const;
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
	template <class T> std::istream& operator >>(std::istream& stream, CVector4<T>& vector);
	template <class T> std::ostream& operator <<(std::ostream& Stream, const CVector4<T>& Vector);

	typedef CVector4<int>   Vector4I;
	typedef CVector4<float> Vector4;

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
	CVector4<T> CVector4<T>::Zero()
	{
		return CVector4<T>(0, 0, 0, 0);
	}

	template <class T>
	CVector4<T> CVector4<T>::One()
	{
		return CVector4<T>(1, 1, 1, 1);
	}

	template <class T>
	CVector4<T> CVector4<T>::UnitX()
	{
		return CVector4<T>(1, 0, 0, 0);
	}

	template <class T>
	CVector4<T> CVector4<T>::UnitY()
	{
		return CVector4<T>(0, 1, 0, 0);
	}

	template <class T>
	CVector4<T> CVector4<T>::UnitZ()
	{
		return CVector4<T>(0, 0, 1, 0);
	}

	template <class T>
	CVector4<T> CVector4<T>::UnitW()
	{
		return CVector4<T>(0, 0, 0, 1);
	}

	template <class T>
	T CVector4<T>::Length() const
	{
		return std::sqrtf(LengthSquared());
	}

	template <class T>
	T CVector4<T>::LengthSquared() const
	{
		return x * x + y * y + z * z + w * w;
	}

	template <class T>
	void CVector4<T>::Normalized()
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
	CVector4<T> CVector4<T>::Normalize(const CVector4<T>& v)
	{
		CVector4<T> result = v;
		result.Normalized();
		return result;
	}

	template <class T>
	T CVector4<T>::Dot(const CVector4<T>& v1, const CVector4<T>& v2)
	{
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z + v1.w * v2.w;
	}

	template <class T>
	CVector4<T> CVector4<T>::Cross(const CVector4<T>& v1, const CVector4<T>& v2)
	{
		return CVector4<T>(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
	}

	template <class T>
	float CVector4<T>::Distance(CVector4<T> value1, CVector4<T> value2)
	{
		return sqrtf(DistanceSquared(value1, value2));
	}

	template <class T>
	float CVector4<T>::DistanceSquared(CVector4<T> value1, CVector4<T> value2)
	{
		CVector4<T> difference = value1 - value2;
		return Dot(difference, difference);
	}

	template <class T>
	CVector4<T> CVector4<T>::Clamp(CVector4<T> value1, CVector4<T> min, CVector4<T> max)
	{
		// This compare order is very important!!!
		// We must follow HLSL behavior in the case user specified min value is bigger than max value.

		float x = value1.x;
		x = (x > max.x) ? max.x : x;
		x = (x < min.x) ? min.x : x;

		float y = value1.y;
		y = (y > max.y) ? max.y : y;
		y = (y < min.y) ? min.y : y;

		float z = value1.z;
		z = (z > max.z) ? max.z : z;
		z = (z < min.z) ? min.z : z;

		float w = value1.w;
		w = (w > max.w) ? max.w : w;
		w = (w < min.w) ? min.w : w;

		return CVector4<T>(x, y, z, w);
	}

	template <class T>
	CVector4<T> CVector4<T>::Lerp(CVector4<T> value1, CVector4<T> value2, float amount)
	{
		return CVector4<T>(
			value1.x + (value2.x - value1.x) * amount,
			value1.y + (value2.y - value1.y) * amount,
			value1.z + (value2.z - value1.z) * amount,
			value1.w + (value2.w - value1.w) * amount);
	}

	template <class T>
	CVector4<T> CVector4<T>::Transform(CVector2<T> position, Matrix4 matrix)
	{
		return CVector4<T>(
			position.x * matrix.m11 + position.y * matrix.m21 + matrix.m41,
			position.x * matrix.m12 + position.y * matrix.m22 + matrix.m42,
			position.x * matrix.m13 + position.y * matrix.m23 + matrix.m43,
			position.x * matrix.m14 + position.y * matrix.m24 + matrix.m44);
	}

	template <class T>
	CVector4<T> CVector4<T>::Transform(CVector3<T> position, Matrix4 matrix)
	{
		return CVector4<T>(
			position.x * matrix.m11 + position.y * matrix.m21 + position.z * matrix.m31 + matrix.m41,
			position.x * matrix.m12 + position.y * matrix.m22 + position.z * matrix.m32 + matrix.m42,
			position.x * matrix.m13 + position.y * matrix.m23 + position.z * matrix.m33 + matrix.m43,
			position.x * matrix.m14 + position.y * matrix.m24 + position.z * matrix.m34 + matrix.m44);
	}

	template <class T>
	CVector4<T> CVector4<T>::Transform(CVector4<T> vector, Matrix4 matrix)
	{
		return CVector4<T>(
			vector.x * matrix.m11 + vector.y * matrix.m21 + vector.z * matrix.m31 + vector.w * matrix.m41,
			vector.x * matrix.m12 + vector.y * matrix.m22 + vector.z * matrix.m32 + vector.w * matrix.m42,
			vector.x * matrix.m13 + vector.y * matrix.m23 + vector.z * matrix.m33 + vector.w * matrix.m43,
			vector.x * matrix.m14 + vector.y * matrix.m24 + vector.z * matrix.m34 + vector.w * matrix.m44);
	}

	template <class T>
	CVector4<T> CVector4<T>::Transform(CVector2<T> value, Quaternion rotation)
	{
		float x2 = rotation.x + rotation.x;
		float y2 = rotation.y + rotation.y;
		float z2 = rotation.z + rotation.z;

		float wx2 = rotation.w * x2;
		float wy2 = rotation.w * y2;
		float wz2 = rotation.w * z2;
		float xx2 = rotation.x * x2;
		float xy2 = rotation.x * y2;
		float xz2 = rotation.x * z2;
		float yy2 = rotation.y * y2;
		float yz2 = rotation.y * z2;
		float zz2 = rotation.z * z2;

		return CVector4<T>(
			value.x * (1.0f - yy2 - zz2) + value.y * (xy2 - wz2),
			value.x * (xy2 + wz2) + value.y * (1.0f - xx2 - zz2),
			value.x * (xz2 - wy2) + value.y * (yz2 + wx2),
			1.0f);
	}

	template <class T>
	CVector4<T> CVector4<T>::Transform(CVector3<T> value, Quaternion rotation)
	{
		float x2 = rotation.x + rotation.x;
		float y2 = rotation.y + rotation.y;
		float z2 = rotation.z + rotation.z;

		float wx2 = rotation.w * x2;
		float wy2 = rotation.w * y2;
		float wz2 = rotation.w * z2;
		float xx2 = rotation.x * x2;
		float xy2 = rotation.x * y2;
		float xz2 = rotation.x * z2;
		float yy2 = rotation.y * y2;
		float yz2 = rotation.y * z2;
		float zz2 = rotation.z * z2;

		return CVector4<T>(
			value.x * (1.0f - yy2 - zz2) + value.y * (xy2 - wz2) + value.z * (xz2 + wy2),
			value.x * (xy2 + wz2) + value.y * (1.0f - xx2 - zz2) + value.z * (yz2 - wx2),
			value.x * (xz2 - wy2) + value.y * (yz2 + wx2) + value.z * (1.0f - xx2 - yy2),
			1.0f);
	}

	template <class T>
	CVector4<T> CVector4<T>::Transform(CVector4<T> value, Quaternion rotation)
	{
		float x2 = rotation.x + rotation.x;
		float y2 = rotation.y + rotation.y;
		float z2 = rotation.z + rotation.z;

		float wx2 = rotation.w * x2;
		float wy2 = rotation.w * y2;
		float wz2 = rotation.w * z2;
		float xx2 = rotation.x * x2;
		float xy2 = rotation.x * y2;
		float xz2 = rotation.x * z2;
		float yy2 = rotation.y * y2;
		float yz2 = rotation.y * z2;
		float zz2 = rotation.z * z2;

		return CVector4<T>(
			value.x * (1.0f - yy2 - zz2) + value.y * (xy2 - wz2) + value.z * (xz2 + wy2),
			value.x * (xy2 + wz2) + value.y * (1.0f - xx2 - zz2) + value.z * (yz2 - wx2),
			value.x * (xz2 - wy2) + value.y * (yz2 + wx2) + value.z * (1.0f - xx2 - yy2),
			value.w);
	}

	template <class T>
	CVector4<T> CVector4<T>::Add(CVector4<T> left, CVector4<T> right)
	{
		return left + right;
	}

	template <class T>
	CVector4<T> CVector4<T>::Subtract(CVector4<T> left, CVector4<T> right)
	{
		return left - right;
	}

	template <class T>
	CVector4<T> CVector4<T>::Multiply(CVector4<T> left, CVector4<T> right)
	{
		return left * right;
	}

	template <class T>
	CVector4<T> CVector4<T>::Multiply(CVector4<T> left, float right)
	{
		return left * CVector4<T>(right, right, right, right);
	}

	template <class T>
	CVector4<T> CVector4<T>::Multiply(float left, CVector4<T> right)
	{
		return CVector4<T>(left, left, left, left) * right;
	}

	template <class T>
	CVector4<T> CVector4<T>::Divide(CVector4<T> left, CVector4<T> right)
	{
		return left / right;
	}

	template <class T>
	CVector4<T> CVector4<T>::Divide(CVector4<T> left, float divisor)
	{
		return left / divisor;
	}

	template <class T>
	CVector4<T> CVector4<T>::Negate(CVector4<T> value)
	{
		return -value;
	}

	template <class T>
	CVector4<T> CVector4<T>::Min(const CVector4<T>& a, const CVector4<T>& b)
	{
		return { std::min(a.x, b.x), std::min(a.y, b.y), std::min(a.z, b.z), std::min(a.w, b.w) };
	}

	template <class T>
	CVector4<T> CVector4<T>::Max(const CVector4<T>& a, const CVector4<T>& b)
	{
		return { std::max(a.x, b.x), std::max(a.y, b.y), std::max(a.z, b.z), std::max(a.w, b.w) };
	}

	template <class T>
	CVector4<T> CVector4<T>::Abs(CVector4<T> v)
	{
		return CVector4<T>(std::fabsf(v.x), std::fabsf(v.y), std::fabsf(v.z), std::fabsf(v.w));
	}

	template <class T>
	CVector4<T> CVector4<T>::Abs() const
	{
		return CVector4<T>(std::fabsf(x), std::fabsf(y), std::fabsf(z), std::fabsf(w));
	}

	template <class T>
	CVector4<T> CVector4<T>::SquareRoot(CVector4<T>& v)
	{
		return CVector4<T>(std::sqrtf(v.x), std::sqrtf(v.y), std::sqrtf(v.z), std::sqrtf(v.w));
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
	CVector4<T> CVector4<T>::operator/(const CVector4<T>& v) const
	{
		return Divide(*this, v);
	}

	template <class T>
	CVector4<T> CVector4<T>::operator*(const CVector4<T>& v) const
	{
		return Multiply(*this, v);			
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
	std::istream& operator >>(std::istream& stream, CVector4<T>& vector)
	{
		return stream >> vector.x >> vector.y >> vector.z >> vector.w;
	}

	template <class T>
	std::ostream& operator <<(std::ostream& Stream, const CVector4<T>& Vector)
	{
		return Stream << Vector.x << " " << Vector.y << " " << Vector.z << " " << Vector.w;
	}
}
