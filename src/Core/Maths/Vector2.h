#ifndef VECTOR2_H
#define VECTOR2_H

#include "Math.h"

#include <limits>
#include <iostream>
#include <cmath>

#include "Memory/MemoryAllocation.h"

#include <cereal/access.hpp>

namespace CasaEngine
{
    template <class T>
    class CVector2 :
		public AllocatedObject<CVector2<T> >
    {
    public :
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

		/*
		 * calculates the dot product
		 */
		float    Dot(const CVector2<T>& v2)const;

		/*
		 * returns positive if v2 is clockwise of this vector,
		 * negative if anticlockwise (assuming the Y axis is pointing down,
		 * X axis to right like a Window app)
		 */
		enum {clockwise = 1, anticlockwise = -1};

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
		float    Distance(const CVector2<T> &v2)const;

		/*
		 * squared version of above.
		 */
		float    DistanceSq(const CVector2<T> &v2)const;

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

        operator T*();

        T x, y;

    private:
        friend class cereal::access;

        template <class Archive>
        void load(Archive& ar)
        {
            ar(x, y);
        }

        template <class Archive>
        void save(Archive& ar) const
        {
            ar(x, y);
        }
    };

    template <class T> CVector2<T>   operator * (const CVector2<T>& v, T t);
    template <class T> CVector2<T>   operator / (const CVector2<T>& v, T t);
    template <class T> CVector2<T>   operator * (T t, const CVector2<T>& v);
    template <class T> T             VectorDot  (const CVector2<T>& v1, const CVector2<T>& v2);
    template <class T> CVector2<T>   VectorCross(const CVector2<T>& v1, const CVector2<T>& v2);
    template <class T> std::istream& operator >>(std::istream& Stream, CVector2<T>& Vector);
    template <class T> std::ostream& operator <<(std::ostream& Stream, const CVector2<T>& Vector);
	
    typedef CVector2<int>   Vector2I;
    typedef CVector2<float> Vector2F;

    #include "Vector2.inl"

}

#endif
