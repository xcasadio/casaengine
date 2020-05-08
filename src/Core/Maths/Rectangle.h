#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "CA_Export.h"
#include "Maths/Vector2.h"
#include "Memory/MemoryAllocation.h"

#include <algorithm>
#include <iostream>

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
		public AllocatedObject<CRectangle<T>>
    {
    public :
    public:
        CRectangle() = default;
        CRectangle(T Left, T Top, T Width, T Height);

        void Set(T Left, T Top, T Width, T Height);

        T Left() const;

        T Right() const;

        T Top() const;

        T Bottom() const;

        CVector2<T> Size() const;

        TIntersection Intersects(const CVector2<T> & Point) const;
        TIntersection Intersects(const CRectangle<T> & Rect) const;

        bool operator ==(const CRectangle<T> & Rect) const;
        bool operator !=(const CRectangle<T> & Rect) const;

        T x, y, w, h;
    };

    template <class T> std::istream& operator >>(std::ostream& Stream, CRectangle<T>& Rect);
    template <class T> std::ostream& operator <<(std::ostream& Stream, const CRectangle<T>& Rect);

    typedef CRectangle<int> CRectangleI;
    typedef CRectangle<float> CRectangleF;

#include "Rectangle.inl"

}


#endif // RECTANGLE_H
