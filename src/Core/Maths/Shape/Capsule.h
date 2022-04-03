#ifndef CAPSULE_H
#define CAPSULE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"

#include "IShape.h"

namespace CasaEngine
{
	class CA_EXPORT Capsule :
		public IShape
	{
	public:
		Capsule();
	};
}

#endif
