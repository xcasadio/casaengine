#ifndef BOX2D_H
#define BOX2D_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "Maths/Vector2.h"

#include "IShape.h"
#include "Parsers/Xml/tinyxml2.h"
#include "CompilationMacro.h"

namespace CasaEngine
{
    /**
     * 
     */
	class CA_EXPORT Box2D :
		public IShape
    {
    public :
		/**
		 *
		 */
        Box2D(Vector2F size_ = Vector2F::One(), Vector3F center_ = Vector3F::Zero());

		/**
		 *
		 */
        ~Box2D();

		/**
		 * 
		 */
		Vector2F Size() const;

		/**
		 * 
		 */
		void Size(Vector2F val);

		/**
		 * 
		 */
		Vector3F Center() const;

		/**
		 * 
		 */
		void Center(Vector3F val);

		void Read( const tinyxml2::XMLElement& node_ ) OVERRIDE;
		void Read( std::ifstream& in ) OVERRIDE;
		void Write( const tinyxml2::XMLElement& node_ ) OVERRIDE;
		void Write( std::ostream& os ) OVERRIDE;

	private:
		Vector3F m_Center;
		Vector2F m_Size;
		
    };
} // namespace CasaEngine


#endif // BOX2D_H
