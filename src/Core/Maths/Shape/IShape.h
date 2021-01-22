#ifndef ISHAPE_H
#define ISHAPE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "ShapeType.h"

#include "Memory/MemoryAllocation.h"
#include "Parsers/Xml/tinyxml2.h"

namespace CasaEngine
{
	class CA_EXPORT IShape :
		public AllocatedObject<IShape>
    {
    public :
        virtual ~IShape();
		ShapeType Type() const;

	protected:
        IShape(ShapeType type_);

	private:
		ShapeType m_ShapeType;
    };
}

#endif
