//==========================================================
// En-têtes
//==========================================================

#include "Game/GameComponent.h"
#include "Game/Game.h"


namespace CasaEngine
{
	Game* IGameComponent::GetGame() const { return m_pGame; }

	IGameComponent::IGameComponent(Game* pGame_) :
		m_Initialized(false)
	{
		m_pGame = pGame_;
	}

	IGameComponent::~IGameComponent()
	{
		m_pGame->RemoveComponent(this);
	}

	int IGameComponent::UpdateOrder() const 
	{ 
		return m_UpdateOrder;
	}

	void IGameComponent::UpdateOrder(int val) 
	{ 
		m_UpdateOrder = val;
		//UpdateOrderChanged.Invoke(this, val);
	}

	bool IGameComponent::IsInitialized() const 
	{ 
		return m_Initialized; 
	}

	void IGameComponent::Initialize()
	{
		m_Initialized = true;
	}

}
