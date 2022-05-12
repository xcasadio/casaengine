#pragma once

#include "Tile.h"
#include "Animations/Animation2D.h"

namespace CasaEngine
{
	class CA_EXPORT AnimatedTile : public ITile
	{
	public:
		explicit AnimatedTile(Animation2D* pAnimation);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z) override;
		void Draw(float x, float y, float z, Rectangle uvOffset) override;

		Animation2D* GetAnimation() const;
		void SetAnimation(Animation2D* const pAnimation);

	private:
		Animation2D* m_pAnimation;
	};
}
