#ifndef CAPSULE_H
#define CAPSULE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "IShape.h"
#include "Parsers/Xml/tinyxml2.h"


namespace CasaEngine
{
    /**
     * 
     */
	class CA_EXPORT Capsule :
		public IShape
    {
    public :
		/**
		 *
		 */
        Capsule();
		
		/**
		 *
		 */
		~Capsule();

		void Read( const tinyxml2::XMLElement& node_ ) override;
		void Read( std::ifstream& in ) override;
		void Write( const tinyxml2::XMLElement& node_ ) override;
		void Write( std::ostream& os ) override;
    };
}


#endif // CAPSULE_H
