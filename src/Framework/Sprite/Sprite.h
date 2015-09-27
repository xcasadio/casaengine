
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "CA_Export.h"
#include "Graphics/Textures/Texture.h"
#include "Maths/Rectangle.h"
#include "Maths/Vector2.h"

#include <string>
#include "Assets/Assetable.h"
#include "Parsers/Xml/tinyxml2.h"
#include <iosfwd>
#include "Maths/Shape/IShape.h"

namespace CasaEngine
{
	/////////////////////////////////////////////////////////////
	/// Sprite
	/////////////////////////////////////////////////////////////
	class CA_EXPORT Sprite : 
		public IAssetable
	{
	public:
		Sprite();
		~Sprite();

		//std::string GetName() const;
		Texture* GetTexture2D() const;
		CRectangle GetPositionInTexture() const;	
		Vector2I GetOrigin() const;
		std::string GetAssetFileName() const;
		void Clear();

		std::vector<IShape *>::iterator GetCollisionShapeIterator();
		std::vector<IShape *>::iterator GetCollisionShapeIteratorEnd();

		virtual void Read( const tinyxml2::XMLElement& node_ );
		virtual void Read( std::ifstream& in );
		virtual void Write( const tinyxml2::XMLElement& node_ );
		virtual void Write( std::ostream& os );

//#if EDITOR
		//void SetName(std::string val);
		void SetTexture2D(Texture *val);
		void SetPositionInTexture(CRectangle val);
		void SetOrigin(Vector2I val);
		void SetAssetFileName(std::string val);
//#endif // EDITOR

	private:
		//ID
		//std::string m_Name;
		//constant
		Texture* m_pTexture2D;		
		CRectangle m_PositionInTexture;		
		Vector2I m_Origin;		
		std::vector<IShape *> m_CollisionShapes;
		//std::vector<Vector2I> m_Sockets;
		std::string m_AssetFileName;
	};
} // namespace CasaEngine

#endif // _SPRITE_H_
