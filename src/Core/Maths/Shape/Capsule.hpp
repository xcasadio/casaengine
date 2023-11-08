#ifndef CAPSULE_H
#define CAPSULE_H

#include "CA_Export.hpp"
#include  "Maths/Matrix4.hpp"

#include  "IShape.hpp"

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
