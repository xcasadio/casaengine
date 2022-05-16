#pragma once

#include "Tile.h"
#include "Sprite/Sprite.h"

namespace CasaEngine
{
	class CA_EXPORT StaticTile : public ITile
	{
	public:
		explicit StaticTile(Sprite* pSprite);
		~StaticTile() override = default;

		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z) override;
		void Draw(float x, float y, float z, const Rectangle& uvOffset) override;

		Sprite* GetSprite() const;
		void setSprite(Sprite* const sprite);

	private:
		Sprite* _sprite;
	};
}
