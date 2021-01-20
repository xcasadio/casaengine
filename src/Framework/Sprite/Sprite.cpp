#include "Base.h"

#include "Sprite/Sprite.h"
#include <iosfwd>

#include "Game/Game.h"
#include "Maths/Vector2.h"
#include "Maths/Rectangle.h"
#include "Graphics/Textures/Texture.h"
#include "Resources/ResourceManager.h"


namespace CasaEngine
{
	std::map<std::string, Texture*> Sprite::_textureCache;

	Sprite* Sprite::CreateFromSpriteData(SpriteData& spriteData)
	{
		auto pSprite = new Sprite();
		Texture* texture;
		auto pair = _textureCache.find(static_cast<std::string>(spriteData.GetAssetFileName()));

		if (pair != _textureCache.end())
		{
			texture = pair->second;
		}
		else
		{
			auto textureFile = Game::Instance().GetMediaManager().FindMedia(spriteData.GetAssetFileName().c_str(), true);
			texture = Texture::loadTexture(textureFile);
			_textureCache.insert(std::make_pair(spriteData.GetAssetFileName(), texture));
		}

		pSprite->SetTexture2D(texture);
		pSprite->SetPositionInTexture(spriteData.GetPositionInTexture());
		pSprite->SetOrigin(spriteData.GetOrigin());

		return pSprite;
	}


	Sprite::Sprite() :
		m_pTexture2D(nullptr)
	{

	}

	Sprite::~Sprite()
	{
		Clear();
	}

	Texture* Sprite::GetTexture2D() const
	{
		return m_pTexture2D;
	}

	RectangleI Sprite::GetPositionInTexture() const
	{
		return m_PositionInTexture;
	}

	Vector2I Sprite::GetOrigin() const
	{
		return m_Origin;
	}

	void Sprite::Clear()
	{
		for (std::vector<IShape*>::iterator it = m_CollisionShapes.begin();
			it != m_CollisionShapes.end();
			it++)
		{
			DELETE_AO* it;
		}

		m_CollisionShapes.clear();
	}

//#ifdef EDITOR

	void Sprite::SetTexture2D(Texture* val)
	{
		m_pTexture2D = val;
	}

	void Sprite::SetPositionInTexture(RectangleI val)
	{
		m_PositionInTexture = val;
	}

	void Sprite::SetOrigin(Vector2I val)
	{
		m_Origin = val;
	}

	std::vector<IShape*>::iterator Sprite::GetCollisionShapeIterator()
	{
		return m_CollisionShapes.begin();
	}

	std::vector<IShape*>::iterator Sprite::GetCollisionShapeIteratorEnd()
	{
		return m_CollisionShapes.end();
	}

//#endif

}
