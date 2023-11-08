#pragma once

#include "CA_Export.hpp"
#include "ShapeType.hpp"

namespace CasaEngine
{
	class CA_EXPORT IShape
	{
	public:
		virtual ~IShape();
		ShapeType Type() const;

		virtual IShape* Copy() = 0;
		virtual bool operator ==(const IShape& rsh) const = 0;

	protected:
		//IShape(const IShape& rsh);
		IShape& operator=(const IShape& rsh);
		IShape(ShapeType type_);

	private:
		ShapeType m_ShapeType;
	};
}
