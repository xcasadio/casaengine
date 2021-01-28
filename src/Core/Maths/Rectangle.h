#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "CA_Export.h"
#include "Maths/Vector2.h"
#include "Memory/MemoryAllocation.h"
#include "Maths/Shape/IShape.h"

#include <algorithm>
#include <iostream>

#include <cereal/access.hpp>

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
		public IShape/*, public virtual AllocatedObject<CRectangle<T>>*/
	{
	public:
		CRectangle();
		CRectangle(const CRectangle<T>& rsh);
		CRectangle<T>& operator=(const CRectangle<T>& rsh);
		CRectangle(T Left, T Top, T Width, T Height);

		void Set(T Left, T Top, T Width, T Height);

		T Left() const;
		T Right() const;
		T Top() const;
		T Bottom() const;
		CVector2<T> Size() const;

		virtual IShape* Copy() override;

		TIntersection Intersects(const CVector2<T>& Point) const;
		TIntersection Intersects(const CRectangle<T>& Rect) const;

		bool operator ==(const CRectangle<T>& Rect) const;
		bool operator !=(const CRectangle<T>& Rect) const;

		T x, y, w, h;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("shape", cereal::base_class<IShape>(this)));
			ar(cereal::make_nvp("x", x));
			ar(cereal::make_nvp("y", y));
			ar(cereal::make_nvp("w", w));
			ar(cereal::make_nvp("h", h));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("shape", cereal::base_class<IShape>(this)));
			ar(cereal::make_nvp("x", x));
			ar(cereal::make_nvp("y", y));
			ar(cereal::make_nvp("w", w));
			ar(cereal::make_nvp("h", h));
		}
	};

	template <class T> std::istream& operator >>(std::ostream& Stream, CRectangle<T>& Rect);
	template <class T> std::ostream& operator <<(std::ostream& Stream, const CRectangle<T>& Rect);

	typedef CRectangle<int> RectangleI;
	typedef CRectangle<float> RectangleF;

#include "Rectangle.inl"
}
/*
#include <cereal/types/polymorphic.hpp>

CEREAL_REGISTER_TYPE_WITH_NAME(CasaEngine::RectangleI, "rectangleI");
CEREAL_REGISTER_TYPE_WITH_NAME(CasaEngine::RectangleF, "rectangleF");

CEREAL_REGISTER_POLYMORPHIC_RELATION(CasaEngine::IShape, CasaEngine::RectangleI);
CEREAL_REGISTER_POLYMORPHIC_RELATION(CasaEngine::IShape, CasaEngine::RectangleF);
*/
#endif // RECTANGLE_H
