#ifndef SHAPETYPE_H
#define SHAPETYPE_H

#include "CA_Export.h"

#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
    /**
     * 
     */
	enum ShapeType
	{
		//3D
		BOX,
		SPHERE,
		CAPSULE,
		//2D
		BOX2D,
		CIRCLE2D,
		POLYGON,
	};
	
} // namespace CasaEngine


#endif // SHAPETYPE_H
