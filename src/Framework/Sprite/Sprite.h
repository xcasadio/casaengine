#ifndef _SPRITE_H_
#define _SPRITE_H_

#include "CA_Export.h"
#include "Graphics/Textures/Texture.h"
#include "Maths/Rectangle.h"
#include "Maths/Vector2.h"

#include <string>
#include "Maths/Shape/IShape.h"
#include <Datas/SpriteData.h>

namespace CasaEngine
{
	class CA_EXPORT Sprite
	{
	private:
		static std::map<std::string, Texture*> _textureCache;

	public:
		static Sprite* CreateFromSpriteData(SpriteData& spriteData);

	public:
		Sprite();
		~Sprite();

		Texture* GetTexture2D() const;
		RectangleI GetPositionInTexture() const;
		Vector2I GetOrigin() const;
		void Clear();

		std::vector<IShape*>::iterator GetCollisionShapeIterator();
		std::vector<IShape*>::iterator GetCollisionShapeIteratorEnd();

		//#if EDITOR
		void SetTexture2D(Texture* val);
		void SetPositionInTexture(RectangleI val);
		void SetOrigin(Vector2I val);
		//#endif // EDITOR

	private:
		Texture* m_pTexture2D;
		RectangleI m_PositionInTexture;
		Vector2I m_Origin;
		std::vector<IShape*> m_CollisionShapes;
		//std::vector<Vector2I> m_Sockets;
	};
}

#endif
