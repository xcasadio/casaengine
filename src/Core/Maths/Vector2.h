#ifndef VECTOR2_H
#define VECTOR2_H

#include <iostream>
#include <cereal/access.hpp>
#include "Math.h"

namespace CasaEngine
{
	template <class T>
	class CVector2
	{
	public:
		static CVector2<T> Zero();
		static CVector2<T> One();
		static CVector2<T> UnitX();
		static CVector2<T> UnitY();

		CVector2(T X = 0, T Y = 0);

		void Set(T X, T Y);
		T getX() const;
		T getY() const;

		bool IsZero() const;
		T Length() const;
		T LengthSquared() const;
		void Normalize();
		
		float Dot(const CVector2<T>& v2)const;

		/*
		 * returns positive if v2 is clockwise of this vector,
		 * negative if anticlockwise (assuming the Y axis is pointing down,
		 * X axis to right like a Window app)
		 */
		enum { clockwise = 1, anticlockwise = -1 };

		int       Sign(const CVector2<T>& v2)const;

		/*
		 * returns the vector that is perpendicular to this one.
		 */
		CVector2<T>  GetOrthogonal() const;

		/*
		 * adjusts x and y so that the length of the vector does not exceed max
		 */
		void      Truncate(float max);

		/*
		 * returns the distance between this vector and th one passed as a parameter
		 */
		float    Distance(const CVector2<T>& v2)const;

		/*
		 * squared version of above.
		 */
		float    DistanceSq(const CVector2<T>& v2)const;

		/*
		 * given a normalized vector this method reflects the vector it
		 * is operating upon. (like the path of a ball bouncing off a wall)
		 */
		void      Reflect(const CVector2<T>& norm);

		/*
		 * returns the vector that is the reverse of this vector
		 */
		CVector2<T>  GetReverse()const;

		CVector2<T> operator +() const;
		CVector2<T> operator -() const;

		CVector2<T> operator +(const CVector2<T>& v) const;
		CVector2<T> operator -(const CVector2<T>& v) const;

		const CVector2<T>& operator +=(const CVector2<T>& v);
		const CVector2<T>& operator -=(const CVector2<T>& v);

		CVector2<T> operator *(T t) const;
		CVector2<T> operator /(T t) const;

		const CVector2<T>& operator *=(T t);
		const CVector2<T>& operator /=(T t);

		bool operator ==(const CVector2<T>& v) const;
		bool operator !=(const CVector2<T>& v) const;

		operator T* ();

		T x, y;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("x", x));
			ar(cereal::make_nvp("y", y));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("x", x));
			ar(cereal::make_nvp("y", y));
		}
	};

	template <class T> CVector2<T>   operator * (const CVector2<T>& v, T t);
	template <class T> CVector2<T>   operator / (const CVector2<T>& v, T t);
	template <class T> CVector2<T>   operator * (T t, const CVector2<T>& v);
	template <class T> T             VectorDot(const CVector2<T>& v1, const CVector2<T>& v2);
	template <class T> CVector2<T>   VectorCross(const CVector2<T>& v1, const CVector2<T>& v2);
	template <class T> std::istream& operator >>(std::istream& Stream, CVector2<T>& Vector);
	template <class T> std::ostream& operator <<(std::ostream& Stream, const CVector2<T>& Vector);

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
	float CVector2<T>::DistanceSq(const CVector2<T>& v2) const
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

	//  given a normalized vector this method reflects the vector it
	//  is operating upon. (like the path of a ball bouncing off a wall)
	template <class T>
	void CVector2<T>::Reflect(const CVector2<T>& norm)
	{
		CVector2<T> res = norm.GetReverse() * (2.0f * Dot(norm));
		x += res.x;
		y += res.y;
	}

	//  returns the vector that is the reverse of this vector
	template <class T>
	CVector2<T> CVector2<T>::GetReverse() const
	{
		return CVector2<T>(-this->x, -this->y);
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

	template <class T>
	std::istream& operator >>(std::istream& Stream, CVector2<T>& Vector)
	{
		return Stream >> Vector.x >> Vector.y;
	}

	template <class T>
	std::ostream& operator <<(std::ostream& Stream, const CVector2<T>& Vector)
	{
		return Stream << Vector.x << " " << Vector.y;
	}
}

#endif
