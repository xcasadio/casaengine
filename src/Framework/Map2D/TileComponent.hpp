#pragma once

#include  "Entities/BaseEntity.hpp"
#include  "Entities/Component.hpp"
#include  "Tile.hpp"

namespace CasaEngine
{
	class CA_EXPORT TileComponent :
		public Component
	{
	public:
		TileComponent(BaseEntity* entity_);

		void Initialize() override;
		void Update(const GameTime& gameTime_) override;
		void Draw() override;

		ITile* Tile() const;
		void Tile(ITile* val);

	private:
		ITile* _tile;
	};
}
