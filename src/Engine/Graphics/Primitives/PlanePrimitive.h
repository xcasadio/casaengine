
#ifndef PLANEPRIMITIVE_H
#define PLANEPRIMITIVE_H

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
    class CA_EXPORT PlanePrimitive : public IPrimitive3D
    {
    public :
		PlanePrimitive(float width_ = 1.0f, float height_ = 1.0f);
        virtual ~PlanePrimitive();
		
	private:
		float m_Width;
		float m_Height;
    };

} // namespace CasaEngine

#endif // PLANEPRIMITIVE_H
