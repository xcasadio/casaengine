
#ifndef BOXPRIMITIVE_H
#define BOXPRIMITIVE_H


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
    class CA_EXPORT BoxPrimitive : public IPrimitive3D
    {
    public :
		BoxPrimitive(float width_ = 1.0f, float height_ = 1.0f, float length_= 1.0f);
        virtual ~BoxPrimitive();		

	private:
		void AddIndex(bool dir_);
		
	private:
		float m_Width;
		float m_Height;
		float m_Length;
    };

} // namespace CasaEngine

#endif // BOXPRIMITIVE_H
