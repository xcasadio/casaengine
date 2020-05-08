#ifndef SPHERE_H
#define SPHERE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "IShape.h"


namespace CasaEngine
{
    /**
     * 
     */
	class CA_EXPORT Sphere :
		public IShape
    {
    public :
		/**
		 *
		 */
		Sphere(Vector3F center_, float radius_);

		/**
		 *
		 */
		~Sphere();

		void Read( const tinyxml2::XMLElement& node_ ) override;
		void Read( std::ifstream& in ) override;
		void Write( const tinyxml2::XMLElement& node_ ) override;
		void Write( std::ostream& os ) override;
		
	private:
		Vector3F m_Center;
		float m_Radius;
    };
}


#endif // SPHERE_H
