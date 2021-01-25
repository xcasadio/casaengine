#ifndef VECTOR3_H
#define VECTOR3_H

#include "Math.h"

#include <limits>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

#include "Memory/MemoryAllocation.h"
#include <math.h>
#include "ValidNumber.h"
#include "CA_Assert.h"
#include "Log/LogManager.h"

namespace CasaEngine
{
	/*class Matrix4;
	class Quaternion;*/

	/**
	 *
	 */
	template <class T>
	class CVector3 :
		public AllocatedObject<CVector3<T> >
	{
	public:
		T x, y, z;

		/**
		 *
		 */
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

		/**
		 *
		 */
		CVector3(T X = 0, T Y = 0, T Z = 0);

		/**
		 *
		 */
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
		inline void CheckMin(const CVector3<T>& other);
		//! check for max bounds
		inline void CheckMax(const CVector3<T>& other);

		// returns a vector that consists of absolute values of this one's coordinates
		inline CVector3<T> Abs() const;

		inline bool IsValid() const;

		/**
		 * sets a vector orthogonal to the input vector
		 *
		 * Example:
		 *  Vec3 v;
		 *  v.SetOrthogonal( i );
		 */
		inline void SetOrthogonal(const CVector3<T>& v);
		inline CVector3<T> GetOrthogonal() const;

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

		inline T& operator [] (int index) { CA_ASSERT(index >= 0 && index <= 2, "Vector3 operator[]"); return ((T*)this)[index]; }
		inline T operator [] (int index) const { CA_ASSERT(index >= 0 && index <= 2, "Vector3 operator[]"); return ((T*)this)[index]; }
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

#include "Vector3.inl"
}

#endif // VECTOR3_H
