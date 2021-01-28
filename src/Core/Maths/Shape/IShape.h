#ifndef ISHAPE_H
#define ISHAPE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "ShapeType.h"

#include "Memory/MemoryAllocation.h"

#include <cereal/access.hpp>
#include <cereal/types/polymorphic.hpp>

namespace CasaEngine
{
	class CA_EXPORT IShape :
		public AllocatedObject<IShape>
	{
	public:
		virtual ~IShape();
		ShapeType Type() const;

		virtual IShape* Copy() = 0;

	protected:
		//IShape(const IShape& rsh);
		IShape& operator=(const IShape& rsh);
		IShape(ShapeType type_);

	private:
		ShapeType m_ShapeType;

	private:
		friend class cereal::access;

		template <class Archive>
		void load(Archive& ar)
		{
			ar(cereal::make_nvp("shape_type", m_ShapeType));
		}

		template <class Archive>
		void save(Archive& ar) const
		{
			ar(cereal::make_nvp("shape_type", m_ShapeType));
		}
	};
}

#endif
