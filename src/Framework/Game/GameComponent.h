
#ifndef _GAMECOMPONENT_H_
#define _GAMECOMPONENT_H_

#include "CA_Export.h"
#include "GameTime.h"
#include "Memory/MemoryAllocation.h"

namespace CasaEngine
{
	class Game;

	/////////////////////////////////////////////////////////////
	/// CGameComponent
	/////////////////////////////////////////////////////////////
	class CA_EXPORT IGameComponent :
		public AllocatedObject<IGameComponent>
	{
	public:
		Game* GetGame() const;

		virtual void Initialize();
		virtual void Update(const GameTime& gameTime_) = 0;
		int UpdateOrder() const;
		void UpdateOrder(int val);
		bool IsInitialized() const;

		//EventHandler<int> UpdateOrderChanged;

	protected:
		IGameComponent(Game* pGame_);
		virtual ~IGameComponent();

	private:
		Game* m_pGame;		
		int m_UpdateOrder;
		bool m_Initialized;
	};
}

#endif // _GAMECOMPONENT_H_
