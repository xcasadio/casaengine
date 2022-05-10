#pragma once

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
		virtual void Draw(float x, float y, float z) = 0;
		virtual void Draw(float x, float y, float z, RectangleI uvOffset) = 0;

		void IsWall(bool val);
		bool IsWall() const;

	protected:
		ITile();
		~ITile() = default;
		void Draw(const Sprite* sprite, float x, float y, float z, const RectangleI& uvOffset) const;

	private:
		SpriteRenderer* _spriteRenderer = nullptr;
		bool _isWall;
	};
}
