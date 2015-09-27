#ifndef POLYGON_H
#define POLYGON_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"

#include "IShape.h"
#include "Maths/Vector2.h"
#include "CompilationMacro.h"

namespace CasaEngine
{
    /**
     * 
     */
	class CA_EXPORT Polygon :
		public IShape
    {
    public :
		/**
		 *
		 */
        Polygon();

		/**
		 *
		 */
		~Polygon();

		void Read( const tinyxml2::XMLElement& node_ ) OVERRIDE;
		void Read( std::ifstream& in ) OVERRIDE;
		void Write( const tinyxml2::XMLElement& node_ ) OVERRIDE;
		void Write( std::ostream& os ) OVERRIDE;
		
	protected:
		

	private:
		std::vector<Vector2F> m_PointList;
    };
} // namespace CasaEngine


#endif // POLYGON_H
