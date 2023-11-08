#pragma once

#include "CA_Export.hpp"
#include  "GameComponent.hpp"
#include  "GameTime.hpp"

namespace CasaEngine
{
	class Game;

	class CA_EXPORT DrawableGameComponent :
		public IGameComponent
	{
	public:
		virtual void OnLoadContent();
		virtual void Draw() = 0;

		int DrawOrder() const;
		void DrawOrder(int val);

	protected:
		DrawableGameComponent(Game* pGame_);

		void Update(const GameTime& gameTime_) override = 0;

	private:
		int m_DrawOrder;
	};

}
