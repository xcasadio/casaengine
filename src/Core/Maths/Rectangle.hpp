#pragma once

#include "CA_Export.hpp"
#include "Maths/Vector2.hpp"
#include "Maths/Shape/IShape.hpp"

namespace CasaEngine
{
	using TIntersection = enum
	{
		INT_IN,        // totally inside
		INT_OUT,       // totally outside
		INT_INTERSECTS // intersection
	};

	template<class T>
	class CA_EXPORT CRectangle :
		public IShape
	{
	public:
		CRectangle();
		~CRectangle() override = default;
		CRectangle(const CRectangle<T>& rsh);
		CRectangle<T>& operator=(const CRectangle<T>& rsh);
		CRectangle(CRectangle<T>&& rsh) = default;
		CRectangle<T>& operator=(CRectangle<T>&& rsh) = default;

		CRectangle(T Left, T Top, T Width, T Height);

		void Set(T Left, T Top, T Width, T Height);

		T Left() const;
		T Right() const;
		T Top() const;
		T Bottom() const;
		CVector2<T> Size() const;
		CVector2<T> Center() const;

		IShape* Copy() override;

		TIntersection Intersects(const CVector2<T>& Point) const;
		TIntersection Intersects(const CRectangle<T>& Rect) const;

		bool operator ==(const CRectangle<T>& Rect) const;
		bool operator !=(const CRectangle<T>& Rect) const;

		bool operator==(const IShape& rsh) const override;

		T x, y, w, h;
	};

	//typedef CRectangle<int> Rectangle;
	typedef CRectangle<float> Rectangle;

	template <class T>
	CRectangle<T>::CRectangle() : IShape(ShapeType::RECTANGLE),
		x(0), y(0), w(0), h(0)
	{
	}

	template <class T>
	CRectangle<T>::CRectangle(const CRectangle<T>& rsh) : IShape(ShapeType::RECTANGLE)
	{
		*this = rsh;
	}

	template <class T>
	CRectangle<T>& CRectangle<T>::operator=(const CRectangle<T>& rsh)
	{
		x = rsh.x;
		y = rsh.y;
		w = rsh.w;
		h = rsh.h;
		IShape::operator=(rsh);

		return *this;
	}

	template <class T>
	CRectangle<T>::CRectangle(T Left, T Top, T Width, T Height) : CRectangle()
	{
		Set(Left, Top, Width, Height);
	}

	template <class T>
	IShape* CRectangle<T>::Copy()
	{
		return new CRectangle<T>(*this);
	}

	template <class T>
	void CRectangle<T>::Set(T Left, T Top, T Width, T Height)
	{
		x = Left;
		y = Top;
		w = Width;
		h = Height;
	}

	template <class T>
	T CRectangle<T>::Left() const
	{
		return x;
	}

	template <class T>
	T CRectangle<T>::Right() const
	{
		return x + w;
	}

	template <class T>
	T CRectangle<T>::Top() const
	{
		return y;
	}

	template <class T>
	T CRectangle<T>::Bottom() const
	{
		return y + h;
	}

	template <class T>
	CVector2<T> CRectangle<T>::Size() const
	{
		return CVector2<T>(w, h);
	}

	template <class T>
	CVector2<T> CRectangle<T>::Center() const
	{
		return CVector2<T>(x + w / 2, y + h / 2);
	}

	template <class T>
	TIntersection CRectangle<T>::Intersects(const CVector2<T>& Point) const
	{
		if (Point.x >= x && Point.y >= y && Point.x <= Right() && Point.y <= Bottom())
		{
			return INT_IN;
		}
		return INT_OUT;
	}

	template <class T>
	TIntersection CRectangle<T>::Intersects(const CRectangle<T>& Rect) const
	{
		T x1 = x > Rect.x ? x : Rect.x;
		T y1 = y > Rect.y ? y : Rect.y;
		T x2 = Right() > Rect.Right() ? Rect.Right() : Right();
		T y2 = Bottom() > Rect.Bottom() ? Rect.Bottom() : Bottom();
		CRectangle<T> Overlap(x1, y1, x1 - x2, y1 - y2);

		if (x1 > x2 || y1 > y2)
		{
			return INT_OUT;
		}
		if (Overlap == *this || Overlap == Rect)
		{
			return INT_IN;
		}
		return INT_INTERSECTS;
	}

	template <class T>
	bool CRectangle<T>::operator ==(const CRectangle<T>& Rect) const
	{
		return x == Rect.x && y == Rect.y && w == Rect.w && h == Rect.h;
	}

	template <class T>
	bool CRectangle<T>::operator !=(const CRectangle<T>& Rect) const
	{
		return !(*this == Rect);
	}

	template <class T>
	bool CRectangle<T>::operator==(const IShape& rsh) const
	{
		if (rsh.Type() != Type())
		{
			return false;
		}

		return *this == dynamic_cast<const Rectangle&>(rsh);
	}
}
