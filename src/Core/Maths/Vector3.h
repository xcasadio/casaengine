#ifndef VECTOR3_H
#define VECTOR3_H

#include "Math.h"

#include <cmath>
#include <algorithm>
#include <cmath>

#include "Maths/ValidNumber.h"
#include "Memory/MemoryAllocation.h"
#include "CA_Assert.h"
#include "Log/LogManager.h"

namespace CasaEngine
{
	template <class T>
	class CVector3 :
		public AllocatedObject<CVector3<T> >
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

		/*static void Transform(const CVector3<T> &position, const Matrix4 &matrix, CVector3<T> &result);
		static void Transform(const std::vector<CVector3<T> > &sourceArray, const Matrix4 &matrix, std::vector<CVector3<T> > &destinationArray);

		/// <summary>
		/// Transforms a vector by a quaternion rotation.
		/// </summary>
		/// <param name="vec">The vector to transform.</param>
		/// <param name="quat">The quaternion to rotate the vector by.</param>
		/// <param name="result">The result of the operation.</param>
		static void Transform(const CVector3<T> &value, const Quaternion &rotation, CVector3<T> &result);

		/// <summary>
		/// Transforms an array of vectors by a quaternion rotation.
		/// </summary>
		/// <param name="sourceArray">The vectors to transform</param>
		/// <param name="rotation">The quaternion to rotate the vector by.</param>
		/// <param name="destinationArray">The result of the operation.</param>
		static void Transform(const std::vector<CVector3<T> > &sourceArray, const Quaternion &rotation, std::vector<CVector3<T> > &destinationArray);

		static void TransformNormal(const CVector3<T> &normal, const Matrix4 &matrix, CVector3<T> &result);*/

		CVector3(T X = 0, T Y = 0, T Z = 0);
		void Set(T X, T Y, T Z);
		T getX() const;
		T getY() const;
		T getZ() const;

		bool IsZero() const;

		T Length() const;
		T LengthSquared() const;

		void Normalize();
		CVector3<T> GetNormalized();

		//! check for min bounds
		void CheckMin(const CVector3<T>& other);
		//! check for max bounds
		void CheckMax(const CVector3<T>& other);

		// returns a vector that consists of absolute values of this one's coordinates
		CVector3<T> Abs() const;

		bool IsValid() const;

		/**
		 * sets a vector orthogonal to the input vector
		 *
		 * Example:
		 *  Vec3 v;
		 *  v.SetOrthogonal( i );
		 */
		void SetOrthogonal(const CVector3<T>& v);
		CVector3<T> GetOrthogonal() const;

		CVector3<T> operator +() const;
		CVector3<T> operator -() const;

		//----------------------------------------------------------
		CVector3<T> operator +(const CVector3<T>& v) const;
		CVector3<T> operator -(const CVector3<T>& v) const;

		const CVector3<T>& operator +=(const CVector3<T>& v);
		const CVector3<T>& operator -=(const CVector3<T>& v);

		const CVector3<T>& operator *=(T t);
		const CVector3<T>& operator /=(T t);

		bool operator ==(const CVector3<T>& v) const;
		bool operator !=(const CVector3<T>& v) const;

		operator T* ();

		T& operator [] (int index) { CA_ASSERT(index >= 0 && index <= 2, "Vector3 operator[]"); return ((T*)this)[index]; }
		T operator [] (int index) const { CA_ASSERT(index >= 0 && index <= 2, "Vector3 operator[]"); return ((T*)this)[index]; }
	};

	//
	template <class T> CVector3<T>   operator * (const CVector3<T>& v, T t);
	template <class T> CVector3<T>   operator / (const CVector3<T>& v, T t);
	template <class T> CVector3<T>   operator * (T t, const CVector3<T>& v);
	template <class T> std::istream& operator >>(std::istream& Stream, CVector3<T>& Vector);
	template <class T> std::ostream& operator <<(std::ostream& Stream, const CVector3<T>& Vector);

	template <class T> bool IsEquivalent(const CVector3<T>& v0, const CVector3<T>& v1, float epsilon = Epsilon)
	{
		return  ((fabs(v0.x - v1.x) <= epsilon) && (fabs(v0.y - v1.y) <= epsilon) && (fabs(v0.z - v1.z) <= epsilon));
	}

	//
	typedef CVector3<int>   TVector3I;
	typedef CVector3<float> Vector3F;

	template <class T>
	CVector3<T> CVector3<T>::Zero()
	{
		return CVector3<T>();
	}

	template <class T>
	CVector3<T> CVector3<T>::One()
	{
		return CVector3<T>(1, 1, 1);
	}

	template <class T>
	CVector3<T> CVector3<T>::UnitX()
	{
		return CVector3<T>(1);
	}

	template <class T>
	CVector3<T> CVector3<T>::UnitY()
	{
		return CVector3<T>(0, 1);
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
	T CVector3<T>::getX() const
	{
		return x;
	}

	template <class T>
	T CVector3<T>::getY() const
	{
		return y;
	}

	template <class T>
	T CVector3<T>::getZ() const
	{
		return z;
	}

	//returns true if both x and y are zero
	template <class T>
	bool CVector3<T>::IsZero()const
	{
		return LengthSquared() < MinDouble;
	}

	template <class T>
	T CVector3<T>::Length() const
	{
		return std::sqrt(static_cast<float>(LengthSquared()));
	}

	template <class T>
	T CVector3<T>::LengthSquared() const
	{
		return x * x + y * y + z * z;
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
	CVector3<T> CVector3<T>::Abs() const
	{
		return CVector3<T>(fabsf(x), fabsf(y), fabsf(z));
	}

	template <class T>
	bool CVector3<T>::IsValid() const
	{
		if (!NumberValid(x)) return false;
		if (!NumberValid(y)) return false;
		if (!NumberValid(z)) return false;
		return true;
	}

	template<class F>
	F sqr(const F& op) { return op * op; }

	template <class T>
	void CVector3<T>::SetOrthogonal(const CVector3<T>& v)
	{
		sqr(T(0.9))* (v | v) - v.x * v.x < 0 ? (x = -v.z, y = 0, z = v.x) : (x = 0, y = v.z, z = -v.y);
	}

	template <class T>
	CVector3<T> CVector3<T>::GetOrthogonal() const
	{
		return sqr(T(0.9)) * (x * x + y * y + z * z) - x * x < 0 ? CVector3<T>(-z, 0, x) : CVector3<T>(0, z, -y);
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
		return CVector3<T>(x + v.x, y + v.y, z + v.z);
	}

	template <class T>
	CVector3<T> CVector3<T>::operator -(const CVector3<T>& v) const
	{
		return CVector3<T>(x - v.x, y - v.y, z - v.z);
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
		return ((std::abs(x - v.x) <= std::numeric_limits<T>::epsilon()) &&
			(std::abs(y - v.y) <= std::numeric_limits<T>::epsilon()) &&
			(std::abs(z - v.z) <= std::numeric_limits<T>::epsilon()));
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

	template <class T>
	std::istream& operator >>(std::istream& Stream, CVector3<T>& Vector)
	{
		return Stream >> Vector.x >> Vector.y >> Vector.z;
	}

	template <class T>
	std::ostream& operator <<(std::ostream& Stream, const CVector3<T>& Vector)
	{
		return Stream << Vector.x << " " << Vector.y << " " << Vector.z;
	}
}

#endif
