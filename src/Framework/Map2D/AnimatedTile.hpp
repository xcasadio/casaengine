#pragma once

#include  "Tile.hpp"
#include  "Animations/Animation2D.hpp"
#include  "Datas/TileSetData.hpp"

namespace CasaEngine
{
	class CA_EXPORT AnimatedTile : public ITile
	{
	public:
		explicit AnimatedTile(Animation2D* animation, AnimatedTileData* _tileData);
		~AnimatedTile() override = default;

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw(float x, float y, float z) override;
		void Draw(float x, float y, float z, const Rectangle& uvOffset) override;

		TileData* GetTileData() override;

		Animation2D* GetAnimation() const;
		void SetAnimation(Animation2D* const pAnimation);

	private:
		Animation2D* _animation;
		AnimatedTileData* _tileData;
	};
}
