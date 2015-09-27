#ifndef BOX_H
#define BOX_H

#include "CA_Export.h"
#include "CompilationMacro.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "IShape.h"

#include "Memory/MemoryAllocation.h"
#include "Parsers/Xml/tinyxml2.h"
#include <iosfwd>
#include "CompilationMacro.h"


namespace CasaEngine
{
    /**
     * 
     */
	class CA_EXPORT Box :
		public IShape
    {
    public :
		/**
		 *
		 */
        Box(Vector3F size_ = Vector3F::One(), Vector3F center_ = Vector3F::Zero());

		/**
		 *
		 */
        ~Box();

		/**
		 * 
		 */
		Vector3F Size() const;

		/**
		 * 
		 */
		void Size(Vector3F val);

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
		
	protected:


	private:
		Vector3F m_Center, m_Size;
	};
} // namespace CasaEngine


#endif // BOX_H
