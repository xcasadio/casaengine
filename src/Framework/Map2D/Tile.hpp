#pragma once

#include <GameTime.hpp>

#include  "Datas/TileSetData.hpp"
#include  "Maths/Rectangle.hpp"
#include  "Sprite/SpriteRenderer.hpp"

namespace CasaEngine
{
	class CA_EXPORT ITile
	{
	public:
		virtual void Initialize();
		virtual void Update(const GameTime& gameTime_) = 0;
		virtual void Draw(float x, float y, float z) = 0;
		virtual void Draw(float x, float y, float z, const Rectangle& uvOffset) = 0;

		virtual TileData* GetTileData() = 0;

	protected:
		ITile();
		virtual ~ITile() = default;
		void Draw(const Sprite* sprite, float x, float y, float z, const Rectangle& uvOffset) const;

	private:
		SpriteRenderer* _spriteRenderer = nullptr;
	};
}