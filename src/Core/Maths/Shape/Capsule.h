#ifndef CAPSULE_H
#define CAPSULE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "IShape.h"
#include "Parsers/Xml/tinyxml2.h"
#include "CompilationMacro.h"

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

		void Read( const tinyxml2::XMLElement& node_ ) OVERRIDE;
		void Read( std::ifstream& in ) OVERRIDE;
		void Write( const tinyxml2::XMLElement& node_ ) OVERRIDE;
		void Write( std::ostream& os ) OVERRIDE;
    };
} // namespace CasaEngine


#endif // CAPSULE_H
