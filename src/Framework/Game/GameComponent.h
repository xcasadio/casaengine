#ifndef _GAMECOMPONENT_H_
#define _GAMECOMPONENT_H_

#include "CA_Export.h"
#include "GameTime.h"


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

#endif
