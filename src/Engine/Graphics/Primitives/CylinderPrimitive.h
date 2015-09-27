
#ifndef CYLINDERPRIMITIVE_H
#define CYLINDERPRIMITIVE_H

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
    class CA_EXPORT CylinderPrimitive : public IPrimitive3D
    {
    public :
		CylinderPrimitive(float diameter_ = 1.0f, float height_ = 1.0f, unsigned int tessellation_= 32);
        virtual ~CylinderPrimitive();
		
	private:
		float m_Diameter;
		float m_Height;
		unsigned int m_Tessellation;
    };

} // namespace CasaEngine

#endif // CYLINDERPRIMITIVE_H
