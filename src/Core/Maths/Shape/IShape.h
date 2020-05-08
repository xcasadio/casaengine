#ifndef ISHAPE_H
#define ISHAPE_H

#include "CA_Export.h"
#include "Maths/Matrix4.h"
#include "Maths/Vector3.h"
#include "ShapeType.h"

#include "Memory/MemoryAllocation.h"
#include "Parsers/Xml/tinyxml2.h"


namespace CasaEngine
{
    /**
     * 
     */
	class CA_EXPORT IShape :
		public AllocatedObject<IShape>
    {
    public :
		/**
		 *
		 */
        virtual ~IShape();
		

		ShapeType Type() const;

		virtual void Read( const tinyxml2::XMLElement& node_ );
		virtual void Read( std::ifstream& in );
		virtual void Write( const tinyxml2::XMLElement& node_ );
		virtual void Write( std::ostream& os );


		static IShape *LoadShape(const tinyxml2::XMLElement& pElem);

	protected:
		/**
		 *
		 */
        IShape(ShapeType type_);

	private:
		ShapeType m_ShapeType;
    };
}


#endif // ISHAPE_H
