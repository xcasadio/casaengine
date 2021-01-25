#ifndef CAPSULE_H
#define CAPSULE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "IShape.h"
#include "Parsers/Xml/tinyxml2.h"

namespace CasaEngine
{
	class CA_EXPORT Capsule :
		public IShape, public virtual AllocatedObject<Capsule>
	{
	public:
		Capsule();
		~Capsule();
	};
}

#endif // CAPSULE_H
