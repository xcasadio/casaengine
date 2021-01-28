//==========================================================
// En-têtes
//==========================================================

#include "Game/DrawableGameComponent.h"
#include "Game/GameComponent.h"
#include "Game/Game.h"

namespace CasaEngine
{
	DrawableGameComponent::DrawableGameComponent(Game* pGame_) : 
		IGameComponent(pGame_),
		m_DrawOrder(0)
	{

	}

	DrawableGameComponent::~DrawableGameComponent()
	{
	}

	void DrawableGameComponent::OnLoadContent() 
	{ 
	}

	int DrawableGameComponent::DrawOrder() const 
	{ 
		return m_DrawOrder; 
	}

	void DrawableGameComponent::DrawOrder(int val) 
	{ 
		m_DrawOrder = val;
		//DrawOrderChanged.Invoke(this, val);
	}

}
