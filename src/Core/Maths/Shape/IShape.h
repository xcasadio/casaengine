#pragma once

#include "CA_Export.h"
#include "ShapeType.h"

namespace CasaEngine
{
	class CA_EXPORT IShape
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
	};
}
