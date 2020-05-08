#ifndef STATICTILE_H_
#define STATICTILE_H_

#include "Tile.h"
#include "Sprite/Sprite.h"
#include "Sprite/SpriteRenderer.h"

namespace CasaEngine
{
	class CA_EXPORT StaticTile : public ITile
	{
	public:
		explicit StaticTile(Sprite* pSprite);

		virtual ~StaticTile() = default;
		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z, CRectangleI& textCoordOffset) override;

		Sprite* GetSprite() const;
		void setSprite(Sprite* const pSprite);

	private:
		Sprite* m_pSprite;
	};
}

#endif
