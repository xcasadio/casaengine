#pragma once

#include "CA_Export.hpp"
#include  "GameTime.hpp"


namespace CasaEngine
{
	class Game;

	class CA_EXPORT IGameComponent
	{
	public:
		Game* GetGame() const;

		virtual void Initialize();
		virtual void Update(const GameTime& gameTime_) = 0;
		int UpdateOrder() const;
		void UpdateOrder(int val);
		bool IsInitialized() const;

	protected:
		IGameComponent(Game* pGame_);
		virtual ~IGameComponent();

	private:
		Game* m_pGame;
		int m_UpdateOrder;
		bool m_Initialized;
	};
}
