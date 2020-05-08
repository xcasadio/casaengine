
#ifndef TORUSPRIMITIVE_H
#define TORUSPRIMITIVE_H

#include <sstream>
#include <string>
#include <vector>

#include "CA_Export.h"

#include "Graphics/Mesh/Mesh.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"
#include "Primitive3D.h"


namespace CasaEngine
{
    /**
     *
     */
    class CA_EXPORT TorusPrimitive : public IPrimitive3D
    {
    public :
		TorusPrimitive(float diameter_ = 1.0f, float thickness_ = 0.333f, unsigned int tessellation_ = 32);
        virtual ~TorusPrimitive();		

	private:
		float m_Diameter;
		float m_Thickness;
		unsigned int m_Tessellation;
    };

}

#endif // TORUSPRIMITIVE_H
