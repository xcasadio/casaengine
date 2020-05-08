#ifndef TILE_H_
#define TILE_H_

#include <GameTime.h>

#include "Maths/Rectangle.h"
#include "Sprite/SpriteRenderer.h"


namespace CasaEngine
{
	class CA_EXPORT ITile
	{
	public:
		virtual void Initialize();
		virtual void Update(const GameTime& gameTime_) = 0;
		virtual void Draw(float x, float y, float z, CRectangleI& textCoordOffset) = 0;

	protected:
		~ITile() = default;
		void Draw(Sprite* pSprite, float x, float y, float z, CRectangleI& textCoordOffset) const;

	private:
		SpriteRenderer* m_pSpriteRenderer = nullptr;
	};

}

#endif
